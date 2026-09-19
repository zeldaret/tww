#include "dolphin/dsp.h"

DSPTaskInfo* __DSP_curr_task;
DSPTaskInfo* __DSP_first_task;
DSPTaskInfo* __DSP_last_task;
DSPTaskInfo* __DSP_tmp_task;

void __DSP_exec_task(DSPTaskInfo* curr, DSPTaskInfo* next) {
    ASSERTMSGLINE(552, next != NULL, "__DSP_exec_task(): NULL task. It is to weep.\n");

    if (curr != NULL) {
        DSPSendMailToDSP((u32)curr->dram_mmem_addr);
        while (DSPCheckMailToDSP() != 0)
            ;
        DSPSendMailToDSP(curr->dram_length);
        while (DSPCheckMailToDSP() != 0)
            ;
        DSPSendMailToDSP(curr->dram_addr);
        while (DSPCheckMailToDSP() != 0)
            ;
    } else {
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0)
            ;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0)
            ;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0)
            ;
    }

    DSPSendMailToDSP((u32)next->iram_mmem_addr);
    while (DSPCheckMailToDSP() != 0)
        ;

    DSPSendMailToDSP(next->iram_length);
    while (DSPCheckMailToDSP() != 0)
        ;

    DSPSendMailToDSP(next->iram_addr);
    while (DSPCheckMailToDSP() != 0)
        ;

    if (next->state == 0) {
        DSPSendMailToDSP(next->dsp_init_vector);
        while (DSPCheckMailToDSP() != 0)
            ;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0)
            ;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0)
            ;
        DSPSendMailToDSP(0);
        while (DSPCheckMailToDSP() != 0)
            ;
    } else {
        DSPSendMailToDSP(next->dsp_resume_vector);
        while (DSPCheckMailToDSP() != 0)
            ;

        DSPSendMailToDSP((u32)next->dram_mmem_addr);
        while (DSPCheckMailToDSP() != 0)
            ;

        DSPSendMailToDSP(next->dram_length);
        while (DSPCheckMailToDSP() != 0)
            ;

        DSPSendMailToDSP(next->dram_addr);
        while (DSPCheckMailToDSP() != 0)
            ;
    }
}

void __DSP_boot_task(DSPTaskInfo* task) {
    volatile u32 mail;

    ASSERTMSGLINE(634, task != NULL, "__DSP_boot_task(): NULL task!\n");
    while (DSPCheckMailFromDSP() == 0)
        ;

    mail = DSPReadMailFromDSP();
    ASSERTMSGLINEV(640, mail == 0x8071FEED, "__DSP_boot_task(): Failed to sync DSP on boot! (0x%08X)\n", mail);

    DSPSendMailToDSP(0x80F3A001);
    while (DSPCheckMailToDSP() != 0)
        ;

    DSPSendMailToDSP((u32)task->iram_mmem_addr);
    while (DSPCheckMailToDSP() != 0)
        ;

    DSPSendMailToDSP(0x80F3C002);
    while (DSPCheckMailToDSP() != 0)
        ;

    DSPSendMailToDSP(task->iram_addr & 0xFFFF);
    while (DSPCheckMailToDSP() != 0)
        ;

    DSPSendMailToDSP(0x80F3A002);
    while (DSPCheckMailToDSP() != 0)
        ;

    DSPSendMailToDSP(task->iram_length);
    while (DSPCheckMailToDSP() != 0)
        ;

    DSPSendMailToDSP(0x80F3B002);
    while (DSPCheckMailToDSP() != 0)
        ;

    DSPSendMailToDSP(0);
    while (DSPCheckMailToDSP() != 0)
        ;

    DSPSendMailToDSP(0x80F3D001);
    while (DSPCheckMailToDSP() != 0)
        ;

    DSPSendMailToDSP(task->dsp_init_vector);
    while (DSPCheckMailToDSP() != 0)
        ;

    __DSP_debug_printf("DSP is booting task: 0x%08X\n", (u32)task);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM MMEM ADDR: 0x%08X\n", (u32)task->iram_mmem_addr);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM DSP ADDR : 0x%08X\n", task->iram_addr);
    __DSP_debug_printf("__DSP_boot_task()  : IRAM LENGTH   : 0x%08X\n", task->iram_length);
    __DSP_debug_printf("__DSP_boot_task()  : DRAM MMEM ADDR: 0x%08X\n", task->dram_length);
    __DSP_debug_printf("__DSP_boot_task()  : Start Vector  : 0x%08X\n", task->dsp_init_vector);
}

void __DSP_insert_task(DSPTaskInfo* task) {
    DSPTaskInfo* temp;

    if (__DSP_first_task == NULL) {
        __DSP_curr_task = task;
        __DSP_first_task = __DSP_last_task = task;
        task->next = task->prev = NULL;
        return;
    }

    temp = __DSP_first_task;
    while (temp != NULL) {
        if (task->priority < temp->priority) {
            task->prev = temp->prev;
            temp->prev = task;
            task->next = temp;
            if (task->prev == NULL)
                __DSP_first_task = task;
            else
                task->prev->next = task;
            break;
        }
        temp = temp->next;
    }

    if (temp == NULL) {
        __DSP_last_task->next = task;
        task->next = NULL;
        task->prev = __DSP_last_task;
        __DSP_last_task = task;
    }
}

void __DSP_add_task(DSPTaskInfo* task) {
    ASSERTMSGLINE(771, task != NULL, "__DSP_add_task(): Why are you adding a NULL task?\n");

    if (__DSP_last_task == NULL) {
        __DSP_curr_task = task;
        __DSP_last_task = task;
        __DSP_first_task = task;
        task->next = task->prev = NULL;
    } else {
        __DSP_last_task->next = task;
        task->next = NULL;
        task->prev = __DSP_last_task;
        __DSP_last_task = task;
    }

    task->state = 0;
    __DSP_debug_printf("__DSP_add_task() : Added task    : 0x%08X\n", (u32)task);
}

void __DSP_remove_task(DSPTaskInfo* task) {
    ASSERTMSGLINE(813, task != NULL, "__DSP_remove_task(): NULL task! Why? WHY?!?!\n");
    task->flags = 0;
    task->state = 3;

    if (__DSP_first_task == task) {
        if (task->next != NULL) {
            __DSP_first_task = task->next;
            task->next->prev = NULL;
        }
        else
            __DSP_first_task = __DSP_last_task = __DSP_curr_task = NULL;
        return;
    }

    if (__DSP_last_task == task) {
        __DSP_last_task = task->prev;
        task->prev->next = NULL;
        __DSP_curr_task = __DSP_first_task;
        return;
    }

    __DSP_curr_task = task->next;
    task->prev->next = task->next;
    task->next->prev = task->prev;
}
