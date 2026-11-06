#include "dolphin/exi/EXIUart.h"
#include "dolphin/os/OS.h"

static s32 Chan;
static u32 Dev;
static u32 Enabled;
static u32 BarnacleEnabled;

// prototypes
int InitializeUART(void);
int ReadUARTN(void);
int WriteUARTN(void *buf, u32 len);

int InitializeUART(void) {
    if (BarnacleEnabled == 0xA5FF005A) {
        return 0;
    }

    if ((OSGetConsoleType() & 0x10000000) == 0) {
        Enabled = 0;
        return 2;
    }

    Chan = 0;
    Dev = 1;
    Enabled = 0xA5FF005A;
    return 0;
}

int ReadUARTN(void) {
    return 4;
}

static int QueueLength(void) {
    u32 cmd;

    if (EXISelect(Chan, Dev, 3) == 0) {
        return -1;
    }

    cmd = 0x20010000;
    EXIImm(Chan, &cmd, sizeof(cmd), EXI_WRITE, 0);
    EXISync(Chan);
    EXIImm(Chan, &cmd, 1, EXI_READ, 0);
    EXISync(Chan);
    EXIDeselect(Chan);
    return 0x10 - (cmd >> 0x18);
}

int WriteUARTN(void *buf, u32 len) {
    u32 cmd;
    s32 xLen;
    int qLen;
    char* ptr;
    int locked;
    int error;

    if ((Enabled - 0xA5FF0000) != 0x5A) {
        return 2;
    }

    locked = EXILock(Chan, Dev, 0);
    if (locked == 0) {
        return 0;
    } else {
        ptr = (char*)buf;
    }

    while ((u32)ptr - (u32)buf < len) {
        if (*(s8*)ptr == 0xA) {
            *ptr = 0xD;
        }
        ptr++;
    }
    error = 0;
    cmd = 0xA0010000;

    while (len != 0) {
        qLen = QueueLength();
        if (qLen < 0) {
            error = 3;
            break;
        }
        
        if ((qLen >= 0xC) || (qLen >= len)) {
            if (EXISelect(Chan, Dev, EXI_FREQ_8M) == 0) {
                error = 3;
                break;
            }
            
            EXIImm(Chan, &cmd, sizeof(cmd), EXI_WRITE, 0);
            EXISync(Chan);

            while((qLen != 0) && (len != 0)) {
                if ((qLen < 4) && (qLen < len)) {
                    break;
                }

                xLen = len < 4 ? (long)len : 4;
                
                EXIImm(Chan, buf, xLen, EXI_WRITE, 0);
                (char*)buf += xLen;
                len -= xLen;
                qLen -= xLen;
                EXISync(Chan);
            }
            EXIDeselect(Chan);
        }
    }

    EXIUnlock(Chan);
    return error;
}
