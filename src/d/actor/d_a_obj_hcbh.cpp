/**
 * d_a_obj_hcbh.cpp
 * Object - Tower of the Gods - Pillar with Companion Statue's face on it.
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_hcbh.h"
#include "d/d_cc_d.h"
#include "res/Object/Hcbh.h"

namespace {

static const char l_arcname[] = "Hcbh";

static const dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_UNK8 | AT_TYPE_BOMB | AT_TYPE_SKULL_HAMMER | AT_TYPE_DARKNUT_SWORD,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 70.0f,
        /* Height */ 556.0f,
    }},
};

static const dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 35.0f,
    }},
};

static const Vec l_co_sph_offset[] = {
    {0.0f, 157.0f, 0.0f},
    {0.0f, 227.0f, 0.0f},
    {0.0f, 297.0f, 0.0f},
    {0.0f, 367.0f, 0.0f},
    {0.0f, 437.0f, 0.0f},
    {0.0f, 507.0f, 0.0f},
};

}; // namespace


#if VERSION == VERSION_DEMO
class daObjHcbh_HIO_c : public JORReflexible {
public:
    daObjHcbh_HIO_c();
    virtual ~daObjHcbh_HIO_c() {}

    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x04 */ s8 mNo;
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
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ u8 field_0x40;
    /* 0x41 */ u8 field_0x41;
    /* 0x42 */ u8 field_0x42;
};

static daObjHcbh_HIO_c l_HIO;

daObjHcbh_HIO_c::daObjHcbh_HIO_c() {
    mNo = -1;
    field_0x08 = 70.0f;
    field_0x0C = 589.0f;
    field_0x10 = -0.011f;
    field_0x14 = 4.0f;
    field_0x18 = 127.0f;
    field_0x1C = 16384.0f;
    field_0x20 = -10.0f;
    field_0x24 = -0.01f;
    field_0x28 = -100.0f;
    field_0x2C = 15.0f;
    field_0x30 = 0.0f;
    field_0x34 = 4.0f;
    field_0x38 = 512.0f;
    field_0x3C = 8.0f;
    field_0x40 = 0;
    field_0x41 = 1;
    field_0x42 = 0;
}
#else
namespace L_HIO {
static const f32 field_0x08 = 70.0f;
static const f32 field_0x0C = 589.0f;
static const f32 field_0x10 = -0.011f;
static const f32 field_0x14 = 4.0f;
static const f32 field_0x18 = 127.0f;
static const f32 field_0x1C = 16384.0f;
static const f32 field_0x20 = -10.0f;
static const f32 field_0x24 = -0.01f;
static const f32 field_0x28 = -100.0f;
static const f32 field_0x2C = 15.0f;
static const f32 field_0x30 = 0.0f;
static const f32 field_0x34 = 4.0f;
static const f32 field_0x38 = 512.0f;
static const f32 field_0x3C = 8.0f;
static const u8 field_0x40 = 0;
static const u8 field_0x41 = 1;
static const u8 field_0x42 = 0;
} // namespace L_HIO
#endif

/* 00000078-000000D8       .text chk_appear__11daObjHcbh_cFv */
bool daObjHcbh_c::chk_appear() {
    int switchIndex = param_get_swSave();
    bool ret = true;
    if (switchIndex != 0xff) {
        ret = fopAcM_isSwitch(this, switchIndex) == FALSE;
    }
    return ret;
}

/* 000000D8-0000029C       .text set_mtx__11daObjHcbh_cFv */
void daObjHcbh_c::set_mtx() {
    f32 var_f31 = JMASSin(mPitch) * 50.0f;

    mDoMtx_stack_c::transS(current.pos.x, mCurY, current.pos.z);

    mDoMtx_stack_c::YrotM(mYaw);
    mDoMtx_stack_c::transM(0.0f, var_f31, 0.0f);
    mDoMtx_stack_c::XrotM(mPitch);
    mDoMtx_stack_c::transM(0.0f, -var_f31, 0.0f);
    mDoMtx_stack_c::YrotM(-mYaw);

    mDoMtx_stack_c::XYZrotM(shape_angle);

    mModel->setBaseTRMtx(mDoMtx_stack_c::get());

    for (int i = 0; i < ARRAY_SSIZE(mBdlModels); i++) {
        mDoMtx_stack_c::transS(mBdlPos[i]);

        mDoMtx_stack_c::YrotM(mBdlYaw[i]);
        mDoMtx_stack_c::XrotM(mBdlPitch[i]);
        mDoMtx_stack_c::YrotM(-mBdlYaw[i]);

        mDoMtx_stack_c::XYZrotM(shape_angle);

        mBdlModels[i]->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

/* 0000029C-0000030C       .text init_mtx__11daObjHcbh_cFv */
void daObjHcbh_c::init_mtx() {
    mModel->setBaseScale(scale);
    for (int i = 0; i < ARRAY_SSIZE(mBdlModels); i++) {
        mBdlModels[i]->setBaseScale(scale);
    }
    set_mtx();
}

/* 0000030C-00000330       .text solidHeapCB__11daObjHcbh_cFP10fopAc_ac_c */
BOOL daObjHcbh_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjHcbh_c*)i_this)->create_heap();
}

/* 00000330-00000500       .text create_heap__11daObjHcbh_cFv */
bool daObjHcbh_c::create_heap() {
    static int bdl_table[4] = {
        dRes_INDEX_HCBH_BDL_HCBH1A_e,
        dRes_INDEX_HCBH_BDL_HCBH1B_e,
        dRes_INDEX_HCBH_BDL_HCBH1C_e,
        dRes_INDEX_HCBH_BDL_HCBH1D_e,
    };

    bool rv = true;

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcname, dRes_INDEX_HCBH_BDL_HCBH2_e);
    if (!modelData) {
        JUT_ASSERT(DEMO_SELECT(496, 499), FALSE);
        rv = false;
    } else {
        mModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);

        for (int i = 0; i < ARRAY_SSIZE(mBdlModels); i++) {
            J3DModelData* bdlModelData = (J3DModelData*)dComIfG_getObjectRes(l_arcname, bdl_table[i]);
            if (bdlModelData == NULL) {
                rv = false;
                break;
            }
            mBdlModels[i] = mDoExt_J3DModel__create(bdlModelData, 0x80000, 0x11000022);
        }

        mBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, dRes_INDEX_HCBH_DZB_HCBH2_e), 1, &mModel->getBaseTRMtx());
        mBdlBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, dRes_INDEX_HCBH_DZB_HCBH1_e), 1, &mBdlModels[0]->getBaseTRMtx());

        if (mModel == NULL ||
            mBdlModels[0] == NULL || mBdlModels[1] == NULL || mBdlModels[2] == NULL || mBdlModels[3] == NULL ||
            mBgW == NULL || mBdlBgW == NULL) {
            rv = false;
        }
    }

    return rv;
}

/* 00000500-000005E8       .text setup_break_condition__11daObjHcbh_cFP10fopAc_ac_c */
void daObjHcbh_c::setup_break_condition(fopAc_ac_c* i_actor) {
    static s16 set_anglY[4] = {-0x8000, -0x4000, 0x4000, 0x0000};

    if (i_actor == NULL) {
        return;
    }

    mYaw = cM_atan2s(mCyl.GetC().x - i_actor->current.pos.x, mCyl.GetC().z - i_actor->current.pos.z);
    for (int i = 0; i < 4; i++) {
        mBdlYaw[i] = set_anglY[i];
        mBdlPitch[i] = 0;
        mFallTimer[i] = std::fabsf(cM_ssin((set_anglY[i] - mYaw) >> 1)) * HIO(field_0x2C) + HIO(field_0x30);
    }
}

/* 000005E8-00000724       .text checkCollision__11daObjHcbh_cFv */
void daObjHcbh_c::checkCollision() {
    if (!mCyl.ChkTgHit()) {
        return;
    }

    cCcD_Obj* hitObj = mCyl.GetTgHitObj();
    fopAc_ac_c* actor;
    if (hitObj != NULL) {
        switch (hitObj->GetAtType()) {
        case AT_TYPE_BOMB:
            mBrokenBy = 3;
            setup_break_condition(mCyl.GetTgHitAc());
            break;
        case AT_TYPE_SKULL_HAMMER:
            mBrokenBy = 2;
            setup_break_condition(mCyl.GetTgHitAc());
            break;
        case AT_TYPE_UNK8:
            actor = mCyl.GetTgHitAc();
            if (actor == NULL) {
                break;
            }
            if (fopAcM_GetProfName(actor) != fpcNm_TN_e) {
                break;
            }
            mBrokenBy = 1;
            setup_break_condition(mCyl.GetTgHitAc());
            break;
        case AT_TYPE_DARKNUT_SWORD:
            mBrokenBy = 1;
            setup_break_condition(mCyl.GetTgHitAc());
            break;
        }
    }

    mCyl.ClrTgHit();
}

/* 00000724-0000077C       .text co_hitCallback__11daObjHcbh_cFP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daObjHcbh_c::co_hitCallback(fopAc_ac_c* i_actor1, dCcD_GObjInf* i_gObjInf1, fopAc_ac_c* i_actor2, dCcD_GObjInf* i_gObjInf2) {
    if (fopAcM_IsActor(i_actor2) && fopAcM_GetProfName(i_actor2) == fpcNm_AM_e) {
        ((daObjHcbh_c*)i_actor1)->mBrokenBy = 4;
    }
}

/* 0000077C-000008F8       .text particle_set__11daObjHcbh_cFv */
void daObjHcbh_c::particle_set() {
    csXyz angle(0, mYaw, 0);
    dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBREAKSHAFTHAHEN00, &current.pos, NULL, NULL, 0xFF, NULL, -1, &tevStr.mColorK0);
    dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBREAKSHAFTHAHEN01, &current.pos, &angle, NULL, 0xFF, NULL, -1, &tevStr.mColorK0);
    if (mBrokenBy != 3) {
        dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBREAKSHAFTHIT00, &current.pos, &angle, NULL, 0xFF, NULL, -1, &tevStr.mColorK0);
    }
    mSmokeCallback.remove();
    dComIfGp_particle_setToon(dPa_name::ID_AK_ST_SIRENBREAKSHAFTSMOKE00, &current.pos, &angle, NULL, 0xA0, &mSmokeCallback, -1, &tevStr.mColorK0);
}

/* 000008F8-000009E4       .text make_item__11daObjHcbh_cFv */
void daObjHcbh_c::make_item() {
    int item = param_get_itemNo();
    int itemSaveBit = param_get_itemSaveBitNo();
    cXyz itemPos = current.pos;
    csXyz itemAngle(0.0f, 0.0f, 0.0f);
    itemPos.y -= 30.0f;
    fopAcM_createItemFromTable(&itemPos, item, itemSaveBit, fopAcM_GetHomeRoomNo(this), 0, &itemAngle, 1, 0);
    param_on_swSave();
}

/* 00000A20-00000E30       .text _create__11daObjHcbh_cFv */
cPhs_State daObjHcbh_c::_create() {
    cPhs_State rv = cPhs_ERROR_e;

    fopAcM_ct(this, daObjHcbh_c);

    if (fopAcM_IsFirstCreating(this)) {
        mCurY = current.pos.y;

        mPitch = 0;
        for (int i = 0; i < ARRAY_SSIZE(mBdlPos); i++) {
            mBdlPos[i].set(current.pos);
            mBdlPitch[i] = 0;
            mBdlYaw[i] = 0;
        }

        mAppear = chk_appear();
    }

    if (mAppear == true) {
        rv = dComIfG_resLoad(&mPhase, l_arcname);
    }

    if (rv == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x2D00)) {
            if (dComIfG_Bgsp()->Regist(mBgW, this) != 0) {
                rv = cPhs_ERROR_e;
            } else if (dComIfG_Bgsp()->Regist(mBdlBgW, this) != 0) {
                rv = cPhs_ERROR_e;
            } else {
                fopAcM_SetMtx(this, mModel->getBaseTRMtx());

                init_mtx();

                mCircle.SetWall(589.0f, 70.0f);

                mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mCircle,
                    fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
                mAcch.ClrWaterNone();
                mAcch.ClrRoofNone();
                mAcch.SetRoofCrrHeight(589.0f);
                mAcch.CrrPos(*dComIfG_Bgsp());
                mAcch.ClrGroundLanding();

                mStts.Init(0xFF, 0xFF, this);
                mCyl.Set(l_cyl_src);
                mCyl.SetStts(&mStts);
                mCyl.SetC(current.pos);
                mCyl.SetCoHitCallback(co_hitCallback);

                for (int i = 0; i < ARRAY_SSIZE(mSph); i++) {
                    mSph[i].Set(l_sph_src);
                    mSph[i].SetStts(&mStts);
                    mSph[i].SetR(70.0f);
                    mSph[i].SetC(current.pos.x, current.pos.y + l_co_sph_offset[i].y, current.pos.z);
                }

                mSmokeCallback.setTevStr(&tevStr);
                mSmokeCallback.setRateOff(false);
                mSmokeCallback.setFollowOff();

                mProcFunc = &daObjHcbh_c::wait_act_proc;

                fopAcM_setCullSizeBox(this, -40.0f, 0.0f, -40.0f, 100.0f, 589.0f, 100.0f);
            }
        } else {
            rv = cPhs_ERROR_e;
        }
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("タートナックの柱", &l_HIO); // "Darknut Pillar"
    }
#endif

    return rv;
}

/* 000011F4-000012F4       .text _delete__11daObjHcbh_cFv */
bool daObjHcbh_c::_delete() {
    if (mAppear == 1) {
        dComIfG_resDelete(&mPhase, l_arcname);

#if VERSION > VERSION_DEMO
        if (heap != NULL)
#endif
        {
            if (mBgW != NULL) {
                if (mBgW->ChkUsed()) {
                    dComIfG_Bgsp()->Release(mBgW);
                }
#if VERSION > VERSION_DEMO
                mBgW = NULL;
#endif
            }

            if (mBdlBgW != NULL) {
                if (mBdlBgW->ChkUsed()) {
                    dComIfG_Bgsp()->Release(mBdlBgW);
                }
#if VERSION > VERSION_DEMO
                mBdlBgW = NULL;
#endif
            }
        }

        mSmokeCallback.remove();
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
#endif

    return true;
}

/* 000012F4-000013BC       .text wait_act_proc__11daObjHcbh_cFv */
void daObjHcbh_c::wait_act_proc() {
#if VERSION == VERSION_DEMO
    mCyl.SetR(l_HIO.field_0x08);
    mCyl.SetH(l_HIO.field_0x0C);
#endif

    checkCollision();
    if (mBrokenBy == 0) {
        dComIfG_Ccsp()->Set(&mCyl);
        return;
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.field_0x41 == 1)
#endif
    {
        particle_set();
    }

    fopAcM_seStartCurrent(this, JA_SE_OBJ_TN_COLUMN_BREAK, 0);
    mCyl.SetCoHitCallback(NULL);
    mProcFunc = &daObjHcbh_c::fall_act_proc;
}

/* 000013BC-000017D8       .text fall_act_proc__11daObjHcbh_cFv */
void daObjHcbh_c::fall_act_proc() {
    if (mPitch < 0) {
        mPitch = -0x8000;
        mPitchStep = 0;
    } else {
        if (mPitch > 0x2000) {
            if (mBgW != NULL && mBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mBgW);
            }

            if (mBdlBgW != NULL && mBdlBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mBdlBgW);
            }
        }

        mPitchStep += (s16)(cM_ssin(mPitch) * HIO(field_0x18) + HIO(field_0x14));
    }

    if (mCurY < home.pos.y + -10.0f) {
        make_item();

        dComIfGp_getVibration().StartShock(8, -17, cXyz(0.0f, 1.0f, 0.0f));

        fopAcM_seStartCurrent(this, JA_SE_OBJ_TN_COLUMN_SMASH, 0);

        fopAcM_delete(this);
    } else {
        mVertStep += -0.011f;
        f32 yOff = cM_ssin(mPitch) * 50.0f;

        mDoMtx_stack_c::transS(current.pos.x, mCurY, current.pos.z);

        mDoMtx_stack_c::YrotM(mYaw);
        mDoMtx_stack_c::transM(0.0f, yOff, 0.0f);
        mDoMtx_stack_c::XrotM(mPitch);
        mDoMtx_stack_c::transM(0.0f, -yOff, 0.0f);
        mDoMtx_stack_c::YrotM(-mYaw);

        mDoMtx_stack_c::XYZrotM(shape_angle);

        for (int i = 0; i < ARRAY_SSIZE(l_co_sph_offset); i++) {
            cXyz offset;
            offset.set(l_co_sph_offset[i]);
            mDoMtx_stack_c::multVec(&offset, &offset);
            mSph[i].MoveCAt(offset);
            dComIfG_Ccsp()->Set(&mSph[i]);
        }
    }

    for (int i = 0; i < ARRAY_SSIZE(mFallTimer); i++) {
        if (mFallTimer[i] > 0) {
            mFallTimer[i] -= 1;
            continue;
        }

        mBdlYStep[i] += HIO(field_0x24);
        mBdlPos[i].y += mBdlYStep[i];

        if (mBdlPos[i].y < HIO(field_0x28) + home.pos.y) {
            mBdlPos[i].y = HIO(field_0x28) + home.pos.y;
        }

        mBdlPitchStep[i] += (s16)(cM_ssin(mBdlPitch[i]) * HIO(field_0x38) + HIO(field_0x34));
        mBdlPitch[i] += mBdlPitchStep[i];
        if (mBdlPitch[i] > 0x4000) {
            mBdlPitch[i] = 0x4000;
        }
    }
}

/* 000017D8-000018D8       .text _execute__11daObjHcbh_cFv */
bool daObjHcbh_c::_execute() {
    set_mtx();
    mStts.Move();
    mAcch.CrrPos(*dComIfG_Bgsp());

    if (mBgW != NULL) {
        if (mBgW->ChkUsed()) {
            mBgW->Move();
        }
    }

    if (mBdlBgW != NULL) {
        if (mBdlBgW->ChkUsed()) {
            mBdlBgW->Move();
        }
    }

    mCurY += mVertStep;
    mPitch += mPitchStep;

    if (mPitch >= (s16)HIO(field_0x1C)) {
        mPitch = (s16)HIO(field_0x1C);
    }

    (this->*mProcFunc)();

    return true;
}

/* 000018D8-0000197C       .text _draw__11daObjHcbh_cFv */
bool daObjHcbh_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel, &tevStr);
    mDoExt_modelUpdateDL(mModel);

    for (int i = 0; i < ARRAY_SSIZE(mBdlModels); i++) {
        g_env_light.setLightTevColorType(mBdlModels[i], &tevStr);
        mDoExt_modelUpdateDL(mBdlModels[i]);
    }

    return true;
}

/* 0000197C-0000199C       .text daObjHcbh_Create__FP10fopAc_ac_c */
static cPhs_State daObjHcbh_Create(fopAc_ac_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_create();
}

/* 0000199C-000019C0       .text daObjHcbh_Delete__FP11daObjHcbh_c */
static BOOL daObjHcbh_Delete(daObjHcbh_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_delete();
}

/* 000019C0-000019E4       .text daObjHcbh_Execute__FP11daObjHcbh_c */
static BOOL daObjHcbh_Execute(daObjHcbh_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_execute();
}

/* 000019E4-00001A08       .text daObjHcbh_Draw__FP11daObjHcbh_c */
static BOOL daObjHcbh_Draw(daObjHcbh_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_draw();
}

/* 00001A08-00001A10       .text daObjHcbh_IsDelete__FP11daObjHcbh_c */
static BOOL daObjHcbh_IsDelete(daObjHcbh_c*) {
    return TRUE;
}

static actor_method_class l_daObjHcbh_Method = {
    (process_method_func)daObjHcbh_Create,
    (process_method_func)daObjHcbh_Delete,
    (process_method_func)daObjHcbh_Execute,
    (process_method_func)daObjHcbh_IsDelete,
    (process_method_func)daObjHcbh_Draw,
};

actor_process_profile_definition g_profile_Obj_Hcbh = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Hcbh_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHcbh_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Hcbh_e,
    /* Actor SubMtd */ &l_daObjHcbh_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
