/**
 * d_a_obj_gong.cpp
 * Object - Gong (Tetra's Ship)
 */

#include "d/actor/d_a_obj_gong.h"
#include "d/res/res_vdora.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_a_obj.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/d_drawlist.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

namespace daObjGong {
    namespace {
        struct Attr_c {
            /* 0x00 */ f32 spec;
            /* 0x04 */ f32 offsetY;
        };

        static const Attr_c L_attr = {
            0.75f, 125.0f,
        };

        inline const Attr_c & attr() { return L_attr; }
    }
}

const char daObjGong::Act_c::M_arcname[6] = "Vdora";

/* 00000078-0000009C       .text solidHeapCB__Q29daObjGong5Act_cFP10fopAc_ac_c */
BOOL daObjGong::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->create_heap();
}

/* 0000009C-0000028C       .text create_heap__Q29daObjGong5Act_cFv */
bool daObjGong::Act_c::create_heap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, VDORA_INDEX_BDL_VDORA));
    J3DAnmTransformKey* bck = static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes(M_arcname, VDORA_INDEX_BCK_05_VDORA_CUT02_HIT));
    JUT_ASSERT(0xbd, (modelData != NULL) && (bck != NULL));

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        bck,
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 0,
        NULL,
        0x00000000,
        0x11020203
    );
    J3DModel * model = mpMorf != NULL ? mpMorf->getModel() : NULL;

    bool ret = false;
    if (model != NULL) {
        J3DSkinDeform * deform = new J3DSkinDeform();
        if (deform != NULL) {
            s32 err = model->setSkinDeform(deform, 1);
            JUT_ASSERT(0xd7, (err == J3DErrType_Success) || (err == J3DErrType_OutOfMemory));
            if (err == J3DErrType_Success)
                ret = true;
        }
    }

    return model != NULL && ret;
}

/* 0000028C-00000374       .text _create__Q29daObjGong5Act_cFv */
cPhs_State daObjGong::Act_c::_create() {
    fopAcM_SetupActor(this, Act_c);

    cPhs_State ret = dComIfG_resLoad(&mPhs, M_arcname);

    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x0)) {
            fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
            init_mtx();
            fopAcM_setCullSizeBox(this, -100.0f, -1.0f, -50.0f, 100.0f, 230.0f, 50.0f);
            eyePos.y += attr().offsetY;
        } else {
            ret = cPhs_ERROR_e;
        }
    }

    return ret;
}

/* 00000374-000003A4       .text _delete__Q29daObjGong5Act_cFv */
bool daObjGong::Act_c::_delete() {
    dComIfG_resDelete(&mPhs, M_arcname);
    return true;
}

/* 000003A4-00000414       .text set_mtx__Q29daObjGong5Act_cFv */
void daObjGong::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000414-00000454       .text init_mtx__Q29daObjGong5Act_cFv */
void daObjGong::Act_c::init_mtx() {
    mpMorf->getModel()->setBaseScale(scale);
    set_mtx();
}

/* 00000454-000004A4       .text demo_move__Q29daObjGong5Act_cFv */
bool daObjGong::Act_c::demo_move() {
    return dDemo_setDemoData(
        this,
        dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
        mpMorf, "Vdora"
    );
}

/* 000004A4-000004F0       .text _execute__Q29daObjGong5Act_cFv */
bool daObjGong::Act_c::_execute() {
    demo_move();
    mpMorf->play(NULL, 0, 0);
    set_mtx();
    return true;
}

/* 000004F0-00000580       .text _draw__Q29daObjGong5Act_cFv */
bool daObjGong::Act_c::_draw() {
    J3DModel* model = (J3DModel*)mpMorf->getModel();
    J3DModelData* modelData = (J3DModelData*)model->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    dDlst_texSpecmapST(&eyePos, &tevStr, modelData, attr().spec);
    mpMorf->updateDL();
    return true;
}

namespace daObjGong {
    namespace {
        /* 00000580-000005A0       .text Mthd_Create__Q29daObjGong26@unnamed@d_a_obj_gong_cpp@FPv */
        cPhs_State Mthd_Create(void* i_this) {
            return ((Act_c*)i_this)->_create();
        }

        /* 000005A0-000005C4       .text Mthd_Delete__Q29daObjGong26@unnamed@d_a_obj_gong_cpp@FPv */
        BOOL Mthd_Delete(void* i_this) {
            return ((Act_c*)i_this)->_delete();
        }

        /* 000005C4-000005E8       .text Mthd_Execute__Q29daObjGong26@unnamed@d_a_obj_gong_cpp@FPv */
        BOOL Mthd_Execute(void* i_this) {
            return ((Act_c*)i_this)->_execute();
        }

        /* 000005E8-0000060C       .text Mthd_Draw__Q29daObjGong26@unnamed@d_a_obj_gong_cpp@FPv */
        BOOL Mthd_Draw(void* i_this) {
            return ((Act_c*)i_this)->_draw();
        }

        /* 0000060C-00000614       .text Mthd_IsDelete__Q29daObjGong26@unnamed@d_a_obj_gong_cpp@FPv */
        BOOL Mthd_IsDelete(void* i_this) {
            return TRUE;
        }

        static actor_method_class Mthd_Table = {
            (process_method_func)Mthd_Create,
            (process_method_func)Mthd_Delete,
            (process_method_func)Mthd_Execute,
            (process_method_func)Mthd_IsDelete,
            (process_method_func)Mthd_Draw,
        };
    }
}

actor_process_profile_definition g_profile_Obj_Gong = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Gong,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjGong::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Gong,
    /* Actor SubMtd */ &daObjGong::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
