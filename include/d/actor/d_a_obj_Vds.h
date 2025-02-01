#ifndef D_A_OBJ_VDS_H
#define D_A_OBJ_VDS_H

#include "f_op/f_op_actor.h"

class J3DAnmTransformKey;

namespace daObjVds {
    static void ds_search_switchCB(void*, void*);

    class Act_c : public fopAc_ac_c {
    public:
        void is_switch() const {}
    
        void SetLoopJointAnimation(J3DAnmTransformKey*, J3DAnmTransformKey*, float, float);
        void PlayLoopJointAnimation();
        void set_first_process();
        void search_switchCB(fopAc_ac_c*);
        void process_off_init();
        void process_off_main();
        void process_on_init();
        void process_on_main();
        void process_init(int);
        void process_main();
        void process_common();
        void create_point_light(int, cXyz*);
        void execute_point_light();
        void delete_point_light();
        void Event_init();
        void Event_exe();
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        s32 _create();
        bool _delete();
        void set_mtx();
        bool _execute();
        bool _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_VDS_H */
