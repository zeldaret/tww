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
        pJSGSystem_ = pSystem;
    }

    virtual ~TCreateObject();
    virtual bool create(JStudio::TObject**, JStudio::stb::data::TParse_TBlock_object const&);
    virtual void find(const JStudio::stb::data::TParse_TBlock_object&, JStage::TEObject);

    /* 0x0C */ const JStage::TSystem* pJSGSystem_;
};

struct TAdaptor_object_ {
    void adaptor_data_(JStage::TObject*, void const*, u32, void const*, u32);
    void adaptor_ENABLE_(JStage::TObject*, JStudio::data::TEOperationData, void const*, u32);

    /* 0x0 */ JStudio::TAdaptor* field_0x0;
    /* 0x4 */ JStage::TSystem* pJSGSystem_;
    /* 0x8 */ JStage::TObject* pJSGObject_;
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
    virtual void adaptor_do_PARENT_NODE(JStudio::data::TEOperationData, void const*,
                                                u32);
    virtual void adaptor_do_PARENT_ENABLE(JStudio::data::TEOperationData, void const*,
                                                    u32);
    virtual void adaptor_do_PARENT_FUNCTION(JStudio::data::TEOperationData, void const*,
                                                    u32);
    virtual void adaptor_do_RELATION(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_RELATION_NODE(JStudio::data::TEOperationData, void const*,
                                                    u32);
    virtual void adaptor_do_RELATION_ENABLE(JStudio::data::TEOperationData, void const*,
                                                    u32);
    virtual void adaptor_do_SHAPE(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_ANIMATION(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_ANIMATION_MODE(JStudio::data::TEOperationData, void const*,
                                                    u32);
    virtual void adaptor_do_TEXTURE_ANIMATION(JStudio::data::TEOperationData,
                                                        void const*, u32);
    virtual void adaptor_do_TEXTURE_ANIMATION_MODE(JStudio::data::TEOperationData,
                                                            void const*, u32);
    
    void setJSG_ID_(void (JStage::TActor::*)(u32),
                                    JStudio::data::TEOperationData, void const*, u32);
    void setJSG_SRT_(JStudio::TControl const*);
    void getJSG_SRT_(JStudio::TControl const*);

    static u8 saoVVOutput_[64];
    static u8 saoVVOutput_ANIMATION_FRAME_[144 + 4 /* padding */];

    /* 0x134 */ u32 field_0x134;
    /* 0x138 */ u32 field_0x138;
    /* 0x13C */ u32 field_0x13c;
    /* 0x140 */ u32 field_0x140;
    /* 0x144 */ u32 field_0x144;
    /* 0x148 */ u8 field_0x148;
    /* 0x14C */ u32 field_0x14c;
    /* 0x150 */ u32 field_0x150;
};

struct TAdaptor_ambientLight : public JStudio::TAdaptor_ambientLight {
    TAdaptor_ambientLight(JStage::TSystem const*, JStage::TAmbientLight*);

    virtual ~TAdaptor_ambientLight();
    virtual void adaptor_do_prepare(const JStudio::TObject*);
    virtual void adaptor_do_begin(const JStudio::TObject*);
    virtual void adaptor_do_end(const JStudio::TObject*);
    virtual void adaptor_do_update(const JStudio::TObject*, u32);
    virtual void adaptor_do_data(const JStudio::TObject*, void const*, u32, void const*, u32);
};

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
    virtual void adaptor_do_PARENT_FUNCTION(JStudio::data::TEOperationData, void const*,
                                                   u32);
    virtual void adaptor_do_TARGET_PARENT(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_TARGET_PARENT_NODE(JStudio::data::TEOperationData, void const*,
                                                      u32);
    virtual void adaptor_do_TARGET_PARENT_ENABLE(JStudio::data::TEOperationData, void const*,
                                                        u32);

    void setJSG_position_(JStudio::TControl const*);
    void getJSG_position_(JStudio::TControl const*);
    void setJSG_targetPosition_(JStudio::TControl const*);
    void getJSG_targetPosition_(JStudio::TControl const*);

    static u8 saoVVOutput_[160 + 4 /* padding */];
};

struct TAdaptor_fog : public JStudio::TAdaptor_fog {
    TAdaptor_fog(JStage::TSystem const*, JStage::TFog*);
    virtual ~TAdaptor_fog();
    virtual void adaptor_do_prepare(const JStudio::TObject*);
    virtual void adaptor_do_begin(const JStudio::TObject*);
    virtual void adaptor_do_end(const JStudio::TObject*);
    virtual void adaptor_do_update(const JStudio::TObject*, u32);
    virtual void adaptor_do_data(const JStudio::TObject*, void const*, u32, void const*, u32);

    static u8 saoVVOutput_[96 + 4 /* padding */];
};

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
};

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
