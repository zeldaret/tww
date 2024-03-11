#ifndef D_D_STAGE_H
#define D_D_STAGE_H

#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_sxyz.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_kankyo.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "global.h"
#include "f_op/f_op_actor_mng.h"

class JKRExpHeap;

void dStage_SetErrorRoom();
void dStage_SetErrorStage();

enum StageType {
    /* 0x00 */ dStageType_OUTDOORS_e,
    /* 0x01 */ dStageType_DUNGEON_e,
    /* 0x02 */ dStageType_MISC_e, // Mostly interior rooms but also some exceptions
    /* 0x03 */ dStageType_BOSS_e,
    /* 0x04 */ dStageType_SUBDUNGEON_e, // Name based on the debug map select entry サブダンジョン
    /* 0x05 */ dStageType_FF1_e,
    /* 0x06 */ dStageType_MINIBOSS_e,
    /* 0x07 */ dStageType_SEA_e,
    /* 0x08 */ dStageType_UNKNOWN_8_e,
};

class stage_vrbox_info_class {
public:
    /* 0x00 */ u32 field_0x00;
    /* 0x04 */ u32 field_0x04;
    /* 0x08 */ u32 field_0x08;
    /* 0x0C */ u32 field_0x0c;
    /* 0x10 */ GXColor mKumoColor;
    /* 0x14 */ GXColor mKumoCenterColor;
    /* 0x18 */ color_RGB_class mSkyColor;
    /* 0x1B */ color_RGB_class mUsoUmiColor;
    /* 0x1E */ color_RGB_class mKasumiMaeColor;
};

class stage_tresure_data_class {
public:
    /* 0x00 */ char mName[8];
    /* 0x08 */ u32 mParameter;
    /* 0x0C */ cXyz mSpawnPos;
    /* 0x18 */ csXyz mAngle;
    /* 0x1E */ u16 mSetId;

    stage_tresure_data_class() {}
    ~stage_tresure_data_class() {}
};  // Size: 0x20

class stage_tresure_class {
public:
    /* 0x00 */ int num;
    /* 0x04 */ stage_tresure_data_class* m_entries;
};

struct stage_stag_info_class {
    /* 0x00 */ f32 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ u8 mCameraType;
    /* 0x09 */ u8 field_0x09;
    /* 0x0A */ u16 field_0x0a;
    /* 0x0C */ u32 field_0x0c;
    /* 0x10 */ u32 field_0x10;
    /* 0x14 */ u32 field_0x14;
    /* 0x18 */ u32 field_0x18;
    /* 0x1C */ u32 field_0x1c;
};

struct stage_scls_info_class {
    /* 0x0 */ char mStage[8];
    /* 0x8 */ u8 mStart;
    /* 0x9 */ u8 mRoom;
    /* 0xA */ u8 mWipe;
    /* 0xB */ u8 field_0xb;
};

struct stage_scls_info_dummy_class {
    /* 0x00 */ int num;
    /* 0x04 */ stage_scls_info_class* m_entries;
};

class stage_lightvec_info_class {
public:
    /* 0x00 */ Vec mPos;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ u8 field_0x18[0x1B - 0x18];
    /* 0x1B */ u8 mFluctuation;
};

class stage_pselect_info_class {
public:
    /* 0x0 */ u8 mPalIdx[8];
    /* 0x8 */ f32 mChangeRate;
};

struct stage_plight_info_class {
    /* 0x00 */ Vec mPos;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ u8 mColorR;
    /* 0x19 */ u8 mColorG;
    /* 0x1A */ u8 mColorB;
    /* 0x1B */ u8 mFluctuation;
};

class stage_palet_info_class {
public:
    /* 0x00 */ color_RGB_class mActor_C0;
    /* 0x03 */ color_RGB_class mActor_K0;
    /* 0x06 */ color_RGB_class mBG0_C0;
    /* 0x09 */ color_RGB_class mBG0_K0;
    /* 0x0C */ color_RGB_class mBG1_C0;
    /* 0x0F */ color_RGB_class mBG1_K0;
    /* 0x12 */ color_RGB_class mBG2_C0;
    /* 0x15 */ color_RGB_class mBG2_K0;
    /* 0x18 */ color_RGB_class mBG3_C0;
    /* 0x1B */ color_RGB_class mBG3_K0;
    /* 0x1E */ color_RGB_class mFog;
    /* 0x21 */ u8 mVirtIdx;
    /* 0x24 */ f32 mFogStartZ;
    /* 0x28 */ f32 mFogEndZ;
};

class stage_map_info_class {
public:
    /* 0x00 */ u8 field_0x00[0x18 - 0x00];
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ u8 field_0x28[0x35 - 0x28];
    /* 0x35 */ u8 field_0x35;
    /* 0x36 */ u8 mOceanXZ;
    /* 0x37 */ u8 field_0x37[0x38 - 0x37];
};

struct stage_map_info_dummy_class {
    int num;
    stage_map_info_class* m_entries;
};

class stage_envr_info_class {
public:
    /* 0x0 */ u8 mPselIdx[8];
};

struct stage_camera2_data_class {
    /* 0x00 */ int field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xc;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u16 field_0x14;
    /* 0x16 */ u16 field_0x16;
};  // Size: 0x18

struct stage_camera_class {
    /* 0x0 */ int num;
    /* 0x4 */ stage_camera2_data_class* m_entries;
};

struct stage_arrow_data_class {
    /* 0x00 */ cXyz mPosition;
    /* 0x0C */ csXyz mAngle;
};  // Size: 0x14

struct stage_arrow_class {
    /* 0x00 */ int num;
    /* 0x04 */ stage_arrow_data_class* m_entries;
};

class stage_actor_data_class {
public:
    /* 0x00 */ char mName[8];
    /* 0x08 */ u32 mParameter;
    /* 0x0C */ cXyz mSpawnPos;
    /* 0x18 */ csXyz mAngle;
    /* 0x1E */ u16 mSetId;
};  // Size: 0x20

class stage_actor_class {
public:
    /* 0x0 */ int num;
    /* 0x4 */ stage_actor_data_class* m_entries;
};

class stage_tgsc_data_class : public stage_actor_data_class {
public:
    fopAcM_prmScale_class mScale;

    stage_tgsc_data_class() {}
    ~stage_tgsc_data_class() {}
};  // Size: 0x24

class stage_tgsc_class {
public:
    /* 0x00 */ int num;
    /* 0x04 */ stage_tgsc_data_class* m_entries;
};

struct roomRead_data_class {
    /* 0x0 */ u8 mRoomCount;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 field_0x2;
    /* 0x4 */ u8* mpRooms;
};

struct roomRead_class {
    /* 0x0 */ int num;
    /* 0x4 */ roomRead_data_class** m_entries;
};

struct dStage_MemoryMap_c {
    /* 0x0 */ int num;
    /* 0x4 */ u32* m_entries;
};

struct dPath;
struct dStage_dPath_c {
    /* 0x0 */ int num;
    /* 0x4 */ dPath* m_path;
};

struct dStage_Mult_info {
    /* 0x0 */ f32 mTransX;
    /* 0x4 */ f32 mTransY;
    /* 0x8 */ s16 mAngle;
    /* 0xA */ u8 mRoomNo;
    /* 0xB */ u8 mWaveMax;
};  // Size: 0xC

class dStage_Multi_c {
public:
    /* 0x0 */ int num;
    /* 0x4 */ dStage_Mult_info* m_entries;
};

struct stage_sound_data {
    /* 0x00 */ char field_0x0[8];
    /* 0x08 */ Vec field_0x8;
    /* 0x14 */ u8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
    /* 0x18 */ u8 field_0x18;
    /* 0x19 */ u8 field_0x19;
    /* 0x1A */ u8 field_0x1a;
};  // Size: 0x1C

struct dStage_SoundInfo_c {
    /* 0x0 */ int num;
    /* 0x4 */ stage_sound_data* m_entries;
};

class dStage_FileList_dt_c {
public:
    /* 0x0 */ u32 mParam;
    /* 0x4 */ f32 mSeaLevel;
};

struct dStage_dPnt_c {
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
    /* 0x4 */ cXyz m_position;
};  // Size: 0x10

struct dStage_FloorInfo_c {};

struct dStage_Lbnk_c {
    /* 0x00 */ u32 m_num;
    /* 0x04 */ u8 * m_bank;
};

struct dStage_MemoryConfig_data {
    /* 0x0 */ u8 m_roomNo;
    /* 0x1 */ u8 m_blockID;
};  // Size: 0x2

struct dStage_MemoryConfig_c {
    /* 0x0 */ int num;
    /* 0x4 */ dStage_MemoryConfig_data* m_entries;
};

struct dStage_DMap_c {};

struct dStage_Event_dt_c {
    /* 0x00 */ u8 field_0x0;
    /* 0x04 */ char mName[15];
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
}; // Size: 0x18

struct dStage_EventInfo_c {
    /* 0x00 */ s32 num;
    /* 0x04 */ dStage_Event_dt_c* events;
}; // Size: 0x08

struct dStage_Ship_data {
    /* 0x0 */ cXyz m_pos;
    /* 0xC */ s16 m_angle;
    /* 0xE */ u8 field_0xe;
    /* 0xF */ u8 field_0xf;
};

class dStage_Ship_c {
public:
    /* 0x0 */ int num;
    /* 0x4 */ dStage_Ship_data* m_entries;
};

struct FuncTable;

class dStage_dt_c {
public:
    dStage_dt_c() {}
    ~dStage_dt_c() {}

    /* vt[ 2] */ virtual void init() = 0;
    /* vt[ 3] */ virtual int getRoomNo() const = 0;
    /* vt[ 4] */ virtual void setCamera(stage_camera_class*) = 0;
    /* vt[ 5] */ virtual stage_camera_class* getCamera() const = 0;
    /* vt[ 6] */ virtual void setArrow(stage_arrow_class*) = 0;
    /* vt[ 7] */ virtual stage_arrow_class* getArrow() const = 0;
    /* vt[ 8] */ virtual void setPlayer(stage_actor_class*) = 0;
    /* vt[ 9] */ virtual stage_actor_class* getPlayer() const = 0;
    /* vt[10] */ virtual void setPlayerNum(u16) = 0;
    /* vt[11] */ virtual u16 getPlayerNum() const = 0;
    /* vt[12] */ virtual void setRoom(roomRead_class*) = 0;
    /* vt[13] */ virtual roomRead_class* getRoom() const = 0;
    /* vt[14] */ virtual void setMapInfo(stage_map_info_class*) = 0;
    /* vt[15] */ virtual stage_map_info_class* getMapInfo() const = 0;
    /* vt[16] */ virtual stage_map_info_class* getMapInfo2(int) const = 0;
    /* vt[17] */ virtual void setMapInfoBase(stage_map_info_dummy_class*) = 0;
    /* vt[18] */ virtual stage_map_info_dummy_class* getMapInfoBase() const = 0;
    /* vt[19] */ virtual void setPaletInfo(stage_palet_info_class*) = 0;
    /* vt[20] */ virtual stage_palet_info_class* getPaletInfo() const = 0;
    /* vt[21] */ virtual void setPselectInfo(stage_pselect_info_class*) = 0;
    /* vt[22] */ virtual stage_pselect_info_class* getPselectInfo() const = 0;
    /* vt[23] */ virtual void setEnvrInfo(stage_envr_info_class*) = 0;
    /* vt[24] */ virtual stage_envr_info_class* getEnvrInfo() const = 0;
    /* vt[25] */ virtual void setVrboxInfo(stage_vrbox_info_class*) = 0;
    /* vt[26] */ virtual stage_vrbox_info_class* getVrboxInfo() const = 0;
    /* vt[27] */ virtual void setPlightInfo(stage_plight_info_class*) = 0;
    /* vt[28] */ virtual stage_plight_info_class* getPlightInfo() const = 0;
    /* vt[29] */ virtual void setPaletNumInfo(int) = 0;
    /* vt[30] */ virtual int getPaletNumInfo() const = 0;
    /* vt[31] */ virtual void setPselectNumInfo(int) = 0;
    /* vt[32] */ virtual int getPselectNumInfo() const = 0;
    /* vt[33] */ virtual void setEnvrNumInfo(int) = 0;
    /* vt[34] */ virtual int getEnvrNumInfo() const = 0;
    /* vt[35] */ virtual void setVrboxNumInfo(int) = 0;
    /* vt[36] */ virtual int getVrboxNumInfo() const = 0;
    /* vt[37] */ virtual void setPlightNumInfo(int) = 0;
    /* vt[38] */ virtual int getPlightNumInfo() const = 0;
    /* vt[39] */ virtual void setLightVecInfo(stage_lightvec_info_class*) = 0;
    /* vt[40] */ virtual stage_lightvec_info_class* getLightVecInfo() const = 0;
    /* vt[41] */ virtual void setLightVecInfoNum(int) = 0;
    /* vt[42] */ virtual int getLightVecInfoNum() const = 0;
    /* vt[43] */ virtual void setStagInfo(stage_stag_info_class*) = 0;
    /* vt[44] */ virtual stage_stag_info_class* getStagInfo() const = 0;
    /* vt[45] */ virtual void setSclsInfo(stage_scls_info_dummy_class*) = 0;
    /* vt[46] */ virtual stage_scls_info_dummy_class* getSclsInfo() const = 0;
    /* vt[47] */ virtual void setPntInfo(dStage_dPnt_c*) = 0;
    /* vt[48] */ virtual dStage_dPnt_c* getPntInf() const = 0;
    /* vt[49] */ virtual void setPathInfo(dStage_dPath_c*) = 0;
    /* vt[50] */ virtual dStage_dPath_c* getPathInf() const = 0;
    /* vt[51] */ virtual void setPnt2Info(dStage_dPnt_c*) = 0;
    /* vt[52] */ virtual dStage_dPnt_c* getPnt2Inf() const = 0;
    /* vt[53] */ virtual void setPath2Info(dStage_dPath_c*) = 0;
    /* vt[54] */ virtual dStage_dPath_c* getPath2Inf() const = 0;
    /* vt[55] */ virtual void setSoundInfo(dStage_SoundInfo_c*) = 0;
    /* vt[56] */ virtual dStage_SoundInfo_c* getSoundInf() const = 0;
    /* vt[57] */ virtual void setEventInfo(dStage_EventInfo_c*) = 0;
    /* vt[58] */ virtual dStage_EventInfo_c* getEventInfo() const = 0;
    /* vt[59] */ virtual void setFileListInfo(dStage_FileList_dt_c*) = 0;
    /* vt[60] */ virtual dStage_FileList_dt_c* getFileListInfo() const = 0;
    /* vt[61] */ virtual void setFloorInfo(dStage_FloorInfo_c*) = 0;
    /* vt[62] */ virtual dStage_FloorInfo_c* getFloorInfo() const = 0;
    /* vt[63] */ virtual void setMemoryConfig(dStage_MemoryConfig_c*) = 0;
    /* vt[64] */ virtual dStage_MemoryConfig_c* getMemoryConfig() const = 0;
    /* vt[65] */ virtual void setMemoryMap(dStage_MemoryMap_c*) = 0;
    /* vt[66] */ virtual dStage_MemoryMap_c* getMemoryMap() const = 0;
    /* vt[67] */ virtual void setShip(dStage_Ship_c*) = 0;
    /* vt[68] */ virtual dStage_Ship_c* getShip() const = 0;
    /* vt[69] */ virtual void setMulti(dStage_Multi_c*) = 0;
    /* vt[70] */ virtual dStage_Multi_c* getMulti() const = 0;
    /* vt[71] */ virtual void setLbnk(dStage_Lbnk_c*) = 0;
    /* vt[72] */ virtual dStage_Lbnk_c* getLbnk() const = 0;
    /* vt[73] */ virtual void setTresure(stage_tresure_class*) = 0;
    /* vt[74] */ virtual stage_tresure_class* getTresure() const = 0;
    /* vt[75] */ virtual void setDMap(dStage_DMap_c*) = 0;
    /* vt[76] */ virtual dStage_DMap_c* getDMap() const = 0;
    /* vt[77] */ virtual void setDrTg(stage_tgsc_class*) = 0;
    /* vt[78] */ virtual stage_tgsc_class* getDrTg() const = 0;
};

class dStage_stageDt_c : public dStage_dt_c {
public:
    dStage_stageDt_c() {}

    /* vt[ 2] */ virtual void init();
    /* vt[ 3] */ virtual int getRoomNo() const { return -1; }
    /* vt[ 4] */ virtual void setCamera(stage_camera_class* i_camera) { mpCamera = i_camera; }
    /* vt[ 5] */ virtual stage_camera_class* getCamera() const { return mpCamera; }
    /* vt[ 6] */ virtual void setArrow(stage_arrow_class* i_arrow) { mpArrow = i_arrow; }
    /* vt[ 7] */ virtual stage_arrow_class* getArrow() const { return mpArrow; }
    /* vt[ 8] */ virtual void setPlayer(stage_actor_class* i_player) { mpPlayer = i_player; }
    /* vt[ 9] */ virtual stage_actor_class* getPlayer() const { return mpPlayer; }
    /* vt[10] */ virtual void setPlayerNum(u16 i_playerNum) { mPlayerNum = i_playerNum; }
    /* vt[11] */ virtual u16 getPlayerNum() const { return mPlayerNum; }
    /* vt[12] */ virtual void setRoom(roomRead_class* i_room) { mpRoomReads = i_room; }
    /* vt[13] */ virtual roomRead_class* getRoom() const { return mpRoomReads; }
    /* vt[14] */ virtual void setMapInfo(stage_map_info_class* i_mapInfo) { mpMapInfo = i_mapInfo; }
    /* vt[15] */ virtual stage_map_info_class* getMapInfo() const { return mpMapInfo; }
    /* vt[16] */ virtual stage_map_info_class* getMapInfo2(int) const;
    /* vt[17] */ virtual void setMapInfoBase(stage_map_info_dummy_class* i_mapInfoBase) { mpMapInfoBase = i_mapInfoBase; }
    /* vt[18] */ virtual stage_map_info_dummy_class* getMapInfoBase() const;
    /* vt[19] */ virtual void setPaletInfo(stage_palet_info_class* i_paletInfo) { mpPaletInfo = i_paletInfo; }
    /* vt[20] */ virtual stage_palet_info_class* getPaletInfo() const { return mpPaletInfo; }
    /* vt[21] */ virtual void setPselectInfo(stage_pselect_info_class* i_pselectInfo) { mpPselectInfo = i_pselectInfo; }
    /* vt[22] */ virtual stage_pselect_info_class* getPselectInfo() const { return mpPselectInfo; }
    /* vt[23] */ virtual void setEnvrInfo(stage_envr_info_class* i_envrInfo) { mpEnvrInfo = i_envrInfo; }
    /* vt[24] */ virtual stage_envr_info_class* getEnvrInfo() const { return mpEnvrInfo; }
    /* vt[25] */ virtual void setVrboxInfo(stage_vrbox_info_class* i_vrboxInfo) { mpVrboxInfo = i_vrboxInfo; }
    /* vt[26] */ virtual stage_vrbox_info_class* getVrboxInfo() const { return mpVrboxInfo; }
    /* vt[27] */ virtual void setPlightInfo(stage_plight_info_class* i_plightInfo) { mpPlightInfo = i_plightInfo; }
    /* vt[28] */ virtual stage_plight_info_class* getPlightInfo() const { return mpPlightInfo; }
    /* vt[29] */ virtual void setPaletNumInfo(int i_paletNum) { mPaletInfoNum = i_paletNum; }
    /* vt[30] */ virtual int getPaletNumInfo() const { return mPaletInfoNum; }
    /* vt[31] */ virtual void setPselectNumInfo(int i_pselectNum) { mPselectInfoNum = i_pselectNum; }
    /* vt[32] */ virtual int getPselectNumInfo() const { return mPselectInfoNum; }
    /* vt[33] */ virtual void setEnvrNumInfo(int i_envrNum) { mEnvrInfoNum = i_envrNum; }
    /* vt[34] */ virtual int getEnvrNumInfo() const { return mEnvrInfoNum; }
    /* vt[35] */ virtual void setVrboxNumInfo(int i_vrboxNum) { mVrboxInfoNum = i_vrboxNum; }
    /* vt[36] */ virtual int getVrboxNumInfo() const { return mVrboxInfoNum; }
    /* vt[39] */ virtual void setLightVecInfo(stage_lightvec_info_class*) {
        dStage_SetErrorStage();
        OSReport("stage non LightVec data !!\n");
        JUT_ASSERT(2380, 0);
    }
    /* vt[40] */ virtual stage_lightvec_info_class* getLightVecInfo() const {
        OSReport("stage non LightVec data !!\n");
        JUT_ASSERT(2384, 0);
        return NULL;
    }
    /* vt[41] */ virtual void setLightVecInfoNum(int) {
        dStage_SetErrorStage();
        OSReport("stage non LightVecNum data !!\n");
        JUT_ASSERT(2391, 0);
    }
    /* vt[42] */ virtual int getLightVecInfoNum() const {
        OSReport("stage non LightVecNum data !!\n");
        JUT_ASSERT(2395, 0);
        return 0;
    }
    /* vt[37] */ virtual void setPlightNumInfo(int i_plightNum) { mPlightInfoNum = i_plightNum; }
    /* vt[38] */ virtual int getPlightNumInfo() const { return mPlightInfoNum; }
    /* vt[43] */ virtual void setStagInfo(stage_stag_info_class* i_stag) { mpStagInfo = i_stag; }
    /* vt[44] */ virtual stage_stag_info_class* getStagInfo() const { return mpStagInfo; }
    /* vt[45] */ virtual void setSclsInfo(stage_scls_info_dummy_class* i_scls) { mpScls = i_scls; }
    /* vt[46] */ virtual stage_scls_info_dummy_class* getSclsInfo() const { return mpScls; }
    /* vt[47] */ virtual void setPntInfo(dStage_dPnt_c* i_pnt) { mpPnt = i_pnt; }
    /* vt[48] */ virtual dStage_dPnt_c* getPntInf() const { return mpPnt; }
    /* vt[49] */ virtual void setPathInfo(dStage_dPath_c* i_path) { mpPath = i_path; }
    /* vt[50] */ virtual dStage_dPath_c* getPathInf() const { return mpPath; }
    /* vt[51] */ virtual void setPnt2Info(dStage_dPnt_c* i_pnt) { mpPnt2 = i_pnt; }
    /* vt[52] */ virtual dStage_dPnt_c* getPnt2Inf() const { return mpPnt2; }
    /* vt[53] */ virtual void setPath2Info(dStage_dPath_c* i_path) { mpPath2 = i_path; }
    /* vt[54] */ virtual dStage_dPath_c* getPath2Inf() const { return mpPath2; }
    /* vt[55] */ virtual void setSoundInfo(dStage_SoundInfo_c* i_soundInfo) { mpSoundInfo = i_soundInfo; }
    /* vt[56] */ virtual dStage_SoundInfo_c* getSoundInf() const { return mpSoundInfo; }
    /* vt[57] */ virtual void setEventInfo(dStage_EventInfo_c* i_eventInfo) { mpEventInfo = i_eventInfo; }
    /* vt[58] */ virtual dStage_EventInfo_c* getEventInfo() const { return mpEventInfo; }
    /* vt[59] */ virtual void setFileListInfo(dStage_FileList_dt_c*) {
        dStage_SetErrorStage();
        OSReport("stage non filelist data!\n");
        JUT_ASSERT(2490, 0);
    }
    /* vt[60] */ virtual dStage_FileList_dt_c* getFileListInfo() const {
        OSReport("stage non filelist data!\n");
        JUT_ASSERT(2494, 0);
        return NULL;
    }
    /* vt[61] */ virtual void setFloorInfo(dStage_FloorInfo_c* i_floorInfo) { mpFloorInfo = i_floorInfo; }
    /* vt[62] */ virtual dStage_FloorInfo_c* getFloorInfo() const { return mpFloorInfo; }
    /* vt[63] */ virtual void setMemoryConfig(dStage_MemoryConfig_c* i_config) { mpMemoryConfig = i_config; }
    /* vt[64] */ virtual dStage_MemoryConfig_c* getMemoryConfig() const { return mpMemoryConfig; }
    /* vt[65] */ virtual void setMemoryMap(dStage_MemoryMap_c* i_map) { mpMemoryMap = i_map; }
    /* vt[66] */ virtual dStage_MemoryMap_c* getMemoryMap() const { return mpMemoryMap; }
    /* vt[67] */ virtual void setShip(dStage_Ship_c*) {
        dStage_SetErrorStage();
        OSReport("stage non SHIP data!\n");
        JUT_ASSERT(2561, 0);
    }
    /* vt[68] */ virtual dStage_Ship_c* getShip() const {
        OSReport("stage non SHIP data!\n");
        JUT_ASSERT(2565, 0);
        return NULL;
    }
    /* vt[69] */ virtual void setMulti(dStage_Multi_c* i_multi) { mpMulti = i_multi; }
    /* vt[70] */ virtual dStage_Multi_c* getMulti() const { return mpMulti; }
    /* vt[71] */ virtual void setLbnk(dStage_Lbnk_c*) {
        dStage_SetErrorStage();
        OSReport("stage non Lbnk data!\n");
        JUT_ASSERT(2590, 0);
    }
    /* vt[72] */ virtual dStage_Lbnk_c* getLbnk() const {
        OSReport("stage non Lbnk data!\n");
        JUT_ASSERT(2597, 0);
        return NULL;
    }
    /* vt[73] */ virtual void setTresure(stage_tresure_class* i_tresure) { mpTresure = i_tresure; }
    /* vt[74] */ virtual stage_tresure_class* getTresure() const { return mpTresure; }
    /* vt[75] */ virtual void setDMap(dStage_DMap_c* i_dmap) { mpDMap = i_dmap; }
    /* vt[76] */ virtual dStage_DMap_c* getDMap() const { return mpDMap; }
    /* vt[77] */ virtual void setDrTg(stage_tgsc_class* i_drtg) { mpDrTg = i_drtg; }
    /* vt[78] */ virtual stage_tgsc_class* getDrTg() const { return mpDrTg; }

public:
    /* 0x04 */ stage_camera_class* mpCamera;
    /* 0x08 */ stage_arrow_class* mpArrow;
    /* 0x0C */ stage_actor_class* mpPlayer;
    /* 0x10 */ roomRead_class* mpRoomReads;
    /* 0x14 */ stage_map_info_class* mpMapInfo;
    /* 0x18 */ stage_map_info_dummy_class* mpMapInfoBase;
    /* 0x1C */ stage_palet_info_class* mpPaletInfo;
    /* 0x20 */ stage_pselect_info_class* mpPselectInfo;
    /* 0x24 */ stage_envr_info_class* mpEnvrInfo;
    /* 0x28 */ stage_vrbox_info_class* mpVrboxInfo;
    /* 0x2C */ stage_plight_info_class* mpPlightInfo;
    /* 0x30 */ int mPaletInfoNum;
    /* 0x34 */ int mPselectInfoNum;
    /* 0x38 */ int mEnvrInfoNum;
    /* 0x3C */ int mVrboxInfoNum;
    /* 0x40 */ int mPlightInfoNum;
    /* 0x44 */ u16 mPlayerNum;
    /* 0x48 */ stage_stag_info_class* mpStagInfo;
    /* 0x4C */ stage_scls_info_dummy_class* mpScls;
    /* 0x50 */ dStage_dPnt_c* mpPnt;
    /* 0x54 */ dStage_dPath_c* mpPath;
    /* 0x58 */ dStage_dPnt_c* mpPnt2;
    /* 0x5C */ dStage_dPath_c* mpPath2;
    /* 0x60 */ dStage_SoundInfo_c* mpSoundInfo;
    /* 0x64 */ dStage_EventInfo_c* mpEventInfo;
    /* 0x68 */ dStage_FloorInfo_c* mpFloorInfo;
    /* 0x6C */ dStage_MemoryConfig_c* mpMemoryConfig;
    /* 0x70 */ dStage_MemoryMap_c* mpMemoryMap;
    /* 0x74 */ dStage_Multi_c* mpMulti;
    /* 0x78 */ stage_tresure_class* mpTresure;
    /* 0x7C */ dStage_DMap_c* mpDMap;
    /* 0x80 */ stage_tgsc_class* mpDrTg;
};

class dStage_roomDt_c : public dStage_dt_c {
public:
    /* vt[ 2] */ virtual void init();
    /* vt[ 3] */ virtual int getRoomNo() const { return mRoomNo; }
    /* vt[ 4] */ virtual void setCamera(stage_camera_class* i_camera) { mpCamera = i_camera; }
    /* vt[ 5] */ virtual stage_camera_class* getCamera() const { return mpCamera; }
    /* vt[ 6] */ virtual void setArrow(stage_arrow_class* i_arrow) { mpArrow = i_arrow; }
    /* vt[ 7] */ virtual stage_arrow_class* getArrow() const { return mpArrow; }
    /* vt[ 8] */ virtual void setPlayer(stage_actor_class* i_player) { mpPlayer = i_player; }
    /* vt[ 9] */ virtual stage_actor_class* getPlayer() const { return mpPlayer; }
    /* vt[10] */ virtual void setPlayerNum(u16 i_playerNum) { mPlayerNum = i_playerNum; }
    /* vt[11] */ virtual u16 getPlayerNum() const { return mPlayerNum; }
    /* vt[12] */ virtual void setRoom(roomRead_class*) {
        dStage_SetErrorRoom();
        OSReport("Room non room data !!\n");
        JUT_ASSERT(1613, 0);
    }
    /* vt[13] */ virtual roomRead_class* getRoom() const {
        OSReport("Room non room data !!\n");
        JUT_ASSERT(1618, 0);
        return NULL;
    }
    /* vt[14] */ virtual void setMapInfo(stage_map_info_class* i_mapInfo) { mpMapInfo = i_mapInfo; }
    /* vt[15] */ virtual stage_map_info_class* getMapInfo() const { return mpMapInfo; }
    /* vt[16] */ virtual stage_map_info_class* getMapInfo2(int) const;
    /* vt[17] */ virtual void setMapInfoBase(stage_map_info_dummy_class* i_mapInfoBase) { mpMapInfoBase = i_mapInfoBase; }
    /* vt[18] */ virtual stage_map_info_dummy_class* getMapInfoBase() const;
    /* vt[19] */ virtual void setPaletInfo(stage_palet_info_class*) {
        dStage_SetErrorRoom();
        OSReport("Room non palet data !!\n");
        JUT_ASSERT(1644, 0);
    }
    /* vt[20] */ virtual stage_palet_info_class* getPaletInfo() const {
        OSReport("Room non palet data !!\n");
        JUT_ASSERT(1648, 0);
        return NULL;
    }
    /* vt[21] */ virtual void setPselectInfo(stage_pselect_info_class*) {
        dStage_SetErrorRoom();
        OSReport("Room non pselect data !!\n");
        JUT_ASSERT(1655, 0);
    }
    /* vt[22] */ virtual stage_pselect_info_class* getPselectInfo() const {
        OSReport("Room non pselect data !!\n");
        JUT_ASSERT(1659, 0);
        return NULL;
    }
    /* vt[23] */ virtual void setEnvrInfo(stage_envr_info_class*) {
        dStage_SetErrorRoom();
        OSReport("Room non envr data !!\n");
        JUT_ASSERT(1666, 0);
    }
    /* vt[24] */ virtual stage_envr_info_class* getEnvrInfo() const {
        OSReport("Room non envr data !!\n");
        JUT_ASSERT(1670, 0);
        return NULL;
    }
    /* vt[25] */ virtual void setVrboxInfo(stage_vrbox_info_class* i_vrbox) { mpVrbox = i_vrbox; }
    /* vt[26] */ virtual stage_vrbox_info_class* getVrboxInfo() const { return mpVrbox; }
    /* vt[27] */ virtual void setPlightInfo(stage_plight_info_class*) {
        dStage_SetErrorRoom();
        OSReport("Room non plight data !!\n");
        JUT_ASSERT(1686, 0);
    }
    /* vt[28] */ virtual stage_plight_info_class* getPlightInfo() const {
        OSReport("Room non plight data !!\n");
        JUT_ASSERT(1690, 0);
        return NULL;
    }
    /* vt[29] */ virtual void setPaletNumInfo(int) {
        dStage_SetErrorRoom();
        OSReport("Room non palet num data !!\n");
        JUT_ASSERT(1700, 0);
    }
    /* vt[30] */ virtual int getPaletNumInfo() const {
        OSReport("Room non palet num data !!\n");
        JUT_ASSERT(1704, 0);
        return 0;
    }
    /* vt[31] */ virtual void setPselectNumInfo(int) {
        dStage_SetErrorRoom();
        OSReport("Room non pselect num data !!\n");
        JUT_ASSERT(1711, 0);
    }
    /* vt[32] */ virtual int getPselectNumInfo() const {
        OSReport("Room non pselect num data !!\n");
        JUT_ASSERT(1715, 0);
        return 0;
    }
    /* vt[33] */ virtual void setEnvrNumInfo(int) {
        dStage_SetErrorRoom();
        OSReport("Room non envr num data !!\n");
        JUT_ASSERT(1722, 0);
    }
    /* vt[34] */ virtual int getEnvrNumInfo() const {
        OSReport("Room non envr num data !!\n");
        JUT_ASSERT(1726, 0);
        return 0;
    }
    /* vt[35] */ virtual void setVrboxNumInfo(int i_vrboxNum) { mVrboxNum = i_vrboxNum; }
    /* vt[36] */ virtual int getVrboxNumInfo() const { return mVrboxNum; }
    /* vt[37] */ virtual void setPlightNumInfo(int) {
        dStage_SetErrorRoom();
        OSReport("Room non plight num data !!\n");
        JUT_ASSERT(1735, 0);
    }
    /* vt[38] */ virtual int getPlightNumInfo() const {
        OSReport("Room non plight num data !!\n");
        JUT_ASSERT(1740, 0);
        return 0;
    }
    /* vt[39] */ virtual void setLightVecInfo(stage_lightvec_info_class* i_lightvecInfo) { mpLightVecInfo = i_lightvecInfo; }
    /* vt[40] */ virtual stage_lightvec_info_class* getLightVecInfo() const { return mpLightVecInfo; }
    /* vt[41] */ virtual void setLightVecInfoNum(int i_num) { mLightVecInfoNum = i_num; }
    /* vt[42] */ virtual int getLightVecInfoNum() const { return mLightVecInfoNum; }
    /* vt[43] */ virtual void setStagInfo(stage_stag_info_class*) {
        dStage_SetErrorRoom();
        OSReport("Room non stag data !!\n");
        JUT_ASSERT(1769, 0);
    }
    /* vt[44] */ virtual stage_stag_info_class* getStagInfo() const {
        OSReport("Room non stag data !!\n");
        JUT_ASSERT(1773, 0);
        return NULL;
    }
    /* vt[45] */ virtual void setSclsInfo(stage_scls_info_dummy_class* i_scls) { mpScls = i_scls; }
    /* vt[46] */ virtual stage_scls_info_dummy_class* getSclsInfo() const { return mpScls; }
    /* vt[47] */ virtual void setPntInfo(dStage_dPnt_c*) {
        dStage_SetErrorRoom();
        OSReport("Room non Pnt data !\n");
        JUT_ASSERT(1794, 0);
    }
    /* vt[48] */ virtual dStage_dPnt_c* getPntInf() const {
        OSReport("Room non Pnts data !\n");
        JUT_ASSERT(1798, 0);
        return NULL;
    }
    /* vt[49] */ virtual void setPathInfo(dStage_dPath_c*) {
        dStage_SetErrorRoom();
        OSReport("Room non Path data !\n");
        JUT_ASSERT(1805, 0);
    }
    /* vt[50] */ virtual dStage_dPath_c* getPathInf() const {
        OSReport("Room non Path data !\n");
        JUT_ASSERT(1809, 0);
        return NULL;
    }
    /* vt[51] */ virtual void setPnt2Info(dStage_dPnt_c* i_pnt) { mpPoint2 = i_pnt; }
    /* vt[52] */ virtual dStage_dPnt_c* getPnt2Inf() const { return mpPoint2; }
    /* vt[53] */ virtual void setPath2Info(dStage_dPath_c* i_path) { mpPath2 = i_path; }
    /* vt[54] */ virtual dStage_dPath_c* getPath2Inf() const { return mpPath2; }
    /* vt[55] */ virtual void setSoundInfo(dStage_SoundInfo_c* i_sound) { mpSound = i_sound; }
    /* vt[56] */ virtual dStage_SoundInfo_c* getSoundInf() const { return mpSound; }
    /* vt[57] */ virtual void setEventInfo(dStage_EventInfo_c*) {
        dStage_SetErrorRoom();
        OSReport("Room non event data!\n");
        JUT_ASSERT(1850, 0);
    }
    /* vt[58] */ virtual dStage_EventInfo_c* getEventInfo() const {
        OSReport("Room non event data!\n");
        JUT_ASSERT(1854, 0);
        return NULL;
    }
    /* vt[59] */ virtual void setFileListInfo(dStage_FileList_dt_c* i_filelist) { mpFileList = i_filelist; }
    /* vt[60] */ virtual dStage_FileList_dt_c* getFileListInfo() const { return mpFileList; }
    /* vt[61] */ virtual void setFloorInfo(dStage_FloorInfo_c* i_floor) { mpFloor = i_floor; }
    /* vt[62] */ virtual dStage_FloorInfo_c* getFloorInfo() const { return mpFloor; }
    /* vt[63] */ virtual void setMemoryConfig(dStage_MemoryConfig_c*) {
        OSReport("Room non memory config data!\n");
        JUT_ASSERT(1900, 0);
    }
    /* vt[64] */ virtual dStage_MemoryConfig_c* getMemoryConfig() const {
        OSReport("Room non memory config data!\n");
        JUT_ASSERT(1909, 0);
        return NULL;
    }
    /* vt[65] */ virtual void setMemoryMap(dStage_MemoryMap_c*) {
        OSReport("Room non memory map data!\n");
        JUT_ASSERT(1919, 0);
    }
    /* vt[66] */ virtual dStage_MemoryMap_c* getMemoryMap() const {
        OSReport("Room non memory map data!\n");
        JUT_ASSERT(1928, 0);
        return NULL;
    }
    /* vt[67] */ virtual void setShip(dStage_Ship_c* i_ship) { mpShip = i_ship; }
    /* vt[68] */ virtual dStage_Ship_c* getShip() const { return mpShip; }
    /* vt[69] */ virtual void setMulti(dStage_Multi_c*) {
        OSReport("Room non multi data!\n");
        JUT_ASSERT(1961, 0);
    }
    /* vt[70] */ virtual dStage_Multi_c* getMulti() const {
        OSReport("Room non multi data!\n");
        JUT_ASSERT(1966, 0);
        return NULL;
    }
    /* vt[71] */ virtual void setLbnk(dStage_Lbnk_c* i_lbnk) { mpLbnk = i_lbnk; }
    /* vt[72] */ virtual dStage_Lbnk_c* getLbnk() const { return mpLbnk; }
    /* vt[73] */ virtual void setTresure(stage_tresure_class* i_tresure) { mpTresure = i_tresure; }
    /* vt[74] */ virtual stage_tresure_class* getTresure() const { return mpTresure; }
    /* vt[75] */ virtual void setDMap(dStage_DMap_c*) { JUT_ASSERT(2002, 0); }
    /* vt[76] */ virtual dStage_DMap_c* getDMap() const {
        JUT_ASSERT(2007, 0);
        return NULL;
    }
    /* vt[77] */ virtual void setDrTg(stage_tgsc_class* i_drtg) { mpDrTg = i_drtg; }
    /* vt[78] */ virtual stage_tgsc_class* getDrTg() const { return mpDrTg; }

public:
    /* 0x04 */ stage_lightvec_info_class* mpLightVecInfo;
    /* 0x08 */ int mLightVecInfoNum;
    /* 0x0C */ stage_map_info_class* mpMapInfo;
    /* 0x10 */ stage_map_info_dummy_class* mpMapInfoBase;
    /* 0x14 */ stage_vrbox_info_class* mpVrbox;
    /* 0x18 */ dStage_FileList_dt_c* mpFileList;
    /* 0x1C */ dStage_Ship_c* mpShip;
    /* 0x20 */ stage_actor_class* mpPlayer;
    /* 0x24 */ dStage_dPnt_c* mpPoint2;
    /* 0x28 */ dStage_dPath_c* mpPath2;
    /* 0x2C */ stage_camera_class* mpCamera;
    /* 0x30 */ stage_arrow_class* mpArrow;
    /* 0x34 */ dStage_SoundInfo_c* mpSound;
    /* 0x38 */ stage_scls_info_dummy_class* mpScls;
    /* 0x3C */ dStage_Lbnk_c* mpLbnk;
    /* 0x40 */ stage_tresure_class* mpTresure;
    /* 0x44 */ stage_tgsc_class* mpDrTg;
    /* 0x48 */ dStage_FloorInfo_c* mpFloor;
    /* 0x4C */ s8 mRoomNo;
    /* 0x4D */ u8 field_0x4D[0x4E - 0x4D];
    /* 0x4E */ u16 mPlayerNum;
    /* 0x50 */ int mVrboxNum;
};

class dStage_darkStatus_c {
public:
    /* 0x00 */ u8 mEnvAlpha;
    /* 0x01 */ u8 mBokoAlpha[2];
    /* 0x04 */ f32 mBokoScale[2];
    /* 0x0C */ int field_0xc;
    /* 0x10 */ f32 field_0x10[2];
    /* 0x18 */ f32 field_0x18[2];

    u8 getEnvAlpha() const { return mEnvAlpha; }
    u8 getBokoAlpha(int i) const { return mBokoAlpha[i]; }
    f32 getBokoScale(int i) const { return mBokoScale[i]; }
    // void getNonAlpha(int i) const {}
    // void getNonScale(int i) const {}
};

class dBgW;
class dStage_roomStatus_c {
public:
    /* 0x000 */ dStage_roomDt_c mRoomDt;
    /* 0x054 */ dKy_tevstr_c mTevStr;
    /* 0x104 */ u8 mFlags;
    /* 0x105 */ bool mDraw;
    /* 0x106 */ s8 mZoneCount;
    /* 0x107 */ s8 mZoneNo;
    /* 0x108 */ s8 mMemBlockID;
    /* 0x10C */ int mProcID;
    /* 0x110 */ dBgW* mpBgW;

    ~dStage_roomStatus_c() {}
    dStage_roomStatus_c() {}
};  // Size: 0x114

STATIC_ASSERT(sizeof(dStage_roomStatus_c) == 0x114);

class dStage_roomControl_c {
public:
    dStage_roomControl_c() {}

    void init();
    dStage_roomDt_c* getStatusRoomDt(int);
    BOOL checkRoomDisp(int) const;
    int loadRoom(int, u8*);
    void zoneCountCheck(int) const;
    void checkDrawArea() const;
    dStage_darkStatus_c* getDarkStatus();
    u32 getDarkMode();

    dKy_tevstr_c* getTevStr(int i_roomNo) { return &mStatus[i_roomNo].mTevStr; }
    BOOL checkStatusFlag(int i_roomNo, u8 flag) const { return cLib_checkBit(mStatus[i_roomNo].mFlags, flag); }
    void offStatusFlag(int i_roomNo, u8 flag) { cLib_offBit(mStatus[i_roomNo].mFlags, flag); }
    void onStatusFlag(int i_roomNo, u8 flag) { cLib_onBit(mStatus[i_roomNo].mFlags, flag); }
    void setStatusFlag(int i_roomNo, u8 flag) { mStatus[i_roomNo].mFlags = flag; }

    static JKRExpHeap* createMemoryBlock(int, u32);
    static void destroyMemoryBlock();
    static void SetTimePass(int);
    static JKRExpHeap* getMemoryBlock(int);
    static void setStayNo(int);
    static s32 GetTimePass();
    static void setZoneNo(int i_roomNo, int i_zoneNo) { mStatus[i_roomNo].mZoneNo = i_zoneNo; }
    static int getZoneNo(int i_roomNo) { return mStatus[i_roomNo].mZoneNo; }
    static void setZoneCount(int i_roomNo, int count) { mStatus[i_roomNo].mZoneCount = count; }

    static s8 getStayNo() { return mStayNo; }
    static s8 getMemoryBlockID(int i_roomNo) { return mStatus[i_roomNo].mMemBlockID; }
    static void onStatusDraw(int i_roomNo) { mStatus[i_roomNo].mDraw = true; }
    static void setProcID(uint id) { mProcID = id; }
    static uint getProcID() { return mProcID; }
    static void setStatusProcID(int i_roomNo, uint i_id) { mStatus[i_roomNo].mProcID = i_id; }
    static uint getStatusProcID(int i_roomNo) { return mStatus[i_roomNo].mProcID; }
    static dStage_darkStatus_c& getDarkStatus(int i_idx) { return mDarkStatus[i_idx]; }
    static char* getDemoArcName() { return mDemoArcName; }
    static u8 getDarkRatio() { return mDarkRatio; }
    static u8* getDarkRatio_p() { return &mDarkRatio; }

    static void setMemoryBlockID(int i_roomNo, int i_blockID) {
        mStatus[i_roomNo].mMemBlockID = i_blockID;
    }

    static dBgW* getBgW(int i_roomNo) { return mStatus[i_roomNo].mpBgW; }
    static void setBgW(int i_roomNo, dBgW* i_bgw) { mStatus[i_roomNo].mpBgW = i_bgw; }

    static JKRExpHeap* mMemoryBlock[16];
    static dStage_roomStatus_c mStatus[64];
    static dStage_darkStatus_c mDarkStatus[8];
    static u8 mDarkRatio;
    static uint mProcID;
    static s8 mStayNo;
    static s8 mOldStayNo;
    static s8 m_time_pass;
    static char mDemoArcName[8];

private:
    /* 0x0 */ u8 field_0x0[4];
};

class dStage_startStage_c {
public:
    void set(const char*, s8, s16, s8);
    const char* getName() const { return mName; }
    s16 getPoint() const { return mPoint; }
    int getRoomNo() const { return mRoomNo; }
    s8 getLayer() const { return mLayer; }
    void setLayer(s8 layer) { mLayer = layer; }

private:
    /* 0x0 */ char mName[8];
    /* 0x8 */ s16 mPoint;
    /* 0xA */ s8 mRoomNo;
    /* 0xB */ s8 mLayer;
};

class dStage_nextStage_c : public dStage_startStage_c {
public:
    dStage_nextStage_c() {
        mEnable = 0;  // TODO: maybe wrong
    }
    void set(const char*, s8, s16, s8, s8);
    void offEnable() { mEnable = 0; }
    s8 isEnable() const { return mEnable; }
    s8 getWipe() const { return mWipe; }

private:
    /* 0xC */ s8 mEnable;
    /* 0xD */ s8 mWipe;
};  // Size: 0xE

class dStage_KeepTresureInfo {
public:
    /* 0x00 */ int num;
    /* 0x04 */ stage_tresure_data_class mTresureData[0x20];

    dStage_KeepTresureInfo() {}
    ~dStage_KeepTresureInfo() {}
};

class dStage_KeepDoorInfo {
public:
    /* 0x00 */ int num;
    /* 0x04 */ stage_tgsc_data_class mDrTgData[0x40];

    dStage_KeepDoorInfo() {}
    ~dStage_KeepDoorInfo() {}
};

// unknown name
struct dStage_objectNameInf {
    char mName[8];
    s16 mProcName;
    s8 mSubtype;
    s8 mGbaName;
};  // Size: 0xC

typedef int (*dStage_Func)(dStage_dt_c*, void*, int, void*);
struct FuncTable {
    char identifier[5];
    dStage_Func function;
};

// made up name
struct dStage_fileHeader {
    /* 0x0 */ int chunkCount;
};

// made up name
struct dStage_nodeHeader {
    /* 0x0 */ u32 m_tag;
    /* 0x4 */ int m_entryNum;
    /* 0x8 */ u32 m_offset;
};

s8 dStage_roomRead_dt_c_GetReverbStage(roomRead_class&, int);
int dStage_mapInfo_GetOceanZ(stage_map_info_class*);
int dStage_mapInfo_GetOceanX(stage_map_info_class*);
void dStage_infoCreate();
void dStage_escapeRestart();
void dStage_dt_c_roomLoader(void* i_data, dStage_dt_c* i_stage);
void dStage_dt_c_roomReLoader(void* i_data, dStage_dt_c* i_stage, int i_roomNo);

dStage_objectNameInf* dStage_searchName(const char*);
const char* dStage_getName2(s16 i_procName, s8 i_subtype);

inline s32 dStage_stagInfo_GetSaveTbl(stage_stag_info_class* i_stagInfo) {
    return (i_stagInfo->field_0x09 >> 1) & 0x7F;
}

inline u32 dStage_stagInfo_GetSTType(stage_stag_info_class* i_stagInfo) {
    return (i_stagInfo->field_0x0c >> 16) & 7;
}

inline u8 dStage_stagInfo_GetParticleNo(stage_stag_info_class* i_stagInfo) {
    return (i_stagInfo->field_0x0a >> 0x3) & 0xFF;
}

inline s8 dStage_stagInfo_GetTimeH(stage_stag_info_class* p_info) {
    return (p_info->field_0x0c >> 8) & 0xFF;
}

inline u8 dStage_stagInfo_getStartSch(stage_stag_info_class* p_info) {
    return (p_info->field_0x10 >> 0x10) & 0xFF;
}

// TODO:
// dStage_stagInfo_GetAgbCon__FP21stage_stag_info_class
// dStage_stagInfo_GetSchSec__FP21stage_stag_info_class - field_0x0c & 0xFF
// dStage_stagInfo_DefaultCameraType__FP21stage_stag_info_class
// dStage_stagInfo_GetCullPoint__FP21stage_stag_info_class
// dStage_stagInfo_GetUpButton__FP21stage_stag_info_class
// dStage_stagInfo_ChkKeyDisp__FP21stage_stag_info_class

inline u8 dStage_roomRead_dt_c_GetLoadRoomIndex(u8 param_0) {
    return param_0 & 0x3F;
}

inline u8 dStage_roomRead_dt_c_ChkBg(u8 param_0) {
    return param_0 & 0x80;
}

inline u8 dStage_roomRead_dt_c_GetReverb(roomRead_data_class& room) {
    return room.field_0x1 & 0x7F;
}

inline s32 dStage_roomRead_dt_c_GetTimePass(roomRead_data_class& data) {
    return data.field_0x2 & 0x03;
}

inline s32 dStage_sclsInfo_getWipe(stage_scls_info_class* p_info) {
    return p_info->mWipe & 0xF;
}

inline int dStage_FileList_dt_ChkPathWindEffect(dStage_FileList_dt_c* i_fili) {
    return i_fili->mParam & 0x100000;
}

inline int dStage_FileList_dt_GlobalWindLevel(dStage_FileList_dt_c* i_fili) {
    return (i_fili->mParam >> 18) & 3;
}

inline f32 dStage_FileList_dt_SeaLevel(dStage_FileList_dt_c* i_fili) {
    return i_fili->mSeaLevel;
}

inline u8 dStage_FileList_dt_PhotoDepth(dStage_FileList_dt_c* i_fili) {
    return (i_fili->mParam >> 7) & 0xFF;
}

inline s32 dStage_FileList_dt_CheckDarkOn(dStage_FileList_dt_c* i_fili) {
    return i_fili->mParam & 1;
}

inline u8 dStage_FileList_dt_DarkNo(dStage_FileList_dt_c* i_fili) {
    return (i_fili->mParam & 0x78) >> 3;
}

inline u8 dStage_FileList_dt_CheckAgbCom(dStage_FileList_dt_c* i_fili) {
    return i_fili->mParam & 2;
}

inline u8 dStage_FileList_dt_CheckAgbHover(dStage_FileList_dt_c* i_fili) {
    return i_fili->mParam & 4;
}

// inline u8 dStage_FileList_dt_GetSongOk(dStage_FileList_dt_c* i_fili) {
    // maybe 0x40000000?
// }

// inline u8 dStage_FileList_dt_GetToonsw(dStage_FileList_dt_c* i_fili) {
    
// }

inline u32 dStage_FileList_dt_GetParticleNo(dStage_FileList_dt_c* i_fili) {
    return (i_fili->mParam >> 21) & 0xFF;
}

bool dStage_chkPlayerId(int playerId, int room_no);
int dStage_changeScene(int i_exitId, f32 speed, u32 mode, s8 room_no);
void dStage_restartRoom(u32 roomParam, u32 mode);
bool dStage_setShipPos(int param_0, int i_roomNo);
BOOL dStage_checkRestart();
void dStage_Create();
void dStage_Delete();

class cBgS_GndChk;
int dStage_RoomCheck(cBgS_GndChk* i_gndChk);

static inline u8 IkadaGetRoomNoArg0(fopAc_ac_c* i_actor) {
    return (fopAcM_GetParam(i_actor) >> 4) & 0x3F;
}

static inline u8 IkadaGetLinkIdArg1(fopAc_ac_c* i_actor) {
    return (fopAcM_GetParam(i_actor) >> 10) & 0xFF;
}

static inline u8 IkadaGetIkadaIdArg2(fopAc_ac_c* i_actor) {
    return (fopAcM_GetParam(i_actor) >> 0x12) & 0xFF;
}

inline int IkadaGetIkadaIdArgPrm(u32 param) {
    return (param >> 0x12) & 0xFF;
}

#endif /* D_D_STAGE_H */
