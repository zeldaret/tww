#ifndef JSGOBJECT_H
#define JSGOBJECT_H

#include "dolphin/mtx/mtxvec.h"

namespace JStage {
    struct TObject {
        virtual ~TObject() = 0;
        virtual s32 JSGFGetType() const = 0;
        virtual bool JSGGetName() const;
        virtual bool JSGGetFlag() const;
        virtual void JSGSetFlag(u32);
        virtual bool JSGGetData(u32, void*, u32) const;
        virtual void JSGSetData(u32, void const*, u32);
        virtual void JSGGetParent(JStage::TObject**, u32*) const;
        virtual void JSGSetParent(JStage::TObject*, u32);
        virtual void JSGSetRelation(bool, JStage::TObject*, u32);
        virtual s32 JSGFindNodeID(char const*) const;
        virtual int JSGGetNodeTransformation(u32, MtxP) const;
    };
};

#endif /* JSGOBJECT_H */
