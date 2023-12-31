//
// Generated by dtk
// Translation Unit: J3DShapeFactory.cpp
//

#include "JSystem/J3DGraphLoader/J3DShapeFactory.h"
#include "JSystem/J3DGraphBase/J3DShape.h"
#include "JSystem/J3DGraphBase/J3DShapeDraw.h"
#include "JSystem/J3DGraphBase/J3DShapeMtx.h"
#include "JSystem/JSupport/JSupport.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "dolphin/gx/GXAttr.h"
#include "dolphin/os/OS.h"

/* 802FE3A8-802FE458       .text __ct__15J3DShapeFactoryFRC13J3DShapeBlock */
J3DShapeFactory::J3DShapeFactory(const J3DShapeBlock& block) {
    mpShapeInitData = JSUConvertOffsetToPtr<J3DShapeInitData>(&block, (u32)block.mpShapeInitData);
    mpIndexTable = JSUConvertOffsetToPtr<u16>(&block, (u32)block.mpIndexTable);
    mpVtxDescList = JSUConvertOffsetToPtr<GXVtxDescList>(&block, (u32)block.mpVtxDescList);
    mpMtxTable = JSUConvertOffsetToPtr<u16>(&block, (u32)block.mpMtxTable);
    mpDisplayListData = JSUConvertOffsetToPtr<u8>(&block, (u32)block.mpDisplayListData);
    mpMtxInitData = JSUConvertOffsetToPtr<J3DShapeMtxInitData>(&block, (u32)block.mpMtxInitData);
    mpDrawInitData = JSUConvertOffsetToPtr<J3DShapeDrawInitData>(&block, (u32)block.mpDrawInitData);
    mpVcdVatCmdBuffer = NULL;
}

/* 802FE458-802FE614       .text create__15J3DShapeFactoryFiUlP14_GXVtxDescList */
J3DShape* J3DShapeFactory::create(int no, u32 flag, GXVtxDescList* vtxDesc) {
    J3DShape* shape = new J3DShape();
    shape->mMtxGroupNum = getMtxGroupNum(no);
    shape->mRadius = getRadius(no);
    shape->mVtxDesc = getVtxDescList(no);
    shape->mShapeMtx = new J3DShapeMtx*[shape->mMtxGroupNum];
    shape->mShapeDraw = new J3DShapeDraw*[shape->mMtxGroupNum];
    shape->mMin = getMin(no);
    shape->mMax = getMax(no);
    shape->mVcdVatCmd = mpVcdVatCmdBuffer + no * J3DShape::kVcdVatDLSize;

    for (s32 i = 0; i < shape->mMtxGroupNum; i++) {
        shape->mShapeMtx[i] = newShapeMtx(flag, no, i);
        shape->mShapeDraw[i] = newShapeDraw(no, i);
    }

    shape->mIndex = no;
    return shape;
}

static inline u32 getMdlDataFlag_MtxLoadType(u32 flag) {
    return flag & 0xF0;
}

enum {
    J3DMdlDataFlag_Imm = 0x10,
    J3DMdlDataFlag_ConcatView = 0x20,
};

enum {
    J3DShapeMtxType_Mtx = 0x00,
    J3DShapeMtxType_BBoard = 0x01,
    J3DShapeMtxType_YBBoard = 0x02,
    J3DShapeMtxType_Multi = 0x03,
};

/* 802FE614-802FEA40       .text newShapeMtx__15J3DShapeFactoryCFUlii */
J3DShapeMtx* J3DShapeFactory::newShapeMtx(u32 flag, int shapeNo, int mtxGroupNo) const {
    J3DShapeMtx* ret = NULL;
    const J3DShapeInitData& shapeInitData = mpShapeInitData[mpIndexTable[shapeNo]];
    const J3DShapeMtxInitData& mtxInitData =  (&mpMtxInitData[shapeInitData.mMtxInitDataIndex])[mtxGroupNo];

    switch (getMdlDataFlag_MtxLoadType(flag)) {
    case J3DMdlDataFlag_Imm:
        switch (shapeInitData.mShapeMtxType) {
        case J3DShapeMtxType_Mtx:
            ret = new J3DShapeMtxImm(mtxInitData.mUseMtxIndex);
            break;
        case J3DShapeMtxType_BBoard:
            ret = new J3DShapeMtxBBoardImm(mtxInitData.mUseMtxIndex);
            break;
        case J3DShapeMtxType_YBBoard:
            ret = new J3DShapeMtxYBBoardImm(mtxInitData.mUseMtxIndex);
            break;
        case J3DShapeMtxType_Multi:
            ret = new J3DShapeMtxMultiImm(mtxInitData.mUseMtxIndex, mtxInitData.mUseMtxCount, &mpMtxTable[mtxInitData.mFirstUseMtxIndex]);
            break;
        default:
            OSReport("WRONG SHAPE MATRIX TYPE (J3DModelInit.cpp)\n");
            break;
        }
        break;

    case J3DMdlDataFlag_ConcatView:
        switch (shapeInitData.mShapeMtxType) {
        case J3DShapeMtxType_Mtx:
            ret = new J3DShapeMtxConcatView(mtxInitData.mUseMtxIndex);
            break;
        case J3DShapeMtxType_BBoard:
            ret = new J3DShapeMtxBBoardConcatView(mtxInitData.mUseMtxIndex);
            break;
        case J3DShapeMtxType_YBBoard:
            ret = new J3DShapeMtxYBBoardConcatView(mtxInitData.mUseMtxIndex);
            break;
        case J3DShapeMtxType_Multi:
            ret = new J3DShapeMtxMultiConcatView(mtxInitData.mUseMtxIndex, mtxInitData.mUseMtxCount, &mpMtxTable[mtxInitData.mFirstUseMtxIndex]);
            break;
        default:
            OSReport("WRONG SHAPE MATRIX TYPE (J3DModelInit.cpp)\n");
            break;
        }
        break;

    case 0:
    default:
        switch (shapeInitData.mShapeMtxType) {
        case J3DShapeMtxType_Mtx:
        case J3DShapeMtxType_BBoard:
        case J3DShapeMtxType_YBBoard:
            ret = new J3DShapeMtx(mtxInitData.mUseMtxIndex);
            break;
        case J3DShapeMtxType_Multi:
            ret = new J3DShapeMtxMulti(mtxInitData.mUseMtxIndex, mtxInitData.mUseMtxCount, &mpMtxTable[mtxInitData.mFirstUseMtxIndex]);
            break;
        default:
            OSReport("WRONG SHAPE MATRIX TYPE (J3DModelInit.cpp)\n");
            break;
        }
        break;
    }

    return ret;
}

/* 802FEA40-802FEACC       .text newShapeDraw__15J3DShapeFactoryCFii */
J3DShapeDraw* J3DShapeFactory::newShapeDraw(int shapeNo, int mtxGroupNo) const {
    const J3DShapeInitData& shapeInitData = mpShapeInitData[mpIndexTable[shapeNo]];
    const J3DShapeDrawInitData& drawInitData = (&mpDrawInitData[shapeInitData.mDrawInitDataIndex])[mtxGroupNo];
    return new J3DShapeDraw(&mpDisplayListData[drawInitData.mDisplayListIndex], drawInitData.mDisplayListSize);
}

/* 802FEACC-802FEB38       .text allocVcdVatCmdBuffer__15J3DShapeFactoryFUl */
void J3DShapeFactory::allocVcdVatCmdBuffer(u32 count) {
    mpVcdVatCmdBuffer = new (0x20) u8[J3DShape::kVcdVatDLSize * count];
    for (u32 i = 0; i < (J3DShape::kVcdVatDLSize * count) / 4; i++)
        ((u32*)mpVcdVatCmdBuffer)[i] = 0;
}

/* 802FEB38-802FEBCC       .text calcSize__15J3DShapeFactoryFiUl */
s32 J3DShapeFactory::calcSize(int shapeNo, u32 flag) {
    s32 size = 0x68;

    s32 mtxGroupNo = getMtxGroupNum(shapeNo);
    size += mtxGroupNo * 4;
    size += mtxGroupNo * 4;

    for (u32 i = 0; i < mtxGroupNo; i++) {
        s32 shapeMtxSize = calcSizeShapeMtx(flag, shapeNo, i);
        size += shapeMtxSize;
        size += 0x0C;
    }

    return size;
}

/* 802FEBCC-802FEBDC       .text calcSizeVcdVatCmdBuffer__15J3DShapeFactoryFUl */
s32 J3DShapeFactory::calcSizeVcdVatCmdBuffer(u32 count) {
    return ALIGN_NEXT(count * J3DShape::kVcdVatDLSize, 0x20);
}

/* 802FEBDC-802FED40       .text calcSizeShapeMtx__15J3DShapeFactoryCFUlii */
s32 J3DShapeFactory::calcSizeShapeMtx(u32 flag, int shapeNo, int mtxGrouNo) const {
    const J3DShapeInitData& shapeInitData = mpShapeInitData[mpIndexTable[shapeNo]];
    u32 ret = 0;

    u32 mtxLoadType = getMdlDataFlag_MtxLoadType(flag);
    switch (mtxLoadType) {
    case J3DMdlDataFlag_Imm:
        switch (shapeInitData.mShapeMtxType) {
        case J3DShapeMtxType_Mtx:
            ret = 0x08;
            break;
        case J3DShapeMtxType_BBoard:
            ret = 0x08;
            break;
        case J3DShapeMtxType_YBBoard:
            ret = 0x08;
            break;
        case J3DShapeMtxType_Multi:
            ret = 0x10;
            break;
        default:
            OSReport("WRONG SHAPE MATRIX TYPE (J3DModelInit.cpp)\n");
        }
        break;

    case J3DMdlDataFlag_ConcatView:
        switch (shapeInitData.mShapeMtxType) {
        case J3DShapeMtxType_Mtx:
            ret = 0x08;
            break;
        case J3DShapeMtxType_BBoard:
            ret = 0x08;
            break;
        case J3DShapeMtxType_YBBoard:
            ret = 0x08;
            break;
        case J3DShapeMtxType_Multi:
            ret = 0x10;
            break;
        default:
            OSReport("WRONG SHAPE MATRIX TYPE (J3DModelInit.cpp)\n");
        }
        break;

    case 0:
    default:
        switch (shapeInitData.mShapeMtxType) {
        case J3DShapeMtxType_Mtx:
        case J3DShapeMtxType_BBoard:
        case J3DShapeMtxType_YBBoard:
            ret = 0x08;
            break;
        case J3DShapeMtxType_Multi:
            ret = 0x10;
            break;
        default:
            OSReport("WRONG SHAPE MATRIX TYPE (J3DModelInit.cpp)\n");
        }
        break;
    }

    return ret;
}
