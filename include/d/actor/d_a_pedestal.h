#ifndef D_A_PEDESTAL_H
#define D_A_PEDESTAL_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "m_Do/m_Do_ext.h"

namespace daPedestal {
    class daPds_c : public fopAc_ac_c {
    public:
        void _delete();
        void CreateHeap();
        void CreateInit();
        void _create();
        void getMyStaffId();
        void wakeupCheck();
        void finishCheck();
        void setAction(int (daPedestal::daPds_c::*)(void*), void*);
        void action(void*);
        void waitAction(void*);
        void eventProc();
        void initialDefault(int);
        void actionDefault(int);
        void initialMoveEvent(int);
        void actionMoveEvent(int);
        void initialEffectSet(int);
        void initialEffectEnd(int);
        void set_mtx();
        void initBrkAnm(unsigned char, bool);
        void playBrkAnm();
        void _execute();
        void _draw();
    
    public:
        /* 0x290 */ u8 m290[0x298 - 0x290];
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ mDoExt_brkAnm mBrk;
        /* 0x2B4 */ u8 m2B4[0x2E4 - 0x2B4];
        /* 0x2E4 */ dBgW* mpBgW;
        /* 0x2E8 */ u8 m2E8[0x324 - 0x2E8];
    };
};

#endif /* D_A_PEDESTAL_H */
