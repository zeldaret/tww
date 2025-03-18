#ifndef D_A_OBJ_EAYOGN_H
#define D_A_OBJ_EAYOGN_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"
// #include "d/d_com_inf_game.h"

class daObjEayogn_c : public fopAc_ac_c {
public:
    // TODO: this function is marked as weak in the REL symbol map, but it does not get inlined for some reason?
    // BOOL check_ev_bit() const { return dComIfGs_isSymbol(1); }
    BOOL check_ev_bit() const;

    cPhs_State _create();
    bool _execute();
    bool _draw();
    bool _delete();
    BOOL create_heap();
    static BOOL solidHeapCB(fopAc_ac_c *i_this);
    void init_mtx();
    static const char M_arcname[7];

public:
    /* 0x290 */ J3DModel * mpModel;
    /* 0x294 */ request_of_phase_process_class mPhs;
    /* 0x2A0 */ dBgW * mpBgW;
};

#endif /* D_A_OBJ_EAYOGN_H */
