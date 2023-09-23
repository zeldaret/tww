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

class JKRArchive;
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
    /* 0x10 */ u8 mTimerType;
};

class dADM {
public:
    /* 0x00 */ int mBlockCount;
    /* 0x04 */ void* mpData;
    /* 0x08 */ u8 mCharTbl[0x90];

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

    ~dComIfG_play_c();

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

    fopAc_ac_c* getPlayerPtr(int idx) { return (fopAc_ac_c*)mpPlayerPtr[idx]; }
    fopAc_ac_c* getPlayer(int idx) { return (fopAc_ac_c*)mpPlayer[idx]; }
    s8 getPlayerCameraID(int idx) { return mCurCamera[idx]; }

    int getItemRupeeCount() { return mItemRupeeCount; }
    void setItemRupeeCount(int count) { mItemRupeeCount += count; }
    void setMessageCountNumber(s16 num) { mMsgCountNumber = num; }

    void setLkDemoAnmArchive(JKRArchive* i_arc) { mpLkDArc = i_arc; }
    void setStatus(u16 status) { mStatus = status; }
    s32 checkStatus(u16 flags) { return flags & mStatus; }

    void setShipId(u8 i_id) { mShipId = i_id; }
    void setShipRoomId(u8 i_id) { mShipRoomId = i_id; }
    u8 getShipId() { return mShipId; }
    u8 getShipRoomId() { return mShipRoomId; }

    void setAgb(fopAc_ac_c* i_agb) { mpAgb = (daAgb_c*)i_agb; }

    void setIkadaShipBeforePos(Vec& i_pos) { mIkadaLinkPos = i_pos; }
    void setIkadaShipId(u8 i_id) { mIkadaShipId = i_id; }
    void setIkadaShipBeforeRoomId(u8 i_roomId) { mIkadaShipBeforeRoomId = i_roomId; }
    u8 getIkadaShipId() { return mIkadaShipId; }
    u8 getIkadaShipBeforeRoomId() { return mIkadaShipBeforeRoomId; }

    dTimer_c* getTimerPtr() { return mTimerInfo.mTimerPtr; }
    s32 getTimerMode() { return mTimerInfo.mTimerMode; }
    
    s16 getItemMagicCount() { return mItemMagicCount; }
    void setItemMagicCount(s16 magic) { mItemMagicCount = magic; }

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
    /* 0x47B8 */ JKRArchive* mpFMapArchive;
    /* 0x47BC */ JKRArchive* mpItemResArchive;
    /* 0x47C0 */ JKRArchive* mpClctResArchive;
    /* 0x47C4 */ JKRArchive* mpFMapResArchive;
    /* 0x47C8 */ JKRArchive* mpDMapResArchive;
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
#if VERSION != VERSION_JP
    /* 0x47F8 */ JKRArchive* mpEnglishTextArchive;
    /* 0x47FC */ JKRArchive* mpHyruleTextArchive;
    /* 0x4800 */ u8 mCARDHeap0[0x04];
#endif
    /* 0x4804 */ u8 mCARDHeap1[0x20];
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
    /* 0x48DC */ s16 field_0x48dc;
    /* 0x48DE */ s16 field_0x48de;
    /* 0x48E0 */ s16 mItemArrowNumCount;
    /* 0x48E2 */ s16 field_0x48e2;
    /* 0x48E4 */ s16 mItemBombNumCount;
    /* 0x48E6 */ s16 field_0x48e6;
    /* 0x48E8 */ u8 field_0x48E8[0x48F6 - 0x48E8];
    /* 0x48F6 */ s16 mItemPendantNumCount;
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
    /* 0x4958 */ u8 field_0x4958;
    /* 0x4959 */ u8 field_0x4959;
    /* 0x495A */ u8 field_0x495a;
    /* 0x495B */ u8 field_0x495b;
    /* 0x495C */ u8 field_0x495c;
    /* 0x495D */ u8 field_0x495d;
    /* 0x495E */ u8 field_0x495e;
    /* 0x495F */ u8 field_0x495f;
    /* 0x4960 */ u8 field_0x4960;
    /* 0x4961 */ u8 field_0x4961;
    /* 0x4962 */ u8 field_0x4962;
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
    /* 0x497C */ JKRExpHeap* field_0x497c;
    /* 0x4980 */ int mMesgCameraTagInfo;
    /* 0x4984 */ int field_0x4984;
    /* 0x4988 */ int field_0x4988[10];
    /* 0x49B0 */ u8 field_0x49B0[0x4A24 - 0x49B0];
    /* 0x4A24 */ daAgb_c* mpAgb;
    /* 0x4A28 */ u32 mPlayerStatus[2][2];
    /* 0x4A38 */ u8 field_0x4A38[0x4A40 - 0x4A38];
    /* 0x4A40 */ __d_timer_info_c mTimerInfo;
    /* 0x4A54 */ dDlst_window_c* field_0x4a54;
    /* 0x4A58 */ camera_class* field_0x4a58;
    /* 0x4A5C */ dDlst_window_c* field_0x4a5c;
    /* 0x4A60 */ J2DOrthoGraph* mp2DOrthoGraph;
    /* 0x4A64 */ u8 mShipId;
    /* 0x4A65 */ u8 mShipRoomId;
    /* 0x4A66 */ u8 mIkadaShipBeforeRoomId;
    /* 0x4A67 */ u8 mIkadaShipId;
    /* 0x4A68 */ cXyz mIkadaLinkPos;
    /* 0x4A74 */ void* mpItemTableArchive;
    /* 0x4A78 */ void* mpFmapDataArchive;
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

#if VERSION != VERSION_JP
STATIC_ASSERT(sizeof(dComIfG_inf_c) == 0x1D1C8);
#endif

extern dComIfG_inf_c g_dComIfG_gameInfo;

extern JUtility::TColor g_saftyWhiteColor;
extern JUtility::TColor g_blackColor;

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

inline BOOL dComIfGs_checkReserveItem(u8 i_itemNo) {
    return dComIfGs_getpBagItem()->checkReserveItem(i_itemNo);
}

inline void dComIfGs_initZone() {
    g_dComIfG_gameInfo.save.initZone();
}

inline u8 dComIfGs_getSelectEquip(int param_0) {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getSelectEquip(param_0);
}

inline u8 dComIfGs_getWalletSize() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getWalletSize();
}

inline int dComIfGs_getRupee() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getRupee();
}

inline u8 dComIfGs_getMagic() {
    return g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusA().getMagic();
}

inline u8 dComIfGs_getItem(int param_0) {
    return g_dComIfG_gameInfo.save.getPlayer().getItem().getItem(param_0);
}

inline u8 dComIfGs_getBeast(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().getBeast(i_idx);
}

inline u8 dComIfGs_getBait(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().getBait(i_idx);
}

inline u8 dComIfGs_getReserve(int i_idx) {
    return g_dComIfG_gameInfo.save.getPlayer().getBagItem().getReserve(i_idx);
}

inline BOOL dComIfGs_isGetItemReserve(int i_No) {
    return g_dComIfG_gameInfo.save.getPlayer().getGetBagItem().isReserve(i_No);
}

inline BOOL dComIfGs_isGetCollectMap(int i_itemNo) {
    return g_dComIfG_gameInfo.save.getPlayer().getMap().isGetMap(i_itemNo - 1);
}

inline u8 dComIfGs_getArrowNum() {
    return g_dComIfG_gameInfo.save.getPlayer().getItemRecord().getArrowNum();
}

inline u8 dComIfGs_getBombNum() {
    return g_dComIfG_gameInfo.save.getPlayer().getItemRecord().getBombNum();
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

inline BOOL dComIfGs_isEventBit(u16 id) {
    return g_dComIfG_gameInfo.save.getEvent().isEventBit(id);
}

inline void dComIfGs_onEventBit(u16 id) {
    g_dComIfG_gameInfo.save.getEvent().onEventBit(id);
}

inline void dComIfGs_setRestartRoomParam(u32 i_param) {
    g_dComIfG_gameInfo.save.getRestart().setRoomParam(i_param);
}

inline s8 dComIfGs_getRestartRoomNo() {
    return g_dComIfG_gameInfo.save.getRestart().getRoomNo();
}

inline s8 dComIfGs_getTurnRestartRoomNo() {
    return g_dComIfG_gameInfo.save.getTurnRestart().getRoomNo();
}

inline void dComIfGs_setStartPoint(s16 i_point) {
    g_dComIfG_gameInfo.save.getRestart().setStartPoint(i_point);
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

BOOL dComIfGs_isStageBossEnemy(int i_stageNo);

inline BOOL dComIfGs_isStageBossEnemy() {
    return g_dComIfG_gameInfo.save.getMemory().getBit().isStageBossEnemy();
}

inline void dComIfGs_onStageLife() {
    g_dComIfG_gameInfo.save.getMemory().getBit().onStageLife();
}

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

inline BOOL dComIfGs_isTriforce(u8 i_no) {
    return g_dComIfG_gameInfo.save.getPlayer().getCollect().isTriforce(i_no);
}

inline BOOL dComIfGs_isSymbol(u8 i_no) {
    return g_dComIfG_gameInfo.save.getPlayer().getCollect().isSymbol(i_no);
}

inline void dComIfGs_onSwitch(int i_no, int i_roomNo) {
    g_dComIfG_gameInfo.save.onSwitch(i_no, i_roomNo);
}

inline void dComIfGs_offSwitch(int i_no, int i_roomNo) {
    g_dComIfG_gameInfo.save.offSwitch(i_no, i_roomNo);
}

inline BOOL dComIfGs_isSwitch(s32 i_no, s32 i_roomNo) {
    return g_dComIfG_gameInfo.save.isSwitch(i_no, i_roomNo);
}

inline void dComIfGs_onItem(int bitNo, int roomNo) {
    g_dComIfG_gameInfo.save.onItem(bitNo, roomNo);
}

inline bool dComIfGs_isItem(int bitNo, int roomNo) {
    return g_dComIfG_gameInfo.save.isItem(bitNo, roomNo);
}

inline void dComIfGs_clearRoomSwitch(int i_zoneNo) {
    g_dComIfG_gameInfo.save.getZone(i_zoneNo).getZoneBit().clearRoomSwitch();
}

inline void dComIfGs_removeZone(int i_zoneNo) {
    g_dComIfG_gameInfo.save.removeZone(i_zoneNo);
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

inline u32 dComIfGs_getRestartRoomParam() {
    return g_dComIfG_gameInfo.save.getRestart().getRoomParam();
}

inline cXyz& dComIfGs_getRestartRoomPos() {
    return g_dComIfG_gameInfo.save.getRestart().getRoomPos();
}

inline s16 dComIfGs_getRestartRoomAngleY() {
    return g_dComIfG_gameInfo.save.getRestart().getRoomAngleY();
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

inline BOOL dComIfGs_isActor(int i_no, int i_roomNo) {
    return g_dComIfG_gameInfo.save.isActor(i_no, i_roomNo);
}

inline void dComIfGs_setTurnRestart(const cXyz& i_pos, s16 i_angle, s8 i_roomNo, u32 i_param) {
    g_dComIfG_gameInfo.save.getTurnRestart().set(i_pos, i_angle, i_roomNo, i_param, i_pos, i_angle, 0);
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

/**
 * === PLAY ===
 */

void dComIfGp_setNextStage(const char* i_stageName, s16 i_point, s8 i_roomNo, s8 i_layer,
                           f32 i_lastSpeed, u32 i_lastMode, int, s8 i_wipe);
dStage_Ship_data* dComIfGp_getShip(int i_roomNo, int param_1);

inline camera_class* dComIfGp_getCamera(int idx) {
    return g_dComIfG_gameInfo.play.getCamera(idx);
}

inline const char* dComIfGp_getStartStageName() {
    return g_dComIfG_gameInfo.play.getStartStageName();
}

inline s8 dComIfGp_getStartStageRoomNo() {
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

inline s32 dComIfGp_roomControl_getTimePass() {
    return g_dComIfG_gameInfo.play.getRoomControl()->GetTimePass();
}

inline s32 dComIfGp_roomControl_getStayNo() {
    return dStage_roomControl_c::getStayNo();
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

inline void dComIfGp_demo_update() {
    g_dComIfG_gameInfo.play.getDemo()->update();
}

inline void dComIfGp_setLkDemoAnmArchive(JKRArchive* i_arc) {
    g_dComIfG_gameInfo.play.setLkDemoAnmArchive(i_arc);
}

inline void dComIfGp_setStatus(u16 status) {
    g_dComIfG_gameInfo.play.setStatus(status);
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

inline daPy_py_c* daPy_getPlayerActorClass() {
    return (daPy_py_c*)dComIfGp_getPlayer(0);
}

inline daPy_lk_c* daPy_getPlayerLinkActorClass() {
    return (daPy_lk_c*)g_dComIfG_gameInfo.play.getPlayerPtr(0);
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

inline void dComIfGp_setItemRupeeCount(int count) {
    g_dComIfG_gameInfo.play.setItemRupeeCount(count);
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
    return g_dComIfG_gameInfo.play.getEvent().onEventFlag(flag);
}

inline void dComIfGp_event_offEventFlag(s16 flag) {
    return g_dComIfG_gameInfo.play.getEvent().offEventFlag(flag);
}

inline void dComIfGp_event_reset() {
    g_dComIfG_gameInfo.play.getEvent().reset();
}

inline u8 dComIfGp_event_getPreItemNo() {
    return g_dComIfG_gameInfo.play.getEvent().getPreItemNo();
}

inline void dComIfGp_event_setItemPartnerId(u32 id) {
    return g_dComIfG_gameInfo.play.getEvent().setPtI_Id(id);
}

inline dEvent_manager_c& dComIfGp_getEventManager() {
    return g_dComIfG_gameInfo.play.getEvtManager();
}

inline u32 dComIfGp_evmng_getEventIdx(char* pName, u8 evNo) {
    return dComIfGp_getEventManager().getEventIdx(pName, evNo);
}

inline int dComIfGp_evmng_getMyStaffId(char* pName, fopAc_ac_c* pActor, s32 param_3) {
    return dComIfGp_getEventManager().getMyStaffId(pName, pActor, param_3);
}

inline int dComIfGp_evmng_getMyActIdx(int staffIdx, const char* const* pActions, int actionCount, int force, int param_5) {
    return dComIfGp_getEventManager().getMyActIdx(staffIdx, pActions, actionCount, force, param_5);
}

inline f32* dComIfGp_evmng_getMyFloatP(int staffIdx, const char* name) {
    return reinterpret_cast<f32*>(dComIfGp_getEventManager().getMySubstanceP(staffIdx, name, 0)); //type 0 is float
}

inline Vec* dComIfGp_evmng_getMyVec3dP(int staffIdx, const char* name) {
    return reinterpret_cast<Vec*>(dComIfGp_getEventManager().getMySubstanceP(staffIdx, name, 1)); //type 1 is vec3f
}

inline u32* dComIfGp_evmng_getMyIntegerP(int staffIdx, const char* name) {
    return reinterpret_cast<u32*>(dComIfGp_getEventManager().getMySubstanceP(staffIdx, name, 3)); //type 3 is int
}

inline char* dComIfGp_evmng_getMyStringP(int staffIdx, const char* name) {
    return reinterpret_cast<char*>(dComIfGp_getEventManager().getMySubstanceP(staffIdx, name, 4)); //type 4 is string
}

inline BOOL dComIfGp_evmng_endCheck(s16 eventID) {
    return dComIfGp_getEventManager().endCheck(eventID);
}

inline BOOL dComIfGp_evmng_ChkPresentEnd() {
    return dComIfGp_getEventManager().ChkPresentEnd();
}

inline void dComIfGp_evmng_CancelPresent() {
    return dComIfGp_getEventManager().CancelPresent();
}

inline BOOL dComIfGp_evmng_getIsAddvance(s32 staffIdx) {
    return dComIfGp_getEventManager().getIsAddvance(staffIdx);
}

inline void dComIfGp_evmng_cutEnd(int staffIdx) {
    return dComIfGp_getEventManager().cutEnd(staffIdx);
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

inline int dComIfG_syncStageRes(const char* name) {
    return g_dComIfG_gameInfo.mResControl.syncStageRes(name);
}

inline int dComIfG_deleteObjectResMain(const char* res) {
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

/**
 * === PARTICLE ===
 */

void set(u8, u16, cXyz const*, csXyz const*, cXyz const*, u8, dPa_levelEcallBack*, s8,
         GXColor const*, GXColor const*, cXyz const*);

inline JPABaseEmitter* dComIfGp_particle_set(u16 particleID, const cXyz* pos, const csXyz* angle,
                                             const cXyz* scale, u8 alpha,
                                             dPa_levelEcallBack* pCallBack, s8 setupInfo,
                                             const GXColor* pPrmColor, const GXColor* pEnvColor,
                                             const cXyz* pScale2D) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->setNormal(particleID, pos, angle, scale, alpha, pCallBack, setupInfo,
                                pPrmColor, pEnvColor, pScale2D);
}

inline JPABaseEmitter* dComIfGp_particle_set(u16 particleID, const cXyz* pos, const csXyz* angle,
                                             const cXyz* scale) {
    return dComIfGp_particle_set(particleID, pos, angle, scale, 0xFF, NULL, -1, NULL, NULL, NULL);
}

inline void dComIfGp_particle_setStripes(u16 particleID, cXyz* pos, csXyz* angle, cXyz* scale, u8 param_4, u16 param_5) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    pParticle->setNormalStripes(particleID, pos, angle, scale, param_4, param_5);
}

inline JPABaseEmitter* dComIfGp_particle_setToon(u16 particleID, const cXyz* pos,
                                                 const csXyz* angle, const cXyz* scale, u8 alpha,
                                                 dPa_levelEcallBack* pCallBack, s8 setupInfo,
                                                 const GXColor* pPrmColor, const GXColor* pEnvColor,
                                                 const cXyz* pScale2D) {
    dPa_control_c* pParticle = g_dComIfG_gameInfo.play.getParticle();
    return pParticle->setToon(particleID, pos, angle, scale, alpha, pCallBack, setupInfo,
                              pPrmColor, pEnvColor, pScale2D);
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

inline void dComIfGp_particle_readScene(u8 particle_no, mDoDvdThd_toMainRam_c** param_1) {
    g_dComIfG_gameInfo.play.getParticle()->readScene(particle_no, param_1);
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

#endif /* D_COM_D_COM_INF_GAME_H */
