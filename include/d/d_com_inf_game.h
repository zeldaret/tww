#ifndef D_COM_D_COM_INF_GAME_H
#define D_COM_D_COM_INF_GAME_H

#include "d/d_save.h"
#include "d/d_bg_s.h"
#include "d/d_cc_s.h"
#include "d/d_stage.h"
#include "d/d_event.h"
#include "d/d_event_manager.h"
#include "d/d_resorce.h"

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

struct dADM {
    /* 0x00 */ int mBlockCount;
    /* 0x04 */ void* mpData;
    /* 0x08 */ u8 mCharTbl[0x90];
    /* 0x98 */ void* vtbl;
};

// setup properly later
struct dAttention_c {
    u8 temp[0x190];
};

struct dVibration_c {
    u8 temp[0x84];
};

struct dDetect_c {
    u8 temp[0x14];
};

struct dDlst_list_c {
    u8 temp[0x16234];
};

class dDlst_window_c {
public:
    /* 0x00 */ f32 mXOrig;
    /* 0x04 */ f32 mYOrig;
    /* 0x08 */ f32 mWidth;
    /* 0x0C */ f32 mHeight;
    /* 0x10 */ f32 mNearZ;
    /* 0x14 */ f32 mFarZ;
    /* 0x18 */ f32 mScissorXOrig;
    /* 0x1C */ f32 mScissorYOrig;
    /* 0x20 */ f32 mScissorWidth;
    /* 0x24 */ f32 mScissorHeight;
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
    /* 0x08 */ u32 field_0x08;
    /* 0x0C */ f32 field_0x0c;
    /* 0x10 */ f32 field_0x10;
};
STATIC_ASSERT(sizeof(dComIfG_camera_info_class) == 0x14);

class dComIfG_play_c {
public:
    /* 0x0000 */ dBgS mBgS;
    /* 0x1404 */ dCcS mCcS;
    /* 0x3DF8 */ dADM mADM;
    /* 0x3E94 */ dStage_startStage_c mCurStage;
    /* 0x3EA0 */ dStage_nextStage_c mNextStage;
    /* 0x3EAE */ u8 field_0x3EAE[0x3EB0 - 0x3EAE];
    /* 0x3EB0 */ dStage_stageDt_c mStageData;
    /* 0x3F34 */ dStage_roomControl_c mRoomCtrl;
    /* 0x3F38 */ dEvt_control_c mEvtCtrl;
    /* 0x402C */ dEvent_manager_c mEventMgr;
    /* 0x4568 */ dAttention_c mAttention;
    /* 0x46F8 */ u8 field_0x46F8[0x4700 - 0x46F8];
    /* 0x4700 */ dVibration_c mVibration;
    /* 0x4784 */ dDetect_c mDetect;
    /* 0x4798 */ JKRArchive* mpMsgArchive;
    /* 0x479C */ JKRArchive* mpDmsgArchive;
    /* 0x47A0 */ JKRArchive* mpTmsgArchive;
    /* 0x47A4 */ JKRArchive* mpMenuArchive;
    /* 0x47A8 */ JKRArchive* mpFontArchive;
    /* 0x47AC */ u8 field_0x47AC[0x47B0 - 0x47AC];
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
    /* 0x47F8 */ JKRArchive* mpEnglishTextArchive;
    /* 0x47FC */ JKRArchive* mpHyruleTextArchive;
    /* 0x4800 */ u8 field_0x4800[0x4824 - 0x4800];
    /* 0x4824 */ dPa_control_c* mParticle;
    /* 0x4828 */ dDemo_manager_c* mDemo;
    /* 0x482C */ dMagma_packet_c* mpMagmaPacket;
    /* 0x4830 */ dGrass_packet_c* mpGrassPacket;
    /* 0x4834 */ dTree_packet_c* mpTreePacket;
    /* 0x4838 */ Packet_c* mpWoodPacket;
    /* 0x483C */ dFlower_packet_c* mpFlowerPacket;
    /* 0x4840 */ u8 mLkDArcIdx;
    /* 0x4841 */ u8 field_0x4841;
    /* 0x4842 */ short mVrboxFlags;
    /* 0x4844 */ dDlst_window_c mDlstWindow[1];
    /* 0x486C */ u8 mCurCameraInfo;
    /* 0x486D */ u8 field_0x486D[0x4870 - 0x486D];
    /* 0x4870 */ dComIfG_camera_info_class mCameraInfo[1];
    /* 0x48A4 */ daPy_py_c* mpCurPlayerActor[1];
    /* 0x48A8 */ u8 mCurCamera;
    /* 0x48A9 */ u8 field_0x48A9[0x48AC - 0x48A9];
    /* 0x48AC */ daPy_lk_c* mpLinkActor;
    /* 0x48B0 */ daPy_npc_c* mpPlayerPartnerActor;
    /* 0x48B4 */ daShip_c* mpShip;
    /* 0x48B8 */ f32 field_0x48b8;
    /* 0x48BC */ int mItemLifeCount;
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
    /* 0x4918 */ u16 mCurrAuctionItemNameMsgID;
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
    /* 0x4A40 */ dTimer_c* mpRestartTimer;
    /* 0x4A44 */ int field_0x4a44;
    /* 0x4A48 */ int field_0x4a48;
    /* 0x4A4C */ int field_0x4a4c;
    /* 0x4A50 */ u16 field_0x4a50;
    /* 0x4A52 */ u8 field_0x4A52[0x4A54 - 0x4A52];
    /* 0x4A54 */ dDlst_window_c* field_0x4a54;
    /* 0x4A58 */ camera_class* field_0x4a58;
    /* 0x4A5C */ dDlst_window_c* field_0x4a5c;
    /* 0x4A60 */ J2DOrthoGraph* mp2DOrthoGraph;
    /* 0x4A64 */ u8 field_0x4A64[0x4A66 - 0x4A64];
    /* 0x4A66 */ u8 mLastSeaRoom;
    /* 0x4A67 */ u8 field_0x4A67[0x4A68 - 0x4A67];
    /* 0x4A68 */ cXyz mIkadaLinkPos;
    /* 0x4A74 */ void* mpItemTableArchive;
    /* 0x4A78 */ void* mpFmapDataArchive;
};

class dComIfG_inf_c {
public:
    /* 0x00000 */ dSv_info_c info;
    /* 0x012A0 */ dComIfG_play_c play;
    /* 0x05D1C */ dDlst_list_c drawlist;
    /* 0x1BF50 */ u8 field_0x1BF50[0x1BFC0 - 0x1BF50];
    /* 0x1BFC0 */ dRes_control_c res_control;
    /* 0x1D1C0 */ u8 field_0x1d1c0;
    /* 0x1D1C1 */ u8 field_0x1d1c1;
};

extern dComIfG_inf_c g_dComIfG_gameInfo;

inline u8 dComIfGs_getSelectEquip(int param_0) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getSelectEquip(param_0);
}

inline u8 dComIfGs_getItem(int param_0) {
    return g_dComIfG_gameInfo.info.getPlayer().getItem().getItem(param_0);
}

#endif /* D_COM_D_COM_INF_GAME_H */
