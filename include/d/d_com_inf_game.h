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
#include "d/d_wood.h"
#include "d/d_demo.h"
#include "d/d_timer.h"
#include "SSystem/SComponent/c_data_tbl.h"

class JKRArchive;
class JKRAramBlock;
class JKRExpHeap;
class dPa_control_c;
class dDemo_manager_c;
class dMagma_packet_c;
class dGrass_packet_c;
class dTree_packet_c;
class dFlower_packet_c;
class Packet_c;
class daPy_py_c;
class daPy_lk_c;
class daPy_npc_c;
class daShip_c;
class daAgb_c;
class dTimer_c;
class camera_class;
class J2DOrthoGraph;
class dDemo_actor_c;

enum ALWAYS_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    ALWAYS_BCK_FA=0xC,
    ALWAYS_BCK_OBM_SYOUGEKISW=0xD,
    ALWAYS_BCK_START=0xE,
    ALWAYS_BCK_VBELL=0xF,
    ALWAYS_BCK_VBOKL=0x10,
    ALWAYS_BCK_VCHUL=0x11,
    ALWAYS_BCK_VDOKL=0x12,
    ALWAYS_BCK_VESAL=0x13,
    ALWAYS_BCK_VHANL=0x14,
    ALWAYS_BCK_VHAPL=0x15,
    ALWAYS_BCK_W_PILLAR_A=0x16,
    ALWAYS_BCK_YJ_DELETE=0x17,
    ALWAYS_BCK_YJ_IN=0x18,
    ALWAYS_BCK_YJ_LOOP=0x19,
    ALWAYS_BCK_YJ_OUT=0x1A,
    ALWAYS_BCK_YJ_SCALE=0x1B,
    
    /* BDL */
    ALWAYS_BDL_ARROWITEM=0x1E,
    ALWAYS_BDL_FA=0x1F,
    ALWAYS_BDL_KROCK_00=0x20,
    ALWAYS_BDL_OBM_KOISI1=0x21,
    ALWAYS_BDL_OBM_KOISI2=0x22,
    ALWAYS_BDL_OBM_KOTUBO1=0x23,
    ALWAYS_BDL_OBM_OOTUBO1=0x24,
    ALWAYS_BDL_VBELL=0x25,
    ALWAYS_BDL_VBOKL=0x26,
    ALWAYS_BDL_VDOKL=0x27,
    ALWAYS_BDL_VESAL=0x28,
    ALWAYS_BDL_VHAPL=0x29,
    ALWAYS_BDL_VHRTL=0x2A,
    ALWAYS_BDL_VKEYL=0x2B,
    
    /* BDLM */
    ALWAYS_BDL_IB=0x2E,
    ALWAYS_BDL_MPA_SIMI=0x2F,
    ALWAYS_BDL_MPI_KOISHI=0x30,
    ALWAYS_BDL_MPM_TUBO=0x31,
    ALWAYS_BDL_MPODA=0x32,
    ALWAYS_BDL_MPODB=0x33,
    ALWAYS_BDL_NH=0x34,
    ALWAYS_BDL_OBM_SYOUGEKISW=0x35,
    ALWAYS_BDL_VCHUL=0x36,
    ALWAYS_BDL_VHANL=0x37,
    ALWAYS_BDL_VHKAL=0x38,
    ALWAYS_BDL_VHUTL=0x39,
    ALWAYS_BDL_VLUPL=0x3A,
    ALWAYS_BDL_W_PILLAR_A=0x3B,
    ALWAYS_BDL_YA=0x3C,
    ALWAYS_BDL_YAZIRUSHI_01=0x3D,
    ALWAYS_BDL_YTHDR00=0x3E,
    
    /* BMTM */
    ALWAYS_BMT_ICE=0x41,
    
    /* BPK */
    ALWAYS_BPK_YJ_DELETE=0x44,
    ALWAYS_BPK_YJ_IN=0x45,
    ALWAYS_BPK_YJ_LOOP=0x46,
    ALWAYS_BPK_YJ_OUT=0x47,
    ALWAYS_BPK_YJ_SCALE=0x48,
    
    /* BRK */
    ALWAYS_BRK_IB_01=0x4B,
    ALWAYS_BRK_IB_02=0x4C,
    ALWAYS_BRK_MPA_SIMI=0x4D,
    ALWAYS_BRK_TNH=0x4E,
    ALWAYS_BRK_VCHUL=0x4F,
    ALWAYS_BRK_VHANL=0x50,
    ALWAYS_BRK_VLUPL=0x51,
    ALWAYS_BRK_YTHDR00=0x52,
    
    /* BTK */
    ALWAYS_BTK_EFA_USONAMI_01=0x55,
    ALWAYS_BTK_IB=0x56,
    ALWAYS_BTK_ICE=0x57,
    ALWAYS_BTK_OBM_SYOUGEKISW=0x58,
    ALWAYS_BTK_VBELL=0x59,
    ALWAYS_BTK_VHANL=0x5A,
    ALWAYS_BTK_VHKAL=0x5B,
    ALWAYS_BTK_VHUTL=0x5C,
    ALWAYS_BTK_VLUPL=0x5D,
    ALWAYS_BTK_W_PILLAR_A=0x5E,
    ALWAYS_BTK_YA=0x5F,
    ALWAYS_BTK_YTHDR00=0x60,
    
    /* BTP */
    ALWAYS_BTP_MPA_SIMI=0x63,
    ALWAYS_BTP_MPI_KIBAKO_TARU=0x64,
    ALWAYS_BTP_MPI_KINOHAHEN=0x65,
    ALWAYS_BTP_MPI_KOISHI=0x66,
    ALWAYS_BTP_MPM_TUBO=0x67,
    
    /* DAT */
    ALWAYS_BIN_ITEM_TABLE=0x6A,
    
    /* TEX */
    ALWAYS_BTI_AK_HOUSHI00=0x6D,
    ALWAYS_BTI_AK_SMOKE01=0x6E,
    ALWAYS_BTI_B_SEA_TEX0AND2=0x6F,
    ALWAYS_BTI_B_WYURAYURA_TEX1=0x70,
    ALWAYS_I4_BALL128B=0x71,
    ALWAYS_BTI_BLACK_WHITE_2=0x72,
    ALWAYS_BTI_CAMERA_FREE=0x73,
    ALWAYS_BTI_CAMERA_SELF=0x74,
    ALWAYS_BTI_F_SHIPICON=0x75,
    ALWAYS_CI4_MAP08G=0x76,
    ALWAYS_CI4_MAP16G=0x77,
    ALWAYS_BTI_MAP_BLACK_CI8=0x78,
    ALWAYS_BTI_MAP_CHECK16_CI4=0x79,
    ALWAYS_BTI_MAP_FRAME1=0x7A,
    ALWAYS_BTI_MAP_FRAME2=0x7B,
    ALWAYS_BTI_MAP_FRAME3=0x7C,
    ALWAYS_BTI_MAP_FRAME4=0x7D,
    ALWAYS_BTI_ROPE=0x7E,
    ALWAYS_BTI_SHMREF=0x7F,
    ALWAYS_BTI_TREASUREBOX=0x80,
    ALWAYS_I8_TX_SNOW01=0x81,
    ALWAYS_BTI_TXA_LENS_32HALF=0x82,
    ALWAYS_BTI_TXA_MOYA_A_64=0x83,
    ALWAYS_BTI_TXA_MOYA_B_64=0x84,
    ALWAYS_BTI_TXA_RING_A_32HAFE=0x85,
    ALWAYS_BTI_TXA_TAIYO=0x86,
    ALWAYS_BTI_TXA_TUKI_AS=0x87,
    ALWAYS_BTI_TXA_TUKI_BS=0x88,
    ALWAYS_BTI_TXA_TUKI_CS=0x89,
    ALWAYS_BTI_TXA_TUKI_DS=0x8A,
    ALWAYS_BTI_TXA_USONAMI_256_64MIP=0x8B,
    ALWAYS_BTI_TXA_USONAMI_M_256_64MIP=0x8C,
    ALWAYS_BTI_TXM_ROPE1=0x8D,
    ALWAYS_BTI_UMIPT=0x8E,
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
    /* 0x04 */ s32 mTimerNowTimeMs;
    /* 0x08 */ s32 mTimerLimitTimeMs;
    /* 0x0C */ s32 mTimerMode;
    /* 0x10 */ u16 mTimerType;
};

class dADM_CharTbl : public cDT {
public:
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
    /* 0x06 */ u8 field_0x06;
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
    dComIfG_play_c() { ct(); }

    void ct();
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
    void setStageNameOff() { mPlacenameState = 1; }

    fopAc_ac_c* getPlayerPtr(int idx) { return (fopAc_ac_c*)mpPlayerPtr[idx]; }
    fopAc_ac_c* getPlayer(int idx) { return (fopAc_ac_c*)mpPlayer[idx]; }
    void setPlayer(int idx, fopAc_ac_c* player) { mpPlayer[idx] = (daPy_py_c*)player; }
    void setPlayerPtr(int idx, fopAc_ac_c* playerPtr) { mpPlayerPtr[idx] = playerPtr; }
    s8 getPlayerCameraID(int idx) { return mCurCamera[idx]; }

    int getItemRupeeCount() { return mItemRupeeCount; }
    void setItemRupeeCount(s32 count) { mItemRupeeCount += count; }
    void setMessageCountNumber(s16 num) { mMsgCountNumber = num; }

    void setLkDemoAnmArchive(JKRArchive* i_arc) { mpLkDArc = i_arc; }
    void setStatus(u16 status) { mStatus = status; }
    void onStatus(u16 status) { mStatus |= status; }
    s32 checkStatus(u16 flags) { return flags & mStatus; }

    void setShipId(u8 i_id) { mShipId = i_id; }
    void setShipRoomId(u8 i_id) { mShipRoomId = i_id; }
    u8 getShipId() { return mShipId; }
    u8 getShipRoomId() { return mShipRoomId; }

    void setAgb(fopAc_ac_c* i_agb) { mpAgb = (daAgb_c*)i_agb; }
    daAgb_c* getAgb() { return mpAgb; }

    void setIkadaShipBeforePos(Vec& i_pos) { mIkadaLinkPos = i_pos; }
    void setIkadaShipId(u8 i_id) { mIkadaShipId = i_id; }
    void setIkadaShipBeforeRoomId(u8 i_roomId) { mIkadaShipBeforeRoomId = i_roomId; }
    u8 getIkadaShipId() { return mIkadaShipId; }
    u8 getIkadaShipBeforeRoomId() { return mIkadaShipBeforeRoomId; }

    dTimer_c* getTimerPtr() { return mTimerInfo.mTimerPtr; }
    s32 getTimerMode() { return mTimerInfo.mTimerMode; }
    
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

    u8 checkMesgCancelButton() { return field_0x4949; }

    void setPlayerStatus(int param_0, int i, u32 flag) { mPlayerStatus[param_0][i] |= flag; }
    void clearPlayerStatus(int param_0, int i, u32 flag) { mPlayerStatus[param_0][i] &= ~flag; }
    bool checkPlayerStatus(int param_0, int i, u32 flag) { return flag & mPlayerStatus[param_0][i]; }

    u8 getSelectItem(int idx) { return mEquippedItems[idx]; }
    void setSelectItem(int idx, u8 itemNo) { mEquippedItems[idx] = itemNo; }
    
    void setAStatus(u8 status) { mCurrButtonBAction = status; }
    void setDoStatus(u8 status) { mCurrButtonAAction = status; }
    void setRStatusForce(u8 status) { field_0x4930 = status; }

    void setCurrentGrafPort(J2DOrthoGraph* i_graf) { mCurrentGrafPort = i_graf; }
    void setCurrentWindow(dDlst_window_c* i_window) { mCurrentWindow = i_window; }
    void setCurrentView(view_class* i_view) { mCurrentView = i_view; }
    void setCurrentViewport(view_port_class* i_viewport) { mCurrentViewport = i_viewport; }

    J2DOrthoGraph* getCurrentGrafPort() { return mCurrentGrafPort; }

    JKRExpHeap * getExpHeap2D() { return mpExpHeap2D; }

    inline u8 getHeapLockFlag() { return mHeapLockFlag; }
    inline void setHeapLockFlag(u8 flag) { mHeapLockFlag = flag; }
    inline void offHeapLockFlag() { mHeapLockFlag = 0; }

    void setMsgArchive(JKRArchive * pArc) { mpMsgArchive = pArc; }
    void setDmsgArchive(JKRArchive * pArc) { mpDmsgArchive = pArc; }
    void setTmsgArchive(JKRArchive * pArc) { mpTmsgArchive = pArc; }
    JKRArchive* getTmsgArchive() { return mpTmsgArchive; }
    void setMenuArchive(JKRArchive * pArc) { mpMenuArchive = pArc; }
    void setFont0Archive(JKRArchive * pArc) { mpFont0Archive = pArc; }
    void setFont1Archive(JKRArchive * pArc) { mpFont1Archive = pArc; }
    JKRArchive* getFontArchive() { return mpFont0Archive; }
    JKRArchive* getRubyArchive() { return mpFont1Archive; }
    void setAnmArchive(JKRArchive * pArc) { mpAnmArchive = pArc; }
    void setLkDArc(JKRArchive * pArc) { mpLkDArc = pArc; }
    void setFmapArchive(JKRArchive * pArc) { mpFmapArchive = pArc; }
    void setItemResArchive(JKRArchive * pArc) { mpItemResArchive = pArc; }
    void setClctResArchive(JKRArchive * pArc) { mpClctResArchive = pArc; }
    void setFmapResArchive(JKRArchive * pArc) { mpFmapResArchive = pArc; }
    void setDmapResArchive(JKRArchive * pArc) { mpDmapResArchive = pArc; }
    void setOptResArchive(JKRArchive * pArc) { mpOptResArchive = pArc; }
    void setClothResArchive(JKRArchive * pArc) { mpClothResArchive = pArc; }
    void setSaveResArchive(JKRArchive * pArc) { mpSaveResArchive = pArc; }
    void setItemIconArchive(JKRArchive * pArc) { mpItemIconArchive = pArc; }
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
    /* 0x4800 */ JKRAramBlock* mAramHeap0[3];
    /* 0x480C */ JKRAramBlock* mAramHeap1[4];
    /* 0x481C */ JKRAramBlock* field_0x481c;
    /* 0x4820 */ JKRAramBlock* field_0x4820;
#else
    /* 0x47FC */ JKRAramBlock* mAramHeap0[3];
    /* 0x480C */ JKRAramBlock* mAramHeap1[4];
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
    /* 0x4841 */ u8 field_0x4841;
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
    /* 0x491A */ s16 field_0x491a;
    /* 0x491C */ s16 field_0x491c;
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
    /* 0x4933 */ u8 mEquippedItems[4];
    /* 0x4937 */ u8 field_0x4937[4];
    /* 0x493B */ u8 mMesgAnime;
    /* 0x493C */ u8 mMesgAnimeTagInfo;
    /* 0x493D */ u8 field_0x493d;
    /* 0x493E */ u8 field_0x493e;
    /* 0x493F */ u8 field_0x493f;
    /* 0x4940 */ u8 field_0x4940;
    /* 0x4941 */ u8 field_0x4941;
    /* 0x4942 */ u8 field_0x4942;
    /* 0x4943 */ u8 field_0x4943;
    /* 0x4944 */ u8 field_0x4944;
    /* 0x4945 */ u8 field_0x4945;
    /* 0x4946 */ u8 field_0x4946;
    /* 0x4947 */ u8 field_0x4947;
    /* 0x4948 */ u8 field_0x4948;
    /* 0x4949 */ u8 field_0x4949;
    /* 0x494A */ u8 field_0x494a[6];
    /* 0x4950 */ u8 mTactMode;
    /* 0x4951 */ u8 field_0x4951;
    /* 0x4952 */ u8 field_0x4952;
    /* 0x4953 */ u8 field_0x4953;
    /* 0x4954 */ u8 field_0x4954;
    /* 0x4955 */ u8 field_0x4955;
    /* 0x4956 */ u8 field_0x4956;
    /* 0x4957 */ u8 mPlacenameIndex;
    /* 0x4958 */ u8 mPlacenameState;
    /* 0x4959 */ u8 field_0x4959;
    /* 0x495A */ u8 field_0x495a;
    /* 0x495B */ u8 field_0x495b;
    /* 0x495C */ u8 field_0x495c;
    /* 0x495D */ u8 field_0x495d;
    /* 0x495E */ u8 field_0x495e;
    /* 0x495F */ u8 field_0x495f;
    /* 0x4960 */ u8 field_0x4960;
    /* 0x4961 */ u8 field_0x4961;
    /* 0x4962 */ u8 mHeapLockFlag;
    /* 0x4963 */ u8 field_0x4963;
    /* 0x4964 */ u8 mGameLanguage;
    /* 0x4965 */ u8 field_0x4965;
    /* 0x4966 */ char field_0x4966[1];
    /* 0x4967 */ u8 field_0x4967[0x4977 - 0x4967];
    /* 0x4977 */ u8 field_0x4977;
    /* 0x4978 */ u8 field_0x4978;
    /* 0x4979 */ u8 field_0x4979;
    /* 0x497A */ u8 field_0x497a;
    /* 0x497B */ u8 field_0x497B[0x497C - 0x497B];
    /* 0x497C */ JKRExpHeap* mpExpHeap2D;
    /* 0x4980 */ int mMesgCameraTagInfo;
    /* 0x4984 */ int field_0x4984;
    /* 0x4988 */ int field_0x4988[10];
    /* 0x49B0 */ u8 field_0x49B0[0x4A24 - 0x49B0];
    /* 0x4A24 */ daAgb_c* mpAgb;
    /* 0x4A28 */ u32 mPlayerStatus[2][2];
    /* 0x4A38 */ u8 field_0x4A38[0x4A3A - 0x4A38];
    /* 0x4A3A */ u8 mMiniGameType;
    /* 0x4A3B */ u8 field_0x4A3B[0x4A40 - 0x4A3B];
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
    dComIfG_inf_c() { ct(); }
    ~dComIfG_inf_c() {}

    void ct();

    /* 0x00000 */ dSv_info_c save;
    /* 0x012A0 */ dComIfG_play_c play;
    /* 0x05D1C */ dDlst_list_c drawlist;
    /* 0x1BF50 */ u8 field_0x1BF50[0x1BFC0 - 0x1BF50];
    /* 0x1BFC0 */ dRes_control_c mResControl;
    /* 0x1D1C0 */ u8 field_0x1d1c0;
    /* 0x1D1C1 */ u8 field_0x1d1c1;
};

#if VERSION != VERSION_JPN
STATIC_ASSERT(sizeof(dComIfG_inf_c) == 0x1D1C8);
#endif

extern dComIfG_inf_c g_dComIfG_gameInfo;

extern JUtility::TColor g_clearColor;
extern JUtility::TColor g_blackColor;
extern JUtility::TColor g_whiteColor;
extern JUtility::TColor g_saftyWhiteColor;

/**
 * === SAVE ===
 */

u8 dComIfGs_checkGetItem(u8);

inline void dComIfGs_init() {
    g_dComIfG_gameInfo.save.init();
}

inline dSv_player_bag_item_c* dComIfGs_getpBagItem() {
    return g_dComIfG_gameInfo.save.getPlayer().getpBagItem();
}

inline u8 dComIfGs_checkReserveItem(u8 i_itemNo) {
    return dComIfGs_getpBagItem()->checkReserveItem(i_itemNo);
}

inline void dComIfGs_initZone() {
    g_dComIfG_gameInfo.save.initZone();
}

inline u32 dComIfGs_createZone(int i_roomNo) {
    return g_dComIfG_gameInfo.save.createZone(i_roomNo);
}

inline u8 dComIfGs_getSelectEquip(int param_0) {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getSelectEquip(param_0);
}

inline u8 dComIfGs_getWalletSize() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getWalletSize();
}

inline void dComIfGs_setWalletSize(u8 size) {
    g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().setWalletSize(size);
}

inline int dComIfGs_getRupee() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getRupee();
}

inline u8 dComIfGs_getItemBeast(int param_0) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().getBeast(param_0);
}

inline u8 dComIfGs_getItemBait(int param_0) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().getBait(param_0);
}

inline u8 dComIfGs_getItemReserve(int param_0) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().getReserve(param_0);
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

inline void dComIfGs_setItem(int i_idx, u8 i_itemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getItem().setItem(i_idx, i_itemNo);
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

inline BOOL dComIfGs_isGetItemReserve(int i_no) {
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

inline void dComIfGs_offCompleteCollectMap(int i_no) {
    g_dComIfG_gameInfo.save.getPlayer().getMap().offCompleteMap(i_no - 1);
}

inline u32 dComIfGs_getArrowNum() {
    return g_dComIfG_gameInfo.save.getPlayer().getItemRecord().getArrowNum();
}

inline void dComIfGs_setArrowNum(u8 num) {
    g_dComIfG_gameInfo.save.getPlayer().getItemRecord().setArrowNum(num);
}

inline u32 dComIfGs_getBombNum() {
    return g_dComIfG_gameInfo.save.getPlayer().getItemRecord().getBombNum();
}

inline void dComIfGs_setBombNum(u8 num) {
    g_dComIfG_gameInfo.save.getPlayer().getItemRecord().setBombNum(num);
}

inline u8 dComIfGs_getBeastNum(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItemRecord().getBeastNum(i_idx);
}

inline u8 dComIfGs_getBaitNum(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItemRecord().getBaitNum(i_idx);
}

inline u8 dComIfGs_getReserveNum(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItemRecord().getReserveNum(i_idx);
}

inline void dComIfGs_setReserveItemEmpty() {
    g_dComIfG_gameInfo.save.getPlayer().getBagItem().setReserveItemEmpty();
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

inline void dComIfGs_setPlayerPriest(u8 i_option, cXyz& i_pos, s16 i_angle, s8 i_roomNo) {
    g_dComIfG_gameInfo.save.getPlayer().getPriest().set(i_option, i_pos, i_angle, i_roomNo);
}

inline int dComIfGs_getTriforceNum() {
    return g_dComIfG_gameInfo.save.getPlayer().getCollect().getTriforceNum();
}

inline u8 dComIfGs_getOptVibration() {
    return g_dComIfG_gameInfo.save.getPlayer().getConfig().getVibration();
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

BOOL dComIfGs_isStageBossEnemy(int i_stageNo);

inline BOOL dComIfGs_isStageBossEnemy() {
    return g_dComIfG_gameInfo.save.getMemory().getBit().isStageBossEnemy();
}

inline void dComIfGs_onStageLife() {
    g_dComIfG_gameInfo.save.getMemory().getBit().onStageLife();
}

void dComIfGs_onStageLife(int i_stageNo);

inline BOOL dComIfGs_isStageLife() {
    return g_dComIfG_gameInfo.save.getMemory().getBit().isStageLife();
}

inline BOOL dComIfGs_isCollect(int i_idx, u8 i_item) {
    return g_dComIfG_gameInfo.save.getPlayer().getCollect().isCollect(i_idx, i_item);
}

inline void dComIfGs_onCollect(int i_idx, u8 i_item) {
    g_dComIfG_gameInfo.save.getPlayer().getCollect().onCollect(i_idx, i_item);
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

void dComIfGs_setSelectEquip(int i_type, u8 i_itemNo);

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

inline void dComIfGs_setEmptyBottle() {
    g_dComIfG_gameInfo.save.getPlayer().getItem().setEmptyBottle();
}

inline void dComIfGs_setEmptyBottleItemIn(u8 i_itemNo) {
    g_dComIfG_gameInfo.save.getPlayer().getItem().setEmptyBottleItemIn(i_itemNo);
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

inline u8 dComIfGs_getClearCount() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerInfo().getClearCount();
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

inline u16 dComIfGs_getMaxLife() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getMaxLife();
}

inline u8 dComIfGs_getMagic() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getMagic();
}

inline u8 dComIfGs_getMaxMagic() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getMaxMagic();
}

inline u8 dComIfGs_getKeyNum() {
    return g_dComIfG_gameInfo.save.getMemory().getBit().getKeyNum();
}

u8 dComIfGs_checkGetItemNum(u8 i_itemNo);

BOOL dComIfGs_checkSeaLandingEvent(s8 i_roomNo);

/**
 * === PLAY ===
 */

void dComIfGp_setNextStage(const char* i_stageName, s16 i_point, s8 i_roomNo, s8 i_layer,
                           f32 i_lastSpeed, u32 i_lastMode, int, s8 i_wipe);
dStage_Ship_data* dComIfGp_getShip(int i_roomNo, int param_1);
bool dComIfGp_getMapTrans(int i_roomNo, f32* o_transX, f32* o_transY, s16* o_angle);

inline camera_class* dComIfGp_getCamera(int idx) {
    return g_dComIfG_gameInfo.play.getCamera(idx);
}

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

inline void dComIfGp_setStageNameOff() {
    g_dComIfG_gameInfo.play.setStageNameOff();
}

inline s8 dComIfGp_getStartStageRoomNo() {
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
    return dStage_roomControl_c::getBgW(i_roomNo);
}

inline void dComIfGp_roomControl_setBgW(int i_roomNo, dBgW * i_bgw) {
    dStage_roomControl_c::setBgW(i_roomNo, i_bgw);
}

inline s32 dComIfGp_roomControl_getZoneNo(int i_roomNo) {
    return dStage_roomControl_c::getZoneNo(i_roomNo);
}

inline void dComIfGp_roomControl_setZoneNo(int i_roomNo, int i_zoneNo) {
    dStage_roomControl_c::setZoneNo(i_roomNo, i_zoneNo);
}

inline dKy_tevstr_c* dComIfGp_roomControl_getTevStr(int room_no) {
    return g_dComIfG_gameInfo.play.getRoomControl()->getTevStr(room_no);
}

inline void dComIfGp_roomControl_init() {
    g_dComIfG_gameInfo.play.getRoomControl()->init();
}

inline dStage_roomStatus_c* dComIfGp_roomControl_getStatusRoomDt(int room_no) {
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

inline int dComIfGp_roomControl_loadRoom(int param_0, u8* param_1) {
    return g_dComIfG_gameInfo.play.getRoomControl()->loadRoom(param_0, param_1);
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

inline dDetect_c& dComIfGp_getDetect() {
    return g_dComIfG_gameInfo.play.getDetect();
}

inline dMagma_packet_c* dComIfGp_getMagma() {
    return g_dComIfG_gameInfo.play.getMagma();
}

inline dGrass_packet_c* dComIfGp_getGrass() {
    return g_dComIfG_gameInfo.play.getGrass();
}

inline dTree_packet_c* dComIfGp_getTree() {
    return g_dComIfG_gameInfo.play.getTree();
}

inline dWood::Packet_c* dComIfGp_getWood() {
    return g_dComIfG_gameInfo.play.getWood();
}

inline dFlower_packet_c* dComIfGp_getFlower() {
    return g_dComIfG_gameInfo.play.getFlower();
}

inline void dComIfGp_executeMagma() {
    return g_dComIfG_gameInfo.play.executeMagma();
}

inline void dComIfGp_executeGrass() {
    return g_dComIfG_gameInfo.play.executeGrass();
}

inline void dComIfGp_executeTree() {
    return g_dComIfG_gameInfo.play.executeTree();
}

inline void dComIfGp_executeWood() {
    return g_dComIfG_gameInfo.play.executeWood();
}

inline void dComIfGp_executeFlower() {
    return g_dComIfG_gameInfo.play.executeFlower();
}

inline void dComIfGp_drawMagma() {
    return g_dComIfG_gameInfo.play.drawMagma();
}

inline void dComIfGp_drawGrass() {
    return g_dComIfG_gameInfo.play.drawGrass();
}

inline void dComIfGp_drawTree() {
    return g_dComIfG_gameInfo.play.drawTree();
}

inline void dComIfGp_drawWood() {
    return g_dComIfG_gameInfo.play.drawWood();
}

inline void dComIfGp_drawFlower() {
    return g_dComIfG_gameInfo.play.drawFlower();
}

inline void dComIfGp_map_mapBufferSendAGB(int param_0) {
    dMap_c::mapBufferSendAGB(param_0);
}

inline dDemo_manager_c* dComIfGp_demo_get() {
    return g_dComIfG_gameInfo.play.getDemo();
}

inline void dComIfGp_demo_update() {
    g_dComIfG_gameInfo.play.getDemo()->update();
}

inline dDemo_actor_c* dComIfGp_demo_getActor(u8 id) {
    return g_dComIfG_gameInfo.play.getDemo()->mDemoObj.getActor(id);
}

inline void dComIfGp_setLkDemoAnmArchive(JKRArchive* i_arc) {
    g_dComIfG_gameInfo.play.setLkDemoAnmArchive(i_arc);
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

inline u8 dComIfGp_checkMesgCancelButton() {
    return g_dComIfG_gameInfo.play.checkMesgCancelButton();
}

inline bool dComIfGp_checkPlayerStatus0(int param_0, u32 flag) {
    return g_dComIfG_gameInfo.play.checkPlayerStatus(param_0, 0, flag);
}

inline bool dComIfGp_checkPlayerStatus1(int param_0, u32 flag) {
    return g_dComIfG_gameInfo.play.checkPlayerStatus(param_0, 1, flag);
}

inline void dComIfGp_clearPlayerStatus0(int param_0, u32 flag) {
    g_dComIfG_gameInfo.play.clearPlayerStatus(param_0, 0, flag);
}

inline void dComIfGp_clearPlayerStatus1(int param_0, u32 flag) {
    g_dComIfG_gameInfo.play.clearPlayerStatus(param_0, 1, flag);
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

inline void dComIfGp_setCurrentGrafPort(J2DOrthoGraph* i_graf) {
    g_dComIfG_gameInfo.play.setCurrentGrafPort(i_graf);
}

inline u8 dComIfGp_getMiniGameType() {
    // TODO add enum for minigame type.
    // 0 for none, 8 for shooting the fishman, 2/6 for orca, 7 for mail sorting, etc
    return g_dComIfG_gameInfo.play.mMiniGameType;
}

inline void dComIfGp_setAStatus(u8 status) {
    g_dComIfG_gameInfo.play.setAStatus(status);
}

inline void dComIfGp_setDoStatus(u8 status) {
    g_dComIfG_gameInfo.play.setDoStatus(status);
}

inline void dComIfGp_setRStatusForce(u8 status) {
    g_dComIfG_gameInfo.play.setRStatusForce(status);
}

inline dDlst_window_c * dComIfGp_getWindow(int idx) { return &g_dComIfG_gameInfo.play.mDlstWindow[idx]; }

inline dADM_CharTbl* dComIfGp_CharTbl() {
    return &g_dComIfG_gameInfo.play.mADM.mCharTbl;
}

inline J2DOrthoGraph* dComIfGp_getCurrentGrafPort() {
    return g_dComIfG_gameInfo.play.getCurrentGrafPort();
}

inline JKRExpHeap * dComIfGp_getExpHeap2D() {
    return g_dComIfG_gameInfo.play.getExpHeap2D();
}

inline u8 dComIfGp_getHeapLockFlag() {
    return g_dComIfG_gameInfo.play.getHeapLockFlag();
}

inline void dComIfGp_setHeapLockFlag(u8 flag) {
    g_dComIfG_gameInfo.play.setHeapLockFlag(flag);
}

inline void dComIfGp_offHeapLockFlag() {
    g_dComIfG_gameInfo.play.offHeapLockFlag();
}

/**
 * === EVENT ===*/

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

inline void dComIfGp_event_remove() {
    g_dComIfG_gameInfo.play.getEvent().remove();
}

inline void dComIfGp_event_reset() {
    g_dComIfG_gameInfo.play.getEvent().reset();
}

inline u8 dComIfGp_event_getPreItemNo() {
    return g_dComIfG_gameInfo.play.getEvent().getPreItemNo();
}

inline void dComIfGp_event_setItemPartnerId(u32 id) {
    g_dComIfG_gameInfo.play.getEvent().setPtI_Id(id);
}

inline void dComIfGp_event_setItemPartner(void* pt) {
    g_dComIfG_gameInfo.play.getEvent().setPtI(pt);
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

inline BOOL dComIfGp_event_compulsory(void* param_1, const char* param_2, u16 param_3) {
    return g_dComIfG_gameInfo.play.getEvent().compulsory(param_1, param_2, param_3);
}

inline s32 dComIfGp_event_order(u16 eventType, u16 priority, u16 flag, u16 hind, void* pActor1, void* pActor2, s16 eventID, u8 infoIdx) {
    return g_dComIfG_gameInfo.play.getEvent().order(eventType, priority, flag, hind, pActor1, pActor2, eventID, infoIdx);
}

inline s32 dComIfGp_event_orderOld(u16 eventType, u16 priority, u16 flag, u16 hind, void* pActor1, void* pActor2, const char *pEventName) {
    return g_dComIfG_gameInfo.play.getEvent().orderOld(eventType, priority, flag, hind, pActor1, pActor2, pEventName);
}

inline fopAc_ac_c* dComIfGp_event_getTalkPartner() {
    u32 t = g_dComIfG_gameInfo.play.getEvent().mPtTalk;
    return g_dComIfG_gameInfo.play.getEvent().convPId(t);
}

inline void dComIfGp_event_setTalkPartner(void* i_actor) {
    g_dComIfG_gameInfo.play.getEvent().setPtT(i_actor);
}

inline fopAc_ac_c* dComIfGp_event_getItemPartner() {
    u32 i = g_dComIfG_gameInfo.play.getEvent().mPtItem;
    return g_dComIfG_gameInfo.play.getEvent().convPId(i);
}

inline fopAc_ac_c* dComIfGp_event_getPt1() {
    u32 pt1 = g_dComIfG_gameInfo.play.getEvent().mPt1;
    return g_dComIfG_gameInfo.play.getEvent().convPId(pt1);
}

inline fopAc_ac_c* dComIfGp_event_getPt2() {
    u32 pt2 = g_dComIfG_gameInfo.play.getEvent().mPt2;
    return g_dComIfG_gameInfo.play.getEvent().convPId(pt2);
}

inline f32 dComIfGp_event_getCullRate() {
    return g_dComIfG_gameInfo.play.getEvent().getCullRate();
}

inline void dComIfGp_event_setCullRate(f32 ratio) {
    g_dComIfG_gameInfo.play.getEvent().setCullRate(ratio);
}

inline dEvent_manager_c* dComIfGp_getPEvtManager() {
    return &g_dComIfG_gameInfo.play.getEvtManager();
}

inline s16 dComIfGp_evmng_getEventPrio(s16 eventIdx) {
    return dComIfGp_getPEvtManager()->getEventPrio(eventIdx);
}

inline s16 dComIfGp_evmng_getEventIdx(const char* pName, u8 evNo) {
    return dComIfGp_getPEvtManager()->getEventIdx(pName, evNo);
}

inline int dComIfGp_evmng_getMyStaffId(const char* pName, fopAc_ac_c* pActor, s32 param_3) {
    return dComIfGp_getPEvtManager()->getMyStaffId(pName, pActor, param_3);
}

inline int dComIfGp_evmng_getMyActIdx(int staffIdx, const char* const* pActions, int actionCount, int force, int param_5) {
    return dComIfGp_getPEvtManager()->getMyActIdx(staffIdx, pActions, actionCount, force, param_5);
}

inline f32* dComIfGp_evmng_getMyFloatP(int staffIdx, const char* name) {
    return reinterpret_cast<f32*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, 0)); //type 0 is float
}

inline Vec* dComIfGp_evmng_getMyXyzP(int staffIdx, const char* name) {
    return reinterpret_cast<Vec*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, 1)); //type 1 is vec3f
}

inline u32* dComIfGp_evmng_getMyIntegerP(int staffIdx, const char* name) {
    return reinterpret_cast<u32*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, 3)); //type 3 is int
}

inline char* dComIfGp_evmng_getMyStringP(int staffIdx, const char* name) {
    return reinterpret_cast<char*>(dComIfGp_getPEvtManager()->getMySubstanceP(staffIdx, name, 4)); //type 4 is string
}

inline BOOL dComIfGp_evmng_startCheck(s16 eventID) {
    return dComIfGp_getPEvtManager()->startCheck(eventID);
}

inline BOOL dComIfGp_evmng_startCheck(const char* pName) {
    return dComIfGp_getPEvtManager()->startCheckOld(pName);
}

inline BOOL dComIfGp_evmng_endCheck(const char* pName) {
    return dComIfGp_getPEvtManager()->endCheckOld(pName);
}

inline BOOL dComIfGp_evmng_endCheck(s16 eventID) {
    return dComIfGp_getPEvtManager()->endCheck(eventID);
}

inline BOOL dComIfGp_evmng_ChkPresentEnd() {
    return dComIfGp_getPEvtManager()->ChkPresentEnd();
}

inline void dComIfGp_evmng_CancelPresent() {
    return dComIfGp_getPEvtManager()->CancelPresent();
}

inline BOOL dComIfGp_evmng_getIsAddvance(s32 staffIdx) {
    return dComIfGp_getPEvtManager()->getIsAddvance(staffIdx);
}

inline void dComIfGp_evmng_cutEnd(int staffIdx) {
    return dComIfGp_getPEvtManager()->cutEnd(staffIdx);
}

inline void dComIfGp_evmng_execute() {
    g_dComIfG_gameInfo.play.executeEvtManager();
}

inline void dComIfGp_evmng_create() {
    dComIfGp_getPEvtManager()->create();
}

inline void dComIfGp_evmng_remove() {
    dComIfGp_getPEvtManager()->remove();
}

inline void dComIfGp_evmng_setGoal(cXyz* pos) {
    dComIfGp_getPEvtManager()->setGoal(pos);
}

inline int dComIfGp_evmng_startDemo(int eventInfoIdx) {
    return dComIfGp_getPEvtManager()->setStartDemo(eventInfoIdx);
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

inline int dComIfGd_setRealShadow2(u32 id, s8 param_2, J3DModel* pModel, cXyz* pPos, f32 param_5,
                                   f32 param_6, dKy_tevstr_c* pTevStr) {
    return g_dComIfG_gameInfo.drawlist.setRealShadow2(id, param_2, pModel, pPos, param_5, param_6,
                                                      pTevStr);
}

int dComIfGd_setSimpleShadow2(cXyz* i_pos, f32 param_1, f32 param_2, cBgS_PolyInfo& i_floorPoly, s16 i_angle, f32 param_5, GXTexObj* i_tex);

inline void dComIfGd_setAlphaModel(u8 type, Mtx mtx, u8 alpha) {
    g_dComIfG_gameInfo.drawlist.setAlphaModel(type, mtx, alpha);
}

inline void dComIfGd_setSpotModel(u8 type, Mtx mtx, u8 alpha) {
    g_dComIfG_gameInfo.drawlist.setSpotModel(type, mtx, alpha);
}

inline void dComIfGd_setLightModel(u8 type, Mtx mtx, u8 alpha) {
    g_dComIfG_gameInfo.drawlist.setLightModel(type, mtx, alpha);
}

inline s32 dComIfGd_getSpotModelNum() {
    return g_dComIfG_gameInfo.drawlist.getSpotModelNum();
}

inline s32 dComIfGd_getLightModelNum() {
    return g_dComIfG_gameInfo.drawlist.getLightModelNum();
}

inline J3DDrawBuffer* dComIfGd_getListFilter() {
    return g_dComIfG_gameInfo.drawlist.getOpaListFilter();
}

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

inline void dComIfGd_peekZ(s16 x, s16 y, u32 * data) { g_dComIfG_gameInfo.drawlist.newPeekZdata(x, y, data); }

inline void dComIfGd_setWindow(dDlst_window_c* pWindow) { g_dComIfG_gameInfo.drawlist.setWindow(pWindow); }
inline void dComIfGd_setViewPort(view_port_class* pViewPort) { g_dComIfG_gameInfo.drawlist.setViewPort(pViewPort); }
inline view_port_class* dComIfGd_getViewport() { return g_dComIfG_gameInfo.drawlist.getViewport(); }
inline void dComIfGd_setView(view_class* pView) { g_dComIfG_gameInfo.drawlist.setView(pView); }
inline view_class* dComIfGd_getView() { return g_dComIfG_gameInfo.drawlist.getView(); }
inline MtxP dComIfGd_getViewRotMtx() { return dComIfGd_getView()->mViewMtxNoTrans; }

/**
 * === ARCHIVE ===
 */


inline void dComIfGp_setAnmArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setAnmArchive(pArc); }
inline void dComIfGp_setMsgArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setMsgArchive(pArc); }
inline void dComIfGp_setDmsgArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setDmsgArchive(pArc); }
inline void dComIfGp_setTmsgArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setTmsgArchive(pArc); }
inline JKRArchive* dComIfGp_getTmsgArchive() { return g_dComIfG_gameInfo.play.getTmsgArchive(); }
inline void dComIfGp_setMenuArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setMenuArchive(pArc); }
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
inline void dComIfGp_setClothResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setClothResArchive(pArc); }
inline void dComIfGp_setSaveResArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setSaveResArchive(pArc); }
inline void dComIfGp_setItemIconArchive(JKRArchive * pArc) { g_dComIfG_gameInfo.play.setItemIconArchive(pArc); }
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

inline void dComIfGp_particle_createCommon(const void * pArc) {
    g_dComIfG_gameInfo.play.getParticle()->createCommon(pArc);
}

inline void dComIfGp_particle_createRoomScene(void * pData) {
    g_dComIfG_gameInfo.play.getParticle()->createRoomScene(pData);
}

inline void dComIfGp_particle_removeRoomScene() {
    g_dComIfG_gameInfo.play.getParticle()->removeRoomScene();
}

/**
 * === ATTENTION ===
 */

inline void dComIfGp_att_CatchRequest(fopAc_ac_c* param_0, u8 param_1, f32 param_2, f32 param_3,
                                      f32 param_4, s16 param_5, s32 param_6) {
    dAttention_c& attention = g_dComIfG_gameInfo.play.getAttention();
    attention.CatchRequest(param_0, param_1, param_2, param_3, param_4,param_5, param_6);
}

/**
 * === MISC ===
 */

class scene_class;
int dComIfG_resetToOpening(scene_class* i_scene);

inline int dComIfG_getTimerMode() {
    return g_dComIfG_gameInfo.play.getTimerMode();
}

inline dTimer_c* dComIfG_getTimerPtr() {
    return g_dComIfG_gameInfo.play.getTimerPtr();
}

inline void dComIfG_TimerDeleteRequest() {
    dComIfG_getTimerPtr()->deleteRequest();
}

int dComIfG_changeOpeningScene(scene_class* i_scene, s16 i_procName);

#endif /* D_COM_D_COM_INF_GAME_H */
