/**
 * d_a_obj_doguu.cpp
 * Object - Goddess Statues (Triangle Islands)
 */

#include "d/actor/d_a_obj_doguu.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/d_item.h"
#include "d/res/res_doguu.h"
#include "d/actor/d_a_player.h"
#include "f_op/f_op_camera.h"
#include "d/d_kankyo_rain.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ cCcD_TgSPrm_IsPlayer_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cCcD_SrcCylAttr
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 200.0f,
        /* Height */ 200.0f,
    }
};

const struct {
    int bmt_vgsm[3];
    int bmt_vgsb[3];
    int bck[3];
    int brk[3];
    int bdl_vgsh[3];
    int bdl_vgsp[3];
} daObjDoguu_idx_table = {
    DOGUU_BMT_VGSMD, DOGUU_BMT_VGSMF, DOGUU_BMT_VGSMN,
    DOGUU_BMT_VGSBD, DOGUU_BMT_VGSBF, DOGUU_BMT_VGSBN,
    DOGUU_BCK_VGSHD, DOGUU_BCK_VGSHF, DOGUU_BCK_VGSHN,
    DOGUU_BRK_VGSMD, DOGUU_BRK_VGSMF, DOGUU_BRK_VGSMN,
    DOGUU_BDL_VGSHD, DOGUU_BDL_VGSHF, DOGUU_BDL_VGSHN,
    DOGUU_BDL_VGSPD, DOGUU_BDL_VGSPF, DOGUU_BDL_VGSPN
};

namespace {
    struct Attr_c {
        /* 0x00 */ float mScale;
        /* 0x04 */ float mOffsetEyePos;
    };

    static const Attr_c L_attr = {
        0.5f, 125.0f,
    };

    inline const Attr_c& attr() { return L_attr; }
}


/* 00000078-00000168       .text setPointLight__12daObjDoguu_cFv */
void daObjDoguu_c::setPointLight() {
    static const s16 light_color[3][3] = {
        {0x00C8, 0x0032, 0x0032},
        {0x0032, 0x00C8, 0x0032},
        {0x0032, 0x0032, 0x00C8},
    };
    cLib_addCalc2(&field_0x8FC, cM_rndF(0.1f)+ 1.0f,0.5f,0.05f);
    mLightInfluence.mPos = mPos;
    mLightInfluence.mColor.r = light_color[field_0x894][0];
    mLightInfluence.mColor.g = light_color[field_0x894][1];
    mLightInfluence.mColor.b = light_color[field_0x894][2];
    mLightInfluence.mPower = (s16)(field_0x8FC * 300.0f);
    mLightInfluence.mFluctuation = 100.0f;
}

/* 00000168-00000188       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daObjDoguu_c*>(i_this)->CreateHeap();
}

/* 00000188-000007D0       .text CreateHeap__12daObjDoguu_cFv */
BOOL daObjDoguu_c::CreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Doguu", DOGUU_BDL_VGSMA));
    JUT_ASSERT(0x160, modelData != NULL);
    
    J3DMaterialTable* bmt = static_cast<J3DMaterialTable*>(dComIfG_getObjectRes("Doguu", daObjDoguu_idx_table.bmt_vgsm[field_0x894]));
    modelData->setMaterialTable(bmt, J3DMatCopyFlag_All);
    field_0x6CC = mDoExt_J3DModel__create(modelData, 0x80000, 0x15220202);

    if (field_0x6CC == NULL) {
        return FALSE;
    }

    J3DAnmTevRegKey* brk_doguu = static_cast<J3DAnmTevRegKey *>(dComIfG_getObjectRes("Doguu", daObjDoguu_idx_table.brk[field_0x894]));
    JUT_ASSERT(0x170, brk_doguu != NULL);
    
    if (mBrk.init(modelData, brk_doguu, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0) == 0) {
        return FALSE;
    }
    
    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Doguu", daObjDoguu_idx_table.bdl_vgsh[field_0x894]));
    JUT_ASSERT(0x177, modelData != NULL);
    field_0x6D0 =  mDoExt_J3DModel__create(modelData, 0,0x11020203);

    if (field_0x6D0 == NULL) {
        return FALSE;
    }

    J3DAnmTransform* bck_head = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Doguu", daObjDoguu_idx_table.bck[field_0x894]));
    JUT_ASSERT(0x17D, bck_head != NULL);
    
    if (mBckHead.init(modelData, bck_head, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false) == 0) {
        return FALSE;
    }

    J3DSkinDeform* deform = new J3DSkinDeform();

    if (deform){
        field_0x6D0->setSkinDeform(deform, 1);
    } else {
        return FALSE;
    }
    
    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Doguu", DOGUU_BDL_VGSBA));
    JUT_ASSERT(0x18f, modelData != NULL);
    bmt =  static_cast<J3DMaterialTable *>(dComIfG_getObjectRes("Doguu", daObjDoguu_idx_table.bmt_vgsb[field_0x894]));
    modelData->setMaterialTable(bmt, J3DMatCopyFlag_All);
    field_0x6D4 = mDoExt_J3DModel__create(modelData, 0x80000,0x15220202);
    
    if (field_0x6D4 == NULL) {
        return FALSE;
    }
    
    JUTNameTab* nameTable = field_0x6D4->getModelData()->getJointName();
    
    for (u16 i = 0; i < field_0x6D4->getModelData()->getJointNum(); i++) {
        const char* name = nameTable->getName(i);
        if (strcmp("head1", name) == 0) {
            mHead1JntNo = i;
            break;
        }
    }
    
    J3DAnmTransform* bck_body = static_cast<J3DAnmTransform *>(dComIfG_getObjectRes("Doguu", DOGUU_BCK_VGSBA));
    JUT_ASSERT(0x1AB, bck_body != NULL);
    
    if (mBckBody.init(modelData, bck_body, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false) == 0) {
        return FALSE;
    }

    deform = new J3DSkinDeform();

    if(deform) {
        field_0x6D4->setSkinDeform(deform, 1);
    } else {
        return FALSE;
    }

    modelData = (J3DModelData*)(dComIfG_getObjectRes("Doguu", daObjDoguu_idx_table.bdl_vgsp[field_0x894]));
    JUT_ASSERT(0x1bd, modelData != NULL);
    field_0x6D8 = mDoExt_J3DModel__create(modelData, 0,0x11020203);

    if (field_0x6D8 == NULL) {
        return FALSE;
    }

    J3DAnmTransform* bck_crystal = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Doguu", DOGUU_BCK_VGSPA));
    JUT_ASSERT(0x1c3, bck_crystal != NULL);
    
    if(mBckCrystal.init(modelData, bck_crystal, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false) == 0){
        return FALSE;
    }

    field_0x89C = 1;
    return TRUE;
}

/* 000007D0-00000B80       .text CreateInit__12daObjDoguu_cFv */
void daObjDoguu_c::CreateInit() {
    fopAcM_SetMtx(this, field_0x6CC->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -600.0f, -0.0f, -600.0f, 600.0f, 400.0f, 600.0f);
    fopAcM_setCullSizeFar(this, 1.0f);

    if (field_0x894 == 0){
        mItemNo = dItem_PEARL_DIN_e;
    } else if(field_0x894 == 1) {
        mItemNo = dItem_PEARL_FARORE_e;
    } else{
        mItemNo = dItem_PEARL_NAYRU_e;
    }

    mStts.Init(0xff, 0xff, this);
    mCyl.Set(l_cyl_src);
    if(!checkItemGet(mItemNo, TRUE)){ 
        mCyl.SetR(50.f);
    }
    mCyl.SetStts(&mStts);
    dKy_plight_set(&mLightInfluence);
    if (subtype >= 1) {
        mBckHead.setFrame(mBckHead.getStartFrame());
        mBckBody.setFrame(mBckBody.getStartFrame());
        mBckCrystal.setFrame(mBckCrystal.getStartFrame());

        field_0x8A0 = true;
        field_0x8A1 = false;
        field_0x8A2 = true;
        field_0x8AC = 14;
    } else if (dComIfGs_isEventBit(0x1480) && dComIfGs_isEventBit(0x1440) && dComIfGs_isEventBit(0x1410)) {

        mBckHead.setFrame(mBckHead.getEndFrame());
        mBckBody.setFrame(mBckBody.getEndFrame());
        mBckCrystal.setFrame(mBckCrystal.getEndFrame());
        field_0x8A0 = true;
        field_0x8A1 = true;
        field_0x8A2 = false;
        field_0x8AC = 14;
        
    } else {
        field_0x8A1 = false;
        if (
            (field_0x894 == 0 && dComIfGs_isEventBit(0x1480)) ||
            (field_0x894 == 1 && dComIfGs_isEventBit(0x1440)) ||
            (field_0x894 == 2 && dComIfGs_isEventBit(0x1410))
        ) {
            field_0x8A2 = true;
            field_0x8A0 = true;
            field_0x8AC = 10;                   
        } else {
            field_0x8A2 = false;
            field_0x8A0 = false;
            field_0x8AC = 0;
        }
    }
    
    eyePos.y += attr().mOffsetEyePos;
    set_mtx();

    mDoguuDemo1EventIdx = dComIfGp_evmng_getEventIdx("DOGUU_DEMO1", 0xff);
    mDoguuDemo2EventIdx = dComIfGp_evmng_getEventIdx("DOGUU_DEMO2", 0xff);
    mDoguuDemo3EventIdx = dComIfGp_evmng_getEventIdx("DOGUU_DEMO3", 0xff);
    mMegamiDemoEventIdx = dComIfGp_evmng_getEventIdx("MEGAMI_DEMO", 0xff);
    field_0x8FC = 1.0f;
    if (field_0x8A0 == true) {
        field_0x8A3 = true;
    } else {
        field_0x8A3 = false;
    }
    mAllColRatio = 1.0f;
}

/* 00000B80-00000CEC       .text set_mtx__12daObjDoguu_cFv */
void daObjDoguu_c::set_mtx() {
    field_0x6CC->setBaseScale(scale);
    field_0x6D4->setBaseScale(scale);
    field_0x6D8->setBaseScale(scale);
    field_0x6D0->setBaseScale(scale);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    field_0x6CC->setBaseTRMtx(mDoMtx_stack_c::get());

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    field_0x6D4->setBaseTRMtx(mDoMtx_stack_c::get());

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    field_0x6D8->setBaseTRMtx(mDoMtx_stack_c::get());

    field_0x6D0->setBaseTRMtx(field_0x6D4->getAnmMtx(mHead1JntNo));
}

/* 00000CEC-00000D80       .text next_msgStatus__12daObjDoguu_cFPUl */
u16 daObjDoguu_c::next_msgStatus(u32* pMsgNo) {
    u16 message_status = fopMsgStts_MSG_CONTINUES_e;
    switch (*pMsgNo) {
        case 3822:
        case 3823:
        case 3824:
            if (getFinishEventCount() == 0) {
                *pMsgNo = 3825;
            } else if (getFinishEventCount() == 1) {
                *pMsgNo = 3826;
            } else {
                message_status = fopMsgStts_MSG_ENDS_e;
            }
            break;

        default:
            message_status = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return message_status;
}

/* 00000D80-00000DBC       .text getMsg__12daObjDoguu_cFv */
u32 daObjDoguu_c::getMsg() {
    if (mActIdx == 4) {
        return 3821;
    } else if (field_0x894 == 0) {
        return 3822;
    } else if (field_0x894 == 1){
        return 3823;
    } else {
        return 3824;
    }
}

/* 00000DBC-00000E98       .text setGoal__12daObjDoguu_cFi */
void daObjDoguu_c::setGoal(int i_staffIdx) {
    cXyz pos = *dComIfGp_evmng_getMyXyzP(i_staffIdx, "Posion");

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::transM(pos.x, pos.y,  pos.z);

    mDoMtx_stack_c::multVecZero(&pos);
    field_0x8B4 = pos;
    dComIfGp_evmng_setGoal(&field_0x8B4);
}

/* 00000E98-00000F18       .text setPlayerAngle__12daObjDoguu_cFi */
void daObjDoguu_c::setPlayerAngle(int i_staffIdx) {
    u32 angle = *dComIfGp_evmng_getMyIntegerP(i_staffIdx, "angle");
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    player->setPlayerPosAndAngle(&player->current.pos, current.angle.y + (s16)angle);
}

/* 00000F18-00000FB8       .text setQuake__12daObjDoguu_cFi */
void daObjDoguu_c::setQuake(int i_staffIdx) {
    u32 pattern = 0x0010FFEE;
    dComIfGp_getVibration().StartQuake((u8*)&pattern, 0, 63, cXyz(0.0f, 1.0f, 0.0f));
    mTimer = *dComIfGp_evmng_getMyIntegerP(i_staffIdx, "Timer");

}

/* 00000FB8-0000100C       .text setJDemo__12daObjDoguu_cFi */
void daObjDoguu_c::setJDemo(int) {
    dComIfGp_setNextStage("ADMumi", (short)field_0x894, 0, 8);
}

/* 0000100C-000015A8       .text privateCut__12daObjDoguu_cFv */
void daObjDoguu_c::privateCut() {
    static char* cut_name_tbl[] = {
        "SETGOAL",
        "SETBALL",
        "SETANGLE",
        "EYEFLASH",
        "MESSAGE_KOKOE",
        "MESSAGE_OITA",
        "QUAKE",
        "JDEMO",
        "SETLIGHT",
    };

    int staffIdx = dComIfGp_evmng_getMyStaffId("Doguu");
    if (staffIdx != -1) {
        mActIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);
        if(mActIdx == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
        } else{
            bool doCutEnd = false;
            if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
                switch (mActIdx) {
                case 0:
                    setGoal(staffIdx);
                    break;
                case 1:
                    field_0x8A0 = true;
                    fopAcM_seStartCurrent(this, JA_SE_LK_PUT_PEARL, 0);
                    break;
                case 2:
                    setPlayerAngle(staffIdx);
                    break;
                case 3:
                    field_0x8A2 = true;
                    break;
                case 5:
                    mDoAud_subBgmStart(JA_BGM_GET_PEARL); 
                    break;
                case 6:
                    setQuake(staffIdx);
                    break;
                case 7:
                    setJDemo(staffIdx);
                    break;
                case 8:
                    field_0x8C4 = 0;
                    break;
                }
            }
            switch (mActIdx) {
            case 0:
                doCutEnd = true;
                break;
            case 1:
                doCutEnd = true;
                break;
            case 2:
                doCutEnd = true;
                break;
            case 3:
                doCutEnd = true;
                break;
            case 4:
                if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
                    doCutEnd = true;
                }
                break;
            case 5:
                if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
                    doCutEnd = true;
                }
                break;
            case 6:
                mTimer--;
                if (mTimer == 0) {
                    doCutEnd = true;
                    dComIfGp_getVibration().StopQuake(63);
                }
                break;
            case 7:
                doCutEnd = true;
                break;
            case 8: {
                int iVar2 = field_0x8C4;
                if(iVar2 >= 200){
                    mAllColRatio = 1.0f;
                    doCutEnd = true;
                } else {
                    field_0x8C4++;
                }
                iVar2 = field_0x8C4;
                if (iVar2 < 21) {
                    mAllColRatio = 1.0f - iVar2 * 0.01875f;
                } else if (iVar2 < 41) {
                    mAllColRatio = 0.625f - (iVar2 + -20) * 0.0125f;
                } else if (iVar2 < 61) {
                    mAllColRatio = 0.375f - (iVar2 + -40) * 0.00625f;
                } else if ((iVar2 >= 130) && (iVar2 < 150)) {
                    mAllColRatio = (iVar2 + -130) * 0.00625f + 0.25f;
                } else if((field_0x8C4 >= 150) && (field_0x8C4 < 170)){
                    mAllColRatio = (iVar2 + -150) * 0.0125f + 0.375f;
                } else if((iVar2 >= 170) && (iVar2 <= 190)){
                    mAllColRatio = (iVar2 + -170) * 0.01875f + 0.625f;
                }

                if (field_0x8C4 == 40) {
                    mPos.x = 0.0f;
                    mPos.y = 0.0f;
                    mPos.z = 0.0f;
                    mDoMtx_stack_c::copy(field_0x6D8->getAnmMtx(field_0x89C));
                    mDoMtx_stack_c::multVecZero(&mPos);
                    
                    if (field_0x894 == 0) {
                        dComIfGp_particle_set(dPa_name::ID_SCENE_8434, &mPos, &current.angle);
                    } else if (field_0x894 == 1) {
                        dComIfGp_particle_set(dPa_name::ID_SCENE_8436, &mPos, &current.angle);
                    } else {
                        dComIfGp_particle_set(dPa_name::ID_SCENE_8435, &mPos, &current.angle);
                    }
                } else if (field_0x8C4 == 125) {
                    field_0x8A3 = true;
                }
                break;
            }
            default:
                doCutEnd = true;
                break;
            }
            if(doCutEnd){
                dComIfGp_evmng_cutEnd(staffIdx);
            } 
        }
    }
}

/* 000015A8-00001630       .text getFinishEventCount__12daObjDoguu_cFv */
int daObjDoguu_c::getFinishEventCount() {
    int count = 0;
    if (dComIfGs_isEventBit(0x1480)) {
        count += 1;
    }
    if (dComIfGs_isEventBit(0x1440)) {
        count += 1;
    }
    if (dComIfGs_isEventBit(0x1410)) {
        count += 1;
    }
    return count;
}


/* 00001630-000016A4       .text setFinishMyEvent__12daObjDoguu_cFv */
void daObjDoguu_c::setFinishMyEvent() {
    if (field_0x894 == 0) {
        dComIfGs_onEventBit(0x1480);
    } else if (field_0x894 == 1) {
        dComIfGs_onEventBit(0x1440);
    } else {
        dComIfGs_onEventBit(0x1410);
    }
}

/* 000016A4-000016C4       .text daObjDoguu_Create__FPv */
static cPhs_State daObjDoguu_Create(void* i_this) {
    return static_cast<daObjDoguu_c*>(i_this)->_create();
}

/* 000016C4-0000178C       .text _create__12daObjDoguu_cFv */
cPhs_State daObjDoguu_c::_create() {
    fopAcM_SetupActor(this, daObjDoguu_c);
    if(subtype >= 1) {
        field_0x894 = subtype - 1;
    } else {
        field_0x894 = fopAcM_GetParam(this) & 0xFF;
    }
    cPhs_State phase_state = dComIfG_resLoad(&mPhs,"Doguu");
    if (phase_state == cPhs_COMPLEATE_e) {
        if(!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0)){
            return cPhs_ERROR_e;
        }
        CreateInit();
    }
    return phase_state;
}

daObjDoguu_c::daObjDoguu_c() {}

bool daObjDoguu_c::_delete(){
    dKy_plight_cut(&mLightInfluence);
    dComIfG_resDelete(&mPhs,"Doguu");
    return true;
}

/* 00001CC8-00001D0C       .text daObjDoguu_Delete__FPv */
static BOOL daObjDoguu_Delete(void* i_this) {
    return static_cast<daObjDoguu_c*>(i_this)->_delete();
}

/* 00001D0C-00001D30       .text daObjDoguu_Draw__FPv */
static BOOL daObjDoguu_Draw(void* i_this) {
    return static_cast<daObjDoguu_c*>(i_this)->_draw();
}

/* 00001D30-00001F64       .text _draw__12daObjDoguu_cFv */
bool daObjDoguu_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(field_0x6CC, &tevStr);
    g_env_light.setLightTevColorType(field_0x6D0, &tevStr);
    g_env_light.setLightTevColorType(field_0x6D4, &tevStr);
    g_env_light.setLightTevColorType(field_0x6D8, &tevStr);
    
    setEffectMtx(&eyePos, attr().mScale);

    if(field_0x8A1){
        J3DMaterialTable* bmt = (J3DMaterialTable*)dComIfG_getObjectRes("Doguu", daObjDoguu_idx_table.bmt_vgsb[field_0x894]);
        
        field_0x6D4->getModelData()->setMaterialTable(bmt, J3DMatCopyFlag_All);
        mBckHead.entry(field_0x6D0->getModelData());
        mDoExt_modelUpdateDL(field_0x6D0);
        field_0x6D0->getModelData()->getJointNodePointer(0)->setMtxCalc(NULL);

        mBckBody.entry(field_0x6D4->getModelData());
        mDoExt_modelUpdateDL(field_0x6D4);
        field_0x6D4->getModelData()->getJointNodePointer(0)->setMtxCalc(NULL);
    } else {
        J3DMaterialTable* bmt = (J3DMaterialTable*)dComIfG_getObjectRes("Doguu", daObjDoguu_idx_table.bmt_vgsm[field_0x894]);
        field_0x6CC->getModelData()->setMaterialTable(bmt, J3DMatCopyFlag_All);
        mBrk.entry(field_0x6CC->getModelData());
        mDoExt_modelUpdateDL(field_0x6CC);
        field_0x6CC->getModelData()->getMaterialTable().removeTevRegAnimator(mBrk.getBrkAnm());
    }
    if (field_0x8A0 == true) {
        mBckCrystal.entry(field_0x6D8->getModelData());
        mDoExt_modelUpdateDL(field_0x6D8);
        field_0x6D8->getModelData()->getJointNodePointer(0)->setMtxCalc(NULL);       
    }
    return true;
}

/* 00001F64-00002264       .text setEffectMtx__12daObjDoguu_cFPC4cXyzf */
void daObjDoguu_c::setEffectMtx(const cXyz* i_pos, float i_scale) {
    static Mtx mtx_adj = { 
        0.5f, 0.0f, 0.0f, 0.5f,
        0.0f, -0.5f, 0.0f, 0.5f,
        0.0f, 0.0f, 1.0f, 0.0f,
    };
    
    float scale = 1.0f /i_scale;
    camera_class* camera = dCam_getCamera();
    cXyz lookDir = *i_pos - camera->mLookat.mEye;
    cXyz lightDir;
    cXyz refl;

    dKyr_get_vectle_calc(&tevStr.mLightPosWorld, (cXyz*)i_pos, &lightDir);

    C_VECHalfAngle(&lookDir, &lightDir, &refl);
    Mtx reflMtx;
    C_MTXLookAt(reflMtx, &cXyz::Zero, &cXyz::BaseY, &refl);
    mDoMtx_stack_c::scaleS(scale, scale, 1.0f);
    mDoMtx_stack_c::concat(mtx_adj);
    mDoMtx_stack_c::concat(reflMtx);
    MtxP mtx = mDoMtx_stack_c::get();
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;
    
    J3DModelData *modelData = field_0x6D0->getModelData();
    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        J3DMaterial* mat = modelData->getMaterialNodePointer(i);
        for (u32 j = 0; j < 8; j++) {
            J3DTexMtx* texMtx = mat->getTexMtx(j);
            if (texMtx != NULL && texMtx->getTexMtxInfo().mInfo == 10) {
                texMtx->getTexMtxInfo().setEffectMtx(mDoMtx_stack_c::get());
            }
        }
    }
    
    modelData = field_0x6D4->getModelData();
    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        J3DMaterial* mat = modelData->getMaterialNodePointer(i);
        for (u32 j = 0; j < 8; j++) {
            J3DTexMtx* texMtx = mat->getTexMtx(j);
            if (texMtx != NULL && texMtx->getTexMtxInfo().mInfo == 10) {
                texMtx->getTexMtxInfo().setEffectMtx(mDoMtx_stack_c::get());
            }
        }
    }
}

/* 00002264-00002288       .text daObjDoguu_Execute__FPv */
static BOOL daObjDoguu_Execute(void* i_this) {
    return static_cast<daObjDoguu_c*>(i_this)->_execute();
}

/* 00002288-000027AC       .text _execute__12daObjDoguu_cFv */
bool daObjDoguu_c::_execute() {
    if (field_0x8A3 == 1) {
        mPos.x = 0.0f;
        mPos.y = 0.0f;
        mPos.z = 0.0f;
        mDoMtx_stack_c::copy(field_0x6D8->getAnmMtx(field_0x89C));
        mDoMtx_stack_c::multVecZero(&mPos);
        setPointLight();
    }
    
    mCyl.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mCyl);
    
    if (mAllColRatio != 1.0f) {
        dKy_set_allcol_ratio(mAllColRatio);
    }
    
    switch(field_0x8AC) {
        case 0:
            if (checkItemGet(mItemNo, TRUE) && mCyl.ChkCoHit()) {
                cCcD_Obj* hitObj = mCyl.GetCoHitObj();
                if (hitObj != NULL) {
                    fopAc_ac_c *ac = hitObj->GetAc();
                    if ((ac != NULL) && (fopAcM_GetName(ac) == PROC_PLAYER)) {
                        mCyl.SetR(50.0f);
                        fopAcM_orderOtherEventId(this, mDoguuDemo1EventIdx);
                        field_0x8AC = 1;
                    }
                }
            }
            break;        
        case 1:
            if(eventInfo.mCommand == dEvtCmd_INDEMO_e){
                field_0x8AC = 2;
            } else {
                fopAcM_orderOtherEventId(this, mDoguuDemo1EventIdx);
            }
            break;
        case 2:
            privateCut();
            if (dComIfGp_evmng_endCheck(mDoguuDemo1EventIdx)) {
            field_0x8AC = 3;
            }
            break;
        case 3:
            if (getFinishEventCount() == 0) {
                fopAcM_orderChangeEventId(this, mDoguuDemo2EventIdx, 0, 0xFFFF);
                field_0x8AC = 4;
            }
            else {
                fopAcM_orderChangeEventId(this, mDoguuDemo3EventIdx, 0, 0xFFFF);
                field_0x8AC = 7;
            }
            break;
        case 4:
            if(eventInfo.mCommand == dEvtCmd_INDEMO_e){
                field_0x8AC = 5;
            }
            break;
        case 5:
            privateCut();
            if (dComIfGp_evmng_endCheck(mDoguuDemo2EventIdx)) {
                field_0x8AC = 6;
            }
            break;
        case 6:
            fopAcM_orderChangeEventId(this, mDoguuDemo3EventIdx, 0, 0xFFFF);
            field_0x8AC = 7;
            break;
        case 7:
            if(eventInfo.mCommand == dEvtCmd_INDEMO_e){
                field_0x8AC = 8;
            }
            break;
        case 8:
            privateCut();
            if (dComIfGp_evmng_endCheck(mDoguuDemo3EventIdx)) {
                field_0x8AC = 9;
            }
            break;
        case 9:
            setFinishMyEvent();
    
            if (getFinishEventCount() >= 3) {
                dComIfGs_onEventBit(0x1e40);
                fopAcM_orderChangeEventId(this, mMegamiDemoEventIdx, 0, 0xFFFF);
                field_0x8AC = 11;
            } else {
                field_0x8AC = 10;
                dComIfGp_event_reset();
            }
            break;
        case 10:
            mCyl.SetR(30.0f);
            break;
        case 11:
            if(eventInfo.mCommand == dEvtCmd_INDEMO_e){
                field_0x8AC = 12;
            }
            break;
        case 12:
            privateCut();
            if (dComIfGp_evmng_endCheck(mMegamiDemoEventIdx)) {
                field_0x8AC = 13;
            }
            break;
        case 14:
            mCyl.SetR(30.0f);
            break;
    }
    
    if (!field_0x8A1 && field_0x8A2 == true) {
        if (mBrk.getFrame() < 1.0f) {
            fopAcM_seStartCurrent(this, JA_SE_OBJ_SDOLL_EYE_PULSE, 0);
        }
        mBrk.play();
    }

    if(demoActorID != 0){
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        if (demo_actor != NULL) {
            if (demo_actor->checkEnable(dDemo_actor_c::ENABLE_SHAPE_e)) {
                mShape = demo_actor->getShapeId();
            }
            if (demo_actor->checkEnable(dDemo_actor_c::ENABLE_ROTATE_e)) {
                current.angle = *demo_actor->getRatate();
            }
            if (demo_actor->checkEnable(dDemo_actor_c::ENABLE_TRANS_e)) {
                current.pos = *demo_actor->getTrans();
            }
            if(demo_actor->checkEnable(dDemo_actor_c::ENABLE_ANM_FRAME_e)) {
                f32 frame = demo_actor->getAnmFrame();
                mBckHead.setFrame(frame);
                mBckBody.setFrame(frame);
                mBckCrystal.setFrame(frame);
            }
        }
        if (mShape == 0) {
            field_0x8A1 = false;
        }else {
            field_0x8A1 = true;
        }
    }
    set_mtx();
    return true;
}

/* 000027AC-000027B4       .text daObjDoguu_IsDelete__FPv */
static BOOL daObjDoguu_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_DoguuMethodTable = {
    (process_method_func)daObjDoguu_Create,
    (process_method_func)daObjDoguu_Delete,
    (process_method_func)daObjDoguu_Execute,
    (process_method_func)daObjDoguu_IsDelete,
    (process_method_func)daObjDoguu_Draw,
};

actor_process_profile_definition g_profile_Obj_Doguu = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Doguu,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjDoguu_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Doguu,
    /* Actor SubMtd */ &daObj_DoguuMethodTable,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
