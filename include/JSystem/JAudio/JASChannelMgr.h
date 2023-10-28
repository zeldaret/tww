#ifndef JASCHANNELMGR_H
#define JASCHANNELMGR_H

#include "dolphin/types.h"

namespace JASystem {
    class TChannel;

    class TChannelMgr {
    public:
        void init();
        void stopAll();
        void stopAllRelease();
        void initAllocChannel(u32);
        TChannel* getLogicalChannel(u32);
        bool moveListHead(TChannel*, u32);
        bool moveListTail(TChannel*, u32);
        void addListHead(TChannel*, u32);
        void addListTail(TChannel*, u32);
        TChannel* getListHead(u32);
        int cutList(TChannel*);
        void receiveAllChannels(TChannelMgr*);
        int checkLimitStart(u32);
        void checkLimitStop(TChannel*, u32);

        u32 field_0x0;
        int field_0x4;
        TChannel* field_0x8;
        TChannel* field_0xc;
        TChannel* field_0x10;
        TChannel* field_0x14;
        f32 field_0x18;
        f32 field_0x1c;
        f32 field_0x20;
        f32 field_0x24;
        f32 field_0x28;
        s16 field_0x2c[8];
        s16 field_0x3c[4];
        int field_0x44;
        int field_0x48;
        s16 field_0x4c;
        u16 field_0x4e[6];
        u8 field_0x5a[6];
        u8 field_0x60;
        u8 field_0x61;
        u8 field_0x62[3];
        int field_0x68;
        u16 field_0x6c;
        int field_0x70;
    };
}

#endif /* JASCHANNELMGR_H */
