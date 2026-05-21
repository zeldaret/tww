#ifndef D_A_NPC_AH_H
#define D_A_NPC_AH_H

#include "JSystem/J3DGraphAnimator/J3DAnimation.h"
#include "d/d_npc.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"

struct sAhAnmDat {
    /* 0x00 */ u8 mBckIdx;
    /* 0x01 */ u8 mMorf;
    /* 0x02 */ s8 field_0x02;
}; // Size: 0x04

struct sAhAnmDat2 {
    /* 0x00 */ u8 field_0x00;
    /* 0x01 */ u8 field_0x01;
    /* 0x02 */ s8 field_0x02;
    /* 0x02 */ s8 field_0x03;
}; // Size: 0x04

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
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ s16 field_0x30;
    /* 0x32 */ s16 field_0x32;
    /* 0x34 */ s16 field_0x34;
    /* 0x36 */ s16 field_0x36;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ s16 field_0x44;
    /* 0x46 */ s16 field_0x46;
    /* 0x48 */ s16 field_0x48;
    /* 0x4A */ s16 field_0x4A;
    /* 0x4C */ s16 field_0x4C;
    /* 0x4E */ s16 field_0x4E;
    /* 0x50 */ s16 field_0x50;
    /* 0x52 */ s8 field_0x52;
    /* 0x53 */ s8 field_0x53;
}; // Size: 0x54

class daNpcAh_c : public fopNpc_npc_c {
public:
    enum Prm_e {
        PRM_SWSAVE_S = 0x08,
        PRM_SWSAVE_W = 0x00,
        PRM_SWSAVE2_W = 0x08,
        PRM_SWSAVE2_S = 0x08,
    };

    daNpcAh_c();

    request_of_phase_process_class* getPhaseP() { return &mPhs; }
    void setResFlag(unsigned char flag) { field_0x747 = flag; }

    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    u8 executeCommon();
    void executeSetMode(unsigned char);
    BOOL executeWaitInit();
    void executeWait();
    BOOL executeTalkInit();
    void executeTalk();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    bool eventMesSet();
    void eventGetItemInit();
    u16 talk2(int);
    u16 next_msgStatus(unsigned long*);
    u32 getMsg();
    void chkMsg();
    void setMessage(unsigned long);
    void setAnmFromMsgTag();
    u8 getPrmArg0();
    u8 getSwBit();
    void setMtx();
    void chkAttention();
    void lookBack();
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(unsigned char, int, float);
    bool setAnmTbl(sAhAnmDat*);
    void setCollision(dCcD_Cyl*, cXyz, float, float);
    BOOL chkEndEvent();

    static const char m_arcname[];


public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ request_of_phase_process_class mPhsMethod;
    /* 0x6D4 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x6D8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6EC */ u32 mShadowId;
    /* 0x6F0 */ dNpc_PathRun_c mPathRun;
    /* 0x6F4 */ cXyz field_0x6F4;
    /* 0x704 */ cXyz mEyePos;
    /* 0x710 */ sAhAnmDat* mpAnmDat;
    /* 0x714 */ u32* mpMsgNo;
    /* 0x718 */ f32 field_0x718;
    /* 0x71C */ f32 field_0x71C;
    /* 0x720 */ f32 field_0x720;
    /* 0x724 */ u32 mItemNo;
    /* 0x728 */ bool mHeadOnlyFollow;
    /* 0x72A */ s16 field_0x72A;
    /* 0x72C */ s16 field_0x72C;
    /* 0x72E */ s16 field_0x72E;
    /* 0x730 */ s16 field_0x730;
    /* 0x732 */ s16 field_0x732;
    /* 0x734 */ u16 field_0x734;
    /* 0x736 */ s16 field_0x736;
    /* 0x738 */ s16 field_0x738;
    /* 0x73A */ s16 mTimer;
    /* 0x73C */ s16 mTargetAngle;
    /* 0x73E */ s16 mLookAtMaxVel;
    /* 0x740 */ s16 mTargetYRot;
    /* 0x742 */ u8 field_0x742;
    /* 0x743 */ u8 field_0x743;
    /* 0x744 */ u8 field_0x744;
    /* 0x745 */ u8 mBtpFrame;
    /* 0x746 */ u8 mMoveState;
    /* 0x747 */ u8 field_0x747;
    /* 0x748 */ u8 field_0x748;
    /* 0x749 */ u8 mBckIdx;
    /* 0x74A */ u8 field_0x74A;
    /* 0x74B */ s8 field_0x74B;
    /* 0x74C */ s8 mActIdx;
    /* 0x74D */ u8 field_0x74D;
    /* 0x74E */ s8 field_0x74E;
    /* 0x74F */ u8 field_0x74F;
    /* 0x750 */ u8 field_0x750;
    /* 0x751 */ u8 field_0x751;
};  // Size: 0x754

#endif /* D_A_NPC_AH_H */
