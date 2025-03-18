#ifndef D_A_OBJ_VOLCANO_H
#define D_A_OBJ_VOLCANO_H

#include "d/d_bg_s_movebg_actor.h"

class J3DMaterial;

namespace daObjVolcano {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_swSave() const {}
    
        void StartFire();
        void StopFire();
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void daObjVolcano_fire_demo_wait();
        void daObjVolcano_fire_demo_main();
        void daObjVolcano_fire_main();
        void daObjVolcano_freeze_demo_wait();
        void daObjVolcano_freeze_demo_main();
        void daObjVolcano_freeze_main();
        void daObjVolcano_fail_demo_wait();
        void daObjVolcano_fail_demo_main();
        virtual BOOL Execute(Mtx**);
        void set_material(J3DMaterial*, unsigned char);
        virtual BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_VOLCANO_H */
