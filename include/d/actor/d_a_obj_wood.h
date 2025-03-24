#ifndef D_A_OBJ_WOOD_H
#define D_A_OBJ_WOOD_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

namespace daObjWood {
    class Act_c : public fopAc_ac_c {
    public:
        inline cPhs_State _create();
        inline bool _delete();
        inline bool _execute();
        inline bool _draw();
    public:
        /* 0x290 */ u32 field_0x290[3];
        /* 0x29C */ dCcD_Stts mStts;
        /* 0x2D8 */ dCcD_Cyl mCyl;
    };

    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_WOOD_H */
