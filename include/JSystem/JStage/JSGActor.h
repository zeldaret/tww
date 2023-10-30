#ifndef JSGACTOR_H
#define JSGACTOR_H

#include "JSystem/JStage/JSGObject.h"

namespace JStage {
    struct TActor : public TObject {
        virtual ~TActor() = 0;
        virtual s32 JSGFGetType() const;
        virtual void JSGGetTranslation(Vec*) const;
        virtual void JSGSetTranslation(Vec const&);
        virtual void JSGGetScaling(Vec*) const;
        virtual void JSGSetScaling(Vec const&);
        virtual void JSGGetRotation(Vec*) const;
        virtual void JSGSetRotation(Vec const&);
        virtual s32 JSGGetShape() const;
        virtual void JSGSetShape(u32);
        virtual s32 JSGGetAnimation() const;
        virtual void JSGSetAnimation(u32);
        virtual f32 JSGGetAnimationFrame() const;
        virtual void JSGSetAnimationFrame(f32);
        virtual f32 JSGGetAnimationFrameMax() const;
        virtual f32 JSGGetAnimationTransition() const;
        virtual void JSGSetAnimationTransition(f32);
        virtual s32 JSGGetTextureAnimation() const;
        virtual void JSGSetTextureAnimation(u32);
        virtual f32 JSGGetTextureAnimationFrame() const;
        virtual void JSGSetTextureAnimationFrame(f32);
        virtual f32 JSGGetTextureAnimationFrameMax() const;
    };
};

#endif /* JSGACTOR_H */
