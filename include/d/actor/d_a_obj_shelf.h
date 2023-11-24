#ifndef D_A_OBJ_SHELF_H
#define D_A_OBJ_SHELF_H

#include "f_op/f_op_actor.h"

namespace daObjShelf {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_groundma() const {}
    
        void CreateHeap();
        void Create();
        void Mthd_Create();
        void Delete();
        void Mthd_Delete();
        void hold_event() const;
        void mode_wait_init();
        void mode_wait();
        void mode_vib_init();
        void mode_vib();
        void mode_rot_init();
        void mode_rot_init2();
        void mode_rot_init3();
        void mode_rot();
        void mode_fell_init();
        void mode_fell();
        void set_mtx();
        void init_mtx();
        void Execute(float(**)[3][4]);
        void Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_SHELF_H */
