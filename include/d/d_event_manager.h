#ifndef D_EVENT_D_EVENT_MANAGER_H
#define D_EVENT_D_EVENT_MANAGER_H

#include "SSystem/SComponent/c_xyz.h"
#include "d/d_event_data.h"
#include "MSL_C/string.h"

class fopAc_ac_c;

class dEvent_exception_c {
public:
    dEvent_exception_c() { mEventInfoIdx = -1; }
    void init();
    int setStartDemo(int eventInfoIdx);
    void getEventName();

    /* 0x0 */ s32 mEventInfoIdx;
    /* 0x4 */ u8 field_0x4;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ u8 field_0x6;
    /* 0x7 */ u8 field_0x7;
    /* 0x8 */ s32 mState;
};

class dEvent_manager_c {
public:
    dEvent_manager_c() {}
    ~dEvent_manager_c() {}

    void debugBfProc();
    void getSubstance(dEvDtData_c*, int);
    void setData(const char*);
    void create();
    void remove();
    void startProc(dEvDtEvent_c*);
    void closeProc(dEvDtEvent_c*);
    void endProc(s16, int);
    void mainProc();
    void runProc();
    dEvDtEvent_c* getEventData(s16);
    s16 getEventIdx(const char*, u8);
    void order(s16);
    BOOL startCheck(s16);
    BOOL startCheckOld(const char*);
    BOOL endCheck(s16);
    BOOL endCheckOld(const char*);
    int getMyStaffId(const char*, fopAc_ac_c*, int);
    BOOL getIsAddvance(int);
    int getMyActIdx(int, const char* const*, int, int, int);
    char* getMyActName(int);
    char* getMyNowCutName(int);
    void getMyDataP(int, const char*, int);
    void* getMySubstanceP(int, const char*, int);
    void getMySubstanceNum(int, const char*);
    void cutEnd(int);
    u16 getEventPrio(s16);
    void getEventEndSound(s16);
    void exceptionProc();
    void issueStaff(const char*);
    void cancelStaff(const char*);
    void setGoal(cXyz*);
    cXyz* getGoal();
    void specialCast_Shutter(s16, int);
    void specialCast(const char*, int);
    void setPrmStaff(void*, int);
    void getToolId(u8, int);
    BOOL ChkPresentEnd();
    void CancelPresent();
    BOOL checkStartDemo();
    dEvDtFlag_c& getFlags() { return mFlag; }

    int setStartDemo(int eventInfoIdx) { return mException.setStartDemo(eventInfoIdx); }
    void cancelStartDemo() { /* TODO */ }
    void setCameraPlay(u32 v) { mCameraPlay = v; }

    /* 0x000 */ dEvDtBase_c mList;
    /* 0x020 */ u32 mCameraPlay;
    /* 0x024 */ dEvent_exception_c mException;
    /* 0x030 */ cXyz mGoal;
    /* 0x03C */ dEvDtFlag_c mFlag;
};

class dEv_seach_prm {
public:
    dEv_seach_prm(const char*, u32, u32);
};

inline int dEvmng_strcmp(const char* s1, const char* s2) {
    return strcmp(s1, s2);
}

#endif /* D_EVENT_D_EVENT_MANAGER_H */
