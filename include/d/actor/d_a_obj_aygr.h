#ifndef D_A_OBJ_AYGR_H
#define D_A_OBJ_AYGR_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_a_obj.h"

class J3DModel;
class dBgW;

namespace daObjAygr {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_MDL_W = 0x01,
            PRM_MDL_S = 0x00,
        };

        u8 prm_get_mdl() const { return daObj::PrmAbstract<Prm_e>(this, PRM_MDL_W, PRM_MDL_S); }

        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        static Mtx M_tmp_mtx;
        static const char M_arcname[];

    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ J3DModel* mpModelH;
        /* 0x2D8 */ dBgW* mpBgWH;
        /* 0x2DC */ Mtx mMtxH;
        /* 0x30C */ bool mHasBgWH;
    };  // Size: 0x310
};

#endif /* D_A_OBJ_AYGR_H */
