#ifndef D_MAP_H
#define D_MAP_H

#include "d/d_drawlist.h"

struct ResTIMG;
struct dmap_dmap_tlut_s;
class fopAc_ac_c;
struct map_dt_c;
class stage_map_info_class;

class dMap_2DMtMapSpcl_tex_c {
public:
    dMap_2DMtMapSpcl_tex_c();
    ~dMap_2DMtMapSpcl_tex_c();
    void init(ResTIMG*, u32, const GXColor&);
    void setScroll(f32, f32, f32, f32);

    /* 0x00 */ u8 field_0x0[4];
    /* 0x04 */ GXTexObj field_0x4;
    /* 0x24 */ GXTlutObj field_0x24;
    /* 0x30 */ GXColor field_0x30;
    /* 0x34 */ u8 field_0x34[0x44 - 0x34];
    /* 0x44 */ u32 field_0x44;
};

class dMap_2DMtMapSpcl_c : public dDlst_base_c {
public:
    dMap_2DMtMapSpcl_c() {}
    ~dMap_2DMtMapSpcl_c() {}
    void init(int, dMap_2DMtMapSpcl_tex_c*);
    void setPos(s16, s16, s16, s16);
    void draw();

    /* 0x04 */ u8 field_0x4;
    /* 0x05 */ u8 field_0x5;
    /* 0x08 */ dMap_2DMtMapSpcl_tex_c* field_0x8;
    /* 0x0C */ s16 field_0xc;
    /* 0x0E */ s16 field_0xe;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
};

class dMap_2DAGBScrDsp_c : public dDlst_base_c {
public:
    ~dMap_2DAGBScrDsp_c() {}
    void setImage(ResTIMG*, map_dt_c*);
    void init(map_dt_c*, ResTIMG*, f32, f32, s16, s16, s16, s16, f32, f32, u8);
    void getScrnPrm(f32, f32, int, f32, int*, f32*, f32*);
    void getScrnPrmXY(f32, f32, f32, f32, int, int, f32, f32, int*, int*, f32*, f32*, f32*, f32*);
    void calc_standard_prm(u16, u16, f32, f32, s16, s16, s16, s16, f32, f32, int*, int*, int*, int*, f32*, f32*, f32*, f32*, f32*, f32*);
    void draw();
    void setPos(s16, s16, s16, s16);
    void setScale(f32, f32);

    /* 0x04 */ map_dt_c* field_0x4;
    /* 0x08 */ ResTIMG* field_0x8;
    /* 0x0C */ GXTexObj field_0xc;
    /* 0x2C */ GXTlutObj field_0x2c;
};

class dMap_RoomInfo_c {
public:
    dMap_RoomInfo_c();
    ~dMap_RoomInfo_c();
    void getRoomDspFloorNo(u8, int);
    void init(dMap_RoomInfo_c*, int);
    void getRoomImage(int, u8, int, ResTIMG**, ResTIMG**, map_dt_c**, stage_map_info_class**, u8*);
    void makeRoomDspFloorNoTbl(int);
    void roomEntryRoom(int, u8, int, u8, dMap_RoomInfo_c*, s16, s16, f32);
    void Changeimage(u8, u8, int, s16, s16, f32);
    void deleteRoom();
    void enlagementSizeTextureCordCalc(f32*, f32*, f32*, f32*, f32, f32, f32, f32, f32, f32);
    void roomDrawRoomEnlargementSize(int, int, int, int, f32, f32, f32, f32, u8);
    void roomDrawRoomRealSize(int, int, int, int, f32, f32, f32, f32, f32, f32, u8);

    /* 0x00 */ u8 field_0x0;
    /* 0x01 */ u8 field_0x1;
    /* 0x02 */ u8 field_0x2[10];
    /* 0x0C */ u8 field_0xc;
    /* 0x10 */ int field_0x10;
    /* 0x14 */ int field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1c;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2c;
    /* 0x30 */ dMap_2DMtMapSpcl_c field_0x30;
    /* 0x44 */ dMap_2DMtMapSpcl_tex_c field_0x44[1];
    /* 0x8C */ dMap_2DAGBScrDsp_c field_0x8c;
    /* 0xE4 */ dMap_RoomInfo_c* field_0xe4;
    /* 0xE8 */ void* field_0xe8;
};

class dMap_RoomInfoCtrl_c {
public:
    void roomExistenceCheck(int, dMap_RoomInfo_c**);
    void getNextRoomP(dMap_RoomInfo_c*);
    void ctrlEntryRoom(int, u8, int, u8, s16, s16, f32);
    void deleteRoom(int);
    void ctrlDrawRoomEnlargementSize(int, int, int, int, int, f32, f32, f32, f32, u8);
    void ctrlDrawRoomRealSize(int, int, int, int, int, f32, f32, f32, f32, f32, f32, u8);
    void init();
    void checkFloorMoveImageChangeRoom(u8, u8, int, s16, s16, f32);
};

class dMap_2DSQ_c : public dDlst_base_c {
public:
    ~dMap_2DSQ_c();
    void draw();
};

class dMap_2DTri_c : public dDlst_base_c {
public:
    ~dMap_2DTri_c();
    void init(s16, s16, const GXColor&, f32, f32, s16);
    void draw();
    void setPos(s16, s16);
};

class dMap_2DPoint_c : public dDlst_base_c {
public:
    dMap_2DPoint_c();
    ~dMap_2DPoint_c();
    void init(s16, s16, const GXColor&, u8);
    void draw();
};

class dMap_2DAGBCursor_c : public dDlst_base_c {
public:
    ~dMap_2DAGBCursor_c();
    void init(s16, s16, const GXColor&, u8);
    void draw();
};

class dMap_2DT2_c : public dDlst_base_c {
public:
    dMap_2DT2_c();
    ~dMap_2DT2_c();
    void draw();
    void init(ResTIMG*, f32, f32, f32, f32, u8, u8, u8, f32, f32, s16);
};

class dMap_Dmap_c : public dDlst_base_c {
public:
    ~dMap_Dmap_c();
    void setTlut(dmap_dmap_tlut_s*, u8, u8, u8, f32);
    void setFloorTextureOne(u8);
    void init(s16, s16, s16, s16, s16, s16, s16, s16, s16, u8, u8, u8, u8, u8);
    void draw();
};

class dMap_c {
public:
    static u8 getMapAlpha() { return mAlpha; }
    static void setMapAlpha(u8 alpha) { mAlpha = alpha; }
    static void setIconFreeAlpha(u8 alpha) { mIconFreeAlpha = alpha; }
    static void setMapDispMode(u8 mode) { mMapDispMode = mode; }
    static s16 getMapDspPosLeftUpX() { return mDispPosLeftUpX; }
    static void setMapDispPosLeftUpX(s16 x) { mDispPosLeftUpX = x; }
    static s16 getMapDspPosLeftUpY() { return mDispPosLeftUpY; }
    static void setMapDispPosLeftUpY(s16 y) { mDispPosLeftUpY = y; }
    static void setIconFreePosX(s16 x) { mIconFreePosX = x; }
    static void setIconFreePosY(s16 y) { mIconFreePosY = y; }
    static void setIconFreeScale(f32 scale) { mIconFreeScale = scale; }
    static void setIconSelfAlpha(u8 alpha) { mIconSelfAlpha = alpha; }
    static void setIconSelfScale(f32 scale) { mIconSelfScale = scale; }
    static u8 getIconDispMode() { return mIconDispMode; }
    static void setIconDispMode(u8 mode) { mIconDispMode = mode; }

    static void setAGBMapSendStopFlg() { mAGBMapSendStopFlg = true; }
    static void clrAGBMapSendStopFlg() { mAGBMapSendStopFlg = false; }
    static bool isAGBMapSendStopFlg() { return mAGBMapSendStopFlg; }
    static void getMapDspSizeHeight() {}
    static void getMapDspSizeWidth() {}
    static void getNowRoom() {}
    static void isMapDispTypeEnlargementSize() {}
    static void isMapDispTypeRealSize() {}
    static void setMapChgSizeEnlargementSize() {}
    static void setMapChgSizeRealSize() {}

    static void create();
    static void isEnableEnlargementScroll();
    static bool isEnableDispMap();
    static void getKindMapType();
    static void remove();
    static void setImage(int, int, f32);
    static void deleteImage(int);
    static void setNowRoom(int);
    static void mapDrawIconFree(s16, s16, u8);
    static void mapDrawIconSelf(s16, s16, u8);
    static void mapDrawFrame(u8);
    static void mapDrawEnlargementSize(f32, f32, f32, f32, u8);
    static void mapDrawRealSize(f32, f32, u8);
    static void mapAGBSendIslandData();
    static void setPlayerStayAgbMapTypeNow(f32, f32);
    static void agbMapNoSet(u8, u8);
    static void agbMapNoSetCall();
    static void agbIsMsgSend();
    static void agbResetCursor();
    static void agbScrollX();
    static void agbScrollY();
    static void agbFlashCheck();
    static void agbIsActive();
    static void isInDspArea(f32, f32, bool);
    static void mapAGBSendStatInit();
    static void mapAGBSendMapMain(f32, f32);
    static void calcEnlargementSizeParameter(f32, f32);
    static void calcScissor();
    static void mapMoveAll(f32, f32, int, f32);
    static void mapDrawAll(f32, f32, int, f32);
    static void mapDrawIcon();
    static void draw(f32, f32, int, f32);
    static void point2Grid(f32, f32, s8*, s8*);
    static void point2GridAndLocal(f32, f32, s8*, s8*, s16*, s16*);
    static void getCheckPointUseGrid(s8, s8);
    static void getFmapChkPntPrm(int, s8*, s8*, s16*, s16*, u8*);
    static void setFmapChkDtPrm();
    static void getFmapChkPntDtPnt(int);
    static void initPoint();
    static void setGbaPoint_ocean(u8, f32, f32, s16, u8, u8, u8, u8);
    static void isPointStayInDspNowRoomAgbScr(s16, s16);
    static void setCollectPoint(u8, u8, f32, f32, f32, s8, s16, u8, u8, u8, u8);
    static void setGbaPoint_dungeon(u8, f32, f32, s16, u8, u8, u8, u8);
    static void getPosAgbMapType(f32, f32, bool);
    static void setGbaPoint(u8, f32, f32, s16, u8, u8, u8, u8);
    static void setArriveInfo(f32, f32);
    static void drawPointPlayer(f32, f32, s16);
    static void drawPointEnemy(f32, f32);
    static void drawPointAgbCursor(f32, f32);
    static void drawPointTbox(f32, f32, f32, f32);
    static void drawPointDoor(f32, f32, f32, f32, s16, u8);
    static void drawPointRestart(f32, f32, s16, f32, f32);
    static void drawPointFriend(f32, f32, f32);
    static void drawPointShip(f32, f32, s16, f32, f32);
    static void drawPointGc(u8, f32, f32, f32, s8, s16, u8, u8, u8, u8);
    static void drawPointMain(u8, u8, f32, f32, f32, s8, s16, u8, u8, u8, u8);
    static void drawPointAgb(u8, f32, f32, f32, s8, s16, u8, u8, u8, u8);
    static void getTypeAgbGcFromTypeAcs(u8, u8*, u8*);
    static void drawPointSingle(u8, f32, f32, f32, s8, s16, u8, u8, u8);
    static void drawActorPointMiniMap(fopAc_ac_c*);
    static void mapBufferSendAGB_commonCursor();
    static void mapBufferSendAGB_ocean();
    static void mapBufferSendAGB_dungeon();
    static void mapSetPointAll();
    static void mapBufferSendAGB(int);

    static u8 mAlpha;
    static u8 mIconFreeAlpha;
    static u8 mMapDispMode;
    static u16 mDispPosLeftUpX;
    static u16 mDispPosLeftUpY;
    static u16 mIconFreePosX;
    static u16 mIconFreePosY;
    static f32 mIconFreeScale;
    static u8 mIconSelfAlpha;
    static f32 mIconSelfScale;
    static u8 mIconDispMode;
    static bool mAGBMapSendStopFlg;
};

inline void dMap_drawPoint(u8 param_1, f32 param_2, f32 param_3, f32 param_4, s8 param_5, s16 param_6, u8 param_7, u8 param_8, u8 param_9) {
    dMap_c::drawPointSingle(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8, param_9);
}
inline void dMap_drawActorPointMiniMap(fopAc_ac_c* actor) { dMap_c::drawActorPointMiniMap(actor); }
inline bool dMap_isEnableDispMap() { return dMap_c::isEnableDispMap(); }
inline void dMap_mapAGBSendIslandData() { dMap_c::mapAGBSendIslandData(); }

inline u8 dMap_getMapAlpha() { return dMap_c::getMapAlpha(); }
inline void dMap_setMapAlpha(u8 alpha) { return dMap_c::setMapAlpha(alpha); }
inline void dMap_setIconFreeAlpha(u8 alpha) { return dMap_c::setIconFreeAlpha(alpha); }
inline void dMap_setMapDispMode(u8 mode) { return dMap_c::setMapDispMode(mode); }
inline s16 dMap_getMapDispPosLeftUpX() { return dMap_c::getMapDspPosLeftUpX(); }
inline void dMap_setMapDispPosLeftUpX(s16 x) { return dMap_c::setMapDispPosLeftUpX(x); }
inline s16 dMap_getMapDispPosLeftUpY() { return dMap_c::getMapDspPosLeftUpY(); }
inline void dMap_setMapDispPosLeftUpY(s16 y) { return dMap_c::setMapDispPosLeftUpY(y); }
inline void dMap_setIconFreePosX(s16 x) { return dMap_c::setIconFreePosX(x); }
inline void dMap_setIconFreePosY(s16 y) { return dMap_c::setIconFreePosY(y); }
inline void dMap_setIconFreeScale(f32 scale) { return dMap_c::setIconFreeScale(scale); }
inline void dMap_setIconSelfAlpha(u8 alpha) { return dMap_c::setIconSelfAlpha(alpha); }
inline void dMap_setIconSelfScale(f32 scale) { return dMap_c::setIconSelfScale(scale); }
inline void dMap_setIconDispMode(u8 mode) { return dMap_c::setIconDispMode(mode); }

inline void dMap_getCheckPointUseGrid(s8, s8) {}
inline void dMap_getFmapChkPntPrm(int, s8*, s8*, s16*, s16*, u8*) {}
inline void dMap_getMapDispSizeHeight() {}
inline void dMap_getMapDispSizeWidth() {}
inline void dMap_isSaveArriveGridUseGridNo(int) {}
inline void dMap_isSaveArriveGridUseGridPos(int, int) {}
inline void dMap_isSaveArriveGrid_UseWorldPos(f32, f32) {}
inline void dMap_onSaveArriveGridUseGridNo(int) {}
inline void dMap_point2Grid(f32, f32, s8*, s8*) {}

#endif /* D_MAP_H */
