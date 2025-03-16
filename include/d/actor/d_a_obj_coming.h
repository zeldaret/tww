#ifndef D_A_OBJ_COMING_H
#define D_A_OBJ_COMING_H

#include "f_op/f_op_actor.h"

namespace daObjComing {
    struct PrmBarrel2_c {
        
    };
    
    class Act_c;
    
    struct Ctrl_c {
        void init(const daObjComing::Act_c*);
        void init_timer(const daObjComing::Act_c*);
        void set_wait_timer(const daObjComing::Act_c*);
        void set_retry_timer(const daObjComing::Act_c*);
        void set_appear_timer(const daObjComing::Act_c*);
    };
    
    class Act_c : public fopAc_ac_c {
    public:
        enum Ptn_e {
            
        };
        
        struct MakeTmp_c {
            
        };
    
        void prm_get_always() const {}
        void prm_get_makeNum() const {}
        void prm_get_range() const {}
        void prm_get_swSave() const {}
        void prm_get_tblNum() const {}
        void prm_get_type() const {}
        void prm_get_waitTime() const; // weak but not inlined?
    
        void chk_switch();
        s32 _create();
        bool _delete();
        void get_aqua_y(const cXyz*);
        void chk_ship_range(const fopAc_ac_c*) const;
        void chk_ship_spd(const fopAc_ac_c*) const;
        void get_make_pos(const fopAc_ac_c*, cXyz*) const;
        void chk_make_pos_gnd(const MakeTmp_c*) const;
        void chk_make_pos_wall(const MakeTmp_c*) const;
        void chk_make_pos_act(void*, void*);
        void chk_make_pos(const MakeTmp_c*) const;
        void barrel2_get_ptn() const;
        void barrel2_get_type(Ptn_e);
        void barrel2_get_item(Ptn_e);
        void barrel2_get_buoy(Ptn_e);
        void barrel2_get_param(PrmBarrel2_c*);
        void mode_barrel2_wait(Ctrl_c*);
        void mode_barrel2_appear(Ctrl_c*);
        void mode_barrel2_leave(Ctrl_c*);
        bool _execute();
        bool _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_COMING_H */
