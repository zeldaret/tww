#ifndef D_A_OBJ_MSDAN_SUB_H
#define D_A_OBJ_MSDAN_SUB_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjMsdanSub {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_SIZE_W = 0x1,
            PRM_SIZE_H = 0x10,

            PRM_SWSAVE_W = 0x8,
            PRM_SWSAVE_S = 0x0,

            PRM_OBJNO_W = 0x8,
            PRM_OBJNO_S = 0x8,
        };

        s32 prm_get_objNo() const { return daObj::PrmAbstract(this, PRM_OBJNO_W, PRM_OBJNO_S); }
        s32 prm_get_size() const { return daObj::PrmAbstract(this, PRM_SIZE_W, PRM_SIZE_H); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
        static const char M_arcname[];
        static Mtx M_tmp_mtx;

    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel *mModel;
        /* 0x2D4 */ s32 m2D4;
        /* 0x2D8 */ s32 mCurObjNo;
        /* 0x2DC */ f32 m2DC;
        /* 0x2E0 */ f32 m2E0;
        /* 0x2E4 */ bool m2E4;
    };
};

#endif /* D_A_OBJ_MSDAN_SUB_H */
