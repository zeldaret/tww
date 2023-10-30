#ifndef JSGSYSTEM_H
#define JSGSYSTEM_H

#include "JSystem/JStage/JSGObject.h"

namespace JStage {
    enum TEObject {
        /* 0x0 */ TOBJ_ACTOR_UNK,
        /* 0x1 */ TOBJ_UNK1,
        /* 0x2 */ TOBJ_ACTOR,
        /* 0x3 */ TOBJ_CAMERA,
        /* 0x4 */ TOBJ_AMBIENT,
        /* 0x5 */ TOBJ_LIGHT,
        /* 0x6 */ TOBJ_FOG,
    };

    struct TSystem : public TObject {
        virtual ~TSystem() = 0;
        virtual s32 JSGFGetType() const;
        virtual bool JSGFindObject(char const*, JStage::TEObject) const;
        virtual bool JSGCreateObject(char const*, JStage::TEObject, u32);
        virtual void JSGDestroyObject(JStage::TObject*);
        virtual bool JSGGetSystemData(u32);
        virtual void JSGSetSystemData(u32, u32);
    };
};

#endif /* JSGSYSTEM_H */
