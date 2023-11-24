#ifndef D_A_OBJ_AUZU_H
#define D_A_OBJ_AUZU_H

#include "f_op/f_op_actor.h"
#include "JSystem/J3DGraphBase/J3DMaterial.h"

namespace daObjAuzu {
    class Act_c : public fopAc_ac_c {
    public:
        void attr() const {}
        void is_appear() const {}
        void prm_get_appear() const {}
        void prm_get_linkID() const {}
        void prm_get_swSave() const {}
        void prm_get_type() const {}
        void prm_make_squid() {}
        void to_appear() {}
        void to_disappear() {}
    
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void _create();
        void _delete();
        void is_exist() const;
        void set_mtx();
        void init_mtx();
        void set_state_map();
        void ship_whirl();
        void bgm_start();
        void _execute();
        void set_material(J3DMaterial*, unsigned char);
        void _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_AUZU_H */
