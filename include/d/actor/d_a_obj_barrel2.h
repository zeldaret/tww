#ifndef D_A_OBJ_BARREL2_H
#define D_A_OBJ_BARREL2_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/actor/d_a_obj_buoyflag.h"

namespace daObjBarrel2 {
    enum Type_e {
        Type_01_e = 0x1,
    };

    class Act_c : public fopAc_ac_c {
    public:
    
        void attr() const {}
        u8 chk_item_give() const {
            return unk_476;
        }
        void delete_req() {}
        void exit_req() {}
        void get_item_id() {}
        static fpc_ProcID make_coming(cXyz* pos, int roomNo, Type_e type, int droppedItem, bool hasFlag, short angleY, daObjBuoyflag::Texture_e arg6) {
            csXyz angle(0, angleY, 0);
            return fopAcM_create(PROC_Obj_Barrel2, make_prm(type, droppedItem, hasFlag, hasFlag, arg6), pos, roomNo, &angle);
        }
        static u32 make_prm(Type_e arg0, int droppedItem, bool hasFlag, bool flagType, daObjBuoyflag::Texture_e arg4) {
            s32 item = (droppedItem & 0x3F);
            s32 tmp = hasFlag ? 1 : 0;
            s32 a6 = arg4;
            return (item | (0x7F << 16)) | (arg0 << 24) | (tmp << 8) | ((hasFlag ? 0 : 1) << 10) | (a6 << 28);
        }
        void prm_get_buoy() const {}
        void prm_get_coming() const {}
        void prm_get_itemNo() const {}
        void prm_get_itemSave() const {}
        void prm_get_texture() const {}
        void prm_get_type() const {}
    
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        cPhs_State _create();
        bool _delete();
        void tg_hitCB(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
        void co_hitCB(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
        void cull_set_draw();
        void cull_set_move();
        void demo_mode_chk() const;
        void mode_afl_init();
        void mode_afl();
        void mode_exit_v_init();
        void mode_exit_v();
        void mode_exit_h_init();
        void mode_exit_h();
        void mode_exit_mine_init();
        void mode_exit_mine();
        void mode_explode_init();
        void mode_explode();
        void mode_demo_break0_init();
        void mode_demo_break0();
        void mode_demo_break1_init();
        void mode_demo_break1();
        void mode_demo_explode0_init();
        void mode_demo_explode0();
        void mode_demo_explode1_init();
        void mode_demo_explode1();
        void mode_proc_call();
        void set_pos_y();
        void set_mtx();
        void init_mtx();
        void eff_break();
        void eff_explode();
        void set_item_position();
        void item_drop_init(float);
        void item_drop();
        void item_delete();
        void item_give();
        void item_connect_check();
        void buoy_jump(float);
        void set_water_pos();
        void afl_sway();
        void mine_chk_range_flash();
        void mine_chk_range_explode();
        void mine_chk_range_damage();
        void execute_sub();
        bool _execute();
        bool _draw();
    
    public:
        /* 0x290 */ char unk290[0x1C8];
        /* 0x458 */ fpc_ProcID unk_458;
        /* 0x45C */ char unk45C[0x18];
        /* 0x474 */ u8 unk_474;
        /* 0x475 */ char unk475[0x1];
        /* 0x476 */ u8 unk_476;
    };
    
    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_BARREL2_H */
