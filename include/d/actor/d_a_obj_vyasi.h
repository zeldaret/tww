#ifndef D_A_OBJ_VYASI_H
#define D_A_OBJ_VYASI_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"

class J3DAnmTransformKey;
class mDoExt_McaMorf;
class J3DNode;

namespace daObjVyasi {
    static BOOL JointNodeCallBack(J3DNode*, int);

    class Act_c : public fopAc_ac_c {
    public:
        void is_switch() const {}

        void SetStopJointAnimation(J3DAnmTransformKey*, float, float);
        void PlayStopJointAnimation();
        void set_first_process();
        void set_collision();
        void process_none_init();
        void process_none_main();
        void process_sag_init();
        void process_sag_main();
        void process_sagWind_init();
        void process_sagWind_main();
        void process_toNormal_init();
        void process_toNormal_main();
        void process_normal_init();
        void process_normal_main();
        void process_init(int);
        void process_main();
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        void calc_dif_angle();
        void quaternion_main();
        void leaf_scale_main();
        bool _execute();
        bool _draw();

    public:
        /* 0x0290 */ u32 field_0x290;
        /* 0x0294 */ s16 field_0x294[14];
        /* 0x02B0 */ s16 field_0x2B0[14];
        /* 0x02CC */ Quaternion mJointQuat[14];
        /* 0x03AC */ csXyz field_0x3AC[14];
        /* 0x0400 */ cXyz field_0x400[14];
        /* 0x04A8 */ f32 field_0x4A8;
        /* 0x04AC */ f32 field_0x4AC;
        /* 0x04B0 */ f32 field_0x4B0;
        /* 0x04B4 */ request_of_phase_process_class mPhs;
        /* 0x04BC */ Mtx field_0x4BC;
        /* 0x04EC */ mDoExt_McaMorf* mpMorf;
        /* 0x04F0 */ J3DAnmTransformKey* mpBckData;
        /* 0x04F4 */ cXyz mEkszsPos;
        /* 0x0500 */ s16 mEkszsRotY;
        /* 0x0502 */ u8 pad_0x502[0x0504 - 0x0502];
        /* 0x0504 */ f32 field_0x504;
        /* 0x0508 */ s16 field_0x508[14];
        /* 0x0524 */ s16 field_0x524[14];
        /* 0x0540 */ u8 pad_0x540[0x0544 - 0x0540];
        /* 0x0544 */ s16 mNormalCounter;
        /* 0x0546 */ u8 pad_0x546[0x0548 - 0x0546];
        /* 0x0548 */ dCcD_Stts field_0x548;
        /* 0x0584 */ dCcD_Cyl mCyl;
        /* 0x06B4 */ dCcD_Stts field_0x6B4[5];
        /* 0x07E0 */ dCcD_Cps field_0x7E0[5];
        /* 0x0DF8 */ cM3dGCpsS field_0xDF8[5];
        /* 0x0E84 */ dCcD_Stts field_0xE84[8];
        /* 0x1064 */ dCcD_Sph field_0x1064[8];
        /* 0x19C4 */ int field_0x19C4;
        /* 0x19C8 */ int mState;
        /* 0x19CC */ f32 field_0x19CC;
        /* 0x19D0 */ s16 field_0x19D0;
        /* 0x19D2 */ u8 pad_0x19D2[0x19D4 - 0x19D2];
        /* 0x19D4 */ f32 field_0x19D4;
    }; // Size: 0x19D8
};

#endif /* D_A_OBJ_VYASI_H */
