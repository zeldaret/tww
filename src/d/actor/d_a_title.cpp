//
// Generated by dtk
// Translation Unit: d_a_title.cpp
//

#include "d/actor/d_a_title.h"
#include "d/d_procname.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/JKernel/JKRExpHeap.h"

namespace {
    struct Attr_c {
        /* 0x00 */ f32 field_0x00;
        /* 0x04 */ f32 field_0x04;
        /* 0x08 */ f32 field_0x08;
        /* 0x0C */ f32 field_0x0C;
        /* 0x10 */ f32 field_0x10;
        /* 0x14 */ f32 field_0x14;
        /* 0x18 */ f32 field_0x18;
        /* 0x1C */ f32 field_0x1C;
        /* 0x20 */ f32 field_0x20;
        /* 0x24 */ f32 field_0x24;
        /* 0x28 */ f32 field_0x28;
        /* 0x2C */ f32 field_0x2C;
        /* 0x30 */ f32 field_0x30;
        /* 0x34 */ f32 field_0x34;
    };

    static const Attr_c L_attr = {
        0.0f, 0.0f, 0.9f, 0.1f,
        -57.0f, -3.0f, 1.0f, 1.0f,
        120.0f, 10.0f, 120.0f, 10.0f,
        85.0f, 5.0f,
    };

    inline const Attr_c & attr() { return L_attr; }
}

/* 00000078-00000638       .text proc_init3D__14daTitle_proc_cFv */
void daTitle_proc_c::proc_init3D() {
    /* Nonmatching */
}

/* 00000638-00000900       .text proc_init2D__14daTitle_proc_cFv */
void daTitle_proc_c::proc_init2D() {
    /* Nonmatching */
}

/* 00000900-00000A78       .text __ct__14daTitle_proc_cFv */
daTitle_proc_c::daTitle_proc_c() {
    m20C = NULL;
    m_exp_heap = NULL;
    m01C = 120;
    m030 = 0;
    m098 = -50;

    m094 = (f32)(m098 * m098) * -attr().field_0x0C;
    m020 = (int)(cM_rndF(attr().field_0x28) + attr().field_0x2C);
    m024 = (int)(cM_rndF(attr().field_0x20) + attr().field_0x24 + 130.0f);

    m02C = 0;
    m018 = 0;
    m090 = 0;
    m008 = 0;
    mpEmitter = NULL;
}

/* 00000C1C-00000D7C       .text __dt__14daTitle_proc_cFv */
daTitle_proc_c::~daTitle_proc_c() {
    JKRHeap* oldHeap = mDoExt_setCurrentHeap(m_exp_heap);
    delete m_Screen;
    m_Screen = NULL;
    mDoExt_destroySolidHeap(m20C);
    m20C = NULL;
    mDoExt_setCurrentHeap(oldHeap);
    fopMsgM_destroyExpHeap(m_exp_heap);
}

/* 00000D7C-00000D94       .text setEnterMode__14daTitle_proc_cFv */
void daTitle_proc_c::setEnterMode() {
    /* Nonmatching */
}

/* 00000D94-00000F20       .text set_mtx__14daTitle_proc_cFv */
void daTitle_proc_c::set_mtx() {
    /* Nonmatching */
}

/* 00000F20-0000172C       .text calc_2d_alpha__14daTitle_proc_cFv */
void daTitle_proc_c::calc_2d_alpha() {
    /* Nonmatching */
}

/* 0000172C-00001880       .text proc_execute__14daTitle_proc_cFv */
void daTitle_proc_c::proc_execute() {
    /* Nonmatching */
}

/* 00001880-000019E0       .text model_draw__14daTitle_proc_cFv */
void daTitle_proc_c::model_draw() {
    /* Nonmatching */
}

/* 000019E0-00001A5C       .text proc_draw__14daTitle_proc_cFv */
void daTitle_proc_c::proc_draw() {
    JKRHeap* oldHeap = mDoExt_setCurrentHeap(m_exp_heap);

    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setPort();
    m_Screen->draw(0.0f, 0.0f, graf);

    mDoExt_setCurrentHeap(oldHeap);
}

/* 00001A5C-00001AAC       .text daTitle_Draw__FP9daTitle_c */
static BOOL daTitle_Draw(daTitle_c* i_this) {
    return i_this->draw();
}

/* 00001AAC-00001CF8       .text daTitle_Execute__FP9daTitle_c */
static BOOL daTitle_Execute(daTitle_c* i_this) {
    return i_this->execute();
}

/* 00001CF8-00001D00       .text daTitle_IsDelete__FP9daTitle_c */
static BOOL daTitle_IsDelete(daTitle_c* i_this) {
    return TRUE;
}

/* 00001D00-00001D70       .text daTitle_Delete__FP9daTitle_c */
static BOOL daTitle_Delete(daTitle_c* i_this) {
    i_this->~daTitle_c();

    return TRUE;
}

/* 00001D70-00001E28       .text daTitle_Create__FP10fopAc_ac_c */
static s32 daTitle_Create(fopAc_ac_c* i_this) {
    return static_cast<daTitle_c*>(i_this)->create();
}

/* 00001E28-00001E48       .text draw__14daTitle_proc_cFv */
void daTitle_proc_c::draw() {
    /* Nonmatching */
}

static actor_method_class l_daTitle_Method = {
    (process_method_func)daTitle_Create,
    (process_method_func)daTitle_Delete,
    (process_method_func)daTitle_Execute,
    (process_method_func)daTitle_IsDelete,
    (process_method_func)daTitle_Draw,
};

actor_process_profile_definition g_profile_TITLE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TITLE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTitle_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x000A,
    /* Actor SubMtd */ &l_daTitle_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
