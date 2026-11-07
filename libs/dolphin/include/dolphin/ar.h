#ifndef AR_H
#define AR_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ARCallback)(void);

ARCallback ARRegisterDMACallback(ARCallback callback);
u32 ARGetDMAStatus(void);
void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length);
u32 ARInit(u32* stack_index_addr, u32 num_entries);
u32 ARAlloc(u32 length);
u32 ARGetBaseAddress();
u32 ARGetSize(void);

#define ARQ_CHUNK_SIZE_DEFAULT 4096

typedef void (*ARQCallback)(uintptr_t request_address);

typedef enum _ARamType {
    ARAM_DIR_MRAM_TO_ARAM,
    ARAM_DIR_ARAM_TO_MRAM,
} ARamType;

typedef enum _ArqPriotity {
    ARQ_PRIORITY_LOW,
    ARQ_PRIORITY_HIGH,
} ArqPriotity;

typedef struct ARQRequest {
    struct ARQRequest* next;
    u32 owner;
    u32 type;
    u32 priority;
    u32 source;
    u32 destination;
    u32 length;
    ARQCallback callback;
} ARQRequest;

void ARQInit(void);
void ARQPostRequest(ARQRequest* task, u32 owner, u32 type, u32 priority, u32 source,
                    u32 destination, u32 length, ARQCallback callback);

#ifdef __cplusplus
};
#endif

#endif /* AR_H */
