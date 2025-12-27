#ifndef D_A_OBJ_MSDAN_SUB2_H
#define D_A_OBJ_MSDAN_SUB2_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjMsdanSub2 {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_objNo() const {}
        void prm_get_swSave() const {}
    
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

#endif /* D_A_OBJ_MSDAN_SUB2_H */
