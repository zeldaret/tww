#ifndef JASDSPINTERFACE_H
#define JASDSPINTERFACE_H

#include "dolphin/types.h"

namespace JASystem {
    namespace Driver {
        struct Wave_ {
            /* 0x00 */ u8 field_0x0;
            /* 0x01 */ u8 field_0x1;
            /* 0x02 */ u8 field_0x2[0x10 - 0x2];
            /* 0x10 */ int field_0x10;
            /* 0x14 */ int field_0x14;
            /* 0x18 */ int field_0x18;
            /* 0x1C */ int field_0x1c;
            /* 0x20 */ short field_0x20;
            /* 0x22 */ short field_0x22;
        };
    }
    namespace DSPInterface {
        struct FxlineConfig_ {
            /* 0x00 */ u8 field_0x0;
            /* 0x02 */ u16 field_0x2;
            /* 0x04 */ short field_0x4;
            /* 0x06 */ u16 field_0x6;
            /* 0x08 */ short field_0x8;
            /* 0x0C */ int field_0xc;
            /* 0x10 */ short field_0x10[8];
        };

        class FXBuffer {
        public:
            bool setFXLine(s16* param_1, FxlineConfig_* param_2);

            /* 0x00 */ short field_0x0;
            /* 0x02 */ short field_0x2;
            /* 0x04 */ s16* field_0x4;
            /* 0x08 */ short field_0x8;
            /* 0x0A */ short field_0xa;
            /* 0x0C */ short field_0xc;
            /* 0x0E */ short field_0xe;
            /* 0x10 */ short field_0x10[8];
        };

        class DSPBuffer {
        public:
            void allocInit();
            void playStart();
            void setWaveInfo(Driver::Wave_* param_1, u32 param_2, u32 param_3);
            void setOscInfo(u32 param_1);
            void initAutoMixer();
            void setAutoMixer(u16 param_1, u8 param_2, u8 param_3, u8 param_4, u8 param_5);
            void setPitch(u16 param_1);
            void setMixerInitDelayMax(u8 param_1);
            void setMixerInitVolume(u8 param_1, s16 param_2, u8 param_3);
            void setMixerVolume(u8 param_1, s16 param_2, u8 param_3);
            void setMixerVolumeOnly(u8 param_1, short param_2);
            void setPauseFlag(u8 param_1);
            void flushChannel();
            void initFilter();
            void setFilterMode(u16 param_1);
            void setIIRFilterParam(s16* param_1);
            void setFIR8FilterParam(s16* param_1);
            void setDistFilter(s16 param_1);
            void setBusConnect(u8 param_1, u8 param_2);

            /* 0x00 */ u16 field_0x0;
            /* 0x02 */ u16 field_0x2;
            /* 0x04 */ u16 field_0x4;
            /* 0x06 */ u8 field0x6[0x8 - 0x6];
            /* 0x08 */ u16 field_0x8;
            /* 0x0A */ u8 field_0xa[0xc - 0xa];
            /* 0x0C */ u16 field_0xc;
            /* 0x0E */ u16 field_0xe;
            /* 0x10 */ u16 field_0x10[1][4];
            /* 0x18 */ u8 field_0x18[0x50 - 0x18];
            /* 0x50 */ u16 field_0x50;
            /* 0x52 */ u16 field_0x52;
            /* 0x54 */ short field_0x54;
            /* 0x56 */ u16 field_0x56;
            /* 0x58 */ u16 field_0x58;
            /* 0x5A */ u8 field_0x5a[0x60 - 0x5a];
            /* 0x60 */ short field_0x60;
            /* 0x62 */ u8 field_0x62[0x64 - 0x62];
            /* 0x64 */ short field_0x64;
            /* 0x66 */ short field_0x66;
            /* 0x68 */ int field_0x68;
            /* 0x6C */ int field_0x6c;
            /* 0x70 */ u8 field_0x70[0x74 - 0x70];
            /* 0x74 */ int field_0x74;
            /* 0x78 */ short field_0x78[4];
            /* 0x80 */ short field_0x80[20];
            /* 0xA8 */ short field_0xa8[4];
            /* 0xB8 */ short field_0xb0[16];
            /* 0xD0 */ u8 field_0xd0[0x100 - 0xd0];
            /* 0x100 */ u16 field_0x100;
            /* 0x102 */ u16 field_0x102;
            /* 0x104 */ short field_0x104;
            /* 0x106 */ short field_0x106;
            /* 0x108 */ short field_0x108;
            /* 0x10A */ u16 field_0x10a;
            /* 0x10C */ u32 field_0x10c;
            /* 0x110 */ int field_0x110;
            /* 0x114 */ int field_0x114;
            /* 0x118 */ int field_0x118;
            /* 0x11C */ int field_0x11c;
            /* 0x120 */ short field_0x120[8];
            /* 0x130 */ u8 field_0x130[0x148 - 0x130];
            /* 0x148 */ short field_0x148[4];
            /* 0x150 */ short field_0x150;
            /* 0x152 */ u8 field_0x152[0x180 - 0x152];
        };


        void setDSPMixerLevel(float param_1);
        DSPBuffer* getDSPHandle(u8 param_1);
        void setFilterTable(short* param_1, short* param_2, u32 param_3);
        void flushBuffer();
        void invalChannelAll();
        void clearBuffer();
        void setupBuffer();
        void initBuffer();
        FXBuffer* getFXHandle(u8 param_1);

        extern u16 SEND_TABLE[12];
        extern u32 DOLBY2_DELAY_BUF[];
        extern u16 JAS_DSP_PREFIX;
        extern DSPBuffer* CH_BUF;
        extern FXBuffer* FX_BUF;
        extern f32 sDSPVolume;
    };
}

u16 DSP_CreateMap2(u32 param_1);

#endif /* JASDSPINTERFACE_H */
