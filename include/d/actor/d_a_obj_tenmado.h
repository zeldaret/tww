#ifndef D_A_OBJ_TENMADO_H
#define D_A_OBJ_TENMADO_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjTenmado {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_swSave() const {}
        void prm_get_swSave2() const {}
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_TENMADO_H */
