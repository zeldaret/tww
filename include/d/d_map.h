#ifndef D_MAP_H
#define D_MAP_H

class fopAc_ac_c;
class dMap_c {
public:
    static void create();
    void isEnableEnlargementScroll();
    void isEnableDispMap();
    void getKindMapType();
    static void remove();
    void setImage(int, int, f32);
    void deleteImage(int);
    void setNowRoom(int);
    void mapDrawIconFree(s16, s16, u8);
    void mapDrawIconSelf(s16, s16, u8);
    void mapDrawFrame(u8);
    void mapDrawEnlargementSize(f32, f32, f32, f32, u8);
    void mapDrawRealSize(f32, f32, u8);
    void mapAGBSendIslandData();
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
    void drawPointSingle(u8, f32, f32, f32, s8, s16, u8, u8, u8);
    void drawActorPointMiniMap(fopAc_ac_c*);
    void mapBufferSendAGB_commonCursor();
    void mapBufferSendAGB_ocean();
    void mapBufferSendAGB_dungeon();
    void mapSetPointAll();
    static void mapBufferSendAGB(int);
};

#endif /* D_MAP_H */