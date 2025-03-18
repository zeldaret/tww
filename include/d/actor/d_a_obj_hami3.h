#ifndef D_A_OBJ_HAMI3_H
#define D_A_OBJ_HAMI3_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjHami3 {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_sound() const {}
        void prm_get_swSave() const {}
        void prm_get_swSave2() const {}
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void daObjHami3_close_stop();
        void daObjHami3_open_demo_wait();
        void daObjHami3_open_demo();
        void daObjHami3_open_stop();
        void daObjHami3_close_demo_wait();
        void daObjHami3_close_demo();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_HAMI3_H */
