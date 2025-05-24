/**
 * d_a_race_item.cpp
 * Item - Barrel Item
 */

#include "d/actor/d_a_race_item.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_sea.h"
#include "d/d_item_data.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/actor/d_a_player_main.h"
#include "m_Do/m_Do_mtx.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 0.0f,
        /* Height */ 0.0f,
    },
};

/* 00000078-000000F8       .text set_mtx__12daRaceItem_cFv */
void daRaceItem_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000000F8-0000012C       .text Delete__12daRaceItem_cFv */
BOOL daRaceItem_c::Delete() {
    return DeleteBase(dItem_data::field_item_res[m_itemNo].mArc);
}

/* 0000012C-00000318       .text create__12daRaceItem_cFv */
cPhs_State daRaceItem_c::create() {
    fopAcM_SetupActor(this, daRaceItem_c);

    m_itemNo = fopAcM_GetParam(this) & 0xFF;
    mItemBitNo = fopAcM_GetParam(this) >> 8 & 0x7F;
    
    if(fopAcM_isItem(this, mItemBitNo) && mItemBitNo != 0x7F) {
        setLoadError();
        return cPhs_ERROR_e;
    }
    else {
        cPhs_State phase_state = dComIfG_resLoad(&mPhs, dItem_data::getFieldArc(m_itemNo));
        if (phase_state == cPhs_COMPLEATE_e) {
            u32 heap_size = dItem_data::getHeapSize(m_itemNo);
            if (!fopAcM_entrySolidHeap(this, &CheckFieldItemCreateHeap, heap_size)) {
                return cPhs_ERROR_e;
            }

            CreateInit();
        }
        
        return phase_state;
    }
}

/* 00000540-000006A4       .text CreateInit__12daRaceItem_cFv */
BOOL daRaceItem_c::CreateInit() {
    set_mtx();
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());

    mStts.Init(0, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    f32 height = getHeight();
    f32 radius = getR();
    if (scale.x > 1.0f) {
        height *= scale.x;
        radius *= scale.x;
    }
    mCyl.SetR(radius);
    mCyl.SetH(height);

    mAcchCir.SetWall(30.0f, 30.0f);
    mAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed);
    mAcch.ClrWaterNone();
    mAcch.ClrRoofNone();
    
    field_0x640 = 0;
    field_0x644 = fopAcM_GetParam(this) >> 0xF & 0xF;

    return true;
}

/* 000006A4-000006F0       .text checkGet__12daRaceItem_cFv */
void daRaceItem_c::checkGet() {
    if(field_0x644 == 1 && mCyl.ChkCoHit()) {
        normalItemGet();
    }
}

/* 000006F0-0000071C       .text daRaceItem_Draw__FP12daRaceItem_c */
static BOOL daRaceItem_Draw(daRaceItem_c* i_this) {
    return i_this->draw();
}

/* 0000071C-0000073C       .text daRaceItem_Execute__FP12daRaceItem_c */
static BOOL daRaceItem_Execute(daRaceItem_c* i_this) {
    return i_this->execute();
}

/* 0000073C-00000C44       .text execute__12daRaceItem_cFv */
BOOL daRaceItem_c::execute() {
    m_timer++;
    animPlay(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    eyePos = current.pos;
    eyePos.y += scale.x * dItem_data::getH(m_itemNo) / 2.0f;
    
    daPy_lk_c* player;
    cXyz headPos;
    switch(field_0x640) {
        case 0: {
            checkGet();

            s16 spin = 0xFFFF / daItemBase_c::m_data.mRotateYSpeed;
            fopAcM_addAngleY(this, current.angle.y + spin, spin);
            mCyl.SetC(current.pos);
            dComIfG_Ccsp()->Set(&mCyl);

            break;
        }
        case 1:
            player = daPy_getPlayerLinkActorClass();
            headPos = player->getHeadTopPos();
            headPos.y += 15.0f;
            current.pos = headPos;
            current.angle.z = 0;
            current.angle.x = 0;
            shape_angle.z = 0;
            shape_angle.x = 0;
            scale.setall(1.0f);

            field_0x63C = 0xD;

            speed.set(0.0f, 23.0f, 0.0f);
            gravity = -6.0f;

            mCyl.ClrTgHit();
            mCyl.ClrCoHit();
            mCyl.ClrCoSet();
            mCyl.ClrTgSet();

            cLib_offBit(field_0x645, (u8)0x01);
            field_0x640 = 2;
        case 2:
            field_0x63C -= 1;

            player = daPy_getPlayerLinkActorClass();
            headPos = player->getHeadTopPos();
            headPos.y += 15.0f;
            current.pos.x = headPos.x;
            current.pos.z = headPos.z;
            fopAcM_posMoveF(this, 0);

            if(current.pos.y < headPos.y) {
                current.pos.y = headPos.y;
            }

            if(field_0x63C < 0) {
                fopAcM_delete(this);
                break;
            }
            
            break;
        case 3:
            field_0x640 = 4;
        case 4:
            checkGet();

            fopAcM_posMoveF(this, mStts.GetCCMoveP());
            mAcch.CrrPos(*dComIfG_Bgsp());

            if(!cLib_checkBit(field_0x645, (u8)0x01) && !fopAcM_checkHookCarryNow(this)) {
                if(mAcch.ChkWaterIn()) {
                    fopAcM_seStart(this, JA_SE_OBJ_FALL_WATER_S, 0);
                    fopAcM_delete(this);
                }
                
                if(daSea_ChkArea(current.pos.x, current.pos.z)) {
                    f32 wave = daSea_calcWave(current.pos.x, current.pos.z);
                    if(wave != 0.0f && current.pos.y - wave < 0.0f) {
                        fopAcM_delete(this);
                    }
                }
            }

            if(current.pos.y < -5000.0f) {
                fopAcM_delete(this);
            }

            mCyl.SetC(current.pos);
            dComIfG_Ccsp()->Set(&mCyl);
    }

    if(mCyl.ChkTgHit() && field_0x644 == 1) {
        cCcD_Obj* hitObj = mCyl.GetTgHitObj();
        if (hitObj) {
            if (hitObj->ChkAtType(AT_TYPE_BOOMERANG)) {
                cLib_onBit(field_0x645, (u8)0x01);
            } else if (hitObj->ChkAtType(AT_TYPE_HOOKSHOT)) {
                cXyz offset(0.0f, dItem_data::getH(m_itemNo) / 2.0f, 0.0f);
                daPy_getPlayerActorClass()->setHookshotCarryOffset(fopAcM_GetID(this), &offset);
            }
        }
    }

    if(cLib_checkBit(field_0x645, (u8)0x01)) {
        fopAc_ac_c* boomerang = (fopAc_ac_c*)fopAcM_SearchByName(PROC_BOOMERANG);
        if(boomerang) {
            current.pos = boomerang->current.pos;
        }
        else {
            cLib_offBit(field_0x645, (u8)0x01);
        }
    }

    if(!checkOffsetPos()) {
        scale.setall(1.0f);
    }

    set_mtx();

    return true;
}

/* 00000C44-00000C4C       .text daRaceItem_IsDelete__FP12daRaceItem_c */
static BOOL daRaceItem_IsDelete(daRaceItem_c*) {
    return TRUE;
}

/* 00000C4C-00000C6C       .text daRaceItem_Delete__FP12daRaceItem_c */
static BOOL daRaceItem_Delete(daRaceItem_c* i_this) {
    return i_this->Delete();
}

/* 00000C6C-00000C8C       .text daRaceItem_Create__FP10fopAc_ac_c */
static cPhs_State daRaceItem_Create(fopAc_ac_c* i_this) {
    return static_cast<daRaceItem_c*>(i_this)->create();
}

static actor_method_class l_daRaceItem_Method = {
    (process_method_func)daRaceItem_Create,
    (process_method_func)daRaceItem_Delete,
    (process_method_func)daRaceItem_Execute,
    (process_method_func)daRaceItem_IsDelete,
    (process_method_func)daRaceItem_Draw,
};

actor_process_profile_definition g_profile_RACEITEM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_RACEITEM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daRaceItem_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_RACEITEM,
    /* Actor SubMtd */ &l_daRaceItem_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
