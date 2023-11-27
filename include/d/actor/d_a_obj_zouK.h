#ifndef D_A_OBJ_ZOUK_H
#define D_A_OBJ_ZOUK_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"

class J3DAnmTransformKey;
class mDoExt_McaMorf;

namespace daObjZouk {
    class Act_c : public fopAc_ac_c {
    public:
        void param_get_arg0() const {}
        void setEffectMtx(const cXyz*, float) {}
    
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        s32 _create();
        BOOL _delete();
        void set_mtx();
        void texture_scroll();
        void play_stop_joint_anime();
        void jokai_demo();
        BOOL _execute();
        BOOL _draw();
    
    public:
        /* 0x290 */ void* vtbl;
        /* 0x294 */ u8 m294[0x29C - 0x294];
        /* 0x29C */ request_of_phase_process_class mpPhs;
        /* 0x2A4 */ Mtx mZeroMtx;
        /* 0x2D4 */ Mtx mMtx;
        /* 0x304 */ J3DAnmTransformKey* mpKeyData;
        /* 0x308 */ mDoExt_McaMorf* mpMorf;
        /* 0x30C */ u8 m30C[0x310 - 0x30C];
        /* 0x310 */ dBgS_GndChk mGndChk;
        /* 0x364 */ f32 m364;
        /* 0x368 */ u32 m368;
        /* 0x36C */ dBgW* mBgBefore;
        /* 0x370 */ dBgW* mBgAfter;
        /* 0x374 */ dCcD_Stts mStts0;
        /* 0x3B0 */ dCcD_Cyl mCyl0;
        /* 0x4E0 */ dCcD_Stts mStts1;
        /* 0x51C */ dCcD_Cyl mCyl1;
        /* 0x64C */ dCcD_Stts mStts2;
        /* 0x688 */ dCcD_Cyl mStts3;
        /* 0x7B8 */ u8 m7B8[0x7C0 - 0x7B8];
    };
};

#endif /* D_A_OBJ_ZOUK_H */
