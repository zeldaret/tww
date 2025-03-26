#ifndef D_A_OBJ_SWFLAT_H
#define D_A_OBJ_SWFLAT_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjSwflat {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prmGetSwNo() const {}
        void prmGetSwNo2() const {}
        void prmGetType() const {}
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
        virtual BOOL IsDelete();
    
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
