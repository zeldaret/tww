#ifndef LINKLIST_H
#define LINKLIST_H

#include "dolphin/types.h"

namespace JGadget {
struct TLinkListNode {
    TLinkListNode() {
        mNext = NULL;
        mPrev = NULL;
    }

    TLinkListNode* getNext() const { return mNext; }
    TLinkListNode* getPrev() const { return mPrev; }

public:
    /* 0x0 */ TLinkListNode* mNext;
    /* 0x4 */ TLinkListNode* mPrev;
};  // Size: 0x8

struct TNodeLinkList {
    struct iterator {
        iterator(TLinkListNode* pNode) { node = pNode; }

        iterator& operator++() { node = node->getNext(); return *this; }
        iterator& operator--() { node = node->getPrev(); return *this; }
        iterator operator++(int) { const iterator old(*this); (void)++*this; return old; }
        iterator operator--(int) { const iterator old(*this); (void)--*this; return old; }
        friend bool operator==(TNodeLinkList::iterator a, TNodeLinkList::iterator b) { return a.node == b.node; }
        friend bool operator!=(TNodeLinkList::iterator a, TNodeLinkList::iterator b) { return !(a == b); }

        TLinkListNode* operator->() const { return node; }
        TLinkListNode& operator*() const { return *node; }

    public:
        /* 0x00 */ TLinkListNode* node;
    };

    struct const_iterator {
        const_iterator(TLinkListNode* pNode) { node = pNode; }

        const_iterator& operator++() { node = node->getNext(); return *this; }
        const_iterator& operator--() { node = node->getPrev(); return *this; }
        const_iterator operator++(int) { const const_iterator old(*this); (void)++*this; return old; }
        const_iterator operator--(int) { const const_iterator old(*this); (void)--*this; return old; }
        friend bool operator==(TNodeLinkList::const_iterator a, TNodeLinkList::const_iterator b) { return a.node == b.node; }
        friend bool operator!=(TNodeLinkList::const_iterator a, TNodeLinkList::const_iterator b) { return !(a == b); }

        TLinkListNode* operator->() const { return node; }
        TLinkListNode& operator*() const { return *node; }

    public:
        /* 0x00 */ TLinkListNode* node;
    };

    TNodeLinkList() : ocObject_() { Initialize_(); }
    ~TNodeLinkList();

    void Initialize_() {
        count = 0;
        ocObject_.mNext = &ocObject_;
        ocObject_.mPrev = &ocObject_;
    }

    iterator begin() { return iterator(ocObject_.getNext()); }
    const_iterator begin() const { return const_iterator(ocObject_.getNext()); }
    iterator end() { return iterator(&ocObject_); }
    const_iterator end() const { return const_iterator((TLinkListNode*)(&ocObject_)); }
    u32 size() { return count; }

    iterator erase(JGadget::TNodeLinkList::iterator, JGadget::TNodeLinkList::iterator);
    iterator erase(JGadget::TNodeLinkList::iterator);
    void splice(JGadget::TNodeLinkList::iterator, JGadget::TNodeLinkList&, JGadget::TNodeLinkList::iterator);
    iterator Find(const JGadget::TLinkListNode*);
    iterator Insert(JGadget::TNodeLinkList::iterator, JGadget::TLinkListNode*);
    iterator Erase(JGadget::TLinkListNode*);
    void Remove(JGadget::TLinkListNode*);

public:
    /* 0x00 */ u32 count;
    /* 0x04 */ TLinkListNode ocObject_;
};  // Size: 0xC

template <typename T, int I>
struct TLinkList : public TNodeLinkList {
    TLinkList() : TNodeLinkList() {}

    static TLinkListNode* Element_toNode(T* element) { return reinterpret_cast<TLinkListNode*>(reinterpret_cast<char*>(element) - I); }
    static T* Element_toValue(TLinkListNode* node) { return reinterpret_cast<T*>(reinterpret_cast<char*>(node) + I); }

    struct iterator {
        iterator(TNodeLinkList::iterator iter) : base(iter) {}

        iterator& operator++() { ++base; return *this; }
        iterator& operator--() { --base; return *this; }
        iterator operator++(int) { const iterator old(*this); ++*this; return old; }
        iterator operator--(int) { const iterator old(*this); --*this; return old; }
        friend bool operator==(iterator a, iterator b) { return a.base == b.base; }
        friend bool operator!=(iterator a, iterator b) { return !(a == b); }

        T* operator->() const { return Element_toValue(base.operator->()); }
        T& operator*() const { return *operator->(); }

    public:
        /* 0x00 */ TNodeLinkList::iterator base;
    };

    struct const_iterator {
        const_iterator(TNodeLinkList::const_iterator iter) : base(iter) {}

        const_iterator& operator++() { ++base; return *this; }
        const_iterator& operator--() { --base; return *this; }
        const_iterator operator++(int) { const const_iterator old(*this); ++*this; return old; }
        const_iterator operator--(int) { const const_iterator old(*this); --*this; return old; }
        friend bool operator==(const_iterator a, const_iterator b) { return a.base == b.base; }
        friend bool operator!=(const_iterator a, const_iterator b) { return !(a == b); }

        T* operator->() const { return Element_toValue(base.operator->()); }
        T& operator*() const { return *operator->(); }

    public:
        /* 0x00 */ TNodeLinkList::const_iterator base;
    };

    iterator Insert(iterator iter, T* element) { return TNodeLinkList::Insert(iter.base, Element_toNode(element)); }
    iterator Erase(T* element) { return TNodeLinkList::Erase(Element_toNode(element)); }

    iterator begin() { return iterator(TNodeLinkList::begin()); }
    const_iterator begin() const { return const_iterator(TNodeLinkList::begin()); }
    iterator end() { return iterator(TNodeLinkList::end()); }
    const_iterator end() const { return const_iterator(TNodeLinkList::end()); }

    void Push_back(T* element) {
        Insert(end(), element);
    }

    iterator Find(T* element) {
        return TNodeLinkList::Find(Element_toNode(element));
    }

    void Remove(T* element) {
        TNodeLinkList::Remove(Element_toNode(element));
    }

    T& front() { return *begin(); }
    T& back() { return *--end(); }
};

template <typename T, int I>
struct TLinkList_factory : public TLinkList<T, I> {
    virtual ~TLinkList_factory() {}
    virtual T* Do_create() = 0;
    virtual void Do_destroy(T*) = 0;
};

template <typename T, int I>
struct TEnumerator {
    TLinkList<T, I> field_0x0;
    TLinkList<T, I> field_0x4;
};

template <typename T, int I>
struct TContainerEnumerator_const : public TEnumerator<T, I> {};

};  // namespace JGadget

#endif /* LINKLIST_H */
