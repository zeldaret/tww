#ifndef D_A_OBJ_MAGMAROCK_H
#define D_A_OBJ_MAGMAROCK_H

#include "f_op/f_op_actor.h"
#include "d/d_kankyo.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "dolphin/mtx/quat.h"

class dBgW;
class JPABaseEmitter;

namespace daObjMagmarock {
    static void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
    static BOOL CheckCreateHeap(fopAc_ac_c*);

    class Act_c : public fopAc_ac_c {
    public:
        typedef void (Act_c::*ProcFunc)();

        void MeltDownRequest() {}
        inline cPhs_State _create();
        inline bool _delete();
        inline bool _draw();
        inline bool _execute();
        BOOL checkProcess(ProcFunc proc) { return mProc == proc ? TRUE : FALSE; }
        void setProcess(ProcFunc proc) { mProc = proc; }

        void set_mtx();
        void demo_move();
        void ControlEffect();
        void play_anim();
        void appear_proc_init();
        void appear_proc();
        void wait_proc_init();
        void wait_proc();
        void stay_proc_init();
        void stay_proc();
        void quake_proc_init();
        void quake_proc();
        void vanish_proc_init();
        void vanish_proc();
        BOOL CreateHeap();
        BOOL CreateInit();
        virtual BOOL LiftUpRequest(cXyz&);
        virtual BOOL BeforeLiftRequest(cXyz&);
        void calc_ground_quat();

        static const char M_arcname[];
        static GXColor default_color;

    public:
        /* 0x294 */ u8 field_0x294[0x298 - 0x294];
        /* 0x298 */ s16 mRideAngle;
        /* 0x29A */ s16 field_0x29a;
        /* 0x29C */ s16 mRideFlag;
        /* 0x29E */ u8 mRideOn;
        /* 0x29F */ u8 mStayType;
        /* 0x2A0 */ JPABaseEmitter* mpEmitter0;
        /* 0x2A4 */ JPABaseEmitter* mpEmitter1;
        /* 0x2A8 */ JPABaseEmitter* mpEmitter2;
        /* 0x2AC */ JPABaseEmitter* mpEmitter3;
        /* 0x2B0 */ Quaternion mQuat;
        /* 0x2C0 */ Quaternion mRideQuat;
        /* 0x2D0 */ Quaternion mGroundQuat;
        /* 0x2E0 */ ProcFunc mProc;
        /* 0x2EC */ request_of_phase_process_class mPhase;
        /* 0x2F4 */ J3DModel* mpModel;
        /* 0x2F8 */ J3DAnmTevRegKey* M_brk;
        /* 0x2FC */ mDoExt_brkAnm mBrk;
        /* 0x314 */ J3DAnmTransform* M_bck;
        /* 0x318 */ mDoExt_bckAnm mBck;
        /* 0x328 */ Mtx mMtx;
        /* 0x358 */ dBgW* mpBgW;
        /* 0x35C */ dKy_tevstr_c mTevStr;
        /* 0x40C */ cXyz mGroundPos[3];
        /* 0x430 */ f32 mTilt;
        /* 0x434 */ f32 mBckFrame;
        /* 0x438 */ f32 mBrkFrame;
        /* 0x43C */ cXyz mLiftPos;
        /* 0x448 */ int mTimer;
        /* 0x44C */ int mCount;
        /* 0x450 */ int field_0x450;
        /* 0x454 */ s16 mWaveAngle;
        /* 0x456 */ s16 mWaveSpeed;
        /* 0x458 */ u8 field_0x458[0x45A - 0x458];
        /* 0x45A */ s16 mDemoState;
        /* 0x45C */ s16 mLiftUp;
        /* 0x45E */ s16 mBeforeLift;
    }; // Size: 0x460

    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_MAGMAROCK_H */
