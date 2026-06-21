/**
 * d_a_demo_item.cpp
 * Item - Cutscene Item
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_demo_item.h"
#include "d/d_drawlist.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_item_data.h"
#include "d/d_item.h"
#include "m_Do/m_Do_mtx.h"
#include "f_op/f_op_camera.h"

const int daDitem_c::m_rot_time = 8*30;

u8 daDitem_c::m_effect_type[0x100] = {
    0x04, // dItemNo_HEART_e
    0x03, // dItemNo_GREEN_RUPEE_e
    0x03, // dItemNo_BLUE_RUPEE_e
    0x03, // dItemNo_YELLOW_RUPEE_e
    0x03, // dItemNo_RED_RUPEE_e
    0x03, // dItemNo_PURPLE_RUPEE_e
    0x03, // dItemNo_ORANGE_RUPEE_e
    DEMO_SELECT(0x01, 0x00), // dItemNo_HEART_PIECE_e
    0x00, // dItemNo_HEART_CONTAINER_e
    0x04, // dItemNo_SMALL_MAGIC_e
    0x04, // dItemNo_LARGE_MAGIC_e
    0x04, // dItemNo_BOMB_5_e
    0x04, // dItemNo_BOMB_10_e
    0x04, // dItemNo_BOMB_20_e
    0x04, // dItemNo_BOMB_30_e
    DEMO_SELECT(0x04, 0x03), // dItemNo_SILVER_RUPEE_e
    0x04, // dItemNo_ARROW_10_e
    0x04, // dItemNo_ARROW_20_e
    0x04, // dItemNo_ARROW_30_e
    0x04, // dItemNo_NOENTRY_19_e
    0x04, // dItemNo_NOENTRY_20_e
    0x02, // dItemNo_SMALL_KEY_e
    0x04, // dItemNo_RECOVER_FAIRY_e
    0x04, // dItemNo_NOENTRY_23_e
    0x04, // dItemNo_NOENTRY_24_e
    0x04, // dItemNo_NOENTRY_25_e
    0x03, // dItemNo_SUB_DUN_RUPEE_e
    0x04, // dItemNo_NOENTRY_27_e
    0x04, // dItemNo_NOENTRY_28_e
    0x04, // dItemNo_NOENTRY_29_e
    0x04, // dItemNo_TRIPLE_HEART_e
    0x01, // dItemNo_JOY_PENDANT_e
    0x00, // dItemNo_TELESCOPE_e
    0x00, // dItemNo_TINGLE_TUNER_e
    0x00, // dItemNo_WIND_WAKER_e
    0x00, // dItemNo_PICTO_BOX_e
    0x00, // dItemNo_SPOILS_BAG_e
    0x00, // dItemNo_GRAPPLING_HOOK_e
    0x00, // dItemNo_DELUXE_PICTO_BOX_e
    0x00, // dItemNo_BOW_e
    0x00, // dItemNo_POWER_BRACELETS_e
    0x00, // dItemNo_IRON_BOOTS_e
    0x00, // dItemNo_MAGIC_ARMOR_e
    0x04, // dItemNo_WATER_BOOTS_e
    0x00, // dItemNo_BAIT_BAG_e
    0x00, // dItemNo_BOOMERANG_e
    0x04, // dItemNo_BARE_HAND_e
    0x00, // dItemNo_HOOKSHOT_e
    0x00, // dItemNo_DELIVERY_BAG_e
    0x00, // dItemNo_BOMB_BAG_e
    0x03, // dItemNo_FUKU_e
    0x00, // dItemNo_SKULL_HAMMER_e
    0x00, // dItemNo_DEKU_LEAF_e
    0x00, // dItemNo_MAGIC_ARROW_e
    0x00, // dItemNo_LIGHT_ARROW_e
    0x04, // dItemNo_NEW_FUKU_e
    0x00, // dItemNo_SWORD_e
    0x00, // dItemNo_MASTER_SWORD_1_e
    0x04, // dItemNo_MASTER_SWORD_2_e
    0x00, // dItemNo_SHIELD_e
    0x00, // dItemNo_MIRROR_SHIELD_e
    DEMO_SELECT(0x04, 0x00), // dItemNo_DROPPED_SWORD_e
    0x04, // dItemNo_MASTER_SWORD_3_e
    0x01, // dItemNo_HEART_PIECE_ALT_e
    0x04, // dItemNo_NOENTRY_64_e
    0x04, // dItemNo_NOENTRY_65_e
    0x00, // dItemNo_PIRATES_CHARM_e
    0x00, // dItemNo_HEROS_CHARM_e
    0x04, // dItemNo_GRASS_BALL_e
    0x01, // dItemNo_SKULL_NECKLACE_e
    0x01, // dItemNo_BOKOBABA_SEED_e
    0x01, // dItemNo_GOLDEN_FEATHER_e
    0x01, // dItemNo_KNIGHTS_CREST_e
    0x01, // dItemNo_RED_JELLY_e
    0x01, // dItemNo_GREEN_JELLY_e
    0x01, // dItemNo_BLUE_JELLY_e
    0x01, // dItemNo_MAP_e
    0x01, // dItemNo_COMPASS_e
    0x00, // dItemNo_BOSS_KEY_e
    0x04, // dItemNo_EMPTY_BSHIP_e
    0x00, // dItemNo_EMPTY_BOTTLE_e
    0x02, // dItemNo_RED_POTION_e
    0x02, // dItemNo_GREEN_POTION_e
    0x02, // dItemNo_BLUE_POTION_e
    DEMO_SELECT(0x04, 0x00), // dItemNo_HALF_SOUP_BOTTLE_e
    0x00, // dItemNo_SOUP_BOTTLE_e
    0x02, // dItemNo_WATER_BOTTLE_e
    0x02, // dItemNo_FAIRY_BOTTLE_e
    0x00, // dItemNo_FIREFLY_BOTTLE_e
    0x02, // dItemNo_FOREST_WATER_e
    0x04, // dItemNo_UNK_BOTTLE_5A_e
    0x04, // dItemNo_UNK_BOTTLE_5B_e
    0x04, // dItemNo_UNK_BOTTLE_5C_e
    0x04, // dItemNo_UNK_BOTTLE_5D_e
    0x04, // dItemNo_UNK_BOTTLE_5E_e
    0x04, // dItemNo_UNK_BOTTLE_5F_e
    0x04, // dItemNo_UNK_BOTTLE_60_e
    0x00, // dItemNo_TRIFORCE1_e
    0x00, // dItemNo_TRIFORCE2_e
    0x00, // dItemNo_TRIFORCE3_e
    0x00, // dItemNo_TRIFORCE4_e
    0x00, // dItemNo_TRIFORCE5_e
    0x00, // dItemNo_TRIFORCE6_e
    0x00, // dItemNo_TRIFORCE7_e
    0x00, // dItemNo_TRIFORCE8_e
    0x00, // dItemNo_PEARL_NAYRU_e
    0x00, // dItemNo_PEARL_DIN_e
    0x00, // dItemNo_PEARL_FARORE_e
    0x04, // dItemNo_KNOWLEDGE_TF_e
    0x04, // dItemNo_WINDS_REQUIEM_e
    0x04, // dItemNo_BALLAD_OF_GALES_e
    0x04, // dItemNo_COMMAND_MELODY_e
    0x04, // dItemNo_EARTH_GODS_LYRIC_e
    0x04, // dItemNo_WIND_GODS_ARIA_e
    0x04, // dItemNo_SONG_OF_PASSING_e
    0x04, // dItemNo_NOENTRY_115_e
    0x04, // dItemNo_NOENTRY_116_e
    0x04, // dItemNo_NOENTRY_117_e
    0x04, // dItemNo_NOENTRY_118_e
    0x04, // dItemNo_NOENTRY_119_e
    0x00, // dItemNo_SAIL_e
    0x00, // dItemNo_TRIFORCE_MAP_1_e
    0x00, // dItemNo_TRIFORCE_MAP_2_e
    0x00, // dItemNo_TRIFORCE_MAP_3_e
    0x00, // dItemNo_TRIFORCE_MAP_4_e
    0x00, // dItemNo_TRIFORCE_MAP_5_e
    0x00, // dItemNo_TRIFORCE_MAP_6_e
    0x00, // dItemNo_TRIFORCE_MAP_7_e
    0x00, // dItemNo_TRIFORCE_MAP_8_e
    0x04, // dItemNo_NOENTRY_129_e
    0x02, // dItemNo_BIRD_BAIT_5_e
    0x02, // dItemNo_HYOI_PEAR_e
    0x04, // dItemNo_ESA_1_e
    0x04, // dItemNo_ESA_2_e
    0x04, // dItemNo_ESA_3_e
    0x04, // dItemNo_ESA_4_e
    0x04, // dItemNo_ESA_5_e
    0x04, // dItemNo_MAGIC_BEAN_e
    0x04, // dItemNo_BIRD_ESA_10_e
    0x04, // dItemNo_NOENTRY_139_e
    0x02, // dItemNo_TOWN_FLOWER_e
    0x02, // dItemNo_SEA_FLOWER_e
    0x02, // dItemNo_EXOTIC_FLOWER_e
    0x02, // dItemNo_HEROS_FLAG_e
    0x02, // dItemNo_BIG_CATCH_FLAG_e
    0x02, // dItemNo_BIG_SALE_FLAG_e
    0x02, // dItemNo_PINWHEEL_e
    0x02, // dItemNo_SICKLE_MOON_FLAG_e
    0x02, // dItemNo_SKULL_TOWER_IDOL_e
    0x02, // dItemNo_FOUNTAIN_IDOL_e
    0x02, // dItemNo_POSTMAN_STATUE_e
    0x02, // dItemNo_SHOP_GURU_STATUE_e
    0x02, // dItemNo_FATHER_LETTER_e
    0x02, // dItemNo_NOTE_TO_MOM_e
    0x02, // dItemNo_MAGGIES_LETTER_e
    0x02, // dItemNo_MOBLINS_LETTER_e
    DEMO_SELECT(0x04, 0x00), // dItemNo_CABANA_DEED_e
    0x02, // dItemNo_COMPLIMENTARY_ID_e
    0x02, // dItemNo_FILL_UP_COUPON_e
    DEMO_SELECT(0x04, 0x00), // dItemNo_LEGENDARY_PICTOGRAPH_e
    0x04, // dItemNo_SALVAGE_ITEM_2_e
    0x04, // dItemNo_SALVAGE_ITEM_3_e
    0x04, // dItemNo_XXX_039_e
    0x00, // dItemNo_TINGLE_STATUE_1_e
    0x00, // dItemNo_TINGLE_STATUE_2_e
    0x00, // dItemNo_TINGLE_STATUE_3_e
    0x00, // dItemNo_TINGLE_STATUE_4_e
    0x00, // dItemNo_TINGLE_STATUE_5_e
    0x00, // dItemNo_TINGLE_STATUE_6_e
    0x04, // dItemNo_NOENTRY_169_e
    0x04, // dItemNo_HURRICANE_SPIN_e
    0x00, // dItemNo_MAX_RUPEE_UP1_e
    0x00, // dItemNo_MAX_RUPEE_UP2_e
    0x00, // dItemNo_MAX_BOMB_UP1_e
    0x00, // dItemNo_MAX_BOMB_UP2_e
    0x00, // dItemNo_MAX_ARROW_UP1_e
    0x00, // dItemNo_MAX_ARROW_UP2_e
    0x04, // dItemNo_MAGIC_POWER_e
    0x04, // dItemNo_MAX_MP_UP1_e
    0x03, // dItemNo_TINGLE_RUPEE_1_e
    0x03, // dItemNo_TINGLE_RUPEE_2_e
    0x03, // dItemNo_TINGLE_RUPEE_3_e
    0x03, // dItemNo_TINGLE_RUPEE_4_e
    0x03, // dItemNo_TINGLE_RUPEE_5_e
    0x03, // dItemNo_TINGLE_RUPEE_6_e
    0x04, // dItemNo_LITHOGRAPH_1_e
    0x04, // dItemNo_LITHOGRAPH_2_e
    0x04, // dItemNo_LITHOGRAPH_3_e
    0x04, // dItemNo_LITHOGRAPH_4_e
    0x04, // dItemNo_LITHOGRAPH_5_e
    0x04, // dItemNo_LITHOGRAPH_6_e
    0x04, // dItemNo_COLLECT_MAP_64_e
    0x04, // dItemNo_COLLECT_MAP_63_e
    0x04, // dItemNo_COLLECT_MAP_62_e
    0x00, // dItemNo_COLLECT_MAP_61_e
    0x00, // dItemNo_COLLECT_MAP_60_e
    0x00, // dItemNo_COLLECT_MAP_59_e
    0x00, // dItemNo_COLLECT_MAP_58_e
    0x00, // dItemNo_COLLECT_MAP_57_e
    0x00, // dItemNo_COLLECT_MAP_56_e
    0x00, // dItemNo_COLLECT_MAP_55_e
    0x00, // dItemNo_COLLECT_MAP_54_e
    0x00, // dItemNo_COLLECT_MAP_53_e
    0x00, // dItemNo_COLLECT_MAP_52_e
    0x00, // dItemNo_COLLECT_MAP_51_e
    0x00, // dItemNo_COLLECT_MAP_50_e
    0x00, // dItemNo_COLLECT_MAP_49_e
    0x00, // dItemNo_COLLECT_MAP_48_e
    0x00, // dItemNo_COLLECT_MAP_47_e
    0x00, // dItemNo_COLLECT_MAP_46_e
    0x00, // dItemNo_COLLECT_MAP_45_e
    0x00, // dItemNo_COLLECT_MAP_44_e
    0x00, // dItemNo_COLLECT_MAP_43_e
    0x00, // dItemNo_COLLECT_MAP_42_e
    0x00, // dItemNo_COLLECT_MAP_41_e
    0x00, // dItemNo_COLLECT_MAP_40_e
    0x00, // dItemNo_COLLECT_MAP_39_e
    0x00, // dItemNo_COLLECT_MAP_38_e
    0x00, // dItemNo_COLLECT_MAP_37_e
    0x00, // dItemNo_COLLECT_MAP_36_e
    0x00, // dItemNo_COLLECT_MAP_35_e
    0x00, // dItemNo_COLLECT_MAP_34_e
    0x00, // dItemNo_COLLECT_MAP_33_e
    0x00, // dItemNo_COLLECT_MAP_32_e
    0x00, // dItemNo_COLLECT_MAP_31_e
    0x00, // dItemNo_COLLECT_MAP_30_e
    0x00, // dItemNo_COLLECT_MAP_29_e
    0x00, // dItemNo_COLLECT_MAP_28_e
    0x00, // dItemNo_COLLECT_MAP_27_e
    0x00, // dItemNo_COLLECT_MAP_26_e
    0x00, // dItemNo_COLLECT_MAP_25_e
    0x00, // dItemNo_COLLECT_MAP_24_e
    0x00, // dItemNo_COLLECT_MAP_23_e
    0x00, // dItemNo_COLLECT_MAP_22_e
    0x00, // dItemNo_COLLECT_MAP_21_e
    0x00, // dItemNo_COLLECT_MAP_20_e
    0x00, // dItemNo_COLLECT_MAP_19_e
    0x00, // dItemNo_COLLECT_MAP_18_e
    0x00, // dItemNo_COLLECT_MAP_17_e
    0x00, // dItemNo_COLLECT_MAP_16_e
    0x00, // dItemNo_COLLECT_MAP_15_e
    0x00, // dItemNo_COLLECT_MAP_14_e
    0x00, // dItemNo_COLLECT_MAP_13_e
    0x00, // dItemNo_COLLECT_MAP_12_e
    0x00, // dItemNo_COLLECT_MAP_11_e
    0x00, // dItemNo_COLLECT_MAP_10_e
    0x00, // dItemNo_COLLECT_MAP_09_e
    0x00, // dItemNo_COLLECT_MAP_08_e
    0x00, // dItemNo_COLLECT_MAP_07_e
    0x00, // dItemNo_COLLECT_MAP_06_e
    0x00, // dItemNo_COLLECT_MAP_05_e
    0x00, // dItemNo_COLLECT_MAP_04_e
    0x00, // dItemNo_COLLECT_MAP_03_e
    0x00, // dItemNo_COLLECT_MAP_02_e
    0x00, // dItemNo_COLLECT_MAP_01_e
    0x04, // dItemNo_NONE_e
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
        mpEmitters[0] = dComIfGp_particle_set(dPa_name::ID_IT_JN_GETITEM_FLASH_L00, &current.pos, &angle);
    case 1:
        mpEmitters[1] = dComIfGp_particle_set(dPa_name::ID_IT_JN_GETITEM_FLASH_S00, &current.pos, &angle);
    case 2:
        mpEmitters[2] = dComIfGp_particle_set(dPa_name::ID_IT_JN_GETITEM_HALO00, &current.pos, &angle);
    case 3:
        mpEmitters[3] = dComIfGp_particle_set(dPa_name::ID_IT_JN_GETITEM_STAR00, &current.pos, &angle);
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
    // Fakematch? Just angleY needs to be const to match the demo build. No effect on retail.
    const s16 angleY = dCam_getAngleY(dComIfGp_getCamera(0));
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
    case dItemNo_EMPTY_BSHIP_e:
    case dItemNo_EMPTY_BOTTLE_e:
    case dItemNo_RED_POTION_e:
    case dItemNo_GREEN_POTION_e:
    case dItemNo_BLUE_POTION_e:
    case dItemNo_HALF_SOUP_BOTTLE_e:
    case dItemNo_SOUP_BOTTLE_e:
    case dItemNo_WATER_BOTTLE_e:
    case dItemNo_FAIRY_BOTTLE_e:
    case dItemNo_FIREFLY_BOTTLE_e:
    case dItemNo_FOREST_WATER_e:
    case dItemNo_UNK_BOTTLE_5A_e:
    case dItemNo_UNK_BOTTLE_5B_e:
    case dItemNo_UNK_BOTTLE_5C_e:
    case dItemNo_UNK_BOTTLE_5D_e:
    case dItemNo_UNK_BOTTLE_5E_e:
    case dItemNo_UNK_BOTTLE_5F_e:
    case dItemNo_UNK_BOTTLE_60_e:
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
    if (isBomb(m_itemNo) || m_itemNo == dItemNo_BOMB_BAG_e || m_itemNo == dItemNo_SKULL_HAMMER_e || m_itemNo == dItemNo_SMALL_KEY_e) {
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
    fopAcM_ct(this, daDitem_c);
    
    m_itemNo = daDitem_prm::getNo(this);
    
    char* arcName = dItem_data::getArcname(m_itemNo);
    if (dItem_data::getBmdIdx(m_itemNo) == -1 || arcName == NULL) {
        m_itemNo = dItemNo_GREEN_RUPEE_e;
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
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Demo_Item_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daDitem_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Demo_Item_e,
    /* Actor SubMtd */ &l_daDitem_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
