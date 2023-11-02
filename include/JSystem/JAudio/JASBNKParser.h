#ifndef JASBNKPARSER_H
#define JASBNKPARSER_H

#include "dolphin/types.h"

namespace JASystem {
    class TBasicBank;
    namespace BNKParser {
        struct THeader;
        struct TInst;
        struct TKeymap;
        struct TOsc;
        struct TPerc;
        struct TPmap;
        struct TRand;
        struct TSense;
        struct TVmap;

        TBasicBank* createBasicBank(void*);
        void findOscPtr(JASystem::TBasicBank*, JASystem::BNKParser::THeader*, JASystem::BNKParser::TOsc*);
        void getOscTableEndPtr(short*);
    };
}

#endif /* JASBNKPARSER_H */
