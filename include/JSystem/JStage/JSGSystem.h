#ifndef JSGSYSTEM_H
#define JSGSYSTEM_H

#include "JSystem/JStage/JSGObject.h"

namespace JStage {
    struct TSystem : public TObject {
        virtual ~TSystem() = 0;
        virtual s32 JSGFGetType() const;
        virtual void* JSGFindObject(char const*, JStage::TEObject) const;
        virtual bool JSGCreateObject(char const*, JStage::TEObject, u32);
        virtual void JSGDestroyObject(JStage::TObject*);
        virtual bool JSGGetSystemData(u32);
        virtual void JSGSetSystemData(u32, u32);
    };
};

#endif /* JSGSYSTEM_H */
