#ifndef D_CHAIN_H
#define D_CHAIN_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "d/d_kankyo.h"

class dChain_packet_c : public J3DPacket {
public:
    dChain_packet_c(int, dKy_tevstr_c*, f32);
    ~dChain_packet_c();
    void draw();

public:
    /* 0x10 */ dKy_tevstr_c* mpTevStr;
    /* 0x14 */ cXyz mScale;
    /* 0x20 */ s32 mNum;
    /* 0x24 */ cXyz* mPt;
};

#endif /* D_CHAIN_H */
