#ifndef D_A_OBJ_MMRR_H
#define D_A_OBJ_MMRR_H

#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"

namespace daObjMmrr {
    class Eff_c : public dPa_followEcallBack {
    public:
        virtual void end();
        void remove();
        virtual ~Eff_c() {}
    };  // Size: 0x14

    class Act_c : public fopAc_ac_c {
    public:
        void setup(const cXyz* pos) {
            current.pos = *pos;
            field_0xBF8 = 1;
        }

        static int solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        void init_cc();
        void set_cc_rec_pos();
        void set_cc_trans_pos();
        void set_cull();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        void init_mtx();
        bool chk_light();
        void eff_start();
        void eff_stop();
        void eff_remove();
        bool _execute();
        bool _draw();

        static const char M_arcname[];
        static const dCcD_SrcTri M_tri_src;
        static const dCcD_SrcCps M_cps_src;

    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpMirrorModel;
        /* 0x29C */ J3DModel* mpBeamModel;
        /* 0x2A0 */ mDoExt_btkAnm mMirrorBtkAnm;
        /* 0x2B4 */ mDoExt_btkAnm mBeamBtkAnm;
        /* 0x2C8 */ dCcD_Tri field_0x2C8[5];
        /* 0x958 */ dCcD_Stts field_0x958[5];
        /* 0xA84 */ dCcD_Cps field_0xA84;
        /* 0xBBC */ dCcD_Stts field_0xBBC;
        /* 0xBF8 */ bool field_0xBF8;
        /* 0xBF9 */ bool field_0xBF9;
        /* 0xBFC */ f32 field_0xBFC;
        /* 0xC00 */ f32 field_0xC00;
        /* 0xC04 */ Eff_c field_0xC04;
    };  // Size: 0xC18
};

#endif /* D_A_OBJ_MMRR_H */
