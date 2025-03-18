#ifndef D_A_OBJ_HAMI2_H
#define D_A_OBJ_HAMI2_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjHami2 {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_swSave() const {}
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void daObjHami2_close_stop();
        void daObjHami2_open_demo_wait();
        void daObjHami2_open_demo();
        void daObjHami2_open_stop();
        void daObjHami2_close_demo_wait();
        void daObjHami2_close_demo();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_HAMI2_H */
