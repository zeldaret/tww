/**
 * d_a_mt.cpp
 * Enemy - Magtail
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mt.h"
#include "d/res/res_mt.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_kankyo_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_path.h"
#include "d/d_s_play.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_cc_uty.h"
#include "d/d_snap.h"
#include "d/actor/d_a_player.h"

static u8 mt_count;
daMt_HIO_c l_HIO;
static int mt_all_count;
static int mt_fight_count;
static int j_index;

static u16 mt_tex_anm_idx[2] = {
    MT_BTP_MG_MABA, MT_BTP_MG_TOJI
};

static u16 mt_tex_max_frame[2] = {
    6, 1
};

static int brk_data[8] = {
    MT_BRK_MG_HEAD1,
    MT_BRK_MG_BODY1, MT_BRK_MG_BODY1, MT_BRK_MG_BODY1, MT_BRK_MG_BODY1, MT_BRK_MG_BODY1, MT_BRK_MG_BODY1,
    MT_BRK_MG_TAIL1
};

static int btk_data[8] = {
    MT_BTK_MG_HEAD1, 
    MT_BTK_MG_BODY1, MT_BTK_MG_BODY1, MT_BTK_MG_BODY1, MT_BTK_MG_BODY1, MT_BTK_MG_BODY1, MT_BTK_MG_BODY1,
    MT_BTK_MG_TAIL1
};

static int move_ad[8] = {0, -6, -12, -18, -24, -30, -36, -42};
static int move_ad2[8] = {0, -3, -6, -9, -12, -15, -18, -21};

static s16 br_no[6] = {1, 0x102, 0x202, 0x100, 0, 0};
static s16 br_ya[11] = {0xCD38, 0xDCD8, 0xF060, 0, 0, 0, 0, 0, 0, 0, 0};

/* 000000EC-000001E8       .text __ct__10daMt_HIO_cFv */
daMt_HIO_c::daMt_HIO_c() {
    m04 = 0;
    m05 = 0;
    m06 = 0;
    m07 = 0;
    m08 = 0x157C;
    m0C = -7500.0f;
    m10 = 15;
    m14 = 0.5f;
    m18 = 21.0f;
    m1C = 0.8f;
    m20 = 0.8f;
    m24 = 450.0f;
    m28 = 350.0f;
    m2C = 30.0f;
    m30 = 17;
    m32 = 40;
    m34 = 400.0f;
    m38 = 45;
    m3C = 43;
    m3E = 47;
    m3A = 70;
    m40 = 55.0f;
    m44 = 30.0f;
    m48 = 25.0f;
    m4C = 0.65f;
    m50 = -5;
    m52 = 11000;
    m54 = 600;
    m58 = 1.0f;
    m5C = 1.0f;
}

/* 00000230-000002D8       .text anm_init__FP8mt_classifUcfi */
void anm_init(mt_class* i_this, int index, float morf, unsigned char loopMode, float playSpeed, int param_6) {
    J3DAnmTransform* bckAnm = (J3DAnmTransform*) dComIfG_getObjectRes("Mt", index);
    i_this->mpMorfs[0]->setAnm(bckAnm, loopMode, morf, playSpeed, 0.0f, -1.0f, NULL);
}

/* 000002D8-00000350       .text mt_a_d_sub__FPvPv */
void* mt_a_d_sub(void* param_1, void*) {
    if (fopAcM_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_MT) {
        mt_all_count++;
        mt_class* mt = (mt_class*)param_1;
        if (mt->m454 == 1) {
            mt_fight_count++;
        }
    }
    return NULL;
}

/* 00000350-00000390       .text mt_check__FP8mt_class */
void mt_check(mt_class* i_this) {
    mt_fight_count = 0;
    mt_all_count = 0;
    fpcM_Search(&mt_a_d_sub, i_this);
}

/* 00000390-00000478       .text mt_bg_check__FP8mt_class */
void mt_bg_check(mt_class* i_this) {
    f32 fVar1 = REG0_F(3) + 40.0f;
    i_this->current.pos.y -= fVar1;
    i_this->old.pos.y -= fVar1;
    fopAcM_OnStatus(i_this, fopAcStts_FREEZE_e);
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    i_this->current.pos.y += fVar1;
    i_this->old.pos.y += fVar1;
    if (i_this->home.pos.y - i_this->current.pos.y > 1000.0f && i_this->current.pos.y - i_this->mAcch.GetGroundH() > 5000.0f) {
        i_this->m1CBC = 1;
        fopAcM_delete(i_this);
    }
}

/* 00000478-0000053C       .text tex_anm_set__FP8mt_classUs */
void tex_anm_set(mt_class* i_this, u16 index) {
    i_this->m345 = 1;
    J3DAnmTexPattern* btp = (J3DAnmTexPattern*)dComIfG_getObjectRes("Mt", mt_tex_anm_idx[index]);
    i_this->m346 = mt_tex_max_frame[index];
    i_this->m33C = btp;
    i_this->m344 = 0;
    i_this->m33C->setFrame(0.0f);
    u16 material_num = btp->getUpdateMaterialNum();
    for (u16 i = 0; i < material_num; i++) {
        i_this->m340[i].setAnmTexPattern(btp);
    }
}

/* 0000053C-000005EC       .text mt_eye_tex_anm__FP8mt_class */
void mt_eye_tex_anm(mt_class* i_this) {
    if (i_this->m464 != 0) {
        i_this->m464--;
    } else {
        i_this->m464 = cM_rndF(100.0f) + 50.0f;
        if (i_this->m345 == 0) {
            tex_anm_set(i_this, 0);
        }
    }

    if (i_this->m345 != 0) {
        if (i_this->m344 < i_this->m346) {
            i_this->m344++;
        } else {
            i_this->m345 = 0;
        }
    }
}

/* 000005EC-00000720       .text nodeCallBack_head__FP7J3DNodei */
static BOOL nodeCallBack_head(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        s32 jntNo = ((J3DJoint*) node)->getJntNo();
        J3DModel* model = j3dSys.getModel();
        mt_class* i_this = (mt_class*) model->getUserArea();
        if (i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo == 2) {
                cMtx_YrotM(*calc_mtx, -i_this->m640);
                cMtx_ZrotM(*calc_mtx, -i_this->m644);
            } else if (jntNo == 3) {
                cMtx_YrotM(*calc_mtx, i_this->m69A);
                cMtx_ZrotM(*calc_mtx, -i_this->m69E);
            } else {
                f32 scale = i_this->m18F0;
                MtxScale(scale, scale, scale, true);
            }
            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 0000075C-0000098C       .text nodeCallBack_body__FP7J3DNodei */
static BOOL nodeCallBack_body(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        s32 jntNo = ((J3DJoint*) node)->getJntNo();
        J3DModel* model = j3dSys.getModel();
        mt_class* i_this = (mt_class*) model->getUserArea();
        if (i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo == 2) {
                cMtx_YrotM(*calc_mtx, -i_this->m640);
                cMtx_ZrotM(*calc_mtx, -i_this->m644);
            } else if (jntNo == 3) {
                cMtx_YrotM(*calc_mtx, i_this->m69A);
                cMtx_ZrotM(*calc_mtx, -i_this->m69E);
            } else {
                f32 scale = i_this->m18F0;
                MtxScale(scale, scale, scale, true);
            }
            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 0000098C-00000B28       .text nodeCallBack_tail__FP7J3DNodei */
static BOOL nodeCallBack_tail(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        s32 jntNo = ((J3DJoint*) node)->getJntNo();
        J3DModel* model = j3dSys.getModel();
        mt_class* i_this = (mt_class*) model->getUserArea();
        if (i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo == 2) {
                cMtx_YrotM(*calc_mtx, -i_this->m68E);
                cMtx_ZrotM(*calc_mtx, -i_this->m692);
            } else if (jntNo == 3) {
                cMtx_YrotM(*calc_mtx, -i_this->m694);
                cMtx_ZrotM(*calc_mtx, -i_this->m698);
            } else if (jntNo == 4) {
                cMtx_YrotM(*calc_mtx, i_this->m6E8);
                cMtx_ZrotM(*calc_mtx, -i_this->m6EC);
            } else if (jntNo == 5) {
                cMtx_YrotM(*calc_mtx, i_this->m6EE);
                cMtx_ZrotM(*calc_mtx, -i_this->m6F2);
            }
            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00000B28-0000171C       .text body_control2__FP8mt_class */
void body_control2(mt_class* i_this) {
    f32 fVar1 = i_this->m18F4;
    i_this->mPos[0] = i_this->current.pos;
    i_this->m560[0] = i_this->shape_angle;

    dBgS_LinChk linChk;

    cXyz local_184(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < 8; i++) {
        if (i > 0) {
            cXyz local_178(i_this->mPos[i].x, i_this->mPos[i].y, i_this->mPos[i].z + 50.0f);
            cMtx_YrotS(*calc_mtx, i_this->m560[i].y);
            cXyz offset(3.0f, -200.0f, 0.0f);
            cXyz out1;
            MtxPosition(&offset, &out1);
            out1 += i_this->mPos[i];
            linChk.Set(&local_178, &out1, i_this);
            u8 crossed = dComIfG_Bgsp()->LineCross(&linChk);
            if (crossed != 0) {
                out1 = linChk.GetCross();
            }
            offset.x *= -1.0f;
            cXyz out2;
            MtxPosition(&offset, &out2);
            out2 += i_this->mPos[i];
            linChk.Set(&local_178, &out2, i_this);
            if (dComIfG_Bgsp()->LineCross(&linChk)) {
                out2 = linChk.GetCross();
                crossed++;
            }

            s16 target = 0;
            f32 f30;
            if (crossed == 2) {
                f30 = i_this->mPos[i].y - 10.0f;
                f32 fVar2 = out1.y + l_HIO.m18;
                if (f30 < fVar2) {
                    offset = out1 - out2;
                    f32 fVar3 = std::sqrtf(offset.x * offset.x + offset.z * offset.z);
                    target = cM_atan2s(offset.y, fVar3);
                    f30 = fVar2;
                }
            }

            cLib_addCalcAngleS2(&i_this->m560[i].z, target, 2, 0x400);
            f32 f = i_this->m590[i].y + f30 - i_this->mPos[i - 1].y;
            if (i_this->m48E == 0) {
                cXyz offset(
                    cM_ssin(i_this->m46A * (REG0_S(5) + 0x5DC) + i * (REG0_S(6) + 0x1D4C)) * 3.0f,
                    0.0f,
                    REG0_F(3) + -5.0f
                );
                cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
                MtxPosition(&offset, &local_184);
            }

            f32 fVar4 = local_184.x + i_this->m590[i].x + i_this->mPos[i].x - i_this->mPos[i - 1].x;
            f32 fVar5 = local_184.z + i_this->m590[i].z + i_this->mPos[i].z - i_this->mPos[i - 1].z;
            int iVar8 = cM_atan2s(fVar4, fVar5);
            fVar4 = std::sqrtf(fVar4 * fVar4 + fVar5 * fVar5);
            s16 iVar9 = -cM_atan2s(f, fVar4);
            cXyz offset2(0.0f, 0.0f, REG0_F(7) + 35.0f);
            cMtx_YrotS(*calc_mtx, iVar8);
            cMtx_XrotM(*calc_mtx, iVar9);
            cXyz local_16c;
            MtxPosition(&offset2, &local_16c);
            i_this->m560[i].x = iVar9;
            i_this->m560[i].y = iVar8 - 0x8000;
            i_this->mOld[i] = i_this->mPos[i];

            i_this->mPos[i].x = i_this->mPos[i - 1].x + local_16c.x;
            i_this->mPos[i].y = i_this->mPos[i - 1].y + local_16c.y;
            i_this->mPos[i].z = i_this->mPos[i - 1].z + local_16c.z;
            i_this->m590[i].x = fVar1 * (i_this->mPos[i].x - i_this->mOld[i].x);
            i_this->m590[i].y = fVar1 * (i_this->mPos[i].y - i_this->mOld[i].y);
            i_this->m590[i].z = fVar1 * (i_this->mPos[i].z - i_this->mOld[i].z);
        }

        J3DModel* model = i_this->mpMorfs[i]->getModel();
        model->setBaseScale(i_this->scale);
        mDoMtx_stack_c::transS(i_this->mPos[i]);
        mDoMtx_stack_c::YrotM(i_this->m560[i].y);
        mDoMtx_stack_c::XrotM(i_this->m560[i].x);
        mDoMtx_stack_c::ZrotM(i_this->m560[i].z);

        if (i == 0) {
            mDoMtx_stack_c::YrotM(i_this->m468);
            mDoMtx_stack_c::scaleM(l_HIO.m1C, l_HIO.m1C, l_HIO.m1C);
        } else {
            mDoMtx_stack_c::scaleM(i_this->mScale[i], i_this->mScale[i] * i_this->m620[i], 1.0f);
            if (i == 7) {
                mDoMtx_stack_c::scaleM(i_this->m18F0, i_this->m18F0, i_this->m18F0);
            }
        }

        mDoMtx_stack_c::transM(0.0f, 0.0f, i_this->m470);
        model->setBaseTRMtx(mDoMtx_stack_c::get());

        if (i == 0) {
            cXyz offset1(0.0f, 0.0f, REG0_F(9) + 30.0f);
            mDoMtx_stack_c::multVec(&offset1, &i_this->eyePos);
            i_this->mEyeSph.SetC(i_this->eyePos);
            cXyz offset2(0.0f, 0.0f, REG6_F(9) + 100.0f);
            cXyz out;
            mDoMtx_stack_c::multVec(&offset2, &out);
            i_this->mSph[0].SetC(out);

            i_this->mSph[0].OffAtVsBitSet(cCcD_AtSPrm_VsEnemy_e);
            i_this->mSph[0].OnAtVsBitSet(cCcD_AtSPrm_VsOther_e);
            if (i_this->mC04 == 1) {
                i_this->mSph[0].OffAtSetBit();
                i_this->mSph[0].OffCoSetBit();
                i_this->mSph[0].OffTgSetBit();
                i_this->mEyeSph.SetR(40.0f);
            } else {
                if (i_this->mC04 == 2) {
                    i_this->mSph[0].OnAtSetBit();
                } else {
                    i_this->mSph[0].OffAtSetBit();
                }
                i_this->mSph[0].OnCoSetBit();
                i_this->mSph[0].OnTgSetBit();
                i_this->mSph[0].SetR(l_HIO.m40);
                i_this->mEyeSph.SetR(l_HIO.m44);
            }
            dComIfG_Ccsp()->Set(&i_this->mEyeSph);
        } else {
            i_this->mSph[i].SetC(i_this->mPos[i]);
            if (i_this->m460 != 0) {
                i_this->mSph[i].SetR(-200.0f);
            } else {
                i_this->mSph[i].SetR(l_HIO.m48);
            }
        }

        dComIfG_Ccsp()->Set(&i_this->mSph[i]);
        if (i_this->mC01 != 0 && i > 0) {
            u8 uVar3 = i_this->mC00 != 0 ? move_ad2[i] : move_ad[i];
            for (int j = 0; j < 6; j++) {
                u8 uVar2 = uVar3 + j;
                i_this->m6F4[uVar2].x = i_this->mPos[i].x + j * (i_this->mPos[i - 1].x - i_this->mPos[i].x) / 5.0f;
                i_this->m6F4[uVar2].y = i_this->mPos[i].y + j * (i_this->mPos[i - 1].y - i_this->mPos[i].y) / 5.0f;
                i_this->m6F4[uVar2].z = i_this->mPos[i].z + j * (i_this->mPos[i - 1].z - i_this->mPos[i].z) / 5.0f;
                i_this->m9F4[uVar2] = i_this->m560[i];
            }
        }
    }

    if (i_this->mC01 != 0) {
        i_this->mC01 = 0;
        i_this->m454 = 0;
        i_this->m455 = 0;
        i_this->mBF4 = 0;
        i_this->m456[1] = 100;
        i_this->m48E = 0;
        anm_init(i_this, 10, 20.0f, 2, 1.0f, 0);
    }

    cLib_addCalc0(&i_this->m18F4, 1.0f, 0.01f);
    cLib_addCalc2(&i_this->m470, 20.0f, 1.0f, 1.0f);
    cLib_addCalcAngleS2(
        &i_this->current.angle.z,
        (REG0_F(5) + 2000.0f) * cM_ssin(i_this->m46A * (REG0_S(8) + 600)),
        2, 0x400);
}

/* 00001B54-00001E44       .text wall_check_sub__FP8mt_classP4cXyzP4cXyz */
BOOL wall_check_sub(mt_class* i_this, cXyz* start, cXyz* end) {
    dBgS_LinChk linChk;
    linChk.Set(start, end, i_this);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 00001E44-00001F10       .text body_wall_check__FP8mt_class */
void body_wall_check(mt_class* i_this) {
    for (int i = 0; i < 8; i++) {
        cXyz start = i_this->mOld[i];
        start.y += 50.0f;
        cXyz end = i_this->mPos[i];
        end.y += 50.0f;
        if (wall_check_sub(i_this, &start, &end)) {
            i_this->mPos[i].x = i_this->mOld[i].x;
            i_this->mPos[i].z = i_this->mOld[i].z;
        }
    }
}

/* 00001F10-000022D8       .text body_control1__FP8mt_class */
void body_control1(mt_class* i_this) {
    i_this->m6F4[i_this->mBF4] = i_this->current.pos;
    i_this->m9F4[i_this->mBF4] = i_this->shape_angle;
    i_this->mB74[i_this->mBF4] = i_this->m468;
    for (int i = 0; i < 8; i++) {
        u8 uVar2 = i_this->mC00 != 0 ? (i_this->mBF4 + move_ad2[i]) & 0x3F : (i_this->mBF4 + move_ad[i]) & 0x3F;
        J3DModel* model = i_this->mpMorfs[i]->getModel();
        model->setBaseScale(i_this->scale);
        mDoMtx_stack_c::transS(i_this->m6F4[uVar2].x, i_this->m6F4[uVar2].y, i_this->m6F4[uVar2].z);
        mDoMtx_stack_c::YrotM(i_this->m9F4[uVar2].y);
        mDoMtx_stack_c::XrotM(i_this->m9F4[uVar2].x);
        mDoMtx_stack_c::ZrotM(i_this->m9F4[uVar2].z);
        mDoMtx_stack_c::YrotM(i_this->mB74[uVar2]);

        if (i == 0) {
            mDoMtx_stack_c::scaleM(l_HIO.m1C, l_HIO.m1C, l_HIO.m1C);
        } else {
            mDoMtx_stack_c::scaleM(i_this->mScale[i], i_this->mScale[i] * i_this->m620[i], 1.0f);
        }

        mDoMtx_stack_c::transM(0.0f, 0.0f, i_this->m470);
        model->setBaseTRMtx(mDoMtx_stack_c::get());
        if (i == 0) {
            cXyz offset(0.0f, 0.0f, REG0_F(9) + 30.0f);
            cXyz pos;
            mDoMtx_stack_c::multVec(&offset, &pos);
            i_this->mEyeSph.SetC(pos);
            i_this->mEyeSph.SetR(l_HIO.m44);
            dComIfG_Ccsp()->Set(&i_this->mEyeSph);

            cXyz offset2(0.0f, 0.0f, REG6_F(9) + 100.0f);
            mDoMtx_stack_c::multVec(&offset, &pos);
            i_this->mSph[0].SetC(pos);
            i_this->mSph[0].SetR(50.0f);
        } else {
            i_this->mSph[i].SetC(i_this->m6F4[uVar2]);
            if (i_this->m460 != 0) {
                i_this->mSph[i].SetR(-200.0f);
            } else {
                i_this->mSph[i].SetR(l_HIO.m48);
            }
        }
        dComIfG_Ccsp()->Set(&i_this->mSph[i]);
        if (i_this->mC01 != 0) {
            i_this->mPos[i] = i_this->m6F4[uVar2];
            i_this->m560[i] = i_this->m9F4[uVar2];
        }
    }

    if (i_this->m48E == 0) {
        i_this->mBF4++;
    }
    i_this->mBF4 &= 0x3F;

    if (i_this->mC01 != 0) {
        i_this->mC01 = 0;
        i_this->m454 = 1;
        i_this->m455 = 0;
        i_this->m456[0] = l_HIO.m10;
        i_this->m48E = 0;
        anm_init(i_this, 10, 20.0f, 2, 1.0f, 0);
    }

    cLib_addCalc2(&i_this->m470, -10.0f, 1.0f, 1.0f);
}

/* 000022D8-000028BC       .text body_control3__FP8mt_class */
void body_control3(mt_class* i_this) {
    i_this->mPos[0] = i_this->current.pos;
    i_this->m560[0] = i_this->shape_angle;
    s16 sVar13 = 0;
    cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
    cMtx_XrotM(*calc_mtx, i_this->shape_angle.x);
    cMtx_XrotM(*calc_mtx, i_this->shape_angle.z); // bug?
    cXyz offset;
    offset.x = 0.0f;
    offset.y = i_this->m474 * 32.0f;
    offset.z = i_this->m474 * -17.0f;
    cXyz out;
    MtxPosition(&offset, &out);
    s16 sVar6 = 0;
    if (i_this->m18FC != 0) {
        sVar6 = (i_this->m18FC & 2) * 500;
    }

    for (int i = 0; i < 8; i++) {
        if (i > 0) {
            sVar13 -= i_this->m48A + sVar6;
            offset.x = i_this->m330 * cM_ssin(i_this->m466 * (REG0_S(5) + 5000) + i * (REG0_S(6) + 7000));
            offset.y = 0.0f;
            offset.z = -i_this->m478;
            cXyz out;
            cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
            cMtx_XrotM(*calc_mtx, i_this->shape_angle.x + sVar13);
            cMtx_ZrotM(*calc_mtx, i_this->shape_angle.z);
            MtxPosition(&offset, &out);
            f32 fVar1 = out.x + i_this->mPos[i].x - i_this->mPos[i - 1].x;
            f32 fVar2 = out.y + i_this->mPos[i].y - i_this->mPos[i - 1].y;
            f32 fVar3 = out.z + i_this->mPos[i].z - i_this->mPos[i - 1].z;
            s16 sVar10 = cM_atan2s(fVar1, fVar3);
            fVar1 = std::sqrtf(fVar1 * fVar1 + fVar3 * fVar3);
            s16 sVar4 = -cM_atan2s(fVar2, fVar1);
            cXyz offset2(0.0f, 0.0f, REG0_F(7) + 35.0f);
            cMtx_YrotS(*calc_mtx, sVar10);
            cMtx_XrotM(*calc_mtx, sVar4);
            MtxPosition(&offset2, &out);
            s16 sVar7 = sVar10 - i_this->shape_angle.y;
            uint uVar5 = sVar7 < 0 ? -sVar7 : sVar7;
            if (uVar5 < 0x4000) {
                i_this->m560[i].y = sVar10;
                i_this->m560[i].x = -(sVar4 - 0x8000);
            } else {
                i_this->m560[i].y = sVar10 - 0x8000;
                i_this->m560[i].x = sVar4;
            }
            i_this->mOld[i] = i_this->mPos[i];
            i_this->mPos[i].x = i_this->mPos[i - 1].x + out.x;
            i_this->mPos[i].y = i_this->mPos[i - 1].y + out.y;
            i_this->mPos[i].z = i_this->mPos[i - 1].z + out.z;
        }

        J3DModel* model = i_this->mpMorfs[i]->getModel();
        model->setBaseScale(i_this->scale);
        mDoMtx_stack_c::transS(i_this->mPos[i] + out);
        mDoMtx_stack_c::YrotM(i_this->m560[i].y);
        mDoMtx_stack_c::XrotM(i_this->m560[i].x);
        mDoMtx_stack_c::ZrotM(i_this->m560[i].z);

        if (i == 0) {
            mDoMtx_stack_c::scaleM(l_HIO.m20, l_HIO.m20, l_HIO.m20);
        } else {
            mDoMtx_stack_c::scaleM(i_this->mScale[i], i_this->mScale[i] * i_this->m620[i], 1.0f);
            if (i == 7) {
                mDoMtx_stack_c::scaleM(i_this->m18F0, i_this->m18F0, i_this->m18F0);
            }
        }

        mDoMtx_stack_c::transM(0.0f, 0.0f, i_this->m470);
        model->setBaseTRMtx(mDoMtx_stack_c::get());
        if (i == 0) {
            i_this->eyePos = i_this->current.pos;
            i_this->mSph[0].SetC(i_this->eyePos);
            i_this->mSph[0].OnAtSetBit();
            i_this->mEyeSph.SetR(-30.0f);
            if (std::fabsf(i_this->speedF) > 2.0f) {
                i_this->mSph[0].OnAtSPrmBit(cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e);
            } else {
                i_this->mSph[0].OffAtSPrmBit(cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e);
            }
            if (i_this->m466 < 90) {
                i_this->mSph[0].OnAtVsPlayerBit();
                i_this->mSph[0].SetR(60.0f);
            } else {
                i_this->mSph[0].OffAtVsPlayerBit();
                i_this->mSph[0].SetR(40.0f);
            }
            dComIfG_Ccsp()->Set(&i_this->mSph[0]);
        }
    }

    cLib_addCalc0(&i_this->m18F4, 1.0f, 0.01f);
    cLib_addCalc2(&i_this->m470, 20.0f, 1.0f, 1.0f);
    cLib_addCalcAngleS2(&i_this->current.angle.z, 0, 2, 0x400);
}

/* 000028BC-00002AB0       .text body_control4__FP8mt_class */
void body_control4(mt_class* i_this) {
    /* Nonmatching */
}

/* 00002AB0-00003008       .text body_control5__FP8mt_class */
void body_control5(mt_class*) {
    /* Nonmatching */
}

/* 00003008-00003210       .text br_draw__FP8mt_class */
void br_draw(mt_class*) {
    /* Nonmatching */
}

/* 00003210-00003360       .text daMt_shadowDraw__FP8mt_class */
static void daMt_shadowDraw(mt_class*) {
    /* Nonmatching */
}

/* 00003360-0000361C       .text daMt_Draw__FP8mt_class */
static BOOL daMt_Draw(mt_class* i_this) {
    cXyz local_3c(0.0f, 0.0f, 0.0f);
    if (i_this->m2BB != 0) {
        return TRUE;
    }

    j_index = 0;
    for (int i = 0; i < 8; i++) {
        J3DModel* model = i_this->mpMorfs[i]->getModel();
        if (i_this->mEnemyIce.mLightShrinkTimer == 0) {
            cXyz cStack_48;
            MTXMultVec(model->getBaseTRMtx(), &local_3c, &cStack_48);
            g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &cStack_48, &i_this->tevStr);
        } else {
            i_this->scale.set(i_this->mEnemyIce.mScaleXZ, i_this->mEnemyIce.mScaleXZ, i_this->mEnemyIce.mScaleXZ);
            model->setBaseScale(i_this->scale);
        }
        g_env_light.setLightTevColorType(model, &i_this->tevStr);
        i_this->btk[i]->entry(model->getModelData());
        i_this->brk[i]->entry(model->getModelData());
        if (i_this->m2E4 == 0) {
            int iVar3 = i_this->m2E8 + i * l_HIO.m50;
            if (iVar3 < 0) {
                iVar3 = 0x28U - iVar3;
            }
            iVar3 %= 0x29U;
            i_this->brk[i]->setFrame(iVar3);
            iVar3 = i_this->m2EC + i * l_HIO.m50;
            if (iVar3 < 0) {
                iVar3 = 0x1EU - iVar3;
            }
            iVar3 %= 0x1F;
            i_this->btk[i]->setFrame(iVar3);
        } else {
            i_this->brk[i]->setFrame(i_this->m2E8);
            i_this->btk[i]->setFrame(i_this->m2EC);
        }

        if (i == 0) {
            model->getModelData()->getMaterialTable().setTexNoAnimator(i_this->m33C, i_this->m340);
            i_this->m33C->setFrame(i_this->m344);
        }
        i_this->mpMorfs[i]->updateDL();
    }
    
    br_draw(i_this);
    daMt_shadowDraw(i_this);
    dSnap_RegistFig(DSNAP_TYPE_MT, i_this, 1.0f, 1.0f, 1.0f);

    return TRUE;
}

/* 0000361C-000037B0       .text bakuha__FP8mt_class */
void bakuha(mt_class*) {
    /* Nonmatching */
}

static f32 check_x[6] = {0.0f, 0.0f, 50.0f, -50.0f, -1.0f, 1.0f};
static f32 check_y[6] = {-50.0f, -50.0f, -150.0f, -150.0f, 100.0f, 100.0f};
static f32 check_z[6] = {150.0f, -10.0f, 0.0f, 0.0f, 200.0f, 200.0f};
static u8 check_bitD[6] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20};

/* 000037B0-000042C4       .text mt_move__FP8mt_class */
void mt_move(mt_class* i_this) {
    u8 bVar8;
    cXyz local_160[6];
    cXyz ends[6];
    dBgS_LinChk linChk;
    cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    cMtx_ZrotM(*calc_mtx, i_this->current.angle.z);
    cXyz offset(0.0f, 50.0f, 0.0f);
    cXyz local_184;
    MtxPosition(&offset, &local_184);
    local_184 = local_184 + i_this->current.pos;
    int iVar6 = abs(i_this->current.angle.x);
    int iVar11 = iVar6 < 0x1000 ? 6 : 4;
    for (int i = 0; i < iVar11; i++) {
        cXyz check;
        check.x = check_x[i];
        check.y = check_y[i];
        check.z = check_z[i];
        MtxPosition(&check, &ends[i]);
        ends[i] += i_this->current.pos;
        linChk.Set(&local_184, &ends[i], i_this);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            local_160[i] = linChk.GetCross();
            bVar8 |= check_bitD[i];
        }
    }

    if ((bVar8 & 0x3) == 0x3) {
        cXyz local_190 = local_160[0] - local_160[1];
        cXyz local_16C(0.0f, l_HIO.m18, 0.0f);
        cXyz local_178;
        MtxPosition(&local_16C, &local_178);
        if (i_this->m48E == 0) {
            cLib_addCalc2(&i_this->current.pos.x, local_178.x + local_160[1].x + local_190.x * 0.5f, 1.0f, 1.0f);
            cLib_addCalc2(&i_this->current.pos.y, local_178.y + local_160[1].y + local_190.y * 0.5f, 1.0f, 1.0f);
            cLib_addCalc2(&i_this->current.pos.z, local_178.z + local_160[1].z + local_190.z * 0.5f, 1.0f, 1.0f);
        }
        f32 fVar1 = std::sqrtf(local_190.x * local_190.x + local_190.z * local_190.z);
        i_this->current.angle.x = -cM_atan2s(local_190.y, fVar1);
        if (std::fabsf(local_190.x) > 0.1f || std::fabsf(local_190.z) > 0.1f) {
            i_this->m48C = cM_atan2s(local_190.x, local_190.z);
        }
        s16 sVar5 = i_this->m48C - i_this->current.angle.y;
        uint uVar4 = (sVar5 < 0) ? -sVar5 : sVar5;
        if (uVar4 > 0x4000) {
            i_this->current.angle.x = 0x8000 - i_this->current.angle.x;
        }
        i_this->m492 = 23;
    } else if ((bVar8 & 0x1) == 0) {
        if (i_this->m492 == 0) {
            i_this->current.angle.x += REG0_S(2) + 0x800;
        } else {
            i_this->m492--;
        }
    }

    if ((bVar8 & 0xC) == 0xC) {
        cXyz local_190 = local_160[2] - local_160[3];
        cMtx_XrotS(*calc_mtx, -i_this->current.angle.x);
        cMtx_YrotM(*calc_mtx, -i_this->current.angle.y);
        cXyz local_178;
        MtxPosition(&local_190, &local_178);
        f32 fVar1 = std::sqrtf(local_178.x * local_178.x + local_178.z * local_178.z);
        i_this->current.angle.z = cM_atan2s(local_178.x, fVar1);
    }

    if (abs(i_this->current.angle.x) < 0x1000) {
        if ((bVar8 & 0x30) == 0x30) {
            cXyz local_190 = local_160[4] - local_160[5];
            i_this->current.angle.y = cM_atan2s(local_190.x, local_190.z) + 0x4000;
        } else {
            if (i_this->m2B4 >= 10) {
                i_this->current.angle.y += i_this->m488;
            } else {
                s16 target_angle;
                if (i_this->m2BC != 0) {
                    cXyz local_190 = i_this->m47C - i_this->current.pos;
                    target_angle = cM_atan2s(local_190.x, local_190.z);
                    i_this->m488 = 0x800;
                    if (std::sqrtf(local_190.x * local_190.x + local_190.z * local_190.z) < 100.0f) {
                        i_this->m2BD += i_this->m2BE;
                        if (i_this->m2BD >= i_this->mpPath->m_num) {
                            if (dPath_ChkClose(i_this->mpPath)) {
                                i_this->m2BD = 0;
                            } else {
                                i_this->m2BE = -1;
                                i_this->m2BD = i_this->mpPath->m_num - 2;
                            } 
                        } else if (i_this->m2BD < 0) {
                            i_this->m2BE = 1;
                            i_this->m2BD = 1;
                        }
                        i_this->m47C = i_this->mpPath->m_points[i_this->m2BD].m_position;
                    }
                } else {
                    target_angle = fopAcM_searchPlayerAngleY(i_this);
                    cLib_addCalcAngleS2(&i_this->m488, REG0_S(4) + 0x400, 1, 0x10);
                }
                 
                if (i_this->m2B5 == 1) {
                    i_this->current.angle.y = target_angle;
                } else {
                    cLib_addCalcAngleS2(&i_this->current.angle.y, target_angle, 0x10, i_this->m488);
                }
            } 

            if (i_this->m2B4 < 10 && i_this->m18F9 == 0 && fopAcM_searchPlayerDistance(i_this) < l_HIO.m24) {
                bool bVar3 = false;
                for (int i = 0; i < 64; i += 8) {
                    if (abs(i_this->m9F4[i].x) > 0x1000) {
                        bVar3 = true;
                        break;
                    }
                }
                if (!bVar3) {
                    i_this->mC01 = 1;
                }
            }
        }
    } else if (i_this->m2B4 < 10) {
        i_this->m488 = 0;
    }

    if (i_this->m48E == 0) {
        cLib_addCalcAngleS2(
            &i_this->m468,
            cM_ssin(i_this->m46A * (REG0_S(0) + 2000)) * (cM_ssin(i_this->m46A * 100) * 1000.0f + 3500.0f),
            4, 0x400
        );
        float fVar2 = i_this->mC00 != 0 ? 10.0f : 5.0f;
        cLib_addCalc2(&i_this->speedF, fVar2, 1.0f, fVar2);
    } else {
        cLib_addCalc0(&i_this->speedF, 1.0f, 5.0f);
    }

    cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    cMtx_YrotM(*calc_mtx, i_this->m468);
    cXyz local_16C(0.0f, 0.0f, i_this->speedF);
    MtxPosition(&local_16C, &i_this->speed);
    fopAcM_posMove(i_this, NULL);
    if (bVar8 == 0) {
        i_this->m46C++;
        if (i_this->m46C > 9) {
            i_this->m454 = 1;
            i_this->m455 = 0x11;
        }
    } else {
        i_this->m46C = 0;
    }
}

/* 000042C4-00005088       .text mt_fight__FP8mt_class */
void mt_fight(mt_class* i_this) {
    float fVar1;
    float fVar2;
    short sVar9;
    f32 fVar11;
    cXyz local_80;
    short local_74[6];
    cXyz local_68;
    cXyz local_5c;
    u64 local_50;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    switch (i_this->m455) {
        case 0:
            mt_check(i_this);
            if (mt_fight_count < 2) {
                local_74[0] = 0;
                local_74[1] = 0;
                local_74[2] = 0;
                local_74[3] = 0;
                local_74[4] = 0;
            } else if (mt_fight_count == 2) {
                local_74[0] = 0x2000;
                local_74[1] = 0x2000;
                local_74[2] = 0;
                local_74[3] = 0;
                local_74[4] = 0;
            } else if (mt_fight_count == 3) {
                local_74[0] = 0;
                local_74[1] = 0xD000;
                local_74[2] = 0x3000;
                local_74[3] = 0;
                local_74[4] = 0;
            } else if (mt_fight_count == 4) {
                local_74[0] = 0x2000;
                local_74[1] = 0xE000;
                local_74[2] = 0x5000;
                local_74[3] = 0xB000;
                local_74[4] = 0;
            } else {
                local_74[0] = 0;
                local_74[1] = 0x3000;
                local_74[2] = 0xD000;
                local_74[3] = 0x6000;
                local_74[4] = 0xA000;
            }

            if (dComIfGp_getAttention().Lockon() && i_this == dComIfGp_getAttention().LockonTarget(0)) {
                mt_count = 0;
            } else {
                mt_count++;
            }
            if (mt_count >= 5) {
                mt_count -= 5;
            }

            local_80 = player->current.pos - i_this->current.pos;
            local_68.x = local_80.x;
            local_68.y = local_80.y + REG6_F(5) + 90.0f;
            local_68.z = local_80.z;
            i_this->m496 = cM_atan2s(local_68.x, local_68.z);
            fVar11 = std::sqrtf(local_68.x * local_68.x + local_68.z * local_68.z);
            i_this->m494 = -cM_atan2s(local_68.y, fVar11);

            local_5c.x = (REG0_F(10) + 30.0f) * cM_ssin(i_this->m46A * 500);
            local_5c.y = (REG0_F(11) + 20.0f) * cM_scos(i_this->m46A * 1400) + 60.0f;
            local_5c.z = l_HIO.m28 + (REG0_F(12) + 30.0f) * cM_scos(i_this->m46A * 600);

            sVar9 = (REG0_F(16) - 2000.0f) * cM_ssin(i_this->m46A * 1400);

            cMtx_YrotS(*calc_mtx, player->shape_angle.y + local_74[mt_count]);
            MtxPosition(&local_5c, &local_68);
            cLib_addCalc2(&i_this->current.pos.x, player->current.pos.x + local_68.x, 0.1f, REG0_F(10) + 4.0f);
            cLib_addCalc2(&i_this->current.pos.z, player->current.pos.z + local_68.z, 0.1f, REG0_F(10) + 4.0f);
            if (fopAcM_searchPlayerDistance(i_this) < l_HIO.m24 + 100.0f || (i_this->m18F9 != 0 && i_this->m466 == 0)) {
                cLib_addCalc2(&i_this->current.pos.y, i_this->mAcch.GetGroundH() + 40.0f, 0.5f, 3.0f);
                sVar9 = 0;
                i_this->m494 = 0;
                if (std::fabsf(i_this->current.pos.y - i_this->mAcch.GetGroundH() + 40.0f) < 2.0f) {
                    i_this->mC01 = 1;
                }
            } else {
                cLib_addCalc2(&i_this->current.pos.y, local_68.y + l_HIO.m18 + i_this->mAcch.GetGroundH(), 0.1f, 5.0f);
                if (i_this->m456[0] == 0) {
                    i_this->m456[0] = l_HIO.m10;
                    if (cM_rndF(1.0f) < l_HIO.m14 && i_this->m466 == 0) {
                        i_this->m455 = 1;
                        i_this->mC02 = 0;
                        cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
                        local_5c.x = 0.0f;
                        local_5c.y = 30.0f;
                        local_5c.z = -30.0f;
                        MtxPosition(&local_5c, &i_this->m47C);
                        i_this->m47C += i_this->current.pos;
                        anm_init(i_this, 8, 0.0f, 2, 0.0f, 0);
                        fopAcM_monsSeStart(i_this, JA_SE_CV_MG_ATTACK, 0);
                    }
                }
            }
            break;
        case 1:
            if (player->getCutType() == 0x10) {
                if (dComIfGp_getAttention().Lockon() && i_this == dComIfGp_getAttention().LockonTarget(0)) {
                    i_this->m454 = 6;
                    i_this->m456[0] = 0;
                    anm_init(i_this, 7, 0.0f, 0, 0.0f, 0);
                    break;
                }
            }
            i_this->mC02++;
            if (l_HIO.m30 <= i_this->mC02 && i_this->mC02 <= l_HIO.m32) {
                i_this->setBtAttackData(0.0f, 20.0f, 10000.0f, fopEn_enemy_c::OPENING_VERTICAL_JUMP_PARRY);
                i_this->setBtMaxDis(l_HIO.m34);
                i_this->setBtNowFrame(10.0f);
            }
            if (i_this->mC02 == l_HIO.m3C) {
                anm_init(i_this, 9, 0.0f, 0, 0.0f, 0);
            }
            if (i_this->mC02 == l_HIO.m38) {
                cMtx_YrotS(*calc_mtx, i_this->m496);
                cMtx_XrotM(*calc_mtx, i_this->m494);
                local_5c.x = 0.0f;
                local_5c.y = REG6_F(6) - 100.0f;
                local_5c.z = REG6_F(7) + 200.0f;
                MtxPosition(&local_5c, &i_this->m47C);
                i_this->m47C += i_this->current.pos;
            }
            fVar11 = l_HIO.m2C;
            if (i_this->mC02 < l_HIO.m38) {
                fVar11 = REG0_F(11) + 4.0f;
                fVar1 = 0.1f;
            } else {
                fVar1 = 0.5f;
                if (i_this->mC02 == l_HIO.m3E) {
                    anm_init(i_this, 7, 0.0f, 0, 0.0f, 0);
                }
            }

            if (i_this->mC02 == l_HIO.m3E + REG0_S(3)) {
                fopAcM_monsSeStart(i_this, JA_SE_CM_MAGTAIL_ATTACK, 0);
            }
            if (i_this->mC02 < l_HIO.m3E + 3 + REG6_S(7)) {
                i_this->mC04 = 1;
            }
            if (i_this->mC02 == l_HIO.m3E + 2) {
                i_this->m18D4 = 1;
            }
            if (l_HIO.m3E + 2 <= i_this->mC02 && i_this->mC02 <= l_HIO.m3E + 15) {
                i_this->mC04 = 2;
            }

            cLib_addCalc2(&i_this->current.pos.x, i_this->m47C.x, fVar1, fVar11);
            cLib_addCalc2(&i_this->current.pos.y, i_this->m47C.y + 20.0f, fVar1, fVar11);
            cLib_addCalc2(&i_this->current.pos.z, i_this->m47C.z, fVar1, fVar11);

            i_this->speed.x = i_this->m47C.x - i_this->current.pos.x;
            i_this->speed.y = -1.0f;
            i_this->speed.z = i_this->m47C.z - i_this->current.pos.z;

            if (player->checkPlayerGuard() && i_this->mSph[0].ChkAtHit()) {
                i_this->m455 = 15;
                cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
                local_5c.x = 0.0f;
                local_5c.y = 80.0f;
                local_5c.z = -120.0f;
                MtxPosition(&local_5c, &i_this->m47C);
                i_this->m47C += i_this->current.pos;
                i_this->m462 = 10;
                i_this->m456[0] = 10;
                anm_init(i_this, 10, 0.0f, 2, 0.0f, 0);
                i_this->m18D4 = 0;
            }
            if (i_this->mC02 == l_HIO.m3A) {
                i_this->m455 = 0;
                i_this->m456[0] = l_HIO.m10;
                anm_init(i_this, 10, 0.0f, 2, 0.0f, 0);
            }
            break;
        case 0xA:
            i_this->current.pos.y += i_this->speed.y;
            i_this->speed.y += i_this->gravity;
            if (i_this->speed.y < -100.0f) {
                i_this->speed.y = -100.0f;
            }
            if (i_this->mAcch.ChkGroundHit()) {
                i_this->m455 = 0;
            }
            break;
        case 0xF:
            cLib_addCalc2(&i_this->current.pos.x, i_this->m47C.x, 0.4f, 20.0f);
            cLib_addCalc2(&i_this->current.pos.y, i_this->m47C.y + 20.0f, 0.4f, 20.0f);
            cLib_addCalc2(&i_this->current.pos.z, i_this->m47C.z, 0.4f, 20.0f);
            i_this->speed.x = i_this->m47C.x - i_this->current.pos.x;
            i_this->speed.y = -1.0f;
            i_this->speed.z = i_this->m47C.z - i_this->current.pos.z;
            if (i_this->m456[0] == 0) {
                i_this->m455 = 0;
                i_this->m456[0] = l_HIO.m10;
                anm_init(i_this, 10, 0.0f, 2, 0.0f, 0);
            }
            break;
        case 0x11:
            if (i_this->mAcch.ChkGroundHit()) {
                i_this->m455 = 0x17;
                i_this->m456[0] = cM_rndF(50.0f) + 50.0f;
                i_this->m48E = i_this->m456[0];
            }
            // TODO - GOTO
            break;
        case 0x14:
            i_this->current.angle.x -= 0x500;
            cLib_addCalcAngleS2(&i_this->current.angle.y, cM_atan2s(i_this->speed.x, i_this->speed.z) - 0x8000, 2, 0x400);
            cLib_addCalc2(&i_this->m18F4, 0.9f, 1.0f, 0.1f);
            if (i_this->speed.y <= 1.0f) {
                if (i_this->m18F8 == 0) {
                    i_this->mSph[0].OffTgShield();
                    tex_anm_set(i_this, 1);
                    i_this->m454 = 2;
                    i_this->m466 = l_HIO.m54;
                    i_this->m478 = 0.0f;
                    i_this->m48A = 0;
                    i_this->m330 = 0.0f;
                    fVar11 = i_this->speed.z;
                    fVar1 = i_this->speed.x;
                    fVar2 = i_this->speed.y;
                    fVar11 = std::sqrtf(fVar1 * fVar1 + fVar11 * fVar11 + fVar2 * fVar2);
                    i_this->speedF = -fVar11;
                    i_this->m455 = 0;
                    fopAcM_SetMin(i_this, -100.0f, -100.0f, -100.0f);
                    fopAcM_SetMax(i_this, 100.0f, 100.0f, 100.0f);
                } else if (i_this->mAcch.ChkGroundHit()) {
                    i_this->m18F8 = 2;
                }
            }
            // TODO - GOTO
            break;
        case 0x17:
            i_this->speed.y = 0.0f;
            cLib_addCalcAngleS2(&i_this->current.angle.x, 0, 1, 0x400);
            i_this->speed.x *= 0.2f;
            i_this->speed.z *= 0.2f;
            if (i_this->m456[0] == 0) {
                i_this->m455 = 10;
            }
            break;
    }

    if (i_this->m454 < 2) {
        if (i_this->m455 < 10) {
            cLib_addCalcAngleS2(&i_this->current.angle.y, i_this->m496, 2, 0x400);
            local_68.y = i_this->current.pos.y - i_this->mAcch.GetGroundH();
            if (local_68.y > 250.0f) {
                i_this->m455 = 10;
            }
            cLib_addCalcAngleS2(&i_this->current.angle.x, i_this->m494 + sVar9, 4, 0x800);
        }
        cLib_addCalcAngleS2(&i_this->m468, 0, 1, 0x100);
    }
}

/* 00005088-00005A04       .text mt_move_maru__FP8mt_class */
void mt_move_maru(mt_class* i_this) {
    i_this->m464 = 3;
    if (i_this->m455 == 0) {
        if (i_this->m456[0] == 0) {
            i_this->mSph[0].OnCoSetBit();
        }
        i_this->shape_angle.x += i_this->speedF * 200.0f;
        cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
        cXyz offset(0.0f, 0.0f, i_this->speedF);
        cXyz out;
        MtxPosition(&offset, &out);
        i_this->speed.x = out.x;
        i_this->speed.z = out.z;
        i_this->current.pos.x += i_this->speed.x;
        i_this->current.pos.y += i_this->speed.y;
        i_this->current.pos.z += i_this->speed.z;
        i_this->speed.y += i_this->gravity;
        if (i_this->speed.y < -100.0f) {
            i_this->speed.y = -100.0f;
        }
        f32 fVar1 = i_this->speed.y;
        mt_bg_check(i_this);
        u8 uVar7;
        if (i_this->mAcch.ChkGroundHit()) {
            if (fVar1 < REG0_F(12) + -50.0f) {
                i_this->m18F8 = 2;
            }

            f32 target = 0.0f;
            f32 fVar2 = 1.0f;

            dBgS_GndChk gndChk;

            cXyz local_f0 = i_this->current.pos;
            local_f0.y += 50.0f;
            gndChk.SetPos(&local_f0);
            f32 fVar9 = dComIfG_Bgsp()->GroundCross(&gndChk);
            cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
            cXyz local_d8(0.0f, 50.0f, 5.0f);
            cXyz out;
            MtxPosition(&local_d8, &out);
            cXyz local_fc = i_this->current.pos + out;
            gndChk.SetPos(&local_fc);
            local_fc.y = dComIfG_Bgsp()->GroundCross(&gndChk);

            if (local_fc.y != C_BG_MIN_HEIGHT) {
                if (local_fc.y < fVar9 - 1.0f) {
                    target = 5.0f;
                    fVar2 = 0.3f;
                } else if (local_fc.y > fVar9 + 1.0f) {
                    target = -5.0f;
                    fVar2 = 0.3f;
                }
            }

            cLib_addCalc2(&i_this->speedF, target, 1.0f, l_HIO.m5C * fVar2);
            if (fVar1 < REG0_F(14) - 15.0f) {
                i_this->speed.y = fVar1 * (REG0_F(15) - 0.4f);
                uVar7 = i_this->speed.y * (REG0_F(5) + 6.0f);
                if (uVar7 > 100) {
                    uVar7 = 100;
                }
            } else {
                i_this->speed.y = -5.0f;
            }
        }

        if (i_this->mAcch.ChkWallHit() && std::abs(i_this->speedF) > 3.0f) {
            i_this->speedF *= -0.5f;
            uVar7 = 50;
        }
        if (uVar7 != 0) {
            fopAcM_seStart(i_this, JA_SE_CM_MAGBALL_BOUND, uVar7);
        }
        cLib_onBit<u32>(i_this->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        i_this->attention_info.distances[fopAc_Attn_TYPE_CARRY_e] = 9;
        if (fopAcM_checkCarryNow(i_this)) {
            cLib_offBit<u32>(i_this->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
            i_this->m455 = 1;
        }
    } else if (i_this->m455 == 1) {
        i_this->mSph[0].OffCoSetBit();
        i_this->current.angle.x = 0;
        i_this->current.angle.y = i_this->shape_angle.y;
        i_this->current.angle.z = i_this->shape_angle.z;
        if (!fopAcM_checkCarryNow(i_this)) {
            if (fopAcM_GetSpeedF(i_this) > 0) {
                i_this->m455 = 0;
                i_this->speedF = l_HIO.m58 * 20.0f;
                i_this->speed.y = l_HIO.m58 * 20.0f;
                i_this->m456[0] = 20;
            } else {
                i_this->m455 = 0;
                i_this->speedF = 0.0f;
                i_this->speed.y = REG0_F(11) + -15.0f;
                i_this->m456[0] = 20;
            }
        } else if (dComIfGp_event_runCheck()) {
            i_this->m466++;
        }
    }

    cLib_addCalcAngleS2(&i_this->m468, 0, 1, 0x100);
    if (i_this->m466 > 70) {
        cLib_addCalc2(&i_this->m474, 1.0f, 1.0f, 0.05f);
        s16 target = l_HIO.m52;
        if (i_this->m466 < 110) {
            if (i_this->m466 > 100 || i_this->m466 < 80) {
                target = l_HIO.m52 - 0x5DC;
            }
            cLib_addCalcAngleS2(&i_this->shape_angle.x, 0x7800, 4, 0x300);
        }
        cLib_addCalcAngleS2(&i_this->m48A, target, 4, 0x1000);
        cLib_addCalc2(&i_this->m478, 1000.0f, 1.0f, 5.0f);
        cLib_addCalc2(&i_this->m338, 0.3f, 1.0f, 0.01f);
    } else {
        if (i_this->m466 == 70) {
            i_this->m330 = REG0_F(3) + 2500.0f;
            i_this->m338 = 0.5f;
            if (i_this->m18FA == 0) {
                i_this->speed.y = REG0_F(11) + 30.0f;
            }
        }
        cLib_addCalc0(&i_this->m330, 1.0f, 125.0f);
        cLib_addCalcAngleS2(&i_this->m468, i_this->m330 * cM_ssin(i_this->m466 * (REG0_S(5) + 5000)) * 5.0f, 2, 0x1000);
        cLib_addCalc2(&i_this->m474, -0.4f, 1.0f, 0.2f);
        cLib_addCalcAngleS2(&i_this->m48A, (REG0_F(14) + 4.0f) * i_this->m330 * cM_ssin(i_this->m466 * (REG0_S(5) + 5000)), 1, 0x1000);
        i_this->current.angle.x = i_this->shape_angle.x;
        i_this->shape_angle.y = i_this->current.angle.y + i_this->m468;
        cLib_addCalc0(&i_this->speedF, 1.0f, 0.5f);
    }

    if (i_this->m466 == 100) {
        i_this->m2E4 = 2;
    }
    if (i_this->m348 != 0) {
        if (i_this->m348 == 1) {
            i_this->m450 = dComIfGp_particle_setToon(
                dPa_name::ID_SCENE_8095,
                &i_this->current.pos, &i_this->current.angle,
                NULL, 0xB4);
            if (i_this->m450 != NULL) {
                i_this->m450->becomeImmortalEmitter();
            }
            i_this->m348 = 2;
            i_this->m34A = 80;
        }

        if (i_this->m450 != NULL) {
            MtxTrans(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z, false);
            cMtx_YrotM(*calc_mtx, i_this->shape_angle.y);
            i_this->m450->setGlobalRTMatrix(*calc_mtx);
            if (i_this->m34A == 0) {
                i_this->m450->quitImmortalEmitter();
                i_this->m450->setMaxFrame(-1);
                i_this->m450->becomeInvalidEmitter();
                i_this->m450 = NULL;
                i_this->m348 = 0;
            } else {
                i_this->m450->setGlobalAlpha(i_this->m34A < 30 ? i_this->m34A * 6 : 180);
            }
        }
    }
}

/* 00005B9C-00005C54       .text water_damage_se_set__FP8mt_class */
void water_damage_se_set(mt_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    fopAcM_seStart(a_this, JA_SE_CM_MAGTAIL_WATER, 0);
    fopAcM_monsSeStart(a_this, JA_SE_CV_MG_WATER, 0);
    i_this->m348 = 1;
}

/* 00005C54-0000614C       .text damage_check__FP8mt_class */
void damage_check(mt_class* i_this) {
    CcAtInfo atInfo;
    u8 iVar4 = 0;
    int i = 0;
    i_this->mStts.Move();
    if (i_this->mC04 == 1) {
        i = 2;
    }
    while (i < 8) {
        if (i_this->mSph[i].ChkTgHit() && i_this->m460 == 0) {
            atInfo.mpObj = i_this->mSph[i].GetTgHitObj();
            if (atInfo.mpObj->ChkAtType(AT_TYPE_LIGHT_ARROW)) {
                i_this->m1CBC = 1;
                i_this->mEnemyIce.mLightShrinkTimer = 1;
                i_this->mEnemyIce.mYOffset = REG0_F(0) + -20.0f;
                i_this->health = 0;
                return;
            }
            at_power_check(&atInfo);
            if (atInfo.mResultingAttackType == 4 || atInfo.mpObj->ChkAtType(AT_TYPE_ICE_ARROW)) {
                iVar4 = 2;
                i_this->m18FB = 0;
                i_this->m460 = 5;
                water_damage_se_set(i_this);
            } else {
                if (i_this->m454 == 2 && (atInfo.mResultingAttackType == 6 || atInfo.mResultingAttackType == 2)) {
                    if (atInfo.mResultingAttackType == 2) {
                        i_this->m18F8 = 3;
                    } else {
                        i_this->m18F8 = 2;
                    }
                    i_this->m460 = 5;
                    return;
                }
                if (atInfo.mResultingAttackType == 2) {
                    iVar4 = 1;
                    i_this->m460 = 5;
                } else {
                    if (atInfo.mResultingAttackType != 6 && i_this->m454 == 1) {
                        i_this->m455 = 0xf;
                        cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
                        cXyz pos(0.0f, 60.0f, -120.0f);
                        MtxPosition(&pos, &i_this->m47C);
                        i_this->m47C += i_this->current.pos;
                        i_this->m462 = REG6_S(7) + 6;
                        i_this->m456[0] = REG6_S(8) + 6;
                        i_this->m460 = 5;
                        def_se_set(i_this, atInfo.mpObj, 0x40);
                        return;
                    }
                    if (i_this->m454 == 2) {
                        i_this->m460 = 5;
                        cc_at_check(i_this, &atInfo);
                        if (i_this->health <= 0) {
                            i_this->m18F8 = 2;
                        }
                        i_this->m18FC = 12;
                        // dScnPly_ply_c::setPauseTimer(REG0_S(7) + 6);
                        dComIfGp_particle_set(dPa_name::ID_SCENE_80CF, &i_this->current.pos);
                    }
                }
            }
            break;
        }
        i++;
    }
    if (i_this->m460 == 0 && i_this->mEyeSph.ChkTgHit()) {
        i_this->m460 = 5;
        atInfo.mpObj = i_this->mEyeSph.GetTgHitObj();
        atInfo.pParticlePos = i_this->mEyeSph.GetTgHitPosP();
        if (atInfo.mpObj->ChkAtType(AT_TYPE_LIGHT_ARROW)) {
            i_this->mEnemyIce.mLightShrinkTimer = 1;
            return;
        }
        at_power_check(&atInfo);
        i_this->m18FB -= atInfo.mDamage;
        if (atInfo.mResultingAttackType != 6 &&
            atInfo.mResultingAttackType != 3 &&
            atInfo.mResultingAttackType != 4 &&
            atInfo.mResultingAttackType != 2 && 
            i_this->mC04 != 1
        ) {
            return;
        }
        atInfo.mpActor = cc_at_check(i_this, &atInfo);
        if (atInfo.mResultingAttackType == 6) {
            i_this->m18F8 = 1;
            i_this->m18FB = 0;
        } else if (atInfo.mResultingAttackType == 4 || atInfo.mpObj->ChkAtType(AT_TYPE_ICE_ARROW)) {
            iVar4 = 2;
            i_this->m18FB = 0;
            water_damage_se_set(i_this);
        }
        if (i_this->m18FB <= 0) {
            iVar4 = 1;
        } else {
            i_this->m455 = 0xf;
            cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
            cXyz pos(0.0f, 60.0f, -120.0f);
            MtxPosition(&pos, &i_this->m47C);
            i_this->m47C += i_this->current.pos;
            i_this->m462 = 25;
            i_this->m456[0] = 10;
            i_this->current.angle.x = -0x4000;
        }
        fopAcM_monsSeStart(i_this, JA_SE_CV_MG_DAMAGE, 0);
        anm_init(i_this, 10, 2.0f, 2, 1.0f, 0);
        i_this->m18D4 = 0;
    }
    if (iVar4 != 0) {
        cMtx_YrotS(*calc_mtx, atInfo.m0C.y);
        cXyz pos(0.0f, l_HIO.m4C * 40.0f, l_HIO.m4C * -20.0f);
        MtxPosition(&pos, &i_this->speed);
        if (iVar4 == 2) {
            i_this->speed.y = 0.0f;
        }
        i_this->m454 = 1;
        i_this->m455 = 0x14;
        i_this->m2E4 = 1;
    }
}

/* 00006188-000074D4       .text daMt_Execute__FP8mt_class */
static BOOL daMt_Execute(mt_class* i_this) {
    /* Nonmatching */
    CcAtInfo atInfo;

    daPy_py_c* player = daPy_getPlayerActorClass();

    if (enemy_ice(&i_this->mEnemyIce)) {
        return TRUE;
    }

    if (i_this->m2BB != 0) {
        if (!dComIfGs_isSwitch(i_this->m2BB, fopAcM_GetRoomNo(i_this))) {
            return TRUE;
        }
        i_this->m2BB = 0;
    }

    fopAcM_OnStatus(i_this, fopAcStts_SHOWMAP_e);
    dBgS_ObjGndChk_Yogan lavaChk;
    cXyz pos(i_this->current.pos.x, i_this->current.pos.y + 200.0f, i_this->current.pos.z);
    lavaChk.SetPos(&pos);
    f32 lavaY = dComIfG_Bgsp()->GroundCross(&lavaChk);
    if (lavaY != C_BG_MIN_HEIGHT && lavaY > i_this->current.pos.y - 30.0f + REG0_F(13)) {
        if (i_this->m18FA == 0) {
            i_this->speedF *= 0.1f;
            i_this->speed.y = 0.0f;
            cXyz pos(i_this->current.pos.x, lavaY, i_this->current.pos.z);
            fopKyM_createMpillar(&pos, 1.75f);
        }
        i_this->m18FA = 1;
        i_this->gravity = -0.5f;
        if (i_this->speed.y < -5.0f) {
            i_this->speed.y = -5.0f;
        }
    } else {
        i_this->m18FA = 0;
        i_this->gravity = -3.0f;
    }
    i_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    mt_eye_tex_anm(i_this);
    if (l_HIO.m04 == 0) {
        if (i_this->m18D4 != 0 && ++i_this->m18D4 == 11) {
            i_this->m18D4 = 0;
        }
        i_this->setBtAttackData(100.0f, 100.0f, 10000.0f, fopEn_enemy_c::OPENING_NONE);
        for (int i = 0; i < 5; i++) {
            if (i_this->m456[i] != 0) {
                i_this->m456[i]--;
            }
        }
        if (i_this->m18FC != 0) {
            i_this->m18FC--;
        }
        if (i_this->m460 != 0) {
            i_this->m460--;
        }
        if (i_this->m462 != 0) {
            i_this->m462--;
        }
        if (i_this->m34A != 0) {
            i_this->m34A--;
        }
        if (i_this->m48E != 0) {
            i_this->m48E--;
            i_this->m490++;
        } else {
            if (i_this->m490 != 0) {
                if (i_this->m490 > 15) {
                    i_this->m490 = 15;
                }
                i_this->m490--;
            }
        }
        i_this->m46A++;
        if (i_this->m466 != 0) {
            i_this->m466--;
        }
        if (i_this->m454 > 3) {
            damage_check(i_this);
        }
        i_this->mC04 = 0;
        dBgS_LinChk linChk;

        cXyz end(player->current.pos.x, player->current.pos.y + 20.0f, player->current.pos.z);
        cXyz start(i_this->current.pos.x, i_this->current.pos.y + 30.0f, i_this->current.pos.z);
        linChk.Set(&start, &end, i_this);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            i_this->m18F9 = 1;
        } else {
            i_this->m18F9 = 0;
        }
        if (i_this->m454 == 0) {
            mt_move(i_this);
            cLib_addCalcAngleS2(&i_this->shape_angle.x, i_this->current.angle.x, 2, 0x800);
            cLib_addCalcAngleS2(&i_this->shape_angle.y, i_this->current.angle.y, 2, 0x800);
            cLib_addCalcAngleS2(&i_this->shape_angle.z, i_this->current.angle.z, 4, 0x800);
            body_control1(i_this);
            i_this->current.pos.x += i_this->mStts.GetCCMoveP()->x;
            i_this->current.pos.z += i_this->mStts.GetCCMoveP()->z;
            for (int i = 0; i < 64; i++) {
                i_this->m6F4[i].x += i_this->mStts.GetCCMoveP()->x;
                i_this->m6F4[i].z += i_this->mStts.GetCCMoveP()->z;
            }
            if (i_this->m456[1] == 0) {
                i_this->m456[1] = cM_rndF(100.0f) + 150.0f + 150.0f;
                if (l_HIO.m05 == 0 && abs(i_this->current.angle.x) < 0x1000) {
                    i_this->m48E = REG0_F(8) + cM_rndF(50.0f) + 50.0f;
                }
            }
        } else if (i_this->m454 == 1) {
            mt_fight(i_this);
            // ?
            f32 f = i_this->m462 * (REG0_F(14) + 500.0f);
            i_this->m49C = f * cM_ssin(i_this->m46A * 0x2100);
            i_this->m49A = f * cM_scos(i_this->m46A * 0x2300);
            i_this->shape_angle = i_this->current.angle; // TODO +
            body_control2(i_this);
            body_wall_check(i_this);
            mt_bg_check(i_this);
            i_this->current.pos.x += i_this->mStts.GetCCMoveP()->x;
            i_this->current.pos.z += i_this->mStts.GetCCMoveP()->z;
        } else if (i_this->m454 == 2) {
            mt_move_maru(i_this);
            body_control3(i_this);
            if (i_this->m466 <= 100) {
                body_wall_check(i_this);
            } else if (i_this->m18FA != 0 && i_this->m466 > 50) {
                i_this->m466 = 51;
            }
            i_this->current.pos.x += i_this->mStts.GetCCMoveP()->x;
            i_this->current.pos.z += i_this->mStts.GetCCMoveP()->z;
            if (i_this->m466 == 50) {
                i_this->m2E4 = 0;
                i_this->m454 = 1;
                i_this->m455 = 1;
                i_this->m18FB = 2;
                i_this->health = 8;
                i_this->mSph[0].OnTgShield();
                i_this->m456[0] = l_HIO.m10;
                i_this->m48E = 0;
                anm_init(i_this, 10, 0.0f, 2, 0.0f, 0);
                fopAcM_SetMin(i_this, -200.0f, -200.0f, -200.0f);
                fopAcM_SetMax(i_this, 200.0f, 200.0f, 200.0f);
                // TODO ObjAt flags
            }
        } else if (i_this->m454 == 3) {
            i_this->m460 = 5;
            i_this->attention_info.flags = 0;
            body_control4(i_this);
            if (i_this->m456[2] == 1) {
                i_this->m1CBC = 1;
                fopAcM_delete(i_this);
                fopAcM_onActor(i_this);
            }
        } else if (i_this->m454 == 6) {
            if (player->getCutType() == 0x10) {
                cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
                cXyz pos(0.0f, 0.0f, REG0_F(14) - 50.0f);
                cXyz pos2;
                MtxPosition(&pos, &pos2);
                cLib_addCalc2(&i_this->current.pos.x, player->current.pos.x + pos2.x, 0.5f, 50.0f);
                cLib_addCalc2(&i_this->current.pos.z, player->current.pos.z + pos2.z, 0.5f, 50.0f);
            }
            i_this->m464 = 3;
            i_this->m2E4 = 1;
            i_this->m460 = 5;
            body_control5(i_this);
            i_this->current.pos.y += i_this->speed.y;
            i_this->speed.y += i_this->gravity;
            mt_bg_check(i_this);
            if (i_this->m456[0] == 0) {
                if (player->getCutType() != 0x10) {
                    i_this->m2E4 = 0;
                    i_this->m454 = 1;
                    i_this->m455 = 0;
                    i_this->mSph[0].OnTgShield();
                    i_this->m456[0] = l_HIO.m10;
                    i_this->m48E = 0;
                    anm_init(i_this, 10, 20.0f, 2, 1.0f, 0);
                    // TODO ObjAt flags
                } else {
                    i_this->m474 = REG0_F(13) + 0.2f;
                    if (i_this->mEyeSph.ChkTgHit()) {
                        i_this->health = 0;
                        i_this->m456[0] = REG0_S(3) + 40;
                        i_this->m474 = REG0_F(13) + 1.5f;
                        fopAcM_seStart(i_this, JA_SE_LK_LAST_HIT, 0);
                        fopAcM_monsSeStart(i_this, JA_SE_CV_MG_DAMAGE, 0);
                        atInfo.mpObj = i_this->mEyeSph.GetTgHitObj();
                        at_power_check(&atInfo);
                        mDoAud_onEnemyDamage();
                        mDoAud_bgmHitSound(atInfo.mHitSoundId);
                        dScnPly_ply_c::setPauseTimer(REG0_S(7) + 6);
                        dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &i_this->current.pos);
                        cXyz scale(2.0f, 2.0f, 2.0f);
                        csXyz angle(0, fopAcM_searchPlayerAngleY(i_this), 0);
                        dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &i_this->current.pos, &angle, &scale);
                        dKy_SordFlush_set(i_this->current.pos, 1);
                        anm_init(i_this, 8, 0.0f, 0, 0.0f, 0);
                    }
                }
            } else {
                i_this->m46E = 0;
                cLib_addCalc0(&i_this->m474, 0.05f, REG0_F(12) + 0.02f);
                if (i_this->m456[0] == 1) {
                    bakuha(i_this);
                }
            }
        }
        if (i_this->m466 <= 60) {
            cLib_addCalc2(&i_this->m18F0, 1.0f, 1.0f, 0.1f);
        } else {
            cLib_addCalc0(&i_this->m18F0, 1.0f, 0.5f);
        }
    }
    dBgS_ObjLinChk linChk;
    cXyz start = i_this->old.pos;
    cXyz end(start.x, start.y + 40.0f, start.z);
    linChk.Set(&start, &end, i_this);
    
}

/* 00007CC4-00007CCC       .text daMt_IsDelete__FP8mt_class */
static BOOL daMt_IsDelete(mt_class* i_this) {
    return TRUE;
}

/* 00007CCC-00007E18       .text daMt_Delete__FP8mt_class */
static BOOL daMt_Delete(mt_class* i_this) {
    dComIfG_resDelete(&i_this->mPhs, "Mt");
    if (i_this->m450 != NULL) {
        i_this->m450->quitImmortalEmitter();
        i_this->m450->becomeInvalidEmitter();
        i_this->m450 = NULL;
    }
    for (int i = 0; i < 8; i++) {
        i_this->m3B0[i]->end(); // TODO remove?
    }
    if (i_this->m1CBC != 0 && i_this->m2B6 != 0 && i_this->m2BA != 0 && !dComIfGs_isSwitch(i_this->m2BA, fopAcM_GetRoomNo(i_this))) {
        fopAcM_prm_class* params = fopAcM_CreateAppend();
        params->mPos = i_this->home.pos;
        params->mAngle = i_this->home.angle;
        params->mParameter = fopAcM_GetParam(i_this);
        params->mRoomNo = fopAcM_GetRoomNo(i_this);
        fopAcM_create(PROC_MT, NULL, params);
    }
    return TRUE;
}

static int br_bmd[3] = {
    0,0,0
};

static s16 bmd_data[8] = {
    0, MT_BDL_KBB, 0, MT_BDL_KBA, 0, MT_BDL_KBA,0, MT_BDL_KBA
};

static f32 scale_data[8] = {
    1.0f, 1.0f, 1.0f, 0.975f, 0.925f, 0.825f, 0.75f, 0.525f
};

/* 00007E18-00008400       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* i_ac) {
    mt_class* actor = (mt_class*) i_ac;
    for (int i = 0; i < 8; i++) {
        actor->mpMorfs[i] = new mDoExt_McaMorf(
            (J3DModelData*) dComIfG_getObjectRes("Mt", bmd_data[i]),
            NULL, NULL, NULL,
            J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
            0x800000, 0x37440402
        );
        if (actor->mpMorfs[i] == NULL) {
            return FALSE;
        }
        J3DModel* model = actor->mpMorfs[i]->getModel();
        if (model == NULL) {
            return FALSE;
        }
        J3DModelData* modelData = model->getModelData();
        actor->btk[i] = new mDoExt_btkAnm();
        JUT_ASSERT(0x11C0, actor->btk[i]);
        if (!actor->btk[i]->init(modelData, (J3DAnmTextureSRTKey*) dComIfG_getObjectRes("Mt", btk_data[i]), TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE)) {
            return FALSE;
        }

        actor->brk[i] = new mDoExt_brkAnm();
        JUT_ASSERT(0x11CD, actor->brk[i]);
        if (!actor->brk[i]->init(modelData, (J3DAnmTevRegKey*) dComIfG_getObjectRes("Mt", brk_data[i]), TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE)) {
            return FALSE;
        }

        if (i == 0) {
            anm_init(actor, 10, 0.0f, 2, 0.0f, 0);
            J3DAnmTexPattern* pat;
            for (int j = 0; j < 2; j++) {
                pat = (J3DAnmTexPattern*) dComIfG_getObjectRes("Mt", mt_tex_anm_idx[j]);
                pat->searchUpdateMaterialID(modelData);
            }
            actor->m340 = new J3DTexNoAnm[pat->getUpdateMaterialNum()];
            for (int j = 0; j < pat->getUpdateMaterialNum(); j++) {
                actor->m340[i].setAnmIndex(j);
            }
            tex_anm_set(actor, 0);
        }

        model->setUserArea((u32) actor);
        for (int jntNo = 0; jntNo < modelData->getJointNum(); jntNo++) {
            if (i == 0) {
                if (jntNo > 1 && jntNo < 6) {
                    modelData->getJointNodePointer(jntNo)->setCallBack(nodeCallBack_head);
                }
            } else if (i == 7) {
                if (jntNo > 1 && jntNo < 6) {
                    modelData->getJointNodePointer(jntNo)->setCallBack(nodeCallBack_tail);
                }
            } else {
                if (jntNo > 1 && jntNo < 6) {
                    modelData->getJointNodePointer(jntNo)->setCallBack(nodeCallBack_body);
                }
            }
        }

        actor->mScale[i] = scale_data[i];
    }

    for (int i = 0; i < 3; i++) {
        J3DModelData* modelData = (J3DModelData*) dComIfG_getObjectRes("Mt", br_bmd[i]);
        JUT_ASSERT(0x127A, modelData != NULL);
        actor->br_modelL[i] = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        JUT_ASSERT(0x127D, actor->br_modelL[i] != NULL);
        actor->br_modelR[i] = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        JUT_ASSERT(0x127F, actor->br_modelR[i] != NULL);
        actor->br_modelL[i]->setBaseScale(actor->scale);
        actor->br_modelR[i]->setBaseScale(actor->scale);
    }

    return TRUE;
}

static dCcD_SrcSph sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ dCcG_SE_UNK2,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
        /* SrcGObjTg Se      */ dCcG_SE_UNK5,
        /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 30.0f,
    },
};

/* 000084AC-000088A8       .text daMt_Create__FP10fopAc_ac_c */
static cPhs_State daMt_Create(fopAc_ac_c* i_ac) {
    static dCcD_SrcSph eye_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ 0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ 0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 30.0f,
        },
    };

    fopAcM_SetupActor(i_ac, mt_class);
    mt_class* i_this = (mt_class*) i_ac;

    cPhs_State phase_state = dComIfG_resLoad(&i_this->mPhs, "Mt");
    if (phase_state == cPhs_COMPLEATE_e) {
        i_this->gbaName = 5;
        i_this->m2B4 = fopAcM_GetParam(i_this) & 0xFF;
        if (i_this->m2B4 == 0xFF) {
            i_this->m2B4 = 0;
        }

        i_this->m2B5 = (fopAcM_GetParam(i_this) >> 8) & 0x7F;
        i_this->m2B6 = (fopAcM_GetParam(i_this) >> 0xF) & 0x1;
        i_this->m2B7 = (fopAcM_GetParam(i_this) >> 0x10) & 0xFF;
        i_this->m2B8 = (fopAcM_GetParam(i_this) >> 0x18) & 0xFF;

        if (i_this->m2B6 == 0) {
            i_this->m2B9 = i_this->current.angle.z;
            if (i_this->m2B9 != 0) {
                if (dComIfGs_isSwitch(i_this->m2B9, fopAcM_GetRoomNo(i_this))) {
                    return cPhs_ERROR_e;
                }
            }
        } else {
            i_this->m2BA = i_this->current.angle.z;
        }
        i_this->current.angle.z = 0;

        i_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("magtail", 0);
        if (!fopAcM_entrySolidHeap(i_this, CallbackCreateHeap, 0x1BFC8)) {
            return cPhs_ERROR_e;
        }

        i_this->initBt(162.5f, 200.0f);
        if (i_this->m2B4 >= 10) {
            switch (i_this->m2B5) {
                case 1:
                    i_this->m488 = 1000;
                    break;
                case 2:
                    i_this->m488 = 500;
                    break;
                case 3:
                    i_this->m488 = 250;
                    break;
                case 11:
                    i_this->m488 = -1000;
                    break;
                case 12:
                    i_this->m488 = -500;
                    break;
                case 13:
                    i_this->m488 = -250;
                    break;
            }
        } else if (i_this->m2B7 != 0xFF) {
            i_this->mpPath = dPath_GetRoomPath(i_this->m2B7, fopAcM_GetRoomNo(i_this));
            if (i_this->mpPath == NULL) {
                return cPhs_ERROR_e;
            }
            i_this->m2BC = i_this->m2B7 + 1;
            i_this->m2BE = 1;
            i_this->m47C = i_this->mpPath->m_points[0].m_position; // TODO might not be a cXyz assignment
        }
        if (i_this->m2B8 != 0xFF) {
            i_this->m2BB = i_this->m2B8 + 1;
        }
        fopAcM_SetMtx(i_this, i_this->mpMorfs[1]->getModel()->getBaseTRMtx());
        fopAcM_SetMin(i_this, -200.0f, -200.0f, -200.0f);
        fopAcM_SetMax(i_this, 200.0f, 200.0f, 200.0f);
        i_this->gravity = -3.0f;
        i_this->m46A = cM_rndF(32768.0f);
        for (int i = 0; i < 64; i++) {
            i_this->m6F4[i] = i_this->current.pos;
            i_this->m9F4[i] = i_this->current.angle;
        }
        i_this->mAcch.Set(fopAcM_GetPosition_p(i_this), fopAcM_GetOldPosition_p(i_this), i_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(i_this));
        i_this->mAcchCir.SetWall(50.0f, REG0_F(0) + 19.0f);
        i_this->mStts.Init(250, 2, i_this);
        for (int i = 0; i < 8; i++) {
            i_this->mSph[i].Set(sph_src);
            i_this->mSph[i].SetStts(&i_this->mStts);
        }
        i_this->mSph[0].SetAtAtp(2);
        i_this->mEyeSph.Set(eye_sph_src);
        i_this->mEyeSph.SetStts(&i_this->mStts);
        i_this->m18F0 = 1.0f;
        i_this->m18FB = 2;
        i_this->max_health = 8;
        i_this->health = 8;
        i_this->mEnemyIce.mpActor = i_this;
        i_this->mEnemyIce.mDeathSwitch = i_this->m2B9;
        daMt_Execute(i_this);
    }
}

static actor_method_class l_daMt_Method = {
    (process_method_func)daMt_Create,
    (process_method_func)daMt_Delete,
    (process_method_func)daMt_Execute,
    (process_method_func)daMt_IsDelete,
    (process_method_func)daMt_Draw,
};

actor_process_profile_definition g_profile_MT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(mt_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_MT,
    /* Actor SubMtd */ &l_daMt_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK40000_e | fopAcStts_UNK8000000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
