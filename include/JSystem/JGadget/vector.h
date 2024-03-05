#ifndef JGADGET_VECTOR_H
#define JGADGET_VECTOR_H

#include "JSystem/JGadget/allocator.h"
#include "dolphin/types.h"

namespace JGadget {
namespace vector {
u32 extend_default(u32, u32, u32);

typedef u32 (*ExtendFunc)(u32, u32, u32);

} // namespace vector

template <typename T, template <class> class Allocator>
struct TVector {
    // struct Destructed_deallocate_ {
    //     ~Destructed_deallocate_(); // unused/inlined
    // };

    // TVector(u32, const T&, const Allocator<T>&);

    // TVector(Allocator<T> alloc)
    // {
    //     _00     = alloc._00;
    //     _04     = nullptr;
    //     mBegin = nullptr;
    //     mEnd  = nullptr;
    //     mExtend = vector::extend_default;
    // }

    ~TVector();

    void insert(T*, u32, const T&);
    void Insert_raw(T*, u32);
    void insert(T*, const T&);
    void assign(u32, const T&);
    void resize(u32, const T&);
    void Resize_raw(u32);
    void operator=(const TVector<T, Allocator>& rhs);

    inline u32 size() const {
        if (mBegin == NULL) {
            return 0;
        }

        return ((int)mEnd - (int)mBegin) / 4;
    }

    void** begin() { return mBegin; }
    void** const begin() const { return mBegin; }
    void** end() { return mEnd; }
    void** const end() const { return mEnd; }

    u8 _00;
    void** mBegin;
    void** mEnd;
    void** _0C;
    vector::ExtendFunc mExtend;
};

struct TVector_pointer_void : TVector<void*, TAllocator> {
    TVector_pointer_void(const JGadget::TAllocator<void*>&);

    ~TVector_pointer_void();

    void insert(void**, void* const&);
    void erase(void**, void**);

    void clear() { erase(begin(), end()); }
    void push_back(const void*& ref) { insert(end(), (void* const&)ref); }
};

template <typename T>
struct TVector_pointer : TVector_pointer_void {
    TVector_pointer(const TAllocator<void*>& allocator) : TVector_pointer_void(allocator) {}
    ~TVector_pointer() {}

    const T* begin() const { return (const T*)TVector_pointer_void::begin(); }
    T* begin() { return (T*)TVector_pointer_void::begin(); }

    const T* end() const { return (const T*)TVector_pointer_void::end(); }
    T* end() { return (T*)TVector_pointer_void::end(); }

    void push_back(const T& ref) {
        static_cast<TVector_pointer_void*>(this)->push_back((const void*&)ref);
    }
};

}  // namespace JGadget

#endif /* JGADGET_VECTOR_H */
