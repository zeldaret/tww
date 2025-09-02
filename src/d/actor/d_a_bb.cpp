/**
 * d_a_bb.cpp
 * Enemy - Kargaroc
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bb.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/res/res_bb.h"
#include "d/d_kankyo.h"
#include "f_op/f_op_kankyo_mng.h"
#include "d/d_snap.h"
#include "d/d_material.h"
#include "d/actor/d_a_esa.h"
#include "d/actor/d_a_sea.h"
#include "d/actor/d_a_mo2.h"
#include "d/actor/d_a_bk.h"
#include "d/actor/d_a_player.h"
#if VERSION == VERSION_DEMO
#include "m_Do/m_Do_controller_pad.h"
#endif
#include "d/d_bg_s_lin_chk.h"
#include "d/d_cc_uty.h"
#include "SSystem/SComponent/c_lib.h"

class bbHIO_c : public mDoHIO_entry_c {
public:
    bbHIO_c() {
        unk_04 = 0;
        unk_05 = 0;
#if VERSION == VERSION_DEMO
        unk_10 = 0x3228;
#endif
        unk_08 = 20.0f;
        unk_0C = 2500.0f;
        unk_12 = 0x258;
        unk_14 = 0x4B0;
        unk_16 = 0x1C2;
        unk_18 = 0x2EE;
        unk_1C = 0.35f;
        unk_20 = 0.5f;
        unk_24 = 1.5f;
        unk_28 = 1.0f;
        unk_2C = 0.85f;
        unk_38 = 0.85f;
        unk_3C = 1.0f;
        unk_40 = 30;
        unk_44 = 1.0f;
        unk_48 = 1.0f;
        unk_4C = 1.5f;
        unk_50 = 0x44C;
        unk_54 = 3.5f;
        unk_32 = 20;
        unk_30 = 0x2D;
        unk_34 = 2.5f;
        unk_58 = 45.0f;
        unk_5C = 30.0f;
        unk_60 = 2;
        unk_62 = 2;
        unk_64 = 1;
        unk_68 = 8000.0f;
        unk_74 = 3000.0f;
        unk_70 = 0x6D60;
        unk_6C = 1500.0f;
        unk_78 = 2000.0f;
        unk_72 = 0x59D8;
        unk_7C = 10000.0f;
    }
    virtual ~bbHIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ s16 unk_32;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ s16 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ f32 unk_4C;
    /* 0x50 */ s16 unk_50;
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ f32 unk_58;
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ s16 unk_60;
    /* 0x62 */ s16 unk_62;
    /* 0x64 */ s16 unk_64;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ s16 unk_70;
    /* 0x72 */ s16 unk_72;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ f32 unk_78;
    /* 0x7C */ f32 unk_7C;
}; // size = 0x80

static s8 callback_check_index[] = {0xFF, 0xFF, 0xFF, 0x64, 0xFF, 0xFF, 0xFF, 0xFF, 0x64, 0xFF, 0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x64, 0x64, 0x64, 0xFF, 0xFF, 0xFF, 0xFF, 0x64, 0x64};
static f32 tial_scale[] = {
    0.25f, 0.275f, 0.2875f, 0.3f, 0.325f, 0.375f, 0.4625f, 0.575f, 0.8f, 
};
static u16 bb_tex_anm_idx[] = {
    BB_BTP_TATACK, BB_BTP_TCLOSE, BB_BTP_TDAMAGE, BB_BTP_TKAIJO, BB_BTP_TMABATAKI, BB_BTP_TOPEN,
};
static u16 bb_tex_max_frame[] = {
    5, 3, 40, 5, 7, 3,
};

static bbHIO_c l_bbHIO;
static esa_class* esa_info[100];
static s32 esa_check_count;

/* 000000EC-000003C8       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    s32 idx;
    s32 jntNo;
    J3DModel* model;
    bb_class* i_this;
    
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        jntNo = joint->getJntNo();
        idx = callback_check_index[jntNo];
        model = j3dSys.getModel();
        i_this = (bb_class*)model->getUserArea();

        if (i_this) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            
            if (idx >= 0 && idx <= 10) {
                cMtx_YrotM(*calc_mtx, i_this->unk_C00[idx].y);
                cMtx_XrotM(*calc_mtx, i_this->unk_C00[idx].x);
                cMtx_ZrotM(*calc_mtx, i_this->unk_C00[idx].z);
                model->setAnmMtx(jntNo, *calc_mtx);
            }

            cXyz v;
            if (jntNo == 0x16) {
                v.x = 0.0f;
                v.z = 0.0f;
                v.y = 0.0f;
                MtxPosition(&v, &i_this->actor.eyePos);
                i_this->actor.attention_info.position = i_this->actor.eyePos;
                i_this->actor.attention_info.position.y += REG0_F(8) * 10.0f + 50.0f;
            } else if (jntNo == 0x1D || jntNo == 0x1E) {
                if (jntNo == 0x1E) {
                    v.x = REG0_F(10) * 10.0f + 10.0f;
                    v.y = REG0_F(11) * 10.0f;
                    v.z = REG0_F(12) * 10.0f;
                } else {
                    v.x = 0.0f;
                    v.z = 0.0f;
                    v.y = 0.0f;
                }

                MtxPosition(&v, &i_this->unk_BD4[jntNo - 0x1D]);
            } else if (jntNo == 0x3 || jntNo == 0x8) {
                v.x = REG0_F(10) * 10.0f + 5.0f;
                v.y = REG0_F(11) * 10.0f;
                v.z = REG0_F(12) * 10.0f;

                if (jntNo == 0x3) {
                    MtxPosition(&v, &i_this->unk_A6C[0]);
                } else {
                    MtxPosition(&v, &i_this->unk_A6C[1]);
                }
            } else if (jntNo == 0x17) {
                cMtx_ZrotM(*calc_mtx, -i_this->unk_C4E);
                model->setAnmMtx(jntNo, *calc_mtx);
            } else if (jntNo == 0x18) {
                cMtx_YrotM(*calc_mtx, i_this->unk_C4E);
                model->setAnmMtx(jntNo, *calc_mtx);
            }
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }

    return TRUE;
}

/* 00000404-000009A4       .text tail_control__FP8bb_class */
void tail_control(bb_class* i_this) {
    s32 i;
    cXyz sp28;
    cXyz sp1C;
    f32 x = i_this->unk_BD4[1].x - i_this->unk_BD4[0].x;
    f32 y = i_this->unk_BD4[1].y - i_this->unk_BD4[0].y;
    f32 z = i_this->unk_BD4[1].z - i_this->unk_BD4[0].z;
    s16 atan2;
    s32 atan;

    i_this->unk_BEE = cM_atan2s(x, z);
    i_this->unk_BEC = -cM_atan2s(y, std::sqrtf(x * x + z * z));

    sp28.x = 0.0f;
    sp28.y = 0.0f;
    sp28.z = REG0_F(5) + 5.0f;
    
    cMtx_YrotS(*calc_mtx, i_this->unk_BEE);
    cMtx_XrotM(*calc_mtx, i_this->unk_BEC);
    MtxPosition(&sp28, &i_this->unk_BF4);

    cXyz* AA8 = &i_this->unk_AA8[1];
    csXyz* B20 = &i_this->unk_B20[1];
    cXyz* B5C = &i_this->unk_B5C[1];
    
    f32 reg2 = REG0_F(2) + 0.8f;
    f32 reg3 = REG0_F(3);
    f32 groundY = i_this->mAcch.GetGroundH() + 5.0f;

    for (i = 1; i < 10; i++, AA8++, B20++, B5C++) {
        f32 tmp = 1.0f - (i - 1) * (REG0_F(4) + 0.1f);
        cXyz sp10;
        
        sp10.x = B5C->x + i_this->unk_BF4.x * tmp;
        sp10.y = B5C->y + i_this->unk_BF4.y * tmp;
        sp10.z = B5C->z + i_this->unk_BF4.z * tmp;

        if (reg3 > 1.0f) {
            sp28.x = reg3 * cM_ssin(i_this->unk_352 * (REG0_S(5) + 1200) + (i * (REG0_S(6) + 6000)));
            sp28.y = reg3 * cM_ssin(i_this->unk_352 * (REG0_S(5) + 1000) + (i * (REG0_S(6) + 5000)));
            sp28.z = 0.0f;

            cMtx_YrotS(*calc_mtx, i_this->unk_BEE);
            cMtx_XrotM(*calc_mtx, i_this->unk_BEC);
            MtxPosition(&sp28, &sp1C);

            sp10.x += sp1C.x;
            sp10.y += sp1C.y;
            sp10.z += sp1C.z;
        }

        f32 gY = AA8->y + sp10.y;
        if (gY < groundY) {
            gY = groundY;
        }
        y = gY - (AA8 - 1)->y;
        x = sp10.x + (AA8->x - (AA8 - 1)->x);
        z = sp10.z + (AA8->z - (AA8 - 1)->z);

        atan = cM_atan2s(x, z);
        atan2 = -cM_atan2s(y, std::sqrtf(x * x + z * z));

        (B20 - 1)->y = atan;
        (B20 - 1)->x = atan2;

        sp28.x = 0.0f;
        sp28.y = 0.0f;
        sp28.z = (i * 0.03f + 0.25f) * 20.0f * 2.0f;

        cMtx_YrotS(*calc_mtx, atan);
        cMtx_XrotM(*calc_mtx, atan2);
        MtxPosition(&sp28, &sp1C);

        B5C->x = AA8->x;
        B5C->y = AA8->y;
        B5C->z = AA8->z;

        AA8->x = (AA8 - 1)->x + sp1C.x;
        AA8->y = (AA8 - 1)->y + sp1C.y;
        AA8->z = (AA8 - 1)->z + sp1C.z;

        B5C->x = reg2 * (AA8->x - B5C->x);
        B5C->y = reg2 * (AA8->y - B5C->y);
        B5C->z = reg2 * (AA8->z - B5C->z);
    }
}

/* 000009A4-00000A94       .text tail_draw__FP8bb_class */
void tail_draw(bb_class* i_this) {
    cXyz* AA8 = &i_this->unk_AA8[0];
    csXyz* B20 = &i_this->unk_B20[0];

    for (s32 i = 0; i < 9; AA8++, B20++, i++) {
        f32 scale = tial_scale[i];
        
        MtxTrans(AA8->x, AA8->y, AA8->z, false);
        MtxScale(scale, scale, scale, true);
        cMtx_YrotM(*calc_mtx, B20->y);
        cMtx_XrotM(*calc_mtx, B20->x);

        J3DModel* model = i_this->unk_A84[i];
        model->setBaseTRMtx(*calc_mtx);
        g_env_light.setLightTevColorType(model, &i_this->actor.tevStr);
        mDoExt_modelUpdate(model);
    }
}

/* 00000A94-00000B90       .text tex_anm_set__FP8bb_classUs */
void tex_anm_set(bb_class* i_this, unsigned short idx) {
    i_this->unk_2CD = 1;
    i_this->unk_2CE = bb_tex_max_frame[idx];
    i_this->unk_2CC = 0;

    J3DAnmTexPattern* btp = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("Bb", bb_tex_anm_idx[idx]));
    JUT_ASSERT(671, btp);

    i_this->mBtpAnm.init(i_this->mpMorf->getModel()->getModelData(), btp, 0, 2, 1.0f, 0, -1, true, 0);
}

/* 00000B90-00000C40       .text bb_eye_tex_anm__FP8bb_class */
void bb_eye_tex_anm(bb_class* i_this) {
    if (i_this->unk_2D0 != 0) {
        i_this->unk_2D0--;
    } else {
        i_this->unk_2D0 = cM_rndF(50.0f) + 10.0f;
        if (i_this->unk_2CD == 0) {
            tex_anm_set(i_this, 4);
        }
    }

    if (i_this->unk_2CD != 0) {
        if (i_this->unk_2CC < i_this->unk_2CE) {
            i_this->unk_2CC++;
        } else {
            i_this->unk_2CD = 0;
        }
    }
}

/* 00000C40-00000D74       .text anm_init__FP8bb_classifUcfi */
void anm_init(bb_class* i_this, int animFileIdx, float morf, unsigned char loopMode, float speed, int soundFileIdx) {
    if (i_this->unk_2DF < 3) {
        if (soundFileIdx >= 0) {
            i_this->mpMorf->setAnm((J3DAnmTransform*)(dComIfG_getObjectRes("Bb", animFileIdx)), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("Bb", soundFileIdx));
        } else {
            i_this->mpMorf->setAnm((J3DAnmTransform*)(dComIfG_getObjectRes("Bb", animFileIdx)), loopMode, morf, speed, 0.0f, -1.0f, NULL);
        }
    }
}

/* 00000D74-00001048       .text s_a_d_sub__FPvPv */
void* s_a_d_sub(void* ac1, void* ac2) {
    dBgS_LinChk linChk;
    cXyz sp14;
    cXyz sp8;

    if (esa_check_count < 100 && fopAc_IsActor(ac1) && fpcM_GetName(ac1) == PROC_ESA) {
        esa_class* esa1 = (esa_class*)ac1;
        esa_class* esa2 = (esa_class*)ac2;

        if (esa1->field_0x298 == 0) {
            sp8 = esa1->current.pos;
            sp8.y += 10.0f;
            sp14 = esa2->current.pos;

            linChk.Set(&sp14, &sp8, esa2);
            if (!dComIfG_Bgsp()->LineCross(&linChk)) {
                esa_info[esa_check_count] = esa1;
                esa_check_count++;
            }
        }
    }

    return NULL;
}

/* 00001480-000015D4       .text search_esa__FP8bb_class */
esa_class* search_esa(bb_class* i_this) {
    esa_check_count = 0;
    fpcM_Search(s_a_d_sub, i_this);
    
    if (esa_check_count != 0) {
        f32 fDist = 50.0f;
        s32 i = 0;

        while (i < esa_check_count) {
            esa_class* esa = esa_info[i];
            f32 x = esa->current.pos.x - i_this->actor.current.pos.x;
            f32 z = esa->current.pos.z - i_this->actor.current.pos.z;

            if (std::sqrtf(x * x + z * z) < fDist) {
                esa->field_0x298 = 1;
                return esa;
            }

            i++;
            if (i == esa_check_count) {
                i = 0;
                fDist += 50.0f;
                if (fDist > 10000.0f) {
                    return NULL;
                }
            }
        }
    }

    return NULL;
}

/* 000015D4-000015F4       .text kuti_open__FP8bb_classsUl */
void kuti_open(bb_class* i_this, short arg1, unsigned long sfxId) {
    if (i_this->unk_C50 == 0) {
        i_this->unk_C50 = arg1;
        i_this->unk_C52 = arg1 - 3;
        i_this->unk_C54 = sfxId;
    }
}

/* 000015F4-00001928       .text bb_player_bg_check__FP8bb_class */
BOOL bb_player_bg_check(bb_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    dBgS_LinChk linChk;
    cXyz sp14;
    cXyz sp8;
    
    sp8 = player->current.pos;
    sp8.y += 100.0f;
    sp14 = a_this->eyePos;

    linChk.Set(&sp14, &sp8, a_this);
    
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    }
    return FALSE;
}

/* 00001928-00001C50       .text bb_setpos_bg_check__FP8bb_class */
BOOL bb_setpos_bg_check(bb_class* i_this) {
    dBgS_LinChk linChk;
    cXyz sp14;
    cXyz sp8;

    sp8 = i_this->actor.home.pos;
    sp8.y += 100.0f;
    sp14 = i_this->actor.eyePos;

    linChk.Set(&sp14, &sp8, &i_this->actor);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    }
    return FALSE;
}

/* 00001C50-00001DF8       .text bb_player_view_check__FP8bb_class */
s32 bb_player_view_check(bb_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s16 var_r5;
    f32 var_f2;

    if (l_bbHIO.unk_06 != 0) {
        return 1;
    }

    if (i_this->unk_2D9 != 0xFF) {
        if (i_this->unk_33C > i_this->unk_2D9 * 100.0f || bb_player_bg_check(i_this)) {
            return 0;
        }
    } else if (i_this->unk_2DD == 4 || i_this->unk_2DD == 7) {
        if (i_this->unk_33C > l_bbHIO.unk_6C || bb_player_bg_check(i_this)) {
            return 0;
        } 
    } else if (i_this->unk_33C > l_bbHIO.unk_68 || bb_player_bg_check(i_this)) {
        return 0;
    }

    if (i_this->unk_2DD == 4 || i_this->unk_2DD == 7) {
        var_r5 = l_bbHIO.unk_72;
        var_f2 = l_bbHIO.unk_78;
    } else {
        var_r5 = l_bbHIO.unk_70;
        var_f2 = l_bbHIO.unk_74;
    }

    if (std::fabsf(player->current.pos.y - i_this->actor.eyePos.y) < var_f2) {
        s16 tmp = i_this->actor.current.angle.y - i_this->unk_C5C - i_this->unk_336;
        if (tmp < 0) {
            tmp = -tmp;
        }
        
        if ((u16)tmp < var_r5) {
            return 1;
        }
    }

    return 0;
}

/* 00001DF8-00002250       .text path_check__FP8bb_class */
void path_check(bb_class* i_this) {
    static u8 check_index[255];

    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;

    if (i_this->ppd == NULL) {
        return;
    }
    
    dBgS_LinChk linChk;
    cXyz sp24;
    cXyz spC;
    dPnt* point;

    sp24 = a_this->current.pos;
    sp24.y += 100.0f;

    point = &i_this->ppd->m_points[0];

    for (s32 i = 0; i < i_this->ppd->m_num; i++, point++) {
        spC.x = point->m_position.x;
        spC.y = point->m_position.y + 100.0f;
        spC.z = point->m_position.z;

        linChk.Set(&sp24, &spC, a_this);
        if (!dComIfG_Bgsp()->LineCross(&linChk)) {
            check_index[i] = 1;
        } else {
            check_index[i] = 0;
        }
    }

    f32 fDist = 0.0f;
    bool r7 = false;

    for (s32 j = 0; j < 100; j++) {
        point = &i_this->ppd->m_points[0];

        for (s32 i = 0; i < i_this->ppd->m_num; i++, point++) {
            if (check_index[i] != 0) {
                f32 x = a_this->current.pos.x - point->m_position.x;
                f32 y = a_this->current.pos.y - point->m_position.y;
                f32 z = a_this->current.pos.z - point->m_position.z;
                
                if (std::sqrtf(x * x + y * y + z * z) < fDist) {
                    i_this->unk_35E = i - (u8)i_this->unk_35F;
                    if (i_this->unk_35E >= (s8)i_this->ppd->m_num) {
                        i_this->unk_35E = i_this->ppd->m_num;
                    } else if (i_this->unk_35E < 0) {
                        i_this->unk_35E = 0;
                    }
                    r7 = true;
                    break;
                }
            }
        }

        if (r7) {
            break;
        }

        fDist += 50.0f;
    }

    if (!r7) {
        i_this->unk_35D = 0;
    } else {
        i_this->unk_35D = i_this->unk_2DA + 1;
    }
}

/* 00002250-0000234C       .text daBb_shadowDraw__FP8bb_class */
static void daBb_shadowDraw(bb_class* i_this) {
    J3DModel* model = i_this->mpMorf->getModel();
    cXyz pos(
        i_this->actor.current.pos.x,
        i_this->actor.current.pos.y + 150.0f + REG8_F(18),
        i_this->actor.current.pos.z
    );

    i_this->unk_2D4 = dComIfGd_setShadow(i_this->unk_2D4, 1, model, &pos, 
                        REG8_F(19) + 800.0f, REG8_F(17) + 40.0f, i_this->actor.current.pos.y, 
                        i_this->mAcch.GetGroundH(), 
                        i_this->mAcch.m_gnd,
                        &i_this->actor.tevStr, 0, 1.0f, &dDlst_shadowControl_c::mSimpleTexObj);

    if (i_this->unk_2D4 != 0) {
        for (s32 i = 0; i < 9; i++) {
            dComIfGd_addRealShadow(i_this->unk_2D4, i_this->unk_A84[i]);
        }
    }
}

/* 0000234C-00002444       .text daBb_Draw__FP8bb_class */
static BOOL daBb_Draw(bb_class* i_this) {
    if (i_this->unk_2F2 != 0) {
        return TRUE;
    }

    J3DModel* model = i_this->mpMorf->getModel();
    g_env_light.setLightTevColorType(model, &i_this->actor.tevStr);

    if (i_this->mEnemyIce.mFreezeTimer > 20) {
        dMat_control_c::iceEntryDL(i_this->mpMorf, -1, NULL);
        daBb_shadowDraw(i_this);
        return TRUE;
    }

    i_this->mBtpAnm.entry(model->getModelData(), i_this->unk_2CC);
    i_this->mpMorf->entryDL();

    J3DModelData* modelData = model->getModelData();
    i_this->mBtpAnm.remove(modelData);
    daBb_shadowDraw(i_this);
    tail_draw(i_this);
#if VERSION == VERSION_DEMO
    dSnap_RegistFig(DSNAP_TYPE_BB, &i_this->actor, 1.0f, 1.0f, 1.0f);
#else
    dSnap_RegistFig(DSNAP_TYPE_BB, &i_this->actor, i_this->actor.eyePos, i_this->actor.shape_angle.y, 1.0f, 1.0f, 1.0f);
#endif
    return TRUE;
}

/* 00002444-00002708       .text bb_pos_move__FP8bb_class */
void bb_pos_move(bb_class* i_this) {
    f32 x = i_this->unk_2F4.x - i_this->actor.current.pos.x;
    f32 y = i_this->unk_2F4.y - i_this->actor.current.pos.y;
    f32 z = i_this->unk_2F4.z - i_this->actor.current.pos.z;

    s16 atan = cM_atan2s(x, z);
    f32 sqrt = std::sqrtf(x * x + z * z);
    s16 atan2 = -cM_atan2s(y, sqrt);

    s16 old_y = i_this->actor.current.angle.y;
    cLib_addCalcAngleS2(&i_this->actor.current.angle.y, atan, REG0_S(3) + 10, i_this->unk_310 * i_this->unk_308);
    old_y = (old_y - i_this->actor.current.angle.y) * 32;
    
    s16 target = REG0_S(1) + 5500;
    if (old_y > target) {
        old_y = target;
    } else if (old_y < -target) {
        old_y = -target;
    }

    cLib_addCalcAngleS2(&i_this->actor.current.angle.z, old_y, REG0_S(3) + 10, i_this->unk_310 * i_this->unk_308 * 0.5f);
    cLib_addCalcAngleS2(&i_this->actor.current.angle.x, atan2, REG0_S(3) + 10, i_this->unk_310 * i_this->unk_308);
    cLib_addCalc2(&i_this->unk_308, 1.0f, 1.0f, 0.04f);
    cLib_addCalc2(&i_this->actor.speedF, i_this->unk_300, 1.0f, i_this->unk_304);

    cXyz v;
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = i_this->actor.speedF;

    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);
    MtxPosition(&v, &i_this->actor.speed);

    i_this->actor.current.pos.x += i_this->actor.speed.x;
    i_this->actor.current.pos.y += i_this->actor.speed.y;
    i_this->actor.current.pos.z += i_this->actor.speed.z;

    if (i_this->unk_324 != 0) {
        i_this->unk_324--;
        i_this->actor.current.pos.y += 5.0f;
    }
}

/* 00002708-00002854       .text bb_ground_pos_move__FP8bb_class */
void bb_ground_pos_move(bb_class* i_this) {
    cXyz v;
    cXyz v2;

    s16 atan = cM_atan2s(i_this->unk_2F4.x - i_this->actor.current.pos.x, i_this->unk_2F4.z - i_this->actor.current.pos.z);
    cLib_addCalcAngleS2(&i_this->actor.current.angle.y, atan, REG0_S(3) + 2, i_this->unk_310 * i_this->unk_308);
    cLib_addCalc2(&i_this->unk_308, 1.0f, 1.0f, 0.1f);
    cLib_addCalc2(&i_this->actor.speedF, i_this->unk_300, 1.0f, i_this->unk_304);

    v.x = 0.0f;
    v.y = 0.0f;
    v.z = i_this->actor.speedF;

    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    MtxPosition(&v, &v2);

    i_this->actor.speed.x = v2.x;
    i_this->actor.speed.z = v2.z;

    i_this->actor.current.pos.x += i_this->actor.speed.x;
    i_this->actor.current.pos.y += i_this->actor.speed.y;
    i_this->actor.current.pos.z += i_this->actor.speed.z;

    i_this->actor.speed.y -= 3.0f;

    if (i_this->mAcch.ChkGroundHit()) {
        i_this->actor.speed.y = -0.5f;
    }
}

/* 00002854-00003224       .text bb_path_move__FP8bb_class */
void bb_path_move(bb_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    s8 r29 = 0;
    s32 frame;
    f32 x;
    f32 y;
    f32 z;
    f32 sqrt;
    dPnt* point;
    esa_class* esa;

    i_this->unk_C60 = 2;

    switch (i_this->unk_2F0) {
        case 0:
            frame = i_this->mpMorf->getFrame();
            if (a_this->current.pos.y > i_this->unk_2F4.y && frame == (REG0_S(0) + 9)) {
                i_this->unk_2F0 = 1;
                anm_init(i_this, 0x19, REG0_F(0) + 12.0f, 2, 1.0f, 9);
            }
            break;

        case 1:
            if (a_this->current.pos.y <= i_this->unk_2F4.y) {
                i_this->unk_2F0 = 0;
                anm_init(i_this, 0x18, 5.0f, 2, l_bbHIO.unk_24, 8);
            }
            break;

        case 10:
            break;
    }

    switch (i_this->unk_2F1) {
        case 0:
            i_this->unk_35E += i_this->unk_35F;
            if (i_this->unk_35E >= (s8)i_this->ppd->m_num) {
                if (i_this->ppd->m_closed & 1) {
                    i_this->unk_35E = 0;
                } else {
                    i_this->unk_35F = -1;
                    i_this->unk_35E = i_this->ppd->m_num - 2;
                }

                if ((s32)i_this->ppd->m_nextID != 0xFFFF) {
                    i_this->ppd = dPath_GetRoomPath(i_this->ppd->m_nextID, fopAcM_GetRoomNo(a_this));
                    JUT_ASSERT(DEMO_SELECT(1476, 1479), i_this->ppd != NULL);
                }
            } else if (i_this->unk_35E < 0) {
                i_this->unk_35F = 1;
                i_this->unk_35E = 1;
            }
        
        case -1:
            i_this->unk_2F1 = 1;

            point = &i_this->ppd->m_points[0];
            point += i_this->unk_35E;

            if (i_this->unk_364 != 0) {
                i_this->unk_300 = 25.0f;
                i_this->unk_304 = 2.0f;
                i_this->unk_364 = 0;
            } else if (a_this->current.pos.y < i_this->unk_2F4.y) {
                i_this->unk_300 = 20.0;
                i_this->unk_304 = REG0_F(11) + 1.0f;
            } else {
                i_this->unk_300 = 30.0;
                i_this->unk_304 = REG0_F(13) + 1.0f;
            }

            i_this->unk_308 = REG0_F(7);
            i_this->unk_2F4 = point->m_position;
            if (point->mArg3 == 1) {
                i_this->unk_2F1 = 10;
            } else if (i_this->unk_2DF == 0) {
                i_this->unk_2F4.x = point->m_position.x + cM_rndFX(150.0f);
                i_this->unk_2F4.y = point->m_position.y + cM_rndFX(150.0f);
                i_this->unk_2F4.z = point->m_position.z + cM_rndFX(150.0f);
            }

            if (l_bbHIO.unk_06 != 0 || (i_this->unk_318[3] == 0 && i_this->unk_2DF == 0)) {
                esa = search_esa(i_this);
                if (esa != NULL) {
                    i_this->unk_330 = fpcM_GetID(esa);
                    i_this->unk_2F1 = 10;
                    i_this->unk_310 = 1000.0f;
                    i_this->unk_35D = 0;
                } else if (bb_player_view_check(i_this) != 0) {
                    i_this->unk_2DD = 3;
                    i_this->unk_2F1 = 0;
                    i_this->unk_35D = 0;
                }
            }
            break;

        case 1:
            cLib_addCalc2(&i_this->unk_308,1.0f, 1.0f, 0.04f);
            x = i_this->unk_2F4.x - a_this->current.pos.x;
            y = i_this->unk_2F4.y - a_this->current.pos.y;
            z = i_this->unk_2F4.z - a_this->current.pos.z;

            sqrt = std::sqrtf(x * x + y * y + z * z);
            i_this->unk_310 = (REG0_F(5) * 10.0f + 100.0f) + (REG0_F(6) * 1000.0f + 500000.0f) / sqrt;
            if (i_this->unk_310 > (REG0_F(4) * 10.0f + 5000.0f)) {
                i_this->unk_310 = REG0_F(4) * 10.0f + 5000.0f;
            }

            if (sqrt < REG0_F(10) * 10.0f + 300.0f) {
                i_this->unk_2F1 = 0;
                point = &i_this->ppd->m_points[0];
                point += i_this->unk_35E;

                if (point->mArg3 == 5) {
                    i_this->unk_2E0 = 1;
                } else if (point->mArg3 == 6) {
                    fopAcM_delete(a_this);
                }
            }
            break;

        case 10:
            i_this->unk_300 = 20.0f;
            x = i_this->unk_2F4.x - a_this->current.pos.x;
            y = (i_this->unk_2F4.y + 50.0f + REG0_F(8) * 10.0f) - a_this->current.pos.y;
            z = i_this->unk_2F4.z - a_this->current.pos.z;
            if (std::sqrtf(x * x + y * y + z * z) < REG0_F(9) * 10.0f + 300.0f) {
                i_this->unk_2F1 = 20;
                i_this->unk_2F0 = 10;
                a_this->speed.y = 0.0f;
                r29 = -1;
            }
            break;

        case 20:
            r29 = -1;
            frame = i_this->mpMorf->getFrame();
            
            cLib_addCalc2(&a_this->current.pos.x, i_this->unk_2F4.x, 0.1f, std::fabsf(a_this->speed.x));
            cLib_addCalc2(&a_this->current.pos.z, i_this->unk_2F4.z, 0.1f, std::fabsf(a_this->speed.z));
            
            a_this->current.pos.y += a_this->speed.y;
            if (frame > (REG0_S(2) + 15)) {
                a_this->speed.y -= REG0_F(7) + 0.8f;
            }

            cLib_addCalcAngleS2(&a_this->current.angle.x, 0, 5, 0x800);
            cLib_addCalcAngleS2(&a_this->current.angle.z, 0, 5, 0x800);

            if (i_this->mAcch.ChkGroundHit()) {
                a_this->speed.y = -0.5f;
            }

            if (i_this->unk_318[2] == 0) {
                i_this->unk_2F1 = 0x17;
            }
            break;

        case 22:
            r29 = 1;
            if (i_this->unk_318[2] == 0) {
                i_this->unk_35E++;
                if (i_this->unk_35E >= i_this->ppd->m_num) {
                    i_this->unk_35E = 0;
                }

                point = &i_this->ppd->m_points[0];
                point += i_this->unk_35E;

                i_this->unk_2F4 = point->m_position;
                if (point->mArg3 == 2) {
                    i_this->unk_2F1 = 0x19;
                } else {
                    i_this->unk_2F1 = 0x17;
                    i_this->unk_310 = 1000.0f;
                    i_this->unk_308 = 1.0f;
                }
            }

            i_this->unk_300 = 0.0f;
            a_this->speedF = 0.0f;
            break;
        
        case 23:
            r29 = 1;
            frame = i_this->mpMorf->getFrame();
            if (frame >= REG0_S(3) && frame <= REG0_S(4) + 9) {
                i_this->unk_300 = i_this->unk_328 * 5.0f;
                a_this->speedF = i_this->unk_328 * 5.0f;
            } else {
                i_this->unk_300 = 0.0f;
                a_this->speedF = 0.0f;

                x = i_this->unk_2F4.x - a_this->current.pos.x;
                z = i_this->unk_2F4.z - a_this->current.pos.z;

                if (std::sqrtf(x * x + z * z) < 50.0f) {
                    i_this->unk_2F1 = 0x16;
                    if (i_this->ppd->m_points[i_this->unk_35E].mArg3 == 3) {
                        i_this->unk_318[2] = cM_rndF(50.0f) + 50.0f;
                    }
                }
            }
            break;

        case 25:
            r29 = 1;
            anm_init(i_this, 0x18, 5.0f, 2, l_bbHIO.unk_24, 8);
            i_this->unk_2F1 = -1;
            i_this->unk_310 = REG0_F(4) * 10.0f + 5000.0f;
            i_this->unk_300 = 25.0f;
            i_this->unk_304 = 2.0f;
            a_this->speedF = 0.0f;
            i_this->unk_324 = REG0_S(4) + 10;
            break;
    }

    switch (r29) {
        case 0:
            bb_pos_move(i_this);
            break;

        case 1:
            bb_ground_pos_move(i_this);
            break;
    }
}

/* 00003224-00003F88       .text bb_auto_move__FP8bb_class */
void bb_auto_move(bb_class* i_this) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    s32 frame;
    s8 r29 = 0;
    cXyz sp34;

    i_this->unk_C60 = 2;

    switch (i_this->unk_2F0) {
        case 0:
            frame = i_this->mpMorf->getFrame();
            if ((i_this->unk_318[0] == 0) && (frame == REG0_S(0) + 9)) {
                i_this->unk_2F0 = 1;
                i_this->unk_318[0] = cM_rndF(200.0) + 50.0f;
                anm_init(i_this, 0x19, REG0_F(0) + 12.0f, 2, 1.0f, 9);
            }
            break;

        case 1:
            if ((i_this->unk_318[0] == 0) && (i_this->actor.current.pos.y < i_this->unk_2F4.y)) {
                i_this->unk_2F0 = 0;
                i_this->unk_318[0] = cM_rndF(60.0) + 20.0f;
                anm_init(i_this, 0x18, 5.0f, 2, l_bbHIO.unk_24, 8);
            }
            break;

        case 10:
            break;

        case 20:
            frame = i_this->mpMorf->getFrame();
            if (frame == 0x22) {
                i_this->unk_2F0 = 0;
                i_this->unk_318[0] = cM_rndF(60.0f) + 20.0f;
                anm_init(i_this, 0x18, 0.0f, 2, l_bbHIO.unk_24, 8);
            }
            break;
    }

    switch(i_this->unk_2F1) {
        case 0:
            if (i_this->unk_318[1] == 0) {
                f32 x = (i_this->actor.home.pos.x + cM_rndFX(l_bbHIO.unk_0C)) - i_this->actor.current.pos.x;
                f32 z = (i_this->actor.home.pos.z + cM_rndFX(l_bbHIO.unk_0C)) - i_this->actor.current.pos.z;

                if (std::sqrtf(x * x + z * z) > 200.0f) {
                    i_this->unk_318[1] = cM_rndF(150.0f) + 50.0f;

                    i_this->unk_2F4.x = x + i_this->actor.current.pos.x;
                    i_this->unk_2F4.y = i_this->actor.home.pos.y + cM_rndF(500.0f);
                    i_this->unk_2F4.z = z + i_this->actor.current.pos.z;

                    i_this->unk_308 = 0.0;
                    i_this->unk_300 = REG0_F(10) + 25.0f;
                    i_this->unk_304 = REG0_F(11) + 1.0f;
                    i_this->unk_310 = cM_rndF(300.0f) + 200.0f;

                    if ((l_bbHIO.unk_06 != 0) || (i_this->unk_318[3] == 0 && (i_this->unk_2DF == 0))) {
                        esa_class* esa = search_esa(i_this);
                        if (esa != NULL) {
                            i_this->unk_330 = fpcM_GetID(esa);
                            i_this->unk_2F1 = 10;
                            i_this->unk_310 = 1000.0f;
                        } else if (bb_player_view_check(i_this) != 0) {
                            i_this->unk_2DD = 3;
                            i_this->unk_2F1 = 0;
                        }
                    }
                }
            }
            break;
        
        case 10:
        case 11: {
            i_this->unk_C60 = 0;

            fopAc_ac_c* ac = fopAcM_SearchByID(i_this->unk_330);
            if (ac != NULL) {
                sp34.x = 0.0f;
                sp34.y = 0.0f;
                sp34.z = REG0_F(16) * 10.0f + -200.0f;
                cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
                cXyz v2;
                MtxPosition(&sp34, &v2);

                i_this->unk_2F4.x = ac->current.pos.x + v2.x;
                i_this->unk_2F4.y = ac->current.pos.y + 80.0f + REG0_F(8) * 10.0f;
                i_this->unk_2F4.z = ac->current.pos.z + v2.z;
                i_this->unk_300 = 20.0f;

                f32 x = i_this->unk_2F4.x - i_this->actor.current.pos.x;
                f32 y = i_this->unk_2F4.y - i_this->actor.current.pos.y;
                f32 z = i_this->unk_2F4.z - i_this->actor.current.pos.z;
                f32 sqrt = std::sqrtf(x * x + y * y + z * z);

                if (i_this->unk_2F1 == 10) {
                    if (sqrt < l_bbHIO.unk_50) {
                        i_this->unk_2F1 = 11;
                        anm_init(i_this, 0x1A, 10.0f, 0, 1.0f, 10);
                    }
                } else if (sqrt < REG0_F(9) * 10.0f + 300.0f) {
                    i_this->unk_2F1 = 20;
                    anm_init(i_this, 0x1F, 5.0f, 2, l_bbHIO.unk_44, 15);
                    i_this->unk_2F0 = 10;
                    i_this->actor.speed.y = 0.0f;
                    i_this->unk_354 = 0;
                    r29 = -1;
                }
            } else {
                i_this->unk_2F1 = 0;
            }
            break;
        }
        case 20: {
            r29 = -1;
            i_this->unk_C60 = 0;

            s16 old_354 = i_this->unk_354;
            i_this->unk_354++;

            cLib_addCalc2(&i_this->actor.current.pos.x, i_this->unk_2F4.x, 0.1f, std::fabsf(i_this->actor.speed.x));
            cLib_addCalc2(&i_this->actor.current.pos.z, i_this->unk_2F4.z, 0.1f, std::fabsf(i_this->actor.speed.z));
            i_this->actor.current.pos.y += i_this->actor.speed.y;

            if (old_354 > l_bbHIO.unk_40) {
                i_this->actor.speed.y -= REG0_F(7) + 0.8f;
            }

            cLib_addCalcAngleS2(&i_this->actor.current.angle.x, 0, 5, 0x800);
            cLib_addCalcAngleS2(&i_this->actor.current.angle.z, 0, 5, 0x800);

            if (i_this->mAcch.GetGroundH() - i_this->actor.current.pos.y < -200.0f) {
                i_this->unk_2F1 = 25;
            } else if (i_this->mAcch.ChkGroundHit()) {
                i_this->actor.speed.y = -0.5f;
                anm_init(i_this, 0x20, 5.0f, 0, l_bbHIO.unk_48, 0x10);
                i_this->unk_2F1 = 22;
                i_this->unk_318[2] = 50;
            }
            break;
        }
        case 21: {
            r29 = 1;
            fopAc_ac_c* esa = search_esa(i_this);
            if (esa == NULL) {
                i_this->unk_2F1 = 25;
            } else {
                i_this->unk_2F1 = 22;
            }
            break;
        }
        case 22:
            r29 = 1;
            i_this->unk_300 = 0.0f;
            i_this->actor.speedF = 0.0f;
            i_this->unk_310 = 0.0f;

            if (i_this->unk_318[2] == 0) {
                i_this->unk_2F1 = 23;
                fopAc_ac_c* ac = fopAcM_SearchByID(i_this->unk_330);
                if (ac != NULL) {
                    i_this->unk_2F4.x = ac->current.pos.x;
                    i_this->unk_2F4.z = ac->current.pos.z;
                    i_this->unk_310 = 1000.0f;
                    i_this->unk_308 = 1.0f;
                    anm_init(i_this, 0x22, 5.0f, 2, 1.0f, 0x12);
                } else {
                    i_this->unk_2F1 = 0x19;
                }
            }
            break;

        case 23: {
            r29 = 1;
            i_this->unk_C60 = 0;
            i_this->unk_300 = l_bbHIO.unk_54;
            i_this->actor.speedF = 1.0;

            f32 x = i_this->unk_2F4.x - i_this->actor.current.pos.x;
            f32 z = i_this->unk_2F4.z - i_this->actor.current.pos.z;

            if (std::sqrtf(x * x + z * z) < 110.0f) {
                i_this->unk_2F1 = 21;
                i_this->unk_318[2] = cM_rndF(50.0f) + 50.0f;

                anm_init(i_this, 0x17, 5.0f, 0, 1.0f, 7);

                i_this->unk_2F1 = 24;
            }
            break;
        }
        case 24: {
            r29 = 1;
            i_this->unk_C50 = 0;
            i_this->unk_C60 = 0;
            i_this->unk_300 = 0.0f;
            i_this->actor.speedF = 0.0f;

            frame = i_this->mpMorf->getFrame();
            if (frame == 9) {
                fopAc_ac_c* ac = fopAcM_SearchByID(i_this->unk_330);
                if (ac != NULL) {
                    fopAcM_delete(ac);
                }
            }

            if (i_this->mpMorf->isStop()) {
                i_this->unk_2F1 = 21;
                i_this->unk_318[2] = cM_rndF(50.0f);
                anm_init(i_this, 0x21, 5.0f, 2, 1.0f, 0x11);
            }
            break;
        }
        case 25:
            r29 = 1;
            i_this->unk_2F1 = 0;
            anm_init(i_this, 0x18, 5.0f, 2, l_bbHIO.unk_24, 8);
            i_this->unk_310 = REG0_F(4) * 10.0f + 2000.0f;
            i_this->unk_300 = 25.0f;
            i_this->unk_304 = 1.0f;
            i_this->actor.speedF = 0.0f;
            i_this->unk_324 = REG0_S(4) + 10;
            i_this->unk_318[3] = cM_rndF(100.0f) + 100.0f;
            i_this->unk_324 = REG0_S(4) + 10;
            if (i_this->unk_2DA != 0xFF) {
                i_this->unk_35D = i_this->unk_2DA + 1;
                path_check(i_this);
                i_this->unk_364 = 1;
            } else {
                i_this->unk_318[1] = 50;
                MtxTrans(i_this->actor.current.pos.x, i_this->actor.current.pos.y, i_this->actor.current.pos.z, false);
                sp34.x = 0.0f;
                sp34.y = 1000.0f;
                sp34.z = 2000.0f;
                cMtx_YrotM(*calc_mtx, i_this->actor.current.angle.y);
                MtxPosition(&sp34, &i_this->unk_2F4);
            }
            break;
    }

    switch (r29) {
        case 0:
            bb_pos_move(i_this);
            break;

        case 1:
            bb_ground_pos_move(i_this);
            if (i_this->unk_2F1 != 25) {
                f32 x = player->current.pos.x - i_this->actor.current.pos.x;
                f32 z = player->current.pos.z - i_this->actor.current.pos.z;

                if (std::sqrtf(x * x + z * z) < 400.0f) {
                    i_this->unk_2F1 = 0;
                    fopAc_ac_c* ac = fopAcM_SearchByID(i_this->unk_330);
                    if (ac != NULL) {
                        esa_class* esa = (esa_class*)ac;
                        esa->field_0x298 = 0;
                    }
                    i_this->unk_2F0 = 0;
                    i_this->unk_318[0] = cM_rndF(60.0f) + 20.0f;
                    anm_init(i_this, 0x18, 3.0f, 2, l_bbHIO.unk_24, 8);
                    if (i_this->unk_2DA != 0xFF) {
                        i_this->unk_35D = i_this->unk_2DA + 1;
                        path_check(i_this);
                        i_this->unk_318[3] = cM_rndF(250.0f) + 250.0f;
                        i_this->unk_364 = 1;
                    } else {
                        i_this->unk_318[1] = 50;
                        i_this->unk_310 = REG0_F(4) * 10.0f + 5000.0f;
                        i_this->unk_300 = 30.0f;
                        i_this->unk_304 = 3.0f;
                        i_this->actor.speedF = 0.0f;

                        MtxTrans(i_this->actor.current.pos.x, i_this->actor.current.pos.y, i_this->actor.current.pos.z, false);

                        sp34.x = 0.0f;
                        sp34.y = 1000.0f;
                        sp34.z = 2000.0f;
                        cMtx_YrotM(*calc_mtx, i_this->actor.current.angle.y);
                        MtxPosition(&sp34, &i_this->unk_2F4);

                        i_this->unk_318[3] = cM_rndF(250.0f) + 250.0f;
                    }
                }
            }
            break;
    }
}

/* 00003F88-00004000       .text bb_water_check__FP8bb_class */
void bb_water_check(bb_class* i_this) {
    if (daSea_ChkArea(i_this->unk_2F4.x, i_this->unk_2F4.z)) {
        f32 waveHeight = daSea_calcWave(i_this->unk_2F4.x, i_this->unk_2F4.z);
        waveHeight = REG0_F(0) + waveHeight;
        waveHeight = 100.0f + waveHeight;
        if (i_this->actor.current.pos.y <= waveHeight) {
            i_this->actor.current.pos.y = waveHeight;
        }
    }
}

/* 00004000-0000404C       .text pl_name_check__FPvPv */
void* pl_name_check(void* ac1, void* ac2) {
    if (fopAc_IsActor(ac1) && fopAcM_GetName(ac1) == PROC_NPC_KAM) {
        return ac1;
    }
    return NULL;
}

/* 0000404C-000044EC       .text bb_kamome_attack__FP8bb_class */
void bb_kamome_attack(bb_class* i_this) {
    daPy_py_c* player = daPy_getPlayerActorClass();

    i_this->unk_C60 = 1;

    switch (i_this->unk_2F0) {
        case 0: {
            s32 frame = i_this->mpMorf->getFrame();
            if ((i_this->actor.current.pos.y > i_this->unk_2F4.y) && (frame == REG0_S(0) + 9)) {
                i_this->unk_2F0 = 1;
                anm_init(i_this, 0x19, REG0_F(0) + 12.0f, 2, 1.0f, 9);
            }
            break;
        }
        case 1: {
            if (i_this->actor.current.pos.y <= i_this->unk_2F4.y) {
                i_this->unk_2F0 = 0;
                anm_init(i_this, 0x18, 5.0f, 2, l_bbHIO.unk_24, 8);
            }
            break;
        }
        default:
            i_this->unk_2F0 = 0;
            break;
    }

    switch (i_this->unk_2F1) {
        case 0:
            anm_init(i_this, 0x19, 10.0f, 2, 1.0f, 9);
            i_this->unk_2F1 = 1;

        case 1: {
            cXyz v;
            v.x = (REG0_F(5) + 300.0f) * cM_ssin(i_this->unk_352 * (REG0_S(5) + 400));
            v.y = (REG0_F(3) + 100.0f) * cM_ssin(i_this->unk_352 * (REG0_S(5) + 300));
            v.z = REG0_F(4) + 100.0f + (REG0_F(7) + 100.0f) * cM_ssin(i_this->unk_352 * (REG0_S(6) + 100));
            cMtx_YrotS(*calc_mtx, player->shape_angle.y);
            cXyz v2;
            MtxPosition(&v, &v2);
            i_this->unk_2F4 = v2 + player->current.pos;
            break;
        }
        default:
            i_this->unk_2F1 = 0;
            break;
    }

    i_this->unk_300 = l_bbHIO.unk_08;
    cXyz tmp = i_this->unk_2F4 - i_this->actor.current.pos;
    if (std::sqrtf(tmp.getSquareMag()) < REG0_F(9) + 100.0f) {
        i_this->unk_300 = 0.0f;
    }

    i_this->unk_304 = REG0_F(10) + 0.5f;
    i_this->unk_310 = REG0_F(11) + 1000.0f;
    i_this->unk_308 = 1.0f;

    bb_pos_move(i_this);

    if ((i_this->unk_352 & 0x3F) == 0 && cM_rndF(1.0f) < 0.5f) {
        kuti_open(i_this, 0x1B, JA_SE_CV_BB_ATTACK);
    }

    i_this->mHeadAtSph.SetC(i_this->actor.eyePos);
    dComIfG_Ccsp()->Set(&i_this->mHeadAtSph);

    if (daSea_ChkArea(i_this->actor.eyePos.x, i_this->actor.eyePos.z)) {
        f32 waveHeight = daSea_calcWave(i_this->actor.eyePos.x, i_this->actor.eyePos.z);
        if (i_this->actor.eyePos.y < waveHeight && i_this->unk_358 >= waveHeight) {
            cXyz i_pos = i_this->actor.eyePos;
            i_pos.y = waveHeight;
            fopKyM_createWpillar(&i_pos, REG0_F(9) + 0.7f, REG0_F(10) + 0.7f, 0);
            fopAcM_seStart(&i_this->actor, JA_SE_OBJ_FALL_WATER_S, 0);
        }

        i_this->unk_358 = i_this->actor.eyePos.y;
        if (i_this->actor.current.pos.y < waveHeight + 30.0f) {
            i_this->actor.current.pos.y = waveHeight + 30.0f;
        }
    }
}

/* 000044EC-00005534       .text bb_atack_move__FP8bb_class */
void bb_atack_move(bb_class* i_this) {
    fopAc_ac_c* a_this = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s8 r29 = 0;
    s8 r28 = 0;
    f32 x;
    f32 y;
    f32 z;

    i_this->unk_C60 = 1;

    if (i_this->unk_C7C != 0) {
        i_this->unk_C7C = 0;
        i_this->unk_318[5] = (cM_rndF(30.0f) + 20.0f) * l_bbHIO.unk_20;

        anm_init(i_this, 0x1B, 10.0f, 2, l_bbHIO.unk_28, 11);

        i_this->unk_308 = 0.0f;
        i_this->unk_30C = 0.0f;
        i_this->unk_2F1 = 4;
        
        kuti_open(i_this, 0x30, JA_SE_CV_BB_NORMAL);
    }

#if VERSION == VERSION_DEMO
    if (&player->base == fpcM_Search(pl_name_check, i_this) || l_bbHIO.unk_10 != 0)
#else
    if (&player->base == fpcM_Search(pl_name_check, i_this))
#endif
    {
        bb_kamome_attack(i_this);
        return;
    }

    switch (i_this->unk_2F1) {
        case 0:
            i_this->unk_2F1 = 1;
            i_this->unk_308 = 0.0f;
            i_this->unk_300 = 30.0f;
            i_this->unk_304 = 1.0f;
            anm_init(i_this, 0x19, 10.0f, 2, 1.0f, 9);

        case 1:
        case 2:
            i_this->unk_2F4 = player->current.pos;
            i_this->unk_2F4.y += 200.0f;

            bb_pos_move(i_this);
            
            x = i_this->unk_2F4.x - a_this->current.pos.x;
            y = i_this->unk_2F4.y - a_this->current.pos.y;
            z = i_this->unk_2F4.z - a_this->current.pos.z;

            if (i_this->unk_2F1 == 1) {
                i_this->unk_310 = 400.0;

                if (std::sqrtf(x * x + y * y + z * z) < l_bbHIO.unk_50) {
                    i_this->unk_2F1 = 2;
                    anm_init(i_this, 0x1A, 10.0f, 0, 1.0f, 10);
                    kuti_open(i_this, 0x15, JA_SE_CV_BB_FIND);
                }
            } else {
                i_this->unk_310 = 2000.0;
                if (std::sqrtf(x * x + y * y + z * z) < REG0_F(9) * 100.0f + 350.0f) {
                    i_this->unk_2F1 = 3;
                }
            }
            break;

        case 3:
            i_this->unk_300 = 0.0f;
            i_this->unk_304 = 3.0f;

            bb_pos_move(i_this);

            if (a_this->speedF < 0.1f) {
                i_this->unk_2F1 = 4;
                i_this->unk_318[0] = 0;

                if ((i_this->unk_2D8 == 4) || (i_this->unk_2D8 == 7)) {
                    i_this->unk_318[1] = l_bbHIO.unk_16 + cM_rndF(l_bbHIO.unk_18 - l_bbHIO.unk_16);
                } else {
                    i_this->unk_318[1] = l_bbHIO.unk_12 + cM_rndF(l_bbHIO.unk_14 - l_bbHIO.unk_12);
                }
                i_this->unk_308 = 0.0f;
                i_this->unk_30C = 0.0f;

                anm_init(i_this, 0x1B, 5.0f, 2, l_bbHIO.unk_28, 11);
                kuti_open(i_this, 0x30, JA_SE_CV_BB_NORMAL);
            }
            break;

        case 4:
            i_this->unk_354++;

            x = cM_ssin(i_this->unk_354 * (REG0_S(2) + 1000)) * 200.0f;
            y = cM_ssin(i_this->unk_354 * (REG0_S(3) + 1200)) * 100.0f;
            z = cM_scos(i_this->unk_354 * (REG0_S(4) + 1500)) * 200.0f;

            cLib_addCalc2(&a_this->current.pos.x, i_this->unk_2F4.x + x, 0.1f, i_this->unk_308 * 20.0f);
            cLib_addCalc2(&a_this->current.pos.y, i_this->unk_2F4.y + y, 0.1f, i_this->unk_308 * 20.0f);
            cLib_addCalc2(&a_this->current.pos.z, i_this->unk_2F4.z + z, 0.1f, i_this->unk_308 * 20.0f);
            cLib_addCalc2(&i_this->unk_308, l_bbHIO.unk_1C, 1.0f, l_bbHIO.unk_1C * 0.1f);

            cLib_addCalcAngleS2(&a_this->current.angle.y, i_this->unk_336, 5, i_this->unk_30C * 1280.0f);
            cLib_addCalcAngleS2(&a_this->current.angle.x, i_this->unk_338, 5, i_this->unk_30C * 768.0f);
            cLib_addCalcAngleS2(&a_this->current.angle.z, 0, 5, i_this->unk_30C * 768.0f);

            cLib_addCalc2(&i_this->unk_30C, 1.0f, 1.0f, 0.05f);

            if (i_this->unk_318[1] == 0) {
                r29 = 1;
                break;
            }

            if (((i_this->unk_318[0] & 0x1F) == 0) && cM_rndF(1.0f) < 0.5f) {
                kuti_open(i_this, 0x1B, JA_SE_CV_BB_ATTACK);
            }

            if (i_this->unk_318[0] == 0) {
                i_this->unk_2F4.x = player->current.pos.x + cM_rndFX(400.0f);
                i_this->unk_2F4.y = player->current.pos.y + 100.0f + cM_rndF(200.0f);
                i_this->unk_2F4.z = player->current.pos.z + cM_rndFX(400.0f);
                i_this->unk_318[0] = cM_rndF(100.0f) + 20.0f;
                i_this->unk_308 = 0.0f;
                i_this->unk_30C = 0.0f;
            }

            if (i_this->unk_318[5] == 0) {
                i_this->unk_318[5] = (l_bbHIO.unk_20 * (cM_rndF(30.0f) + 20.0f));
                if (i_this->unk_33C > ((REG0_F(5) * 10.0f + 200.0f)) && i_this->unk_33C < (REG0_F(6) * 10.0f + 350.0f)) {
                    i_this->unk_2F1 = 5;
                    i_this->unk_318[0] = l_bbHIO.unk_32;
                    anm_init(i_this, 0x1B, 2.0f, 2, l_bbHIO.unk_34, 0xB);
                    tex_anm_set(i_this, 0);
                }
            }
            break;

        case 5:
            i_this->unk_2D0 = 2;
            
            x = cM_ssin(i_this->unk_354 * (REG0_S(2) + 1000)) * 200.0f;
            z = cM_scos(i_this->unk_354 * (REG0_S(4) + 1500)) * 200.0f;

            cLib_addCalc2(&a_this->current.pos.x, i_this->unk_2F4.x + x, 0.1f, i_this->unk_308 * 30.0f);
            cLib_addCalc2(&a_this->current.pos.y, player->current.pos.y + 175.0f, 0.1f, i_this->unk_308 * 30.0f);
            cLib_addCalc2(&a_this->current.pos.z, i_this->unk_2F4.z + z, 0.1f, i_this->unk_308 * 30.0f);
            cLib_addCalc2(&i_this->unk_308, l_bbHIO.unk_1C, 1.0f, l_bbHIO.unk_1C * 0.1f);

            cLib_addCalcAngleS2(&a_this->current.angle.y, i_this->unk_336, 5, i_this->unk_30C * 2048.0f);
            cLib_addCalc2(&i_this->unk_30C, 1.0f, 1.0f, 0.05f);

            if (i_this->unk_318[0] == 0) {
                i_this->unk_2F1 = 6;
                anm_init(i_this, 0x15, 2.0f, 0, l_bbHIO.unk_2C, 6);
                
                i_this->unk_2F4.x = player->current.pos.x;
                i_this->unk_2F4.y = player->current.pos.y + 100.0f;
                i_this->unk_2F4.z = player->current.pos.z;

                i_this->unk_308 = 0.0f;
                i_this->unk_30C = 0.0f;
                i_this->unk_300 = REG0_F(7) + 15.0f;
                i_this->unk_304 = 5.0f;
                a_this->speedF = 0.0f;
            }
            break;

        case 6: {
            i_this->unk_2D0 = 2;
            i_this->unk_C60 = 0;

            s32 frame = i_this->mpMorf->getFrame();
            if (frame == 0x12) {
                i_this->unk_300 = -10.0f;
                i_this->unk_304 = 5.0f;
            }

            i_this->unk_310 = 2000.0f;

            bb_pos_move(i_this);

            if (i_this->mpMorf->isStop()) {
                i_this->unk_2F1 = 4;

                anm_init(i_this, 0x1B, 3.0f, 2, l_bbHIO.unk_28, 11);

                i_this->unk_318[5] = l_bbHIO.unk_20 * (cM_rndF(30.0f) + 20.0f);
                i_this->unk_308 = 0.0f;
                i_this->unk_30C = 0.0f;

                tex_anm_set(i_this, 3);
            } else if (frame < REG0_S(2) + 18) {
                r28 = 1;
                if (player->checkPlayerGuard() && i_this->mHeadAtSph.ChkAtHit()) {
                    i_this->unk_326 = 10;
                    
                    fopAcM_seStart(a_this, JA_SE_LK_ROPE_HOOK_METAL, 0);
                    
                    cXyz scale;
                    scale.x = scale.y = scale.z = 4.0f;
                    
                    dComIfGp_particle_set(dPa_name::ID_COMMON_PURPLE_HIT, &a_this->eyePos, NULL, &scale);

                    i_this->unk_2F1 = 10;
                    i_this->unk_318[0] = l_bbHIO.unk_30;

                    anm_init(i_this, 0x1E, 0.0f, 0, l_bbHIO.unk_38, 14);
                    i_this->unk_300 = REG0_F(7);
                    i_this->unk_304 = 1.0f;
                    a_this->speedF = -20.0f;
                    r28 = 0;

                    fopAcM_monsSeStart(a_this, JA_SE_CV_BB_DAMAGE, 0);

                    tex_anm_set(i_this, 1);
                }
            }
            break;
        }
        case 10:
        case 11:
            i_this->unk_2D0 = 2;
            i_this->unk_C60 = 0;

            bb_pos_move(i_this);

            if (i_this->mpMorf->isStop() && (i_this->unk_2F1 == 10)) {
                i_this->unk_2F1 = 11;
                anm_init(i_this, 0x1D, 0.0f, 2, l_bbHIO.unk_3C, 13);
            }

            if ((i_this->unk_2F1 == 11) && ((i_this->unk_318[0] & 7) == 5)) {
                kuti_open(i_this, 0x12, JA_SE_CV_BB_FURAFURA);
            }

            if (i_this->unk_318[0] == 0) {
                i_this->unk_2F1 = 4;
                i_this->unk_318[5] = l_bbHIO.unk_20 * (cM_rndF(30.0f) + 20.0f);
                
                anm_init(i_this, 0x1B, 10.0f, 2, l_bbHIO.unk_28, 11);
                
                i_this->unk_308 = 0.0f;
                i_this->unk_30C = 0.0f;

                tex_anm_set(i_this, 5);
            }

            cLib_addCalc2(&a_this->current.pos.y, i_this->mAcch.GetGroundH() + 50.0f, 0.05f, 5.0f);
            break;
    }

    if (i_this->unk_2D8 != 3) {
        x = i_this->unk_2F4.x - a_this->current.pos.x;
        y = i_this->unk_2F4.y - a_this->current.pos.y;
        z = i_this->unk_2F4.z - a_this->current.pos.z;

        if (std::sqrtf(x * x + y * y + z * z) > l_bbHIO.unk_7C || bb_player_bg_check(i_this) || bb_setpos_bg_check(i_this) || r29 != 0) {
            i_this->unk_2DD = i_this->unk_2D8;
            if (i_this->unk_2DA != 0xFF) {
                i_this->unk_35D = i_this->unk_2DA + 1;
                path_check(i_this);
            }

            if ((i_this->unk_2DD == 4) || (i_this->unk_2DD == 7)) {
                i_this->unk_2F1 = 10;
                anm_init(i_this, 0x18, 5.0f, 2, l_bbHIO.unk_24, 8);
            } else {
                i_this->unk_2F1 = 0;
                i_this->unk_318[0] = 0;
                i_this->unk_318[1] = 0;
                i_this->unk_2F0 = 1;

                anm_init(i_this, 0x19, REG0_F(0) + 12.0f, 2, 1.0f, 9);

                a_this->speedF = 0.0;
                i_this->unk_2F4.y = player->current.pos.y + 500.0f;
                i_this->unk_318[3] = cM_rndF(200.0f) + 300.0f;
            }
            i_this->unk_308 = 0.0f;
        }
    }

    if (r28 != 0) {
        i_this->mHeadAtSph.SetC(a_this->eyePos);
        dComIfG_Ccsp()->Set(&i_this->mHeadAtSph);
        if (daSea_ChkArea(a_this->eyePos.x, a_this->eyePos.z)) {
            f32 waveHeight = daSea_calcWave(a_this->eyePos.x, a_this->eyePos.z);
            if (a_this->eyePos.y < waveHeight && i_this->unk_358 >= waveHeight) {
                cXyz i_pos;
                i_pos = a_this->eyePos;
                i_pos.y = waveHeight;
                fopKyM_createWpillar(&i_pos, REG0_F(9) + 0.7f, REG0_F(10) + 0.7f, 0);
                fopAcM_seStart(a_this, JA_SE_OBJ_FALL_WATER_S, 0);
            }
            i_this->unk_358 = a_this->eyePos.y;
        }
    } else {
        i_this->mHeadAtSph.ClrAtHit();
    }
}

/* 00005534-00005BB4       .text bb_wait_move__FP8bb_class */
void bb_wait_move(bb_class* i_this) {
    cXyz v;
    cXyz v2;
    s8 r30 = -1;

    f32 speedX = std::fabsf(i_this->actor.speed.x);
    if (speedX < 5.0f) {
        speedX = 5.0f;
    }

    f32 speedZ = std::fabsf(i_this->actor.speed.z);
    if (speedZ < 5.0f) {
        speedZ = 5.0f;
    }

    i_this->unk_C60 = 2;

    switch (i_this->unk_2F1) {
        case -1:
            i_this->unk_57C = 1;
            if (!i_this->mpMorf->isStop()) {
                break;
            }
            i_this->unk_2F1 = 0;

        case 0:
            anm_init(i_this, 0x21, 1.0f, 2, 1.0f, 0x11);
            i_this->unk_2F1 = 1;
            i_this->unk_318[0] = 100;

        case 1:
            i_this->unk_57C = 1;

            cLib_addCalcAngleS2(&i_this->actor.current.angle.y, i_this->actor.home.angle.y, 5, 0x300);
            cLib_addCalcAngleS2(&i_this->actor.current.angle.x, 0, 5, 0x800);
            cLib_addCalcAngleS2(&i_this->actor.current.angle.z, 0, 5, 0x800);

            cLib_addCalc2(&i_this->actor.current.pos.x, i_this->actor.home.pos.x, 0.2f, speedX);
            cLib_addCalc2(&i_this->actor.current.pos.z, i_this->actor.home.pos.z, 0.2f, speedZ);

            i_this->actor.current.pos.y = i_this->actor.home.pos.y;
            if ((i_this->unk_318[0] == 0) && bb_player_view_check(i_this)) {
                i_this->unk_2F1 = 2;
                i_this->unk_318[0] = 0x1E;
            }
            break;

        case 2:
            i_this->unk_C60 = 1;
            if (i_this->unk_318[0] != 0) { 
                break;
            }
            i_this->unk_2F1 = 3;
            anm_init(i_this, 0x18, 5.0f , 2, l_bbHIO.unk_24 * 1.5f, 8);
            i_this->unk_318[0] = REG0_S(0) + 70;

        case 3:
            i_this->unk_C60 = 1;
            cLib_addCalcAngleS2(&i_this->actor.current.angle.y, i_this->unk_336, 10, 0x200);

            v.x = 0.0f;
            v.y = REG0_F(0) * 10.0f + 300.0f;
            v.z = REG0_F(1) * 10.0f + 300.0f;
            cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
            MtxPosition(&v, &v2);

            cLib_addCalc2(&i_this->actor.current.pos.x, i_this->actor.home.pos.x + v2.x, 0.1f, 10.0f);
            cLib_addCalc2(&i_this->actor.current.pos.y, i_this->actor.home.pos.y + v2.y, 0.1f, 10.0f);
            cLib_addCalc2(&i_this->actor.current.pos.z, i_this->actor.home.pos.z + v2.z, 0.1f, 10.0f);

            if (i_this->unk_318[0] == 0) {
                i_this->unk_2DD = 3;
                i_this->unk_2F1 = 0;
            }
            break;

        case 10:
        case 11:
        case 12: {
            r30 = 0;
            i_this->unk_C60 = 0;
            v.x = 0.0;
            v.y = 0.0;
            v.z = 0.0;
            cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
            MtxPosition(&v, &v2);

            f32 fVar2 = 80.0f;
            if (i_this->unk_2F1 == 10) {
                fVar2 = 300.0f;
            }

            i_this->unk_2F4.x = i_this->actor.home.pos.x + v2.x;
            i_this->unk_2F4.y = i_this->actor.home.pos.y + fVar2;
            i_this->unk_2F4.z = i_this->actor.home.pos.z + v2.z;

            i_this->unk_300 = 20.0f;
            i_this->unk_304 = 5.0f;
            i_this->unk_310 = 2000.0f;

            f32 x = i_this->unk_2F4.x - i_this->actor.current.pos.x;
            f32 y = i_this->unk_2F4.y - i_this->actor.current.pos.y;
            f32 z = i_this->unk_2F4.z - i_this->actor.current.pos.z;
            f32 sqrt = std::sqrtf(x * x + y * y + z * z);

            if (i_this->unk_2F1 == 10) {
                if (sqrt < 2000.0f) {
                    i_this->unk_2F1 = 11;
                }
            } else if (i_this->unk_2F1 == 11) {
                if (sqrt < l_bbHIO.unk_50) {
                    i_this->unk_2F1 = 12;
                    anm_init(i_this, 0x1A, 10.0f, 0, 1.0f, 10);
                }
            } else if (i_this->unk_2F1 == 12 && sqrt < REG0_F(9) * 10.0f + 300.0f) {
                i_this->unk_2F1 = 20;
                anm_init(i_this, 0x1F, 5.0f, 2, l_bbHIO.unk_44, 15);
                i_this->unk_2F0 = 10;
                i_this->actor.speed.y = 0.0f;
                i_this->unk_354 = 0;
                r30 = -1;
            }
            break;
        }
        case 20: {
            i_this->unk_57C = 1;
            i_this->unk_C60 = 0;
            s16 old_354 = i_this->unk_354;
            i_this->unk_354++;
            cLib_addCalc2(&i_this->actor.current.pos.x, i_this->actor.home.pos.x, 0.1f, speedX);
            cLib_addCalc2(&i_this->actor.current.pos.z, i_this->actor.home.pos.z, 0.1f, speedZ);

            i_this->actor.current.pos.y += i_this->actor.speed.y;
            if (old_354 > l_bbHIO.unk_40) {
                i_this->actor.speed.y -= REG0_F(7) + 0.8f;
            }

            cLib_addCalcAngleS2(&i_this->actor.current.angle.x, 0, 5, 0x800);
            cLib_addCalcAngleS2(&i_this->actor.current.angle.y, i_this->actor.home.angle.y, 5, 0x300);
            cLib_addCalcAngleS2(&i_this->actor.current.angle.z, 0, 5, 0x800);
            
            if (i_this->actor.current.pos.y <= i_this->actor.home.pos.y) {
                i_this->actor.current.pos.y = i_this->actor.home.pos.y;
                i_this->actor.speed.y = -0.5;
                if (old_354 > l_bbHIO.unk_40) {
                    anm_init(i_this, 0x20, 5.0f, 0, l_bbHIO.unk_48, 0x10);
                    i_this->unk_2F1 = -1;
                }
            }
            break;
        }
    }

    switch (r30) {
        case 0:
            bb_pos_move(i_this);
            break;
    }
}

/* 00005BB4-00006234       .text bb_su_wait_move__FP8bb_class */
void bb_su_wait_move(bb_class* i_this) {
    cXyz v;
    cXyz v2;
    s8 r30 = -1;

    f32 speedX = std::fabsf(i_this->actor.speed.x);
    if (speedX < 5.0f) {
        speedX = 5.0f;
    }

    f32 speedZ = std::fabsf(i_this->actor.speed.z);
    if (speedZ < 5.0f) {
        speedZ = 5.0f;
    }

    i_this->unk_C60 = 2;

    switch (i_this->unk_2F1) {
        case -1:
            i_this->unk_57C = 1;
            if (!i_this->mpMorf->isStop()) {
                break;
            }
            i_this->unk_2F1 = 0;

        case 0:
            anm_init(i_this, 0x21, 1.0f, 2, 1.0f, 0x11);
            i_this->unk_2F1 = 1;
            i_this->unk_318[0] = 100;

        case 1:
            i_this->unk_57C = 1;

            cLib_addCalcAngleS2(&i_this->actor.current.angle.y, i_this->actor.home.angle.y, 5, 0x300);
            cLib_addCalcAngleS2(&i_this->actor.current.angle.x, 0, 5, 0x800);
            cLib_addCalcAngleS2(&i_this->actor.current.angle.z, 0, 5, 0x800);

            cLib_addCalc2(&i_this->actor.current.pos.x, i_this->actor.home.pos.x, 0.2f, speedX);
            cLib_addCalc2(&i_this->actor.current.pos.z, i_this->actor.home.pos.z, 0.2f, speedZ);

            i_this->actor.current.pos.y = i_this->actor.home.pos.y;
            if ((i_this->unk_318[0] == 0) && bb_player_view_check(i_this)) {
                i_this->unk_2F1 = 2;
                i_this->unk_318[0] = 0x1E;
            }
            break;

        case 2:
            i_this->unk_C60 = 1;
            if (i_this->unk_318[0] != 0) { 
                break;
            }
            i_this->unk_2F1 = 3;
            anm_init(i_this, 0x18, 5.0f , 2, l_bbHIO.unk_24 * 1.5f, 8);
            i_this->unk_318[0] = REG0_S(0) + 70;

        case 3:
            i_this->unk_C60 = 1;
            cLib_addCalcAngleS2(&i_this->actor.current.angle.y, i_this->unk_336, 10, 0x200);

            v.x = 0.0;
            v.y = REG0_F(0) * 10.0f + 300.0f;
            v.z = REG0_F(1) * 10.0f + 300.0f;
            cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
            MtxPosition(&v, &v2);

            cLib_addCalc2(&i_this->actor.current.pos.x, i_this->actor.home.pos.x + v2.x, 0.1f, 10.0f);
            cLib_addCalc2(&i_this->actor.current.pos.y, i_this->actor.home.pos.y + v2.y, 0.1f, 10.0f);
            cLib_addCalc2(&i_this->actor.current.pos.z, i_this->actor.home.pos.z + v2.z, 0.1f, 10.0f);

            if (i_this->unk_318[0] == 0) {
                i_this->unk_2DD = 3;
                i_this->unk_2F1 = 0;
            }
            break;

        case 10:
        case 11:
        case 12: {
            r30 = 0;
            i_this->unk_C60 = 0;
            v.x = 0.0;
            v.y = 0.0;
            v.z = 0.0;
            cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
            MtxPosition(&v, &v2);

            f32 fVar2 = 80.0f;
            if (i_this->unk_2F1 == 10) {
                fVar2 = 300.0f;
            }

            i_this->unk_2F4.x = i_this->actor.home.pos.x + v2.x;
            i_this->unk_2F4.y = i_this->actor.home.pos.y + fVar2;
            i_this->unk_2F4.z = i_this->actor.home.pos.z + v2.z;

            i_this->unk_300 = 20.0f;
            i_this->unk_304 = 5.0f;
            i_this->unk_310 = 2000.0f;

            f32 x = i_this->unk_2F4.x - i_this->actor.current.pos.x;
            f32 y = i_this->unk_2F4.y - i_this->actor.current.pos.y;
            f32 z = i_this->unk_2F4.z - i_this->actor.current.pos.z;
            f32 sqrt = std::sqrtf(x * x + y * y + z * z);

            if (i_this->unk_2F1 == 10) {
                if (sqrt < 2000.0f) {
                    i_this->unk_2F1 = 11;
                }
            } else if (i_this->unk_2F1 == 11) {
                if (sqrt < l_bbHIO.unk_50) {
                    i_this->unk_2F1 = 12;
                    anm_init(i_this, 0x1A, 10.0f, 0, 1.0f, 10);
                }
            } else if (i_this->unk_2F1 == 12 && sqrt < REG0_F(9) * 10.0f + 300.0f) {
                i_this->unk_2F1 = 20;
                anm_init(i_this, 0x1F, 5.0f, 2, l_bbHIO.unk_44, 15);
                i_this->unk_2F0 = 10;
                i_this->actor.speed.y = 0.0f;
                i_this->unk_354 = 0;
                r30 = -1;
            }
            break;
        }
        case 20: {
            i_this->unk_57C = 1;
            i_this->unk_C60 = 0;
            s16 old_354 = i_this->unk_354;
            i_this->unk_354++;

            cLib_addCalc2(&i_this->actor.current.pos.x, i_this->actor.home.pos.x, 0.1f, speedX);
            cLib_addCalc2(&i_this->actor.current.pos.z, i_this->actor.home.pos.z, 0.1f, speedZ);

            i_this->actor.current.pos.y += i_this->actor.speed.y;
            if (old_354 > l_bbHIO.unk_40) {
                i_this->actor.speed.y -= REG0_F(7) + 0.8f;
            }

            cLib_addCalcAngleS2(&i_this->actor.current.angle.x, 0, 5, 0x800);
            cLib_addCalcAngleS2(&i_this->actor.current.angle.y, i_this->actor.home.angle.y, 5, 0x300);
            cLib_addCalcAngleS2(&i_this->actor.current.angle.z, 0, 5, 0x800);
            
            if (i_this->actor.current.pos.y <= i_this->actor.home.pos.y) {
                i_this->actor.current.pos.y = i_this->actor.home.pos.y;
                i_this->actor.speed.y = -0.5;
                if (old_354 > l_bbHIO.unk_40) {
                    anm_init(i_this, 0x20, 5.0f, 0, l_bbHIO.unk_48, 0x10);
                    i_this->unk_2F1 = -1;
                }
            }
            break;
        }
    }

    switch (r30) {
        case 0:
            bb_pos_move(i_this);
            break;
    }
}

/* 00006234-00006278       .text bb_fail_move__FP8bb_class */
void bb_fail_move(bb_class* i_this) {
    fopAcM_createDisappear(&i_this->actor, &i_this->actor.current.pos, 10, 0, i_this->actor.stealItemBitNo);
    fopAcM_delete(&i_this->actor);
}

#if VERSION == VERSION_DEMO
void bb_key_move(bb_class* i_this) {
    f32 stickX = g_mDoCPd_cpadInfo[0].mMainStickPosX;
    f32 stickY = g_mDoCPd_cpadInfo[0].mMainStickPosY;

    switch (i_this->unk_2F0) {
        case 0: {
            s32 frame = i_this->mpMorf->getFrame();
            i_this->unk_300 = 30.0f;
            i_this->unk_304 = 0.5f;

            if (!CPad_CHECK_HOLD_B(0) && frame == REG0_S(0) + 9) {
                i_this->unk_2F0 = 1;
                anm_init(i_this, 25, REG0_F(0) + 12.0f, 2, 1.0f, 9);
            }
            break;
        }
        case 1:
            if (CPad_CHECK_HOLD_X(0)) {
                i_this->unk_300 = 5.0f;
                i_this->unk_304 = 0.2f;
            } else {
                i_this->unk_300 = 20.0f;
                i_this->unk_304 = 0.1f;
            }

            if (CPad_CHECK_HOLD_B(0)) {
                i_this->unk_2F0 = 0;
                anm_init(i_this, 24, 5.0f, 2, l_bbHIO.unk_24, 8);
                fopAcM_monsSeStart(&i_this->actor, JA_SE_CV_BB_NORMAL, 0);
            }
            break;
    }

    s16 x = stickX * (REG0_F(10) + -5.0f) * 1000.0f;
    s16 y = stickY * (REG0_F(11) + 5.0f) * 1000.0f;
    s16 d;
    s16 c;
    s16 a;
    s16 b;

    if (std::fabsf(stickX) > 0.2f) {
        a = 0x200;
        b = 0x800;
    } else {
        a = 0x80;
        b = 0x80;
    }

    if (std::fabsf(stickY) > 0.2f) {
        c = 0x200;
    } else {
        c = 0x80;
    }

    if (y > 0 && i_this->mAcch.ChkGroundHit()) {
        y = 0;
        c = 0x800;
        d = 10;
    } else {
        d = 4;
    }

    cLib_addCalcAngleS2(&i_this->unk_368, x, 10, a);
    cLib_addCalcAngleS2(&i_this->unk_366, y, d, c);
    cLib_addCalc2(&i_this->unk_32C, stickX * (REG0_F(12) + -0.4f) * 1000.0f, 1.0f, 50.0f);

    i_this->actor.current.angle.y += (s16)i_this->unk_32C;

    cLib_addCalcAngleS2(&i_this->actor.current.angle.x, y, d, c);
    cLib_addCalcAngleS2(&i_this->actor.current.angle.z, -x, 5, b);
    cLib_addCalc2(&i_this->actor.speedF, i_this->unk_300, 1.0f, i_this->unk_304);

    cXyz v;
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = i_this->actor.speedF;
    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);
    MtxPosition(&v, &i_this->actor.speed);

    i_this->actor.current.pos.x += i_this->actor.speed.x;
    i_this->actor.current.pos.y += i_this->actor.speed.y;
    i_this->actor.current.pos.z += i_this->actor.speed.z;
}
#endif

/* 00006278-0000696C       .text damage_check__FP8bb_class */
void damage_check(bb_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    daPy_py_c* player = static_cast<daPy_py_c*>(dComIfGp_getPlayer(0));
    cXyz scale;
    JPABaseEmitter* emitter;
    CcAtInfo sp30;
    
    i_this->mStts.Move();

    if ((i_this->mBodyTgSph.ChkTgHit() || i_this->mHeadTgSph.ChkTgHit()) && i_this->unk_340 == 0) {
        i_this->unk_340 = 5;
        
        tex_anm_set(i_this, 2);

        if (i_this->mBodyTgSph.ChkTgHit()) {
            sp30.mpObj = i_this->mBodyTgSph.GetTgHitObj();
            sp30.pParticlePos = i_this->mBodyTgSph.GetTgHitPosP();
        } else if (i_this->mHeadTgSph.ChkTgHit()) {
            sp30.mpObj = i_this->mHeadTgSph.GetTgHitObj();
            sp30.pParticlePos = i_this->mHeadTgSph.GetTgHitPosP();
        }

        if (sp30.mpObj->GetAtType() & (AT_TYPE_LIGHT_ARROW | AT_TYPE_ICE_ARROW)) {
            if (sp30.mpObj->GetAtType() & AT_TYPE_ICE_ARROW) {
                i_this->mEnemyIce.mFreezeDuration = REG0_S(3) + 300;
                i_this->unk_2DD = 3;
                i_this->unk_2F1 = 0;
                anm_init(i_this, 0x16, 0.0f, 0, 1.0f, -1);
            } else {
                i_this->mEnemyIce.mLightShrinkTimer = 1;
            }
            enemy_fire_remove(&i_this->mEnemyFire);
            return;
        }
        
        if (sp30.mpObj->GetAtType() & (AT_TYPE_FIRE_ARROW | AT_TYPE_FIRE)) {
            i_this->mEnemyFire.mFireDuration = REG0_S(2) + 100;
            i_this->unk_340 = 50;
        }

        s8 old_health;
        old_health = a_this->health;

        at_power_check(&sp30);

        if (sp30.mResultingAttackType == 14) {
            a_this->health = 20;
        }

        sp30.mpActor = cc_at_check(a_this, &sp30);

#if VERSION == VERSION_DEMO
        if (sp30.mResultingAttackType == 14) {
            a_this->health = old_health;
        }
#else
        if (sp30.mResultingAttackType == 14) {
            a_this->health = old_health;
            dComIfGp_particle_set(dPa_name::ID_COMMON_STARS_BLOW, sp30.pParticlePos);
        } else if (a_this->health <= 0) {
            dComIfGp_particle_set(dPa_name::ID_COMMON_0010, sp30.pParticlePos);
            scale.x = 2.0f;
            scale.y = 2.0f;
            scale.z = 2.0f;
            dComIfGp_particle_set(dPa_name::ID_COMMON_BIG_HIT, sp30.pParticlePos, &player->shape_angle, &scale);
        } else {
            dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, sp30.pParticlePos, &player->shape_angle);
        }
#endif

        dKy_Sound_set(a_this->current.pos, 100, fpcM_GetID(i_this), 5);

        if (l_bbHIO.unk_04 != 0) {
            a_this->health = 10;
        }

        if (sp30.mbDead) {
            if (a_this->health <= 0) {
                i_this->unk_C7E = 1;
                i_this->unk_2F1 = 0;
                fopAcM_monsSeStart(a_this, JA_SE_CV_BB_FAINTED, 0);
            } else {
                fopAcM_monsSeStart(a_this, JA_SE_CV_BB_DAMAGE, 0);
            }
            i_this->unk_34C = REG0_F(13) * 100.0f + 5000.0f;
        } else {
            i_this->unk_C58 = REG0_F(9) * 200.0f + 10000.0f;
            i_this->unk_34C = REG0_F(13) * 100.0f + 3000.0f;
            fopAcM_monsSeStart(a_this, JA_SE_CV_BB_DAMAGE, 0);
        }

        dComIfGp_particle_setToon(dPa_name::ID_COMMON_0438, &a_this->current.pos, &a_this->current.angle, NULL, 0xFF, NULL, 
            fopAcM_GetRoomNo(a_this), &a_this->tevStr.mColorK0, &a_this->tevStr.mColorK0);
        
        i_this->mParticleCallBack.end();

        emitter = dComIfGp_particle_setToon(dPa_name::ID_COMMON_0439, &a_this->current.pos, &a_this->current.angle, NULL, 0xFF, &i_this->mParticleCallBack, 
            fopAcM_GetRoomNo(a_this));

        if (emitter != NULL) {
            if (sp30.mbDead) {
                emitter->setMaxFrame(REG0_S(7) + 20);
            } else {
                emitter->setMaxFrame(REG0_S(8) + 6);
            }

            emitter->setGlobalPrmColor(a_this->tevStr.mColorK0.r, a_this->tevStr.mColorK0.g, a_this->tevStr.mColorK0.b);
            emitter->setGlobalEnvColor(a_this->tevStr.mColorK0.r, a_this->tevStr.mColorK0.g, a_this->tevStr.mColorK0.b);
        }

        if (sp30.mResultingAttackType == 1) {
            i_this->unk_342 = i_this->unk_336;
            i_this->unk_344 = i_this->unk_338;
        } else {
            i_this->unk_342 = sp30.m0C.y;
            i_this->unk_344 = 0;
        }

        if (i_this->unk_2DD != 3) {
            i_this->unk_2DD = 3;
            i_this->unk_318[1] = l_bbHIO.unk_16 + cM_rndF(l_bbHIO.unk_18 - l_bbHIO.unk_16);
            i_this->unk_35D = 0;
        }

        if (sp30.mbDead) {
            i_this->unk_348 = l_bbHIO.unk_58;
            if (cM_rndF(1.0f) < 0.5f) {
                i_this->unk_350 = cM_rndF(3000.0f) + 5000.0f;
            } else {
                i_this->unk_350 = -(cM_rndF(3000.0f) + 5000.0f);
            }
        } else {
            i_this->unk_348 = l_bbHIO.unk_5C;
            i_this->unk_350 = 0;
        }

        i_this->unk_C7C = 1;
        anm_init(i_this, 0x16, 0.0f, 0, 1.0f, -1);
    }
}

/* 000069A8-00007778       .text daBb_Execute__FP8bb_class */
static BOOL daBb_Execute(bb_class* i_this) {
    s16 z;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    cXyz sp28;
    cXyz sp1C;
    cXyz sp10;

    i_this->mEnemyIce.m02C = REG0_F(5) + 50.0f;

    if (enemy_ice(&i_this->mEnemyIce)) {
        i_this->mpMorf->setPlayMode(J3DFrameCtrl::EMode_NONE);
        i_this->mpMorf->setPlaySpeed(3.0f);
        i_this->mpMorf->play(&i_this->actor.eyePos, 0, 0);
        MtxTrans(i_this->actor.current.pos.x, i_this->actor.current.pos.y, i_this->actor.current.pos.z, false);

        cMtx_YrotM(*calc_mtx, i_this->actor.current.angle.y + i_this->unk_368);
        cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x + i_this->unk_366);
        cMtx_ZrotM(*calc_mtx, i_this->actor.current.angle.z);

        J3DModel* model = i_this->mpMorf->getModel();
        model->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->mpMorf->calc();
        i_this->unk_AA8[0] = i_this->unk_BD4[1];

        tail_control(i_this);
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->actor.current.pos, &i_this->actor.tevStr);

    f32 xDiff = player->current.pos.x - i_this->actor.current.pos.x;
    f32 yDiff = (player->current.pos.y + 100.0f) - i_this->actor.current.pos.y;
    f32 zDiff = player->current.pos.z - i_this->actor.current.pos.z;

    i_this->unk_33C = std::sqrtf(SQUARE(xDiff) + SQUARE(zDiff));
    i_this->unk_336 = cM_atan2s(xDiff, zDiff);
    i_this->unk_338 = -cM_atan2s(yDiff, i_this->unk_33C);

    i_this->unk_352++;
    if (i_this->unk_2F2 != 0) {
        if (dComIfGs_isSwitch(i_this->unk_2F2 - 1, fopAcM_GetRoomNo(&i_this->actor))) {
            i_this->unk_2F2 = 0;
        } else {
            return TRUE;
        }
    }

    i_this->actor.attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    fopAcM_OnStatus(&i_this->actor, fopAcStts_SHOWMAP_e);

    if (l_bbHIO.unk_05 == 0) {
        for (s32 i = 0; i < 6; i++) {
            if (i_this->unk_318[i] != 0) {
                i_this->unk_318[i]--;
            }
        }

        if (i_this->unk_326 != 0) {
            i_this->unk_326--;
        }

        if (i_this->unk_340 != 0) {
            i_this->unk_340--;
        }

        if (i_this->unk_348 > 0.01f) {
            sp28.x = 0.0f;
            sp28.y = 0.0f;
            sp28.z = -i_this->unk_348;

            cMtx_YrotS(*calc_mtx, i_this->unk_342);
            cMtx_XrotM(*calc_mtx, i_this->unk_344);
            MtxPosition(&sp28, &sp1C);

            i_this->actor.current.pos.x += sp1C.x;
            i_this->actor.current.pos.y += sp1C.y;
            i_this->actor.current.pos.z += sp1C.z;

            cLib_addCalc0(&i_this->unk_348, 1.0f, 2.0f);

            i_this->unk_308 = 0.0f;
            i_this->unk_30C = 0.0f;

            i_this->actor.current.angle.y += i_this->unk_350;
            cLib_addCalcAngleS2(&i_this->unk_350, 0, 1, 200);
            
            i_this->mpMorf->play(&i_this->actor.current.pos, 0, 0);
        } else {
            i_this->mpMorf->play(&i_this->actor.current.pos, 0, 0);
            if (i_this->unk_C7E != 0) {
                bb_fail_move(i_this);
            } else if (i_this->unk_35D != 0) {
                bb_path_move(i_this);
#if VERSION == VERSION_DEMO
            } else if (i_this->unk_2DD == 1) {
                bb_key_move(i_this);
#endif
            } else if (i_this->unk_2DD == 3) {
                bb_atack_move(i_this);
            } else if (i_this->unk_2DD == 4) {
                bb_wait_move(i_this);
            } else if (i_this->unk_2DD == 7) {
                bb_su_wait_move(i_this);
            } else {
                bb_auto_move(i_this);
            }
        }
    }

    MtxTrans(i_this->actor.current.pos.x, i_this->actor.current.pos.y + i_this->mEnemyIce.m028, i_this->actor.current.pos.z, false);
    
    s16 x = i_this->unk_C00[0].x / 2;
    z = i_this->unk_C00[0].z / 2;
    
    cMtx_YrotM(*calc_mtx, i_this->actor.current.angle.y + i_this->unk_368 + x);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x + i_this->unk_366 + z);
    cMtx_ZrotM(*calc_mtx, i_this->actor.current.angle.z);

    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(i_this->actor.scale);
    model->setBaseTRMtx(*calc_mtx);

    i_this->mpMorf->calc();

    i_this->unk_AA8[0].x = i_this->unk_BD4[1].x;
    i_this->unk_AA8[0].y = i_this->unk_BD4[1].y;
    i_this->unk_AA8[0].z = i_this->unk_BD4[1].z;

    tail_control(i_this);

    enemy_fire(&i_this->mEnemyFire);

    if (i_this->unk_2DF != 0) {
        switch (i_this->unk_2DF) {
            case 1:
                anm_init(i_this, 0x1C, 1.0f, 2, l_bbHIO.unk_4C, 0xC);
                i_this->unk_2DF = 2;
                break;
            
            case 2: {
                    fopAc_ac_c* ac = fopAcM_SearchByID(i_this->unk_2E8);
                    if (ac != NULL) {
                        i_this->unk_2E4 = ac;
                        i_this->unk_2DF = 3;
                    }
                }
                break;

            case 3: {
                    fopAc_ac_c* ac = i_this->unk_2E4;

                    sp10.x = (i_this->unk_A6C[1].x - i_this->unk_A6C[0].x) / 2.0f + i_this->unk_A6C[0].x;
                    sp10.y = (i_this->unk_A6C[1].y - i_this->unk_A6C[0].y) / 2.0f + i_this->unk_A6C[0].y;
                    sp10.z = (i_this->unk_A6C[1].z - i_this->unk_A6C[0].z) / 2.0f + i_this->unk_A6C[0].z;

                    ac->current.pos = sp10;
                    ac->current.angle = i_this->actor.current.angle;
                    ac->shape_angle = i_this->actor.current.angle;

                    if (i_this->unk_2EC == PROC_MO2 || i_this->unk_2EC == PROC_BK) {
                        damagereaction* dr;

                        if (i_this->unk_2EC == PROC_MO2) {
                            dr = &((mo2_class*)ac)->mDamageReaction;
                            dr->m468 = REG0_F(8) * 10.0f + -110.0f;
                            dr->m46C = REG0_F(9) * 10.0f + 10.0f;
                        } else if (i_this->unk_2EC == PROC_BK) {
                            dr = &((bk_class*)ac)->dr;
                            dr->m468 = REG0_F(8) * 10.0f + -100.0f;
                            dr->m46C = REG0_F(9) * 10.0f;
                        }

                        if (i_this->unk_2E0 != 0) {
                            i_this->unk_2DF = 0;
                            anm_init(i_this, 0x19, 12.0f, 2, 1.0f, 9);
                            dr->mAction = 31;
                            ac->speedF = 40.0f;
                        }
                    }

                }
                break;
        }
    }

    i_this->mHeadTgSph.SetC(i_this->actor.eyePos);
    i_this->mBodyTgSph.SetC(i_this->actor.current.pos);
    i_this->mBodyCoSph.SetC(i_this->actor.current.pos);

    dComIfG_Ccsp()->Set(&i_this->mHeadTgSph);
    dComIfG_Ccsp()->Set(&i_this->mBodyTgSph);
    dComIfG_Ccsp()->Set(&i_this->mBodyCoSph);

    if (i_this->unk_57C == 0) {
        i_this->actor.current.pos.y -= REG0_F(5) + 70.0f;
        i_this->actor.old.pos.y -= REG0_F(5) + 70.0f;

        i_this->mAcch.CrrPos(*dComIfG_Bgsp());

        i_this->actor.current.pos.y += REG0_F(5) + 70.0f;
        i_this->actor.old.pos.y += REG0_F(5) + 70.0f;
    }

    i_this->unk_57C = 0;
    bb_water_check(i_this);

    for (s32 i = 0; i < 11; i++) {
        i_this->unk_C00[i].x = i_this->unk_C00[i].y = i_this->unk_C00[i].z = 0;
    }

    if (i_this->unk_34C > 0.1f) {
        f32 tmp = i_this->unk_34C;

        if (tmp > 4000.0f) {
            tmp = 4000.0f;
        }

        for (s32 i = 0; i < 11; i++) {
            i_this->unk_C00[i].x += tmp * cM_ssin(i_this->unk_352 * (REG0_S(0) + 6000) + (i * (REG0_S(1) + 13000))) * 1.0f;
            i_this->unk_C00[i].y += tmp * cM_ssin(i_this->unk_352 * (REG0_S(3) + 7000) + (i * (REG0_S(4) + 18000))) * 2.0f;
            i_this->unk_C00[i].z += tmp * cM_scos(i_this->unk_352 * (REG0_S(6) + 6500) + (i * (REG0_S(7) + 24000))) * 3.0f;
        }

        cLib_addCalc0(&i_this->unk_34C, 1.0f, REG0_F(16) * 10.0f + 120.0f);
    }

    s16 atan = cM_atan2s(player->current.pos.x - i_this->actor.eyePos.x, player->current.pos.z - i_this->actor.eyePos.z);
    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y - atan);

    sp28.x = 0.0f;
    sp28.y = 0.0f;
    sp28.z = i_this->unk_C58;
    MtxPosition(&sp28, &sp1C);

    i_this->unk_C00[8].z += (s16)sp1C.z;
    i_this->unk_C00[9].z += (s16)sp1C.z;
    i_this->unk_C00[8].y += (s16)(sp1C.x * (REG0_F(10) + 1.0f));
    i_this->unk_C00[9].y += (s16)(sp1C.x * (REG0_F(10) + 1.0f));
    i_this->unk_C00[10].y += (s16)(sp1C.x * (REG0_F(10) + 1.0f));

    cLib_addCalc0(&i_this->unk_C58, 0.1f, (REG0_F(12) + 400.0f) * 100.0f);

    damage_check(i_this);

    if (i_this->unk_C58 > 1.0f) {
        i_this->unk_C60 = 3;
    }

    s16 tmp2 = 0x800;

    if (i_this->unk_C60 != 0) {
        if (i_this->unk_C60 == 1) {
            i_this->unk_C5E = i_this->actor.current.angle.y - atan;
            if (i_this->unk_C5E > 0x3A98) {
                i_this->unk_C5E = 0x3A98;
            } else if (i_this->unk_C5E < -0x3A98) {
                i_this->unk_C5E = -0x3A98;
            }
        } else if (i_this->unk_C60 == 2) {
            if ((i_this->unk_352 & 0xF) == 0 && cM_rndF(1.0f) < 0.4f) {
                i_this->unk_C5E = cM_rndFX(15000.0f);
                tmp2 = 0x200;
            }

            if ((i_this->unk_352 & 0x3F) == 0 && cM_rndF(1.0f) < 0.5f) {
                kuti_open(i_this, 0x30, JA_SE_CV_BB_NORMAL);
            }
        } else if (i_this->unk_C60 == 3) {
            i_this->unk_C5E = i_this->unk_C58 * cM_ssin(i_this->unk_352 * (REG0_S(5) + 9000)) * 5.0f;
            tmp2 = 0x2000;
        }
        i_this->unk_C60 = 0;
    } else {
        i_this->unk_C5E = 0;
    }

    cLib_addCalcAngleS2(&i_this->unk_C5C, i_this->unk_C5E, 2, tmp2);

    i_this->unk_C00[10].x = (i_this->unk_C00[10].x - i_this->unk_C5C) / 2;
    i_this->unk_C00[9].x = (i_this->unk_C00[9].x - i_this->unk_C5C) / 2;

    tmp2 = 0;
    if (i_this->unk_C50 != 0) {
        i_this->unk_C50--;
        tmp2 = 0x2000;

        if (i_this->unk_C50 == i_this->unk_C52 && i_this->unk_C54 != 0) {
            fopAcM_monsSeStart(&i_this->actor, i_this->unk_C54, 0);
        }
    }

    cLib_addCalcAngleS2(&i_this->unk_C4E, tmp2, 3, 0x2000);

    s16 div = i_this->unk_C4E / 8;
    i_this->unk_C00[8].z += div;
    i_this->unk_C00[9].z += div;
    i_this->unk_C00[10].z += div;

    bb_eye_tex_anm(i_this);

    return TRUE;
}

/* 00007778-00007780       .text daBb_IsDelete__FP8bb_class */
static BOOL daBb_IsDelete(bb_class*) {
    return TRUE;
}

/* 00007780-000077EC       .text daBb_Delete__FP8bb_class */
static BOOL daBb_Delete(bb_class* i_this) {
    dComIfG_resDelete(&i_this->mPhase, "Bb");
#if VERSION == VERSION_DEMO
    l_bbHIO.removeHIO();
#endif
    i_this->mParticleCallBack.end();
    enemy_fire_remove(&i_this->mEnemyFire);
#if VERSION > VERSION_DEMO
    if (i_this->actor.heap != NULL) {
        i_this->mpMorf->stopZelAnime();
    }
#endif
    return TRUE;
}

/* 000077EC-00007A68       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* ac) {
    bb_class* i_this = (bb_class*)ac;

    i_this->mpMorf = new mDoExt_McaMorf(
        static_cast<J3DModelData*>(dComIfG_getObjectRes("Bb", BB_BDL_BB)),
        NULL,
        NULL,
        static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes("Bb", BB_BCK_FLY02)),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, 
        dComIfG_getObjectRes("Bb", BB_BAS_FLY02),
        0x80000,
        0x37221203
    );

    if (i_this->mpMorf == NULL || i_this->mpMorf->getModel() == NULL) {
        return FALSE;
    }

    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Bb", BB_BDL_BB_TAIL));
    JUT_ASSERT(DEMO_SELECT(4508, 4535), modelData != NULL);
    
    for (s32 i = 0; i < 9; i++) {
        i_this->unk_A84[i] = mDoExt_J3DModel__create(modelData, 0x80000, 0x33221202);
        if (i_this->unk_A84[i] == NULL) {
            return FALSE;
        }
    }

    J3DAnmTexPattern* btp = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("Bb", bb_tex_anm_idx[4]));
    JUT_ASSERT(DEMO_SELECT(4529, 4556), btp);

    s32 ret = i_this->mBtpAnm.init(i_this->mpMorf->getModel()->getModelData(), btp, 0, 2, 1.0f, 0, -1, false, 0);
    if (ret == 0) {
        return FALSE;
    }
    return TRUE;
}

/* 00007A68-00007F58       .text daBb_Create__FP10fopAc_ac_c */
static cPhs_State daBb_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph head_at_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ dCcG_SE_UNK5,
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
            /* Radius */ 62.5f,
        }},
    };
    static dCcD_SrcSph head_tg_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
#if VERSION == DEMO
            /* SrcGObjTg HitMark */ dCcG_SE_UNK1,
#else
            /* SrcGObjTg HitMark */ 0,
#endif
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
#if VERSION == DEMO
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
#else
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
#endif
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 62.5f,
        }},
    };
    static dCcD_SrcSph body_tg_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
#if VERSION == DEMO
            /* SrcGObjTg HitMark */ dCcG_SE_UNK1,
#else
            /* SrcGObjTg HitMark */ 0,
#endif
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
#if VERSION == DEMO
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
#else
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
#endif
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 62.5f,
        }},
    };
    static dCcD_SrcSph body_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
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
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 87.5f,
        }},
    };

    bb_class* i_this = (bb_class*)a_this;

    cPhs_State ret = dComIfG_resLoad(&i_this->mPhase, "Bb");

    fopAcM_SetupActor(a_this, bb_class);

    if (ret == cPhs_COMPLEATE_e) {
        i_this->unk_2D8 = (fopAcM_GetParam(i_this) >> 0) & 0xFF;
        i_this->unk_2DD = i_this->unk_2D8;
        i_this->unk_2D9 = (fopAcM_GetParam(i_this) >> 8) & 0xFF;
        i_this->unk_2DA = (fopAcM_GetParam(i_this) >> 16) & 0xFF;
        i_this->unk_2DB = (fopAcM_GetParam(i_this) >> 24) & 0xFF;
        i_this->unk_2DC = a_this->home.angle.z;
        a_this->current.angle.x = a_this->current.angle.z = 0;

        if (i_this->unk_2DC == 0xFF) {
            i_this->unk_2DC = 0;
        }

        if (dComIfGs_isEventBit(0x1101) && i_this->unk_2DC != 0 && dComIfGs_isSwitch(i_this->unk_2DC, fopAcM_GetRoomNo(a_this))) {
            return cPhs_ERROR_e;
        }

        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x9FA0)) {
            return cPhs_ERROR_e;
        }

        tex_anm_set(i_this, 4);
        a_this->current.pos.y += REG0_F(5) + 70.0f;
        a_this->home.pos = a_this->current.pos;
        a_this->gbaName = 0x1A;

        a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Bb", 0);
        J3DModel* model = i_this->mpMorf->getModel();

        for (u16 i = 0; i < model->getModelData()->getJointNum(); i++) {
            if (callback_check_index[i] >= 0) {
                model->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
            }
        }

        model->setUserArea(reinterpret_cast<u32>(i_this));

        if (i_this->unk_2DA != 0xFF) {
            i_this->ppd = dPath_GetRoomPath(i_this->unk_2DA, fopAcM_GetRoomNo(a_this));
            if (i_this->ppd == NULL) {
                return cPhs_ERROR_e;
            }

            i_this->unk_35D = i_this->unk_2DA + 1;
            i_this->unk_35F = 1;
        }

        if (i_this->unk_2DB != 0xFF) {
            i_this->unk_2F2 = i_this->unk_2DB + 1;
        }

        if (i_this->unk_2DD == 5 || i_this->unk_2DD == 6) {
            i_this->unk_2DF = 1;

            fopAcM_prm_class* ac = fopAcM_CreateAppend();
            ac->base.position = a_this->current.pos;
            ac->base.angle = a_this->home.angle;
            ac->room_no = fopAcM_GetRoomNo(a_this);
            ac->base.parameters = (fopAcM_GetParam(i_this) & 0xFF000000) | 0xFFFF05;

            if (i_this->unk_2DD == 5) {
                i_this->unk_2E8 = fpcM_Create(PROC_MO2, NULL, ac);
                i_this->unk_2EC = PROC_MO2;
            } else {
                i_this->unk_2E8 = fpcM_Create(PROC_BK, NULL, ac);
                i_this->unk_2EC = PROC_BK;
            }
        } else if (i_this->unk_2D8 == 3) {
            i_this->unk_2DD = 3;
        }

        a_this->cullMtx = i_this->mpMorf->getModel()->getBaseTRMtx();
        fopAcM_SetMin(a_this, -200.0f, -200.0f, -200.0f);
        fopAcM_SetMax(a_this, 200.0f, 200.0f, 200.0f);

        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
        i_this->mAcchCir.SetWall(50.0f, 120.0f);
        
        a_this->health = 2;
        a_this->max_health = 2;

        i_this->mStts.Init(100, 0xFF, a_this);
        i_this->mHeadAtSph.Set(head_at_sph_src);
        i_this->mHeadTgSph.Set(head_tg_sph_src);
        i_this->mBodyTgSph.Set(body_tg_sph_src);
        i_this->mBodyCoSph.Set(body_co_sph_src);

        i_this->mHeadAtSph.SetStts(&i_this->mStts);
        i_this->mHeadTgSph.SetStts(&i_this->mStts);
        i_this->mBodyTgSph.SetStts(&i_this->mStts);
        i_this->mBodyCoSph.SetStts(&i_this->mStts);

        i_this->unk_318[3] = cM_rndF(200.0f) + 300.0f;
        i_this->unk_352 = cM_rndF(10000.0f);
        i_this->mEnemyIce.mpActor = a_this;
        i_this->mEnemyIce.mWallRadius = REG0_F(4) + 50.0f;
        i_this->mEnemyIce.mCylHeight = REG0_F(5) + 80.0f;
        i_this->mEnemyIce.mParticleScale = 1.3f;
        i_this->mEnemyIce.mYOffset = -2.0f;
        i_this->mEnemyFire.mpMcaMorf = i_this->mpMorf;
        i_this->mEnemyFire.mpActor = a_this;

        static u8 fire_j[] = {
            0xB, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x15, 0x1D,
        };
        static f32 fire_sc[] = {
            1.0f, 0.8f, 0.7f, 0.6f, 0.5f, 1.0f, 0.8f, 0.7f, 0.6f, 0.5f,
        };

        for (s32 i = 0; i < 10; i++) {
            i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
            i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
        }

        a_this->stealItemLeft = 3;
        daBb_Execute(i_this);
#if VERSION == VERSION_DEMO
        l_bbHIO.entryHIO("カーゴ鳥");
#endif
    }

    return ret;
}

static actor_method_class l_daBb_Method = {
    (process_method_func)daBb_Create,
    (process_method_func)daBb_Delete,
    (process_method_func)daBb_Execute,
    (process_method_func)daBb_IsDelete,
    (process_method_func)daBb_Draw,
};

actor_process_profile_definition g_profile_BB = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BB,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bb_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BB,
    /* Actor SubMtd */ &l_daBb_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
