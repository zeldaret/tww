#include "dolphin/os/OSMutex.h"
#include "dolphin/os/OS.h"

#define PushTail(queue, mutex, link)                                                               \
    do {                                                                                           \
        OSMutex* __prev;                                                                           \
                                                                                                   \
        __prev = (queue)->tail;                                                                    \
        if (__prev == NULL)                                                                        \
            (queue)->head = (mutex);                                                               \
        else                                                                                       \
            __prev->link.next = (mutex);                                                           \
        (mutex)->link.prev = __prev;                                                               \
        (mutex)->link.next = NULL;                                                                 \
        (queue)->tail = (mutex);                                                                   \
    } while (0)

#define PopHead(queue, mutex, link)                                                                \
    do {                                                                                           \
        OSMutex* __next;                                                                           \
                                                                                                   \
        (mutex) = (queue)->head;                                                                   \
        __next = (mutex)->link.next;                                                               \
        if (__next == NULL)                                                                        \
            (queue)->tail = NULL;                                                                  \
        else                                                                                       \
            __next->link.prev = NULL;                                                              \
        (queue)->head = __next;                                                                    \
    } while (0)

#define PopItem(queue, mutex, link)                                                                \
    do {                                                                                           \
        OSMutex* __next;                                                                           \
        OSMutex* __prev;                                                                           \
                                                                                                   \
        __next = (mutex)->link.next;                                                               \
        __prev = (mutex)->link.prev;                                                               \
                                                                                                   \
        if (__next == NULL)                                                                        \
            (queue)->tail = __prev;                                                                \
        else                                                                                       \
            __next->link.prev = __prev;                                                            \
                                                                                                   \
        if (__prev == NULL)                                                                        \
            (queue)->head = __next;                                                                \
        else                                                                                       \
            __prev->link.next = __next;                                                            \
    } while (0)

//
// Declarations:
//

void OSInitMutex(OSMutex* mutex) {
    OSInitThreadQueue(&mutex->queue);
    mutex->thread = 0;
    mutex->count = 0;
}

void OSLockMutex(OSMutex* mutex) {
    BOOL enabled = OSDisableInterrupts();
    OSThread* currentThread = OSGetCurrentThread();
    OSThread* ownerThread;

    while (TRUE) {
        ownerThread = ((OSMutex*)mutex)->thread;
        if (ownerThread == 0) {
            mutex->thread = currentThread;
            mutex->count++;
            PushTail(&currentThread->owned_mutexes, mutex, link);
            break;
        } else if (ownerThread == currentThread) {
            mutex->count++;
            break;
        } else {
            currentThread->mutex = mutex;
            __OSPromoteThread(mutex->thread, currentThread->effective_priority);
            OSSleepThread(&mutex->queue);
            currentThread->mutex = 0;
        }
    }
    OSRestoreInterrupts(enabled);
}

void OSUnlockMutex(OSMutex* mutex) {
    BOOL enabled = OSDisableInterrupts();
    OSThread* currentThread = OSGetCurrentThread();

    if (mutex->thread == currentThread && --mutex->count == 0) {
        PopItem(&currentThread->owned_mutexes, mutex, link);
        mutex->thread = NULL;
        if ((s32)currentThread->effective_priority < (s32)currentThread->base_priority) {
            currentThread->effective_priority = __OSGetEffectivePriority(currentThread);
        }

        OSWakeupThread(&mutex->queue);
    }
    OSRestoreInterrupts(enabled);
}

void __OSUnlockAllMutex(OSThread* thread) {
    OSMutex* mutex;

    while (thread->owned_mutexes.head) {
        PopHead(&thread->owned_mutexes, mutex, link);
        mutex->count = 0;
        mutex->thread = NULL;
        OSWakeupThread(&mutex->queue);
    }
}


BOOL OSTryLockMutex(OSMutex* mutex) {
    BOOL enabled = OSDisableInterrupts();
    OSThread* currentThread = OSGetCurrentThread();
    BOOL locked;
    if (mutex->thread == 0) {
        mutex->thread = currentThread;
        mutex->count++;
        PushTail(&currentThread->owned_mutexes, mutex, link);
        locked = TRUE;
    } else if (mutex->thread == currentThread) {
        mutex->count++;
        locked = TRUE;
    } else {
        locked = FALSE;
    }
    OSRestoreInterrupts(enabled);
    return locked;
}

void OSInitCond(OSCond* cond) { OSInitThreadQueue(&cond->queue); }

void OSWaitCond(OSCond* cond, OSMutex* mutex) {
    BOOL enabled = OSDisableInterrupts();
    OSThread* currentThread = OSGetCurrentThread();
    s32 count;

    if (mutex->thread == currentThread) {
        count = mutex->count;
        mutex->count = 0;
        PopItem(&currentThread->owned_mutexes, mutex, link);
        mutex->thread = NULL;

        if (currentThread->effective_priority < (s32)currentThread->base_priority) {
            currentThread->effective_priority = __OSGetEffectivePriority(currentThread);
        }

        OSDisableScheduler();
        OSWakeupThread(&mutex->queue);
        OSEnableScheduler();
        OSSleepThread(&cond->queue);
        OSLockMutex(mutex);
        mutex->count = count;
    }

    OSRestoreInterrupts(enabled);
}

void OSSignalCond(OSCond* cond) {
    OSWakeupThread(&cond->queue);
}

static BOOL IsMember(OSMutexQueue* queue, OSMutex* mutex) {
    OSMutex* member;

    for (member = queue->head; member; member = member->link.next) {
        if (mutex == member)
            return TRUE;
    }
    return FALSE;
}

BOOL __OSCheckMutex(OSMutex* mutex) {
    OSThread* thread;
    OSThreadQueue* queue;
    OSPriority priority = 0;

    queue = &mutex->queue;
    if (!(queue->head == NULL || queue->head->link.prev == NULL))
        return FALSE;
    if (!(queue->tail == NULL || queue->tail->link.next == NULL))
        return FALSE;
    for (thread = queue->head; thread; thread = thread->link.next) {
        if (!(thread->link.next == NULL || thread == thread->link.next->link.prev))
            return FALSE;
        if (!(thread->link.prev == NULL || thread == thread->link.prev->link.next))
            return FALSE;

        if (thread->state != OS_THREAD_STATE_WAITING)
            return FALSE;

        if (thread->effective_priority < priority)
            return FALSE;
        priority = thread->effective_priority;
    }

    if (mutex->thread) {
        if (mutex->count <= 0)
            return FALSE;
    } else {
        if (0 != mutex->count)
            return FALSE;
    }

    return TRUE;
}

BOOL __OSCheckDeadLock(OSThread* thread) {
    OSMutex* mutex;

    mutex = thread->mutex;
    while (mutex && mutex->thread) {
        if (mutex->thread == thread)
            return TRUE;
        mutex = mutex->thread->mutex;
    }
    return FALSE;
}

BOOL __OSCheckMutexes(OSThread* thread) {
    OSMutex* mutex;

    for (mutex = thread->owned_mutexes.head; mutex; mutex = mutex->link.next) {
        if (mutex->thread != thread)
            return FALSE;
        if (!__OSCheckMutex(mutex))
            return FALSE;
    }
    return TRUE;
}
