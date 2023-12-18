#ifndef JASCMDSTACK_H
#define JASCMDSTACK_H

#include "dolphin/types.h"

namespace JASystem {
    namespace Kernel {
        class TPortArgs;
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
