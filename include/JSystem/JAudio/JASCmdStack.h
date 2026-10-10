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

        typedef void (*TPortFunc)(TPortArgs*);

        class TPortCmd;

        class TPortHead {
        public:
            /* 0x00 */ TPortCmd* mFirst;
            /* 0x04 */ TPortCmd* mLast;
        };

        class TPortCmd {
        public:
            TPortCmd();
            ~TPortCmd() {}
            bool addPortCmdOnce();
            bool setPortCmd(TPortFunc, TPortArgs*);
            bool addPortCmd(TPortHead*);

            TPortHead* getHead() { return mHead; }
            void setHead(TPortHead* head) { mHead = head; }
            TPortCmd* getNext() { return mNext; }
            TPortFunc getFunc() { return mFunc; }
            TPortArgs* getArgs() { return mArgs; }

        private:
            /* 0x00 */ TPortHead* mHead;
            /* 0x04 */ TPortCmd* mNext;
            /* 0x08 */ TPortFunc mFunc;
            /* 0x0C */ TPortArgs* mArgs;
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
