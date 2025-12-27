#ifndef D_A_OBJ_HAMI3_H
#define D_A_OBJ_HAMI3_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjHami3 {
    class Act_c : public dBgS_MoveBgActor {
    public:
    
        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,
            
            PRM_SWSAVE2_W = 0x08,
            PRM_SWSAVE2_S = 0x08,

            PRM_SOUND_W = 0x01,
            PRM_SOUND_S = 0x10,
        };
        int prm_get_sound() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SOUND_W, PRM_SOUND_S); }
        int prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        int prm_get_swSave2() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE2_W, PRM_SWSAVE2_S); }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void daObjHami3_close_stop();
        void daObjHami3_open_demo_wait();
        void daObjHami3_open_demo();
        void daObjHami3_open_stop();
        void daObjHami3_close_demo_wait();
        void daObjHami3_close_demo();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        static Mtx M_tmp_mtx;
        static const char M_arcname[];
#if VERSION > VERSION_DEMO
        static const char M_evname[];
#endif
    
    public:
        /* 0x2C8 */ s16 field_0x2C8;
        /* 0x2CA */ s16 field_0x2CA;
        /* 0x2CC */ request_of_phase_process_class field_0x2CC;
        /* 0x2D4 */ J3DModel* field_0x2D4;
        /* 0x2D8 */ int field_0x2D8;
        /* 0x2DC */ s16 field_0x2DC;
        /* 0x2DE */ s16 field_0x2DE;
    };  // Size: 0x2E0
};

#endif /* D_A_OBJ_HAMI3_H */
