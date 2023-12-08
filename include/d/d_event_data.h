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
    s32 startCheck();
    s32 getNext() { return mNextCutIdx; }
    u32 getFlagId() { return mFlagIdx; }
    u32 getTagId() { return mTagId; }

public:
    /* 0x00 */ char mName[32];
    /* 0x20 */ u32 mTagId;
    /* 0x24 */ u32 mIndex;
    /* 0x28 */ u32 mFlagCheck[3];
    /* 0x34 */ u32 mFlagIdx;
    /* 0x38 */ u32 field_0x38;
    /* 0x3C */ u32 mNextCutIdx;
    /* 0x40 */ u32 field_0x40[4];
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

    u32 getCurrentCut() { return mCurCutIdx; }

    enum StaffType_e {
        NORMAL_e,
        ALL_e,
        CAMERA_e,
        EFFECT_e,
        TIMEKEEPER_e,
        FIVE_e,
        DIRECTOR_e,
        MESSAGE_e,
        SOUND_e,
        LIGHT_e,
        TEN_e,
        PACKAGE_e,
        CREATE_e,
    };

public:
    /* 0x00 */ char mName[32];
    /* 0x20 */ int mSub;
    /* 0x24 */ int mStaffIdx;
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
    /* 0x46 */ u8 mAdvance;
    /* 0x47 */ u8 mbNeedsAction;
    /* 0x48 */ u8 field_48[0x50 - 0x48];
};  // Size: 0x50

class dEvDtEvent_c {
public:
    BOOL finish_check();
    void specialStaffProc(dEvDtStaff_c*);

    char * getName() { return mName; }
    u32 getStaff(int idx) { return mStaffIdx[idx]; }
    s32 getNStaff() { return mNStaff; }
    u32 getPriority() { return mPriority; }

public:
    /* 0x00 */ char mName[0x20];
    /* 0x20 */ u32 field_0x20;
    /* 0x24 */ u32 field_0x24;
    /* 0x28 */ u32 mPriority;
    /* 0x2C */ u32 mStaffIdx[20];
    /* 0x7C */ s32 mNStaff;
    /* 0x80 */ int mFlagCheckStart[2];
    /* 0x88 */ int mFlagCheckFinish[3];
    /* 0x94 */ u8 mEventEndSound;
    /* 0x98 */ u32 field_0x98;
    /* 0x9C */ u32 field_0x9c;
    /* 0xA0 */ u32 field_0xa0;
    /* 0xA4 */ u32 mEventState;
    /* 0xA8 */ u32 field_0xa8;
    /* 0xAC */ u32 field_0xac;
};

class dEvDtFlag_c {
public:
    dEvDtFlag_c() {}

    BOOL flagCheck(int);
    BOOL flagSet(int);
    BOOL flagMaxCheck(int);
    void init();

public:
    u32 mFlag[320];
    enum { FlagMax = 320 * 32 };
};  // Size = 0x500

class dEvDtBase_c {
public:
    dEvDtBase_c() { init(); }
    ~dEvDtBase_c() {}

    void init();
    void advanceCut(dEvDtEvent_c*);
    bool advanceCutLocal(dEvDtStaff_c*);

    dEvDtCut_c * getCutP(int idx) { return &mCutP[idx]; }

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
