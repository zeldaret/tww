#ifndef D_A_SALVAGE_TBOX_H
#define D_A_SALVAGE_TBOX_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"

class daSTBox_shadowEcallBack_c : public dPa_levelEcallBack {
public:
    void deleteCallBack() {}
    JPABaseEmitter* getEmitter() { return mpEmitter; }
    void setDepth(float depth) { mpDepth = depth; }
    void setIndirectTexData(f32 exTransY, f32 exScaleY) { mExTransY = exTransY; mExScaleY = exScaleY; }
    void setPos(cXyz& pos) { mpPos = &pos; }
    void setWaterFlatY(float waterFlatY) { mpWaterFlatY = waterFlatY; }
    void setWaterY(float waterY) { mpWaterY = waterY; }
    void setup(JPABaseEmitter* emitter, const cXyz*, const csXyz* angle, signed char) { 
        mpWaterFlatY = 0;
        mpAngle = const_cast<csXyz*>(angle);
        mpEmitter = emitter; 
    }

    void getMaxWaterY(JGeometry::TVec3<f32>*);
    void execute(JPABaseEmitter*);
    void draw(JPABaseEmitter*);

    // TODO: Fields below are a nudge in the right direction
    // /* 0x2C1 */ u8 field_0x2C1[0x2C8 - 0x2C1];
    // /* 0x2C8 */ f32 field_0x2C8;
    // /* 0x2CC */ f32 field_0x2CC;
    // /* 0x2D0 */ f32 field_0x2D0;
    // /* 0x2D4 */ JGeometry::TVec3<f32> field_0x2D4[3];
    // /* 0x2F8 */ f32 field_0x2F8;
    // /* 0x2FC */ f32 field_0x2FC;
    // /* 0x300 */ f32 field_0x300;
    // /* 0x304 */ u8 field_0x304[0x308 - 0x304];
    // /* 0x308 */ f32 field_0x308;
    // /* 0x30C */ f32 field_0x30C;
    // /* 0x310 */ u8 field_0x310[0x314 - 0x310];
    // /* 0x314 */ s32 field_0x314;

    private:
    s16 mpWaterFlatY;
    f32 mpWaterY;
    cXyz* mpPos;
    f32 mExTransY;
    JGeometry::TVec3<f32> mPos[3];
    f32 mExScaleY;
    f32 mVel;
    f32 mMinVel;
    csXyz* mpAngle;
    f32 mpDepth;
    f32 bliz;
    f32 blaz;
    JPABaseEmitter* mpEmitter;

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
    void actWait(int);
    void actDrop(int);
    BOOL actWait02(int);
    s32 actWaitGetItem(int);
    s32 actWaitDummy(int);

    static const s16 m_heapsize[3];
    static const char m_arc_name[];
    static const f32 m_rope_max_length;
    static const s16 m_bdlidx[3];
    static const u8 m_shadow_alpha;
    static const f32 m_shadow_depth;
    static const f32 m_shadow_scroll;
    static const f32 m_shadow_scale;
    
public:
    /* 0x290 */ request_of_phase_process_class field_0x290;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ JPABaseEmitter* field_0x29C[2];
    /* 0x2A4 */ JPABaseEmitter* field_0x2A4;
    /* 0x2A8 */ u8 field_0x2A8[0x2AC - 0x2A8];
    /* 0x2AC */ dPa_rippleEcallBack mRippleCallBack;
    /* 0x2C0 */ daSTBox_shadowEcallBack_c field_0x2C0;

    // Moved to shadowEcallBack
    // /* 0x2C1 */ u8 field_0x2C1[0x2C8 - 0x2C1];
    // /* 0x2C8 */ f32 field_0x2C8;
    // /* 0x2CC */ f32 field_0x2CC;
    // /* 0x2D0 */ f32 field_0x2D0;
    // /* 0x2D4 */ JGeometry::TVec3<f32> field_0x2D4[3];
    // /* 0x2F8 */ f32 field_0x2F8;
    // /* 0x2FC */ f32 field_0x2FC;
    // /* 0x300 */ f32 field_0x300;
    // /* 0x304 */ u8 field_0x304[0x308 - 0x304];
    // /* 0x308 */ f32 field_0x308;
    // /* 0x30C */ f32 field_0x30C;
    // /* 0x310 */ u8 field_0x310[0x314 - 0x310];
    // /* 0x314 */ s32 field_0x314;

    /* 0x318 */ f32 field_0x318;
    /* 0x31C */ f32 field_0x31C;
    /* 0x320 */ f32 field_0x320;
    /* 0x324 */ f32 field_0x324;
    /* 0x328 */ f32 field_0x328;
    /* 0x32C */ f32 field_0x32C;
    /* 0x330 */ u8 field_0x330;
    /* 0x331 */ u8 field_0x331;
    /* 0x332 */ s16 field_0x332;
    /* 0x334 */ u8 field_0x334;
    /* 0x335 */ u8 field_0x335;
    /* 0x336 */ u8 field_0x336;
    /* 0x337 */ u8 field_0x337[0x338 - 0x337];
    /* 0x338 */ s32 field_0x338;
};  // Size: 0x33C
#endif /* D_A_SALVAGE_TBOX_H */
