#ifndef D_A_OBJ_FLAME_H
#define D_A_OBJ_FLAME_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "SSystem/SComponent/c_phase.h"

class JPABaseEmitter;
class mDoExt_btkAnm;
class mDoExt_brkAnm;

namespace daObjFlame {
    struct AttrBase_c {
        /* 0x00 */ s32 mKiInterval;
        /* 0x04 */ s16 mRotSpdA;
        /* 0x06 */ s16 mRotSpdB;
        /* 0x08 */ s16 mLiftupYOfs;
        /* 0x0A */ s16 mLiftupYMin;
        /* 0x0C */ s16 mLiftupYMax;
        /* 0x0E */ s16 mLiftupBase;
        /* 0x10 */ s16 mLiftupPeak;
        /* 0x12 */ s16 field_0x12;
    };  // Size: 0x14

    struct AttrScl_c {
        /* 0x00 */ f32 mSizeScale;
        /* 0x04 */ f32 mHeightScale;
        /* 0x08 */ f32 mScaleXZ;
        /* 0x0C */ f32 mScaleY;
        /* 0x10 */ s32 mModelRes;
        /* 0x14 */ s32 mBtkRes;
        /* 0x18 */ s32 mBrkRes;
        /* 0x1C */ u32 mHeapSize;
        /* 0x20 */ f32 mAnmSpeed;
        /* 0x24 */ f32 mPhaseScale;
        /* 0x28 */ u32 mEm2Id;
        /* 0x2C */ bool mEmSimple;
        /* 0x2D */ bool mEmOnce;
        /* 0x2E */ u8 field_0x2E[0x30 - 0x2E];
        /* 0x30 */ f32 mEm0ScaleXZ;
        /* 0x34 */ f32 mEm0ScaleY;
        /* 0x38 */ f32 mEm1ScaleXZ;
        /* 0x3C */ f32 mEm1ScaleY;
        /* 0x40 */ f32 mEm2Scale;
        /* 0x44 */ f32 field_0x44;
        /* 0x48 */ s16 mCullMinX;
        /* 0x4A */ s16 mCullMinY;
        /* 0x4C */ s16 mCullMinZ;
        /* 0x4E */ s16 mCullMaxX;
        /* 0x50 */ s16 mCullMaxY;
        /* 0x52 */ s16 mCullMaxZ;
        /* 0x54 */ f32 mCpsOnHeight;
    };  // Size: 0x58

    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_SCH_W = 8,
            PRM_SCH_S = 0,
            PRM_KINUM_W = 5,
            PRM_KINUM_S = 8,
            PRM_KICYCLE_W = 2,
            PRM_KICYCLE_S = 13,
            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 16,
            PRM_SCL_W = 2,
            PRM_SCL_S = 24,
            PRM_TYPE_W = 2,
            PRM_TYPE_S = 28,
            PRM_HAZE_W = 1,
            PRM_HAZE_S = 31,
        };

        enum ModeProc_e {
            MODE_WAIT_e = 0,
            MODE_WAIT2_e = 1,
            MODE_L_BEFORE_e = 2,
            MODE_L_U_e = 3,
            MODE_U_e = 4,
            MODE_U_L_e = 5,
            MODE_L_AFTER_e = 6,
        };

        int prm_get_haze() const { return daObj::PrmAbstract(this, PRM_HAZE_W, PRM_HAZE_S); }
        int prm_get_kiCycle() const { return daObj::PrmAbstract(this, PRM_KICYCLE_W, PRM_KICYCLE_S); }
        int prm_get_kiNum() const { return daObj::PrmAbstract(this, PRM_KINUM_W, PRM_KINUM_S); }
        u8 prm_get_sch() const { return daObj::PrmAbstract(this, PRM_SCH_W, PRM_SCH_S); }
        int prm_get_scl() const { return daObj::PrmAbstract(this, PRM_SCL_W, PRM_SCL_S); }
        int prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        int prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }

        inline cPhs_State _create();
        inline bool _delete();
        inline bool _draw();
        inline bool _execute();
        BOOL _is_delete() { return TRUE; }
        const AttrBase_c& attr_base() const { return M_attr_base; }
        const AttrScl_c& attr_scl() const { return M_attr_scl[mType]; }

        void set_switch();
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        void create_mode_init();
        void set_mtx();
        void init_mtx();
        void em_position();
        void em_simple_set();
        void em_simple_inv();
        void em_manual_set();
        void em_manual_inv();
        void ki_init();
        void ki_make();
        void eff_hase();
        void se_fireblast_omen();
        static void* liftup_magmarock(void*, void*);
        static void* liftup_mflft(void*, void*);
        void mode_wait();
        void mode_wait2();
        void mode_l_before();
        void mode_l_u();
        void mode_u();
        void mode_u_l();
        void mode_l_after();
        void mode_proc_call();

    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ mDoExt_btkAnm* mpBtkAnm;
        /* 0x2A0 */ mDoExt_brkAnm* mpBrkAnm;
        /* 0x2A4 */ dCcD_Stts mStts;
        /* 0x2E0 */ dCcD_Cps mCps;
        /* 0x418 */ cXyz mCpsP0;
        /* 0x424 */ cXyz mCpsP1;
        /* 0x430 */ f32 mCpsRad;
        /* 0x434 */ bool mCpsOn;
        /* 0x435 */ u8 field_0x435[0x438 - 0x435];
        /* 0x438 */ int mType;
        /* 0x43C */ int mModeProc;
        /* 0x440 */ f32 mTimer;
        /* 0x444 */ f32 mHeight;
        /* 0x448 */ JPABaseEmitter* mpEmitter0;
        /* 0x44C */ JPABaseEmitter* mpEmitter1;
        /* 0x450 */ JPABaseEmitter* mpEmitter2;
        /* 0x454 */ s8 mEm0State;
        /* 0x455 */ s8 mEm1State;
        /* 0x456 */ s8 mEm2State;
        /* 0x457 */ s8 mEmPosOn;
        /* 0x458 */ s8 mReverb;
        /* 0x459 */ u8 mEmOnceDone;
        /* 0x45A */ u8 mKiActive;
        /* 0x45B */ u8 field_0x45B;
        /* 0x45C */ int mKiCycleTmr;
        /* 0x460 */ int mKiIntervalTmr;
        /* 0x464 */ int mKiCount;
        /* 0x468 */ s16 mRotY;
        /* 0x46A */ s16 field_0x46A;
        /* 0x46C */ f32 mSpread;
        /* 0x470 */ f32 mExtraScaleY;
        /* 0x474 */ cXyz mOrigScale;

        static const AttrBase_c M_attr_base;
        static const dCcD_SrcCps M_cps_src;
        static const AttrScl_c M_attr_scl[4];
        static char M_arcname[];
    };

    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_FLAME_H */
