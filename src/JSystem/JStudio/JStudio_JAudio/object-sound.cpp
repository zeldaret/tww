//
// Generated by dtk
// Translation Unit: object-sound.cpp
//

#include "JSystem/JStudio/JStudio_JAudio/object-sound.h"
#include "JSystem/JAudio/JAISound.h"
#include "JSystem/JAudio/JAIBasic.h"
#include "math.h"
#include "dolphin/types.h"

namespace JStudio_JAudio {

/* 80278D20-80278DC0       .text __ct__Q214JStudio_JAudio14TAdaptor_soundFP8JAIBasic */
TAdaptor_sound::TAdaptor_sound(JAIBasic* basic) {
    mpBasic = basic;
    mpSound = NULL;
    mFlags = ~0;
    mPosition = NULL;
}

/* 80278DC0-80278E38       .text __dt__Q214JStudio_JAudio14TAdaptor_soundFv */
TAdaptor_sound::~TAdaptor_sound() {
    if (mpSound != NULL) {
        mpSound->stop(0);
    }
}

/* 80278E38-80278F40       .text adaptor_do_prepare__Q214JStudio_JAudio14TAdaptor_soundFPCQ27JStudio7TObject */
void TAdaptor_sound::adaptor_do_prepare(const JStudio::TObject* param_1) {
    static TSetVariableValue_immediate aoData[] = {
        TSetVariableValue_immediate(0, 0.0f),
        TSetVariableValue_immediate(1, 0.0f),
        TSetVariableValue_immediate(2, 0.0f),
        TSetVariableValue_immediate(0xFFFFFFFF, NAN),
    };
    adaptor_setVariableValue_immediate(aoData);
    mVariableValues[3].setOutput(&TAdaptor_sound::soVVOOn_BEGIN_FADE_IN_);
    mVariableValues[4].setOutput(&TAdaptor_sound::soVVOOn_END_FADE_OUT_);

    for (TAdaptor_sound::TVVOSetValue_* value = TAdaptor_sound::saoVVOSetValue_; value->mValueIndex != -1; value++) {
        mVariableValues[value->mValueIndex].setOutput(value);
    }
}

TAdaptor_sound::TVVOOn_BEGIN_FADE_IN_ TAdaptor_sound::soVVOOn_BEGIN_FADE_IN_;
TAdaptor_sound::TVVOOn_END_FADE_OUT_ TAdaptor_sound::soVVOOn_END_FADE_OUT_;
TAdaptor_sound::TVVOSetValue_ TAdaptor_sound::saoVVOSetValue_[] = {
    TAdaptor_sound::TVVOSetValue_(UNK_6_e, &JAISound::setDemoVolume),
    TAdaptor_sound::TVVOSetValue_(UNK_7_e, &JAISound::setDemoPan),
    TAdaptor_sound::TVVOSetValue_(UNK_8_e, &JAISound::setDemoPitch),
    TAdaptor_sound::TVVOSetValue_(UNK_9_e, &JAISound::setTempoProportion),
    TAdaptor_sound::TVVOSetValue_(UNK_A_e, &JAISound::setDemoFxmix),
    TAdaptor_sound::TVVOSetValue_(UNK_MINUS1_e, NULL),
};

/* 80278F40-80278FB8       .text adaptor_do_update__Q214JStudio_JAudio14TAdaptor_soundFPCQ27JStudio7TObjectUl */
void TAdaptor_sound::adaptor_do_update(const JStudio::TObject* object, u32) {
    JStudio::TControl* control = (JStudio::TControl*)object->getControl();
    Vec* r30 = &_F8;
    adaptor_getVariableValue_Vec(r30, sauVariableValue_3_POSITION_XYZ);
    if (control->mTransformOnSet) {
        Vec temp;
        MTXMultVec(control->mTransformOnSet_Matrix, r30, &temp);
        *r30 = temp;
    }
}

/* 80278FB8-80279064       .text adaptor_do_SOUND__Q214JStudio_JAudio14TAdaptor_soundFQ37JStudio4data15TEOperationDataPCvUl */
void TAdaptor_sound::adaptor_do_SOUND(JStudio::data::TEOperationData op, const void* data, u32) {
    switch (op) {
    case JStudio::data::TEOD_Unknown_19:
        u32 flags = *(s32*)data;
        if (flags & 0xc0000000) {
            if (mpSound) {
                mpSound->stop(0);
            }
            mFlags = flags;
            mpBasic->prepareSoundVec(flags, &mpSound, mPosition, 0, 0, 4);
            if (!mpSound) {
                return;
            }
        } else {
            mFlags = *(s32*)data;
        }
    }
}

/* 80279064-8027908C       .text adaptor_do_LOCATED__Q214JStudio_JAudio14TAdaptor_soundFQ37JStudio4data15TEOperationDataPCvUl */
void TAdaptor_sound::adaptor_do_LOCATED(JStudio::data::TEOperationData op, const void* data, u32 flag) {
    switch (op) {
    case JStudio::data::TEOD_Unknown_02:
        Vec* pos  = *(Vec**)data;
        mPosition = NULL;
        if (!pos)
            return;
        mPosition = &_F8;
        break;
    }
}

/* 8027908C-8027915C       .text __cl__Q314JStudio_JAudio14TAdaptor_sound21TVVOOn_BEGIN_FADE_IN_CFfPQ27JStudio8TAdaptor */
void TAdaptor_sound::TVVOOn_BEGIN_FADE_IN_::operator()(f32 value, JStudio::TAdaptor* adaptor) const {
    JStudio_JAudio::TAdaptor_sound* adaptor_sound = (JStudio_JAudio::TAdaptor_sound*)adaptor;
    JAISound* sound = adaptor_sound->mpSound;
    u32 flags = adaptor_sound->mFlags;
    if (flags & 0xc0000000) {
        if (adaptor_sound->mpSound) {
            adaptor_sound->mpSound->start(value);
        }
    } else {
        if (adaptor_sound->mpSound) {
            if (!adaptor_sound->mpBasic->checkEnablePrepare(adaptor_sound->mFlags)) {
                adaptor_sound->mpSound->stop(0);
            }
        }
        adaptor_sound->mpBasic->startSoundVec(flags, &adaptor_sound->mpSound, adaptor_sound->mPosition, value, 0, 4);
        if (!adaptor_sound->mpSound) {
            return;
        }
    }
}

/* 8027915C-8027919C       .text __cl__Q314JStudio_JAudio14TAdaptor_sound20TVVOOn_END_FADE_OUT_CFfPQ27JStudio8TAdaptor */
void TAdaptor_sound::TVVOOn_END_FADE_OUT_::operator()(f32 value, JStudio::TAdaptor* adaptor) const {
    JAISound* sound = ((JStudio_JAudio::TAdaptor_sound*)adaptor)->mpSound;
    if (sound) {
        sound->stop(value);
    }
}

/* 8027919C-802791D8       .text __cl__Q314JStudio_JAudio14TAdaptor_sound13TVVOSetValue_CFfPQ27JStudio8TAdaptor */
void TAdaptor_sound::TVVOSetValue_::operator()(f32 value, JStudio::TAdaptor* adaptor) const {
    JAISound* sound = ((JStudio_JAudio::TAdaptor_sound*)adaptor)->mpSound;
    if (sound) {
        (sound->*(this->mSetFunc))(value, 0);
    }
}

}; // namespace JStudio_JAudio
