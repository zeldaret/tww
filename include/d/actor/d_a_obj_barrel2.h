#ifndef D_A_OBJ_BARREL2_H
#define D_A_OBJ_BARREL2_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/actor/d_a_obj_buoyflag.h"
#include "d/d_a_obj.h"

class mDoExt_brkAnm;
class daRaceItem_c;

namespace daObjBarrel2 {
    enum Type_e {
        Type_01_e = 0x1,
    };

    struct Attr_c {
        /* 0x00 */ u16 m00;
        /* 0x02 */ u16 m02;
        /* 0x04 */ u32 m04;
        /* 0x08 */ f32 m08;
        /* 0x0C */ f32 m0C;
        /* 0x10 */ f32 m10;
        /* 0x14 */ f32 m14;
        /* 0x18 */ f32 m18;
        /* 0x1C */ f32 m1C;
        /* 0x20 */ f32 m20;
        /* 0x24 */ f32 m24;
        /* 0x28 */ f32 m28;
        /* 0x2C */ f32 m2C;
        /* 0x30 */ f32 m30;
        /* 0x34 */ f32 m34;
        /* 0x38 */ f32 m38;
        /* 0x3C */ f32 m3C;
        /* 0x40 */ f32 m40;
        /* 0x44 */ f32 m44;
        /* 0x48 */ f32 m48;
        /* 0x4C */ f32 m4C;
        /* 0x50 */ f32 m50;
        /* 0x54 */ f32 m54;
        /* 0x58 */ s16 m58;
        /* 0x5C */ f32 m5C;
        /* 0x60 */ f32 m60;
        /* 0x64 */ f32 m64;
        /* 0x68 */ f32 m68;
        /* 0x6C */ f32 m6C;
        /* 0x70 */ f32 m70;
    }; // size = 0x74

    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_ITEM_SAVE_W = 7,
            PRM_ITEM_SAVE_S = 0x10,

            PRM_ITEM_NO_W = 6,
            PRM_ITEM_NO_S = 0,

            PRM_BUOY_W = 1,
            PRM_BUOY_S = 8,

            PRM_TYPE_W = 2,
            PRM_TYPE_S = 0x18,

            PRM_TEXTURE_W = 1,
            PRM_TEXTURE_S = 10,

            PRM_COMING_W = 1,
            PRM_COMING_S = 0x1C,
        };
        
        const Attr_c* attr() const { return &M_attr[m410]; }
        u8 chk_item_give() const { return m476; }
        void delete_req() {}
        void exit_req() {}
        void get_item_id() {}
        static fpc_ProcID make_coming(cXyz* pos, int roomNo, Type_e type, int droppedItem, bool hasFlag, short angleY, daObjBuoyflag::Texture_e arg6) {
            csXyz angle(0, angleY, 0);
            return fopAcM_create(PROC_Obj_Barrel2, make_prm(type, droppedItem, hasFlag, false, arg6), pos, roomNo, &angle);
        }
        static u32 make_prm(Type_e arg0, int droppedItem, bool hasFlag, bool flagType, daObjBuoyflag::Texture_e arg4) {
            s32 item = (droppedItem & 0x3F);
            s32 tmp = hasFlag ? 1 : 0;
            s32 a6 = arg4;
            return (item | (0x7F << 16)) | (arg0 << 24) | (tmp << 8) | ((flagType ? 1 : 0) << 10) | (a6 << 28);
        }
        s32 prm_get_buoy() const {
            return daObj::PrmAbstract(this, PRM_BUOY_W, PRM_BUOY_S);
        }
        bool prm_get_coming() const {
            return daObj::PrmAbstract(this, PRM_COMING_W, PRM_COMING_S);
        }
        s32 prm_get_itemNo() const {
            return daObj::PrmAbstract(this, PRM_ITEM_NO_W, PRM_ITEM_NO_S);
        }
        s32 prm_get_itemSave() const {
            return daObj::PrmAbstract(this, PRM_ITEM_SAVE_W, PRM_ITEM_SAVE_S);
        }
        daObjBuoyflag::Texture_e prm_get_texture() const {
            return daObjBuoyflag::Texture_e(daObj::PrmAbstract(this, PRM_TEXTURE_W, PRM_TEXTURE_S));
        }
        s32 prm_get_type() const {
            return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S);
        }
    
        static int solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        static void tg_hitCB(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
        static void co_hitCB(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
        void cull_set_draw();
        void cull_set_move();
        bool demo_mode_chk() const;
        void mode_afl_init();
        bool mode_afl();
        void mode_exit_v_init();
        bool mode_exit_v();
        void mode_exit_h_init();
        bool mode_exit_h();
        void mode_exit_mine_init();
        bool mode_exit_mine();
        void mode_explode_init();
        bool mode_explode();
        void mode_demo_break0_init();
        bool mode_demo_break0();
        void mode_demo_break1_init();
        bool mode_demo_break1();
        void mode_demo_explode0_init();
        bool mode_demo_explode0();
        void mode_demo_explode1_init();
        bool mode_demo_explode1();
        bool mode_proc_call();
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
        bool mine_chk_range_flash();
        bool mine_chk_range_explode();
        bool mine_chk_range_damage();
        void execute_sub();
        bool _execute();
        bool _draw();

        static const char M_arcname[];
        static const char M_evname_brk[];
        static const Attr_c M_attr[4];
        static const dCcD_SrcCyl M_cyl_src;
        static daRaceItem_c* M_tmp_item_actor;
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhase;
        /* 0x298 */ J3DModel* m298;
        /* 0x29C */ mDoExt_brkAnm* m29C;
        /* 0x2A0 */ dCcD_Stts mStts;
        /* 0x2DC */ dCcD_Cyl mCyl;
        /* 0x40C */ s32 m40C;
        /* 0x410 */ int m410;
        /* 0x414 */ f32 m414;
        /* 0x418 */ f32 m418;
        /* 0x41C */ f32 m41C;
        /* 0x420 */ cXyz m420;
        /* 0x42C */ f32 m42C;
        /* 0x430 */ f32 m430;
        /* 0x434 */ f32 m434;
        /* 0x438 */ f32 m438;
        /* 0x43C */ s16 m43C;
        /* 0x440 */ f32 m440;
        /* 0x444 */ f32 m444;
        /* 0x448 */ f32 m448;
        /* 0x44C */ f32 m44C;
        /* 0x450 */ f32 m450;
        /* 0x458 */ f32 m454;
        /* 0x458 */ fpc_ProcID m458;
        /* 0x45C */ f32 m45C;
        /* 0x460 */ fpc_ProcID m460;
        /* 0x464 */ s32 m464;
        /* 0x468 */ u8 m468;
        /* 0x46A */ s16 m46A;
        /* 0x46C */ u8 m46C;
        /* 0x46D */ u8 m46D;
        /* 0x470 */ s32 m470;
        /* 0x474 */ u8 m474;
        /* 0x475 */ u8 m475;
        /* 0x476 */ u8 m476;
        /* 0x478 */ Mtx m478;
    }; // size = 0x4A8
    
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
