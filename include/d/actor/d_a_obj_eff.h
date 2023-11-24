#ifndef D_A_OBJ_EFF_H
#define D_A_OBJ_EFF_H

#include "f_op/f_op_actor.h"

namespace daObjEff {
    class Act_c : public fopAc_ac_c {
    public:
        void make_barrel_smoke(cXyz*) {}
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
        BOOL _delete();
        void die_barrel_smoke();
        void die_stool_smoke();
        void die_skull_smoke();
        void die_land_smoke();
        void die_pinecone_smoke();
        void die_woodBox_smoke();
        void die();
        BOOL _execute();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_EFF_H */
