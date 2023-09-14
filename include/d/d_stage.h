#ifndef D_D_STAGE_H
#define D_D_STAGE_H

#include "global.h"
#include "d/d_kankyo.h"
#include "SSystem/SComponent/c_lib.h"

class JKRExpHeap;

struct stage_vrbox_info_class {};

class stage_tresure_class {};

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
    /* 0xA */ u8 field_0xa;
    /* 0xB */ s8 mWipe;
};

struct stage_scls_info_dummy_class {
    /* 0x00 */ int num;
    /* 0x04 */ stage_scls_info_class* m_entries;
};

struct stage_lightvec_info_class {};

struct stage_pselect_info_class {};

struct stage_plight_info_class {};

struct stage_palet_info_class {};

struct stage_map_info_class {};

struct stage_map_info_dummy_class {};

struct stage_envr_info_class {};

struct stage_camera_class {};

struct stage_arrow_class {};

class stage_actor_data_class {};

class stage_actor_class {};

struct stage_tgsc_data_class : public stage_actor_data_class {};

class stage_tgsc_class {};

struct roomRead_data_class {};

struct roomRead_class {};

struct dStage_MemoryMap_c {};

struct dStage_dPath_c {};

struct dStage_Mult_info {
    /* 0x0 */ f32 mTransX;
    /* 0x4 */ f32 mTransY;
    /* 0x8 */ s16 mAngle;
    /* 0xA */ u8 mRoomNo;
};  // Size: 0xC

class dStage_Multi_c {
public:
    /* 0x0 */ int m_num;
    /* 0x4 */ dStage_Mult_info* m_entries;
};

struct dStage_SoundInfo_c {};

class dStage_FileList_dt_c {};

struct dStage_dPnt_c {};

struct dStage_FloorInfo_c {};

struct dStage_Lbnk_c {};

struct dStage_MemoryConfig_c {};

struct dStage_DMap_c {};

struct dStage_EventInfo_c {};

struct dStage_Ship_data {
    /* 0x0 */ u8 field_0x0[0xE];
    /* 0xE */ u8 field_0xe;
    /* 0xF */ u8 field_0xf;
};

class dStage_Ship_c {
public:
    /* 0x0 */ int m_num;
    /* 0x4 */ dStage_Ship_data* m_entries;
};

class dStage_dt_c {
public:
    dStage_dt_c() {}

    /* vt[ 2] */ virtual void init(void) = 0;
    /* vt[ 3] */ virtual s8 getRoomNo() = 0;
    /* vt[ 4] */ virtual void setCamera(stage_camera_class*) = 0;
    /* vt[ 5] */ virtual stage_camera_class* getCamera(void) const = 0;
    /* vt[ 6] */ virtual void setArrow(stage_arrow_class*) = 0;
    /* vt[ 7] */ virtual stage_arrow_class* getArrow(void) const = 0;
    /* vt[ 8] */ virtual void setPlayer(stage_actor_class*) = 0;
    /* vt[ 9] */ virtual stage_actor_class* getPlayer(void) const = 0;
    /* vt[10] */ virtual void setPlayerNum(u16) = 0;
    /* vt[11] */ virtual u16 getPlayerNum(void) const = 0;
    /* vt[12] */ virtual void setRoom(roomRead_class*) = 0;
    /* vt[13] */ virtual roomRead_class* getRoom(void) const = 0;
    /* vt[14] */ virtual void setMapInfo(stage_map_info_class*) = 0;
    /* vt[15] */ virtual stage_map_info_class* getMapInfo(void) const = 0;
    /* vt[16] */ virtual stage_map_info_class* getMapInfo2(int) const = 0;
    /* vt[17] */ virtual void setMapInfoBase(stage_map_info_dummy_class*) = 0;
    /* vt[18] */ virtual stage_map_info_dummy_class* getMapInfoBase(void) const = 0;
    /* vt[19] */ virtual void setPaletInfo(stage_palet_info_class*) = 0;
    /* vt[20] */ virtual stage_palet_info_class* getPaletInfo(void) const = 0;
    /* vt[21] */ virtual void setPselectInfo(stage_pselect_info_class*) = 0;
    /* vt[22] */ virtual stage_pselect_info_class* getPselectInfo(void) const = 0;
    /* vt[23] */ virtual void setEnvrInfo(stage_envr_info_class*) = 0;
    /* vt[24] */ virtual stage_envr_info_class* getEnvrInfo(void) const = 0;
    /* vt[25] */ virtual void setVrboxInfo(stage_vrbox_info_class*) = 0;
    /* vt[26] */ virtual stage_vrbox_info_class* getVrboxInfo(void) const = 0;
    /* vt[27] */ virtual void setPlightInfo(stage_plight_info_class*) = 0;
    /* vt[28] */ virtual stage_plight_info_class* getPlightInfo(void) const = 0;
    /* vt[29] */ virtual void setPaletNumInfo(int) = 0;
    /* vt[30] */ virtual int getPaletNumInfo(void) const = 0;
    /* vt[31] */ virtual void setPselectNumInfo(int) = 0;
    /* vt[32] */ virtual int getPselectNumInfo(void) const = 0;
    /* vt[33] */ virtual void setEnvrNumInfo(int) = 0;
    /* vt[34] */ virtual int getEnvrNumInfo(void) const = 0;
    /* vt[35] */ virtual void setVrboxNumInfo(int) = 0;
    /* vt[36] */ virtual int getVrboxNumInfo(void) const = 0;
    /* vt[37] */ virtual void setPlightNumInfo(int) = 0;
    /* vt[38] */ virtual int getPlightNumInfo(void) const = 0;
    /* vt[39] */ virtual void setLightVecInfo(stage_lightvec_info_class*) = 0;
    /* vt[40] */ virtual stage_lightvec_info_class* getLightVecInfo(void) const = 0;
    /* vt[41] */ virtual void setLightVecInfoNum(int) = 0;
    /* vt[42] */ virtual int getLightVecInfoNum(void) const = 0;
    /* vt[43] */ virtual void setStagInfo(stage_stag_info_class*) = 0;
    /* vt[44] */ virtual stage_stag_info_class* getStagInfo(void) const = 0;
    /* vt[45] */ virtual void setSclsInfo(stage_scls_info_dummy_class*) = 0;
    /* vt[46] */ virtual stage_scls_info_dummy_class* getSclsInfo(void) const = 0;
    /* vt[47] */ virtual void setPntInfo(dStage_dPnt_c*) = 0;
    /* vt[48] */ virtual dStage_dPnt_c* getPntInf(void) const = 0;
    /* vt[49] */ virtual void setPathInfo(dStage_dPath_c*) = 0;
    /* vt[50] */ virtual dStage_dPath_c* getPathInf(void) const = 0;
    /* vt[51] */ virtual void setPnt2Info(dStage_dPnt_c*) = 0;
    /* vt[52] */ virtual dStage_dPnt_c* getPnt2Inf(void) const = 0;
    /* vt[53] */ virtual void setPath2Info(dStage_dPath_c*) = 0;
    /* vt[54] */ virtual dStage_dPath_c* getPath2Inf(void) const = 0;
    /* vt[55] */ virtual void setSoundInf(dStage_SoundInfo_c*) = 0;
    /* vt[56] */ virtual dStage_SoundInfo_c* getSoundInf(void) const = 0;
    /* vt[57] */ virtual void setEventInfo(dStage_EventInfo_c*) = 0;
    /* vt[58] */ virtual dStage_EventInfo_c* getEventInfo(void) const = 0;
    /* vt[59] */ virtual void setFileListInfo(dStage_FileList_dt_c*) = 0;
    /* vt[60] */ virtual dStage_FileList_dt_c* getFileListInfo(void) const = 0;
    /* vt[61] */ virtual void setFloorInfo(dStage_FloorInfo_c*) = 0;
    /* vt[62] */ virtual dStage_FloorInfo_c* getFloorInfo(void) const = 0;
    /* vt[63] */ virtual void setMemoryConfig(dStage_MemoryConfig_c*) = 0;
    /* vt[64] */ virtual dStage_MemoryConfig_c* getMemoryConfig(void) const = 0;
    /* vt[65] */ virtual void setMemoryMap(dStage_MemoryMap_c*) = 0;
    /* vt[66] */ virtual dStage_MemoryMap_c* getMemoryMap(void) const = 0;
    /* vt[67] */ virtual void setShip(dStage_Ship_c*) = 0;
    /* vt[68] */ virtual dStage_Ship_c* getShip() const = 0;
    /* vt[69] */ virtual void setMulti(dStage_Multi_c*) = 0;
    /* vt[70] */ virtual dStage_Multi_c* getMulti(void) const = 0;
    /* vt[71] */ virtual void setLbnk(dStage_Lbnk_c*) = 0;
    /* vt[72] */ virtual dStage_Lbnk_c* getLbnk(void) const = 0;
    /* vt[73] */ virtual void setTresure(stage_tresure_class*) = 0;
    /* vt[74] */ virtual stage_tresure_class* getTresure(void) const = 0;
    /* vt[75] */ virtual void setDMap(dStage_DMap_c*) = 0;
    /* vt[76] */ virtual dStage_DMap_c* getDMap(void) const = 0;
    /* vt[77] */ virtual void setDrTg(stage_tgsc_class*) = 0;
    /* vt[78] */ virtual stage_tgsc_class* getDrTg(void) const = 0;
};

class dStage_stageDt_c : public dStage_dt_c {
public:
    dStage_stageDt_c() {}

    /* vt[ 2] */ virtual void init(void);
    /* vt[ 3] */ virtual s8 getRoomNo();
    /* vt[ 4] */ virtual void setCamera(stage_camera_class*);
    /* vt[ 5] */ virtual stage_camera_class* getCamera(void) const;
    /* vt[ 6] */ virtual void setArrow(stage_arrow_class*);
    /* vt[ 7] */ virtual stage_arrow_class* getArrow(void) const;
    /* vt[ 8] */ virtual void setPlayer(stage_actor_class*);
    /* vt[ 9] */ virtual stage_actor_class* getPlayer(void) const;
    /* vt[10] */ virtual void setPlayerNum(u16);
    /* vt[11] */ virtual u16 getPlayerNum(void) const;
    /* vt[12] */ virtual void setRoom(roomRead_class*);
    /* vt[13] */ virtual roomRead_class* getRoom(void) const;
    /* vt[14] */ virtual void setMapInfo(stage_map_info_class*);
    /* vt[15] */ virtual stage_map_info_class* getMapInfo(void) const;
    /* vt[16] */ virtual stage_map_info_class* getMapInfo2(int) const;
    /* vt[17] */ virtual void setMapInfoBase(stage_map_info_dummy_class*);
    /* vt[18] */ virtual stage_map_info_dummy_class* getMapInfoBase(void) const;
    /* vt[19] */ virtual void setPaletInfo(stage_palet_info_class*);
    /* vt[20] */ virtual stage_palet_info_class* getPaletInfo(void) const;
    /* vt[21] */ virtual void setPselectInfo(stage_pselect_info_class*);
    /* vt[22] */ virtual stage_pselect_info_class* getPselectInfo(void) const;
    /* vt[23] */ virtual void setEnvrInfo(stage_envr_info_class*);
    /* vt[24] */ virtual stage_envr_info_class* getEnvrInfo(void) const;
    /* vt[25] */ virtual void setVrboxInfo(stage_vrbox_info_class*);
    /* vt[26] */ virtual stage_vrbox_info_class* getVrboxInfo(void) const;
    /* vt[27] */ virtual void setPlightInfo(stage_plight_info_class*);
    /* vt[28] */ virtual stage_plight_info_class* getPlightInfo(void) const;
    /* vt[29] */ virtual void setPaletNumInfo(int);
    /* vt[30] */ virtual int getPaletNumInfo(void) const;
    /* vt[31] */ virtual void setPselectNumInfo(int);
    /* vt[32] */ virtual int getPselectNumInfo(void) const;
    /* vt[33] */ virtual void setEnvrNumInfo(int);
    /* vt[34] */ virtual int getEnvrNumInfo(void) const;
    /* vt[35] */ virtual void setVrboxNumInfo(int);
    /* vt[36] */ virtual int getVrboxNumInfo(void) const;
    /* vt[37] */ virtual void setPlightNumInfo(int);
    /* vt[38] */ virtual int getPlightNumInfo(void) const;
    /* vt[39] */ virtual void setLightVecInfo(stage_lightvec_info_class*);
    /* vt[40] */ virtual stage_lightvec_info_class* getLightVecInfo(void) const;
    /* vt[41] */ virtual void setLightVecInfoNum(int);
    /* vt[42] */ virtual int getLightVecInfoNum(void) const;
    /* vt[43] */ virtual void setStagInfo(stage_stag_info_class*);
    /* vt[44] */ virtual stage_stag_info_class* getStagInfo(void) const;
    /* vt[45] */ virtual void setSclsInfo(stage_scls_info_dummy_class*);
    /* vt[46] */ virtual stage_scls_info_dummy_class* getSclsInfo(void) const;
    /* vt[47] */ virtual void setPntInfo(dStage_dPnt_c*);
    /* vt[48] */ virtual dStage_dPnt_c* getPntInf(void) const;
    /* vt[49] */ virtual void setPathInfo(dStage_dPath_c*);
    /* vt[50] */ virtual dStage_dPath_c* getPathInf(void) const;
    /* vt[51] */ virtual void setPnt2Info(dStage_dPnt_c*);
    /* vt[52] */ virtual dStage_dPnt_c* getPnt2Inf(void) const;
    /* vt[53] */ virtual void setPath2Info(dStage_dPath_c*);
    /* vt[54] */ virtual dStage_dPath_c* getPath2Inf(void) const;
    /* vt[55] */ virtual void setSoundInf(dStage_SoundInfo_c*);
    /* vt[56] */ virtual dStage_SoundInfo_c* getSoundInf(void) const;
    /* vt[57] */ virtual void setEventInfo(dStage_EventInfo_c*);
    /* vt[58] */ virtual dStage_EventInfo_c* getEventInfo(void) const;
    /* vt[59] */ virtual void setFileListInfo(dStage_FileList_dt_c*);
    /* vt[60] */ virtual dStage_FileList_dt_c* getFileListInfo(void) const;
    /* vt[61] */ virtual void setFloorInfo(dStage_FloorInfo_c*);
    /* vt[62] */ virtual dStage_FloorInfo_c* getFloorInfo(void) const;
    /* vt[63] */ virtual void setMemoryConfig(dStage_MemoryConfig_c*);
    /* vt[64] */ virtual dStage_MemoryConfig_c* getMemoryConfig(void) const;
    /* vt[65] */ virtual void setMemoryMap(dStage_MemoryMap_c*);
    /* vt[66] */ virtual dStage_MemoryMap_c* getMemoryMap(void) const;
    /* vt[67] */ virtual void setShip(dStage_Ship_c*);
    /* vt[68] */ virtual dStage_Ship_c* getShip() const;
    /* vt[69] */ virtual void setMulti(dStage_Multi_c*);
    /* vt[70] */ virtual dStage_Multi_c* getMulti(void) const;
    /* vt[71] */ virtual void setLbnk(dStage_Lbnk_c*);
    /* vt[72] */ virtual dStage_Lbnk_c* getLbnk(void) const;
    /* vt[73] */ virtual void setTresure(stage_tresure_class*);
    /* vt[74] */ virtual stage_tresure_class* getTresure(void) const;
    /* vt[75] */ virtual void setDMap(dStage_DMap_c*);
    /* vt[76] */ virtual dStage_DMap_c* getDMap(void) const;
    /* vt[77] */ virtual void setDrTg(stage_tgsc_class*);
    /* vt[78] */ virtual stage_tgsc_class* getDrTg(void) const;

public:
    /* 0x04 */ stage_camera_class* mpCamera;
    /* 0x08 */ stage_arrow_class* mpArrow;
    /* 0x0C */ void* field_0x0c;
    /* 0x10 */ roomRead_class* mpRoomReads;
    /* 0x14 */ stage_map_info_class* mpMapInfo;
    /* 0x18 */ stage_map_info_dummy_class* mpMapInfoBase;
    /* 0x1C */ stage_palet_info_class* mpPaletInfo;
    /* 0x20 */ stage_pselect_info_class* mpPselectInfo;
    /* 0x24 */ stage_envr_info_class* mpEnvrInfo;
    /* 0x28 */ stage_vrbox_info_class* mpVrboxInfo;
    /* 0x2C */ stage_plight_info_class* mpPlightInfo;
    /* 0x30 */ void* field_0x30;
    /* 0x34 */ void* field_0x34;
    /* 0x38 */ void* field_0x38;
    /* 0x3C */ int field_0x3c;
    /* 0x40 */ int mPlightInfoNum;
    /* 0x44 */ void* field_0x44;
    /* 0x48 */ stage_stag_info_class* mpStagInfo;
    /* 0x4C */ stage_scls_info_dummy_class* mpScls;
    /* 0x50 */ dStage_dPnt_c* mpPnt;
    /* 0x54 */ dStage_dPath_c* mpPath;
    /* 0x58 */ dStage_dPnt_c* mpPnt2;
    /* 0x5C */ dStage_dPath_c* mpPath2;
    /* 0x60 */ void* field_0x60;
    /* 0x64 */ dStage_EventInfo_c* mpEventInfo;
    /* 0x68 */ void* field_0x68;
    /* 0x6C */ void* field_0x6c;
    /* 0x70 */ void* field_0x70;
    /* 0x74 */ dStage_Multi_c* mpMulti;
    /* 0x78 */ void* field_0x78;
    /* 0x7C */ void* field_0x7c;
    /* 0x80 */ void* field_0x80;
};

class dStage_roomDt_c : public dStage_dt_c {
public:
    /* vt[ 2] */ virtual void init(void);
    /* vt[ 3] */ virtual s8 getRoomNo();
    /* vt[ 4] */ virtual void setCamera(stage_camera_class*);
    /* vt[ 5] */ virtual stage_camera_class* getCamera(void) const;
    /* vt[ 6] */ virtual void setArrow(stage_arrow_class*);
    /* vt[ 7] */ virtual stage_arrow_class* getArrow(void) const;
    /* vt[ 8] */ virtual void setPlayer(stage_actor_class*);
    /* vt[ 9] */ virtual stage_actor_class* getPlayer(void) const;
    /* vt[10] */ virtual void setPlayerNum(u16);
    /* vt[11] */ virtual u16 getPlayerNum(void) const;
    /* vt[12] */ virtual void setRoom(roomRead_class*);
    /* vt[13] */ virtual roomRead_class* getRoom(void) const;
    /* vt[14] */ virtual void setMapInfo(stage_map_info_class*);
    /* vt[15] */ virtual stage_map_info_class* getMapInfo(void) const;
    /* vt[16] */ virtual stage_map_info_class* getMapInfo2(int) const;
    /* vt[17] */ virtual void setMapInfoBase(stage_map_info_dummy_class*);
    /* vt[18] */ virtual stage_map_info_dummy_class* getMapInfoBase(void) const;
    /* vt[19] */ virtual void setPaletInfo(stage_palet_info_class*);
    /* vt[20] */ virtual stage_palet_info_class* getPaletInfo(void) const;
    /* vt[21] */ virtual void setPselectInfo(stage_pselect_info_class*);
    /* vt[22] */ virtual stage_pselect_info_class* getPselectInfo(void) const;
    /* vt[23] */ virtual void setEnvrInfo(stage_envr_info_class*);
    /* vt[24] */ virtual stage_envr_info_class* getEnvrInfo(void) const;
    /* vt[25] */ virtual void setVrboxInfo(stage_vrbox_info_class*);
    /* vt[26] */ virtual stage_vrbox_info_class* getVrboxInfo(void) const;
    /* vt[27] */ virtual void setPlightInfo(stage_plight_info_class*);
    /* vt[28] */ virtual stage_plight_info_class* getPlightInfo(void) const;
    /* vt[29] */ virtual void setPaletNumInfo(int);
    /* vt[30] */ virtual int getPaletNumInfo(void) const;
    /* vt[31] */ virtual void setPselectNumInfo(int);
    /* vt[32] */ virtual int getPselectNumInfo(void) const;
    /* vt[33] */ virtual void setEnvrNumInfo(int);
    /* vt[34] */ virtual int getEnvrNumInfo(void) const;
    /* vt[35] */ virtual void setVrboxNumInfo(int);
    /* vt[36] */ virtual int getVrboxNumInfo(void) const;
    /* vt[37] */ virtual void setPlightNumInfo(int);
    /* vt[38] */ virtual int getPlightNumInfo(void) const;
    /* vt[39] */ virtual void setLightVecInfo(stage_lightvec_info_class*);
    /* vt[40] */ virtual stage_lightvec_info_class* getLightVecInfo(void) const;
    /* vt[41] */ virtual void setLightVecInfoNum(int);
    /* vt[42] */ virtual int getLightVecInfoNum(void) const;
    /* vt[43] */ virtual void setStagInfo(stage_stag_info_class*);
    /* vt[44] */ virtual stage_stag_info_class* getStagInfo(void) const;
    /* vt[45] */ virtual void setSclsInfo(stage_scls_info_dummy_class*);
    /* vt[46] */ virtual stage_scls_info_dummy_class* getSclsInfo(void) const;
    /* vt[47] */ virtual void setPntInfo(dStage_dPnt_c*);
    /* vt[48] */ virtual dStage_dPnt_c* getPntInf(void) const;
    /* vt[49] */ virtual void setPathInfo(dStage_dPath_c*);
    /* vt[50] */ virtual dStage_dPath_c* getPathInf(void) const;
    /* vt[51] */ virtual void setPnt2Info(dStage_dPnt_c*);
    /* vt[52] */ virtual dStage_dPnt_c* getPnt2Inf(void) const;
    /* vt[53] */ virtual void setPath2Info(dStage_dPath_c*);
    /* vt[54] */ virtual dStage_dPath_c* getPath2Inf(void) const;
    /* vt[55] */ virtual void setSoundInf(dStage_SoundInfo_c*);
    /* vt[56] */ virtual dStage_SoundInfo_c* getSoundInf(void) const;
    /* vt[57] */ virtual void setEventInfo(dStage_EventInfo_c*);
    /* vt[58] */ virtual dStage_EventInfo_c* getEventInfo(void) const;
    /* vt[59] */ virtual void setFileListInfo(dStage_FileList_dt_c*);
    /* vt[60] */ virtual dStage_FileList_dt_c* getFileListInfo(void) const;
    /* vt[61] */ virtual void setFloorInfo(dStage_FloorInfo_c*);
    /* vt[62] */ virtual dStage_FloorInfo_c* getFloorInfo(void) const;
    /* vt[63] */ virtual void setMemoryConfig(dStage_MemoryConfig_c*);
    /* vt[64] */ virtual dStage_MemoryConfig_c* getMemoryConfig(void) const;
    /* vt[65] */ virtual void setMemoryMap(dStage_MemoryMap_c*);
    /* vt[66] */ virtual dStage_MemoryMap_c* getMemoryMap(void) const;
    /* vt[67] */ virtual void setShip(dStage_Ship_c*);
    /* vt[68] */ virtual dStage_Ship_c* getShip() const;
    /* vt[69] */ virtual void setMulti(dStage_Multi_c*);
    /* vt[70] */ virtual dStage_Multi_c* getMulti(void) const;
    /* vt[71] */ virtual void setLbnk(dStage_Lbnk_c*);
    /* vt[72] */ virtual dStage_Lbnk_c* getLbnk(void) const;
    /* vt[73] */ virtual void setTresure(stage_tresure_class*);
    /* vt[74] */ virtual stage_tresure_class* getTresure(void) const;
    /* vt[75] */ virtual void setDMap(dStage_DMap_c*);
    /* vt[76] */ virtual dStage_DMap_c* getDMap(void) const;
    /* vt[77] */ virtual void setDrTg(stage_tgsc_class*);
    /* vt[78] */ virtual stage_tgsc_class* getDrTg(void) const;

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
    /* 0x4C */ u8 mRoomNo;
    /* 0x4D */ u8 field_0x4D[0x4E - 0x4D];
    /* 0x4E */ short mPlayerNum;
    /* 0x50 */ int mVrboxNum;
};

class dStage_darkStatus_c {
public:
    // name to offset relation is guessed based on debug map
    // may need to be fixed

    /* 0x00 */ u8 mRatio;
    /* 0x01 */ u8 mNonAlpha[2];
    /* 0x04 */ f32 mNonScale[2];
    /* 0x0C */ int field_0xc;
    /* 0x10 */ int field_0x10[2];
    /* 0x18 */ int field_0x18[2];
};

class dBgW_base;
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
    /* 0x110 */ dBgW_base* mpBgW;

    int getZoneNo() const { return mZoneNo; }
    ~dStage_roomStatus_c() {}
    dStage_roomStatus_c() {}
};  // Size: 0x114

STATIC_ASSERT(sizeof(dStage_roomStatus_c) == 0x114);

class dStage_roomControl_c {
public:
    dStage_roomControl_c() {}
    
    void init();
    dStage_roomStatus_c* getStatusRoomDt(int);
    bool checkRoomDisp(int) const;
    int loadRoom(int, u8*);
    void zoneCountCheck(int) const;
    void checkDrawArea() const;
    void getDarkStatus();
    void getDarkMode();
    void getBgW(int);

    static void createMemoryBlock(int, u32);
    static void destroyMemoryBlock(void);
    static void SetTimePass(int);
    static JKRExpHeap* getMemoryBlock(int);
    static void setStayNo(int);
    static s8 GetTimePass();
    static void setZoneNo(int, int);
    static int getZoneNo(int i_roomNo);

    static s8 getStayNo() { return mStayNo; }
    static s8 getMemoryBlockID(int i_roomNo) { return mStatus[i_roomNo].mMemBlockID; }
    dKy_tevstr_c* getTevStr(int i_roomNo) { return &mStatus[i_roomNo].mTevStr; }
    void setStatusFlag(int i_roomNo, u8 flag) { mStatus[i_roomNo].mFlags = flag; }
    static void onStatusDraw(int i_roomNo) { mStatus[i_roomNo].mDraw = true; }
    static void setProcID(u32 id) { mProcID = id; }
    static u32 getProcID() { return mProcID; }
    static void setStatusProcID(int i_roomNo, unsigned int i_id) { mStatus[i_roomNo].mProcID = i_id; }
    static int getStatusProcID(int i_roomNo) { return mStatus[i_roomNo].mProcID; }
    static dStage_darkStatus_c& getDarkStatus(int i_idx) { return mDarkStatus[i_idx]; }

    static void setMemoryBlockID(int i_roomNo, int i_blockID) {
        mStatus[i_roomNo].mMemBlockID = i_blockID;
    }

    static void setBgW(int param_0, dBgW_base* i_bgw) {
        mStatus[param_0].mpBgW = i_bgw;
    }

    BOOL checkStatusFlag(int i_roomNo, u8 flag) const {
        return cLib_checkBit(mStatus[i_roomNo].mFlags, flag);
    }

    void offStatusFlag(int i_roomNo, u8 flag) {
        return cLib_offBit(mStatus[i_roomNo].mFlags, flag);
    }

    void onStatusFlag(int i_roomNo, u8 flag) {
        return cLib_onBit(mStatus[i_roomNo].mFlags, flag);
    }

    static JKRExpHeap* mMemoryBlock[101];
    static dStage_roomStatus_c mStatus[64];
    static dStage_darkStatus_c mDarkStatus[8];
    static u32 mProcID;
    static s8 mStayNo;
    static s8 mOldStayNo;
    static s8 m_time_pass;

private:
    /* 0x0 */ u8 field_0x0[4];
};

class dStage_startStage_c {
public:
    void set(const char*, s8, s16, s8);
    const char* getName() const { return mName; }
    s16 getPoint() const { return mPoint; }
    s8 getRoomNo() const { return mRoomNo; }
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

s8 dStage_roomRead_dt_c_GetReverbStage(roomRead_class&, int);
int dStage_mapInfo_GetOceanZ(stage_map_info_class*);
int dStage_mapInfo_GetOceanX(stage_map_info_class*);
void dStage_infoCreate();

inline s32 dStage_stagInfo_GetSaveTbl(stage_stag_info_class* i_stagInfo) {
    return (i_stagInfo->field_0x09 >> 1) & 0x7F;
}

inline u32 dStage_stagInfo_GetSTType(stage_stag_info_class* i_stagInfo) {
    return (i_stagInfo->field_0x0c >> 16) & 7;
}

inline u8 dStage_stagInfo_GetParticleNo(stage_stag_info_class* i_stagInfo) {
    return (i_stagInfo->field_0x0a >> 0x3) & 0xFF;
}

#endif /* D_D_STAGE_H */