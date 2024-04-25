#ifndef D_A_NPC_ROTEN_H
#define D_A_NPC_ROTEN_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

struct sRotenAnmDat {
    /* 0x00 */ u8 field_0x00;
    /* 0x01 */ u8 field_0x01;
    /* 0x02 */ u8 field_0x02;
}; // Size: 0x03

class daNpcRoten_c : public fopNpc_npc_c {
public:
    enum Prm_e {
        PRM_RAIL_ID_W = 0x08,
        PRM_RAIL_ID_S = 0x10,

        PRM_NPC_NO_W = 0x08,
        PRM_NPC_NO_S = 0x18,
    };

    request_of_phase_process_class* getPhaseP() { return &mPhs; }
    cXyz getWindVec() { return field_0x720; }
    void setNpcNo(u8 npcNo) { mNpcNo = npcNo; }
    void setResFlag(u8 flag) { field_0x9BC = flag; }

    daNpcRoten_c();
    s32 _create();
    BOOL createHeap();
    s32 createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    bool executeCommon();
    void executeSetMode(u8);
    s32 executeWaitInit();
    void executeWait();
    s32 executeTalkInit();
    void executeTalk();
    s32 executeWalkInit();
    void executeWalk();
    s32 executeTurnInit();
    void executeTurn();
    s32 executeWindInit();
    void executeWind();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventInit();
    void eventMesSetInit(int);
    bool eventMesSet();
    void eventSetItemInit();
    bool eventSetItem();
    void eventClrItemInit();
    void eventGetItemInit(int);
    void eventSetAngleInit();
    void eventOnPlrInit();
    void eventOffPlrInit();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setMessage(u32);
    void setAnmFromMsgTag();
    u8 getPrmNpcNo();
    u8 getPrmRailID();
    void setMtx();
    void chkAttention();
    void lookBack();
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(u8, int, f32);
    bool setAnmTbl(sRotenAnmDat*);
    BOOL isHaitatuItem(u8);
    BOOL isKoukanItem(u8);
    BOOL isGetMap(u8);
    s16 XyEventCB(int);
    void setCollisionB();
    void setCollisionH();

public:
    typedef s32(daNpcRoten_c::*InitFunc_t)();
    typedef void(daNpcRoten_c::*MoveFunc_t)();

    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ request_of_phase_process_class mPhs2;
    /* 0x6D4 */ J3DModel* field_0x6D4;
    /* 0x6D8 */ mDoExt_McaMorf* field_0x6D8;
    /* 0x6DC */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x6E0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F4 */ u32 mShadowId;
    /* 0x6F8 */ u32 field_0x6F8;
    /* 0x6FC */ uint field_0x6FC;
    /* 0x700 */ dNpc_PathRun_c mPathRun;
    /* 0x708 */ cXyz field_0x708;
    /* 0x714 */ cXyz field_0x714;
    /* 0x720 */ cXyz field_0x720;
    /* 0x72C */ dCcD_Cyl mCyl2;
    /* 0x85C */ dCcD_Sph mSph;
    /* 0x988 */ sRotenAnmDat* field_0x988;
    /* 0x98C */ u32* field_0x98C;
    /* 0x990 */ f32 field_0x990;
    /* 0x994 */ f32 field_0x994;
    /* 0x998 */ s32 field_0x998;
    /* 0x99C */ bool field_0x99C;
    /* 0x99E */ s16 field_0x99E;
    /* 0x9A0 */ s16 field_0x9A0;
    /* 0x9A2 */ s16 field_0x9A2;
    /* 0x9A4 */ s16 field_0x9A4;
    /* 0x9A6 */ s16 field_0x9A6;
    /* 0x9A8 */ s16 field_0x9A8;
    /* 0x9AA */ s16 field_0x9AA;
    /* 0x9AC */ s16 field_0x9AC;
    /* 0x9AE */ s16 field_0x9AE;
    /* 0x9B0 */ s16 field_0x9B0;
    /* 0x9B2 */ u16 field_0x9B2;
    /* 0x9B4 */ bool field_0x9B4;
    /* 0x9B5 */ u8 field_0x9B5;
    /* 0x9B6 */ u8 field_0x9B6;
    /* 0x9B7 */ u8 field_0x9B7;
    /* 0x9B8 */ u8 field_0x9B8;
    /* 0x9B9 */ s8 m_hand_L_jnt_num;
    /* 0x9BA */ s8 m_bag_jnt_num;
    /* 0x9BB */ u8 field_0x9BB;
    /* 0x9BC */ u8 field_0x9BC;
    /* 0x9BD */ u8 mNpcNo;
    /* 0x9BE */ u8 field_0x9BE;
    /* 0x9BF */ u8 field_0x9BF;
    /* 0x9C0 */ u8 field_0x9C0;
    /* 0x9C1 */ u8 field_0x9C1;
    /* 0x9C2 */ s8 field_0x9C2;
    /* 0x9C3 */ s8 field_0x9C3;
    /* 0x9C4 */ s8 field_0x9C4;
    /* 0x9C5 */ u8 field_0x9C5;
    /* 0x9C6 */ u8 field_0x9C6;
    /* 0x9C7 */ u8 field_0x9C7;
    /* 0x9C8 */ u8 field_0x9C8;
    /* 0x9C9 */ u8 field_0x9C9;
    /* 0x9CA */ u8 field_0x9CA;

    static const char m_arcname[];
}; // Size: 0x9CC

#endif /* D_A_NPC_ROTEN_H */
