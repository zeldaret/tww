#ifndef JASHARDSTREAM_H
#define JASHARDSTREAM_H

#include "dolphin/types.h"

typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct DVDFileInfo DVDFileInfo;

namespace JASystem {
    namespace HardStream {
        int unregistBgmAll();
        void main();
        void firstBgmCallback(s32, DVDFileInfo*);
        void secondBgmCallback(s32, DVDFileInfo*);
        void getAddrCallback(s32, DVDCommandBlock*);

        class TControl {
        public:
            TControl();
            ~TControl() {}
            u16 getIntroNum();
            u16 getLoopNum();
            BOOL fileOpen(u16, DVDFileInfo*);
            void clearListOne();
            void setLastAddr(DVDFileInfo*);
            u32 getLastAddr();
            BOOL startFirst(u16, DVDFileInfo*, u32*);
            BOOL startSecond(u16, DVDFileInfo*, u32*);
            void resetFader();
            u8 getCurVol();
            void calcCurVolume();
            u8 volFloatToU8(f32);

            /* 0x00 */ int field_0x0;
            /* 0x04 */ void* field_0x4;
            /* 0x08 */ u16 field_0x8;
            /* 0x0A */ u8 field_0xa;
            /* 0x0B */ u8 field_0xb;
            /* 0x0C */ f32 field_0xc;
            /* 0x10 */ f32 field_0x10;
            /* 0x14 */ int field_0x14;
            /* 0x18 */ int field_0x18;
            /* 0x1C */ int field_0x1c;
            /* 0x20 */ f32 field_0x20;
            /* 0x24 */ f32 field_0x24;
            /* 0x28 */ f32 field_0x28;
            /* 0x2C */ f32 field_0x2c;
            /* 0x30 */ f32 field_0x30;
            /* 0x34 */ f32 field_0x34;
            /* 0x38 */ int field_0x38;
            /* 0x3C */ int field_0x3c;
            /* 0x40 */ int field_0x40;
            /* 0x44 */ u32 field_0x44[2];
            /* 0x4C */ u8 field_0x4c;
        };

        extern TControl strCtrl;
        extern bool useHardStreaming;
        extern char* streamFiles;
        extern u32* playList;
        extern int playListMax;
        extern char rootDir[];
    }
}

#endif /* JASHARDSTREAM_H */
