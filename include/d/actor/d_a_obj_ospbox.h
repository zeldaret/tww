#ifndef D_A_OBJ_OSPBOX_H
#define D_A_OBJ_OSPBOX_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjOspbox {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_itemNo() const {}
        void prm_get_spec() const {}
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void make_item();
        void eff_break();
        void sound_break();
        void set_ground();
        void init_ground();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_OSPBOX_H */
