#ifndef D_A_OBJ_DOGUU_H
#define D_A_OBJ_DOGUU_H

#include "d/d_npc.h"

class daObjDoguu_c : public fopNpc_npc_c {
public:
    daObjDoguu_c();
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    inline void setEffectMtx(const cXyz*, float); // weak but not inlined?

    void setPointLight();
    BOOL CreateHeap();
    void CreateInit();
    void set_mtx();
    u16 next_msgStatus(unsigned long*);
    u32 getMsg();
    void setGoal(int);
    void setPlayerAngle(int);
    void setQuake(int);
    void setJDemo(int);
    void privateCut();
    int getFinishEventCount();
    void setFinishMyEvent();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ J3DModel* field_0x6CC;
    /* 0x6D0 */ J3DModel* field_0x6D0;
    /* 0x6D4 */ J3DModel* field_0x6D4;
    /* 0x6D8 */ J3DModel* field_0x6D8;
    /* 0x6DC */ mDoExt_brkAnm mBrk;
    /* 0x6F4 */ mDoExt_bckAnm mBck1;
    /* 0x704 */ mDoExt_bckAnm mBck2;
    /* 0x714 */ mDoExt_bckAnm mBck3;
    /* 0x724 */ dCcD_Stts mStts;
    /* 0x760 */ dCcD_Cyl mCyl;
    /* 0x890 */ u8 mItemNo;
    /* 0x894 */ int field_0x894;
    /* 0x898 */ u32 mJointIdx;
    /* 0x89C */ u32 field_0x89C;
    /* 0x8A0 */ bool field_0x8A0;
    /* 0x8A1 */ bool field_0x8A1;
    /* 0x8A2 */ bool field_0x8A2;
    /* 0x8A3 */ bool field_0x8A3;
    /* 0x8A4 */ s16 mDoguuDemo1EventIdx;
    /* 0x8A6 */ s16 mDoguuDemo2EventIdx;
    /* 0x8A8 */ s16 mDoguuDemo3EventIdx;
    /* 0x8AA */ s16 mMegamiDemoEventIdx;
    /* 0x8AC */ int field_0x8AC;
    /* 0x8B0 */ s8 mActIdx;
    /* 0x8B4 */ cXyz field_0x8B4;
    /* 0x8C0 */ int mTimer;
    /* 0x8C4 */ int field_0x8C4;
    /* 0x8C8 */ f32 mAllColRatio;
    /* 0x8CC */ u32 mShape;
    /* 0x8D0 */ cXyz mPos;
    /* 0x8DC */ LIGHT_INFLUENCE mLightInfluence;
    /* 0x8FC */ f32 field_0x8FC;
};  // Size: 0x900

#endif /* D_A_OBJ_DOGUU_H */
