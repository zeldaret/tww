//
// Generated by dtk
// Translation Unit: JKRMemArchive.cpp
//

#include "JSystem/JKernel/JKRMemArchive.h"
#include "JSystem/JKernel/JKRDecomp.h"
#include "JSystem/JKernel/JKRDvdRipper.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "string.h"

/* 802B9568-802B95A4       .text __ct__13JKRMemArchiveFv */
JKRMemArchive::JKRMemArchive() {}

/* 802B95A4-802B9658       .text __ct__13JKRMemArchiveFlQ210JKRArchive15EMountDirection */
JKRMemArchive::JKRMemArchive(s32 entryNum, JKRArchive::EMountDirection mountDirection) : JKRArchive(entryNum, MOUNT_MEM) {
    mIsMounted = false;
    mMountDirection = mountDirection;
    if (!open(entryNum, mMountDirection)) {
        return;
    }

    mVolumeType = 'RARC';
    mVolumeName = mStringTable + mNodes->name_offset;

    getVolumeList().prepend(&mFileLoaderLink);
    mIsMounted = true;
}

/* 802B9658-802B9700       .text __dt__13JKRMemArchiveFv */
JKRMemArchive::~JKRMemArchive() {
    if (mIsMounted == true) {
        if (mIsOpen) {
            if (mArcHeader)
                JKRFreeToHeap(mHeap, mArcHeader);
        }

        getVolumeList().remove(&mFileLoaderLink);
        mIsMounted = false;
    }
}

/* 802B9700-802B9740       .text fixedInit__13JKRMemArchiveFl */
void JKRMemArchive::fixedInit(s32 param_1) {
    mIsMounted = false;
    mMountMode = 1;
    mMountCount = 1;
    field_0x58 = 2;
    mHeap = JKRHeap::sCurrentHeap;
    mEntryNum = param_1;
    if (sCurrentVolume) return;
    sCurrentVolume = this;
    setCurrentDirID(0);
}

/* 802B9740-802B9810       .text mountFixed__13JKRMemArchiveFPv15JKRMemBreakFlag */
bool JKRMemArchive::mountFixed(void* param_1, JKRMemBreakFlag param_2) {
    if (check_mount_already((s32)param_1)) {
        return false;
    }
    fixedInit((s32)param_1);
    if (!open(param_1, 0xffff, param_2)) {
        return false;
    }
    mVolumeType = 'RARC';
    mVolumeName = mStringTable + mNodes->name_offset;
    sVolumeList.prepend(&mFileLoaderLink);
    mIsOpen = param_2 == 1;
    mIsMounted = true;
    return true;
}

/* 802B9810-802B98FC       .text unmountFixed__13JKRMemArchiveFv */
void JKRMemArchive::unmountFixed() {
    JUT_ASSERT(337, isMounted());
    JUT_ASSERT(340, mMountCount == 1);
    if (sCurrentVolume == this) {
        sCurrentVolume = NULL;
    }
    if (mIsOpen && mArcHeader) {
        JKRHeap::free(mArcHeader, mHeap);
    }
    sVolumeList.remove(&mFileLoaderLink);
    mIsMounted = false;
}

/* 802B98FC-802B9A90       .text open__13JKRMemArchiveFlQ210JKRArchive15EMountDirection */
bool JKRMemArchive::open(s32 entryNum, JKRArchive::EMountDirection mountDirection) {
    mArcHeader = NULL;
    mArcInfoBlock = NULL;
    mArchiveData = NULL;
    mNodes = NULL;
    mFiles = NULL;
    mStringTable = NULL;
    mIsOpen = false;
    mMountDirection = mountDirection;

    if (mMountDirection == JKRArchive::MOUNT_DIRECTION_HEAD) {
        u32 loadedSize;
        mArcHeader = (SArcHeader *)JKRDvdRipper::loadToMainRAM(
            entryNum, NULL, EXPAND_SWITCH_UNKNOWN1, 0, mHeap, JKRDvdRipper::ALLOC_DIRECTION_FORWARD,
            0, (int *)&mCompression);
    } else {
        u32 loadedSize;
        mArcHeader = (SArcHeader *)JKRDvdRipper::loadToMainRAM(
            entryNum, NULL, EXPAND_SWITCH_UNKNOWN1, 0, mHeap,
            JKRDvdRipper::ALLOC_DIRECTION_BACKWARD, 0, (int *)&mCompression);
    }

    if (!mArcHeader) {
        mMountMode = UNKNOWN_MOUNT_MODE;
    } else {
        JUT_ASSERT(418, mArcHeader->signature =='RARC');
        mArcInfoBlock = (SArcDataInfo *)((u8 *)mArcHeader + mArcHeader->header_length);
        mNodes = (SDIDirEntry *)((u8 *)&mArcInfoBlock->num_nodes + mArcInfoBlock->node_offset);
        mFiles = (SDIFileEntry *)((u8 *)&mArcInfoBlock->num_nodes + mArcInfoBlock->file_entry_offset);
        mStringTable = (char *)((u8 *)&mArcInfoBlock->num_nodes + mArcInfoBlock->string_table_offset);

        mArchiveData =
            (u8 *)((u32)mArcHeader + mArcHeader->header_length + mArcHeader->file_data_offset);
        mIsOpen = true;
    }
    if (mMountMode == 0) {
        OSReport(":::Cannot alloc memory [%s][%d]\n", __FILE__, 440);
    }

    return (mMountMode == UNKNOWN_MOUNT_MODE) ? false : true;
}

/* 802B9A90-802B9B90       .text open__13JKRMemArchiveFPvUl15JKRMemBreakFlag */
bool JKRMemArchive::open(void* buffer, u32 bufferSize, JKRMemBreakFlag flag) {
    mArcHeader = (SArcHeader *)buffer;
    JUT_ASSERT(471, mArcHeader->signature =='RARC');
    mArcInfoBlock = (SArcDataInfo *)((u8 *)mArcHeader + mArcHeader->header_length);
    mNodes = (SDIDirEntry *)((u8 *)&mArcInfoBlock->num_nodes + mArcInfoBlock->node_offset);
    mFiles = (SDIFileEntry *)((u8 *)&mArcInfoBlock->num_nodes + mArcInfoBlock->file_entry_offset);
    mStringTable = (char *)((u8 *)&mArcInfoBlock->num_nodes + mArcInfoBlock->string_table_offset);
    mArchiveData = (u8 *)(((u32)mArcHeader + mArcHeader->header_length) + mArcHeader->file_data_offset);
    mIsOpen = (flag == JKRMEMBREAK_FLAG_UNKNOWN1) ? true : false; // mIsOpen might be u8
    mHeap = JKRHeap::findFromRoot(buffer);
    mCompression = COMPRESSION_NONE;
    return true;
}

/* 802B9B90-802B9C34       .text fetchResource__13JKRMemArchiveFPQ210JKRArchive12SDIFileEntryPUl */
void* JKRMemArchive::fetchResource(SDIFileEntry* fileEntry, u32* resourceSize) {
    JUT_ASSERT(535, isMounted());
    if (!fileEntry->data) {
        fileEntry->data = mArchiveData + fileEntry->data_offset;
    }

    if (resourceSize) {
        *resourceSize = fileEntry->data_size;
    }

    return fileEntry->data;
}

/* 802B9C34-802B9D38       .text fetchResource__13JKRMemArchiveFPvUlPQ210JKRArchive12SDIFileEntryPUl */
void* JKRMemArchive::fetchResource(void* buffer, u32 bufferSize, SDIFileEntry* fileEntry, u32* resourceSize) {
    JUT_ASSERT(575, isMounted());
    u32 srcLength = fileEntry->data_size;
    if (srcLength > bufferSize) {
        srcLength = bufferSize;
    }

    if (fileEntry->data != NULL) {
        memcpy(buffer, fileEntry->data, srcLength);
    } else {
        JKRCompression compression = JKRConvertAttrToCompressionType(fileEntry->getAttr());
        void* data = mArchiveData + fileEntry->data_offset;
        srcLength =
            fetchResource_subroutine((u8*)data, srcLength, (u8*)buffer, bufferSize, compression);
    }

    if (resourceSize) {
        *resourceSize = srcLength;
    }

    return buffer;
}

/* 802B9D38-802B9DE8       .text removeResourceAll__13JKRMemArchiveFv */
void JKRMemArchive::removeResourceAll() {
    JUT_ASSERT(622, isMounted());

    if (mArcInfoBlock == NULL)
        return;
    if (mMountMode == MOUNT_MEM)
        return;

    // !@bug: looping over file entries without incrementing the fileEntry pointer. Thus, only the
    // first fileEntry will clear/remove the resource data.
    SDIFileEntry* fileEntry = mFiles;
    for (int i = 0; i < mArcInfoBlock->num_file_entries; i++) {
        if (fileEntry->data) {
            fileEntry->data = NULL;
        }
    }
}

/* 802B9DE8-802B9E80       .text removeResource__13JKRMemArchiveFPv */
bool JKRMemArchive::removeResource(void* resource) {
    JUT_ASSERT(653, isMounted());

    SDIFileEntry* fileEntry = findPtrResource(resource);
    if (!fileEntry)
        return false;

    fileEntry->data = NULL;
    return true;
}

/* 802B9E80-802B9F50       .text fetchResource_subroutine__13JKRMemArchiveFPUcUlPUcUli */
u32 JKRMemArchive::fetchResource_subroutine(u8* src, u32 srcLength, u8* dst, u32 dstLength, int compression) {
    switch (compression) {
    case COMPRESSION_NONE:
        if (srcLength > dstLength) {
            srcLength = dstLength;
        }

        memcpy(dst, src, srcLength);
        return srcLength;

    case COMPRESSION_YAY0:
    case COMPRESSION_YAZ0:
        u32 expendedSize = JKRDecompExpandSize(src);
        srcLength = expendedSize;
        if (expendedSize > dstLength) {
            srcLength = dstLength;
        }

        JKRDecompress(src, dst, srcLength, 0);
        return srcLength;

    default:
        OSPanic(__FILE__, 703, ":::??? bad sequence\n");
        break;
    }

    return 0;
}

/* 802B9F50-802B9FE0       .text getExpandedResSize__13JKRMemArchiveCFPCv */
u32 JKRMemArchive::getExpandedResSize(const void* resource) const {
    SDIFileEntry* fileEntry = findPtrResource(resource);
    if (fileEntry == NULL)
        return -1;

    if (fileEntry->isCompressed() == false) {
        return getResSize(resource);
    } else {
        return JKRDecompExpandSize((u8*)resource);
    }
}
