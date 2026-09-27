#ifndef D_A_OBJ_MAGMAROCK_H
#define D_A_OBJ_MAGMAROCK_H

#include "JSystem/J3DGraphAnimator/J3DAnimation.h"
#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_kankyo.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/mtx/quat.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class dBgW;

namespace daObjMagmarock {
    static void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
    static BOOL CheckCreateHeap(fopAc_ac_c*);

    class Act_c;
    typedef void (Act_c::* Process)();
    
    class Act_c : public fopAc_ac_c {
    public:
        void MeltDownRequest() {}
        inline cPhs_State _create();
        inline bool _delete();
        inline bool _draw();
        inline bool _execute();
        BOOL checkProcess(Process p) {
            return m2e0 == p;
        }
        void setProcess(Process p) {
            m2e0 = p;
        }
    
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
        virtual bool BeforeLiftRequest(cXyz&);
        void calc_ground_quat();

    public:
        /* 0294 */ u8 m294[0x298-0x294];
        /* 0298 */ s16 m298;
        /* 029a */ u16 m29a;
        /* 029c */ s16 m29c;
        /* 029e */ u8 m29e;
        /* 029f */ u8 m29f;
        /* 02a0 */ JPABaseEmitter *m2a0;
        /* 02a4 */ JPABaseEmitter *m2a4;
        /* 02a8 */ JPABaseEmitter *m2a8;
        /* 02ac */ JPABaseEmitter *m2ac;
        /* 02b0 */ Quaternion m2b0;
        /* 02c0 */ Quaternion m2c0;
        /* 02d0 */ Quaternion m2d0;
        /* 02e0 */ Process m2e0;
        /* 02ec */ request_of_phase_process_class mPhase;
        /* 02f4 */ J3DModel *mpModel;
        /* 02f8 */ J3DAnmTevRegKey *M_brk;
        /* 02fc */ mDoExt_brkAnm mBrkAnm;
        /* 0314 */ J3DAnmTransform *M_bck;
        /* 0318 */ mDoExt_bckAnm mBckAnm;
        /* 0328 */ Mtx mtx;
        /* 0358 */ dBgW *mpBgW;
        /* 035c */ dKy_tevstr_c m35c;
        /* 040c */ cXyz m40c[3];
        /* 0430 */ f32 m430;
        /* 0434 */ f32 m434;
        /* 0438 */ f32 m438;
        /* 043c */ cXyz m43c;
        /* 0448 */ s32 m448;
        /* 044c */ s32 m44c;
        /* 0450 */ u32 m450;
        /* 0454 */ s16 m454;
        /* 0456 */ s16 m456;
        /* 0458 */ u8 m458[2];
        /* 045a */ s16 m45a;
        /* 045c */ s16 m45c;
        /* 045e */ s16 m45e;

        static const char M_arcname[];
        static const GXColor default_color;
    }; // size 0x460

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
