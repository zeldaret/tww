#ifndef D_A_OBJ_KANOKE_H
#define D_A_OBJ_KANOKE_H

#include "f_op/f_op_actor.h"

class daObjKanoke_c : public fopAc_ac_c {
public:
    enum Prm_e {
        
    };
    
    daObjKanoke_c();
    cPhs_State _create();
    void createHeap();
    void createInit();
    BOOL _delete();
    BOOL _draw();
    BOOL _execute();
    void executeNormal();
    void executeYureYoko();
    void executeOpenYoko();
    void executeEffectYoko();
    void executeYureTate();
    void executeOpenTate();
    void executeEffectTate();
    void executeWait();
    void getPrmType();
    void getPrmSearch();
    void getPrmYure();
    void getPrmSwNo();
    void getPrmSwNo2();
    void setMtx();
    void setMtxHontai();
    void setMtxHuta(cXyz*);

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_KANOKE_H */
