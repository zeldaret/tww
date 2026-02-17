/**
 * d_a_boomerang.cpp
 * Item - Boomerang
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_boomerang.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/res/res_link.h"
#include "dolphin/gf/GF.h"

#include "assets/l_sightMatDL.h"
#include "assets/l_sightDL__d_a_boomerang.h"

static cXyz l_blur_top(40.0f, 0.0f, 0.0f);
static cXyz l_blur_root(-40.0f, 0.0f, 0.0f);

static dCcD_SrcCps l_at_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_BOOMERANG,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e | cCcD_AtSPrm_NoTgHitInfSet_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ dCcG_SE_UNK4,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_Unk1_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 3.0f,
    }},
};

/* 800E0C08-800E0D44       .text initBlur__18daBoomerang_blur_cFPA4_fs */
void daBoomerang_blur_c::initBlur(MtxP mtx, s16 yRot) {
    cMtx_multVec(mtx, &l_blur_top, &arr_0x24[0][0]);
    cMtx_multVec(mtx, &l_blur_root, &arr_0x2F4[0][0]);
    arr_0x24[0][1] = arr_0x24[0][0];
    arr_0x2F4[0][1] = arr_0x2F4[0][0];

    field_0x14 = 0;

    pos.x = mtx[0][3];
    pos.y = mtx[1][3];
    pos.z = mtx[2][3];

    mDoMtx_stack_c::copy(mtx);
    mDoMtx_stack_c::YrotM(-(yRot * 2));
    mDoMtx_stack_c::multVec(&l_blur_top, &arr_0x5C4[0][0]);
    mDoMtx_stack_c::multVec(&l_blur_root, &arr_0x894[0][0]);
    arr_0x5C4[0][1] = arr_0x5C4[0][0];
    arr_0x894[0][1] = arr_0x894[0][0];
}

/* 800E0D44-800E101C       .text copyBlur__18daBoomerang_blur_cFPA4_fs */
void daBoomerang_blur_c::copyBlur(MtxP mtx, s16 yRot) {
    for (int i = 54; i >= 0; i--) {
        arr_0x24[1][i] = arr_0x24[0][i];
        arr_0x2F4[1][i] = arr_0x2F4[0][i];
        arr_0x5C4[1][i] = arr_0x5C4[0][i];
        arr_0x894[1][i] = arr_0x894[0][i];
    }

    float t = 0.0f;

    cXyz inPos;
    inPos.x = mtx[0][3];
    inPos.y = mtx[1][3];
    inPos.z = mtx[2][3];

    cXyz diff = pos - inPos;

    pos = inPos;

    mDoMtx_stack_c::push();

    int i;
    for (i = 0; i < 5; i++) {
        mDoMtx_stack_c::multVec(&l_blur_top, &arr_0x24[0][i]);
        mDoMtx_stack_c::multVec(&l_blur_root, &arr_0x2F4[0][i]);
        VECAdd(&arr_0x24[0][i], &(diff * t), &arr_0x24[0][i]);
        VECAdd(&arr_0x2F4[0][i], &(diff * t), &arr_0x2F4[0][i]);
        t += 0.2f;
        mDoMtx_stack_c::YrotM(0x633);
    }

    t = 0.0f;

    mDoMtx_stack_c::pop();

    mDoMtx_stack_c::YrotM(-(yRot * 2));

    for (i = 0; i < 5; i++) {
        // FIXME: i is in the wrong register.
        mDoMtx_stack_c::multVec(&l_blur_top, &arr_0x5C4[0][i]);
        mDoMtx_stack_c::multVec(&l_blur_root, &arr_0x894[0][i]);
        VECAdd(&arr_0x5C4[0][i], &(diff * t), &arr_0x5C4[0][i]);
        VECAdd(&arr_0x894[0][i], &(diff * t), &arr_0x894[0][i]);
        t += 0.2f;
        mDoMtx_stack_c::YrotM(-0x633);
    }

    field_0x14 += 5;

    if (field_0x14 >= 59) {
        field_0x14 = 58;
    }
}

/* 800E101C-800E13A4       .text draw__18daBoomerang_blur_cFv */
void daBoomerang_blur_c::draw() {
    /* Nonmatching */

#include "assets/l_matDL__draw__18daBoomerang_blur_cFv.h"

    static GXVtxDescList l_vtxDescList[] = {
        {GX_VA_POS, GX_DIRECT},
        {GX_VA_TEX0, GX_DIRECT},
        {GX_VA_NULL, GX_NONE},
    };

    static GXVtxAttrFmtList l_vtxAttrFmtList[] = {
        {GX_VA_POS, GX_POS_XYZ, GX_F32, 0x00},
        {GX_VA_TEX0, GX_TEX_ST, GX_S16, 0x08},
        {GX_VA_NULL, GX_POS_XYZ, GX_F32, 0x00},
    };

    static GXTexObj texObj;

    j3dSys.reinitGX();

    GXSetNumIndStages(0);
    GXInitTexObj(&texObj, imageData, 16, 4, GX_TF_I4, GX_CLAMP, GX_CLAMP, FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, FALSE, FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    GXCallDisplayList(l_matDL, 0x80);

    static GXColor color0 = {0xFF, 0xFF, 0x7B, 0x96};
    GFSetTevColor(GX_TEVREG0, color0);

    s16 alphaStep = 0xFF / (field_0x14 / 2 + 1);

    GFSetVtxDescv(l_vtxDescList);
    GFSetVtxAttrFmtv(GX_VTXFMT0, l_vtxAttrFmtList);

    GFLoadPosMtxImm(j3dSys.getViewMtx(), GX_PNMTX0);

    // Start quads.
    GXFIFO.u8 = GX_QUADS | GX_VTXFMT0;
    GXFIFO.u16 = field_0x14 * 4 + 4;

    s16 alpha1;
    s16 alphaNext;
    s16 alpha0;

    alphaNext = alphaStep;
    alpha0 = 0;
    if (field_0x14 >= 0) {
        for (int i = field_0x14 + 1; i >= 0; i--) {
            alpha1 = alphaNext;
            {
                // GXPositionXYZ(arr_0x24[0][i]);
                GXPosition3f32(arr_0x24[0][i].x, arr_0x24[0][i].y, arr_0x24[0][i].z);
                GXPosition1x16(alpha1);
                GXPosition1x16(0x00);
            }
            {
                // GXPositionXYZ(arr_0x2F4[0][i]);
                GXPosition3f32(arr_0x2F4[0][i].x, arr_0x2F4[0][i].y, arr_0x2F4[0][i].z);
                GXPosition1x16(alpha1);
                GXPosition1x16(0xFF);
            }
            {
                // GXPositionXYZ(arr_0x2F4[0][i + 1]);
                GXPosition3f32(arr_0x2F4[0][i + 1].x, arr_0x2F4[0][i + 1].y, arr_0x2F4[0][i + 1].z);
                GXPosition1x16(alpha0);
                GXPosition1x16(0xFF);
            }
            {
                // GXPositionXYZ(arr_0x24[0][i]);
                GXPosition3f32(arr_0x24[0][i + 1].x, arr_0x24[0][i + 1].y, arr_0x24[0][i + 1].z);
                GXPosition1x16(alpha0);
                GXPosition1x16(0x00);
            }

            alphaNext = alpha1 + alphaStep;
            alpha0 = alpha1;
        }
    }

    // Start quads.
    GXFIFO.u8 = GX_QUADS | GX_VTXFMT0;
    GXFIFO.u16 = field_0x14 * 4 + 4;

    alphaNext = alphaStep;
    alpha0 = 0;
    if (field_0x14 >= 0) {
        for (int i = field_0x14 + 1; i >= 0; i--) {
            alpha1 = alphaNext;
            {
                GXPosition3f32(arr_0x5C4[0][i].x, arr_0x5C4[0][i].y, arr_0x5C4[0][i].z);
                GXPosition1x16(alpha1);
                GXPosition1x16(0x00);
            }
            {
                GXPosition3f32(arr_0x894[0][i].x, arr_0x894[0][i].y, arr_0x894[0][i].z);
                GXPosition1x16(alpha1);
                GXPosition1x16(0xFF);
            }
            {
                GXPosition3f32(arr_0x894[0][i + 1].x, arr_0x894[0][i + 1].y, arr_0x894[0][i + 1].z);
                GXPosition1x16(alpha0);
                GXPosition1x16(0xFF);
            }
            {
                GXPosition3f32(arr_0x5C4[0][i + 1].x, arr_0x5C4[0][i + 1].y, arr_0x5C4[0][i + 1].z);
                GXPosition1x16(alpha0);
                GXPosition1x16(0x00);
            }

            alphaNext = alpha1 + alphaStep;
            alpha0 = alpha1;
        }
    }

#if VERSION > VERSION_JPN
    J3DShape::resetVcdVatCache();
#endif
}

/* 800E13A4-800E14F0       .text draw__25daBoomerang_sightPacket_cFv */
void daBoomerang_sightPacket_c::draw() {
    /* Nonmatching */
}

/* 800E14F0-800E1718       .text setSight__25daBoomerang_sightPacket_cFP4cXyzi */
void daBoomerang_sightPacket_c::setSight(cXyz*, int) {
    /* Nonmatching */
}

/* 800E1718-800E1754       .text play__25daBoomerang_sightPacket_cFi */
void daBoomerang_sightPacket_c::play(int n) {
    u8* p = &field_0xF4[0];
    for (int i = 0; i < n; i++) {
        *p = *p + 1;
        if (*p == 26) {
            *p = 0;
        }
        p++;
    }
}

/* 800E1754-800E1998       .text draw__13daBoomerang_cFv */
BOOL daBoomerang_c::draw() {
    /* Nonmatching */
}

/* 800E1998-800E19B8       .text daBoomerang_Draw__FP13daBoomerang_c */
static BOOL daBoomerang_Draw(daBoomerang_c* i_this) {
    return ((daBoomerang_c*)i_this)->draw();
}

/* 800E19B8-800E1A14       .text getFlyMax__13daBoomerang_cFv */
float daBoomerang_c::getFlyMax() {
    /* Nonmatching */
}

/* 800E1A14-800E1AAC       .text rockLineCallback__13daBoomerang_cFP10fopAc_ac_c */
void daBoomerang_c::rockLineCallback(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 800E1AAC-800E1AD0       .text daBoomerang_rockLineCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daBoomerang_rockLineCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 800E1AD0-800E1B20       .text setAimActor__13daBoomerang_cFP10fopAc_ac_c */
void daBoomerang_c::setAimActor(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 800E1B20-800E1C20       .text setLockActor__13daBoomerang_cFP10fopAc_ac_ci */
void daBoomerang_c::setLockActor(fopAc_ac_c*, int) {
    /* Nonmatching */
}

/* 800E1C20-800E1C58       .text resetLockActor__13daBoomerang_cFv */
void daBoomerang_c::resetLockActor() {
    /* Nonmatching */
}

/* 800E1C58-800E1CFC       .text setRoomInfo__13daBoomerang_cFv */
void daBoomerang_c::setRoomInfo() {
    /* Nonmatching */
}

/* 800E1CFC-800E1DA8       .text setKeepMatrix__13daBoomerang_cFv */
void daBoomerang_c::setKeepMatrix() {
    /* Nonmatching */
}

/* 800E1DA8-800E1E6C       .text setAimPos__13daBoomerang_cFv */
void daBoomerang_c::setAimPos() {
    /* Nonmatching */
}

/* 800E1E6C-800E1F94       .text checkBgHit__13daBoomerang_cFP4cXyzP4cXyz */
void daBoomerang_c::checkBgHit(cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 800E1F94-800E239C       .text procWait__13daBoomerang_cFv */
BOOL daBoomerang_c::procWait() {
    /* Nonmatching */
}

/* 800E239C-800E2AF4       .text procMove__13daBoomerang_cFv */
BOOL daBoomerang_c::procMove() {
    /* Nonmatching */
}

/* 800E2AF4-800E2BD0       .text execute__13daBoomerang_cFv */
BOOL daBoomerang_c::execute() {
    for (int i = 0; i < field_0xF31; i++) {
        arr_0xF18[i] = fopAcM_SearchByID(arr_0xF04[i]);
    }

    if (mCurrProcFunc) {
        (this->*mCurrProcFunc)();
    }

    attention_info.position = current.pos;
    eyePos = current.pos;

    setRoomInfo();
    mSightPacket.play(field_0xF31);

    return TRUE;
}

/* 800E2BD0-800E2BF0       .text daBoomerang_Execute__FP13daBoomerang_c */
static BOOL daBoomerang_Execute(daBoomerang_c* i_this) {
    return ((daBoomerang_c*)i_this)->execute();
}

/* 800E2BF0-800E2BF8       .text daBoomerang_IsDelete__FP13daBoomerang_c */
static BOOL daBoomerang_IsDelete(daBoomerang_c*) {
    return TRUE;
}

/* 800E2BF8-800E2C00       .text daBoomerang_Delete__FP13daBoomerang_c */
static BOOL daBoomerang_Delete(daBoomerang_c*) {
    return TRUE;
}

/* 800E2C00-800E2CC8       .text createHeap__13daBoomerang_cFv */
BOOL daBoomerang_c::createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Link", LINK_BDL_BOOMERANG);
    JUT_ASSERT(1546, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x37220202);
    if (mpModel == NULL)
        return FALSE;
    return TRUE;
}

/* 800E2CC8-800E2CE8       .text daBoomerang_createHeap__FP10fopAc_ac_c */
static BOOL daBoomerang_createHeap(fopAc_ac_c* i_this) {
    return static_cast<daBoomerang_c*>(i_this)->createHeap();
}

/* 800E2CE8-800E2EF0       .text create__13daBoomerang_cFv */
cPhs_State daBoomerang_c::create() {
    /* Nonmatching */
    fopAcM_SetupActor(this, daBoomerang_c);

    if (!fopAcM_entrySolidHeap(this, daBoomerang_createHeap, 0xD40)) {
        return cPhs_ERROR_e;
    }

    setKeepMatrix();
    cullMtx = model->getBaseTRMtx();
    mCurrProcFunc = &daBoomerang_c::procWait;
    mStts.Init(0x3C, 0xFF, this);
    mCps.Set(l_at_cps_src);

    mCps.SetAtHitCallback(&daBoomerang_rockLineCallback);
    mCps.SetStts(&mStts);

    for (int i = 0; i < 5; i++) {
        arr_0xF04[i] = -1;
    }

    {
        ResTIMG* tmp_img = (ResTIMG*)dComIfG_getObjectRes("Link", LINK_BTI_BLUR);
        JUT_ASSERT(1629, tmp_img != NULL);
        mBlur.imageData = (u8*)tmp_img + tmp_img->imageOffset;
    }

    {
        ResTIMG* tmp_img = (ResTIMG*)dComIfG_getObjectRes("Link", LINK_BTI_ROCK_MARK);
        JUT_ASSERT(1637, tmp_img != NULL);
        mSightPacket.imageData = (u8*)tmp_img + tmp_img->imageOffset;
        mSightPacket.sightImage = tmp_img;
    }

    setRoomInfo();
    model = mpModel;

    return cPhs_COMPLEATE_e;
}

/* 800E2EF0-800E329C       .text __ct__13daBoomerang_cFv */
daBoomerang_c::daBoomerang_c() {
    /* Nonmatching */
}

/* 800E33F0-800E3410       .text daBoomerang_Create__FP10fopAc_ac_c */
static cPhs_State daBoomerang_Create(fopAc_ac_c* i_this) {
    return ((daBoomerang_c*)i_this)->create();
}

static actor_method_class l_daBoomerang_Method = {
    (process_method_func)daBoomerang_Create,
    (process_method_func)daBoomerang_Delete,
    (process_method_func)daBoomerang_Execute,
    (process_method_func)daBoomerang_IsDelete,
    (process_method_func)daBoomerang_Draw,
};

actor_process_profile_definition g_profile_BOOMERANG = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BOOMERANG,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBoomerang_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BOOMERANG,
    /* Actor SubMtd */ &l_daBoomerang_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
