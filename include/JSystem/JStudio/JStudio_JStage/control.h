#ifndef JSTUDIO_JSTAGE_CONTROL_H
#define JSTUDIO_JSTAGE_CONTROL_H

#include "JSystem/JStage/JSGActor.h"
#include "JSystem/JStage/JSGAmbientLight.h"
#include "JSystem/JStage/JSGCamera.h"
#include "JSystem/JStage/JSGFog.h"
#include "JSystem/JStage/JSGLight.h"
#include "JSystem/JStage/JSGSystem.h"
#include "JSystem/JStudio/JStudio/jstudio-object.h"

namespace JStudio_JStage {
struct TCreateObject : public JStudio::TCreateObject {
    TCreateObject(const JStage::TSystem* pSystem) {
        mSystem = pSystem;
    }

    virtual ~TCreateObject();
    virtual bool create(JStudio::TObject**, JStudio::stb::data::TParse_TBlock_object const&);
    virtual JStage::TObject* find(const JStudio::stb::data::TParse_TBlock_object&, JStage::TEObject);

    /* 0x0C */ const JStage::TSystem* mSystem;
};

template <typename Adaptor, typename Object>
struct TVariableValueOutput_object_ : public JStudio::TVariableValue::TOutput {
    typedef void (Object::*Setter)(f32);
    typedef f32 (Object::*Getter)() const;

    TVariableValueOutput_object_(int valueIndex, Setter setter, Getter getter)
        : TOutput()
        , mValueIndex(valueIndex)
        , mSetter(setter)
        , mGetter(getter)
    {
    }

    virtual void operator()(f32 value, JStudio::TAdaptor* adaptor) const // _08 (weak)
    {
        (static_cast<Object*>(static_cast<Adaptor*>(adaptor)->mObject)->*mSetter)(value);
    }
    virtual ~TVariableValueOutput_object_() { } // _0C (weak)

    int mValueIndex; // _04
    Setter mSetter;  // _08
    Getter mGetter;  // _14
};

struct TAdaptor_object_ {
    static void adaptor_data_(JStage::TObject*, void const*, u32, void const*, u32);
    static void adaptor_ENABLE_(JStage::TObject*, JStudio::data::TEOperationData, void const*, u32);

    /* 0x0 */ JStudio::TAdaptor* field_0x0;
    /* 0x4 */ JStage::TSystem* mSystem;
    /* 0x8 */ JStage::TObject* mObject;
};

struct TAdaptor_actor : public JStudio::TAdaptor_actor, public JStudio_JStage::TAdaptor_object_ {
    struct TVVOutput_ANIMATION_FRAME_ {
        void operator()(f32, JStudio::TAdaptor*) const;
        ~TVVOutput_ANIMATION_FRAME_();
    };

    TAdaptor_actor(JStage::TSystem const*, JStage::TActor*);

    virtual ~TAdaptor_actor();
    virtual void adaptor_do_prepare(const JStudio::TObject*);
    virtual void adaptor_do_begin(const JStudio::TObject*);
    virtual void adaptor_do_end(const JStudio::TObject*);
    virtual void adaptor_do_update(const JStudio::TObject*, u32);
    virtual void adaptor_do_data(const JStudio::TObject*, void const*, u32, void const*, u32);
    virtual void adaptor_do_PARENT(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_PARENT_NODE(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_PARENT_ENABLE(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_PARENT_FUNCTION(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_RELATION(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_RELATION_NODE(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_RELATION_ENABLE(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_SHAPE(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_ANIMATION(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_ANIMATION_MODE(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_TEXTURE_ANIMATION(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_TEXTURE_ANIMATION_MODE(JStudio::data::TEOperationData, void const*, u32);
    
    void setJSG_ID_(void (JStage::TActor::*)(u32),
                                    JStudio::data::TEOperationData, void const*, u32);
    void setJSG_SRT_(JStudio::TControl const*);
    void getJSG_SRT_(JStudio::TControl const*);

    static u8 saoVVOutput_[64];
    static u8 saoVVOutput_ANIMATION_FRAME_[144 + 4 /* padding */];

    /* 0x130 */ u8 field_0x130[0x144 - 0x130];
};  // Size: 0x144

struct TAdaptor_ambientLight : public JStudio::TAdaptor_ambientLight {
    TAdaptor_ambientLight(JStage::TSystem const*, JStage::TAmbientLight*);

    virtual ~TAdaptor_ambientLight();
    virtual void adaptor_do_prepare(const JStudio::TObject*);
    virtual void adaptor_do_begin(const JStudio::TObject*);
    virtual void adaptor_do_end(const JStudio::TObject*);
    virtual void adaptor_do_update(const JStudio::TObject*, u32);
    virtual void adaptor_do_data(const JStudio::TObject*, void const*, u32, void const*, u32);

    /* 0x5C */ const JStage::TSystem* mSystem;
    /* 0x60 */ JStage::TAmbientLight* mLight;
};  // Size: 0x64

struct TAdaptor_camera : public JStudio::TAdaptor_camera {
    TAdaptor_camera(JStage::TSystem const*, JStage::TCamera*);
    virtual ~TAdaptor_camera();
    virtual void adaptor_do_prepare(const JStudio::TObject*);
    virtual void adaptor_do_begin(const JStudio::TObject*);
    virtual void adaptor_do_end(const JStudio::TObject*);
    virtual void adaptor_do_update(const JStudio::TObject*, u32);
    virtual void adaptor_do_data(const JStudio::TObject*, void const*, u32, void const*, u32);
    virtual void adaptor_do_PARENT(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_PARENT_NODE(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_PARENT_ENABLE(JStudio::data::TEOperationData, void const*, u32);

    void setJSG_position_(JStudio::TControl const*);
    void getJSG_position_(JStudio::TControl const*);
    void setJSG_targetPosition_(JStudio::TControl const*);
    void getJSG_targetPosition_(JStudio::TControl const*);

    static u8 saoVVOutput_[160 + 4 /* padding */];

    /* 0xE8 */ u8 field_0xE8[0xF8 - 0xE8];
};  // Size: 0xF8

struct TAdaptor_fog : public JStudio::TAdaptor_fog {
    typedef TVariableValueOutput_object_<TAdaptor_fog, JStage::TFog> TVVOutput;

    TAdaptor_fog(JStage::TSystem const*, JStage::TFog*);
    virtual ~TAdaptor_fog();
    virtual void adaptor_do_prepare(const JStudio::TObject*);
    virtual void adaptor_do_begin(const JStudio::TObject*);
    virtual void adaptor_do_end(const JStudio::TObject*);
    virtual void adaptor_do_update(const JStudio::TObject*, u32);
    virtual void adaptor_do_data(const JStudio::TObject*, void const*, u32, void const*, u32);

    static const TVVOutput saoVVOutput_[3];

    /* 0x84 */ const JStage::TSystem* mSystem;
    /* 0x88 */ JStage::TFog* mObject;
};  // Size: 0x8C

struct TAdaptor_light : public JStudio::TAdaptor_light {
    struct TVVOutput_direction_ {
        void operator()(f32, JStudio::TAdaptor*) const;
        ~TVVOutput_direction_();
    };

    TAdaptor_light(JStage::TSystem const*, JStage::TLight*);
    virtual ~TAdaptor_light();
    virtual void adaptor_do_prepare(const JStudio::TObject*);
    virtual void adaptor_do_begin(const JStudio::TObject*);
    virtual void adaptor_do_end(const JStudio::TObject*);
    virtual void adaptor_do_update(const JStudio::TObject*, u32);
    virtual void adaptor_do_data(const JStudio::TObject*, void const*, u32, void const*, u32);
    virtual void adaptor_do_ENABLE(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_FACULTY(JStudio::data::TEOperationData, void const*, u32);

    static u8 saoVVOutput_direction_[72];

    /* 0x110 */ u8 field_0x110[0x11C - 0x110];
};  // Size: 0x11C

void
    transform_toGlobalFromLocal(f32 (*)[4],
                                JStudio::TControl::TTransform_translation_rotation_scaling const&,
                                JStage::TObject const*, u32);
void transform_toGlobalFromLocal(f32 (*)[4],
                                                JStudio::TControl::TTransform_position const&,
                                                JStage::TObject const*, u32);
void
    transform_toLocalFromGlobal(f32 (*)[4],
                                JStudio::TControl::TTransform_translation_rotation_scaling const&,
                                JStage::TObject const*, u32);
void transform_toLocalFromGlobal(f32 (*)[4],
                                                JStudio::TControl::TTransform_position const&,
                                                JStage::TObject const*, u32);
};  // namespace JStudio_JStage

#endif /* JSTUDIO_JSTAGE_CONTROL_H */
