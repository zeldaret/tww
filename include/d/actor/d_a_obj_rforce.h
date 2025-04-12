#ifndef D_A_OBJ_RFORCE_H
#define D_A_OBJ_RFORCE_H

#include "d/d_bg_s.h"
#include "f_op/f_op_actor.h"

namespace daObjRforce {
    class Act_c : public fopAc_ac_c {
    public:
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        bool _execute();
        bool _draw();

        virtual ~Act_c() {};
    
    public:
        static const char M_arcname[8];
        
        /* 0x294 */ request_of_phase_process_class mPhs;
        /* 0x29C */ J3DModel* mpModel;
        /* 0x2A0 */ dBgW* mpBgw;
        /* 0x2A4 */ Mtx mtx;
    };
};

#endif /* D_A_OBJ_RFORCE_H */
