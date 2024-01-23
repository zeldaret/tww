#ifndef D_A_OBJ_OJTREE_H
#define D_A_OBJ_OJTREE_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_movebg_actor.h"


namespace daObjOjtree {
    class Act_c : public dBgS_MoveBgActor {
    public:
        
        static Mtx M_tmp_mtx;
        static const char M_arcname[];
        
        int CreateHeap();
        int Create();
        s32 Mthd_Create();
        BOOL Delete();
        s32 Mthd_Delete();
        void set_mtx();
        void init_mtx();
        int Execute(Mtx**);
        BOOL Draw();

    public:
        /* Place member variables here */
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ u8 field_0x2d4;
        /* 0x2D5 */ u8 field_0x2d5[0x2d7 - 0x2d5];
    };
};

#endif /* D_A_OBJ_OJTREE_H */
