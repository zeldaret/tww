#ifndef D_A_OBJ_WARPT_H
#define D_A_OBJ_WARPT_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"

class dBgW;

class daObj_Warpt_c : public fopAc_ac_c {
public:
    enum Proc_e {
        PROC_INIT_e,
        PROC_RUN_e,
    };

    void modeProcInit(int) {}

    BOOL _createHeap();
    bool createHutaHeap();
    bool createBodyHeap();
    void _ride(fopAc_ac_c*);
    bool isHuta();
    bool isSp();
    bool isOtherHuta();
    bool isRealHuta();
    void warp(int);
    void onWarpBit(u8);
    bool isWarpBit(u8);
    void setMtx();
    void initCollision();
    void setCollision();
    void breakHuta(int);
    void openHuta();
    void checkHitSE();
    void modeOpenInit();
    void modeOpen();
    void modeCloseInit();
    void modeClose();
    void modeBreakFireInit();
    void modeBreakFire();
    void modeEventWarpInit();
    void modeEventWarp();
    bool normalWarp();
    bool spWarp();
    void modeEventOpenInit();
    void modeEventOpen();
    void modeProc(Proc_e, int);
    bool _execute();
    bool _draw();
    void getArg();
    void createInit();
    cPhs_State _create();
    bool _delete();

    static const char m_arc_name[];
    static const u16 m_event_reg[];
    static const GXColor m_def_smoke_prm_color[];
    static const GXColor m_def_smoke_env_color[];
    static const dCcD_SrcCyl m_cyl_body_src;
    static const dCcD_SrcCyl m_cyl_huta_src;

public:
    /* 0x290 */ s32 m290;
    /* 0x294 */ u8 m294[0x298 - 0x294];
    /* 0x298 */ s32 m298;
    /* 0x29C */ s32 m29C;
    /* 0x2A0 */ s32 m2A0;
    /* 0x2A4 */ s32 m2A4;
    /* 0x2A8 */ s32 m2A8;
    /* 0x2AC */ s32 m2AC;
    /* 0x2B0 */ s32 m2B0;
    /* 0x2B4 */ s32 m2B4;
    /* 0x2B8 */ s32 m2B8;
    /* 0x2BC */ s32 m2BC;
    /* 0x2C0 */ s32 m2C0;
    /* 0x2C4 */ u8 m2C4;
    /* 0x2C5 */ u8 m2C5;
    /* 0x2C6 */ bool m2C6;
    /* 0x2C8 */ request_of_phase_process_class mPhase;
    /* 0x2D0 */ J3DModel* mpBodyModel;
    /* 0x2D4 */ J3DModel* mpLidModel1;
    /* 0x2D8 */ dBgW* mpBodyBgW1;
    /* 0x2DC */ Mtx m2DC;
    /* 0x30C */ dBgW* mpBodyBgW2;
    /* 0x310 */ Mtx m310;
    /* 0x340 */ dBgW* mpLidBgW;
    /* 0x344 */ Mtx m344;
    /* 0x374 */ J3DModel* mpLidModel2;
    /* 0x378 */ mDoExt_brkAnm mLidBrk;
    /* 0x390 */ dCcD_Stts mStts;
    /* 0x3CC */ dCcD_Cyl mCyl1;
    /* 0x4FC */ dCcD_Cyl mCyl2;
    /* 0x62C */ dBgS_ObjAcch mAcch;
    /* 0x7F0 */ dBgS_AcchCir mAcchCir;
    /* 0x830 */ cXyz m830;
    /* 0x83C */ int m83C;
    /* 0x840 */ char m840;
    /* 0x844 */ dPa_followEcallBack m844;
    /* 0x858 */ dPa_followEcallBack m858;
    /* 0x86C */ GXColor m86C;
    /* 0x870 */ GXColor m870;
}; // size = 0x874

#endif /* D_A_OBJ_WARPT_H */
