/**
 * d_a_obj_Vteng.cpp
 * Object - Puppet Ganon curtains (intro cutscene)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_Vteng.h"
#include "res/Object/Vteng.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

#if VERSION == VERSION_DEMO
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_hostIO.h"

class daObjVteng_HIO_c : public JORReflexible {
public:
    daObjVteng_HIO_c();
    virtual ~daObjVteng_HIO_c() {}
    void genMessage(JORMContext*) {}

    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
};

static daObjVteng_HIO_c l_HIO;

daObjVteng_HIO_c::daObjVteng_HIO_c() {
    mNo = -1;
    m05 = 0;
}
#endif

namespace {
    static const char l_arcname[] = "Vteng";
#if VERSION == VERSION_DEMO
    static const f32 l_setAnmStartFrame = 1.0f;
    static const f32 l_setAnmPlaySpeed = 0.0f;
    static const f32 l_setAnmEndFrame = -1.0f;
#endif
};

/* 00000078-00000120       .text init_mtx__12daObjVteng_cFv */
void daObjVteng_c::init_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::XYZrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::scaleM(scale);
    MTXCopy(mDoMtx_stack_c::get(), mtx);
}

/* 00000120-00000144       .text solidHeapCB__12daObjVteng_cFP10fopAc_ac_c */
BOOL daObjVteng_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjVteng_c*)i_this)->create_heap();
}

/* 00000144-000002C4       .text create_heap__12daObjVteng_cFv */
bool daObjVteng_c::create_heap() {
    bool ret = true;

    J3DModelData* pModelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcname, dRes_INDEX_VTENG_BDL_VTENG_e));
    J3DAnmTransform * pAnm = (J3DAnmTransform *)dComIfG_getObjectRes(l_arcname, dRes_INDEX_VTENG_BCK_VTENG_e);

    if (!pModelData || !pAnm) {
        JUT_ASSERT(DEMO_SELECT(0xb3, 0xb7), FALSE);
        ret = false;
    } else {
        mpMorf = new mDoExt_McaMorf(
            pModelData,
            NULL, NULL,
            pAnm,
            J3DFrameCtrl::EMode_NONE, DEMO_SELECT(l_setAnmStartFrame, 1.0f), 0x3B, -1, 0,
            NULL,
            0x00000000,
            0x11020203
        );
        if (!mpMorf) {
            ret = false;
        } else {
            J3DModel * model = mpMorf->getModel();
            mpModel = model;
            mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, dRes_INDEX_VTENG_DZB_VTENG_e), cBgW::MOVE_BG_e, &mtx);
            if (!mpBgW)
                ret = false;
        }
    }

    return ret;
}

/* 000002C4-00000324       .text jokai_demo__12daObjVteng_cFv */
bool daObjVteng_c::jokai_demo() {
    bool ret = false;

    if (dDemo_setDemoData(
        this,
        dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
        mpMorf, "Vteng"
    ) == TRUE)
        ret = true;

    return ret;
}

/* 00000324-000003F4       .text _create__12daObjVteng_cFv */
cPhs_State daObjVteng_c::_create() {
    fopAcM_ct(this, daObjVteng_c);

    cPhs_State ret = dComIfG_resLoad(&mPhs, l_arcname);

    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x72a0)) {
            fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
            init_mtx();
            if (dComIfG_Bgsp()->Regist(mpBgW, this)) {
                ret = cPhs_ERROR_e;
            }
        } else {
            ret = cPhs_ERROR_e;
        }
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("\x83\x4b\x83\x6d\x83\x93\x8f\xe9\x82\xcc\x93\x56\x8a\x57", &l_HIO);
    }
#endif

    return ret;
}

/* 000003F4-00000488       .text _delete__12daObjVteng_cFv */
bool daObjVteng_c::_delete() {
    dComIfG_resDelete(&mPhs, l_arcname);

#if VERSION == VERSION_DEMO
    if (mpBgW != NULL)
#else
    if (heap != NULL && mpBgW != NULL)
#endif
    {
        if (mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
        }

#if VERSION > VERSION_DEMO
        mpBgW = NULL;
#endif
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
#endif

    return true;
}

/* 00000488-00000510       .text _execute__12daObjVteng_cFv */
bool daObjVteng_c::_execute() {
#if VERSION == VERSION_DEMO
    if (mpBgW != NULL && mpBgW->ChkUsed())
        mpBgW->Move();

    if (!jokai_demo()) {
        if (l_HIO.m05 == 1) {
            l_HIO.m05 = 0;
            J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes(
                l_arcname, dRes_INDEX_VTENG_BCK_VTENG_e);
            mDoExt_McaMorf* morf = mpMorf;
            morf->setAnm(
                anm, 0,
                l_setAnmPlaySpeed,
                l_setAnmStartFrame,
                morf->getFrame(),
                l_setAnmEndFrame,
                NULL);
        }
        mpMorf->play(NULL, 0, 0);
    }
    
#else
    if (mpBgW != NULL && mpBgW->ChkUsed())
        mpBgW->Move();
    if (!jokai_demo())
        mpMorf->play(NULL, 0, 0);
#endif

    return true;
}

/* 00000510-00000578       .text _draw__12daObjVteng_cFv */
bool daObjVteng_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG3, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mpMorf->updateDL();
    fopAcM_SetModel(this, mpModel);
    return true;
}

/* 00000578-00000598       .text daObjVteng_Create__FP10fopAc_ac_c */
static cPhs_State daObjVteng_Create(fopAc_ac_c* i_this) {
    return ((daObjVteng_c*)i_this)->_create();
}

/* 00000598-000005BC       .text daObjVteng_Delete__FP12daObjVteng_c */
static BOOL daObjVteng_Delete(daObjVteng_c* i_this) {
    return i_this->_delete();
}

/* 000005BC-000005E0       .text daObjVteng_Execute__FP12daObjVteng_c */
static BOOL daObjVteng_Execute(daObjVteng_c* i_this) {
    return i_this->_execute();
}

/* 000005E0-00000604       .text daObjVteng_Draw__FP12daObjVteng_c */
static BOOL daObjVteng_Draw(daObjVteng_c* i_this) {
    return i_this->_draw();
}

/* 00000604-0000060C       .text daObjVteng_IsDelete__FP12daObjVteng_c */
static BOOL daObjVteng_IsDelete(daObjVteng_c* i_this) {
    return TRUE;
}

static actor_method_class l_daObjVteng_Method = {
    (process_method_func)daObjVteng_Create,
    (process_method_func)daObjVteng_Delete,
    (process_method_func)daObjVteng_Execute,
    (process_method_func)daObjVteng_IsDelete,
    (process_method_func)daObjVteng_Draw,
};

actor_process_profile_definition g_profile_Obj_Vteng = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Vteng_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjVteng_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Vteng_e,
    /* Actor SubMtd */ &l_daObjVteng_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
