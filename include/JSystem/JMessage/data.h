#ifndef JMESSAGE_DATA_H
#define JMESSAGE_DATA_H

#include "JSystem/JGadget/binary.h"
#include "JSystem/JUtility/JUTDataHeader.h"

namespace JMessage {
namespace data {
extern const int ga4cSignature;

struct TParse_THeader : public JGadget::binary::TParseData_aligned<4> {
    TParse_THeader(const void* data) : TParseData_aligned(data) {}

    // TODO: create a struct for this content (BMG header)
    char* get() const { return (char*)getRaw(); }
    const void* getContent() const { return (char*)getRaw() + 0x20; }

    u32* get_signature() const { return (u32*)(get() + 0x0); }
    u32 get_type() const { return *(u32*)(get() + 0x4); }
    u32 get_blockNumber() const { return *(u32*)(get() + 0xC); }
    u8 get_encoding() const { return *(u8*)(get() + 0x10); }
};

struct TParse_TBlock : public JGadget::binary::TParseData_aligned<4> {
    TParse_TBlock(const void* data) : TParseData_aligned(data) {}
};

// INF1
struct JUTMesgInfo {
public:
    /* 0x00 */ JUTDataBlockHeader header;
    /* 0x08 */ u16 messageEntryNumber;
    /* 0x0A */ u16 messageEntrySize;
    /* 0x0C */ u16 groupID;
    /* 0x0E */ u8 defaultColor;
    /* 0x0F */ u8 reserved;
    /* 0x10 */ char messageEntryTable[];
};

struct TParse_TBlock_info : public TParse_TBlock {
    TParse_TBlock_info(const void* data) : TParse_TBlock(data) {}

    JUTMesgInfo* get() const { return (JUTMesgInfo*)getRaw(); }
    char* getContent() const { return get()->messageEntryTable; }

    u32 get_messageEntryNumber() const { return get()->messageEntryNumber; }
    u32 get_messageEntrySize() const { return get()->messageEntrySize; }
    u16 get_groupID() const { return get()->groupID; }
};

// MID1
struct JUTMesgIDData {
public:
    /* 0x00 */ JUTDataBlockHeader mHeader;
    /* 0x08 */ u16 numEntries;
    /* 0x0A */ u8 format;
    /* 0x0B */ u8 info;
    /* 0x0C */ u8 reserved[4];
    /* 0x10 */ u32 messageIDTable[];
};

inline u16 getTagCode(u32 tag) { return tag & 0xFFFF; }
inline u8 getTagGroup(u32 tag) { return (tag >> 0x10) & 0xFF; }

} // namespace data
} // namespace JMessage

#endif /* JMESSAGE_DATA_H */
