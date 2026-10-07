/**
 * d_a_obj_vyasi.cpp
 * Object - Palm tree blowing in the wind (Gale Isle)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_vyasi.h"
#include "d/d_a_obj.h"
#include "d/d_cc_d.h"
#include "d/d_kankyo_wether.h"
#include "d/d_lib.h"
#include "res/Object/Vyasi.h"
#include "SSystem/SComponent/c_lib.h"

namespace daObjVyasi {

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
    /* 0x20 */ s16 field_0x20;
    /* 0x22 */ s16 field_0x22;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ u8 pad[0x84 - 0x30];
}; // Size: 0x84

static Attr_c const L_attr = {
    1.0f, 79.0f, 250.0f, 0.0f, 0.0f, 0.0f, 0.4f, 1.5f, 2, 0, 700.0f, 1700.0f, 1700.0f, {},
};

inline Attr_c const& attr() {
    return L_attr;
}
} // namespace

enum {
    STATE_NONE = 0,
    STATE_SAG,
    STATE_SAG_WIND,
    STATE_TO_NORMAL,
    STATE_NORMAL,
    STATE_MAX,
};

static const dCcD_SrcCyl M_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsPlayer_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
        /* Height */ 200.0f,
    }},
};


static const dCcD_SrcCps M_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsPlayer_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
    }},
};


static const dCcD_SrcSph M_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
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
        /* Radius */ 100.0f,
    }},
};

static u8 joint_kind_table[14] = { 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };

}; // namespace daObjVyasi

/* 000000EC-0000015C       .text SetStopJointAnimation__Q210daObjVyasi5Act_cFP18J3DAnmTransformKeyff */
BOOL daObjVyasi::Act_c::SetStopJointAnimation(J3DAnmTransformKey* i_key, float i_speed, float i_morf) {
    if (i_key != NULL) {
        mpMorf->setAnm(i_key, 0, i_morf, i_speed, 0.0f, -1.0f, NULL);
        mAnmPlaying = 1;
        return TRUE;
    }
    return FALSE;
}

/* 0000015C-00000194       .text PlayStopJointAnimation__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::PlayStopJointAnimation() {
    if (mpMorf->play(NULL, 0, 0) == 0) {
        return TRUE;
    }
    return FALSE;
}

/* 00000194-0000021C       .text set_first_process__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_first_process() {
    process_init(is_switch() ? STATE_NORMAL : STATE_SAG);
    mNormalCounter = 0;
    mWindScale = 1.0f;
    shape_angle.y += 0x8000;
}

/* 0000021C-000005B8       .text set_collision__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_collision() {
    if (mCyl.ChkTgHit()) {
        mCyl.GetTgHitObj();
        daObj::HitSeStart(&current.pos, fopAcM_GetRoomNo(this), &mCyl, 7);
        daObj::HitEff_kikuzu(this, &mCyl);
        dKy_Sound_set(current.pos, 4, fopAcM_GetID(this), 100);
        mCyl.ClrTgHit();
    } else {
        mCyl.SetR(79.0f);
        mCyl.SetH(250.0f);
        mCyl.SetC(current.pos);
        dComIfG_Ccsp()->Set(&mCyl);
    }

    for (int i = 0; i < 5; i++) {
        if (mCps[i].ChkTgHit()) {
            mCps[i].GetTgHitObj();
            daObj::HitSeStart(&current.pos, fopAcM_GetRoomNo(this), &mCps[i], 7);
            dKy_Sound_set(current.pos, 4, fopAcM_GetID(this), 100);
            mCps[i].ClrTgHit();
        } else {
            int k = i + 1;
            field_0xDF8[i].mStart = mJointPos[i];
            field_0xDF8[i].mEnd = mJointPos[k];
            field_0xDF8[i].mRadius = 47.4f;
            mCps[i].cM3dGCps::Set(field_0xDF8[i]);
            dComIfG_Ccsp()->Set(&mCps[i]);
        }
    }

    for (int i = 0; i < 8; i += 2) {
        int idx = i >> 1;
        int j = idx + 1;
        int k = idx + 2;

        cXyz delta((mJointPos[k].x - mJointPos[j].x) * 0.33333f, (mJointPos[k].y - mJointPos[j].y) * 0.33333f, (mJointPos[k].z - mJointPos[j].z) * 0.33333f);

        cXyz pos;
        pos.x = mJointPos[j].x + delta.x;
        pos.y = mJointPos[j].y + delta.y;
        pos.z = mJointPos[j].z + delta.z;
        field_0x1064[i].SetC(pos);
        field_0x1064[i].SetR(47.4f);
        dComIfG_Ccsp()->Set(&field_0x1064[i]);

        pos.x = mJointPos[j].x + delta.x * 2.0f;
        pos.y = mJointPos[j].y + delta.y * 2.0f;
        pos.z = mJointPos[j].z + delta.z * 2.0f;
        field_0x1064[i + 1].SetC(pos);
        field_0x1064[i + 1].SetR(47.4f);
        dComIfG_Ccsp()->Set(&field_0x1064[i + 1]);
    }
}

/* 000005F4-000009B8       .text JointNodeCallBack__10daObjVyasiFP7J3DNodei */
BOOL daObjVyasi::JointNodeCallBack(J3DNode* i_node, int i_calcTiming) {
    J3DModel* model = j3dSys.getModel();
    s32 jntNo = ((J3DJoint*)i_node)->getJntNo();
    Act_c* i_this = (Act_c*)model->getUserArea();
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
        Mtx mtx;
        MTXCopy(model->getAnmMtx(jntNo), mtx);
        cXyz trans(mtx[0][3], mtx[1][3], mtx[2][3]);
        mtx[0][3] = mtx[1][3] = mtx[2][3] = 0.0f;

        mDoMtx_stack_c::transS(trans);
        mDoMtx_stack_c::quatM(&i_this->mJointQuat[jntNo]);
        mDoMtx_stack_c::concat(mtx);
        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        MTXCopy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);

        csXyz angles_table[14] = {
            csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0),
            csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0),
        };

        csXyz angle = angles_table[jntNo];
        angle += i_this->mJointAngle[jntNo];
        mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
        mDoMtx_stack_c::ZXYrotM(angle);

        if (joint_kind_table[jntNo] == 0) {
            mDoMtx_stack_c::scaleM(i_this->mLeafScale.x, i_this->mLeafScale.y, i_this->mLeafScale.z);
        }

        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        MTXCopy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
        cXyz src(0.0f, 0.0f, 0.0f);
        cMtx_multVec(mDoMtx_stack_c::get(), &src, &i_this->mJointPos[jntNo]);
    }
    return TRUE;
}

/* 000009F4-000009FC       .text process_none_init__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::process_none_init() {
    return TRUE;
}

/* 000009FC-00000A00       .text process_none_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_none_main() {
    return;
}

/* 00000A00-00000A64       .text process_sag_init__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::process_sag_init() {
    if (SetStopJointAnimation(M_bck_data, 1.0f, 0.0f) != 0) {
        mpMorf->setPlaySpeed(0.0f);
        return TRUE;
    }
    return FALSE;
}

/* 00000A64-00000AD8       .text process_sag_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_sag_main() {
    fopAc_ac_c* actor = fopAcM_SearchByName(fpcNm_Obj_Ekskz_e);
    if (actor != NULL) {
        mEkszsPos = actor->current.pos;
        mEkszsRotY = actor->shape_angle.y;
        process_init(STATE_SAG_WIND);
    }
}

/* 00000AD8-00000CC0       .text process_sagWind_init__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::process_sagWind_init() {
    if (SetStopJointAnimation(M_bck_data, 1.0f, 3.0f)) {
        f32 dist = mEkszsPos.abs(current.pos);
        dist = cLib_maxLimit(dist, 2800.0f);
        dist = cLib_minLimit(dist, 1000.0f);

        mSagRatio = (dist - 2800.0f) / -1800.0f;
        f32 amp = 5000.0f + 7000.0f * mSagRatio;

        for (int i = 0; i < 14; i++) {
            if (joint_kind_table[i] == 0) {
                if (!(i & 1)) {
                    mWaveSpeed[i] = amp + cM_rndF(2000.0f);
                } else {
                    mWaveSpeed[i] = -(amp + cM_rndF(2000.0f));
                }
            } else {
                mWaveSpeed[i] = 0.5f * amp;
            }
        }
        mpMorf->setPlaySpeed(0.0f);
        return TRUE;
    }
    return FALSE;
}

/* 00000CC0-00000D20       .text process_sagWind_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_sagWind_main() {
    if (is_switch()) {
        process_init(STATE_TO_NORMAL);
    }
}

/* 00000D20-00000D54       .text process_toNormal_init__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::process_toNormal_init() {
    return SetStopJointAnimation(M_bck_data, 1.0f, 0.0f);
}

/* 00000D54-00000E10       .text process_toNormal_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_toNormal_main() {
    if (mAnmPlaying == 0) {
        if (std::fabsf(field_0x19CC) <= 0.1f && process_init(STATE_NORMAL)) {
            field_0x19CC = 0.0f;
            mWindScale = 0.0f;
            mNormalCounter = 2;
        }
        field_0x19CC *= 0.85f;
        field_0x19D0 += 0x3000;
    } else {
        field_0x19CC = -1792.0f * mSagRatio;
        field_0x19D0 = 0;
    }
}

/* 00000E10-00000E74       .text process_normal_init__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::process_normal_init() {
    if (SetStopJointAnimation(M_bck_data, -1.0f, 0.0f)) {
        mpMorf->setPlaySpeed(0.0f);
        return TRUE;
    }
    return FALSE;
}

/* 00000E74-00000ED0       .text process_normal_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_normal_main() {
    if (mNormalCounter == 0 || mNormalCounter == 1) {
        mNormalCounter++;
    }
    cLib_addCalc(&mWindScale, 1.0f, 0.01f, 1.0f, 0.007f);
}

char const daObjVyasi::Act_c::M_arcname[] = "Vyasi";

/* 00000ED0-00000FE4       .text process_init__Q210daObjVyasi5Act_cFi */
BOOL daObjVyasi::Act_c::process_init(int i_idx) {
    typedef BOOL (daObjVyasi::Act_c::*initProc)();
    static initProc init_table[] = {
        &daObjVyasi::Act_c::process_none_init,     &daObjVyasi::Act_c::process_sag_init,    &daObjVyasi::Act_c::process_sagWind_init,
        &daObjVyasi::Act_c::process_toNormal_init, &daObjVyasi::Act_c::process_normal_init,
    };

    if (i_idx >= 0 && i_idx < STATE_MAX && (this->*init_table[i_idx])()) {
        mState = i_idx;
        return TRUE;
    }
    return FALSE;
}

/* 00000FE4-000010C8       .text process_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_main() {
    typedef void (daObjVyasi::Act_c::*mainProc)();
    static mainProc main_table[] = {
        &daObjVyasi::Act_c::process_none_main,     &daObjVyasi::Act_c::process_sag_main,    &daObjVyasi::Act_c::process_sagWind_main,
        &daObjVyasi::Act_c::process_toNormal_main, &daObjVyasi::Act_c::process_normal_main,
    };

    if (mState >= 0 && mState < STATE_MAX) {
        (this->*main_table[mState])();
    }
}

/* 000010C8-000010EC       .text solidHeapCB__Q210daObjVyasi5Act_cFP10fopAc_ac_c */
BOOL daObjVyasi::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->create_heap();
}

/* 000010EC-00001290       .text create_heap__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::create_heap() {
    J3DModelData* mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VYASI_BDL_VYASI_e);
    JUT_ASSERT(1146, mdl_data != NULL);

    M_bck_data = (J3DAnmTransformKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VYASI_BCK_VYASI_e);
    JUT_ASSERT(1151, M_bck_data != NULL);

    if (M_bck_data != NULL && mdl_data != NULL) {
        mpMorf = new mDoExt_McaMorf(mdl_data, NULL, NULL, M_bck_data, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, 1, NULL, 0, 0x11000002);
    }
    return M_bck_data != NULL && mpMorf != NULL && mpMorf->getModel() != NULL;
}

/* 00001290-000016E0       .text _create__Q210daObjVyasi5Act_cFv */
cPhs_State daObjVyasi::Act_c::_create() {
    fopAcM_ct(this, daObjVyasi::Act_c);

    cPhs_State res = dComIfG_resLoad(&mPhs, M_arcname);
    if (res == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
            set_first_process();
            set_mtx();
            fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
            fopAcM_setCullSizeBox(this, -2000.0f, 0.0f, -2000.0f, 2000.0f, 2000.0f, 2000.0f);
            fopAcM_setCullSizeFar(this, 2.0f);
            mStts.Init(0xFF, 0xFF, this);
            mCyl.Set(M_cyl_src);
            mCyl.SetStts(&mStts);
            mCyl.SetTgVec((cXyz&)cXyz::Zero);
            mCyl.OnTgNoHitMark();

            for (int i = 0; i < 5; i++) {
                mCpsStts[i].Init(100, 0xFF, this);
                mCps[i].Set(M_cps_src);
                mCps[i].SetStts(&mCpsStts[i]);
                field_0xDF8[i].mStart = current.pos;
                field_0xDF8[i].mEnd = current.pos;
                field_0xDF8[i].mRadius = 100.0f;
            }

            for (int i = 0; i < 8; i++) {
                field_0xE84[i].Init(100, 0xFF, this);
                field_0x1064[i].Set(M_sph_src);
                field_0x1064[i].SetStts(&field_0xE84[i]);
                mCyl.SetTgVec((cXyz&)cXyz::Zero);
                mCyl.OnTgNoHitMark();
            }

            J3DModel* model = mpMorf->getModel();
            J3DModelData* modelData = model->getModelData();
            model->setUserArea((uintptr_t)this);
            for (u16 i = 0; i < model->getModelData()->getJointNum(); i++) {
                modelData->getJointNodePointer(i)->setCallBack(JointNodeCallBack);
            }

            for (u16 i = 0; i < 14; i++) {
                mJointQuat[i] = ZeroQuat;
            }

            mLeafScale.set(1.0f, 1.0f, 1.0f);
        } else {
            res = cPhs_ERROR_e;
        }
    }
    return res;
}

/* 00001D8C-00001DBC       .text _delete__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_delete() {
    dComIfG_resDeleteDemo(&mPhs, M_arcname);
    return true;
}

/* 00001DBC-00001E5C       .text set_mtx__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_mtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), mMtx);
}

/* 00001E5C-000025A8       .text calc_dif_angle__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::calc_dif_angle() {
    for (int i = 0; i < 14; i++) {
        csXyz target(0, 0, 0);
        s16 step = 2;
        if (mState == STATE_SAG_WIND) {
            if (joint_kind_table[i] == 2) {
                f32 ratio = mSagRatio * cM_ssin(mWavePhase[i]);
                target.set(20.0f * ratio, 40.0f * ratio, 40.0f * ratio);
            } else if (joint_kind_table[i] == 1) {
                f32 ratio = mSagRatio * cM_ssin(mWavePhase[i]);
                target.set(120.0f * ratio, 180.0f * ratio, 220.0f * ratio);

                if (i == 1) {
                    target.z += (s16)(-3200.0f + 3200.0f * mSagRatio);
                }
            } else if (joint_kind_table[i] == 0) {
                static csXyz sag_offset_angle[14] = {
                    csXyz(0, 0, 0), csXyz(0, 0, 0),    csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0),     csXyz(0, 0, 0),     csXyz(0, 0, 0),
                    csXyz(0, 0, 0), csXyz(0, 0, 5000), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, -5000), csXyz(0, 0, -7000), csXyz(0, 0, -2700),
                };
                f32 ratio = mSagRatio * cM_ssin(mWavePhase[i]);
                target.set(700.0f * ratio, 1700.0f * ratio, 1700.0f * ratio);

                target.x += sag_offset_angle[i].x;
                target.y += sag_offset_angle[i].y;
                target.z += sag_offset_angle[i].z;
                step = 1;
            }
        } else if (mState == STATE_TO_NORMAL) {
            if (mAnmPlaying == 0 && (i == 0 || i == 1 || i == 6)) {
                target.z = field_0x19CC * cM_ssin(field_0x19D0);
            }
        }

        cLib_addCalcAngleS2(&mJointAngle[i].x, target.x, step, 0x4000);
        cLib_addCalcAngleS2(&mJointAngle[i].y, target.y, step, 0x4000);
        cLib_addCalcAngleS2(&mJointAngle[i].z, target.z, step, 0x4000);

        if (joint_kind_table[i] == 0) {
            mWavePhase[i] += (s16)(1.5f * mWaveSpeed[i]);
        } else {
            mWavePhase[i] += mWaveSpeed[i];
        }
    }
}

/* 000025A8-00002880       .text quaternion_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::quaternion_main() {
    for (int i = 0; i < 14; i++) {
        Quaternion quat;
        quat = ZeroQuat;

        if (mState == STATE_NORMAL && joint_kind_table[i] == 0) {
            cXyz up(0.0f, 1.0f, 0.0f);
            cMtx_YrotS(*calc_mtx, -current.angle.y);

            cXyz windDir;
            MtxPosition(dKyw_get_wind_vec(), &windDir);

            f32 windPow = dKyw_get_wind_pow();
            cXyz dir = up.outprod(windDir);
            s16 angle = 1400.0f * windPow * mWindScale;
            f32 sin = cM_ssin(angle);

            Quaternion windQuat;
            windQuat.x = sin * dir.x;
            windQuat.y = sin * dir.y;
            windQuat.z = sin * dir.z;
            windQuat.w = cM_scos(angle);

            s16 target = 360.0f * windPow * mWindScale;
            target = target > 0xDC ? 0xDC : target;
            cLib_addCalcAngleS2(&mAnimDir[i], target, 4, 0x20);
            s32 add = (2048.0f * windPow * mWindScale) + cM_rndFX(256.0f);
            mAnimWave[i] += add;
            f32 w = cM_ssin(mAnimDir[i]);

            Quaternion animQuat;
            animQuat.x = w * cM_ssin(mAnimWave[i]);
            animQuat.y = 0.0f;
            animQuat.z = w * cM_ssin(mAnimWave[i]);
            animQuat.w = cM_scos(mAnimDir[i]);
            mDoMtx_quatMultiply(&windQuat, &animQuat, &quat);
        }

        if (mNormalCounter == 1) {
            mJointQuat[i] = quat;
        } else {
            mDoMtx_quatSlerp(&mJointQuat[i], &quat, &mJointQuat[i], 0.4f);
        }
    }
}

/* 00002880-00002938       .text leaf_scale_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::leaf_scale_main() {
    cXyz scale(1.0f, 1.0f, 1.0f);
    if (mState == STATE_SAG_WIND) {
        scale.x = 0.35000002f * mSagRatio + 1.0f;
        scale.y = -0.5f * mSagRatio + 1.0f;
        scale.z = scale.y;
    }
    cLib_addCalc2(&mLeafScale.x, scale.x, 0.5f, 0.5f);
    cLib_addCalc2(&mLeafScale.y, scale.y, 0.5f, 0.5f);
    cLib_addCalc2(&mLeafScale.z, scale.z, 0.5f, 0.5f);
}

/* 00002938-000029BC       .text _execute__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_execute() {
    if (mState != STATE_NONE) {
        mAnmPlaying = PlayStopJointAnimation();
        process_main();
        set_collision();
        quaternion_main();
        calc_dif_angle();
        leaf_scale_main();
        set_mtx();
        fopAcM_rollPlayerCrash(this, 79.0f, 7);
    }
    return true;
}

/* 000029BC-00002A6C       .text _draw__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_draw() {
    if (mState != STATE_NONE) {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpMorf->getModel(), &tevStr);
        dComIfGd_setListBG();
        mpMorf->updateDL();
        dComIfGd_setList();
    }
    return true;
}

namespace daObjVyasi {
namespace {
/* 00002A6C-00002A8C       .text Mthd_Create__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_create();
}

/* 00002A8C-00002AB0       .text Mthd_Delete__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_delete();
}

/* 00002AB0-00002AD4       .text Mthd_Execute__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_execute();
}

/* 00002AD4-00002AF8       .text Mthd_Draw__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_draw();
}

/* 00002AF8-00002B00       .text Mthd_IsDelete__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjVyasi

actor_process_profile_definition g_profile_Obj_Vyasi = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Vyasi_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjVyasi::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Vyasi_e,
    /* Actor SubMtd */ &daObjVyasi::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
