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
    void init(ResTIMG*, u32, const _GXColor&);
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
    /* 0x0C */ short field_0xc;
    /* 0x0E */ short field_0xe;
    /* 0x10 */ short field_0x10;
    /* 0x12 */ short field_0x12;
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
    void init(s16, s16, const _GXColor&, f32, f32, s16);
    void draw();
    void setPos(s16, s16);
};

class dMap_2DPoint_c : public dDlst_base_c {
public:
    dMap_2DPoint_c();
    ~dMap_2DPoint_c();
    void init(s16, s16, const _GXColor&, u8);
    void draw();
};

class dMap_2DAGBCursor_c : public dDlst_base_c {
public:
    ~dMap_2DAGBCursor_c();
    void init(s16, s16, const _GXColor&, u8);
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
    void clrAGBMapSendStopFlg() {}
    void getIconDispMode() {}
    void getMapAlpha() {}
    void getMapDspPosLeftUpX() {}
    void getMapDspPosLeftUpY() {}
    void getMapDspSizeHeight() {}
    void getMapDspSizeWidth() {}
    void getNowRoom() {}
    void isAGBMapSendStopFlg() {}
    void isMapDispTypeEnlargementSize() {}
    void isMapDispTypeRealSize() {}
    void setAGBMapSendStopFlg() {}
    void setIconDispMode(u8) {}
    void setIconFreeAlpha(u8) {}
    void setIconFreePosX(s16) {}
    void setIconFreePosY(s16) {}
    void setIconFreeScale(f32) {}
    void setIconSelfAlpha(u8) {}
    void setIconSelfScale(f32) {}
    void setMapAlpha(u8) {}
    void setMapChgSizeEnlargementSize() {}
    void setMapChgSizeRealSize() {}
    void setMapDispMode(u8) {}
    void setMapDispPosLeftUpX(s16) {}
    void setMapDispPosLeftUpY(s16) {}

    static void create();
    void isEnableEnlargementScroll();
    static bool isEnableDispMap();
    void getKindMapType();
    static void remove();
    static void setImage(int, int, f32);
    static void deleteImage(int);
    void setNowRoom(int);
    void mapDrawIconFree(s16, s16, u8);
    void mapDrawIconSelf(s16, s16, u8);
    void mapDrawFrame(u8);
    void mapDrawEnlargementSize(f32, f32, f32, f32, u8);
    void mapDrawRealSize(f32, f32, u8);
    static void mapAGBSendIslandData();
    void setPlayerStayAgbMapTypeNow(f32, f32);
    void agbMapNoSet(u8, u8);
    void agbMapNoSetCall();
    void agbIsMsgSend();
    void agbResetCursor();
    void agbScrollX();
    void agbScrollY();
    void agbFlashCheck();
    void agbIsActive();
    void isInDspArea(f32, f32, bool);
    void mapAGBSendStatInit();
    void mapAGBSendMapMain(f32, f32);
    void calcEnlargementSizeParameter(f32, f32);
    void calcScissor();
    void mapMoveAll(f32, f32, int, f32);
    void mapDrawAll(f32, f32, int, f32);
    void mapDrawIcon();
    void draw(f32, f32, int, f32);
    void point2Grid(f32, f32, s8*, s8*);
    void point2GridAndLocal(f32, f32, s8*, s8*, s16*, s16*);
    void getCheckPointUseGrid(s8, s8);
    void getFmapChkPntPrm(int, s8*, s8*, s16*, s16*, u8*);
    void setFmapChkDtPrm();
    void getFmapChkPntDtPnt(int);
    void initPoint();
    void setGbaPoint_ocean(u8, f32, f32, s16, u8, u8, u8, u8);
    void isPointStayInDspNowRoomAgbScr(s16, s16);
    void setCollectPoint(u8, u8, f32, f32, f32, s8, s16, u8, u8, u8, u8);
    void setGbaPoint_dungeon(u8, f32, f32, s16, u8, u8, u8, u8);
    void getPosAgbMapType(f32, f32, bool);
    void setGbaPoint(u8, f32, f32, s16, u8, u8, u8, u8);
    void setArriveInfo(f32, f32);
    void drawPointPlayer(f32, f32, s16);
    void drawPointEnemy(f32, f32);
    void drawPointAgbCursor(f32, f32);
    void drawPointTbox(f32, f32, f32, f32);
    void drawPointDoor(f32, f32, f32, f32, s16, u8);
    void drawPointRestart(f32, f32, s16, f32, f32);
    void drawPointFriend(f32, f32, f32);
    void drawPointShip(f32, f32, s16, f32, f32);
    void drawPointGc(u8, f32, f32, f32, s8, s16, u8, u8, u8, u8);
    void drawPointMain(u8, u8, f32, f32, f32, s8, s16, u8, u8, u8, u8);
    void drawPointAgb(u8, f32, f32, f32, s8, s16, u8, u8, u8, u8);
    void getTypeAgbGcFromTypeAcs(u8, u8*, u8*);
    static void drawPointSingle(u8, f32, f32, f32, s8, s16, u8, u8, u8);
    static void drawActorPointMiniMap(fopAc_ac_c*);
    void mapBufferSendAGB_commonCursor();
    void mapBufferSendAGB_ocean();
    void mapBufferSendAGB_dungeon();
    void mapSetPointAll();
    static void mapBufferSendAGB(int);
};

inline void dMap_drawPoint(u8 param_1, f32 param_2, f32 param_3, f32 param_4, s8 param_5, s16 param_6, u8 param_7, u8 param_8, u8 param_9) {
    dMap_c::drawPointSingle(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8, param_9);
}

#endif /* D_MAP_H */
