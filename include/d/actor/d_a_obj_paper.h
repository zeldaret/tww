#ifndef D_A_OBJ_PAPER_H
#define D_A_OBJ_PAPER_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_msg.h"

namespace daObjPaper {
    class Act_c : public fopAc_ac_c {
    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ dCcD_Cyl mCyl;
        /* 0x3CC */ dCcD_Stts mStts;
        /* 0x408 */ u8 mbHasCc;
        /* 0x409 */ u8 m409[0x40C - 0x409];
        /* 0x40C */ int mMode;
        /* 0x410 */ int mMsgId;
        /* 0x414 */ msg_class* mpMsg;
        /* 0x418 */ int mType;
    };
};

#endif /* D_A_OBJ_PAPER_H */
