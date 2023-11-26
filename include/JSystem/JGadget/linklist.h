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
        iterator(const iterator& iter) { *this = iter; }
        operator bool() const {
            return node != NULL;
        }

        iterator& operator++() {
            node = node->getNext();
            return *this;
        }
        iterator& operator--() {
            node = node->getPrev();
            return *this;
        }
        bool operator==(const iterator& o) { return o.node == node; }
        bool operator!=(const iterator& o) { return !(*this == o); }

        TLinkListNode* node;
    };

    struct const_iterator {
        const_iterator(TLinkListNode* pNode) { node = pNode; }
        const_iterator(const const_iterator& iter) { *this = iter; }
        operator bool() const {
            return node != NULL;
        }

        const_iterator& operator++() {
            node = node->getNext();
            return *this;
        }
        const_iterator& operator--() {
            node = node->getPrev();
            return *this;
        }
        bool operator==(const const_iterator& o) { return o.node == node; }
        bool operator!=(const const_iterator& o) { return !(*this == o); }

        TLinkListNode* node;
    };

    TNodeLinkList() : ocObject_() { Initialize_(); }

    void Initialize_() {
        count = 0;
        ocObject_.mNext = &ocObject_;
        ocObject_.mPrev = &ocObject_;
    }

    iterator begin() {
        iterator iter(ocObject_.getNext());
        return iter;
    }

    iterator end() {
        iterator iter(ocObject_.getPrev());
        return iter;
    }

    const_iterator begin() const {
        const_iterator iter(ocObject_.getNext());
        return iter;
    }

    const_iterator end() const {
        const_iterator iter(ocObject_.getPrev());
        return iter;
    }

    ~TNodeLinkList();
    iterator erase(JGadget::TNodeLinkList::iterator, JGadget::TNodeLinkList::iterator);
    iterator erase(JGadget::TNodeLinkList::iterator);
    void splice(JGadget::TNodeLinkList::iterator, JGadget::TNodeLinkList&,
                JGadget::TNodeLinkList::iterator);
    iterator Find(const JGadget::TLinkListNode*);
    iterator Insert(JGadget::TNodeLinkList::iterator, JGadget::TLinkListNode*);
    iterator Erase(JGadget::TLinkListNode*);
    void Remove(JGadget::TLinkListNode*);
    u32 size() { return count; }

    /* 0x00 */ u32 count;
    /* 0x04 */ TLinkListNode ocObject_;
};  // Size: 0xC

template <typename T, int I>
struct TLinkList : public TNodeLinkList {
    TLinkList() : TNodeLinkList() {}

    static TLinkListNode* Element_toNode(T* element) { return reinterpret_cast<TLinkListNode*>(((char*)element) - I); }
    static T* Element_toValue(TLinkListNode* node) { return reinterpret_cast<T*>(((char*)node) + I); }

    struct iterator : TNodeLinkList::iterator {
        iterator(TNodeLinkList::iterator iter) : TNodeLinkList::iterator(iter) {}
        iterator(const iterator& o) : TNodeLinkList::iterator(o) {}

        iterator& operator++() {
            iterator it(TNodeLinkList::iterator::operator++());
            return it;
        }
        iterator& operator--() {
            iterator it(TNodeLinkList::iterator::operator--());
            return it;
        }

        T* operator*() {
            return Element_toValue(node);
        }
        T* operator->() {
            return Element_toValue(node);
        }
    };

    struct const_iterator : TNodeLinkList::const_iterator {
        const_iterator(TNodeLinkList::const_iterator iter) : TNodeLinkList::const_iterator(iter) {}
        const_iterator(const const_iterator& o) : TNodeLinkList::const_iterator(o) {}

        const_iterator& operator++() {
            const_iterator it(TNodeLinkList::const_iterator::operator++());
            return it;
        }
        const_iterator& operator--() {
            const_iterator it(TNodeLinkList::const_iterator::operator--());
            return it;
        }

        T* operator*() {
            return Element_toValue(node);
        }
        T* operator->() {
            return Element_toValue(node);
        }
    };

    void Insert(TLinkList::iterator iter, T* element) {
        TLinkListNode* node = Element_toNode(element);
        TNodeLinkList::Insert(iter, node);
    }

    iterator Erase(T* element) {
        TLinkListNode* node = Element_toNode(element);
        return ((TNodeLinkList*)this)->Erase(node);
    }

    TLinkList::iterator begin() {
        TNodeLinkList::iterator node_iter = TNodeLinkList::begin();
        TLinkList::iterator iter(node_iter);
        return iter;
    }

    TLinkList::iterator end() {
        TNodeLinkList::iterator node_iter = TNodeLinkList::end();
        TLinkList::iterator iter(node_iter);
        return iter;
    }

    TLinkList::const_iterator begin() const {
        TNodeLinkList::const_iterator node_iter = TNodeLinkList::begin();
        TLinkList::const_iterator iter(node_iter);
        return iter;
    }

    TLinkList::const_iterator end() const {
        TNodeLinkList::const_iterator node_iter = TNodeLinkList::end();
        TLinkList::const_iterator iter(node_iter);
        return iter;
    }

    void Push_back(T* element) {
        TLinkList::iterator iter(TLinkList::end());
        this->Insert(iter, element);
    }

    iterator Find(T* element) {
        return TNodeLinkList::Find(Element_toNode(element));
    }

    void Remove(T* element) {
        TNodeLinkList::Remove(Element_toNode(element));
    }

    T* front() {
        TLinkList::iterator iter(TLinkList::begin());
        return *iter;
    }

    T* back() {
        TLinkList::iterator iter(TLinkList::end());
        --iter;
        return *iter;
    }
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
