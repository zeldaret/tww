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
#include "d/actor/d_a_player_main.h"

static u8 mt_count;
static daMt_HIO_c l_HIO;
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

static u8 br_no[11] = {0, 1, 1, 2, 2, 2, 1, 0, 0, 0, 0};
static s16 br_ya[11] = {0xCD38, 0xDCD8, 0xF060, 0, 0, 0, 0, 0, 0, 0, 0};

static f32 check_x[6] = {0.0f, 0.0f, 50.0f, -50.0f, -1.0f, 1.0f};
static f32 check_y[6] = {-50.0f, -50.0f, -150.0f, -150.0f, 100.0f, 100.0f};
static f32 check_z[6] = {150.0f, -10.0f, 0.0f, 0.0f, 200.0f, 200.0f};
static u8 check_bitD[6] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20};

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
    i_this->mpMorf[0]->setAnm(bckAnm, loopMode, morf, playSpeed, 0.0f, -1.0f, NULL);
}

/* 000002D8-00000350       .text mt_a_d_sub__FPvPv */
void* mt_a_d_sub(void* param_1, void*) {
    if (fopAcM_IsActor(param_1) && fopAcM_GetName(param_1) == PROC_MT) {
        mt_all_count++;
        mt_class* mt = (mt_class*)param_1;
        if (mt->mMode == 1) {
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
    i_this->mTexAnmPlaying = true;
    J3DAnmTexPattern* btp = (J3DAnmTexPattern*)dComIfG_getObjectRes("Mt", mt_tex_anm_idx[index]);
    i_this->mAnmTexMaxFrame = mt_tex_max_frame[index];
    i_this->mpAnmTex = btp;
    i_this->mTexAnmFrame = 0;
    i_this->mpAnmTex->setFrame(0.0f);
    u16 material_num = btp->getUpdateMaterialNum();
    for (u16 i = 0; i < material_num; i++) {
        i_this->mpTexNoAnm[i].setAnmTexPattern(btp);
    }
}

/* 0000053C-000005EC       .text mt_eye_tex_anm__FP8mt_class */
void mt_eye_tex_anm(mt_class* i_this) {
    if (i_this->mBlinkTimer != 0) {
        i_this->mBlinkTimer--;
    } else {
        i_this->mBlinkTimer = cM_rndF(100.0f) + 50.0f;
        if (!i_this->mTexAnmPlaying) {
            tex_anm_set(i_this, 0);
        }
    }

    if (i_this->mTexAnmPlaying) {
        if (i_this->mTexAnmFrame < i_this->mAnmTexMaxFrame) {
            i_this->mTexAnmFrame++;
        } else {
            i_this->mTexAnmPlaying = false;
        }
    }
}

/* 000005EC-00000720       .text nodeCallBack_head__FP7J3DNodei */
static BOOL nodeCallBack_head(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        s32 jntNo = ((J3DJoint*)node)->getJntNo();
        J3DModel* model = j3dSys.getModel();
        mt_class* i_this = (mt_class*) model->getUserArea();
        if (i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo == 2) {
                cMtx_YrotM(*calc_mtx, -i_this->m640[0].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[0].z);
            } else if (jntNo == 3) {
                cMtx_YrotM(*calc_mtx, i_this->m640[15].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[15].z);
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
                cMtx_YrotM(*calc_mtx, -i_this->m640[j_index + 1].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[j_index + 1].z);
            } else if (jntNo == 3) {
                cMtx_YrotM(*calc_mtx, -i_this->m640[j_index + 2].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[j_index + 2].z);
            } else if (jntNo == 4) {
                cMtx_YrotM(*calc_mtx, i_this->m640[j_index + 16].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[j_index + 16].z);
            } else if (jntNo == 5) {
                cMtx_YrotM(*calc_mtx, i_this->m640[j_index + 17].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[j_index + 17].z);
                j_index += 2;
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
                cMtx_YrotM(*calc_mtx, -i_this->m640[13].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[13].z);
            } else if (jntNo == 3) {
                cMtx_YrotM(*calc_mtx, -i_this->m640[14].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[14].z);
            } else if (jntNo == 4) {
                cMtx_YrotM(*calc_mtx, i_this->m640[28].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[28].z);
            } else if (jntNo == 5) {
                cMtx_YrotM(*calc_mtx, i_this->m640[29].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[29].z);
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
    i_this->mAngle[0] = i_this->shape_angle;

    cXyz* pos_i = &i_this->mPos[0];
    cXyz* old_pos_i = &i_this->mOldPos[0];
    csXyz* angle_i = &i_this->mAngle[0];
    cXyz* m590_i = &i_this->m590[0];
    dBgS_LinChk linChk;
    cXyz diff, end2, end1, offset, out, start, local_184;

    local_184.set(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 8; i++, pos_i++, old_pos_i++, angle_i++, m590_i++) {
        if (i > 0) {
            u8 num_crossed = 0;
            start = *pos_i;
            start.y += 50.0f;
            cMtx_YrotS(*calc_mtx, angle_i->y);
            offset.set(3.0f, -200.0f, 0.0f);
            MtxPosition(&offset, &end1);
            end1 += *pos_i;
            linChk.Set(&start, &end1, i_this);
            bool crossed = dComIfG_Bgsp()->LineCross(&linChk);
            if (crossed != 0) {
                end1 = linChk.GetCross();
                num_crossed = 1;
            }
            offset.x *= -1.0f;
            MtxPosition(&offset, &end2);
            end2 += *pos_i;
            linChk.Set(&start, &end2, i_this);
            if (dComIfG_Bgsp()->LineCross(&linChk)) {
                end2 = linChk.GetCross();
                num_crossed++;
            }

            s16 target = 0;
            f32 f30;
            if (num_crossed == 2) {
                f30 = pos_i->y - 10.0f;
                f32 fVar2 = end1.y + l_HIO.m18;
                if (f30 < fVar2) {
                    f30 = fVar2;
                    diff = end1 - end2;
                    f32 xzmag = std::sqrtf(diff.x * diff.x + diff.z * diff.z);
                    target = cM_atan2s(diff.y, xzmag);
                }
            }

            cLib_addCalcAngleS2(&angle_i->z, target, 2, 0x400);
            f32 f = m590_i->y - pos_i[-1].y + f30;
            if (i_this->m48E == 0) {
                offset.set(
                    cM_ssin(i_this->m46A * (REG0_S(5) + 0x5DC) + i * (REG0_S(6) + 0x1D4C)) * 3.0f,
                    0.0f,
                    REG0_F(3) + -5.0f
                );
                cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
                MtxPosition(&offset, &local_184);
            }

            f32 fVar4 = pos_i->x - pos_i[-1].x + m590_i->x + local_184.x;
            f32 fVar5 = pos_i->z - pos_i[-1].z + m590_i->z + local_184.z;
            int iVar8 = cM_atan2s(fVar4, fVar5);
            fVar4 = std::sqrtf(fVar4 * fVar4 + fVar5 * fVar5);
            s16 iVar9 = -cM_atan2s(f, fVar4);
            offset.set(0.0f, 0.0f, REG0_F(7) + 35.0f);
            cMtx_YrotS(*calc_mtx, iVar8);
            cMtx_XrotM(*calc_mtx, iVar9);
            MtxPosition(&offset, &out);
            angle_i->y = iVar8 + 0x8000;
            angle_i->x = -iVar9;
            *old_pos_i = *pos_i;

            pos_i->x = pos_i[-1].x + out.x;
            pos_i->y = pos_i[-1].y + out.y;
            pos_i->z = pos_i[-1].z + out.z;
            m590_i->x = fVar1 * (pos_i->x - old_pos_i->x);
            m590_i->y = fVar1 * (pos_i->y - old_pos_i->y);
            m590_i->z = fVar1 * (pos_i->z - old_pos_i->z);
        }

        J3DModel* model = i_this->mpMorf[i]->getModel();
        model->setBaseScale(i_this->scale);
        mDoMtx_stack_c::transS(*pos_i);
        mDoMtx_stack_c::YrotM(angle_i->y);
        mDoMtx_stack_c::XrotM(angle_i->x);
        mDoMtx_stack_c::ZrotM(angle_i->z);

        if (i == 0) {
            mDoMtx_stack_c::YrotM(i_this->m468);
        }
        if (i == 0) {
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
            offset.set(0.0f, 0.0f, REG0_F(9) + 30.0f);
            mDoMtx_stack_c::multVec(&offset, &i_this->eyePos);
            i_this->mEyeSph.SetC(i_this->eyePos);
            offset.set(0.0f, 0.0f, REG6_F(9) + 100.0f);
            mDoMtx_stack_c::multVec(&offset, &out);
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
            i_this->mSph[i].SetC(*pos_i);
            if (i_this->m460 != 0) {
                i_this->mSph[i].SetR(-200.0f);
            } else {
                i_this->mSph[i].SetR(l_HIO.m48);
            }
        }

        dComIfG_Ccsp()->Set(&i_this->mSph[i]);
        if (i_this->mC01 && i >= 1) {
            u32 uVar3 = i_this->mC00 ? move_ad2[i] & 0x3F : move_ad[i] & 0x3F;
            for (int j = 0; j < 6; j++) {
                u8 uVar2 = (uVar3 + j) & 0x3F;
                f32 diff_x = ((pos_i[-1].x - pos_i->x) / 5.0f) * j;
                f32 diff_y = ((pos_i[-1].y - pos_i->y) / 5.0f) * j;
                f32 diff_z = ((pos_i[-1].z - pos_i->z) / 5.0f) * j;
                i_this->m6F4[uVar2].x = pos_i->x + diff_x;
                i_this->m6F4[uVar2].y = pos_i->y + diff_y;
                i_this->m6F4[uVar2].z = pos_i->z + diff_z;
                i_this->m9F4[uVar2] = *angle_i;
            }
        }
    }

    if (i_this->mC01) {
        i_this->mC01 = false;
        i_this->mMode = 0;
        i_this->mFightMode = 0;
        i_this->mBF4 = 0;
        i_this->mTimer[1] = 100;
        i_this->m48E = 0;
        anm_init(i_this, MT_BCK_WAIT1, 20.0f, 2, 1.0f, 0);
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
    for (int i = 1; i < 8; i++) {
        cXyz start = i_this->mOldPos[i];
        start.y += 50.0f;
        cXyz end = i_this->mPos[i];
        end.y += 50.0f;
        if (wall_check_sub(i_this, &start, &end)) {
            i_this->mPos[i].x = i_this->mOldPos[i].x;
            i_this->mPos[i].z = i_this->mOldPos[i].z;
        }
    }
}

/* 00001F10-000022D8       .text body_control1__FP8mt_class */
void body_control1(mt_class* i_this) {
    i_this->m6F4[i_this->mBF4] = i_this->current.pos;
    i_this->m9F4[i_this->mBF4] = i_this->shape_angle;
    i_this->mB74[i_this->mBF4] = i_this->m468;
    for (int i = 0; i < 8; i++) {
        u32 uVar2 = i_this->mC00 ? (i_this->mBF4 + move_ad2[i]) & 0x3F : (i_this->mBF4 + move_ad[i]) & 0x3F;
        J3DModel* model = i_this->mpMorf[i]->getModel();
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

            offset.set(0.0f, 0.0f, REG6_F(9) + 100.0f);
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
        if (i_this->mC01) {
            i_this->mPos[i] = i_this->m6F4[uVar2];
            i_this->mAngle[i] = i_this->m9F4[uVar2];
        }
    }

    if (i_this->m48E == 0) {
        i_this->mBF4++;
    }
    i_this->mBF4 &= 0x3F;

    if (i_this->mC01) {
        i_this->mC01 = false;
        i_this->mMode = 1;
        i_this->mFightMode = 0;
        i_this->mTimer[0] = l_HIO.m10;
        i_this->m48E = 0;
        anm_init(i_this, MT_BCK_WAIT1, 20.0f, 2, 1.0f, 0);
    }

    cLib_addCalc2(&i_this->m470, -10.0f, 1.0f, 1.0f);
}

/* 000022D8-000028BC       .text body_control3__FP8mt_class */
void body_control3(mt_class* i_this) {
    i_this->mPos[0] = i_this->current.pos;
    i_this->mAngle[0] = i_this->shape_angle;

    cXyz* old_pos_i = &i_this->mOldPos[0];
    cXyz* pos_i = &i_this->mPos[0];
    csXyz* angle_i = &i_this->mAngle[0];

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


    for (int i = 0; i < 8; i++, old_pos_i++, angle_i++, pos_i++) {
        if (i > 0) {
            sVar13 -= (s16)(i_this->m48A + sVar6);
            offset.x = i_this->m330 * cM_ssin(i_this->m466 * (REG0_S(5) + 5000) + i * (REG0_S(6) + 7000));
            offset.y = 0.0f;
            offset.z = -i_this->m478;
            cXyz out;
            cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
            cMtx_XrotM(*calc_mtx, i_this->shape_angle.x + sVar13);
            cMtx_ZrotM(*calc_mtx, i_this->shape_angle.z);
            MtxPosition(&offset, &out);
            f32 fVar1 = pos_i->x - pos_i[-1].x + out.x;
            f32 fVar2 = pos_i->y - pos_i[-1].y + out.y;
            f32 fVar3 = pos_i->z - pos_i[-1].z + out.z;
            s32 sVar10 = cM_atan2s(fVar1, fVar3);
            fVar1 = std::sqrtf(fVar1 * fVar1 + fVar3 * fVar3);
            s16 sVar4 = -cM_atan2s(fVar2, fVar1);
            cXyz offset2(0.0f, 0.0f, REG0_F(7) + 35.0f);
            cMtx_YrotS(*calc_mtx, sVar10);
            cMtx_XrotM(*calc_mtx, sVar4);
            MtxPosition(&offset2, &out);
            s16 sVar7 = sVar10 - i_this->shape_angle.y;
            u32 uVar5 = sVar7 < 0 ? -sVar7 : sVar7;
            if (uVar5 < 0x4000) {
                angle_i->y = sVar10;
                angle_i->x = -(sVar4 - 0x8000);
            } else {
                angle_i->y = sVar10 - 0x8000;
                angle_i->x = sVar4;
            }
            *old_pos_i = *pos_i;
            pos_i->x = pos_i[-1].x + out.x;
            pos_i->y = pos_i[-1].y + out.y;
            pos_i->z = pos_i[-1].z + out.z;
        }

        J3DModel* model = i_this->mpMorf[i]->getModel();
        model->setBaseScale(i_this->scale);
        mDoMtx_stack_c::transS(pos_i->x + out.x, pos_i->y + out.y, pos_i->z + out.z);
        mDoMtx_stack_c::YrotM(angle_i->y);
        mDoMtx_stack_c::XrotM(angle_i->x);
        mDoMtx_stack_c::ZrotM(angle_i->z);

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
                i_this->mSph[0].OffAtSPrmBit(cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e);
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
    J3DModel* model = i_this->mpMorf[0]->getModel();
    mDoMtx_stack_c::scaleS(0.0f, 0.0f, 0.0f);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    for (int i = 1; i < 8; i++) {
        if (i_this->m5F0[i] != 0) {
            i_this->m5F0[i]--;
        } else {
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8060, &i_this->mPos[i], 0xFF, g_whiteColor, g_whiteColor);
            i_this->mPos[i].x += i_this->m590[i].x;
            i_this->mPos[i].y += i_this->m590[i].y;
            i_this->mPos[i].z += i_this->m590[i].z;
            i_this->m590[i].y -= 2.5f;
            i_this->mAngle[i].x += 0x1800;
            i_this->mAngle[i].y += 0x1800;
            if (i_this->m590[i].y < 0.0f) {
                cLib_addCalc0(&i_this->mScale[i], 1.0f, 0.025f);
            }
        }

        model = i_this->mpMorf[i]->getModel();
        mDoMtx_stack_c::transS(i_this->mPos[i]);
        mDoMtx_stack_c::YrotM(i_this->mAngle[i].y);
        mDoMtx_stack_c::XrotM(i_this->mAngle[i].x);
        mDoMtx_stack_c::ZrotM(i_this->mAngle[i].z);
        mDoMtx_stack_c::scaleM(i_this->mScale[i], i_this->mScale[i], i_this->mScale[i]);
        if (i == 7) {
            mDoMtx_stack_c::scaleM(0.0f, 0.0f, 0.0f);
        }
        model->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

/* 00002AB0-00003008       .text body_control5__FP8mt_class */
void body_control5(mt_class* i_this) {
    i_this->mPos[0] = i_this->current.pos;
    i_this->mAngle[0] = i_this->shape_angle;

    f32 fVar3 = l_HIO.m18 + i_this->mAcch.GetGroundH();
    for (int i = 0; i < 8; i++) {
        if (i > 0) {
            cXyz offset;
            offset.x = i_this->m474 * (REG0_F(4) + 50.0f) * cM_ssin(i_this->m46A * (REG0_S(5) + 0xDAC) + i * (REG0_S(6) + 7000));
            offset.y = i_this->m474 * (REG0_F(5) + 80.0f) * cM_ssin(i_this->m46A * (REG0_S(7) + 0x1194) + i * (REG0_S(8) + 6000));
            offset.z = REG0_F(3) + -30.0f;
            cXyz out;
            cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
            MtxPosition(&offset, &out);
            f32 fVar2 = i_this->mPos[i].y - 10.0f + out.y;
            if (fVar2 < fVar3) {
                fVar2 = fVar3;
            }
            f32 mag_x = i_this->mPos[i].x - i_this->mPos[i - 1].x + out.x;
            f32 mag_y = fVar2 - i_this->mPos[i - 1].y;
            f32 mag_z = i_this->mPos[i].z - i_this->mPos[i - 1].z + out.z;
            int angle_y = cM_atan2s(mag_x, mag_z);
            f32 mag_xz = std::sqrtf(mag_x * mag_x + mag_z * mag_z);
            s16 angle_x = -cM_atan2s(mag_y, mag_xz);
            offset.set(0.0f, 0.0f, REG0_F(7) + 35.0f);
            cXyz dir;
            cMtx_YrotS(*calc_mtx, angle_y);
            cMtx_XrotM(*calc_mtx, angle_x);
            MtxPosition(&offset, &dir);
            i_this->mAngle[i].y = angle_y + 0x8000;
            i_this->mAngle[i].x = -angle_x;
            i_this->mPos[i].x = i_this->mPos[i - 1].x + dir.x;
            i_this->mPos[i].y = i_this->mPos[i - 1].y + dir.y;
            i_this->mPos[i].z = i_this->mPos[i - 1].z + dir.z;
        }

        J3DModel* model = i_this->mpMorf[i]->getModel();
        model->setBaseScale(i_this->scale);
        mDoMtx_stack_c::transS(i_this->mPos[i]);
        mDoMtx_stack_c::YrotM(i_this->mAngle[i].y);
        mDoMtx_stack_c::XrotM(i_this->mAngle[i].x);
        mDoMtx_stack_c::ZrotM(i_this->mAngle[i].z);
        if (i == 0) {
            mDoMtx_stack_c::YrotM(i_this->m468);
        }
        if (i == 0) {
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
            cXyz offset(0.0f, 0.0f, REG0_F(9) + 30.0f);
            mDoMtx_stack_c::multVec(&offset, &i_this->eyePos);
            i_this->mEyeSph.SetC(i_this->eyePos);
            i_this->mEyeSph.SetR(30.0f);
            dComIfG_Ccsp()->Set(&i_this->mEyeSph);
        } else {
            i_this->mSph[i].OffCoSetBit();
            i_this->mSph[i].SetC(i_this->mPos[i]);
        }

        i_this->mSph[i].OffAtSetBit();
        i_this->mSph[i].OffCoSetBit();
        dComIfG_Ccsp()->Set(&i_this->mSph[i]);
    }

    cLib_addCalc2(&i_this->m470, 20.0f, 1.0f, 1.0f);
    i_this->m468 =i_this->m474 * (REG0_F(7) + 3000.0f) * cM_ssin(i_this->m46A * (REG0_S(0) + 3000));
}

/* 00003008-00003210       .text br_draw__FP8mt_class */
void br_draw(mt_class* i_this) {
    if (i_this->br_frame != 0) {
        MtxTrans(i_this->eyePos.x, i_this->eyePos.y, i_this->eyePos.z, false);
        cMtx_YrotM(*calc_mtx, i_this->shape_angle.y);
        cMtx_XrotM(*calc_mtx, i_this->shape_angle.x);
        cMtx_ZrotM(*calc_mtx, i_this->shape_angle.z);
        f32 scale = l_HIO.m1C * (REG0_F(4) + 2.0f);
        MtxPush();
        cMtx_YrotM(*calc_mtx, br_ya[i_this->br_frame - 1]);
        cMtx_XrotM(*calc_mtx, -0x4000);
        MtxScale(scale, scale, scale, true);

        J3DModel* model = i_this->br_modelL[br_no[i_this->br_frame - 1]];
        g_env_light.setLightTevColorType(model, &i_this->tevStr);
        model->setBaseTRMtx(*calc_mtx);
        mDoExt_modelUpdateDL(model);
        MtxPull();
        cMtx_ZrotM(*calc_mtx, -0x8000);
        cMtx_YrotM(*calc_mtx, br_ya[i_this->br_frame - 1]);
        cMtx_XrotM(*calc_mtx, -0x4000);
        MtxScale(scale, scale, scale, true);
        model = i_this->br_modelR[br_no[i_this->br_frame - 1]];
        g_env_light.setLightTevColorType(model, &i_this->tevStr);
        model->setBaseTRMtx(*calc_mtx);
        mDoExt_modelUpdateDL(model);
    }
}

/* 00003210-00003360       .text daMt_shadowDraw__FP8mt_class */
static void daMt_shadowDraw(mt_class* i_this) {
    if (!fopAcM_checkCarryNow(i_this)) {
        cXyz pos(
            i_this->current.pos.x,
            i_this->current.pos.y + 150.0f + REG0_F(18),
            i_this->current.pos.z
        );

        i_this->m1CB8 = dComIfGd_setShadow(
            i_this->m1CB8, 1, i_this->mpMorf[0]->getModel(), &pos,
            REG0_F(19) + 800.0f, REG0_F(17) + 40.0f,
            i_this->current.pos.y, i_this->mAcch.GetGroundH(), i_this->mAcch.m_gnd,
            &i_this->tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
        );

        for (int i = 1; i < 8; i++) {
            dComIfGd_addRealShadow(i_this->m1CB8, i_this->mpMorf[i]->getModel());
        }
    } else {
        u32 player_shadow_id = daPy_getPlayerLinkActorClass()->getShadowID();
        if (player_shadow_id != 0) {
            for (int i = 0; i < 8; i++) {
                dComIfGd_addRealShadow(player_shadow_id, i_this->mpMorf[i]->getModel());
            }
        }
    }
}

/* 00003360-0000361C       .text daMt_Draw__FP8mt_class */
static BOOL daMt_Draw(mt_class* i_this) {
    cXyz local_3c(0.0f, 0.0f, 0.0f);
    if (i_this->m2BB != 0) {
        return TRUE;
    }

    j_index = 0;
    for (int i = 0; i < 8; i++) {
        J3DModel* model = i_this->mpMorf[i]->getModel();
        if (i_this->mEnemyIce.mLightShrinkTimer == 0) {
            cXyz cStack_48;
            MTXMultVec(model->getBaseTRMtx(), &local_3c, &cStack_48);
            g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &cStack_48, &i_this->tevStr);
        } else {
            f32 scale = i_this->mEnemyIce.mScaleXZ;
            i_this->scale.z = scale;
            i_this->scale.y = scale;
            i_this->scale.x = scale;
            model->setBaseScale(i_this->scale);
        }

        g_env_light.setLightTevColorType(model, &i_this->tevStr);
        i_this->btk[i]->entry(model->getModelData());
        i_this->brk[i]->entry(model->getModelData());
        if (i_this->m2E4 == 0) {
            int new_brk_frame = i_this->mBrkFrame + i * l_HIO.m50;
            while (new_brk_frame < 0) {
                new_brk_frame += 41;
            }
            i_this->brk[i]->setFrame(new_brk_frame);

            int new_btk_frame = i_this->mBtkFrame + i * l_HIO.m50;
            while (new_btk_frame < 0) {
                new_btk_frame += 31;
            }
            i_this->btk[i]->setFrame(new_btk_frame);
        } else {
            i_this->brk[i]->setFrame(i_this->mBrkFrame);
            i_this->btk[i]->setFrame(i_this->mBtkFrame);
        }

        if (i == 0) {
            model->getModelData()->getMaterialTable().setTexNoAnimator(i_this->mpAnmTex, i_this->mpTexNoAnm);
            i_this->mpAnmTex->setFrame(i_this->mTexAnmFrame);
        }
        i_this->mpMorf[i]->updateDL();
    }

    br_draw(i_this);
    daMt_shadowDraw(i_this);
    dSnap_RegistFig(DSNAP_TYPE_MT, i_this, 1.0f, 1.0f, 1.0f);

    return TRUE;
}

/* 0000361C-000037B0       .text bakuha__FP8mt_class */
void bakuha(mt_class* i_this) {
    fopAcM_createDisappear(i_this, &i_this->eyePos, 10, daDisItem_IBALL_e);
    if (!i_this->m2B6 && i_this->m2B9 != 0) {
        dComIfGs_onSwitch(i_this->m2B9, fopAcM_GetRoomNo(i_this));
    }

    i_this->mMode = 3;
    i_this->mTimer[2] = REG0_S(0) + 57;
    for (int i = 1; i < 8; i++) {
        i_this->m590[i].x = cM_rndFX(REG0_F(4) + 30.0f);
        i_this->m590[i].y = cM_rndF(10.0f) + 20.0f + REG0_F(5);
        i_this->m590[i].z = cM_rndFX(REG0_F(4) + 30.0f);
        i_this->m5F0[i] = cM_rndF(3.0f);
        if (i_this->m18F8 == 3) {
            i_this->m5F0[i] += 5;
        }
    }

    dComIfGp_particle_set(dPa_name::ID_SCENE_8096, &i_this->current.pos);
}

/* 000037B0-000042C4       .text mt_move__FP8mt_class */
void mt_move(mt_class* i_this) {
    fopAc_ac_c* actor = i_this;
    cXyz cross_pos[6];
    cXyz end_pos[6];
    dBgS_LinChk linChk;
    u8 cross_bits = 0;
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    cMtx_ZrotM(*calc_mtx, actor->current.angle.z);
    cXyz offset(0.0f, 50.0f, 0.0f);
    cXyz start_pos;
    MtxPosition(&offset, &start_pos);
    start_pos = start_pos + actor->current.pos;
    int segs = abs(actor->current.angle.x) < 0x1000 ? 6 : 4;
    for (int i = 0; i < segs; i++) {
        cXyz check_pos;
        check_pos.x = check_x[i];
        check_pos.y = check_y[i];
        check_pos.z = check_z[i];
        MtxPosition(&check_pos, &end_pos[i]);
        end_pos[i] += actor->current.pos;
        linChk.Set(&start_pos, &end_pos[i], actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            cross_pos[i] = linChk.GetCross();
            cross_bits |= check_bitD[i];
        }
    }

    if ((cross_bits & 0x3) == 0x3) {
        cXyz local_190 = cross_pos[0] - cross_pos[1];
        cXyz local_16C(0.0f, l_HIO.m18, 0.0f);
        cXyz local_178;
        MtxPosition(&local_16C, &local_178);
        if (i_this->m48E == 0) {
            cLib_addCalc2(&actor->current.pos.x, local_178.x + cross_pos[1].x + local_190.x * 0.5f, 1.0f, 1.0f);
            cLib_addCalc2(&actor->current.pos.y, local_178.y + cross_pos[1].y + local_190.y * 0.5f, 1.0f, 1.0f);
            cLib_addCalc2(&actor->current.pos.z, local_178.z + cross_pos[1].z + local_190.z * 0.5f, 1.0f, 1.0f);
        }
        f32 fVar1 = std::sqrtf(local_190.x * local_190.x + local_190.z * local_190.z);
        actor->current.angle.x = -cM_atan2s(local_190.y, fVar1);
        if (std::fabsf(local_190.x) > 0.1f || std::fabsf(local_190.z) > 0.1f) {
            i_this->m48C = cM_atan2s(local_190.x, local_190.z);
        }
        s16 sVar5 = i_this->m48C - actor->current.angle.y;
        uint uVar4 = (sVar5 < 0) ? -sVar5 : sVar5;
        if (uVar4 > 0x4000) {
            actor->current.angle.x = 0x8000 - actor->current.angle.x;
        }
        i_this->m492 = 23;
    } else if ((cross_bits & 0x1) == 0) {
        if (i_this->m492 == 0) {
            actor->current.angle.x += REG0_S(2) + 0x800;
        } else {
            i_this->m492--;
        }
    }

    if ((cross_bits & 0xC) == 0xC) {
        cXyz local_190 = cross_pos[2] - cross_pos[3];
        cMtx_XrotS(*calc_mtx, -actor->current.angle.x);
        cMtx_YrotM(*calc_mtx, -actor->current.angle.y);
        cXyz local_178;
        MtxPosition(&local_190, &local_178);
        f32 fVar1 = std::sqrtf(local_178.x * local_178.x + local_178.z * local_178.z);
        actor->current.angle.z = cM_atan2s(local_178.x, fVar1);
    }

    if (abs(actor->current.angle.x) < 0x1000) {
        if ((cross_bits & 0x30) == 0x30) {
            cXyz local_190 = cross_pos[4] - cross_pos[5];
            actor->current.angle.y = cM_atan2s(local_190.x, local_190.z) + 0x4000;
        } else {
            if (i_this->m2B4 >= 10) {
                actor->current.angle.y += i_this->m488;
            } else {
                s16 target_angle;
                if (i_this->m2BC != 0) {
                    cXyz local_190 = i_this->m47C - actor->current.pos;
                    target_angle = cM_atan2s(local_190.x, local_190.z);
                    i_this->m488 = 0x800;
                    if (std::sqrtf(local_190.x * local_190.x + local_190.z * local_190.z) < 100.0f) {
                        i_this->mPathPntIdx += i_this->mPathDir;
                        if (i_this->mPathPntIdx >= (s8)i_this->mpPath->m_num) {
                            if (dPath_ChkClose(i_this->mpPath)) {
                                i_this->mPathPntIdx = 0;
                            } else {
                                i_this->mPathDir = -1;
                                i_this->mPathPntIdx = i_this->mpPath->m_num - 2;
                            }
                        } else if (i_this->mPathPntIdx < 0) {
                            i_this->mPathDir = 1;
                            i_this->mPathPntIdx = 1;
                        }
                        dPnt* pt = &i_this->mpPath->m_points[i_this->mPathPntIdx];
                        i_this->m47C = pt->m_position;
                    }
                } else {
                    target_angle = fopAcM_searchPlayerAngleY(actor);
                    cLib_addCalcAngleS2(&i_this->m488, REG0_S(4) + 0x400, 1, 0x10);
                }
                 
                if (i_this->m2B5 == 1) {
                    actor->current.angle.y = target_angle;
                } else {
                    cLib_addCalcAngleS2(&actor->current.angle.y, target_angle, 0x10, i_this->m488);
                }
            } 

            if (i_this->m2B4 < 10 && !i_this->mBlocked && fopAcM_searchPlayerDistance(actor) < l_HIO.m24) {
                bool bVar3 = false;
                for (int i = 0; i < 64; i += 8) {
                    if (abs(i_this->m9F4[i].x) > 0x1000) {
                        bVar3 = true;
                        break;
                    }
                }
                if (!bVar3) {
                    i_this->mC01 = true;
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
        float fVar2 = i_this->mC00 ? 10.0f : 5.0f;
        cLib_addCalc2(&actor->speedF, fVar2, 1.0f, fVar2);
    } else {
        cLib_addCalc0(&actor->speedF, 1.0f, 5.0f);
    }

    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);
    cMtx_YrotM(*calc_mtx, i_this->m468);
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = actor->speedF;
    MtxPosition(&offset, &actor->speed);
    fopAcM_posMove(actor, NULL);
    if (cross_bits == 0) {
        i_this->m46C++;
        if (i_this->m46C >= 10) {
            i_this->mMode = 1;
            i_this->mFightMode = 0x11;
        }
    } else {
        i_this->m46C = 0;
    }
}

/* 000042C4-00005088       .text mt_fight__FP8mt_class */
void mt_fight(mt_class* i_this) {
    float fVar1;
    float fVar2;
    f32 fVar11;
    cXyz local_80;
    short local_74[6];
    cXyz local_68;
    cXyz local_5c;
    u64 local_50;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    short sVar9 = 0;
    switch (i_this->mFightMode) {
        case 0:
            mt_check(i_this);
            if (mt_fight_count <= 1) {
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
            local_5c.y = (REG0_F(11) + 20.0f) * cM_ssin(i_this->m46A * 1400) + 60.0f;
            local_5c.z = l_HIO.m28 + (REG0_F(12) + 30.0f) * cM_ssin(i_this->m46A * 600);

            sVar9 = (REG0_F(16) + -2000.0f) * cM_ssin(i_this->m46A * 1400);

            cMtx_YrotS(*calc_mtx, player->shape_angle.y + local_74[mt_count]);
            MtxPosition(&local_5c, &local_68);
            cLib_addCalc2(&i_this->current.pos.x, player->current.pos.x + local_68.x, 0.1f, REG0_F(10) + 4.0f);
            cLib_addCalc2(&i_this->current.pos.z, player->current.pos.z + local_68.z, 0.1f, REG0_F(10) + 4.0f);
            if (fopAcM_searchPlayerDistance(i_this) > l_HIO.m24 + 100.0f || (i_this->mBlocked && i_this->m466 == 0)) {
                cLib_addCalc2(&i_this->current.pos.y, i_this->mAcch.GetGroundH() + 40.0f, 0.5f, 3.0f);
                sVar9 = 0;
                i_this->m494 = 0;
                if (std::fabsf(i_this->current.pos.y - i_this->mAcch.GetGroundH() + 40.0f) < 2.0f) {
                    i_this->mC01 = true;
                }
            } else {
                cLib_addCalc2(&i_this->current.pos.y, local_68.y + l_HIO.m18 + i_this->mAcch.GetGroundH(), 0.1f, 5.0f);
                if (i_this->mTimer[0] == 0) {
                    i_this->mTimer[0] = l_HIO.m10;
                    if (cM_rndF(1.0f) < l_HIO.m14 && i_this->m466 == 0) {
                        i_this->mFightMode = 1;
                        i_this->mC02 = 0;
                        cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
                        local_5c.x = 0.0f;
                        local_5c.y = 30.0f;
                        local_5c.z = -30.0f;
                        MtxPosition(&local_5c, &i_this->m47C);
                        i_this->m47C += i_this->current.pos;
                        anm_init(i_this, MT_BCK_SUKI, 5.0f, 2, 1.0f, 0);
                        fopAcM_monsSeStart(i_this, JA_SE_CV_MG_ATTACK, 0);
                    }
                }
            }
            break;
        case 1:
            if (player->getCutType() == 0x10) {
                if (dComIfGp_getAttention().Lockon() && i_this == dComIfGp_getAttention().LockonTarget(0)) {
                    i_this->mMode = 6;
                    i_this->mTimer[0] = 0;
                    anm_init(i_this, MT_BCK_ATTACK, 2.0f, 0, 1.0f, 0);
                    break;
                }
            }
            i_this->mC02++;
            if (i_this->mC02 >= l_HIO.m30 && i_this->mC02 <= l_HIO.m32) {
                i_this->setBtAttackData(0.0f, 20.0f, 10000.0f, fopEn_enemy_c::OPENING_VERTICAL_JUMP_PARRY);
                i_this->setBtMaxDis(l_HIO.m34);
                i_this->setBtNowFrame(10.0f);
            }
            if (i_this->mC02 == l_HIO.m3C) {
                anm_init(i_this, MT_BCK_TUKKOMI, 2.0f, 0, 1.0f, 0);
            }
            if (i_this->mC02 == l_HIO.m38) {
                cMtx_YrotS(*calc_mtx, i_this->m496);
                cMtx_XrotM(*calc_mtx, i_this->m494);
                local_5c.x = 0.0f;
                local_5c.y = REG6_F(6) + -100.0f;
                local_5c.z = REG6_F(7) + 200.0f;
                MtxPosition(&local_5c, &i_this->m47C);
                i_this->m47C += i_this->current.pos;
            }
            f32 fVar11;
            if (i_this->mC02 >= l_HIO.m38) {
                fVar11 = l_HIO.m2C;
                fVar1 = 0.5f;
                if (i_this->mC02 == l_HIO.m3E) {
                    anm_init(i_this, MT_BCK_ATTACK, 2.0f, 0, 1.0f, 0);
                }
            } else {
                fVar11 = REG0_F(11) + 4.0f;
                fVar1 = 0.1f;
            }

            if (i_this->mC02 == l_HIO.m3E + REG0_S(3)) {
                fopAcM_monsSeStart(i_this, JA_SE_CM_MAGTAIL_ATTACK, 0);
            }
            if (i_this->mC02 < l_HIO.m3E + 3 + REG6_S(7)) {
                i_this->mC04 = 1;
            }
            if (i_this->mC02 == l_HIO.m3E + 2) {
                i_this->br_frame = 1;
            }
            if (i_this->mC02 >= l_HIO.m3E + 2 && i_this->mC02 <= l_HIO.m3E + 15) {
                i_this->mC04 = 2;
            }

            cLib_addCalc2(&i_this->current.pos.x, i_this->m47C.x, fVar1, fVar11);
            cLib_addCalc2(&i_this->current.pos.y, i_this->m47C.y + 20.0f, fVar1, fVar11);
            cLib_addCalc2(&i_this->current.pos.z, i_this->m47C.z, fVar1, fVar11);

            i_this->speed.x = i_this->m47C.x - i_this->current.pos.x;
            i_this->speed.y = -1.0f;
            i_this->speed.z = i_this->m47C.z - i_this->current.pos.z;

            if (player->checkPlayerGuard() && i_this->mSph[0].ChkAtHit()) {
                i_this->mFightMode = 0xF;
                cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
                local_5c.x = 0.0f;
                local_5c.y = 80.0f;
                local_5c.z = -120.0f;
                MtxPosition(&local_5c, &i_this->m47C);
                i_this->m47C += i_this->current.pos;
                i_this->m462 = 10;
                i_this->mTimer[0] = 10;
                anm_init(i_this, MT_BCK_WAIT1, 2.0f, 2, 1.0f, 0);
                i_this->br_frame = 0;
            }
            if (i_this->mC02 == l_HIO.m3A) {
                i_this->mFightMode = 0;
                i_this->mTimer[0] = l_HIO.m10;
                anm_init(i_this, MT_BCK_WAIT1, 5.0f, 2, 1.0f, 0);
            }
            break;
        case 0xA:
            i_this->current.pos.y += i_this->speed.y;
            i_this->speed.y += i_this->gravity;
            if (i_this->speed.y < -100.0f) {
                i_this->speed.y = -100.0f;
            }
            if (i_this->mAcch.ChkGroundHit()) {
                i_this->mFightMode = 0;
            }
            break;
        case 0xF:
            cLib_addCalc2(&i_this->current.pos.x, i_this->m47C.x, 0.5f, 20.0f);
            cLib_addCalc2(&i_this->current.pos.y, i_this->m47C.y + 20.0f, 0.5f, 20.0f);
            cLib_addCalc2(&i_this->current.pos.z, i_this->m47C.z, 0.5f, 20.0f);
            i_this->speed.x = i_this->m47C.x - i_this->current.pos.x;
            i_this->speed.y = -1.0f;
            i_this->speed.z = i_this->m47C.z - i_this->current.pos.z;
            if (i_this->mTimer[0] == 0) {
                i_this->mFightMode = 0;
                i_this->mTimer[0] = l_HIO.m10;
                anm_init(i_this, MT_BCK_WAIT1, 2.0f, 2, 1.0f, 0);
            }
            break;
        case 0x11:
            if (i_this->mAcch.ChkGroundHit()) {
                i_this->mFightMode = 0x17;
                i_this->mTimer[0] = cM_rndF(50.0f) + 50.0f;
                i_this->m48E = i_this->mTimer[0];
            }
            goto switch_end;
        case 0x14:
            i_this->current.angle.x -= 0x500;
            cLib_addCalcAngleS2(&i_this->current.angle.y, cM_atan2s(i_this->speed.x, i_this->speed.z) + 0x8000, 2, 0x400);
            cLib_addCalc2(&i_this->m18F4, 0.9f, 1.0f, 0.1f);
            if (i_this->speed.y <= 1.0f) {
                if (i_this->m18F8 != 0) {
                    if (i_this->mAcch.ChkGroundHit()) {
                        i_this->m18F8 = 2;
                    }
                } else {
                    i_this->mSph[0].OffTgShield();
                    tex_anm_set(i_this, 1);
                    i_this->mMode = 2;
                    i_this->m466 = l_HIO.m54;
                    i_this->m478 = 0.0f;
                    i_this->m48A = 0;
                    i_this->m330 = 0.0f;
                    fVar11 = i_this->speed.z;
                    fVar1 = i_this->speed.x;
                    fVar2 = i_this->speed.y;
                    fVar11 = std::sqrtf(fVar1 * fVar1 + fVar11 * fVar11 + fVar2 * fVar2);
                    i_this->speedF = -fVar11;
                    i_this->mFightMode = 0;
                    fopAcM_SetMin(i_this, -100.0f, -100.0f, -100.0f);
                    fopAcM_SetMax(i_this, 100.0f, 100.0f, 100.0f);
                }
            }
            goto switch_end;
        case 0x17:
            i_this->speed.y = 0.0f;
            cLib_addCalcAngleS2(&i_this->current.angle.x, 0, 1, 0x400);
            i_this->speed.x *= 0.2f;
            i_this->speed.z *= 0.2f;
            if (i_this->mTimer[0] == 0) {
                i_this->mFightMode = 0xA;
            }
switch_end:
            i_this->m460 = 5;
            i_this->current.pos.x += i_this->speed.x;
            i_this->current.pos.y += i_this->speed.y;
            i_this->current.pos.z += i_this->speed.z;
            i_this->speed.y += i_this->gravity;
            if (i_this->speed.y < -100.0f) {
                i_this->speed.y = -100.0f;
            }
            break;
    }

    if (i_this->mMode < 2) {
        if (i_this->mFightMode < 0xA) {
            cLib_addCalcAngleS2(&i_this->current.angle.y, i_this->m496, 2, 0x400);
            local_68.y = i_this->current.pos.y - i_this->mAcch.GetGroundH();
            if (local_68.y > 250.0f) {
                i_this->mFightMode = 0xA;
            }
            cLib_addCalcAngleS2(&i_this->current.angle.x, i_this->m494 + sVar9, 4, 0x800);
        }
        cLib_addCalcAngleS2(&i_this->m468, 0, 1, 0x100);
    }
}

/* 00005088-00005A04       .text mt_move_maru__FP8mt_class */
void mt_move_maru(mt_class* i_this) {
    f32 fVar1;
    uint uVar7 = 0;
    cXyz out;
    cXyz offset;
    cXyz out2;

    i_this->mBlinkTimer = 3;
    switch (i_this->mFightMode) {
    case 0:
        if (i_this->mTimer[0] == 0) {
            i_this->mSph[0].OnCoSetBit();
        }
        i_this->shape_angle.x += (s16)(i_this->speedF * 200.0f);
        cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
        offset.x = 0.0f;
        offset.y = 0.0f;
        offset.z = i_this->speedF;
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
        fVar1 = i_this->speed.y;
        mt_bg_check(i_this);
        if (i_this->mAcch.ChkGroundHit()) {
            if (fVar1 < REG0_F(12) + -50.0f) {
                i_this->m18F8 = 2;
            }

            f32 target_speed = 0.0f;
            f32 fVar2 = 1.0f;

            dBgS_GndChk gndChk;

            cXyz local_f0 = i_this->current.pos;
            local_f0.y += 50.0f;
            gndChk.SetPos(&local_f0);
            f32 cur_gnd_y = dComIfG_Bgsp()->GroundCross(&gndChk);
            cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
            offset.set(0.0f, 50.0f, 5.0f);
            MtxPosition(&offset, &out2);
            cXyz ahead_gnd_pt = i_this->current.pos + out2;
            gndChk.SetPos(&ahead_gnd_pt);
            ahead_gnd_pt.y = dComIfG_Bgsp()->GroundCross(&gndChk);

            if (ahead_gnd_pt.y != -G_CM3D_F_INF) {
                if (ahead_gnd_pt.y < cur_gnd_y - 1.0f) {
                    target_speed = 5.0f;
                    fVar2 = 0.3f;
                } else if (ahead_gnd_pt.y > cur_gnd_y + 1.0f) {
                    target_speed = -5.0f;
                    fVar2 = 0.3f;
                }
            }

            cLib_addCalc2(&i_this->speedF, target_speed, 1.0f, l_HIO.m5C * fVar2);
            if (fVar1 < REG0_F(14) + -15.0f) {
                i_this->speed.y = fVar1 * (REG0_F(15) + -0.4f);
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
            i_this->mFightMode = 1;
        }
        break;
    case 1:
        i_this->mSph[0].OffCoSetBit();
        i_this->current.angle.x = 0;
        i_this->current.angle.y = i_this->shape_angle.y;
        i_this->current.angle.z = i_this->shape_angle.z;
        if (!fopAcM_checkCarryNow(i_this)) {
            if (fopAcM_GetSpeedF(i_this) > 0) {
                i_this->mFightMode = 0;
                i_this->speedF = l_HIO.m58 * 20.0f;
                i_this->speed.y = l_HIO.m58 * 20.0f;
                i_this->mTimer[0] = 20;
            } else {
                i_this->mFightMode = 0;
                i_this->speedF = 0.0f;
                i_this->speed.y = REG0_F(11) + -15.0f;
                i_this->mTimer[0] = 20;
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
                target -= 1500;
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
            if (!i_this->mInLava) {
                i_this->speed.y = REG0_F(11) + 30.0f;
            }
        }
        cLib_addCalc0(&i_this->m330, 1.0f, 125.0f);
        cLib_addCalcAngleS2(&i_this->m468, i_this->m330 * cM_ssin(i_this->m466 * (REG0_S(5) + 5000)) * 5.0f, 2, 0x1000);
        cLib_addCalcAngleS2(&i_this->shape_angle.x, 0, 4, 0x1000);
        cLib_addCalc2(&i_this->m474, -0.4f, 1.0f, 0.2f);
        cLib_addCalcAngleS2(&i_this->m48A, (REG0_F(14) + 4.0f) * (i_this->m330 * cM_ssin(i_this->m466 * (REG0_S(5) + 5000))), 1, 0x1000);
        i_this->current.angle.x = i_this->shape_angle.x;
        i_this->shape_angle.y = i_this->current.angle.y + i_this->m468;
        cLib_addCalc0(&i_this->speedF, 1.0f, 0.5f);
    }

    if (i_this->m466 == 100) {
        i_this->m2E4 = 2;
    }
    if (i_this->m348 != 0) {
        if (i_this->m348 == 1) {
            i_this->mpEmitter = dComIfGp_particle_setToon(
                dPa_name::ID_SCENE_8095,
                &i_this->current.pos, &i_this->current.angle,
                NULL, 0xB4, NULL,
                (s8)fopAcM_GetRoomNo(i_this)
            );
            if (i_this->mpEmitter != NULL) {
                i_this->mpEmitter->becomeImmortalEmitter();
            }
            i_this->m348 = 2;
            i_this->m34A = 80;
        }

        if (i_this->mpEmitter != NULL) {
            MtxTrans(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z, false);
            cMtx_YrotM(*calc_mtx, i_this->shape_angle.y);
            i_this->mpEmitter->setGlobalRTMatrix(*calc_mtx);
            if (i_this->m34A == 0) {
                i_this->mpEmitter->quitImmortalEmitter();
                i_this->mpEmitter->becomeInvalidEmitter();
                i_this->mpEmitter = NULL;
                i_this->m348 = 0;
            } else {
                u8 uVar4 = 180;
                if (i_this->m34A < 30) {
                    uVar4 = i_this->m34A * 6;
                }
                i_this->mpEmitter->setGlobalAlpha(uVar4);
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
    fopAc_ac_c* actor = i_this;
    CcAtInfo atInfo;
    atInfo.pParticlePos = NULL;

    u8 iVar4 = 0;
    int startI = 0;
    i_this->mStts.Move();
    if (i_this->mC04 == 1) {
        startI = 2;
    }

    cXyz pos;
    for (int i = startI; i < 8; i++) {
        if (i_this->mSph[i].ChkTgHit() && i_this->m460 == 0) {
            atInfo.mpObj = i_this->mSph[i].GetTgHitObj();
            if (atInfo.mpObj->ChkAtType(AT_TYPE_LIGHT_ARROW)) {
                i_this->m1CBC = 1;
                i_this->mEnemyIce.mLightShrinkTimer = 1;
                i_this->mEnemyIce.mYOffset = REG0_F(0) + -20.0f;
                actor->health = 0;
                return;
            }
            at_power_check(&atInfo);
            if (atInfo.mResultingAttackType == 4 || atInfo.mpObj->ChkAtType(AT_TYPE_ICE_ARROW)) {
                iVar4 = 2;
                i_this->m18FB = 0;
                i_this->m460 = 5;
                water_damage_se_set(i_this);
            } else {
                if (i_this->mMode == 2 && (atInfo.mResultingAttackType == 6 || atInfo.mResultingAttackType == 2)) {
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
                    if (atInfo.mResultingAttackType != 6 && i_this->mMode == 1) {
                        i_this->mFightMode = 0xF;
                        cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
                        pos.set(0.0f, 60.0f, -120.0f);
                        MtxPosition(&pos, &i_this->m47C);
                        i_this->m47C += actor->current.pos;
                        i_this->m462 = REG6_S(7) + 6;
                        i_this->mTimer[0] = REG6_S(8) + 6;
                        i_this->m460 = 5;
                        def_se_set(actor, atInfo.mpObj, 0x40);
                        return;
                    }
                    if (i_this->mMode == 2) {
                        i_this->m460 = 5;
                        cc_at_check(actor, &atInfo);
                        if (actor->health <= 0) {
                            i_this->m18F8 = 2;
                        }
                        i_this->m18FC = 12;
                        dComIfGp_particle_set(dPa_name::ID_SCENE_80CF, &actor->current.pos);
                    }
                }
            }
            break;
        }
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
        atInfo.mpActor = cc_at_check(actor, &atInfo);
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
            i_this->mFightMode = 0xF;
            cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
            pos.set(0.0f, 60.0f, -120.0f);
            MtxPosition(&pos, &i_this->m47C);
            i_this->m47C += actor->current.pos;
            i_this->m462 = 25;
            i_this->mTimer[0] = 10;
            actor->current.angle.x = -0x4000;
        }
        fopAcM_monsSeStart(actor, JA_SE_CV_MG_DAMAGE, 0);
        anm_init(i_this, MT_BCK_WAIT1, 2.0f, 2, 1.0f, 0);
        i_this->br_frame = 0;
    }
    if (iVar4 != 0) {
        cMtx_YrotS(*calc_mtx, atInfo.m0C.y);
        cXyz pos(0.0f, l_HIO.m4C * 40.0f, l_HIO.m4C * -20.0f);
        MtxPosition(&pos, &actor->speed);
        if (iVar4 == 2) {
            actor->speed.y = 0.0f;
        }
        i_this->mMode = 1;
        i_this->mFightMode = 0x14;
        i_this->m2E4 = 1;
    }
}

/* 00006188-000074D4       .text daMt_Execute__FP8mt_class */
static BOOL daMt_Execute(mt_class* i_this) {
    CcAtInfo atInfo;

    daPy_py_c* player = daPy_getPlayerActorClass();

    if (enemy_ice(&i_this->mEnemyIce)) {
        return TRUE;
    }

    if (i_this->m2BB != 0) {
        if (dComIfGs_isSwitch(i_this->m2BB - 1, fopAcM_GetRoomNo(i_this))) {
            i_this->m2BB = 0;
        } else {
            return TRUE;
        }
    }

    fopAcM_OnStatus(i_this, fopAcStts_SHOWMAP_e);
    dBgS_ObjGndChk_Yogan lavaChk;
    cXyz pos(i_this->current.pos.x, i_this->current.pos.y + 200.0f, i_this->current.pos.z);
    lavaChk.SetPos(&pos);
    f32 lavaY = dComIfG_Bgsp()->GroundCross(&lavaChk);
    if (lavaY != -G_CM3D_F_INF && i_this->current.pos.y - 30.0f + REG0_F(13) < lavaY) {
        if (!i_this->mInLava) {
            i_this->speedF *= 0.1f;
            i_this->speed.y = 0.0f;
            cXyz pos(i_this->current.pos.x, lavaY, i_this->current.pos.z);
            fopKyM_createMpillar(&pos, 0.5);
        }
        i_this->mInLava = true;
        i_this->gravity = -0.5f;
        if (i_this->speed.y < -5.0f) {
            i_this->speed.y = -5.0f;
        }
    } else {
        i_this->mInLava = false;
        i_this->gravity = -3.0f;
    }
    i_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    mt_eye_tex_anm(i_this);
    if (l_HIO.m04 == 0) {
        if (i_this->br_frame != 0) {
            if (++i_this->br_frame == 11) {
                i_this->br_frame = 0;
            }
        }
        i_this->setBtAttackData(100.0f, 100.0f, 10000.0f, fopEn_enemy_c::OPENING_NONE);
        i_this->setBtNowFrame(0.0f);
        for (int i = 0; i < 5; i++) {
            if (i_this->mTimer[i] != 0) {
                i_this->mTimer[i]--;
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
        if (i_this->mMode > 3) {
            damage_check(i_this);
        }
        i_this->mC04 = 0;
        dBgS_LinChk linChk;

        cXyz end = player->current.pos;
        end.y += 20.0f;
        cXyz start = i_this->current.pos;
        start.y += 30.0f;
        linChk.Set(&start, &end, i_this);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            i_this->mBlocked = true;
        } else {
            i_this->mBlocked = false;
        }

        f32 f;
        dCcD_Stts* stts;
        switch (i_this->mMode) {
            case 0:
                mt_move(i_this);
                cLib_addCalcAngleS2(&i_this->shape_angle.x, i_this->current.angle.x, 2, 0x800);
                cLib_addCalcAngleS2(&i_this->shape_angle.y, i_this->current.angle.y, 2, 0x800);
                cLib_addCalcAngleS2(&i_this->shape_angle.z, i_this->current.angle.z, 4, 0x400);
                body_control1(i_this);
                stts = &i_this->mStts;
                if (stts != NULL) {
                    i_this->current.pos.x += stts->GetCCMoveP()->x;
                    i_this->current.pos.z += stts->GetCCMoveP()->z;
                    for (int i = 0; i < 64; i++) {
                        i_this->m6F4[i].x += stts->GetCCMoveP()->x;
                        i_this->m6F4[i].z += stts->GetCCMoveP()->z;
                    }
                }
                if (i_this->mTimer[1] == 0) {
                    i_this->mTimer[1] = cM_rndF(100.0f) + 150.0f;
                    if (l_HIO.m05 == 0 && abs(i_this->current.angle.x) < 0x1000) {
                        i_this->m48E = cM_rndF(50.0f) + 50.0f + REG0_F(8);
                    }
                }
                break;
            case 1:
                mt_fight(i_this);
                f = i_this->m462 * (REG0_F(14) + 500.0f);
                i_this->m49A.y = f * cM_ssin(i_this->m46A * 0x2100);
                i_this->m49A.x = f * cM_scos(i_this->m46A * 0x2300);
                i_this->shape_angle = i_this->current.angle + i_this->m49A;
                body_control2(i_this);
                body_wall_check(i_this);
                mt_bg_check(i_this);
                stts = &i_this->mStts;
                if (stts != NULL) {
                    i_this->current.pos.x += stts->GetCCMoveP()->x;
                    i_this->current.pos.z += stts->GetCCMoveP()->z;
                }
                break;
            case 2:
                mt_move_maru(i_this);
                body_control3(i_this);
                if (i_this->m466 <= 100) {
                    body_wall_check(i_this);
                } else if (i_this->mInLava && i_this->m466 > 50) {
                    i_this->m466 = 71;
                }
                stts = &i_this->mStts;
                if (stts != NULL) {
                    i_this->current.pos.x += stts->GetCCMoveP()->x;
                    i_this->current.pos.z += stts->GetCCMoveP()->z;
                }
                if (i_this->m466 == 50) {
                    i_this->m2E4 = 0;
                    i_this->mMode = 1;
                    i_this->mFightMode = 0;
                    i_this->m18FB = 2;
                    i_this->health = 8;
                    i_this->mSph[0].OnTgShield();
                    i_this->mTimer[0] = l_HIO.m10;
                    i_this->m48E = 0;
                    anm_init(i_this, MT_BCK_WAIT1, 20.0f, 2, 1.0f, 0);
                    fopAcM_SetMin(i_this, -200.0f, -200.0f, -200.0f);
                    fopAcM_SetMax(i_this, 200.0f, 200.0f, 200.0f);
                    i_this->mSph[0].OffAtSPrmBit(cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e);
                    i_this->mSph[0].OnAtVsPlayerBit();
                }
                break;
            case 3:
                i_this->m460 = 5;
                i_this->attention_info.flags = 0;
                body_control4(i_this);
                if (i_this->mTimer[2] == 1) {
                    i_this->m1CBC = 1;
                    fopAcM_delete(i_this);
                    fopAcM_onActor(i_this);
                }
                break;
            case 6:
                if (player->getCutType() == 0x10) {
                    cMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
                    cXyz pos(0.0f, 0.0f, REG0_F(14) + -50.0f);
                    cXyz pos2;
                    MtxPosition(&pos, &pos2);
                    cLib_addCalc2(&i_this->current.pos.x, player->current.pos.x + pos2.x, 0.5f, 50.0f);
                    cLib_addCalc2(&i_this->current.pos.z, player->current.pos.z + pos2.z, 0.5f, 50.0f);
                }
                i_this->mBlinkTimer = 3;
                i_this->m2E4 = 1;
                i_this->m460 = 5;
                body_control5(i_this);
                i_this->current.pos.y += i_this->speed.y;
                i_this->speed.y += i_this->gravity;
                mt_bg_check(i_this);
                if (i_this->mTimer[0] == 0) {
                    if (player->getCutType() != 0x10) {
                        i_this->m2E4 = 0;
                        i_this->mMode = 1;
                        i_this->mFightMode = 0;
                        i_this->mSph[0].OnTgShield();
                        i_this->mTimer[0] = l_HIO.m10;
                        i_this->m48E = 0;
                        anm_init(i_this, MT_BCK_WAIT1, 20.0f, 2, 1.0f, 0);
                        i_this->mSph[0].OffAtSPrmBit(cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e);
                        i_this->mSph[0].OnAtVsPlayerBit();
                    } else {
                        i_this->m474 = REG0_F(13) + 0.2f;
                        if (i_this->mEyeSph.ChkTgHit()) {
                            i_this->health = 0;
                            i_this->mTimer[0] = REG0_S(3) + 40;
                            i_this->m474 = REG0_F(13) + 1.5f;
                            fopAcM_seStart(i_this, JA_SE_LK_LAST_HIT, 0);
                            fopAcM_monsSeStart(i_this, JA_SE_CV_MG_DAMAGE, 0);
                            atInfo.mpObj = i_this->mEyeSph.GetTgHitObj();
                            at_power_check(&atInfo);
                            mDoAud_onEnemyDamage();
                            mDoAud_bgmHitSound(atInfo.mHitSoundId);
                            dScnPly_ply_c::setPauseTimer(REG0_S(7) + 6);
                            dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &i_this->current.pos);
                            cXyz scale;
                            scale.z = 2.0f;
                            scale.y = 2.0f;
                            scale.x = 2.0f;
                            csXyz angle;
                            angle.z = 0;
                            angle.x = 0;
                            angle.y = fopAcM_searchPlayerAngleY(i_this);
                            dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &i_this->current.pos, &angle, &scale);
                            dKy_SordFlush_set(i_this->current.pos, 1);
                            anm_init(i_this, MT_BCK_SUKI, 5.0f, 0, 1.0f, 0);
                        }
                    }
                } else {
                    i_this->m46E = 0;
                    cLib_addCalc0(&i_this->m474, 0.05f, REG0_F(12) + 0.02f);
                    if (i_this->mTimer[0] == 1) {
                        bakuha(i_this);
                    }
                }
        }
        if (i_this->m466 > 60) {
            cLib_addCalc0(&i_this->m18F0, 1.0f, 0.05f);
        } else {
            cLib_addCalc2(&i_this->m18F0, 1.0f, 1.0f, 0.1f);
        }
    }

    // Fakematch? these linChks get deconstructed so they need to go out of scope
    {
        dBgS_ObjLinChk linChk;
        cXyz start = i_this->old.pos;
        cXyz end = start;
        end.y += 40.0f;
        linChk.Set(&start, &end, i_this);

        cXyz end2;
        f32 h = 40.0f;
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            h = linChk.GetCrossP()->y - 1 - i_this->old.pos.y;
            if (h < 0.0f) {
                h = 0.0f;
            }
        }
        cXyz start2 = i_this->old.pos;
        start2.y += h;
        end2 = i_this->current.pos;
        end2.y += h;

        dBgS_ObjLinChk linChk2;
        linChk2.Set(&start2, &end2, i_this);
        bool cross2 = dComIfG_Bgsp()->LineCross(&linChk2);
        dBgS_ObjLinChk linChk3;
        linChk3.Set(&end2, &start2, i_this);
        bool cross3 = dComIfG_Bgsp()->LineCross(&linChk3);
        if (cross2 && !cross3) {
            i_this->current.pos = *linChk2.GetCrossP();
            cXyz* norm = &dComIfG_Bgsp()->GetTriPla(linChk2)->mNormal;
            i_this->current.pos.x += norm->x;
            i_this->current.pos.y += norm->y;
            i_this->current.pos.z += norm->z;
        }
    }

    i_this->attention_info.position = i_this->eyePos;

    int step = 1;
    int brk_start_frame;
    int brk_end_frame;
    int btk_end_frame;
    switch (i_this->m2E4) {
        case 0:
            brk_start_frame = 0;
            brk_end_frame = 40;
            btk_end_frame = 30;
            break;
        case 1:
            brk_start_frame = 40;
            brk_end_frame = 100;
            btk_end_frame = 90;
            step = 2;
            break;
        case 2:
            brk_start_frame = 100;
            brk_end_frame = 130;
            btk_end_frame = 120;
            break;
    }

    i_this->mBrkFrame += step;
    if (i_this->mBrkFrame > brk_end_frame) {
        if (i_this->m2E4 == 0) {
            i_this->mBrkFrame = brk_start_frame;
        } else {
            i_this->mBrkFrame = brk_end_frame;
        }
    }
    i_this->mBtkFrame += step;
    if (i_this->mBtkFrame > btk_end_frame) {
        if (i_this->m2E4 == 0) {
            i_this->mBtkFrame = 0;
        } else {
            i_this->mBtkFrame = btk_end_frame;
        }
    }

    if (i_this->mMode < 2 || i_this->m466 <= 120) {
        if (i_this->m466 == 120) {
            i_this->m490 = 15;
        }
        i_this->mpMorf[0]->play(&i_this->current.pos, 0, 0);
        i_this->m46E += l_HIO.m08;
        for (int i = 0; i < 30; i++) {
            int iVar4 = i;
            if (i >= 15) {
                iVar4 = i - 15;
            }
            s16 sVar2;
            if (i_this->m48E != 0) {
                if (iVar4 >= i_this->m490) {
                    sVar2 = i_this->m46E;
                } else {
                    sVar2 = 0;
                }
            } else {
                if (14 - iVar4 >= i_this->m490) {
                    sVar2 = i_this->m46E;
                } else {
                    sVar2 = 0;
                }
            }

            iVar4 = (REG6_F(11) + 5000.0f) * -cM_ssin(sVar2 + i * (REG6_S(2) + 13000));
            i_this->m640[i].x = iVar4;
            iVar4 = l_HIO.m0C + (REG6_F(12) + 5000.0f) * cM_scos(sVar2 + i * (REG6_S(3) + 13000));
            cLib_addCalcAngleS2(&i_this->m640[i].z, iVar4, 1, i_this->m334);
        }

        cLib_addCalcAngleS2(&i_this->m334, 0x2000, 1, 0x100);

        for (int i = 0; i < 8; i++) {
            i_this->m620[i] = i_this->m338 * cM_ssin(i_this->m46A * (REG0_S(5) + 0x9C4) + i * (REG0_S(6) + 0x1D4C)) + 1.0f;
        }
        cLib_addCalc2(&i_this->m338, 0.1f, 1.0f, 0.002f);
    } else {
        i_this->m334 = 0;
        for (int i = 0; i < 30; i++) {
            i_this->m640[i].x = 0;
            cLib_addCalcAngleS2(&i_this->m640[i].z, 10000, 10, 300);
        }
    }

    if ((i_this->m2B4 & 1) == 0) {
        for (int i = 0; i < 8; i++) {
            J3DModel* model = i_this->mpMorf[i]->getModel();
            cXyz local_300(REG0_F(5), REG0_F(6), REG0_F(7));
            MTXMultVec(model->getBaseTRMtx(), &local_300, &i_this->m350[i]);
            if ((i_this->mMode >= 2 && i_this->m466 > 40) || i_this->mMode == 6 || l_HIO.m07 != 0) {
                i_this->m350[i].y += 10000.0f;
            }
            if (i >= 0 && i <= 6) {
                dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8058, &i_this->m350[i], 0xFF, g_whiteColor, g_whiteColor);
            }
            if (i >= 1 && i <= 6) {
                dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8059, &i_this->m350[i], 0xFF, g_whiteColor, g_whiteColor);
            }
            if (!i_this->m34C && (i == 1 || i == 3 || i == 5)) {
                dComIfGp_particle_setProjection(dPa_name::ID_SCENE_C06C, &i_this->m350[i], NULL, NULL, 0xFF, &i_this->mPtclCallback[i]);
            }
        }
        i_this->m34C = true;
    }

    if (i_this->mMode < 2 && !i_this->mInLava && i_this->m48E == 0) {
        if (i_this->mTimer[3] == 0) {
            i_this->mTimer[3] = cM_rndF(45.0f) + 45.0f;
            fopAcM_monsSeStart(i_this, JA_SE_CV_MG_NORMAL, 0);
        }
        if (i_this->mTimer[4] == 0) {
            i_this->mTimer[4] = cM_rndF(3.0f) + 6.0f;
            fopAcM_monsSeStart(i_this, JA_SE_CM_MAGTAIL_MOVE, 0);
        }
    }

    if (i_this->m18F8 >= 2) {
        bakuha(i_this);
        i_this->m18F8 = -1;
    }

    return TRUE;
}

/* 00007CC4-00007CCC       .text daMt_IsDelete__FP8mt_class */
static BOOL daMt_IsDelete(mt_class* i_this) {
    return TRUE;
}

/* 00007CCC-00007E18       .text daMt_Delete__FP8mt_class */
static BOOL daMt_Delete(mt_class* i_this) {
    dComIfG_resDelete(&i_this->mPhs, "Mt");
#if VERSION == VERSION_DEMO
    l_HIO.removeHIO();
#else
    if (i_this->mpEmitter != NULL) {
        i_this->mpEmitter->quitImmortalEmitter();
        i_this->mpEmitter->becomeInvalidEmitter();
        i_this->mpEmitter = NULL;
    }
#endif
    for (int i = 0; i < 8; i++) {
        i_this->mPtclCallback[i].remove();
    }
    if (i_this->m1CBC != 0 && i_this->m2B6 && i_this->m2BA != 0 && !dComIfGs_isSwitch(i_this->m2BA, fopAcM_GetRoomNo(i_this))) {
        fopAcM_prm_class* params = fopAcM_CreateAppend();
        params->base.position = i_this->home.pos;
        params->base.angle = i_this->home.angle;
        params->base.parameters = fopAcM_GetParam(i_this);
        params->room_no = fopAcM_GetRoomNo(i_this);
        fopAcM_create(PROC_MT, NULL, params);
    }
    return TRUE;
}

static int bmd_data[8] = {
    MT_BDL_MG_HEAD, MT_BDL_MG_BODY, MT_BDL_MG_BODY, MT_BDL_MG_BODY,
    MT_BDL_MG_BODY, MT_BDL_MG_BODY, MT_BDL_MG_BODY, MT_BDL_MG_TAIL
};

static f32 scale_data[8] = {
    1.0f, 1.0f, 1.0f, 0.975f, 0.925f, 0.825f, 0.75f, 0.525f
};

static int br_bmd[3] = {
    MT_BDL_KBA, MT_BDL_KBB, MT_BDL_KBC
};

// static int bmd_data[8] = {
//     MT_BDL_MG_HEAD, MT_BDL_MG_BODY, MT_BDL_MG_BODY, MT_BDL_MG_BODY,
//     MT_BDL_MG_BODY, MT_BDL_MG_BODY, MT_BDL_MG_BODY, MT_BDL_MG_TAIL
// };

// static f32 scale_data[8] = {
//     1.0f, 1.0f, 1.0f, 0.975f, 0.925f, 0.825f, 0.75f, 0.525f
// };

// static int br_bmd[3] = {
//     MT_BDL_KBA, MT_BDL_KBB, MT_BDL_KBC
// };

/* 00007E18-00008400       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* i_ac) {
    mt_class* actor = (mt_class*) i_ac;
    for (int i = 0; i < 8; i++) {
        actor->mpMorf[i] = new mDoExt_McaMorf(
            (J3DModelData*) dComIfG_getObjectRes("Mt", bmd_data[i]),
            NULL, NULL, NULL,
            J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
            0x800000, 0x37440402
        );
        if (actor->mpMorf[i] == NULL || actor->mpMorf[i]->getModel() == NULL) {
            return FALSE;
        }

        J3DModel* model = actor->mpMorf[i]->getModel();
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
            anm_init(actor, 10, 20.0f, 2, 1.0f, 0);
            J3DAnmTexPattern* pat;
            for (int j = 0; j < 2; j++) {
                pat = (J3DAnmTexPattern*) dComIfG_getObjectRes("Mt", mt_tex_anm_idx[j]);
                pat->searchUpdateMaterialID(modelData);
            }
            actor->mpTexNoAnm = new J3DTexNoAnm[pat->getUpdateMaterialNum()];
            for (u16 j = 0; j < pat->getUpdateMaterialNum(); j++) {
                actor->mpTexNoAnm[j].setAnmIndex(j);
            }
            tex_anm_set(actor, 0);
        }

        model->setUserArea((u32) actor);
        for (u16 jntNo = 0; jntNo < modelData->getJointNum(); jntNo++) {
            if (i == 0) {
                if (jntNo >= 2 && jntNo <= 5) {
                    modelData->getJointNodePointer(jntNo)->setCallBack(nodeCallBack_head);
                }
            } else if (i == 7) {
                if (jntNo >= 2 && jntNo <= 5) {
                    modelData->getJointNodePointer(jntNo)->setCallBack(nodeCallBack_tail);
                }
            } else {
                if (jntNo >= 2 && jntNo <= 5) {
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

const char* unused[4] = {
    "i_this->btk[i]",
    "i_this->brk[i]",
    "i_this->br_modelL[i] != 0",
    "i_this->br_modelR[i] != 0"
};

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
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 30.0f,
        }},
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

        if (!i_this->m2B6) {
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
            i_this->mPathDir = 1;
            i_this->m47C = i_this->mpPath->m_points[0].m_position; // TODO might not be a cXyz assignment
        }
        if (i_this->m2B8 != 0xFF) {
            i_this->m2BB = i_this->m2B8 + 1;
        }
        fopAcM_SetMtx(i_this, i_this->mpMorf[1]->getModel()->getBaseTRMtx());
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
