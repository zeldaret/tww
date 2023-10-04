#ifndef JSUMEMORYSTREAM_H
#define JSUMEMORYSTREAM_H

#include "JSystem/JSupport/JSURandomInputStream.h"

class JSUMemoryInputStream : public JSURandomInputStream {
public:
    JSUMemoryInputStream(const void* res, u32 size) { setBuffer(res, size); }

    virtual ~JSUMemoryInputStream() {}
    void setBuffer(void const*, s32);
    u32 readData(void*, s32);
    s32 seekPos(s32, JSUStreamSeekFrom);
    s32 getLength() const;
    s32 getPosition() const;

private:
    /* 0x08 */ const void* mBuffer;
    /* 0x0C */ s32 mLength;
    /* 0x10 */ s32 mPosition;
};  // Size = 0x14

#endif /* JSUMEMORYSTREAM_H */
