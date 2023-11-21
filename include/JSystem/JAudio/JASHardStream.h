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

        class TPlayPair {
        public:
            u16 getIntro() { return mIntroNum; }
            u16 getLoop() { return mLoopNum; }

        public:
            /* 0x00 */ u16 field_0x0;
            /* 0x02 */ u16 field_0x2;
            /* 0x04 */ u16 mIntroNum;
            /* 0x06 */ u16 mLoopNum;
        };

        class TPlayList {
        public:
            void clear() {
                mpPair = NULL;
                mpNextList = NULL;
                field_0x8 = 0;
            }
            TPlayPair* getPair() { return mpPair; }
            TPlayList* getNext() { return mpNextList; }

        public:
            /* 0x00 */ TPlayPair* mpPair;
            /* 0x04 */ TPlayList* mpNextList;
            /* 0x08 */ u32 field_0x8;
        };

        class TControl {
        public:
            TControl();
            ~TControl() {}
            u16 getIntroNum();
            u16 getLoopNum();
            BOOL fileOpen(u16, DVDFileInfo*);
            BOOL clearListOne();
            void setLastAddr(DVDFileInfo*);
            u32 getLastAddr();
            BOOL startFirst(u16, DVDFileInfo*, u32*);
            BOOL startSecond(u16, DVDFileInfo*, u32*);
            void resetFader();
            u8 getCurVol();
            void calcCurVolume();
            u8 volFloatToU8(f32);

            void getLastAddrBefore() {}
            TPlayList* getList() { return mpList; }
            void getPlayArea() {}
            void getRestart() {}
            void getState() {}
            void setList(TPlayList* list) { mpList = list; }
            void setPlayArea(u16) {}
            void setRestart(u8) {}
            void setState(u8) {}

            /* 0x00 */ int field_0x0;
            /* 0x04 */ TPlayList* mpList;
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
        extern TPlayList* playList;
        extern int playListMax;
        extern char rootDir[];
    }
}

#endif /* JASHARDSTREAM_H */
