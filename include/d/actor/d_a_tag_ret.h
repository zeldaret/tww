#ifndef D_A_TAG_RET_H
#define D_A_TAG_RET_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"

namespace daTagRet {
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_LINK_ID_W = 8,
            PRM_LINK_ID_S = 0,
        };

        cPhs_State _create();
        bool _delete();
        void set_mtx();
        bool _execute();
        bool _draw();

        u32 prm_get_linkID() const { return daObj::PrmAbstract(this, PRM_LINK_ID_W, PRM_LINK_ID_S); }

    public:
        /* 0x290 */ u8 m290[0x29C - 0x290];
        /* 0x29C */ dCcD_Stts mStts;
        /* 0x2D8 */ dCcD_Cyl mCyl;
    };

};

#endif /* D_A_TAG_RET_H */
