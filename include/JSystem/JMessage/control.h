#ifndef JMESSAGE_CONTROL_H
#define JMESSAGE_CONTROL_H

#include "JSystem/JMessage/processor.h"
#include "dolphin/types.h"

namespace JMessage {
struct TControl {
    TControl();
    virtual ~TControl();

    void reset();
    int update();
    void render();
    int setMessageCode(u16, u16);
    int setMessageID(u32, u32, bool*);

    bool isReady_update_() const { return pMessageText_begin_ != 0 && pSequenceProcessor_ != NULL; }
    bool isReady_render_() const { return field_0x20 != 0 && pRenderingProcessor_ != NULL; }

    TProcessor* getProcessor() const {
        return pSequenceProcessor_ != NULL ? (TProcessor*)pSequenceProcessor_ :
                                             (TProcessor*)pRenderingProcessor_;
    }

    const char* getMessageText_begin() const { return pMessageText_begin_; }
    void* getMessageEntry() const { return pEntry_; }
    void setSequenceProcessor(TSequenceProcessor* processor) { pSequenceProcessor_ = processor; }
    void setRenderingProcessor(TRenderingProcessor* processor) { pRenderingProcessor_ = processor; }

    /* 0x04 */ TSequenceProcessor* pSequenceProcessor_;
    /* 0x08 */ TRenderingProcessor* pRenderingProcessor_;
    /* 0x0C */ u16 messageCode_;
    /* 0x0E */ u16 field_0xe;
    /* 0x10 */ const TResource* pResourceCache_;
    /* 0x14 */ void* pEntry_;
    /* 0x18 */ const char* pMessageText_begin_;
    /* 0x1C */ const char* pszText_update_current_;
    /* 0x20 */ const char* field_0x20;
    /* 0x24 */ TProcessor::TStack_ oStack_renderingProcessor_;
};
};  // namespace JMessage

#endif /* JMESSAGE_CONTROL_H */
