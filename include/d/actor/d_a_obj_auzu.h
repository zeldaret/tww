#ifndef D_A_OBJ_AUZU_H
#define D_A_OBJ_AUZU_H

#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class J3DMaterial;

namespace daObjAuzu {
    struct Attr_c {
        /* 0x00 */ f32 mRadiusMult;
        /* 0x04 */ f32 mOuterActivationMult;
        /* 0x08 */ f32 mInnerActivationMult;
        /* 0x0C */ f32 mAnmSpeed;
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
        const Attr_c& attr() const { return M_attr[mType]; }
        bool is_appear() const { return mScaleAnimFactor > 0.999f; }
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
        void to_appear() { mbToAppear = true; }
        void to_disappear() { mbToAppear = false; }
    
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
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ mDoExt_btkAnm mBtkAnm;
        /* 0x2B0 */ s32 mType;
        /* 0x2B4 */ f32 mScaleAnimFactor;
        /* 0x2B8 */ bool mbToAppear;
        /* 0x2B9 */ bool mbIsExist;
        /* 0x2BA */ bool mbBgmStarted;
        /* 0x2BB */ /* 1 byte of alignment padding */
        /* 0x2BC */ fpc_ProcID mKytagPcId;
    };  // Size: 0x2C0
};

#endif /* D_A_OBJ_AUZU_H */
