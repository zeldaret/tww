//
// Generated by dtk
// Translation Unit: JPAEmitterLoader.cpp
//

#include "JSystem/JParticle/JPAEmitterLoader.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "JSystem/JParticle/JPAResourceManager.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JKernel/JKRHeap.h"

#include "JSystem/JParticle/JPADynamicsBlock.h"
#include "JSystem/JParticle/JPABaseShape.h"
#include "JSystem/JParticle/JPAExtraShape.h"
#include "JSystem/JParticle/JPASweepShape.h"
#include "JSystem/JParticle/JPAExTexShape.h"
#include "JSystem/JParticle/JPAKeyBlock.h"
#include "JSystem/JParticle/JPAFieldBlock.h"

class JPAEmitterArchiveLoader_v10 {
public:
    void load();
    JPAEmitterResource* getEmitterResource() { return mpEmtrRes; }
    JPATextureResource* getTextureResource() { return mpTexRes; }

public:
    /* 0x00 */ JKRHeap* pHeap;
    /* 0x04 */ const u8* pData;
    /* 0x08 */ JPAEmitterResource* mpEmtrRes;
    /* 0x0C */ JPATextureResource* mpTexRes;
};

static void dummy() {
    OSReport("JPAEmitterLoader.cpp");
    OSReport("%s");
    OSReport("This is WRONG Version File\n");
    OSReport("This is NO JPA File\n");
    OSReport("pEmtrRes");
    OSReport("Halt");
    OSReport("pEmtrRes->pLinkInfoArray");
    OSReport("pLinkInfo");
    OSReport("pLinkInfo->keyBlocks || pLinkInfo->keyNum == 0");
    OSReport("pLinkInfo->fldBlocks || pLinkInfo->fldNum == 0");
    OSReport("pLinkInfo->texDataBase || texNum == 0");
    OSReport("pLinkInfo->fldBlocks[fldCntr]");
    OSReport("pLinkInfo->keyBlocks[keyCntr]");
    OSReport("pLinkInfo->dynBlock");
    OSReport("pLinkInfo->bspBlock");
    OSReport("pLinkInfo->espBlock");
    OSReport("pLinkInfo->sspBlock");
    OSReport("pLinkInfo->etxBlock");
    OSReport("This is WRONG File\n");
    OSReport("pLinkInfo->fldBlocks[fld_cntr]");
    OSReport("pLinkInfo->keyBlocks[key_cntr]");
    OSReport("pTex");
}

/* 802590B4-8025917C       .text load__31JPAEmitterArchiveLoaderDataBaseFPCUcP7JKRHeapPP18JPAEmitterResourcePP18JPATextureResource */
void JPAEmitterArchiveLoaderDataBase::load(const u8* data, JKRHeap* heap, JPAEmitterResource** dstEmtrRes, JPATextureResource** dstTexRes) {
    u32 magic = ((const u32*)data)[0];

    if (magic == 'JPAC') {
        u32 version = ((const u32*)data)[1];
        if (version == '1-00') {
            JPAEmitterArchiveLoader_v10 loader;
            loader.pHeap = heap;
            loader.pData = data;
            loader.mpEmtrRes = NULL;
            loader.mpTexRes = NULL;
            loader.load();
            *dstEmtrRes = loader.getEmitterResource();
            *dstTexRes = loader.getTextureResource();
        } else {
            JUT_WARN(201, "%s", "This is WRONG Version File\n");
        }
    } else {
        JUT_WARN(202, "%s", "This is WRONG File\n");
    }
}

struct JPAEmitterArchiveData_v10 {
    /* 0x00 */ u32 magic;
    /* 0x04 */ u32 size;
    /* 0x08 */ u16 emtrResNum;
    /* 0x0A */ u16 texResNum;
};

/* 8025917C-8025991C       .text load__27JPAEmitterArchiveLoader_v10Fv */
void JPAEmitterArchiveLoader_v10::load() {
    const JPAEmitterArchiveData_v10* header = (const JPAEmitterArchiveData_v10*)pData;
    mpEmtrRes = new(pHeap, 0) JPAEmitterResource(header->emtrResNum, pHeap);
    mpTexRes = new(pHeap, 0) JPATextureResource(header->texResNum, pHeap);

    u32 offs = 0x20;
    for (s32 i = 0; i < header->emtrResNum; i++) {
        const u8* data = &pData[offs];

        JPAEmitterData* pEmtrRes = new(pHeap, 0) JPAEmitterData();
        JUT_ASSERT(234, pEmtrRes);

        JPADataBlockLinkInfo* pLinkInfo = new(pHeap, 0) JPADataBlockLinkInfo();
        JUT_ASSERT(238, pLinkInfo);

        pEmtrRes->infoNum = 1;
        pEmtrRes->pLinkInfoArray = new(pHeap, 0) JPADataBlockLinkInfo*[pEmtrRes->infoNum];
        JUT_ASSERT(243, pEmtrRes->pLinkInfoArray);
        pEmtrRes->pLinkInfoArray[0] = pLinkInfo;

        pLinkInfo->keyNum = data[0x14];
        pLinkInfo->keyBlocks = (JPAKeyBlock**) (pLinkInfo->keyNum != 0 ? new(pHeap, 0) JPAKeyBlockArc*[pLinkInfo->keyNum] : NULL);
        JUT_ASSERT(250, pLinkInfo->keyBlocks || pLinkInfo->keyNum == 0);

        pLinkInfo->fldNum = data[0x15];
        pLinkInfo->fldBlocks = (JPAFieldBlock**) (pLinkInfo->fldNum != 0 ? new(pHeap, 0) JPAFieldBlockArc*[pLinkInfo->fldNum] : NULL);
        JUT_ASSERT(256, pLinkInfo->fldBlocks || pLinkInfo->fldNum == 0);

        pLinkInfo->mTextureNum = data[0x16];
        pLinkInfo->texDataBase = NULL;

        u32 fld_cntr = 0;
        u32 key_cntr = 0;
        u32 j = 0;
        u32 blockOffs = offs + 0x20;
        for (; j < *((u32*)(data + 0x0C)); j++) {
            const u8* block = (const u8*)(pData + blockOffs);
            u32 size = ((u32*)block)[1];
            switch (((u32*)block)[0]) {
            case 'FLD1':
                pLinkInfo->fldBlocks[fld_cntr] = (JPAFieldBlock*) new(pHeap, 0) JPAFieldBlockArc(pData + blockOffs);
                JUT_ASSERT(274, pLinkInfo->fldBlocks[fld_cntr]);
                fld_cntr++;
                break;
            case 'KFA1':
                pLinkInfo->keyBlocks[key_cntr] = (JPAKeyBlock*) new(pHeap, 0) JPAKeyBlockArc(pData + blockOffs);
                JUT_ASSERT(279, pLinkInfo->keyBlocks[key_cntr]);
                key_cntr++;
                break;
            case 'BEM1':
                pLinkInfo->dynBlock = (JPADynamicsBlock*) new(pHeap, 0) JPADynamicsBlockArc(pData + blockOffs);
                JUT_ASSERT(284, pLinkInfo->dynBlock);
                break;
            case 'BSP1':
                pLinkInfo->bspBlock = (JPABaseShape*) new(pHeap, 0) JPABaseShapeArc(pData + blockOffs, pHeap);
                JUT_ASSERT(288, pLinkInfo->bspBlock);
                break;
            case 'ESP1':
                pLinkInfo->espBlock = (JPAExtraShape*) new(pHeap, 0) JPAExtraShapeArc(pData + blockOffs);
                JUT_ASSERT(292, pLinkInfo->espBlock);
                break;
            case 'SSP1':
                pLinkInfo->sspBlock = (JPASweepShape*) new(pHeap, 0) JPASweepShapeArc(pData + blockOffs);
                JUT_ASSERT(296, pLinkInfo->sspBlock);
                break;
            case 'ETX1':
                pLinkInfo->etxBlock = (JPAExTexShape*) new(pHeap, 0) JPAExTexShapeArc(pData + blockOffs);
                JUT_ASSERT(300, pLinkInfo->etxBlock);
                break;
            case 'TDB1':
                pLinkInfo->texDataBase = (u16*)(block + 0x0c);
                break;
            }

            blockOffs += size;
        }

        getEmitterResource()->registration(pEmtrRes, *(u16*)(data + 0x18));
        offs = blockOffs;
    }

    for (s32 i = 0; i < header->texResNum; i++) {
        u32 size = *(u32*)(pData + offs + 0x04);
        JPATexture* pTex = new(pHeap, 0) JPATextureArc(pData + offs);
        JUT_ASSERT(319, pTex);
        getTextureResource()->registration(pTex);
        offs += size;
    }
}
