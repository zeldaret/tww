#ifndef D_COM_D_COM_INF_GAME_H
#define D_COM_D_COM_INF_GAME_H

#include "d/d_attention.h"
#include "d/d_bg_s.h"
#include "d/d_cc_s.h"
#include "d/d_detect.h"
#include "d/d_drawlist.h"
#include "d/d_event.h"
#include "d/d_event_manager.h"
#include "d/d_map.h"
#include "d/d_particle.h"
#include "d/d_resorce.h"
#include "d/d_s_actor_data_mng.h"
#include "d/d_save.h"
#include "d/d_stage.h"
#include "d/d_vibration.h"
#include "d/d_demo.h"
#include "d/d_timer.h"

#include "d/res/res_always.h" // IWYU pragma: export

class JKRArchive;
class JKRAramBlock;
class JKRExpHeap;
class dMagma_packet_c;
class dGrass_packet_c;
class dTree_packet_c;
class dFlower_packet_c;
namespace dWood { class Packet_c; };
class daShip_c;
class daAgb_c;
class camera_class;
class J2DOrthoGraph;

enum daPy__PlayerStatus0 {
    daPyStts0_UNK1_e           = 0x00000001,
    daPyStts0_UNK2_e           = 0x00000002,
    daPyStts0_UNK4_e           = 0x00000004,
    daPyStts0_UNK10_e          = 0x00000010,
    daPyStts0_UNK20_e          = 0x00000020,
    daPyStts0_UNK40_e          = 0x00000040,
    daPyStts0_UNK80_e          = 0x00000080, // Maybe inside a Baba Bud before being spat out?
    daPyStts0_UNK100_e         = 0x00000100,
    daPyStts0_UNK200_e         = 0x00000200,
    daPyStts0_UNK400_e         = 0x00000400,
    daPyStts0_UNK800_e         = 0x00000800,
    daPyStts0_BOW_AIM_e        = 0x00001000,
    daPyStts0_UNK2000_e        = 0x00002000,
    daPyStts0_HOOKSHOT_AIM_e   = 0x00004000,
    daPyStts0_SWORD_SWING_e    = 0x00008000,
    daPyStts0_SHIP_RIDE_e      = 0x00010000,
    daPyStts0_ROPE_AIM_e       = 0x00020000,
    daPyStts0_UNK40000_e       = 0x00040000,
    daPyStts0_BOOMERANG_AIM_e  = 0x00080000,
    daPyStts0_SWIM_e           = 0x00100000,
    daPyStts0_TELESCOPE_LOOK_e = 0x00200000,
    daPyStts0_BOOMERANG_WAIT_e = 0x00400000,
    daPyStts0_UNK800000_e      = 0x00800000,
    daPyStts0_UNK1000000_e     = 0x01000000,
    daPyStts0_UNK2000000_e     = 0x02000000,
    daPyStts0_UNK4000000_e     = 0x04000000,
    daPyStts0_CRAWL_e          = 0x08000000,
    daPyStts0_UNK10000000_e    = 0x10000000,
    daPyStts0_UNK20000000_e    = 0x20000000,
    daPyStts0_SPIN_ATTACK_e    = 0x40000000,
    daPyStts0_UNK80000000_e    = 0x80000000,

    // This is some combination of flags which is seemingly related to "judgement", used in dAttention_c
    daPyStts0_UNK37a02371_e    = daPyStts0_UNK1_e | daPyStts0_UNK10_e | daPyStts0_UNK20_e
                                 | daPyStts0_UNK40_e | daPyStts0_UNK100_e | daPyStts0_UNK200_e
                                 | daPyStts0_UNK2000_e| daPyStts0_TELESCOPE_LOOK_e
                                 | daPyStts0_UNK800000_e | daPyStts0_UNK1000000_e
                                 | daPyStts0_UNK2000000_e | daPyStts0_UNK4000000_e
                                 | daPyStts0_UNK10000000_e | daPyStts0_UNK20000000_e
};

enum daPy__PlayerStatus1 {
    daPyStts1_WIND_WAKER_CONDUCT_e = 0x00000001,
    daPyStts1_UNK2_e               = 0x00000002,
    daPyStts1_UNK4_e               = 0x00000004,
    daPyStts1_PICTO_BOX_AIM_e      = 0x00000008,
    daPyStts1_UNK10_e              = 0x00000010,
    daPyStts1_DEKU_LEAF_FLY_e      = 0x00000020,
    daPyStts1_DEKU_LEAF_FAN_e      = 0x00000040,
    daPyStts1_UNK80_e              = 0x00000080,
    daPyStts1_UNK100_e             = 0x00000100,
    daPyStts1_UNK200_e             = 0x00000200,
    daPyStts1_SAIL_e               = 0x00000400,
    daPyStts1_UNK800_e             = 0x00000800,
    daPyStts1_UNK1000_e            = 0x00001000,
    daPyStts1_UNK2000_e            = 0x00002000,
    daPyStts1_UNK4000_e            = 0x00004000,
    daPyStts1_UNK8000_e            = 0x00008000,
    daPyStts1_UNK10000_e           = 0x00010000,
    daPyStts1_UNK20000_e           = 0x00020000,
    daPyStts1_UNK40000_e           = 0x00040000,
    daPyStts1_UNK80000_e           = 0x00080000,
};

class __d_timer_info_c {
public:
    __d_timer_info_c() {
        mTimerMode = -1;
        mTimerLimitTimeMs = 0;
        mTimerNowTimeMs = 0;
        mTimerPtr = NULL;
    }

    /* 0x00 */ dTimer_c* mTimerPtr;
    /* 0x04 */ int mTimerNowTimeMs;
    /* 0x08 */ int mTimerLimitTimeMs;
    /* 0x0C */ int mTimerMode;
    /* 0x10 */ u16 mWaveFrame;
};

class dComIfG_camera_info_class {
public:
    dComIfG_camera_info_class() {}
    ~dComIfG_camera_info_class() {}

    /* 0x00 */ camera_class* mpCamera;
    /* 0x04 */ s8 mDlstWindowIdx;
    /* 0x05 */ s8 mCamP1Id;
    /* 0x06 */ s8 mCamP2Id;
    /* 0x07 */ u8 field_0x07;
    /* 0x08 */ u32 mCameraAttentionStatus;
    /* 0x0C */ f32 mCameraZoomScale;
    /* 0x10 */ f32 mCameraZoomForcus;
    /* 0x14 */ cXyz mCameraPos;
    /* 0x20 */ cXyz mCameraTarget;
    /* 0x2C */ f32 mCameraFovy;
    /* 0x30 */ s16 mCameraBank;
};
STATIC_ASSERT(sizeof(dComIfG_camera_info_class) == 0x34);

// This is /res/ItemTable/item_table.bin
// The real name of this struct is not currently known, this is a fake name.
struct ItemTableList {
    u8 mMagic[0xA]; // "ITEM_TABLE"
    short mEntryCount; // 0x1E
    u32 mPadding;
    u8 mItemTables[0x1E][0x10];
};

class dComIfG_MesgCamInfo_c {
public:
    /* 0x00 */ int mID;
    /* 0x04 */ int mBasicID;
    /* 0x08 */ fopAc_ac_c* mActor[10];
};

class dComIfG_play_c {
public:
#if VERSION <= VERSION_JPN
    dComIfG_play_c();
#else
    dComIfG_play_c() { ct(); }
    void ct();
#endif

    void init();
    void itemInit();
    static int getLayerNo(int i_roomNo);
    void createParticle();
    void createDemo();
    void removeDemo();
    void executeEvtManager();
    dMagma_packet_c* createMagma();
    void removeMagma();
    void executeMagma();
    void drawMagma();
    dGrass_packet_c* createGrass();
    void removeGrass();
    void executeGrass();
    void drawGrass();
    dFlower_packet_c* createFlower();
    void removeFlower();
    void executeFlower();
    void drawFlower();
    dTree_packet_c* createTree();
    void removeTree();
    void executeTree();
    void drawTree();
    dWood::Packet_c* createWood();
    void removeWood();
    void executeWood();
    void drawWood();

    BOOL checkCameraAttentionStatus(int idx, u32 flag) {
        return mCameraInfo[idx].mCameraAttentionStatus & flag;
    }
    u32 getCameraAttentionStatus(int i) { return mCameraInfo[i].mCameraAttentionStatus; }
    void setCameraAttentionStatus(int i, u32 flag) { mCameraInfo[i].mCameraAttentionStatus = flag; }
    void onCameraAttentionStatus(int i, u32 flag) { mCameraInfo[i].mCameraAttentionStatus |= flag; }
    void offCameraAttentionStatus(int i, u32 flag) {
        mCameraInfo[i].mCameraAttentionStatus &= ~flag;
    }

    void setCamera(int i, camera_class* cam) { mCameraInfo[i].mpCamera = cam; }
    void setCameraInfo(int idx, camera_class* camera_p, int dlst_window_idx, int player1_camera_id, int player2_camera_id) {
        mCameraInfo[idx].mpCamera = camera_p;
        mCameraInfo[idx].mDlstWindowIdx = dlst_window_idx;
        mCameraInfo[idx].mCamP1Id = player1_camera_id;
        mCameraInfo[idx].mCamP2Id = player2_camera_id;
        setCameraAttentionStatus(0, 0);
    }

    f32 getCameraZoomForcus(int i_no) { return mCameraInfo[i_no].mCameraZoomForcus; }
    void setCameraZoomForcus(int i_no, f32 i_focus) { mCameraInfo[i_no].mCameraZoomForcus = i_focus; }

    f32 getCameraZoomScale(int i_no) { return mCameraInfo[i_no].mCameraZoomScale; }
    void setCameraZoomScale(int i_no, f32 i_scale) { mCameraInfo[i_no].mCameraZoomScale = i_scale; }

    void saveCameraPosition(int i, cXyz* i_pos, cXyz* i_target, f32 i_fovy, s16 i_bank) {
        mCameraInfo[i].mCameraPos = *i_pos;
        mCameraInfo[i].mCameraTarget = *i_target;
        mCameraInfo[i].mCameraFovy = i_fovy;
        mCameraInfo[i].mCameraBank = i_bank;
    }

    void loadCameraPosition(int i, cXyz* o_pos, cXyz* o_target, f32* o_fovy, s16* o_bank) {
        *o_pos = mCameraInfo[i].mCameraPos;
        *o_target = mCameraInfo[i].mCameraTarget;
        *o_fovy = mCameraInfo[i].mCameraFovy;
        *o_bank = mCameraInfo[i].mCameraBank;
    }
    void setMesgCamInfoBasicID(int id) { mMesgCamInfo.mBasicID = id; }
    dComIfG_MesgCamInfo_c* getMesgCamInfo() { return &mMesgCamInfo; }
    int getMesgCamInfoID() { return mMesgCamInfo.mID; }
    void setMesgCamInfoID(int param_0) { mMesgCamInfo.mID = param_0; }
    void clearMesgCamInfoID() { mMesgCamInfo.mID = -1; }

    ~dComIfG_play_c() {}

    dStage_roomControl_c* getRoomControl() { return &mRoomCtrl; }
    dStage_dt_c& getStage() { return mStageData; }
    dEvt_control_c* getEvent() { return &mEvtCtrl; }
    dEvent_manager_c& getEvtManager() { return mEvtManager; }
    dPa_control_c* getParticle() { return mParticle; }
    dVibration_c& getVibration() { return mVibration; }
    dAttention_c& getAttention() { return mAttention; }
    dDetect_c& getDetect() { return mDetect; }
    dDemo_manager_c* getDemo() { return mDemo; }
    camera_class* getCamera(int idx) { return mCameraInfo[idx].mpCamera; }
    f32 getCamZoomForcus(int idx) { return mCameraInfo[idx].mCameraZoomForcus; }

    dMagma_packet_c* getMagma() { return mpMagmaPacket; }
    dGrass_packet_c* getGrass() { return mpGrassPacket; }
    dTree_packet_c* getTree() { return mpTreePacket; }
    dWood::Packet_c* getWood() { return mpWoodPacket; }
    dFlower_packet_c* getFlower() { return mpFlowerPacket; }

    const char* getStartStageName() { return mCurStage.getName(); }
    s8 getStartStageRoomNo() { return mCurStage.getRoomNo(); }
    s8 getStartStageLayer() { return mCurStage.getLayer(); }
    s16 getStartStagePoint() { return mCurStage.getPoint(); }
    void setStartStageLayer(s8 layer) { mCurStage.setLayer(layer); }
    void setStartStage(dStage_startStage_c* i_startStage) { mCurStage = *i_startStage; }
    dStage_startStage_c* getStartStage() { return &mCurStage; }

    const char* getNextStageName() { return mNextStage.getName(); }
    dStage_startStage_c* getNextStartStage() { return &mNextStage; }
    s8 getNextStageRoomNo() { return mNextStage.getRoomNo(); }
    s8 getNextStageLayer() { return mNextStage.getLayer(); }
    s16 getNextStagePoint() { return mNextStage.getPoint(); }
    s8 getNextStageWipe() { return mNextStage.getWipe(); }
    bool isEnableNextStage() { return mNextStage.isEnable(); }
    void offEnableNextStage() { mNextStage.offEnable(); }
    void setNextStage(const char* i_stageName, s8 i_roomNo, s16 i_point, s8 i_layer, s8 i_wipe) {
        mNextStage.set(i_stageName, i_roomNo, i_point, i_layer, i_wipe);
    }

    u8 getNowStageNum() { return mPlacenameIndex; }
    u8 checkStageName() { return mPlacenameState; }
    void setStageNameOn(u8 idx) {
        mPlacenameIndex = idx;
        mPlacenameState = 2;
    }
    void setStageNameDelete() { mPlacenameState = 0; }
    void setStageNameOff() { mPlacenameState = 1; }

    u8 getGameoverStatus() { return mGameoverStatus; }
    void setGameoverStatus(u8 stts) { mGameoverStatus = stts; }

    fopAc_ac_c* getPlayer(int idx) { return mPlayerInfo[idx].mpPlayer; }
    void setPlayer(int idx, fopAc_ac_c* player) { mPlayerInfo[idx].mpPlayer = player; }
    int getPlayerCameraID(int idx) { return mPlayerInfo[idx].mCameraID; }
    void setPlayerInfo(int idx, fopAc_ac_c* player, int cam) {
        mPlayerInfo[idx].mpPlayer = player;
        mPlayerInfo[idx].mCameraID = cam;
    }
    
    fopAc_ac_c* getPlayerPtr(int idx) { return (fopAc_ac_c*)mpPlayerPtr[idx]; }
    void setPlayerPtr(int idx, fopAc_ac_c* playerPtr) { mpPlayerPtr[idx] = playerPtr; }
    int getCameraPlayer1ID(int i) { return mCameraInfo[i].mCamP1Id; }
    int getCameraPlayer2ID(int i) { return mCameraInfo[i].mCamP2Id; }
    int getCameraWinID(int i) { return mCameraInfo[i].mDlstWindowIdx; }

    int getItemTimer() { return mItemTimer; }
    void resetItemTimer(s16 timer) {
        mItemTimer = timer;
        mStartItemTimer = false;
    }
    void startItemTimer() { mStartItemTimer = true; }

    int getMessageRupee() { return mMessageRupee; }
    void setMessageRupee(s16 count) { mMessageRupee = count; }

    void setAuctionRupee(s16 count) { mAuctionRupee = count; }
    void setAuctionGauge(s16 gauge) { mAuctionGauge = gauge; }

    int getItemRupeeCount() { return mItemRupeeCount; }
    void setItemRupeeCount(s32 count) { mItemRupeeCount += count; }
    void setMessageCountNumber(s16 num) { mMsgCountNumber = num; }
    s16 getMessageCountNumber() { return mMsgCountNumber; }

    void setMessageSetNumber(s16 num) { mMsgSetNumber = num; }
    s16 getMessageSetNumber() { return mMsgSetNumber; }

    s16 getMiniGameRupee() { return mMiniGameRupee; }
    void setMiniGameRupee(s16 count) { mMiniGameRupee = count; }
    void plusMiniGameRupee(s16 count) {
        if(mMiniGameRupee + count > 0) {
            mMiniGameRupee += count;
        }
        else {
            mMiniGameRupee = 0;
        }
    }

    JKRArchive* getLkDemoAnmArchive() { return mpLkDArc; }
    void setLkDemoAnmArchive(JKRArchive* i_arc) { mpLkDArc = i_arc; }
    s8 getLkDemoAnmNo() { return mLkDArcIdx; }
    void setLkDemoAnmNo(s8 idx) { mLkDArcIdx = idx; }
    void setStatus(u16 status) { mStatus = status; }
    void onStatus(u16 status) { mStatus |= status; }
    s32 checkStatus(u16 flags) { return flags & mStatus; }

    void setShipId(u8 i_id) { mShipId = i_id; }
    void setShipRoomId(u8 i_id) { mShipRoomId = i_id; }
    u8 getShipId() { return mShipId; }
    u8 getShipRoomId() { return mShipRoomId; }

    u8* getPlayerInfoBuffer() { return mPlayerInfoBuffer; }
    void setPlayerInfoBufferStageNo(u8 i_stageno) { mPlayerInfoBufferStageNo = i_stageno; }
    u8 getPlayerInfoBufferStageNo() { return mPlayerInfoBufferStageNo; }

    void setAgb(fopAc_ac_c* i_agb) { mpAgb = (daAgb_c*)i_agb; }
    daAgb_c* getAgb() { return mpAgb; }

    void setIkadaShipBeforePos(Vec& i_pos) { mIkadaLinkPos = i_pos; }
    void setIkadaShipId(u8 i_id) { mIkadaShipId = i_id; }
    void setIkadaShipBeforeRoomId(u8 i_roomId) { mIkadaShipBeforeRoomId = i_roomId; }
    u8 getIkadaShipId() { return mIkadaShipId; }
    u8 getIkadaShipBeforeRoomId() { return mIkadaShipBeforeRoomId; }

    void setTimerPtr(dTimer_c* timer) { mTimerInfo.mTimerPtr = timer; }
    dTimer_c* getTimerPtr() { return mTimerInfo.mTimerPtr; }
    void setTimerMode(int mode) { mTimerInfo.mTimerMode = mode; }
    int getTimerMode() { return mTimerInfo.mTimerMode; }
    void setTimerNowTimeMs(int ms) { mTimerInfo.mTimerNowTimeMs = ms; }
    int getTimerNowTimeMs() { return mTimerInfo.mTimerNowTimeMs; }
    void setTimerLimitTimeMs(int ms) { mTimerInfo.mTimerLimitTimeMs = ms; }
    int getTimerLimitTimeMs() { return mTimerInfo.mTimerLimitTimeMs; }
    void setWaveFrame(u16 frame) { mTimerInfo.mWaveFrame = frame; }
    u16 getWaveFrame() { return mTimerInfo.mWaveFrame; }
    void fmapOpenOn() { mFmapOpen = true; }

    s16 getItemMagicCount() { return mItemMagicCount; }
    void setItemMagicCount(s16 magic) { mItemMagicCount += magic; }
    s16 getItemMaxMagicCount() { return mItemMaxMagicCount; }
    void setItemMaxMagicCount(s16 magic) { mItemMaxMagicCount += magic; }

    s16 getItemBombNumCount() { return mItemBombNumCount; }
    void setItemBombNumCount(s16 num) { mItemBombNumCount += num; }

    u16 getItemNowLife() { return mItemNowLife; }
    void setItemNowLife(u16 life) { mItemNowLife = life; }

    f32 getItemLifeCount() { return mItemLifeCount; }
    void setItemLifeCount(f32 num) { mItemLifeCount += num; }

    s16 getItemMaxLifeCount() { return mItemMaxLifeCount; }
    void setItemMaxLifeCount(s16 num) { mItemMaxLifeCount += num; }

    s16 getItemArrowNumCount() { return mItemArrowNumCount; }
    void setItemArrowNumCount(s16 num) { mItemArrowNumCount += num; }

    void setNpcNameMessageID(u32 id) { mNpcNameMessageID = id; }
    void setItemNameMessageID(u32 id) { mItemNameMessageID = id; }

    s16 getItemKeyNumCount() { return mItemKeyNumCount; }
    void setItemKeyNumCount(s16 num) { mItemKeyNumCount += num; }

    s16 getItemBeastNumCount(int i_idx) { return mItemBeastNumCounts[i_idx]; }
    void setItemBeastNumCount(int i_idx, s16 num) { mItemBeastNumCounts[i_idx] += num; }

    s32 getItemTimeCount() { return mAirMeter; }
    void setItemTimeCount(s32 time) {
        mAirMeter = time;
        mItemSwimTimerStatus = true;
    }
    void clearItemTimeCount() {
        mAirMeter = 0;
        mItemSwimTimerStatus = false;
    }

    s32 getItemTimeMax() { return mItemTimeMax; }
    void setItemTimeMax(s32 time) { mItemTimeMax = time; }

    bool getItemSwimTimerStatus() { return mItemSwimTimerStatus; }
    void startItemSwimTimer() { mItemSwimTimerStatus = true; }
    void stopItemSwimTimer() { mItemSwimTimerStatus = false; }

    u8 getScopeType() { return mScopeType; }
    void setScopeType(u8 type) { mScopeType = type; }

    u8 getOperateWind() { return mOperateWind; }
    void setOperateWindCancelOff() { mOperateWind = 0; }
    void setOperateWindChangeOff() { mOperateWind = 1; }
    void setOperateWindOn() { mOperateWind = 2; }

    u8 checkMesgSendButton() { return mMesgSendButton; }
    void setMesgSendButton(u8 button) { mMesgSendButton = button; }
    u8 checkMesgCancelButton() { return mMesgCancelButton; }
    void setMesgCancelButton(u8 button) { mMesgCancelButton = button; }

    void setPlayerStatus(int param_0, int i, u32 flag) { mPlayerStatus[param_0][i] |= flag; }
    void clearPlayerStatus(int param_0, int i, u32 flag) { mPlayerStatus[param_0][i] &= ~flag; }
    u32 checkPlayerStatus(int param_0, int i, u32 flag) { return mPlayerStatus[param_0][i] & flag; }

    u8 getSelectItem(int idx) { return mSelectItem[idx]; }
    void setSelectItem(int idx, u8 itemNo) { mSelectItem[idx] = itemNo; }
    void setSelectEquip(int idx, u8 itemNo) { mSelectEquip[idx] = itemNo; }

    void setItem(u8 i_slot, u8 i_itemNo) {
        mItemSlot = i_slot;
        mItemNo = i_itemNo;
    }

    u8 getRStatus() { return mRStatus; }
    void setRStatus(u8 status) { mRStatus = status; }
    u8 getAStatus() { return mAStatus; }
    void setAStatus(u8 status) { mAStatus = status; }
    u8 getDoStatus() { return mDoStatus; }
    void setDoStatus(u8 status) { mDoStatus = status; }
    u8 getRStatusForce() { return mRStatusForce; }
    void setRStatusForce(u8 status) { mRStatusForce = status; }
    u8 getAStatusForce() { return mAStatusForce; }
    void setAStatusForce(u8 value) { mAStatusForce = value; }
    u8 getDoStatusForce() { return mDoStatusForce; }
    void setDoStatusForce(u8 value) { mDoStatusForce = value; }

    u8 getPictureStatus() { return mPictureStatus; }
    void setPictureStatusOn() { mPictureStatus = 2; }
    void setPictureStatusGetOn(u8 to_set) {
        mPictureStatus = 3;
        field_0x495f = to_set;
    }

    u8 getScopeMesgStatus() { return mScopeMesgStatus; }
    void setScopeMesgStatus(u8 status) { mScopeMesgStatus = status; }

    void setCurrentGrafPort(J2DOrthoGraph* i_graf) { mCurrentGrafPort = i_graf; }
    void setCurrentWindow(dDlst_window_c* i_window) { mCurrentWindow = i_window; }
    void setCurrentView(view_class* i_view) { mCurrentView = i_view; }
    view_port_class* getCurrentViewport() { return mCurrentViewport; }
    void setCurrentViewport(view_port_class* i_viewport) { mCurrentViewport = i_viewport; }
    s32 getWindowNum() { return mDlstWindowNum; }
    void setWindowNum(u8 num) { mDlstWindowNum = num; }
    dDlst_window_c * getWindow(int idx) { return &mDlstWindow[idx]; }
    void setWindow(int idx, f32 x, f32 y, f32 w, f32 h, f32 n, f32 f, int cameraID, int mode) {
        mDlstWindow[idx].setViewPort(x, y, w, h, n, f);
        mDlstWindow[idx].setScissor(x, y, w, h);
        mDlstWindow[idx].setCameraID(cameraID);
        mDlstWindow[idx].setMode(mode);
    }

    J2DOrthoGraph* getCurrentGrafPort() { return mCurrentGrafPort; }

    JKRExpHeap* getExpHeap2D() { return mpExpHeap2D; }
    void setExpHeap2D(void* heap) { mpExpHeap2D = (JKRExpHeap*)heap; }

    inline u8 isHeapLockFlag() { return mHeapLockFlag; }
    inline void setHeapLockFlag(u8 flag) { mHeapLockFlag = flag; }
    inline void offHeapLockFlag() { mHeapLockFlag = 0; }

    bool getMetronome() { return mMetronome; }
    void setMetronomeOn() { mMetronome = true; }
    void setMetronomeOff() { mMetronome = false; }

#if VERSION > VERSION_DEMO
    // These inlines aren't present in WW demo debug maps, but are present in TP debug.
    inline u8 getNowVibration() { return mNowVibration; }
    inline void setNowVibration(u8 vibration) { mNowVibration = vibration; }
#endif

#if VERSION > VERSION_JPN
    // Inline name is fake (not present in demo debug maps), but was guessed based on the similar
    // dSv_player_config_c::getPalLanguage() const inline in TP debug.
    inline u8 getPalLanguage() { return mPalLanguage; }
    inline void setPalLanguage(u8 lang) { mPalLanguage = lang; }
#endif

    void setMsgArchive(JKRArchive * pArc) { mpMsgArchive = pArc; }
    JKRArchive* getMsgArchive() { return mpMsgArchive; }
#if VERSION > VERSION_DEMO
    void setDmsgArchive(JKRArchive * pArc) { mpDmsgArchive = pArc; }
    JKRArchive* getDmsgArchive() { return mpDmsgArchive; }
#endif
    void setTactMsgArchive(JKRArchive * pArc) { mTactMsgArchive = pArc; }
    JKRArchive* getTactMsgArchive() { return mTactMsgArchive; }
    void setMenuArchive(JKRArchive * pArc) { mpMenuArchive = pArc; }
    JKRArchive* getMenuArchive() { return mpMenuArchive; }
    void setFont0Archive(JKRArchive * pArc) { mpFont0Archive = pArc; }
    void setFont1Archive(JKRArchive * pArc) { mpFont1Archive = pArc; }
    JKRArchive* getFontArchive() { return mpFont0Archive; }
    JKRArchive* getRubyArchive() { return mpFont1Archive; }
    void setAnmArchive(JKRArchive * pArc) { mpAnmArchive = pArc; }
    JKRArchive* getAnmArchive() { return mpAnmArchive; }
    void setLkDArc(JKRArchive * pArc) { mpLkDArc = pArc; }
    void setFmapArchive(JKRArchive * pArc) { mpFmapArchive = pArc; }
    void setItemResArchive(JKRArchive * pArc) { mpItemResArchive = pArc; }
    void setCollectResArchive(JKRArchive * pArc) { mpCollectResArchive = pArc; }
    void setFmapResArchive(JKRArchive * pArc) { mpFmapResArchive = pArc; }
    void setDmapResArchive(JKRArchive * pArc) { mpDmapResArchive = pArc; }
    void setOptionResArchive(JKRArchive * pArc) { mpOptionResArchive = pArc; }
    JKRArchive* getClothResArchive() { return mpClothResArchive; }
    void setClothResArchive(JKRArchive * pArc) { mpClothResArchive = pArc; }
    void setSaveResArchive(JKRArchive * pArc) { mpSaveResArchive = pArc; }
    void setItemIconArchive(JKRArchive * pArc) { mpItemIconArchive = pArc; }
    JKRArchive* getItemIconArchive() { return mpItemIconArchive; }
    void setNameResArchive(JKRArchive * pArc) { mpNameResArchive = pArc; }
    void setErrorResArchive(JKRArchive * pArc) { mpErrorResArchive = pArc; }
    JKRArchive* getErrorResArchive() { return mpErrorResArchive; }
    void setActionIconArchive(JKRArchive * pArc) { mpActionIconArchive = pArc; }
    JKRArchive* getActionIconArchive() { return mpActionIconArchive; }
    void setScopeResArchive(JKRArchive * pArc) { mpScopeResArchive = pArc; }
    void setCameraResArchive(JKRArchive * pArc) { mpCameraResArchive = pArc; }
    JKRArchive* getSwimResArchive() { return mpSwimResArchive; }
    void setSwimResArchive(JKRArchive * pArc) { mpSwimResArchive = pArc; }
    void setWindResArchive(JKRArchive * pArc) { mpWindResArchive = pArc; }
    void setFontArchive(JKRArchive * pArc) { mpFont0Archive = pArc; }
    void setMsgDtArchive(JKRArchive * pArc) { mpEnglishTextArchive = pArc; }
    JKRArchive* getMsgDtArchive() { return mpEnglishTextArchive; }
#if VERSION > VERSION_JPN
    void setMsgDt2Archive(JKRArchive * pArc) { mpHyruleTextArchive = pArc; }
    JKRArchive* getMsgDt2Archive() { return mpHyruleTextArchive; }
#endif

    void setItemTable(void * pData) { mpItemTable = (ItemTableList*)pData; }
    ItemTableList* getItemTable() { return mpItemTable; }
    void* getFmapData() { return mpFmapData; }
    void setFmapData(void * pData) { mpFmapData = pData; }

    JKRAramBlock* getPictureBoxData(int i) { return mPictureBoxData[i]; }
    void setPictureBoxData(JKRAramBlock* aramBlock, int i) { mPictureBoxData[i] = aramBlock; }
    bool isPictureFlag(u8 i) { return mPictureFlag & (u8)(1 << i); }
    void onPictureFlag(u8 i) {
        u8 mask = (1 << i);
        mPictureFlag |= mask;
    }
    void offPictureFlag(u8 i) {
        u8 mask = (1 << i);
        mPictureFlag &= ~mask;
    }
    u8 getPictureFormat() { return mPictureFormat; }
    u8 getPictureResult() { return mPictureResult; }
    u8 getPictureResultDetail() { return mPictureResultDetail; }
    void setBossBattleData(JKRAramBlock* aramBlock, int i) { mBossBattleData[i] = aramBlock; }

    void startFwaterTimer() { mFwaterTimer = 1; }
    void stopFwaterTimer() { mFwaterTimer = 0; }
    u8 checkFwaterTimer() { return mFwaterTimer; }

    u8 getMiniGameType() { return mMiniGameType; }
    void startMiniGame(u8 i_gameType) {
        mMiniGameType = i_gameType;
        mMinigameFlags |= 1 << (i_gameType - 1); // set Nth bit
    }
    void endMiniGame(u16 i_gameType) {
        mMiniGameType = 0;
        mMinigameFlags ^= 1 << (i_gameType - 1); // toggle Nth bit
        mMinigameResult = 0;
    }
    u8 getMiniGameResult() { return mMinigameResult; }
    void setMiniGameResult(u8 i_result) {
        mMinigameResult = i_result;
    }

    void show2dOn() { m2dShow = true; }
    void show2dOff() { m2dShow = false; }
    bool show2dCheck() { return m2dShow; }

    u8 getMelodyNum() { return mMelodyNum; }
    void setMelodyNum(u8 melody) { mMelodyNum = melody; }

    u8 getBaseAnimeID() { return mMesgAnime; }
    void setBaseAnimeID(u8 id) { mMesgAnime = id; }
    void clearBaseAnimeID() { mMesgAnime = 0xFF; }
    u8 getNowAnimeID() { return mMesgAnimeTagInfo; }
    void setNowAnimeID(u8 id) { mMesgAnimeTagInfo = id; }
    void clearNowAnimeID() { mMesgAnimeTagInfo = 0xFF; }
    u8 getMesgStatus() { return mMesgStatus; }
    void setMesgStatus(u8 status) { mMesgStatus = status; }
    u8 checkMesgBgm() { return mMesgBgm; }
    void setMesgBgm(u8 param_0) { mMesgBgm = param_0; }

    u8 getButtonMode() { return mButtonMode; }
    void setButtonMode(u8 mode) { mButtonMode = mode; }

    char* getInputPassword() { return mInputPassword; }
    void setInputPassword(const char* password) { strcpy(mInputPassword, password); }

    u8 getDirection() { return mDirection; }
    void setDirection(u8 direction) { mDirection = direction; }

    void onMenuCollect() { mMenuCollect = true; }

    void nameOpenOn() { field_0x4952 = 2; }
    u8 nameOpenCheck() { return field_0x4952; }

    /* 0x0000 */ dBgS mBgS;
    /* 0x1404 */ dCcS mCcS;
    /* 0x3DF8 */ dADM mADM;
    /* 0x3E94 */ dStage_startStage_c mCurStage;
    /* 0x3EA0 */ dStage_nextStage_c mNextStage;
    /* 0x3EAE */ u8 field_0x3EAE[0x3EB0 - 0x3EAE];
    /* 0x3EB0 */ dStage_stageDt_c mStageData;
    /* 0x3F34 */ dStage_roomControl_c mRoomCtrl;
    /* 0x3F38 */ dEvt_control_c mEvtCtrl;
    /* 0x402C */ dEvent_manager_c mEvtManager;
    /* 0x4568 */ dAttention_c mAttention;
    /* 0x46F8 */ u8 field_0x46F8[0x4700 - 0x46F8];
    /* 0x4700 */ dVibration_c mVibration;
    /* 0x4784 */ dDetect_c mDetect;
    /* 0x4798 */ JKRArchive* mpMsgArchive;
#if VERSION > VERSION_DEMO
    /* 0x479C */ JKRArchive* mpDmsgArchive;
#endif
    /* Offsets below are for retail JPN/USA/PAL */

    /* 0x47A0 */ JKRArchive* mTactMsgArchive;
    /* 0x47A4 */ JKRArchive* mpMenuArchive;
    /* 0x47A8 */ JKRArchive* mpFont0Archive;
    /* 0x47AC */ JKRArchive* mpFont1Archive;
    /* 0x47B0 */ JKRArchive* mpAnmArchive;
    /* 0x47B4 */ JKRArchive* mpLkDArc;
    /* 0x47B8 */ JKRArchive* mpFmapArchive;
    /* 0x47BC */ JKRArchive* mpItemResArchive;
    /* 0x47C0 */ JKRArchive* mpCollectResArchive;
    /* 0x47C4 */ JKRArchive* mpFmapResArchive;
    /* 0x47C8 */ JKRArchive* mpDmapResArchive;
    /* 0x47CC */ JKRArchive* mpOptionResArchive;
    /* 0x47D0 */ JKRArchive* mpClothResArchive;
    /* 0x47D4 */ JKRArchive* mpSaveResArchive;
    /* 0x47D8 */ JKRArchive* mpItemIconArchive;
    /* 0x47DC */ JKRArchive* mpNameResArchive;
    /* 0x47E0 */ JKRArchive* mpErrorResArchive;
    /* 0x47E4 */ JKRArchive* mpActionIconArchive;
    /* 0x47E8 */ JKRArchive* mpScopeResArchive;
    /* 0x47EC */ JKRArchive* mpCameraResArchive;
    /* 0x47F0 */ JKRArchive* mpSwimResArchive;
    /* 0x47F4 */ JKRArchive* mpWindResArchive;
    /* 0x47F8 */ JKRArchive* mpEnglishTextArchive;
#if VERSION > VERSION_JPN
    /* 0x47FC */ JKRArchive* mpHyruleTextArchive;
    /* 0x4800 */ JKRAramBlock* mPictureBoxData[3];
    /* 0x480C */ JKRAramBlock* mBossBattleData[4];
    /* 0x481C */ JKRAramBlock* field_0x481c;
    /* 0x4820 */ JKRAramBlock* field_0x4820;
#else
    /* 0x47FC */ JKRAramBlock* mPictureBoxData[3];
    /* 0x480C */ JKRAramBlock* mBossBattleData[4];
#endif
    /* Offsets below are for USA/PAL */

    /* 0x4824 */ dPa_control_c* mParticle;
    /* 0x4828 */ dDemo_manager_c* mDemo;
    /* 0x482C */ dMagma_packet_c* mpMagmaPacket;
    /* 0x4830 */ dGrass_packet_c* mpGrassPacket;
    /* 0x4834 */ dTree_packet_c* mpTreePacket;
    /* 0x4838 */ dWood::Packet_c* mpWoodPacket;
    /* 0x483C */ dFlower_packet_c* mpFlowerPacket;
    /* 0x4840 */ s8 mLkDArcIdx;
    /* 0x4841 */ u8 mDlstWindowNum;
    /* 0x4842 */ u16 mStatus;
    /* 0x4844 */ dDlst_window_c mDlstWindow[1];
    /* 0x4870 */ dComIfG_camera_info_class mCameraInfo[1];
    /* 0x48A4 */ struct {
        /* 0x0 */ fopAc_ac_c* mpPlayer;
        /* 0x4 */ s8 mCameraID;
    } mPlayerInfo[1];
    /* 0x48AC */ fopAc_ac_c* mpPlayerPtr[3];  // 0: Link, 1: Partner, 2: Ship
    /* 0x48B8 */ f32 field_0x48b8;
    /* 0x48BC */ f32 mItemLifeCount;
    /* 0x48C0 */ s32 mItemRupeeCount;
    /* 0x48C4 */ s32 mAirMeter;
    /* 0x48C8 */ s32 mItemTimeMax;
    /* 0x48CC */ u32 mNpcNameMessageID;
    /* 0x48D0 */ u32 mItemNameMessageID;
    /* 0x48D4 */ s16 mItemKeyNumCount;
    /* 0x48D6 */ s16 mItemMaxLifeCount;
    /* 0x48D8 */ s16 mItemMagicCount;
    /* 0x48DA */ s16 field_0x48da;
    /* 0x48DC */ s16 mItemMaxMagicCount;
    /* 0x48DE */ s16 field_0x48de;
    /* 0x48E0 */ s16 mItemArrowNumCount;
    /* 0x48E2 */ s16 field_0x48e2;
    /* 0x48E4 */ s16 mItemBombNumCount;
    /* 0x48E6 */ s16 field_0x48e6;
    /* 0x48E8 */ s16 mItemBeastNumCounts[8];
    /* 0x48F8 */ u8 field_0x48F8[0x4918 - 0x48F8];
    /* 0x4918 */ s16 mMsgCountNumber;
    /* 0x491A */ s16 mMsgSetNumber;
    /* 0x491C */ s16 mMessageRupee;
    /* 0x491E */ s16 mAuctionRupee;
    /* 0x4920 */ s16 mAuctionGauge;
    /* 0x4922 */ s16 mItemTimer;
    /* 0x4924 */ u16 mItemNowLife;
    /* 0x4926 */ s16 mItemNowRupee;
    /* 0x4928 */ bool mItemSwimTimerStatus;
    /* 0x4929 */ u8 field_0x4929;
    /* 0x492A */ u8 mMesgStatus;
    /* 0x492B */ u8 mScopeMesgStatus;
    /* 0x492C */ u8 field_0x492c;
    /* 0x492D */ u8 mRStatus;
    /* 0x492E */ u8 mAStatus;
    /* 0x492F */ u8 mDoStatus;
    /* 0x4930 */ u8 mRStatusForce;
    /* 0x4931 */ u8 mAStatusForce;
    /* 0x4932 */ u8 mDoStatusForce;
    /* 0x4933 */ u8 mSelectItem[4];
    /* 0x4937 */ u8 mSelectEquip[4];
    /* 0x493B */ u8 mMesgAnime;
    /* 0x493C */ u8 mMesgAnimeTagInfo;
    /* 0x493D */ u8 mItemSlot;
    /* 0x493E */ u8 mItemNo;
    /* 0x493F */ u8 field_0x493f;
    /* 0x4940 */ u8 field_0x4940;
    /* 0x4941 */ u8 mDirection;
    /* 0x4942 */ u8 mButtonMode;
    /* 0x4943 */ u8 field_0x4943;
    /* 0x4944 */ u8 field_0x4944;
    /* 0x4945 */ u8 mScopeType;
    /* 0x4946 */ u8 mOperateWind;
    /* 0x4947 */ bool mMetronome;
    /* 0x4948 */ u8 mMesgSendButton;
    /* 0x4949 */ u8 mMesgCancelButton;
    /* 0x494A */ u8 field_0x494a[6];
    /* 0x4950 */ u8 mMelodyNum;
    /* 0x4951 */ bool mFmapOpen;
    /* 0x4952 */ u8 field_0x4952;
    /* 0x4953 */ u8 field_0x4953;
    /* 0x4954 */ u8 field_0x4954;
    /* 0x4955 */ bool mStartItemTimer;
    /* 0x4956 */ u8 mFwaterTimer;
    /* 0x4957 */ u8 mPlacenameIndex;
    /* 0x4958 */ u8 mPlacenameState;
    /* 0x4959 */ u8 mGameoverStatus;
    /* 0x495A */ u8 mMenuCollect;
    /* 0x495B */ u8 mPictureFlag;
    /* 0x495C */ u8 mPictureResult;
    /* 0x495D */ u8 mPictureResultDetail;
    /* 0x495E */ u8 mPictureStatus;
    /* 0x495F */ u8 field_0x495f;
    /* 0x4960 */ u8 mPictureFormat;
    /* 0x4961 */ u8 field_0x4961;
    /* 0x4962 */ u8 mHeapLockFlag;
#if VERSION > VERSION_DEMO
    /* 0x4963 */ u8 mNowVibration;
#endif
#if VERSION > VERSION_JPN
    /* 0x4964 */ u8 mPalLanguage;
#endif
    /* 0x4965 */ u8 field_0x4965;
    /* 0x4966 */ char mInputPassword[0x11];
    /* 0x4977 */ u8 mMesgBgm;
    /* 0x4978 */ u8 field_0x4978;
    /* 0x4979 */ u8 m2dShow;
    /* 0x497A */ u8 field_0x497a;
    /* 0x497B */ u8 field_0x497B[0x497C - 0x497B];
    /* 0x497C */ JKRExpHeap* mpExpHeap2D;
    /* 0x4980 */ dComIfG_MesgCamInfo_c mMesgCamInfo;
    /* 0x49B0 */ u8 mPlayerInfoBuffer[sizeof(dSv_player_status_c_c)];
    /* 0x4A20 */ u8 mPlayerInfoBufferStageNo;
    /* 0x4A24 */ daAgb_c* mpAgb;
    /* 0x4A28 */ u32 mPlayerStatus[1][4];
    /* 0x4A38 */ u16 mMinigameFlags;
    /* 0x4A3A */ u8 mMiniGameType;
    /* 0x4A3C */ s16 mMiniGameRupee;
    /* 0x4A3E */ u8 mMinigameResult;
    /* 0x4A40 */ __d_timer_info_c mTimerInfo;
    /* 0x4A54 */ dDlst_window_c* mCurrentWindow;
    /* 0x4A58 */ view_class* mCurrentView;
    /* 0x4A5C */ view_port_class* mCurrentViewport;
    /* 0x4A60 */ J2DOrthoGraph* mCurrentGrafPort;
    /* 0x4A64 */ u8 mShipId;
    /* 0x4A65 */ u8 mShipRoomId;
    /* 0x4A66 */ u8 mIkadaShipBeforeRoomId;
    /* 0x4A67 */ u8 mIkadaShipId;
    /* 0x4A68 */ cXyz mIkadaLinkPos;
    /* 0x4A74 */ ItemTableList* mpItemTable;
    /* 0x4A78 */ void* mpFmapData;
};

class dComIfG_inf_c {
public:
#if VERSION <= VERSION_JPN
    dComIfG_inf_c();
#else
    dComIfG_inf_c() { ct(); }
#endif
    ~dComIfG_inf_c() {}

    void ct();

    /* 0x00000 */ dSv_info_c save;
    /* 0x012A0 */ dComIfG_play_c play;
    /* 0x05D1C */ dDlst_list_c drawlist;
    /* 0x1BF50 */ u8 field_0x1BF50[0x1BFC0 - 0x1BF50];
    /* 0x1BFC0 */ dRes_control_c mResControl;
    /* 0x1D1C0 */ u8 field_0x1d1c0;
    /* 0x1D1C1 */ u8 mBrightness;
};

#if VERSION > VERSION_JPN
STATIC_ASSERT(sizeof(dComIfG_inf_c) == 0x1D1C8);
#endif

extern dComIfG_inf_c g_dComIfG_gameInfo;

extern GXColor g_clearColor;
extern GXColor g_blackColor;
extern GXColor g_whiteColor;
extern GXColor g_saftyWhiteColor;


/**
 * === SAVE ===
 */

void dComIfGs_setGameStartStage();
void dComIfGs_gameStart();
void dComIfGs_copyPlayerRecollectionData();
u8 dComIfGs_checkGetItem(u8);

inline void dComIfGs_init() {
    g_dComIfG_gameInfo.save.init();
}

inline void dComIfGs_reinit() {
    g_dComIfG_gameInfo.save.reinit();
}

inline u8 dComIfGs_checkReserveItem(u8 i_itemNo) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().checkReserveItem(i_itemNo);
}

inline void dComIfGs_initZone() {
    g_dComIfG_gameInfo.save.initZone();
}

inline u32 dComIfGs_createZone(int i_roomNo) {
    return g_dComIfG_gameInfo.save.createZone(i_roomNo);
}

inline u8 dComIfGs_getSelectEquip(int i_no) {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getSelectEquip(i_no);
}

void dComIfGs_setSelectEquip(int i_type, u8 i_itemNo);

inline u8 dComIfGs_getWalletSize() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getWalletSize();
}

inline void dComIfGs_setWalletSize(u8 size) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().setWalletSize(size);
}

inline int dComIfGs_getRupee() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getRupee();
}

inline void dComIfGp_startItemTimer() {
    g_dComIfG_gameInfo.play.startItemTimer();
}

inline int dComIfGp_getItemTimer() {
    return g_dComIfG_gameInfo.play.getItemTimer();
}

inline void dComIfGp_resetItemTimer(s16 timer) {
    g_dComIfG_gameInfo.play.resetItemTimer(timer);
}

inline void dComIfGp_decItemTimer() {
    // TODO
}

inline int dComIfGp_getMessageRupee() {
    return g_dComIfG_gameInfo.play.getMessageRupee();
}

inline void dComIfGp_setMessageRupee(s16 count) {
    g_dComIfG_gameInfo.play.setMessageRupee(count);
}

inline void dComIfGp_setAuctionRupee(s16 count) {
    g_dComIfG_gameInfo.play.setAuctionRupee(count);
}

inline void dComIfGp_setAuctionGauge(s16 gauge) {
    g_dComIfG_gameInfo.play.setAuctionGauge(gauge);
}

inline void dComIfGs_setRupee(u16 rupee) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().setRupee(rupee);
}

inline u16 dComIfGs_getRupeeMax() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getRupeeMax();
}

inline u8 dComIfGs_getItemBeast(int param_0) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().getBeast(param_0);
}

inline void dComIfGs_setItemBeast(int i_idx, u8 i_itemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setBeast(i_idx, i_itemNo);
}

inline u8 dComIfGs_getItemBait(int param_0) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().getBait(param_0);
}

inline void dComIfGs_setItemBait(int i_idx, u8 i_itemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setBait(i_idx, i_itemNo);
}

inline u8 dComIfGs_getItemReserve(int param_0) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().getReserve(param_0);
}

inline void dComIfGs_setItemReserve(int i_idx, u8 i_itemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setReserve(i_idx, i_itemNo);
}

inline OSTime dComIfGs_getDateIpl() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusB().getDateIpl();
}

// The inventory slot for items. Also known as "select item".
enum dInventorySlot_e {
    dInvSlot_ItemFirst_e = 0,
    dInvSlot_TELESCOPE_e = 0,
    dInvSlot_SAIL_e = 1,
    dInvSlot_WIND_WAKER_e = 2,
    dInvSlot_GRAPPLING_HOOK_e = 3,
    dInvSlot_SPOILS_BAG_e = 4,
    dInvSlot_BOOMERANG_e = 5,
    dInvSlot_DEKU_LEAF_e = 6,
    dInvSlot_TINGLE_TUNER_e = 7,
    dInvSlot_CAMERA_e = 8,
    dInvSlot_IRON_BOOTS_e = 9,
    dInvSlot_MAGIC_ARMOR_e = 10,
    dInvSlot_BAIT_BAG_e = 11,
    dInvSlot_BOW_e = 12,
    dInvSlot_BOMB_e = 13,
    dInvSlot_BOTTLE0_e = 14,
    dInvSlot_BOTTLE1_e = 15,
    dInvSlot_BOTTLE2_e = 16,
    dInvSlot_BOTTLE3_e = 17,
    dInvSlot_BOTTLE_COUNT_e = dInvSlot_BOTTLE3_e + 1 - dInvSlot_BOTTLE0_e,
    dInvSlot_DELIVERY_BAG_e = 18,
    dInvSlot_HOOKSHOT_e = 19,
    dInvSlot_SKULL_HAMMER_e = 20,
    dInvSlot_ItemLast_e = 21,

    dInvSlot_BeastFirst_e = 24, // Spoils Bag
    dInvSlot_BeastLast_e = 32,

    dInvSlot_BaitFirst_e = 36, // Bait Bag
    dInvSlot_BaitLast_e = 44,

    dInvSlot_ReserveFirst_e = 48,
    dInvSlot_ReserveLast_e = 56,

    dInvSlot_NONE_e = 0xFF,
};

// The index of a button that can have an item assigned to it.
enum dItemButton_e {
    dItemBtn_X_e = 0,
    dItemBtn_Y_e = 1,
    dItemBtn_Z_e = 2,
    dItemBtn_NONE_e = 3,
    dItemBtn_COUNT_e = 3,
};

/**
 * Returns which item is in a specific inventory slot.
 * @param i_invIdx The index of the inventory slot.
 * @return The item number of the item in that slot, or 0xFF for no item.
 */
inline u8 dComIfGs_getItem(int i_invIdx) {
    if (i_invIdx < dInvSlot_ItemLast_e) {
        return g_dComIfG_gameInfo.save.getPlayer().getItem().getItem(i_invIdx);
    } else if (i_invIdx < dInvSlot_BeastFirst_e) {
        return 0xFF;
    } else if (i_invIdx < dInvSlot_BeastLast_e) {
        return dComIfGs_getItemBeast(i_invIdx - dInvSlot_BeastFirst_e);
    } else if (i_invIdx < dInvSlot_BaitFirst_e) {
        return 0xFF;
    } else if (i_invIdx < dInvSlot_BaitLast_e) {
        return dComIfGs_getItemBait(i_invIdx - dInvSlot_BaitFirst_e);
    } else if (i_invIdx < dInvSlot_ReserveFirst_e) {
        return 0xFF;
    } else if (i_invIdx < dInvSlot_ReserveLast_e) {
        return dComIfGs_getItemReserve(i_invIdx - dInvSlot_ReserveFirst_e);
    } else {
        return 0xFF;
    }
}

/**
 * Sets a specific inventory slot to contain a particular item.
 * @param i_invIdx The index of the inventory slot.
 * @param i_itemNo The item number of the item to place in that slot, or 0xFF for no item.
 */
inline void dComIfGs_setItem(int i_invIdx, u8 i_itemNo) {
    if (i_invIdx < dInvSlot_ItemLast_e) {
        g_dComIfG_gameInfo.save.getPlayer().getItem().setItem(i_invIdx, i_itemNo);
    } else if (i_invIdx < dInvSlot_BeastFirst_e) {
        return;
    } else if (i_invIdx < dInvSlot_BeastLast_e) {
        dComIfGs_setItemBeast(i_invIdx - dInvSlot_BeastFirst_e, i_itemNo);
    } else if (i_invIdx < dInvSlot_BaitFirst_e) {
        return;
    } else if (i_invIdx < dInvSlot_BaitLast_e) {
        dComIfGs_setItemBait(i_invIdx - dInvSlot_BaitFirst_e, i_itemNo);
    } else if (i_invIdx < dInvSlot_ReserveFirst_e) {
        return;
    } else if (i_invIdx < dInvSlot_ReserveLast_e) {
        dComIfGs_setItemReserve(i_invIdx - dInvSlot_ReserveFirst_e, i_itemNo);
    } else {
        return;
    }
}

inline u8 dComIfGs_getBeast(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().getBeast(i_idx);
}

inline void dComIfGs_setBeastItem(u8 i_itemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setBeastItem(i_itemNo);
}

inline u8 dComIfGs_getBait(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().getBait(i_idx);
}

inline void dComIfGs_setBaitItem(u8 i_itemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setBaitItem(i_itemNo);
}

inline void dComIfGs_setBaitItemEmpty() {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setBaitItemEmpty();
}

inline u8 dComIfGs_getReserve(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().getReserve(i_idx);
}

inline void dComIfGs_setReserveItem(u8 i_itemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setReserveItem(i_itemNo);
}

inline BOOL dComIfGs_isGetItemReserve(u8 i_no) {
    return g_dComIfG_gameInfo.save.getPlayer().getGetBagItem().isReserve(i_no);
}

inline void dComIfGs_onGetItemReserve(int i_no) {
    g_dComIfG_gameInfo.save.getPlayer().getGetBagItem().onReserve(i_no);
}

inline BOOL dComIfGs_isGetCollectMap(int i_no) {
    return g_dComIfG_gameInfo.save.getPlayer().getMap().isGetMap(i_no - 1);
}

inline void dComIfGs_onCompleteCollectMap(int i_no) {
    g_dComIfG_gameInfo.save.getPlayer().getMap().onCompleteMap(i_no - 1);
}

inline void dComIfGs_onGetCollectMap(int i_no) {
    g_dComIfG_gameInfo.save.getPlayer().getMap().onGetMap(i_no - 1);
}

inline BOOL dComIfGs_isCollectMapTriforce(int i_no) {
    return g_dComIfG_gameInfo.save.getPlayer().getMap().isTriforce(i_no - 1);
}

inline void dComIfGs_offCollectMapTriforce(int i_no) {
    g_dComIfG_gameInfo.save.getPlayer().getMap().offTriforce(i_no - 1);
}

inline BOOL dComIfGs_isOpenCollectMap(int i_no) {
    return g_dComIfG_gameInfo.save.getPlayer().getMap().isOpenMap(i_no - 1);
}

inline void dComIfGs_onOpenCollectMap(int i_no) {
    g_dComIfG_gameInfo.save.getPlayer().getMap().onOpenMap(i_no - 1);
}

inline void dComIfGs_offOpenCollectMap(int i_no) {
    g_dComIfG_gameInfo.save.getPlayer().getMap().offOpenMap(i_no - 1);
}

inline BOOL dComIfGs_isCompleteCollectMap(int i_no) {
    return g_dComIfG_gameInfo.save.getPlayer().getMap().isCompleteMap(i_no - 1);
}

inline void dComIfGs_offCompleteCollectMap(int i_no) {
    g_dComIfG_gameInfo.save.getPlayer().getMap().offCompleteMap(i_no - 1);
}

inline s32 dComIfGs_getCollectMapNum() {
    return g_dComIfG_gameInfo.save.getPlayer().getMap().getCollectMapNum();
}

inline void dComIfGs_onSaveArriveGridForAgb(int i_no) {
    g_dComIfG_gameInfo.save.getPlayer().getMap().onSaveArriveGridForAgb(i_no);
}

inline BOOL dComIfGs_isSaveArriveGridForAgb(int i_no) {
    return g_dComIfG_gameInfo.save.getPlayer().getMap().isSaveArriveGridForAgb(i_no);
}

inline u8 dComIfGs_getArrowNum() {
    return g_dComIfG_gameInfo.save.getPlayer().getItemRecord().getArrowNum();
}

inline void dComIfGs_setArrowNum(u8 num) {
    g_dComIfG_gameInfo.save.getPlayer().getItemRecord().setArrowNum(num);
}

inline u8 dComIfGs_getBombNum() {
    return g_dComIfG_gameInfo.save.getPlayer().getItemRecord().getBombNum();
}

inline void dComIfGs_setBombNum(u8 num) {
    g_dComIfG_gameInfo.save.getPlayer().getItemRecord().setBombNum(num);
}

inline u8 dComIfGs_getPictureNum() {
    return g_dComIfG_gameInfo.save.getPlayer().getItemRecord().getPictureNum();
}

inline void dComIfGs_setPictureNum(u8 num) {
    g_dComIfG_gameInfo.save.getPlayer().getItemRecord().setPictureNum(num);
}

inline u8 dComIfGs_getBeastNum(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItemRecord().getBeastNum(i_idx);
}

inline void dComIfGs_setBeastNum(int i_idx, u8 num) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItemRecord().setBeastNum(i_idx, num);
}

inline u8 dComIfGs_getBaitNum(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItemRecord().getBaitNum(i_idx);
}

inline void dComIfGs_setBaitNum(int i_idx, u8 num) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItemRecord().setBaitNum(i_idx, num);
}

inline u8 dComIfGs_getReserveNum(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItemRecord().getReserveNum(i_idx);
}

inline void dComIfGs_setReserveNum(int i_idx, u8 num) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItemRecord().setReserveNum(i_idx, num);
}

inline void dComIfGs_setReserveItemChange(u8 i_itemBtn, u8 no) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setReserveItemChange(i_itemBtn, no);
}

inline u8 dComIfGs_checkReserveItemEmpty() {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().checkReserveItemEmpty();
}

inline void dComIfGs_setReserveItemEmpty() {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setReserveItemEmpty();
}

inline void dComIfGs_setReserveItemEmpty(u8 i_itemBtn) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setReserveItemEmpty(i_itemBtn);
}

inline void dComIfGs_setReserveBaitEmpty(u8 i_itemBtn) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setBaitItemEmpty(i_itemBtn);
}

inline void dComIfGs_setEventReg(u16 i_reg, u8 i_no) {
    g_dComIfG_gameInfo.save.getEvent().setEventReg(i_reg, i_no);
}

inline u8 dComIfGs_getEventReg(u16 i_reg) {
    return g_dComIfG_gameInfo.save.getEvent().getEventReg(i_reg);
}

inline BOOL dComIfGs_isOceanSvBit(u8 i_grid, u16 i_bit) {
    return g_dComIfG_gameInfo.save.getOcean().isOceanSvBit(i_grid, i_bit);
}

inline void dComIfGs_onOceanSvBit(u8 i_grid, u16 i_bit) {
    g_dComIfG_gameInfo.save.getOcean().onOceanSvBit(i_grid, i_bit);
}

inline BOOL dComIfGs_isEventBit(u16 id) {
    return g_dComIfG_gameInfo.save.getEvent().isEventBit(id);
}

inline void dComIfGs_onEventBit(u16 id) {
    g_dComIfG_gameInfo.save.getEvent().onEventBit(id);
}

inline void dComIfGs_offEventBit(u16 id) {
    g_dComIfG_gameInfo.save.getEvent().offEventBit(id);
}

inline BOOL dComIfGs_isTmpBit(u16 id) {
    return g_dComIfG_gameInfo.save.getTmp().isEventBit(id);
}

inline void dComIfGs_onTmpBit(u16 id) {
    g_dComIfG_gameInfo.save.getTmp().onEventBit(id);
}

inline void dComIfGs_offTmpBit(u16 id) {
    g_dComIfG_gameInfo.save.getTmp().offEventBit(id);
}

inline void dComIfGs_setTmpReg(u16 id, u8 no) {
    g_dComIfG_gameInfo.save.getTmp().setEventReg(id, no);
}

inline u8 dComIfGs_getTmpReg(u16 id) {
    return g_dComIfG_gameInfo.save.getTmp().getEventReg(id);
}

inline s16 dComIfGs_getStartPoint() {
    return g_dComIfG_gameInfo.save.getRestart().getStartPoint();
}

inline void dComIfGs_setRestartRoom(const cXyz& i_pos, s16 i_angle, s8 i_roomNo) {
    g_dComIfG_gameInfo.save.getRestart().setRoom(i_pos, i_angle, i_roomNo);
}

inline void dComIfGs_setRestartRoomParam(u32 i_param) {
    g_dComIfG_gameInfo.save.getRestart().setRoomParam(i_param);
}

inline s8 dComIfGs_getRestartRoomNo() {
    return g_dComIfG_gameInfo.save.getRestart().getRoomNo();
}

inline s8 dComIfGs_getRestartOption() {
    return g_dComIfG_gameInfo.save.getRestart().getRestartOption();
}

inline s16 dComIfGs_getRestartOptionPoint() {
    return g_dComIfG_gameInfo.save.getRestart().getRestartOptionPoint();
}

inline s8 dComIfGs_getRestartOptionRoomNo() {
    return g_dComIfG_gameInfo.save.getRestart().getRestartOptionRoomNo();
}

inline cXyz& dComIfGs_getRestartOptionPos() {
    return g_dComIfG_gameInfo.save.getRestart().getRestartOptionPos();
}

inline s16 dComIfGs_getRestartOptionAngleY() {
    return g_dComIfG_gameInfo.save.getRestart().getRestartOptionAngleY();
}

inline f32 dComIfGs_getLastSceneSpeedF() {
    return g_dComIfG_gameInfo.save.getRestart().getLastSpeedF();
}

inline u32 dComIfGs_getLastSceneMode() {
    return g_dComIfG_gameInfo.save.getRestart().getLastMode();
}

inline void dComIfGs_setRestartOption(s8 i_option) {
    g_dComIfG_gameInfo.save.getRestart().setRestartOption(i_option);
}

inline void dComIfGs_setRestartOption(cXyz* i_pos, s16 i_angle, s8 i_roomNo, s8 i_option) {
    g_dComIfG_gameInfo.save.getRestart().setRestartOption(i_option, i_pos, i_angle, i_roomNo);
    g_dComIfG_gameInfo.save.getPlayer().getPriest().set(i_option, *i_pos, i_angle, i_roomNo);
}

inline u32 dComIfGs_getRestartRoomParam() {
    return g_dComIfG_gameInfo.save.getRestart().getRoomParam();
}

inline cXyz& dComIfGs_getRestartRoomPos() {
    return g_dComIfG_gameInfo.save.getRestart().getRoomPos();
}

inline s16 dComIfGs_getRestartRoomAngleY() {
    return g_dComIfG_gameInfo.save.getRestart().getRoomAngleY();
}

inline void dComIfGs_setStartPoint(s16 i_point) {
    g_dComIfG_gameInfo.save.getRestart().setStartPoint(i_point);
}

inline s8 dComIfGs_getTurnRestartRoomNo() {
    return g_dComIfG_gameInfo.save.getTurnRestart().getRoomNo();
}

inline u32 dComIfGs_getTurnRestartParam() {
    return g_dComIfG_gameInfo.save.getTurnRestart().getParam();
}

inline cXyz& dComIfGs_getTurnRestartPos() {
    return g_dComIfG_gameInfo.save.getTurnRestart().getPos();
}

inline cXyz& dComIfGs_getTurnRestartShipPos() {
    return g_dComIfG_gameInfo.save.getTurnRestart().getShipPos();
}

inline s16 dComIfGs_getTurnRestartAngleY() {
    return g_dComIfG_gameInfo.save.getTurnRestart().getAngleY();
}

inline s16 dComIfGs_getTurnRestartShipAngleY() {
    return g_dComIfG_gameInfo.save.getTurnRestart().getShipAngleY();
}

#if VERSION > VERSION_DEMO
// The "HasShip" name is fake. These inlines don't exist in the demo, but must exist in the final release.
inline BOOL dComIfGs_getTurnRestartHasShip() {
    return g_dComIfG_gameInfo.save.getTurnRestart().getHasShip();
}

inline void dComIfGs_setTurnRestartHasShip(BOOL hasShip) {
    g_dComIfG_gameInfo.save.getTurnRestart().setHasShip(hasShip);
}
#endif

#if VERSION == VERSION_DEMO
inline void dComIfGs_setTurnRestart(const cXyz& i_pos, s16 i_angle, s8 i_roomNo, u32 i_param) {
    g_dComIfG_gameInfo.save.getTurnRestart().set(i_pos, i_angle, i_roomNo, i_param, i_pos, i_angle);
}

inline void dComIfGs_setTurnRestart(const cXyz& i_pos, s16 i_angle, s8 i_roomNo, u32 i_param, const cXyz& i_shipPos, s16 i_shipAngle) {
    g_dComIfG_gameInfo.save.getTurnRestart().set(i_pos, i_angle, i_roomNo, i_param, i_shipPos, i_shipAngle);
}
#else
inline void dComIfGs_setTurnRestart(const cXyz& i_pos, s16 i_angle, s8 i_roomNo, u32 i_param) {
    g_dComIfG_gameInfo.save.getTurnRestart().set(i_pos, i_angle, i_roomNo, i_param, i_pos, i_angle, FALSE);
}

// Note: The "BOOL i_hasShip" parameter doesn't exist in the demo, but was added for the final release.
inline void dComIfGs_setTurnRestart(const cXyz& i_pos, s16 i_angle, s8 i_roomNo, u32 i_param, const cXyz& i_shipPos, s16 i_shipAngle, BOOL i_hasShip) {
    g_dComIfG_gameInfo.save.getTurnRestart().set(i_pos, i_angle, i_roomNo, i_param, i_shipPos, i_shipAngle, i_hasShip);
}
#endif

inline void dComIfGs_setMemoryToCard(u8* i_cardPtr, int i_dataNum) {
    g_dComIfG_gameInfo.save.memory_to_card((char*)i_cardPtr, i_dataNum);
}

inline void dComIfGs_setInitDataToCard(u8* i_cardPtr, int i_dataNum) {
    g_dComIfG_gameInfo.save.initdata_to_card((char*)i_cardPtr, i_dataNum);
}

inline u8 dComIfGs_getDataNum() {
    return g_dComIfG_gameInfo.save.getDataNum();
}

inline void dComIfGs_setDataNum(u8 num) {
    g_dComIfG_gameInfo.save.setDataNum(num);
}

inline u8 dComIfGs_getNoFile() {
    return g_dComIfG_gameInfo.save.getNoFile();
}

inline void dComIfGs_setNoFile(u8 num) {
    g_dComIfG_gameInfo.save.setNoFile(num);
}

inline u64 dComIfGs_getMemCardCheckID() {
    return g_dComIfG_gameInfo.save.getMemCardCheckID();
}

inline u8 dComIfGs_getNewFile() {
    return g_dComIfG_gameInfo.save.getNewFile();
}

inline void dComIfGs_setNewFile(u8 file) {
    g_dComIfG_gameInfo.save.setNewFile(file);
}

inline void dComIfGs_setMemCardCheckID(u64 id) {
    g_dComIfG_gameInfo.save.setMemCardCheckID(id);
}

inline u8 dComIfGs_getPlayerPriestFlag() {
    return g_dComIfG_gameInfo.save.getPlayer().getPriest().getFlag();
}

inline cXyz& dComIfGs_getPlayerPriestPos() {
    return g_dComIfG_gameInfo.save.getPlayer().getPriest().getPos();
}

inline s16 dComIfGs_getPlayerPriestRotate() {
    return g_dComIfG_gameInfo.save.getPlayer().getPriest().getRotate();
}

inline s8 dComIfGs_getPlayerPriestRoomNo() {
    return g_dComIfG_gameInfo.save.getPlayer().getPriest().getRoomNo();
}

inline void dComIfGs_setPlayerPriest(u8 i_option, cXyz& i_pos, s16 i_angle, s8 i_roomNo) {
    g_dComIfG_gameInfo.save.getPlayer().getPriest().set(i_option, i_pos, i_angle, i_roomNo);
}

inline int dComIfGs_getTriforceNum() {
    return g_dComIfG_gameInfo.save.getPlayer().getCollect().getTriforceNum();
}

inline u8 dComIfGs_getOptRuby() {
    return g_dComIfG_gameInfo.save.getPlayer().getConfig().getRuby();
}

inline void dComIfGs_setOptRuby(u8 ruby) {
    g_dComIfG_gameInfo.save.getPlayer().getConfig().setRuby(ruby);
}

inline u8 dComIfGs_getOptSound() {
    return g_dComIfG_gameInfo.save.getPlayer().getConfig().getSound();
}

inline void dComIfGs_setOptSound(u8 mode) {
    g_dComIfG_gameInfo.save.getPlayer().getConfig().setSound(mode);
}

inline u8 dComIfGs_getOptAttentionType() {
    return g_dComIfG_gameInfo.save.getPlayer().getConfig().getAttentionType();
}

inline void dComIfGs_setOptAttentionType(u8 type) {
    g_dComIfG_gameInfo.save.getPlayer().getConfig().setAttentionType(type);
}

inline u8 dComIfGs_getOptVibration() {
    return g_dComIfG_gameInfo.save.getPlayer().getConfig().getVibration();
}

inline void dComIfGs_setOptVibration(u8 vib) {
    g_dComIfG_gameInfo.save.getPlayer().getConfig().setVibration(vib);
}

#if VERSION > VERSION_DEMO
/* Not present in debug maps, imitates TP version */
inline u8 dComIfGs_checkOptVibration() {
    return g_dComIfG_gameInfo.save.getPlayer().getConfig().checkVibration();
}
#endif

inline BOOL dComIfGs_isTbox(int i_no) {
    return g_dComIfG_gameInfo.save.getMemory().getBit().isTbox(i_no);
}

inline BOOL dComIfGs_isSaveTbox(int i_stageNo, int i_no) {
    return g_dComIfG_gameInfo.save.getSavedata().getSave(i_stageNo).getBit().isTbox(i_no);
}

inline void dComIfGs_onTbox(int i_no) {
    g_dComIfG_gameInfo.save.getMemory().getBit().onTbox(i_no);
}

inline void dComIfGs_onSaveTbox(int i_stageNo, int i_no) {
    g_dComIfG_gameInfo.save.getSavedata().getSave(i_stageNo).getBit().onTbox(i_no);
}

void dComIfGs_onStageTbox(int i_stageNo, int i_no);
BOOL dComIfGs_isStageTbox(int i_stageNo, int i_no);

/**
 * This does not appear in the demo debug maps, but it likely existed and was simply unused until the
 * final release based on the fact that dComIfGs_onSaveSwitch does appear in the maps.
 */
inline BOOL dComIfGs_isSaveSwitch(int i_stageNo, int i_no) {
    return g_dComIfG_gameInfo.save.getSavedata().getSave(i_stageNo).getBit().isSwitch(i_no);
}

inline void dComIfGs_onSaveSwitch(int i_stageNo, int i_no) {
    g_dComIfG_gameInfo.save.getSavedata().getSave(i_stageNo).getBit().onSwitch(i_no);
}

inline BOOL dComIfGs_isCollect(int i_idx, u8 i_item) {
    return g_dComIfG_gameInfo.save.getPlayer().getCollect().isCollect(i_idx, i_item);
}

inline void dComIfGs_onCollect(int i_idx, u8 i_item) {
    g_dComIfG_gameInfo.save.getPlayer().getCollect().onCollect(i_idx, i_item);
}

inline void dComIfGs_offCollect(int i_idx, u8 i_item) {
    g_dComIfG_gameInfo.save.getPlayer().getCollect().offCollect(i_idx, i_item);
}

inline u8 dComIfGs_checkCollect(int no) {
    return g_dComIfG_gameInfo.save.getPlayer().getCollect().checkCollect(no);
}

inline void dComIfGs_setCollect(int idx, u8 byte) {
    g_dComIfG_gameInfo.save.getPlayer().getCollect().setCollect(idx, byte);
}

inline BOOL dComIfGs_isTact(u8 i_no) {
    return g_dComIfG_gameInfo.save.getPlayer().getCollect().isTact(i_no);
}

inline void dComIfGs_onTact(u8 i_no) {
    g_dComIfG_gameInfo.save.getPlayer().getCollect().onTact(i_no);
}

inline BOOL dComIfGs_isTriforce(u8 i_no) {
    return g_dComIfG_gameInfo.save.getPlayer().getCollect().isTriforce(i_no);
}

inline void dComIfGs_onTriforce(u8 i_no) {
    g_dComIfG_gameInfo.save.getPlayer().getCollect().onTriforce(i_no);
}

inline BOOL dComIfGs_isSymbol(u8 i_no) {
    return g_dComIfG_gameInfo.save.getPlayer().getCollect().isSymbol(i_no);
}

inline void dComIfGs_onSymbol(u8 i_no) {
    g_dComIfG_gameInfo.save.getPlayer().getCollect().onSymbol(i_no);
}

inline BOOL dComIfGs_isDungeonItemMap() {
    return g_dComIfG_gameInfo.save.getMemory().getBit().isDungeonItemMap();
}

inline void dComIfGs_onDungeonItemMap() {
    g_dComIfG_gameInfo.save.getMemory().getBit().onDungeonItemMap();
}

inline BOOL dComIfGs_isDungeonItemCompass() {
    return g_dComIfG_gameInfo.save.getMemory().getBit().isDungeonItemCompass();
}

inline void dComIfGs_onDungeonItemCompass() {
    g_dComIfG_gameInfo.save.getMemory().getBit().onDungeonItemCompass();
}

inline BOOL dComIfGs_isDungeonItemBossKey() {
    return g_dComIfG_gameInfo.save.getMemory().getBit().isDungeonItemBossKey();
}

inline void dComIfGs_onDungeonItemBossKey() {
    g_dComIfG_gameInfo.save.getMemory().getBit().onDungeonItemBossKey();
}

inline void dComIfGs_onStageBossEnemy() {
    g_dComIfG_gameInfo.save.getMemory().getBit().onStageBossEnemy();
}

BOOL dComIfGs_isStageBossEnemy(int i_stageNo);

inline BOOL dComIfGs_isStageBossEnemy() {
    return g_dComIfG_gameInfo.save.getMemory().getBit().isStageBossEnemy();
}

inline BOOL dComIfGs_isStageBossEnemySaveBit(int i_stageNo) {
    return g_dComIfG_gameInfo.save.getSavedata().getSave(i_stageNo).getBit().isStageBossEnemy();
}

inline void dComIfGs_onStageLife() {
    g_dComIfG_gameInfo.save.getMemory().getBit().onStageLife();
}

BOOL dComIfGs_isStageLife(int i_stageNo);

inline BOOL dComIfGs_isStageLife() {
    return g_dComIfG_gameInfo.save.getMemory().getBit().isStageLife();
}

void dComIfGs_onStageLife(int i_stageNo);

inline void dComIfGs_onStageBossDemo() {
    g_dComIfG_gameInfo.save.getMemory().getBit().onStageBossDemo();
}

inline BOOL dComIfGs_isStageBossDemo() {
    return g_dComIfG_gameInfo.save.getMemory().getBit().isStageBossDemo();
}

inline BOOL dComIfGs_isStageBossDemoSaveBit(int i_stageNo) {
    return g_dComIfG_gameInfo.save.getSavedata().getSave(i_stageNo).getBit().isStageBossDemo();
}

inline void dComIfGs_onSwitch(int i_no, int i_roomNo) {
    g_dComIfG_gameInfo.save.onSwitch(i_no, i_roomNo);
}

inline void dComIfGs_offSwitch(int i_no, int i_roomNo) {
    g_dComIfG_gameInfo.save.offSwitch(i_no, i_roomNo);
}

inline BOOL dComIfGs_isSwitch(int i_no, int i_roomNo) {
    return g_dComIfG_gameInfo.save.isSwitch(i_no, i_roomNo);
}

inline void dComIfGs_revSwitch(int i_no, int i_roomNo) {
    g_dComIfG_gameInfo.save.revSwitch(i_no, i_roomNo);
}

inline void dComIfGs_onItem(int bitNo, int roomNo) {
    g_dComIfG_gameInfo.save.onItem(bitNo, roomNo);
}

inline BOOL dComIfGs_isItem(int bitNo, int roomNo) {
    return g_dComIfG_gameInfo.save.isItem(bitNo, roomNo);
}

inline void dComIfGs_onVisitedRoom(int i_no) {
    g_dComIfG_gameInfo.save.getMemory().getBit().onVisitedRoom(i_no);
}

inline BOOL dComIfGs_isVisitedRoom(int i_no) {
    return g_dComIfG_gameInfo.save.getMemory().getBit().isVisitedRoom(i_no);
}

inline void dComIfGs_clearRoomSwitch(int i_zoneNo) {
    g_dComIfG_gameInfo.save.getZone(i_zoneNo).getZoneBit().clearRoomSwitch();
}

inline void dComIfGs_removeZone(int i_zoneNo) {
    g_dComIfG_gameInfo.save.removeZone(i_zoneNo);
}

inline void dComIfGs_putSave(int i_stageNo) {
    g_dComIfG_gameInfo.save.putSave(i_stageNo);
}

inline void dComIfGs_getSave(int i_stageNo) {
    g_dComIfG_gameInfo.save.getSave(i_stageNo);
}

inline void dComIfGs_initDan(s8 i_stageNo) {
    g_dComIfG_gameInfo.save.initDan(i_stageNo);
}

inline void dComIfGs_onActor(int i_no, int i_roomNo) {
    g_dComIfG_gameInfo.save.onActor(i_no, i_roomNo);
}

inline BOOL dComIfGs_isActor(int i_no, int i_roomNo) {
    return g_dComIfG_gameInfo.save.isActor(i_no, i_roomNo);
}

/**
 * Returns which inventory slot the item equipped on a specific button is located in.
 * @param i_itemBtn The dItemButton_e of the button.
 * @return The index of the inventory slot for the item equipped on that button, or 0xFF for no item.
 */
inline u8 dComIfGs_getSelectItem(int i_itemBtn) {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getSelectItem(i_itemBtn);
}

/**
 * Sets which inventory slot the item equipped on a specific button is located in.
 * @param i_itemBtn The dItemButton_e of the button.
 * @param i_invIdx The index of the inventory slot, or 0xFF for no item.
 */
inline void dComIfGs_setSelectItem(int i_itemBtn, u8 i_invIdx) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().setSelectItem(i_itemBtn, i_invIdx);
}

inline u16 dComIfGs_getDate() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusB().getDate();
}

inline void dComIfGs_setDate(u16 i_date) {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusB().setDate(i_date);
}

inline f32 dComIfGs_getTime() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusB().getTime();
}

inline void dComIfGs_setTime(f32 i_time) {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusB().setTime(i_time);
}

inline BOOL dComIfGs_isGetItem(int i_field, u8 i_item) {
    return g_dComIfG_gameInfo.save.getPlayer().getGetItem().isItem(i_field, i_item);
}

inline void dComIfGs_onGetItem(int i_field, u8 i_item) {
    return g_dComIfG_gameInfo.save.getPlayer().getGetItem().onItem(i_field, i_item);
}

inline BOOL dComIfGs_isGetItemBeast(u8 i_beast) {
    return g_dComIfG_gameInfo.save.getPlayer().getGetBagItem().isBeast(i_beast);
}

inline void dComIfGs_onGetItemBeast(u8 i_beast) {
    g_dComIfG_gameInfo.save.getPlayer().getGetBagItem().onBeast(i_beast);
}

inline BOOL dComIfGs_isGetItemBait(u8 i_bait) {
    return g_dComIfG_gameInfo.save.getPlayer().getGetBagItem().isBait(i_bait);
}

inline void dComIfGs_onGetItemBait(u8 i_bait) {
    g_dComIfG_gameInfo.save.getPlayer().getGetBagItem().onBait(i_bait);
}

inline BOOL dComIfGs_isGetBottleItem(u8 i_itemNo) {
    return g_dComIfG_gameInfo.save.getPlayer().getGetItem().isBottleItem(i_itemNo);
}

inline void  dComIfGs_onGetBottleItem(u8 i_itemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getGetItem().onBottleItem(i_itemNo);
}

inline void dComIfGs_setBottleItemIn(u8 prevItemNo, u8 newItemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getItem().setBottleItemIn(prevItemNo, newItemNo);
}

inline void dComIfGs_setEmptyBottleItemIn(u8 i_itemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getItem().setEmptyBottleItemIn(i_itemNo);
}

inline void dComIfGs_setEmptyBottle() {
    g_dComIfG_gameInfo.save.getPlayer().getItem().setEmptyBottle();
}

inline void dComIfGs_setEquipBottleItemIn(u8 i_itemBtn, u8 i_itemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getItem().setEquipBottleItemIn(i_itemBtn, i_itemNo);
}

inline void dComIfGs_setEquipBottleItemEmpty(u8 i_itemBtn) {
    g_dComIfG_gameInfo.save.getPlayer().getItem().setEquipBottleItemEmpty(i_itemBtn);
}

inline void dComIfGs_setEquipBottleItemEmpty() {
    g_dComIfG_gameInfo.save.getPlayer().getItem().setEquipBottleItemEmpty();
}

inline u8 dComIfGs_checkBottle(u8 i_itemNo) {
    return g_dComIfG_gameInfo.save.getPlayer().getItem().checkBottle(i_itemNo);
}

inline BOOL dComIfGs_checkEmptyBottle() {
    return g_dComIfG_gameInfo.save.getPlayer().getItem().checkEmptyBottle();
}

inline BOOL dComIfGs_checkGetBottle() {
    u8 bottleCount = 0;
    for (int i = 0; i < 4; i++) {
        if (dComIfGs_getItem(dInvSlot_BOTTLE0_e + i) != dItem_NONE_e) {
            bottleCount++;
        }
    }
    return bottleCount != 0;
}

inline s16 dComIfGs_getWindY() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusB().getWindY();
}

inline s16 dComIfGs_getWindX() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusB().getWindX();
}

inline void dComIfGs_setWindY(s16 i_windY) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusB().setWindY(i_windY);
}

inline void dComIfGs_setWindX(s16 i_windX) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusB().setWindX(i_windX);
}

inline const char* dComIfGs_getPlayerName() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerInfo().getPlayerName();
}

inline void dComIfGs_setPlayerName(const char* name) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerInfo().setPlayerName(name);
}

inline u8 dComIfGs_getClearCount() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerInfo().getClearCount();
}

inline void dComIfGs_setClearCount(u8 count) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerInfo().setClearCount(count);
}

inline void dComIfGs_clearCountUp() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerInfo().clearCountUp();
}

inline void dComIfGs_addDeathCount() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerInfo().addDeathCount();
}

inline u8 dComIfGs_getRandomSalvagePoint() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerInfo().getRandomSalvage();
}

inline void dComIfGs_setRandomSalvagePoint(u8 point) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerInfo().setRandomSalvage(point);
}

inline u8 dComIfGs_getGbaRupeeCount() {
    return g_dComIfG_gameInfo.save.getDan().getGbaRupeeCount();
}

inline void dComIfGs_incGbaRupeeCount() {
    g_dComIfG_gameInfo.save.getDan().incGbaRupeeCount();
}

inline u8 dComIfGs_checkBaitItem(u8 item) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().checkBaitItem(item);
}

inline u8 dComIfGs_checkBaitItemEmpty() {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().checkBaitItemEmpty();
}

inline u8 dComIfGs_getBombMax() {
    return g_dComIfG_gameInfo.save.getPlayer().getItemMax().getBombNum();
}

inline void dComIfGs_setBombMax(u8 num) {
    g_dComIfG_gameInfo.save.getPlayer().getItemMax().setBombNum(num);
}

inline u8 dComIfGs_getArrowMax() {
    return g_dComIfG_gameInfo.save.getPlayer().getItemMax().getArrowNum();
}

inline void dComIfGs_setArrowMax(u8 num) {
    g_dComIfG_gameInfo.save.getPlayer().getItemMax().setArrowNum(num);
}

inline u16 dComIfGs_getLife() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getLife();
}

inline void dComIfGs_setLife(u16 life) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().setLife(life);
}

inline u16 dComIfGs_getMaxLife() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getMaxLife();
}

inline void dComIfGs_setMaxLife(u8 life) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().setMaxLife(life);
}

inline u8 dComIfGs_getMagic() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getMagic();
}

inline void dComIfGs_setMagic(u8 magic) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().setMagic(magic);
}

inline u8 dComIfGs_getMaxMagic() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getMaxMagic();
}

inline void dComIfGs_setMaxMagic(u8 magic) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().setMaxMagic(magic);
}

inline u8 dComIfGs_getKeyNum() {
    return g_dComIfG_gameInfo.save.getMemory().getBit().getKeyNum();
}

inline void dComIfGs_setKeyNum(u8 i_keyNum) {
    g_dComIfG_gameInfo.save.getMemory().getBit().setKeyNum(i_keyNum);
}

inline dSv_player_status_a_c* dComIfGs_getpPlayerStatusA() {
    return g_dComIfG_gameInfo.save.getPlayer().getpPlayerStatusA();
}

inline dSv_player_status_b_c* dComIfGs_getpPlayerStatusB() {
    return g_dComIfG_gameInfo.save.getPlayer().getpPlayerStatusB();
}

inline dSv_player_return_place_c* dComIfGs_getpPlayerReturnPlace() {
    return g_dComIfG_gameInfo.save.getPlayer().getpPlayerReturnPlace();
}

inline dSv_player_item_c* dComIfGs_getpItem() {
    return g_dComIfG_gameInfo.save.getPlayer().getpItem();
}

inline dSv_player_get_item_c* dComIfGs_getpGetItem() {
    return g_dComIfG_gameInfo.save.getPlayer().getpGetItem();
}

inline dSv_player_item_record_c* dComIfGs_getpItemRecord() {
    return g_dComIfG_gameInfo.save.getPlayer().getpItemRecord();
}

inline dSv_player_item_max_c* dComIfGs_getpItemMax() {
    return g_dComIfG_gameInfo.save.getPlayer().getpItemMax();
}

inline dSv_player_bag_item_c* dComIfGs_getpBagItem() {
    return g_dComIfG_gameInfo.save.getPlayer().getpBagItem();
}

inline dSv_player_get_bag_item_c* dComIfGs_getpGetBagItem() {
    return g_dComIfG_gameInfo.save.getPlayer().getpGetBagItem();
}

inline dSv_player_bag_item_record_c* dComIfGs_getpBagItemRecord() {
    return g_dComIfG_gameInfo.save.getPlayer().getpBagItemRecord();
}

inline dSv_player_collect_c* dComIfGs_getpCollect() {
    return g_dComIfG_gameInfo.save.getPlayer().getpCollect();
}

inline dSv_player_map_c* dComIfGs_getpMap() {
    return g_dComIfG_gameInfo.save.getPlayer().getpMap();
}

inline dSv_player_info_c* dComIfGs_getpPlayerInfo() {
    return g_dComIfG_gameInfo.save.getPlayer().getpPlayerInfo();
}

inline dSv_player_config_c* dComIfGs_getpConfig() {
    return g_dComIfG_gameInfo.save.getPlayer().getpConfig();
}

inline dSv_player_priest_c* dComIfGs_getpPriest() {
    return g_dComIfG_gameInfo.save.getPlayer().getpPriest();
}

inline dSv_player_status_c_c* dComIfGs_getpPlayerStatusC(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getpPlayerStatusC(i_idx);
}

inline dSv_memory_c* dComIfGs_getPCourseInfo() {
    return g_dComIfG_gameInfo.save.getPSave();
}

inline dSv_ocean_c* dComIfGs_getPOcean() {
    return g_dComIfG_gameInfo.save.getPOcean();
}

inline dSv_event_c* dComIfGs_getPEvent() {
    return g_dComIfG_gameInfo.save.getPEvent();
}

inline dSv_reserve_c* dComIfGs_getPReserve() {
    return g_dComIfG_gameInfo.save.getPReserve();
}

inline u8* dComIfGs_getPEventBit() {
    return g_dComIfG_gameInfo.save.getEvent().getPEventBit();
}

inline void dComIfGs_setCardToMemory(u8* i_cardPtr, int i_dataNum) {
    g_dComIfG_gameInfo.save.card_to_memory((char*)i_cardPtr, i_dataNum);
}

u8 dComIfGs_checkGetItemNum(u8 i_itemNo);

stage_scls_info_class* dComIfGd_getMeshSceneList(Vec& vec);

BOOL dComIfGs_checkSeaLandingEvent(s8 i_roomNo);

inline u16 dComIfGs_getFwaterTimer() {
    return g_dComIfG_gameInfo.save.getPlayer().getItemRecord().getTimer();
}

inline void dComIfGs_startFwaterTimer() {
    g_dComIfG_gameInfo.play.startFwaterTimer();
}

inline void dComIfGs_stopFwaterTimer() {
    g_dComIfG_gameInfo.play.stopFwaterTimer();
}

inline u8 dComIfGs_checkFwaterTimer() {
    return g_dComIfG_gameInfo.play.checkFwaterTimer();
}

inline void dComIfGs_resetFwaterTimer(u16) {
    // TODO
}

inline void dComIfGs_decFwaterTimer() {
    // TODO
}

void dComIfGs_setPlayerRecollectionData();
void dComIfGs_revPlayerRecollectionData();

/**
 * === PLAY ===
 */

inline void dComIfGp_init() {
    g_dComIfG_gameInfo.play.init();
}

inline void dComIfGp_itemDataInit() {
    g_dComIfG_gameInfo.play.itemInit();
}

void dComIfGp_setNextStage(const char* i_stageName, s16 i_point, s8 i_roomNo, s8 i_layer = -1,
                           f32 i_lastSpeed = 0.0f, u32 i_lastMode = 0, BOOL i_setPoint = TRUE,
                           s8 i_wipe = 0);
dStage_Ship_dt_c* dComIfGp_getShip(int i_roomNo, int param_1);
bool dComIfGp_getMapTrans(int i_roomNo, f32* o_transX, f32* o_transY, s16* o_angle);

inline camera_class* dComIfGp_getCamera(int idx) { return g_dComIfG_gameInfo.play.getCamera(idx); }
inline f32 dComIfGp_getCamZoomForcus(int idx) { return g_dComIfG_gameInfo.play.getCamZoomForcus(idx); }

inline const char* dComIfGp_getStartStageName() {
    return g_dComIfG_gameInfo.play.getStartStageName();
}

inline u32 dComIfGp_getNowStageNum() {
    return g_dComIfG_gameInfo.play.getNowStageNum();
}

inline u8 dComIfGp_checkStageName() {
    return g_dComIfG_gameInfo.play.checkStageName();
}

inline void dComIfGp_setStageNameOn(u8 idx) {
    g_dComIfG_gameInfo.play.setStageNameOn(idx);
}

inline void dComIfGp_setStageNameDelete() {
    g_dComIfG_gameInfo.play.setStageNameDelete();
}

inline void dComIfGp_setStageNameOff() {
    g_dComIfG_gameInfo.play.setStageNameOff();
}

inline u8 dComIfGp_getGameoverStatus() {
    return g_dComIfG_gameInfo.play.getGameoverStatus();
}

inline void dComIfGp_setGameoverStatus(u8 stts) {
    g_dComIfG_gameInfo.play.setGameoverStatus(stts);
}

inline int dComIfGp_getStartStageRoomNo() {
    return g_dComIfG_gameInfo.play.getStartStageRoomNo();
}

inline s8 dComIfGp_getStartStageLayer() {
    return g_dComIfG_gameInfo.play.getStartStageLayer();
}

inline s16 dComIfGp_getStartStagePoint() {
    return g_dComIfG_gameInfo.play.getStartStagePoint();
}

inline void dComIfGp_offEnableNextStage() {
    g_dComIfG_gameInfo.play.offEnableNextStage();
}

inline const char* dComIfGp_getNextStageName() {
    return g_dComIfG_gameInfo.play.getNextStageName();
}

inline dStage_startStage_c* dComIfGp_getNextStartStage() {
    return g_dComIfG_gameInfo.play.getNextStartStage();
}

inline dStage_startStage_c* dComIfGp_getStartStage() {
    return g_dComIfG_gameInfo.play.getStartStage();
}

inline void dComIfGp_setStartStage(dStage_startStage_c* p_startStage) {
    g_dComIfG_gameInfo.play.setStartStage(p_startStage);
}

inline s8 dComIfGp_getNextStageRoomNo() {
    return g_dComIfG_gameInfo.play.getNextStageRoomNo();
}

inline s8 dComIfGp_getNextStageLayer() {
    return g_dComIfG_gameInfo.play.getNextStageLayer();
}

inline s32 dComIfGp_getNextStageWipe() {
    return g_dComIfG_gameInfo.play.getNextStageWipe();
}

inline bool dComIfGp_isEnableNextStage() {
    return g_dComIfG_gameInfo.play.isEnableNextStage();
}

inline s16 dComIfGp_getNextStagePoint() {
    return g_dComIfG_gameInfo.play.getNextStagePoint();
}

inline fopAc_ac_c* dComIfGp_getPlayer(int idx) {
    return g_dComIfG_gameInfo.play.getPlayer(idx);
}

inline void dComIfGp_setPlayer(int idx, fopAc_ac_c* player) {
    g_dComIfG_gameInfo.play.setPlayer(idx, player);
}

inline void dComIfGp_setPlayerInfo(int idx, fopAc_ac_c* player, int cam) {
    g_dComIfG_gameInfo.play.setPlayerInfo(idx, player, cam);
}

inline void dComIfGp_setPlayerPtr(int idx, fopAc_ac_c* player) {
    g_dComIfG_gameInfo.play.setPlayerPtr(idx, player);
}

inline fopAc_ac_c* dComIfGp_getCb1Player() {
    return g_dComIfG_gameInfo.play.getPlayerPtr(1);
}

inline void dComIfGp_setCb1Player(fopAc_ac_c* player) {
    g_dComIfG_gameInfo.play.setPlayerPtr(1, player);
}

inline dStage_dt_c& dComIfGp_getStage() {
    return g_dComIfG_gameInfo.play.getStage();
}

inline roomRead_class* dComIfGp_getStageRoom() {
    return g_dComIfG_gameInfo.play.getStage().getRoom();
}

inline dStage_Multi_c* dComIfGp_getMulti() {
    return g_dComIfG_gameInfo.play.getStage().getMulti();
}

inline stage_envr_info_class* dComIfGp_getStageEnvrInfo() {
    return g_dComIfG_gameInfo.play.getStage().getEnvrInfo();
}

inline stage_palet_info_class* dComIfGp_getStagePaletteInfo() {
    return g_dComIfG_gameInfo.play.getStage().getPaletInfo();
}

inline stage_pselect_info_class* dComIfGp_getStagePselectInfo() {
    return g_dComIfG_gameInfo.play.getStage().getPselectInfo();
}

inline stage_vrbox_info_class* dComIfGp_getStageVrboxInfo() {
    return g_dComIfG_gameInfo.play.getStage().getVrboxInfo();
}

inline stage_stag_info_class* dComIfGp_getStageStagInfo() {
    return g_dComIfG_gameInfo.play.getStage().getStagInfo();
}

inline stage_plight_info_class* dComIfGp_getStagePlightInfo() {
    return g_dComIfG_gameInfo.play.getStage().getPlightInfo();
}

inline int dComIfGp_getStagePlightNumInfo() {
    return g_dComIfG_gameInfo.play.getStage().getPlightNumInfo();
}

inline stage_actor_class* dComIfGp_getStagePlayer() {
    return g_dComIfG_gameInfo.play.getStage().getPlayer();
}

inline u16 dComIfGp_getStagePlayerNum() {
    return g_dComIfG_gameInfo.play.getStage().getPlayerNum();
}

inline stage_scls_info_dummy_class* dComIfGp_getStageSclsInfo() {
    return g_dComIfG_gameInfo.play.getStage().getSclsInfo();
}

inline daShip_c* dComIfGp_getShipActor() {
    return (daShip_c*)g_dComIfG_gameInfo.play.getPlayerPtr(2);
}

inline void dComIfGp_setShipActor(fopAc_ac_c* player) {
    g_dComIfG_gameInfo.play.setPlayerPtr(2, player);
}

inline void dComIfGp_getIkadaShipBeforePos(Vec* o_pos) {
    *o_pos = g_dComIfG_gameInfo.play.mIkadaLinkPos;
}

inline void dComIfGp_setIkadaShipBeforePos(Vec& i_pos) {
    g_dComIfG_gameInfo.play.setIkadaShipBeforePos(i_pos);
}

inline void dComIfGp_setIkadaShipId(u8 i_id) {
    g_dComIfG_gameInfo.play.setIkadaShipId(i_id);
}

inline void dComIfGp_setIkadaShipBeforeRoomId(u8 i_roomId) {
    g_dComIfG_gameInfo.play.setIkadaShipBeforeRoomId(i_roomId);
}

inline u8 dComIfGp_getIkadaShipId() {
    return g_dComIfG_gameInfo.play.getIkadaShipId();
}

inline u8 dComIfGp_getIkadaShipBeforeRoomId() {
    return g_dComIfG_gameInfo.play.getIkadaShipBeforeRoomId();
}

inline dVibration_c& dComIfGp_getVibration() {
    return g_dComIfG_gameInfo.play.getVibration();
}

inline dDetect_c& dComIfGp_getDetect() {
    return g_dComIfG_gameInfo.play.getDetect();
}

inline dMagma_packet_c* dComIfGp_createMagma() { return g_dComIfG_gameInfo.play.createMagma(); }
inline dGrass_packet_c* dComIfGp_createGrass() { return g_dComIfG_gameInfo.play.createGrass(); }
inline dTree_packet_c* dComIfGp_createTree() { return g_dComIfG_gameInfo.play.createTree(); }
inline dFlower_packet_c* dComIfGp_createFlower() { return g_dComIfG_gameInfo.play.createFlower(); }
inline dWood::Packet_c* dComIfGp_createWood() { return g_dComIfG_gameInfo.play.createWood(); }

inline dMagma_packet_c* dComIfGp_getMagma() { return g_dComIfG_gameInfo.play.getMagma(); }
inline dGrass_packet_c* dComIfGp_getGrass() { return g_dComIfG_gameInfo.play.getGrass(); }
inline dTree_packet_c* dComIfGp_getTree() { return g_dComIfG_gameInfo.play.getTree(); }
inline dFlower_packet_c* dComIfGp_getFlower() { return g_dComIfG_gameInfo.play.getFlower(); }
inline dWood::Packet_c* dComIfGp_getWood() { return g_dComIfG_gameInfo.play.getWood(); }

inline void dComIfGp_executeMagma() { return g_dComIfG_gameInfo.play.executeMagma(); }
inline void dComIfGp_executeGrass() { return g_dComIfG_gameInfo.play.executeGrass(); }
inline void dComIfGp_executeTree() { return g_dComIfG_gameInfo.play.executeTree(); }
inline void dComIfGp_executeFlower() { return g_dComIfG_gameInfo.play.executeFlower(); }
inline void dComIfGp_executeWood() { return g_dComIfG_gameInfo.play.executeWood(); }

inline void dComIfGp_drawMagma() { return g_dComIfG_gameInfo.play.drawMagma(); }
inline void dComIfGp_drawGrass() { return g_dComIfG_gameInfo.play.drawGrass(); }
inline void dComIfGp_drawTree() { return g_dComIfG_gameInfo.play.drawTree(); }
inline void dComIfGp_drawFlower() { return g_dComIfG_gameInfo.play.drawFlower(); }
inline void dComIfGp_drawWood() { return g_dComIfG_gameInfo.play.drawWood(); }

inline void dComIfGp_removeMagma() { g_dComIfG_gameInfo.play.removeMagma(); }
inline void dComIfGp_removeGrass() { g_dComIfG_gameInfo.play.removeGrass(); }
inline void dComIfGp_removeTree() { g_dComIfG_gameInfo.play.removeTree(); }
inline void dComIfGp_removeWood() { g_dComIfG_gameInfo.play.removeWood(); }
inline void dComIfGp_removeFlower() { g_dComIfG_gameInfo.play.removeFlower(); }

inline JKRArchive* dComIfGp_getLkDemoAnmArchive() {
    return g_dComIfG_gameInfo.play.getLkDemoAnmArchive();
}

inline void dComIfGp_setLkDemoAnmArchive(JKRArchive* i_arc) {
    g_dComIfG_gameInfo.play.setLkDemoAnmArchive(i_arc);
}

inline s8 dComIfGp_getLkDemoAnmNo() {
    return g_dComIfG_gameInfo.play.getLkDemoAnmNo();
}

inline void dComIfGp_setLkDemoAnmNo(s8 idx) {
    g_dComIfG_gameInfo.play.setLkDemoAnmNo(idx);
}

inline void dComIfGp_setStatus(u16 status) {
    g_dComIfG_gameInfo.play.setStatus(status);
}

inline void dComIfGp_onStatus(u16 status) {
    g_dComIfG_gameInfo.play.onStatus(status);
}

inline void dComIfGp_setShipId(u8 i_id) {
    g_dComIfG_gameInfo.play.setShipId(i_id);
}

inline void dComIfGp_setShipRoomId(u8 i_id) {
    g_dComIfG_gameInfo.play.setShipRoomId(i_id);
}

inline u8 dComIfGp_getShipId() {
    return g_dComIfG_gameInfo.play.getShipId();
}

inline int dComIfGp_getShipRoomId() {
    return g_dComIfG_gameInfo.play.getShipRoomId();
}

inline u8* dComIfGp_getPlayerInfoBuffer() {
    return g_dComIfG_gameInfo.play.getPlayerInfoBuffer();
}

inline void dComIfGp_setPlayerInfoBufferStageNo(u8 i_stageno) {
    g_dComIfG_gameInfo.play.setPlayerInfoBufferStageNo(i_stageno);
}

inline u8 dComIfGp_getPlayerInfoBufferStageNo() {
    return g_dComIfG_gameInfo.play.getPlayerInfoBufferStageNo();
}

inline void dComIfGp_setAgb(fopAc_ac_c* i_agb) {
    g_dComIfG_gameInfo.play.setAgb(i_agb);
}

inline daAgb_c* dComIfGp_getAgb() {
    return g_dComIfG_gameInfo.play.getAgb();
}

inline fopAc_ac_c* dComIfGp_getLinkPlayer() {
    return g_dComIfG_gameInfo.play.getPlayerPtr(0);
}

inline void dComIfGp_setLinkPlayer(fopAc_ac_c* player) {
    g_dComIfG_gameInfo.play.setPlayerPtr(0, player);
}

inline void dComIfGp_setWindowNum(int num) {
    g_dComIfG_gameInfo.play.setWindowNum(num);
}

inline int dComIfGp_getCameraPlayer1ID(int idx) {
    return g_dComIfG_gameInfo.play.getCameraPlayer1ID(idx);
}

inline int dComIfGp_getCameraPlayer2ID(int idx) {
    return g_dComIfG_gameInfo.play.getCameraPlayer2ID(idx);
}

inline int dComIfGp_getCameraWinID(int idx) {
    return g_dComIfG_gameInfo.play.getCameraWinID(idx);
}

inline int dComIfGp_getPlayerCameraID(int idx) {
    return g_dComIfG_gameInfo.play.getPlayerCameraID(idx);
}

inline u32 dComIfGp_checkCameraAttentionStatus(int idx, u32 flag) {
    return g_dComIfG_gameInfo.play.checkCameraAttentionStatus(idx, flag);
}

inline void dComIfGp_onCameraAttentionStatus(int i, u32 flag) {
    g_dComIfG_gameInfo.play.onCameraAttentionStatus(i, flag);
}

inline void dComIfGp_offCameraAttentionStatus(int i, u32 flag) {
    g_dComIfG_gameInfo.play.offCameraAttentionStatus(i, flag);
}

inline void dComIfGp_setCamera(int i, camera_class* cam) {
    g_dComIfG_gameInfo.play.setCamera(i, cam);
}

inline void dComIfGp_setCameraInfo(int idx, camera_class* camera, int dlst, int cam, int p5) {
    g_dComIfG_gameInfo.play.setCameraInfo(idx, camera, dlst, cam, p5);
}

inline void dComIfGp_setCameraZoomScale(int i_no, f32 i_scale) {
    g_dComIfG_gameInfo.play.setCameraZoomScale(i_no, i_scale);
}

inline f32 dComIfGp_getCameraZoomScale(int i_no) {
    return g_dComIfG_gameInfo.play.getCameraZoomScale(i_no);
}

inline void dComIfGp_setCameraZoomForcus(int i_no, f32 i_focus) {
    g_dComIfG_gameInfo.play.setCameraZoomForcus(i_no, i_focus);
}

inline f32 dComIfGp_getCameraZoomForcus(int i_no) {
    return g_dComIfG_gameInfo.play.getCameraZoomForcus(i_no);
}

inline u32 dComIfGp_getCameraAttentionStatus(int i_no) {
    return g_dComIfG_gameInfo.play.getCameraAttentionStatus(i_no);
}

inline void dComIfGp_saveCameraPosition(int i, cXyz* i_pos, cXyz* i_target, f32 i_fovy, s16 i_bank) {
    g_dComIfG_gameInfo.play.saveCameraPosition(i, i_pos, i_target, i_fovy, i_bank);
}

inline void dComIfGp_loadCameraPosition(int i, cXyz* o_pos, cXyz* o_target, f32* o_fovy, s16* o_bank) {
    g_dComIfG_gameInfo.play.loadCameraPosition(i, o_pos, o_target, o_fovy, o_bank);
}

inline int dComIfGp_getItemRupeeCount() {
    return g_dComIfG_gameInfo.play.getItemRupeeCount();
}

inline void dComIfGp_setItemRupeeCount(s32 count) {
    g_dComIfG_gameInfo.play.setItemRupeeCount(count);
}

inline s16 dComIfGp_getMessageSetNumber() {
    return g_dComIfG_gameInfo.play.getMessageSetNumber();
}

inline void dComIfGp_setMessageSetNumber(s16 num) {
    g_dComIfG_gameInfo.play.setMessageSetNumber(num);
}

inline u16 dComIfGp_getItemNowLife() {
    return g_dComIfG_gameInfo.play.getItemNowLife();
}

inline void dComIfGp_setItemNowLife(u16 life) {
    g_dComIfG_gameInfo.play.setItemNowLife(life);
}

inline f32 dComIfGp_getItemLifeCount() {
    return g_dComIfG_gameInfo.play.getItemLifeCount();
}

inline void dComIfGp_setItemLifeCount(f32 amount) {
    g_dComIfG_gameInfo.play.setItemLifeCount(amount);
}

inline s16 dComIfGp_getItemMaxLifeCount() {
    return g_dComIfG_gameInfo.play.getItemMaxLifeCount();
}

inline void dComIfGp_setItemMaxLifeCount(s16 num) {
    g_dComIfG_gameInfo.play.setItemMaxLifeCount(num);
}

inline void dComIfGp_setNpcNameMessageID(u32 id) {
    g_dComIfG_gameInfo.play.setNpcNameMessageID(id);
}

inline void dComIfGp_setItemNameMessageID(u32 id) {
    g_dComIfG_gameInfo.play.setItemNameMessageID(id);
}

inline s16 dComIfGp_getItemKeyNumCount() {
    return g_dComIfG_gameInfo.play.getItemKeyNumCount();
}

inline void dComIfGp_setItemKeyNumCount(s16 num) {
    g_dComIfG_gameInfo.play.setItemKeyNumCount(num);
}

inline s32 dComIfGp_getItemTimeCount() {
    return g_dComIfG_gameInfo.play.getItemTimeCount();
}

inline void dComIfGp_setItemTimeCount(s32 time) {
    g_dComIfG_gameInfo.play.setItemTimeCount(time);
}

inline void dComIfGp_clearItemTimeCount() {
    g_dComIfG_gameInfo.play.clearItemTimeCount();
}

inline s32 dComIfGp_getItemTimeMax() {
    return g_dComIfG_gameInfo.play.getItemTimeMax();
}

inline void dComIfGp_setItemTimeMax(s32 time) {
    g_dComIfG_gameInfo.play.setItemTimeMax(time);
}

inline bool dComIfGp_getItemSwimTimerStatus() {
    return g_dComIfG_gameInfo.play.getItemSwimTimerStatus();
}

inline void dComIfGp_startItemSwimTimer() {
    g_dComIfG_gameInfo.play.startItemSwimTimer();
}

inline void dComIfGp_stopItemSwimTimer() {
    g_dComIfG_gameInfo.play.stopItemSwimTimer();
}

inline void dComIfGp_setMessageCountNumber(s16 num) {
    g_dComIfG_gameInfo.play.setMessageCountNumber(num);
}

inline s16 dComIfGp_getMessageCountNumber() {
    return g_dComIfG_gameInfo.play.getMessageCountNumber();
}

inline s32 dComIfGp_checkStatus(u16 flags) {
    return g_dComIfG_gameInfo.play.checkStatus(flags);
}

inline s16 dComIfGp_getItemMagicCount() {
    return g_dComIfG_gameInfo.play.getItemMagicCount();
}

inline void dComIfGp_setItemMagicCount(s16 magic) {
    g_dComIfG_gameInfo.play.setItemMagicCount(magic);
}

inline s16 dComIfGp_getItemMaxMagicCount() {
    return g_dComIfG_gameInfo.play.getItemMaxMagicCount();
}

inline void dComIfGp_setItemMaxMagicCount(s16 magic) {
    g_dComIfG_gameInfo.play.setItemMaxMagicCount(magic);
}

inline s16 dComIfGp_getItemBombNumCount() {
    return g_dComIfG_gameInfo.play.getItemBombNumCount();
}

inline void dComIfGp_setItemBombNumCount(s16 num) {
    g_dComIfG_gameInfo.play.setItemBombNumCount(num);
}

inline s16 dComIfGp_getItemArrowNumCount() {
    return g_dComIfG_gameInfo.play.getItemArrowNumCount();
}

inline void dComIfGp_setItemArrowNumCount(s16 num) {
    return g_dComIfG_gameInfo.play.setItemArrowNumCount(num);
}

inline void dComIfGp_setItemBeastNumCount(int i_idx, s16 num) {
    g_dComIfG_gameInfo.play.setItemBeastNumCount(i_idx, num);
}

inline s16 dComIfGp_getItemBeastNumCount(int i_idx) {
    return g_dComIfG_gameInfo.play.getItemBeastNumCount(i_idx);
}

inline u8 dComIfGp_getScopeType() {
    return g_dComIfG_gameInfo.play.getScopeType();
}

inline void dComIfGp_setScopeType(u8 type) {
    g_dComIfG_gameInfo.play.setScopeType(type);
}

inline u8 dComIfGp_getOperateWind() {
    return g_dComIfG_gameInfo.play.getOperateWind();
}

inline void dComIfGp_setOperateWindCancelOff() {
    g_dComIfG_gameInfo.play.setOperateWindCancelOff();
}

inline void dComIfGp_setOperateWindChangeOff() {
    g_dComIfG_gameInfo.play.setOperateWindChangeOff();
}

inline void dComIfGp_setOperateWindOn() {
    g_dComIfG_gameInfo.play.setOperateWindOn();
}

inline void dComIfGp_setMesgSendButton(u8 button) {
    g_dComIfG_gameInfo.play.setMesgSendButton(button);
}

inline u8 dComIfGp_checkMesgSendButton() {
    return g_dComIfG_gameInfo.play.checkMesgSendButton();
}

inline void dComIfGp_setMesgCancelButton(u8 button) {
    g_dComIfG_gameInfo.play.setMesgCancelButton(button);
}

inline u8 dComIfGp_checkMesgCancelButton() {
    return g_dComIfG_gameInfo.play.checkMesgCancelButton();
}

inline u32 dComIfGp_checkPlayerStatus0(int param_0, u32 flag) {
    return g_dComIfG_gameInfo.play.checkPlayerStatus(param_0, 0, flag);
}

inline u32 dComIfGp_checkPlayerStatus1(int param_0, u32 flag) {
    return g_dComIfG_gameInfo.play.checkPlayerStatus(param_0, 1, flag);
}

inline void dComIfGp_setPlayerStatus0(int param_0, u32 flag) {
    g_dComIfG_gameInfo.play.setPlayerStatus(param_0, 0, flag);
}

inline void dComIfGp_setPlayerStatus1(int param_0, u32 flag) {
    g_dComIfG_gameInfo.play.setPlayerStatus(param_0, 1, flag);
}

inline void dComIfGp_clearPlayerStatus0(int param_0, u32 flag) {
    g_dComIfG_gameInfo.play.clearPlayerStatus(param_0, 0, flag);
}

inline void dComIfGp_clearPlayerStatus1(int param_0, u32 flag) {
    g_dComIfG_gameInfo.play.clearPlayerStatus(param_0, 1, flag);
}

inline void dComIfGp_onMenuCollect() {
    g_dComIfG_gameInfo.play.onMenuCollect();
}

/**
 * Returns which item is on a specific button.
 * @param i_itemBtn The dItemButton_e of the button.
 * @return The item number of the item in that slot, or 0xFF for no item.
 */
inline u8 dComIfGp_getSelectItem(int i_itemBtn) {
    return g_dComIfG_gameInfo.play.getSelectItem(i_itemBtn);
}

/**
 * Updates which item is on a specific button to match which item is in the inventory slot correspond to that button.
 * @param i_itemBtn The dItemButton_e of the button.
 */
inline void dComIfGp_setSelectItem(int i_itemBtn) {
    if (dComIfGs_getSelectItem(i_itemBtn) != dInvSlot_NONE_e) {
        int invIdx = dComIfGs_getSelectItem(i_itemBtn);
        u8 itemNo = dComIfGs_getItem(invIdx);
        g_dComIfG_gameInfo.play.setSelectItem(i_itemBtn, itemNo);

        invIdx = dComIfGs_getSelectItem(i_itemBtn);
        itemNo = dComIfGs_getItem(invIdx);
        if (itemNo == dItem_NONE_e) {
            dComIfGs_setSelectItem(i_itemBtn, dInvSlot_NONE_e);
        }
    } else {
        g_dComIfG_gameInfo.play.setSelectItem(i_itemBtn, dItem_NONE_e);
    }
}

inline void dComIfGp_setSelectEquip(int idx, u8 itemNo) {
    g_dComIfG_gameInfo.play.setSelectEquip(idx, itemNo);
}

inline void dComIfGp_setItem(u8 slot, u8 i_itemNo) {
    g_dComIfG_gameInfo.play.setItem(slot, i_itemNo);
}

inline u8 dComIfGp_getScopeMesgStatus() {
    return g_dComIfG_gameInfo.play.getScopeMesgStatus();
}

inline void dComIfGp_setScopeMesgStatus(u8 status) {
    g_dComIfG_gameInfo.play.setScopeMesgStatus(status);
}

inline void dComIfGp_setCurrentGrafPort(J2DOrthoGraph* i_graf) {
    g_dComIfG_gameInfo.play.setCurrentGrafPort(i_graf);
}

inline u8 dComIfGp_getMiniGameType() {
    // TODO add enum for minigame type.
    // 0 for none, 8 for shooting the fishman, 2/6 for orca, 7 for mail sorting, etc
    return g_dComIfG_gameInfo.play.getMiniGameType();
}

inline void dComIfGp_startMiniGame(u8 i_gameType) {
    g_dComIfG_gameInfo.play.startMiniGame(i_gameType);
}

inline void dComIfGp_endMiniGame(u16 i_gameType) {
    g_dComIfG_gameInfo.play.endMiniGame(i_gameType);
}

inline void dComIfGp_setMiniGameResult(u8 result) {
    g_dComIfG_gameInfo.play.setMiniGameResult(result);
}

inline u8 dComIfGp_getMiniGameResult() {
    return g_dComIfG_gameInfo.play.getMiniGameResult();
}

enum dActionStatus_e {
    /* 0x00 */ dActStts_BLANK_e,
    /* 0x01 */ dActStts_LOOK_e, // "Look"
    /* 0x02 */ dActStts_SPEAK_e, // "Speak"
    /* 0x03 */ dActStts_CHARTS_e, // "Charts"
    /* 0x04 */ dActStts_LIFT_e, // "Lift"
    /* 0x05 */ dActStts_CLIMB_e, // "Climb"
    /* 0x06 */ dActStts_LET_GO_e, // "Let Go"
    /* 0x07 */ dActStts_RETURN_e, // "Return"
    /* 0x08 */ dActStts_PUT_AWAY_e, // "Put Away"
    /* 0x09 */ dActStts_DROP_e, // "Drop"
    /* 0x0A */ dActStts_CHECK_e, // "Check"
    /* 0x0B */ dActStts_OPEN_e, // "Open"
    /* 0x0C */ dActStts_ATTACK_e, // "Attack"
    /* 0x0D */ dActStts_ba_osu, // "おす"
    /* 0x0E */ dActStts_THROW_e, // "Throw"
    /* 0x0F */ dActStts_CROUCH_e, // "Crouch"
    /* 0x10 */ dActStts_SIDLE_e, // "Sidle"
    /* 0x11 */ dActStts_GRAB_e, // "Grab"
    /* 0x12 */ dActStts_JUMP_e, // "Jump"
    /* 0x13 */ dActStts_STOP_e, // "Stop"
    /* 0x14 */ dActStts_ba_haru, // "はる"
    /* 0x15 */ dActStts_ba_tatamu, // "たたむ"
    /* 0x16 */ dActStts_LET_GO_ROPE_e, // "Let Go"
    /* 0x17 */ dActStts_CHOOSE_e, // "Choose"
    /* 0x18 */ dActStts_ba_kogu, // "こぐ"
    /* 0x19 */ dActStts_NEXT_e, // "Next"
    /* 0x1A */ dActStts_PARRY_e,
    /* 0x1B */ dActStts_PICK_UP_e, // "Pick Up"
    /* 0x1C */ dActStts_GET_IN_SHIP_e, // "Get In"
    /* 0x1D */ dActStts_GET_OUT_SHIP_e, // "Get Out"
    /* 0x1E */ dActStts_ba_save, // "セーブ"
    /* 0x1F */ dActStts_ba_option, // "オプション"
    /* 0x20 */ dActStts_TAKE_PHOTO_e, // "Take Photo"
    /* 0x21 */ dActStts_INFO_e, // "Info"
    /* 0x22 */ dActStts_SWAP_MODES_e, // "Swap Modes"
    /* 0x23 */ dActStts_FLY_e, // "Fly"
    /* 0x24 */ dActStts_CALL_e, // "Call"
    /* 0x25 */ dActStts_BID_e, // "Bid"
    /* 0x26 */ dActStts_READ_e, // "Read"
    /* 0x27 */ dActStts_CANCEL_e, // "Cancel"
    /* 0x28 */ dActStts_ba_kakudai, // "拡大"
    /* 0x29 */ dActStts_ba_hikaku, // "ひかく"
    /* 0x2A */ dActStts_ba_zoom01, // "Zoom 1"
    /* 0x2B */ dActStts_ba_zoom02, // "Zoom 2"
    /* 0x2C */ dActStts_CRUISE_e, // "Cruise"
    /* 0x2D */ dActStts_ba_nageru__dupe_2D, // TODO: special case
    /* 0x2E */ dActStts_ba_motu__dupe_2E, // TODO: special case, use medlis' harp to reflect light?
    /* 0x2F */ dActStts_SWING_e, // "Swing"
    /* 0x30 */ dActStts_SEA_CHART_e, // "Sea Chart"
    /* 0x31 */ dActStts_ba_sake__dupe_31, // TODO: special case
    /* 0x32 */ dActStts_ba_modoru__dupe_32, // TODO
    /* 0x33 */ dActStts_ba_save__dupe_33, // TODO
    /* 0x34 */ dActStts_ba_save__dupe_34, // TODO
    /* 0x35 */ dActStts_sword_01, // TODO
    /* 0x36 */ dActStts_DEFEND_e, // "Defend"
    /* 0x37 */ dActStts_boko_stick, // TODO
    /* 0x38 */ dActStts_hatchet, // TODO
    /* 0x39 */ dActStts_iron_club, // TODO
    /* 0x3A */ dActStts_longsword, // TODO
    /* 0x3B */ dActStts_spear, // TODO
    /* 0x3C */ dActStts_spear__dupe_3C, // TODO
    /* 0x3D */ dActStts_bow_01, // TODO
    /* 0x3E */ dActStts_HIDDEN_e, // Hides the entire button itself, not just the text on the button
    /* 0x43 */ dActStts_UNK43 = 0x43, // TODO
};

// R Button
inline u8 dComIfGp_getRStatus() {
    return g_dComIfG_gameInfo.play.getRStatus();
}

// R Button
inline void dComIfGp_setRStatus(u8 status) {
    g_dComIfG_gameInfo.play.setRStatus(status);
}

// B Button
inline u8 dComIfGp_getAStatus() {
    return g_dComIfG_gameInfo.play.getAStatus();
}

// B Button
inline void dComIfGp_setAStatus(u8 status) {
    g_dComIfG_gameInfo.play.setAStatus(status);
}

// A Button
inline u8 dComIfGp_getDoStatus() {
    return g_dComIfG_gameInfo.play.getDoStatus();
}

// A Button
inline void dComIfGp_setDoStatus(u8 status) {
    g_dComIfG_gameInfo.play.setDoStatus(status);
}

// R Button
inline u8 dComIfGp_getRStatusForce() {
    return g_dComIfG_gameInfo.play.getRStatusForce();
}

// R Button
inline void dComIfGp_setRStatusForce(u8 status) {
    g_dComIfG_gameInfo.play.setRStatusForce(status);
}

// B Button
inline u8 dComIfGp_getAStatusForce() {
    return g_dComIfG_gameInfo.play.getAStatusForce();
}

// B Button
inline void dComIfGp_setAStatusForce(u8 value) {
    g_dComIfG_gameInfo.play.setAStatusForce(value);
}

// A Button
inline u8 dComIfGp_getDoStatusForce() {
    return g_dComIfG_gameInfo.play.getDoStatusForce();
}

// A Button
inline void dComIfGp_setDoStatusForce(u8 value) {
    g_dComIfG_gameInfo.play.setDoStatusForce(value);
}

inline u8 dComIfGp_getPictureStatus() {
    return g_dComIfG_gameInfo.play.getPictureStatus();
}

inline void dComIfGp_setPictureStatusOn() {
    g_dComIfG_gameInfo.play.setPictureStatusOn();
}

inline void dComIfGp_setPictureStatusGetOn(u8 to_set){
    g_dComIfG_gameInfo.play.setPictureStatusGetOn(to_set);
}

inline s16 dComIfGp_getMiniGameRupee() {
    return g_dComIfG_gameInfo.play.getMiniGameRupee();
}

inline void dComIfGp_setMiniGameRupee(s16 count) {
    return g_dComIfG_gameInfo.play.setMiniGameRupee(count);
}

inline void dComIfGp_plusMiniGameRupee(s16 count) {
    g_dComIfG_gameInfo.play.plusMiniGameRupee(count);
}

inline s32 dComIfGp_getWindowNum() { return g_dComIfG_gameInfo.play.getWindowNum(); }
inline void dComIfGp_setWindowNum(u8 num) { g_dComIfG_gameInfo.play.setWindowNum(num); }
inline dDlst_window_c * dComIfGp_getWindow(int idx) { return g_dComIfG_gameInfo.play.getWindow(idx); }
inline void dComIfGp_setWindow(int idx, f32 x, f32 y, f32 w, f32 h, f32 n, f32 f, int cameraID, int mode) {
    g_dComIfG_gameInfo.play.setWindow(idx, x, y, w, h, n, f, cameraID, mode);
}
inline J2DOrthoGraph* dComIfGp_getCurrentGrafPort() { return g_dComIfG_gameInfo.play.getCurrentGrafPort(); }
inline void dComIfGp_setCurrentWindow(dDlst_window_c* window) { return g_dComIfG_gameInfo.play.setCurrentWindow(window); }
inline void dComIfGp_setCurrentView(view_class* view) { return g_dComIfG_gameInfo.play.setCurrentView(view); }
inline view_port_class* dComIfGp_getCurrentViewport() { return g_dComIfG_gameInfo.play.getCurrentViewport(); }
inline void dComIfGp_setCurrentViewport(view_port_class* viewport) { return g_dComIfG_gameInfo.play.setCurrentViewport(viewport); }

inline dADM_CharTbl* dComIfGp_CharTbl() {
    return &g_dComIfG_gameInfo.play.mADM.mCharTbl;
}

inline JKRExpHeap* dComIfGp_getExpHeap2D() { return g_dComIfG_gameInfo.play.getExpHeap2D(); }
inline void dComIfGp_setExpHeap2D(void* heap) { g_dComIfG_gameInfo.play.setExpHeap2D(heap); }

inline u8 dComIfGp_isHeapLockFlag() {
    return g_dComIfG_gameInfo.play.isHeapLockFlag();
}

inline void dComIfGp_setHeapLockFlag(u8 flag) {
    g_dComIfG_gameInfo.play.setHeapLockFlag(flag);
}

inline void dComIfGp_offHeapLockFlag() {
    g_dComIfG_gameInfo.play.offHeapLockFlag();
}

#if VERSION > VERSION_DEMO
// Inline name from TP debug.
inline u8 dComIfGp_getNowVibration() {
    return g_dComIfG_gameInfo.play.getNowVibration();
}

// Inline name from TP debug.
inline void dComIfGp_setNowVibration(u8 vibration) {
    g_dComIfG_gameInfo.play.setNowVibration(vibration);
}
#endif

#if VERSION > VERSION_JPN
// Inline name is official because while it's not present in the JPN debug maps, it is present in
// the USA release maps because there was one TU where it failed to get inlined (f_op_msg_mng).
inline u8 dComIfGs_getPalLanguage() {
    return g_dComIfG_gameInfo.play.getPalLanguage();
}

// Inline name is fake, but guessed based on the above inline.
inline void dComIfGs_setPalLanguage(u8 lang) {
    g_dComIfG_gameInfo.play.setPalLanguage(lang);
}
#endif

inline void dComIfGp_2dShowOn() {
    g_dComIfG_gameInfo.play.show2dOn();
}

inline void dComIfGp_2dShowOff() {
    g_dComIfG_gameInfo.play.show2dOff();
}

inline bool dComIfGp_2dShowCheck() {
    return g_dComIfG_gameInfo.play.show2dCheck();
}

inline u8 dComIfGp_getMelodyNum() {
    return g_dComIfG_gameInfo.play.getMelodyNum();
}

inline void dComIfGp_setMelodyNum(u8 melody) {
    g_dComIfG_gameInfo.play.setMelodyNum(melody);
}

inline u8 dComIfGp_getMesgAnimeAttrInfo() {
    return g_dComIfG_gameInfo.play.getBaseAnimeID();
}

inline void dComIfGp_setMesgAnimeAttrInfo(u8 id) {
    g_dComIfG_gameInfo.play.setBaseAnimeID(id);
}

inline void dComIfGp_clearMesgAnimeAttrInfo() {
    g_dComIfG_gameInfo.play.clearBaseAnimeID();
}

inline u8 dComIfGp_getMesgAnimeTagInfo() {
    return g_dComIfG_gameInfo.play.getNowAnimeID();
}

inline void dComIfGp_setMesgAnimeTagInfo(u8 id) {
    g_dComIfG_gameInfo.play.setNowAnimeID(id);
}

inline void dComIfGp_clearMesgAnimeTagInfo() {
    g_dComIfG_gameInfo.play.clearNowAnimeID();
}

inline int dComIfGp_getMesgCameraTagInfo() {
    return g_dComIfG_gameInfo.play.getMesgCamInfoID();
}

inline void dComIfGp_clearMesgCameraTagInfo() {
    g_dComIfG_gameInfo.play.clearMesgCamInfoID();
}

inline u8 dComIfGp_getMesgStatus() {
    return g_dComIfG_gameInfo.play.getMesgStatus();
}

inline void dComIfGp_setMesgStatus(u8 status) {
    g_dComIfG_gameInfo.play.setMesgStatus(status);
}

inline void dComIfGp_setMesgCameraTagInfo(int id) {
    g_dComIfG_gameInfo.play.setMesgCamInfoID(id);
}

inline void dComIfGp_setMesgCameraAttrInfo(int param_1) {
    g_dComIfG_gameInfo.play.setMesgCamInfoBasicID(param_1);
}

inline dComIfG_MesgCamInfo_c* dComIfGp_getMesgCameraInfo() {
    return g_dComIfG_gameInfo.play.getMesgCamInfo();
}

inline u8 dComIfGp_checkMesgBgm() {
    return g_dComIfG_gameInfo.play.checkMesgBgm();
}

inline void dComIfGp_setMesgBgmOff() {
    g_dComIfG_gameInfo.play.setMesgBgm(0);
}

inline void dComIfGp_setMesgBgmOn() {
    g_dComIfG_gameInfo.play.setMesgBgm(1);
}

inline void dComIfGp_setMesgBgmOn2() {
    g_dComIfG_gameInfo.play.setMesgBgm(2);
}

inline JKRAramBlock* dComIfGp_getPictureBoxData(int i) {
    return g_dComIfG_gameInfo.play.getPictureBoxData(i);
}

inline void dComIfGp_setPictureBoxData(JKRAramBlock* aramBlock, int i) {
    g_dComIfG_gameInfo.play.setPictureBoxData(aramBlock, i);
}

inline bool dComIfGp_isPictureFlag(u8 i) {
    return g_dComIfG_gameInfo.play.isPictureFlag(i);
}

inline void dComIfGp_onPictureFlag(u8 i) {
    g_dComIfG_gameInfo.play.onPictureFlag(i);
}

inline void dComIfGp_offPictureFlag(u8 i) {
    g_dComIfG_gameInfo.play.offPictureFlag(i);
}

inline u8 dComIfGp_getPictureFormat() {
    return g_dComIfG_gameInfo.play.getPictureFormat();
}

inline u8 dComIfGp_getPictureResult() {
    return g_dComIfG_gameInfo.play.getPictureResult();
}

inline u8 dComIfGp_getPictureResultDetail() {
    return g_dComIfG_gameInfo.play.getPictureResultDetail();
}

inline void dComIfGp_setBossBattleData(JKRAramBlock* aramBlock, int i) {
    g_dComIfG_gameInfo.play.setBossBattleData(aramBlock, i);
}

inline u8 dComIfGp_getButtonActionMode() {
    return g_dComIfG_gameInfo.play.getButtonMode();
}

inline void dComIfGp_setButtonActionMode(u8 mode) {
    g_dComIfG_gameInfo.play.setButtonMode(mode);
}

inline void dComIfGp_setInputPassword(const char* password) {
    g_dComIfG_gameInfo.play.setInputPassword(password);
}

inline u8 dComIfGp_getAdvanceDirection() {
    return g_dComIfG_gameInfo.play.getDirection();
}

inline void dComIfGp_setAdvanceDirection(u8 direction) {
    return g_dComIfG_gameInfo.play.setDirection(direction);
}

/**
 * === ROOM CONTROL ===
 */

inline s32 dComIfGp_roomControl_getTimePass() {
    return g_dComIfG_gameInfo.play.getRoomControl()->GetTimePass();
}

inline int dComIfGp_roomControl_getStayNo() {
    return dStage_roomControl_c::getStayNo();
}

inline dBgW* dComIfGp_roomControl_getBgW(int i_roomNo) {
    return g_dComIfG_gameInfo.play.getRoomControl()->getBgW(i_roomNo);
}

inline s32 dComIfGp_roomControl_getZoneNo(int i_roomNo) {
    return g_dComIfG_gameInfo.play.getRoomControl()->getZoneNo(i_roomNo);
}

inline void dComIfGp_roomControl_setZoneNo(int i_roomNo, int i_zoneNo) {
    g_dComIfG_gameInfo.play.getRoomControl()->setZoneNo(i_roomNo, i_zoneNo);
}

inline dKy_tevstr_c* dComIfGp_roomControl_getTevStr(int room_no) {
    return g_dComIfG_gameInfo.play.getRoomControl()->getTevStr(room_no);
}

inline void dComIfGp_roomControl_init() {
    g_dComIfG_gameInfo.play.getRoomControl()->init();
}

inline dStage_roomDt_c* dComIfGp_roomControl_getStatusRoomDt(int room_no) {
    return g_dComIfG_gameInfo.play.getRoomControl()->getStatusRoomDt(room_no);
}

inline void dComIfGp_roomControl_checkDrawArea() {
    return g_dComIfG_gameInfo.play.getRoomControl()->checkDrawArea();
}

inline void dComIfGp_roomControl_setStayNo(int stayNo) {
    g_dComIfG_gameInfo.play.getRoomControl()->setStayNo(stayNo);
}

inline void dComIfGp_roomControl_setStatusFlag(int i_roomNo, u8 i_flag) {
    g_dComIfG_gameInfo.play.getRoomControl()->setStatusFlag(i_roomNo, i_flag);
}

inline void dComIfGp_roomControl_onStatusFlag(int i_roomNo, u8 i_flag) {
    g_dComIfG_gameInfo.play.getRoomControl()->onStatusFlag(i_roomNo, i_flag);
}

inline void dComIfGp_roomControl_offStatusFlag(int i_roomNo, u8 i_flag) {
    g_dComIfG_gameInfo.play.getRoomControl()->offStatusFlag(i_roomNo, i_flag);
}

inline BOOL dComIfGp_roomControl_checkStatusFlag(int i_roomNo, u8 i_flag) {
    return g_dComIfG_gameInfo.play.getRoomControl()->checkStatusFlag(i_roomNo, i_flag);
}

inline void dComIfGp_roomControl_zoneCountCheck(int i_roomNo) {
    g_dComIfG_gameInfo.play.getRoomControl()->zoneCountCheck(i_roomNo);
}

inline void dComIfGp_roomControl_setTimePass(int isPassing) {
    g_dComIfG_gameInfo.play.getRoomControl()->SetTimePass(isPassing);
}

inline int dComIfGp_roomControl_loadRoom(int roomCount, u8* rooms) {
    return g_dComIfG_gameInfo.play.getRoomControl()->loadRoom(roomCount, rooms);
}

inline BOOL dComIfGp_roomControl_checkRoomDisp(int i_roomNo) {
    return g_dComIfG_gameInfo.play.getRoomControl()->checkRoomDisp(i_roomNo);
}

/**
 * === EVENT ===
 */

inline BOOL dComIfGp_event_runCheck() {
    return g_dComIfG_gameInfo.play.getEvent()->runCheck();
}

inline u16 dComIfGp_event_checkHind(u16 i_hindFlag) {
    if (!dComIfGp_event_runCheck()) {
        return false;
    }
    return g_dComIfG_gameInfo.play.getEvent()->checkHind(i_hindFlag);
}

/**
 * Returns the button (X Y or Z) that was used to start this event.
 * @return The dTalkXYButton_e of the button the player used to initiate this event.
 */
inline u8 dComIfGp_event_getTalkXYBtn() {
    return g_dComIfG_gameInfo.play.getEvent()->getTalkXYBtn();
}

inline bool dComIfGp_event_chkTalkXY() {
    return g_dComIfG_gameInfo.play.getEvent()->chkTalkXY();
}

inline void dComIfGp_event_onEventFlag(u16 flag) {
    g_dComIfG_gameInfo.play.getEvent()->onEventFlag(flag);
}

inline void dComIfGp_event_offEventFlag(u16 flag) {
    g_dComIfG_gameInfo.play.getEvent()->offEventFlag(flag);
}

inline u16 dComIfGp_event_chkEventFlag(u16 flag) {
    return g_dComIfG_gameInfo.play.getEvent()->chkEventFlag(flag);
}

inline void dComIfGp_event_remove() {
    g_dComIfG_gameInfo.play.getEvent()->remove();
}

inline void dComIfGp_event_reset() {
    g_dComIfG_gameInfo.play.getEvent()->reset();
}

inline int dComIfGp_event_getPreItemNo() {
    return g_dComIfG_gameInfo.play.getEvent()->getPreItemNo();
}

inline void dComIfGp_event_setGtItm(u8 itemNo) {
    g_dComIfG_gameInfo.play.getEvent()->setGtItm(itemNo);
}

inline u8 dComIfGp_event_getGtItm() {
    return g_dComIfG_gameInfo.play.getEvent()->getGtItm();
}

inline s32 dComIfGp_event_moveApproval(void* actor) {
    return g_dComIfG_gameInfo.play.getEvent()->moveApproval(actor);
}

inline BOOL dComIfGp_event_compulsory(void* param_1, const char* param_2 = NULL, u16 param_3 = -1) {
    return g_dComIfG_gameInfo.play.getEvent()->compulsory(param_1, param_2, param_3);
}

inline s32 dComIfGp_event_order(u16 eventType, u16 priority, u16 flag, u16 hind, void* pActor1,
                                void* pActor2, s16 eventID = -1, u8 infoIdx = -1) {
    return g_dComIfG_gameInfo.play.getEvent()->order(eventType, priority, flag, hind, pActor1, pActor2, eventID, infoIdx);
}

inline s32 dComIfGp_event_orderOld(u16 eventType, u16 priority, u16 flag, u16 hind, void* pActor1, void* pActor2, const char *pEventName) {
    return g_dComIfG_gameInfo.play.getEvent()->orderOld(eventType, priority, flag, hind, pActor1, pActor2, pEventName);
}

inline fopAc_ac_c* dComIfGp_event_getTalkPartner() {
    return g_dComIfG_gameInfo.play.getEvent()->getPtT();
}

inline void dComIfGp_event_setTalkPartner(void* i_actor) {
    g_dComIfG_gameInfo.play.getEvent()->setPtT(i_actor);
}

inline fopAc_ac_c* dComIfGp_event_getItemPartner() {
    return g_dComIfG_gameInfo.play.getEvent()->getPtI();
}

inline void dComIfGp_event_setItemPartner(void* pt) {
    g_dComIfG_gameInfo.play.getEvent()->setPtI(pt);
}

inline void dComIfGp_event_setItemPartnerId(fpc_ProcID id) {
    g_dComIfG_gameInfo.play.getEvent()->setPtI_Id(id);
}

inline fopAc_ac_c* dComIfGp_event_getPt1() {
    return g_dComIfG_gameInfo.play.getEvent()->getPt1();
}

inline fopAc_ac_c* dComIfGp_event_getPt2() {
    return g_dComIfG_gameInfo.play.getEvent()->getPt2();
}

inline f32 dComIfGp_event_getCullRate() {
    return g_dComIfG_gameInfo.play.getEvent()->getCullRate();
}

inline void dComIfGp_event_setCullRate(f32 ratio) {
    g_dComIfG_gameInfo.play.getEvent()->setCullRate(ratio);
}

inline BOOL dComIfGp_event_check() {
    return g_dComIfG_gameInfo.play.getEvent()->check();
}

inline u8 dComIfGp_event_getMode() {
    return g_dComIfG_gameInfo.play.getEvent()->getMode();
}

inline u8 dComIfGp_event_getTactFreeMStick(int which) {
    return g_dComIfG_gameInfo.play.getEvent()->getTactFreeMStick(which);
}

inline u8 dComIfGp_event_getTactFreeCStick(int which) {
    return g_dComIfG_gameInfo.play.getEvent()->getTactFreeCStick(which);
}

inline bool dComIfGp_getMetronome() {
    return g_dComIfG_gameInfo.play.getMetronome();
}

inline void dComIfGp_setMetronomeOn() {
    g_dComIfG_gameInfo.play.setMetronomeOn();
}

inline void dComIfGp_setMetronomeOff() {
    g_dComIfG_gameInfo.play.setMetronomeOff();
}

/**
 * === EVENT MANAGER ===
 */

inline dEvent_manager_c* dComIfGp_getPEvtManager() {
    return &g_dComIfG_gameInfo.play.getEvtManager();
}

// Note: Some of the below functions call g_dComIfG_gameInfo.play.getEvtManager(), while others use
// dComIfGp_getPEvtManager(), without a clear pattern for which was chosen.

inline u32 dComIfGp_evmng_getEventPrio(s16 eventIdx) {
    return g_dComIfG_gameInfo.play.getEvtManager().getEventPrio(eventIdx);
}

inline s16 dComIfGp_evmng_getEventIdx(const char* pName, u8 evNo = -1) {
    return g_dComIfG_gameInfo.play.getEvtManager().getEventIdx(pName, evNo);
}

inline int dComIfGp_evmng_getToolId(u8 idx, int sub) {
    return dComIfGp_getPEvtManager()->getToolId(idx, sub);
}

inline int dComIfGp_evmng_getMyStaffId(const char* pName, fopAc_ac_c* pActor = NULL, int staffType = 0) {
    return dComIfGp_getPEvtManager()->getMyStaffId(pName, pActor, staffType);
}

inline int dComIfGp_evmng_getMyActIdx(int staffIdx, char** pActions, int actionCount, BOOL force, int nameType) {
    return dComIfGp_getPEvtManager()->getMyActIdx(staffIdx, pActions, actionCount, force, nameType);
}

inline char* dComIfGp_evmng_getMyActName(int staffIdx) {
    return dComIfGp_getPEvtManager()->getMyActName(staffIdx);
}

inline f32* dComIfGp_evmng_getMyFloatP(int staffIdx, char* name) {
    return reinterpret_cast<f32*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, dEvDtData_c::TYPE_FLOAT));
}

inline Vec* dComIfGp_evmng_getMyVec3dP(int staffIdx, char* name) {
    return reinterpret_cast<Vec*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, dEvDtData_c::TYPE_VEC));
}

inline cXyz* dComIfGp_evmng_getMyXyzP(int staffIdx, char* name) {
    return reinterpret_cast<cXyz*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, dEvDtData_c::TYPE_VEC));
}

inline int* dComIfGp_evmng_getMyIntegerP(int staffIdx, char* name) {
    return reinterpret_cast<int*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, dEvDtData_c::TYPE_INT));
}

inline char* dComIfGp_evmng_getMyStringP(int staffIdx, char* name) {
    return reinterpret_cast<char*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, dEvDtData_c::TYPE_STRING));
}

inline BOOL dComIfGp_evmng_startCheck(s16 eventID) {
    return g_dComIfG_gameInfo.play.getEvtManager().startCheck(eventID);
}

inline BOOL dComIfGp_evmng_startCheck(const char* pName) {
    return g_dComIfG_gameInfo.play.getEvtManager().startCheckOld(pName);
}

inline BOOL dComIfGp_evmng_endCheck(const char* pName) {
    return g_dComIfG_gameInfo.play.getEvtManager().endCheckOld(pName);
}

inline BOOL dComIfGp_evmng_endCheck(s16 eventID) {
    return g_dComIfG_gameInfo.play.getEvtManager().endCheck(eventID);
}

inline BOOL dComIfGp_evmng_ChkPresentEnd() {
    return dComIfGp_getPEvtManager()->ChkPresentEnd();
}

inline void dComIfGp_evmng_CancelPresent() {
    dComIfGp_getPEvtManager()->CancelPresent();
}

inline BOOL dComIfGp_evmng_getIsAddvance(int staffIdx) {
    return dComIfGp_getPEvtManager()->getIsAddvance(staffIdx);
}

inline void dComIfGp_evmng_cutEnd(int staffIdx) {
    dComIfGp_getPEvtManager()->cutEnd(staffIdx);
}

inline void dComIfGp_evmng_execute() {
    g_dComIfG_gameInfo.play.executeEvtManager();
}

inline void dComIfGp_evmng_create() {
    g_dComIfG_gameInfo.play.getEvtManager().create();
}

inline void dComIfGp_evmng_remove() {
    g_dComIfG_gameInfo.play.getEvtManager().remove();
}

inline cXyz* dComIfGp_evmng_getGoal() {
    return dComIfGp_getPEvtManager()->getGoal();
}

inline void dComIfGp_evmng_setGoal(cXyz* pos) {
    dComIfGp_getPEvtManager()->setGoal(pos);
}

inline int dComIfGp_evmng_startDemo(int eventInfoIdx) {
    return dComIfGp_getPEvtManager()->setStartDemo(eventInfoIdx);
}

inline BOOL dComIfGp_evmng_checkStartDemo() {
    return dComIfGp_getPEvtManager()->checkStartDemo();
}

inline void dComIfGp_evmng_cancelStartDemo() {
    dComIfGp_getPEvtManager()->cancelStartDemo();
}

inline BOOL dComIfGp_evmng_existence(const char* pName) {
    return g_dComIfG_gameInfo.play.getEvtManager().getEventData(dComIfGp_evmng_getEventIdx(pName)) != NULL;
}

inline BOOL dComIfGp_evmng_existence(s16 eventIdx) {
    return g_dComIfG_gameInfo.play.getEvtManager().getEventData(eventIdx) != NULL;
}

inline BOOL dComIfGp_evmng_order(s16 eventIdx) {
    return g_dComIfG_gameInfo.play.getEvtManager().order(eventIdx);
}

inline u8 dComIfGp_evmng_getEventEndSound(s16 eventIdx) {
    return g_dComIfG_gameInfo.play.getEvtManager().getEventEndSound(eventIdx);
}

inline int dComIfGp_evmng_cameraPlay() {
    return dComIfGp_getPEvtManager()->cameraPlay();
}

/**
 * === DEMO ===
 */

inline void dComIfGp_createDemo() {
    return g_dComIfG_gameInfo.play.createDemo();
}

inline void dComIfGp_removeDemo() {
    return g_dComIfG_gameInfo.play.removeDemo();
}

inline dDemo_manager_c* dComIfGp_demo_get() {
    return g_dComIfG_gameInfo.play.getDemo();
}

inline void dComIfGp_demo_create(const u8* demo_data, cXyz* offsetPos, f32 offsetAngleY) {
    g_dComIfG_gameInfo.play.getDemo()->create(demo_data, offsetPos, offsetAngleY);
}

inline void dComIfGp_demo_remove() {
    g_dComIfG_gameInfo.play.getDemo()->remove();
}

inline void dComIfGp_demo_update() {
    g_dComIfG_gameInfo.play.getDemo()->update();
}

inline s32 dComIfGp_demo_mode() {
    return g_dComIfG_gameInfo.play.getDemo()->getMode();
}

inline dDemo_actor_c* dComIfGp_demo_getActor(u8 id) {
    return g_dComIfG_gameInfo.play.getDemo()->getObject()->getActor(id);
}

inline dDemo_camera_c* dComIfGp_demo_getCamera() {
    return g_dComIfG_gameInfo.play.getDemo()->getObject()->getActiveCamera();
}

stage_camera_class* dComIfGp_getRoomCamera(int i_roomNo);
stage_arrow_class* dComIfGp_getRoomArrow(int i_roomNo);

/**
 * === DRAWLIST ===
 */

int dComIfGd_setShadow(u32 id, s8 shouldFade, J3DModel* pModel, cXyz* pPos, f32 casterSize, f32 scaleXZ,
                       f32 y, f32 groundY, cBgS_PolyInfo& pFloorPoly, dKy_tevstr_c* pTevStr,
                       s16 rotY = 0, f32 scaleZ = 1.0f,
                       GXTexObj* pTexObj = dDlst_shadowControl_c::getSimpleTex());

inline int dComIfGd_setSimpleShadow(cXyz* i_pos, f32 groundY, f32 scaleXZ, cXyz* floor_nrm,
                                    s16 i_angle = 0, f32 scaleZ = 1.0f,
                                    GXTexObj* i_tex = dDlst_shadowControl_c::getSimpleTex()) {
    return g_dComIfG_gameInfo.drawlist.setSimpleShadow(i_pos, groundY, scaleXZ, floor_nrm, i_angle,
                                                       scaleZ, i_tex);
}

int dComIfGd_setSimpleShadow2(cXyz* i_pos, f32 groundY, f32 scaleXZ, cBgS_PolyInfo& i_floorPoly,
                              s16 i_angle = 0, f32 scaleZ = 1.0f,
                              GXTexObj* i_tex = dDlst_shadowControl_c::getSimpleTex());

inline int dComIfGd_setRealShadow(u32 id, s8 shouldFade, J3DModel* pModel, cXyz* pPos, f32 casterSize,
                                   f32 heightAboveGround, dKy_tevstr_c* pTevStr) {
    return g_dComIfG_gameInfo.drawlist.setRealShadow(id, shouldFade, pModel, pPos, casterSize, heightAboveGround,
                                                     pTevStr);
}

inline int dComIfGd_setRealShadow2(u32 id, s8 shouldFade, J3DModel* pModel, cXyz* pPos, f32 casterSize,
                                   f32 heightAboveGround, dKy_tevstr_c* pTevStr) {
    return g_dComIfG_gameInfo.drawlist.setRealShadow2(id, shouldFade, pModel, pPos, casterSize, heightAboveGround,
                                                      pTevStr);
}

inline bool dComIfGd_addRealShadow(u32 id, J3DModel* pModel) {
    return g_dComIfG_gameInfo.drawlist.addRealShadow(id, pModel);
}

inline void dComIfGd_imageDrawShadow(Mtx mtx) {
    g_dComIfG_gameInfo.drawlist.imageDrawShadow(mtx);
}

inline void dComIfGd_set3DlineMat(mDoExt_3DlineMat_c* mat) {
    g_dComIfG_gameInfo.drawlist.set3DlineMat(mat);
}

inline void dComIfGd_setAlphaModel(u8 type, Mtx mtx, u8 alpha) { g_dComIfG_gameInfo.drawlist.setAlphaModel(type, mtx, alpha); }
inline void dComIfGd_setSpotModel(u8 type, Mtx mtx, u8 alpha) { g_dComIfG_gameInfo.drawlist.setSpotModel(type, mtx, alpha); }
inline void dComIfGd_setLightModel(u8 type, Mtx mtx, u8 alpha) { g_dComIfG_gameInfo.drawlist.setLightModel(type, mtx, alpha); }

inline void dComIfGd_drawAlphaModel(Mtx mtx) { g_dComIfG_gameInfo.drawlist.drawAlphaModel(mtx); }
inline void dComIfGd_drawSpotModel(Mtx mtx) { g_dComIfG_gameInfo.drawlist.drawSpotModel(mtx); }
inline void dComIfGd_drawLightModel(Mtx mtx) { g_dComIfG_gameInfo.drawlist.drawLightModel(mtx); }

inline s32 dComIfGd_getSpotModelNum() { return g_dComIfG_gameInfo.drawlist.getSpotModelNum(); }
inline s32 dComIfGd_getLightModelNum() { return g_dComIfG_gameInfo.drawlist.getLightModelNum(); }
inline void dComIfGd_setAlphaModelColor(GXColor& color) { g_dComIfG_gameInfo.drawlist.setAlphaModelColor(color); }
inline void dComIfGd_setSpotModelColor(GXColor& color) { g_dComIfG_gameInfo.drawlist.setSpotModelColor(color); }
inline void dComIfGd_setLightModelColor(GXColor& color) { g_dComIfG_gameInfo.drawlist.setLightModelColor(color); }
inline GXColor & dComIfGd_getAlphaModelColor() { return g_dComIfG_gameInfo.drawlist.getAlphaModelColor(); }
inline GXColor & dComIfGd_getLightModelColor() { return g_dComIfG_gameInfo.drawlist.getLightModelColor(); }
inline GXColor & dComIfGd_getSpotModelColor() { return g_dComIfG_gameInfo.drawlist.getSpotModelColor(); }
inline void dComIfGd_resetAlphaModel() { g_dComIfG_gameInfo.drawlist.resetAlphaModel(); }
inline void dComIfGd_resetSpotModel() { g_dComIfG_gameInfo.drawlist.resetSpotModel(); }
inline void dComIfGd_resetLightModel() { g_dComIfG_gameInfo.drawlist.resetLightModel(); }

inline J3DDrawBuffer* dComIfGd_getOpaListP1() { return g_dComIfG_gameInfo.drawlist.getOpaListP1(); }
inline J3DDrawBuffer* dComIfGd_getOpaListSky() { return g_dComIfG_gameInfo.drawlist.getOpaListSky(); }
inline J3DDrawBuffer* dComIfGd_getListFilter() { return g_dComIfG_gameInfo.drawlist.getOpaListFilter(); }
inline J3DDrawBuffer* dComIfGd_getList2D() { return g_dComIfG_gameInfo.drawlist.getOpaList2D(); }
inline J3DDrawBuffer* dComIfGd_getXluList() { return g_dComIfG_gameInfo.drawlist.getXluList(); }
inline J3DDrawBuffer* dComIfGd_getXluListP1() { return g_dComIfG_gameInfo.drawlist.getXluListP1(); }

inline void dComIfGd_setList() {
    g_dComIfG_gameInfo.drawlist.setOpaList();
    g_dComIfG_gameInfo.drawlist.setXluList();
}

inline void dComIfGd_setXluList() {
    g_dComIfG_gameInfo.drawlist.setXluList();
}

inline void dComIfGd_setListInvisisble() {
    g_dComIfG_gameInfo.drawlist.setOpaListInvisible();
    g_dComIfG_gameInfo.drawlist.setXluListInvisible();
}

inline void dComIfGd_setListMaskOff() {
    g_dComIfG_gameInfo.drawlist.setOpaListMaskOff();
    g_dComIfG_gameInfo.drawlist.setXluListMaskOff();
}

inline void dComIfGd_setListSky() {
    g_dComIfG_gameInfo.drawlist.setOpaListSky();
    g_dComIfG_gameInfo.drawlist.setXluListSky();
}

inline void dComIfGd_setListP0() {
    g_dComIfG_gameInfo.drawlist.setOpaListP0();
    g_dComIfG_gameInfo.drawlist.setXluListP0();
}

inline void dComIfGd_setListP1() {
    g_dComIfG_gameInfo.drawlist.setOpaListP1();
    g_dComIfG_gameInfo.drawlist.setXluListP1();
}

inline void dComIfGd_setListBG() {
    g_dComIfG_gameInfo.drawlist.setOpaListBG();
    g_dComIfG_gameInfo.drawlist.setXluListBG();
}

inline void dComIfGd_setXluListBG() {
    g_dComIfG_gameInfo.drawlist.setXluListBG();
}

inline void dComIfGd_setListFilter() {
    g_dComIfG_gameInfo.drawlist.setOpaListFilter();
    g_dComIfG_gameInfo.drawlist.setXluListFilter();
}

inline void dComIfGd_setList2D() {
    g_dComIfG_gameInfo.drawlist.setOpaList2D();
    g_dComIfG_gameInfo.drawlist.setXluList2D();
}

inline void dComIfGd_entryZSortXluList(J3DPacket* i_packet, cXyz& param_1) {
    g_dComIfG_gameInfo.drawlist.entryZSortXluList(i_packet, param_1);
}

inline void dComIfGd_entryZSortXluListMaskOff(J3DPacket* i_packet, cXyz& param_1) {
    g_dComIfG_gameInfo.drawlist.entryZSortXluListMaskOff(i_packet, param_1);
}

inline void dComIfGd_set2DOpaTop(dDlst_base_c* pBase) { g_dComIfG_gameInfo.drawlist.set2DOpaTop(pBase); }
inline void dComIfGd_set2DOpa(dDlst_base_c* pBase) { g_dComIfG_gameInfo.drawlist.set2DOpa(pBase); }
inline void dComIfGd_set2DXlu(dDlst_base_c* pBase) { g_dComIfG_gameInfo.drawlist.set2DXlu(pBase); }

inline void dComIfGd_drawCopy2D() { g_dComIfG_gameInfo.drawlist.drawCopy2D(); }
inline void dComIfGd_draw2DOpa() { g_dComIfG_gameInfo.drawlist.draw2DOpa(); }
inline void dComIfGd_draw2DOpaTop() { g_dComIfG_gameInfo.drawlist.draw2DOpaTop(); }
inline void dComIfGd_draw2DXlu() { g_dComIfG_gameInfo.drawlist.draw2DXlu(); }

inline void dComIfGd_drawOpaListSky() { g_dComIfG_gameInfo.drawlist.drawOpaListSky(); }
inline void dComIfGd_drawXluListSky() { g_dComIfG_gameInfo.drawlist.drawXluListSky(); }
inline void dComIfGd_drawOpaListP0() { g_dComIfG_gameInfo.drawlist.drawOpaListP0(); }
inline void dComIfGd_drawOpaListP1() { g_dComIfG_gameInfo.drawlist.drawOpaListP1(); }
inline void dComIfGd_drawXluListP1() { g_dComIfG_gameInfo.drawlist.drawXluListP1(); }
inline void dComIfGd_drawOpaListBG() { g_dComIfG_gameInfo.drawlist.drawOpaListBG(); }
inline void dComIfGd_drawXluListBG() { g_dComIfG_gameInfo.drawlist.drawXluListBG(); }
inline void dComIfGd_drawOpaList() { g_dComIfG_gameInfo.drawlist.drawOpaList(); }
inline void dComIfGd_drawXluList() { g_dComIfG_gameInfo.drawlist.drawXluList(); }
inline void dComIfGd_drawOpaListFilter() { g_dComIfG_gameInfo.drawlist.drawOpaListFilter(); }
inline void dComIfGd_drawOpaListMaskOff() { g_dComIfG_gameInfo.drawlist.drawOpaListMaskOff(); }
inline void dComIfGd_drawXluListMaskOff() { g_dComIfG_gameInfo.drawlist.drawXluListMaskOff(); }
inline void dComIfGd_drawOpaListInvisible() { g_dComIfG_gameInfo.drawlist.drawOpaListInvisible(); }
inline void dComIfGd_drawXluListInvisible() { g_dComIfG_gameInfo.drawlist.drawXluListInvisible(); }
inline void dComIfGd_drawOpaList2D() { g_dComIfG_gameInfo.drawlist.drawOpaList2D(); }

inline void dComIfGd_drawShadow(Mtx mtx) { g_dComIfG_gameInfo.drawlist.drawShadow(mtx); }

inline void dComIfGd_peekZ(s16 x, s16 y, u32 * data) { g_dComIfG_gameInfo.drawlist.newPeekZdata(x, y, data); }
inline void dComIfGd_peekZdata() { g_dComIfG_gameInfo.drawlist.peekZdata(); }

inline void dComIfGd_setWindow(dDlst_window_c* pWindow) { g_dComIfG_gameInfo.drawlist.setWindow(pWindow); }
inline void dComIfGd_setViewport(view_port_class* pViewPort) { g_dComIfG_gameInfo.drawlist.setViewport(pViewPort); }
inline view_port_class* dComIfGd_getViewport() { return g_dComIfG_gameInfo.drawlist.getViewport(); }
inline void dComIfGd_setView(view_class* pView) { g_dComIfG_gameInfo.drawlist.setView(pView); }
inline view_class* dComIfGd_getView() { return g_dComIfG_gameInfo.drawlist.getView(); }
inline MtxP dComIfGd_getViewRotMtx() { return dComIfGd_getView()->mViewMtxNoTrans; }
inline MtxP dComIfGd_getInvViewMtx() { return g_dComIfG_gameInfo.drawlist.getView()->mInvViewMtx; }
inline Mtx44* dComIfGd_getProjViewMtx() { return &g_dComIfG_gameInfo.drawlist.getView()->mProjViewMtx; }
inline void dComIfGd_init() { g_dComIfG_gameInfo.drawlist.init(); }
inline void dComIfGd_reset() { g_dComIfG_gameInfo.drawlist.reset(); }

/**
 * === ARCHIVE ===
 */

inline void dComIfGp_setAnmArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setAnmArchive(pArc); }
inline JKRArchive* dComIfGp_getAnmArchive() { return g_dComIfG_gameInfo.play.getAnmArchive(); }
inline void dComIfGp_setMsgArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setMsgArchive(pArc); }
inline JKRArchive* dComIfGp_getMsgArchive() { return g_dComIfG_gameInfo.play.getMsgArchive(); }
#if VERSION > VERSION_DEMO
inline void dComIfGp_setDmsgArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setDmsgArchive(pArc); }
inline JKRArchive* dComIfGp_getDmsgArchive() { return g_dComIfG_gameInfo.play.getDmsgArchive(); }
#endif
inline void dComIfGp_setTactMsgArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setTactMsgArchive(pArc); }
inline JKRArchive* dComIfGp_getTactMsgArchive() { return g_dComIfG_gameInfo.play.getTactMsgArchive(); }
inline void dComIfGp_setMenuArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setMenuArchive(pArc); }
inline JKRArchive* dComIfGp_getMenuArchive() { return g_dComIfG_gameInfo.play.getMenuArchive(); }
inline void dComIfGp_setFont0Archive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setFont0Archive(pArc); }
inline void dComIfGp_setFont1Archive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setFont1Archive(pArc); }
inline JKRArchive* dComIfGp_getFontArchive() { return g_dComIfG_gameInfo.play.getFontArchive(); }
inline JKRArchive* dComIfGp_getRubyArchive() { return g_dComIfG_gameInfo.play.getRubyArchive(); }
inline void dComIfGp_setLkDArc(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setLkDArc(pArc); }
inline void dComIfGp_setFmapArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setFmapArchive(pArc); }
inline void dComIfGp_setItemResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setItemResArchive(pArc); }
inline void dComIfGp_setCollectResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setCollectResArchive(pArc); }
inline void dComIfGp_setFmapResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setFmapResArchive(pArc); }
inline void dComIfGp_setDmapResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setDmapResArchive(pArc); }
inline void dComIfGp_setOptionResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setOptionResArchive(pArc); }
inline JKRArchive* dComIfGp_getClothResArchive() { return g_dComIfG_gameInfo.play.getClothResArchive(); }
inline void dComIfGp_setClothResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setClothResArchive(pArc); }
inline void dComIfGp_setSaveResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setSaveResArchive(pArc); }
inline void dComIfGp_setItemIconArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setItemIconArchive(pArc); }
inline JKRArchive* dComIfGp_getItemIconArchive() { return g_dComIfG_gameInfo.play.getItemIconArchive(); }
inline void dComIfGp_setNameResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setNameResArchive(pArc); }
inline void dComIfGp_setErrorResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setErrorResArchive(pArc); }
inline JKRArchive* dComIfGp_getErrorResArchive() { return g_dComIfG_gameInfo.play.getErrorResArchive(); }
inline void dComIfGp_setActionIconArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setActionIconArchive(pArc); }
inline JKRArchive* dComIfGp_getActionIconArchive() { return g_dComIfG_gameInfo.play.getActionIconArchive(); }
inline void dComIfGp_setScopeResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setScopeResArchive(pArc); }
inline void dComIfGp_setCameraResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setCameraResArchive(pArc); }
inline JKRArchive* dComIfGp_getSwimResArchive() { return g_dComIfG_gameInfo.play.getSwimResArchive(); }
inline void dComIfGp_setSwimResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setSwimResArchive(pArc); }
inline void dComIfGp_setWindResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setWindResArchive(pArc); }
inline void dComIfGp_setFontArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setFontArchive(pArc); }
inline void dComIfGp_setMsgDtArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setMsgDtArchive(pArc); }
inline JKRArchive* dComIfGp_getMsgDtArchive() { return g_dComIfG_gameInfo.play.getMsgDtArchive(); }
#if VERSION > VERSION_JPN
inline void dComIfGp_setMsgDt2Archive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setMsgDt2Archive(pArc); }
inline JKRArchive* dComIfGp_getMsgDt2Archive() { return g_dComIfG_gameInfo.play.getMsgDt2Archive(); }
#endif

inline void dComIfGp_setItemTable(void * pData) { g_dComIfG_gameInfo.play.setItemTable(pData); }
inline ItemTableList* dComIfGp_getItemTable() { return g_dComIfG_gameInfo.play.getItemTable(); }
inline void dComIfGp_setActorData(void * pData) { g_dComIfG_gameInfo.play.mADM.SetData(pData); }
inline void* dComIfGp_getFmapData() { return g_dComIfG_gameInfo.play.getFmapData(); }
inline void dComIfGp_setFmapData(void * pData) { g_dComIfG_gameInfo.play.setFmapData(pData); }

/**
 * === RESOURCE ===
 */

struct request_of_phase_process_class;
cPhs_State dComIfG_resLoad(request_of_phase_process_class* i_phase, char const* arc_name);
int dComIfG_resDelete(request_of_phase_process_class* i_phase, char const* resName);

inline int dComIfG_setObjectRes(const char* name, u8 direction, JKRHeap* heap) {
    return g_dComIfG_gameInfo.mResControl.setObjectRes(name, direction, heap);
}

inline int dComIfG_setStageRes(const char* name, JKRHeap* heap) {
    return g_dComIfG_gameInfo.mResControl.setStageRes(name, heap);
}

inline int dComIfG_syncObjectRes(const char* name) {
    return g_dComIfG_gameInfo.mResControl.syncObjectRes(name);
}

inline int dComIfG_syncAllObjectRes() {
    return g_dComIfG_gameInfo.mResControl.syncAllObjectRes();
}

inline int dComIfG_syncStageRes(const char* name) {
    return g_dComIfG_gameInfo.mResControl.syncStageRes(name);
}

#if VERSION == VERSION_DEMO
// A number of actors used dComIfG_deleteObjectRes in actor delete functions, but these were changed
// to dComIfG_resDelete for the retail version.
#define dComIfG_resDeleteDemo(i_phase, i_resName) dComIfG_deleteObjectRes(i_resName)
#else
#define dComIfG_resDeleteDemo(i_phase, i_resName) dComIfG_resDelete(i_phase, i_resName);
#endif

inline int dComIfG_deleteObjectRes(const char* res) {
    return g_dComIfG_gameInfo.mResControl.deleteObjectRes(res);
}

inline int dComIfG_deleteStageRes(const char* res) {
    return g_dComIfG_gameInfo.mResControl.deleteStageRes(res);
}

inline void* dComIfG_getStageRes(const char* arcName, const char* resName) {
    return g_dComIfG_gameInfo.mResControl.getStageRes(arcName, resName);
}

inline void* dComIfG_getStageRes(const char* arcName, int index) {
    return g_dComIfG_gameInfo.mResControl.getStageRes(arcName, index);
}

inline void* dComIfG_getObjectRes(const char* arcName, const char* resName) {
    return g_dComIfG_gameInfo.mResControl.getObjectRes(arcName, resName);
}

inline void* dComIfG_getObjectRes(const char* arcName, int index) {
    return g_dComIfG_gameInfo.mResControl.getObjectRes(arcName, index);
}

inline void* dComIfG_getObjectIDRes(const char* arcName, int id) {
    return g_dComIfG_gameInfo.mResControl.getObjectIDRes(arcName, id);
}

inline void* dComIfG_getObjectIDRes(const char* arcName, u16 id) {
    return g_dComIfG_gameInfo.mResControl.getObjectIDRes(arcName, id);
}

inline dRes_info_c* dComIfG_getObjectResInfo(const char* arcName) {
    return g_dComIfG_gameInfo.mResControl.getObjectResInfo(arcName);
}

inline void dComIfG_dumpResControl() {
    g_dComIfG_gameInfo.mResControl.dump();
}

/**
 * === PARTICLE ===
 */

inline JPABaseEmitter* dComIfGp_particle_set(u16 particleID, const cXyz* pos,
                                             const csXyz* angle = NULL, const cXyz* scale = NULL,
                                             u8 alpha = 0xFF, dPa_levelEcallBack* pCallBack = NULL,
                                             s8 setupInfo = -1, const GXColor* pPrmColor = NULL,
                                             const GXColor* pEnvColor = NULL,
                                             const cXyz* pScale2D = NULL) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->setNormal(particleID, pos, angle, scale, alpha, pCallBack, setupInfo,
                                pPrmColor, pEnvColor, pScale2D);
}

inline JPABaseEmitter* dComIfGp_particle_setP1(u16 particleID, const cXyz* pos,
                                               const csXyz* angle = NULL, const cXyz* scale = NULL,
                                               u8 alpha = 0xFF, dPa_levelEcallBack* pCallBack = NULL,
                                               s8 setupInfo = -1, const GXColor* pPrmColor = NULL,
                                               const GXColor* pEnvColor = NULL,
                                               const cXyz* pScale2D = NULL) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->setNormalP1(particleID, pos, angle, scale, alpha, pCallBack, setupInfo,
                                pPrmColor, pEnvColor, pScale2D);
}

inline JPABaseEmitter* dComIfGp_particle_setToon(u16 particleID, const cXyz* pos,
                                                 const csXyz* angle = NULL, const cXyz* scale = NULL,
                                                 u8 alpha = 0xFF, dPa_levelEcallBack* pCallBack = NULL,
                                                 s8 setupInfo = -1, const GXColor* pPrmColor = NULL,
                                                 const GXColor* pEnvColor = NULL,
                                                 const cXyz* pScale2D = NULL) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->setToon(particleID, pos, angle, scale, alpha, pCallBack, setupInfo,
                              pPrmColor, pEnvColor, pScale2D);
}

inline JPABaseEmitter* dComIfGp_particle_setToonP1(u16 particleID, const cXyz* pos,
                                                   const csXyz* angle = NULL, const cXyz* scale = NULL,
                                                   u8 alpha = 0xFF, dPa_levelEcallBack* pCallBack = NULL,
                                                   s8 setupInfo = -1, const GXColor* pPrmColor = NULL,
                                                   const GXColor* pEnvColor = NULL,
                                                   const cXyz* pScale2D = NULL) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->setToonP1(particleID, pos, angle, scale, alpha, pCallBack, setupInfo,
                              pPrmColor, pEnvColor, pScale2D);
}

inline JPABaseEmitter* dComIfGp_particle_setProjection(u16 particleID, const cXyz* pos,
                                                       const csXyz* angle = NULL, const cXyz* scale = NULL,
                                                       u8 alpha = 0xFF, dPa_levelEcallBack* pCallBack = NULL,
                                                       s8 setupInfo = -1, const GXColor* pPrmColor = NULL,
                                                       const GXColor* pEnvColor = NULL,
                                                       const cXyz* pScale2D = NULL) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->setProjection(particleID, pos, angle, scale, alpha, pCallBack, setupInfo,
                                    pPrmColor, pEnvColor, pScale2D);
}

inline JPABaseEmitter* dComIfGp_particle_setShipTail(u16 particleID, const cXyz* pos,
                                                     const csXyz* angle = NULL, const cXyz* scale = NULL,
                                                     u8 alpha = 0xFF, dPa_levelEcallBack* pCallBack = NULL,
                                                     s8 setupInfo = -1, const GXColor* pPrmColor = NULL,
                                                     const GXColor* pEnvColor = NULL,
                                                     const cXyz* pScale2D = NULL) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->setShipTail(particleID, pos, angle, scale, alpha, pCallBack, setupInfo,
                                  pPrmColor, pEnvColor, pScale2D);
}

inline JPABaseEmitter* dComIfGp_particle_set2Dfore(u16 particleID, const cXyz* pos,
                                                   const csXyz* angle = NULL, const cXyz* scale = NULL,
                                                   u8 alpha = 0xFF, dPa_levelEcallBack* pCallBack = NULL,
                                                   s8 setupInfo = -1, const GXColor* pPrmColor = NULL,
                                                   const GXColor* pEnvColor = NULL,
                                                   const cXyz* pScale2D = NULL) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->set2Dfore(particleID, pos, angle, scale, alpha, pCallBack, setupInfo,
                                pPrmColor, pEnvColor, pScale2D);
}

inline JPABaseEmitter* dComIfGp_particle_set2Dback(u16 particleID, const cXyz* pos,
                                                   const csXyz* angle = NULL, const cXyz* scale = NULL,
                                                   u8 alpha = 0xFF, dPa_levelEcallBack* pCallBack = NULL,
                                                   s8 setupInfo = -1, const GXColor* pPrmColor = NULL,
                                                   const GXColor* pEnvColor = NULL,
                                                   const cXyz* pScale2D = NULL) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->set2Dback(particleID, pos, angle, scale, alpha, pCallBack, setupInfo,
                                pPrmColor, pEnvColor, pScale2D);
}

inline JPABaseEmitter* dComIfGp_particle_set2DmenuFore(u16 particleID, const cXyz* pos,
                                                       const csXyz* angle = NULL, const cXyz* scale = NULL,
                                                       u8 alpha = 0xFF, dPa_levelEcallBack* pCallBack = NULL,
                                                       s8 setupInfo = -1, const GXColor* pPrmColor = NULL,
                                                       const GXColor* pEnvColor = NULL,
                                                       const cXyz* pScale2D = NULL) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->set2DmenuFore(particleID, pos, angle, scale, alpha, pCallBack, setupInfo,
                                    pPrmColor, pEnvColor, pScale2D);
}

inline JPABaseEmitter* dComIfGp_particle_setSingleRipple(u16 particleID, const cXyz* pos,
                                                         const csXyz* angle = NULL,
                                                         const cXyz* scale = NULL,
                                                         u8 alpha = 0xFF) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->setSingleRipple(particleID, pos, angle, scale, alpha);
}

inline void dComIfGp_particle_setStripes(u16 particleID, const cXyz* pos, const csXyz* angle,
                                         const cXyz* scale, u8 param_4, u16 param_5) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    pParticle->setNormalStripes(particleID, pos, angle, scale, param_4, param_5);
}

inline void dComIfGp_particle_setSimple(u16 particleID, cXyz* pos, u8 alpha = 0xFF,
                                        GXColor& prmColor = g_whiteColor,
                                        GXColor& envColor = g_whiteColor,
                                        int param_6 = 0) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    pParticle->setSimple(particleID, pos, alpha, prmColor, envColor, param_6);
}

inline JPABaseEmitter* dComIfGp_particle_setSimpleLand(int code, const cXyz* param_1, const csXyz* param_2,
                                            f32 param_3, f32 param_4, f32 param_5,
                                            dKy_tevstr_c* param_6, int* param_7, int param_8) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->setSimpleLand(code, param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8);
}

inline JPABaseEmitter* dComIfGp_particle_setSimpleLand(cBgS_PolyInfo& param_1, const cXyz* pos, const csXyz* angle, f32 param_4, f32 param_5, f32 param_6, dKy_tevstr_c* param_7, int* param_8, int param_9) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->setSimpleLand(param_1, pos, angle, param_4, param_5, param_6, param_7, param_8, param_9);
}

inline void dComIfGp_particle_forceDeleteEmitter(JPABaseEmitter* emitter) {
    dPa_control_c::forceDeleteEmitter(emitter);
}

inline JPABaseEmitter* dComIfGp_particle_setBombSmoke(u16 particleID, const cXyz* pos,
                                           const csXyz* angle = NULL, const cXyz* scale = NULL,
                                           u8 alpha = 0xFF) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->setBombSmoke(particleID, pos, angle, scale, alpha);
}

inline void dComIfGp_particle_calc3D() {
    g_dComIfG_gameInfo.play.getParticle()->calc3D();
}

inline void dComIfGp_particle_calc2D() {
    g_dComIfG_gameInfo.play.getParticle()->calc2D();
}

inline void dComIfGp_particle_calcMenu() {
    g_dComIfG_gameInfo.play.getParticle()->calcMenu();
}

inline int dComIfGp_particle_addModelEmitter(dPa_modelEmitter_c* emitter){
    return g_dComIfG_gameInfo.play.getParticle()->addModelEmitter(emitter);
}

inline void dComIfGp_particle_drawModelParticle() {
    g_dComIfG_gameInfo.play.getParticle()->drawModelParticle();
}

inline bool dComIfGp_particle_readScene(u8 particle_no, mDoDvdThd_toMainRam_c** param_1) {
    return g_dComIfG_gameInfo.play.getParticle()->readScene(particle_no, param_1);
}

inline void dComIfGp_particle_create() {
    g_dComIfG_gameInfo.play.createParticle();
}

inline void dComIfGp_particle_createCommon(const void * pArc) {
    g_dComIfG_gameInfo.play.getParticle()->createCommon(pArc);
}

inline void dComIfGp_particle_createScene(const void* pArc) {
    g_dComIfG_gameInfo.play.getParticle()->createScene(pArc);
}

inline void dComIfGp_particle_createRoomScene(void * pData) {
    g_dComIfG_gameInfo.play.getParticle()->createRoomScene(pData);
}

inline void dComIfGp_particle_removeRoomScene() {
    g_dComIfG_gameInfo.play.getParticle()->removeRoomScene();
}

inline void dComIfGp_particle_removeScene() {
    g_dComIfG_gameInfo.play.getParticle()->removeScene();
}

inline void dComIfGp_particle_swapFrameBufferTexture() {
    g_dComIfG_gameInfo.play.getParticle()->swapFrameBufferTexture();
}

inline void dComIfGp_particle_draw(JPADrawInfo* inf) { if (g_dComIfG_gameInfo.play.getParticle() != NULL) g_dComIfG_gameInfo.play.getParticle()->draw(inf); }
inline void dComIfGp_particle_drawP1(JPADrawInfo* inf) { if (g_dComIfG_gameInfo.play.getParticle() != NULL) g_dComIfG_gameInfo.play.getParticle()->drawP1(inf); }
inline void dComIfGp_particle_drawToon(JPADrawInfo* inf) { if (g_dComIfG_gameInfo.play.getParticle() != NULL) g_dComIfG_gameInfo.play.getParticle()->drawToon(inf); }
inline void dComIfGp_particle_drawToonP1(JPADrawInfo* inf) { if (g_dComIfG_gameInfo.play.getParticle() != NULL) g_dComIfG_gameInfo.play.getParticle()->drawToonP1(inf); }
inline void dComIfGp_particle_drawProjection(JPADrawInfo* inf) { if (g_dComIfG_gameInfo.play.getParticle() != NULL) g_dComIfG_gameInfo.play.getParticle()->drawProjection(inf); }
inline void dComIfGp_particle_drawShipTail(JPADrawInfo* inf) { if (g_dComIfG_gameInfo.play.getParticle() != NULL) g_dComIfG_gameInfo.play.getParticle()->drawShipTail(inf); }
inline void dComIfGp_particle_drawWind(JPADrawInfo* inf) { if (g_dComIfG_gameInfo.play.getParticle() != NULL) g_dComIfG_gameInfo.play.getParticle()->drawWind(inf); }
inline void dComIfGp_particle_draw2Dfore(JPADrawInfo* inf) { if (g_dComIfG_gameInfo.play.getParticle() != NULL) g_dComIfG_gameInfo.play.getParticle()->draw2Dfore(inf); }
inline void dComIfGp_particle_draw2Dback(JPADrawInfo* inf) { if (g_dComIfG_gameInfo.play.getParticle() != NULL) g_dComIfG_gameInfo.play.getParticle()->draw2Dback(inf); }
inline void dComIfGp_particle_draw2DmenuFore(JPADrawInfo* inf) { if (g_dComIfG_gameInfo.play.getParticle() != NULL) g_dComIfG_gameInfo.play.getParticle()->draw2DmenuFore(inf); }
inline void dComIfGp_particle_draw2DmenuBack(JPADrawInfo* inf) { if (g_dComIfG_gameInfo.play.getParticle() != NULL) g_dComIfG_gameInfo.play.getParticle()->draw2DmenuBack(inf); }

inline u32 dComIfGp_particle_getParticleNum() { return g_dComIfG_gameInfo.play.getParticle()->getParticleNum(); }
inline u32 dComIfGp_particle_getEmitterNum() { return g_dComIfG_gameInfo.play.getParticle()->getEmitterNum(); }
inline JKRHeap* dComIfGp_particle_getCommonHeap() { return g_dComIfG_gameInfo.play.getParticle()->getHeap(); }

inline s32 dComIfGp_particle_checkAtrCodeEffect(int code) { return g_dComIfG_gameInfo.play.getParticle()->checkAtrCodeEffect(code); }

/**
 * === ATTENTION ===
 */

inline dAttention_c& dComIfGp_getAttention() {
    return g_dComIfG_gameInfo.play.getAttention();
}

inline void dComIfGp_att_revivalAleart() {
    dComIfGp_getAttention().revivalAleart();
}

inline void dComIfGp_att_offAleart() {
    dComIfGp_getAttention().offAleart();
}

inline int dComIfGp_att_ZHintRequest(fopAc_ac_c* i_actor, int priority) {
    return dComIfGp_getAttention().ZHintRequest(i_actor, priority);
}

inline void dComIfGp_att_LookRequest(fopAc_ac_c* param_0, f32 i_horizontalDist, f32 i_upDist,
                                     f32 i_downDist, s16 i_angle, int param_5) {
    dComIfGp_getAttention().LookRequest(param_0, i_horizontalDist, i_upDist, i_downDist, i_angle, param_5);
}

inline void dComIfGp_att_Look2RequestF(fopAc_ac_c* param_0, s16 param_1, int param_2) {
    dComIfGp_getAttention().Look2RequestF(param_0, param_1, param_2);
}

inline void dComIfGp_att_CatchRequest(fopAc_ac_c* reqActor, u8 itemNo, f32 horizontalDist, f32 upDist,
                                      f32 downDist, s16 angle, int param_6) {
    dComIfGp_getAttention().CatchRequest(reqActor, itemNo, horizontalDist, upDist, downDist,angle, param_6);
}

inline u8 dComIfGp_att_getCatchChgItem() {
    return dComIfGp_getAttention().getCatchChgItem();
}

inline fopAc_ac_c* dComIfGp_att_getCatghTarget() {
    return dComIfGp_getAttention().getCatghTarget();
}

inline void dComIfGp_att_ChangeOwner() {
    dComIfGp_getAttention().changeOwner();
}

inline fopAc_ac_c* dComIfGp_att_getLookTarget() {
    return dComIfGp_getAttention().getLookTarget();
}

inline fopAc_ac_c* dComIfGp_att_getZHint() {
    return dComIfGp_getAttention().getZHintTarget();
}

inline bool dComIfGp_att_chkEnemySound() {
    return dComIfGp_getAttention().chkEnemySound();
}

/**
 * === MAP ===
 */

 inline void dComIfGp_map_draw(f32 x, f32 z, int roomNo, f32 y) {
    dMap_c::draw(x, z, roomNo, y);
}

inline void dComIfGp_map_mapBufferSendAGB(int param_0) {
    dMap_c::mapBufferSendAGB(param_0);
}

inline void dComIfGp_map_setImage(int param_0, int param_1, f32 param_2) {
    dMap_c::setImage(param_0, param_1, param_2);
}

inline void dComIfGp_map_deleteImage(int param_0) {
    dMap_c::deleteImage(param_0);
}

inline void dComIfGp_map_setAGBMapSendStopFlg() {
    dMap_c::setAGBMapSendStopFlg();
}

inline void dComIfGp_map_clrAGBMapSendStopFlg() {
    dMap_c::clrAGBMapSendStopFlg();
}

/**
 * === MISC ===
 */

 inline dBgS* dComIfG_Bgsp() {
    return &g_dComIfG_gameInfo.play.mBgS;
}

inline dCcS* dComIfG_Ccsp() {
    return &g_dComIfG_gameInfo.play.mCcS;
}

inline void dComIfG_setTimerMode(int ms) { g_dComIfG_gameInfo.play.setTimerMode(ms); }
inline int dComIfG_getTimerMode() { return g_dComIfG_gameInfo.play.getTimerMode(); }

inline void dComIfG_setTimerPtr(dTimer_c* timer) { g_dComIfG_gameInfo.play.setTimerPtr(timer); }
inline dTimer_c* dComIfG_getTimerPtr() { return g_dComIfG_gameInfo.play.getTimerPtr(); }

inline void dComIfG_setTimerLimitTimeMs(int ms) { g_dComIfG_gameInfo.play.setTimerLimitTimeMs(ms); }
inline int dComIfG_getTimerLimitTimeMs() { return g_dComIfG_gameInfo.play.getTimerLimitTimeMs(); }

inline void dComIfG_setTimerNowTimeMs(int ms) { g_dComIfG_gameInfo.play.setTimerNowTimeMs(ms); }
inline int dComIfG_getTimerNowTimeMs() { return g_dComIfG_gameInfo.play.getTimerNowTimeMs(); }

inline void dComIfGp_setWaveFrame(u16 frame) { g_dComIfG_gameInfo.play.setWaveFrame(frame); }
inline u16 dComIfGp_getWaveFrame() { return g_dComIfG_gameInfo.play.getWaveFrame(); }

inline void dComIfGp_fmapOpenOn() { g_dComIfG_gameInfo.play.fmapOpenOn(); }

inline int dComIfG_getTimerRestTimeMs() {
    int limit = g_dComIfG_gameInfo.play.getTimerLimitTimeMs();
    int now = g_dComIfG_gameInfo.play.getTimerNowTimeMs();
    return limit - now;
}

inline void dComIfG_TimerDeleteRequest() {
    if (dComIfG_getTimerPtr() != NULL)
        dComIfG_getTimerPtr()->deleteRequest();
}
inline void dComIfG_TimerStart(int mode, s16 timer) {
    if (dComIfG_getTimerMode() == mode && dComIfG_getTimerPtr() != NULL) {
        if (!timer)
            dComIfG_getTimerPtr()->start();
        else
            dComIfG_getTimerPtr()->start(timer);
    }
}
inline void dComIfG_TimerReStart(int timer) {
    if (dComIfG_getTimerPtr() != NULL)
        dComIfG_getTimerPtr()->restart(timer);
}
inline void dComIfG_TimerStop(int timer) {
    if (dComIfG_getTimerPtr() != NULL)
        dComIfG_getTimerPtr()->stop(timer);
}

inline u8 dComIfG_getBrightness() { return g_dComIfG_gameInfo.mBrightness; }
inline void dComIfG_setBrightness(u8 v) { g_dComIfG_gameInfo.mBrightness = v; }

class scene_class;
BOOL dComIfG_resetToOpening(scene_class* i_scene);

int dComIfG_changeOpeningScene(scene_class* i_scene, s16 i_procName);

inline void dComIfGp_InputPasswordOpenOn() {
    g_dComIfG_gameInfo.play.nameOpenOn();
}

inline u8 dComIfGp_InputPasswordOpenCheck() {
    return g_dComIfG_gameInfo.play.nameOpenCheck();
}

inline char* dComIfGp_getInputPassword() {
    return g_dComIfG_gameInfo.play.getInputPassword();
}

#endif /* D_COM_D_COM_INF_GAME_H */
