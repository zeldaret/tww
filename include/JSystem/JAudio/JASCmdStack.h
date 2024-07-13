#ifndef JASCMDSTACK_H
#define JASCMDSTACK_H

#include "JSystem/JAudio/JASTrack.h"
#include "dolphin/types.h"

namespace JASystem {
    namespace Kernel {
        class TPortArgs {
        public:
            /* 0x00 */ TTrack* mTrack;
            /* 0x04 */ u32 mFlags;
            /* 0x08 */ f32 mTrackVolume;
            /* 0x0C */ f32 mTrackPitch;
            /* 0x10 */ f32 mTrackPan;
            /* 0x14 */ f32 mTrackFxmix;
            /* 0x18 */ f32 mTrackDolby;
            /* 0x1C */ f32 _1C;
            /* 0x20 */ u32 _20;
            /* 0x24 */ f32 mTrackTempo;
        };

        class TPortCmd;

        class TPortHead {
        public:
            /* 0x00 */ TPortCmd* field_0x0;
            /* 0x04 */ TPortCmd* field_0x4;
        };

        class TPortCmd {
        public:
            TPortCmd();
            ~TPortCmd() {}
            bool addPortCmdOnce();
            bool setPortCmd(void (*)(TPortArgs*), TPortArgs*);
            bool addPortCmd(TPortHead*);

            /* 0x00 */ TPortHead* field_0x0;
            /* 0x04 */ TPortCmd* field_0x4;
            /* 0x08 */ void (*field_0x8)(TPortArgs*);
            /* 0x0C */ TPortArgs* field_0xc;
        };

        void portCmdProcOnce(TPortHead*);
        void portCmdProcStay(TPortHead*);
        void portHeadInit(TPortHead*);
        void portCmdInit();
        TPortCmd* getPortCmd(TPortHead*);
        s32 portCmdMain(void*);
    }
}

#endif /* JASCMDSTACK_H */
