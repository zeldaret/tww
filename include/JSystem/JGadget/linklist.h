#ifndef LINKLIST_H
#define LINKLIST_H

#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JGadget/define.h"
#include <iterator.h>

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
        typedef ptrdiff_t difference_type;
        typedef TLinkListNode value_type;
        typedef TLinkListNode* pointer;
        typedef TLinkListNode& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

        iterator() { node = NULL; }
        explicit iterator(TLinkListNode* pNode) { node = pNode; }
        iterator& operator=(const iterator& other) { node = other.node; return *this; }

        iterator& operator++() { node = node->getNext(); return *this; }
        iterator& operator--() { node = node->getPrev(); return *this; }
        iterator operator++(int) { const iterator old(*this); (void)++*this; return old; }
        iterator operator--(int) { const iterator old(*this); (void)--*this; return old; }
        friend bool operator==(iterator a, iterator b) { return a.node == b.node; }
        friend bool operator!=(iterator a, iterator b) { return !(a == b); }

        TLinkListNode* operator->() const { return node; }
        TLinkListNode& operator*() const { return *node; }

    public:
        /* 0x00 */ TLinkListNode* node;
    };

    struct const_iterator {
        typedef ptrdiff_t difference_type;
        typedef const TLinkListNode value_type;
        typedef const TLinkListNode* pointer;
        typedef const TLinkListNode& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

        explicit const_iterator(TLinkListNode* pNode) { node = pNode; }
        explicit const_iterator(iterator it) { node = it.node; }

        const_iterator& operator++() { node = node->getNext(); return *this; }
        const_iterator& operator--() { node = node->getPrev(); return *this; }
        const_iterator operator++(int) { const const_iterator old(*this); (void)++*this; return old; }
        const_iterator operator--(int) { const const_iterator old(*this); (void)--*this; return old; }
        friend bool operator==(const_iterator a, const_iterator b) { return a.node == b.node; }
        friend bool operator!=(const_iterator a, const_iterator b) { return !(a == b); }

        friend bool operator==(const_iterator a, iterator b) { return a.node == b.node; }
        friend bool operator!=(const_iterator a, iterator b) { return !(a == b); }

        const TLinkListNode* operator->() const { return node; }
        const TLinkListNode& operator*() const { return *node; }

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
    u32 size() const { return count; }
    bool empty() const { return size() == 0; }
    iterator pop_front() { return erase(begin()); }

    iterator erase(JGadget::TNodeLinkList::iterator, JGadget::TNodeLinkList::iterator);
    iterator erase(JGadget::TNodeLinkList::iterator);
    void splice(JGadget::TNodeLinkList::iterator, JGadget::TNodeLinkList&,
                JGadget::TNodeLinkList::iterator);
    iterator Find(const JGadget::TLinkListNode*);
    iterator Insert(JGadget::TNodeLinkList::iterator, JGadget::TLinkListNode*);
    iterator Erase(JGadget::TLinkListNode*);
    void Remove(JGadget::TLinkListNode*);

    bool Iterator_isEnd_(const_iterator it) const { return it.node == &ocObject_; }
    template <typename Predicate>
    void Remove_if(Predicate predicate, TNodeLinkList& tList) {
        iterator it = begin();

        while (!Iterator_isEnd_(const_iterator(it))) {
            if (predicate(*it)) {
                iterator itPrev = it;
                ++it;
                tList.splice(tList.end(), *this, itPrev);
            } else {
                ++it;
            }
        }
    }

    template <typename Predicate>
    void remove_if(Predicate predicate) {
        TNodeLinkList list;
        Remove_if(predicate, list);
    }

public:
    /* 0x00 */ u32 count;
    /* 0x04 */ TLinkListNode ocObject_;
};  // Size: 0xC

template <typename T, int I>
struct TLinkList : public TNodeLinkList {
    TLinkList() : TNodeLinkList() {}

    struct iterator {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

        iterator() {}
        explicit iterator(TNodeLinkList::iterator iter) : base(iter) {}

        iterator& operator++() {
            ++base;
            return *this;
        }
        iterator& operator--() {
            --base;
            return *this;
        }
        iterator operator++(int) {
            const iterator old(*this);
            ++*this;
            return old;
        }
        iterator operator--(int) {
            const iterator old(*this);
            --*this;
            return old;
        }
        friend bool operator==(iterator a, iterator b) { return a.base == b.base; }
        friend bool operator!=(iterator a, iterator b) { return !(a == b); }

        T* operator->() const { return Element_toValue(base.operator->()); }
        T& operator*() const { return *operator->(); }

    public:
        /* 0x00 */ TNodeLinkList::iterator base;
    };

    struct const_iterator {
        typedef ptrdiff_t difference_type;
        typedef const T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

        explicit const_iterator(TNodeLinkList::const_iterator iter) : base(iter) {}
        explicit const_iterator(iterator iter) : base(iter.base) {}

        const_iterator& operator++() {
            ++base;
            return *this;
        }
        const_iterator& operator--() {
            --base;
            return *this;
        }
        const_iterator operator++(int) {
            const const_iterator old(*this);
            ++*this;
            return old;
        }
        const_iterator operator--(int) {
            const const_iterator old(*this);
            --*this;
            return old;
        }
        friend bool operator==(const_iterator a, const_iterator b) { return a.base == b.base; }
        friend bool operator!=(const_iterator a, const_iterator b) { return !(a == b); }

        const T* operator->() const { return Element_toValue(base.operator->()); }
        const T& operator*() const { return *operator->(); }

    public:
        /* 0x00 */ TNodeLinkList::const_iterator base;
    };

    static TLinkListNode* Element_toNode(T* p) {
        JUT_ASSERT_DEBUG(0x2F1, p!=0);
        return reinterpret_cast<TLinkListNode*>(reinterpret_cast<char*>(p) - I);
    }
    static const TLinkListNode* Element_toNode(const T* p) {
        JUT_ASSERT_DEBUG(0x2F6, p!=0);
        return reinterpret_cast<const TLinkListNode*>(reinterpret_cast<const char*>(p) - I);
    }
    static T* Element_toValue(TLinkListNode* p) {
        JUT_ASSERT_DEBUG(0x2FB, p!=0);
        return reinterpret_cast<T*>(reinterpret_cast<char*>(p) + I);
    }
    static const T* Element_toValue(const TLinkListNode* p) {
        JUT_ASSERT_DEBUG(0x300, p!=0);
        return reinterpret_cast<const T*>(reinterpret_cast<const char*>(p) + I);
    }

    iterator Insert(iterator iter, T* element) {
        return iterator(TNodeLinkList::Insert(iter.base, Element_toNode(element)));
    }
    iterator Erase(T* element) { return iterator(TNodeLinkList::Erase(Element_toNode(element))); }

    iterator begin() { return iterator(TNodeLinkList::begin()); }
    const_iterator begin() const { return const_iterator(const_cast<TLinkList*>(this)->begin()); }
    iterator end() { return iterator(TNodeLinkList::end()); }
    const_iterator end() const { return const_iterator(const_cast<TLinkList*>(this)->end()); }
    T& front() { return *begin(); }
    T& back() { return *--end(); }
    void pop_front() { erase(TNodeLinkList::begin()); }
    void Push_front(T* element) { Insert(begin(), element); }
    void Push_back(T* element) { Insert(end(), element); }
    iterator Find(const T* element) {
        return iterator(TNodeLinkList::Find(Element_toNode(element)));
    }
    void Remove(T* element) { TNodeLinkList::Remove(Element_toNode(element)); }
};

template <typename T, int I>
struct TLinkList_factory : public TLinkList<T, I> {
    inline virtual ~TLinkList_factory() = 0;
    virtual T* Do_create() = 0;
    virtual void Do_destroy(T*) = 0;

    void Clear_destroy() {
        while (!this->empty()) {
            T* item = &this->front();
            this->pop_front();
            Do_destroy(item);
        }
    }

    typename TLinkList<T, I>::iterator Erase_destroy(T* param_0) {
        typename TLinkList<T, I>::iterator spC(Erase(param_0));
        Do_destroy(param_0);
        return spC;
    }
};

template <typename T, int I>
TLinkList_factory<T, I>::~TLinkList_factory() {
    JGADGET_ASSERTWARN(934, empty());
}

template <typename Iterator>
struct TEnumerator {
    typedef typename std::iterator_traits<Iterator>::reference reference;

    inline TEnumerator(Iterator _current, Iterator _end)
        : current(_current), end(_end) {}

    bool isEnd() const { return current != end; }
    operator bool() const { return isEnd(); }
    reference operator*() {
        reference rv = *current;
        ++current;
        return rv;
    }

    Iterator current;
    Iterator end;
};

template <typename T>
struct TEnumerator<T*> {
    inline TEnumerator(T* _current, T* _end)
        : current(_current), end(_end) {}

    bool isEnd() const { return current != end; }
    operator bool() const { return isEnd(); }
    T* operator*() {
        T* rv = current;
        ++current;
        return rv;
    }

    T* current;
    T* end;
};

template <typename T>
struct TContainerEnumerator : public TEnumerator<typename T::iterator> {
    inline TContainerEnumerator(T& param_0)
        : TEnumerator<typename T::iterator>(param_0.begin(), param_0.end()) {}
};


template <typename T>
struct TContainerEnumerator_const : public TEnumerator<typename T::const_iterator> {
    inline TContainerEnumerator_const(const T& param_0)
        : TEnumerator<typename T::const_iterator>(param_0.begin(), param_0.end()) {}
};

namespace {

template <typename T>
class TPRIsEqual_pointer_ {
public:
    TPRIsEqual_pointer_<T>(const T* p) { this->p_ = p; }

    bool operator()(const T& rSrc) const { return &rSrc == this->p_; }

private:
    const T* p_;
};

};  // namespace

};  // namespace JGadget

#endif /* LINKLIST_H */
