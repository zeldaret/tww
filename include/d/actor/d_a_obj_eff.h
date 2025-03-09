#ifndef D_A_OBJ_EFF_H
#define D_A_OBJ_EFF_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_particle.h"
#include "d/d_procname.h"

namespace daObjEff {
    class Act_c : public fopAc_ac_c {
    public:
        static void make_barrel_smoke(cXyz* pos) { fopAcM_create(PROC_Obj_Eff, NULL, pos); }
        void make_land_smoke(cXyz*, float) {}
        void make_pinecone_smoke(cXyz*) {}
        void make_skull_smoke(cXyz*) {}
        void make_stool_smoke(cXyz*) {}
        void make_woodBox_smoke(cXyz*) {}
        void prm_get_type() const {}
    
        void solidHeapCB(fopAc_ac_c*);
        void create_heap_barrel_smoke();
        void create_heap_stool_smoke();
        void create_heap_skull_smoke();
        void create_heap_land_smoke();
        void create_heap_pinecone_smoke();
        void create_heap_woodBox_smoke();
        void create_heap();
        void eff_set_barrel_smoke();
        void eff_set_stool_smoke();
        void eff_set_skull_smoke();
        void eff_set_land_smoke();
        void eff_set_pinecone_smoke();
        void eff_set_woodBox_smoke();
        void eff_set();
        s32 _create();
        void remove_barrel_smoke();
        void remove_stool_smoke();
        void remove_skull_smoke();
        void remove_land_smoke();
        void remove_pinecone_smoke();
        void remove_woodBox_smoke();
        void remove();
        bool _delete();
        void die_barrel_smoke();
        void die_stool_smoke();
        void die_skull_smoke();
        void die_land_smoke();
        void die_pinecone_smoke();
        void die_woodBox_smoke();
        void die();
        bool _execute();
    
    public:
        /* Place member variables here */
    };

    class BarrelSmokeCB : public dPa_smokeEcallBack {
    public:
        BarrelSmokeCB();
        void execute(JPABaseEmitter*);
    };

    class StoolSmokeCB : public dPa_smokeEcallBack {
    public:
        StoolSmokeCB();
        void execute(JPABaseEmitter*);
    };

    class SkullSmokeCB : public dPa_smokeEcallBack {
    public:
        SkullSmokeCB();
        void execute(JPABaseEmitter*);
    };

    class LandSmokeCB : public dPa_smokeEcallBack {
    public:
        LandSmokeCB();
    };

    class PineconeSmokeCB : public dPa_smokeEcallBack {
    public:
        PineconeSmokeCB();
        void execute(JPABaseEmitter*);
    };

    class WoodBoxSmokeCB : public dPa_smokeEcallBack {
    public:
        WoodBoxSmokeCB();
        void execute(JPABaseEmitter*);
    };
};

#endif /* D_A_OBJ_EFF_H */
