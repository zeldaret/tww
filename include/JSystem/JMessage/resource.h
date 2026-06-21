#ifndef RESOURCE_H
#define RESOURCE_H

#include "JSystem/JGadget/binary.h"
#include "JSystem/JGadget/linklist.h"
#include "JSystem/JMessage/data.h"

namespace JMessage {
    namespace data {
        struct JUTMesgInfo;
        struct JUTMesgIDData;
    };

    class TResource {
    public:
        TResource() : mHeader(NULL), mInfo(NULL) {
            mMessageData = NULL;
            mStringAttribute = NULL;
            mMessageID = NULL;
        }

        void setData_header(const void* p) { mHeader.setRaw(p); }
        void setData_block_info(const void* p) { mInfo.setRaw(p); }
        void setData_block_messageData(const void* p) { mMessageData = (const char*)p; }
        void setData_block_stringAttribute(const void* p) { mStringAttribute = (const char*)p; }
        void setData_block_messageID(const void* p) { mMessageID = (data::JUTMesgIDData*)p; }

        u32 getMessageEntryNumber() const { return mInfo.get_messageEntryNumber(); }
        u32 getMessageEntrySize() const { return mInfo.get_messageEntrySize(); }
        u16 getGroupID() const { return mInfo.get_groupID(); }

        void* getMessageEntry(u16 messageIndex) const {
            // Fakematch?
            // Debug maps suggest the isMessageIndexContained inline was used for this check, but
            // using it here causes various issues with matching from instruction order to regalloc
            // and even completely wrong codegen on demo. Writing the check directly fixes this.
            if (messageIndex >= getMessageEntryNumber()) {
                return NULL;
            }
            return getMessageEntry_(messageIndex);
        }
        void* getMessageEntry_(u16 messageIndex) const {
            return mInfo.getContent() + (messageIndex * getMessageEntrySize());
        }
        bool isMessageIndexContained(u16 messageIndex) const {
            // wrong somehow?
            return messageIndex < getMessageEntryNumber();
        }
        void getMessageData_messageEntry(const void*) const {} // TODO

    public:
        /* 0x00 */ JGadget::TLinkListNode mLinkNode;
        /* 0x08 */ data::TParse_THeader mHeader;
        /* 0x0C */ data::TParse_TBlock_info mInfo;
        /* 0x10 */ const char* mMessageData;
        /* 0x14 */ const char* mStringAttribute;
        /* 0x18 */ data::JUTMesgIDData* mMessageID;
    };

#ifdef __MWERKS__
    class TResourceContainer : public JGadget::TLinkList_factory<TResource, -offsetof(TResource, mLinkNode)>
#else
    // clangd does not support offsetof in template arguments.
    class TResourceContainer : public JGadget::TLinkList_factory<TResource, -0x00>
#endif
    {
    public:
        TResourceContainer();
        virtual TResource* Do_create();
        virtual void Do_destroy(JMessage::TResource*);

        TResource* Get_groupID(u16 groupID);
        void SetEncoding(u8);

        bool IsEncodingSettable(u8 encoding) const {
            return mEncoding == encoding || mEncoding == 0;
        }
        bool IsLeadByte(int param_0) const { return mIsLeadByteFunc(param_0); }

        void Get_groupID(u16) const {}

    private:
        void SetEncoding_(u8);

    private:
        /* 0x10 */ u8 mEncoding;
        /* 0x14 */ bool (*mIsLeadByteFunc)(int);
    };

    class TParse : public JGadget::binary::TParse_header_block {
    public:
        TParse(JMessage::TResourceContainer*);
        virtual ~TParse();
        virtual bool parseHeader_next(const void**, u32*, u32);
        virtual bool parseBlock_next(const void**, u32*, u32);

    public:
        /* 0x04 */ TResourceContainer* mResourceContainer;
        /* 0x08 */ TResource* mResource;
    };
}

#endif /* RESOURCE_H */
