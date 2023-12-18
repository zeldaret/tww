#ifndef JAISYSTEMINTERFACE_H
#define JAISYSTEMINTERFACE_H

#include "JSystem/JAudio/JASCmdStack.h"

class JAISound;

namespace JASystem {
    class TTrack;
    namespace Kernel {
        class TPortArgs;
    }
}

namespace JAInter {
    class SeqUpdateData;
    namespace SystemInterface {
        s32 checkFileExsistence(char*);
        int checkSeqActiveFlag(JASystem::TTrack*);
        void trackToSeqp(JAISound*, u8);
        void setSeqPortargsF32(JAInter::SeqUpdateData*, u32, u8, f32);
        void setSeqPortargsU32(JAInter::SeqUpdateData*, u32, u8, u32);
        void rootInit(JAInter::SeqUpdateData*);
        void trackInit(JAInter::SeqUpdateData*);
        void outerInit(JAInter::SeqUpdateData*, void*, u32, u16, u8);
        void setPortParameter(JASystem::Kernel::TPortArgs*, JASystem::TTrack*, u32, u32);
        void setSePortParameter(JASystem::Kernel::TPortArgs*);

        extern JASystem::Kernel::TPortCmd systemPortCmd;
    }
}

#endif /* JAISYSTEMINTERFACE_H */
