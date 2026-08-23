#ifndef D_A_SALVAGE_TBOX_H
#define D_A_SALVAGE_TBOX_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor_mng.h"

class daSTBox_shadowEcallBack_c : public dPa_levelEcallBack {
public:
    JPABaseEmitter* getEmitter() { return mpEmitter; }
    void setWaterY(f32 waterY) { mWaterY = waterY; }
    void setWaterFlatY(f32 waterFlatY) { mWaterFlatY = waterFlatY; }
    void setDepth(f32 depth) { mDepth = depth; }
    void setup(JPABaseEmitter* emitter, const cXyz*, const csXyz* angle, s8) { 
        field_0x4 = 0;
        mpAngle = angle;
        mpEmitter = emitter; 
    }
    void setIndirectTexData(f32 exTransY, f32 exScaleY) {
        mExTransY = exTransY;
        mExScaleY = exScaleY;
    }
    void setPos(cXyz& pos) { mPos = pos; }
    void deleteCallBack() {
        if (mpEmitter != NULL) {
            mpEmitter->setEmitterCallBackPtr(NULL);
            mpEmitter->becomeInvalidEmitter();
        }
        mpEmitter = NULL;
    }

    ~daSTBox_shadowEcallBack_c() {}

    void getMaxWaterY(JGeometry::TVec3<f32>*);
    void execute(JPABaseEmitter*);
    void draw(JPABaseEmitter*);

private:
    /* 0x04 */  s16 field_0x4;
    /* 0x08 */  f32 mWaterY;
    /* 0x0C */  f32 mWaterFlatY;
    /* 0x10 */  f32 mDepth;
    /* 0x14 */  JGeometry::TVec3<f32> field_0x14[3];
    /* 0x38 */  cXyz mPos;
    /* 0x44 */  const csXyz* mpAngle;
    /* 0x48 */  f32 mExTransY;
    /* 0x4C */  f32 mExScaleY;
    /* 0x50 */  f32 field_0x50;
    /* 0x54 */  JPABaseEmitter* mpEmitter;
};  // Size: 0x58

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

    static const s16 m_heapsize[3];
    static const char m_arcname[];
    static const f32 m_rope_max_length;
    static const s16 m_bdlidx[3];
    static const u8 m_shadow_alpha;
    static const f32 m_shadow_depth;
    static const f32 m_shadow_scroll;
    static const f32 m_shadow_scale;
    
public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ JPABaseEmitter* field_0x29C[3];
    /* 0x2A8 */ u8 field_0x2A8[0x2AC - 0x2A8];
    /* 0x2AC */ dPa_rippleEcallBack mRippleCallBack;
    /* 0x2C0 */ daSTBox_shadowEcallBack_c mShadowCallback;
    /* 0x318 */ cXyz mParticlePos;
    /* 0x324 */ cXyz field_0x324;
    /* 0x330 */ u8 field_0x330;
    /* 0x331 */ u8 field_0x331;
    /* 0x332 */ s16 field_0x332;
    /* 0x334 */ u8 field_0x334;
    /* 0x335 */ u8 field_0x335;
#if VERSION > VERSION_DEMO
    /* 0x336 */ u8 field_0x336;
    /* 0x338 */ fpc_ProcID mItemPID;
#endif
};  // Size: 0x33C

namespace daSTBox_prm {
    inline u32 getBoxType(daSTBox_c* i_this) { return (fopAcM_GetParam(i_this) >> 8) & 0xF; }
    inline u32 getItemNo(daSTBox_c* i_this) { return fopAcM_GetParam(i_this) & 0xFF; }
};

#endif /* D_A_SALVAGE_TBOX_H */
