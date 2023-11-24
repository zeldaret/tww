#ifndef D_A_OBJ_VYASI_H
#define D_A_OBJ_VYASI_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "JSystem/J3DGraphAnimator/J3DAnimation.h"

namespace daObjVyasi {
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
        s32 _create();
        BOOL _delete();
        void set_mtx();
        void calc_dif_angle();
        void quaternion_main();
        void leaf_scale_main();
        BOOL _execute();
        BOOL _draw();
    
    public:
        /* 0x0290 */ u8 m0290[0x0294 - 0x0290];
        /* 0x0294 */ s16 m0294[14];
        /* 0x02B0 */ s16 m02B0[14];
        /* 0x02CC */ Quaternion mJointQuat[14];
        /* 0x03AC */ csXyz m03AC[14];
        /* 0x0400 */ cXyz m0400[14];
        /* 0x04A8 */ f32 m04A8;
        /* 0x04AC */ f32 m04AC;
        /* 0x04B0 */ f32 m04B0;
        /* 0x04B4 */ request_of_phase_process_class mPhs;
        /* 0x04BC */ Mtx m04BC;
        /* 0x04EC */ mDoExt_McaMorf* mpMorf;
        /* 0x04F0 */ J3DAnmTransformKey* mpBckData;
        /* 0x04F4 */ cXyz mEkszsPos;
        /* 0x0500 */ s16 mEkszsRotY;
        /* 0x0502 */ u8 m0502[0x0504 - 0x0502];
        /* 0x0504 */ f32 m0504;
        /* 0x0508 */ u8 m0508[0x0524 - 0x0508];
        /* 0x0524 */ s16 m0524[15];
        /* 0x0542 */ u8 m0542[0x0544 - 0x0542];
        /* 0x0544 */ s16 mNormalCounter;
        /* 0x0546 */ u8 m0546[0x0584 - 0x0546];
        /* 0x0584 */ dCcD_Cyl mCyl;
        /* 0x06B4 */ u8 m06B4[0x19C4 - 0x06B4];
        /* 0x19C4 */ int m19C4;
        /* 0x19C8 */ int mState;
        /* 0x19CC */ f32 m19CC;
        /* 0x19D0 */ s16 m19D0;
        /* 0x19D2 */ u8 m19D2[0x19D4 - 0x19D2];
        /* 0x19D4 */ f32 m19D4;
    };
};

#endif /* D_A_OBJ_VYASI_H */
