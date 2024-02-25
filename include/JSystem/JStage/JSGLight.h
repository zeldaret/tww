#ifndef JSGLIGHT_H
#define JSGLIGHT_H

#include "JSystem/JStage/JSGObject.h"
#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"

namespace JStage {
    enum TELight {
        kLightMax = 0xFFFFFFFF,
    };

    struct TLight : public TObject {
        virtual ~TLight() = 0;
        virtual s32 JSGFGetType() const;
        virtual bool JSGGetLightType() const;
        virtual void JSGSetLightType(JStage::TELight);
        virtual void JSGGetPosition(Vec*) const;
        virtual void JSGSetPosition(Vec const&);
        virtual GXColor JSGGetColor() const;
        virtual void JSGSetColor(GXColor);
        virtual void JSGGetDistanceAttenuation(f32*, f32*, GXDistAttnFn*) const;
        virtual void JSGSetDistanceAttenuation(f32, f32, GXDistAttnFn);
        virtual void JSGGetAngleAttenuation(f32*, GXSpotFn*) const;
        virtual void JSGSetAngleAttenuation(f32, GXSpotFn);
        virtual void JSGGetDirection(Vec*) const;
        virtual void JSGSetDirection(Vec const&);
    };
};

#endif /* JSGLIGHT_H */
