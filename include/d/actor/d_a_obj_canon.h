#ifndef D_A_OBJ_CANON_H
#define D_A_OBJ_CANON_H

#include "d/d_cc_d.h"
#include "d/d_npc.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class J3DNode;
class dCcD_SrcSph;

class daObj_Canon_c : public fopAc_ac_c {
public:
    enum Proc_e {
        PROC_INIT = 0,
        PROC_EXEC = 1
    };

    void modeProcInit(int newMode) { modeProc(PROC_INIT, newMode); }

    void _nodeControl(J3DNode*, J3DModel*);
    BOOL _createHeap();
    void setEffect(u16);
    bool checkTgHit();
    void attackCannon();
    void lockonCannon();
    void setAttention();
    void setCollision();
    void setMtx();
    void modeWaitInit();
    void modeWait();
    void modeAttackInit();
    void modeAttack();
    void modeDeleteInit();
    void modeDelete();
    void modeSwWaitInit();
    void modeSwWait();
    void modeAppearInit();
    void modeAppear();
    void modeProc(Proc_e, int);
    bool _execute();
    void debugDraw();
    bool _draw();
    void createInit();
    void getArg();
    cPhs_State _create();
    bool _delete();

    static const u32 m_heapsize;
    static const char m_arc_name[];
    static const dCcD_SrcSph m_sph_src;

public:
    /* 0x290 */ s32 mCurMode;
    /* 0x294 */ u8 field_0x294;
    /* 0x295 */ u8 field_0x295;
    /* 0x296 */ u8 field_0x296;
    /* 0x297 */ u8 field_0x297;
    /* 0x298 */ dNpc_PathRun_c field_0x298;
    /* 0x2A0 */ u8 field_0x2A0[0x2B0 - 0x2A0];
    /* 0x2B0 */ dPath* field_0x2B0;
    /* 0x2B0 */ u8 field_0x2B4[0x2B8 - 0x2B4];
    /* 0x2B8 */ request_of_phase_process_class mPhs;
    /* 0x2C0 */ J3DModel* mpModel;
    /* 0x2C4 */ s16 field_0x2C4;
    /* 0x2C6 */ s16 field_0x2C6;
    /* 0x2C8 */ s16 field_0x2C8;
    /* 0x2CA */ s16 field_0x2CA;
    /* 0x2CC */ cXyz field_0x2CC;
    /* 0x2D8 */ dCcD_Sph mSph;
    /* 0x420 */ dCcD_Stts mStts;
    /* 0x444 */ int field_0x440;
    /* 0x444 */ int field_0x444;
    /* 0x448 */ u8 field_0x448[0x450 - 0x448];
    /* 0x450 */ cXyz field_0x450;
    /* 0x45C */ cXyz field_0x45C;
    /* 0x468 */ s16 field_0x468;
    /* 0x46A */ s16 field_0x46A;
    /* 0x46C */ f32 field_0x46C;
    /* 0x470 */ dPa_followEcallBack field_0x470;
    /* 0x484 */ int field_0x484;
    /* 0x488 */ s32 field_0x488;
}; // Size: 0x48C

class daObj_Canon_HIO_c : public mDoHIO_entry_c {
public:
    daObj_Canon_HIO_c();
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ bool debug_draw;
    /* 0x05 */ u8 field_0x05;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ s16 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ s16 field_0x30;
    /* 0x32 */ s16 field_0x32;
    /* 0x34 */ s16 field_0x34;
    /* 0x36 */ s16 field_0x36;
    /* 0x38 */ s16 field_0x38;
    /* 0x3A */ s16 field_0x3A;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ s16 field_0x3E;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ s16 field_0x48;
}; // Size: 0x4C

#endif /* D_A_OBJ_CANON_H */
