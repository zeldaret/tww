/**
 * d_a_shop_item.cpp
 * Item - Shop Item
 */

#include "d/actor/d_a_shop_item.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/d_item.h"
#include "d/d_item_data.h"
#include "d/d_cloth_packet.h"
#include "d/res/res_fdai.h"
#include "d/res/res_cloth.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_lib.h"

const char daShopItem_c::m_cloth_arcname[] = "Cloth";
const f32 daShopItem_c::m_cullfar_max = 5000.0f;

/* 00000078-000000D8       .text getShopArcname__12daShopItem_cFv */
char* daShopItem_c::getShopArcname() {
    u8 type = fopAcM_GetParamBit(fopAcM_GetParam(this), 8, 4);
    if(type == 1 || (type == 0 && mModelType[m_itemNo] == 0x01)) {
        return dItem_data::getFieldArc(m_itemNo);
    }
    else {
        return dItem_data::getArcname(m_itemNo);
    }
}

/* 000000D8-00000140       .text getShopBmdIdx__12daShopItem_cFv */
s16 daShopItem_c::getShopBmdIdx() {
    u8 type = fopAcM_GetParamBit(fopAcM_GetParam(this), 8, 4);
    if(type == 1 || (type == 0 && mModelType[m_itemNo] == 0x01)) {
        return dItem_data::getFieldBmdIdx(m_itemNo);
    }
    else {
        return dItem_data::getBmdIdx(m_itemNo);
    }
}

/* 00000140-00000240       .text CreateInit__12daShopItem_cFv */
void daShopItem_c::CreateInit() {
    fopAcM_SetMtx(this, field_0x64C);
    fopAcM_setCullSizeBox(this, -100.0f, 0.0f, -100.0f, 100.0f, 200.0f, 100.0f);
    if(mDoLib_clipper::mSystemFar > 1.0f) {
        fopAcM_setCullSizeFar(this, 5000.0f / mDoLib_clipper::mSystemFar);
    }
    show();

    scale = getData()[m_itemNo].mScale;
    home.pos = current.pos;
    set_mtx();

    if(isDaizaItem(m_itemNo)) {
        mTevType = TEV_TYPE_ACTOR;
    }
    else {
        mTevType = TEV_TYPE_BG1_PLIGHT;
    }

    mpModel->setUserArea(0);
}

/* 00000240-000003BC       .text clothCreate__12daShopItem_cFv */
BOOL daShopItem_c::clothCreate() {
    if(isUseClothPacket(m_itemNo)) {
        dCloth_packet_c::CreateFunc clothFunc[4] = {
            (dCloth_packet_c::CreateFunc)dClothVobj03_create,
            (dCloth_packet_c::CreateFunc)dClothVobj04_create,
            (dCloth_packet_c::CreateFunc)dClothVobj05_create,
            (dCloth_packet_c::CreateFunc)dClothVobj07_0_create
        };
        u32 clothRes[4] = {
            FDAI_BTI_FTEX03,
            FDAI_BTI_FTEX04,
            FDAI_BTI_FTEX05,
            FDAI_BTI_FTEX07
        };

        switch(m_itemNo) {
            case HEROS_FLAG:
                field_0x648 = 0;
                break;
            case TAIRYO_FLAG:
                field_0x648 = 1;
                break;
            case SALES_FLAG:
                field_0x648 = 2;
                break;
            case RED_FLAG:
            default:
                field_0x648 = 3;
        }

        ResTIMG* shopArc = (ResTIMG*)dComIfG_getObjectRes(getShopArcname(), clothRes[field_0x648]);
        ResTIMG* clothArc = (ResTIMG*)dComIfG_getObjectRes(m_cloth_arcname, CLOTH_BTI_CLOTHTOON);

        field_0x644 = (*clothFunc[field_0x648])(shopArc, clothArc, &tevStr, 0);
        if (field_0x644 == 0) {
            return FALSE;
        }
    }
    else {
        field_0x644 = 0;
    }
    
    return TRUE;
}

/* 000003BC-000005A8       .text set_mtx__12daShopItem_cFv */
void daShopItem_c::set_mtx() {
    mpModel->setBaseScale(scale);
    MTXTrans(mDoMtx_stack_c::get(), current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(current.angle.x, current.angle.y, current.angle.z);
    MTXCopy(mDoMtx_stack_c::get(), field_0x64C);

    const Vec& temp1 = getData()[m_itemNo].field_0x0C;
    mDoMtx_stack_c::transM(temp1.x, temp1.y, temp1.z);
    const SVec& temp2 = getData()[m_itemNo].field_0x18;
    mDoMtx_stack_c::ZXYrotM(temp2.x, temp2.y, temp2.z);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());

    if(field_0x644 != 0) {
        // I have no clue why Nintendo would do this but it works
        cXyz local[4];
        cXyz local2[4];

        local2[3].set(0.0f, REG10_F(15) + 94.0f, 0.0f);
        local[0].set(0.0f, REG10_F(15) + 94.0f, 0.0f);
        local2[2].set(0.0f, REG10_F(15) + 94.0f, 0.0f);
        local[1].set(0.0f, REG10_F(15) + 94.0f, 0.0f);
        local2[1].set(0.0f, REG10_F(15) + 97.5f, 0.0f);
        local[2].set(0.0f, REG10_F(15) + 97.5f, 0.0f);
        local2[0].set(0.0f, REG10_F(15) + 94.0f, 0.0f);
        local[3].set(0.0f, REG10_F(15) + 94.0f, 0.0f);

        mDoMtx_stack_c::transM(local[field_0x648]);
        mDoMtx_stack_c::YrotM(0x4000);
        field_0x644->setScale(scale);
        field_0x644->setMtx(mDoMtx_stack_c::get());
    }
}

/* 000005A8-000005F8       .text _execute__12daShopItem_cFv */
bool daShopItem_c::_execute() {
    animPlay(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    set_mtx();

    return true;
}

/* 000005F8-00000694       .text _draw__12daShopItem_cFv */
bool daShopItem_c::_draw() {
    if(!chkDraw()) return true;

    if(m_itemNo == WATER_STATUE || m_itemNo == POSTMAN_STATUE) {
        mpModel->getModelData()->getJointTree().getJointNodePointer(0)->setMtxCalc(0);
    }
    DrawBase();
    
    if(field_0x644 != 0) field_0x644->cloth_draw();

    return true;
}

/* 00000694-0000070C       .text settingBeforeDraw__12daShopItem_cFv */
void daShopItem_c::settingBeforeDraw() {
    if(isBomb(m_itemNo) || (m_itemNo == dItem_BOMB_BAG_e) || (m_itemNo == dItem_SKULL_HAMMER_e) || m_itemNo == dItem_SMALL_KEY_e || m_itemNo == PRESIDENT_STATUE) {
        dDlst_texSpecmapST(&eyePos, &tevStr, mpModel->getModelData(), 1.0f);
    }
}

/* 0000070C-000007A4       .text setTevStr__12daShopItem_cFv */
void daShopItem_c::setTevStr() {
    g_env_light.settingTevStruct(mTevType, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    for(int i = 0; i < 2; i++) {
        if(mpModelArrow[i] != 0) {
            g_env_light.setLightTevColorType(mpModelArrow[i], &tevStr);
        }
    }
    
}

/* 000007A4-000007C4       .text daShopItem_Create__FPv */
static cPhs_State daShopItem_Create(void* i_this) {
    return static_cast<daShopItem_c*>(i_this)->_create();
}

/* 000007C4-00000AA4       .text _create__12daShopItem_cFv */
cPhs_State daShopItem_c::_create() {
    fopAcM_SetupActor(this, daShopItem_c);
    
    m_itemNo = fopAcM_GetParamBit(fopAcM_GetParam(this), 0, 8);
    
    const char* arcName = getShopArcname();
    if (getShopBmdIdx() == -1 || arcName == 0) {
        m_itemNo = dItem_GREEN_RUPEE_e;
    }

    arcName = getShopArcname();
    cPhs_State result = dComIfG_resLoad(&mPhs, arcName);
    if(result != cPhs_COMPLEATE_e) {
        return result;
    }
    else {
        int result2 = cPhs_COMPLEATE_e;
        if(isUseClothPacket(m_itemNo)) {
            result2 = dComIfG_resLoad(&mPhase, m_cloth_arcname);
        }

        if(result2 != cPhs_COMPLEATE_e) {
            return result2;
        }
        else if(result == cPhs_COMPLEATE_e && result2 == cPhs_COMPLEATE_e) {
            u8 type = fopAcM_GetParamBit(fopAcM_GetParam(this), 8, 4);
            if(type == 2 || (type == 0 && mModelType[m_itemNo] == 0x02)) {
                if(fopAcM_entrySolidHeap(this, CheckItemCreateHeap, dItem_data::getHeapSize(m_itemNo)) == 0) {
                    return cPhs_ERROR_e;
                }
            }
            else if(type == 1 || (type == 0 && mModelType[m_itemNo] == 0x01)) {
                if(fopAcM_entrySolidHeap(this, CheckFieldItemCreateHeap, dItem_data::getFieldHeapSize(m_itemNo)) == 0) {
                    return cPhs_ERROR_e;
                }
            }
            else {
                if(fopAcM_entrySolidHeap(this, CheckItemCreateHeap, dItem_data::getHeapSize(m_itemNo)) == 0) {
                    return cPhs_ERROR_e;
                }
            }

            CreateInit();
        }
    }
    
    return result;
}

/* 00000CCC-00000D2C       .text daShopItem_Delete__FPv */
static BOOL daShopItem_Delete(void* i_this) {
    daShopItem_c* inst = static_cast<daShopItem_c*>(i_this);

    if(isUseClothPacket(inst->m_itemNo)) {
        dComIfG_resDelete(&inst->mPhase, daShopItem_c::m_cloth_arcname);
    }
    inst->DeleteBase(inst->getShopArcname());

    return TRUE;
}

/* 00000D2C-00000D50       .text daShopItem_Draw__FPv */
static BOOL daShopItem_Draw(void* i_this) {
    return static_cast<daShopItem_c*>(i_this)->_draw();
}

/* 00000D50-00000D74       .text daShopItem_Execute__FPv */
static BOOL daShopItem_Execute(void* i_this) {
    return static_cast<daShopItem_c*>(i_this)->_execute();
}

/* 00000D74-00000D7C       .text daShopItem_IsDelete__FPv */
static BOOL daShopItem_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daShopItemMethodTable = {
    (process_method_func)daShopItem_Create,
    (process_method_func)daShopItem_Delete,
    (process_method_func)daShopItem_Execute,
    (process_method_func)daShopItem_IsDelete,
    (process_method_func)daShopItem_Draw,
};

actor_process_profile_definition g_profile_ShopItem = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_ShopItem,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daShopItem_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_ShopItem,
    /* Actor SubMtd */ &daShopItemMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
