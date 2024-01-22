#ifndef JASDRUMSET_H
#define JASDRUMSET_H

#include "JSystem/JAudio/JASBasicInst.h"

namespace JASystem {
    class TInstEffect;
    class TInstParam;

    class TDrumSet : public TInst {
    public:
        class TPerc {
        public:
            TPerc();
            ~TPerc();
            void setEffectCount(u32);
            void setVeloRegionCount(u32);
            TBasicInst::TVeloRegion* getVeloRegion(int);
            void setEffect(int, JASystem::TInstEffect*);
            void setRelease(u32);

            /* 0x00 */ f32 field_0x0;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ f32 field_0x8;
            /* 0x0C */ u16 field_0xc;
            /* 0x10 */ TInstEffect** mEffect;
            /* 0x14 */ u32 mEffectCount;
            /* 0x18 */ u32 mVelomapCount;
            /* 0x1C */ TBasicInst::TVeloRegion* mVelomap;
        };

        TDrumSet() {}
        ~TDrumSet();
        bool getParam(int, int, JASystem::TInstParam*) const;
        TPerc* getPerc(int);
        u32 getType() const { return 'PERC'; }

        static const u32 sPercCount = 128;

        /* 0x04 */ TPerc field_0x4[sPercCount];
    };
}

#endif /* JASDRUMSET_H */
