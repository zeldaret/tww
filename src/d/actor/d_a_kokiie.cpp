/**
 * d_a_kokiie.cpp
 * Object - Forbidden Woods - Hanging flower house
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_kokiie.h"
#include "d/actor/d_a_shand.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/d_com_inf_game.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/res/res_kokiie.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "JSystem/JUtility/JUTReport.h"

static cXyz ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    // There was an unused function here that got stripped out, but it still affected literal and weak function ordering.
    f32* dummy = NULL;
    *dummy = 10.0f;
    *dummy = 50.0f;
    *dummy = 5.0f;
    *dummy = 1.0f;
    *dummy = 1.2f;
    *dummy = -100.0f;
    *dummy = 0.1f;
    cXyz temp(0.0f, 0.0f, 0.0f);
    return temp;
}

/* 000000B4-00000154       .text daKokiie_Draw__FP12kokiie_class */
static BOOL daKokiie_Draw(kokiie_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &actor->current.pos, &actor->tevStr);
    g_env_light.setLightTevColorType(i_this->mpModel, &(i_this->actor).tevStr);

    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(i_this->mpModel);
    dComIfGd_setList();
    return TRUE;
}

/* 00000154-00000884       .text kokiie_move__FP12kokiie_class */
void kokiie_move(kokiie_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    int i;
    int uVar6;
    s16 maxSpeed;
    s16 target;
    s16 sVar1;

    static u8 himo_off_check[] = {1, 2, 4, 8, 16};
    static s16 himo_off_ya[] = {
        0x1,    0x0,    0x2EE0, 0x1D4C, 0x5FB4, 0x0,    0x4E20, 0x30D4, 0x987C, 0x0,    0x0,    0x1964, 0x7FFF, 0x7FFF, 0x6784, 0x5014,
        0xCF2C, 0xE2B4, 0x0,    0x0,    0x0,    0xE4A8, 0x4C2C, 0x1D4C, 0xB1E0, 0xCF2C, 0xB3D4, 0xE2B4, 0x987C, 0xB3D4, 0x8000, 0x1,
    };
    static s16 himo_off_xa[] = {
        0x0,   0x7D0, 0x7D0, 0xBB8, 0x7D0, 0x0,   0xBB8, 0xFA0, 0x7D0, 0x0,   0x0,   0x7D0, 0xBB8, 0x7D0, 0xFA0, 0xFA0,
        0x3E8, 0x7D0, 0x0,   0xFA0, 0x0,   0x7D0, 0x7D0, 0xFA0, 0xBB8, 0xFA0, 0xBB8, 0xFA0, 0xFA0, 0xFA0, 0xFA0, 0xFA0,
    };
    static s16 himo_off_yp[] = {
        0x0,  0x96,  0x96,  0x12C, 0x96,  0x190, 0x190, 0x1F4, 0x96,  0x12C, 0x12C, 0x1F4, 0x12C, 0x1F4, 0x1F4, 0x2BC,
        0x96, 0x12C, 0x12C, 0x1F4, 0x12C, 0x1F4, 0x1F4, 0x2BC, 0x12C, 0x1F4, 0x1F4, 0x2BC, 0x1F4, 0x2BC, 0x2BC, 0x0,
    };

    i_this->m298++;

    switch (i_this->m29A) {
    case 0: {
        uVar6 = 0;
        for (i = 0; i < ARRAY_SSIZE(i_this->m32C); i++) {
            if (i_this->m32C[i] == 2) {
                i_this->m32C[i] = 0;
                i_this->m338 = 0.0f;
            }

            if (i_this->m32C[i] != 0) {
                if (i_this->m32C[i] == 1) {
                    i_this->m338 = 1.0f;
                    i_this->m32C[i] = 5;
                }
                uVar6 |= himo_off_check[i];
            }
        }

        sVar1 = himo_off_ya[uVar6];
        target = himo_off_xa[uVar6];
        cLib_addCalc2(&i_this->m2D0, REG8_F(4) - himo_off_yp[uVar6], 0.1f, i_this->m338 * 50.0f);
        if ((uVar6 == 0x1f) && dComIfGs_checkGetItem(dItem_BOOMERANG_e)) {
            i_this->m29A = 1;
            actor->health = 0;
            i_this->m378 = 1;
        }

        maxSpeed = i_this->m338 * 10000.0f;
        cLib_addCalcAngleS2(&i_this->m334, target, 4, maxSpeed);

        if (target != 0) {
            cLib_addCalcAngleS2(&i_this->m332, sVar1, 2, maxSpeed);
        }

        cLib_addCalc2(&i_this->m338, 1.0f, 1.0f, REG8_F(14) + 0.001f);
        cLib_addCalcAngleS2(&actor->current.angle.x, 0, 10, 0x200);
        cLib_addCalcAngleS2(&actor->current.angle.z, 0, 10, 0x200);

        i_this->m2C8.x = i_this->m2BC * cM_ssin(i_this->m298 * 900);
        i_this->m2C8.z = i_this->m2C4 * cM_ssin(i_this->m298 * 700);

        cLib_addCalc2(&i_this->m2BC, REG14_F(9) + 300.0f, 1.0f, REG14_F(3) + 20.0f);
        cLib_addCalc2(&i_this->m2C4, REG14_F(9) + 300.0f, 1.0f, REG14_F(3) + 20.0f);

        i_this->m2A4.x = i_this->m2B0 * cM_ssin(i_this->m298 * 0x2ee);
        i_this->m2A4.z = i_this->m2B8 * cM_ssin(i_this->m298 * 900);

        cLib_addCalc0(&i_this->m2B0, 1.0f, 0.25f);
        cLib_addCalc0(&i_this->m2B8, 1.0f, 0.25f);

        actor->shape_angle = actor->current.angle + i_this->m2C8;
        actor->current.pos = actor->home.pos + i_this->m2A4;
        actor->current.pos.y += i_this->m2D0;
        cLib_addCalc0(&i_this->m2A4.y, 0.05f, REG0_F(7) + 2.0f);
    } break;

    case 1:
        cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 10, 0x800);
        cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 10, 0x800);
        cLib_addCalcAngleS2(&i_this->m334, 0, 4, 0x200);

        actor->current.pos.y += actor->speed.y;
        actor->speed.y -= REG12_F(14) + 3.0f;

        if (i_this->m37A == (s16)(REG0_S(4) + 0x1b)) {
            if (i_this->m2A2 != 0xff) {
                dComIfGs_onSwitch(i_this->m2A2, fopAcM_GetRoomNo(&i_this->actor));
            }

            fopAcM_seStartCurrent(&i_this->actor, JA_SE_OBJ_KOKIRI_H_CRASH, 0);
            dComIfGp_getVibration().StartShock(REG0_S(2) + 4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        }

        if (i_this->m37A == (s16)(REG0_S(5) + 0x40)) {
            cXyz sp44 = actor->current.pos;
            sp44.y = 1170.0f;
            dComIfGp_particle_set(dPa_name::ID_SCENE_82A4, &sp44);
            dComIfGp_particle_set(dPa_name::ID_SCENE_82A5, &sp44);
            dComIfGp_particle_set(dPa_name::ID_SCENE_82A6, &actor->current.pos);
            dComIfGp_particle_set(dPa_name::ID_SCENE_82A7, &sp44);
        }

        i_this->m374 = (REG0_F(9) + 5180.0f) - 3800.0f;
        if (actor->current.pos.y <= i_this->m374) {
            actor->current.pos.y = i_this->m374;
            if (actor->speed.y < -20.0f) {
                dComIfGp_getVibration().StartShock(REG6_S(2) + 7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                fopAcM_seStartCurrent(&i_this->actor, JA_SE_OBJ_KOKIRI_H_LANDING, 0);
                i_this->m39C = REG12_F(10) + 40.0f + 50.0f;
            }
            actor->speed.y = 0.0f;
            cLib_addCalcAngleS2(&i_this->m334, 0, 2, 0x2000);
        }
        break;
    }
}

/* 00000884-00000A18       .text himo_create__FP12kokiie_class */
#if VERSION == VERSION_DEMO
void himo_create(kokiie_class* i_this) {
#else
BOOL himo_create(kokiie_class* i_this) {
#endif
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
#if VERSION > VERSION_DEMO
    if ((i_this->m2A2 != 0xff) && fopAcM_isSwitch(&i_this->actor, i_this->m2A2)) {
        return FALSE;
    }
    s32 uVar2 = 0;
#endif

    fopAcM_prm_class* pfVar3;
    shand_class* pfVar6;

    for (s32 i = 0; i < ARRAY_SSIZE(i_this->m2E8); i++) {
        switch (i_this->m2E8[i]) {
        case 0:
            pfVar3 = fopAcM_CreateAppend();
            pfVar3->base.position = actor->current.pos;
            pfVar3->base.angle.y = actor->current.angle.y + i * 0x3333 + -13000;
            pfVar3->base.parameters = 0xffffff01;
            pfVar3->room_no = actor->current.roomNo;
            i_this->m2D4[i] = fopAcM_create(PROC_SHAND, NULL, pfVar3);
            i_this->m2E8[i]++;

        case 1:
            pfVar6 = (shand_class*)fopAcM_SearchByID(i_this->m2D4[i]);
            if (pfVar6 != NULL) {
                pfVar6->field_308 = fopAcM_GetID(&i_this->actor);
                pfVar6->field_310 = &i_this->m2F0[i];
                pfVar6->field_314 = &i_this->m32C[i];
                i_this->m2E8[i]++;
#if VERSION > VERSION_DEMO
                uVar2++;
#endif
            }
            break;

        case 2:
            break;
        }
    }

#if VERSION > VERSION_DEMO
    return uVar2 < 5;
#endif
}

/* 00000A18-00000E98       .text demo_camera__FP12kokiie_class */
void demo_camera(kokiie_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    cXyz sp5C;
    cXyz sp50;

    cMtx_YrotS(*calc_mtx, actor->shape_angle.y);

    switch (i_this->m378) {
    case 0:
        break;

    case 1:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(&i_this->actor, 2, 0xffff, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->m378++;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->m37C = actor->current.pos;
        sp5C.x = (REG12_F(2) + 1300.0f) - 800.0f;
        sp5C.y = 0.0f;
        sp5C.z = REG12_F(4) - 1000.0f;
        MtxPosition(&sp5C, &sp50);

        i_this->m37C.x = actor->current.pos.x + sp50.x;
        i_this->m37C.y = ((REG12_F(5) + 4030.0f) - 3800.0f) + 1500.0f;
        i_this->m37C.z = actor->current.pos.z + sp50.z;
        i_this->m388 = actor->current.pos;
        i_this->m388.y += REG12_F(6) + -450.0f;
        i_this->m3A0 = REG12_F(18) + 65.0f;
        i_this->m37A = 0;

    case 2:
        if (i_this->m37A < (s16)(REG12_S(3) + 10)) {
            actor->speed.y = 0.0f;
        }

        cLib_addCalc2(&i_this->m388.y, (actor->current.pos.y - 450.0f) + REG12_F(6), REG12_F(7) + 0.5f, REG12_F(8) + 200.0f);
        if (i_this->m37A > (s16)(REG12_S(4) + 0x32)) {
            cLib_addCalc2(&i_this->m3A0, REG12_F(19) + 80.0f, 0.02f, REG12_F(20) + 0.5f);
        }

        if (i_this->m37A == 100) {
            mDoAud_seStart(JA_SE_READ_RIDDLE_1);
        }

        if ((i_this->m37A == 0x96) && (REG0_S(3) == 0)) {
            i_this->m378 = 0;
            dComIfGp_event_reset();
            camera->mCamera.Reset(i_this->m388, i_this->m37C);
            camera->mCamera.Start();
            camera->mCamera.SetTrimSize(0);
        }
        break;
    }

    if (i_this->m378 != 0) {
        f32 sin = i_this->m39C * cM_ssin(i_this->m37A * 0x3300);
        f32 cos = i_this->m39C * cM_scos(i_this->m37A * 0x3000);
        cXyz sp44;
        cXyz sp38;

        sp44.x = i_this->m37C.x + sin;
        sp44.y = i_this->m37C.y + cos;
        sp44.z = i_this->m37C.z;

        sp38.x = i_this->m388.x + sin;
        sp38.y = i_this->m388.y + cos;
        sp38.z = i_this->m388.z;

        s16 iVar1 = i_this->m39C * cM_scos(i_this->m298 * 0x1c00) * 8.0f;
        camera->mCamera.Set(sp38, sp44, iVar1, i_this->m3A0);
        cLib_addCalc0(&i_this->m39C, 1.0f, REG0_F(16) + 5.0f);
        JUTReport(0x19a, 0x1ae, "K SUB  COUNT  %d", i_this->m37A);
        i_this->m37A = i_this->m37A + 1;
    }
}

/* 00000E98-0000107C       .text daKokiie_Execute__FP12kokiie_class */
static BOOL daKokiie_Execute(kokiie_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    kokiie_move(i_this);
    MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, 0);

    cMtx_YrotM(*calc_mtx, actor->shape_angle.y);
    cMtx_YrotM(*calc_mtx, i_this->m332);
    cMtx_XrotM(*calc_mtx, i_this->m334);
    cMtx_YrotM(*calc_mtx, -i_this->m332);
    cMtx_XrotM(*calc_mtx, actor->shape_angle.x);
    cMtx_ZrotM(*calc_mtx, actor->shape_angle.z);
    cMtx_YrotM(*calc_mtx, 0xb54);

    i_this->mpModel->setBaseTRMtx(*calc_mtx);
    MTXCopy(*calc_mtx, i_this->m340);
    i_this->pm_bgw->Move();
    cMtx_YrotM(*calc_mtx, -0xb54);

    for (s32 i = 0; i < ARRAY_SSIZE(i_this->m2F0); i++) {
        MtxPush();
        cMtx_YrotM(*calc_mtx, i * 0x3333);
        cXyz sp08;
        sp08.x = 0.0f;
        sp08.y = REG0_F(5) + -170.0f;
        sp08.z = REG0_F(6) + 400.0f;
        MtxPosition(&sp08, &i_this->m2F0[i]);
        MtxPull();
    }

#if VERSION == VERSION_DEMO
    himo_create(i_this);
#endif
    demo_camera(i_this);
    return TRUE;
}

/* 0000107C-00001084       .text daKokiie_IsDelete__FP12kokiie_class */
static BOOL daKokiie_IsDelete(kokiie_class*) {
    return TRUE;
}

/* 00001084-000010E4       .text daKokiie_Delete__FP12kokiie_class */
static BOOL daKokiie_Delete(kokiie_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    dComIfG_resDeleteDemo(&i_this->mPhase, "Kokiie");
#if VERSION > VERSION_DEMO
    if (actor->heap != NULL)
#endif
    {
        dComIfG_Bgsp()->Release(i_this->pm_bgw);
    }
    return TRUE;
}

/* 000010E4-00001250       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* a_this) {
    kokiie_class* actor = (kokiie_class*)a_this;

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Kokiie", KOKIIE_BDL_KOKI_00);
    actor->mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (actor->mpModel == NULL) {
        return FALSE;
    }

    JUT_ASSERT(DEMO_SELECT(924, 945), modelData != NULL);

    actor->pm_bgw = new dBgW();
    JUT_ASSERT(DEMO_SELECT(929, 950), actor->pm_bgw != NULL);

    actor->pm_bgw->Set((cBgD_t*)dComIfG_getObjectRes("Kokiie", KOKIIE_DZB_KOKI_00), dBgW::MOVE_BG_e, &actor->m340);
    actor->pm_bgw->SetCrrFunc(dBgS_MoveBGProc_Typical);
    return TRUE;
}

/* 00001250-000014E4       .text daKokiie_Create__FP10fopAc_ac_c */
static cPhs_State daKokiie_Create(fopAc_ac_c* a_this) {
    kokiie_class* i_this = (kokiie_class*)a_this;

    fopAcM_ct(a_this, kokiie_class);

    cPhs_State PVar3 = dComIfG_resLoad(&i_this->mPhase, "Kokiie");
#if VERSION == VERSION_DEMO
    if (PVar3 == cPhs_COMPLEATE_e)
#else
    if (PVar3 != cPhs_COMPLEATE_e) {
        return PVar3;
    }
#endif
    {

        i_this->m2A0 = fopAcM_GetParam(a_this);
        if (i_this->m2A0 == 0xff) {
            i_this->m2A0 = 0;
        }

        i_this->m2A2 = fopAcM_GetParam(a_this) >> 0x18;
#if VERSION > VERSION_DEMO
        if (himo_create(i_this)) {
            return FALSE;
        }
#endif

        if (!fopAcM_entrySolidHeap(a_this, CallbackCreateHeap, 0x10000)) {
            return cPhs_ERROR_e;
        }

        if ((i_this->pm_bgw != NULL) && dComIfG_Bgsp()->Regist(i_this->pm_bgw, a_this)) {
            return cPhs_ERROR_e;
        }

        switch (i_this->m2A0) {
        case 1:
            a_this->scale.x = 0.9f;
            a_this->scale.z = 0.9f;
            break;

        case 2:
            a_this->scale.x = 0.8f;
            a_this->scale.z = 0.8f;
            break;

        case 3:
            a_this->scale.x = 0.7f;
            a_this->scale.z = 0.7f;
            break;

        default:
            a_this->scale.z = 1.0f;
            a_this->scale.x = 1.0f;
            break;
        }

        a_this->scale.y = 1.0f;

        fopAcM_SetMtx(a_this, i_this->mpModel->getBaseTRMtx());
        fopAcM_SetMin(a_this, a_this->scale.x * -1000.0f, VERSION_SELECT(-1000.0f, -1000.0f, -1500.0f, -1000.0f), a_this->scale.z * -1000.0f);
        fopAcM_SetMax(a_this, a_this->scale.x * 1000.0f, 1000.0f, a_this->scale.z * 1000.0f);

        i_this->mpModel->setBaseScale(a_this->scale);
        a_this->health = 1;
        if ((i_this->m2A2 != 0xff) && fopAcM_isSwitch(a_this, i_this->m2A2)) {
            a_this->current.pos.y = i_this->m374 + 50.0f + 720.0f + REG0_F(17);
            i_this->m29A = 1;
            a_this->health = 0;

#if VERSION == VERSION_DEMO
            for (s32 i = 0; i < ARRAY_SSIZE(i_this->m2E8); i++) {
                i_this->m2E8[i] = 2;
            }
#endif
        }

        for (s32 i = 0; i < 2; i++) {
            daKokiie_Execute(i_this);
        }
    }
    return PVar3;
}

static actor_method_class l_daKokiie_Method = {
    (process_method_func)daKokiie_Create,
    (process_method_func)daKokiie_Delete,
    (process_method_func)daKokiie_Execute,
    (process_method_func)daKokiie_IsDelete,
    (process_method_func)daKokiie_Draw,
};

actor_process_profile_definition g_profile_KOKIIE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KOKIIE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kokiie_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KOKIIE,
    /* Actor SubMtd */ &l_daKokiie_Method,
    /* Status       */ fopAcStts_CULL_e | DEMO_SELECT(0, fopAcStts_UNK4000_e) | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
