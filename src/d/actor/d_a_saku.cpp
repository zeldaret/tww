/**
 * d_a_saku.cpp
 * Object - Brown wooden barricade
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_saku.h"
#include "res/Object/KsakuCo.h"
#include "res/Object/Ksaku_00.h"
#include "res/Object/Knsak_00.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"
#include "f_op/f_op_actor_mng.h"
#include "SSystem/SComponent/c_lib.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "JAZelAudio/JAIZelBasic.h"

class sakuHIO_c : public JORReflexible {
public:
    sakuHIO_c() : mNo(-1) {
        field_0x06 = 70;
        field_0x08 = 70;
        field_0x0A = 65;
        field_0x0C = 7;
        field_0x0E = 1;
        field_0xf = 1;
        field_0x10 = 5;
        field_0x12 = 0xB4;
        field_0x13[0] = 0x69;
        field_0x13[1] = 0x5B;
        field_0x13[2] = 0x30;
        field_0x16 = 0x64;
    }
    virtual ~sakuHIO_c() {}
    void genMessage(JORMContext*) {}

    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x05;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
    /* 0x0E */ u8 field_0x0E;
    /* 0x0F */ u8 field_0xf;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13[0x3];
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
};

static sakuHIO_c l_sakuHIO;

class J3DModelData;
class J3DMaterial;

BOOL matAlphaAnim(J3DModelData*, u8, bool);

/* 000000EC-00000200       .text CreateInit__8daSaku_cFv */
void daSaku_c::CreateInit() {
    for (int i = 0; i < 2; i++) {
        field_0xebc[i] = 0;
        field_0xeac[i] = 0;
        field_0xedc[i][0] = 0xff;
        field_0xedc[i][1] = 0;
        field_0xee0[i] = -1;
        field_0xef0[i] = 2;
    }
    field_0xef4 = 0;
    field_0xeec = 0;
    cullMtx = mpModel[0][0]->getBaseTRMtx();
    mStts.Init(0xff, 0xff, this);
    setCol();
    setMtx();
    for (int i = 0; i < 2; i++) {
        field_0x290[i].setColor(dust_color);
        field_0x290[i].setRateOff(1);
    }
}

/* 00000200-000003A8       .text saku_draw_sub__8daSaku_cFi */
int daSaku_c::saku_draw_sub(int i_no) {
    bool flag = true;
    if (field_0xedc[i_no][0] < l_sakuHIO.field_0x16) {
        flag = false;
    }
    if (m_heap[i_no][0] != 0 && mpModel[i_no][0] != 0 && field_0xedc[i_no][0] != 0) {
        g_env_light.settingTevStruct(0, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpModel[i_no][0], &tevStr);
        matAlphaAnim(mpModel[i_no][0]->getModelData(), field_0xedc[i_no][0], flag);
        j3dSys.mDrawBuffer[0] = g_dComIfG_gameInfo.drawlist.mpOpaListBG;
        j3dSys.mDrawBuffer[1] = g_dComIfG_gameInfo.drawlist.mpXluListBG;
        mDoExt_modelUpdateDL(mpModel[i_no][0]);
        j3dSys.mDrawBuffer[0] = g_dComIfG_gameInfo.drawlist.mpOpaList;
        j3dSys.mDrawBuffer[1] = g_dComIfG_gameInfo.drawlist.mpXluList;
        matAlphaAnim(mpModel[i_no][0]->getModelData(), 0xff, true);
    }
    if (m_heap[i_no][1] != 0 && mpModel[i_no][1] != 0 && field_0xedc[i_no][1] != 0) {
        g_env_light.settingTevStruct(0, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpModel[i_no][1], &tevStr);
        matAlphaAnim(mpModel[i_no][1]->getModelData(), 0xff, flag ? false : true);
        mDoExt_modelUpdateDL(mpModel[i_no][1]);
        matAlphaAnim(mpModel[i_no][1]->getModelData(), 0xff, true);
    }
    return 1;
}

/* 000003A8-00000590       .text mode_break_none__8daSaku_cFi */
BOOL daSaku_c::mode_break_none(int i) {
    u32 b_burn = false;
    u32 b_break = false;
    for (int j = 0; j < 3; j++) {
        dCcD_Cyl* cyl = &field_0x30c[i][j];
        if (cyl->ChkTgHit()) {
            cCcD_Obj* hitObj = cyl->GetTgHitObj();
            if (hitObj != NULL) {
                if (mSturdinessType == 0) {
                    b_break |= hitObj->ChkAtType(AT_TYPE_SWORD) || hitObj->ChkAtType(AT_TYPE_UNK8) ||
                               hitObj->ChkAtType(AT_TYPE_BOMB) || hitObj->ChkAtType(AT_TYPE_MACHETE) ||
                               hitObj->ChkAtType(AT_TYPE_UNK800) ||
                               hitObj->ChkAtType(AT_TYPE_DARKNUT_SWORD) ||
                               hitObj->ChkAtType(AT_TYPE_MOBLIN_SPEAR) ||
                               hitObj->ChkAtType(AT_TYPE_SKULL_HAMMER);
                } else if (mSturdinessType == 1) {
                    b_break |= hitObj->ChkAtType(AT_TYPE_MACHETE) || hitObj->ChkAtType(AT_TYPE_BOMB) ||
                               hitObj->ChkAtType(AT_TYPE_UNK800) ||
                               hitObj->ChkAtType(AT_TYPE_DARKNUT_SWORD);
                }
                if (b_break) {
                    dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                }
                b_burn |= hitObj->ChkAtType(AT_TYPE_FIRE) || hitObj->ChkAtType(AT_TYPE_UNK20000) ||
                          hitObj->ChkAtType(AT_TYPE_FIRE_ARROW);
                if (b_burn) {
                    break;
                }
            }
        }
    }
    if (b_burn) {
        return burn();
    } else if (b_break) {
        if (i == 1 && field_0xef8[0] == 1) {
            broken(0);
        }
        return broken(i);
    }
    return TRUE;
}

/* 000005CC-000006A8       .text mode_break_fire__8daSaku_cFi */
BOOL daSaku_c::mode_break_fire(int i) {
    if (field_0xebc[0] > m_saku_alpha_out_time) {
        cLib_chaseUC(&field_0xedc[i][1], 0xff, (u8)l_sakuHIO.field_0x10);
        if (cLib_chaseUC(&field_0xedc[i][0], 0, (u8)l_sakuHIO.field_0x10)) {
            if (m_heap[i][0]) {
                if (m_heap[i][0]) {
                    if (field_0xef0[i]) {
                        field_0xef0[i]--;
                        if (!field_0xef0[i]) {
                            mDoExt_destroySolidHeap(m_heap[i][0]);
                            m_heap[i][0] = NULL;
                            mpModel[i][0] = NULL;
                        }
                    }
                }
            }
        }
    }
    return TRUE;
}

/* 000006A8-0000083C       .text mode_break_throw_obj__8daSaku_cFi */
BOOL daSaku_c::mode_break_throw_obj(int i) {
    if (m_heap[i][0] != 0 && m_heap[i][1] != 0 && field_0xef0[i] != 0) {
        field_0xef0[i]--;
        if (field_0xef0[i] == 0) {
            mDoExt_destroySolidHeap(m_heap[i][0]);
            m_heap[i][0] = NULL;
            mpModel[i][0] = NULL;
        }
    }
    if (field_0xebc[i] >= m_alpha_start_time && field_0x290[i].getEmitter() != 0) {
        cLib_chaseF(&field_0xeb4[i], 0.0f,
                    (f32)l_sakuHIO.field_0x12 / (255.0f * (f32)m_fade_time));
        field_0xeb4[i] = fabs(field_0xeb4[i]);
        u8 alpha = 255.0f * field_0xeb4[i];
        field_0x290[i].getEmitter()->setGlobalAlpha(alpha);
        if (alpha == 0) {
            field_0x290[i].end();
            field_0xeac[i] = 0;
        }
    }
    return TRUE;
}

/* 0000083C-000008EC       .text RecreateHeap__8daSaku_cFii */
BOOL daSaku_c::RecreateHeap(int heap_id, int saku_id) {
    JUT_ASSERT(869, m_heap[saku_id][heap_id] != 0);
    m_heap[saku_id][heap_id]->freeAll();
    JKRHeap* old_heap = mDoExt_setCurrentHeap(m_heap[saku_id][heap_id]);
    CreateHeap(1, saku_id);
    mDoExt_setCurrentHeap(old_heap);
    return TRUE;
}

/* 000008EC-000009B0       .text CreateHeap__8daSaku_cFii */
BOOL daSaku_c::CreateHeap(int heap_id, int saku_id) {
    int model_idx = heap_id;
    switch (field_0xef8[saku_id]) {
    case 1:
        model_idx = 0;
        break;
    case 3:
        model_idx = 2;
        break;
    case 2:
        model_idx = 1;
        break;
    }
    if (loadModel(model_idx, heap_id, saku_id) == 0) {
        return FALSE;
    }
    return loadMoveBG(GetDzbId(saku_id), heap_id, saku_id) != 0 ? 1 : 0;
}

/* 000009B0-00000A4C       .text GetDzbId__8daSaku_cFi */
int daSaku_c::GetDzbId(int i_idx) {
    s32 val = field_0xef8[i_idx];
    int ret;
    if (i_idx == 1 || field_0xef8[1] == 0) {
        if (val == 1) {
            ret = 0;
        } else {
            ret = 1;
        }
    } else if (val == 3 || val == 2) {
        ret = 3;
    } else if (fopAcM_isSwitch(this, mTopHalfDestroyedSwitch)) {
        ret = 4;
    } else {
        ret = 2;
    }
    return ret;
}

/* 00000A4C-00000ADC       .text CreateDummyHeap__8daSaku_cFi */
BOOL daSaku_c::CreateDummyHeap(int i_no) {
    int model_idx;
    if (mSturdinessType == 0) {
        model_idx = 0;
    } else {
        model_idx = i_no;
        if (mSturdinessType == 1) {
            model_idx = 1;
        }
    }
    if (loadModel(model_idx, 1, i_no) == 0) {
        return FALSE;
    }
    return loadMoveBG(1, 1, i_no) != 0 ? 1 : 0;
}

/* 00000ADC-00000BE8       .text loadMoveBG__8daSaku_cFiii */
BOOL daSaku_c::loadMoveBG(int dzb_id, int heap_id, int saku_id) {
    int dzb_idx[5] = {
        dRes_INDEX_KSAKUCO_DZB_KSAKU_00_e, dRes_INDEX_KSAKUCO_DZB_KSAKU_01_e,
        dRes_INDEX_KSAKUCO_DZB_KSAKU_02_e, dRes_INDEX_KSAKUCO_DZB_KSAKU_03_e,
        dRes_INDEX_KSAKUCO_DZB_KSAKU_00_e,
    };
    field_0xe34[saku_id][heap_id] = new dBgW();
    if (field_0xe34[saku_id][heap_id] != 0) {
        return field_0xe34[saku_id][heap_id]->Set(
                   (cBgD_t*)dComIfG_getObjectRes(m_arcname[0], dzb_idx[dzb_id]),
                   cBgW::MOVE_BG_e, &field_0xe4c[saku_id]) != true ? 1 : 0;
    }
    return FALSE;
}

/* 00000BE8-00000D7C       .text loadModel__8daSaku_cFiii */
BOOL daSaku_c::loadModel(int i_idx, int heap_id, int saku_id) {
    int res_idx0[6] = {
        dRes_INDEX_KSAKU_00_BDL_KSAKU_00_e, dRes_INDEX_KSAKU_00_BDL_KSAKU_04_e,
        dRes_INDEX_KSAKU_00_BDL_KSAKU_02_e, dRes_INDEX_KSAKU_00_BDL_KSAKU_01_e,
        dRes_INDEX_KSAKU_00_BDL_KSAKU_03_e, dRes_INDEX_KSAKU_00_BDL_KSAKU_05_e,
    };
    int res_idx1[6] = {
        dRes_INDEX_KNSAK_00_BDL_KNSAK_00_e, dRes_INDEX_KNSAK_00_BDL_KNSAK_02_e,
        dRes_INDEX_KNSAK_00_BDL_KNSAK_01_e, dRes_INDEX_KNSAK_00_BDL_KNSAK_03_e,
        dRes_INDEX_KNSAK_00_BDL_KNSAK_05_e, dRes_INDEX_KNSAK_00_BDL_KNSAK_04_e,
    };
    if (saku_id == 1) {
        i_idx += 3;
    }
    J3DModelData* modelData;
    if (mSturdinessType == 0) {
        modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname[1], res_idx0[i_idx]);
    } else if (mSturdinessType == 1) {
        modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname[2], res_idx1[i_idx]);
    }
    JUT_ASSERT(1085, modelData != 0);
    mpModel[saku_id][heap_id] = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpModel[saku_id][heap_id] == 0) {
        return FALSE;
    }
    return TRUE;
}

/* 00000D7C-00000E8C       .text burn__8daSaku_cFv */
BOOL daSaku_c::burn() {
    if (field_0xef4 == 0) {
        if (field_0xef8[0] == 1) {
            field_0xef8[0] = 2;
            RecreateHeap(1, 0);
            field_0xee0[0] = 0x32;
        }
        if (field_0xef8[1] == 1) {
            field_0xef8[1] = 2;
            RecreateHeap(1, 1);
            field_0xee0[1] = 0x32;
        }
        if (mpModel[0][1] != 0) {
            cullMtx = mpModel[0][1]->getBaseTRMtx();
        } else if (mpModel[1][1] != 0) {
            cullMtx = mpModel[1][1]->getBaseTRMtx();
        }
        setEffFire(0);
        field_0xeec = 0x5a;
        dComIfGs_onSwitch(mBottomHalfDestroyedSwitch, home.roomNo);
        if (field_0xef8[1] != 0) {
            dComIfGs_onSwitch(mTopHalfDestroyedSwitch, home.roomNo);
        }
        field_0xef4 = 1;
    }
    return TRUE;
}

/* 00000E8C-00000F60       .text broken__8daSaku_cFi */
BOOL daSaku_c::broken(int i) {
    setEffBreak(i);
    field_0xef8[i] = 3;
    field_0xee0[i] = 0;
    if (i == 0) {
        dComIfGs_onSwitch(mBottomHalfDestroyedSwitch, home.roomNo);
    } else {
        dComIfGs_onSwitch(mTopHalfDestroyedSwitch, home.roomNo);
    }
    RecreateHeap(1, i);
    if (i == 0) {
        cullMtx = mpModel[i][1]->getBaseTRMtx();
    }
    field_0xedc[i][0] = 0;
    field_0xedc[i][1] = 0xff;
    return TRUE;
}

/* 00000F60-00000FF4       .text changeCollision__8daSaku_cFi */
BOOL daSaku_c::changeCollision(int i_no) {
    if (field_0xef8[i_no] == 0) {
        return FALSE;
    }
    if (field_0xee0[i_no] >= 0) {
        if (field_0xee0[i_no] == 0) {
            dComIfG_Bgsp()->Release(field_0xe44[i_no]);
            MoveBGResist(1, i_no);
        }
        field_0xee0[i_no]--;
    }
    return TRUE;
}

/* 00000FF4-0000113C       .text setMtx__8daSaku_cFv */
void daSaku_c::setMtx() {
    for (int i = 0; i < 2; i++) {
        J3DModel* model = mpModel[0][i];
        if (model != 0) {
            model->setBaseScale(scale);
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::ZXYrotM(shape_angle);
            model->setBaseTRMtx(mDoMtx_stack_c::get());
        }
    }
    if (field_0xef8[1] != 0) {
        for (int i = 0; i < 2; i++) {
            J3DModel* model = mpModel[1][i];
            if (model != 0) {
                model->setBaseScale(scale);
                mDoMtx_stack_c::transS(current.pos.x, 200.0f + current.pos.y, current.pos.z);
                mDoMtx_stack_c::ZXYrotM(shape_angle);
                model->setBaseTRMtx(mDoMtx_stack_c::get());
            }
        }
    }
}

/* 0000113C-0000120C       .text setMoveBGMtx__8daSaku_cFv */
void daSaku_c::setMoveBGMtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
    MTXCopy(mDoMtx_stack_c::get(), field_0xe4c[0]);
    if (field_0xef8[1] != 0) {
        mDoMtx_stack_c::transS(current.pos.x, 200.0f + current.pos.y, current.pos.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
        MTXCopy(mDoMtx_stack_c::get(), field_0xe4c[1]);
    }
}

/* 0000120C-0000134C       .text checkCol__8daSaku_cFv */
void daSaku_c::checkCol() {
    if (field_0xeec != 0) {
        for (int i = 0; i < 3; i++) {
            field_0xa74[i].SetC(field_0xa2c[0][i]);
            dComIfG_Ccsp()->Set(&field_0xa74[i]);
        }
    }
    if (field_0xef8[0] == 1) {
        for (int i = 0; i < 3; i++) {
            field_0x30c[0][i].SetC(field_0xa2c[0][i]);
            dComIfG_Ccsp()->Set(&field_0x30c[0][i]);
        }
    }
    if (field_0xef8[1] != 0) {
        if (field_0xef8[1] == 1) {
            for (int i = 0; i < 3; i++) {
                field_0x30c[1][i].SetC(field_0xa2c[1][i]);
                dComIfG_Ccsp()->Set(&field_0x30c[1][i]);
            }
        }
    }
}

/* 0000134C-00001510       .text setCol__8daSaku_cFv */
void daSaku_c::setCol() {
    field_0xa2c[0][0].set(0.0f, 20.0f, 0.0f);
    field_0xa2c[0][1].set(-100.0f, 20.0f, 0.0f);
    field_0xa2c[0][2].set(100.0f, 20.0f, 0.0f);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    for (int i = 0; i < 3; i++) {
        mDoMtx_stack_c::multVec(&field_0xa2c[0][i], &field_0xa2c[0][i]);
        field_0x30c[0][i].Set(m_cyl_src);
        field_0x30c[0][i].SetStts(&mStts);
    }
    if (field_0xef8[1] != 0) {
        field_0xa2c[1][0].set(0.0f, 220.0f, 0.0f);
        field_0xa2c[1][1].set(-100.0f, 220.0f, 0.0f);
        field_0xa2c[1][2].set(100.0f, 220.0f, 0.0f);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(shape_angle);
        for (int i = 0; i < 3; i++) {
            mDoMtx_stack_c::multVec(&field_0xa2c[1][i], &field_0xa2c[1][i]);
            field_0x30c[1][i].Set(m_cyl_src);
            field_0x30c[1][i].SetStts(&mStts);
        }
    }
}

/* 00001510-00001598       .text MoveBGResist__8daSaku_cFii */
BOOL daSaku_c::MoveBGResist(int i_idx, int i_no) {
    if (dComIfG_Bgsp()->Regist(field_0xe34[i_no][i_idx], this)) {
        return FALSE;
    }
    field_0xe44[i_no] = field_0xe34[i_no][i_idx];
    field_0xe44[i_no]->Move();
    return TRUE;
}

/* 00001598-000016C0       .text setEffFire__8daSaku_cFi */
BOOL daSaku_c::setEffFire(int) {
    cXyz pos = current.pos;
    dPa_control_c* pa;
    pa = g_dComIfG_gameInfo.play.getParticle();
    pa->set(0, dPa_name::ID_IT_JN_SK_FIRE_A, &pos, &current.angle, NULL, 0xff, NULL, -1, NULL, NULL, NULL);
    pa = g_dComIfG_gameInfo.play.getParticle();
    pa->set(0, dPa_name::ID_IT_JT_SK_SMOKE, &pos, &current.angle, NULL, m_smoke_alpha, NULL, -1, NULL, NULL, NULL);
    field_0xebc[1] = 1;
    field_0xebc[0] = 1;
    s8 reverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
    JAIZelBasic::getInterface()->seStart(JA_SE_OBJ_BURN_WRAILING, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
    return TRUE;
}

/* 000016C0-000019AC       .text setEffBreak__8daSaku_cFi */
BOOL daSaku_c::setEffBreak(int i) {
    cXyz pos = current.pos;
    pos.y += 100.0f;
    if (i == 1) {
        pos.y += 200.0f;
    }
    if (l_sakuHIO.field_0xf != 0) {
        dPa_control_c* pa = g_dComIfG_gameInfo.play.getParticle();
        pa->set(0, dPa_name::ID_IT_JN_SK_HAHEN_A, &pos, &current.angle, &scale, 0xff, NULL, -1,
                (GXColor*)&tevStr.mColorK0, (GXColor*)&tevStr.mColorK0, NULL);
    }
    field_0xeb4[i] = (f32)l_sakuHIO.field_0x12 / 255.0f;
    dust_color.r = l_sakuHIO.field_0x13[0];
    dust_color.g = l_sakuHIO.field_0x13[1];
    dust_color.b = l_sakuHIO.field_0x13[2];
    field_0xec4[i] = pos;
    dComIfGp_particle_setToon(dPa_name::ID_AK_JT_ELEMENTSMOKE01, &field_0xec4[i], &current.angle,
                              NULL, l_sakuHIO.field_0x12, &field_0x290[i], fopAcM_GetRoomNo(this));
    if (field_0x290[i].getEmitter() != NULL) {
        field_0x290[i].getEmitter()->setGlobalAlpha(255.0f * field_0xeb4[i]);
        field_0x290[i].getEmitter()->becomeImmortalEmitter();
        cXyz dynScale(2.0f, 2.0f, 2.0f);
        cXyz emitScale(1.0f, 0.5f, 0.7f);
        field_0x290[i].getEmitter()->setGlobalParticleScale(3.2f, 3.2f);
        field_0x290[i].getEmitter()->setGlobalDynamicsScale(dynScale);
        field_0x290[i].getEmitter()->setEmitterScale(emitScale);
        field_0x290[i].getEmitter()->setRate(40.0f);
        field_0x290[i].getEmitter()->setMaxFrame(1);
    }
    if (mSturdinessType == 0) {
        s8 reverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
        JAIZelBasic::getInterface()->seStart(JA_SE_OBJ_COL_BRK_WRAILING, &eyePos, 0, reverb,
                                             1.0f, 1.0f, -1.0f, -1.0f, 0);
    } else if (mSturdinessType == 1) {
        s8 reverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
        JAIZelBasic::getInterface()->seStart(JA_SE_OBJ_BRK_WRAIL_K, &eyePos, 0, reverb,
                                             1.0f, 1.0f, -1.0f, -1.0f, 0);
    }
    field_0xebc[i] = 1;
    return TRUE;
}

static void changeXluMaterialAlpha(J3DMaterial*, u8, bool);

/* 000019AC-00001A50       .text matAlphaAnim__FP12J3DModelDataUcb */
BOOL matAlphaAnim(J3DModelData* modelData, u8 alpha, bool flag) {
    JUT_ASSERT(1489, modelData != 0);
    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        changeXluMaterialAlpha(modelData->getMaterialNodePointer(i), alpha, flag);
    }
    return TRUE;
}

/* 00001A50-00001B98       .text changeXluMaterialAlpha__FP11J3DMaterialUcb */
static void changeXluMaterialAlpha(J3DMaterial* i_material, u8 i_alpha, bool i_flag) {
    JUT_ASSERT(1535, i_material != 0);
    static J3DBlendInfo l_blendInfo = {1, 4, 5, 7};
    static J3DZModeInfo l_zmodeInfo = {1, 3, 0};
    static J3DZModeInfo l_zmodeInfo2 = {1, 3, 1};

    J3DPEBlock* pe = i_material->getPEBlock();
    i_material->getTevKColor(3)->mColor.a = i_alpha;
    pe->getBlend()->setBlendInfo(l_blendInfo);
    if (i_flag) {
        pe->getZMode()->setZModeInfo(l_zmodeInfo2);
    } else {
        pe->getZMode()->setZModeInfo(l_zmodeInfo);
    }
}

const char* daSaku_c::m_arcname[3] = {"KsakuCo", "Ksaku_00", "Knsak_00"};
u8 daSaku_c::m_smoke_alpha = 0xE6;
s32 daSaku_c::m_alpha_start_time = 10;
s32 daSaku_c::m_saku_alpha_out_time = 10;
s32 daSaku_c::m_fade_time = 40;
GXColor daSaku_c::dust_color = {0x69, 0x5B, 0x30, 0xFF};

/* 00001B98-00001BB8       .text daSaku_Create__FP10fopAc_ac_c */
static cPhs_State daSaku_Create(fopAc_ac_c* i_this) {
    return ((daSaku_c*)i_this)->_daSaku_create();
}

/* 00001BB8-00001F28       .text _daSaku_create__8daSaku_cFv */
cPhs_State daSaku_c::_daSaku_create() {
    s32 size = 0;
    fopAcM_SetupActor(this, daSaku_c);

    mSturdinessType = daSaku_prm::getType(this);

    int model_idx = 2;
    if (mSturdinessType == 0) {
        model_idx = 1;
    }
    cPhs_State phase = (cPhs_State)dComIfG_resLoad(&field_0xe04[0], m_arcname[model_idx]);
    if (phase != cPhs_COMPLEATE_e) {
        return phase;
    }
    phase = (cPhs_State)dComIfG_resLoad(&field_0xe04[1], m_arcname[0]);
    if (phase != cPhs_COMPLEATE_e) {
        return phase;
    }

    mBottomHalfDestroyedSwitch = daSaku_prm::getSwitchNo(this);
    mTopHalfDestroyedSwitch = daSaku_prm::getSwitchNo2(this);
    field_0xef8[0] = 1;
    if (fopAcM_isSwitch(this, mBottomHalfDestroyedSwitch)) {
        field_0xef8[0] = 3;
    }
    field_0xef8[1] = 0;
    if (daSaku_prm::checkSaku2(this)) {
        field_0xef8[1] = 1;
        if (fopAcM_isSwitch(this, mTopHalfDestroyedSwitch)) {
            field_0xef8[1] = 3;
        }
    }
    setMoveBGMtx();

    for (int i = 0; i < 2; i++) {
        if (field_0xef8[i] != 0) {
            m_heap[i][0] = mDoExt_createSolidHeapFromGameToCurrent(0x2280, 0x20);
            if (m_heap[i][0] == NULL) {
                return cPhs_ERROR_e;
            }
            BOOL res = CreateHeap(0, i);
            if (res) {
                MoveBGResist(0, i);
            }
            mDoExt_restoreCurrentHeap();
            size += mDoExt_adjustSolidHeap(m_heap[i][0]);
            if (!res) {
                return cPhs_ERROR_e;
            }
            mpModel[i][1] = NULL;
            if (field_0xef8[i] == 1) {
                m_heap[i][1] = mDoExt_createSolidHeapFromGameToCurrent(0x2280, 0x20);
                if (m_heap[i][1] == NULL) {
                    return cPhs_ERROR_e;
                }
                BOOL res2 = CreateDummyHeap(i);
                mpModel[i][1] = NULL;
                mDoExt_restoreCurrentHeap();
                size += mDoExt_adjustSolidHeap(m_heap[i][1]);
                if (!res2) {
                    return cPhs_ERROR_e;
                }
            }
        }
    }
    CreateInit();
    if (l_sakuHIO.mNo < 0) {
        l_sakuHIO.mNo = mDoHIO_createChild("柵", &l_sakuHIO);
    }
    return cPhs_COMPLEATE_e;
}

BOOL daSaku_c::_daSaku_delete() {
    if (l_sakuHIO.mNo >= 0) {
        mDoHIO_deleteChild(l_sakuHIO.mNo);
        l_sakuHIO.mNo = -1;
    }
    for (int i = 0; i < 2; i++) {
        field_0x290[i].end();
    }
    for (int i = 0; i < 2; i++) {
        if (field_0xef8[i] != 0) {
            dComIfG_Bgsp()->Release(field_0xe44[i]);
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (m_heap[i][j] != 0) {
                mDoExt_destroySolidHeap(m_heap[i][j]);
                m_heap[i][j] = NULL;
                mpModel[i][j] = NULL;
            }
        }
    }
    dComIfG_resDelete(&field_0xe04[1], m_arcname[0]);
    if (mSturdinessType == 0) {
        dComIfG_resDelete(&field_0xe04[0], m_arcname[1]);
    } else {
        dComIfG_resDelete(&field_0xe04[0], m_arcname[2]);
    }
    return TRUE;
}

/* 00002264-000023D8       .text daSaku_Delete__FP8daSaku_c */
static BOOL daSaku_Delete(daSaku_c* i_this) {
    return i_this->_daSaku_delete();
}

/* 000023D8-000023E0       .text daSaku_IsDelete__FP8daSaku_c */
static BOOL daSaku_IsDelete(daSaku_c*) {
    return TRUE;
}

BOOL daSaku_c::_daSaku_draw() {
    saku_draw_sub(0);
    if (field_0xef8[1] != 0) {
        saku_draw_sub(1);
    }
    return TRUE;
}

/* 000023E0-0000242C       .text daSaku_Draw__FP8daSaku_c */
static BOOL daSaku_Draw(daSaku_c* i_this) {
    return i_this->_daSaku_draw();
}

BOOL daSaku_c::_daSaku_execute() {
    for (int i = 0; i < 2; i++) {
        if (field_0xebc[i] && field_0xebc[i] < m_max_particle_timer) {
            field_0xebc[i]++;
        }
    }
    if (field_0xeec != 0) {
        field_0xeec--;
    }
    field_0xee8++;
    for (int i = 0; i < 2; i++) {
        switch (field_0xef8[i]) {
        case 0:
            break;
        case 1:
            mode_break_none(i);
            break;
        case 3:
            mode_break_throw_obj(i);
            break;
        case 2:
            mode_break_fire(i);
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < 2; i++) {
        changeCollision(i);
    }
    setMtx();
    checkCol();
    return TRUE;
}

// These const statics must be defined here, between the _daSaku_execute
// inline body (parsed above, initializer not yet visible, so the
// m_max_particle_timer read stays a memory load) and the daSaku_Execute
// dispatcher that instantiates it (definition already seen by codegen,
// so the objects land in .rodata). Defining them earlier folds the load
// into an immediate; defining them later demotes them to .data.
const s32 daSaku_c::m_max_particle_timer = 2000;
const u8 daSaku_c::m_start_alpha = 0xB4;
const u16 daSaku_c::m_alpha_spd = 5;
const f32 daSaku_c::m_saku_height = 200.0f;

const dCcD_SrcCyl daSaku_c::m_at_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_FIRE | AT_TYPE_UNK20000,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
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
        /* Radius */ 50.0f,
        /* Height */ 400.0f,
    }},
};

/* 0000242C-00002560       .text daSaku_Execute__FP8daSaku_c */
static BOOL daSaku_Execute(daSaku_c* i_this) {
    return i_this->_daSaku_execute();
}

const dCcD_SrcCyl daSaku_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_SWORD | AT_TYPE_UNK8 | AT_TYPE_BOMB | AT_TYPE_FIRE | AT_TYPE_MACHETE | AT_TYPE_UNK800 | AT_TYPE_SKULL_HAMMER | AT_TYPE_UNK20000 | AT_TYPE_FIRE_ARROW,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 50.0f,
        /* Height */ 200.0f,
    }},
};

static actor_method_class l_daSaku_Method = {
    (process_method_func)daSaku_Create,
    (process_method_func)daSaku_Delete,
    (process_method_func)daSaku_Execute,
    (process_method_func)daSaku_IsDelete,
    (process_method_func)daSaku_Draw,
};

actor_process_profile_definition g_profile_SAKU = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_SAKU_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daSaku_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_SAKU_e,
    /* Actor SubMtd */ &l_daSaku_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_9_e,
};
