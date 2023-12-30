#ifndef D_A_OBJ_SWFLAT_H
#define D_A_OBJ_SWFLAT_H

#include "f_op/f_op_actor.h"

namespace daObjSwflat {
    class Act_c : public fopAc_ac_c {
    public:
        void prmGetSwNo() const {}
        void prmGetSwNo2() const {}
        void prmGetType() const {}
    
        void CreateHeap();
        s32 Create();
        void Mthd_Create();
        BOOL Delete();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void Execute(float(**)[3][4]);
        BOOL Draw();
        BOOL IsDelete();
    
    public:
        /* Place member variables here */
    };
};

class daObjSwflat_HIO_c {
public:
    daObjSwflat_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_SWFLAT_H */
