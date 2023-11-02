#ifndef JASBASICINST_H
#define JASBASICINST_H

#include "JSystem/JAudio/JASInst.h"
#include "JSystem/JAudio/JASOscillator.h"

namespace JASystem {
    class TInstEffect;
    class TBasicInst : public TInst {
    public:
        class TKeymap {
        public:
            TKeymap() {
                field_0x0 = -1;
                field_0x4 = 0;
                mVelomap = NULL;
            }
            ~TKeymap();
            void setVeloRegionCount(u32);
            void* getVeloRegion(int);
            const void* getVeloRegion(int) const;

            /* 0x00 */ int field_0x0;
            /* 0x04 */ u32 field_0x4;
            /* 0x08 */ void* mVelomap;
        };

        TBasicInst();
        ~TBasicInst();
        bool getParam(int, int, TInstParam*) const;
        int getKeymapIndex(int) const;
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
        /* 0x1C */ u32 field_0x1c;
        /* 0x20 */ TKeymap* mKeymap;
    };
}

#endif /* JASBASICINST_H */
