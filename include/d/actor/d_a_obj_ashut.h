#ifndef D_A_OBJ_ASHUT_H
#define D_A_OBJ_ASHUT_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjAshut {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Mode_e {
            
        };
    
        void is_switch() const {}
        void prm_get_evId() const {}
        void prm_get_swSave() const {}
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void chk_safe_area() const;
        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        void mode_demoreq_init(Mode_e);
        void mode_demoreq();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_ASHUT_H */
