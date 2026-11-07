#ifndef JSGAMBIENTLIGHT_H
#define JSGAMBIENTLIGHT_H

#include "JSystem/JStage/JSGObject.h"
#include "dolphin/gx/GXStruct.h"

namespace JStage {
    struct TAmbientLight : public TObject {
        virtual ~TAmbientLight() = 0;
        virtual s32 JSGFGetType() const;
        virtual GXColor JSGGetColor() const;
        virtual void JSGSetColor(GXColor);
    };
};

#endif /* JSGAMBIENTLIGHT_H */
