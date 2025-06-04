#ifndef D_A_WIND_TAG_H
#define D_A_WIND_TAG_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_point_wind.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"

class JPABaseEmitter;
struct dPath;

namespace daWindTag {
    static BOOL CheckCreateHeap(fopAc_ac_c*);

    class daWindTag_c : public fopAc_ac_c {
    public:
        f32 getCurLength() const {
            return mOffsY;
        }
        f32 getMaxLength() const {
            return field_0x49c * mData[mType * 2 + 1];
        }
    
        bool _delete();
        BOOL CreateHeap();
        void CreateInit();
        void set_wind_angle();
        cPhs_State _create();
        void set_mtx();
        bool checkSizeSpecialBig();
        void set_wind_se_sub(unsigned long, cXyz*);
        void set_wind_se();
        bool _execute();
        void path_move();
        void set_next_pnt();
        bool _draw();
        void MoveEmitter();
        
        static const f32 mData[];
        static const char* m_arcname[];
        static s16 m_bdlidx[];
        static s16 m_heapsize[];
        static s16 m_bckidx[];
        static s16 m_btkidx[];
        static s16 m_btkidx2[];
        static f32 m_cullsize_far;
        static f32 m_ef_cullsize_far;

    public:
        /* Place member variables here */
        /* 0x290 */ dCcD_Stts mStts;
        /* 0x2CC */ dCcD_Cps mCps;
        /* 0x404 */ cM3dGCpsS mCpsS;
        /* 0x420 */ request_of_phase_process_class mPhs;
        /* 0x428 */ J3DModel* mpModel;
        /* 0x42C */ mDoExt_btkAnm mBtkAnm0;
        /* 0x440 */ mDoExt_btkAnm mBtkAnm1;
        /* 0x454 */ mDoExt_bckAnm mBckAnm;
        /* 0x464 */ dPointWind_c mPointWind;
        /* 0x494 */ u8 mType;
        /* 0x498 */ f32 mOffsY;
        /* 0x49C */ f32 field_0x49c;
        /* 0x4A0 */ JPABaseEmitter* mpEmitter;
        /* 0x4A4 */ GXColor mEfColor;
        /* 0x4A8 */ dKy_tevstr_c mEfTevStr;
        /* 0x558 */ cXyz mSePos;
        /* 0x564 */ cXyz mTargetPos;
        /* 0x570 */ dPath* mpPath;
        /* 0x574 */ u8 mPathId;
        /* 0x575 */ s8 mCurPathPoint;
        /* 0x576 */ s8 mPathPointDir;
        /* 0x578 */ s32 mSwNo;
        /* 0x57C */ u8 field_0x57c;
        /* 0x57D */ u8 field_0x57d;
        /* 0x57E */ bool mbDraw;
        /* 0x57F */ u8 field_0x57f;
        /* 0x580 */ fpc_ProcID mLevelSeID;
    };
};  // namespace daWindTag

#endif /* D_A_WIND_TAG_H */
