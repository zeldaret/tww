/**
 * d_a_obj_lpalm.cpp
 * Object - Palm tree
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_lpalm.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo_wether.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_oyashi.h"
#include "m_Do/m_Do_ext.h"

const char daObjLpalm_c::M_arcname[7] = "Oyashi";
daObjLpalm_c::Attr_c const daObjLpalm_c::M_attr = {0, 0};

/* 00000078-00000098       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daObjLpalm_c*)i_this)->CreateHeap();
}

/* 00000098-00000164       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* joint, int calcTiming) {
    J3DModel* model = j3dSys.getModel();
    s32 jntNo = ((J3DJoint*)joint)->getJntNo();
    daObjLpalm_c* i_this = (daObjLpalm_c*)model->getUserArea();
    if (calcTiming == J3DNodeCBCalcTiming_In && (jntNo == 2 || jntNo == 3)) {
        mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
        mDoMtx_stack_c::ZrotM(-0x4000);
        mDoMtx_stack_c::quatM(&i_this->mBaseQuat);
        if (jntNo == 2)
            mDoMtx_stack_c::quatM(&i_this->mAnmMtxQuat[0]);
        else
            mDoMtx_stack_c::quatM(&i_this->mAnmMtxQuat[1]);
        mDoMtx_stack_c::ZrotM(0x4000);
        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
    }

    return TRUE;
}

/* 00000164-00000268       .text CreateHeap__12daObjLpalm_cFv */
BOOL daObjLpalm_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname, OYASHI_BDL_OYASHI);
    for (u16 i = 0; i < modelData->getJointNum(); i++)
        modelData->getJointNodePointer(i)->setCallBack(nodeCallBack);
    if (modelData == NULL)
        return false;

    mModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);
    if (mModel == NULL)
        return false;

    mModel->setUserArea((u32)this);
    mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(M_arcname, OYASHI_DZB_OYASHI), dBgW::MOVE_BG_e, &mModel->getBaseTRMtx());
    if (mpBgW == NULL)
        return false;

    return true;
}

/* 00000268-00000404       .text CreateInit__12daObjLpalm_cFv */
void daObjLpalm_c::CreateInit() {
    Quaternion q = {0.0f, 0.0f, 0.0f, 1.0f};

    mBaseQuat = mBaseQuatTarget = q;
    mAnmMtxQuat[0] = mAnmMtxQuat[1] = q;
    mAnimDir[0] = 0;
    mAnimDir[1] = 0;
    mAnimWave[0] = 0;
    mAnimWave[1] = cM_rndFX(32768.0f);
    fopAcM_SetMtx(this, mModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -350.0f, -50.0f, -350.0f, 350.0f, 1300.0f, 350.0f);
    fopAcM_setCullSizeFar(this, 2.37f);
    dComIfG_Bgsp()->Regist(mpBgW, this);
    mModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

cPhs_State daObjLpalm_c::_create() {
#if VERSION == VERSION_DEMO
    cPhs_State ret = dComIfG_resLoad(&mPhs, M_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        fopAcM_SetupActor(this, daObjLpalm_c);
#else
    fopAcM_SetupActor(this, daObjLpalm_c);
    cPhs_State ret = dComIfG_resLoad(&mPhs, M_arcname);
    if (ret == cPhs_COMPLEATE_e) {
#endif
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0xf00) == 0) {
            ret = cPhs_ERROR_e;
        } else {
            CreateInit();
        }
    }

    return ret;
}

bool daObjLpalm_c::_delete() {
#if VERSION > VERSION_DEMO
    if (heap != NULL && mpBgW->ChkUsed())
#endif
    {
        dComIfG_Bgsp()->Release(mpBgW);
    }

    dComIfG_resDeleteDemo(&mPhs, M_arcname);
    return true;
}

/* 00000404-000004A4       .text daObjLpalmCreate__FPv */
static cPhs_State daObjLpalmCreate(void* i_this) {
    return ((daObjLpalm_c*)i_this)->_create();
}

/* 000004A4-00000528       .text daObjLpalmDelete__FPv */
static BOOL daObjLpalmDelete(void* i_this) {
    return ((daObjLpalm_c*)i_this)->_delete();
}

/* 00000528-0000054C       .text daObjLpalmExecute__FPv */
static BOOL daObjLpalmExecute(void* i_this) {
    return ((daObjLpalm_c*)i_this)->_execute();
}

/* 0000054C-000008C4       .text _execute__12daObjLpalm_cFv */
bool daObjLpalm_c::_execute() {
    /* Nonmatching */
    if (attr().flag0)
        return true;

    Quaternion q;
    cXyz up(0.0f, 1.0f, 0.0f);
    cXyz windDir;

    cMtx_YrotS(*calc_mtx, -current.angle.y);
    MtxPosition(dKyw_get_wind_vec(), &windDir);
    f32 windPow = dKyw_get_wind_pow();
    s16 angle = windPow * 0x600;
    cXyz dir = up.outprod(windDir);
    f32 mag = dir.abs();
    if (mag < 8e-09) {
        mBaseQuatTarget.x = 0.0f;
        mBaseQuatTarget.y = 0.0f;
        mBaseQuatTarget.z = 0.0f;
        mBaseQuatTarget.w = 1.0f;
    } else {
        f32 sin = cM_ssin(angle);
        dir = dir.normZP();
        mBaseQuatTarget.x = sin * dir.x;
        mBaseQuatTarget.y = sin * dir.y;
        mBaseQuatTarget.z = sin * dir.z;
        mBaseQuatTarget.w = cM_scos(angle);
    }

    mDoMtx_quatSlerp(&mBaseQuat, &mBaseQuatTarget, &q, 0.25f);
    mBaseQuat = q;

    for (s32 i = 0; i < 2; i++) {
        s16 target = windPow * 0x180;
        if (target > 0x100)
            target = 0x100;
        cLib_addCalcAngleS2(&mAnimDir[i], target, 4, 0x20);
        s32 add = (windPow * 0x800) + cM_rndFX(128.0f);
        mAnimWave[i] += add;
        f32 w = cM_ssin(mAnimDir[i]);
        mAnmMtxQuat[i].x = cM_ssin(mAnimWave[i]) * w;
        mAnmMtxQuat[i].y = 0.0f;
        mAnmMtxQuat[i].z = cM_ssin(mAnimWave[i]) * w;
        mAnmMtxQuat[i].w = cM_scos(mAnimDir[i]);
    }

    mpBgW->Move();
    return false;
}

bool daObjLpalm_c::_draw() {
    if (attr().flag1)
        return true;

    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel, &tevStr);
    mDoExt_modelUpdateDL(mModel);
    return true;
}

/* 000008C4-00000950       .text daObjLpalmDraw__FPv */
static BOOL daObjLpalmDraw(void* i_this) {
    return ((daObjLpalm_c*)i_this)->_draw();
}

/* 00000950-00000958       .text daObjLpalmIsDelete__FPv */
static BOOL daObjLpalmIsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class daObjLpalmMethodTable = {
    (process_method_func)daObjLpalmCreate,
    (process_method_func)daObjLpalmDelete,
    (process_method_func)daObjLpalmExecute,
    (process_method_func)daObjLpalmIsDelete,
    (process_method_func)daObjLpalmDraw,
};

actor_process_profile_definition g_profile_Obj_Lpalm = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Lpalm,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjLpalm_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Lpalm,
    /* Actor SubMtd */ &daObjLpalmMethodTable,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
