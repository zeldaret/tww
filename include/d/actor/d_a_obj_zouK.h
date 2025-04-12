#ifndef D_A_OBJ_ZOUK_H
#define D_A_OBJ_ZOUK_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"

class J3DAnmTransformKey;
class mDoExt_McaMorf;

namespace daObjZouk {
    namespace {
        struct Attr_c {
            /* 0x00 */ f32 v[12];
        };
    }

    class Act_c : public fopAc_ac_c {
    public:
        virtual ~Act_c() {}
        inline s32 param_get_arg0() const { return daObj::PrmAbstract<int>(this, 0x04, 0x00); }
        inline void setEffectMtx(const cXyz*, float);
    
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        void texture_scroll();
        void play_stop_joint_anime();
        BOOL jokai_demo();
        bool _execute();
        bool _draw();
    
    public:
        /* 0x294 */ u32 field_0x294;
        /* 0x298 */ u32 field_0x298;
        /* 0x29C */ request_of_phase_process_class mPhs;
        /* 0x2A4 */ Mtx mBgMtx;
        /* 0x2D4 */ Mtx mMtx;
        /* 0x304 */ J3DAnmTransformKey* M_bck_data;
        /* 0x308 */ mDoExt_McaMorf* M_anm;
        /* 0x30C */ u8 m30C[0x310 - 0x30C];
        /* 0x310 */ dBgS_ObjGndChk mGndChk;
        /* 0x364 */ f32 mGndY;
        /* 0x368 */ s32 mBgMode;
        /* 0x36C */ dBgW* mBgBefore;
        /* 0x370 */ dBgW* mBgAfter;
        /* 0x374 */ dCcD_Stts mStts0;
        /* 0x3B0 */ dCcD_Cyl mCyl0;
        /* 0x4E0 */ dCcD_Stts mStts1;
        /* 0x51C */ dCcD_Cyl mCyl1;
        /* 0x64C */ dCcD_Stts mStts2;
        /* 0x688 */ dCcD_Cyl mCyl2;
        /* 0x7B8 */ u8 m7B8[0x7C0 - 0x7B8];

        static const char M_arcname[6];
    };
};

#endif /* D_A_OBJ_ZOUK_H */
