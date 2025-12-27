#ifndef D_A_OBJ_OTBLE_H
#define D_A_OBJ_OTBLE_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"

class dBgW;

namespace daObj_Otble {
    struct Attr_c {
        u8 m00;
        u8 m01;
    }; // size = 0x2

    class Act_c : public fopAc_ac_c {
    public:
        inline cPhs_State _create();
        inline bool _delete();
        const Attr_c* attr() const { return &M_attr; }
    
        void set_mtx();
        BOOL _execute();
        BOOL _draw();
        BOOL _createHeap();
        void CreateInit();

        static const Attr_c M_attr;
    
    public:
        /* 0x290 */ J3DModel* mModel;
        /* 0x294 */ s32 m294;
        /* 0x298 */ request_of_phase_process_class mPhase;
        /* 0x2A0 */ dBgW* mBgW;
        /* 0x2A4 */ Mtx m2A4;
        /* 0x2D4 */ dBgS_ObjAcch mObjAcch;
        /* 0x498 */ dBgS_AcchCir mObjAcchCir;
    }; // size = 0x4D8

    namespace Mthd {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_OTBLE_H */
