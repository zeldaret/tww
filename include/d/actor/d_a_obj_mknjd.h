#ifndef D_A_OBJ_MKNJD_H
#define D_A_OBJ_MKNJD_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_particle.h"
#include "d/d_com_inf_game.h"
#include "SSystem/SComponent/c_phase.h"

class msg_class;

namespace daObjMknjD {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_SWITCH_W = 0x08,
            PRM_SWITCH_S = 0x00,

            PRM_TYPE_W = 0x01,
            PRM_TYPE_S = 0x10,
        };

        int prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWITCH_W, PRM_SWITCH_S); }
        u8 prm_get_Type() const { return daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S); }

        void anmAtr(u16) {}
        u32 getMsg() {
            if (m0500 == 0) {
                dComIfGp_setMelodyNum(mTactMode);
                return 0x05B3;
            }
            else {
                return 0x1901;
            }
        }
    
        s32 Mthd_Create();
        s32 Mthd_Delete();

        s16 XyCheckCB(int);
        s16 XyEventCB(int);

        int CreateHeap();
        int Create();

        int Delete();

        void set_mtx();
        void init_mtx();

        void setGoal(int);
        void setPlayerAngle(int);
        u16 talk(int);
        void privateCut();
        bool daObjMknjD_break();

        int Execute(Mtx**);
        int Draw();

        static const char M_arcname[];
        static Mtx M_tmp_mtx;

        /* 0x02C8 */ cXyz mLeftHalfPos;
        /* 0x02D4 */ cXyz mRightHalfPos;
        /* 0x02E0 */ cXyz mShardPositions[0x14];
        /* 0x03D0 */ f32 mShardHeights[0x14];
        /* 0x0420 */ request_of_phase_process_class mPhs;
        /* 0x0428 */ J3DModel* mMainMdl;
        /* 0x042C */ J3DModel* mBreakMdl;
        /* 0x0430 */ u16 m0430;
        /* 0x0432 */ u16 m0432;
        /* 0x0434 */ u16 m0434;
        /* 0x0438 */ s32 mBreakTimer;
        /* 0x043C */ u8 mMainMdlAlpha;
        /* 0x043D */ bool m043D;
        /* 0x043E */ u8 m043E;
        /* 0x043F */ u8 m043F;
        /* 0x0440 */ JPABaseEmitter* mEmitters[4];
        /* 0x0450 */ dPa_smokeEcallBack mSmokeCBs[4];
        /* 0x04D0 */ cXyz mBrokenPos;
        /* 0x04DC */ s16 mCheckEventIdx;
        /* 0x04DE */ s16 mDemoEventIdx;
        /* 0x04E0 */ s16 mErrorEventIdx;
        /* 0x04E2 */ s16 mLessonEventIdx;
        /* 0x04E4 */ s8 mActionIdx;
        /* 0x04E5 */ u8 mTactMode;
        /* 0x04E6 */ u8 mGiveItemNo;
        /* 0x04E8 */ cXyz mGoalPos;
        /* 0x04F4 */ u32 mMsgNo;
        /* 0x04F8 */ uint mMsgPID;
        /* 0x04FC */ msg_class* mMsgPtr;
        /* 0x0500 */ s32 m0500;
        /* 0x0504 */ bool m0504;
    };

    const char Act_c::M_arcname[] = "MknjD";

    static void manage_friend_draw(int);
    static void setMaterial(J3DMaterial*, u8);
};

#endif /* D_A_OBJ_MKNJD_H */
