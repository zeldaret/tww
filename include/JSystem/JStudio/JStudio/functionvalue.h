#ifndef FUNCTIONVALUE_H
#define FUNCTIONVALUE_H

#include "JSystem/JGadget/search.h"
#include "JSystem/JGadget/vector.h"
#include "global.h"

namespace JStudio {

typedef f64 (*ExtrapolateParameter)(f64, f64);

class TFunctionValue;
class TFunctionValueAttributeSet;

class TFunctionValueAttribute_refer;
class TFunctionValueAttribute_range;
class TFunctionValueAttribute_interpolate;

class TFunctionValue {
public:
    enum TEProgress { PROG_INIT };
    enum TEAdjust { ADJ_INIT, ADJ_UNK1, ADJ_UNK2, ADJ_UNK3, ADJ_UNK4 };
    enum TEOutside { OUT_INIT };
    enum TEInterpolate {};

    TFunctionValue();
    virtual ~TFunctionValue() = 0;

    virtual u32 getType() const = 0;
    virtual TFunctionValueAttributeSet getAttributeSet() = 0;
    virtual void initialize() = 0;
    virtual void prepare() = 0;
    virtual f64 getValue(f64 arg1) = 0;

    static ExtrapolateParameter toFunction_outside(int);

    static ExtrapolateParameter toFunction(TFunctionValue::TEOutside outside) {
        return toFunction_outside(outside);
    }
};

class TFunctionValueAttributeSet_const {
public:
    TFunctionValueAttributeSet_const(TFunctionValueAttribute_refer* refer,
                                     TFunctionValueAttribute_range* range,
                                     TFunctionValueAttribute_interpolate* interp)
        : refer_(refer), range_(range), interp_(interp) {}

    TFunctionValueAttribute_refer* refer_get() const { return refer_; }
    TFunctionValueAttribute_range* range_get() const { return range_; }
    TFunctionValueAttribute_interpolate* interpolate_get() const { return interp_; }

private:
    /* 0x00 */ TFunctionValueAttribute_refer* refer_;
    /* 0x04 */ TFunctionValueAttribute_range* range_;
    /* 0x08 */ TFunctionValueAttribute_interpolate* interp_;
};

class TFunctionValueAttributeSet : public TFunctionValueAttributeSet_const {
public:
    TFunctionValueAttributeSet(TFunctionValueAttribute_refer* refer,
                               TFunctionValueAttribute_range* range,
                               TFunctionValueAttribute_interpolate* interp)
        : TFunctionValueAttributeSet_const(refer, range, interp) {}

    TFunctionValueAttribute_refer* refer_get() const {
        return static_cast<const TFunctionValueAttributeSet_const*>(this)->refer_get();
    }
    TFunctionValueAttribute_range* range_get() const {
        return static_cast<const TFunctionValueAttributeSet_const*>(this)->range_get();
    }
    TFunctionValueAttribute_interpolate* interpolate_get() const {
        return static_cast<const TFunctionValueAttributeSet_const*>(this)->interpolate_get();
    }
};

class TFunctionValueAttribute_refer : public JGadget::TVector_pointer<TFunctionValue*> {
public:
    TFunctionValueAttribute_refer() :
    JGadget::TVector_pointer<TFunctionValue*>(JGadget::TAllocator<void*>()) {}
    ~TFunctionValueAttribute_refer() {}

    void refer_initialize();

    const TFunctionValueAttribute_refer* refer_getContainer() const { return this; }
    JGadget::TVector_pointer<TFunctionValue*>& refer_referContainer() { return *this; }
    bool refer_isReferring(const TFunctionValue* p) const { return false; }  // todo
};

class TFunctionValueAttribute_range {
public:
    TFunctionValueAttribute_range();

    void range_initialize();
    void range_prepare();
    void range_set(f64, f64);
    f64 range_getParameter(f64, f64, f64) const;

    TFunctionValue::TEProgress range_getProgress() const {
        return (TFunctionValue::TEProgress)mProgress;
    }
    void range_setProgress(TFunctionValue::TEProgress progress) { mProgress = progress; }
    TFunctionValue::TEAdjust range_getAdjust() const { return (TFunctionValue::TEAdjust)mAdjust; }
    void range_setAdjust(TFunctionValue::TEAdjust adjust) { mAdjust = adjust; }
    void range_setOutside(TFunctionValue::TEOutside outside) { range_setOutside(outside, outside); }
    void range_setOutside(TFunctionValue::TEOutside begin, TFunctionValue::TEOutside end) {
        range_setOutside_begin(begin);
        range_setOutside_end(end);
    }
    void range_setOutside_begin(TFunctionValue::TEOutside begin) { mBegin = begin; }
    void range_setOutside_end(TFunctionValue::TEOutside end) { mEnd = end; }
    f64 range_getParameter_outside(f64 arg1) const {
        f64 result = arg1;
        result -= fBegin_;
        if (result < 0.0) {
            result = TFunctionValue::toFunction(mBegin)(result, fDifference_);
        } else if (result >= fDifference_) {
            result = TFunctionValue::toFunction(mEnd)(result, fDifference_);
        }
        result += fBegin_;
        return result;
    }
    f64 range_getParameter_progress(f64 arg1) const { return _20 + _28 * (arg1 - _20); }
    f64 range_getBegin() const { return fBegin_;}
    f64 range_getEnd() const { return fEnd_;}
    f64 range_getDifference() const { return fDifference_; }

private:
    /* 0x00 */ f64 fBegin_;
    /* 0x08 */ f64 fEnd_;
    /* 0x10 */ f64 fDifference_;
    /* 0x18 */ s8 mProgress;
    /* 0x19 */ s8 mAdjust;
    /* 0x1A */ s8 _1a[2];
    /* 0x1C */ u32 _1c;
    /* 0x20 */ f64 _20;
    /* 0x28 */ f64 _28;
    /* 0x30 */ TFunctionValue::TEOutside mBegin;
    /* 0x34 */ TFunctionValue::TEOutside mEnd;
};

class TFunctionValueAttribute_interpolate {
public:
    TFunctionValueAttribute_interpolate() : interpolate_(0) {}

    void interpolate_initialize() { interpolate_ = 0; }
    void interpolate_prepare() {}
    u32 interpolate_get() const { return interpolate_; }
    void interpolate_set(TFunctionValue::TEInterpolate interpolate) { interpolate_ = interpolate; }

private:
    /* 0x0 */ u32 interpolate_;
};

class TFunctionValue_constant : public TFunctionValue {
public:
    TFunctionValue_constant();
    virtual ~TFunctionValue_constant() {}

    virtual u32 getType() const;
    virtual TFunctionValueAttributeSet getAttributeSet();
    virtual void initialize();
    virtual void prepare();
    virtual f64 getValue(f64);

    void data_set(f64 value) { fValue_ = value; }

private:
    f64 fValue_;
};

class TFunctionValue_composite : public TFunctionValue, public TFunctionValueAttribute_refer {
public:
    struct TData {
        TData(void* data) : u32data((u32)data) {}
        TData(const void* data) : rawData(data) {}
        TData(u32 data) : u32data(data) {}
        TData(f32 data) : f32data(data) {}

        inline void operator=(const TData& rhs) { f32data = rhs.f32data; }
        u32 get_unsignedInteger() const { return u32data; }
        f64 get_value() const { return f32data; }

        union {
            const void* rawData;
            u32 u32data;
            f64 f32data;
        };
    };
    typedef f64 (*UnkFunc)(f64, const TFunctionValueAttribute_refer*,
                           const TFunctionValue_composite::TData*);
    typedef f64 (*CompositeFunc)(const JGadget::TVector_pointer<TFunctionValue>&,
                                 const TFunctionValue_composite::TData&, f64);

    TFunctionValue_composite();
    virtual ~TFunctionValue_composite() {}

    virtual u32 getType() const;
    virtual TFunctionValueAttributeSet getAttributeSet();
    virtual void initialize();
    virtual void prepare();
    virtual f64 getValue(f64);
    static f64 composite_raw(TVector_pointer<TFunctionValue*> const&, TData const&, f64);
    static f64 composite_index(TVector_pointer<TFunctionValue*> const&, TData const&, f64);
    static f64 composite_parameter(TVector_pointer<TFunctionValue*> const&,
                                                  TData const&, f64);
    static f64 composite_add(TVector_pointer<JStudio::TFunctionValue*> const&,
                                            TData const&, f64);
    static f64 composite_subtract(TVector_pointer<TFunctionValue*> const&, TData const&,
                                           f64);
    static f64 composite_multiply(TVector_pointer<TFunctionValue*> const&, TData const&,
                                           f64);
    static f64 composite_divide(TVector_pointer<TFunctionValue*> const&, TData const&,
                                         f64);

    void data_set(CompositeFunc fn, const TData& dat) {
        pfn_ = (UnkFunc)fn;
        data_setData(dat);
    }
    const TData* data_getData() const { return &data; }
    void data_setData(const TData& dat) { data = dat; }

// private:
    UnkFunc pfn_;
    TData data;
};

class TFunctionValue_transition : public TFunctionValue,
                                  public TFunctionValueAttribute_range,
                                  public TFunctionValueAttribute_interpolate {
public:
    TFunctionValue_transition();
    virtual ~TFunctionValue_transition() {}

    virtual u32 getType() const;
    virtual TFunctionValueAttributeSet getAttributeSet();
    virtual void initialize();
    virtual void prepare();
    virtual f64 getValue(f64);

    void data_set(f64 a1, f64 a2) {
        _48 = a1;
        _50 = a2;
    }

    f64 data_getDifference() const { return _50 - _48; }

private:
    /* 0x48 */ f64 _48;
    /* 0x50 */ f64 _50;
};

class TFunctionValue_list : public TFunctionValue,
                            public TFunctionValueAttribute_range,
                            public TFunctionValueAttribute_interpolate {
public:
    struct TIndexData_ {
        f64 _0;
        f64 _8;
        u32 _10;
    };
    typedef f64 (*update_INTERPOLATE)(const TFunctionValue_list&, const TIndexData_&);

    TFunctionValue_list();
    virtual ~TFunctionValue_list() {}

    virtual u32 getType() const;
    virtual TFunctionValueAttributeSet getAttributeSet();
    virtual void initialize();
    virtual void prepare();
    virtual f64 getValue(f64);

    void data_set(const f32* pf, u32 u) {
        ASSERT((pf != NULL) || (u == 0));
        _44 = pf;
        uData_ = u;
    }

    void data_setInterval(f64 f) {
        ASSERT(f > TValue(0));
        _50 = f;
    }

    static f64
    update_INTERPOLATE_NONE_(JStudio::TFunctionValue_list const&,
                             JStudio::TFunctionValue_list::TIndexData_ const&);
    static f64
    update_INTERPOLATE_LINEAR_(JStudio::TFunctionValue_list const&,
                               JStudio::TFunctionValue_list::TIndexData_ const&);
    static f64
    update_INTERPOLATE_PLATEAU_(JStudio::TFunctionValue_list const&,
                                JStudio::TFunctionValue_list::TIndexData_ const&);
    static f64
    update_INTERPOLATE_BSPLINE_dataMore3_(JStudio::TFunctionValue_list const&,
                                          JStudio::TFunctionValue_list::TIndexData_ const&);

private:
    /* 0x44 */ const f32* _44;
    /* 0x48 */ u32 uData_;
    /* 0x50 */ f64 _50;
    /* 0x58 */ update_INTERPOLATE pfnUpdate_;
};

class TFunctionValue_list_parameter : public TFunctionValue,
                                      public TFunctionValueAttribute_range,
                                      public TFunctionValueAttribute_interpolate {
public:
    struct TIterator_data_ {
        TIterator_data_(const f32* value) : value_(value) {}
        TIterator_data_(const TIterator_data_& other) : value_(other.value_) {}

        void operator=(const TIterator_data_& rhs) { value_ = rhs.value_; }
        TIterator_data_& operator--() {
            value_ -= 2;
            return *this;
        }
        friend bool operator==(const TIterator_data_& lhs, const TIterator_data_& rhs) { return lhs.value_ == rhs.value_; }

        const f32* get() const { return value_; }
        void set(const f32* value) { value_ = value; }

        const f32* value_;
    };
    typedef f64 (*update_INTERPOLATE)(const TFunctionValue_list_parameter&, f64);

    TFunctionValue_list_parameter();
    virtual ~TFunctionValue_list_parameter() {}

    virtual u32 getType() const;
    virtual TFunctionValueAttributeSet getAttributeSet();
    void data_set(f32 const*, u32);
    virtual void initialize();
    virtual void prepare();
    virtual f64 getValue(f64);

    static f64
    update_INTERPOLATE_NONE_(JStudio::TFunctionValue_list_parameter const&, f64);
    static f64
    update_INTERPOLATE_LINEAR_(JStudio::TFunctionValue_list_parameter const&, f64);
    static f64
    update_INTERPOLATE_PLATEAU_(JStudio::TFunctionValue_list_parameter const&, f64);
    static f64
    update_INTERPOLATE_BSPLINE_dataMore3_(JStudio::TFunctionValue_list_parameter const&, f64);

    f64 data_getValue_back() { 
        return pfData_[(uData_ - 1) * 2];
    }
    f64 data_getValue_front() { return pfData_[0]; }

private:
    /* 0x44 */ const f32* pfData_;
    /* 0x48 */ u32 uData_;
    /* 0x4c */ TIterator_data_ dat1;
    /* 0x50 */ TIterator_data_ dat2;
    /* 0x54 */ TIterator_data_ dat3;
    /* 0x58 */ update_INTERPOLATE pfnUpdate_;
};

class TFunctionValue_hermite : public TFunctionValue, public TFunctionValueAttribute_range {
public:
    struct TIterator_data_ {
        TIterator_data_(const TFunctionValue_hermite& rParent, const f32* value) {
            value_ = value;
            size_ = rParent.data_getSize();
        }

        const f32* get() { return value_; }

        void set(const f32* value, u32 size) {
            value_ = value;
            size_ = size;
        }
   
        friend bool operator==(const TIterator_data_& lhs, const TIterator_data_& rhs) { return lhs.value_ == rhs.value_; }

        TIterator_data_& operator--() {
            value_ -= size_;
            return *this;
        }

        /* 0x00 */ const f32* value_;
        /* 0x04 */ u32 size_;
    };

    TFunctionValue_hermite();
    virtual ~TFunctionValue_hermite() {}

    virtual u32 getType() const;
    virtual TFunctionValueAttributeSet getAttributeSet();
    void data_set(f32 const*, u32, u32);
    virtual void initialize();
    virtual void prepare();
    virtual f64 getValue(f64);

    u32 data_getSize() const { return uSize_; }
    f64 data_getValue_back() { 
        return pf_[(u_ - 1) * uSize_];
    }
    f64 data_getValue_front() { return pf_[0]; }

private:
    /* 0x40 */ const f32* pf_;
    /* 0x44 */ u32 u_;
    /* 0x48 */ u32 uSize_;
    /* 0x4c */ TIterator_data_ dat1;
    /* 0x50 */ TIterator_data_ dat2;
    /* 0x54 */ TIterator_data_ dat3;
};

}  // namespace JStudio

#endif /* FUNCTIONVALUE_H */
