#ifndef _JSYSTEM_JGADGET_VECTOR_H
#define _JSYSTEM_JGADGET_VECTOR_H

#include "JSystem/JGadget/allocator.h"
#include "algorithm.h"
#include "msl_memory.h"

namespace JGadget {
namespace vector {
u32 extend_default(u32, u32, u32);

typedef u32 (*ExtendFunc)(u32, u32, u32);

} // namespace vector

template <typename T, class Allocator = JGadget::TAllocator<T> /***/>
struct TVector {
    struct TDestructed_deallocate_ {
        TDestructed_deallocate_(JGadget::TAllocator<T>& alloc, T* pointer)
        {
            mAllocator = &alloc;
            mPointer   = pointer;
        }

        ~TDestructed_deallocate_() { mAllocator->deallocate(mPointer, 0); }

        void set(T* p) { mPointer = p; }

        Allocator* mAllocator;
        T* mPointer;
    };

    ~TVector() {
        Confirm();
        clear();
        delete mBegin;
    }

    // void insert(T*, u32, const T&);
    void insert(T* position, u32 count, T const& value)
    {
        if (!count) {
            return;
        }

        void** v = Insert_raw(position, count); // insert `count` values before element at `position`

        if (v != this->mEnd) {
            for (int i = 0; i != count; i++) {
                if (v) {
                    *v = value;
                }
                v++;
            }
        }
    }

    void** Insert_raw(T* position, u32 count)
    {
        // purpose: to make space for `count` many elements at the supplied location
        // returns: pointer to location for new items

        T* const pFirst = position;

        // JUT_DEBUG_ASSERT((mBegin<=pItFirst_)&&(pItFirst_<=mEnd), 0x1be);

        // it's assumed the pointer is to something already in the vector, or pointing to the end

        if (count == 0) {
            return position;
        }

        // can we fit in the space already allocated?
        if (count + size() <= mCapacity) {

            // get the theoretical new end
            void** newEnd = pFirst + count;

            // if there exists items in the current vector past where we will insert these items
            // then we need to move them to be at the end of the vector
            if (newEnd < mEnd) {

                // get a pointer to the `count` many values that need to be pushed to the end
                void** pOverwrittenValues = mEnd - count;

                // copy `count` many values to the end of the vector
                std::uninitialized_copy(pOverwrittenValues, mEnd, mEnd);

                // copy the remaining values that need to be shifted
                // copying backwards so we don't move a value into the range we're copying from, erasing data
                std::copy_backward(pFirst, pOverwrittenValues, mEnd);

                // destroy everything from pFirst -> newEnd, this treats the inserted items as "uninitialized"
                DestroyElement_(pFirst, newEnd);

                // increment count
                mEnd += count;

                // return pointer to new items
                return pFirst;
            } else {
                // position + count >= mEnd
                // else our values that we want to add will write beyond the current mEnd

                // copy the values that exist at our pointer to the newEnd, which is position + count, making room for our `count` many
                // items
                std::uninitialized_copy(pFirst, mEnd, newEnd);

                // uninitialize the values that used to be there
                DestroyElement_(pFirst, mEnd);

                // increment count
                mEnd += count;

                // return pointer to new items
                return position;
            }
        }

        // count + size() > mCapacity
        // we need more space

        // figure out how much space we'll need
        u32 newSize = GetSize_extend_(count);

        // allocate that space
        void** newDataPointer = mAllocator.allocate(newSize, 0);

        // make sure that data was actually allocated
        if (!newDataPointer) {
            // return end pointer so we know not to actually assign any values
            return end();
        }

        // this struct will deallocate the specified data pointer when destroyed
        // If we end up throwing an exception, it'll deallocate our new data pointer, no leaks!
        TDestructed_deallocate_ destructionDeallocator(mAllocator, newDataPointer);

        // copy all the beginning of our data up to our pointer to the new data
        void** const endOfCopy = std::uninitialized_copy(mBegin, pFirst, newDataPointer);

        // copy the rest of the data to fit at the end of our new data
        // this leaves a gap of `count` many items in our new data
        std::uninitialized_copy(pFirst, mEnd, endOfCopy + count);

        // destroy all our current elements, the other elements should be living in the new data
        // and we're about to deallocate our
        DestroyElement_all_();

        // everything should be set, so now we can deallocate our old data pointer
        // when this func exits
        destructionDeallocator.set(mBegin);

        // set our new vector member variables
        mEnd      = newDataPointer + (mEnd - mBegin + count);
        mBegin    = newDataPointer;
        mCapacity = newSize;

        // return where the gap of `count` many items lives
        return endOfCopy;
    }

    void** insert(T* position, const T& value)
    {
        u32 posOffset = position - mBegin;
        // insert one value of `value` at `position`
        insert(position, 1, value);
        return mBegin + posOffset; // return pointer to new value at position
    }

    void assign(u32, const T&);
    void resize(u32, const T&);
    void Resize_raw(u32);
    void operator=(const TVector<T>& rhs);

    size_t GetSize_extend_(size_t count) const
    {
        u32 oldSize        = size();
        u32 neededNewSpace = oldSize + count;
        u32 extendedSize   = mExtend(capacity(), oldSize, count);

        return neededNewSpace > extendedSize ? neededNewSpace : extendedSize;
    }

    T* begin() { return mBegin; }
    T* const begin() const { return mBegin; }
    T* end() { return mEnd; }
    T* const end() const { return mEnd; }

    size_t capacity() const { return mCapacity; }

    inline size_t size() const
    {
        if (begin() == NULL) {
            return 0;
        }
        return ((int)mEnd - (int)mBegin) / 4;
    }

    void DestroyElement_(T* pFirst, T* pLast)
    {
        void** iter = pFirst;
        while (iter != pLast) {
            mAllocator.destroy(iter);
            ++iter;
        }
    }
    void DestroyElement_all_() { DestroyElement_(mBegin, mEnd); }

    void Confirm() const {}

    void clear() {
        erase(begin(), end());
    }
    T* erase(T* start, T* end) {
        T* ppvVar3 = std::copy(end, TVector::end(), start);
        DestroyElement_(ppvVar3, mEnd);
        mEnd = ppvVar3;
        return start;
    }

    /* 0x00 */ Allocator mAllocator;
    /* 0x04 */ T* mBegin;
    /* 0x08 */ T* mEnd;
    /* 0x0C */ size_t mCapacity;
    /* 0x10 */ vector::ExtendFunc mExtend;
};

// clang-format off
struct TVector_pointer_void : public TVector<void*, TAllocator<void*> > {
    TVector_pointer_void(const JGadget::TAllocator<void*>& allocator);
    TVector_pointer_void(u32, void* const&, const JGadget::TAllocator<void*>& allocator); // unused/inlined

    ~TVector_pointer_void();

    void** erase(void**, void**);
    void** insert(void**, void* const&);

    void clear() { erase(begin(), end()); }
    void push_back(const void*& value) { insert(end(), (void* const&)value); }

    /* 0x00 */ /* TVector */
};
// clang-format on

template <typename T>
struct TVector_pointer : public TVector_pointer_void {
    TVector_pointer(const TAllocator<void*>& allocator)
        : TVector_pointer_void(allocator)
    {
    }

    ~TVector_pointer() { }

    const T* begin() const { return (const T*)TVector_pointer_void::begin(); }
    T* begin() { return (T*)TVector_pointer_void::begin(); }

    const T* end() const { return (const T*)TVector_pointer_void::end(); }
    T* end() { return (T*)TVector_pointer_void::end(); }

    void push_back(const T& value) { TVector_pointer_void::push_back((const void*&)value); }

    /* 0x00 */ /* TVector_pointer_void */
};

// clang-format off
typedef JGadget::TVector<void*, JGadget::TAllocator<void*> > TVPVBase;
// clang-format on

// template <>
// void TVPVBase::insert(void** values, u32 count, void* const& defaultValue)
// {
//     if (!count) {
//         return;
//     }

//     void** v = Insert_raw(values, count);

//     if (v != this->mEnd) {
//         for (int i = 0; i != count; i++) {
//             if (v) {
//                 *v = defaultValue;
//             }
//             v++;
//         }
//     }
// }

/**
 * @note Address: 0x80027718
 * @note Size: 0x470
 */
template <>
void** TVPVBase::Insert_raw(void** pItFirst, u32 count)
{
    // purpose: to make space for `count` many elements at the supplied location
    // returns: pointer to location for new items

    void** const pItFirst_ = pItFirst;

    // JUT_DEBUG_ASSERT((mBegin<=pItFirst_)&&(pItFirst_<=mEnd), 0x1be);

    // it's assumed the pointer is to something already in the vector, or pointing to the end

    if (count == 0) {
        return pItFirst;
    }

    // can we fit in the space already allocated?
    if (count + size() <= mCapacity) {

        // get the theoretical new end
        void** newEnd = pItFirst_ + count;

        // if there exists items in the current vector past where we will insert these items
        // then we need to move them to be at the end of the vector
        if (newEnd < mEnd) {

            // get a pointer to the `count` many values that need to be pushed to the end
            void** pOverwrittenValues = mEnd - count;

            // copy `count` many values to the end of the vector
            std::uninitialized_copy(pOverwrittenValues, mEnd, mEnd);

            // copy the remaining values that need to be shifted
            // copying backwards so we don't move a value into the range we're copying from, erasing data
            std::copy_backward(pItFirst_, pOverwrittenValues, mEnd);

            // destroy everything from pItFirst_ -> newEnd, this treats the inserted items as "uninitialized"
            DestroyElement_(pItFirst_, newEnd);

            // increment count
            mEnd += count;

            // return pointer to new items
            return pItFirst;
        } else {
            // pItFirst + count >= mEnd
            // else our values that we want to add will write beyond the current mEnd

            // copy the values that exist at our pointer to the newEnd, which is pItFirst + count, making room for our `count` many
            // items
            std::uninitialized_copy(pItFirst_, mEnd, newEnd);

            // uninitialize the values that used to be there
            DestroyElement_(pItFirst_, mEnd);

            // increment count
            mEnd += count;

            // return pointer to new items
            return pItFirst;
        }
    }

    // count + size() > mCapacity
    // we need more space

    // figure out how much space we'll need
    u32 newSize = GetSize_extend_(count);

    // allocate that space
    void** newDataPointer = mAllocator.allocate(newSize, 0);

    // make sure that data was actually allocated
    if (!newDataPointer) {
        // return end pointer?
        return end();
    }

    // this struct will deallocate the specified data pointer when destroyed
    // If we end up throwing an exception, it'll deallocate our new data pointer, no leaks!
    TDestructed_deallocate_ destructionDeallocator(mAllocator, newDataPointer);

    // copy all the beginning of our data up to our pointer to the new data
    void** const endOfCopy = std::uninitialized_copy(mBegin, pItFirst_, newDataPointer);

    // copy the rest of the data to fit at the end of our new data
    // this leaves a gap of `count` many items in our new data
    std::uninitialized_copy(pItFirst_, mEnd, endOfCopy + count);

    // destroy all our current elements, the other elements should be living in the new data
    // and we're about to deallocate our
    DestroyElement_all_();

    // everything should be set, so now we can deallocate our old data pointer
    // when this func exits
    destructionDeallocator.set(mBegin);

    // set our new vector member variables
    mEnd      = newDataPointer + (mEnd - mBegin + count);
    mBegin    = newDataPointer;
    mCapacity = newSize;

    // return where the gap of `count` many items lives
    return endOfCopy;
}

} // namespace JGadget

#endif
