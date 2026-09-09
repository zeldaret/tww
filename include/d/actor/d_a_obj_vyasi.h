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
        virtual ~Act_c() {}

        BOOL is_switch() const;

        BOOL SetStopJointAnimation(J3DAnmTransformKey*, f32, f32);
        BOOL PlayStopJointAnimation();
        void set_first_process();
        void set_collision();
        BOOL process_none_init();
        void process_none_main();
        BOOL process_sag_init();
        void process_sag_main();
        BOOL process_sagWind_init();
        void process_sagWind_main();
        BOOL process_toNormal_init();
        void process_toNormal_main();
        BOOL process_normal_init();
        void process_normal_main();
        BOOL process_init(int);
        void process_main();
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        void calc_dif_angle();
        void quaternion_main();
        void leaf_scale_main();
        bool _execute();
        bool _draw();

        static const char M_arcname[6];

    public:
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
        /* 0x04F0 */ J3DAnmTransformKey* M_bck_data;
        /* 0x04F4 */ cXyz mEkszsPos;
        /* 0x0500 */ s16 mEkszsRotY;
        /* 0x0502 */ u8 m0502[0x0504 - 0x0502];
        /* 0x0504 */ f32 m0504;
        /* 0x0508 */ s16 m0508[14];
        /* 0x0524 */ s16 m0524[14];
        /* 0x0540 */ u8 m0540[0x0544 - 0x0540];
        /* 0x0544 */ s16 mNormalCounter;
        /* 0x0546 */ u8 m0546[0x0548 - 0x0546];
        /* 0x0548 */ dCcD_Stts mStts;
        /* 0x0584 */ dCcD_Cyl mCyl;
        /* 0x06B4 */ dCcD_Stts mCpsStts[5];
        /* 0x07E0 */ dCcD_Cps mCps[5];
        /* 0x0DF8 */ cM3dGCpsS mCpsData[5];
        /* 0x0E84 */ dCcD_Stts mSphStts[8];
        /* 0x1064 */ dCcD_Sph mSph[8];
        /* 0x19C4 */ int m19C4;
        /* 0x19C8 */ int mState;
        /* 0x19CC */ f32 m19CC;
        /* 0x19D0 */ s16 m19D0;
        /* 0x19D2 */ u8 m19D2[0x19D4 - 0x19D2];
        /* 0x19D4 */ f32 m19D4;
    };  // Size: 0x19D8
};

#endif /* D_A_OBJ_VYASI_H */
