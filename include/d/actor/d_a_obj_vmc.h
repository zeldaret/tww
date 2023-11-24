#ifndef D_A_OBJ_VMC_H
#define D_A_OBJ_VMC_H

#include "f_op/f_op_actor.h"

namespace daObjVmc {
    class Act_c : public fopAc_ac_c {
    public:
        void daObjVmc_ChangeGrow() {}
        void prm_get_swSave() const {}
    
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void CreateInit();
        s32 _create();
        BOOL _delete();
        void set_mtx();
        void init_mtx();
        void daObjVmc_base_main();
        void daObjVmc_tree_demo_wait();
        void daObjVmc_tree_demo_main();
        void daObjVmc_tree_main();
        BOOL _execute();
        BOOL _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_VMC_H */
