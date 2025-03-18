#ifndef D_A_OBJ_OTBLE_H
#define D_A_OBJ_OTBLE_H

#include "f_op/f_op_actor.h"

namespace daObj_Otble {
    class Act_c : public fopAc_ac_c {
    public:
        inline cPhs_State _create();
        inline bool _delete();
        void attr() const {}
    
        void set_mtx();
        bool _execute();
        bool _draw();
        void _createHeap();
        void CreateInit();
    
    public:
        /* Place member variables here */
    };

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
