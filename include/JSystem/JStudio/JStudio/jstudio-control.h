#ifndef JSTUDIO_CONTROL_H
#define JSTUDIO_CONTROL_H

#include "JSystem/JStudio/JStudio/fvb.h"
#include "JSystem/JStudio/JStudio/stb.h"
#include "dolphin/gx/GX.h"
#include "dolphin/mtx/vec.h"
#include "dolphin/mtx/mtxvec.h"

namespace JStudio {
struct TObject;
struct TCreateObject {
    TCreateObject() {}
    virtual ~TCreateObject() = 0;
    virtual bool create(TObject**, stb::data::TParse_TBlock_object const&) = 0;

    /* 0x4 */ JGadget::TLinkListNode mNode;
};  // Size: 0xC

struct TFactory : public stb::TFactory {
    TFactory() {}

    virtual ~TFactory();
    virtual TObject* create(stb::data::TParse_TBlock_object const&);

    void appendCreateObject(TCreateObject*);

    /* 0x04 */ JGadget::TLinkList<TCreateObject, -4> mList;
    /* 0x10 */ fvb::TFactory fvb_Factory;
};

class TControl : public stb::TControl {
public:
    struct TTransform_position {
        Vec mPosition;
    };
    struct TTransform_position_direction {
        Vec mPosition;  // _00
        Vec mDirection; // _0C
    };
    struct TTransform_translation_rotation {};
    struct TTransform_translation_rotation_scaling {};

    TControl();
    virtual ~TControl();
    void transformOnSet_setOrigin(const Vec&, f32);
    void transformOnGet_setOrigin(const Vec&, f32);

    void setFactory(TFactory* factory) {
        stb::TFactory* stb_factory = factory;
        fvb::TFactory* fvb_factory = factory == NULL ? NULL : &factory->fvb_Factory;
        stb::TControl::setFactory(stb_factory);
        fvb_Control.setFactory(fvb_factory);
    }

    void stb_destroyObject_all() { stb::TControl::destroyObject_all(); }
    void fvb_destroyObject_all() { fvb_Control.destroyObject_all(); }

    void destroyObject_all() {
        stb_destroyObject_all();
        fvb_destroyObject_all();
    }

    bool transformOnSet_isEnabled() const { return mTransformOnSet; }
    void transformOnSet_enable(bool param_0) { mTransformOnSet = param_0; }
    bool transformOnGet_isEnabled() const { return mTransformOnGet; }
    void transformOnGet_enable(bool param_0) { mTransformOnGet = param_0; }

    void transform_enable(bool param_0) {
        transformOnGet_enable(param_0);
        transformOnSet_enable(param_0);
    }

    void transform_setOrigin(const Vec& xyz, f32 rotY) {
        transformOnGet_setOrigin(xyz, rotY);
        transformOnSet_setOrigin(xyz, rotY);
    }

    f32 transformOnSet_getRotationY() const { return mTransformOnSet_RotationY; }
    CMtxP transformOnSet_getMatrix() const { return mTransformOnSet_Matrix; }
    CMtxP transformOnGet_getMatrix() const { return mTransformOnGet_Matrix; }

    void setSecondPerFrame(f64 param_0) { mSecondPerFrame = param_0; }
    f64 getSecondPerFrame() const { return mSecondPerFrame; }


    fvb::TObject* fvb_getObject(const void* param_1, u32 param_2) {
        return fvb_Control.getObject(param_1, param_2);
    }

    fvb::TObject* fvb_getObject_index(u32 index) {
        return fvb_Control.getObject_index(index);
    }

    TFunctionValue* getFunctionValue(const void* param_1, u32 param_2) {
        fvb::TObject* obj = fvb_getObject(param_1, param_2);
        if (obj == NULL) {
            return NULL;
        } 
        return obj->referFunctionValue();
    }

    TFunctionValue* getFunctionValue_index(u32 index) {
        fvb::TObject* obj = fvb_getObject_index(index);
        if (obj == NULL) {
            return NULL;
        } 
        return obj->referFunctionValue();
    }
    
    const TTransform_position_direction* transformOnGet_transform_ifEnabled(const TTransform_position_direction& posDir, TTransform_position_direction* transformedPosDir) const {
        if (!transformOnGet_isEnabled()) {
            return &posDir;
        } else {
            transformOnGet_transform(posDir, transformedPosDir);
            return transformedPosDir;
        }
    }
    void transformOnGet_transform(const TTransform_position_direction& posDir, TTransform_position_direction* transformedPosDir) const {
        transformOnGet_transformTranslation(posDir.mPosition, &transformedPosDir->mPosition);
        transformOnGet_transformDirection(posDir.mDirection, &transformedPosDir->mDirection);
    }
    void transformOnGet_transformTranslation(const Vec& pos, Vec* transformedPos) const {
        MTXMultVec(transformOnGet_getMatrix(), &pos, transformedPos);
    }
    void transformOnGet_transformDirection(const Vec& dir, Vec* transformedDir) const {
        MTXMultVecSR(transformOnGet_getMatrix(), &dir, transformedDir);
    }
    
    // TODO
    void fvb_getObjectContainer() const {}
    void fvb_referControl() {}
    void fvb_removeObject_all() {}
    void stb_getObjectContainer() const {}
    void stb_referObjectContainer() {}
    void stb_removeObject(TObject*) {}
    void transformOnGet_transform(const TTransform_position&, TTransform_position*) const {}
    void transformOnGet_transform(const TTransform_translation_rotation&, TTransform_translation_rotation*) const {}
    void transformOnGet_transformRotation(const Vec&, Vec*) const {}
    void transformOnGet_transform_ifEnabled(const TTransform_translation_rotation&, TTransform_translation_rotation*) const {}
    void transformOnSet_transform(const TTransform_position&, TTransform_position*) const {}
    void transformOnSet_transform(const TTransform_position_direction&, TTransform_position_direction*) const {}
    void transformOnSet_transform(const TTransform_translation_rotation&, TTransform_translation_rotation*) const {}
    void transformOnSet_transform(CMtxP, MtxP) const {}
    void transformOnSet_transformDirection(const Vec&, Vec*) const {}
    void transformOnSet_transformDirection_ifEnabled(const Vec&, Vec*) const {}
    void transformOnSet_transformRotation(const Vec&, Vec*) const {}
    void transformOnSet_transformTranslation(const Vec&, Vec*) const {}
    void transformOnSet_transformTranslation_ifEnabled(const Vec&, Vec*) const {}
    void transformOnSet_transform_ifEnabled(const TTransform_position_direction&, TTransform_position_direction*) const {}
    void transformOnSet_transform_ifEnabled(const TTransform_translation_rotation&, TTransform_translation_rotation*) const {}
    void transformOnSet_transform_ifEnabled(CMtxP, MtxP) const {}

    /* 0x58 */ f64 mSecondPerFrame;
    /* 0x60 */ fvb::TControl fvb_Control;
    /* 0x74 */ bool mTransformOnSet;
    /* 0x75 */ bool mTransformOnGet;
    /* 0x78 */ Vec field_0x8c;
    /* 0x84 */ Vec field_0x98;
    /* 0x90 */ f32 mTransformOnSet_RotationY;
    /* 0x94 */ f32 field_0xa8;
    /* 0x98 */ Mtx mTransformOnSet_Matrix;
    /* 0xC8 */ Mtx mTransformOnGet_Matrix;
};

struct TParse : public stb::TParse {
    TParse(TControl*);
    bool parseBlock_block_fvb_(stb::data::TParse_TBlock const&, u32);

    virtual ~TParse();
    virtual bool parseHeader(stb::data::TParse_THeader const&, u32);
    virtual bool parseBlock_block(stb::data::TParse_TBlock const&, u32);

    TControl* getControl() { return (TControl*)stb::TParse::getControl(); }

    /* 0x04 */ fvb::TParse field_0x04;
};

};  // namespace JStudio

#endif /* JSTUDIO_CONTROL_H */
