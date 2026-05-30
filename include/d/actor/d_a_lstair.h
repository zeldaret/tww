#ifndef D_A_LSTAIR_H
#define D_A_LSTAIR_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_kankyo.h"
#include "d/d_com_inf_game.h"

class daLStair_c : public fopAc_ac_c {
public:
    inline BOOL _draw();
    BOOL _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    void set_mtx();
    void setMoveBGMtx();
    int _execute();
    void demoMove();
    void checkAppear();
    void moveBG();
    void appear_stair();
    void disappear_stair();
    void set_on_se();
    void set_off_se();

    static const char m_arcname[];

    /* 0x290 */ request_of_phase_process_class mPhase; 
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ Mtx mBgMtx; 
    /* 0x2D0 */ mDoExt_bckAnm mBckAnm;
    /* 0x2E0 */ mDoExt_btkAnm mBtkAnm;
    /* 0x2F4 */ mDoExt_bpkAnm mBpkAnm0;
    /* 0x308 */ mDoExt_bpkAnm mBpkAnm1;
    /* 0x31C */ mDoExt_brkAnm mBrkAnm;
    /* 0x334 */ f32  mStairYOffset;
    /* 0x338 */ s32  mSwitchNo;
    /* 0x33C */ u16  mEventState;
    /* 0x33E */ s16  mEventIdx;
    /* 0x340 */ u8   mTimer;
    /* 0x341 */ s8   mAppearTimer;
    /* 0x342 */ bool mSwitchStatus;
    /* 0x343 */ bool mEnemyGone;
};

inline BOOL daLStair_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    J3DModelData* modelData = mpModel->getModelData();
    mBtkAnm.entry(modelData, mBtkAnm.getFrame());
    modelData = mpModel->getModelData();
    mBpkAnm0.entry(modelData, mBpkAnm0.getFrame());
    modelData = mpModel->getModelData();
    mBpkAnm1.entry(modelData, mBpkAnm1.getFrame());
    modelData = mpModel->getModelData();
    mBrkAnm.entry(modelData, mBrkAnm.getFrame());

    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();

    return TRUE;
}

#endif /* D_A_LSTAIR_H */
