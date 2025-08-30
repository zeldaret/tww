/**
 * d_a_dk.cpp
 * NPC - Helmaroc King (Forsaken Fortress 1 tower, Outset Island)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_dk.h"
#include "d/res/res_dk.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "f_op/f_op_actor_mng.h"

static void dummy() {
    // string-ordering fix.
    OSReport("Dk");
}

daDk_HIO_c l_HIO;

/* 000000EC-00000130       .text __ct__10daDk_HIO_cFv */
daDk_HIO_c::daDk_HIO_c() {
    mNo = -1;
    field_0x05 = 0;
    field_0x08 = 1.0f;
    field_0x0C = 4.0f;
    field_0x10 = 1.5f;
    field_0x14 = 0;
}

/* 00000130-000001EC       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    /* Nonmatching */
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jnt_no = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();

        dk_class* a_this = (dk_class*)model->getUserArea();
        if (a_this != NULL) {
            MTXCopy(model->getAnmMtx(jnt_no), *calc_mtx);

            s32 tail_idx = ((jnt_no - 58) / 2);

            cXyz pos_vec;
            pos_vec.x = pos_vec.y = pos_vec.z = 0.0f;
            MtxPosition(&pos_vec, &a_this->tails[tail_idx].field_0x150[1]);
            pos_vec.x = -10.0f;
            MtxPosition(&pos_vec, &a_this->tails[tail_idx].field_0x150[0]);
        }
    }

    return TRUE;
}

/* 00000228-00000720       .text tail_control__FP8dk_classP6tail_s */
static void tail_control(dk_class* a_this, tail_s* tail) {
    /* Nonmatching */
    s32 i;

    cXyz vec = tail->field_0x150[1] - tail->field_0x150[0];

    tail->field_0x168.y = cM_atan2s(vec.x, vec.z);
    f32 xz_dist = std::sqrtf(vec.x * vec.x + vec.z * vec.z);
    tail->field_0x168.x = -cM_atan2s(vec.y, xz_dist);

    vec.x = 0.0f;
    vec.y = 0.0f;
    vec.z = REG0_F(5) + 25.0f + 5.0f;
    cMtx_YrotS(*calc_mtx, tail->field_0x168.y);
    cMtx_XrotM(*calc_mtx, tail->field_0x168.x);
    MtxPosition(&vec, &tail->field_0x170);

    tail->field_0x024[0] = tail->field_0x150[1];

    cXyz* field_24_ptr = &tail->field_0x024[1];
    csXyz* field_9C_ptr = &tail->field_0x09C[1];
    cXyz* field_D8_ptr = &tail->field_0x0D8[1];

    f32 unk = REG0_F(2) + 0.77000004f;
    f32 unk2;
    if (a_this->field_0x2B4 >= 2) {
        unk2 = -G_CM3D_F_INF;
    } else {
        unk2 = a_this->field_0x900.GetGroundH() + 5.0f;
    }

    for (i = 1; i < 10; i++) {
        cXyz* field_24_ptr_prev = field_24_ptr - 1;
        cXyz pos_vec;

        f32 multiplier = 1.0f - (i - 1) * (REG0_F(4) + 0.1f);
        cXyz new_vec;
        new_vec.x = field_D8_ptr->x + tail->field_0x170.x * multiplier;
        new_vec.y = field_D8_ptr->y + tail->field_0x170.y * multiplier;
        new_vec.z = field_D8_ptr->z + tail->field_0x170.z * multiplier;

        f32 y_base = field_24_ptr->y + new_vec.y;
        if (y_base < unk2) {
            y_base = unk2;
        }

        f32 y_2 = y_base - field_24_ptr_prev->y;
        f32 x_2 = new_vec.x + (field_24_ptr->x - field_24_ptr_prev->x);
        f32 z_2 = new_vec.z + (field_24_ptr->z - field_24_ptr_prev->z);

        s16 new_x_angle;
        s32 new_y_angle = cM_atan2s(x_2, z_2);
        f32 xz_dist = std::sqrtf(x_2 * x_2 + z_2 * z_2);
        new_x_angle = -cM_atan2s(y_2, xz_dist);
        (field_9C_ptr - 1)->y = new_y_angle;
        (field_9C_ptr - 1)->x = new_x_angle;

        vec.x = 0.0f;
        vec.y = 0.0f;

        f32 temp = l_HIO.field_0x10 * ((i * 0.03f) + 0.25f) * 20.0f;
        vec.z = temp * (2.0f * l_HIO.field_0x0C);

        cMtx_YrotS(*calc_mtx, new_y_angle);
        cMtx_XrotM(*calc_mtx, new_x_angle);

        MtxPosition(&vec, &pos_vec);
        *field_D8_ptr = *field_24_ptr;

        field_24_ptr->x = field_24_ptr_prev->x + pos_vec.x;
        field_24_ptr->y = field_24_ptr_prev->y + pos_vec.y;
        field_24_ptr->z = field_24_ptr_prev->z + pos_vec.z;

        field_D8_ptr->x = unk * (field_24_ptr->x - field_D8_ptr->x);
        field_D8_ptr->y = unk * (field_24_ptr->y - field_D8_ptr->y);
        field_D8_ptr->z = unk * (field_24_ptr->z - field_D8_ptr->z);

        field_24_ptr++;
        field_9C_ptr++;
        field_D8_ptr++;
    }
}

static f32 tial_scale[] = {
    0.25f, 0.275f, 0.2875f, 0.3f, 0.325f, 0.375f, 0.4625f, 0.575f, 0.8f,
};

/* 00000720-00000820       .text tail_draw__FP8dk_classP6tail_s */
static void tail_draw(dk_class* a_this, tail_s* tail) {
    cXyz* trans = &tail->field_0x024[0];
    csXyz* rot = &tail->field_0x09C[0];

    for (int i = 0; i < 9; i++) {
        f32 scale = l_HIO.field_0x0C * tial_scale[i];

        MtxTrans(trans->x, trans->y, trans->z, false);
        MtxScale(scale, scale, scale, true);
        cMtx_YrotM(*calc_mtx, rot->y);
        cMtx_XrotM(*calc_mtx, rot->x);

        J3DModel* model = tail->models[i];

        model->setBaseTRMtx(*calc_mtx);
        g_env_light.setLightTevColorType(model, &a_this->tevStr);
        mDoExt_modelUpdate(model);

        trans++;
        rot++;
    }
}

/* 00000820-00000938       .text kamen_draw__FP8dk_class */
static void kamen_draw(dk_class* a_this) {
    J3DModel* model = a_this->mpModelKamen;

    MTXCopy(a_this->field_0x2B8->getModel()->getAnmMtx(24), *calc_mtx);
    cMtx_YrotM(*calc_mtx, 0x4000);
    cMtx_ZrotM(*calc_mtx, -0x4000);
    MtxTrans(REG0_F(0) * 0.01f,
             (REG0_F(1) * 0.01f) + 50.0f - 10.0f,
             (REG0_F(2) * 0.01f) + 140.0f - 15.0f,
             true);
    model->setBaseTRMtx(*calc_mtx);

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &a_this->current.pos, &a_this->tevStr);
    g_env_light.setLightTevColorType(model, &a_this->tevStr);
    mDoExt_modelUpdateDL(model);
}

/* 00000938-00000A18       .text daDk_Draw__FP8dk_class */
static BOOL daDk_Draw(dk_class* a_this) {
    if ((l_HIO.field_0x14 == 0 && a_this->field_0xAEE != 0)) {
        return TRUE;
    }

    if (l_HIO.field_0x14 != 0 || a_this->field_0xAC5 > 2) {
        J3DModel* model = a_this->field_0x2B8->getModel();
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &a_this->current.pos, &a_this->tevStr);
        g_env_light.setLightTevColorType(model, &a_this->tevStr);

        a_this->field_0x2B8->entryDL();

        kamen_draw(a_this);
        for (s32 i = 0; i < 4; i++) {
            tail_draw(a_this, &a_this->tails[i]);
        }
    }
    return TRUE;
}

/* 00000A18-00000A1C       .text move__FP8dk_class */
static void move(dk_class*) {
}

/* 00000A1C-00000A20       .text daDk_demoProc__FP8dk_class */
static void daDk_demoProc(dk_class*) {
}

/* 00000A20-00000A60       .text daDk_delete_Bdk__Fv */
static void daDk_delete_Bdk() {
    fopAc_ac_c* actor = fopAcM_searchFromName("Bdk", 0, 0);
    if (actor != NULL) {
        fopAcM_delete(actor);
    }
}

/* 00000A60-00000D08       .text daDk_Execute__FP8dk_class */
static BOOL daDk_Execute(dk_class* a_this) {
    a_this->field_0x2BC++;

    for (s32 i = 0; i < 5; i++) {
        if (a_this->field_0x2C0[i] != 0) {
            a_this->field_0x2C0[i]--;
        }
    }

    if (l_HIO.field_0x05 == 0) {
        move(a_this);

        a_this->eyePos = a_this->current.pos;
        a_this->eyePos.y += 100.0f;

        BOOL demo_set = dDemo_setDemoData(
            a_this,
            dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
            a_this->field_0x2B8,
            "Dk"
        );

        if (demo_set) {
            daDk_demoProc(a_this);
            a_this->field_0xAEE = 0;
            daDk_delete_Bdk();
        } else {
            a_this->field_0x2B8->play(&a_this->eyePos, 0, 0);
            a_this->field_0xAEE = 1;
        }

        switch (a_this->field_0xAC5) {
            case 0:
                if (dComIfGs_isEventBit(dSv_evtBit_c::UNK_310)) {
                    a_this->field_0xAC5 = 2;
                }
                break;
            case 2:
                if (dComIfGp_evmng_startCheck("zelda_fly")) {
                    a_this->field_0xAC5 = 3;
                }
                // fallthrough
            case 3:
                if (dComIfGs_isEventBit(dSv_evtBit_c::UNK_1)) {
                    a_this->field_0xAC5 = -1;
                }
                break;
            case 10:
            default:
                break;
        }
    }

    if (a_this->field_0x2B4 < 2) {
        a_this->field_0x900.CrrPos(*dComIfG_Bgsp());
    }

    a_this->scale.x = a_this->scale.y = a_this->scale.z = l_HIO.field_0x08;
    J3DModel* model = a_this->field_0x2B8->getModel();
    model->setBaseScale(a_this->scale);

    mDoMtx_stack_c::transS(a_this->current.pos);
    mDoMtx_stack_c::YrotM(a_this->current.angle.y);
    mDoMtx_stack_c::XrotM(a_this->current.angle.x);
    mDoMtx_stack_c::ZrotM(a_this->current.angle.z);
    model->setBaseTRMtx(mDoMtx_stack_c::get());

    a_this->field_0x2B8->calc();
    for (s32 i = 0; i < 4; i++) {
        tail_control(a_this, &a_this->tails[i]);
    }

    return TRUE;
}

/* 00000D08-00000D10       .text daDk_IsDelete__FP8dk_class */
static BOOL daDk_IsDelete(dk_class*) {
    return TRUE;
}

/* 00000D10-00000D7C       .text daDk_Delete__FP8dk_class */
static BOOL daDk_Delete(dk_class* a_this) {
    dComIfG_resDelete(&a_this->mPhs, "Dk");
    a_this->field_0xACC.end();
    mDoHIO_deleteChild(l_HIO.mNo);
    return TRUE;
}

/* 00000D7C-00000FFC       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_this) {
    dk_class* a_this = (dk_class*)i_this;

    mDoExt_McaMorf* morf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectIDRes("Dk", DK_BDL_DK),
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Dk", DK_BCK_FLY1),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11020002
    );
    a_this->field_0x2B8 = morf;

    if (a_this->field_0x2B8 == NULL || a_this->field_0x2B8->getModel() == NULL) {
        return FALSE;
    }

    for (u16 i = 0; i < a_this->field_0x2B8->getModel()->getModelData()->getJointNum(); i++) {
        if (i == 58 || i == 60 || i == 62 || i == 64) {
            a_this->field_0x2B8->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
        }
    }
    a_this->field_0x2B8->getModel()->setUserArea((u32) a_this);

    J3DModelData* modelData = (J3DModelData*) dComIfG_getObjectIDRes("Dk", DK_BDL_DK_KAMEN);
    a_this->mpModelKamen = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020002);
#if VERSION > VERSION_DEMO
    if (a_this->mpModelKamen == NULL) {
        return FALSE;
    }
#endif

    modelData = (J3DModelData*) dComIfG_getObjectIDRes("Dk", DK_BDL_DK_TAIL);
    JUT_ASSERT(DEMO_SELECT(817, 819), modelData != NULL);

    for (s32 i = 0; i < 4; i++) {
        for (s32 j = 0; j < 9; j++) {
            a_this->tails[i].models[j] = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020002);
#if VERSION > VERSION_DEMO
            if (a_this->tails[i].models[j] == NULL) {
                return FALSE;
            }
#endif
        }
    }

    return TRUE;
}

/* 00000FFC-000011EC       .text daDk_Create__FP10fopAc_ac_c */
static cPhs_State daDk_Create(fopAc_ac_c* i_this) {
    dk_class* a_this = (dk_class*)i_this;
    fopAcM_SetupActor(i_this, dk_class);

    cPhs_State res = dComIfG_resLoad(&a_this->mPhs, "Dk");
    if (res == cPhs_COMPLEATE_e) {
        a_this->field_0x2B4 = fopAcM_GetParam(a_this);
        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x1BD80)) {
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(i_this, a_this->field_0x2B8->getModel()->getBaseTRMtx());
        fopAcM_SetMin(i_this, -1000.0f, -1000.0f, -1000.0f);
        fopAcM_SetMax(i_this, 1000.0f, 1000.0f, 1000.0f);

        l_HIO.mNo = mDoHIO_createChild("大怪鳥", &l_HIO);

        if (a_this->field_0x2B4 < 2) {
            a_this->field_0x900.Set(
                fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this),
                a_this, 1, &a_this->field_0x8C0, fopAcM_GetSpeed_p(a_this), NULL, NULL);
        }
        a_this->field_0x8C0.SetWall(0.0f, 300.0f);
        if (a_this->field_0x2B4 == 1) {
            a_this->field_0xAC5 = 0;
        } else {
            a_this->field_0xAC5 = 10;
        }
        a_this->field_0xAC8 = 0;
    }

    return res;
}

static actor_method_class l_daDk_Method = {
    (process_method_func)daDk_Create,
    (process_method_func)daDk_Delete,
    (process_method_func)daDk_Execute,
    (process_method_func)daDk_IsDelete,
    (process_method_func)daDk_Draw,
};

actor_process_profile_definition g_profile_DK = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DK,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(dk_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DK,
    /* Actor SubMtd */ &l_daDk_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
