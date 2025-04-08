#ifndef JSGOBJECT_H
#define JSGOBJECT_H

#include "dolphin/mtx/mtxvec.h"

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

    struct TObject {
        void JSGFDisableFlag(u32 flag) { JSGSetFlag(JSGGetFlag() & ~flag); }
        void JSGFEnableFlag(u32 flag) { JSGSetFlag(JSGGetFlag() | flag); }
        
        virtual ~TObject() = 0;
        virtual s32 JSGFGetType() const = 0;
        virtual bool JSGGetName() const;
        virtual u32 JSGGetFlag() const;
        virtual void JSGSetFlag(u32);
        virtual bool JSGGetData(u32, void*, u32) const;
        virtual void JSGSetData(u32, void const*, u32);
        virtual void JSGGetParent(JStage::TObject**, u32*) const;
        virtual void JSGSetParent(JStage::TObject*, u32);
        virtual void JSGSetRelation(bool, JStage::TObject*, u32);
        virtual s32 JSGFindNodeID(char const*) const;
        virtual bool JSGGetNodeTransformation(u32, MtxP) const;
    };
};

#endif /* JSGOBJECT_H */
