#ifndef D_MAP_H
#define D_MAP_H

#include "dolphin/types.h"

class fopAc_ac_c;

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