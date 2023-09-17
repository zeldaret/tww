//
// Generated by dtk
// Translation Unit: d_a_spotbox.cpp
//

#include "JSystem/JKernel/JKRHeap.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_mtx.h"
#include "dolphin/types.h"

struct daSpotbox_c : public fopAc_ac_c {
public:
    inline int create();
    inline int draw();
    inline int execute();
    inline u32 getType();
public:
    Mtx mtx;
}; /* size = 0x2A0 */

int daSpotbox_c::create() {
    /* Matching 96% */
    fopAcM_SetupActor(this, daSpotbox_c);
    float baseScale = this->getType() != 0 ? 100.0f : 1000.0f;
    this->mScale.x *= baseScale;
    this->mScale.y *= baseScale;
    this->mScale.z *= (baseScale * 1.2f);
    this->current.pos.y += this->mScale.y * 0.5f;
    this->mCullMtx = ((daSpotbox_c *)this)->mtx;
    fopAcM_setCullSizeBox(this, -0.5, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f);

    return cPhs_COMPLEATE_e;
}

int daSpotbox_c::draw() {
    if(g_dComIfG_gameInfo.drawlist.getAlphaModel2()->mCount != 0) {
        g_dComIfG_gameInfo.drawlist.setAlphaModel2(0x3, this->mtx, 0x20);
    }
    return TRUE;
}

int daSpotbox_c::execute() {
    PSMTXTrans(mDoMtx_stack_c::now, this->current.pos.x, this->current.pos.y, this->current.pos.z);
    mDoMtx_YrotM(mDoMtx_stack_c::now, this->current.angle.y);
    mDoMtx_stack_c::scaleM(this->mScale.x, this->mScale.y, this->mScale.z);
    PSMTXCopy(mDoMtx_stack_c::now, this->mtx);
    return TRUE;
}

u32 daSpotbox_c::getType() {
    return fopAcM_GetParam(this) & 1;
}


/* 00000078-000000C4       .text daSpotbox_Draw__FP11daSpotbox_c */
static int daSpotbox_Draw(daSpotbox_c* i_this) {
    return ((daSpotbox_c*)i_this)->draw();
}

/* 000000C4-00000138       .text daSpotbox_Execute__FP11daSpotbox_c */
static int daSpotbox_Execute(daSpotbox_c* i_this) {
    return ((daSpotbox_c*)i_this)->execute();
}

/* 00000138-00000140       .text daSpotbox_IsDelete__FP11daSpotbox_c */
static int daSpotbox_IsDelete(daSpotbox_c* i_this) {
    return TRUE;
}

/* 00000140-00000170       .text daSpotbox_Delete__FP11daSpotbox_c */
static int daSpotbox_Delete(daSpotbox_c* self) {
    self->~daSpotbox_c();
    return true;
}

/* 00000170-00000250       .text daSpotbox_Create__FP10fopAc_ac_c */
static int daSpotbox_Create(fopAc_ac_c* i_this) {
    return ((daSpotbox_c*)i_this)->create();
}
