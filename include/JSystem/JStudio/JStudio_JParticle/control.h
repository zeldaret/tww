#ifndef JSTUDIO_JPARTICLE_CONTROL_H
#define JSTUDIO_JPARTICLE_CONTROL_H

#include "JSystem/JParticle/JPAParticle.h"
#include "JSystem/JStage/JSGSystem.h"
#include "JSystem/JStudio/JStudio/jstudio-object.h"

namespace JStudio_JParticle {
struct TCreateObject : public JStudio::TCreateObject {
    TCreateObject(JPAEmitterManager* p_emitMgr, const JStage::TSystem* p_system) {
        pJPAEmitterManager_ = p_emitMgr;
        pJSGSystem_ = p_system;
        mPermit_onExit_notEnd = false;
    }

    virtual ~TCreateObject();
    virtual bool create(JStudio::TObject**, JStudio::stb::data::TParse_TBlock_object const&);

    /* 0x0C */ JPAEmitterManager* pJPAEmitterManager_;
    /* 0x10 */ const JStage::TSystem* pJSGSystem_;
    /* 0x14 */ bool mPermit_onExit_notEnd;
};

struct TAdaptor_particle : public JStudio::TAdaptor_particle {
	struct TJPACallback_ : JPACallBackBase<JPABaseEmitter*> {
		inline TJPACallback_(TAdaptor_particle* adaptor)
		    : mAdaptor(adaptor)
		    , mObject(NULL)
		{
		}

		virtual ~TJPACallback_() { }           // _08 (weak)
		virtual void execute(JPABaseEmitter*); // _0C

		TAdaptor_particle* mAdaptor;     // _04
		const JStudio::TObject* mObject; // _08
	};

    TAdaptor_particle(JPAEmitterManager*, const JStage::TSystem*);
    void beginParticle_fadeIn_();
    void endParticle_fadeOut_(u32);

    virtual ~TAdaptor_particle();
    virtual void adaptor_do_prepare(const JStudio::TObject*);
    virtual void adaptor_do_end(const JStudio::TObject*);
    virtual void adaptor_do_update(const JStudio::TObject*, u32);
    virtual void adaptor_do_PARTICLE(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_PARENT(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_PARENT_NODE(JStudio::data::TEOperationData, void const*, u32);
    virtual void adaptor_do_PARENT_ENABLE(JStudio::data::TEOperationData, void const*, u32);

	/* 0x19C */ JPAEmitterManager* mEmitterManager;
	/* 0x1A0 */ JPABaseEmitter* mEmitter;
	/* 0x1A4 */ TJPACallback_ mCallback;
	/* 0x1B0 */ int _188;
	/* 0x1B4 */ u32 _18C;
	/* 0x1B8 */ u32 _190;
	/* 0x1BC */ u32 _194;
	/* 0x1C0 */ const JStage::TSystem* mSystem;
	/* 0x1C4 */ JStage::TObject* _19C;
	/* 0x1C8 */ u32 _1A0;
	/* 0x1CC */ bool _1A4;
};  // Size: 0x1D0

};  // namespace JStudio_JParticle

#endif /* JSTUDIO_JPARTICLE_CONTROL_H */
