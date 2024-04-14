#ifndef D_A_NPC_NZ_H
#define D_A_NPC_NZ_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_particle.h"
#include "d/d_bg_s_acch.h"
#include "d/d_npc.h"
#include "d/actor/d_a_shop_item.h"

class J3DNode;

class daNpc_Nz_c : public fopNpc_npc_c {
public:
    enum Proc_e {
        PROC_INIT = 0,
        PROC_EXEC = 1,
    };

    // objdiff says this is a weak function
    // but defining it here with {} causes it to be inlined with fopAcM_SetupActor which breaks things
    daNpc_Nz_c();

    void modeProcInit(int newMode) { modeProc(PROC_INIT, newMode); }

    BOOL NodeCallBack(J3DNode*, int);
    BOOL TailNodeCallBack(J3DNode*, int);
    void TailControl();
    bool _createHeap();
    s16 XyEventCB(int);
    void eventOrder();
    void checkOrder();
    void setAttention();
    void LookBack();
    void setAnm(s8, bool);
    void setMtx();
    void modeWaitInit();
    void modeWait();
    void modeEventEsaInit();
    void modeEventEsa();
    void modeProc(Proc_e, int);
    void createShopItem(u8, u8);
    daShopItem_c* getShopItem(int);
    void deleteShopItem();
    u16 next_msgStatus(u32*);
    void anmAtr(u16);
    bool _execute();
    bool _draw();
    BOOL createInit();
    void setSmokeParticle();
    void getArg();
    s32 _create();
    bool _delete();
    BOOL _searchEsa(fopAc_ac_c*);
    void cutProc();
    void cutEatesaStart();
    void cutEatesaProc();
    void cutEatesaFirstStart();
    void cutEatesaFirstProc();
    void cutKillAllStart();
    void cutKillAllProc();
    void cutShowStart();
    void cutShowProc();
    void cutHideStart();
    void cutHideProc();
    void cutSetAnmStart();
    void cutSetAnmProc();
    void cutGoHomeStart();
    void cutGoHomeProc();
    void cutChkGetItemStart();
    void cutChkGetItemProc();

public:
    static const char m_arc_name[];
    static const char m_bdl_arc_name[];

    /* 0x6C4 */ cXyz field_0x6C4;
    /* 0x6D0 */ int mCurMode;
    /* 0x6D4 */ s8 field_0x6D4;
    /* 0x6D5 */ s8 field_0x6D5;
    /* 0x6D6 */ s8 field_0x6D6;
    /* 0x6D8 */ request_of_phase_process_class mPhs1;
    /* 0x6E0 */ request_of_phase_process_class mPhs2;
    /* 0x6E8 */ mDoExt_McaMorf* mpMorf;
    /* 0x6EC */ f32 field_0x6EC;
    /* 0x6F0 */ dBgS_ObjAcch mAcch;
    /* 0x8B4 */ dBgS_AcchCir mAcchCir;
    /* 0x8F4 */ int field_0x8F4;
    /* 0x8F8 */ u8 field_0x8F8;
    /* 0x8FA */ s16 field_0x8FA;
    /* 0x8FC */ bool field_0x8FC;
    /* 0x8FE */ s16 field_0x8FE;
    /* 0x900 */ u32 field_0x900;
    /* 0x904 */ s16 field_0x904;
    /* 0x906 */ s16 field_0x906;
    /* 0x908 */ u8 field_0x908;
    /* 0x909 */ u8 field_0x909;
    /* 0x90A */ s16 field_0x90A;
    /* 0x90C */ fopAc_ac_c* mpBait;
    /* 0x910 */ f32 field_0x910;
    /* 0x914 */ dPa_smokeEcallBack field_0x914;
    /* 0x934 */ mDoExt_3DlineMat1_c field_0x934;
    /* 0x970 */ u32 field_0x970;
    /* 0x974 */ cXyz field_0x974[10];
    /* 0x9EC */ cXyz field_0x9EC[10];
    /* 0xA64 */ cXyz field_0xA64[2];
    /* 0xA7C */ u8 field_0xA70[0xC];
    /* 0xA88 */ u32 field_0xA88;
    /* 0xA8C */ u32 field_0xA8C;
    /* 0xA90 */ s16 field_0xA90;
}; // Size: 0xA92

class daNpc_Nz_HIO_c : public JORReflexible {
public:
    daNpc_Nz_HIO_c();
    virtual ~daNpc_Nz_HIO_c() {}

    /* 0x00 - vtable */
    /* 0x04 */ s8 field_0x04;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
    /* 0x0E */ s16 field_0x0E;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s8 field_0x1A;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
}; // Size: 0x28

#endif /* D_A_NPC_NZ_H */
