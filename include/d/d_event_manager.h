#ifndef D_EVENT_D_EVENT_MANAGER_H
#define D_EVENT_D_EVENT_MANAGER_H

#include "SSystem/SComponent/c_xyz.h"
#include "d/d_event_data.h"

class fopAc_ac_c;

class dEvent_exception_c {
public:
    dEvent_exception_c() { mEventInfoIdx = -1; }
    void init();
    int setStartDemo(int eventInfoIdx);
    const char* getEventName();

    /* 0x0 */ s32 mEventInfoIdx;
    /* 0x4 */ s32 field_0x4;
    /* 0x8 */ s32 mState;
};

class dEvent_manager_c {
public:
    dEvent_manager_c() {}
    ~dEvent_manager_c() {}

    void debugBfProc();
    void* getSubstance(dEvDtData_c*, int);
    void setData(const char*);
    BOOL create();
    void remove();
    void startProc(dEvDtEvent_c*);
    void closeProc(dEvDtEvent_c*);
    void endProc(s16, int);
    void mainProc();
    void runProc();
    dEvDtEvent_c* getEventData(s16);
    s16 getEventIdx(const char*, u8);
    BOOL order(s16);
    BOOL startCheck(s16);
    BOOL startCheckOld(const char*);
    BOOL endCheck(s16);
    BOOL endCheckOld(const char*);
    int getMyStaffId(const char*, fopAc_ac_c*, int);
    BOOL getIsAddvance(int);
    int getMyActIdx(int staffIdx, const char* const* action, int actionNum, BOOL force, int nameType);
    char* getMyActName(int);
    char* getMyNowCutName(int);
    dEvDtData_c* getMyDataP(int, const char*, int);
    void* getMySubstanceP(int, const char*, int);
    s32 getMySubstanceNum(int, const char*);
    void cutEnd(int);
    u32 getEventPrio(s16);
    u8 getEventEndSound(s16);
    void exceptionProc();
    void issueStaff(const char*);
    void cancelStaff(const char*);
    void setGoal(cXyz*);
    cXyz* getGoal();
    fopAc_ac_c* specialCast_Shutter(s16, int);
    fopAc_ac_c* specialCast(const char*, int);
    void setPrmStaff(void*, int);
    u8 getToolId(u8, int);
    BOOL ChkPresentEnd();
    BOOL CancelPresent();
    BOOL checkStartDemo();
    dEvDtFlag_c& getFlags() { return mFlag; }

    int setStartDemo(int eventInfoIdx) { return mException.setStartDemo(eventInfoIdx); }
    void cancelStartDemo() { mException.init(); }
    void setCameraPlay(int v) { mCameraPlay = v; }
    int cameraPlay() { return mCameraPlay; }

    /* 0x000 */ dEvDtBase_c mList;
    /* 0x020 */ u32 mCameraPlay;
    /* 0x024 */ dEvent_exception_c mException;
    /* 0x030 */ cXyz mGoal;
    /* 0x03C */ dEvDtFlag_c mFlag;
};

class dEv_seach_prm {
public:
    dEv_seach_prm(const char*, u32, u32);

public:
    /* 0x00 */ const char* mName;
    /* 0x04 */ u32 mMask;
    /* 0x08 */ u32 mValue;
    /* 0x0C */ u16 mCastInFlag;
};

int dEv_extra_createCB(void* actor);

#endif /* D_EVENT_D_EVENT_MANAGER_H */
