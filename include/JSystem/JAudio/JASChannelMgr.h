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

        /* 0x00 */ u32 field_0x0;
        /* 0x04 */ int field_0x4;
        /* 0x08 */ TChannel* field_0x8;
        /* 0x0C */ TChannel* field_0xc;
        /* 0x10 */ TChannel* field_0x10;
        /* 0x14 */ TChannel* field_0x14;
        /* 0x18 */ f32 field_0x18;
        /* 0x1C */ f32 field_0x1c;
        /* 0x20 */ f32 field_0x20;
        /* 0x24 */ f32 field_0x24;
        /* 0x28 */ f32 field_0x28;
        /* 0x2C */ s16 field_0x2c[8];
        /* 0x3C */ s16 field_0x3c[4];
        /* 0x44 */ int field_0x44;
        /* 0x48 */ int field_0x48;
        /* 0x4C */ s16 field_0x4c;
        /* 0x4E */ u16 field_0x4e[6];
        /* 0x5A */ u8 field_0x5a[6];
        /* 0x60 */ u8 field_0x60;
        /* 0x61 */ u8 field_0x61;
        /* 0x62 */ u8 field_0x62[3];
        /* 0x68 */ int field_0x68;
        /* 0x6C */ u16 field_0x6c;
        /* 0x70 */ int field_0x70;
    };
}

#endif /* JASCHANNELMGR_H */
