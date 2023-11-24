#ifndef D_A_OBJ_VOLCANO_H
#define D_A_OBJ_VOLCANO_H

#include "f_op/f_op_actor.h"
#include "JSystem/J3DGraphBase/J3DMaterial.h"

namespace daObjVolcano {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_swSave() const {}
    
        void StartFire();
        void StopFire();
        void CreateHeap();
        s32 Create();
        void Mthd_Create();
        BOOL Delete();
        void Mthd_Delete();
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
        void Execute(float(**)[3][4]);
        void set_material(J3DMaterial*, unsigned char);
        BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_VOLCANO_H */
