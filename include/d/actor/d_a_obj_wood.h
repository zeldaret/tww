#ifndef D_A_OBJ_WOOD_H
#define D_A_OBJ_WOOD_H

#include "f_op/f_op_actor.h"

namespace daObjWood {
    class Method : public fopAc_ac_c {
    public:
        void Create(void*);
        void Delete(void*);
        void Execute(void*);
        void Draw(void*);
        void IsDelete(void*);
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_WOOD_H */
