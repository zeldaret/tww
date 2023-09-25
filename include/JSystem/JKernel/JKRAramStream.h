#ifndef JKRARAMSTREAM_H
#define JKRARAMSTREAM_H

#include "JSystem/JKernel/JKRThread.h"

class JSUFileInputStream;

class JKRAramStreamCommand {
public:
    enum Type {
        UNKNOWN = 0,
        READ = 1,
        WRITE = 2,
    };

    JKRAramStreamCommand();

public:
    /* 0x00 */ Type mType;
    /* 0x04 */ u32 mAddress;
    /* 0x08 */ u32 mSize;
    /* 0x0C */ u32 field_0x0c;
    /* 0x10 */ JSUFileInputStream* mStream;
    /* 0x14 */ u32 mOffset;
    /* 0x18 */ u8* mTransferBuffer;
    /* 0x1C */ u32 mTransferBufferSize;
    /* 0x20 */ JKRHeap* mHeap;
    /* 0x24 */ bool mAllocatedTransferBuffer;
    /* 0x25 */ u8 padding_0x29[3];
    /* 0x28 */ u32 field_0x2c;
    /* 0x2C */ OSMessageQueue mMessageQueue;
    /* 0x4C */ OSMessage mMessage;
    /* 0x50 */ u32 field_0x54;
    /* 0x54 */ u32 field_0x58;
};

class JKRAramStream : public JKRThread {
private:
    JKRAramStream(s32);
    virtual ~JKRAramStream();

    /* vt[03] */ void* run(void); /* override */

public:
    static JKRAramStream* create(s32);

    static s32 readFromAram(void);
    static s32 writeToAram(JKRAramStreamCommand*);
    static JKRAramStreamCommand* write_StreamToAram_Async(JSUFileInputStream*, u32, u32, u32);
    static JKRAramStreamCommand* sync(JKRAramStreamCommand*, BOOL);
    static void setTransBuffer(u8*, u32, JKRHeap*);

private:
    static JKRAramStream* sAramStreamObject;
    static OSMessage sMessageBuffer[4];
    static OSMessageQueue sMessageQueue;

    static u8* transBuffer;
    static u32 transSize;
    static JKRHeap* transHeap;
};

inline JKRAramStream* JKRCreateAramStreamManager(s32 priority) {
    return JKRAramStream::create(priority);
}

inline JKRAramStreamCommand* JKRStreamToAram_Async(JSUFileInputStream *stream, u32 addr, u32 size, u32 offset, void (*callback)(u32)) {
    return JKRAramStream::write_StreamToAram_Async(stream, addr, size, offset);
}

#endif /* JKRARAMSTREAM_H */
