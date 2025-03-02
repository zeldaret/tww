#ifndef D_A_OBJ_SHELF_H
#define D_A_OBJ_SHELF_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_a_obj.h"

namespace daObjShelf {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_GROUNDMA_W = 0x01,
            PRM_GROUNDMA_S = 0x00,
        };

        bool prm_get_groundma() const { return daObj::PrmAbstract<Prm_e>(this, PRM_GROUNDMA_W, PRM_GROUNDMA_S); }
    
        int CreateHeap();
        int Create();
        s32 Mthd_Create();
        BOOL Delete();
        int Mthd_Delete();
        void hold_event() const;
        void mode_wait_init();
        void mode_wait();
        void mode_vib_init();
        void mode_vib();
        void mode_rot_init();
        void mode_rot_init2();
        void mode_rot_init3();
        void mode_rot();
        void mode_fell_init();
        void mode_fell();
        void set_mtx();
        void init_mtx();
        BOOL Execute(Mtx**);
        BOOL Draw();
    
    public:
        static const char M_arcname[6];

        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel * mpModel;
        /* 0x2D4 */ int mMode;
        /* 0x2D8 */ float mRotSpeed;
        /* 0x2DC */ short mTargetAngle;
        /* 0x2DE */ short mTimer;
        /* 0x2E0 */ short mVibY;
        /* 0x2E2 */ short mVibX;
        /* 0x2E4 */ short mVibZ;
        /* 0x2E6 */ s8 mCurBounce;
        /* 0x2E7 */ bool m2e7;
    };
};

#endif /* D_A_OBJ_SHELF_H */
