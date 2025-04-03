#ifndef D_A_OBJ_SMPLBG_H
#define D_A_OBJ_SMPLBG_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjSmplbg {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void attr() const {}
        void isStop() {}
        void offStop() {}
        void onStop() {}
        void prm_get_type() const {}
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void exec_qtkhd();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* 0x290 */ u8 field_0x290[0x2C8 - 0x290];
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ int field_0x2D4;
        /* 0x2D8 */ u8 field_0x2D8[0x2DC - 0x2D8];
    };  // Size: 0x2DC
};

#endif /* D_A_OBJ_SMPLBG_H */
