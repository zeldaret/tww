#ifndef D_EVENT_D_EVENT_DATA_H
#define D_EVENT_D_EVENT_DATA_H

#include "global.h"

struct event_binary_data_header {
    /* 0x00 */ u32 eventTop;  // offset to Event chunk
    /* 0x04 */ s32 eventNum;
    /* 0x08 */ u32 staffTop;  // offset to Staff chunk
    /* 0x0C */ s32 staffNum;
    /* 0x10 */ u32 cutTop;  // offset to Cut chunk
    /* 0x14 */ s32 cutNum;
    /* 0x18 */ u32 dataTop;  // offset to Data chunk
    /* 0x1C */ s32 dataNum;
    /* 0x20 */ u32 fDataTop;  // offset to FData chunk
    /* 0x24 */ s32 fDataNum;
    /* 0x28 */ u32 iDataTop;  // offset to IData chunk
    /* 0x2C */ s32 iDataNum;
    /* 0x30 */ u32 sDataTop;  // offset to SData chunk
    /* 0x34 */ s32 sDataNum;
    /* 0x38 */ u8 unk[8];
};  // Size: 0x40

class dEvDtData_c {};

class dEvDtCut_c {
public:
    void startCheck();
};

class dEvDtStaff_c {
public:
    void specialProc_WaitStart(int);
    void specialProc_WaitProc(int);
    void specialProc();
    void init();
    void advanceCut(int);
    void specialProcLight();
    void specialProcMessage();
    void specialProcSound();
    void specialProcCreate();
    void specialProcDirector();
    void specialProcPackage();
    void specialProcTimekeeper();

public:
    /* 0x00 */ char mName[32];
    /* 0x20 */ int mSub;
    /* 0x24 */ int mIndex;
    /* 0x28 */ int m28;
    /* 0x2C */ int mStaffType;
    /* 0x30 */ int mFirstCutIdx;
    /* 0x34 */ u8 m34[0x38 - 0x34];
    /* 0x38 */ int mCurCutIdx;
    /* 0x3C */ u32 mCurActionIdx;
    /* 0x40 */ s16 mWipeDirection;
    /* 0x42 */ s16 mTimer;
    /* 0x44 */ u8 m44;
    /* 0x45 */ u8 m45;
    /* 0x46 */ u8 mbIsAdvance;
    /* 0x47 */ u8 mbNeedsAction;
    /* 0x48 */ u8 field_48[0x50 - 0x48];
};

class dEvDtEvent_c {
public:
    void finish_check();
    void specialStaffProc(dEvDtStaff_c*);
};

class dEvDtFlag_c {
public:
    dEvDtFlag_c() {}

    void flagCheck(int);
    void flagSet(int);
    void flagMaxCheck(int);
    void init();

public:
    u32 mFlags[320];
};  // Size = 0x500

class dEvDtBase_c {
public:
    dEvDtBase_c() { init(); }
    ~dEvDtBase_c() {}

    void init();
    void advanceCut(dEvDtEvent_c*);
    void advanceCutLocal(dEvDtStaff_c*);

public:
    /* 0x00 */ event_binary_data_header* mHeaderP;
    /* 0x04 */ dEvDtEvent_c* mEventP;
    /* 0x08 */ dEvDtStaff_c* mStaffP;
    /* 0x0C */ dEvDtCut_c* mCutP;
    /* 0x10 */ dEvDtData_c* mDataP;
    /* 0x14 */ f32* mFDataP;
    /* 0x18 */ int* mIDataP;
    /* 0x1C */ char* mSDataP;
};  // Size = 0x20

STATIC_ASSERT(sizeof(dEvDtBase_c) == 0x20);

#endif /* D_EVENT_D_EVENT_DATA_H */