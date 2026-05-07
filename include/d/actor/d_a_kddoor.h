#ifndef D_A_KDDOOR_H
#define D_A_KDDOOR_H

#include "f_op/f_op_actor.h"
#include "d/d_door.h"
#include "d/d_kankyo.h"

class dBgW;

class dDoor_ssk_sub_c {
public:
    dDoor_ssk_sub_c();
    void init();
    void end();
    void openInit();
    BOOL openProc(dDoor_info_c*);
    void closeInit();
    BOOL closeProc(dDoor_info_c*);
    void calcMtx(dDoor_info_c*, f32, f32, u8);
    BOOL drawSet();

public:
    /* 0x000 */ mDoExt_McaMorf* mpModel;
    /* 0x004 */ mDoExt_McaMorf* mpMorf;
    /* 0x008 */ dPa_smokeEcallBack mSmokeCb;
    /* 0x028 */ dCcD_Stts mStts;
    /* 0x064 */ dCcD_Cyl mCyl;
    /* 0x194 */ u8 m194;
    /* 0x195 */ u8 m195;
    /* 0x196 */ s16 m196;
    /* 0x198 */ s16 m198;
    /* 0x19A */ s16 m19A;
    /* 0x19C */ s16 m19C;
    /* 0x19E */ s16 m19E;
    /* 0x1A0 */ f32 m1A0;
    /* 0x1A4 */ f32 m1A4;
    /* 0x1A8 */ f32 m1A8;
    /* 0x1AC */ f32 m1AC;
    /* 0x1B0 */ f32 m1B0;
    /* 0x1B4 */ f32 m1B4;
    /* 0x1B8 */ cXyz m1B8;
    /* 0x1C4 */ u8 m1C4;
    /* 0x1C5 */ u8 m1C5;
};  // Size: 0x1C8

class dDoor_ssk_c {
public:
    void init(dDoor_info_c*);
    void end();
    void calcMtx(dDoor_info_c*);
    void execute(dDoor_info_c*);
    void draw(dDoor_info_c*);
    void closeInit();
    BOOL closeProc(dDoor_info_c*);
    void openInit();
    BOOL openProc(dDoor_info_c*);

public:
    /* 0x000 */ dDoor_ssk_sub_c mSub[3];
    /* 0x558 */ u8 m8;
    /* 0x559 */ u8 m9;
    /* 0x55A */ u8 mA;
    /* 0x55B */ u8 mB;
    /* 0x55C */ dKy_tevstr_c mTevStr;
};  // Size: 0x60C

class daKddoor_c : public dDoor_info_c {
public:
    bool checkFlag(u16 flag) { return mFlags & flag; }
    void offFlag(u16 flag) { mFlags &= ~flag; }
    void onFlag(u16 flag) { mFlags |= flag; }
    void setAction(int i_action) { mAction = i_action; }

    BOOL CreateHeap();
    void setKey();
    void setStop();
    void setStopDemo();
    BOOL chkMakeKey();
    BOOL chkMakeStop();
    s32 chkStopF();
    s32 chkStopB();
    BOOL chkGenocideCase();
    BOOL chkFeelerCase();
    BOOL chkStopOpen();
    BOOL chkStopClose();
    const char* getBmdName();
    const char* getBmdName2();
    const char* getDzbName();

    void setEventPrm();
    void openInit();
    BOOL openProc();
    void openEnd();
    void closeInit();
    BOOL closeProc();
    void closeEnd();
    void calcMtx();
    int CreateInit();
    cPhs_State create();
    int execute();
    void demoProc();
    BOOL draw();

    static const char M_arcname[];

public:
    /* 0x2D0 */ request_of_phase_process_class mPhase;
    /* 0x2D8 */ dDoor_smoke_c mSmoke;
    /* 0x310 */ dDoor_key2_c mKeyLock;
    /* 0x334 */ dDoor_ssk_c mStopBars;
    /* 0x940 */ J3DModel* mpModel;
    /* 0x944 */ union {
        dBgW* mpBgW;
        struct {
            u8 m944;
            u8 m945;
            u16 m946;
        } m_bgw_union;
    };
    /* 0x948 */ u8 mAction;
    /* 0x949 */ u8 m949;
    /* 0x94A */ u16 mFlags;
    /* 0x94C */ f32 m94C;
};

#endif /* D_A_KDDOOR_H */
