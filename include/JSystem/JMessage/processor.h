#ifndef JMESSAGE_PROCESSOR_H
#define JMESSAGE_PROCESSOR_H

#include "JSystem/JMessage/resource.h"

namespace JMessage {

struct TReference;
struct TControl;
struct TResource;

struct TProcessor {
public:
    TProcessor(TControl *control) : mControl(control), mCurrent(NULL) {}

    typedef bool (*ProcessorCallBack)(TProcessor*);
    typedef const char* (*OnSelectBeginCallBack)(TProcessor*);
    typedef const char* (*ProcessOnSelectCallBack)(TProcessor*);

    struct TStack_ {
        TStack_() { clear(); }

        TStack_(const TStack_& other) {
            for (int i = 0; i < mNum; i++) {
                mStack[i] = mStack[i];
            }
            mNum = other.mNum;
        }

        inline void clear() { mNum = 0; }
        inline void push(const char* str) {
            mStack[mNum - 1] = str;
            mNum++;
        }
        inline bool IsStorable() const { return mNum < 4; }
        inline void pop() { mNum--; }
        inline const char* top() const { return mStack[mNum - 2]; }
        inline bool empty() const { return mNum == 0; }

        /* 0x00 */ const char* mStack[4];
        /* 0x10 */ u32 mNum;
    };

    // XXX: None of this shows up in the debug map. Is this TStatusData?
    struct TProcess {
        TProcess() { reset_normal(); }

        void reset_normal() { mCallBack = process_onCharacterEnd_normal_; }
        void reset_select() { mCallBack = process_onCharacterEnd_select_; }

        /* 0x00 */ ProcessorCallBack mCallBack;
        /* 0x04 */ void* mCallBackWork[4];
    };

    ~TProcessor();

    virtual void do_character(int);
    virtual bool do_tag(u32, const void*, u32);
    virtual bool do_systemTagCode(u16, const void*, u32);
    virtual void do_select_begin(u32);
    virtual void do_select_end();
    virtual void do_select_separate();
    virtual void do_begin_(const void*, const char*)      = 0;
    virtual void do_end_()                                = 0;
    virtual bool do_tag_(u32, const void*, u32)           = 0;
    virtual void do_systemTagCode_(u16, const void*, u32) = 0;

    void setBegin_messageCode(u16, u16);
    void setBegin_messageID(u32, u32, bool*);
    void setBegin_messageCode(u32); // weak
    TResource* getResource_groupID(u16) const;
    u32 toMessageCode_messageID(u32, u32, bool*) const;
    char* on_message(u32) const;                 // weak
    char* getMessageText_messageCode(u32) const; // weak
    static bool process_onCharacterEnd_normal_(TProcessor*);
    static bool process_onCharacterEnd_select_(TProcessor*);
    static const char* process_onSelect_limited_(TProcessor*);
    static const char* process_onSelect_(TProcessor*);
    void reset_(const char*);

    static const char* process_select_limited_(TProcessor*);
    static const char* process_select_(TProcessor*);

    void pushCurrent(const char*);
    const char* popCurrent();
    void on_select_begin(OnSelectBeginCallBack, const void*, const char*, u32);
    void on_select_end();
    void on_select_separate();
    void on_tag_();
    bool process_character_();

    const char* getCurrent() const { return mCurrent; }

    /* 0x00 */ /* vtable */
    /* 0x04 */ TControl* mControl;
    /* 0x08 */ const char* mCurrent;
    /* 0x0C */ TStack_ mStack;
    /* 0x20 */ TProcess mProcess;
};

struct TSequenceProcessor : public TProcessor {
    typedef bool OnJumpRegisterCallBack(TSequenceProcessor*);
    typedef bool OnBranchRegisterCallBack(TSequenceProcessor*, u32);
    typedef void* ProcessOnJumpCallBack(const TSequenceProcessor*);

    TSequenceProcessor(const TReference*, TControl*);
    TSequenceProcessor(TControl*);

    /* 0x08 */ virtual ~TSequenceProcessor();
    /* 0x30 */ virtual void do_begin_(const void*, const char*);
    /* 0x34 */ virtual void do_end_();
    /* 0x38 */ virtual bool do_tag_(u32, const void*, u32);
    /* 0x3C */ virtual void do_systemTagCode_(u16, const void*, u32);
    /* 0x40 */ virtual void do_begin(const void*, const char*);
    /* 0x44 */ virtual void do_end();
    /* 0x48 */ virtual bool do_isReady();
    /* 0x4C */ virtual bool do_jump_isReady();
    /* 0x50 */ virtual void do_jump(const void*, const char*);
    /* 0x54 */ virtual void do_branch_query(u16);
    /* 0x58 */ virtual int do_branch_queryResult();
    /* 0x5C */ virtual void do_branch(const void*, const char*);

    const char* process(const char*);
    bool on_isReady();
    bool on_jump_isReady();
    void on_jump(const void*, const char*);
    int on_branch_queryResult();
    void on_branch(const void*, const char*);

    void reset_(const char*);
    static bool process_jump_limited_(TSequenceProcessor*);
    static bool process_jump_(TSequenceProcessor*);
    static bool process_branch_limited_(TSequenceProcessor*, u32);
    static bool process_branch_(TSequenceProcessor*, u32);

    // Unused/inlined:
    const char* toString_status(int);
    int toValue_status(const char*);
    void on_jump_register(OnJumpRegisterCallBack*, u32);
    void on_branch_register(OnBranchRegisterCallBack*, const void*, u32);
    void on_branch_query(u16);
    void process_setMessageIndex_reserved_(u16);
    void process_setMessageCode_(const TSequenceProcessor*, u16, u16);

    void reset() {}
    void setBegin(const void* param_1, const char* param_2) {
        reset_(param_2);
        do_begin_(param_1, param_2);
    }

    enum {
        kStatus_Begin,
        kStatus_End,
        kStatus_Normal,
        kStatus_Jump,
        kStatus_Branch,
    };

    /* 0x00 */ /* TProcessor */
    /* 0x34 */ int mStatus;
};

struct TRenderingProcessor : public TProcessor {
    TRenderingProcessor(const TReference*);
    TRenderingProcessor(TControl*);

    void setBegin(const void* entry, const char* data) {
        reset_(data);
        do_begin_(entry, data);
    }

    virtual void do_begin_(const void*, const char*);
    virtual void do_end_();
    virtual bool do_tag_(u32, const void*, u32);
    virtual void do_systemTagCode_(u16, const void*, u32);
    virtual ~TRenderingProcessor();
    virtual void do_begin(const void*, const char*);
    virtual void do_end();

    const char* process(const char*);

    /* 0x00 */ /* TProcessor */
};
} // namespace JMessage

#endif /* JMESSAGE_PROCESSOR_H */
