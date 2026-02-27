#ifndef D_A_OBJ_AUZU_H
#define D_A_OBJ_AUZU_H

#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class J3DMaterial;

namespace daObjAuzu {
    struct Attr_c {
        f32 m00;
        f32 m04;
        f32 m08;
        f32 m0C;
    };
    
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_APPEAR_W = 0x1,
            PRM_APPEAR_S = 0x10,

            PRM_LINK_ID_W = 0x8,
            PRM_LINK_ID_S = 0x8,
            
            PRM_SWSAVE_W = 0x8,
            PRM_SWSAVE_S = 0x0,

            PRM_TYPE_W = 0x4,
            PRM_TYPE_S = 0x14
        };
    public:
        const Attr_c& attr() const { return M_attr[field_0x2B0]; }
        bool is_appear() const { return field_0x2B4 > 0.999f; }
        s32 prm_get_appear() const { return daObj::PrmAbstract(this, PRM_APPEAR_W, PRM_APPEAR_S); }
        s32 prm_get_linkID() const { return daObj::PrmAbstract(this, PRM_LINK_ID_W, PRM_LINK_ID_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        static s32 prm_make_squid() { 
            return 
             0x1 << 20 | // type
             0x1 << 16 | // appear  
            0x00 <<  8 | // linkID
            0xFF <<  0;  // swSave 
        }
        void to_appear() { field_0x2B8 = true; }
        void to_disappear() { field_0x2B8 = false; }
    
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        bool is_exist() const;
        void set_mtx();
        void init_mtx();
        void set_state_map();
        void ship_whirl();
        void bgm_start();
        bool _execute();
        bool _draw();
        static BOOL solidHeapCB(fopAc_ac_c*);            
        static void set_material(J3DMaterial*, u8);
        static const char M_arcname[];
        static const Attr_c M_attr[2];
    public:
        /* 0x290 */ request_of_phase_process_class field_0x290;
        /* 0x298 */ J3DModel* field_0x298;
        /* 0x29C */ mDoExt_btkAnm field_0x29C;
        /* 0x2B0 */ s32 field_0x2B0;
        /* 0x2B4 */ f32 field_0x2B4;
        /* 0x2B8 */ u8 field_0x2B8;
        /* 0x2B9 */ u8 field_0x2B9;
        /* 0x2BA */ u8 field_0x2BA;
        /* 0x2BB */ u8 field_0x2BB[0x2BC - 0x2BB];
        /* 0x2BC */ fpc_ProcID field_0x2BC;
    };  // Size: 0x2C0
};

#endif /* D_A_OBJ_AUZU_H */
