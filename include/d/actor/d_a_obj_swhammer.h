#ifndef D_A_OBJ_SWHAMMER_H
#define D_A_OBJ_SWHAMMER_H

#include "d/d_a_obj.h"
#include "d/d_bg_s_movebg_actor.h"
#include "c/c_damagereaction.h"

class J3DNode;

namespace daObjSwhammer {
    class Act_c : public dBgS_MoveBgActor {
    public:
        BOOL is_switch() const {
            return fopAcM_isSwitch(const_cast<Act_c*>(this), prm_get_swSave());
        }
        void off_switch2() const {}
        void on_switch() const {}
        s32 prm_get_swSave() const { return -1; }
        void prm_get_swSave2() const {}
    
        Act_c();
        int CreateHeap();
        int Create();
        s32 _create();
        BOOL Delete();
        bool _delete();
        void set_mtx();
        void init_mtx();
        void set_damage();
        void vib_start(short, float);
        void vib_proc();
        void crush_start();
        void crush_proc();
        void eff_crush();
        void calc_top_pos();
        static BOOL jnodeCB(J3DNode*, int);
        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        BOOL Execute(Mtx**);
        BOOL Draw();

        static int M_damage;
        static short M_damage_dir;
        static Mtx M_tmp_mtx;
    
        static const char M_arcname[7];
        static const dCcD_SrcCyl M_cyl_src_co;
        static const dCcD_SrcCyl M_cyl_src_tg;

    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ dCcD_Cyl mCylCo;
        /* 0x404 */ dCcD_Stts mSttsCo;
        /* 0x440 */ dCcD_Cyl mCylTg;
        /* 0x570 */ dCcD_Stts mSttsTg;
        /* 0x5AC */ int mMode;
        /* 0x5B0 */ short m5B0;
        /* 0x5B2 */ u8 m5B2;
        /* 0x5B4 */ float m5B4;
        /* 0x5B8 */ float m5B8;
        /* 0x5BC */ float m5BC;
        /* 0x5C0 */ float m5C0;
        /* 0x5C4 */ float m5C4;
        /* 0x5C8 */ float m5C8;
        /* 0x5CC */ float m5CC;
        /* 0x5D0 */ float m5D0;
        /* 0x5D4 */ float m5D4;
        /* 0x5D8 */ float mTopPos;
        /* 0x5DC */ dPa_followEcallBack m5DC; // TODO verify
        /* 0x5F0 */ u8 m5F0[0x5FC - 0x5F0];
        /* 0x5FC */ bool m5FC;

    }; /* Size: 0x600 */

    // TODO STATIC_ASSERT(sizeof(Act_c) == 0x600);
};

#endif /* D_A_OBJ_SWHAMMER_H */
