/**
 * d_a_obj_canon.cpp
 * Object - Great Sea enemy cannon
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_canon.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/J3DGraphAnimator/J3DNode.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_ship.h"
#include "d/d_cc_uty.h"
#include "d/d_com_inf_game.h"
#include "d/d_path.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/actor/d_a_bomb.h"
#include "d/d_s_play.h"
#include "d/res/res_wallbom.h"

daObj_Canon_HIO_c l_HIO;

const u32 daObj_Canon_c::m_heapsize = 0x8C0;
const char daObj_Canon_c::m_arc_name[] = "WallBom";
const dCcD_SrcSph daObj_Canon_c::m_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 75.0f,
    }},
};


/* 000000EC-000001A0       .text __ct__17daObj_Canon_HIO_cFv */
daObj_Canon_HIO_c::daObj_Canon_HIO_c() {
    debug_draw = false;
    field_0x05 = 0;
    field_0x08 = 150.0f;
    field_0x14 = 0.0f;
    field_0x18 = 180.0f;
    field_0x1C = 0.0f;
    field_0x20 = 90.0f;
    field_0x24 = -1.1f;
    field_0x28 = 0x16;
    field_0x2C = 5000.0f;
    field_0x30 = 0x3000;
    field_0x32 = 0x2328;
    field_0x34 = -0x2328;
    field_0x36 = 0x2328;
    field_0x38 = -0x2328;
    field_0x3A = 0x2800;
    field_0x3C = 0x1E;
    field_0x3E = 0x1E;
    field_0x40 = 2000.0f;
    field_0x44 = 0.2f;
    field_0x48 = 0;
}

/* 000001E8-00000234       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daObj_Canon_c* i_this = reinterpret_cast<daObj_Canon_c*>(model->getUserArea());
        if (i_this) {
            i_this->_nodeControl(node, model);
        }
    }

    return TRUE;
}

/* 00000234-000003D8       .text _nodeControl__13daObj_Canon_cFP7J3DNodeP8J3DModel */
void daObj_Canon_c::_nodeControl(J3DNode* node, J3DModel* model) {
    J3DJoint* joint = (J3DJoint*)node;
    s32 jntNo = joint->getJntNo();
    mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
    csXyz temp(0, 0, 0);
    if(REG12_S(1)) {
        temp.x = REG12_S(2);
        temp.y = REG12_S(3);
        temp.z = REG12_S(4);
    }
    else {
        temp.x = -field_0x2CA;
        temp.z = -field_0x2C6;
    }
    mDoMtx_stack_c::ZXYrotM(temp);
    field_0x468 += REG12_S(2) + 0x1830;
    mDoMtx_stack_c::XrotM(field_0x46A * (REG12_S(5) + 5) * cM_ssin(field_0x468));
    cXyz temp2;
    temp2.x = REG12_F(3);
    temp2.y = -field_0x46C;
    temp2.z = REG12_F(5);
    mDoMtx_stack_c::transM(temp2);
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
}

/* 000003D8-000003F8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return static_cast<daObj_Canon_c*>(i_this)->_createHeap();
}

/* 000003F8-000004CC       .text _createHeap__13daObj_Canon_cFv */
BOOL daObj_Canon_c::_createHeap() {
    J3DModelData* modelData = (J3DModelData *)dComIfG_getObjectRes(m_arc_name, WALLBOM_BDL_WALLBOM);
    JUT_ASSERT(0x115, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
#if VERSION > VERSION_DEMO
    if(mpModel == NULL) {
        return FALSE;
    }
#endif

    mpModel->setUserArea((u32)this);
    modelData->getJointNodePointer(3)->setCallBack(nodeControl_CB);

    return TRUE;
}

/* 000004CC-000005AC       .text setEffect__13daObj_Canon_cFUs */
void daObj_Canon_c::setEffect(u16 param_1) {
#if VERSION == VERSION_DEMO
    csXyz sp18 = shape_angle;
#endif

    GXColor* prmColor = NULL, *envColor = NULL;
    if(param_1 == dPa_name::ID_SCENE_82E4) {
        prmColor = &tevStr.mColorK0;
        envColor = &tevStr.mColorK0;
    }

    if(param_1 == dPa_name::ID_COMMON_03E1) {
        dComIfGp_particle_set(
            param_1,
#if VERSION == VERSION_DEMO
            &current.pos, &sp18, &scale,
#else
            &current.pos, &shape_angle, &scale,
#endif
            0xFF, &field_0x470, -1,
            prmColor, envColor
        );
        field_0x484 = 0xE6;
    }
    else {
        dComIfGp_particle_set(
            param_1,
#if VERSION == VERSION_DEMO
            &current.pos, &sp18, &scale,
#else
            &current.pos, &shape_angle, &scale,
#endif
            0xFF, NULL, -1,
            prmColor, envColor
        );
    }
}

/* 000005AC-0000082C       .text checkTgHit__13daObj_Canon_cFv */
bool daObj_Canon_c::checkTgHit() {
    mStts.Move();
    if(l_HIO.field_0x05) {
        health = 0;
        modeProcInit(2);
        return true;
    }

    if(cLib_calcTimer(&field_0x440) == 0) {
        CcAtInfo atInfo;
        atInfo.pParticlePos = NULL;
        cCcD_Obj* tg = mSph.GetTgHitObj();
        cXyz hitPos = *mSph.GetTgHitPosP();
        atInfo.mpObj = mSph.GetTgHitObj();
        if (tg == NULL) {
            return false;
        }

        bool hit = true;
        switch(tg->GetAtType()) {
            case AT_TYPE_BOMB:
                health -= 2;
                break;
            case AT_TYPE_BOOMERANG:
                field_0x46A = 0x190;
                fopAcM_seStart(this, JA_SE_LK_W_WEP_HIT, 0x20);
                health -= 1;
                break;
            default:
                hit = false;
        }

        if(hit) {
            field_0x440 = 5;
            dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &hitPos);

            if(health <= 0) {
                daPy_py_c* player = daPy_getPlayerActorClass();
                cXyz particleScale(2.0f, 2.0f, 2.0f);
                dComIfGp_particle_set(dPa_name::ID_COMMON_BIG_HIT, &hitPos, &player->shape_angle, &particleScale);
                fopAcM_seStart(this, JA_SE_LK_LAST_HIT, 0);
                modeProcInit(2);
            }
            else {
                modeProcInit(0);
            }

            return true;
        }
    }

    return false;
}

/* 0000082C-00000990       .text attackCannon__13daObj_Canon_cFv */
void daObj_Canon_c::attackCannon() {
    csXyz angle;
    angle.set(shape_angle.x - field_0x2CA, shape_angle.y + field_0x2C6, shape_angle.z);
    daBomb_c* bomb = (daBomb_c*)fopAcM_fastCreate(PROC_BOMB, daBomb_c::prm_make(daBomb_c::STATE_4, true, true), &field_0x450, tevStr.mRoomNo, &angle);
    bomb->setNoGravityTime(l_HIO.field_0x28);
    bomb->speedF = l_HIO.field_0x20 * cM_scos(angle.x);
    bomb->speed.y = -(l_HIO.field_0x20 * cM_ssin(angle.x));
    bomb->gravity = l_HIO.field_0x24;

    field_0x46A = 0xC8;

    mDoAud_seStart(JA_SE_LK_SHIP_CANNON_FIRE, &field_0x450);
}

/* 00000990-00000B4C       .text lockonCannon__13daObj_Canon_cFv */
void daObj_Canon_c::lockonCannon() {
    f32 temp2 = (current.pos - field_0x2CC).absXZ();

    field_0x2C4 = cLib_targetAngleY(&current.pos, &field_0x2CC) - shape_angle.y;
    s16 temp3 = 0;
    if(temp2 > l_HIO.field_0x2C) {
        temp2 -= l_HIO.field_0x2C;
        temp3 = temp2;
        if(temp3 > l_HIO.field_0x30) {
            temp3 = l_HIO.field_0x30;
        }
    }
    field_0x2C8 = temp3 + cLib_targetAngleX(&current.pos, &field_0x2CC);
    field_0x2C8 = cLib_minMaxLimit(field_0x2C8, l_HIO.field_0x34, l_HIO.field_0x32);
    field_0x2C4 = cLib_minMaxLimit(field_0x2C4, l_HIO.field_0x38, l_HIO.field_0x36);
}

/* 00000B4C-00000BA8       .text setAttention__13daObj_Canon_cFv */
void daObj_Canon_c::setAttention() {
    attention_info.position = field_0x45C;
    attention_info.position.y += l_HIO.field_0x0C;
    eyePos = field_0x45C;
    eyePos.y += l_HIO.field_0x10;
}

/* 00000BA8-00000C2C       .text setCollision__13daObj_Canon_cFv */
void daObj_Canon_c::setCollision() {
    mSph.SetR((80.0f + REG12_F(0)) * scale.x);
    mSph.SetC(field_0x45C);

    if(mCurMode != 2 && mCurMode != 3) {
        dComIfG_Ccsp()->Set(&mSph);
    }
}

/* 00000C2C-00000CB4       .text setMtx__13daObj_Canon_cFv */
void daObj_Canon_c::setMtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000CB4-00000CC8       .text modeWaitInit__13daObj_Canon_cFv */
void daObj_Canon_c::modeWaitInit() {
    field_0x444 = l_HIO.field_0x3E;
}

/* 00000CC8-00001064       .text modeWait__13daObj_Canon_cFv */
void daObj_Canon_c::modeWait() {
    if(!checkTgHit()) {
        daPy_py_c* player = daPy_getPlayerActorClass();

        if(dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK1000000_e)) {
            field_0x444 = l_HIO.field_0x3E * 10;
            field_0x488 = 0;
        }

        daShip_c* ship = dComIfGp_getShipActor();
        if(ship && ship->checkShootCannon()) {
            field_0x488++;
        }

        if(cLib_calcTimer(&field_0x444) == 0) {
            if(field_0x298.chkInside(&player->current.pos)) {
                s16 temp = l_HIO.field_0x08;

                f32 abs = (current.pos - field_0x2CC).absXZ();
                if(abs > l_HIO.field_0x40) {
                    temp = temp + (abs - l_HIO.field_0x40) * l_HIO.field_0x44;
                }

                field_0x2CC = daPy_getPlayerActorClass()->current.pos;

                if(field_0x298.chkInside(&field_0x2CC)) {
                    if(dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK1000000_e | daPyStts0_SWIM_e)) {
                        field_0x488 = 0;
                        f32 tmp = 3000.0f; 
                        temp += tmp;
                    }
                    else if(abs > l_HIO.field_0x40 && field_0x488 < 6) {
                        f32 tmp = 200.0f * (6 - field_0x488);
                        temp += tmp;
                    }

                    s16 temp2 = fopAcM_searchActorAngleY(this, daPy_getPlayerActorClass());

                    field_0x2CC.x -= temp * cM_ssin(temp2);
                    field_0x2CC.z -= temp * cM_scos(temp2);

                    field_0x444 = l_HIO.field_0x3E;

                    modeProcInit(1);
                }
            }
            else {
                field_0x2C8 = 0;
                field_0x2C4 = 0;
                field_0x444 = l_HIO.field_0x3E;
            }
        }
    }
}

/* 00001064-00001078       .text modeAttackInit__13daObj_Canon_cFv */
void daObj_Canon_c::modeAttackInit() {
    field_0x444 = l_HIO.field_0x3C;
}

/* 00001078-000010DC       .text modeAttack__13daObj_Canon_cFv */
void daObj_Canon_c::modeAttack() {
    if(!checkTgHit()) {
        lockonCannon();

        if(cLib_calcTimer(&field_0x444) == 0) {
            attackCannon();
            modeProcInit(0);
        }
    }
}

/* 000010DC-00001174       .text modeDeleteInit__13daObj_Canon_cFv */
void daObj_Canon_c::modeDeleteInit() {
    field_0x46A = 0;

    if(field_0x295 != 0xFF) {
        dComIfGs_onSwitch(field_0x295, fopAcM_GetRoomNo(this));
    }

    setEffect(dPa_name::ID_SCENE_82E4);
    setEffect(dPa_name::ID_SCENE_82E5);
    setEffect(dPa_name::ID_SCENE_82E6);
    setEffect(dPa_name::ID_COMMON_03E1);

    fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e | 0x1F);
}

/* 00001174-00001178       .text modeDelete__13daObj_Canon_cFv */
void daObj_Canon_c::modeDelete() {
    return;
}

/* 00001178-00001194       .text modeSwWaitInit__13daObj_Canon_cFv */
void daObj_Canon_c::modeSwWaitInit() {
    field_0x46C = 120.0f;
    fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e | 0x1F);
}

/* 00001194-000011F4       .text modeSwWait__13daObj_Canon_cFv */
void daObj_Canon_c::modeSwWait() {
    if(field_0x296 != 0xFF) {
        if(dComIfGs_isSwitch(field_0x296, fopAcM_GetRoomNo(this))) {
            modeProcInit(4);
        }
    }
}

/* 000011F4-0000121C       .text modeAppearInit__13daObj_Canon_cFv */
void daObj_Canon_c::modeAppearInit() {
    field_0x46A = 0x258;
    field_0x46C = 120.0f;
    fopAcM_SetStatusMap(this, 0x15);
}

/* 0000121C-00001290       .text modeAppear__13daObj_Canon_cFv */
void daObj_Canon_c::modeAppear() {
    cLib_addCalc2(&field_0x46C, 0.0f, 0.1f, 1.0f);
    if(field_0x46C < 2.0f) {
        field_0x46C = 0.0f;
        modeProcInit(0);
    }
}

/* 00001290-00001410       .text modeProc__13daObj_Canon_cFQ213daObj_Canon_c6Proc_ei */
void daObj_Canon_c::modeProc(daObj_Canon_c::Proc_e proc, int newMode) {
    typedef void(daObj_Canon_c::*mode_func_t)(void);
    struct mode_entry_t {
        mode_func_t init;
        mode_func_t run;
        const char* name;
    };
    
    static mode_entry_t mode_tbl[] = {
        {
            &daObj_Canon_c::modeWaitInit,
            &daObj_Canon_c::modeWait,
            "WAIT",
        },
        {
            &daObj_Canon_c::modeAttackInit,
            &daObj_Canon_c::modeAttack,
            "ATTACK",
        },
        {
            &daObj_Canon_c::modeDeleteInit,
            &daObj_Canon_c::modeDelete,
            "DELETE",
        },
        {
            &daObj_Canon_c::modeSwWaitInit,
            &daObj_Canon_c::modeSwWait,
            "SW_WAIT",
        },
        {
            &daObj_Canon_c::modeAppearInit,
            &daObj_Canon_c::modeAppear,
            "APPEAR",
        },
    };

    if(proc == PROC_INIT) {
        mCurMode = newMode;
        (this->*mode_tbl[mCurMode].init)();
    }
    else if(proc == PROC_EXEC) {
        (this->*mode_tbl[mCurMode].run)();
    }
}

/* 00001410-000015AC       .text _execute__13daObj_Canon_cFv */
bool daObj_Canon_c::_execute() {
    cLib_addCalcAngleS2(&field_0x46A, 0, 0xA, 0xA);
    cLib_addCalcAngleS2(&field_0x2CA, field_0x2C8, 0x6, 0x300);
    cLib_addCalcAngleS2(&field_0x2C6, field_0x2C4, 0x6, 0x300);

    setAttention();
    setCollision();

    modeProc(PROC_EXEC, 5);

    mpModel->calc();
    Vec temp = {0.0f, 0.0f, 0.0f};
    temp.x = l_HIO.field_0x14;
    temp.y = l_HIO.field_0x18 * scale.x;
    temp.z = l_HIO.field_0x1C;
    mDoMtx_multVec(mpModel->getAnmMtx(3), &temp, &field_0x450);
    Vec temp2 = {0.0f, 0.0f, 0.0f};
    temp2.x = REG12_F(0);
    temp2.y = (REG12_F(1) + 60.0f) * scale.x;
    temp2.z = REG12_F(2);
    mDoMtx_multVec(mpModel->getAnmMtx(3), &temp2, &field_0x45C);

    if(field_0x470.getEmitter()) {
        if(cLib_calcTimer(&field_0x484) == 0) {
            field_0x470.end();
        }
    }

    setMtx();

    return false;
}

/* 000015AC-000015B0       .text debugDraw__13daObj_Canon_cFv */
void daObj_Canon_c::debugDraw() {
    GXColor col = {0xFF, 0x00, 0x00, 0x80};
    GXColor col2 = {0xFF, 0x00, 0x00, 0x80};

    return;
}

/* 000015B0-00001688       .text _draw__13daObj_Canon_cFv */
bool daObj_Canon_c::_draw() {
    if(l_HIO.debug_draw) {
        debugDraw();
    }

    if(mCurMode == 2 || mCurMode == 3) {
        mpModel->getModelData()->getJointNodePointer(3)->getMesh()->getShape()->hide();
    }
    else {
        mpModel->getModelData()->getJointNodePointer(3)->getMesh()->getShape()->show();
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelEntryDL(mpModel);

    return true;
}

/* 00001688-00001804       .text createInit__13daObj_Canon_cFv */
void daObj_Canon_c::createInit() {
    if(field_0x295 != 0xFF && dComIfGs_isSwitch(field_0x295, fopAcM_GetRoomNo(this))) {
        modeProcInit(2);
    }
    else if(field_0x296 != 0xFF && !dComIfGs_isSwitch(field_0x296, fopAcM_GetRoomNo(this))) {
        modeProcInit(3);
    }
    else {
        modeProcInit(0);
    }

    max_health = 2;
    health = max_health;
    
    field_0x2B0 = dPath_GetRoomPath(field_0x294, current.roomNo);
    field_0x298.setInfDrct(field_0x2B0);

    setMtx();

    mpModel->calc();

    f32 temp = scale.x;
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -100.0f * temp, -100.0f * temp, -10.0f * temp, 100.0f * temp, 100.0f * temp, 150.0f * temp);
    fopAcM_setCullSizeFar(this, 10.0f);

    mStts.Init(0xFF, 0xFF, this);
    mSph.Set(m_sph_src);
    mSph.SetStts(&mStts);
}

/* 00001804-00001880       .text getArg__13daObj_Canon_cFv */
void daObj_Canon_c::getArg() {
    u32 param = fopAcM_GetParam(this);
    field_0x297 = fopAcM_GetParamBit(param, 0, 0xFF);
    field_0x296 = fopAcM_GetParamBit(param, 8, 0xFF);
    field_0x294 = fopAcM_GetParamBit(param, 16, 0xFF);
    field_0x295 = fopAcM_GetParamBit(param, 24, 0xFF);
    if(field_0x297 != 0xFF) {
        scale.set(1.0 + field_0x297 * 0.1, 1.0 + field_0x297 * 0.1, 1.0 + field_0x297 * 0.1);
    }
}

/* 00001880-000019D8       .text _create__13daObj_Canon_cFv */
cPhs_State daObj_Canon_c::_create() {
    fopAcM_SetupActor(this, daObj_Canon_c);

    int result = dComIfG_resLoad(&mPhs, m_arc_name);
    if(result == cPhs_COMPLEATE_e) {
        getArg();

#if VERSION > VERSION_DEMO
        if(field_0x294 == 0xFF) {
            return cPhs_ERROR_e;
        }
#endif

        if(!fopAcM_entrySolidHeap(this, createHeap_CB, m_heapsize)) {
            return cPhs_ERROR_e;
        }

        createInit();
    }

    return result;
}

/* 00001BEC-00001C50       .text _delete__13daObj_Canon_cFv */
bool daObj_Canon_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
    field_0x470.end();
#if VERSION > VERSION_DEMO
    mDoAud_seDeleteObject(&field_0x450);
#endif

    return true;
}

/* 00001C50-00001C70       .text daObj_CanonCreate__FPv */
static cPhs_State daObj_CanonCreate(void* i_this) {
    return ((daObj_Canon_c*)i_this)->_create();
}

/* 00001C70-00001C94       .text daObj_CanonDelete__FPv */
static BOOL daObj_CanonDelete(void* i_this) {
    return ((daObj_Canon_c*)i_this)->_delete();
}

/* 00001C94-00001CB8       .text daObj_CanonExecute__FPv */
static BOOL daObj_CanonExecute(void* i_this) {
    return ((daObj_Canon_c*)i_this)->_execute();
}

/* 00001CB8-00001CDC       .text daObj_CanonDraw__FPv */
static BOOL daObj_CanonDraw(void* i_this) {
    return ((daObj_Canon_c*)i_this)->_draw();
}

/* 00001CDC-00001CE4       .text daObj_CanonIsDelete__FPv */
static BOOL daObj_CanonIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_CanonMethodTable = {
    (process_method_func)daObj_CanonCreate,
    (process_method_func)daObj_CanonDelete,
    (process_method_func)daObj_CanonExecute,
    (process_method_func)daObj_CanonIsDelete,
    (process_method_func)daObj_CanonDraw,
};

actor_process_profile_definition g_profile_OBJ_CANON = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_CANON,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Canon_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_CANON,
    /* Actor SubMtd */ &daObj_CanonMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
