#ifndef JMESSAGE_CONTROL_H
#define JMESSAGE_CONTROL_H

#include "JSystem/JMessage/processor.h"
#include "dolphin/types.h"

namespace JMessage {
struct TControl {
    TControl();
    virtual ~TControl();

    void reset();
    bool update();
    void render();
    void setMessageCode(u32 param_1) {
        setMessageCode(param_1 >> 0x10, param_1);
    }
    void setMessageCode(u16 message_code, u16 message_index) {
        mMessageCode = message_code;
        mMessageIndex = message_index;
        setMessageCode_flush_();
    }
    bool setMessageCode_flush_();

    bool isReady_update_() const { return mResourceCache != NULL && mMessageBegin != 0 && mBaseProcSeq != NULL; }
    bool isReady_render_() const { return mResourceCache != NULL && _20 != NULL && mBaseProcRender != NULL; }

    TProcessor* getProcessor() const {
        return mBaseProcSeq != NULL ? (TProcessor*)mBaseProcSeq : (TProcessor*)mBaseProcRender;
    }

    const char* getMessageText_begin() const { return mMessageBegin; }
    void* getMessageEntry() const { return mEntry; }
    void setSequenceProcessor(TSequenceProcessor* processor) { mBaseProcSeq = processor; }
    void setRenderingProcessor(TRenderingProcessor* processor) { mBaseProcRender = processor; }

    void getResource_groupID(u16) const;
    void getMessageData(u16, u16) const;
    void do_word(u32);
    void reset_();

    /* 0x04 */ void* _04;
    /* 0x08 */ void* _08;
	/* 0x0C */ TSequenceProcessor* mBaseProcSeq;
	/* 0x10 */ TRenderingProcessor* mBaseProcRender;
	/* 0x14 */ u16 mMessageCode;
	/* 0x16 */ u16 mMessageIndex;
	/* 0x18 */ const TResource* mResourceCache;
	/* 0x1C */ const char* mMessageBegin;
	/* 0x20 */ const char* _20;
	/* 0x24 */ const char* mCurrentText;
	/* 0x28 */ void* mEntry;
	/* 0x2C */ TProcessor::TStack_ mRenderStack;
};
};  // namespace JMessage

#endif /* JMESSAGE_CONTROL_H */
