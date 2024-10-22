//
// Generated by dtk
// Translation Unit: d_magma.cpp
//

#include "d/d_magma.h"
#include "d/d_com_inf_game.h"
#include "d/d_path.h"
#include "d/res/res_magma.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_lib.h"

// #pragma sym on

#include "weak_bss_3569.h" // IWYU pragma: keep
#include "weak_data_2100_2080.h" // IWYU pragma: keep

Mtx l_kuroOrthoMtx;
Mtx l_colOrthoMtx;
GXTexObj dMagma_packet_c::mKuroTexObj;
Mtx dMagma_packet_c::mKuroMtx;
GXTexObj dMagma_packet_c::mColTexObj;
Mtx dMagma_packet_c::mFloorMtx;
Mtx dMagma_packet_c::mBallMtx;

Vec l_YfloorPos[] = {
    { -500.0f, -0.0f, 500.0f },
    { 500.0f, -0.0f, 500.0f },
    { -500.0f, 0.0f, -500.0f },
    { 500.0f, 0.0f, -500.0f },
};

u8 l_YfloorDL[] ALIGN_DECL(32) = {
    0x98, 0x00, 0x04, 0x01, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

u8 l_YfloorMatDL[] ALIGN_DECL(32) = {
    0x61, 0xC0, 0x08, 0xF4, 0x8F, 0x61, 0xC1, 0x08, 0x9F, 0xF0, 0x61, 0x43, 0x00, 0x00, 0x01, 0x61,
    0x40, 0x00, 0x00, 0x07, 0x61, 0x41, 0x00, 0x01, 0x0C, 0x61, 0xF3, 0x64, 0x80, 0x80, 0x10, 0x00,
    0x00, 0x10, 0x3F, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x10, 0x09, 0x00, 0x00, 0x00, 0x00,
    0x61, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
};

Vec l_YballPos[] = {
    {172.280487f, -7.398514f, -167.445663f},
    {0.000006f, -7.398514f, -236.803879f},
    {-172.280487f, -7.398515f, -167.445648f},
    {-243.641357f, -7.398515f, 0.000004f},
    {-172.280487f, -7.398514f, 167.445602f},
    {0.000008f, -7.398514f, 236.803879f},
    {172.280487f, -7.398514f, 167.445602f},
    {243.641403f, -7.398514f, -0.000015f},
    {150.773376f, 13.801255f, -149.81015f},
    {0.000006f, 13.801253f, -211.863525f},
    {-150.773346f, 13.801253f, -149.81015f},
    {-213.225739f, 13.801253f, 0.000002f},
    {-150.773346f, 13.801253f, 149.810089f},
    {0.000008f, 13.801253f, 211.86348f},
    {150.773376f, 13.801255f, 149.81012f},
    {213.225739f, 13.801255f, -0.000014f},
    {121.820717f, 31.773548f, -118.401939f},
    {0.000006f, 31.773548f, -167.445648f},
    {-121.820679f, 31.773542f, -118.401939f},
    {-172.280487f, 31.773542f, 0.000001f},
    {-121.820679f, 31.773542f, 118.401939f},
    {0.000007f, 31.773548f, 167.445602f},
    {121.820717f, 31.773548f, 118.401909f},
    {172.280487f, 31.773548f, -0.000012f},
    {65.928886f, 43.782257f, -64.078682f},
    {0.000006f, 43.782257f, -90.620918f},
    {-65.928879f, 43.782257f, -64.078674f},
    {-93.237503f, 43.782257f, -0.000002f},
    {-65.928879f, 43.782257f, 64.078667f},
    {0.000007f, 43.782257f, 90.620911f},
    {65.928886f, 43.782257f, 64.078667f},
    {93.237541f, 43.782257f, -0.000009f},
    {0.000007f, 47.999146f, -0.000006f},
};

u8 l_YballDL[] ALIGN_DECL(32) = {
    0x98, 0x00, 0x12, 0x00, 0x09, 0x01, 0x0A, 0x02, 0x0B, 0x03, 0x0C, 0x04, 0x0D, 0x05, 0x0E, 0x06,
    0x0F, 0x07, 0x08, 0x00, 0x09, 0x98, 0x00, 0x12, 0x0C, 0x15, 0x0D, 0x16, 0x0E, 0x17, 0x0F, 0x10,
    0x08, 0x11, 0x09, 0x12, 0x0A, 0x13, 0x0B, 0x14, 0x0C, 0x15, 0x98, 0x00, 0x12, 0x10, 0x19, 0x11,
    0x1A, 0x12, 0x1B, 0x13, 0x1C, 0x14, 0x1D, 0x15, 0x1E, 0x16, 0x1F, 0x17, 0x18, 0x10, 0x19, 0x98,
    0x00, 0x05, 0x18, 0x1F, 0x20, 0x1E, 0x1D, 0x98, 0x00, 0x05, 0x1D, 0x1C, 0x20, 0x1B, 0x1A, 0x98,
    0x00, 0x04, 0x1A, 0x19, 0x20, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

u8 l_YballMatDL[] ALIGN_DECL(32) = {
    0x61, 0x43, 0x00, 0x00, 0x41, 0x61, 0x40, 0x00, 0x00, 0x17, 0x61, 0x41, 0x00, 0x01, 0x0C, 0x61,
    0xF3, 0x7F, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x3F, 0x00, 0x00, 0x00, 0x02, 0x10, 0x00, 0x00,
    0x10, 0x09, 0x00, 0x00, 0x00, 0x00, 0x61, 0x00, 0x00, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/* 800755A4-800756B8       .text draw__13dMagma_ball_cFv */
void dMagma_ball_c::draw() {
    GXLoadTexMtxImm(mTexProjMtx, GX_TEXMTX2, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX2, GX_FALSE, GX_PTTEXMTX0);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, GXGetTexObjWidth(&dMagma_packet_c::getKuroTexObj()), GXGetTexObjHeight(&dMagma_packet_c::getKuroTexObj()));
    GXSetTexCoordBias(GX_TEXCOORD0, GX_FALSE, GX_FALSE);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX2, GX_FALSE, GX_PTTEXMTX1);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_TRUE, GXGetTexObjWidth(&dMagma_packet_c::getColTexObj()), GXGetTexObjHeight(&dMagma_packet_c::getColTexObj()));
    GXSetTexCoordBias(GX_TEXCOORD1, GX_FALSE, GX_FALSE);
    GXLoadPosMtxImm(mPosMtx, GX_PNMTX0);
    GXCallDisplayList(l_YballDL, 0x60);
}

/* 800756B8-800757D4       .text rangeCheck__13dMagma_ball_cFR4cXyzPf */
BOOL dMagma_ball_c::rangeCheck(cXyz& pos, f32* dst) {
    f32 distSq = mPos.abs2XZ(pos);
    f32 rad1 = mScale * 243.6414f;
    if (distSq < rad1*rad1) {
        f32 rad2 = mScale * 800.0f;
        f32 dist = std::sqrtf(rad2 * rad2 - distSq);
        f32 temp = (mPos.y - (rad2 - 47.999146f));
        temp += dist;
        *dst = temp;
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 800757D4-80075878       .text calc__17dMagma_ballPath_cFfUci */
void dMagma_ballPath_c::calc(f32 offsY, u8 pathNo, int roomNo) {
    if (mWave < 0) {
        setup(offsY, pathNo, roomNo);
        mWaveTimer = 0;
        mWave = 0;
    }

    if (cLib_calcTimer(&mWaveTimer) == 0) {
        mWave += 200;
        mPos.y = mBaseY + (cM_ssin(mWave) - 1.0f) * 100.0f;
    }
}

/* 80075878-800758B4       .text update__17dMagma_ballPath_cFv */
void dMagma_ballPath_c::update() {
    mTexProjMtx[1][3] = mPos.y;
    mDoMtx_concat(j3dSys.getViewMtx(), mTexProjMtx, mPosMtx);
}

/* 800758B4-80075A6C       .text setup__17dMagma_ballPath_cFfUci */
void dMagma_ballPath_c::setup(f32 offsY, u8 pathNo, int roomNo) {
    /* Nonmatching */
    dPath* path = dPath_GetRoomPath(pathNo, roomNo);
    s32 ptNo = (s32)cM_rndF(path->m_num - 1);
    dPath__Point* pt = &path->mpPnt[ptNo];
    mPos.x = pt->mPos.x + cM_rndFX(pt->mArg3 * 100.0f);
    mPos.z = pt->mPos.z + cM_rndFX(pt->mArg3 * 100.0f);
    mScale = cM_rndF(1.0f) + 1.0f;
    mBaseY = offsY - cM_rndF(20.0f);
    mWave = cM_rndF(8.0f) * 4096.0f;
    mPos.y = mBaseY + (cM_ssin(mWave) - 1.0f) * 100.0f;
    mWaveTimer = 0;
    mDoMtx_stack_c::transS(mPos);
    mDoMtx_stack_c::scaleM(mScale, 1.0f, mScale);
    mDoMtx_copy(mDoMtx_stack_c::get(), mTexProjMtx);
}

/* 80075A6C-80075CB8       .text draw__14dMagma_floor_cFv */
void dMagma_floor_c::draw() {
    GXSetArray(GX_VA_POS, l_YfloorPos, sizeof(*l_YfloorPos));
    GXLoadTexMtxImm(mTexMtx0, GX_TEXMTX2, GX_MTX3x4);
    GXLoadTexMtxImm(dMagma_packet_c::getKuroMtx(), (u32)GX_PTTEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX2, GX_FALSE, GX_PTTEXMTX0);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, GXGetTexObjWidth(&dMagma_packet_c::getKuroTexObj()), GXGetTexObjHeight(&dMagma_packet_c::getKuroTexObj()));
    GXSetTexCoordBias(GX_TEXCOORD0, GX_FALSE, GX_FALSE);
    GXCallDisplayList(&l_YfloorMatDL, 0x40);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXLoadPosMtxImm(mPosMtx, GX_PNMTX0);
    GXCallDisplayList(&l_YfloorDL, 0x20);
    GXSetArray(GX_VA_POS, l_YballPos, sizeof(*l_YballPos));
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXA, GX_CC_HALF, GX_CC_ONE, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_COMP_RGB8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_TEXC, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXCallDisplayList(l_YballMatDL, 0x40);
    GXLoadTexMtxImm(mPostMtx0, (u32)GX_PTTEXMTX1, GX_MTX3x4);

    dMagma_ball_c** ball = getBall();
    for (s32 i = 0; i < getBallNum(); ball++, i++)
        (*ball)->draw();
}

/* 80075CB8-80075DD8       .text calc__14dMagma_floor_cFi */
void dMagma_floor_c::calc(int i_roomNo) {
    mDoMtx_stack_c::scaleS(1.0f, 0.05f, 1.0f);
    if (strcmp(dComIfGp_getStartStageName(), "M_DragB") == 0 || strcmp(dComIfGp_getStartStageName(), "Xboss0") == 0)
        mDoMtx_stack_c::transM(0.0f, -(mPos.y + 20.0f), 0.0f);
    else
        mDoMtx_stack_c::transM(0.0f, -(mPos.y + 30.0f), 0.0f);
    mDoMtx_concat(l_colOrthoMtx, mDoMtx_stack_c::get(), mPostMtx0);
    dMagma_ball_c** ball = getBall();
    for (s32 i = 0; i < getBallNum(); ball++, i++)
        (*ball)->calc(mPos.y, mPathNo, i_roomNo);
}

/* 80075DD8-80075E50       .text update__14dMagma_floor_cFv */
void dMagma_floor_c::update() {
    mDoMtx_concat(j3dSys.getViewMtx(), mTexMtx0, mPosMtx);
    dMagma_ball_c** ball = getBall();
    for (s32 i = 0; i < getBallNum(); ball++, i++)
        (*ball)->update();
}

/* 80075E50-80076038       .text create__14dMagma_floor_cFR4cXyzR4cXyzsUci */
dMagma_ball_c** dMagma_floor_c::create(cXyz& pos, cXyz& scale, s16 pathNo, u8 ballNum, int roomNo) {
    mPos.set(pos.x, pos.y + 5.0f, pos.z);

    mpBalls = new dMagma_ball_c*[ballNum];
    if (mpBalls == NULL)
        return NULL;

    mBallNum = ballNum;

    if (pathNo < 0) {
        dMagma_ball_c** ball = mpBalls;
        for (u8 i = 0; i < mBallNum; i++) {
            *ball = new dMagma_ballBoss_c();
            if (*ball == NULL) {
                mBallNum = i;
            } else {
                (*ball)->setup(mPos.y, (int)i, roomNo);
                ball++;
            }
        }
    } else {
        dMagma_ball_c** ball = mpBalls;
        for (u8 i = 0; i < mBallNum; i++) {
            *ball = new dMagma_ballPath_c();
            if (*ball == NULL) {
                mBallNum = i;
            } else {
                (*ball)->setup(mPos.y, pathNo, roomNo);
                ball++;
            }
        }
    }

    mScaleX = scale.x;
    mScaleZ = scale.z;
    mPathNo = pathNo;
    mDoMtx_stack_c::transS(mPos);
    mDoMtx_stack_c::scaleM(mScaleX, 1.0f, mScaleZ);
    mDoMtx_copy(mDoMtx_stack_c::get(), mTexMtx0);
    update();
    return mpBalls;
}

/* 80076080-80076100       .text remove__14dMagma_floor_cFv */
void dMagma_floor_c::remove() {
    dMagma_ball_c** ball = getBall();
    for (s32 i = 0; i < getBallNum(); ball++, i++)
        delete *ball;

    delete mpBalls;
    mpBalls = NULL;
}

/* 80076100-80076110       .text newFloor__13dMagma_room_cFP14dMagma_floor_c */
void dMagma_room_c::newFloor(dMagma_floor_c* floor) {
    floor->setNext(mpFirst);
    mpFirst = floor;
}

/* 80076110-80076158       .text deleteFloor__13dMagma_room_cFv */
void dMagma_room_c::deleteFloor() {
    while (mpFirst != NULL) {
        mpFirst->remove();
        mpFirst = mpFirst->getNext();
    }
}

/* 80076158-800762D0       .text __ct__15dMagma_packet_cFv */
dMagma_packet_c::dMagma_packet_c() {
    dComIfG_setObjectRes("Magma", JKRArchive::DEFAULT_MOUNT_DIRECTION, NULL);

    ResTIMG* kuro = (ResTIMG*)dComIfG_getObjectRes("Magma", MAGMA_BTI_MAG_KURO);
    mDoLib_setResTimgObj(kuro, &getKuroTexObj(), 0, NULL);

    C_MTXLightOrtho(l_kuroOrthoMtx, 1.0f, -1.0f, -1.0f, 1.0f, 0.5f, -0.5f, 0.5f, 0.5f);
    mDoMtx_copy(l_kuroOrthoMtx, l_colOrthoMtx);

    ResTIMG* col = (ResTIMG*)dComIfG_getObjectRes("Magma", MAGMA_BTI_MAG_COL);
    mDoLib_setResTimgObj(col, &getColTexObj(), 0, NULL);
    mDoMtx_identity(mFloorMtx);
    mDoMtx_identity(mBallMtx);
    mTimer = 0.0f;
}

/* 800762D0-800762DC       .text __ct__13dMagma_room_cFv */
dMagma_room_c::dMagma_room_c() : mpFirst() {
}

/* 800762DC-80076318       .text __dt__14dMagma_floor_cFv */
dMagma_floor_c::~dMagma_floor_c() {
}

/* 80076318-80076324       .text __ct__14dMagma_floor_cFv */
dMagma_floor_c::dMagma_floor_c() {
    mpBalls = NULL;
}

/* 80076324-800763CC       .text __dt__15dMagma_packet_cFv */
dMagma_packet_c::~dMagma_packet_c() {
    dComIfG_deleteObjectRes("Magma");
}

/* 800763CC-800764EC       .text draw__15dMagma_packet_cFv */
void dMagma_packet_c::draw() {
    j3dSys.reinitGX();
    GXSetNumIndStages(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXLoadTexObj(&getKuroTexObj(), GX_TEXMAP0);
    GXLoadTexObj(&getColTexObj(), GX_TEXMAP1);
    dKy_GxFog_set();
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_OR, GX_GREATER, 0);
    GXSetTevColor(GX_TEVREG1, mColor1);
    GXSetCurrentMtx(GX_PNMTX0);

    dMagma_floor_c* floor = &mFloor[0];
    for (s32 i = 0; i < 8; i++, floor++) {
        if (floor->mpBalls != NULL)
            floor->draw();
    }

    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_FALSE, 0, 0);
    J3DShape::resetVcdVatCache();
}

/* 800764EC-800764FC       .text morfCalc__Ffff */
f32 morfCalc(f32 min, f32 max, f32 v) {
    return (max - min) * v + min;
}

/* 800764FC-80076770       .text calc__15dMagma_packet_cFv */
void dMagma_packet_c::calc() {
    /* Nonmatching - regalloc */
    f32 f1 = l_kuroOrthoMtx[0][3];
    f1 += 0.001f;
    if (f1 >= 1.5f)
        f1 -= 1.0f;
    l_kuroOrthoMtx[0][3] = f1;
    l_kuroOrthoMtx[1][3] = f1;

    mDoMtx_stack_c::scaleS(0.0022f, 0.0018f, 0.0017f);
    mDoMtx_stack_c::XrotM(0x4000);
    mDoMtx_concat(l_kuroOrthoMtx, mDoMtx_stack_c::get(), getKuroMtx());

    dMagma_room_c* room = mRoom;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mRoom); i++, room++)
        for (dMagma_floor_c* floor = room->getFloor(); floor != NULL; floor = floor->getNext())
            if (floor->mpBalls != NULL)
                floor->calc(i);

    mTimer += 1.0f;
    if (mTimer >= 119.0f)
        mTimer -= 119.0f;

    static GXColor l_keyColor[] = {
        { 0x00, 0x00, 0x00, 0x00 },
        { 0xFF, 0x96, 0x00, 0x3C },
        { 0x00, 0x00, 0x00, 0x77 },
    };

    GXColor* color = &l_keyColor[1];
    f32 f3;
    for (s32 i = 1; i < ARRAY_SIZE(l_keyColor); i++, color++) {
        f3 = color->a;
        if (mTimer < f3)
            break;
    }

    GXColor* color0 = &color[-1];
    GXColor* color1 = &color[0];

    f32 f4 = color0->a;
    f32 t = (mTimer - f4) / (f3 - f4);
    mColor1.r = morfCalc(color0->r, color1->r, t);
    mColor1.g = morfCalc(color0->g, color1->g, t);
    mColor1.b = morfCalc(color0->b, color1->b, t);
}

/* 80076770-800767E4       .text update__15dMagma_packet_cFv */
void dMagma_packet_c::update() {
    dMagma_floor_c* floor = mFloor;
    for (s32 i = 0; i < 8; i++, floor++) {
        if (floor->mpBalls != NULL)
            floor->update();
    }
    j3dSys.getDrawBuffer(0)->entryImm(this, 0);
}

/* 800767E4-80076924       .text checkYpos__15dMagma_packet_cFR4cXyz */
f32 dMagma_packet_c::checkYpos(cXyz& pos) {
    /* Nonmatching */
    f32 ret = -1e8;
    dMagma_floor_c* floor = mFloor;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mFloor); floor++, i++) {
        if (floor->mpBalls == NULL)
            continue;

        if (std::fabsf(pos.y - floor->getPos().y) <= 236.803879f && std::fabsf(pos.x - floor->getPos().x) <= floor->getScaleX() * 500.0f && std::fabsf(pos.z - floor->getPos().z) <= floor->getScaleZ() * 500.0f) {
            dMagma_ball_c** ball = floor->getBall();
            for (s32 j = 0; j < floor->getBallNum(); ball++, j++) {
                f32 y;
                if ((*ball)->rangeCheck(pos, &y)) {
                    if (y < floor->getPos().y)
                        y = floor->getPos().y;

                    if (y > ret)
                        ret = y;
                }
            }
        }
    }

    return ret;
}

/* 80076924-80076AA4       .text newFloor__15dMagma_packet_cFR4cXyzR4cXyzis */
dMagma_floor_c* dMagma_packet_c::newFloor(cXyz& p0, cXyz& p1, int i_roomNo, s16 i_pathNo) {
    JUT_ASSERT(0x36e, 0 <= i_roomNo && i_roomNo < 64);

    dMagma_floor_c* floor = mFloor;
    for (s32 i = 0; i < ARRAY_SIZE(mFloor); i++, floor++) {
        if (floor->mpBalls == NULL) {
            s32 param = 0;
            if (i_pathNo < 0) {
                param = -i_pathNo;
            } else {
                dPath* path = dPath_GetRoomPath(i_pathNo, i_roomNo);
                if (path == NULL)
                    return NULL;

                dPath__Point* pnt = path->mpPnt;
                for (s32 j = 0; j < path->m_num; j++)
                    param += (s32)(pnt->mArg3 * 4.0f); // bug? forgot to increment pnt
            }

            dMagma_ball_c** balls = floor->create(p0, p1, i_pathNo, param, i_roomNo);
            if (balls == NULL)
                return NULL;

            mRoom[i_roomNo].newFloor(floor);
            return floor;
        }
    }

    return NULL;
}
