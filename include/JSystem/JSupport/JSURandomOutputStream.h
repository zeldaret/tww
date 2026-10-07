#ifndef JSURANDOMOUTPUTSTREAM_H
#define JSURANDOMOUTPUTSTREAM_H

#include "JSystem/JSupport/JSUInputStream.h"
#include "JSystem/JSupport/JSUOutputStream.h"

class JSURandomOutputStream : public JSUOutputStream {
public:
    JSURandomOutputStream() {}
    virtual ~JSURandomOutputStream() {}

    /* vt[4] */ virtual s32 writeData(const void*, s32) = 0;
    /* vt[5] */ virtual s32 getLength() const = 0;
    /* vt[6] */ virtual s32 getPosition() const = 0;
    /* vt[7] */ virtual s32 seek(s32, JSUStreamSeekFrom);
    /* vt[8] */ virtual s32 getAvailable() const;
    /* vt[9] */ virtual s32 seekPos(s32, JSUStreamSeekFrom) = 0;
};  // Size = 0x8

#endif /* JSURANDOMOUTPUTSTREAM_H */
