#ifndef D_A_NPC_MT_H
#define D_A_NPC_MT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"

struct sMtAnmDat {
    /* 0x00 */ u8 field_0x00;
    /* 0x01 */ u8 field_0x01;
    /* 0x02 */ u8 field_0x02;
};

struct NpcDatStruct {
    /* 0x00 */ s16 mMax_head_x;
    /* 0x02 */ s16 mMax_head_y;
    /* 0x04 */ s16 mMax_backbone_x;
    /* 0x06 */ s16 mMax_backbone_y;
    /* 0x08 */ s16 mMin_head_x;
    /* 0x0A */ s16 mMin_head_y;
    /* 0x0C */ s16 mMin_backbone_x;
    /* 0x0E */ s16 mMin_backbone_y;
    /* 0x10 */ s16 mMax_turn_step;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2A;
    /* 0x2C */ s16 field_0x2C;
    /* 0x2E */ s16 field_0x2E;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ s16 field_0x3E;
    /* 0x40 */ s16 field_0x40;
    /* 0x42 */ s16 field_0x42;
    /* 0x44 */ s16 field_0x44;
    /* 0x46 */ s16 field_0x46;
    /* 0x48 */ s16 field_0x48;
    /* 0x4A */ s8 field_0x4A;
    /* 0x4B */ s8 field_0x4B;
}; // Size: 0x4c

class daNpcMt_c : public fopNpc_npc_c {
public:
    typedef s32(daNpcMt_c::*InitFunc_t)();
    typedef void(daNpcMt_c::*MoveFunc_t)();

    void attnOff() {
        m753 = false;
    }
    void attnOn() {
        m753 = true;
    }
    u8 getNpcNo() { return mNpcNo; }
    request_of_phase_process_class* getPhaseP() { return &mPhsArcname; }
    void setResFlag(u8 flag) { m747 = flag; }

    daNpcMt_c();
    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    BOOL executeCommon();
    void executeSetMode(u8);
    s32 executeWaitInit();
    void executeWait();
    s32 executeTalkInit();
    void executeTalk();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    bool eventMesSet();
    void eventGetItemInit();
    u16 talk2(int);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void chkMsg();
    void setMessage(u32);
    void setAnmFromMsgTag();
    u8 getPrmNpcNo();
    void setMtx();
    void chkAttention();
    void lookBack();
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(u8, int, f32);
    bool setAnmTbl(sMtAnmDat*);
    s16 XyCheckCB(int);
    void setCollision(dCcD_Cyl*, cXyz, f32, f32);
    BOOL chkEndEvent();
    u8 isFigureGet(u8);
    void setFigure(u8);
    int getFigureMakeNum();
    BOOL isComp();
    u8 changePhotoNo(u8);

    static const char m_arcname[6];

private:
    /* 0x6C4 */ request_of_phase_process_class mPhsArcname;
    /* 0x6CC */ request_of_phase_process_class mPhs;
    /* 0x6D4 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x6D8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6EC */ s32 mShadowId;
    /* 0x6F0 */ u32 m6F0;
    /* 0x6F4 */ u8 m6F4[0x704 - 0x6F4];
    /* 0x704 */ cXyz mLookAtPos;
    /* 0x710 */ sMtAnmDat* mpAnmDat;
    /* 0x714 */ u32* mpMsgTbl;
    /* 0x718 */ f32 m718;
    /* 0x71C */ f32 m71C;
    /* 0x720 */ f32 m720;
    /* 0x724 */ s32 mItemNo;
    /* 0x728 */ bool m728;
    /* 0x729 */ u8 m729;
    /* 0x72A */ s16 mMtGetItemEventIdx;
    /* 0x72C */ s16 m72C;
    /* 0x72E */ s16 m72E;
    /* 0x730 */ s16 m730;
    /* 0x732 */ s16 m732;
    /* 0x734 */ u16 m734;
    /* 0x736 */ s16 m736;
    /* 0x738 */ u8 m738[0x73A - 0x738];
    /* 0x73A */ s16 mTimer;
    /* 0x73C */ s16 m73C;
    /* 0x73E */ s16 m73E;
    /* 0x740 */ s16 m740;
    /* 0x742 */ u8 m742;
    /* 0x743 */ u8 m743;
    /* 0x744 */ u8 m744;
    /* 0x745 */ u8 mFrame;
    /* 0x746 */ u8 m746;
    /* 0x747 */ u8 m747;
    /* 0x748 */ u8 mNpcNo;
    /* 0x749 */ u8 m749;
    /* 0x74A */ u8 m74A;
    /* 0x74B */ u8 mAnmFlag;
    /* 0x74C */ s8 m74C;
    /* 0x74D */ s8 m74D;
    /* 0x74E */ u8 m74E;
    /* 0x74F */ s8 m74F;
    /* 0x750 */ u8 m750;
    /* 0x751 */ u8 m751;
    /* 0x752 */ u8 m752;
    /* 0x753 */ bool m753;
    /* 0x754 */ u8 m754[0x758 - 0x754];
};

#endif /* D_A_NPC_MT_H */
