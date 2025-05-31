/**
 * d_a_demo_item.cpp
 * Item - Cutscene Item
 */

#include "d/actor/d_a_demo_item.h"
#include "d/d_procname.h"
#include "d/d_drawlist.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_item_data.h"
#include "d/d_item.h"
#include "m_Do/m_Do_mtx.h"
#include "f_op/f_op_camera.h"

#include "weak_bss_936_to_1036.h" // IWYU pragma: keep

const int daDitem_c::m_rot_time = 8*30;

u8 daDitem_c::m_effect_type[0x100] = {
    0x04, // dItem_HEART_e
    0x03, // dItem_GREEN_RUPEE_e
    0x03, // dItem_BLUE_RUPEE_e
    0x03, // dItem_YELLOW_RUPEE_e
    0x03, // dItem_RED_RUPEE_e
    0x03, // dItem_PURPLE_RUPEE_e
    0x03, // dItem_ORANGE_RUPEE_e
    0x00, // dItem_HEART_PIECE_e
    0x00, // dItem_HEART_CONTAINER_e
    0x04, // dItem_SMALL_MAGIC_e
    0x04, // dItem_LARGE_MAGIC_e
    0x04, // dItem_BOMB_5_e
    0x04, // dItem_BOMB_10_e
    0x04, // dItem_BOMB_20_e
    0x04, // dItem_BOMB_30_e
    0x03, // dItem_SILVER_RUPEE_e
    0x04, // dItem_ARROW_10_e
    0x04, // dItem_ARROW_20_e
    0x04, // dItem_ARROW_30_e
    0x04, // noentry19
    0x04, // noentry20
    0x02, // dItem_SMALL_KEY_e
    0x04, // dItem_RECOVER_FAIRY_e
    0x04, // noentry23
    0x04, // noentry24
    0x04, // noentry25
    0x03, // dItem_SUB_DUN_RUPEE_e
    0x04, // noentry27
    0x04, // noentry28
    0x04, // noentry29
    0x04, // dItem_TRIPLE_HEART_e
    0x01, // dItem_JOY_PENDANT_e
    0x00, // dItem_TELESCOPE_e
    0x00, // dItem_TINGLE_TUNER_e
    0x00, // dItem_WIND_WAKER_e
    0x00, // CAMERA
    0x00, // dItem_SPOILS_BAG_e
    0x00, // dItem_GRAPPLING_HOOK_e
    0x00, // CAMERA2
    0x00, // dItem_BOW_e
    0x00, // dItem_POWER_BRACELETS_e
    0x00, // dItem_IRON_BOOTS_e
    0x00, // dItem_MAGIC_ARMOR_e
    0x04, // WATER_BOOTS
    0x00, // dItem_BAIT_BAG_e
    0x00, // dItem_BOOMERANG_e
    0x04, // BARE_HAND
    0x00, // dItem_HOOKSHOT_e
    0x00, // dItem_DELIVERY_BAG_e
    0x00, // dItem_BOMB_BAG_e
    0x03, // dItem_FUKU_e
    0x00, // dItem_SKULL_HAMMER_e
    0x00, // dItem_DEKU_LEAF_e
    0x00, // dItem_MAGIC_ARROW_e
    0x00, // dItem_LIGHT_ARROW_e
    0x04, // dItem_NEW_FUKU_e
    0x00, // dItem_SWORD_e
    0x00, // dItem_MASTER_SWORD_1_e
    0x04, // dItem_MASTER_SWORD_2_e
    0x00, // dItem_SHIELD_e
    0x00, // dItem_MIRROR_SHIELD_e
    0x00, // dItem_DROPPED_SWORD_e
    0x04, // dItem_MASTER_SWORD_3_e
    0x01, // KAKERA_HEART2
    0x04, // noentry64
    0x04, // noentry65
    0x00, // dItem_PIRATES_CHARM_e
    0x00, // dItem_HEROS_CHARM_e
    0x04, // GRASS_BALL
    0x01, // dItem_SKULL_NECKLACE_e
    0x01, // dItem_BOKOBABA_SEED_e
    0x01, // dItem_GOLDEN_FEATHER_e
    0x01, // BOKO_BELT
    0x01, // dItem_RED_JELLY_e
    0x01, // dItem_GREEN_JELLY_e
    0x01, // dItem_BLUE_JELLY_e
    0x01, // dItem_MAP_e
    0x01, // dItem_COMPASS_e
    0x00, // dItem_BOSS_KEY_e
    0x04, // EMPTY_BSHIP
    0x00, // dItem_EMPTY_BOTTLE_e
    0x02, // dItem_RED_POTION_e
    0x02, // dItem_GREEN_POTION_e
    0x02, // dItem_BLUE_POTION_e
    0x00, // dItem_HALF_SOUP_BOTTLE_e
    0x00, // dItem_SOUP_BOTTLE_e
    0x02, // dItem_WATER_BOTTLE_e
    0x02, // dItem_FAIRY_BOTTLE_e
    0x00, // dItem_FIREFLY_BOTTLE_e
    0x02, // dItem_FOREST_WATER_e
    0x04, // UNK_BOTTLE_5A
    0x04, // UNK_BOTTLE_5B
    0x04, // UNK_BOTTLE_5C
    0x04, // UNK_BOTTLE_5D
    0x04, // UNK_BOTTLE_5E
    0x04, // UNK_BOTTLE_5F
    0x04, // UNK_BOTTLE_60
    0x00, // dItem_TRIFORCE1_e
    0x00, // dItem_TRIFORCE2_e
    0x00, // dItem_TRIFORCE3_e
    0x00, // dItem_TRIFORCE4_e
    0x00, // dItem_TRIFORCE5_e
    0x00, // dItem_TRIFORCE6_e
    0x00, // dItem_TRIFORCE7_e
    0x00, // dItem_TRIFORCE8_e
    0x00, // dItem_PEARL_NAYRU_e
    0x00, // dItem_PEARL_DIN_e
    0x00, // dItem_PEARL_FARORE_e
    0x04, // KNOWLEDGE_TF
    0x04, // TACT_SONG1
    0x04, // TACT_SONG2
    0x04, // TACT_SONG3
    0x04, // TACT_SONG4
    0x04, // TACT_SONG5
    0x04, // TACT_SONG6
    0x04, // noentry115
    0x04, // noentry116
    0x04, // noentry117
    0x04, // noentry118
    0x04, // noentry119
    0x00, // NORMAL_SAIL
    0x00, // TRIFORCE_MAP1
    0x00, // TRIFORCE_MAP2
    0x00, // TRIFORCE_MAP3
    0x00, // TRIFORCE_MAP4
    0x00, // TRIFORCE_MAP5
    0x00, // TRIFORCE_MAP6
    0x00, // TRIFORCE_MAP7
    0x00, // TRIFORCE_MAP8
    0x04, // noentry129
    0x02, // dItem_BIRD_BAIT_5_e
    0x02, // dItem_HYOI_PEAR_e
    0x04, // ESA1
    0x04, // ESA2
    0x04, // ESA3
    0x04, // ESA4
    0x04, // ESA5
    0x04, // MAGIC_BEAN
    0x04, // BIRD_ESA_10
    0x04, // noentry139
    0x02, // FLOWER_1
    0x02, // FLOWER_2
    0x02, // FLOWER_3
    0x02, // HEROS_FLAG
    0x02, // TAIRYO_FLAG
    0x02, // SALES_FLAG
    0x02, // WIND_FLAG
    0x02, // RED_FLAG
    0x02, // FOSSIL_HEAD
    0x02, // WATER_STATUE
    0x02, // POSTMAN_STATUE
    0x02, // PRESIDENT_STATUE
    0x02, // dItem_FATHER_LETTER_e
    0x02, // dItem_NOTE_TO_MOM_e
    0x02, // MAGYS_LETTER
    0x02, // MO_LETTER
    0x00, // COTTAGE_PAPER
    0x02, // KAISEN_PRESENT1
    0x02, // KAISEN_PRESENT2
    0x00, // SALVAGE_ITEM1
    0x04, // SALVAGE_ITEM2
    0x04, // SALVAGE_ITEM3
    0x04, // XXX_039
    0x00, // TINGLE_STATUE1
    0x00, // TINGLE_STATUE2
    0x00, // TINGLE_STATUE3
    0x00, // TINGLE_STATUE4
    0x00, // TINGLE_STATUE5
    0x00, // TINGLE_STATUE6
    0x04, // noentry169
    0x04, // dItem_HURRICANE_SPIN_e
    0x00, // dItem_MAX_RUPEE_UP1_e
    0x00, // dItem_MAX_RUPEE_UP2_e
    0x00, // dItem_MAX_BOMB_UP1_e
    0x00, // dItem_MAX_BOMB_UP2_e
    0x00, // dItem_MAX_ARROW_UP1_e
    0x00, // dItem_MAX_ARROW_UP2_e
    0x04, // dItem_MAGIC_POWER_e
    0x04, // dItem_MAX_MP_UP1_e
    0x03, // TINCLE_RUPEE1
    0x03, // TINCLE_RUPEE2
    0x03, // TINCLE_RUPEE3
    0x03, // TINCLE_RUPEE4
    0x03, // TINCLE_RUPEE5
    0x03, // TINCLE_RUPEE6
    0x04, // LITHOGRAPH1
    0x04, // LITHOGRAPH2
    0x04, // LITHOGRAPH3
    0x04, // LITHOGRAPH4
    0x04, // LITHOGRAPH5
    0x04, // LITHOGRAPH6
    0x04, // dItem_COLLECT_MAP_64_e
    0x04, // dItem_COLLECT_MAP_63_e
    0x04, // dItem_COLLECT_MAP_62_e
    0x00, // dItem_COLLECT_MAP_61_e
    0x00, // dItem_COLLECT_MAP_60_e
    0x00, // dItem_COLLECT_MAP_59_e
    0x00, // dItem_COLLECT_MAP_58_e
    0x00, // dItem_COLLECT_MAP_57_e
    0x00, // dItem_COLLECT_MAP_56_e
    0x00, // dItem_COLLECT_MAP_55_e
    0x00, // dItem_COLLECT_MAP_54_e
    0x00, // dItem_COLLECT_MAP_53_e
    0x00, // dItem_COLLECT_MAP_52_e
    0x00, // dItem_COLLECT_MAP_51_e
    0x00, // dItem_COLLECT_MAP_50_e
    0x00, // dItem_COLLECT_MAP_49_e
    0x00, // dItem_COLLECT_MAP_48_e
    0x00, // dItem_COLLECT_MAP_47_e
    0x00, // dItem_COLLECT_MAP_46_e
    0x00, // dItem_COLLECT_MAP_45_e
    0x00, // dItem_COLLECT_MAP_44_e
    0x00, // dItem_COLLECT_MAP_43_e
    0x00, // dItem_COLLECT_MAP_42_e
    0x00, // dItem_COLLECT_MAP_41_e
    0x00, // dItem_COLLECT_MAP_40_e
    0x00, // dItem_COLLECT_MAP_39_e
    0x00, // dItem_COLLECT_MAP_38_e
    0x00, // dItem_COLLECT_MAP_37_e
    0x00, // dItem_COLLECT_MAP_36_e
    0x00, // dItem_COLLECT_MAP_35_e
    0x00, // dItem_COLLECT_MAP_34_e
    0x00, // dItem_COLLECT_MAP_33_e
    0x00, // dItem_COLLECT_MAP_32_e
    0x00, // dItem_COLLECT_MAP_31_e
    0x00, // dItem_COLLECT_MAP_30_e
    0x00, // dItem_COLLECT_MAP_29_e
    0x00, // dItem_COLLECT_MAP_28_e
    0x00, // dItem_COLLECT_MAP_27_e
    0x00, // dItem_COLLECT_MAP_26_e
    0x00, // dItem_COLLECT_MAP_25_e
    0x00, // dItem_COLLECT_MAP_24_e
    0x00, // dItem_COLLECT_MAP_23_e
    0x00, // dItem_COLLECT_MAP_22_e
    0x00, // dItem_COLLECT_MAP_21_e
    0x00, // dItem_COLLECT_MAP_20_e
    0x00, // dItem_COLLECT_MAP_19_e
    0x00, // dItem_COLLECT_MAP_18_e
    0x00, // dItem_COLLECT_MAP_17_e
    0x00, // dItem_COLLECT_MAP_16_e
    0x00, // dItem_COLLECT_MAP_15_e
    0x00, // dItem_COLLECT_MAP_14_e
    0x00, // dItem_COLLECT_MAP_13_e
    0x00, // dItem_COLLECT_MAP_12_e
    0x00, // dItem_COLLECT_MAP_11_e
    0x00, // dItem_COLLECT_MAP_10_e
    0x00, // dItem_COLLECT_MAP_09_e
    0x00, // dItem_COLLECT_MAP_08_e
    0x00, // dItem_COLLECT_MAP_07_e
    0x00, // dItem_COLLECT_MAP_06_e
    0x00, // dItem_COLLECT_MAP_05_e
    0x00, // dItem_COLLECT_MAP_04_e
    0x00, // dItem_COLLECT_MAP_03_e
    0x00, // dItem_COLLECT_MAP_02_e
    0x00, // dItem_COLLECT_MAP_01_e
    0x04, // dItem_NONE_e
};

/* 000000EC-00000320       .text setParticle__9daDitem_cFv */
void daDitem_c::setParticle() {
    cXyz unused_scale(1.0f, 1.0f, 1.0f);
    cXyz unused_pos(current.pos);
    
    if (mpEmitters[0] || mpEmitters[1] || mpEmitters[2] || mpEmitters[3]) {
        return;
    }
    if (chkArgFlag(FLAG_UNK02) || chkArgFlag(FLAG_UNK04) || chkArgFlag(FLAG_UNK08)) {
        return;
    }
    
    csXyz angle;
    angle.x = dCam_getAngleX(dComIfGp_getCamera(0)) - 0x2000;
    angle.y = dCam_getAngleY(dComIfGp_getCamera(0));
    angle.z = 0;
    
    switch (m_effect_type[m_itemNo]) {
    case 0:
        mpEmitters[0] = dComIfGp_particle_set(dPa_name::ID_COMMON_01F7, &current.pos, &angle);
    case 1:
        mpEmitters[1] = dComIfGp_particle_set(dPa_name::ID_COMMON_01F8, &current.pos, &angle);
    case 2:
        mpEmitters[2] = dComIfGp_particle_set(dPa_name::ID_COMMON_01F9, &current.pos, &angle);
    case 3:
        mpEmitters[3] = dComIfGp_particle_set(dPa_name::ID_COMMON_01FA, &current.pos, &angle);
    case 4:
        break;
    }
}

/* 0000035C-000003F0       .text CreateInit__9daDitem_cFv */
bool daDitem_c::CreateInit() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    hide();
    clrFlag();
    mArgFlag = daDitem_prm::getFlag(this);
    if (!chkArgFlag(FLAG_UNK02) && !chkArgFlag(FLAG_UNK04) && !chkArgFlag(FLAG_UNK08)) {
        current.angle.y = -0x2000;
    }
    for (int i = 0; i < ARRAY_SIZE(mpEmitters); i++) {
        mpEmitters[i] = NULL;
    }
    return true;
}

/* 000003F0-000004AC       .text set_effect__9daDitem_cFv */
void daDitem_c::set_effect() {
    s16 angleX = dCam_getAngleX(dComIfGp_getCamera(0)) - 0x2000;
    s16 angleY = dCam_getAngleY(dComIfGp_getCamera(0));
    for (int i = 0; i < (int)ARRAY_SIZE(mpEmitters); i++) {
        if (mpEmitters[i] == NULL) {
            continue;
        }
        JGeometry::TVec3<s16> rot;
        rot.x = angleX;
        rot.y = angleY;
        rot.z = 0;
        mpEmitters[i]->playCreateParticle();
        mpEmitters[i]->setGlobalTranslation(current.pos);
        mpEmitters[i]->setGlobalRotation(rot);
    }
}

/* 000004AC-000006E4       .text set_pos__9daDitem_cFv */
void daDitem_c::set_pos() {
    static cXyz offset_tbl[3] = {
        cXyz(0.0f, 130.0f, 0.0f),
        cXyz(0.0f, 90.0f, 50.0f),
        cXyz(30.0f, 140.0f, 20.0f),
    };
    
    cXyz pos;
    cXyz offset;
    if (chkArgFlag(FLAG_UNK02)) {
        offset = offset_tbl[1];
    } else if (chkArgFlag(FLAG_UNK04)) {
        offset = offset_tbl[2];
    } else if (chkArgFlag(FLAG_UNK08)) {
        offset = mOffsetPos;
    } else {
        offset = offset_tbl[0];
    }
    
    if (!chkArgFlag(FLAG_UNK08)) {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        mDoMtx_stack_c::ZXYrotS(player->current.angle.x, player->shape_angle.y, player->current.angle.z);
        mDoMtx_stack_c::multVec(&offset, &offset);
        pos = dComIfGp_getPlayer(0)->current.pos;
    } else {
        pos = home.pos;
    }
    
    pos += offset;
    current.pos = pos;
}

/* 000006E4-00000760       .text anim_control__9daDitem_cFv */
void daDitem_c::anim_control() {
    switch (m_itemNo) {
    case EMPTY_BSHIP:
    case dItem_EMPTY_BOTTLE_e:
    case dItem_RED_POTION_e:
    case dItem_GREEN_POTION_e:
    case dItem_BLUE_POTION_e:
    case dItem_HALF_SOUP_BOTTLE_e:
    case dItem_SOUP_BOTTLE_e:
    case dItem_WATER_BOTTLE_e:
    case dItem_FAIRY_BOTTLE_e:
    case dItem_FIREFLY_BOTTLE_e:
    case dItem_FOREST_WATER_e:
    case UNK_BOTTLE_5A:
    case UNK_BOTTLE_5B:
    case UNK_BOTTLE_5C:
    case UNK_BOTTLE_5D:
    case UNK_BOTTLE_5E:
    case UNK_BOTTLE_5F:
    case UNK_BOTTLE_60:
        if (m_timer > 30) {
            animPlay(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        }
        break;
    default:
        animPlay(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        break;
    }
}

/* 00000760-00000880       .text set_mtx__9daDitem_cFv */
void daDitem_c::set_mtx() {
    mpModel->setBaseScale(scale);
    fopAcM_addAngleY(this, current.angle.y + 0x0111, 0x0111);
    
    if (chkArgFlag(FLAG_UNK02) || chkArgFlag(FLAG_UNK04) || chkArgFlag(FLAG_UNK08)) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y);
    } else {
        mDoMtx_stack_c::copy(dComIfGd_getInvViewMtx());
        mDoMtx_stack_c::ZrotM(current.angle.z);
        mDoMtx_stack_c::XrotM(0x12C0);
        mDoMtx_stack_c::YrotM(current.angle.y);
        mDoMtx_stack_c::get()[0][3] = current.pos.x;
        mDoMtx_stack_c::get()[1][3] = current.pos.y;
        mDoMtx_stack_c::get()[2][3] = current.pos.z;
    }
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000880-000008F0       .text settingBeforeDraw__9daDitem_cFv */
void daDitem_c::settingBeforeDraw() {
    if (isBomb(m_itemNo) || m_itemNo == dItem_BOMB_BAG_e || m_itemNo == dItem_SKULL_HAMMER_e || m_itemNo == dItem_SMALL_KEY_e) {
        dDlst_texSpecmapST(&eyePos, &tevStr, mpModel->getModelData(), 1.0f);
    }
}

/* 000008F0-000008F4       .text setListStart__9daDitem_cFv */
void daDitem_c::setListStart() {
}

BOOL daDitem_c::Delete() {
    if (!chkArgFlag(FLAG_UNK01)) {
        execItemGet(m_itemNo);
    }
    
    for (int i = 0; i < ARRAY_SIZE(mpEmitters); i++) {
        if (mpEmitters[i]) {
            mpEmitters[i]->setGlobalAlpha(0);
            mpEmitters[i]->becomeInvalidEmitter();
            mpEmitters[i] = NULL;
        }
    }
    
    return DeleteBase(dItem_data::getArcname(m_itemNo));
}

cPhs_State daDitem_c::create() {
    fopAcM_SetupActor(this, daDitem_c);
    
    m_itemNo = daDitem_prm::getNo(this);
    
    char* arcName = dItem_data::getArcname(m_itemNo);
    if (dItem_data::getBmdIdx(m_itemNo) == -1 || arcName == NULL) {
        m_itemNo = dItem_GREEN_RUPEE_e;
    }
    
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, dItem_data::getArcname(m_itemNo));
    if (phase_state == cPhs_COMPLEATE_e) {
        u32 heap_size = dItem_data::getHeapSize(m_itemNo);
        if (!fopAcM_entrySolidHeap(this, CheckItemCreateHeap, heap_size)) {
            return cPhs_ERROR_e;
        }
        CreateInit();
    }
    
    return phase_state;
}

BOOL daDitem_c::draw() {
    return DrawBase();
}

BOOL daDitem_c::execute() {
    m_timer++;
    
    if (chkDraw()) {
        setParticle();
        set_effect();
        fopAcM_onDraw(this);
    } else {
        fopAcM_offDraw(this);
    }
    
    anim_control();
    
    if (chkDead()) {
        fopAcM_delete(this);
    }
    
    set_pos();
    set_mtx();
    
    return TRUE;
}

/* 000008F4-00000994       .text daDitem_Delete__FP9daDitem_c */
static BOOL daDitem_Delete(daDitem_c* i_this) {
    return i_this->Delete();
}

/* 00000994-00000B6C       .text daDitem_Create__FP9daDitem_c */
static cPhs_State daDitem_Create(daDitem_c* i_this) {
    return i_this->create();
}

/* 00000D94-00000DB4       .text daDitem_IsDelete__FP9daDitem_c */
static BOOL daDitem_IsDelete(daDitem_c* i_this) {
    return i_this->isdelete();
}

/* 00000DB4-00000E58       .text daDitem_Execute__FP9daDitem_c */
static BOOL daDitem_Execute(daDitem_c* i_this) {
    return i_this->execute();
}

/* 00000E58-00000E84       .text daDitem_Draw__FP9daDitem_c */
static BOOL daDitem_Draw(daDitem_c* i_this) {
    return i_this->draw();
}

/* 00000E84-00000E8C       .text isdelete__9daDitem_cFv */
BOOL daDitem_c::isdelete() {
    return TRUE;
}

static actor_method_class l_daDitem_Method = {
    (process_method_func)daDitem_Create,
    (process_method_func)daDitem_Delete,
    (process_method_func)daDitem_Execute,
    (process_method_func)daDitem_IsDelete,
    (process_method_func)daDitem_Draw,
};

actor_process_profile_definition g_profile_Demo_Item = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Demo_Item,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daDitem_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00FC,
    /* Actor SubMtd */ &l_daDitem_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
