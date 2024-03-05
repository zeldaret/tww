#ifndef JMESSAGE_PROCESSOR_H
#define JMESSAGE_PROCESSOR_H

#include "JSystem/JMessage/resource.h"
#include "dolphin/types.h"

namespace JMessage {

struct TReference;
struct TControl;
struct TResource;

struct TProcessor {
    typedef bool (*OnCharacterEndCallBack)(TProcessor*);
    typedef const char* (*OnSelectBeginCallBack)(TProcessor*);
    typedef const char* (*ProcessOnSelectCallBack)(TProcessor*);

    struct TStack_ {
        TStack_() { clear(); }

        TStack_(const TStack_& other)
        {
            mSize = other.mSize;
            for (int i = 0; i < mSize; i++) {
                mStack[i] = mStack[i];
            }
        }

        inline bool empty() const { return mSize == 0; }
        inline bool isPushable() const { return mSize < 4; }
        inline void clear() { mSize = 0; }

        inline u32 getMaxSize() const { return 4; }
        inline u32 getSize() const { return mSize; }
        inline const char* getTop() const { return mStack[mSize - 1]; }

        inline void push(const char* str)
        {
            mStack[mSize] = str;
            mSize++;
        }

        inline void pop() { mSize--; }

        u32 mSize;             // _00
        const char* mStack[3]; // _04
    };

    struct TProcess {
        struct TProcessData {
            ProcessOnSelectCallBack mSelectCallback; // _00
            const char* mBase;                       // _04
            const void* mOffset;                     // _08
            u32 mRest;                               // _0C
        };

        TProcess() { reset_normal(); }

        void reset_normal() { mEndCallback = process_onCharacterEnd_normal_; }
        void reset_select() { mEndCallback = process_onCharacterEnd_select_; }

        OnCharacterEndCallBack mEndCallback; // _00
        TProcessData mData;                  // _04
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
    char* on_message_limited(u16) const;         // weak
    char* on_message(u32) const;                 // weak
    char* getMessageText_messageCode(u32) const; // weak
    static bool process_onCharacterEnd_normal_(TProcessor*);
    static bool process_onCharacterEnd_select_(TProcessor*);
    static const char* process_onSelect_limited_(TProcessor*);
    static const char* process_onSelect_(TProcessor*);
    void reset_(const char*);

    void process_select_limited_(TProcessor*);
    void process_select_(TProcessor*);

    int setBegin_messageEntryText(const TResource* resource, const void* entry, const char* param_2)
    {
        // mResourceCache = resource;
        reset_(param_2);
        do_begin_(entry, param_2);
        return TRUE;
    }

    const TResource* getResourceCache() const { return mResourceCache; }
    const char* getCurrent() const { return mCurrent; }
    const TReference* getReference() const { return mReference; }

    // Unused/inlined:
    void pushCurrent(const char*);
    const char* popCurrent();
    void on_select_begin(OnSelectBeginCallBack, const void*, const char*, u32);
    void on_select_end();
    void on_select_separate();
    void on_tag_();
    void process_character_();

    // _00 = VTBL
    const TReference* mReference;    // _04
    const TResource* mResourceCache; // _08
    const char* mCurrent;            // _0C
    TStack_ mStack;                  // _10
    TProcess mProcess;               // _24
};

struct TSequenceProcessor : public TProcessor {
    typedef bool OnJumpRegisterCallBack(TSequenceProcessor*);
    typedef bool OnBranchRegisterCallBack(TSequenceProcessor*, u32);
    typedef void* ProcessOnJumpCallBack(const TSequenceProcessor*);

    TSequenceProcessor(const TReference*, TControl*);
    TSequenceProcessor(TControl*);

    virtual ~TSequenceProcessor();                         // _08
    virtual void do_reset_(const char*);                   // _28
    virtual bool do_setBegin_isReady_() const;             // _2C
    virtual void do_begin_(const void*, const char*);      // _30
    virtual void do_end_();                                // _34
    virtual bool do_tag_(u32, const void*, u32);           // _38
    virtual void do_systemTagCode_(u16, const void*, u32); // _3C
    virtual void do_begin(const void*, const char*);       // _40
    virtual void do_end();                                 // _44
    virtual bool do_isReady();                             // _48
    virtual bool do_jump_isReady();                        // _4C
    virtual void do_jump(const void*, const char*);        // _50
    virtual void do_branch_query(u16);                     // _54
    virtual int do_branch_queryResult();                   // _58
    virtual void do_branch(const void*, const char*);      // _5C

    char* process(const char*);
    bool on_isReady();
    void on_jump_isReady();
    void on_jump(const void*, const char*);
    void on_branch_queryResult();
    void on_branch(const void*, const char*);
    void process_onJump_limited_(const TSequenceProcessor*);
    static void* process_onJump_(const TSequenceProcessor*);
    void process_onBranch_limited_(const TSequenceProcessor*, u32);
    void process_onBranch_(const TSequenceProcessor*, u32);

    void reset_(const char*);
    void process_jump_limited_(TSequenceProcessor*);
    void process_jump_(TSequenceProcessor*);
    void process_branch_limited_(TSequenceProcessor*, u32);
    void process_branch_(TSequenceProcessor*, u32);

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

    // _00     = VTBL
    // _00-_38 = TProcessor
    TControl* _38;              // _38
    int _3C;                    // _3C
    ProcessOnJumpCallBack* _40; // _40 - processorCallBack(void*, ulong) pointer?
    u32 _44;                    // _44
    u32 _48;                    // _48
};

struct TRenderingProcessor : public TProcessor {
    TRenderingProcessor(const TReference*);
    TRenderingProcessor(TControl*);

    virtual void do_begin_(const void*, const char*);
    virtual void do_end_();
    virtual bool do_tag_(u32, const void*, u32);
    virtual void do_systemTagCode_(u16, const void*, u32);
    virtual ~TRenderingProcessor();
    virtual void do_begin(const void*, const char*);
    virtual void do_end();
    
    void process(const char*);

    // _00     = VTBL
    // _00-_38 = TProcessor
};
} // namespace JMessage

#endif /* JMESSAGE_PROCESSOR_H */
