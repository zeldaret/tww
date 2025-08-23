/**
 * d_a_machine.cpp
 * Enemy - Blade Trap (biting) (Wind Temple - giant fan room)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_machine.h"
#include "d/actor/d_a_player.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_hkikai1.h"

static dCcD_SrcSph l_sph_src_at = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
        /* SrcObjTg  Type    */ ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 150.0f,
    }},
};

static dCcD_SrcSph l_sph_src_col = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
        /* SrcObjTg  Type    */ ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 50.0f,
    }},
    
};

const char daMachine_c::m_arcname[8] = "Hkikai1";

const f32 daMachine_c::m_search_r = 300.0f;
const f32 daMachine_c::m_search_l = 800.0f;

/* 00000078-000000A8       .text _delete__11daMachine_cFv */
bool daMachine_c::_delete() {
    dComIfG_resDeleteDemo(&mPhs, m_arcname);
    return true;
}

/* 000000A8-000000C8       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daMachine_c*)i_this)->CreateHeap();
}

/* 000000C8-0000022C       .text CreateHeap__11daMachine_cFv */
BOOL daMachine_c::CreateHeap() {
    BOOL success;

    J3DModelData * modelData = (J3DModelData *)dComIfG_getObjectRes(m_arcname, HKIKAI1_BDL_HKIKAI1);
    JUT_ASSERT(DEMO_SELECT(340, 345), modelData != NULL);
    
    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);
    if(mpModel == NULL) {
        success = false;   
    } else{
        J3DAnmTransform * pbck = (J3DAnmTransform *)dComIfG_getObjectRes(m_arcname, HKIKAI1_BCK_HKIKAI1);
        JUT_ASSERT(DEMO_SELECT(356, 361), pbck != NULL)

        int initRet = field_0xc04.init(modelData,pbck, true, 0,1.0f,0,-1,false);
        if(initRet == NULL)
            success = false;
        else{
            field_0xc04.entry(mpModel->getModelData());
            success = true;
        }
    }
    
    return success;
}

/* 0000022C-000002A0       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if(calcTiming == J3DNodeCBCalcTiming_In){
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daMachine_c* i_this = (daMachine_c*)model->getUserArea();
        
        if(i_this) {
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            cMtx_copy(mDoMtx_stack_c::get(), i_this->field_0xc3c);
        }
    }

    return TRUE;
}

/* 000002A0-00000520       .text CreateInit__11daMachine_cFv */
void daMachine_c::CreateInit() {
    scale.setall(1.5f);
    
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());

    fopAcM_setCullSizeBox(this, -100.0f, -100.0f, -50.0f, 100.0f, 100.0f, 500.0f);
    mStts.Init(255, 255, this);
    mSph.Set(l_sph_src_at);
    mSph.SetStts(&mStts);
    
    for(int i = 0; i < 3; ++i) {
        field_0x404[i].Set(l_sph_src_col);
        field_0x404[i].SetStts(&mStts);
    }

    field_0x788.Set(l_sph_src_col);
    field_0x788.SetStts(&mStts);
    field_0xa78.SetWallR(50.0f);

    field_0x84b.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), 
                    this, 1,&field_0xa78,
                    fopAcM_GetSpeed_p(this));

    set_mtx();

    mpModel->setUserArea((u32)this);

    JUTNameTab* jointName = mpModel->getModelData()->getJointName();
    for(u16 i = 0; i < mpModel->getModelData()->getJointNum(); ++i) {
        if(strcmp("joint3", jointName->getName(i)) == 0) {
            mpModel->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
            break;
        }
    }

    mpModel->calc();
    field_0xc14 = fopAcM_GetParam(this);
    if (field_0xc14 != 0xff){
        field_0xc18 = dPath_GetRoomPath(field_0xc14, fopAcM_GetRoomNo(this));
        if(field_0xc18 != NULL){
            field_0xc16 = 1;
            field_0xc15 = 1;
            
            dPnt* pnt = &field_0xc18->m_points[field_0xc15];
            field_0xc1c = pnt->m_position;
            field_0xc28 = field_0xc1c;

            current.pos.x = field_0xc18->m_points[0].m_position.x;
            current.pos.y = field_0xc18->m_points[0].m_position.y;
            current.pos.z = field_0xc18->m_points[0].m_position.z;
            
        }else {
            field_0xc14 = 0xff;
        }
    }
}

/* 00000520-00000604       .text path_move__11daMachine_cFv */
void daMachine_c::path_move() {
    if (field_0xc14 != 0xFF){
        f32 temp2 = speedF;
        cLib_chasePos(&current.pos, field_0xc1c, temp2);
        
        f32 temp = (field_0xc1c - current.pos).abs();
        if(temp < 80.0f)
            set_next_pnt();
    }
}

/* 00000604-00000700       .text set_next_pnt__11daMachine_cFv */
void daMachine_c::set_next_pnt() {
    if (field_0xc14 == 0xFF) return;
    
    field_0xc15 += field_0xc16;

    if(dPath_ChkClose(field_0xc18)) {
        if (field_0xc15 > (s8)field_0xc18->m_num - 1) {
            field_0xc15 = 0;
        } else if (field_0xc15 < 0) {
            field_0xc15 = field_0xc18->m_num - 1;
        }
    } else {
        if(field_0xc15 > field_0xc18->m_num - 1 ) {
            field_0xc16 = -1;
            field_0xc15 = field_0xc18->m_num - 2;
        } else if (field_0xc15 < 0){
            field_0xc16 = 1;
            field_0xc15 = 1;
        }
    }

    field_0xc28 = field_0xc1c;
    dPnt* pnt = &field_0xc18->m_points[field_0xc15];
    field_0xc1c = pnt->m_position;
}

/* 00000700-00000734       .text search_wind_mill__11daMachine_cFv */
daWindMill_c* daMachine_c::search_wind_mill() {
    return (daWindMill_c*)fopAcM_SearchByName(PROC_WINDMILL);
}

/* 00000734-000007F8       .text set_speed__11daMachine_cFv */
void daMachine_c::set_speed() {
    f32 f31 = 5.0f;
    daWindMill_c* windmill = search_wind_mill();
    
    f32 f1;
    if(windmill != NULL) {
        s16 max_rot_speed = daWindMill_c::m_max_rot_speed[windmill->mType];;
        f1 = (f32)windmill->mAngle[1]/(f32)max_rot_speed;
    } else {
        f1 = 0.0f;
    }

    f32 old_speedF = speedF;
    cLib_addCalc(&old_speedF, f31 * f1, 0.1f, 1.0f, 0.5f);
    speedF = old_speedF;
}

/* 000007F8-00000898       .text _create__11daMachine_cFv */
cPhs_State daMachine_c::_create() {
    fopAcM_SetupActor(this, daMachine_c);

    cPhs_State ret = dComIfG_resLoad(&mPhs, m_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, &CheckCreateHeap, 0xb00)) {
            return cPhs_ERROR_e;
        }else {
            CreateInit();
        }
    }

    return ret;
}

/* 00000898-00000AA0       .text __ct__11daMachine_cFv */
daMachine_c::daMachine_c() {}

/* 00000F74-0000100C       .text set_mtx__11daMachine_cFv */
void daMachine_c::set_mtx() {
    csXyz xyz = current.angle;
    
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(xyz.x, xyz.y, xyz.z);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 0000100C-000010F8       .text _execute__11daMachine_cFv */
bool daMachine_c::_execute() {
    cXyz xyz;
    set_speed();
    xyz = cXyz::Zero - current.pos;
    current.angle.y = cM_atan2s(xyz.x,xyz.z);
    path_move();
    attack();
    set_body();
    set_at();
    set_mtx();

    f32 temp = speedF;
    if(temp != 0.0f) {
        fopAcM_seStart(this, JA_SE_OBJ_JAMA_MECHA_MOVE, 0);
    }

    return true;
}

/* 000010F8-0000124C       .text attack__11daMachine_cFv */
void daMachine_c::attack() {
    f32 f31 = 1.0f;
    daPy_py_c* player = daPy_getPlayerActorClass();

    if(player == NULL)
        return;

    set_cube();
    
    cXyz player_pos = player->current.pos;
    player_pos.y += 60.0f;

    field_0xbf0.SetC(player_pos);
    field_0xbf0.SetR(90.0f);

    switch (field_0xc78) {
    case 0: {
        cXyz unused;
        if(field_0xab8.Cross(&field_0xbf0, &unused)) {
            field_0xc78 = 1;
            return;
        }
        break;
    }
    case 1:
        fopAcM_seStart(this, JA_SE_OBJ_JAMA_MECHA_OUT,0);
        field_0xc04.setFrame(0.0f);
        field_0xc04.setPlaySpeed(f31);
        field_0xc78 += 1;
        // Fall through
    case 2:
        if(field_0xc04.play()) {
            field_0xc78 = NULL;
        }
        break;
    }
}

/* 0000124C-00001330       .text set_cube__11daMachine_cFv */
void daMachine_c::set_cube() {
    f32 f2 = 500.0f;
    f32 f31 = 200.0f;
    cXyz xyz1(0.0f, 0.0f, f31 + 150.0f);
    cXyz xyz2(0.0f, 0.0f, f2);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&xyz2, &xyz2);
    mDoMtx_stack_c::multVec(&xyz1, &xyz1);
    field_0xab8.GetStart() = xyz1;
    field_0xab8.GetEnd() = xyz2;
    field_0xab8.SetR(f31);
}

/* 00001330-0000144C       .text set_body__11daMachine_cFv */
void daMachine_c::set_body() {
    cXyz xyz[3];
    xyz[0].set(0.0f,0.0f,75.0f);
    xyz[1].set(0.0f,0.0f,225.0f);
    xyz[2].set(0.0f,0.0f,375.0f);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(current.angle);
    
    for(int i=0; i < 3; ++i) {
        mDoMtx_stack_c::multVec(&xyz[i], &xyz[i]);
        field_0x404[i].SetC(xyz[i]);
        dComIfG_Ccsp()->Set(&field_0x404[i]);
    }

    field_0x404[0].OnAtSPrmBit(cCcD_AtSPrm_Set_e);

    field_0x404[0].SetR(100.0f);
}

/* 0000144C-000014D4       .text set_at__11daMachine_cFv */
void daMachine_c::set_at() {
    f32 f1 = 5.0f;
    f32 f2 = 25.0f;
    f32 frame = field_0xc04.getFrameCtrl()->getFrame();
    if (f1 < frame && f2 > frame) {
        field_0xc6c.set(field_0xc3c[0][3],
                        field_0xc3c[1][3],
                        field_0xc3c[2][3]);

        mSph.SetC(field_0xc6c);
        dComIfG_Ccsp()->Set(&mSph);
    }
}

/* 000014D4-0000154C       .text _draw__11daMachine_cFv */
bool daMachine_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    field_0xc04.entry(mpModel->getModelData());
    mDoExt_modelUpdateDL(mpModel);
    return true;
}

/* 0000154C-0000156C       .text daMachine_Create__FPv */
static cPhs_State daMachine_Create(void* i_this) {
    return ((daMachine_c*)i_this)->_create();
}

/* 0000156C-00001590       .text daMachine_Delete__FPv */
static BOOL daMachine_Delete(void* i_this) {
    return ((daMachine_c*)i_this)->_delete();
}

/* 00001590-000015B4       .text daMachine_Draw__FPv */
static BOOL daMachine_Draw(void* i_this) {
    return ((daMachine_c*)i_this)->_draw();
}

/* 000015B4-000015D8       .text daMachine_Execute__FPv */
static BOOL daMachine_Execute(void* i_this) {
    return ((daMachine_c*)i_this)->_execute();
}

/* 000015D8-000015E0       .text daMachine_IsDelete__FPv */
static BOOL daMachine_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daMachineMethodTable = {
    (process_method_func)daMachine_Create,
    (process_method_func)daMachine_Delete,
    (process_method_func)daMachine_Execute,
    (process_method_func)daMachine_IsDelete,
    (process_method_func)daMachine_Draw,
};

actor_process_profile_definition g_profile_MACHINE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MACHINE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daMachine_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_MACHINE,
    /* Actor SubMtd */ &daMachineMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
