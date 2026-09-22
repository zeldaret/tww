/**
 * d_a_saku.cpp
 * Object - Brown wooden barricade
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_saku.h"
#include "d/d_cc_d.h"

static sakuHIO_c l_sakuHIO;

class J3DModelData;
class J3DMaterial;

/* 000000EC-00000200       .text CreateInit__8daSaku_cFv */
void daSaku_c::CreateInit() {
    for (int i = 0; i < 2; i++) {
        mParticleTimers[i] = 0;
        field_0xEAC[i] = 0;

        field_0xEDC[i][0] = 0xff;
        field_0xEDC[i][1] = 0;

        field_0xEE0[i] = 0xffffffff;
        field_0xEF0[i] = 2;
    }

    field_0xEF4 = 0;
    field_0xEEC = 0;
    cullMtx = mModels[0][0]->getBaseTRMtx();
    mStts.Init(0xff, 0xff, this);
    setCol();
    setMtx();

    for (int i = 0; i < 2; i++) {
        field_0x290[i].setColor(dust_color);
        field_0x290[i].setRateOff(1);
    }

    return;
}

/* 00000200-000003A8       .text saku_draw_sub__8daSaku_cFi */
int daSaku_c::saku_draw_sub(int i_sakuId) {
    bool flag = true;
    if (field_0xEDC[i_sakuId][0] < l_sakuHIO.dustColor.a) {
        flag = false;
    }

    if (m_heap[i_sakuId][0] != NULL && mModels[i_sakuId][0] != NULL && field_0xEDC[i_sakuId][0] != NULL) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mModels[i_sakuId][0], &tevStr);

        matAlphaAnim(mModels[i_sakuId][0]->getModelData(), field_0xEDC[i_sakuId][0], flag);

        j3dSys.mDrawBuffer[0] = g_dComIfG_gameInfo.drawlist.mpOpaListBG;
        j3dSys.mDrawBuffer[1] = g_dComIfG_gameInfo.drawlist.mpXluListBG;

        mDoExt_modelUpdateDL(mModels[i_sakuId][0]);

        j3dSys.mDrawBuffer[0] = g_dComIfG_gameInfo.drawlist.mpOpaList;
        j3dSys.mDrawBuffer[1] = g_dComIfG_gameInfo.drawlist.mpXluList;

        matAlphaAnim(mModels[i_sakuId][0]->getModelData(), 0xff, true);
    }

    if (m_heap[i_sakuId][1] != NULL && mModels[i_sakuId][1] != NULL && field_0xEDC[i_sakuId][1] != NULL) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mModels[i_sakuId][1], &tevStr);

        matAlphaAnim(mModels[i_sakuId][1]->getModelData(), 0xff, flag ? false : true);
        mDoExt_modelUpdateDL(mModels[i_sakuId][1]);
        matAlphaAnim(mModels[i_sakuId][1]->getModelData(), 0xff, true);
    }

    return 1;
}

/* 000003A8-00000590       .text mode_break_none__8daSaku_cFi */
BOOL daSaku_c::mode_break_none(int i_sakuId) {
    u32 burned = FALSE;
    u32 broke = FALSE;

    for (int i = 0; i < 3; i++) {
        dCcD_GObjInf* this_00 = &field_0x30C[i_sakuId][i];

        if (this_00->ChkTgHit() != NULL) {
            cCcD_Obj* hitObj = this_00->GetTgHitObj();

            if (hitObj != NULL) {
                if (mSturdinessType == 0) {
                    broke |= hitObj->ChkAtType(AT_TYPE_SWORD) || hitObj->ChkAtType(AT_TYPE_UNK8) || hitObj->ChkAtType(AT_TYPE_BOMB) ||
                             hitObj->ChkAtType(AT_TYPE_MACHETE) || hitObj->ChkAtType(AT_TYPE_UNK800) || hitObj->ChkAtType(AT_TYPE_DARKNUT_SWORD) ||
                             hitObj->ChkAtType(AT_TYPE_MOBLIN_SPEAR) || hitObj->ChkAtType(AT_TYPE_SKULL_HAMMER);

                } else if (mSturdinessType == 1) {
                    broke |= hitObj->ChkAtType(AT_TYPE_MACHETE) || hitObj->ChkAtType(AT_TYPE_BOMB) || hitObj->ChkAtType(AT_TYPE_UNK800) ||
                             hitObj->ChkAtType(AT_TYPE_DARKNUT_SWORD);
                }

                if (broke) {
                    g_dComIfG_gameInfo.play.mVibration.StartShock(4, -0x21, cXyz(0, 1.0, 0));
                }

                burned |= hitObj->ChkAtType(AT_TYPE_FIRE) || hitObj->ChkAtType(AT_TYPE_UNK20000) || hitObj->ChkAtType(AT_TYPE_FIRE_ARROW);

                if (burned) {
                    break;
                }
            }
        }
    }

    if (burned) {
        return burn();
    }

    else if (broke)
    {
        if (i_sakuId == 1 && field_0xEF8[0] == 1) {
            broken(0);
        }
        return broken(i_sakuId);
    }

    return TRUE;
}

/* 000005CC-000006A8       .text mode_break_fire__8daSaku_cFi */
BOOL daSaku_c::mode_break_fire(int i_sakuId) {
    if (mParticleTimers[0] > m_saku_alpha_out_time) {
        cLib_chaseUC(&field_0xEDC[i_sakuId][1], 0xff, l_sakuHIO.field_0x10 & 0xff);

        int result = cLib_chaseUC(field_0xEDC[i_sakuId], 0, l_sakuHIO.field_0x10 & 0xff);

        if (result != 0) {
            if (m_heap[i_sakuId][0] != NULL && m_heap[i_sakuId][0] != NULL) { // instructions indicate checked twice
                if (field_0xEF0[i_sakuId] != 0) {
                    field_0xEF0[i_sakuId] -= 1;

                    if (field_0xEF0[i_sakuId] == 0) {
                        mDoExt_destroySolidHeap(m_heap[i_sakuId][0]);
                        m_heap[i_sakuId][0] = NULL;
                        mModels[i_sakuId][0] = NULL;
                    }
                }
            }
        }
    }

    return TRUE;
}

/* 000006A8-0000083C       .text mode_break_throw_obj__8daSaku_cFi */
BOOL daSaku_c::mode_break_throw_obj(int i_sakuId) {
    if (m_heap[i_sakuId][0] != NULL && m_heap[i_sakuId][1] != NULL) {
        if (field_0xEF0[i_sakuId] != 0) {
            field_0xEF0[i_sakuId] -= 1;

            if (field_0xEF0[i_sakuId] == 0) {
                mDoExt_destroySolidHeap(m_heap[i_sakuId][0]);
                m_heap[i_sakuId][0] = NULL;
                mModels[i_sakuId][0] = NULL;
            }
        }
    }

    if (mParticleTimers[i_sakuId] >= m_alpha_start_time) {
        if (field_0x290[i_sakuId].getEmitter() != NULL) {
            cLib_chaseF(&field_0xEB4[i_sakuId], 0, (f32)l_sakuHIO.field_0x12 / (255.0f * (f32)m_fade_time));
            field_0xEB4[i_sakuId] = fabs(field_0xEB4[i_sakuId]);

            u8 alpha = 255.0f * field_0xEB4[i_sakuId];
            field_0x290[i_sakuId].getEmitter()->setGlobalAlpha(alpha);

            if (alpha == 0) {
                field_0x290[i_sakuId].end();
                field_0xEAC[i_sakuId] = 0.0;
            }
        }
    }

    return TRUE;
}

/* 0000083C-000008EC       .text RecreateHeap__8daSaku_cFii */
BOOL daSaku_c::RecreateHeap(int heap_id, int saku_id) {
    JUT_ASSERT(0x365, m_heap[saku_id][heap_id] != NULL);

    m_heap[saku_id][heap_id]->freeAll();
    JKRHeap* heap = mDoExt_setCurrentHeap(m_heap[saku_id][heap_id]);

    CreateHeap(1, saku_id);

    mDoExt_setCurrentHeap(heap);

    return TRUE;
}

/* 000008EC-000009B0       .text CreateHeap__8daSaku_cFii */
BOOL daSaku_c::CreateHeap(int i_heapId, int i_sakuId) {
    u32 arcnameIndex;

    switch (field_0xEF8[i_sakuId]) {
        case 1:
            arcnameIndex = 0;
            break;

        case 3:
            arcnameIndex = 2;
            break;

        case 2:
            arcnameIndex = 1;
            break;
    }

    if (loadModel(arcnameIndex, i_heapId, i_sakuId) == 0) {
        return FALSE;
    }

    return loadMoveBG(GetDzbId(i_sakuId), i_heapId, i_sakuId) ? TRUE : FALSE;
}

/* 000009B0-00000A4C       .text GetDzbId__8daSaku_cFi */
int daSaku_c::GetDzbId(int i_sakuId) {
    s32 val = field_0xEF8[i_sakuId];
    u32 dzbId;

    if (i_sakuId == 1 || field_0xEF8[1] == 0) {
        if (val == 1) {
            dzbId = 0;
        } else {
            dzbId = 1;
        }
    }

    else if (val == 3 || val == 2)
    {
        dzbId = 3;
    } else {
        if (dComIfGs_isSwitch(mTopHalfDestroyedSwitch, home.roomNo)) {
            dzbId = 4;
        } else {
            dzbId = 2;
        }
    }

    return dzbId;
}

/* 00000A4C-00000ADC       .text CreateDummyHeap__8daSaku_cFi */
BOOL daSaku_c::CreateDummyHeap(int i_sakuId) {
    int i_arcnameIndex;

    if (mSturdinessType == 0) {
        i_arcnameIndex = 0;
    } else {
        i_arcnameIndex = i_sakuId;

        if (mSturdinessType == 1) {
            i_arcnameIndex = 1;
        }
    }

    if (loadModel(i_arcnameIndex, 1, i_sakuId) == FALSE) {
        return FALSE;
    }

    return loadMoveBG(1, 1, i_sakuId) ? TRUE : FALSE;
}

/* 00000ADC-00000BE8       .text loadMoveBG__8daSaku_cFiii */
BOOL daSaku_c::loadMoveBG(int i_index0, int i_index1, int i_sakuId) {
    int sp[5] = {3, 4, 5, 6, 3};

    field_0xE34[i_sakuId][i_index1] = new dBgW();

    if (field_0xE34[i_sakuId][i_index1] != NULL) {
        cBgD_t* bgd = (cBgD_t*)dComIfG_getObjectRes(m_arcname[0], sp[i_index0]);

        if (field_0xE34[i_sakuId][i_index1]->Set(bgd, dBgW::MOVE_BG_e, &mMtx[i_sakuId]) != true) {
            return TRUE;
        }
        return FALSE;
    }

    return FALSE;
}

/* 00000BE8-00000D7C       .text loadModel__8daSaku_cFiii */
BOOL daSaku_c::loadModel(int i_arcnameIndex, int i_heapId, int i_sakuId) {
    J3DModelData* modelData;

    int sp_0x20[6] = {3, 7, 5, 4, 6, 8};
    int sp_0x08[6] = {3, 5, 4, 6, 8, 7};

    if (i_sakuId == 1) {
        i_arcnameIndex += 3;
    }

    if (mSturdinessType == 0) {
        modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname[1], sp_0x20[i_arcnameIndex]);
    }

    else if (mSturdinessType == 1)
    {
        modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname[2], sp_0x08[i_arcnameIndex]);
    }

    JUT_ASSERT(0x43d, modelData != 0);
    mModels[i_sakuId][i_heapId] = mDoExt_J3DModel__create(modelData, 0, 0x11020203);

    if (mModels[i_sakuId][i_heapId] == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 00000D7C-00000E8C       .text burn__8daSaku_cFv */
BOOL daSaku_c::burn() {
    if (field_0xEF4 == 0) {
        if (field_0xEF8[0] == 1) {
            field_0xEF8[0] = 2;
            RecreateHeap(1, 0);
            field_0xEE0[0] = 50;
        }

        if (field_0xEF8[1] == 1) {
            field_0xEF8[1] = 2;
            RecreateHeap(1, 1);
            field_0xEE0[1] = 50;
        }

        J3DModel* model = mModels[0][1];

        if (model) {
            cullMtx = model->getBaseTRMtx();
        } else {
            model = mModels[1][1];
            if (model) {
                cullMtx = model->getBaseTRMtx();
            }
        }

        setEffFire(0);
        field_0xEEC = 0x5a;
        dComIfGs_onSwitch(mBottomHalfDestroyedSwitch, home.roomNo);

        if (field_0xEF8[1] != 0) {
            dComIfGs_onSwitch(mTopHalfDestroyedSwitch, home.roomNo);
        }

        field_0xEF4 = 1;
    }

    return TRUE;
}

/* 00000E8C-00000F60       .text broken__8daSaku_cFi */
BOOL daSaku_c::broken(int saku_id) {
    setEffBreak(saku_id);
    field_0xEF8[saku_id] = 3;
    field_0xEE0[saku_id] = 0;

    if (saku_id == 0) {
        dComIfGs_onSwitch(mBottomHalfDestroyedSwitch, home.roomNo);
    } else {
        dComIfGs_onSwitch(mTopHalfDestroyedSwitch, home.roomNo);
    }

    RecreateHeap(1, saku_id);

    if (saku_id == 0) {
        cullMtx = mModels[saku_id][1]->getBaseTRMtx();
    }

    field_0xEDC[saku_id][0] = 0;
    field_0xEDC[saku_id][1] = 0xff;

    return TRUE;
}

/* 00000F60-00000FF4       .text changeCollision__8daSaku_cFi */
BOOL daSaku_c::changeCollision(int param_1) {
    if (field_0xEF8[param_1] == 0) {
        return FALSE;
    }

    else {
        if (field_0xEE0[param_1] >= 0) {
            if (field_0xEE0[param_1] == 0) {
                dComIfG_Bgsp()->Release(field_0xE44[param_1]);
                MoveBGResist(1, param_1);
            }

            field_0xEE0[param_1] -= 1;
        }

        return TRUE;
    }
}

/* 00000FF4-0000113C       .text setMtx__8daSaku_cFv */
void daSaku_c::setMtx() {
    int i;
    J3DModel* model;

    for (i = 0; i < 2; i++) {
        model = mModels[0][i];
        if (model != NULL) {
            model->setBaseScale(scale);

            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::ZXYrotM(shape_angle);
            model->setBaseTRMtx(mDoMtx_stack_c::get());
        }
    }

    int j;
    if (field_0xEF8[1] != 0) {
        for (j = 0; j < 2; j++) {
            model = mModels[1][j];
            if (model != NULL) {
                model->setBaseScale(scale);

                mDoMtx_stack_c::transS(current.pos.x, current.pos.y + 200, current.pos.z);
                mDoMtx_stack_c::ZXYrotM(shape_angle);
                model->setBaseTRMtx(mDoMtx_stack_c::get());
            }
        }
    }
    return;
}

/* 0000113C-0000120C       .text setMoveBGMtx__8daSaku_cFv */
void daSaku_c::setMoveBGMtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);

    PSMTXCopy(mDoMtx_stack_c::now, mMtx[0]);

    if (field_0xEF8[1] != 0) {
        PSMTXTrans(mDoMtx_stack_c::now, current.pos.x, current.pos.y + 200, current.pos.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
        PSMTXCopy(mDoMtx_stack_c::now, mMtx[1]);
    };

    return;
}

/* 0000120C-0000134C       .text checkCol__8daSaku_cFv */
void daSaku_c::checkCol() {
    if (field_0xEEC != 0) {
        for (int i = 0; i < 3; i++) {
            field_0xA74[i].SetC(mPos[0][i]);
            g_dComIfG_gameInfo.play.mCcS.Set(&field_0xA74[i]);
        }
    }

    if (field_0xEF8[0] == 1) {
        for (int i = 0; i < 3; i++) {
            field_0x30C[0][i].SetC(mPos[0][i]);
            g_dComIfG_gameInfo.play.mCcS.Set(&field_0x30C[0][i]);
        }
    }

    if (field_0xEF8[1] != 0 && field_0xEF8[1] == 1) {
        for (int i = 0; i < 3; i++) {
            field_0x30C[1][i].SetC(mPos[1][i]);
            g_dComIfG_gameInfo.play.mCcS.Set(&field_0x30C[1][i]);
        }
    }

    return;
}

/* 0000134C-00001510       .text setCol__8daSaku_cFv */
void daSaku_c::setCol() {
    mPos[0][0].set(0, 20, 0);
    mPos[0][1].set(-100, 20, 0);
    mPos[0][2].set(100, 20, 0);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);

    for (int i = 0; i < 3; i++) {
        mDoMtx_stack_c::multVec(&mPos[0][i], &mPos[0][i]);

        field_0x30C[0][i].Set(m_cyl_src);
        field_0x30C[0][i].SetStts(&mStts);
    }

    if (field_0xEF8[1] != 0) {
        mPos[1][0].set(0, 220, 0);
        mPos[1][1].set(-100, 220, 0);
        mPos[1][2].set(100, 220, 0);

        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(shape_angle);

        for (int i = 0; i < 3; i++) {
            mDoMtx_stack_c::multVec(&mPos[1][i], &mPos[1][i]);

            field_0x30C[1][i].Set(m_cyl_src);
            field_0x30C[1][i].SetStts(&mStts);
        }
    }
}

/* 00001510-00001598       .text MoveBGResist__8daSaku_cFii */
BOOL daSaku_c::MoveBGResist(int i_index0, int i_index1) {
    if (g_dComIfG_gameInfo.play.mBgS.Regist(field_0xE34[i_index1][i_index0], this) != 0) {
        return FALSE;

    } else {
        field_0xE44[i_index1] = field_0xE34[i_index1][i_index0];
        field_0xE44[i_index1]->Move();
        return TRUE;
    }
}

/* 00001598-000016C0       .text setEffFire__8daSaku_cFi */
BOOL daSaku_c::setEffFire(int _) {
    // input param seems to be unused
    cXyz local_18 = current.pos;

    dComIfGp_particle_set(0x45c, &local_18, &current.angle, 0x0, 0xff, 0x0, -1, 0x0, 0x0, 0x0);
    dComIfGp_particle_set(0x245e, &local_18, &current.angle, 0x0, m_smoke_alpha, 0x0, -1, 0x0, 0x0, 0x0);

    mParticleTimers[1] = 1;
    mParticleTimers[0] = 1;

    JAIZelBasic::zel_basic->seStart(0x6924, &eyePos, 0, dComIfGp_getReverb(current.roomNo), 1.0, 1.0, -1.0, -1.0, 0);

    return TRUE;
}

BOOL daSaku_c::setEffBreak(int i_index) {
    cXyz localPos = current.pos;
    localPos.y += (f32)100.0;

    if (i_index == 1) {
        localPos.y += (f32)200.0;
    }

    if (l_sakuHIO.field_0x0F != 0) {
        dComIfGp_particle_set(0x45d, &localPos, &current.angle, &scale, 0xff, 0, -1, &tevStr.mColorK0, &tevStr.mColorK0, NULL);
    }

    field_0xEB4[i_index] = (f32)l_sakuHIO.field_0x12 / 255.0f;
    dust_color.r = l_sakuHIO.dustColor.r;
    dust_color.g = l_sakuHIO.dustColor.g;
    dust_color.b = l_sakuHIO.dustColor.b;

    field_0xEC4[i_index] = localPos;

    dComIfGp_particle_setToon(
        0x2027,
        &field_0xEC4[i_index],
        &current.angle,
        NULL,
        l_sakuHIO.field_0x12,
        &field_0x290[i_index],
        fopAcM_GetRoomNo(this),
        0,
        0,
        0
    );

    JPABaseEmitter* em = field_0x290[i_index].getEmitter();
    if (em != NULL) {

        em->setGlobalAlpha(field_0xEB4[i_index] * 255.0f);
        field_0x290[i_index].getEmitter()->becomeImmortalEmitter();

        cXyz dScale(2.0f, 2.0f, 2.0f);
        cXyz eScale(1.0f, 0.5f, 0.7f);

        field_0x290[i_index].getEmitter()->setGlobalParticleScale(3.2f, 3.2f);
        field_0x290[i_index].getEmitter()->setGlobalDynamicsScale(dScale);
        field_0x290[i_index].getEmitter()->setEmitterScale(eScale);

        field_0x290[i_index].getEmitter()->setRate(40.0f);
        field_0x290[i_index].getEmitter()->setMaxFrame(1);
    }

    if (mSturdinessType == 0) {
        s8 reverb = dComIfGp_getReverb(current.roomNo);
        JAIZelBasic::zel_basic->seStart(0x6847, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
    } else if (mSturdinessType == 1) {
        s8 reverb = dComIfGp_getReverb(current.roomNo);
        JAIZelBasic::zel_basic->seStart(0x693f, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
    }

    mParticleTimers[i_index] = 1;

    return TRUE;
}

static void changeXluMaterialAlpha(J3DMaterial*, u8, bool);

/* 000019AC-00001A50       .text matAlphaAnim__FP12J3DModelDataUcb */
BOOL matAlphaAnim(J3DModelData* modelData, u8 i_alpha, bool i_isZmodeInfo2) {
    JUT_ASSERT(0x5d1, modelData != 0);

    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        changeXluMaterialAlpha(modelData->getMaterialNodePointer(i), i_alpha, i_isZmodeInfo2);
    }

    return 1;
}

/* 00001A50-00001B98       .text changeXluMaterialAlpha__FP11J3DMaterialUcb */
void changeXluMaterialAlpha(J3DMaterial* i_material, u8 alpha, bool i_isZmodeInfo2) {
    static J3DBlendInfo l_blendInfo = {1, 4, 5, 7};
    static J3DZModeInfo l_zmodeInfo = {1, 3, 0};
    static J3DZModeInfo l_zmodeInfo2 = {1, 3, 1};

    JUT_ASSERT(0x5ff, i_material != 0);

    J3DPEBlock* block = i_material->getPEBlock();

    i_material->getTevKColor(3)->mColor.a = alpha;
    block->getBlend()->setBlendInfo(l_blendInfo);

    if (i_isZmodeInfo2) {
        block->getZMode()->setZModeInfo(l_zmodeInfo2);
    } else {
        block->getZMode()->setZModeInfo(l_zmodeInfo);
    }
}

const char* daSaku_c::m_arcname[3] = {"KsakuCo", "Ksaku_00", "Knsak_00"};

/* 00001B98-00001BB8       .text daSaku_Create__FP10fopAc_ac_c */
static cPhs_State daSaku_Create(fopAc_ac_c* i_this) {
    return ((daSaku_c*)i_this)->_daSaku_create();
}

/* 00001BB8-00001F28       .text _daSaku_create__8daSaku_cFv */
cPhs_State daSaku_c::_daSaku_create() {
    s32 size = 0; // not used, but instructions indicate that it has size of solid heap

    fopAcM_ct(this, daSaku_c);
    mSturdinessType = daSaku_prm::getType(this);

    int arcnameIndex = 2;
    if (mSturdinessType == 0) {
        arcnameIndex = 1;
    }

    cPhs_State phase = dComIfG_resLoad(&field_0xE04, m_arcname[arcnameIndex]);
    if (phase != cPhs_COMPLEATE_e) {
        return phase;
    }

    phase = dComIfG_resLoad(&field_0xE0C, m_arcname[0]);
    if (phase != cPhs_COMPLEATE_e) {
        return phase;
    }

    mBottomHalfDestroyedSwitch = base.base.mParameters >> 8 & 0xff;
    ;
    mTopHalfDestroyedSwitch = base.base.mParameters >> 0x10 & 0xff;
    ;

    field_0xEF8[0] = 1;

    if (dComIfGs_isSwitch(mBottomHalfDestroyedSwitch, home.roomNo)) {
        field_0xEF8[0] = 3;
    }
    field_0xEF8[1] = 0;

    if ((base.base.mParameters & 0xfU) != 0) {
        field_0xEF8[1] = 1;

        if (dComIfGs_isSwitch(mTopHalfDestroyedSwitch, home.roomNo)) {
            field_0xEF8[1] = 3;
        }
    }

    setMoveBGMtx();

    for (int i = 0; i < 2; i++) {
        if (field_0xEF8[i] != 0) {
            m_heap[i][0] = mDoExt_createSolidHeapFromGameToCurrent(0x2280, 0x20);

            if (m_heap[i][0] == NULL) {
                return cPhs_ERROR_e;
            }

            BOOL heapCreated = CreateHeap(0, i);

            if (heapCreated) {
                MoveBGResist(0, i);
            }

            mDoExt_restoreCurrentHeap();
            size += mDoExt_adjustSolidHeap(m_heap[i][0]);

            if (!heapCreated) {
                return cPhs_ERROR_e;
            }

            mModels[i][1] = NULL;
            if (field_0xEF8[i] == 1) {
                m_heap[i][1] = mDoExt_createSolidHeapFromGameToCurrent(0x2280, 0x20);

                if (m_heap[i][1] == NULL) {
                    return cPhs_ERROR_e;
                }

                heapCreated = CreateDummyHeap(i);
                mModels[i][1] = NULL;
                mDoExt_restoreCurrentHeap();

                size += mDoExt_adjustSolidHeap(m_heap[i][1]);

                if (!heapCreated) {
                    return cPhs_ERROR_e;
                }
            }
        }
    }

    CreateInit();
    if (l_sakuHIO.field_0x04 < 0) {
        l_sakuHIO.field_0x04 = mDoHIO_createChild("柵", &l_sakuHIO);
    }

    return cPhs_COMPLEATE_e;
}

BOOL daSaku_c::_daSaku_delete() {
    if (l_sakuHIO.field_0x04 >= 0) {
        mDoHIO_deleteChild(l_sakuHIO.field_0x04);
        l_sakuHIO.field_0x04 = -1;
    }

    for (int i = 0; i < 2; i++) {
        field_0x290[i].end();
    }

    for (int i = 0; i < 2; i++) {
        if (field_0xEF8[i] != 0) {
            dComIfG_Bgsp()->Release(field_0xE44[i]);
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (m_heap[i][j] != 0) {
                mDoExt_destroySolidHeap(m_heap[i][j]);
                m_heap[i][j] = NULL;
                mModels[i][j] = NULL;
            }
        }
    }

    dComIfG_resDelete(&field_0xE0C, m_arcname[0]);

    if (mSturdinessType == 0) {
        dComIfG_resDelete(&field_0xE04, m_arcname[1]);
    } else {
        dComIfG_resDelete(&field_0xE04, m_arcname[2]);
    }

    return true;
}

/* 00002264-000023D8       .text daSaku_Delete__FP8daSaku_c */
static BOOL daSaku_Delete(daSaku_c* i_this) {
    return i_this->_daSaku_delete();
}

/* 000023D8-000023E0       .text daSaku_IsDelete__FP8daSaku_c */
static BOOL daSaku_IsDelete(daSaku_c*) {
    return TRUE;
}

/* 000023E0-0000242C       .text daSaku_Draw__FP8daSaku_c */
static BOOL daSaku_Draw(daSaku_c* i_this) {
    i_this->saku_draw_sub(0);
    if (i_this->field_0xEF8[1] != 0) {
        i_this->saku_draw_sub(1);
    }

    return TRUE;
}

BOOL daSaku_c::_daSaku_execute() {
    int particleTimer;

    for (int i = 0; i < 2; i++) {
        particleTimer = mParticleTimers[i];
        if (particleTimer != 0 && particleTimer < m_max_particle_timer) {
            mParticleTimers[i] = particleTimer + 1;
        }
    }

    if (field_0xEEC != 0) {
        field_0xEEC -= 1;
    }
    field_0xEE0[2] += 1;

    for (int i = 0; i < 2; i++) {
        switch (field_0xEF8[i]) {
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
        }
    }

    for (int i = 0; i < 2; i++) {
        changeCollision(i);
    }

    setMtx();
    checkCol();

    return TRUE;
}

// Need to instantiate here.
// If put prior to _daSaku_execute, doesn't get read from .rodata
// If put after daSaku_Execute, ends up in .data instead of .rodata
const s32 daSaku_c::m_max_particle_timer = 2000;

/* 0000242C-00002560       .text daSaku_Execute__FP8daSaku_c */
static BOOL daSaku_Execute(daSaku_c* i_this) {
    return i_this->_daSaku_execute();
}

u8 daSaku_c::m_smoke_alpha = 230;
const s32 daSaku_c::m_alpha_start_time = 10;
s32 daSaku_c::m_saku_alpha_out_time = 10;
s32 daSaku_c::m_fade_time = 40;
GXColor daSaku_c::dust_color = {0x69, 0x5B, 0x30, 0xFF};

const u8 daSaku_c::m_start_alpha = 180;
const u16 daSaku_c::m_alpha_spd = 5;
const f32 daSaku_c::m_saku_height = 200.0;

const dCcD_SrcCyl daSaku_c::m_at_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_FIRE | AT_TYPE_UNK20000,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ 15,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 1,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 6,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0, 0.0, 0.0},
        /* Radius */ 50.0,
        /* Height */ 400.0,
    }},
};

dCcD_SrcCyl daSaku_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_SWORD | AT_TYPE_UNK8 | AT_TYPE_BOMB | AT_TYPE_FIRE | AT_TYPE_MACHETE | AT_TYPE_UNK800 | AT_TYPE_SKULL_HAMMER |
            AT_TYPE_UNK20000 | AT_TYPE_FIRE_ARROW,
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
