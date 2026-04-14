#ifndef D_A_NPC_SO_H
#define D_A_NPC_SO_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_npc.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_jnt_hit.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class J3DNode;
class J3DModel;
class mDoExt_McaMorf;
class dCamera_c;

// Forward declarations
class daNpc_So_HIO_c;

class daNpc_So_c : public fopNpc_npc_c {
public:
    enum Proc_e {
        PROC_INIT_e = 0,
        PROC_EXEC_e = 1,
    };

    enum {
        MODE_WAIT_e,
        MODE_HIDE_e,
        MODE_JUMP_e,
        MODE_SWIM_e,
        MODE_NEAR_SWIM_e,
        MODE_EVENT_FIRST_WAIT_e,
        MODE_EVENT_FIRST_e,
        MODE_EVENT_FIRST_END_e,
        MODE_EVENT_ESA_e,
        MODE_EVENT_MAPOPEN_e,
        MODE_EVENT_BOW_e,
        MODE_TALK_e,
        MODE_DISAPPEAR_e,
        MODE_DEBUG_e,
        MODE_GET_RUPEE_e,
        MODE_EVENT_TRIFORCE_e,
    };

    int getMiniGameRestArrow() { return 10 - mB78; }
    void isAnm(signed char) {}
    void modeProcInit(int newMode) { modeProc(PROC_INIT_e, newMode); }

    void _searchEsa(fopAc_ac_c*);
    void _nodeControl(J3DNode*, J3DModel*);
    fopAc_ac_c* _searchTagSo(fopAc_ac_c*);
    fopAc_ac_c* _searchMinigameTagSo(fopAc_ac_c*);
    s16 XyCheckCB(int);
    s16 XyEventCB(int);
    bool jntHitCreateHeap();
    int _createHeap();
    BOOL checkTgHit();
    void offsetZero();
    void offsetDive();
    void offsetSwim();
    void offsetAppear();
    u32 getMsg();
    u16 next_msgStatus(unsigned long*);
    void lookBack();
    void setAttention();
    void setAnm(signed char, bool);
    void setAnmSwimSpeed();
    void setMtx();
    void modeWaitInit();
    void modeWait();
    void modeHideInit();
    void modeHide();
    void modeJumpInit();
    void modeJump();
    void modeSwimInit();
    void modeSwim();
    void modeNearSwimInit();
    void modeNearSwim();
    void modeEventFirstWaitInit();
    void modeEventFirstWait();
    void modeEventFirstInit();
    void modeEventFirst();
    void modeEventFirstEndInit();
    void modeEventFirstEnd();
    void modeEventEsaInit();
    void modeEventEsa();
    void modeEventMapopenInit();
    void modeEventMapopen();
    void modeEventBowInit();
    void modeEventBow();
    void modeTalkInit();
    void modeTalk();
    void modeDisappearInit();
    void modeDisappear();
    void modeDebugInit();
    void modeDebug();
    void modeGetRupeeInit();
    void modeGetRupee();
    void modeEventTriForceInit();
    void modeEventTriForce();
    void modeProc(Proc_e, int);
    void eventOrder();
    void checkOrder();
    void setScale();
    bool _execute();
    void debugDraw();
    void hudeDraw();
    bool _draw();
    void createInit();
    void getArg();
    cPhs_State _create();
    bool _delete();

    void cutAppearProc();
    void cutAppearStart();
    void cutDisappearProc();
    void cutDisappearStart();
    void cutDiveProc();
    void cutDiveStart();
    void cutEatesaFirstProc();
    void cutEatesaFirstStart();
    void cutEatesaProc();
    void cutEatesaStart();
    void cutEffectProc();
    void cutEffectStart();
    void cutEquipProc();
    void cutEquipStart();
    void cutJumpMapopenProc();
    void cutJumpMapopenStart();
    void cutJumpProc();
    void cutJumpStart();
    void cutMiniGameEndProc();
    void cutMiniGameEndStart();
    void cutMiniGamePlTurnProc();
    void cutMiniGamePlTurnStart();
    void cutMiniGamePlUpProc();
    void cutMiniGamePlUpStart();
    void cutMiniGameProc();
    void cutMiniGameReturnProc();
    void cutMiniGameReturnStart();
    void cutMiniGameStart();
    void cutMiniGameWaitProc();
    void cutMiniGameWaitStart();
    void cutMiniGameWarpProc();
    void cutMiniGameWarpStart();
    void cutPartnerShipProc();
    void cutPartnerShipStart();
    void cutProc();
    void cutSetAnmProc();
    void cutSetAnmStart();
    void cutSwimProc();
    void cutSwimStart();
    void cutTurnProc();
    void cutTurnStart();
    void cutUnequipProc();
    void cutUnequipStart();
    void initCam();
    void moveCam();

    static const dCcD_SrcSph m_sph_src;
    static char* m_arc_name;

public:
    // Binary offsets from actor start. fopNpc_npc_c base ends at 0x6C4.
    // Fields 0x290-0x6C3 are inherited from fopNpc_npc_c.
    // m029C (0x29C) maps to m_jnt.mbBackBoneLock in fopNpc_npc_c.
    // mEventCut (0x2C4) is inherited from fopNpc_npc_c.
    /* 0x6C4 */ u8 m6C4_pad[0x6CC - 0x6C4];
    /* 0x6CC */ s32 mCurMode;
    /* 0x6D0 */ // continues below
    /* 0x6D0 */ s16 m06D0;
    /* 0x6D2 */ s8 m06D2;
    /* 0x6D3 */ s8 m06D3;
    /* 0x6D4 */ u8 m6D4_pad[0x6D8 - 0x6D4];
    /* 0x6D8 */ int m06D8;
    /* 0x6DC */ request_of_phase_process_class mPhs;
    /* 0x6E4 */ dCcD_Stts mStts;
    /* 0x720 */ dCcD_Sph mSph;
    /* 0x84C */ mDoExt_McaMorf* mpMorf;
    /* 0x850 */ J3DModel* mpModel;
    /* 0x854 */ mDoExt_btpAnm mBtpAnm;
    /* 0x868 */ u8 m868_pad[0x870 - 0x868];
    /* 0x870 */ dBgS_ObjAcch mAcch;
    /* 0xA34 */ dBgS_AcchCir mAcchCir;
    /* 0xA74 */ u8 mA74_pad[0xA78 - 0xA74];
    /* 0xA78 */ u8 mEquipNecklace;
    /* 0xA79 */ u8 m0A79;
    /* 0xA7A */ u8 mA7A_pad[0xA7C - 0xA7A];
    /* 0xA7C */ f32 m0A7C;
    /* 0xA80 */ cXyz m0A80;
    /* 0xA8C */ u8 mA8C_pad[0xA90 - 0xA8C];
    /* 0xA90 */ s32 m0A90;
    /* 0xA94 */ u8 mA94_pad[0xA9C - 0xA94];
    /* 0xA9C */ int m0A9C;
    /* 0xAA0 */ u8 mAA0_pad[0xAA8 - 0xAA0];
    /* 0xAA8 */ JntHit_c* mpJntHit2;
    /* 0xAAC */ u8 mAAC_pad[0xAFC - 0xAAC];
    /* 0xAFC */ f32 m0AFC;
    /* 0xB00 */ f32 mB00;
    /* 0xB04 */ f32 field_0xB04;
    /* 0xB08 */ f32 mB08;
    /* 0xB0C */ s8 mB0C;
    /* 0xB0D */ u8 mB0D_pad[0xB10 - 0xB0D];
    /* 0xB10 */ cXyz mB10;
    /* 0xB1C */ cXyz mB1C;
    /* 0xB28 */ f32 mB28;
    /* 0xB2C */ f32 mB2C;
    /* 0xB30 */ s16 mB30;
    /* 0xB32 */ s16 mB32;
    /* 0xB34 */ f32 mB34;
    /* 0xB38 */ f32 mB38;
    /* 0xB3C */ f32 mB3C;
    /* 0xB40 */ f32 mB40;
    /* 0xB44 */ u8 mB44_pad[0xB54 - 0xB44];
    /* 0xB54 */ cXyz mB54;
    /* 0xB60 */ cXyz mB60;
    /* 0xB6C */ s32 mStaffId;
    /* 0xB70 */ u8 mB70;
    /* 0xB71 */ u8 mB71_pad[0xB74 - 0xB71];
    /* 0xB74 */ s32 mB74;
    /* 0xB78 */ s32 mB78;
    /* 0xB7C */ s32 mB7C;
    /* 0xB80 */ s32 mB80;
    /* 0xB84 */ u8 mB84;
    /* 0xB85 */ u8 mB85_pad[0xB88 - 0xB85];
    /* 0xB88 */ f32 mB88;
    /* 0xB8C */ f32 mB8C;
    /* 0xB90 */ cXyz mB90;
    /* 0xB9C */ s16 mB9C;
    /* 0xB9E */ u8 mB9E_pad[0xBA0 - 0xB9E];
    /* 0xBA0 */ cXyz mBA0;
    /* 0xBAC */ s16 mBAC;
    /* 0xBAE */ u8 mBAE;
    /* 0xBAF */ u8 mBAF_pad[0xBBC - 0xBAF];
    /* 0xBBC */ s32 mBbc;
    /* 0xBC0 */ cXyz mBC0;
    /* 0xBCC */ cXyz mBCC;
    /* 0xBD8 */ u8 mBD8;
    /* 0xBD9 */ u8 mBD9;
    /* 0xBDA */ u8 mBDA;
    /* 0xBDB */ u8 mBDB;
    /* 0xBDC */ s16 mBDC;
    /* 0xBDE */ u8 m0BDE;
    /* 0xBDF */ u8 m0BDF_pad[0xBE0 - 0xBDF];

    static daNpc_So_HIO_c m_heapsize;
};

class daNpc_So_HIO_c : public mDoHIO_entry_c {
public:
    daNpc_So_HIO_c();
    virtual ~daNpc_So_HIO_c() {}

public:
    /* 0x04 */ dNpc_HIO_c mNpcHIO;
    /* 0x2C */ u8 field_0x2c[0x34 - 0x2C];
    /* 0x34 */ f32 m0034;
    /* 0x38 */ f32 m0038;
    /* 0x3C */ f32 m003C;
    /* 0x40 */ f32 m0040;
    /* 0x44 */ f32 m0044;
    /* 0x48 */ f32 m0048;
    /* 0x4C */ f32 m004C;
    /* 0x50 */ f32 m0050;
    /* 0x54 */ f32 m0054;
    /* 0x58 */ f32 m0058;
    /* 0x5C */ f32 m005C;
    /* 0x60 */ f32 m0060;
    /* 0x64 */ s16 m0064;
    /* 0x66 */ s16 m0066;
    /* 0x68 */ s16 m0068;
    /* 0x6A */ s16 m006A;
    /* 0x6C */ f32 m006C;
    /* 0x70 */ f32 m0070;
    /* 0x74 */ f32 m0074;
    /* 0x78 */ f32 m0078;
    /* 0x7C */ s16 m007C;
    /* 0x80 */ f32 m0080;
    /* 0x84 */ f32 m0084;
    /* 0x88 */ f32 m0088;
    /* 0x8C */ f32 m008C;
    /* 0x90 */ f32 m0090;
    /* 0x94 */ f32 m0094;
    /* 0x98 */ u8 m0098_pad[0xA8 - 0x98];
    /* 0xA8 */ f32 m00A8;
    /* 0xAC */ u8 m00AC_pad[0xB0 - 0xAC];
    /* 0xB0 */ f32 m00B0;
    /* 0xB4 */ f32 m00B4;
    /* 0xB8 */ f32 m00B8;
    /* 0xBC */ u8 m00BC_pad[0xC4 - 0xBC];
    /* 0xC4 */ f32 m00C4;
    /* 0xC8 */ f32 m00C8;
    /* 0xCC */ f32 m00CC;
    /* 0xD0 */ f32 m00D0;
    /* 0xD4 */ f32 m00D4;
    /* 0xD8 */ f32 m00D8;
    /* 0xDC */ f32 m00DC;
    /* 0xE0 */ f32 m00E0;
    /* 0xE4 */ f32 m00E4;
    /* 0xE8 */ f32 m00E8;
    /* 0xEC */ f32 m00EC;
    /* 0xF0 */ f32 m00F0;
    /* 0xF4 */ f32 m00F4;
    /* 0xF8 */ f32 m00F8;
    /* 0xFC */ f32 m00FC;
    /* 0x100 */ f32 m0100;
    /* 0x104 */ f32 m0104;
    /* 0x108 */ f32 m0108;
    /* 0x10C */ f32 m010C;
    /* 0x110 */ f32 m0110;
    /* 0x114 */ f32 m0114;
    /* 0x118 */ f32 m0118;
    /* 0x11C */ f32 m011C;
    /* 0x120 */ s16 m0120;
    /* 0x122 */ s16 m0122;
    /* 0x124 */ s16 m0124;
    /* 0x126 */ s16 m0126;
    /* 0x128 */ s16 m0128;
    /* 0x12A */ s16 m012A;
    /* 0x12C */ f32 m012C;
    /* 0x130 */ f32 m0130;
    /* 0x134 */ f32 m0134;
    /* 0x138 */ f32 m0138;
    /* 0x13C */ f32 m013C;
    /* 0x140 */ f32 m0140;
    /* 0x144 */ f32 m0144;
};

extern daNpc_So_HIO_c l_HIO;

#endif /* D_A_NPC_SO_H */
