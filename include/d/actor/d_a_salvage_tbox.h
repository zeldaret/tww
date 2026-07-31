#ifndef D_A_SALVAGE_TBOX_H
#define D_A_SALVAGE_TBOX_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"

class J3DModel;
class JPABaseEmitter;

class daSTBox_shadowEcallBack_c : public dPa_levelEcallBack {
public:
    void deleteCallBack() {}
    void getEmitter() {}
    void setDepth(float) {}
    void setIndirectTexData(float, float) {}
    void setPos(cXyz&) {}
    void setWaterFlatY(float) {}
    void setWaterY(float) {}
    void setup(JPABaseEmitter* emitter, const cXyz*, const csXyz* angle, signed char) {
        mState = 0;
        mpAngle = angle;
        mpBaseEmitter = emitter;
    }

    void getMaxWaterY(JGeometry::TVec3<float>*);
    void execute(JPABaseEmitter*);
    void draw(JPABaseEmitter*);

    /* 0x04 */ s16 mState;
    /* 0x06 */ u8 field_0x06[0x2];
    /* 0x08 */ f32 mWaterFlatY;
    /* 0x0C */ f32 mWaterY;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ JGeometry::TVec3<f32> mPos[3];
    /* 0x38 */ cXyz field_0x38;
    /* 0x44 */ const csXyz* mpAngle;
    /* 0x48 */ f32 mScale;
    /* 0x4C */ f32 mDepth;
    /* 0x50 */ f32 mScroll;
    /* 0x54 */ JPABaseEmitter* mpBaseEmitter;
};

class daSTBox_c : public fopAc_ac_c {
public:
    inline bool _draw();

    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    void set_mtx();
    bool _execute();
    void initWait(int);
    void initWait02(int);
    void initWaitGetItem(int);
    void initWaitDummy(int);
    void initDrop(int);
    BOOL actWait(int);
    BOOL actDrop(int);
    BOOL actWait02(int);
    BOOL actWaitGetItem(int);
    BOOL actWaitDummy(int);

public:
    static const char m_arcname[];
    static const s16 m_heapsize[];
    static const s16 m_bdlidx[];
    static const f32 m_rope_max_length;
    static const u8 m_shadow_alpha;
    static const f32 m_shadow_depth;
    static const f32 m_shadow_scroll;
    static const f32 m_shadow_scale;

    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ JPABaseEmitter* mpEmitter[3];
    /* 0x2A8 */ u8 field_0x2A8[0x4];
    /* 0x2AC */ dPa_rippleEcallBack mRippleCb;
    /* 0x2C0 */ daSTBox_shadowEcallBack_c mShadowCb;
    /* 0x318 */ cXyz field_0x318;
    /* 0x324 */ cXyz field_0x324;
    /* 0x330 */ u8 mItemNo;
    /* 0x331 */ u8 mType;
    /* 0x332 */ s16 mTimer;
    /* 0x334 */ u8 mSplashEmitted;
    /* 0x335 */ u8 mRippleEmitted;
    /* 0x336 */ u8 mBgmStarted;
    /* 0x337 */ u8 field_0x337;
    /* 0x338 */ fpc_ProcID mItemPID;
};  // size = 0x33C

#endif /* D_A_SALVAGE_TBOX_H */
