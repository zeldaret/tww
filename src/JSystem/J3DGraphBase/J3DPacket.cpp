//
// Generated by dtk
// Translation Unit: J3DPacket.cpp
//

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "JSystem/J3DGraphBase/J3DMaterial.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "string.h"
#include "dolphin/gx/GX.h"
#include "dolphin/os/OS.h"

/* 802DAE1C-802DAE9C       .text newDisplayList__17J3DDisplayListObjFUl */
J3DError J3DDisplayListObj::newDisplayList(u32 capacity) {
    mCapacity = ALIGN_NEXT(capacity, 0x20);
    mpData[0] = new (0x20) char[mCapacity];
    mpData[1] = new (0x20) char[mCapacity];
    mSize = 0;

    if (mpData[0] == NULL || mpData[1] == NULL)
        return J3DErrType_OutOfMemory;

    return J3DErrType_Success;
}

/* 802DAE9C-802DAF00       .text newSingleDisplayList__17J3DDisplayListObjFUl */
J3DError J3DDisplayListObj::newSingleDisplayList(u32 capacity) {
    mCapacity = ALIGN_NEXT(capacity, 0x20);
    mpData[0] = new (0x20) char[mCapacity];
    mpData[1] = mpData[0];
    mSize = 0;

    if (mpData[0] == NULL)
        return J3DErrType_OutOfMemory;

    return J3DErrType_Success;
}

/* 802DAF00-802DAF78       .text single_To_Double__17J3DDisplayListObjFv */
J3DError J3DDisplayListObj::single_To_Double() {
    if (mpData[0] == mpData[1]) {
        mpData[1] = new (0x20) char[mCapacity];

        if (mpData[1] == NULL)
            return J3DErrType_OutOfMemory;

        memcpy(mpData[1], mpData[0], mCapacity);
        DCStoreRange(mpData[1], mCapacity);
    }

    return J3DErrType_Success;
}

/* 802DAF78-802DAF98       .text setSingleDisplayList__17J3DDisplayListObjFPvUl */
void J3DDisplayListObj::setSingleDisplayList(void* pDLData, u32 size) {
    mCapacity = ALIGN_NEXT(size, 0x20);
    mpData[0] = pDLData;
    mpData[1] = mpData[0];
    mSize = size;
}

/* 802DAF98-802DAFAC       .text swapBuffer__17J3DDisplayListObjFv */
void J3DDisplayListObj::swapBuffer() {
    void* pTmp = mpData[0];
    mpData[0] = mpData[1];
    mpData[1] = pTmp;
}

/* 802DAFAC-802DAFD8       .text callDL__17J3DDisplayListObjCFv */
void J3DDisplayListObj::callDL() const {
    GXCallDisplayList(mpData[0], mSize);
}

GDLObj J3DDisplayListObj::sGDLObj;
s32 J3DDisplayListObj::sInterruptFlag;

/* 802DAFD8-802DB02C       .text beginDL__17J3DDisplayListObjFv */
void J3DDisplayListObj::beginDL() {
    swapBuffer();
    sInterruptFlag = OSDisableInterrupts();
    GDInitGDLObj(&sGDLObj, (u8*)mpData[0], mCapacity);
    GDSetCurrent(&sGDLObj);
}

/* 802DB02C-802DB088       .text endDL__17J3DDisplayListObjFv */
u32 J3DDisplayListObj::endDL() {
    GDPadCurr32();
    OSRestoreInterrupts(sInterruptFlag);
    mSize = GDGetGDLObjOffset(&sGDLObj);
    GDFlushCurrToMem();
    GDSetCurrent(NULL);
    return mSize;
}

/* 802DB088-802DB0A8       .text beginPatch__17J3DDisplayListObjFv */
void J3DDisplayListObj::beginPatch() {
    beginDL();
}

/* 802DB0A8-802DB0E4       .text endPatch__17J3DDisplayListObjFv */
u32 J3DDisplayListObj::endPatch() {
    OSRestoreInterrupts(sInterruptFlag);
    GDSetCurrent(NULL);
    return mSize;
}

/* 802DB0E4-802DB0EC       .text isSame__9J3DPacketCFP12J3DMatPacket */
bool J3DPacket::isSame(J3DMatPacket*) const {
    return false;
}

/* 802DB0EC-802DB0F4       .text entry__9J3DPacketFP13J3DDrawBuffer */
int J3DPacket::entry(J3DDrawBuffer*) {
    return 1;
}

/* 802DB0F4-802DB114       .text addChildPacket__9J3DPacketFP9J3DPacket */
void J3DPacket::addChildPacket(J3DPacket* pPacket) {
    if (mpFirstChild == NULL) {
        mpFirstChild = pPacket;
    } else {
        pPacket->mpNextPacket = mpFirstChild;
        mpFirstChild = pPacket;
    }
}

/* 802DB114-802DB1A0       .text draw__17J3DCallBackPacketFv */
void J3DCallBackPacket::draw() {
    if (mpCallBack != NULL)
        mpCallBack(this, 0);

    for (J3DPacket * pPacket = mpFirstChild; pPacket != NULL; pPacket = pPacket->getNextPacket())
        pPacket->draw();

    if (mpCallBack != NULL)
        mpCallBack(this, 1);
}

/* 802DB1A0-802DB1D4       .text __ct__13J3DDrawPacketFv */
J3DDrawPacket::J3DDrawPacket() {
    mFlags = 0;
    mpDisplayListObj = NULL;
}

/* 802DB1D4-802DB230       .text __dt__13J3DDrawPacketFv */
J3DDrawPacket::~J3DDrawPacket() {
}

/* 802DB230-802DB2BC       .text newDisplayList__13J3DDrawPacketFUl */
J3DError J3DDrawPacket::newDisplayList(u32 size) {
    mpDisplayListObj = new J3DDisplayListObj();

    if (mpDisplayListObj == NULL)
        return J3DErrType_OutOfMemory;

    J3DError ret = mpDisplayListObj->newDisplayList(size);
    if (ret != J3DErrType_Success)
        return ret;

    return J3DErrType_Success;
}

/* 802DB2BC-802DB348       .text newSingleDisplayList__13J3DDrawPacketFUl */
J3DError J3DDrawPacket::newSingleDisplayList(u32 size) {
    mpDisplayListObj = new J3DDisplayListObj();

    if (mpDisplayListObj == NULL)
        return J3DErrType_OutOfMemory;

    J3DError ret = mpDisplayListObj->newSingleDisplayList(size);
    if (ret != J3DErrType_Success)
        return ret;

    return J3DErrType_Success;
}

/* 802DB348-802DB36C       .text draw__13J3DDrawPacketFv */
void J3DDrawPacket::draw() {
    mpDisplayListObj->callDL();
}

/* 802DB36C-802DB3C4       .text __ct__12J3DMatPacketFv */
J3DMatPacket::J3DMatPacket() {
    mpInitShapePacket = NULL;
    mpMaterial = NULL;
    mDiffFlag = -1;
    mpTexture = NULL;
    mpMaterialAnm = NULL;
}

/* 802DB3C4-802DB424       .text __dt__12J3DMatPacketFv */
J3DMatPacket::~J3DMatPacket() {
}

/* 802DB424-802DB444       .text addShapePacket__12J3DMatPacketFP14J3DShapePacket */
void J3DMatPacket::addShapePacket(J3DShapePacket* pShape) {
    if (mpShapePacket == NULL) {
        mpShapePacket = pShape;
    } else {
        pShape->mpNextPacket = mpShapePacket;
        mpShapePacket = pShape;
    }
}

/* 802DB444-802DB46C       .text beginDiff__12J3DMatPacketFv */
void J3DMatPacket::beginDiff() {
    mpInitShapePacket->mpDisplayListObj->beginDL();
}

/* 802DB46C-802DB494       .text endDiff__12J3DMatPacketFv */
void J3DMatPacket::endDiff() {
    mpInitShapePacket->mpDisplayListObj->endDL();
}

/* 802DB494-802DB524       .text draw__12J3DMatPacketFv */
void J3DMatPacket::draw() {
    j3dSys.setTexture(mpTexture);
    j3dSys.setMatPacket(this);

    mpMaterial->load();
    J3DShapePacket* packet = getShapePacket();

    J3DShape* shape = packet->getShape();
    shape->loadPreDrawSetting();

    while (packet != NULL) {
        if (packet->getDisplayListObj() != NULL) {
            packet->getDisplayListObj()->callDL();
        }

        packet->drawFast();
        packet = (J3DShapePacket*)packet->getNextPacket();
    }

    shape->resetVcdVatCache();
}

/* 802DB524-802DB584       .text __ct__14J3DShapePacketFv */
J3DShapePacket::J3DShapePacket() {
    mpShape = NULL;
    mpDrawMtx = NULL;
    mpNrmMtx = NULL;
    mpBaseMtxPtr = NULL;
    mpCurrentViewNo = &j3dDefaultViewNo;
    mpScaleFlagArray = NULL;
    mpModel = NULL;
}

/* 802DB584-802DB5E4       .text __dt__14J3DShapePacketFv */
J3DShapePacket::~J3DShapePacket() {
}

u32 sDifferedRegister[] = {
    0x00000001, 0x00000002, 0x01000000, 0x10000000, 0x20000000, 0x02000000, 0x08000000,
};

s32 sSizeOfDiffered[] = {
    13, 21, 120, 55, 15, 19, 45,
};

/* 802DB5E4-802DB7CC       .text calcDifferedBufferSize__14J3DShapePacketFUl */
u32 J3DShapePacket::calcDifferedBufferSize(u32 flag) {
    int iVar5 = 0;
    for (int i = 0; i < 7; i++) {
        if ((flag & sDifferedRegister[i]) != 0) {
            iVar5 += sSizeOfDiffered[i];
        }
    }

    iVar5 += getDiffFlag_LightObjNum(flag) * 0x48;
    u32 uVar2 = getDiffFlag_TexGenNum(flag);
    if (uVar2 != 0) {
        u32 local_4c = mpShape->getMaterial()->getTexGenNum();
        if (uVar2 > local_4c) {
            local_4c = uVar2;
        }

        if ((flag & 0x1000)) {
            iVar5 += calcDifferedBufferSize_TexGenSize(local_4c);
        } else {
            iVar5 += calcDifferedBufferSize_TexMtxSize(local_4c);
        }
    }

    uVar2 = getDiffFlag_TexNoNum(flag);
    if (uVar2 != 0) {
        u8 local_58;
        if (mpShape->getMaterial()->getTevStageNum() > 8) {
            local_58 = 8;
        } else {
            local_58 = mpShape->getMaterial()->getTevStageNum();
        }
        u32 local_50 = local_58;
        local_50 = uVar2 > local_50 ? uVar2 : local_50;
        if ((flag & 0x4000000)) {
            iVar5 += calcDifferedBufferSize_TexNoAndTexCoordScaleSize(local_50);
        } else {
            iVar5 += calcDifferedBufferSize_TexNoSize(local_50);
        }
    }

    uVar2 = getDiffFlag_TevStageNum(flag);
    if (uVar2 != 0) {
        u8 local_58;
        if (mpShape->getMaterial()->getTevStageNum() > 8) {
            local_58 = 8;
        } else {
            local_58 = mpShape->getMaterial()->getTevStageNum();
        }
        u32 local_50 = local_58;
        local_50 = uVar2 > local_50 ? uVar2 : local_50;
        iVar5 += calcDifferedBufferSize_TevStageSize(local_50);
        if (flag & 0x8000000) {
            iVar5 += calcDifferedBufferSize_TevStageDirectSize(local_50);
        }
    }

    return ALIGN_NEXT(iVar5, 0x20);
}

/* 802DB7CC-802DB818       .text newDifferedDisplayList__14J3DShapePacketFUl */
J3DError J3DShapePacket::newDifferedDisplayList(u32 flag) {
    mDiffFlag = flag;
    u32 bufSize = calcDifferedBufferSize(flag);
    J3DError error = newDisplayList(bufSize);

    if (error != J3DErrType_Success) {
        return error;
    }

    setDisplayListObj(getDisplayListObj());
    return J3DErrType_Success;
}

/* 802DB818-802DB890       .text prepareDraw__14J3DShapePacketCFv */
void J3DShapePacket::prepareDraw() const {
    mpModel->getVertexBuffer()->setArray();
    j3dSys.setModel(mpModel);
    j3dSys.setShapePacket((J3DShapePacket*)this);

    mpShape->setScaleFlagArray(mpScaleFlagArray);
    mpShape->setDrawMtx(mpDrawMtx);
    mpShape->setNrmMtx(mpNrmMtx);
    mpShape->setCurrentViewNoPtr(mpCurrentViewNo);
}

/* 802DB890-802DB8F8       .text draw__14J3DShapePacketFv */
void J3DShapePacket::draw() {
    if (!checkFlag(J3DShpFlag_Hidden) && mpShape != NULL) {
        prepareDraw();

        if (mpDisplayListObj != NULL)
            mpDisplayListObj->callDL();

        mpShape->draw();
    }
}

/* 802DB8F8-802DB950       .text drawFast__14J3DShapePacketFv */
void J3DShapePacket::drawFast() {
    if (!checkFlag(J3DShpFlag_Hidden) && mpShape != NULL) {
        prepareDraw();
        mpShape->drawFast();
    }
}

/* 802DB950-802DB978       .text isSame__12J3DMatPacketCFP12J3DMatPacket */
bool J3DMatPacket::isSame(J3DMatPacket* pOther) const {
    bool isSame = false;

    if (mDiffFlag == pOther->mDiffFlag && !(mDiffFlag >> 0x1F)) {
        isSame = true;
    }
    return isSame;
}
