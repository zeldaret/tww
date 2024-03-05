#ifndef JSTUDIO_JAUDIO_CONTROL_H
#define JSTUDIO_JAUDIO_CONTROL_H

#include "dolphin/gx/GX.h"
#include "JSystem/JStudio/JStudio/jstudio-object.h"
#include "JSystem/JStage/JSGSystem.h"

struct JAIBasic;
struct JAISound;
namespace JStudio_JAudio {
typedef JStudio::TObject* (*JStudioAudioCreateFunc)(const JStudio::stb::data::TParse_TBlock_object&, JAIBasic*);

struct TAdaptor_sound : public JStudio::TAdaptor_sound {
    struct TVVOOn_BEGIN_FADE_IN_ : public JStudio::TVariableValue::TOutput {
        void operator()(float, JStudio::TAdaptor*) const;
    };

    struct TVVOOn_END_FADE_OUT_ : public JStudio::TVariableValue::TOutput {
        void operator()(float, JStudio::TAdaptor*) const;
    };

	struct TVVOSetValue_ : public JStudio::TVariableValue::TOutput {
		virtual void operator()(f32, JStudio::TAdaptor*) const; // _08
		virtual ~TVVOSetValue_();                               // _0C (weak)

		// _00 = VTBL
		int _04; // _04
		u32 _08; // _08, unknown
		int _0C; // _0C
		int _10; // _10
	};

    static TVVOOn_BEGIN_FADE_IN_ soVVOOn_BEGIN_FADE_IN_;
    static TVVOOn_END_FADE_OUT_ soVVOOn_END_FADE_OUT_;
    static TVVOSetValue_ saoVVOSetValue_[];

	TAdaptor_sound(JAIBasic*);

	virtual ~TAdaptor_sound();                                                               // _08
	virtual void adaptor_do_prepare(const JStudio::TObject*);                                // _0C
	virtual void adaptor_do_end(const JStudio::TObject*);                                    // _14
	virtual void adaptor_do_update(const JStudio::TObject*, u32);                            // _18
	virtual void adaptor_do_SOUND(JStudio::data::TEOperationData, const void*, u32);         // _20
	virtual void adaptor_do_BEGIN(JStudio::data::TEOperationData, const void*, u32);         // _24
	virtual void adaptor_do_BEGIN_FADE_IN(JStudio::data::TEOperationData, const void*, u32); // _28
	virtual void adaptor_do_END(JStudio::data::TEOperationData, const void*, u32);           // _2C
	virtual void adaptor_do_END_FADE_OUT(JStudio::data::TEOperationData, const void*, u32);  // _30
	virtual void adaptor_do_PARENT(JStudio::data::TEOperationData, const void*, u32);        // _34
	virtual void adaptor_do_PARENT_NODE(JStudio::data::TEOperationData, const void*, u32);   // _38
	virtual void adaptor_do_PARENT_ENABLE(JStudio::data::TEOperationData, const void*, u32); // _3C
	virtual void adaptor_do_LOCATED(JStudio::data::TEOperationData, const void*, u32);       // _40

	void beginSound_fadeIn_(u32);
	void endSound_fadeOut_(u32);

	/* 0x0E8 */ JAIBasic* mpBasic;
	/* 0x0EC */ JAISound* mpSound;
	/* 0x0F0 */ u32 _F0;
	/* 0x0F4 */ int _F4;
    /* 0x0F8 */ u8 _F8[0x104 - 0x0F8];

	// u32 _E4;
	// Vec* _E8;                        // Vector3f* in ghidra, should be Vec* or JGeometry::TVec3* surely
	// Vec _EC;                         // same as above
	// JStage::TSystem* mSystem;
	// JStage::TObject* _FC;
	// u32 _100;
	// u8 _104;
};  // Size: 0x104

struct TCreateObject : public JStudio::TCreateObject {
	TCreateObject(JAIBasic* jai, const JStage::TSystem* system)
	{
		mSound  = jai;
		mSystem = system;
	}
	virtual ~TCreateObject();                                                                                // _08
	virtual bool create(JStudio::TObject** newObject, const JStudio::stb::data::TParse_TBlock_object& data); // _0C

	// _00     = VTBL
	// _00-_0C = JStudio::TCreateObject
	JAIBasic* mSound;               // _04
	const JStage::TSystem* mSystem; // _08
};
} // namespace JStudio_JAudio

#endif /* JSTUDIO_JAUDIO_CONTROL_H */
