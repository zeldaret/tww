#ifndef D_A_PEDESTAL_H
#define D_A_PEDESTAL_H

#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor.h"

#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"

namespace daPedestal {

    class daPds_infiniteEcallBack_c : public dPa_levelEcallBack {
    public:
        void execute(JPABaseEmitter*);
        void end();
        void makeEmitter(unsigned short, const cXyz*, const csXyz*, const cXyz*);

        void getEmitter() {}
        void setAngle(const csXyz*) {}
        void setPos(const cXyz*) {}
        void setup(JPABaseEmitter* emitter, const cXyz*, const csXyz*, signed char) {
            mpEmitter = emitter;
        }

    public:
        /* 0x04 */ JPABaseEmitter* mpEmitter;
        /* 0x08 */ const cXyz* mpPos;
        /* 0x08 */ const csXyz* mpAngle;
    };

    class daPds_c : public fopAc_ac_c {
    public:
        BOOL _delete();
        void CreateHeap();
        void CreateInit();
        s32 _create();
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
        BOOL _execute();
        BOOL _draw();

        static const char m_arcname[];

    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ mDoExt_brkAnm mBrk;
        /* 0x2B4 */ u8 m2B4[0x2E4 - 0x2B4];
        /* 0x2E4 */ dBgW* mpBgW;
        /* 0x2E8 */ daPds_infiniteEcallBack_c mInfiniteEcallBack;
        /* 0x2F4 */ u8 m2F4[0x324 - 0x2F4];
    };
};

#endif /* D_A_PEDESTAL_H */
