#ifndef D_A_OBJ_HLIFT_H
#define D_A_OBJ_HLIFT_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjHlift {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Mode_e {
            
        };
    
        void prm_get_dist() const {}
        void prm_get_evId() const {}
        void prm_get_size() const {}
        void prm_get_swSave() const {}
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_demoreq_init(Mode_e);
        void mode_demoreq();
        void set_mtx();
        void init_mtx();
        void rot_set();
        void vib_set();
        void vib_proc();
        void chk_demo_end();
        void se_whole();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_HLIFT_H */
