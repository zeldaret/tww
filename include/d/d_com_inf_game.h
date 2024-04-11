#ifndef D_COM_D_COM_INF_GAME_H
#define D_COM_D_COM_INF_GAME_H

#include "JSystem/JUtility/TColor.h"
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
#include "d/d_save.h"
#include "d/d_stage.h"
#include "d/d_vibration.h"
#include "d/d_demo.h"
#include "d/d_timer.h"
#include "d/res/res_always.h"
#include "SSystem/SComponent/c_data_tbl.h"

class JKRArchive;
class JKRAramBlock;
class JKRExpHeap;
class dMagma_packet_c;
class dGrass_packet_c;
class dTree_packet_c;
class dFlower_packet_c;
namespace dWood { class Packet_c; };
class daPy_py_c;
class daPy_lk_c;
class daShip_c;
class daAgb_c;
class camera_class;
class J2DOrthoGraph;

enum daPy__PlayerStatus0 {
    daPyStts0_UNK1_e           = 0x00000001,
    daPyStts0_UNK10_e          = 0x00000010,
    daPyStts0_UNK100_e         = 0x00000100,
    daPyStts0_BOW_AIM_e        = 0x00001000,
    daPyStts0_SWORD_SWING_e    = 0x00008000,
    daPyStts0_SHIP_RIDE_e      = 0x00010000,
    daPyStts0_BOOMERANG_AIM_e  = 0x00080000,
    daPyStts0_SWIM_e           = 0x00100000,
    daPyStts0_TELESCOPE_LOOK_e = 0x00200000,
    daPyStts0_BOOMERANG_WAIT_e = 0x00400000,
    daPyStts0_UNK2000000_e     = 0x02000000,
    daPyStts0_CRAWL_e          = 0x08000000,
    daPyStts0_UNK20000000_e    = 0x20000000,
    daPyStts0_SPIN_ATTACK_e    = 0x40000000,
};

enum daPy__PlayerStatus1 {
    daPyStts1_WIND_WAKER_CONDUCT_e = 0x00000001,
    daPyStts1_PICTO_BOX_AIM_e      = 0x00000008,
    daPyStts1_DEKU_LEAF_FLY_e      = 0x00000020,
    daPyStts1_DEKU_LEAF_FAN_e      = 0x00000040,
    daPyStts1_SAIL_e               = 0x00000400,
    daPyStts1_UNK8000_e            = 0x00008000,
    daPyStts1_UNK40000_e           = 0x00040000,
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

class dADM_CharTbl : public cDT {
public:
    s32 GetNITEM0()  { return mIndex_N_ITEM0; }
    s32 GetNITEM1()  { return mIndex_N_ITEM1; }
    s32 GetNITEM2()  { return mIndex_N_ITEM2; }
    s32 GetNITEM3()  { return mIndex_N_ITEM3; }
    s32 GetNITEM4()  { return mIndex_N_ITEM4; }
    s32 GetNITEM5()  { return mIndex_N_ITEM5; }
    s32 GetNITEM6()  { return mIndex_N_ITEM6; }
    s32 GetNITEM7()  { return mIndex_N_ITEM7; }
    s32 GetNITEM8()  { return mIndex_N_ITEM8; }
    s32 GetNITEM9()  { return mIndex_N_ITEM9; }
    s32 GetNITEM10() { return mIndex_N_ITEM10; }
    s32 GetNITEM11() { return mIndex_N_ITEM11; }
    s32 GetNITEM12() { return mIndex_N_ITEM12; }
    s32 GetNITEM13() { return mIndex_N_ITEM13; }
    s32 GetNITEM14() { return mIndex_N_ITEM14; }
    s32 GetNITEM15() { return mIndex_N_ITEM15; }
    s32 GetPercent() { return mIndex_percent; }
    s32 GetITEM0() { return mIndex_ITEM0; }
    s32 GetITEM1() { return mIndex_ITEM1; }
    s32 GetITEM2() { return mIndex_ITEM2; }
    s32 GetITEM3() { return mIndex_ITEM3; }
    s32 GetITEM4() { return mIndex_ITEM4; }
    s32 GetITEM5() { return mIndex_ITEM5; }
    s32 GetITEM6() { return mIndex_ITEM6; }
    s32 GetITEM7() { return mIndex_ITEM7; }

private:
    /* 0x28 */ s32 mIndex_ARG;
    /* 0x2C */ s32 mIndex_N_ITEM0;
    /* 0x30 */ s32 mIndex_N_ITEM1;
    /* 0x34 */ s32 mIndex_N_ITEM2;
    /* 0x38 */ s32 mIndex_N_ITEM3;
    /* 0x3C */ s32 mIndex_N_ITEM4;
    /* 0x40 */ s32 mIndex_N_ITEM5;
    /* 0x44 */ s32 mIndex_N_ITEM6;
    /* 0x48 */ s32 mIndex_N_ITEM7;
    /* 0x4C */ s32 mIndex_N_ITEM8;
    /* 0x50 */ s32 mIndex_N_ITEM9;
    /* 0x54 */ s32 mIndex_N_ITEM10;
    /* 0x58 */ s32 mIndex_N_ITEM11;
    /* 0x5C */ s32 mIndex_N_ITEM12;
    /* 0x60 */ s32 mIndex_N_ITEM13;
    /* 0x64 */ s32 mIndex_N_ITEM14;
    /* 0x68 */ s32 mIndex_N_ITEM15;
    /* 0x6C */ s32 mIndex_percent;
    /* 0x70 */ s32 mIndex_ITEM0;
    /* 0x74 */ s32 mIndex_ITEM1;
    /* 0x78 */ s32 mIndex_ITEM2;
    /* 0x7C */ s32 mIndex_ITEM3;
    /* 0x80 */ s32 mIndex_ITEM4;
    /* 0x84 */ s32 mIndex_ITEM5;
    /* 0x88 */ s32 mIndex_ITEM6;
    /* 0x8C */ s32 mIndex_ITEM7;
};
STATIC_ASSERT(sizeof(dADM_CharTbl) == 0x90);

class dADM {
public:
    /* 0x00 */ int mBlockCount;
    /* 0x04 */ void* mpData;
    /* 0x08 */ dADM_CharTbl mCharTbl;

public:
    dADM();
    void FindTag(u32, u32*, u32*);
    void SetData(void*);

    virtual ~dADM();
};

class dComIfG_camera_info_class {
public:
    dComIfG_camera_info_class() {}
    ~dComIfG_camera_info_class() {}

    /* 0x00 */ camera_class* mpCamera;
    /* 0x04 */ u8 mDlstWindowIdx;
    /* 0x05 */ u8 mCamIdx;
    /* 0x06 */ s8 field_0x06;
    /* 0x07 */ u8 field_0x07;
    /* 0x08 */ u32 mCameraAttentionStatus;
    /* 0x0C */ f32 mCameraZoomScale;
    /* 0x10 */ f32 mCameraZoomForcus;
    /* 0x14 */ u8 field_0x14[0x34 - 0x14];
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

class dComIfG_play_c {
public:
#if VERSION == VERSION_JPN
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

    ~dComIfG_play_c() {}

    dStage_roomControl_c* getRoomControl() { return &mRoomCtrl; }
    dStage_stageDt_c& getStage() { return mStageData; }
    dEvt_control_c& getEvent() { return mEvtCtrl; }
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

    void setGameoverStatus(u8 stts) { mGameoverStatus = stts; }

    fopAc_ac_c* getPlayerPtr(int idx) { return (fopAc_ac_c*)mpPlayerPtr[idx]; }
    fopAc_ac_c* getPlayer(int idx) { return (fopAc_ac_c*)mpPlayer[idx]; }
    void setPlayer(int idx, fopAc_ac_c* player) { mpPlayer[idx] = (daPy_py_c*)player; }
    void setPlayerPtr(int idx, fopAc_ac_c* playerPtr) { mpPlayerPtr[idx] = playerPtr; }
    s8 getPlayerCameraID(int idx) { return mCurCamera[idx]; }
    void setPlayerInfo(int idx, fopAc_ac_c* player, int cam) {
        mpPlayer[idx] = (daPy_py_c*)player;
        mCurCamera[idx] = cam;
    }
    
    int getMessageRupee() { return mMessageRupee; }

    int getItemRupeeCount() { return mItemRupeeCount; }
    void setItemRupeeCount(s32 count) { mItemRupeeCount += count; }
    void setMessageCountNumber(s16 num) { mMsgCountNumber = num; }

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

    s16 getItemMagicCount() { return mItemMagicCount; }
    void setItemMagicCount(s16 magic) { mItemMagicCount += magic; }
    s16 getItemMaxMagicCount() { return mItemMaxMagicCount; }
    void setItemMaxMagicCount(s16 magic) { mItemMaxMagicCount += magic; }

    void setItemBombNumCount(s16 num) { mItemBombNumCount += num; }

    f32 getItemLifeCount() { return mItemLifeCount; }
    void setItemLifeCount(f32 num) { mItemLifeCount += num; }

    s16 getItemMaxLifeCount() { return mItemMaxLifeCount; }
    void setItemMaxLifeCount(s16 num) { mItemMaxLifeCount += num; }

    s16 getItemArrowNumCount() { return mItemArrowNumCount; }
    void setItemArrowNumCount(s16 num) { mItemArrowNumCount += num; }

    void setItemKeyNumCount(s16 num) { mItemKeyNumCount += num; }

    void setItemBeastNumCount(int i_idx, s16 num) { mItemBeastNumCounts[i_idx] += num; }
    s16 getItemBeastNumCount(int i_idx) { return mItemBeastNumCounts[i_idx]; }

    void setItemTimeCount(s32 time) { mAirMeter = time; }
    void setItemTimeMax(s32 time) { field_0x4928 = time; }

    u8 checkMesgSendButton() { return mMesgSendButton; }
    u8 checkMesgCancelButton() { return mMesgCancelButton; }

    void setPlayerStatus(int param_0, int i, u32 flag) { mPlayerStatus[param_0][i] |= flag; }
    void clearPlayerStatus(int param_0, int i, u32 flag) { mPlayerStatus[param_0][i] &= ~flag; }
    bool checkPlayerStatus(int param_0, int i, u32 flag) { return flag & mPlayerStatus[param_0][i]; }

    u8 getSelectItem(int idx) { return mSelectItem[idx]; }
    void setSelectItem(int idx, u8 itemNo) { mSelectItem[idx] = itemNo; }
    void setSelectEquip(int idx, u8 itemNo) { mSelectEquip[idx] = itemNo; }

    void setItem(u8 i_slot, u8 i_itemNo) {
        mItemSlot = i_slot;
        mItemNo = i_itemNo;
    }

    u8 getAStatus() { return mCurrButtonBAction; }
    void setAStatus(u8 status) { mCurrButtonBAction = status; }
    u8 getDoStatus() { return mCurrButtonAAction; }
    void setDoStatus(u8 status) { mCurrButtonAAction = status; }
    void setRStatus(u8 status) { field_0x492d = status; }
    u8 getRStatusForce() { return field_0x4930; }
    void setRStatusForce(u8 status) { field_0x4930 = status; }
    u8 getAStatusForce() { return field_0x4931; }
    void setAStatusForce(u8 value) { field_0x4931 = value; }
    u8 getDoStatusForce() { return field_0x4932; }
    void setDoStatusForce(u8 value) { field_0x4932 = value; }
    u8 getPictureStatus() { return mPictureStatus; }
    void setPictureStatusOn() { mPictureStatus = 2; }

    u8 getScopeType() { return mbCamOverrideFarPlane; }
    void setScopeType(u8 v) { mbCamOverrideFarPlane = v; }
    void setCameraInfo(int idx, camera_class* camera_p, int dlst_window_idx, int cam_idx, int p5) {
        mCameraInfo[idx].mpCamera = camera_p;
        mCameraInfo[idx].mDlstWindowIdx = dlst_window_idx;
        mCameraInfo[idx].mCamIdx = cam_idx;
        mCameraInfo[idx].field_0x06 = p5;
        setCameraAttentionStatus(0, 0);
    }
    void setCameraAttentionStatus(int idx, u32 stts) {
        mCameraInfo[idx].mCameraAttentionStatus = stts;
    }
    void setCurrentGrafPort(J2DOrthoGraph* i_graf) { mCurrentGrafPort = i_graf; }
    void setCurrentWindow(dDlst_window_c* i_window) { mCurrentWindow = i_window; }
    void setCurrentView(view_class* i_view) { mCurrentView = i_view; }
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

    void setMsgArchive(JKRArchive * pArc) { mpMsgArchive = pArc; }
    void setDmsgArchive(JKRArchive * pArc) { mpDmsgArchive = pArc; }
    void setTmsgArchive(JKRArchive * pArc) { mpTmsgArchive = pArc; }
    JKRArchive* getTmsgArchive() { return mpTmsgArchive; }
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
    void setClctResArchive(JKRArchive * pArc) { mpClctResArchive = pArc; }
    void setFmapResArchive(JKRArchive * pArc) { mpFmapResArchive = pArc; }
    void setDmapResArchive(JKRArchive * pArc) { mpDmapResArchive = pArc; }
    void setOptResArchive(JKRArchive * pArc) { mpOptResArchive = pArc; }
    JKRArchive* getClothResArchive() { return mpClothResArchive; }
    void setClothResArchive(JKRArchive * pArc) { mpClothResArchive = pArc; }
    void setSaveResArchive(JKRArchive * pArc) { mpSaveResArchive = pArc; }
    void setItemIconArchive(JKRArchive * pArc) { mpItemIconArchive = pArc; }
    JKRArchive* getItemIconArchive() { return mpItemIconArchive; }
    void setNameResArchive(JKRArchive * pArc) { mpNameResArchive = pArc; }
    void setErrorResArchive(JKRArchive * pArc) { mpErrorResArchive = pArc; }
    void setActionIconArchive(JKRArchive * pArc) { mpActionIconArchive = pArc; }
    void setScopeResArchive(JKRArchive * pArc) { mpScopeResArchive = pArc; }
    void setCamResArchive(JKRArchive * pArc) { mpCamResArchive = pArc; }
    void setSwimResArchive(JKRArchive * pArc) { mpSwimResArchive = pArc; }
    void setWindResArchive(JKRArchive * pArc) { mpWindResArchive = pArc; }
    void setFontArchive(JKRArchive * pArc) { mpFont0Archive = pArc; }
    void setMsgDtArchive(JKRArchive * pArc) { mpEnglishTextArchive = pArc; }
#if VERSION != VERSION_JPN
    void setMsgDt2Archive(JKRArchive * pArc) { mpHyruleTextArchive = pArc; }
#endif

    void setItemTable(void * pData) { mpItemTable = (ItemTableList*)pData; }
    ItemTableList* getItemTable() { return mpItemTable; }
    void setFmapData(void * pData) { mpFmapData = pData; }

    void setPictureBoxData(JKRAramBlock* aramHeap, int i) { mPictureBoxDataHeap[i] = aramHeap; }
    void offPictureFlag(u8 i) {
        u8 mask = (1 << i);
        mPictureFlag &= ~mask;
    }
    void setBossBattleData(JKRAramBlock* aramHeap, int i) { mBossBattleDataHeap[i] = aramHeap; }

    void stopFwaterTimer() { mFwaterTimer = 0; }
    u8 checkFwaterTimer() { return mFwaterTimer; }

    u8 getMiniGameType() { return mMiniGameType; }

    void endMiniGame(u16 param_1) {
        mMiniGameType = 0;
        field_0x4A38 ^= 1 << (param_1 - 1); // toggle Nth bit
        field_0x4A3E = 0;
    }

    void show2dOn() { m2dShow = true; }
    void show2dOff() { m2dShow = false; }
    bool show2dCheck() { return m2dShow; }

    u8 getMelodyNum() { return mMelodyNum; }
    void setMelodyNum(u8 melody) { mMelodyNum = melody; }

    u8 getBaseAnimeID() { return mMesgAnime; }
    void clearBaseAnimeID() { mMesgAnime = 0xFF; }
    u8 getNowAnimeID() { return mMesgAnimeTagInfo; }
    void clearNowAnimeID() { mMesgAnimeTagInfo = 0xFF; }

    u8 getButtonMode() { return mButtonMode; }
    void setButtonMode(u8 mode) { mButtonMode = mode; }

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
    /* 0x479C */ JKRArchive* mpDmsgArchive;
    /* 0x47A0 */ JKRArchive* mpTmsgArchive;
    /* 0x47A4 */ JKRArchive* mpMenuArchive;
    /* 0x47A8 */ JKRArchive* mpFont0Archive;
    /* 0x47AC */ JKRArchive* mpFont1Archive;
    /* 0x47B0 */ JKRArchive* mpAnmArchive;
    /* 0x47B4 */ JKRArchive* mpLkDArc;
    /* 0x47B8 */ JKRArchive* mpFmapArchive;
    /* 0x47BC */ JKRArchive* mpItemResArchive;
    /* 0x47C0 */ JKRArchive* mpClctResArchive;
    /* 0x47C4 */ JKRArchive* mpFmapResArchive;
    /* 0x47C8 */ JKRArchive* mpDmapResArchive;
    /* 0x47CC */ JKRArchive* mpOptResArchive;
    /* 0x47D0 */ JKRArchive* mpClothResArchive;
    /* 0x47D4 */ JKRArchive* mpSaveResArchive;
    /* 0x47D8 */ JKRArchive* mpItemIconArchive;
    /* 0x47DC */ JKRArchive* mpNameResArchive;
    /* 0x47E0 */ JKRArchive* mpErrorResArchive;
    /* 0x47E4 */ JKRArchive* mpActionIconArchive;
    /* 0x47E8 */ JKRArchive* mpScopeResArchive;
    /* 0x47EC */ JKRArchive* mpCamResArchive;
    /* 0x47F0 */ JKRArchive* mpSwimResArchive;
    /* 0x47F4 */ JKRArchive* mpWindResArchive;
    /* 0x47F8 */ JKRArchive* mpEnglishTextArchive;
#if VERSION != VERSION_JPN
    /* 0x47FC */ JKRArchive* mpHyruleTextArchive;
    /* 0x4800 */ JKRAramBlock* mPictureBoxDataHeap[3];
    /* 0x480C */ JKRAramBlock* mBossBattleDataHeap[4];
    /* 0x481C */ JKRAramBlock* field_0x481c;
    /* 0x4820 */ JKRAramBlock* field_0x4820;
#else
    /* 0x47FC */ JKRAramBlock* mPictureBoxDataHeap[3];
    /* 0x480C */ JKRAramBlock* mBossBattleDataHeap[4];
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
    /* 0x48A4 */ daPy_py_c* mpPlayer[1];
    /* 0x48A8 */ s8 mCurCamera[1];
    /* 0x48A9 */ u8 field_0x48A9[0x48AC - 0x48A9];
    /* 0x48AC */ fopAc_ac_c* mpPlayerPtr[3];  // 0: Link, 1: Partner, 2: Ship
    /* 0x48B8 */ f32 field_0x48b8;
    /* 0x48BC */ f32 mItemLifeCount;
    /* 0x48C0 */ int mItemRupeeCount;
    /* 0x48C4 */ int mAirMeter;
    /* 0x48C8 */ int field_0x48c8;
    /* 0x48CC */ int mNpcNameMessageID;
    /* 0x48D0 */ int mItemNameMessageID;
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
    /* 0x4918 */ u16 mMsgCountNumber;
    /* 0x491A */ s16 mMsgSetNumber;
    /* 0x491C */ s16 mMessageRupee;
    /* 0x491E */ s16 field_0x491e;
    /* 0x4920 */ s16 field_0x4920;
    /* 0x4922 */ s16 field_0x4922;
    /* 0x4924 */ s16 mCurrHP;
    /* 0x4926 */ s16 mRupyCountDisplay;
    /* 0x4928 */ u8 field_0x4928;
    /* 0x4929 */ u8 field_0x4929;
    /* 0x492A */ u8 field_0x492a;
    /* 0x492B */ u8 mbCamOverrideFarPlane;
    /* 0x492C */ u8 field_0x492c;
    /* 0x492D */ u8 field_0x492d;
    /* 0x492E */ u8 mCurrButtonBAction;
    /* 0x492F */ u8 mCurrButtonAAction;
    /* 0x4930 */ u8 field_0x4930;
    /* 0x4931 */ u8 field_0x4931;
    /* 0x4932 */ u8 field_0x4932;
    /* 0x4933 */ u8 mSelectItem[4];
    /* 0x4937 */ u8 mSelectEquip[4];
    /* 0x493B */ u8 mMesgAnime;
    /* 0x493C */ u8 mMesgAnimeTagInfo;
    /* 0x493D */ u8 mItemSlot;
    /* 0x493E */ u8 mItemNo;
    /* 0x493F */ u8 field_0x493f;
    /* 0x4940 */ u8 field_0x4940;
    /* 0x4941 */ u8 field_0x4941;
    /* 0x4942 */ u8 mButtonMode;
    /* 0x4943 */ u8 field_0x4943;
    /* 0x4944 */ u8 field_0x4944;
    /* 0x4945 */ u8 field_0x4945;
    /* 0x4946 */ u8 field_0x4946;
    /* 0x4947 */ u8 field_0x4947;
    /* 0x4948 */ u8 mMesgSendButton;
    /* 0x4949 */ u8 mMesgCancelButton;
    /* 0x494A */ u8 field_0x494a[6];
    /* 0x4950 */ u8 mMelodyNum;
    /* 0x4951 */ u8 field_0x4951;
    /* 0x4952 */ u8 field_0x4952;
    /* 0x4953 */ u8 field_0x4953;
    /* 0x4954 */ u8 field_0x4954;
    /* 0x4955 */ u8 field_0x4955;
    /* 0x4956 */ u8 mFwaterTimer;
    /* 0x4957 */ u8 mPlacenameIndex;
    /* 0x4958 */ u8 mPlacenameState;
    /* 0x4959 */ u8 mGameoverStatus;
    /* 0x495A */ u8 field_0x495a;
    /* 0x495B */ u8 mPictureFlag;
    /* 0x495C */ u8 field_0x495c;
    /* 0x495D */ u8 field_0x495d;
    /* 0x495E */ u8 mPictureStatus;
    /* 0x495F */ u8 field_0x495f;
    /* 0x4960 */ u8 field_0x4960;
    /* 0x4961 */ u8 field_0x4961;
    /* 0x4962 */ u8 mHeapLockFlag;
    /* 0x4963 */ u8 field_0x4963;
#if VERSION != VERSION_JPN
    /* 0x4964 */ u8 mGameLanguage;
#endif
    /* 0x4965 */ u8 field_0x4965;
    /* 0x4966 */ char field_0x4966[1];
    /* 0x4967 */ u8 field_0x4967[0x4977 - 0x4967];
    /* 0x4977 */ u8 field_0x4977;
    /* 0x4978 */ u8 field_0x4978;
    /* 0x4979 */ u8 m2dShow;
    /* 0x497A */ u8 field_0x497a;
    /* 0x497B */ u8 field_0x497B[0x497C - 0x497B];
    /* 0x497C */ JKRExpHeap* mpExpHeap2D;
    /* 0x4980 */ int mMesgCameraTagInfo;
    /* 0x4984 */ int field_0x4984;
    /* 0x4988 */ int field_0x4988[10];
    /* 0x49B0 */ u8 mPlayerInfoBuffer[0x4A20 - 0x49B0];
    /* 0x4A20 */ u8 mPlayerInfoBufferStageNo;
    /* 0x4A24 */ daAgb_c* mpAgb;
    /* 0x4A28 */ u32 mPlayerStatus[2][2];
    /* 0x4A38 */ u16 field_0x4A38;
    /* 0x4A3A */ u8 mMiniGameType;
    /* 0x4A3C */ s16 mMiniGameRupee;
    /* 0x4A3E */ u8 field_0x4A3E;
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
#if VERSION == VERSION_JPN
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

#if VERSION != VERSION_JPN
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

void dComIfGs_gameStart();
u8 dComIfGs_checkGetItem(u8);

inline void dComIfGs_init() {
    g_dComIfG_gameInfo.save.init();
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

inline int dComIfGp_getMessageRupee() {
    return g_dComIfG_gameInfo.play.getMessageRupee();
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

/**
 * Returns which item is in a specific inventory slot.
 * @param i_invIdx The index of the inventory slot.
 * @return The item number of the item in that slot, or 0xFF for no item.
 */
inline u8 dComIfGs_getItem(int i_invIdx) {
    if (i_invIdx < 0x15) {
        return g_dComIfG_gameInfo.save.getPlayer().getItem().getItem(i_invIdx);
    } else if (i_invIdx < 0x18) {
        return 0xFF;
    } else if (i_invIdx < 0x18 + 8) {
        return dComIfGs_getItemBeast(i_invIdx - 0x18);
    } else if (i_invIdx < 0x24) {
        return 0xFF;
    } else if (i_invIdx < 0x24 + 8) {
        return dComIfGs_getItemBait(i_invIdx - 0x24);
    } else if (i_invIdx < 0x30) {
        return 0xFF;
    } else if (i_invIdx < 0x30 + 8) {
        return dComIfGs_getItemReserve(i_invIdx - 0x30);
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
    if (i_invIdx < 0x15) {
        g_dComIfG_gameInfo.save.getPlayer().getItem().setItem(i_invIdx, i_itemNo);
    } else if (i_invIdx < 0x18) {
        return;
    } else if (i_invIdx < 0x18 + 8) {
        dComIfGs_setItemBeast(i_invIdx - 0x18, i_itemNo);
    } else if (i_invIdx < 0x24) {
        return;
    } else if (i_invIdx < 0x24 + 8) {
        dComIfGs_setItemBait(i_invIdx - 0x24, i_itemNo);
    } else if (i_invIdx < 0x30) {
        return;
    } else if (i_invIdx < 0x30 + 8) {
        dComIfGs_setItemReserve(i_invIdx - 0x30, i_itemNo);
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

inline u16 dComIfGs_getFwaterTimer() {
    return g_dComIfG_gameInfo.save.getPlayer().getItemRecord().getTimer();
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

inline u8 dComIfGs_checkReserveItemEmpty() {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().checkReserveItemEmpty();
}

inline void dComIfGs_setReserveItemEmpty() {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setReserveItemEmpty();
}

inline void dComIfGs_setReserveBaitEmpty(u8 i_btnIdx) {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setBaitItemEmpty(i_btnIdx);
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

inline BOOL dComIfGs_isEventBit(u16 id) {
    return g_dComIfG_gameInfo.save.getEvent().isEventBit(id);
}

inline void dComIfGs_onEventBit(u16 id) {
    g_dComIfG_gameInfo.save.getEvent().onEventBit(id);
}

inline void dComIfGs_offEventBit(u16 id) {
    g_dComIfG_gameInfo.save.getEvent().offEventBit(id);
}

inline void dComIfGs_onTmpBit(u16 id) {
    g_dComIfG_gameInfo.save.getTmp().onEventBit(id);
}

inline void dComIfGs_offTmpBit(u16 id) {
    g_dComIfG_gameInfo.save.getTmp().offEventBit(id);
}

inline s16 dComIfGs_getStartPoint() {
    return g_dComIfG_gameInfo.save.getRestart().getStartPoint();
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

inline void dComIfGs_setTurnRestart(const cXyz& i_pos, s16 i_angle, s8 i_roomNo, u32 i_param) {
    g_dComIfG_gameInfo.save.getTurnRestart().set(i_pos, i_angle, i_roomNo, i_param, i_pos, i_angle, 0);
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
 * @param i_btnIdx The index of the button. 0 for X, 1 for Y, 2 for Z.
 * @return The index of the inventory slot for the item equipped on that button, or 0xFF for no item.
 */
inline u8 dComIfGs_getSelectItem(int i_btnIdx) {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getSelectItem(i_btnIdx);
}

/**
 * Sets which inventory slot the item equipped on a specific button is located in.
 * @param i_btnIdx The index of the button. 0 for X, 1 for Y, 2 for Z.
 * @param i_invIdx The index of the inventory slot, or 0xFF for no item.
 */
inline void dComIfGs_setSelectItem(int i_btnIdx, u8 i_invIdx) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().setSelectItem(i_btnIdx, i_invIdx);
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

inline void dComIfGs_setEquipBottleItemIn(u8 i_btnIdx, u8 i_itemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getItem().setEquipBottleItemIn(i_btnIdx, i_itemNo);
}

inline void dComIfGs_setEquipBottleItemEmpty(u8 i_btnIdx) {
    g_dComIfG_gameInfo.save.getPlayer().getItem().setEquipBottleItemEmpty(i_btnIdx);
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
        if (dComIfGs_getItem(0xE + i) != 0xFF) {
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

u8 dComIfGs_checkGetItemNum(u8 i_itemNo);

stage_scls_info_class* dComIfGd_getMeshSceneList(Vec& vec);

BOOL dComIfGs_checkSeaLandingEvent(s8 i_roomNo);

inline void dComIfGs_stopFwaterTimer() {
    g_dComIfG_gameInfo.play.stopFwaterTimer();
}

inline u8 dComIfGs_checkFwaterTimer() {
    return g_dComIfG_gameInfo.play.checkFwaterTimer();
}

void dComIfGs_setPlayerRecollectionData();
void dComIfGs_revPlayerRecollectionData();

/**
 * === PLAY ===
 */

inline void dComIfGp_init() { g_dComIfG_gameInfo.play.init(); }

void dComIfGp_setNextStage(const char* i_stageName, s16 i_point, s8 i_roomNo, s8 i_layer = -1,
                           f32 i_lastSpeed = 0.0f, u32 i_lastMode = 0, BOOL i_setPoint = TRUE,
                           s8 i_wipe = 0);
dStage_Ship_data* dComIfGp_getShip(int i_roomNo, int param_1);
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

inline void dComIfGp_setGameoverStatus(u8 stts) {
    g_dComIfG_gameInfo.play.setGameoverStatus(stts);
}

inline int dComIfGp_getStartStageRoomNo() {
    return g_dComIfG_gameInfo.play.getStartStageRoomNo();
}

inline s8 dComIfGp_getStartStageLayer() {
    return g_dComIfG_gameInfo.play.getStartStageLayer();
}

inline s32 dComIfGp_getStartStagePoint() {
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

inline roomRead_class* dComIfGp_getStageRoom() {
    return g_dComIfG_gameInfo.play.getStage().getRoom();
}

inline dStage_Multi_c* dComIfGp_getMulti() {
    return g_dComIfG_gameInfo.play.getStage().getMulti();
}

inline stage_envr_info_class* dComIfGp_getStageEnvrInfo() {
    return g_dComIfG_gameInfo.play.getStage().getEnvrInfo();
}

inline dStage_EventInfo_c* dComIfGp_getStageEventInfo() {
    return g_dComIfG_gameInfo.play.getStage().getEventInfo();
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

inline dBgS* dComIfG_Bgsp() {
    return &g_dComIfG_gameInfo.play.mBgS;
}

inline dCcS* dComIfG_Ccsp() {
    return &g_dComIfG_gameInfo.play.mCcS;
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

inline stage_scls_info_dummy_class* dComIfGp_getStageSclsInfo() {
    return g_dComIfG_gameInfo.play.getStage().getSclsInfo();
}

inline dStage_stageDt_c& dComIfGp_getStage() {
    return g_dComIfG_gameInfo.play.getStage();
}

inline dVibration_c& dComIfGp_getVibration() {
    return g_dComIfG_gameInfo.play.getVibration();
}

inline dAttention_c& dComIfGp_getAttention() {
    return g_dComIfG_gameInfo.play.getAttention();
}

inline void dComIfGp_att_revivalAleart() {
    return dComIfGp_getAttention().revivalAleart();
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
    return g_dComIfG_gameInfo.play.getDemo()->mDemoObj.getActor(id);
}

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

inline u8 dComIfGp_getShipRoomId() {
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

inline daPy_py_c* daPy_getPlayerActorClass() {
    return (daPy_py_c*)dComIfGp_getPlayer(0);
}

inline fopAc_ac_c* dComIfGp_getLinkPlayer() {
    return g_dComIfG_gameInfo.play.getPlayerPtr(0);
}

inline void dComIfGp_setLinkPlayer(fopAc_ac_c* player) {
    g_dComIfG_gameInfo.play.setPlayerPtr(0, player);
}

inline daPy_lk_c* daPy_getPlayerLinkActorClass() {
    return (daPy_lk_c*)dComIfGp_getLinkPlayer();
}

inline s8 dComIfGp_getPlayerCameraID(int idx) {
    return g_dComIfG_gameInfo.play.getPlayerCameraID(idx);
}

inline BOOL dComIfGp_checkCameraAttentionStatus(int idx, u32 flag) {
    return g_dComIfG_gameInfo.play.checkCameraAttentionStatus(idx, flag);
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

inline void dComIfGp_setItemKeyNumCount(s16 num) {
    g_dComIfG_gameInfo.play.setItemKeyNumCount(num);
}

inline void dComIfGp_setItemTimeCount(s32 time) {
    g_dComIfG_gameInfo.play.setItemTimeCount(time);
}

inline void dComIfGp_setItemTimeMax(s32 time) {
    g_dComIfG_gameInfo.play.setItemTimeMax(time);
}

inline void dComIfGp_setMessageCountNumber(s16 num) {
    g_dComIfG_gameInfo.play.setMessageCountNumber(num);
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

inline u8 dComIfGp_checkMesgSendButton() {
    return g_dComIfG_gameInfo.play.checkMesgSendButton();
}

inline u8 dComIfGp_checkMesgCancelButton() {
    return g_dComIfG_gameInfo.play.checkMesgCancelButton();
}

inline bool dComIfGp_checkPlayerStatus0(int param_0, u32 flag) {
    return g_dComIfG_gameInfo.play.checkPlayerStatus(param_0, 0, flag);
}

inline bool dComIfGp_checkPlayerStatus1(int param_0, u32 flag) {
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

inline void dComIfGp_setDoStatusForce(u8 value) {
    g_dComIfG_gameInfo.play.setDoStatusForce(value);
}
inline void dComIfGp_setAStatusForce(u8 value) {
    g_dComIfG_gameInfo.play.setAStatusForce(value);
}

/**
 * Returns which item is on a specific button.
 * @param i_btnIdx The index of the button. 0 for X, 1 for Y, 2 for Z.
 * @return The item number of the item in that slot, or 0xFF for no item.
 */
inline u8 dComIfGp_getSelectItem(int i_btnIdx) {
    return g_dComIfG_gameInfo.play.getSelectItem(i_btnIdx);
}

/**
 * Updates which item is on a specific button to match which item is in the inventory slot correspond to that button.
 * @param i_btnIdx The index of the button. 0 for X, 1 for Y, 2 for Z.
 */
inline void dComIfGp_setSelectItem(int i_btnIdx) {
    if (dComIfGs_getSelectItem(i_btnIdx) != 0xFF) {
        int invIdx = dComIfGs_getSelectItem(i_btnIdx);
        u8 itemNo = dComIfGs_getItem(invIdx);
        g_dComIfG_gameInfo.play.setSelectItem(i_btnIdx, itemNo);

        invIdx = dComIfGs_getSelectItem(i_btnIdx);
        itemNo = dComIfGs_getItem(invIdx);
        if (itemNo == 0xFF) {
            dComIfGs_setSelectItem(i_btnIdx, 0xFF);
        }
    } else {
        g_dComIfG_gameInfo.play.setSelectItem(i_btnIdx, 0xFF);
    }
}

inline void dComIfGp_setSelectEquip(int idx, u8 itemNo) {
    g_dComIfG_gameInfo.play.setSelectEquip(idx, itemNo);
}

inline void dComIfGp_setItem(u8 slot, u8 i_itemNo) {
    g_dComIfG_gameInfo.play.setItem(slot, i_itemNo);
}

inline u8 dComIfGp_getScopeType() { return g_dComIfG_gameInfo.play.getScopeType(); }
inline void dComIfGp_setScopeType(u8 v) { g_dComIfG_gameInfo.play.setScopeType(v); }

inline void dComIfGp_setCurrentGrafPort(J2DOrthoGraph* i_graf) {
    g_dComIfG_gameInfo.play.setCurrentGrafPort(i_graf);
}

inline u8 dComIfGp_getMiniGameType() {
    // TODO add enum for minigame type.
    // 0 for none, 8 for shooting the fishman, 2/6 for orca, 7 for mail sorting, etc
    return g_dComIfG_gameInfo.play.getMiniGameType();
}

inline void dComIfGp_endMiniGame(u16 param_1) {
    g_dComIfG_gameInfo.play.endMiniGame(param_1);
}

inline u8 dComIfGp_getAStatus() {
    return g_dComIfG_gameInfo.play.getAStatus();
}

inline void dComIfGp_setAStatus(u8 status) {
    g_dComIfG_gameInfo.play.setAStatus(status);
}

inline u8 dComIfGp_getDoStatus() {
    return g_dComIfG_gameInfo.play.getDoStatus();
}

inline void dComIfGp_setDoStatus(u8 status) {
    g_dComIfG_gameInfo.play.setDoStatus(status);
}

inline void dComIfGp_setRStatus(u8 status) {
    g_dComIfG_gameInfo.play.setRStatus(status);
}

inline u8 dComIfGp_getRStatusForce() {
    return g_dComIfG_gameInfo.play.getRStatusForce();
}

inline void dComIfGp_setRStatusForce(u8 status) {
    g_dComIfG_gameInfo.play.setRStatusForce(status);
}

inline u8 dComIfGp_getPictureStatus() {
    return g_dComIfG_gameInfo.play.getPictureStatus();
}

inline void dComIfGp_setPictureStatusOn() {
    g_dComIfG_gameInfo.play.setPictureStatusOn();
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

inline void dComIfGp_setCameraInfo(int idx, camera_class* camera, int dlst, int cam, int p5) {
    g_dComIfG_gameInfo.play.setCameraInfo(idx, camera, dlst, cam, p5);
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

inline void dComIfGp_2dShowOn() {
    g_dComIfG_gameInfo.play.show2dOn();
}

inline void dComIfGp_2dShowOff() {
    g_dComIfG_gameInfo.play.show2dOff();
}

inline bool dComIfGp_2dShowCheck() {
    return g_dComIfG_gameInfo.play.show2dCheck();
}

inline u8 dComIfGp_setMelodyNum() {
    return g_dComIfG_gameInfo.play.getMelodyNum();
}

inline void dComIfGp_setMelodyNum(u8 melody) {
    g_dComIfG_gameInfo.play.setMelodyNum(melody);
}

inline u8 dComIfGp_getMesgAnimeAttrInfo() {
    return g_dComIfG_gameInfo.play.getBaseAnimeID();
}

inline void dComIfGp_clearMesgAnimeAttrInfo() {
    g_dComIfG_gameInfo.play.clearBaseAnimeID();
}

inline u8 dComIfGp_getMesgAnimeTagInfo() {
    return g_dComIfG_gameInfo.play.getNowAnimeID();
}

inline void dComIfGp_clearMesgAnimeTagInfo() {
    g_dComIfG_gameInfo.play.clearNowAnimeID();
}

inline void dComIfGp_setPictureBoxData(JKRAramBlock* aramHeap, int i) {
    g_dComIfG_gameInfo.play.setPictureBoxData(aramHeap, i);
}

inline void dComIfGp_offPictureFlag(u8 i) {
    g_dComIfG_gameInfo.play.offPictureFlag(i);
}

inline void dComIfGp_setBossBattleData(JKRAramBlock* aramHeap, int i) {
    g_dComIfG_gameInfo.play.setBossBattleData(aramHeap, i);
}

inline u8 dComIfGp_getButtonActionMode() {
    return g_dComIfG_gameInfo.play.getButtonMode();
}

inline void dComIfGp_setButtonActionMode(u8 mode) {
    g_dComIfG_gameInfo.play.setButtonMode(mode);
}

/**
 * === EVENT ===
 */

inline BOOL dComIfGp_event_runCheck() {
    return g_dComIfG_gameInfo.play.getEvent().runCheck();
}

inline u8 dComIfGp_event_getTalkXYBtn() {
    return g_dComIfG_gameInfo.play.getEvent().getTalkXYBtn();
}

inline bool dComIfGp_event_chkTalkXY() {
    return g_dComIfG_gameInfo.play.getEvent().chkTalkXY();
}

inline void dComIfGp_event_onEventFlag(s16 flag) {
    g_dComIfG_gameInfo.play.getEvent().onEventFlag(flag);
}

inline void dComIfGp_event_offEventFlag(s16 flag) {
    g_dComIfG_gameInfo.play.getEvent().offEventFlag(flag);
}

inline u16 dComIfGp_event_chkEventFlag(s16 flag) {
    return g_dComIfG_gameInfo.play.getEvent().chkEventFlag(flag);
}

inline void dComIfGp_event_remove() {
    g_dComIfG_gameInfo.play.getEvent().remove();
}

inline void dComIfGp_event_reset() {
    g_dComIfG_gameInfo.play.getEvent().reset();
}

inline int dComIfGp_event_getPreItemNo() {
    return g_dComIfG_gameInfo.play.getEvent().getPreItemNo();
}

inline void dComIfGp_event_setGtItm(u8 itemNo) {
    g_dComIfG_gameInfo.play.getEvent().setGtItm(itemNo);
}

inline u8 dComIfGp_event_getGtItm() {
    return g_dComIfG_gameInfo.play.getEvent().getGtItm();
}

inline s32 dComIfGp_event_moveApproval(void* actor) {
    return g_dComIfG_gameInfo.play.getEvent().moveApproval(actor);
}

inline BOOL dComIfGp_event_compulsory(void* param_1, const char* param_2 = NULL, u16 param_3 = -1) {
    return g_dComIfG_gameInfo.play.getEvent().compulsory(param_1, param_2, param_3);
}

inline s32 dComIfGp_event_order(u16 eventType, u16 priority, u16 flag, u16 hind, void* pActor1, void* pActor2, s16 eventID, u8 infoIdx) {
    return g_dComIfG_gameInfo.play.getEvent().order(eventType, priority, flag, hind, pActor1, pActor2, eventID, infoIdx);
}

inline s32 dComIfGp_event_orderOld(u16 eventType, u16 priority, u16 flag, u16 hind, void* pActor1, void* pActor2, const char *pEventName) {
    return g_dComIfG_gameInfo.play.getEvent().orderOld(eventType, priority, flag, hind, pActor1, pActor2, pEventName);
}

inline fopAc_ac_c* dComIfGp_event_getTalkPartner() {
    return (fopAc_ac_c*)g_dComIfG_gameInfo.play.getEvent().getPtT();
}

inline void dComIfGp_event_setTalkPartner(void* i_actor) {
    g_dComIfG_gameInfo.play.getEvent().setPtT(i_actor);
}

inline fopAc_ac_c* dComIfGp_event_getItemPartner() {
    return (fopAc_ac_c*)g_dComIfG_gameInfo.play.getEvent().getPtI();
}

inline void dComIfGp_event_setItemPartner(void* pt) {
    g_dComIfG_gameInfo.play.getEvent().setPtI(pt);
}

inline void dComIfGp_event_setItemPartnerId(uint id) {
    g_dComIfG_gameInfo.play.getEvent().setPtI_Id(id);
}

inline fopAc_ac_c* dComIfGp_event_getPt1() {
    return (fopAc_ac_c*)g_dComIfG_gameInfo.play.getEvent().getPt1();
}

inline fopAc_ac_c* dComIfGp_event_getPt2() {
    return (fopAc_ac_c*)g_dComIfG_gameInfo.play.getEvent().getPt2();
}

inline f32 dComIfGp_event_getCullRate() {
    return g_dComIfG_gameInfo.play.getEvent().getCullRate();
}

inline void dComIfGp_event_setCullRate(f32 ratio) {
    g_dComIfG_gameInfo.play.getEvent().setCullRate(ratio);
}

inline BOOL dComIfGp_event_check() {
    return g_dComIfG_gameInfo.play.getEvent().check();
}

inline dEvent_manager_c* dComIfGp_getPEvtManager() {
    return &g_dComIfG_gameInfo.play.getEvtManager();
}

inline u8 dComIfGp_event_getMode() {
    return g_dComIfG_gameInfo.play.getEvent().getMode();
}

// Note: Some of the below functions call g_dComIfG_gameInfo.play.getEvtManager(), while others use
// dComIfGp_getPEvtManager(), without a clear pattern for which was chosen.

inline u32 dComIfGp_evmng_getEventPrio(s16 eventIdx) {
    return g_dComIfG_gameInfo.play.getEvtManager().getEventPrio(eventIdx);
}

inline s16 dComIfGp_evmng_getEventIdx(const char* pName, u8 evNo) {
    return g_dComIfG_gameInfo.play.getEvtManager().getEventIdx(pName, evNo);
}

inline int dComIfGp_evmng_getToolId(u8 idx, int sub) {
    return dComIfGp_getPEvtManager()->getToolId(idx, sub);
}

inline int dComIfGp_evmng_getMyStaffId(const char* pName, fopAc_ac_c* pActor = NULL, int staffType = 0) {
    return dComIfGp_getPEvtManager()->getMyStaffId(pName, pActor, staffType);
}

inline int dComIfGp_evmng_getMyActIdx(int staffIdx, char** pActions, int actionCount, int force, int param_5) {
    return dComIfGp_getPEvtManager()->getMyActIdx(staffIdx, pActions, actionCount, force, param_5);
}

inline char* dComIfGp_evmng_getMyActName(int staffIdx) {
    return dComIfGp_getPEvtManager()->getMyActName(staffIdx);
}

inline f32* dComIfGp_evmng_getMyFloatP(int staffIdx, char* name) {
    return reinterpret_cast<f32*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, 0)); //type 0 is float
}

inline Vec* dComIfGp_evmng_getMyVec3dP(int staffIdx, char* name) {
    return reinterpret_cast<Vec*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, 1)); //type 1 is vec3f
}

inline cXyz* dComIfGp_evmng_getMyXyzP(int staffIdx, char* name) {
    return reinterpret_cast<cXyz*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, 1)); //type 1 is vec3f
}

inline u32* dComIfGp_evmng_getMyIntegerP(int staffIdx, char* name) {
    return reinterpret_cast<u32*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, 3)); //type 3 is int
}

inline char* dComIfGp_evmng_getMyStringP(int staffIdx, char* name) {
    return reinterpret_cast<char*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, 4)); //type 4 is string
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
    s16 eventIdx = dComIfGp_evmng_getEventIdx(pName, 0xFF);
    return g_dComIfG_gameInfo.play.getEvtManager().getEventData(eventIdx) != NULL;
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

/**
 * === DRAWLIST ===
 */

int dComIfGd_setShadow(u32 id, s8 param_2, J3DModel* pModel, cXyz* pPos, f32 param_5, f32 param_6,
                       f32 y, f32 param_8, cBgS_PolyInfo& pFloorPoly, dKy_tevstr_c* param_10,
                       s16 rotY, f32 param_12, GXTexObj* pTexObj);

inline int dComIfGd_setSimpleShadow(cXyz* pPos, f32 param_1, f32 param_2, cXyz* param_3, s16 angle,
                                    f32 param_5, GXTexObj* pTex) {
    return g_dComIfG_gameInfo.drawlist.setSimpleShadow(pPos, param_1, param_2, param_3, angle,
                                                       param_5, pTex);
}

int dComIfGd_setSimpleShadow2(cXyz* pPos, f32 param_1, f32 param_2, cBgS_PolyInfo& pPolyInfo,
                              s16 param_4, f32 param_5, GXTexObj* pTex);

inline int dComIfGd_setRealShadow(u32 id, s8 param_2, J3DModel* pModel, cXyz* pPos, f32 param_5,
                                   f32 param_6, dKy_tevstr_c* pTevStr) {
    return g_dComIfG_gameInfo.drawlist.setRealShadow(id, param_2, pModel, pPos, param_5, param_6,
                                                     pTevStr);
}

inline int dComIfGd_setRealShadow2(u32 id, s8 param_2, J3DModel* pModel, cXyz* pPos, f32 param_5,
                                   f32 param_6, dKy_tevstr_c* pTevStr) {
    return g_dComIfG_gameInfo.drawlist.setRealShadow2(id, param_2, pModel, pPos, param_5, param_6,
                                                      pTevStr);
}

inline bool dComIfGd_addRealShadow(u32 id, J3DModel* pModel) {
    return g_dComIfG_gameInfo.drawlist.addRealShadow(id, pModel);
}

inline void dComIfGd_imageDrawShadow(Mtx mtx) {
    g_dComIfG_gameInfo.drawlist.imageDrawShadow(mtx);
}

int dComIfGd_setSimpleShadow2(cXyz* i_pos, f32 param_1, f32 param_2, cBgS_PolyInfo& i_floorPoly, s16 i_angle, f32 param_5, GXTexObj* i_tex);

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
inline void dComIfGp_setDmsgArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setDmsgArchive(pArc); }
inline void dComIfGp_setTmsgArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setTmsgArchive(pArc); }
inline JKRArchive* dComIfGp_getTmsgArchive() { return g_dComIfG_gameInfo.play.getTmsgArchive(); }
inline void dComIfGp_setMenuArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setMenuArchive(pArc); }
inline JKRArchive* dComIfGp_getMenuArchive() { return g_dComIfG_gameInfo.play.getMenuArchive(); }
inline void dComIfGp_setFont0Archive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setFont0Archive(pArc); }
inline void dComIfGp_setFont1Archive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setFont1Archive(pArc); }
inline JKRArchive* dComIfGp_getFontArchive() { return g_dComIfG_gameInfo.play.getFontArchive(); }
inline JKRArchive* dComIfGp_getRubyArchive() { return g_dComIfG_gameInfo.play.getRubyArchive(); }
inline void dComIfGp_setLkDArc(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setLkDArc(pArc); }
inline void dComIfGp_setFmapArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setFmapArchive(pArc); }
inline void dComIfGp_setItemResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setItemResArchive(pArc); }
inline void dComIfGp_setClctResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setClctResArchive(pArc); }
inline void dComIfGp_setFmapResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setFmapResArchive(pArc); }
inline void dComIfGp_setDmapResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setDmapResArchive(pArc); }
inline void dComIfGp_setOptResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setOptResArchive(pArc); }
inline JKRArchive* dComIfGp_getClothResArchive() { return g_dComIfG_gameInfo.play.getClothResArchive(); }
inline void dComIfGp_setClothResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setClothResArchive(pArc); }
inline void dComIfGp_setSaveResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setSaveResArchive(pArc); }
inline void dComIfGp_setItemIconArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setItemIconArchive(pArc); }
inline JKRArchive* dComIfGp_getItemIconArchive() { return g_dComIfG_gameInfo.play.getItemIconArchive(); }
inline void dComIfGp_setNameResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setNameResArchive(pArc); }
inline void dComIfGp_setErrorResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setErrorResArchive(pArc); }
inline void dComIfGp_setActionIconArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setActionIconArchive(pArc); }
inline void dComIfGp_setScopeResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setScopeResArchive(pArc); }
inline void dComIfGp_setCamResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setCamResArchive(pArc); }
inline void dComIfGp_setSwimResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setSwimResArchive(pArc); }
inline void dComIfGp_setWindResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setWindResArchive(pArc); }
inline void dComIfGp_setFontArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setFontArchive(pArc); }
inline void dComIfGp_setMsgDtArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setMsgDtArchive(pArc); }
#if VERSION != VERSION_JPN
inline void dComIfGp_setMsgDt2Archive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setMsgDt2Archive(pArc); }
#endif

inline void dComIfGp_setItemTable(void * pData) { g_dComIfG_gameInfo.play.setItemTable(pData); }
inline ItemTableList* dComIfGp_getItemTable() { return g_dComIfG_gameInfo.play.getItemTable(); }
inline void dComIfGp_setActorData(void * pData) { g_dComIfG_gameInfo.play.mADM.SetData(pData); }
inline void dComIfGp_setFmapData(void * pData) { g_dComIfG_gameInfo.play.setFmapData(pData); }

/**
 * === RESOURCE ===
 */

class request_of_phase_process_class;
int dComIfG_resLoad(request_of_phase_process_class* i_phase, char const* arc_name);
int dComIfG_resLoad(request_of_phase_process_class* i_phase, char const* resName, JKRHeap* heap);
int dComIfG_resDelete(request_of_phase_process_class* i_phase, char const* resName);

inline int dComIfG_setObjectRes(const char* name, u8 param_1, JKRHeap* heap) {
    return g_dComIfG_gameInfo.mResControl.setObjectRes(name, param_1, heap);
}

inline int dComIfG_setObjectRes(const char* name, void* param_1, u32 param_2) {
    return g_dComIfG_gameInfo.mResControl.setObjectRes(name, param_1, param_2, NULL);
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

void set(u8, u16, cXyz const*, csXyz const*, cXyz const*, u8, dPa_levelEcallBack*, s8,
         GXColor const*, GXColor const*, cXyz const*);

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

inline void dComIfGp_particle_setSimple(u16 particleID, cXyz* pos, u8 alpha, GXColor& prmColor,
                                        GXColor& envColor, int param_6) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    pParticle->setSimple(particleID, pos, alpha, prmColor, envColor, param_6);
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

/**
 * === ATTENTION ===
 */

inline void dComIfGp_att_CatchRequest(fopAc_ac_c* param_0, u8 param_1, f32 param_2, f32 param_3,
                                      f32 param_4, s16 param_5, s32 param_6) {
    dAttention_c& attention = g_dComIfG_gameInfo.play.getAttention();
    attention.CatchRequest(param_0, param_1, param_2, param_3, param_4,param_5, param_6);
}

inline u8 dComIfGp_att_getCatchChgItem() {
    return g_dComIfG_gameInfo.play.getAttention().getCatchChgItem();
}

/**
 * === MISC ===
 */

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

inline int dComIfG_getTimerRestTimeMs() {
    int limit = g_dComIfG_gameInfo.play.getTimerLimitTimeMs();
    int now = g_dComIfG_gameInfo.play.getTimerNowTimeMs();
    return limit - now;
}

inline void dComIfG_TimerDeleteRequest() {
    if (dComIfG_getTimerPtr() != NULL)
        dComIfG_getTimerPtr()->deleteRequest();
}
inline void dComIfG_TimerStart(int timer, s16 mode) {
    if (dComIfG_getTimerMode() == mode && dComIfG_getTimerPtr() != NULL)
        if (timer != 0)
            dComIfG_getTimerPtr()->start(timer);
        else
            dComIfG_getTimerPtr()->start();
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
int dComIfG_resetToOpening(scene_class* i_scene);

int dComIfG_changeOpeningScene(scene_class* i_scene, s16 i_procName);

#endif /* D_COM_D_COM_INF_GAME_H */
