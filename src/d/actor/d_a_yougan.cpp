/**
 * d_a_yougan.cpp
 * Object - Unused - Lava bubbles
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_yougan.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_yougan.h"
#include "m_Do/m_Do_lib.h"

class daYOUGAN_HIO_c : public JORReflexible {
public:
    daYOUGAN_HIO_c();
    virtual ~daYOUGAN_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ u8 field_0x20;
    /* 0x21 */ s8 field_0x21;
    /* 0x22 */ s8 field_0x22;
};  // Size: 0x23

static daYOUGAN_HIO_c l_HIO;
static s32 yg_awa_num = 16;
char daYougan_c::m_arcname[] = "Yougan";

/* 000000EC-00000158       .text __ct__14daYOUGAN_HIO_cFv */
daYOUGAN_HIO_c::daYOUGAN_HIO_c() {
    mNo = -1;
    field_0x22 = 0;
    field_0x06 = 16;
    field_0x08 = 1250.0f;
    field_0x0C = 40.0f;
    field_0x10 = 60.0f;
    field_0x14 = 0.2f;
    field_0x18 = 0.5f;
    field_0x1C = 100.0f;
    field_0x20 = 1;
    field_0x21 = 1;
}

/* 00000158-00000178       .text daYougan_Draw__FP10daYougan_c */
static BOOL daYougan_Draw(daYougan_c* i_this) {
    return ((daYougan_c*)i_this)->_daYougan_draw();
}

/* 00000178-000002A8       .text _daYougan_draw__10daYougan_cFv */
BOOL daYougan_c::_daYougan_draw() {
    yg_awa_num = l_HIO.field_0x06;
    for (s32 i = 0; i < yg_awa_num; i++) {
        if (l_HIO.field_0x20) {
            if (!mDoLib_clipper::clip(j3dSys.getViewMtx(), field_0x298[i].field_0x2C, l_HIO.field_0x1C)) {
                J3DModelData* model_data = field_0x298[i].field_0x04->getModelData();
                f32 frame = field_0x298[i].field_0x18.getFrame();
                field_0x298[i].field_0x18.entry(model_data, frame);

                model_data = field_0x298[i].field_0x04->getModelData();
                frame = field_0x298[i].field_0x18.getFrame();
                field_0x298[i].field_0x08.entry(model_data, field_0x298[i].field_0x08.getFrame());
                mDoExt_modelUpdateDL(field_0x298[i].field_0x04);
            }
        } else {
            J3DModelData* model_data = field_0x298[i].field_0x04->getModelData();
            f32 frame = field_0x298[i].field_0x18.getFrame();
            field_0x298[i].field_0x18.entry(model_data, frame);

            model_data = field_0x298[i].field_0x04->getModelData();
            frame = field_0x298[i].field_0x18.getFrame();
            field_0x298[i].field_0x08.entry(model_data, field_0x298[i].field_0x08.getFrame());
            mDoExt_modelUpdateDL(field_0x298[i].field_0x04);

        }
    }
    return TRUE;
}

/* 000002A8-000002C8       .text daYougan_Execute__FP10daYougan_c */
static BOOL daYougan_Execute(daYougan_c* i_this) {
    return ((daYougan_c*)i_this)->_daYougan_execute();
}

/* 000002C8-00000554       .text _daYougan_execute__10daYougan_cFv */
BOOL daYougan_c::_daYougan_execute() {
    yg_awa_num = l_HIO.field_0x06;

    for (s32 i = 0; i < yg_awa_num; i++) {
        switch (field_0x298[i].field_0x00) {
            case 0: {
                field_0x298[i].field_0x38 = cXyz::Zero;
                field_0x298[i].field_0x48 = l_HIO.field_0x0C + cM_rndF(l_HIO.field_0x10);
                field_0x298[i].field_0x44 = l_HIO.field_0x14 + cM_rndF(l_HIO.field_0x18);
                f32 fVar4 = l_HIO.field_0x08 * scale.x;
                f32 fVar5 = cM_rndFX(fVar4);
                fVar4 = cM_rndFX(fVar4 - std::fabsf(fVar5));

                field_0x298[i].field_0x2C.x = current.pos.x + fVar5;
                field_0x298[i].field_0x2C.y = current.pos.y - 17.591f;
                field_0x298[i].field_0x2C.z = current.pos.z + fVar4;
                field_0x298[i].field_0x00 = 1;
                break;
            }
            case 1:
                if (field_0x298[i].field_0x38.x <= field_0x298[i].field_0x44) {
                    field_0x298[i].field_0x38.x += field_0x298[i].field_0x44 / field_0x298[i].field_0x48;
                    field_0x298[i].field_0x38.y = field_0x298[i].field_0x38.x;
                    field_0x298[i].field_0x38.z = field_0x298[i].field_0x38.x;
                } else {
                    field_0x298[i].field_0x00 = 2;
                }
                break;
            case 2:
                field_0x298[i].field_0x08.setPlaySpeed(1.0f);
                field_0x298[i].field_0x18.setPlaySpeed(1.0f);

                if (field_0x298[i].field_0x08.play() || field_0x298[i].field_0x18.play()) {

                    field_0x298[i].field_0x08.setFrame(0.0f);
                    field_0x298[i].field_0x18.setFrame(0.0f);

                    field_0x298[i].field_0x38.set(0.0f, 0.0f, 0.0f);
                    field_0x298[i].field_0x00 = 0;
                }
                break;
            default:
                field_0x298[i].field_0x00 = 0;
                break;
        }
    }
    yg_awa_num = l_HIO.field_0x06;
    for (s32 i = 0; i < yg_awa_num; i++) {
        J3DModel* p_model = field_0x298[i].field_0x04;
        p_model->setBaseScale(field_0x298[i].field_0x38);
        mDoMtx_stack_c::transS(field_0x298[i].field_0x2C);
        p_model->setBaseTRMtx(mDoMtx_stack_c::get());
    }
    return TRUE;
}

/* 00000554-00000574       .text daYougan_IsDelete__FP10daYougan_c */
static BOOL daYougan_IsDelete(daYougan_c* i_this) {
    return ((daYougan_c*)i_this)->_daYougan_isdelete();
}

/* 00000574-0000057C       .text _daYougan_isdelete__10daYougan_cFv */
BOOL daYougan_c::_daYougan_isdelete() {
    return TRUE;
}

/* 0000057C-0000059C       .text daYougan_Delete__FP10daYougan_c */
static BOOL daYougan_Delete(daYougan_c* i_this) {
    return ((daYougan_c*)i_this)->_daYougan_delete();
}

/* 0000059C-00000600       .text _daYougan_delete__10daYougan_cFv */
BOOL daYougan_c::_daYougan_delete() {
    dComIfG_resDeleteDemo(&mPhase, m_arcname);
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    return TRUE;
}

/* 00000600-00000884       .text useHeapInit__10daYougan_cFv */
BOOL daYougan_c::useHeapInit() {
    J3DModelData* modelData = (J3DModelData*) dComIfG_getObjectRes(m_arcname, YOUGAN_BMD_YOUGAN_AWA);
    JUT_ASSERT(DEMO_SELECT(462, 464), modelData != NULL);
    J3DAnmTransform* anmKey = (J3DAnmTransform*) dComIfG_getObjectRes(m_arcname, YOUGAN_BCK_YOUGAN_AWA);
    JUT_ASSERT(DEMO_SELECT(467,469), anmKey != NULL);
    J3DAnmTextureSRTKey* srtKey = (J3DAnmTextureSRTKey*) dComIfG_getObjectRes(m_arcname, YOUGAN_BTK_YOUGAN_AWA);
    JUT_ASSERT(DEMO_SELECT(472, 474), srtKey != NULL);

    yg_awa_num = l_HIO.field_0x06;
    for(s32 i = 0; i < yg_awa_num; i++) {
        field_0x298[i].field_0x00 = 0;
        J3DModel* p_model = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        field_0x298[i].field_0x04 = p_model;
#if VERSION != VERSION_DEMO
        if(field_0x298[i].field_0x04 == NULL) {
            return FALSE;
        }
#endif
    }
    for(s32 i = 0; i < yg_awa_num; i++) {
        if(!field_0x298[i].field_0x08.init(modelData, anmKey, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false)) {
            return FALSE;
        }
    }
    for(s32 i = 0; i < yg_awa_num; i++) {
        if(!field_0x298[i].field_0x18.init(modelData, srtKey, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE)) {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00000884-000008A4       .text daYougan_solidHeapCB__FP10fopAc_ac_c */
static BOOL daYougan_solidHeapCB(fopAc_ac_c* i_this) {
    return ((daYougan_c*)i_this)->useHeapInit();

}

/* 000008A4-000008C4       .text daYougan_Create__FP10fopAc_ac_c */
static cPhs_State daYougan_Create(fopAc_ac_c* i_this) {
    return ((daYougan_c*)i_this)->_daYougan_create();
}

/* 000008C4-000009C8       .text _daYougan_create__10daYougan_cFv */
cPhs_State daYougan_c::_daYougan_create() {
    fopAcM_ct(this, daYougan_c);

    cPhs_State state = dComIfG_resLoad(&this->mPhase, m_arcname);

    if(state == cPhs_COMPLEATE_e) {
        if(fopAcM_entrySolidHeap(this, daYougan_solidHeapCB, 0x16000)) {
            fopAcM_SetMtx(this,field_0x298[0].field_0x04->getBaseTRMtx());
        } else {
            state = cPhs_ERROR_e;
        }
        if (l_HIO.mNo < 0) {
            l_HIO.mNo = mDoHIO_createChild("溶岩の気泡", &l_HIO);
        }
    }
    return state;
}

static actor_method_class l_daYougan_Method = {
    (process_method_func)daYougan_Create,
    (process_method_func)daYougan_Delete,
    (process_method_func)daYougan_Execute,
    (process_method_func)daYougan_IsDelete,
    (process_method_func)daYougan_Draw,
};

actor_process_profile_definition g_profile_YOUGAN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_YOUGAN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daYougan_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_YOUGAN,
    /* Actor SubMtd */ &l_daYougan_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
