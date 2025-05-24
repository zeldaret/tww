#ifndef M_DO_M_DO_RESET_H
#define M_DO_M_DO_RESET_H

#include "global.h"

void mDoRst_reset(int, u32, int);
void mDoRst_resetCallBack(int, void*);

extern u8 sDefaultDirection;

struct mDoRstData {
    /* 0x00 */ int mReset;
    /* 0x04 */ int mResetPrepare;
    /* 0x08 */ int m3ButtonReset;
    /* 0x0C */ int m3ButtonResetPort;
};  // Size = 0x10

class mDoRst {
public:
#if VERSION > VERSION_JPN
    static void set3ButtonResetPort(int port) { mResetData->m3ButtonResetPort = port; }
    static void off3ButtonReset() { mResetData->m3ButtonReset = 0; }
    static void offResetPrepare() { mResetData->mResetPrepare = 0; }
    static void offReset() {
        mResetData->mReset = 0;
        mResetData->mResetPrepare = 0;
    }
    static int isReset() { return mResetData->mReset; }
    static int get3ButtonResetPort() { return mResetData->m3ButtonResetPort; }
    static int is3ButtonReset() { return mResetData->m3ButtonReset; }
    static void onReset() { mResetData->mReset = 1; }
    static void on3ButtonReset() { mResetData->m3ButtonReset = 1; }

    static mDoRstData* getResetData() { return mResetData; }
    static void setResetData(mDoRstData* rstData) { mResetData = rstData; }

    static mDoRstData* mResetData;
#else
    static void set3ButtonResetPort(int port) { m3ButtonResetPort = port; }
    static void off3ButtonReset() { m3ButtonResetFlag = 0; }
    static void offResetPrepare() { mResetPrepare = 0; }
    static void offReset() {
        mResetFlag = 0;
        mResetPrepare = 0;
    }
    static int isReset() { return mResetFlag; }
    static int get3ButtonResetPort() { return m3ButtonResetPort; }
    static int is3ButtonReset() { return m3ButtonResetFlag; }
    static void onReset() { mResetFlag = 1; }
    static void on3ButtonReset() { m3ButtonResetFlag = 1; }

    static int mResetPrepare;
    static int mResetFlag;
    static int m3ButtonResetFlag;
    static int m3ButtonResetPort;
#endif
};

extern bool mDoDvdErr_initialized;

#endif /* M_DO_M_DO_RESET_H */
