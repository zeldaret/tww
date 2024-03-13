#ifndef JMESSAGE_CONTROL_H
#define JMESSAGE_CONTROL_H

#include "JSystem/JMessage/processor.h"
#include "dolphin/types.h"

namespace JMessage {
class TResource;

struct TControl {
    TControl();
    virtual ~TControl();
    virtual const char* do_word(u32);

    void reset();
    bool update();
    void render();
    bool setMessageCode(u32 packed) {
        return setMessageCode(packed >> 16, packed & 0xFFFF);
    }
    bool setMessageCode(u16 groupID, u16 messageIndex) {
        mGroupID = groupID;
        mMessageIndex = messageIndex;
        return setMessageCode_flush_();
    }
    bool setMessageCode_flush_();

    const void* getMessageEntry() const { return mMessageEntry; }
    const char* getMessageData_begin() const { return mMessageDataStart; }

    bool isResourceCached_groupID(u16 groupID) const {
        return mResource != NULL && mResource->getGroupID() == groupID;
    }

    const char* getMessageData_cached_messageEntry_(u16 messageIndex, const void* messageEntry) const { /* TODO */ return NULL; }

    bool isReady_update_() const { return mMessageEntry != NULL && mMessageDataStart != 0 && mBaseProcSeq != NULL; }
    bool isReady_render_() const { return mMessageEntry != NULL && mMessageDataCurrent != NULL && mBaseProcRender != NULL; }

    TProcessor* getProcessor() const {
        return mBaseProcSeq != NULL ? (TProcessor*)mBaseProcSeq : (TProcessor*)mBaseProcRender;
    }

    void setSequenceProcessor(TSequenceProcessor* processor) { mBaseProcSeq = processor; }
    void setRenderingProcessor(TRenderingProcessor* processor) { mBaseProcRender = processor; }

    const char* on_message(u32 code) { return getMessageData(code >> 16, code); }
    const char* on_message_limited(u16 messageIndex) { return getMessageData(mGroupID, messageIndex); }
    const char* on_word(u16 messageIndex) { return do_word(messageIndex); }

    TResource* getResource_groupID(u16) const;
    const char* getMessageData(u16, u16) const;
    void reset_();

    void getMessageCode() const {}
    void getMessageData(u32) const {}
    void getMessageEntry(u32) const {}
    void getMessageEntry(u16, u16) const {}
    void getMessageGroupID() const {}
    void getMessageIndex() const {}
    void on_isLeadByte(int) {}
    void on_word(u32) {}
    void setMessageIndex(u16) {}
    void setResourceContainer(const JMessage::TResourceContainer*) {}

    /* 0x04 */ TResourceContainer* mResourceContainer;
    /* 0x08 */ mutable TResource* mResource;
    /* 0x0C */ TSequenceProcessor* mBaseProcSeq;
    /* 0x10 */ TRenderingProcessor* mBaseProcRender;
    /* 0x14 */ u16 mGroupID;
    /* 0x16 */ u16 mMessageIndex;
    /* 0x18 */ const void* mMessageEntry;
    /* 0x1C */ const char* mMessageDataStart;
    /* 0x20 */ const char* mMessageDataCurrent;
    /* 0x24 */ const char* mCurrentText;
    /* 0x28 */ TProcessor::TStack_ mRenderStack;
};
};  // namespace JMessage

#endif /* JMESSAGE_CONTROL_H */
