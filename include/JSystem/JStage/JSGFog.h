#ifndef JSGFOG_H
#define JSGFOG_H

#include "JSystem/JStage/JSGObject.h"
#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"

namespace JStage {
    struct TFog : public TObject {
        void JSGFDisableFlag(u32 flag) { JSGSetFlag(JSGGetFlag() & ~flag); }
        void JSGFEnableFlag(u32 flag) { JSGSetFlag(JSGGetFlag() | flag); }
        
        virtual ~TFog() = 0;
        virtual s32 JSGFGetType() const;
        virtual bool JSGGetFogFunction() const;
        virtual void JSGSetFogFunction(GXFogType);
        virtual f32 JSGGetStartZ() const;
        virtual void JSGSetStartZ(f32);
        virtual f32 JSGGetEndZ() const;
        virtual void JSGSetEndZ(f32);
        virtual GXColor JSGGetColor() const;
        virtual void JSGSetColor(GXColor);
    };
};

#endif /* JSGFOG_H */
