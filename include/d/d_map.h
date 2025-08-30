#ifndef D_MAP_H
#define D_MAP_H

#include "d/d_drawlist.h"
#include "JSystem/JUtility/JUTAssert.h"

struct ResTIMG;
struct dmap_dmap_tlut_s;
class fopAc_ac_c;
struct stage_map_info_class;

const int AGB_POINT_TYPE_NUM = 21;
const int DSP_ENABLE_BOTH_SIZE = 3;

struct map_dt_c {
    u16 field_0x0;
    u16 field_0x2;
    u8 field_0x4[0x6 - 0x4];
    u8 field_0x6;
    u8 field_0x7[0xC - 0x7];
    int field_0xc;
    u8 field_0x10[0x32 - 0x10];
    u8 field_0x32;
    u8 field_0x33[0x38 - 0x33];
    int field_0x38;
};

// fake name
struct dMap_CollectPoint {
    f32 field_0x0;
    f32 field_0x4;
    f32 field_0x8;
    s16 field_0xc;
    u8 field_0xe;
    u8 field_0xf;
    u8 field_0x10;
    u8 field_0x11;
    u8 field_0x12;
    u8 field_0x13;
    u8 field_0x14;
    u8 field_0x15;
    u8 field_0x16;
    u8 field_0x17;
};

class dMap_2DMtMapSpcl_tex_c {
public:
    dMap_2DMtMapSpcl_tex_c() {}
    ~dMap_2DMtMapSpcl_tex_c() {}
    void init(ResTIMG*, u32, const GXColor&);
    void setScroll(f32, f32, f32, f32);

    /* 0x00 */ u8 field_0x0;
    /* 0x01 */ u8 field_0x1;
    /* 0x04 */ GXTexObj field_0x4;
    /* 0x24 */ GXTlutObj field_0x24;
    /* 0x30 */ GXColor field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3c;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ u32 field_0x44;
};

class dMap_2DMtMapSpcl_c : public dDlst_base_c {
public:
    virtual ~dMap_2DMtMapSpcl_c() {}
    void init(int, dMap_2DMtMapSpcl_tex_c*);
    void setPos(s16, s16, s16, s16);
    virtual void draw();

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
    virtual ~dMap_2DAGBScrDsp_c() {}
    void setImage(ResTIMG*, map_dt_c*);
    void init(map_dt_c*, ResTIMG*, f32, f32, s16, s16, s16, s16, f32, f32, u8);
    void getScrnPrm(f32, f32, int, f32, int*, f32*, f32*);
    void getScrnPrmXY(f32, f32, f32, f32, int, int, f32, f32, int*, int*, f32*, f32*, f32*, f32*);
    void calc_standard_prm(u16, u16, f32, f32, s16, s16, s16, s16, f32, f32, int*, int*, int*, int*, f32*, f32*, f32*, f32*, f32*, f32*);
    virtual void draw();
    void setPos(s16, s16, s16, s16);
    void setScale(f32, f32);

    /* 0x04 */ map_dt_c* field_0x4;
    /* 0x08 */ ResTIMG* mImg;
    /* 0x0C */ GXTexObj field_0xc;
    /* 0x2C */ GXTlutObj field_0x2c;
    /* 0x38 */ int field_0x38;
    /* 0x3C */ s16 field_0x3c;
    /* 0x3E */ s16 field_0x3e;
    /* 0x40 */ s16 field_0x40;
    /* 0x42 */ s16 field_0x42;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 mScaleX;
    /* 0x50 */ f32 mScaleY;
    /* 0x54 */ u8 field_0x54;
};

class dMap_RoomInfo_c {
public:
    dMap_RoomInfo_c() {}
    ~dMap_RoomInfo_c() {}
    u8 getRoomDspFloorNo(u8, int);
    dMap_RoomInfo_c* init(dMap_RoomInfo_c*, int);
    u8 getRoomImage(int, u8, int, ResTIMG**, ResTIMG**, map_dt_c**, stage_map_info_class**, u8*);
    BOOL makeRoomDspFloorNoTbl(int);
    dMap_RoomInfo_c* roomEntryRoom(int, u8, int, u8, dMap_RoomInfo_c*, s16, s16, f32);
    BOOL Changeimage(u8, u8, int, s16, s16, f32);
    BOOL deleteRoom();
    bool enlagementSizeTextureCordCalc(f32*, f32*, f32*, f32*, f32, f32, f32, f32, f32, f32);
    void roomDrawRoomEnlargementSize(int, int, int, int, f32, f32, f32, f32, u8);
    void roomDrawRoomRealSize(int, int, int, int, f32, f32, f32, f32, f32, f32, u8);

    void clrUseRoom() {}
    void setUseRoom() {}
    void checkUseRoom() {}
    void getStageMapInfoPE() {}
    void getStageMapInfoCmPDot() {}
    void getStageMapInfoMap0_X0() {}
    void getStageMapInfoMap0_X1() {}
    void getStageMapInfoMap0_Z0() {}
    void getStageMapInfoMap0_Z1() {}
    void getStageMapInfoMap0_XC() {}
    void getStageMapInfoMap0_ZC() {}
    void getStageMapInfoMap1_X0() {}
    void getStageMapInfoMap1_X1() {}
    void getStageMapInfoMap1_Z0() {}
    void getStageMapInfoMap1_Z1() {}
    void getStageMapInfoMap1_ZC() {}
    void getStageMapInfoMap1_XC() {}
    void getStageMapInfoAlpha() {}
    void getMapDtP() {}
    void getNowDspFloorNo() {}
    void getMapDtSize() {}
    void getMap0ScaleX() {}
    void getMap0ScaleZ() {}
    void getMap1ScaleX() {}
    void getMap1ScaleZ() {}
    void getMap1Width() {}
    void getMap1Height() {}

    u8 getEnableFlg() { return field_0x1; }
    int getRoomNo() { return m_no; }
    stage_map_info_class* getStageMapInfoP() { JUT_ASSERT(1127, mStageMapInfoP != NULL); return mStageMapInfoP; }
    dMap_RoomInfo_c* getNextRoomInfoP() { return m_next; }

    /* 0x00 */ u8 m_exist;
    /* 0x01 */ u8 field_0x1;
    /* 0x02 */ u8 field_0x2[10];
    /* 0x0C */ u8 field_0xc;
    /* 0x10 */ int m_no;
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
    /* 0xE4 */ dMap_RoomInfo_c* m_next;
    /* 0xE8 */ stage_map_info_class* mStageMapInfoP;
};

class dMap_RoomInfoCtrl_c {
public:
    bool roomExistenceCheck(int, dMap_RoomInfo_c**);
    dMap_RoomInfo_c* getNextRoomP(dMap_RoomInfo_c*);
    dMap_RoomInfo_c* ctrlEntryRoom(int, u8, int, u8, s16, s16, f32);
    bool deleteRoom(int);
    void ctrlDrawRoomEnlargementSize(int, int, int, int, int, f32, f32, f32, f32, u8);
    void ctrlDrawRoomRealSize(int, int, int, int, int, f32, f32, f32, f32, f32, f32, u8);
    void init();
    void checkFloorMoveImageChangeRoom(u8, u8, int, s16, s16, f32);

public:
    /* 0x00 */ s32 m_num;
    /* 0x04 */ dMap_RoomInfo_c *m_info;
};

class dMap_2DSQ_c : public dDlst_base_c {
public:
    virtual ~dMap_2DSQ_c() {}
    virtual void draw();

    /* 0x04 */ int field_0x4;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ int field_0xc;
    /* 0x10 */ int field_0x10;
    /* 0x14 */ u8 field_0x14;
    /* 0x18 */ int field_0x18;
    /* 0x1C */ GXColor field_0x1c;
};

class dMap_2DTri_c : public dDlst_base_c {
public:
    virtual ~dMap_2DTri_c() {}
    void init(s16, s16, const GXColor&, f32, f32, s16);
    virtual void draw();
    void setPos(s16, s16);

    void setAlpha(u8 alpha) { mColor.a = alpha; }
    void setAngle(s16 angle) { mAngle = angle; }
    void setScaleX(f32 scaleX) { mScaleX = scaleX; }
    void setScaleY(f32 scaleY) { mScaleY = scaleY; }
    void setScissor(u32 x, u32 y, u32 width, u32 height) {
        mScissorX = x;
        mScissorY = y;
        mScissorWidth = width;
        mScissorHeight = height;
    }

    /* 0x04 */ s16 mPosX;
    /* 0x06 */ s16 mPosY;
    /* 0x08 */ GXColor mColor;
    /* 0x0C */ s16 mAngle;
    /* 0x10 */ f32 mScaleX;
    /* 0x14 */ f32 mScaleY;
    /* 0x18 */ u32 mScissorX;
    /* 0x1C */ u32 mScissorY;
    /* 0x20 */ u32 mScissorWidth;
    /* 0x24 */ u32 mScissorHeight;
};

class dMap_2DPoint_c : public dDlst_base_c {
public:
    virtual ~dMap_2DPoint_c() {}
    void init(s16, s16, const GXColor&, u8);
    virtual void draw();

    void setScissor(u32 x, u32 y, u32 width, u32 height) {
        field_0x4 = x;
        field_0x8 = y;
        field_0xc = width;
        field_0x10 = height;
    }

    /* 0x04 */ u32 field_0x4;
    /* 0x08 */ u32 field_0x8;
    /* 0x0C */ u32 field_0xc;
    /* 0x10 */ u32 field_0x10;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ GXColor field_0x18;
    /* 0x1C */ u8 field_0x1c;
};

class dMap_2DAGBCursor_c : public dDlst_base_c {
public:
    virtual ~dMap_2DAGBCursor_c() {}
    void init(s16, s16, const GXColor&, u8);
    virtual void draw();

    void setScissor(u32 x, u32 y, u32 width, u32 height) {
        mScissorX = x;
        mScissorY = y;
        mScissorWidth = width;
        mScissorHeight = height;
    }

    /* 0x04 */ u32 mScissorX;
    /* 0x08 */ u32 mScissorY;
    /* 0x0C */ u32 mScissorWidth;
    /* 0x10 */ u32 mScissorHeight;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ GXColor field_0x18;
    /* 0x1C */ u8 field_0x1c;
};

class dMap_2DT2_c : public dDlst_base_c {
public:
    virtual ~dMap_2DT2_c() {}
    virtual void draw();
    void init(ResTIMG*, f32, f32, f32, f32, u8, u8, u8, f32, f32, s16);

    void setPos(f32 x, f32 y) {
        mPosX = x;
        mPosY = y;
    }
    void setWide(f32 width) { mWidth = width; }
    void setHeight(f32 height) { mHeight = height; }
    void setScaleX(f32 scaleX) { mScaleX = scaleX; }
    void setScaleY(f32 scaleY) { mScaleY = scaleY; }
    void setColorW(GXColor color) { mColorW = color; }
    void setColorB(GXColor color) { mColorB = color; }
    void setScissor(u32 x, u32 y, u32 width, u32 height) {
        mScissorX = x;
        mScissorY = y;
        mScissorWidth = width;
        mScissorHeight = height;
    }
    void setRotZ(s16 rotz) { mRotZ = rotz; }

    /* 0x04 */ GXTexObj field_0x4;
    /* 0x24 */ f32 mPosX;
    /* 0x28 */ f32 mPosY;
    /* 0x2C */ f32 mWidth;
    /* 0x30 */ f32 mHeight;
    /* 0x34 */ f32 mScaleX;
    /* 0x38 */ f32 mScaleY;
    /* 0x3C */ GXColor mColorW;
    /* 0x40 */ GXColor mColorB;
    /* 0x44 */ u32 mScissorX;
    /* 0x48 */ u32 mScissorY;
    /* 0x4C */ u32 mScissorWidth;
    /* 0x50 */ u32 mScissorHeight;
    /* 0x54 */ s16 mRotZ;
    /* 0x56 */ u8 field_0x56;
    /* 0x57 */ u8 field_0x57;
    /* 0x58 */ u8 field_0x58;
};

class dMap_Dmap_c : public dDlst_base_c {
public:
    virtual ~dMap_Dmap_c() {}
    void setTlut(dmap_dmap_tlut_s*, u8, u8, u8, f32);
    void setFloorTextureOne(u8);
    void init(s16, s16, s16, s16, s16, s16, s16, s16, s16, u8, u8, u8, u8, u8);
    virtual void draw();
};

class dMap_c {
public:
    static u8 getMapAlpha() { return mAlpha; }
    static void setMapAlpha(u8 alpha) { mAlpha = alpha; }
    static void setMapDispMode(u8 mode) { mMapDispMode = mode; }
    static u8 getIconDispMode() { return mIconDispMode; }
    static void setIconDispMode(u8 mode) { mIconDispMode = mode; }
    static void setIconFreeAlpha(u8 alpha) { mIconFreeAlpha = alpha; }
    static void setIconSelfAlpha(u8 alpha) { mIconSelfAlpha = alpha; }
    static bool isAGBMapSendStopFlg() { return mAGBMapSendStopFlg; }
    static void setAGBMapSendStopFlg() { mAGBMapSendStopFlg = true; }
    static void clrAGBMapSendStopFlg() { mAGBMapSendStopFlg = false; }
    static void setIconFreePosX(s16 x) { mIconFreePosX = x; }
    static void setIconFreePosY(s16 y) { mIconFreePosY = y; }
    static s16 getMapDspPosLeftUpX() { return mDispPosLeftUpX; }
    static void setMapDispPosLeftUpX(s16 x) { mDispPosLeftUpX = x; }
    static s16 getMapDspPosLeftUpY() { return mDispPosLeftUpY; }
    static void setMapDispPosLeftUpY(s16 y) { mDispPosLeftUpY = y; }
    static void setIconFreeScale(f32 scale) { mIconFreeScale = scale; }
    static void setIconSelfScale(f32 scale) { mIconSelfScale = scale; }

    static void getMapDspSizeHeight() {}
    static void getMapDspSizeWidth() {}
    static void getNowRoom() {}
    static void isMapDispTypeEnlargementSize() {}
    static void isMapDispTypeRealSize() {}
    static void setMapChgSizeEnlargementSize() {}
    static void setMapChgSizeRealSize() {}

    static void create();
    static BOOL isEnableEnlargementScroll();
    static bool isEnableDispMap();
    static int getKindMapType();
    static void remove();
    static void setImage(int, int, f32);
    static void deleteImage(int);
    static BOOL setNowRoom(int);
    static void mapDrawIconFree(s16, s16, u8);
    static void mapDrawIconSelf(s16, s16, u8);
    static void mapDrawFrame(u8);
    static void mapDrawEnlargementSize(f32, f32, f32, f32, u8);
    static void mapDrawRealSize(f32, f32, u8);
    static void mapAGBSendIslandData();
    static void setPlayerStayAgbMapTypeNow(f32, f32);
    static void agbMapNoSet(u8, u8);
    static void agbMapNoSetCall();
    static BOOL agbIsMsgSend();
    static void agbResetCursor();
    static u16 agbScrollX();
    static u16 agbScrollY();
    static BOOL agbFlashCheck();
    static BOOL agbIsActive();
    static BOOL isInDspArea(f32, f32, bool);
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
    static BOOL isPointStayInDspNowRoomAgbScr(s16, s16);
    static void setCollectPoint(u8, u8, f32, f32, f32, s8, s16, u8, u8, u8, u8);
    static void setGbaPoint_dungeon(u8, f32, f32, s16, u8, u8, u8, u8);
    static u8 getPosAgbMapType(f32, f32, bool);
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

    static u8 mAgbSendBuf[];
    static u8 mAgbSendBufIsland[];
    static dMap_RoomInfo_c mRoomInfo[];
    static dMap_2DMtMapSpcl_c mFrameTex[];
    static dMap_2DMtMapSpcl_tex_c mFrameTexture[];
    static dMap_2DMtMapSpcl_c mIconFreeTex;
    static dMap_2DMtMapSpcl_tex_c mIconFreeTexture;
    static dMap_2DMtMapSpcl_c mIconSelfTex;
    static dMap_2DMtMapSpcl_tex_c mIconSelfTexture;
    static dMap_2DTri_c mCursor;
    static dMap_2DAGBCursor_c mAgbCursor;
    static dMap_2DPoint_c mPoint[];
    static dMap_2DSQ_c m2DSQdraw;
    static dMap_2DSQ_c m2DSQdraw2;
    static dMap_2DT2_c mTbox[];
    static dMap_2DT2_c mDoor[];
    static dMap_2DTri_c mPointRestart;
    static dMap_2DPoint_c mPointFriend[];
    static dMap_2DT2_c mShip;
    static dMap_CollectPoint mCollectPointData[];
    static s8 mCollectPointDataLinkList[];

    static u8 mCompAlpha;
    static u8 mAlpha;
    static u8 mDrawPointCntPlayer;
    static u8 mDrawPointCntEnemy;
    static u8 mDrawPointCntAgbCursor;
    static u8 mTboxNum;
    static u8 mDoorNum;
    static u8 mPointFriendNum;
    static u8 mDrawPointCntShip;
    static u8 mDrawPointRestartCnt;
    static u8 mCollectPointDataCnt;
    static u8 mAGBMapSendStatus;
    static u8 mSetCursorFlg;
    static u8 mMapDispMode;
    static u8 mIconDispMode;
    static u8 mIconFreeAlpha;
    static u8 mIconSelfAlpha;
    static bool mAGBMapSendStopFlg;
    static u8 mMapAGBCursorFlashFrmCnt;
    static u8 mPlayerStayAgbMapTypeNow;
    static u8 mPlayerStayAgbMapTypeOld;
    static s8 mPlGridX;
    static s8 mPlGridY;
    static s8 mPlGridX_Old;
    static s8 mPlGridY_Old;
    static u8 mNowFloorNo;
    static s16 mIconFreePosX;
    static s16 mIconFreePosY;
    static u16 mAGBPointValueC;
    static u16 mAGBPointValueE;
    static u16 mAGBPointValueAll;
    static u16 mAGBPointValueRoomAll;
    static char mAgbSendNowStageName[8];
    static int mAgbSendNowRoomNo;
    static s16 mAgbSendNowDspFloorNo;
    static u8 mAgbSendNowAgbMapType;
    static f32 mEnlargementSizeCenterX;
    static f32 mEnlargementSizeCenterZ;
    static f32 mEnlargementSizeScaleX;
    static f32 mEnlargementSizeScaleZ;
    static u8 mFmapChkPntValue;
    static int mFmapChkPntData_p;
    static s16 mDispPosLeftUpX;
    static s16 mDispPosLeftUpY;
    static s16 mDispSizeX;
    static s16 mDispSizeY;
    static int mScissorOrigY;
    static int mScissorOrigX;
    static int mScissorWidth;
    static int mScissorHeight;
    static f32 mIconFreeScale;
    static f32 mIconSelfScale;
    static f32 mNowCenterX;
    static f32 mNowCenterZ;
    static f32 mNowScaleX;
    static f32 mNowScaleZ;
    // static ? mGbaSendMapOceanDt;
    static dMap_RoomInfoCtrl_c mRoomInfoCtrl;
    static dMap_RoomInfo_c* mNowRoomInfoP;
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
