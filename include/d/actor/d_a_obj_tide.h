#ifndef D_A_OBJ_TIDE_H
#define D_A_OBJ_TIDE_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjTide {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_swSave() const {}
        void prm_get_type() const {}
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void move_to_aim(float, bool);
        void chk_demo_rescue() const;
        void gmtw_demo_up_start() const;
        void mode_norm_init();
        void mode_norm();
        void mode_gmtw_pre_init();
        void mode_gmtw_pre();
        void mode_gmtw_init();
        void mode_gmtw();
        void mode_gmtw_demo_init();
        void mode_gmtw_demo();
        void se_init_gmtw();
        void se_set_gmtw();
        void se_start_gopo();
        void se_start_out();
        void se_start_up();
        void se_stop_gopo();
        void se_stop_out();
        void se_stop_up();
        void se_pos_up();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_TIDE_H */
