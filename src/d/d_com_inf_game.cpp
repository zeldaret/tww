/**
 * d_com_inf_game.cpp
 * Game - Shared Runtime Data ("Common Info Game")
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_com_inf_game.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "string.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_com_lib_game.h"
#include "d/d_demo.h"
#include "d/d_flower.h"
#include "d/d_grass.h"
#include "d/d_item_data.h"
#include "d/d_magma.h"
#include "d/d_particle.h"
#include "d/d_procname.h"
#include "d/d_tree.h"
#include "d/d_wood.h"
#include "f_op/f_op_scene_mng.h"
#include "m_Do/m_Do_Reset.h"
#include "m_Do/m_Do_audio.h"
#include "d/actor/d_a_arrow.h"
#include "d/actor/d_a_ship.h"

dComIfG_inf_c g_dComIfG_gameInfo;

GXColor g_clearColor      = {0x00, 0x00, 0x00, 0x00};
GXColor g_blackColor      = {0x00, 0x00, 0x00, 0xFF};
GXColor g_whiteColor      = {0xFF, 0xFF, 0xFF, 0xFF};
GXColor g_saftyWhiteColor = {0xA0, 0xA0, 0xA0, 0xFF};

/* 80052134-800521A4       .text ct__14dComIfG_play_cFv */
#if VERSION <= VERSION_JPN
dComIfG_play_c::dComIfG_play_c()
#else
void dComIfG_play_c::ct()
#endif
{
    mDlstWindowNum = 0;
    mParticle = NULL;
    mDemo = NULL;
    mpMagmaPacket = NULL;
    mpGrassPacket = NULL;
    mpTreePacket = NULL;
    mpWoodPacket = NULL;
    mpFlowerPacket = NULL;
    mShipId = 0xFF;
    mShipRoomId = 0xFF;
    mIkadaShipBeforeRoomId = 0xFF;
    mIkadaShipId = 0xFF;
    mIkadaLinkPos.set(0.0f, 0.0f, 0.0f);
    mLkDArcIdx = -1;

    init();
}

/* 800521A4-800521D4       .text init__14dComIfG_play_cFv */
void dComIfG_play_c::init() {
    for (int i = 0; i < ARRAY_SIZE(mPlayerInfo); i++) {
        mPlayerInfo[i].mpPlayer = NULL;
        mPlayerInfo[i].mCameraID = -1;
    }

    for (int i = 0; i < ARRAY_SIZE(mpPlayerPtr); i++) {
        mpPlayerPtr[i] = NULL;
    }
}

/* 800521D4-80052400       .text itemInit__14dComIfG_play_cFv */
void dComIfG_play_c::itemInit() {
    field_0x48b8 = 0.0f;
    mItemLifeCount = 0.0f;
    mItemRupeeCount = 0;
    mAirMeter = 0;
    mItemTimeMax = 0;
    mNpcNameMessageID = 0;
    mItemNameMessageID = 0;
    mItemKeyNumCount = 0;
    mItemMaxLifeCount = 0;
    mItemMagicCount = 0;
    field_0x48da = 0;
    mItemMaxMagicCount = 0;
    field_0x48de = 0;
    mItemArrowNumCount = 0;
    field_0x48e2 = 0;
    mItemBombNumCount = 0;
    field_0x48e6 = 0;

    for (int i = 0; i < 4; i++) {
    }

    mMsgCountNumber = 0;
    mMsgSetNumber = 0;
    mMessageRupee = 0;
    mAuctionRupee = 0;
    mAuctionGauge = 0;
    mItemTimer = 0;
    mItemNowLife = 0;
    mItemNowRupee = 0;
    mItemSwimTimerStatus = 0;
    field_0x4929 = 0;
    mMesgStatus = 0;
    mScopeMesgStatus = 0;
    field_0x492c = 0;
    mRStatus = 0;
    mAStatus = 0;
    mDoStatus = 0;
    mRStatusForce = 0;
    mAStatusForce = 0;
    mDoStatusForce = 0;

    for (int i = 0; i < ARRAY_SIZE(mSelectItem); i++) {
        mSelectItem[i] = 0;
        mSelectEquip[i] = 0;
    }

    mMesgAnime = 0;
    mMesgAnimeTagInfo = 0;
    mItemSlot = 0;
    mItemNo = 0;
    field_0x493f = 0;
    field_0x4940 = 0;
    mDirection = 0;
    mButtonMode = 0;

    if (dComIfGs_checkGetItem(dItem_TELESCOPE_e)) {
        field_0x4943 = 0;
    } else {
        field_0x4943 = 0x15;
    }

    field_0x4944 = 7;
    mScopeType = 0;
    mOperateWind = 0;
    mMetronome = false;
    mMesgSendButton = 0;
    mMesgCancelButton = 0;

    for (int i = 0; i < ARRAY_SIZE(field_0x494a); i++) {
        field_0x494a[i] = 0;
    }

    mMelodyNum = 0;
    mFmapOpen = false;
    field_0x4952 = 0;
    field_0x4953 = 0;
    field_0x4954 = 0;
    mStartItemTimer = false;
    mFwaterTimer = 0;
    mPlacenameIndex = 0;
    mPlacenameState = 0;
    mGameoverStatus = 0;
    mMenuCollect = false;
    mPictureFlag = 0;
    mPictureResult = 0;
    mPictureResultDetail = 0;
    mPictureStatus = 0;
    field_0x495f = 0;
    mPictureFormat = 0;
    field_0x4961 = 0;
    mHeapLockFlag = 0;
    field_0x4965 = 0;

    strcpy(mInputPassword, "\0");

    mMesgBgm = 0;
    field_0x4978 = 0;
    m2dShow = 0;
    field_0x497a = 0;
#if VERSION > VERSION_DEMO
    mNowVibration = dComIfGs_getOptVibration();
    daArrow_c::setKeepType(daArrow_c::TYPE_NORMAL);
    mMesgCamInfo.mID = 0;
    mMesgCamInfo.mBasicID = 0;

    for (int i = 0; i < ARRAY_SIZE(mMesgCamInfo.mActor); i++) {
        mMesgCamInfo.mActor[i] = 0;
    }
#endif
}

/* 80052400-8005286C       .text getLayerNo__14dComIfG_play_cFi */
int dComIfG_play_c::getLayerNo(int i_roomNo) {
    int stageLayer = dComIfGp_getStartStageLayer();
    if (stageLayer < 0) {
        int hour = dKy_getdaytime_hour();
        int layer = dKy_checkEventNightStop() ? 1 :
                    hour >= 6 && hour < 18 ? 0 : 1;

        if (strcmp(dComIfGp_getStartStageName(), "sea") == 0) {
            if (i_roomNo == dIsleRoom_OutsetIsland_e) {
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520)) {
                    return layer | 4;
                } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E20)) {
                    return layer | 2;
                } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0101)) {
                    return 9;
                }
            } else if (i_roomNo == dIsleRoom_WindfallIsland_e) {
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D01)) {
                    return layer | 4;
                } else if (dKy_checkEventNightStop()) {
                    return layer | 2;
                }
            } else if (i_roomNo == dIsleRoom_ForsakenFortress_e) {
                return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1820) ? 3 : 1;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "A_mori") == 0) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::MET_KORL)) {
                return layer | 2;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "Asoko") == 0) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520)) {
                return layer | 2;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "Hyrule") == 0) {
            if (dComIfGs_getTriforceNum() == 8) {
                return layer | 4;
            } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3280)) {
                return layer | 2;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "Hyroom") == 0) {
            if (dComIfGs_getTriforceNum() == 8 && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C01)) {
                return layer | 4;
            } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3280)) {
                return layer | 2;
            } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3B40)) {
                return layer | 6;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "kenroom") == 0) {
#if VERSION <= VERSION_JPN
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C01)) {
#else
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C01) ||
                (dComIfGs_isEventBit(dSv_event_flag_c::COLORS_IN_HYRULE) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_3280)))
            {
#endif
                return layer | 6;
            } else if (dComIfGs_getTriforceNum() == 8) {
                return layer | 4;
            } else if (dComIfGs_isEventBit(VERSION_SELECT(dSv_event_flag_c::UNK_3280, dSv_event_flag_c::UNK_3280, dSv_event_flag_c::COLORS_IN_HYRULE, dSv_event_flag_c::COLORS_IN_HYRULE))) {
                return layer | 2;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "M2tower") == 0) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D01)) {
                return layer | 2;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "GanonK") == 0) {
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3B02)) {
                return 8;
            }
        } else if (strcmp(dComIfGp_getStartStageName(), "GTower") == 0) {
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_4002)) {
                return 8;
            }
        }

        return layer;
    }

    return stageLayer;
}

/* 8005286C-800528F4       .text createParticle__14dComIfG_play_cFv */
void dComIfG_play_c::createParticle() {
    mParticle = new dPa_control_c();

    JUT_ASSERT(VERSION_SELECT(358, 358, 360, 360), mParticle != NULL);
}

/* 800528F4-8005297C       .text createDemo__14dComIfG_play_cFv */
void dComIfG_play_c::createDemo() {
    mDemo = new dDemo_manager_c();

    JUT_ASSERT(VERSION_SELECT(388, 388, 390, 390), mDemo != NULL);
}

/* 8005297C-800529B8       .text removeDemo__14dComIfG_play_cFv */
void dComIfG_play_c::removeDemo() {
    delete mDemo;
    mDemo = NULL;
}

/* 800529B8-800529DC       .text executeEvtManager__14dComIfG_play_cFv */
void dComIfG_play_c::executeEvtManager() {
    mEvtManager.runProc();
}

/* 800529DC-80052A30       .text createMagma__14dComIfG_play_cFv */
dMagma_packet_c* dComIfG_play_c::createMagma() {
    if (mpMagmaPacket == NULL) {
        mpMagmaPacket = new dMagma_packet_c();
    }

    return mpMagmaPacket;
}

/* 80052A30-80052A84       .text removeMagma__14dComIfG_play_cFv */
void dComIfG_play_c::removeMagma() {
    if (mpMagmaPacket != NULL) {
        delete mpMagmaPacket;
        mpMagmaPacket = NULL;
    }
}

/* 80052A84-80052AB0       .text executeMagma__14dComIfG_play_cFv */
void dComIfG_play_c::executeMagma() {
    if (mpMagmaPacket != NULL) {
        mpMagmaPacket->calc();
    }
}

/* 80052AB0-80052ADC       .text drawMagma__14dComIfG_play_cFv */
void dComIfG_play_c::drawMagma() {
    if (mpMagmaPacket != NULL) {
        mpMagmaPacket->update();
    }
}

/* 80052ADC-80052B34       .text createGrass__14dComIfG_play_cFv */
dGrass_packet_c* dComIfG_play_c::createGrass() {
    if (mpGrassPacket == NULL) {
        mpGrassPacket = new dGrass_packet_c();
    }

    return mpGrassPacket;
}

/* 80052B34-80052B88       .text removeGrass__14dComIfG_play_cFv */
void dComIfG_play_c::removeGrass() {
    if (mpGrassPacket != NULL) {
        delete mpGrassPacket;
        mpGrassPacket = NULL;
    }
}

/* 80052B88-80052C0C       .text __dt__15dGrass_packet_cFv */
dGrass_packet_c::~dGrass_packet_c() {}

/* 80052C0C-80052C48       .text __dt__13dGrass_data_cFv */
dGrass_data_c::~dGrass_data_c() {}

/* 80052C48-80052C74       .text executeGrass__14dComIfG_play_cFv */
void dComIfG_play_c::executeGrass() {
    if (mpGrassPacket != NULL) {
        mpGrassPacket->calc();
    }
}

/* 80052C74-80052CA0       .text drawGrass__14dComIfG_play_cFv */
void dComIfG_play_c::drawGrass() {
    if (mpGrassPacket != NULL) {
        mpGrassPacket->update();
    }
}

/* 80052CA0-80052CF4       .text createFlower__14dComIfG_play_cFv */
dFlower_packet_c* dComIfG_play_c::createFlower() {
    if (mpFlowerPacket == NULL) {
        mpFlowerPacket = new dFlower_packet_c();
    }

    return mpFlowerPacket;
}

/* 80052CF4-80052D48       .text removeFlower__14dComIfG_play_cFv */
void dComIfG_play_c::removeFlower() {
    if (mpFlowerPacket != NULL) {
        delete mpFlowerPacket;
        mpFlowerPacket = NULL;
    }
}

/* 80052D48-80052DCC       .text __dt__16dFlower_packet_cFv */
dFlower_packet_c::~dFlower_packet_c() {}

/* 80052DCC-80052E08       .text __dt__14dFlower_data_cFv */
dFlower_data_c::~dFlower_data_c() {}

/* 80052E08-80052E34       .text executeFlower__14dComIfG_play_cFv */
void dComIfG_play_c::executeFlower() {
    if (mpFlowerPacket != NULL) {
        mpFlowerPacket->calc();
    }
}

/* 80052E34-80052E60       .text drawFlower__14dComIfG_play_cFv */
void dComIfG_play_c::drawFlower() {
    if (mpFlowerPacket != NULL) {
        mpFlowerPacket->update();
    }
}

/* 80052E60-80052EB4       .text createTree__14dComIfG_play_cFv */
dTree_packet_c* dComIfG_play_c::createTree() {
    if (mpTreePacket == NULL) {
        mpTreePacket = new dTree_packet_c();
    }

    return mpTreePacket;
}

/* 80052EB4-80052F08       .text removeTree__14dComIfG_play_cFv */
void dComIfG_play_c::removeTree() {
    if (mpTreePacket != NULL) {
        delete mpTreePacket;
        mpTreePacket = NULL;
    }
}

/* 80052F08-80052FA4       .text __dt__14dTree_packet_cFv */
dTree_packet_c::~dTree_packet_c() {}

/* 80052FA4-80052FE0       .text __dt__12dTree_data_cFv */
dTree_data_c::~dTree_data_c() {}

/* 80052FE0-8005301C       .text __dt__11dTree_anm_cFv */
dTree_anm_c::~dTree_anm_c() {}

/* 8005301C-80053048       .text executeTree__14dComIfG_play_cFv */
void dComIfG_play_c::executeTree() {
    if (mpTreePacket != NULL) {
        mpTreePacket->calc();
    }
}

/* 80053048-80053074       .text drawTree__14dComIfG_play_cFv */
void dComIfG_play_c::drawTree() {
    if (mpTreePacket != NULL) {
        mpTreePacket->update();
    }
}

/* 80053074-800530CC       .text createWood__14dComIfG_play_cFv */
dWood::Packet_c* dComIfG_play_c::createWood() {
    if (mpWoodPacket == NULL) {
        mpWoodPacket = new dWood::Packet_c();
    }

    return mpWoodPacket;
}

/* 800530CC-80053120       .text removeWood__14dComIfG_play_cFv */
void dComIfG_play_c::removeWood() {
    if (mpWoodPacket != NULL) {
        delete mpWoodPacket;
        mpWoodPacket = NULL;
    }
}

/* 80053120-8005314C       .text executeWood__14dComIfG_play_cFv */
void dComIfG_play_c::executeWood() {
    if (mpWoodPacket != NULL) {
        mpWoodPacket->calc();
    }
}

/* 8005314C-80053178       .text drawWood__14dComIfG_play_cFv */
void dComIfG_play_c::drawWood() {
    if (mpWoodPacket != NULL) {
        mpWoodPacket->update();
    }
}

#if VERSION <= VERSION_JPN
dComIfG_inf_c::dComIfG_inf_c() {
    mBrightness = 0xFF;
}
#else
/* 80053178-800531A8       .text ct__13dComIfG_inf_cFv */
void dComIfG_inf_c::ct() {
    mBrightness = 0xFF;
    play.ct();
}
#endif

/* 800531A8-8005326C       .text dComIfG_changeOpeningScene__FP11scene_classs */
int dComIfG_changeOpeningScene(scene_class* i_scene, s16 i_procName) {
    dComIfGp_offEnableNextStage();

    dComIfGp_setNextStage("sea_T", 0, 44, 0);
    mDoAud_setSceneName(dComIfGp_getNextStageName(), dComIfGp_getNextStageRoomNo(),
                        dComIfGp_getNextStageLayer());
    dComIfGs_setRestartRoomParam(0);

    fopScnM_ChangeReq(i_scene, i_procName, PROC_OVERLAP0, 30);
    fopScnM_ReRequest(i_procName, 0);
    return 1;
}

/* 8005326C-800532D8       .text dComIfG_resetToOpening__FP11scene_class */
BOOL dComIfG_resetToOpening(scene_class* i_scene) {
    if (!mDoRst::isReset()) {
        return FALSE;
    }

    dComIfG_changeOpeningScene(i_scene, 8);
    mDoAud_bgmStop(30);
    mDoAud_resetProcess();
    return TRUE;
}

/* 800532D8-80053330       .text phase_1__FPc */
static cPhs_State phase_1(char* i_arcName) {
    if (dComIfG_setObjectRes(i_arcName, JKRArchive::DEFAULT_MOUNT_DIRECTION, NULL) == FALSE) {
        return cPhs_ERROR_e;
    } else {
        return cPhs_NEXT_e;
    }
}

/* 80053330-80053388       .text phase_2__FPc */
static cPhs_State phase_2(char* i_arcName) {
    int syncStatus = dComIfG_syncObjectRes(i_arcName);

    if (syncStatus < 0) {
        return cPhs_ERROR_e;
    } else if (syncStatus > 0) {
        return cPhs_INIT_e;
    } else {
        return cPhs_NEXT_e;
    }
}

/* 80053388-80053390       .text phase_3__FPc */
static cPhs_State phase_3(char* i_arcName) {
    return cPhs_COMPLEATE_e;
}

/* 80053390-800533D0       .text dComIfG_resLoad__FP30request_of_phase_process_classPCc */
cPhs_State dComIfG_resLoad(request_of_phase_process_class* i_phase, const char* i_arcName) {
    static cPhs__Handler l_method[] = {
        (cPhs__Handler)phase_1,
        (cPhs__Handler)phase_2,
        (cPhs__Handler)phase_3
    };

    if (i_phase->id == 2) {
        return cPhs_COMPLEATE_e;
    }

    return dComLbG_PhaseHandler(i_phase, l_method, (void*)i_arcName);
}

/* 800533D0-8005347C       .text dComIfG_resDelete__FP30request_of_phase_process_classPCc */
int dComIfG_resDelete(request_of_phase_process_class* i_phase, const char* i_resName) {
    JUT_ASSERT(VERSION_SELECT(1045, 1045, 1048, 1048), i_phase->id != 1);

    if (i_phase->id == 2) {
        dComIfG_deleteObjectRes(i_resName);
        i_phase->id = 0;
    }

    return 0;
}

/* 8005347C-800534C4       .text dComIfGp_getReverb__Fi */
s8 dComIfGp_getReverb(int param_0) {
    return dStage_roomRead_dt_c_GetReverbStage(*dComIfGp_getStageRoom(), param_0);
}

/* 800534C4-800535B8       .text dComIfGd_setSimpleShadow2__FP4cXyzffR13cBgS_PolyInfosfP9_GXTexObj */
int dComIfGd_setSimpleShadow2(cXyz* i_pos, f32 groundY, f32 scaleXZ, cBgS_PolyInfo& i_floorPoly,
                              s16 i_angle, f32 scaleZ, GXTexObj* i_tex) {
    if (i_floorPoly.ChkSetInfo() && -G_CM3D_F_INF != groundY) {
        cM3dGPla* plane_p =
            dComIfG_Bgsp()->GetTriPla(i_floorPoly);

        return dComIfGd_setSimpleShadow(i_pos, groundY, scaleXZ, plane_p->GetNP(), i_angle, scaleZ, i_tex);
    } else {
        return 0;
    }
}

/* 800535B8-80053678       .text dComIfGp_getShip__Fii */
dStage_Ship_dt_c* dComIfGp_getShip(int i_roomNo, int param_1) {
    dStage_roomDt_c* roomSt_p = dComIfGp_roomControl_getStatusRoomDt(i_roomNo);
    if (roomSt_p == NULL) {
        return NULL;
    }

    dStage_Ship_c* ship_p = roomSt_p->getShip();
    if (ship_p == NULL || ship_p->num <= 0 || param_1 == 0xFF) {
        return NULL;
    }

    dStage_Ship_dt_c* data_p = ship_p->m_entries;
    if (data_p == NULL) {
        return NULL;
    }

    for (int i = 0; i < ship_p->num; i++) {
        if (param_1 == data_p->field_0xe) {
            return data_p;
        }

        data_p++;
    }

    return NULL;
}

/* 80053678-80053728       .text dComIfGp_getMapTrans__FiPfPfPs */
bool dComIfGp_getMapTrans(int i_roomNo, f32* o_transX, f32* o_transY, s16* o_angle) {
    dStage_Multi_c* multi_p = dComIfGp_getMulti();
    if (multi_p == NULL) {
        return false;
    }

    dStage_Mult_info* data_p = multi_p->m_entries;
    for (int i = 0; i < multi_p->num; i++) {
        if (i_roomNo == data_p->mRoomNo) {
            *o_transX = data_p->mTransX;
            *o_transY = data_p->mTransY;
            *o_angle = data_p->mAngle;
            return true;
        }
        data_p++;
    }

    return false;
}

/* 80053728-80053778       .text dComIfGp_getRoomCamera__Fi */
stage_camera_class* dComIfGp_getRoomCamera(int i_roomNo) {
    dStage_roomDt_c* status = dComIfGp_roomControl_getStatusRoomDt(i_roomNo);

    if (status == NULL) {
        return NULL;
    }

    return status->getCamera();
}

/* 80053778-800537C8       .text dComIfGp_getRoomArrow__Fi */
stage_arrow_class* dComIfGp_getRoomArrow(int i_roomNo) {
    dStage_roomDt_c* status = dComIfGp_roomControl_getStatusRoomDt(i_roomNo);

    if (status == NULL) {
        return NULL;
    }

    return status->getArrow();
}

/* 800537C8-8005388C       .text dComIfGp_setNextStage__FPCcsScScfUliSc */
void dComIfGp_setNextStage(const char* i_stageName, s16 i_point, s8 i_roomNo, s8 i_layer,
                           f32 i_lastSpeed, u32 i_lastMode, BOOL i_setPoint, s8 i_wipe) {
    g_dComIfG_gameInfo.play.setNextStage(i_stageName, i_roomNo, i_point, i_layer, i_wipe);

    if (daPy_getPlayerLinkActorClass() != NULL) {
        daPy_lk_c* link = daPy_getPlayerLinkActorClass();

        if (link->checkEquipDragonShield()) {
            i_lastMode |= 0x8000;
        }

        i_lastMode |= link->checkTinkleShield() << 0x10;

        if (link->checkNoResetFlg1(daPy_lk_c::daPyFlg1_SOUP_POWER_UP)) {
            i_lastMode |= 0x4000;
        }
    }

    g_dComIfG_gameInfo.save.getRestart().setLastSceneInfo(i_lastSpeed, i_lastMode);
    if (i_setPoint) {
        dComIfGs_setStartPoint(i_point);
    }
}

/* 8005388C-80053918       .text dComIfGs_onStageTbox__Fii */
void dComIfGs_onStageTbox(int i_stageNo, int i_no) {
    stage_stag_info_class* stag_info = dComIfGp_getStageStagInfo();

    if (i_stageNo == dStage_stagInfo_GetSaveTbl(stag_info)) {
        dComIfGs_onTbox(i_no);
    }

    dComIfGs_onSaveTbox(i_stageNo, i_no);
}

/* 80053918-800539A8       .text dComIfGs_isStageTbox__Fii */
BOOL dComIfGs_isStageTbox(int i_stageNo, int i_no) {
    stage_stag_info_class* stag_info = dComIfGp_getStageStagInfo();

    if (i_stageNo == dStage_stagInfo_GetSaveTbl(stag_info)) {
        return dComIfGs_isTbox(i_no);
    } else {
        return dComIfGs_isSaveTbox(i_stageNo, i_no);
    }
}

/* 800539A8-80053A2C       .text dComIfGs_isStageBossEnemy__Fi */
BOOL dComIfGs_isStageBossEnemy(int i_stageNo) {
    stage_stag_info_class* stag_info = dComIfGp_getStageStagInfo();

    if (i_stageNo == dStage_stagInfo_GetSaveTbl(stag_info)) {
        return dComIfGs_isStageBossEnemy();
    } else {
        return g_dComIfG_gameInfo.save.getSavedata().getSave(i_stageNo).getBit().isStageBossEnemy();
    }
}

/* 80053A2C-80053AAC       .text dComIfGs_onStageLife__Fi */
void dComIfGs_onStageLife(int i_stageNo) {
    stage_stag_info_class* stag_info = dComIfGp_getStageStagInfo();

    if (i_stageNo == dStage_stagInfo_GetSaveTbl(stag_info)) {
        dComIfGs_onStageLife();
    }

    g_dComIfG_gameInfo.save.getSavedata().getSave(i_stageNo).getBit().onStageLife();
}

/* 80053AAC-80053B30       .text dComIfGs_isStageLife__Fi */
BOOL dComIfGs_isStageLife(int i_stageNo) {
    stage_stag_info_class* stag_info = dComIfGp_getStageStagInfo();

    if (i_stageNo == dStage_stagInfo_GetSaveTbl(stag_info)) {
        return dComIfGs_isStageLife();
    } else {
        return g_dComIfG_gameInfo.save.getSavedata().getSave(i_stageNo).getBit().isStageLife();
    }
}

/* 80053B30-80053F70       .text dComIfGs_checkGetItem__FUc */
u8 dComIfGs_checkGetItem(u8 i_itemNo) {
    u8 get_item = 0;

    switch (i_itemNo) {
    case TACT_SONG1:
        if (dComIfGs_isTact(0)) {
            get_item = 1;
        }
        break;
    case TACT_SONG2:
        if (dComIfGs_isTact(1)) {
            get_item = 1;
        }
        break;
    case TACT_SONG3:
        if (dComIfGs_isTact(2)) {
            get_item = 1;
        }
        break;
    case TACT_SONG4:
        if (dComIfGs_isTact(3)) {
            get_item = 1;
        }
        break;
    case TACT_SONG5:
        if (dComIfGs_isTact(4)) {
            get_item = 1;
        }
        break;
    case TACT_SONG6:
        if (dComIfGs_isTact(5)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE1_e:
        if (dComIfGs_isTriforce(0)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE2_e:
        if (dComIfGs_isTriforce(1)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE3_e:
        if (dComIfGs_isTriforce(2)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE4_e:
        if (dComIfGs_isTriforce(3)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE5_e:
        if (dComIfGs_isTriforce(4)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE6_e:
        if (dComIfGs_isTriforce(5)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE7_e:
        if (dComIfGs_isTriforce(6)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE8_e:
        if (dComIfGs_isTriforce(7)) {
            get_item = 1;
        }
        break;
    case dItem_PEARL_NAYRU_e:
        if (dComIfGs_isSymbol(0)) {
            get_item = 1;
        }
        break;
    case dItem_PEARL_DIN_e:
        if (dComIfGs_isSymbol(1)) {
            get_item = 1;
        }
        break;
    case dItem_PEARL_FARORE_e:
        if (dComIfGs_isSymbol(2)) {
            get_item = 1;
        }
        break;
    case dItem_PIRATES_CHARM_e:
        if (dComIfGs_isCollect(3, 0)) {
            get_item = 1;
        }
        break;
    case dItem_HEROS_CHARM_e:
        if (dComIfGs_isCollect(4, 0)) {
            get_item = 1;
        }
        break;
    default:
        for (int i = 0; i < 60; i++) {
            if (i_itemNo == dComIfGs_getItem(i)) {
                get_item++;
            }
        }

        for (int i = 0; i < 3; i++) {
            if (i_itemNo == dComIfGs_getSelectEquip(i)) {
                get_item++;
            }
        }

        if (i_itemNo >= 0xBF && i_itemNo <= dItem_NONE_e - 1 &&
            dComIfGs_isGetCollectMap(dItem_NONE_e - i_itemNo))
        {
            get_item++;
        }
        break;
    }

    return get_item;
}

/* 80053F70-80054578       .text dComIfGs_checkGetItemNum__FUc */
u8 dComIfGs_checkGetItemNum(u8 i_itemNo) {
    u8 get_item = 0;

    switch (i_itemNo) {
    case TACT_SONG1:
        if (dComIfGs_isTact(0)) {
            get_item = 1;
        }
        break;
    case TACT_SONG2:
        if (dComIfGs_isTact(1)) {
            get_item = 1;
        }
        break;
    case TACT_SONG3:
        if (dComIfGs_isTact(2)) {
            get_item = 1;
        }
        break;
    case TACT_SONG4:
        if (dComIfGs_isTact(3)) {
            get_item = 1;
        }
        break;
    case TACT_SONG5:
        if (dComIfGs_isTact(4)) {
            get_item = 1;
        }
        break;
    case TACT_SONG6:
        if (dComIfGs_isTact(5)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE1_e:
        if (dComIfGs_isTriforce(0)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE2_e:
        if (dComIfGs_isTriforce(1)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE3_e:
        if (dComIfGs_isTriforce(2)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE4_e:
        if (dComIfGs_isTriforce(3)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE5_e:
        if (dComIfGs_isTriforce(4)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE6_e:
        if (dComIfGs_isTriforce(5)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE7_e:
        if (dComIfGs_isTriforce(6)) {
            get_item = 1;
        }
        break;
    case dItem_TRIFORCE8_e:
        if (dComIfGs_isTriforce(7)) {
            get_item = 1;
        }
        break;
    case dItem_PEARL_NAYRU_e:
        if (dComIfGs_isSymbol(0)) {
            get_item = 1;
        }
        break;
    case dItem_PEARL_DIN_e:
        if (dComIfGs_isSymbol(1)) {
            get_item = 1;
        }
        break;
    case dItem_PEARL_FARORE_e:
        if (dComIfGs_isSymbol(2)) {
            get_item = 1;
        }
        break;
    case dItem_PIRATES_CHARM_e:
        if (dComIfGs_isCollect(3, 0)) {
            get_item = 1;
        }
        break;
    case dItem_HEROS_CHARM_e:
        if (dComIfGs_isCollect(4, 0)) {
            get_item = 1;
        }
        break;
    case dItem_BOW_e:
        if (dComIfGs_getItem(dInvSlot_BOW_e) != dItem_HEART_e) { // Bug?
            get_item = dComIfGs_getArrowNum();
        }
        break;
    case dItem_BOMB_BAG_e:
        if (dComIfGs_getItem(dInvSlot_BOMB_e) != dItem_HEART_e) { // Bug?
            get_item = dComIfGs_getBombNum();
        }
        break;
    case dItem_SKULL_NECKLACE_e:
        for (int i = 0; i < 8; i++) {
            if (dComIfGs_getBeast(i) == dItem_SKULL_NECKLACE_e) {
                get_item = dComIfGs_getBeastNum(0);
            }
        }
        break;
    case dItem_BOKOBABA_SEED_e:
        for (int i = 0; i < 8; i++) {
            if (dComIfGs_getBeast(i) == dItem_BOKOBABA_SEED_e) {
                get_item = dComIfGs_getBeastNum(1);
            }
        }
        break;
    case dItem_GOLDEN_FEATHER_e:
        for (int i = 0; i < 8; i++) {
            if (dComIfGs_getBeast(i) == dItem_GOLDEN_FEATHER_e) {
                get_item = dComIfGs_getBeastNum(2);
            }
        }
        break;
    case BOKO_BELT:
        for (int i = 0; i < 8; i++) {
            if (dComIfGs_getBeast(i) == BOKO_BELT) {
                get_item = dComIfGs_getBeastNum(3);
            }
        }
        break;
    case dItem_RED_JELLY_e:
        for (int i = 0; i < 8; i++) {
            if (dComIfGs_getBeast(i) == dItem_RED_JELLY_e) {
                get_item = dComIfGs_getBeastNum(4);
            }
        }
        break;
    case dItem_GREEN_JELLY_e:
        for (int i = 0; i < 8; i++) {
            if (dComIfGs_getBeast(i) == dItem_GREEN_JELLY_e) {
                get_item = dComIfGs_getBeastNum(5);
            }
        }
        break;
    case dItem_BLUE_JELLY_e:
        for (int i = 0; i < 8; i++) {
            if (dComIfGs_getBeast(i) == dItem_BLUE_JELLY_e) {
                get_item = dComIfGs_getBeastNum(6);
            }
        }
        break;
    case dItem_JOY_PENDANT_e:
        for (int i = 0; i < 8; i++) {
            if (dComIfGs_getBeast(i) == dItem_JOY_PENDANT_e) {
                get_item = dComIfGs_getBeastNum(7);
            }
        }
        break;
    default:
        for (int i = 0; i < 60; i++) {
            if (i_itemNo == dComIfGs_getItem(i)) {
                get_item = 1;
            }
        }

        for (int i = 0; i < 3; i++) {
            if (i_itemNo == dComIfGs_getSelectEquip(i)) {
                get_item = 1;
            }
        }

        if (i_itemNo >= 0xBF && i_itemNo <= dItem_NONE_e - 1 &&
            dComIfGs_isGetCollectMap(dItem_NONE_e - i_itemNo))
        {
            get_item = 1;
        }
        break;
    }

    return get_item;
}

/* 80054578-8005468C       .text dComIfGd_setShadow__FUlScP8J3DModelP4cXyzffffR13cBgS_PolyInfoP12dKy_tevstr_csfP9_GXTexObj */
int dComIfGd_setShadow(u32 id, s8 shouldFade, J3DModel* pModel, cXyz* pPos, f32 casterSize, f32 scaleXZ,
                       f32 y, f32 groundY, cBgS_PolyInfo& pFloorPoly, dKy_tevstr_c* pTevStr,
                       s16 rotY, f32 scaleZ, GXTexObj* pTexObj) {
    if (groundY <= -G_CM3D_F_INF) {
        return 0;
    }

    int sid = dComIfGd_setRealShadow2(id, shouldFade, pModel, pPos, casterSize, y - groundY, pTevStr);
    if (sid == 0) {
        cXyz pos(pPos->x, y, pPos->z);
        dComIfGd_setSimpleShadow2(&pos, groundY, scaleXZ, pFloorPoly, rotY, scaleZ, pTexObj);
    }
    return sid;
}

static void dummy() {
    OSReport("0 <= cam_id && cam_id < mapc->num");
    OSReport("0 <= arrow_id && arrow_id < mapa->num");
    OSReport("0 <= room_cam_id && room_cam_id < pcam->num");
    OSReport("0 <= arrow_id && arrow_id < parr->num");
}

/* 8005468C-800547BC       .text getSceneList__Fi */
stage_scls_info_class* getSceneList(int i_no) {
    stage_scls_info_dummy_class* sclsInfo = dComIfGp_getStage().getSclsInfo();
    JUT_ASSERT(VERSION_SELECT(2129, 2129, 2132, 2132), sclsInfo != NULL);

    JUT_ASSERT(VERSION_SELECT(2131, 2131, 2134, 2134), 0 <= i_no && i_no < sclsInfo->num);

    stage_scls_info_class* sclsData = sclsInfo->m_entries;
    JUT_ASSERT(VERSION_SELECT(2133, 2133, 2136, 2136), sclsData != NULL);

    return &sclsData[i_no];
}

/* 800547BC-80054870       .text dComIfGd_getMeshSceneList__FR3Vec */
stage_scls_info_class* dComIfGd_getMeshSceneList(Vec& vec) {
    s32 x = (s32)((vec.x + 350000.0f) * 2e-05f);
    s32 z = (s32)((vec.z + 350000.0f) * 2e-05f);
    if (x < 0) {
        x = 0;
    } else if (13 < x) {
        x = 13;
    }
    if (z < 0) {
        z = 0;
    } else if (13 < z) {
        z = 13;
    }
    return getSceneList((x & 1) + ((x >> 1) + (z >> 1) * 7) * 4 + (z & 1) * 2);
}

/* 80054870-800548FC       .text dComIfGs_checkSeaLandingEvent__FSc */
BOOL dComIfGs_checkSeaLandingEvent(s8 i_roomNo) {
    struct landing_event {
        /* 0x0 */ s8 roomNo;
        /* 0x2 */ u16 event;
    };

    static landing_event l_landingEvent[] = {
        {dIsleRoom_ForsakenFortress_e,  dSv_event_flag_c::UNK_3040},
        {dIsleRoom_GaleIsle_e,          dSv_event_flag_c::UNK_2E02},
        {dIsleRoom_DragonRoostIsland_e, dSv_event_flag_c::UNK_0902},
        {dIsleRoom_GreatfishIsle_e,     dSv_event_flag_c::ENDLESS_NIGHT},
        {dIsleRoom_ForestHaven_e,       dSv_event_flag_c::UNK_0A20},
        {dIsleRoom_HeadstoneIsland_e,   dSv_event_flag_c::UNK_2E04},
    };

    landing_event* event_check = l_landingEvent;

    for (u32 i = 0; i < ARRAY_SIZE(l_landingEvent); i++) {
        if (i_roomNo == event_check->roomNo && !dComIfGs_isEventBit(event_check->event)) {
            return FALSE;
        }

        event_check++;
    }

    return TRUE;
}

/* 800548FC-80054C70       .text dComIfGs_setGameStartStage__Fv */
void dComIfGs_setGameStartStage() {
    struct check_data {
        /* 0x0 */ u8 mbHasEvent;
        /* 0x2 */ u16 mEvent;
        /* 0x4 */ char mStage[8];
        /* 0xC */ s8 mRoomNo;
        /* 0xD */ u8 mStartCode;
    };

    static check_data l_checkData[] = {
        {true,  dSv_event_flag_c::RODE_KORL, "",        0,                          0},
        {true,  dSv_event_flag_c::MET_KORL,  "sea",     dIsleRoom_WindfallIsland_e, 128},
        {true,  dSv_event_flag_c::UNK_0801,  "MajyuE",  0,                          0},
        {true,  dSv_event_flag_c::UNK_0808,  "MajyuE",  0,                          18},
        {true,  dSv_event_flag_c::UNK_2401,  "A_umikz", 0,                          204},
        {false, 0,                           "sea",     dIsleRoom_OutsetIsland_e,   128},
    };

    check_data* data_p = l_checkData;
    for (u32 i = 0; i < ARRAY_SIZE(l_checkData)-1; i++) {
        if (data_p->mbHasEvent == true && dComIfGs_isEventBit(data_p->mEvent)) {
            break;
        }

        data_p++;
    }

    char stage_name[8];
    s8 room_no;
    u8 point;

    if (strcmp(data_p->mStage, "") != 0) {
        strcpy(stage_name, data_p->mStage);
        room_no = data_p->mRoomNo;
        point = data_p->mStartCode;
    } else {
        u32 stage_type = dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo());
        int stageNo = dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo());
        BOOL isNot_PShip = strcmp(dComIfGp_getStartStageName(), "PShip");

        if (!isNot_PShip) {
            strcpy(stage_name, "sea");
            room_no = dComIfGs_getEventReg(dSv_event_flag_c::UNK_C3FF);
            point = dComIfGs_getEventReg(dSv_event_flag_c::UNK_85FF);
            dKy_set_nexttime(120.0f);
        } else if (stage_type == dStageType_SEA_e) {
            daPy_lk_c* player_p = daPy_getPlayerLinkActorClass();
            point = player_p->mRestartPoint;

            room_no = fopAcM_GetRoomNo(player_p);

            if (fopAcM_GetRoomNo(player_p) >= 0 && point != 0xFF && dComIfGs_checkSeaLandingEvent(room_no)) {
                strcpy(stage_name, dComIfGp_getStartStageName());
            } else {
                stage_scls_info_class* scls_p;
                if (dComIfGp_getShipActor() != NULL) {
                    scls_p = dComIfGd_getMeshSceneList(dComIfGp_getShipActor()->current.pos);
                } else {
                    scls_p = dComIfGd_getMeshSceneList(player_p->current.pos);
                }

                strcpy(stage_name, scls_p->mStage);
                room_no = scls_p->mRoom;
                point = scls_p->mStart;
            }
        } else if (stage_type == dStageType_DUNGEON_e || stage_type == dStageType_MINIBOSS_e ||
                   stage_type == dStageType_BOSS_e || stage_type == dStageType_UNKNOWN_8_e ||
                   stageNo == dSv_save_c::STAGE_HYRULE)
        {
            stage_scls_info_class* scls_p = getSceneList(0);
            strcpy(stage_name, scls_p->mStage);
            room_no = scls_p->mRoom;
            point = scls_p->mStart;
        } else if (stageNo == dSv_save_c::STAGE_SHIP) {
            cXyz ikada_pos;
            dComIfGp_getIkadaShipBeforePos(&ikada_pos);

            stage_scls_info_class* scls_p = dComIfGd_getMeshSceneList(ikada_pos);
            strcpy(stage_name, scls_p->mStage);
            room_no = scls_p->mRoom;
            point = scls_p->mStart;
        } else if (stageNo == dSv_save_c::STAGE_MISC || stageNo == dSv_save_c::STAGE_SUBDUNGEON ||
                   stageNo == dSv_save_c::STAGE_SUBDUNGEON_NEW)
        {
            strcpy(stage_name, "sea");

            stage_map_info_class* mapInfo = dComIfGp_getStage().getMapInfo();
            JUT_ASSERT(VERSION_SELECT(2359, 2359, 2362, 2362), mapInfo != NULL);

            room_no = 4 + dStage_mapInfo_GetOceanX(mapInfo) + ((dStage_mapInfo_GetOceanZ(mapInfo) + 3) * 7);
            point = 0;
        } else {
            strcpy(stage_name, "sea");
            room_no = dIsleRoom_WindfallIsland_e;
            point = 0;
        }
    }

    g_dComIfG_gameInfo.save.getPlayer().getPlayerReturnPlace().set(stage_name, room_no, point);
}

/* 80054C70-80054CC0       .text dComIfGs_gameStart__Fv */
void dComIfGs_gameStart() {
    dComIfGp_offEnableNextStage();

    s8 roomNo = g_dComIfG_gameInfo.save.getPlayer().getPlayerReturnPlace().getRoomNo();
    s16 point = g_dComIfG_gameInfo.save.getPlayer().getPlayerReturnPlace().getPoint();
    char* name = g_dComIfG_gameInfo.save.getPlayer().getPlayerReturnPlace().getName();
    dComIfGp_setNextStage(name, point, roomNo);
}

/* 80054CC0-80054E9C       .text dComIfGs_copyPlayerRecollectionData__Fv */
void dComIfGs_copyPlayerRecollectionData() {
    s32 tbl;
    dSv_player_status_c_c stts;

    if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_BOSS_e) {
        if (dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo()) == dSv_save_c::STAGE_DRC)
            tbl = 0;
        else if (dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo()) == dSv_save_c::STAGE_FW)
            tbl = 1;
        else if (dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo()) == dSv_save_c::STAGE_ET)
            tbl = 2;
        else if (dStage_stagInfo_GetSaveTbl(dComIfGp_getStageStagInfo()) == dSv_save_c::STAGE_WT)
            tbl = 3;
        else
            return;
    } else {
        return;
    }

    u8* buffer = (u8*)&stts;
    memcpy(buffer + offsetof(dSv_player_status_c_c, mRecollectStatusA),       dComIfGs_getpPlayerStatusA(),             sizeof(stts.mRecollectStatusA));
    memcpy(buffer + offsetof(dSv_player_status_c_c, mRecollectItem),          dComIfGs_getpItem(),                      sizeof(stts.mRecollectItem));
    memcpy(buffer + offsetof(dSv_player_status_c_c, mRecollectItemRecord),    &dComIfGs_getpItemRecord()->mItemRecord2, sizeof(stts.mRecollectItemRecord));
    memcpy(buffer + offsetof(dSv_player_status_c_c, mRecollectItemMax),       &dComIfGs_getpItemMax()->mItemMax2,       sizeof(stts.mRecollectItemMax));
    memcpy(buffer + offsetof(dSv_player_status_c_c, mRecollectBagItem),       dComIfGs_getpBagItem(),                   sizeof(stts.mRecollectBagItem));
    memcpy(buffer + offsetof(dSv_player_status_c_c, mRecollectBagItemRecord), dComIfGs_getpBagItemRecord(),             sizeof(stts.mRecollectBagItemRecord));
    memcpy(buffer + offsetof(dSv_player_status_c_c, mRecollectCollect),       dComIfGs_getpCollect(),                   sizeof(stts.mRecollectCollect));
    memcpy(dComIfGs_getpPlayerStatusC(tbl), &stts, sizeof(stts));
}

/* 80054E9C-80055318       .text dComIfGs_setPlayerRecollectionData__Fv */
void dComIfGs_setPlayerRecollectionData() {
#if VERSION > VERSION_JPN
    daArrow_c::setKeepType(daArrow_c::TYPE_NORMAL);
#endif

    u32 tbl;
    if (strcmp(dComIfGp_getStartStageName(), "Xboss0") == 0 && dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D80) != 0) {
        tbl = 0;
        dComIfGp_setPlayerInfoBufferStageNo(1);
    } else if (strcmp(dComIfGp_getStartStageName(), "Xboss1") == 0 && dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D40) != 0) {
        tbl = 1;
        dComIfGp_setPlayerInfoBufferStageNo(2);
    } else if (strcmp(dComIfGp_getStartStageName(), "Xboss2") == 0 && dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D20) != 0) {
        tbl = 2;
        dComIfGp_setPlayerInfoBufferStageNo(3);
    } else if (strcmp(dComIfGp_getStartStageName(), "Xboss3") == 0 && dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D10) != 0) {
        tbl = 3;
        dComIfGp_setPlayerInfoBufferStageNo(4);
    } else {
        dComIfGs_setSelectItem(dItemBtn_X_e, dInvSlot_NONE_e);
        dComIfGs_setSelectItem(dItemBtn_Y_e, dInvSlot_NONE_e);
        dComIfGs_setSelectItem(dItemBtn_Z_e, dInvSlot_NONE_e);
        return;
    }

    if (dComIfGs_getpPlayerStatusC(tbl)->mRecollectItem.mItems[dInvSlot_TELESCOPE_e] != dItem_TELESCOPE_e) {
        dComIfGs_setSelectItem(dItemBtn_X_e, dInvSlot_NONE_e);
        dComIfGs_setSelectItem(dItemBtn_Y_e, dInvSlot_NONE_e);
        dComIfGs_setSelectItem(dItemBtn_Z_e, dInvSlot_NONE_e);
        return;
    }

    dSv_player_status_a_c tmp_sttsA;
    dSv_player_item_max_c tmp_max;
    dSv_player_item_record2_c tmp_record2;
    dSv_player_collect_c tmp_collect;
    dSv_player_item_c tmp_item;

    tmp_sttsA.mMaxLife = dComIfGs_getMaxLife();
    tmp_sttsA.mLife = dComIfGs_getLife();
    tmp_sttsA.mMaxMagic = dComIfGs_getMaxMagic();
    tmp_sttsA.mMagic = dComIfGs_getMagic();

    tmp_max.mItemMax2.mArrowNum = dComIfGs_getArrowMax();
    tmp_record2.mArrowNum = dComIfGs_getArrowNum();
    tmp_max.mItemMax2.mBombNum = dComIfGs_getBombMax();
    tmp_record2.mBombNum = dComIfGs_getBombNum();
    tmp_record2.mPictureNum = dComIfGs_getPictureNum();

    tmp_collect.mCollect[0] = dComIfGs_checkCollect(0);
    tmp_collect.mCollect[1] = dComIfGs_checkCollect(1);
    tmp_collect.mCollect[2] = dComIfGs_checkCollect(2);
    tmp_collect.mCollect[3] = dComIfGs_checkCollect(3);
    tmp_collect.mCollect[4] = dComIfGs_checkCollect(4);

    tmp_sttsA.mSelectEquip[0] = dComIfGs_getSelectEquip(0);
    tmp_sttsA.mSelectEquip[1] = dComIfGs_getSelectEquip(1);
    tmp_sttsA.mSelectEquip[2] = dComIfGs_getSelectEquip(2);
    tmp_sttsA.mSelectEquip[3] = dComIfGs_getSelectEquip(3);
    tmp_sttsA.mSelectEquip[4] = dComIfGs_getSelectEquip(4);

    tmp_item.mItems[dInvSlot_BOTTLE0_e] = dComIfGs_getItem(dInvSlot_BOTTLE0_e);
    tmp_item.mItems[dInvSlot_BOTTLE1_e] = dComIfGs_getItem(dInvSlot_BOTTLE1_e);
    tmp_item.mItems[dInvSlot_BOTTLE2_e] = dComIfGs_getItem(dInvSlot_BOTTLE2_e);
    tmp_item.mItems[dInvSlot_BOTTLE3_e] = dComIfGs_getItem(dInvSlot_BOTTLE3_e);
    tmp_item.mItems[dInvSlot_CAMERA_e]  = dComIfGs_getItem(dInvSlot_CAMERA_e);

    // TODO: This matches but could probably be cleaned up somehow.
    dSv_player_status_c_c* stts = dComIfGs_getpPlayerStatusC(tbl);
    u32 buffer = (u32)dComIfGp_getPlayerInfoBuffer();
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectStatusA)),       dComIfGs_getpPlayerStatusA(),             sizeof(stts->mRecollectStatusA));
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectItem)),          dComIfGs_getpItem(),                      sizeof(stts->mRecollectItem));
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectItemRecord)),    &dComIfGs_getpItemRecord()->mItemRecord2, sizeof(stts->mRecollectItemRecord));
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectItemMax)),       &dComIfGs_getpItemMax()->mItemMax2,       sizeof(stts->mRecollectItemMax));
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectBagItem)),       dComIfGs_getpBagItem(),                   sizeof(stts->mRecollectBagItem));
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectBagItemRecord)), dComIfGs_getpBagItemRecord(),             sizeof(stts->mRecollectBagItemRecord));
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectCollect)),       dComIfGs_getpCollect(),                   sizeof(stts->mRecollectCollect));

    memcpy(dComIfGs_getpPlayerStatusA(),             &stts->mRecollectStatusA,       sizeof(stts->mRecollectStatusA));
    memcpy(dComIfGs_getpItem(),                      &stts->mRecollectItem,          sizeof(stts->mRecollectItem));
    memcpy(&dComIfGs_getpItemRecord()->mItemRecord2, &stts->mRecollectItemRecord,    sizeof(stts->mRecollectItemRecord));
    memcpy(&dComIfGs_getpItemMax()->mItemMax2,       &stts->mRecollectItemMax,       sizeof(stts->mRecollectItemMax));
    memcpy(dComIfGs_getpBagItem(),                   &stts->mRecollectBagItem,       sizeof(stts->mRecollectBagItem));
    memcpy(dComIfGs_getpBagItemRecord(),             &stts->mRecollectBagItemRecord, sizeof(stts->mRecollectBagItemRecord));
    memcpy(dComIfGs_getpCollect(),                   &stts->mRecollectCollect,       sizeof(stts->mRecollectCollect));

    dComIfGs_setMaxLife(tmp_sttsA.mMaxLife);
    dComIfGs_setLife(tmp_sttsA.mLife);
    dComIfGs_setMaxMagic(tmp_sttsA.mMaxMagic);
    dComIfGs_setMagic(tmp_sttsA.mMagic);

    dComIfGs_setArrowMax(tmp_max.mItemMax2.mArrowNum);
    dComIfGs_setArrowNum(tmp_record2.mArrowNum);
    dComIfGs_setBombMax(tmp_max.mItemMax2.mBombNum);
    dComIfGs_setBombNum(tmp_record2.mBombNum);
    dComIfGs_setPictureNum(tmp_record2.mPictureNum);

    dComIfGs_setCollect(0, tmp_collect.mCollect[0]);
    dComIfGs_setCollect(1, tmp_collect.mCollect[1]);
    dComIfGs_setCollect(2, tmp_collect.mCollect[2]);
    dComIfGs_setCollect(3, tmp_collect.mCollect[3]);
    dComIfGs_setCollect(4, tmp_collect.mCollect[4]);

    dComIfGs_setSelectEquip(0, tmp_sttsA.mSelectEquip[0]);
    dComIfGs_setSelectEquip(1, tmp_sttsA.mSelectEquip[1]);
    dComIfGs_setSelectEquip(2, tmp_sttsA.mSelectEquip[2]);
    dComIfGs_setSelectEquip(3, tmp_sttsA.mSelectEquip[3]);
    // Potential bug: This array is only length 4, so it's reading and writing the wallet size in a non-standard way.
    // Usually the wallet size would be set via dComIfGs_setWalletSize instead.
    // TODO: Investigate this more.
    dComIfGs_setSelectEquip(4, tmp_sttsA.mSelectEquip[4]);

    dComIfGp_setSelectEquip(0, dComIfGs_getSelectEquip(0));
    dComIfGp_setSelectEquip(1, dComIfGs_getSelectEquip(1));
    dComIfGp_setSelectEquip(2, dComIfGs_getSelectEquip(2));
    dComIfGp_setSelectEquip(3, dComIfGs_getSelectEquip(3));
    // Bug: The following line sets out of bounds of dComIfG_play_c's mSelectEquip array.
    // It seems to set dComIfG_play_c's mMesgAnime value to the current wallet size value.
    // TODO: Investigate this more.
    dComIfGp_setSelectEquip(4, dComIfGs_getSelectEquip(4));

    dComIfGs_setItem(dInvSlot_BOTTLE0_e, tmp_item.mItems[dInvSlot_BOTTLE0_e]);
    dComIfGs_setItem(dInvSlot_BOTTLE1_e, tmp_item.mItems[dInvSlot_BOTTLE1_e]);
    dComIfGs_setItem(dInvSlot_BOTTLE2_e, tmp_item.mItems[dInvSlot_BOTTLE2_e]);
    dComIfGs_setItem(dInvSlot_BOTTLE3_e, tmp_item.mItems[dInvSlot_BOTTLE3_e]);
    dComIfGs_setItem(dInvSlot_CAMERA_e,  tmp_item.mItems[dInvSlot_CAMERA_e]);

    dComIfGs_setSelectItem(dItemBtn_X_e, dInvSlot_NONE_e);
    dComIfGs_setSelectItem(dItemBtn_Y_e, dInvSlot_NONE_e);
    dComIfGs_setSelectItem(dItemBtn_Z_e, dInvSlot_NONE_e);
}

/* 80055318-80055580       .text dComIfGs_revPlayerRecollectionData__Fv */
void dComIfGs_revPlayerRecollectionData() {
    if (dComIfGp_getPlayerInfoBufferStageNo() != 0) {
        dComIfGp_setPlayerInfoBufferStageNo(0);
    } else {
        return;
    }

    dSv_player_status_a_c tmp_sttsA;
    dSv_player_item_max_c tmp_max;
    dSv_player_item_record2_c tmp_record2;
    dSv_player_collect_c tmp_collect;
    dSv_player_item_c tmp_item;

    tmp_sttsA.mMaxLife = dComIfGs_getMaxLife();
    tmp_sttsA.mLife = dComIfGs_getLife();
    tmp_sttsA.mMaxMagic = dComIfGs_getMaxMagic();
    tmp_sttsA.mMagic = dComIfGs_getMagic();

    tmp_max.mItemMax2.mArrowNum = dComIfGs_getArrowMax();
    tmp_record2.mArrowNum = dComIfGs_getArrowNum();
    tmp_max.mItemMax2.mBombNum = dComIfGs_getBombMax();
    tmp_record2.mBombNum = dComIfGs_getBombNum();
    tmp_record2.mPictureNum = dComIfGs_getPictureNum();

    tmp_collect.mCollect[0] = dComIfGs_checkCollect(0);
    tmp_collect.mCollect[1] = dComIfGs_checkCollect(1);
    tmp_collect.mCollect[2] = dComIfGs_checkCollect(2);
    tmp_collect.mCollect[3] = dComIfGs_checkCollect(3);
    tmp_collect.mCollect[4] = dComIfGs_checkCollect(4);

    tmp_sttsA.mSelectEquip[0] = dComIfGs_getSelectEquip(0);
    tmp_sttsA.mSelectEquip[1] = dComIfGs_getSelectEquip(1);
    tmp_sttsA.mSelectEquip[2] = dComIfGs_getSelectEquip(2);
    tmp_sttsA.mSelectEquip[3] = dComIfGs_getSelectEquip(3);
    tmp_sttsA.mSelectEquip[4] = dComIfGs_getSelectEquip(4);

    tmp_item.mItems[dInvSlot_BOTTLE0_e] = dComIfGs_getItem(dInvSlot_BOTTLE0_e);
    tmp_item.mItems[dInvSlot_BOTTLE1_e] = dComIfGs_getItem(dInvSlot_BOTTLE1_e);
    tmp_item.mItems[dInvSlot_BOTTLE2_e] = dComIfGs_getItem(dInvSlot_BOTTLE2_e);
    tmp_item.mItems[dInvSlot_BOTTLE3_e] = dComIfGs_getItem(dInvSlot_BOTTLE3_e);
    tmp_item.mItems[dInvSlot_CAMERA_e]  = dComIfGs_getItem(dInvSlot_CAMERA_e);

    // TODO: This matches but could probably be cleaned up somehow.
    u32 buffer = (u32)dComIfGp_getPlayerInfoBuffer();
    memcpy(dComIfGs_getpPlayerStatusA(),             (void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectStatusA)),       sizeof(dSv_player_status_c_c().mRecollectStatusA));
    memcpy(dComIfGs_getpItem(),                      (void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectItem)),          sizeof(dSv_player_status_c_c().mRecollectItem));
    memcpy(&dComIfGs_getpItemRecord()->mItemRecord2, (void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectItemRecord)),    sizeof(dSv_player_status_c_c().mRecollectItemRecord));
    memcpy(&dComIfGs_getpItemMax()->mItemMax2,       (void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectItemMax)),       sizeof(dSv_player_status_c_c().mRecollectItemMax));
    memcpy(dComIfGs_getpBagItem(),                   (void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectBagItem)),       sizeof(dSv_player_status_c_c().mRecollectBagItem));
    memcpy(dComIfGs_getpBagItemRecord(),             (void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectBagItemRecord)), sizeof(dSv_player_status_c_c().mRecollectBagItemRecord));
    memcpy(dComIfGs_getpCollect(),                   (void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectCollect)),       sizeof(dSv_player_status_c_c().mRecollectCollect));

    dComIfGs_setMaxLife(tmp_sttsA.mMaxLife);
    dComIfGs_setLife(tmp_sttsA.mLife);
    dComIfGs_setMaxMagic(tmp_sttsA.mMaxMagic);
    dComIfGs_setMagic(tmp_sttsA.mMagic);

    dComIfGs_setArrowMax(tmp_max.mItemMax2.mArrowNum);
    dComIfGs_setArrowNum(tmp_record2.mArrowNum);
    dComIfGs_setBombMax(tmp_max.mItemMax2.mBombNum);
    dComIfGs_setBombNum(tmp_record2.mBombNum);
    dComIfGs_setPictureNum(tmp_record2.mPictureNum);

    dComIfGs_setCollect(0, tmp_collect.mCollect[0]);
    dComIfGs_setCollect(1, tmp_collect.mCollect[1]);
    dComIfGs_setCollect(2, tmp_collect.mCollect[2]);
    dComIfGs_setCollect(3, tmp_collect.mCollect[3]);
    dComIfGs_setCollect(4, tmp_collect.mCollect[4]);

    dComIfGs_setSelectEquip(0, tmp_sttsA.mSelectEquip[0]);
    dComIfGs_setSelectEquip(1, tmp_sttsA.mSelectEquip[1]);
    dComIfGs_setSelectEquip(2, tmp_sttsA.mSelectEquip[2]);
    dComIfGs_setSelectEquip(3, tmp_sttsA.mSelectEquip[3]);
    // Potential bug: This array is only length 4, so it's reading and writing the wallet size in a non-standard way.
    // Usually the wallet size would be set via dComIfGs_setWalletSize instead.
    // TODO: Investigate this more.
    dComIfGs_setSelectEquip(4, tmp_sttsA.mSelectEquip[4]);

    dComIfGp_setSelectEquip(0, dComIfGs_getSelectEquip(0));
    dComIfGp_setSelectEquip(1, dComIfGs_getSelectEquip(1));
    dComIfGp_setSelectEquip(2, dComIfGs_getSelectEquip(2));
    dComIfGp_setSelectEquip(3, dComIfGs_getSelectEquip(3));
    // Bug: The following line sets out of bounds of dComIfG_play_c's mSelectEquip array.
    // It seems to set dComIfG_play_c's mMesgAnime value to the current wallet size value.
    // TODO: Investigate this more.
    dComIfGp_setSelectEquip(4, dComIfGs_getSelectEquip(4));

    dComIfGs_setItem(dInvSlot_BOTTLE0_e, tmp_item.mItems[dInvSlot_BOTTLE0_e]);
    dComIfGs_setItem(dInvSlot_BOTTLE1_e, tmp_item.mItems[dInvSlot_BOTTLE1_e]);
    dComIfGs_setItem(dInvSlot_BOTTLE2_e, tmp_item.mItems[dInvSlot_BOTTLE2_e]);
    dComIfGs_setItem(dInvSlot_BOTTLE3_e, tmp_item.mItems[dInvSlot_BOTTLE3_e]);
    dComIfGs_setItem(dInvSlot_CAMERA_e,  tmp_item.mItems[dInvSlot_CAMERA_e]);

    dComIfGs_setSelectItem(dItemBtn_X_e, dInvSlot_NONE_e);
    dComIfGs_setSelectItem(dItemBtn_Y_e, dInvSlot_NONE_e);
    dComIfGs_setSelectItem(dItemBtn_Z_e, dInvSlot_NONE_e);
}

/* 80055580-8005586C       .text dComIfGs_exchangePlayerRecollectionData__Fv */
void dComIfGs_exchangePlayerRecollectionData() {
    if (dComIfGp_getPlayerInfoBufferStageNo() == 0) {
        return;
    }

    dSv_player_status_a_c tmp_sttsA;
    dSv_player_item_max_c tmp_max;
    dSv_player_item_record2_c tmp_record2;
    dSv_player_collect_c tmp_collect;
    dSv_player_item_c tmp_item;

    tmp_sttsA.mMaxLife = dComIfGs_getMaxLife();
    tmp_sttsA.mLife = dComIfGs_getLife();
    tmp_sttsA.mMaxMagic = dComIfGs_getMaxMagic();
    tmp_sttsA.mMagic = dComIfGs_getMagic();

    tmp_max.mItemMax2.mArrowNum = dComIfGs_getArrowMax();
    tmp_record2.mArrowNum = dComIfGs_getArrowNum();
    tmp_max.mItemMax2.mBombNum = dComIfGs_getBombMax();
    tmp_record2.mBombNum = dComIfGs_getBombNum();
    tmp_record2.mPictureNum = dComIfGs_getPictureNum();

    tmp_collect.mCollect[0] = dComIfGs_checkCollect(0);
    tmp_collect.mCollect[1] = dComIfGs_checkCollect(1);
    tmp_collect.mCollect[2] = dComIfGs_checkCollect(2);
    tmp_collect.mCollect[3] = dComIfGs_checkCollect(3);
    tmp_collect.mCollect[4] = dComIfGs_checkCollect(4);

    tmp_sttsA.mSelectEquip[0] = dComIfGs_getSelectEquip(0);
    tmp_sttsA.mSelectEquip[1] = dComIfGs_getSelectEquip(1);
    tmp_sttsA.mSelectEquip[2] = dComIfGs_getSelectEquip(2);
    tmp_sttsA.mSelectEquip[3] = dComIfGs_getSelectEquip(3);
    tmp_sttsA.mSelectEquip[4] = dComIfGs_getSelectEquip(4);

    tmp_item.mItems[dInvSlot_BOTTLE0_e] = dComIfGs_getItem(dInvSlot_BOTTLE0_e);
    tmp_item.mItems[dInvSlot_BOTTLE1_e] = dComIfGs_getItem(dInvSlot_BOTTLE1_e);
    tmp_item.mItems[dInvSlot_BOTTLE2_e] = dComIfGs_getItem(dInvSlot_BOTTLE2_e);
    tmp_item.mItems[dInvSlot_BOTTLE3_e] = dComIfGs_getItem(dInvSlot_BOTTLE3_e);
    tmp_item.mItems[dInvSlot_CAMERA_e]  = dComIfGs_getItem(dInvSlot_CAMERA_e);

    // TODO: This matches but could probably be cleaned up somehow.
    dSv_player_status_c_c stts;
    memcpy(&stts, dComIfGp_getPlayerInfoBuffer(), sizeof(stts));
    u8* buffer = dComIfGp_getPlayerInfoBuffer();
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectStatusA)),       dComIfGs_getpPlayerStatusA(),             sizeof(stts.mRecollectStatusA));
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectItem)),          dComIfGs_getpItem(),                      sizeof(stts.mRecollectItem));
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectItemRecord)),    &dComIfGs_getpItemRecord()->mItemRecord2, sizeof(stts.mRecollectItemRecord));
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectItemMax)),       &dComIfGs_getpItemMax()->mItemMax2,       sizeof(stts.mRecollectItemMax));
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectBagItem)),       dComIfGs_getpBagItem(),                   sizeof(stts.mRecollectBagItem));
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectBagItemRecord)), dComIfGs_getpBagItemRecord(),             sizeof(stts.mRecollectBagItemRecord));
    memcpy((void*)(buffer + offsetof(dSv_player_status_c_c, mRecollectCollect)),       dComIfGs_getpCollect(),                   sizeof(stts.mRecollectCollect));

    u8* stts_buffer = (u8*)&stts;
    memcpy(dComIfGs_getpPlayerStatusA(),             stts_buffer + offsetof(dSv_player_status_c_c, mRecollectStatusA),       sizeof(stts.mRecollectStatusA));
    memcpy(dComIfGs_getpItem(),                      stts_buffer + offsetof(dSv_player_status_c_c, mRecollectItem),          sizeof(stts.mRecollectItem));
    memcpy(&dComIfGs_getpItemRecord()->mItemRecord2, stts_buffer + offsetof(dSv_player_status_c_c, mRecollectItemRecord),    sizeof(stts.mRecollectItemRecord));
    memcpy(&dComIfGs_getpItemMax()->mItemMax2,       stts_buffer + offsetof(dSv_player_status_c_c, mRecollectItemMax),       sizeof(stts.mRecollectItemMax));
    memcpy(dComIfGs_getpBagItem(),                   stts_buffer + offsetof(dSv_player_status_c_c, mRecollectBagItem),       sizeof(stts.mRecollectBagItem));
    memcpy(dComIfGs_getpBagItemRecord(),             stts_buffer + offsetof(dSv_player_status_c_c, mRecollectBagItemRecord), sizeof(stts.mRecollectBagItemRecord));
    memcpy(dComIfGs_getpCollect(),                   stts_buffer + offsetof(dSv_player_status_c_c, mRecollectCollect),       sizeof(stts.mRecollectCollect));

    dComIfGs_setMaxLife(tmp_sttsA.mMaxLife);
    dComIfGs_setLife(tmp_sttsA.mLife);
    dComIfGs_setMaxMagic(tmp_sttsA.mMaxMagic);
    dComIfGs_setMagic(tmp_sttsA.mMagic);

    dComIfGs_setArrowMax(tmp_max.mItemMax2.mArrowNum);
    dComIfGs_setArrowNum(tmp_record2.mArrowNum);
    dComIfGs_setBombMax(tmp_max.mItemMax2.mBombNum);
    dComIfGs_setBombNum(tmp_record2.mBombNum);
    dComIfGs_setPictureNum(tmp_record2.mPictureNum);

    dComIfGs_setCollect(0, tmp_collect.mCollect[0]);
    dComIfGs_setCollect(1, tmp_collect.mCollect[1]);
    dComIfGs_setCollect(2, tmp_collect.mCollect[2]);
    dComIfGs_setCollect(3, tmp_collect.mCollect[3]);
    dComIfGs_setCollect(4, tmp_collect.mCollect[4]);

    dComIfGs_setSelectEquip(0, tmp_sttsA.mSelectEquip[0]);
    dComIfGs_setSelectEquip(1, tmp_sttsA.mSelectEquip[1]);
    dComIfGs_setSelectEquip(2, tmp_sttsA.mSelectEquip[2]);
    dComIfGs_setSelectEquip(3, tmp_sttsA.mSelectEquip[3]);
    // Potential bug: This array is only length 4, so it's reading and writing the wallet size in a non-standard way.
    // Usually the wallet size would be set via dComIfGs_setWalletSize instead.
    // TODO: Investigate this more.
    dComIfGs_setSelectEquip(4, tmp_sttsA.mSelectEquip[4]);

    dComIfGp_setSelectEquip(0, dComIfGs_getSelectEquip(0));
    dComIfGp_setSelectEquip(1, dComIfGs_getSelectEquip(1));
    dComIfGp_setSelectEquip(2, dComIfGs_getSelectEquip(2));
    dComIfGp_setSelectEquip(3, dComIfGs_getSelectEquip(3));
    // Bug: The following line sets out of bounds of dComIfG_play_c's mSelectEquip array.
    // It seems to set dComIfG_play_c's mMesgAnime value to the current wallet size value.
    // TODO: Investigate this more.
    dComIfGp_setSelectEquip(4, dComIfGs_getSelectEquip(4));

    dComIfGs_setItem(dInvSlot_BOTTLE0_e, tmp_item.mItems[dInvSlot_BOTTLE0_e]);
    dComIfGs_setItem(dInvSlot_BOTTLE1_e, tmp_item.mItems[dInvSlot_BOTTLE1_e]);
    dComIfGs_setItem(dInvSlot_BOTTLE2_e, tmp_item.mItems[dInvSlot_BOTTLE2_e]);
    dComIfGs_setItem(dInvSlot_BOTTLE3_e, tmp_item.mItems[dInvSlot_BOTTLE3_e]);
    dComIfGs_setItem(dInvSlot_CAMERA_e,  tmp_item.mItems[dInvSlot_CAMERA_e]);
}

/* 8005586C-800559E8       .text dComIfGs_setSelectEquip__FiUc */
void dComIfGs_setSelectEquip(int i_type, u8 i_itemNo) {
    switch (i_type) {
    case 0:
        switch (i_itemNo) {
        case dItem_SWORD_e:
            dComIfGs_onCollect(i_type, 0);
            break;
        case dItem_MASTER_SWORD_1_e:
            dComIfGs_onCollect(i_type, 1);
            break;
        case dItem_MASTER_SWORD_2_e:
            dComIfGs_onCollect(i_type, 2);
            break;
        case dItem_MASTER_SWORD_3_e:
            dComIfGs_onCollect(i_type, 3);
            break;
        }
        break;
    case 1:
        switch (i_itemNo) {
        case dItem_SHIELD_e:
            dComIfGs_onCollect(i_type, 0);
            break;
        case dItem_MIRROR_SHIELD_e:
            dComIfGs_onCollect(i_type, 1);
            break;
        }
        break;
    case 2:
        if (i_itemNo == dItem_POWER_BRACELETS_e) {
            dComIfGs_onCollect(i_type, 0);
        }
        break;
    }

    g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().setSelectEquip(i_type, i_itemNo);
}
