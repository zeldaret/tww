#ifndef D_A_OBJ_OSPBOX_H
#define D_A_OBJ_OSPBOX_H

#include "d/d_bg_s_movebg_actor.h"
#include "include/d/d_bg_s_gnd_chk.h"

namespace daObjOspbox {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_ITEMNO_W = 0x06,
            PRM_ITEMNO_S = 0x00,
            PRM_SPEC_W = 0x03,
            PRM_SPEC_S = 0x08,
        };

        int prm_get_itemNo() const {
            return daObj::PrmAbstract(this, PRM_ITEMNO_W, PRM_ITEMNO_S);
        }
        int prm_get_spec() const {
            return daObj::PrmAbstract(this, PRM_SPEC_W, PRM_SPEC_S);
        }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void make_item();
        void eff_break();
        void sound_break();
        void set_ground();
        void init_ground();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        static const char M_arcname[];
        static const dCcD_SrcCyl M_cyl_src;

    private:
        static Mtx M_tmp_mtx;
    
    public:
        /* 0x2C8 */ request_of_phase_process_class mPhase;
        /* 0x2D0 */ J3DModel *mpModel;
        /* 0x2D4 */ dCcD_Stts mStts;
        /* 0x310 */ dCcD_Cyl mCyl;
        /* 0x440 */ dBgS_ObjGndChk mObjGndChk;
        /* 0x494 */ f32 m494;
        /* 0x498 */ s16 m498;
        /* 0x49a */ u8 m49A;
    };
};

#endif /* D_A_OBJ_OSPBOX_H */
