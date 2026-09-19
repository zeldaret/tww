/**
 * d_a_saku.cpp
 * Object - Brown wooden barricade
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_saku.h"
#include "d/d_cc_d.h"

static sakuHIO_c l_sakuHIO;

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


class J3DModelData;
class J3DMaterial;

/* 000000EC-00000200       .text CreateInit__8daSaku_cFv */
void daSaku_c::CreateInit() {
    /* Nonmatching */
}

/* 00000200-000003A8       .text saku_draw_sub__8daSaku_cFi */
void daSaku_c::saku_draw_sub(int) {
    /* Nonmatching */
}

/* 000003A8-00000590       .text mode_break_none__8daSaku_cFi */
void daSaku_c::mode_break_none(int) {
    /* Nonmatching */
}

/* 000005CC-000006A8       .text mode_break_fire__8daSaku_cFi */
void daSaku_c::mode_break_fire(int) {
    /* Nonmatching */
}

/* 000006A8-0000083C       .text mode_break_throw_obj__8daSaku_cFi */
int daSaku_c::mode_break_throw_obj(int i) {
    /* Nonmatching */

    if(mHeap[i][0] != NULL && mHeap[i][1] != NULL) {
        if(this->field_0xEF0[i] != 0) {
            this->field_0xEF0[i] -= 1;

            if(this->field_0xEF0[i] == 0) {
                mDoExt_destroySolidHeap(mHeap[i][0]);
                mHeap[i][0] = NULL;
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
void daSaku_c::RecreateHeap(int, int) {
    /* Nonmatching */
}

/* 000008EC-000009B0       .text CreateHeap__8daSaku_cFii */
bool daSaku_c::CreateHeap(int i_heapId, int i_sakuId) {
    int iVar1;
    int iVar2 = i_heapId;
    bool bVar3;

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
        bVar3 = FALSE;
    }
    else {
        iVar1 = GetDzbId(i_sakuId);
        iVar1 = loadMoveBG(iVar1, i_heapId, i_sakuId);
        bVar3 = iVar1 != 0;
    }

    return bVar3;
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
void daSaku_c::CreateDummyHeap(int) {
    /* Nonmatching */
}

/* 00000ADC-00000BE8       .text loadMoveBG__8daSaku_cFiii */
void daSaku_c::loadMoveBG(int, int, int) {
    /* Nonmatching */
}

/* 00000BE8-00000D7C       .text loadModel__8daSaku_cFiii */
void daSaku_c::loadModel(int, int, int) {
    /* Nonmatching */
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
            this->field_0x30C[i].SetC(mPos[0][i]);
            g_dComIfG_gameInfo.play.mCcS.Set(&this->field_0x30C[i]);
        }
    }


    if(field_0xEF8[1] != 0 && this->field_0xEF8[1] == 1) {
        for(int i = 0; i < 3; i++) {
            this->field_0x69C[i].SetC(mPos[1][i]);
            g_dComIfG_gameInfo.play.mCcS.Set(&this->field_0x69C[i]);
        }
    }

    return;
}

/* 0000134C-00001510       .text setCol__8daSaku_cFv */
void daSaku_c::setCol() {
    /* Nonmatching */
}

/* 00001510-00001598       .text MoveBGResist__8daSaku_cFii */
void daSaku_c::MoveBGResist(int, int) {
    /* Nonmatching */
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

/* 000019AC-00001A50       .text matAlphaAnim__FP12J3DModelDataUcb */
void matAlphaAnim(J3DModelData*, unsigned char, bool) {
    /* Nonmatching */
}

/* 00001A50-00001B98       .text changeXluMaterialAlpha__FP11J3DMaterialUcb */
void changeXluMaterialAlpha(J3DMaterial*, unsigned char, bool) {
    /* Nonmatching */
}

/* 00001B98-00001BB8       .text daSaku_Create__FP10fopAc_ac_c */
static cPhs_State daSaku_Create(fopAc_ac_c* i_this) {
    return ((daSaku_c*)i_this)->_daSaku_create();
}

/* 00001BB8-00001F28       .text _daSaku_create__8daSaku_cFv */
cPhs_State daSaku_c::_daSaku_create() {
    /* Nonmatching */
}

/* 00002264-000023D8       .text daSaku_Delete__FP8daSaku_c */
static BOOL daSaku_Delete(daSaku_c*) {
    /* Nonmatching */
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
