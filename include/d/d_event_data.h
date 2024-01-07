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

class dEvDtData_c {
public:
    /* 0x00 */ char mName[32];
    /* 0x20 */ s32 mIndex;
    /* 0x24 */ s32 mSubstanceType;
    /* 0x28 */ s32 mSubstanceIdx;
    /* 0x2C */ s32 mSubstanceSize;
    /* 0x30 */ s32 mNextIdx;
    /* 0x34 */ u32 field_0x34[3];

    char* getName() { return mName; }
    s32 getNext() { return mNextIdx; }
    s32 getNumber() { return mSubstanceSize; }
    s32 getIndex() { return mSubstanceIdx; }
    s32 getType() { return mSubstanceType; }
}; // Size: 0x40

class dEvDtCut_c {
public:
    s32 startCheck();
    s32 getNext() { return mNextCutIdx; }
    u32 getFlagId() { return mFlagIdx; }
    u32 getTagId() { return mTagId; }
    u32 getStartFlag(int idx) { return mStartFlag[idx]; }
    u32 getDataTop() { return mFirstDataIdx; }
    char* getName() { return mName; }

public:
    /* 0x00 */ char mName[32];
    /* 0x20 */ u32 mTagId;
    /* 0x24 */ u32 mIndex;
    /* 0x28 */ u32 mStartFlag[3];
    /* 0x34 */ u32 mFlagIdx;
    /* 0x38 */ u32 mFirstDataIdx;
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

    const char* getName() { return mName; }
    u32 getStartCut() { return mFirstCutIdx; }
    u32 getCurrentCut() { return mCurCutIdx; }
    s32 getType() { return mStaffType; }
    s32 getTagID() { return mTagID; }

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
    /* 0x20 */ int mTagID;
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
    /* 0x47 */ u8 mbHasAction;
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
    u8 getEndSound() { return mEventEndSound; }

    enum {
        NONE_e,
        ORDER_e,
        PLAY_e,
        UNK3_e,
        CLOSE_e,
    };

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
    /* 0xA4 */ s32 mEventState;
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

    event_binary_data_header* getHeaderP() { return mHeaderP; }
    dEvDtStaff_c* getStaffP(int i) { return &mStaffP[i]; }
    dEvDtEvent_c* getEventP(int i) { return &mEventP[i]; }
    dEvDtData_c* getDataP(int i) { return &mDataP[i]; }
    dEvDtCut_c* getCutP(int i) { return &mCutP[i]; }
    char* getEventName(int i) { return mEventP[i].getName(); }
    int getStaffCurrentCut(int i) { return mStaffP[i].getCurrentCut(); }
    dEvDtCut_c* getCutStaffCurrentCutP(int i) { return getCutP(getStaffCurrentCut(i)); }
    int getStaffStartCut(int i) { return mStaffP[i].getStartCut(); }
    dEvDtCut_c* getCutStaffStartCutP(int i) { return getCutP(getStaffStartCut(i)); }
    int* getIDataP(int i) { return &mIDataP[i]; }
    f32* getFDataP(int i) { return &mFDataP[i]; }
    char* getSDataP(int i) { return &mSDataP[i]; }
    u32 getEventTop() { return mHeaderP->eventTop; }
    s32 getEventNum() { return mHeaderP->eventNum; }
    u32 getStaffTop() { return mHeaderP->staffTop; }
    s32 getStaffNum() { return mHeaderP->staffNum; }
    u32 getCutTop() { return mHeaderP->cutTop; }
    s32 getCutNum() { return mHeaderP->cutNum; }
    u32 getDataTop() { return mHeaderP->dataTop; }
    s32 getDataNum() { return mHeaderP->dataNum; }
    u32 getFDataTop() { return mHeaderP->fDataTop; }
    s32 getFDataNum() { return mHeaderP->fDataNum; }
    u32 getIDataTop() { return mHeaderP->iDataTop; }
    s32 getIDataNum() { return mHeaderP->iDataNum; }
    u32 getSDataTop() { return mHeaderP->sDataTop; }
    s32 getSDataNum() { return mHeaderP->sDataNum; }

    void setHeaderP(event_binary_data_header* p_header) { mHeaderP = p_header; }
    void setEventP(dEvDtEvent_c* p_event) { mEventP = p_event; }
    void setStaffP(dEvDtStaff_c* p_staff) { mStaffP = p_staff; }
    void setCutP(dEvDtCut_c* p_cut) { mCutP = p_cut; }
    void setDataP(dEvDtData_c* p_data) { mDataP = p_data; }
    void setFDataP(f32* p_fdata) { mFDataP = p_fdata; }
    void setIDataP(int* p_idata) { mIDataP = p_idata; }
    void setSDataP(char* p_sdata) { mSDataP = p_sdata; }

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
