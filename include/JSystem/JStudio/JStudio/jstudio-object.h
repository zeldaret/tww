#ifndef JSTUDIO_OBJECT_H
#define JSTUDIO_OBJECT_H

#include "JSystem/JStudio/JStudio/jstudio-control.h"
#include "limits.h"

typedef struct _GXColor GXColor;

namespace JStudio {
namespace data {
    enum TEOperationData {
        TEOD_Unknown_00 = 0x00,
        TEOD_Unknown_01 = 0x01,
        TEOD_Unknown_02 = 0x02,
        TEOD_Unknown_03 = 0x03,
        TEOD_Unknown_04 = 0x04,
        TEOD_Unknown_05 = 0x05,
        TEOD_Unknown_06 = 0x06,
        TEOD_Unknown_07 = 0x07,
        TEOD_Unknown_08 = 0x08,
        TEOD_Unknown_09 = 0x09,
        TEOD_Unknown_0A = 0x0A,
        TEOD_Unknown_0B = 0x0B,
        TEOD_Unknown_0C = 0x0C,
        TEOD_Unknown_0D = 0x0D,
        TEOD_Unknown_0E = 0x0E,
        TEOD_Unknown_0F = 0x0F,
        TEOD_Unknown_10 = 0x10,
        TEOD_Unknown_11 = 0x11,
        TEOD_Unknown_12 = 0x12,
        TEOD_Unknown_13 = 0x13,
        TEOD_Unknown_14 = 0x14,
        TEOD_Unknown_15 = 0x15,
        TEOD_Unknown_16 = 0x16,
        TEOD_Unknown_17 = 0x17,
        TEOD_Unknown_18 = 0x18,
        TEOD_Unknown_19 = 0x19,
    };
};

struct TAdaptor;
struct TVariableValue {
    struct TOutput {
        virtual void operator()(f32, JStudio::TAdaptor*) const = 0;
        virtual ~TOutput() = 0;
    };  // Size: 0x04

    struct TOutput_none_ : public TOutput {
        ~TOutput_none_();
        void operator()(f32, JStudio::TAdaptor*) const;
    };

    void update(f64, JStudio::TAdaptor*);
    static void update_immediate_(JStudio::TVariableValue*, f64);
    static void update_time_(JStudio::TVariableValue*, f64);
    static void update_functionValue_(JStudio::TVariableValue*, f64);
    TVariableValue()
        : field_0x4(0)
        , field_0x8(NULL)
        , pOutput_(&soOutput_none_)
    {
    }

    void setValue_immediate(f32 value) {
        field_0x8 = &update_immediate_;
        field_0x4 = 0;
        field_0xc.val = value;
    }

     void setValue_none() {
        field_0x8 = NULL;
    }

    void setValue_time(f32 value) {
        field_0x8 = &update_time_;
        field_0x4 = 0;
        field_0xc.val = value;
    }
    
    void setValue_functionValue(TFunctionValue* value) {
        field_0x8 = &update_functionValue_;
        field_0x4 = 0;
        field_0xc.fv = value;
    }

    f32 getValue() const { return mValue; }

    template<typename T>
    T getValue_clamp() const {
        f32 val = mValue;
        if (val <= std::numeric_limits<T>::min()) {
            return std::numeric_limits<T>::min();
        } else if (val >= std::numeric_limits<T>::max()) {
            return std::numeric_limits<T>::max();
        }
        return val;
    }
    u8 getValue_uint8() const { return getValue_clamp<u8>(); }

    void forward(u32 param_0) {
        if (std::numeric_limits<u32>::max() - field_0x4 <= param_0) {
            field_0x4 = std::numeric_limits<u32>::max();
        } else {
            field_0x4 += param_0;
        }
    }

    inline void setOutput(const TOutput* output) {
        pOutput_ = (output != NULL ? (TOutput*)output : (TOutput*)&soOutput_none_);
    }

    static TOutput_none_ soOutput_none_;

    /* 0x00 */ f32 mValue;
    /* 0x04 */ u32 field_0x4;
    /* 0x08 */ void (*field_0x8)(TVariableValue*, double);
    /* 0x0C */ union {
        TFunctionValue* fv;
        f32 val;
    } field_0xc;
    /* 0x10 */ TOutput* pOutput_;
};  // Size: 0x14

typedef void (TObject::*paragraphFunc)(u32, void const*, u32); 

class TObject : public stb::TObject {
public:
    TObject(JStudio::stb::data::TParse_TBlock_object const&, JStudio::TAdaptor*);
    void forward_value(u32);

    virtual ~TObject() = 0;
    virtual void do_begin();
    virtual void do_end();
    virtual void do_paragraph(u32, void const*, u32) = 0;
    virtual void do_wait(u32);
    virtual void do_data(void const*, u32, void const*, u32);

    TAdaptor* getAdaptor() { return mpAdaptor; }
    TControl* getControl() { return (TControl*)stb::TObject::getControl(); }
    const TControl* getControl() const { return (const TControl*)stb::TObject::getControl(); }

    void prepareAdaptor() {
        if (mpAdaptor != NULL) {
            // mpAdaptor->adaptor_setObject_(this);
            // mpAdaptor->adaptor_do_begin();
        }
    }

    template<class T>
    T* createFromAdaptor(const stb::data::TParse_TBlock_object& param_0, T* param_1) {
        T* n = new T(param_0, param_1);

        if (n == NULL) {
            return NULL;
        }

        n->prepareAdaptor();

        return n;
    }

    /* 0x34 */ TAdaptor* mpAdaptor;
};

struct TAdaptor {
    inline TAdaptor(TVariableValue* values, int count)
        : mVariableValues(values)
        , mCount(count)
    {
    }

    struct TSetVariableValue_immediate {
        inline TSetVariableValue_immediate(u32 p1, f32 p2)
            : field_0x0(p1)
            , field_0x4(p2)
        {
        }

        u32 field_0x0;
        f32 field_0x4;
    };
    typedef void (*setVarFunc)(JStudio::TAdaptor*, JStudio::TObject*, u32, void const*, u32);
    virtual ~TAdaptor() = 0;
    virtual void adaptor_do_prepare(const JStudio::TObject*);
    virtual void adaptor_do_begin(const JStudio::TObject*);
    virtual void adaptor_do_end(const JStudio::TObject*);
    virtual void adaptor_do_update(const JStudio::TObject*, u32);
    virtual void adaptor_do_data(const JStudio::TObject*, void const*, u32, void const*, u32);

    void adaptor_setVariableValue(JStudio::TObject*, u32, JStudio::data::TEOperationData, void const*, u32);
    void adaptor_setVariableValue_n(JStudio::TObject*, u32 const*, u32, JStudio::data::TEOperationData, void const*, u32);
    void adaptor_setVariableValue_immediate(JStudio::TAdaptor::TSetVariableValue_immediate const*);
    void adaptor_setVariableValue_Vec(u32 const*, Vec const&);
    void adaptor_getVariableValue_Vec(Vec*, u32 const*) const;
    void adaptor_setVariableValue_GXColor(u32 const*, GXColor const&);
    void adaptor_getVariableValue_GXColor(GXColor*, u32 const*) const;
    void adaptor_updateVariableValue(JStudio::TObject*, u32);
    static void adaptor_setVariableValue_VOID_(JStudio::TAdaptor*, JStudio::TObject*, u32,
                                                       void const*, u32);
    static void adaptor_setVariableValue_IMMEDIATE_(JStudio::TAdaptor*, JStudio::TObject*,
                                                            u32, void const*, u32);
    static void adaptor_setVariableValue_TIME_(JStudio::TAdaptor*, JStudio::TObject*, u32,
                                                       void const*, u32);
    static void adaptor_setVariableValue_FVR_NAME_(JStudio::TAdaptor*, JStudio::TObject*,
                                                           u32, void const*, u32);
    static void adaptor_setVariableValue_FVR_INDEX_(JStudio::TAdaptor*, JStudio::TObject*,
                                                            u32, void const*, u32);


    TVariableValue* adaptor_referVariableValue(u32 param_0) {
        return &mVariableValues[param_0];
    }

    void adaptor_setVariableValue_immediate(u32 param_0, f32 param_1) {
        adaptor_referVariableValue(param_0)->setValue_immediate(param_1);
    }

     const TVariableValue* adaptor_getVariableValue(u32 param_0) const {
        return &mVariableValues[param_0];
    }

    /* 0x4 */ TVariableValue* mVariableValues;
    /* 0x8 */ u32 mCount;
};

struct TAdaptor_actor : public TAdaptor {
    enum TEVariableValue {
        TE_VALUE_NONE = -1,
        TEACTOR_1 = 1,
    };

    TAdaptor_actor()
        : TAdaptor(mValue, ARRAY_SIZE(mValue))
        , mValue()
    {
    }
    virtual ~TAdaptor_actor() = 0;
    virtual void adaptor_do_PARENT(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_PARENT_NODE(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_PARENT_ENABLE(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_RELATION(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_RELATION_NODE(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_RELATION_ENABLE(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_SHAPE(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_ANIMATION(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_ANIMATION_MODE(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_TEXTURE_ANIMATION(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_TEXTURE_ANIMATION_MODE(JStudio::data::TEOperationData, void const*, u32) = 0;

    /* 0x10 */ TVariableValue mValue[14];

    static u32 const sauVariableValue_3_TRANSLATION_XYZ[3];
    static u32 const sauVariableValue_3_ROTATION_XYZ[3];
    static u32 const sauVariableValue_3_SCALING_XYZ[3];
};  // Size: 0x128

struct TObject_actor : public TObject {
    TObject_actor(JStudio::stb::data::TParse_TBlock_object const&,
                                 JStudio::TAdaptor_actor*);
    
    virtual ~TObject_actor();
    virtual void do_paragraph(u32, void const*, u32);
};

struct TAdaptor_ambientLight : public TAdaptor {
    TAdaptor_ambientLight()
        : TAdaptor(mValue, ARRAY_SIZE(mValue))
        , mValue()
    {
    }
    virtual ~TAdaptor_ambientLight()  = 0;

    /* 0x10 */ TVariableValue mValue[4];

    static const u32 sauVariableValue_3_COLOR_RGB[3];
    static const u32 sauVariableValue_4_COLOR_RGBA[4];
};

struct TObject_ambientLight : public TObject {
    TObject_ambientLight(JStudio::stb::data::TParse_TBlock_object const&,
                                        JStudio::TAdaptor_ambientLight*);
    
    virtual ~TObject_ambientLight();
    virtual void do_paragraph(u32, void const*, u32);
};

struct TAdaptor_camera : public TAdaptor {
    enum TEVariableValue {
        TE_VALUE_NONE = -1,
        TECAMERA_6 = 6,
        TECAMERA_7 = 7,
        TECAMERA_8 = 8,
        TECAMERA_9 = 9,
    };

    TAdaptor_camera()
        : TAdaptor(mValue, ARRAY_SIZE(mValue))
        , mValue()
    {
    }
    virtual ~TAdaptor_camera() = 0;
    virtual void adaptor_do_PARENT(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_PARENT_NODE(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_PARENT_ENABLE(JStudio::data::TEOperationData, void const*, u32) = 0;

    /* 0x10 */ TVariableValue mValue[11];

    static u32 const sauVariableValue_3_POSITION_XYZ[3];
    static u32 const sauVariableValue_3_TARGET_POSITION_XYZ[3];
    static u32 const sauVariableValue_2_DISTANCE_NEAR_FAR[2];
};

struct TObject_camera : public TObject {
    TObject_camera(JStudio::stb::data::TParse_TBlock_object const&, JStudio::TAdaptor_camera*);
    
    virtual ~TObject_camera();
    virtual void do_paragraph(u32, void const*, u32);
};

struct TAdaptor_fog : public TAdaptor {
    enum TEVariableValue {
        TE_VALUE_NONE = -1,
        TEFOG_4 = 4,
        TEFOG_5 = 5,
    };

    TAdaptor_fog()
        : TAdaptor(mValue, ARRAY_SIZE(mValue))
        , mValue()
    {
    }
    virtual ~TAdaptor_fog() = 0;

    /* 0x10 */ TVariableValue mValue[6];

    static const u32 sauVariableValue_3_COLOR_RGB[3];
    static const u32 sauVariableValue_4_COLOR_RGBA[4];
    static const u32 sauVariableValue_2_RANGE_BEGIN_END[2];
};

struct TObject_fog : public TObject {
    TObject_fog(JStudio::stb::data::TParse_TBlock_object const&,
                               JStudio::TAdaptor_fog*);
    
    virtual ~TObject_fog();
    virtual void do_paragraph(u32, void const*, u32);
};

struct TAdaptor_light : public TAdaptor {
    enum TEVariableValue {
        TE_VALUE_NONE = -1,
        TE_VALUE_7 = 7,
        TE_VALUE_8 = 8,
        TE_VALUE_9 = 9,
        TE_VALUE_10 = 10,
        TE_VALUE_11 = 11,
    };
    enum TEDirection_ {
        DIRECTION_0,
        DIRECTION_1,
        DIRECTION_2,
    };

    TAdaptor_light()
        : TAdaptor(mValue, ARRAY_SIZE(mValue))
        , mValue()
    {
    }
    virtual ~TAdaptor_light() = 0;
    virtual void adaptor_do_ENABLE(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_FACULTY(JStudio::data::TEOperationData, void const*, u32) = 0;

    /* 0x10 */ TVariableValue mValue[13];

    static u32 const sauVariableValue_3_COLOR_RGB[3];
    static u32 const sauVariableValue_4_COLOR_RGBA[4];
    static u32 const sauVariableValue_3_POSITION_XYZ[3];
    static u32 const sauVariableValue_3_TARGET_POSITION_XYZ[3];
    static u32 const sauVariableValue_2_DIRECTION_THETA_PHI[2];
};

struct TObject_light : public TObject {
    TObject_light(JStudio::stb::data::TParse_TBlock_object const&,
                                 JStudio::TAdaptor_light*);
    
    virtual ~TObject_light();
    virtual void do_paragraph(u32, void const*, u32);
};

struct TAdaptor_message : public TAdaptor {
    TAdaptor_message()
        : TAdaptor(NULL, 0)
    {
    }

    virtual ~TAdaptor_message() = 0;
    virtual void adaptor_do_MESSAGE(JStudio::data::TEOperationData, const void*, u32) = 0;
};

struct TObject_message : public TObject {
    TObject_message(JStudio::stb::data::TParse_TBlock_object const&,
                                   JStudio::TAdaptor_message*);
    
    virtual ~TObject_message();
    virtual void do_paragraph(u32, void const*, u32);
};

struct TAdaptor_particle : public TAdaptor {
    TAdaptor_particle()
        : TAdaptor(mValue, ARRAY_SIZE(mValue))
        , mValue()
    {
    }
    virtual ~TAdaptor_particle() = 0;
    virtual void adaptor_do_PARTICLE(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_PARENT(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_PARENT_NODE(JStudio::data::TEOperationData, void const*, u32) = 0;
    virtual void adaptor_do_PARENT_ENABLE(JStudio::data::TEOperationData, void const*, u32) = 0;

    /* 0x10 */ TVariableValue mValue[20];

    static u32 const sauVariableValue_3_TRANSLATION_XYZ[3];
    static u32 const sauVariableValue_3_ROTATION_XYZ[3];
    static u32 const sauVariableValue_3_SCALING_XYZ[3];
    static u32 const sauVariableValue_3_COLOR_RGB[3];
    static u32 const sauVariableValue_4_COLOR_RGBA[4];
    static u32 const sauVariableValue_3_COLOR1_RGB[3];
    static u32 const sauVariableValue_4_COLOR1_RGBA[4];
};

struct TObject_particle : public TObject {
    TObject_particle(JStudio::stb::data::TParse_TBlock_object const&,
                                    JStudio::TAdaptor_particle*);
    
    virtual ~TObject_particle();
    virtual void do_paragraph(u32, void const*, u32);
};

struct TAdaptor_sound : public TAdaptor {
    enum TEVariableValue {
        UNK_MINUS1_e = -1,
        UNK_6_e = 6,
        UNK_7_e = 7,
        UNK_8_e = 8,
        UNK_9_e = 9,
        UNK_A_e = 0xA,
    };

    TAdaptor_sound()
        : TAdaptor(mValue, ARRAY_SIZE(mValue))
        , mValue()
    {
    }
    virtual ~TAdaptor_sound() = 0;
    virtual void adaptor_do_SOUND(JStudio::data::TEOperationData, const void*, u32) = 0;
    virtual void adaptor_do_LOCATED(JStudio::data::TEOperationData, const void*, u32) = 0;

    /* 0x10 */ TVariableValue mValue[11];

    static const u32 sauVariableValue_3_POSITION_XYZ[3];
};  // Size: 0x114

struct TObject_sound : public TObject {
    TObject_sound(JStudio::stb::data::TParse_TBlock_object const&,
                                 JStudio::TAdaptor_sound*);
    
    virtual ~TObject_sound();
    virtual void do_paragraph(u32, void const*, u32);
};

};  // namespace JStudio

#endif /* JSTUDIO_OBJECT_H */
