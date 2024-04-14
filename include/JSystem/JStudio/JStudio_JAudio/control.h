#ifndef JSTUDIO_JAUDIO_CONTROL_H
#define JSTUDIO_JAUDIO_CONTROL_H

#include "dolphin/gx/GX.h"
#include "JSystem/JStudio/JStudio/jstudio-object.h"
#include "JSystem/JStage/JSGSystem.h"

struct JAIBasic;
struct JAISound;
namespace JStudio_JAudio {
typedef JStudio::TObject* (*JStudioAudioCreateFunc)(const JStudio::stb::data::TParse_TBlock_object&, JAIBasic*);
typedef void (JAISound::*TVVOSoundSetFunc)(f32, u32); // e.g. JAISound::setDirectVolume, JAISound::setDirectPitch

struct TAdaptor_sound : public JStudio::TAdaptor_sound {
    struct TVVOOn_BEGIN_FADE_IN_ : public JStudio::TVariableValue::TOutput {
        void operator()(float, JStudio::TAdaptor*) const;
        virtual ~TVVOOn_BEGIN_FADE_IN_() {}
    };

    struct TVVOOn_END_FADE_OUT_ : public JStudio::TVariableValue::TOutput {
        void operator()(float, JStudio::TAdaptor*) const;
        virtual ~TVVOOn_END_FADE_OUT_() {}
    };

    struct TVVOSetValue_ : public JStudio::TVariableValue::TOutput {
        TVVOSetValue_(JStudio::TAdaptor_sound::TEVariableValue idx, TVVOSoundSetFunc func) {
            mValueIndex = idx;
            mSetFunc = func;
        }

        virtual void operator()(f32, JStudio::TAdaptor*) const;
        virtual ~TVVOSetValue_() {}

        /* 0x00 */ /* JStudio::TVariableValue::TOutput */
        /* 0x04 */ int mValueIndex;
        /* 0x08 */ TVVOSoundSetFunc mSetFunc;
    };  // Size: 0x14

    static TVVOOn_BEGIN_FADE_IN_ soVVOOn_BEGIN_FADE_IN_;
    static TVVOOn_END_FADE_OUT_ soVVOOn_END_FADE_OUT_;
    static TVVOSetValue_ saoVVOSetValue_[];

    TAdaptor_sound(JAIBasic*);

    virtual ~TAdaptor_sound();                                                               // _08
    virtual void adaptor_do_prepare(const JStudio::TObject*);                                // _0C
    virtual void adaptor_do_update(const JStudio::TObject*, u32);                            // _18
    virtual void adaptor_do_SOUND(JStudio::data::TEOperationData, const void*, u32);         // _20
    virtual void adaptor_do_LOCATED(JStudio::data::TEOperationData, const void*, u32);       // _24

    void beginSound_fadeIn_(u32);
    void endSound_fadeOut_(u32);

    /* 0x0E8 */ JAIBasic* mpBasic;
    /* 0x0EC */ JAISound* mpSound;
    /* 0x0F0 */ u32 mFlags;
    /* 0x0F4 */ Vec* mPosition;
    /* 0x0F8 */ Vec _F8;

    // u32 _E4;
    // Vec* _E8;                        // Vector3f* in ghidra, should be Vec* or JGeometry::TVec3* surely
    // Vec _EC;                         // same as above
    // JStage::TSystem* mSystem;
    // JStage::TObject* _FC;
    // u32 _100;
    // u8 _104;
};  // Size: 0x104

struct TCreateObject : public JStudio::TCreateObject {
    TCreateObject(JAIBasic* jai)
    {
        mSound  = jai;
    }
    virtual ~TCreateObject();                                                                                // _08
    virtual bool create(JStudio::TObject** newObject, const JStudio::stb::data::TParse_TBlock_object& data); // _0C

    /* 0x00 */ /* JStudio::TCreateObject */
    /* 0x0C */ JAIBasic* mSound;
};
} // namespace JStudio_JAudio

#endif /* JSTUDIO_JAUDIO_CONTROL_H */
