#ifndef JASCHANNEL_H
#define JASCHANNEL_H

#include "JSystem/JAudio/JASDriverIF.h"
#include "JSystem/JAudio/JASOscillator.h"
#include "JSystem/JSupport/JSUList.h"

namespace JASystem {
    class TChannelMgr;
    class TDSPChannel;
    namespace Driver {
        struct Wave_;
    }

    class TChannel {
    public:
        enum CalcType {
            // NB: haven't seen others used, add from calc_sw_table in JASChannel.cpp if needed
            CALC_None           = 0,
            CALC_AddChannelOnly = 1,
            CALC_AddAll         = 13,
            CALC_WeightAll      = 26,
        };

        union MixConfig {
            u16 mWhole;
            struct {
                u8 u;
                u8 l0 : 4;
                u8 l1 : 4;
            } mParts;
        };

        TChannel() : field_0x4(NULL), field_0x8(NULL), field_0x20(NULL), field_0x24(NULL), field_0xd8(this) {
            for (int i = 0; i < 4; i++) {
                osc[i] = NULL;
            }
        }
        ~TChannel() {}
        void init();
        void setOscillator(u32, TOscillator*);
        void setOscInit(u32, const TOscillator::Osc_*);
        bool forceStopOsc(u32);
        bool releaseOsc(u32);
        void directReleaseOsc(u32, u16);
        f32 bankOscToOfs(u32);
        void effectOsc(u32, f32);
        u8 getOscState(u32) const;
        BOOL isOsc(u32);
        void copyOsc(u32, TOscillator::Osc_*);
        void overwriteOsc(u32, TOscillator::Osc_*);
        void setKeySweepTarget(u8, u32);
        void setPauseFlag(u8);
        void setPauseFlagReq(u8);
        void setPanPower(f32, f32, f32, f32);
        BOOL checkLogicalChannel();
        BOOL play(u32);
        void stop(u16);
        void updateJcToDSP();
        bool forceStopLogicalChannel();
        BOOL stopLogicalChannel();
        BOOL playLogicalChannel();
        void updateEffectorParam();
        static void killBrokenLogicalChannels(TDSPChannel*);
        static int updatecallDSPChannel(TDSPChannel*, u32);
        static f32 calcEffect(const Driver::PanMatrix_*, const Driver::PanMatrix_*, u8);
        static f32 calcPan(const Driver::PanMatrix_*, const Driver::PanMatrix_*, u8);
        void updateJcToDSPInit();
        void updateAutoMixer(f32, f32, f32, f32);
        void updateMixer(f32, f32, f32, f32);
        static u32 extraUpdate(TChannel*, u32);
        static BOOL updatecallLogicalChannel(TChannel*, u32);

        u8 getNoteOnPriority() const { return field_0x48; }
        u8 getReleasePriority() const { return field_0x48 >> 8; }
        u8 getLifeTimePriority() const { return field_0x48 >> 0x10; }

        // TODO
        void setSkipSamples(u32) {}

        /* 0x00 */ u8 field_0x0;
        /* 0x01 */ u8 field_0x1;
        /* 0x02 */ u8 mPauseFlag;
        /* 0x03 */ u8 field_0x3;
        /* 0x04 */ TChannelMgr* field_0x4;
        /* 0x08 */ TChannel** field_0x8;
        /* 0x0C */ u8 field_0xc;
        /* 0x10 */ Driver::Wave_* field_0x10;
        /* 0x14 */ int field_0x14;
        /* 0x18 */ int field_0x18;
        /* 0x1C */ int field_0x1c;
        /* 0x20 */ TDSPChannel* field_0x20;
        /* 0x24 */ TChannel* field_0x24;
        /* 0x28 */ BOOL (*field_0x28)(TChannel*, u32);
        /* 0x2C */ u32 (*field_0x2c)(TChannel*, u32);
        /* 0x30 */ int field_0x30;
        /* 0x34 */ s32 field_0x34;
        /* 0x38 */ TOscillator* osc[4];
        /* 0x48 */ u32 field_0x48;
        /* 0x4C */ u16 field_0x4c;
        /* 0x50 */ f32 field_0x50;
        /* 0x54 */ f32 field_0x54;
        /* 0x58 */ f32 field_0x58;
        /* 0x5C */ f32 field_0x5c;
        /* 0x60 */ u8 mCalcTypes[3]; // Pan, FxMix, ?
        /* 0x64 */ Driver::PanMatrix_ mPanPower;
        /* 0x70 */ Driver::PanMatrix_ mPanVec;
        /* 0x7C */ Driver::PanMatrix_ mFxmixVec;
        /* 0x88 */ Driver::PanMatrix_ mDolbyVec;
        /* 0x94 */ f32 field_0x94;
        /* 0x98 */ f32 field_0x98;
        /* 0x9C */ f32 field_0x9c;
        /* 0xA0 */ u16 mPitch;
        /* 0xA2 */ u16 field_0xa2;
        /* 0xA4 */ TChannelMgr* field_0xa4;
        /* 0xA8 */ f32 field_0xa8;
        /* 0xAC */ f32 field_0xac;
        /* 0xB0 */ MixConfig mMixConfigs[6];
        /* 0xBC */ u16 field_0xbc[6];
        /* 0xC8 */ u16 field_0xc8;
        /* 0xCC */ int field_0xcc;
        /* 0xD0 */ int field_0xd0;
        /* 0xD4 */ int field_0xd4;
        /* 0xD8 */ JSULink<TChannel> field_0xd8;
        /* 0xE8 */ u32 field_0xe8;
    };
}

#endif /* JASCHANNEL_H */
