#ifndef D_A_OBJ_MSDAN_SUB2_H
#define D_A_OBJ_MSDAN_SUB2_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjMsdanSub2 {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_objNo() const {}
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prm_get_size() const { return daObj::PrmAbstract(this, PRM_SIZE_W, PRM_SIZE_H); }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        enum Prm_e {
            PRM_SIZE_W = 8,
            PRM_SIZE_H = 0,

            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 8,
        };

        static const char M_arcname[];
    
    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mModel;
        /* 0x2D4 */ s32 field_0x2D4;
        /* 0x2D8 */ f32 field_0x2D8;
        /* 0x2DC */ f32 field_0x2DC;
        /* 0x2E0 */ u8 field_0x2E0[0x2E4 - 0x2E0];
    };  // Size: 0x2E4
};

#endif /* D_A_OBJ_MSDAN_SUB2_H */
