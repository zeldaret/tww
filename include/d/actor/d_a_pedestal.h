#ifndef D_A_PEDESTAL_H
#define D_A_PEDESTAL_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"

namespace daPedestal {
    static BOOL CheckCreateHeap(fopAc_ac_c*);
    static s32 daPds_Create(void*);
    static BOOL daPds_Delete(void*);
    static BOOL daPds_Draw(void*);
    static BOOL daPds_Execute(void*);
    static BOOL daPds_IsDelete(void*);

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
    
    public:
        /* 0x290 */ u8 m290[0x298 - 0x290];
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ mDoExt_brkAnm mBrk;
        /* 0x2B4 */ u8 m2B4[0x2E4 - 0x2B4];
        /* 0x2E4 */ dBgW* mpBgW;
        /* 0x2E8 */ u8 m2E8[0x324 - 0x2E8];
    };

    class daPds_infiniteEcallBack_c : public dPa_levelEcallBack {
        void execute(JPABaseEmitter*);
        void end();
        void makeEmitter(unsigned short, const cXyz*, const csXyz*, const cXyz*);
        void setup(JPABaseEmitter*, const cXyz*, const csXyz*, signed char);
    };
};

#endif /* D_A_PEDESTAL_H */
