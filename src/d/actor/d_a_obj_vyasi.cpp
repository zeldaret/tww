/**
 * d_a_obj_vyasi.cpp
 * Object - Palm tree blowing in the wind (Gale Isle)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_vyasi.h"
#include "d/d_a_obj.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo_wether.h"
#include "d/d_lib.h"
#include "m_Do/m_Do_ext.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "res/Object/Vyasi.h"

namespace daObjVyasi {
namespace {
    struct Attr_c {
        /* 0x00 */ f32 field_0x00;
        /* 0x04 */ f32 field_0x04;
        /* 0x08 */ f32 field_0x08;
        /* 0x0C */ Vec field_0x0c;
        /* 0x18 */ f32 field_0x18;
        /* 0x1C */ f32 field_0x1c;
        /* 0x20 */ s16 field_0x20;
        /* 0x22 */ s16 field_0x22;
        /* 0x24 */ f32 field_0x24;
        /* 0x28 */ f32 field_0x28;
        /* 0x2C */ f32 field_0x2c;
        /* 0x30 */ s16 field_0x30[14][3];
    };

    const Attr_c L_attr = {
        1.0f, 79.0f, 250.0f, {0.0f, 0.0f, 0.0f}, 0.4f, 1.5f, 2, 0, 700.0f, 1700.0f, 1700.0f,
    };
} // namespace

static const dCcD_SrcCyl M_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
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
        /* Center */ { 0.0f, 0.0f, 0.0f },
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
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
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
        /* Start  */ { 0.0f, 0.0f, 0.0f },
        /* End    */ { 0.0f, 0.0f, 0.0f },
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
        /* Center */ { 0.0f, 0.0f, 0.0f },
        /* Radius */ 100.0f,
    }},
};

static u8 joint_kind_table[14] = {2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
} // namespace daObjVyasi

inline BOOL daObjVyasi::Act_c::is_switch() const {
    return fopAcM_isSwitch((fopAc_ac_c*)this, daObj::PrmAbstract(this, 8, 0));
}

/* 000000EC-0000015C       .text SetStopJointAnimation__Q210daObjVyasi5Act_cFP18J3DAnmTransformKeyff */
BOOL daObjVyasi::Act_c::SetStopJointAnimation(J3DAnmTransformKey* i_anm, f32 i_playSpeed, f32 i_morf) {
    if (i_anm != NULL) {
        mpMorf->setAnm(i_anm, 0, i_morf, i_playSpeed, 0.0f, -1.0f, NULL);
        m19C4 = 1;
        return TRUE;
    }
    return FALSE;
}

/* 0000015C-00000194       .text PlayStopJointAnimation__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::PlayStopJointAnimation() {
    return mpMorf->play(NULL, 0, 0) ? 0 : 1;
}

/* 00000194-0000021C       .text set_first_process__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_first_process() {
    process_init(is_switch() ? 4 : 1);
    mNormalCounter = 0;
    m19D4 = 1.0f;
    shape_angle.y += 0x8000;
}

/* 0000021C-000005B8       .text set_collision__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_collision() {
    if (mCyl.ChkTgHit()) {
        mCyl.GetTgHitObj();
        daObj::HitSeStart(&current.pos, current.roomNo, &mCyl, 7);
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
            daObj::HitSeStart(&current.pos, current.roomNo, &mCps[i], 7);
            dKy_Sound_set(current.pos, 4, fopAcM_GetID(this), 100);
            mCps[i].ClrTgHit();
        } else {
            int k = i + 1;
            mCpsData[i].mStart = m0400[i];
            mCpsData[i].mEnd = m0400[k];
            mCpsData[i].mRadius = 47.4f;
            mCps[i].cM3dGCps::Set(mCpsData[i]);
            dComIfG_Ccsp()->Set(&mCps[i]);
        }
    }

    for (int i = 0; i < 8; i += 2) {
        int j = i >> 1;
        int j1 = j + 1;
        int j2 = j + 2;
        cXyz delta;
        cXyz pos;
        delta.set(0.33333f * (m0400[j2].x - m0400[j1].x),
                  0.33333f * (m0400[j2].y - m0400[j1].y),
                  0.33333f * (m0400[j2].z - m0400[j1].z));
        pos.x = m0400[j1].x + delta.x;
        pos.y = m0400[j1].y + delta.y;
        pos.z = m0400[j1].z + delta.z;
        mSph[i].SetC(pos);
        mSph[i].SetR(47.4f);
        dComIfG_Ccsp()->Set(&mSph[i]);
        pos.x = m0400[j1].x + 2.0f * delta.x;
        pos.y = m0400[j1].y + 2.0f * delta.y;
        pos.z = m0400[j1].z + 2.0f * delta.z;
        mSph[i + 1].SetC(pos);
        mSph[i + 1].SetR(47.4f);
        dComIfG_Ccsp()->Set(&mSph[i + 1]);
    }
}

/* 000005F4-000009B8       .text JointNodeCallBack__10daObjVyasiFP7J3DNodei */
BOOL daObjVyasi::JointNodeCallBack(J3DNode* i_node, int i_timing) {
    J3DModel* model = j3dSys.getModel();
    s32 jntNo = ((J3DJoint*)i_node)->getJntNo();
    Act_c* i_this = (Act_c*)model->getUserArea();
    if (i_timing == 0) {
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

        csXyz add_angle_table[14] = {
            csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0),
            csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0),
            csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0),
        };
        csXyz ang = add_angle_table[jntNo];
        ang += i_this->m03AC[jntNo];
        mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
        mDoMtx_stack_c::ZXYrotM(ang);
        if (joint_kind_table[jntNo] == 0) {
            mDoMtx_stack_c::scaleM(i_this->m04A8, i_this->m04AC, i_this->m04B0);
        }
        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        MTXCopy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
        cXyz base(0.0f, 0.0f, 0.0f);
        cMtx_multVec(mDoMtx_stack_c::get(), &base, &i_this->m0400[jntNo]);
    }
    return TRUE;
}

/* 000009F4-000009FC       .text process_none_init__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::process_none_init() {
    return TRUE;
}

/* 000009FC-00000A00       .text process_none_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_none_main() {
}

/* 00000A00-00000A64       .text process_sag_init__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::process_sag_init() {
    if (SetStopJointAnimation(M_bck_data, 1.0f, 0.0f)) {
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
        process_init(2);
    }
}

/* 00000AD8-00000CC0       .text process_sagWind_init__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::process_sagWind_init() {
    if (SetStopJointAnimation(M_bck_data, 1.0f, 3.0f)) {
        f32 dist = mEkszsPos.abs(current.pos);
        dist = dist > 2800.0f ? 2800.0f : dist;
        dist = dist < 1000.0f ? 1000.0f : dist;
        m0504 = (dist - 2800.0f) / -1800.0f;
        f32 amp = 5000.0f + 7000.0f * m0504;
        for (int i = 0; i < 14; i++) {
            if (joint_kind_table[i] == 0) {
                if (!(i & 1)) {
                    m0524[i] = amp + cM_rndF(2000.0f);
                } else {
                    m0524[i] = -(amp + cM_rndF(2000.0f));
                }
            } else {
                m0524[i] = 0.5f * amp;
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
        process_init(3);
    }
}

/* 00000D20-00000D54       .text process_toNormal_init__Q210daObjVyasi5Act_cFv */
BOOL daObjVyasi::Act_c::process_toNormal_init() {
    return SetStopJointAnimation(M_bck_data, 1.0f, 0.0f);
}

/* 00000D54-00000E10       .text process_toNormal_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_toNormal_main() {
    if (m19C4 == 0) {
        if (std::fabsf(m19CC) <= 0.1f) {
            if (process_init(4)) {
                m19CC = 0.0f;
                m19D4 = 0.0f;
                mNormalCounter = 2;
            }
        }
        m19CC *= 0.85f;
        m19D0 += 0x3000;
    } else {
        m19CC = -1792.0f * m0504;
        m19D0 = 0;
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
    cLib_addCalc(&m19D4, 1.0f, 0.01f, 1.0f, 0.007f);
}

/* 00000ED0-00000FE4       .text process_init__Q210daObjVyasi5Act_cFi */
BOOL daObjVyasi::Act_c::process_init(int i_no) {
    static BOOL (Act_c::*init_table[5])() = {
        &Act_c::process_none_init,
        &Act_c::process_sag_init,
        &Act_c::process_sagWind_init,
        &Act_c::process_toNormal_init,
        &Act_c::process_normal_init,
    };
    if (i_no >= 0 && i_no < 5 && (this->*init_table[i_no])()) {
        mState = i_no;
        return TRUE;
    }
    return FALSE;
}

/* 00000FE4-000010C8       .text process_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_main() {
    static void (Act_c::*main_table[5])() = {
        &Act_c::process_none_main,
        &Act_c::process_sag_main,
        &Act_c::process_sagWind_main,
        &Act_c::process_toNormal_main,
        &Act_c::process_normal_main,
    };
    if (mState >= 0 && mState < 5) {
        (this->*main_table[mState])();
    }
}

/* 000010C8-000010EC       .text solidHeapCB__Q210daObjVyasi5Act_cFP10fopAc_ac_c */
BOOL daObjVyasi::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->create_heap();
}

const char daObjVyasi::Act_c::M_arcname[6] = "Vyasi";

/* 000010EC-00001290       .text create_heap__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::create_heap() {
    J3DModelData* mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VYASI_BDL_VYASI_e);
    JUT_ASSERT(1146, mdl_data != 0);
    M_bck_data = (J3DAnmTransformKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VYASI_BCK_VYASI_e);
    JUT_ASSERT(1151, M_bck_data != 0);
    if (M_bck_data != NULL && mdl_data != NULL) {
        mpMorf = new mDoExt_McaMorf(mdl_data, NULL, NULL, M_bck_data, 0, 1.0f, 0, -1, 1, NULL, 0, 0x11000002);
    }
    return M_bck_data != NULL && mpMorf != NULL && mpMorf->getModel() != NULL;
}

/* 00001290-000016E0       .text _create__Q210daObjVyasi5Act_cFv */
cPhs_State daObjVyasi::Act_c::_create() {
    fopAcM_SetupActor(this, Act_c);

    cPhs_State step = dComIfG_resLoad(&mPhs, M_arcname);
    if (step == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
            set_first_process();
            set_mtx();
            fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
            fopAcM_setCullSizeBox(this, -2000.0f, 0.0f, -2000.0f, 2000.0f, 2000.0f, 2000.0f);
            fopAcM_setCullSizeFar(this, 2.0f);
            mStts.Init(0xff, 0xff, this);
            mCyl.Set(M_cyl_src);
            mCyl.SetStts(&mStts);
            mCyl.SetTgVec((cXyz&)cXyz::Zero);
            mCyl.OnTgNoHitMark();
            for (int i = 0; i < 5; i++) {
                mCpsStts[i].Init(100, 0xff, this);
                mCps[i].Set(M_cps_src);
                mCps[i].SetStts(&mCpsStts[i]);
                mCpsData[i].mStart = current.pos;
                mCpsData[i].mEnd = current.pos;
                mCpsData[i].mRadius = 100.0f;
            }
            for (int i = 0; i < 8; i++) {
                mSphStts[i].Init(100, 0xff, this);
                mSph[i].Set(M_sph_src);
                mSph[i].SetStts(&mSphStts[i]);
                mCyl.SetTgVec((cXyz&)cXyz::Zero);
                mCyl.OnTgNoHitMark();
            }
            J3DModel* model = mpMorf->getModel();
            J3DModelData* mdl_data = model->getModelData();
            model->setUserArea((u32)this);
            for (u16 i = 0; i < model->getModelData()->getJointNum(); i++) {
                mdl_data->getJointNodePointer(i)->setCallBack(JointNodeCallBack);
            }
            for (u16 i = 0; i < 14; i++) {
                mJointQuat[i] = ZeroQuat;
            }
            m04A8 = 1.0f;
            m04AC = 1.0f;
            m04B0 = 1.0f;
        } else {
            step = cPhs_ERROR_e;
        }
    }

    return step;
}

/* 00001D8C-00001DBC       .text _delete__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_delete() {
    dComIfG_resDelete(&mPhs, M_arcname);
    return true;
}

/* 00001DBC-00001E5C       .text set_mtx__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_mtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), m04BC);
}

/* 00001E5C-000025A8       .text calc_dif_angle__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::calc_dif_angle() {
    for (int i = 0; i < 14; i++) {
        csXyz target(0, 0, 0);
        s16 step = 2;
        if (mState == 2) {
            if (joint_kind_table[i] == 2) {
                f32 ratio = m0504 * cM_ssin(m0508[i]);
                target.x = 20.0f * ratio;
                target.y = 40.0f * ratio;
                target.z = 40.0f * ratio;
            } else if (joint_kind_table[i] == 1) {
                f32 ratio = m0504 * cM_ssin(m0508[i]);
                target.x = 120.0f * ratio;
                target.y = 180.0f * ratio;
                target.z = 220.0f * ratio;
                if (i == 1) {
                    target.z += (s16)(-3200.0f + 3200.0f * m0504);
                }
            } else if (joint_kind_table[i] == 0) {
                static csXyz sag_offset_angle[14] = {
                    csXyz(0, 0, 0),    csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0),
                    csXyz(0, 0, 0),    csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, 0),
                    csXyz(0, 0, 5000), csXyz(0, 0, 0), csXyz(0, 0, 0), csXyz(0, 0, -5000),
                    csXyz(0, 0, -7000), csXyz(0, 0, -2700),
                };
                f32 ratio = m0504 * cM_ssin(m0508[i]);
                target.x = 700.0f * ratio;
                target.y = 1700.0f * ratio;
                target.z = 1700.0f * ratio;
                target.x += sag_offset_angle[i].x;
                target.y += sag_offset_angle[i].y;
                target.z += sag_offset_angle[i].z;
                step = 1;
            }
        } else if (mState == 3) {
            if (m19C4 == 0 && (i == 0 || i == 1 || i == 6)) {
                target.z = m19CC * cM_ssin(m19D0);
            }
        }
        cLib_addCalcAngleS2(&m03AC[i].x, target.x, step, 0x4000);
        cLib_addCalcAngleS2(&m03AC[i].y, target.y, step, 0x4000);
        cLib_addCalcAngleS2(&m03AC[i].z, target.z, step, 0x4000);
        if (joint_kind_table[i] == 0) {
            m0508[i] += (s16)(1.5f * m0524[i]);
        } else {
            m0508[i] += m0524[i];
        }
    }
}

/* 000025A8-00002880       .text quaternion_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::quaternion_main() {
    for (int i = 0; i < 14; i++) {
        Quaternion q;
        q = ZeroQuat;
        if (mState == 4 && joint_kind_table[i] == 0) {
            cXyz up(0.0f, 1.0f, 0.0f);
            mDoMtx_YrotS(*calc_mtx, -current.angle.y);
            cXyz windvec;
            MtxPosition(dKyw_get_wind_vec(), &windvec);
            f32 windPow = dKyw_get_wind_pow();
            cXyz axis = up.outprod(windvec);
            s16 angle = 1400.0f * windPow * m19D4;
            f32 sin = cM_ssin(angle);
            Quaternion q2;
            q2.x = sin * axis.x;
            q2.y = sin * axis.y;
            q2.z = sin * axis.z;
            q2.w = cM_scos(angle);
            s16 target = 360.0f * windPow * m19D4;
            target = target > 0xdc ? 0xdc : target;
            cLib_addCalcAngleS2(&m02B0[i], target, 4, 0x20);
            s32 add = (2048.0f * windPow * m19D4) + cM_rndFX(256.0f);
            m0294[i] += add;
            f32 w = cM_ssin(m02B0[i]);
            Quaternion q3;
            q3.x = w * cM_ssin(m0294[i]);
            q3.y = 0.0f;
            q3.z = w * cM_ssin(m0294[i]);
            q3.w = cM_scos(m02B0[i]);
            PSQUATMultiply(&q2, &q3, &q);
        }
        if (mNormalCounter == 1) {
            mJointQuat[i] = q;
        } else {
            mDoMtx_quatSlerp(&mJointQuat[i], &q, &mJointQuat[i], 0.4f);
        }
    }
}

/* 00002880-00002938       .text leaf_scale_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::leaf_scale_main() {
    f32 scale[3];
    f32* p = scale;
    p[0] = 1.0f;
    p[1] = 1.0f;
    p[2] = 1.0f;
    if (mState == 2) {
        p[0] = 1.0f + (1.0f - 0.65f) * m0504;
        p[2] = p[1] = 1.0f + -0.5f * m0504;
    }
    cLib_addCalc2(&m04A8, p[0], 0.5f, 0.5f);
    cLib_addCalc2(&m04AC, p[1], 0.5f, 0.5f);
    cLib_addCalc2(&m04B0, p[2], 0.5f, 0.5f);
}

/* 00002938-000029BC       .text _execute__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_execute() {
    if (mState != 0) {
        m19C4 = PlayStopJointAnimation();
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
    if (mState != 0) {
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
