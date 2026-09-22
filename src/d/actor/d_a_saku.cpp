/**
 * d_a_saku.cpp
 * Object - Brown wooden barricade
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_saku.h"
#include "d/d_cc_d.h"

static sakuHIO_c l_sakuHIO;

dCcD_SrcCyl daSaku_c::m_cyl_src = {
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


class J3DModelData;
class J3DMaterial;

// declare before matAlphaAnim to use within that func
static void changeXluMaterialAlpha(J3DMaterial*, u8 , bool);

/* 000019AC-00001A50       .text matAlphaAnim__FP12J3DModelDataUcb */
BOOL matAlphaAnim(J3DModelData* modelData, u8 param_1, bool param_2) {
    JUT_ASSERT(0x5d1, modelData != 0);


    for (u16 i = 0; i < modelData->getMaterialNum(); i ++) {
        changeXluMaterialAlpha(modelData->getMaterialNodePointer(i), param_1, param_2);
    }

    return 1;
}

/* 00001A50-00001B98       .text changeXluMaterialAlpha__FP11J3DMaterialUcb */
void changeXluMaterialAlpha(J3DMaterial* i_material, u8 param_2, bool param_3) {
    static J3DBlendInfo l_blendInfo = {1, 4, 5, 7};
    static J3DZModeInfo l_zmodeInfo = {1,3,0};
    static J3DZModeInfo l_zmodeInfo2 = {1,3,1};

    JUT_ASSERT(0x5ff, i_material != 0);


    J3DPEBlock* block = i_material->getPEBlock();

    i_material->getTevKColor(3)->mColor.a = param_2;
    block->getBlend()->setBlendInfo(l_blendInfo);

    if (param_3) {
        block->getZMode()->setZModeInfo(l_zmodeInfo2);
    } else {
        block->getZMode()->setZModeInfo(l_zmodeInfo);
    }
}

/* 000000EC-00000200       .text CreateInit__8daSaku_cFv */
void daSaku_c::CreateInit() {
    for(int i = 0; i < 2; i++) {
        field_0xEBC[i] = 0;
        field_0xEAC[i] = 0;
        
        field_0xEDC[i][0] = 0xff;
        field_0xEDC[i][1] = 0;

        field_0xEE0[i] = 0xffffffff;
        field_0xEF0[i] = 2;
    }

    this->field_0xEF4 = 0;
    this->field_0xEEC = 0;
    this->cullMtx = this->mModels[0][0]->getBaseTRMtx();
    this->mStts.Init(0xff, 0xff, this);
    setCol();
    setMtx();

    for(int i = 0; i < 2; i++) {
        this->field_0x290[i].setColor(dust_color);
        this->field_0x290[i].setRateOff(1);
    }
    
    return;
}

/* 00000200-000003A8       .text saku_draw_sub__8daSaku_cFi */
int daSaku_c::saku_draw_sub(int param_1) {
    bool bVar1 = true;
    if(field_0xEDC[param_1][0] < l_sakuHIO.dustColor.a) {
        bVar1 = false;
    }

    if(m_heap[param_1][0] != NULL && mModels[param_1][0] != NULL && field_0xEDC[param_1][0] != NULL) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mModels[param_1][0], &tevStr);

        matAlphaAnim(mModels[param_1][0]->getModelData(), field_0xEDC[param_1][0], bVar1);

        j3dSys.mDrawBuffer[0] = g_dComIfG_gameInfo.drawlist.mpOpaListBG;
        j3dSys.mDrawBuffer[1] = g_dComIfG_gameInfo.drawlist.mpXluListBG;

        mDoExt_modelUpdateDL(mModels[param_1][0]);

        j3dSys.mDrawBuffer[0] = g_dComIfG_gameInfo.drawlist.mpOpaList;
        j3dSys.mDrawBuffer[1] = g_dComIfG_gameInfo.drawlist.mpXluList;

        matAlphaAnim(mModels[param_1][0]->getModelData(), 0xff, true);
    }

    if (m_heap[param_1][1] != NULL && mModels[param_1][1] != NULL && this->field_0xEDC[param_1][1] != NULL) { 
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mModels[param_1][1], &tevStr);

        matAlphaAnim(mModels[param_1][1]->getModelData(), 0xff, bVar1 ? false : true);
        mDoExt_modelUpdateDL(mModels[param_1][1]);
        matAlphaAnim(mModels[param_1][1]->getModelData(), 0xff, true);
    }

    return 1;
}

/* 000003A8-00000590       .text mode_break_none__8daSaku_cFi */
BOOL daSaku_c::mode_break_none(int param_1) {
    u32 burned = FALSE;
    u32 broke = FALSE;

    for (int i = 0; i < 3; i++) {
        dCcD_GObjInf *this_00 = &field_0x30C[param_1][i];

        if (this_00->ChkTgHit() != NULL) {
            cCcD_Obj* hitObj = this_00->GetTgHitObj();

            if (hitObj != NULL) {
                if (mSturdinessType == 0) {
                    broke |= hitObj->ChkAtType(AT_TYPE_SWORD) || 
                        hitObj->ChkAtType(AT_TYPE_UNK8) || 
                        hitObj->ChkAtType(AT_TYPE_BOMB) || 
                        hitObj->ChkAtType(AT_TYPE_MACHETE) || 
                        hitObj->ChkAtType(AT_TYPE_UNK800) || 
                        hitObj->ChkAtType(AT_TYPE_DARKNUT_SWORD) || 
                        hitObj->ChkAtType(AT_TYPE_MOBLIN_SPEAR) || 
                        hitObj->ChkAtType(AT_TYPE_SKULL_HAMMER);
                        
                }
                else if (mSturdinessType == 1) {
                    broke |= hitObj->ChkAtType(AT_TYPE_MACHETE) ||
                        hitObj->ChkAtType(AT_TYPE_BOMB) ||
                        hitObj->ChkAtType(AT_TYPE_UNK800) ||
                        hitObj->ChkAtType(AT_TYPE_DARKNUT_SWORD);
                }

                if (broke) {
                    g_dComIfG_gameInfo.play.mVibration.StartShock(4, -0x21, cXyz(0, 1.0, 0));
                }

                burned |= hitObj->ChkAtType(AT_TYPE_FIRE) ||
                    hitObj->ChkAtType(AT_TYPE_UNK20000) ||
                    hitObj->ChkAtType(AT_TYPE_FIRE_ARROW);

                if (burned) {
                    break;
                }
            }
        }
    }

    if (burned) {
        return burn();
    }

    else if (broke) {
        if(param_1 == 1 && field_0xEF8[0] == 1) {
            broken(0);
        }
        return broken(param_1);
    }

    return TRUE;
}

/* 000005CC-000006A8       .text mode_break_fire__8daSaku_cFi */
BOOL daSaku_c::mode_break_fire(int i) {
    if(field_0xEBC[0] > m_saku_alpha_out_time) {
        cLib_chaseUC(&field_0xEDC[i][1], 0xff, l_sakuHIO.field_0x10 & 0xff);

        int reuslt = cLib_chaseUC(field_0xEDC[i], 0, l_sakuHIO.field_0x10 & 0xff);
        
        if(reuslt != 0) {
            if(m_heap[i][0] != NULL && m_heap[i][0] != NULL) { // instructions indicate checked twice
                if(field_0xEF0[i] != 0) {
                    field_0xEF0[i] -= 1;

                    if(field_0xEF0[i] == 0) {
                        mDoExt_destroySolidHeap(m_heap[i][0]);
                        m_heap[i][0] = NULL;
                        mModels[i][0] = NULL;
                    }
                }
            }
        }

    }

    return TRUE;
}

/* 000006A8-0000083C       .text mode_break_throw_obj__8daSaku_cFi */
int daSaku_c::mode_break_throw_obj(int i) {
    if(m_heap[i][0] != NULL && m_heap[i][1] != NULL) {
        if(this->field_0xEF0[i] != 0) {
            this->field_0xEF0[i] -= 1;

            if(this->field_0xEF0[i] == 0) {
                mDoExt_destroySolidHeap(m_heap[i][0]);
                m_heap[i][0] = NULL;
                mModels[i][0] = NULL;
            }
        }
    }

    if(this->field_0xEBC[i] >= m_alpha_start_time) {
        if(this->field_0x290[i].getEmitter() != NULL) {
            cLib_chaseF(&this->field_0xEB4[i], 0, (f32)l_sakuHIO.field_0x12 / (255.0f * (f32)m_fade_time));
            this->field_0xEB4[i] = fabs(this->field_0xEB4[i]);

            u8 uVar1 = 255.0f * this->field_0xEB4[i];
            this->field_0x290[i].getEmitter()->setGlobalAlpha(uVar1);

            if (uVar1 == 0) {
                this->field_0x290[i].end();
                this->field_0xEAC[i] = 0.0;
            }
        }
    }

    return 1; 
}

/* 0000083C-000008EC       .text RecreateHeap__8daSaku_cFii */
BOOL daSaku_c::RecreateHeap(int heap_id, int saku_id) {
    /* Nonmatching */
    // DONE- WAITING FOR JUT ASSERTION
    JUT_ASSERT(0x365, m_heap[saku_id][heap_id] != NULL);

    m_heap[saku_id][heap_id]->freeAll();
    JKRHeap *heap = mDoExt_setCurrentHeap(m_heap[saku_id][heap_id]);

    CreateHeap(1, saku_id);

    mDoExt_setCurrentHeap(heap);

    return TRUE;
}

/* 000008EC-000009B0       .text CreateHeap__8daSaku_cFii */
BOOL daSaku_c::CreateHeap(int i_heapId, int i_sakuId) {
    s32 iVar1;
    u32 iVar2 = i_heapId;

    iVar1 = this->field_0xEF8[i_sakuId];

    switch(iVar1) {
        case 1:
            iVar2 = 0;
            break;
        
        case 3:
            iVar2 = 2;
            break;

        case 2:
            iVar2 = 1;
            break;
    }

    iVar1 = loadModel(iVar2, i_heapId, i_sakuId);
    if (iVar1 == 0) {
        return FALSE;
    }

    iVar1 = GetDzbId(i_sakuId);
    return loadMoveBG(iVar1, i_heapId, i_sakuId) ? TRUE : FALSE;
}

/* 000009B0-00000A4C       .text GetDzbId__8daSaku_cFi */
int daSaku_c::GetDzbId(int param_1) {
    s32 iVar1 = field_0xEF8[param_1];
    u32 uVar2;
    bool bVar3;

    if (param_1 == 1 || field_0xEF8[1] == 0) {
        if (iVar1 == 1) {
            uVar2 = 0;
        }
        else {
            uVar2 = 1;
        }
    }

    else if(iVar1 == 3 || iVar1 == 2) {
        uVar2 = 3;
    }
    else {
        bVar3 = dComIfGs_isSwitch(mTopHalfDestroyedSwitch, home.roomNo);

        if (bVar3) {
            uVar2 = 4;
        }
        else {
            uVar2 = 2;
        }
    }

    return uVar2;
}

/* 00000A4C-00000ADC       .text CreateDummyHeap__8daSaku_cFi */
BOOL daSaku_c::CreateDummyHeap(int param_1) {
    int iVar1; 

    if (mSturdinessType == 0) {
        iVar1 = 0;
    }
    else {
        iVar1 = param_1;

        if(mSturdinessType == 1) {
            iVar1 = 1;
        }
    }

    if (loadModel(iVar1, 1, param_1) == FALSE) {
        return FALSE;
    }

    return loadMoveBG(1, 1, param_1) ? TRUE : FALSE;
}

/* 00000ADC-00000BE8       .text loadMoveBG__8daSaku_cFiii */
BOOL daSaku_c::loadMoveBG(int param_1, int param_2, int param_3) {
    int sp[5] =  {3, 4, 5, 6, 3};

    field_0xE34[param_3][param_2] = new dBgW();

    if(field_0xE34[param_3][param_2] != NULL) {
        cBgD_t* bgd = (cBgD_t*)dComIfG_getObjectRes(m_arcname[0], sp[param_1]);

        if(field_0xE34[param_3][param_2]->Set(bgd, dBgW::MOVE_BG_e, &mMtx[param_3]) != true) {
            return TRUE;
        }
        return FALSE;
    }

    return FALSE;

}

/* 00000BE8-00000D7C       .text loadModel__8daSaku_cFiii */
BOOL daSaku_c::loadModel(int param_1, int param_2, int param_3) {
    J3DModelData *modelData;

    int sp_0x20[6] = {3, 6, 5, 4, 6, 8};
    int sp_0x08[6] = {3, 5, 4, 6, 8, 7};

    if(param_3 == 1) {
        param_1 += 3;
    }

    if(mSturdinessType == 0) {
        modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname[1], sp_0x20[param_1]);
    }

    else if (mSturdinessType == 1) {
        modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname[2], sp_0x08[param_1]);
    }

    JUT_ASSERT(0x43d, modelData != 0);
    mModels[param_3][param_2] = mDoExt_J3DModel__create(modelData, 0, 0x11020203);

    if(mModels[param_3][param_2] == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 00000D7C-00000E8C       .text burn__8daSaku_cFv */
int daSaku_c::burn() {
    if (this->field_0xEF4 == 0) {
        if (this->field_0xEF8[0] == 1) {
            this->field_0xEF8[0] = 2;
            RecreateHeap(1, 0);
            this->field_0xEE0[0] = 50;
        }

        if (this->field_0xEF8[1] == 1) {
            this->field_0xEF8[1] = 2;
            RecreateHeap(1, 1);
            this->field_0xEE0[1] = 50;
        }

        J3DModel* pVar1;
        pVar1 = mModels[0][1];
        if(pVar1) {
            this->cullMtx = pVar1->getBaseTRMtx();
        }
        else {
            pVar1 = mModels[1][1];
            if(pVar1) {
                this->cullMtx = pVar1->getBaseTRMtx();
            }
        }

        setEffFire(0);
        this->field_0xEEC = 0x5a;
        dComIfGs_onSwitch(mBottomHalfDestroyedSwitch, home.roomNo);

        if(this->field_0xEF8[1] != 0) {
            dComIfGs_onSwitch(mTopHalfDestroyedSwitch, home.roomNo);
        }

        this->field_0xEF4 = 1;
    }

    return 1;

}

/* 00000E8C-00000F60       .text broken__8daSaku_cFi */
int daSaku_c::broken(int param_1) {
    setEffBreak(param_1);
    this->field_0xEF8[param_1] = 3;
    this->field_0xEE0[param_1] = 0;

    if (param_1 == 0) {
        dComIfGs_onSwitch(mBottomHalfDestroyedSwitch, home.roomNo);
    }
    else {
        dComIfGs_onSwitch(mTopHalfDestroyedSwitch, home.roomNo);
    }

    RecreateHeap(1, param_1);

    if(param_1 == 0) {
        this->cullMtx = mModels[param_1][1]->getBaseTRMtx();
    }

    this->field_0xEDC[param_1][0] = 0;
    this->field_0xEDC[param_1][1] = 0xff;

    return 1;
}

/* 00000F60-00000FF4       .text changeCollision__8daSaku_cFi */
bool daSaku_c::changeCollision(int param_1) {
    bool flag; 
    if (this->field_0xEF8[param_1] == 0) {
        flag = FALSE;
    }

    else {
        if(this->field_0xEE0[param_1] >= 0) {
            if(this->field_0xEE0[param_1] == 0){
                dComIfG_Bgsp()->Release(this->field_0xE44[param_1]);
                MoveBGResist(1, param_1);
            }
            
            this->field_0xEE0[param_1] -= 1;
        }

        flag = TRUE;
    }

    return flag;
}

/* 00000FF4-0000113C       .text setMtx__8daSaku_cFv */
void daSaku_c::setMtx() {
    int i;
    J3DModel* m;

    for(i = 0; i < 2; i++) {
        m = mModels[0][i];
        if (m != NULL) {
            m->setBaseScale(scale);

            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::ZXYrotM(shape_angle);
            m->setBaseTRMtx(mDoMtx_stack_c::get());
        }
    }

    int j;
    if (this->field_0xEF8[1] != 0) {
        for(j = 0; j < 2; j++) {
            m = mModels[1][j];
            if (m != NULL) {
                m->setBaseScale(scale);

                mDoMtx_stack_c::transS(current.pos.x, current.pos.y + 200, current.pos.z);
                mDoMtx_stack_c::ZXYrotM(shape_angle);
                m->setBaseTRMtx(mDoMtx_stack_c::get());
            }
        }
    }
    return;
}

/* 0000113C-0000120C       .text setMoveBGMtx__8daSaku_cFv */
void daSaku_c::setMoveBGMtx() {
    /* Nonmatching */
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(this->shape_angle.y);
    mDoMtx_stack_c::scaleM(this->scale.x, this->scale.y, this->scale.z);

    PSMTXCopy(mDoMtx_stack_c::now, mMtx[0]);

    if(this->field_0xEF8[1] != 0) {
        PSMTXTrans(mDoMtx_stack_c::now, current.pos.x, current.pos.y + 200, current.pos.z);
        mDoMtx_stack_c::YrotM(this->shape_angle.y);
        mDoMtx_stack_c::scaleM(this->scale.x, this->scale.y, this->scale.z);
        PSMTXCopy(mDoMtx_stack_c::now, mMtx[1]);
    };

    return;
}

/* 0000120C-0000134C       .text checkCol__8daSaku_cFv */
void daSaku_c::checkCol() {
    if(this->field_0xEEC != 0) {
        for(int i = 0; i < 3; i++) {
            this->field_0xA74[i].SetC(mPos[0][i]);
            g_dComIfG_gameInfo.play.mCcS.Set(&this->field_0xA74[i]);
        }
    }

    if(this->field_0xEF8[0] == 1) {
        for(int i = 0; i < 3; i++) {
            this->field_0x30C[0][i].SetC(mPos[0][i]);
            g_dComIfG_gameInfo.play.mCcS.Set(&this->field_0x30C[0][i]);
        }
    }


    if(field_0xEF8[1] != 0 && this->field_0xEF8[1] == 1) {
        for(int i = 0; i < 3; i++) {
            this->field_0x30C[1][i].SetC(mPos[1][i]);
            g_dComIfG_gameInfo.play.mCcS.Set(&this->field_0x30C[1][i]);
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

    for(int i = 0; i < 3; i++){ 
        mDoMtx_stack_c::multVec(&mPos[0][i], &mPos[0][i]);

        field_0x30C[0][i].Set(m_cyl_src);
        field_0x30C[0][i].SetStts(&mStts);
    }

    if(field_0xEF8[1] != 0) {
        mPos[1][0].set(0, 220, 0);
        mPos[1][1].set(-100, 220, 0);
        mPos[1][2].set(100, 220, 0);

        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(shape_angle);

        for(int i = 0; i < 3; i++) {
            mDoMtx_stack_c::multVec(&mPos[1][i], &mPos[1][i]);

            field_0x30C[1][i].Set(m_cyl_src);
            field_0x30C[1][i].SetStts(&mStts);
        }
    }

}

/* 00001510-00001598       .text MoveBGResist__8daSaku_cFii */
int daSaku_c::MoveBGResist(int param_1, int param_2) {
    u8 cVar1;

    cVar1 = g_dComIfG_gameInfo.play.mBgS.Regist(field_0xE34[param_2][param_1], this);

    if (cVar1 != 0) {
            return 0;

    }
    else {
        field_0xE44[param_2] = field_0xE34[param_2][param_1];
        field_0xE44[param_2]->Move();
        return 1;
    }
}

/* 00001598-000016C0       .text setEffFire__8daSaku_cFi */
int daSaku_c::setEffFire(int _) {
    // input param seems to be unused
    s8 sVar1;
    cXyz local_18;

    local_18.set(current.pos);

    dComIfGp_particle_set(0x45c, &local_18, &current.angle, 0x0, 0xff, 0x0, -1, 0x0, 0x0, 0x0);
    dComIfGp_particle_set(0x245e, &local_18, &current.angle, 0x0, m_smoke_alpha, 0x0, -1, 0x0, 0x0, 0x0);

    this->field_0xEBC[1] = 1;
    this->field_0xEBC[0] = 1;

    sVar1 = dComIfGp_getReverb(this->current.roomNo);

    JAIZelBasic::zel_basic->seStart(0x6924, &this->eyePos, 0, sVar1, 1.0, 1.0, -1.0, -1.0, 0);

    return 1;
    
}

/* 000016C0-000019AC       .text setEffBreak__8daSaku_cFi */
void daSaku_c::setEffBreak(int) {
    /* Nonmatching */
}


}

/* 00001B98-00001BB8       .text daSaku_Create__FP10fopAc_ac_c */
static cPhs_State daSaku_Create(fopAc_ac_c* i_this) {
    return ((daSaku_c*)i_this)->_daSaku_create();
}

/* 00001BB8-00001F28       .text _daSaku_create__8daSaku_cFv */
cPhs_State daSaku_c::_daSaku_create() {
    /* MATCHING EXCEPT FOR STRINGBASE */
    s32 size = 0; // not used, but instructions indicate that it has size of solid heap 

    fopAcM_ct(this, daSaku_c);
    mSturdinessType = daSaku_prm::getType(this);

    int iVar5 = 2;
    if(mSturdinessType == 0) {
        iVar5 = 1;
    }

    cPhs_State phase =  dComIfG_resLoad(&field_0xE04, m_arcname[iVar5]);
    if(phase != cPhs_COMPLEATE_e) {
        return phase;
    }

    phase = dComIfG_resLoad(&field_0xE0C, m_arcname[0]);
    if(phase != cPhs_COMPLEATE_e) {
        return phase;
    }

    mBottomHalfDestroyedSwitch = this->base.base.mParameters >> 8 & 0xff;;
    mTopHalfDestroyedSwitch = this->base.base.mParameters >> 0x10 & 0xff;;

    field_0xEF8[0] = 1;

    if (dComIfGs_isSwitch(mBottomHalfDestroyedSwitch, home.roomNo)) {
        field_0xEF8[0] = 3;
    }
    field_0xEF8[1]  = 0;

    if ((this->base.base.mParameters & 0xfU) != 0) {
        this->field_0xEF8[1] = 1;

        if (dComIfGs_isSwitch(mTopHalfDestroyedSwitch, home.roomNo)) {
            field_0xEF8[1] = 3;
        }
    }

    setMoveBGMtx();

    for(int i = 0; i < 2; i ++) {
        if (field_0xEF8[i] != 0) {
            m_heap[i][0] = mDoExt_createSolidHeapFromGameToCurrent(0x2280, 0x20);

            if(m_heap[i][0] == NULL) {
                return cPhs_ERROR_e;
            }

            BOOL bVar3 = CreateHeap(0, i);

            if (bVar3) {
                MoveBGResist(0, i);
            }

            mDoExt_restoreCurrentHeap();
            size += mDoExt_adjustSolidHeap(m_heap[i][0]);

            if (!bVar3) {
                return cPhs_ERROR_e;
            }

            mModels[i][1] = NULL;
            if(field_0xEF8[i] == 1) {
                m_heap[i][1]= mDoExt_createSolidHeapFromGameToCurrent(0x2280, 0x20);

                if(m_heap[i][1] == NULL) {
                    return cPhs_ERROR_e;
                }

                bVar3 = CreateDummyHeap(i);
                mModels[i][1] = NULL;
                mDoExt_restoreCurrentHeap();

                size += mDoExt_adjustSolidHeap(m_heap[i][1]);

                if(!bVar3) {
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

    for (int i = 0; i < 2; i ++) {
        field_0x290[i].end();
    }

    for (int i = 0; i < 2; i ++) {
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
    
    if(mSturdinessType == 0) {
        dComIfG_resDelete(&field_0xE04, m_arcname[1]);
    }
    else {
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
static BOOL daSaku_Draw(daSaku_c* m) {
    /* Nonmatching */
    m->saku_draw_sub(0);
    if(m->field_0xEF8[1] != 0) {
        m->saku_draw_sub(1);
    }
    
    return TRUE;
}

BOOL daSaku_c::_daSaku_execute() {
    int iVar2;

    for(int i = 0; i < 2; i++) {
        iVar2 = field_0xEBC[i] ;
        if(iVar2 != 0 && iVar2 < m_max_particle_timer) {
            field_0xEBC[i] = iVar2 + 1;
        }
    }

    if (field_0xEEC != 0) {
        field_0xEEC -= 1;
    }
    field_0xEE0[2] += 1;

    for(int i = 0; i < 2; i ++) {
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

    for(int i = 0; i < 2; i++) {
        changeCollision(i);
    }

    setMtx();
    checkCol();

    return TRUE;
}

/* 0000242C-00002560       .text daSaku_Execute__FP8daSaku_c */
static BOOL daSaku_Execute(daSaku_c* i_this) {
    return i_this->_daSaku_execute();
}

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
