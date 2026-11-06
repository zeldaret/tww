#ifndef JSTUDIO_JMESSAGE_CONTROL_H
#define JSTUDIO_JMESSAGE_CONTROL_H

#include "JSystem/JStudio/JStudio/jstudio-object.h"
#include "JSystem/JMessage/control.h"

namespace JStudio_JMessage {
struct TCreateObject_base : JStudio::TCreateObject {
    virtual ~TCreateObject_base() = 0;                                                                       // _08
    virtual bool create(JStudio::TObject** newObject, const JStudio::stb::data::TParse_TBlock_object& data); // _0C
    virtual JMessage::TControl* find(const JStudio::stb::data::TParse_TBlock_object&) = 0;                   // _10
};
} // namespace JStudio_JMessage

namespace JStudio_JMessage {
struct TCreateObject : public TCreateObject_base {
    TCreateObject(JMessage::TControl* control) { mControl = control; }

    virtual ~TCreateObject();                                                          // _08
    virtual JMessage::TControl* find(const JStudio::stb::data::TParse_TBlock_object&); // _10

    /* 0x0C */ JMessage::TControl* mControl;
};

struct TAdaptor_message : public JStudio::TAdaptor_message {
    virtual ~TAdaptor_message();                                                       // _08
    virtual void adaptor_do_MESSAGE(JStudio::data::TEOperationData, const void*, u32); // _20

    TAdaptor_message(JMessage::TControl*);
    /* 0x0C */ JMessage::TControl* mControl;
};
} // namespace JStudio_JMessage

#endif /* JSTUDIO_JMESSAGE_CONTROL_H */
