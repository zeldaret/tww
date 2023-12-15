#ifndef RESOURCE_H
#define RESOURCE_H

#include <dolphin/types.h>

namespace JMessage {
    class TResource {
    public:
        TResource() {
            field_0x0 = 0;
            field_0x4 = 0;
            field_0x8 = 0;
            field_0xc = 0;
            field_0x10 = 0;
            field_0x14 = 0;
            field_0x18 = 0;
        }

        int field_0x0;
        int field_0x4;
        int field_0x8;
        int field_0xc;
        int field_0x10;
        int field_0x14;
        int field_0x18;
    };
    class TResourceContainer {
    public:
        int field_0x0;
        int field_0x4;
        int field_0x8;

        TResourceContainer();
        virtual ~TResourceContainer();
        void Get_groupID(u16);
        void SetEncoding(u8);
        virtual TResource* Do_create();
        virtual void Do_destroy(JMessage::TResource*);
        void SetEncoding_(u8);

        u8 field_0x10;
        bool (*field_0x14)(int);
    };

    class TParse {
    public:
        TParse(JMessage::TResourceContainer*);
        virtual ~TParse();
        virtual void parseHeader_next(const void**, u32*, u32);
        virtual void parseBlock_next(const void**, u32*, u32);
    };
}

#endif /* RESOURCE_H */
