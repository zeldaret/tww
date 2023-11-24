#ifndef JASBASICINST_H
#define JASBASICINST_H

#include "JSystem/JAudio/JASInst.h"
#include "JSystem/JAudio/JASOscillator.h"

namespace JASystem {
    class TInstEffect;
    class TBasicInst : public TInst {
    public:
        struct TVeloRegion {
            /* 0x00 */ s32 mBaseVel;
            /* 0x04 */ s32 field_0x04;
            /* 0x08 */ f32 field_0x08;
            /* 0x0C */ f32 field_0x0c;
        };

        class TKeymap {
        public:
            TKeymap() {
                mBaseKey = -1;
                mVeloRegionCount = 0;
                mVelomap = NULL;
            }
            ~TKeymap();
            void setVeloRegionCount(u32);
            TVeloRegion* getVeloRegion(int);
            const TVeloRegion* getVeloRegion(int) const;

            /* 0x00 */ int mBaseKey;
            /* 0x04 */ u32 mVeloRegionCount;
            /* 0x08 */ TVeloRegion* mVelomap;
        };

        TBasicInst();
        ~TBasicInst();
        bool getParam(int, int, TInstParam*) const;
        virtual int getKeymapIndex(int) const;
        void setKeyRegionCount(u32);
        void setEffectCount(u32);
        void setEffect(int, TInstEffect*);
        void setOscCount(u32);
        void setOsc(int, TOscillator::Osc_*);
        TKeymap* getKeyRegion(int);
        u32 getType() const { return 'BSIC'; }

        /* 0x04 */ f32 field_0x4;
        /* 0x08 */ f32 field_0x8;
        /* 0x0C */ TInstEffect** mEffect;
        /* 0x10 */ u32 mEffectCount;
        /* 0x14 */ TOscillator::Osc_** mOsc;
        /* 0x18 */ u32 mOscCount;
        /* 0x1C */ u32 mKeyRegionCount;
        /* 0x20 */ TKeymap* mKeymap;
    };
}

#endif /* JASBASICINST_H */
