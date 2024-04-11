#ifndef D_A_OBJ_PAPER_H
#define D_A_OBJ_PAPER_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_msg.h"
#include "d/d_a_obj.h"

namespace daObjPaper {
    enum Type_e {
        Opaper_e,
        Ppos_e,
        Piwa_e,
    };

    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_MSG_NO_W = 0x10,
            PRM_MSG_NO_S = 0x00,

            PRM_TYPE_W = 0x04,
            PRM_TYPE_S = 0x10,
        };

        enum Act_Mode_e {
            ActMode_WAIT_e,
            ActMode_TALKBEGIN_e,
            ActMode_GETMSG_e,
            ActMode_TALKWAIT_e,
        };

        u32 prm_get_msgNo() const { return daObj::PrmAbstract<Prm_e>(this, PRM_MSG_NO_W, PRM_MSG_NO_S); }
        Type_e prm_get_type() const { return (Type_e)daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S); }
    
        static const dCcD_SrcCyl M_cyl_src;
    
        static int solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        s32 _create();
        bool _delete();
        void mode_wait_init();
        void mode_wait();
        void mode_talk0_init();
        void mode_talk0();
        void mode_talk1_init();
        void mode_talk1();
        void mode_talk2_init();
        void mode_talk2();
        void set_mtx();
        void init_mtx();
        void damage_cc_proc();
        bool _execute();
        bool _draw();
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ dCcD_Cyl mCylinderCol;
        /* 0x3CC */ dCcD_Stts mColStatus;
        /* 0x408 */ bool mbHasCc;
        /* 0x40C */ int mMode;
        /* 0x410 */ uint mMsgId;
        /* 0x414 */ msg_class* mpMsg;
        /* 0x418 */ Type_e mType;
    };
};

#endif /* D_A_OBJ_PAPER_H */
