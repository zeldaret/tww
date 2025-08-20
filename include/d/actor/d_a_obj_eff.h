#ifndef D_A_OBJ_EFF_H
#define D_A_OBJ_EFF_H

#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_particle.h"
#include "d/d_procname.h"

namespace daObjEff {
    class Act_c : public fopAc_ac_c {
    public:
        typedef BOOL (Act_c::*Proc)();
        typedef void (Act_c::*voidProc)();
        typedef bool (Act_c::*HeapProc)();

        enum Prm_e {
            PRM_TYPE_W = 8,
            PRM_TYPE_S = 0,
        };

        static void make_barrel_smoke(cXyz* pos) { fopAcM_create(PROC_Obj_Eff, 0, pos); }
        static void make_land_smoke(cXyz*, float) {}
        static void make_pinecone_smoke(cXyz* pos) { fopAcM_create(PROC_Obj_Eff, 4, pos); }
        static void make_skull_smoke(cXyz* pos) { fopAcM_create(PROC_Obj_Eff, 2, pos); }
        static void make_stool_smoke(cXyz* pos) { fopAcM_create(PROC_Obj_Eff, 1, pos); }
        static void make_woodBox_smoke(cXyz*) {}
        int prm_get_type() const {
            return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S);
        }
    
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap_barrel_smoke();
        bool create_heap_stool_smoke();
        bool create_heap_skull_smoke();
        bool create_heap_land_smoke();
        bool create_heap_pinecone_smoke();
        bool create_heap_woodBox_smoke();
        bool create_heap();
        BOOL eff_set_barrel_smoke();
        BOOL eff_set_stool_smoke();
        BOOL eff_set_skull_smoke();
        BOOL eff_set_land_smoke();
        BOOL eff_set_pinecone_smoke();
        BOOL eff_set_woodBox_smoke();
        BOOL eff_set();
        cPhs_State _create();
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
        /* 0x290 */ int mProcIndex;
        /* 0x294 */ dPa_followEcallBack* mParticleCallback;
    };

    class BarrelSmokeCB : public dPa_smokeEcallBack {
    public:
        BarrelSmokeCB();
        void execute(JPABaseEmitter*);
    public:
        /* 0x20 */ int field_0x20;
        /* 0x24 */ static const GXColor original_color;
    };

    class StoolSmokeCB : public dPa_smokeEcallBack {
    public:
        StoolSmokeCB();
        void execute(JPABaseEmitter*);
    public:
        /* 0x20 */ int field_0x20;
        /* 0x24 */ static const GXColor original_color;
    };

    class SkullSmokeCB : public dPa_smokeEcallBack {
    public:
        SkullSmokeCB();
        void execute(JPABaseEmitter*);
    public:
        /* 0x20 */ int field_0x20;
        /* 0x24 */ static const GXColor original_color;
    };

    class LandSmokeCB : public dPa_smokeEcallBack {
    public:
        LandSmokeCB();
    };

    class PineconeSmokeCB : public dPa_smokeEcallBack {
    public:
        PineconeSmokeCB();
        void execute(JPABaseEmitter*);
    public:
        /* 0x20 */ int field_0x20;
        /* 0x24 */ static const GXColor original_color;
    };

    class WoodBoxSmokeCB : public dPa_smokeEcallBack {
    public:
        WoodBoxSmokeCB();
        void execute(JPABaseEmitter*);
    public:
        /* 0x20 */ int field_0x20;
        /* 0x24 */ static const GXColor original_color;
    };
};

#endif /* D_A_OBJ_EFF_H */
