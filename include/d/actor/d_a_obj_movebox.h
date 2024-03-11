#ifndef D_A_OBJ_MOVEBOX_H
#define D_A_OBJ_MOVEBOX_H

#include "d/d_a_obj.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_wtr_chk.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_particle.h"
#include "d/d_bg_w.h"
#include "d/d_path.h"

namespace daObjMovebox {
    class Act_c;
    
    struct Attr_c {
        /* 0x00 */ s16 m00;
        /* 0x02 */ s16 m02;
        /* 0x04 */ s16 m04;
        /* 0x06 */ s16 m06;
        /* 0x08 */ s16 m08;
        /* 0x0A */ s16 m0A;
        /* 0x0C */ f32 m0C;
        /* 0x10 */ f32 m10;
        /* 0x14 */ f32 m14;
        /* 0x18 */ f32 m18;
        /* 0x1C */ f32 m1C;
        /* 0x20 */ f32 m20;
        /* 0x24 */ f32 mLandSmokeScale;
        /* 0x28 */ f32 m28;
        /* 0x2C */ f32 m2C;
        /* 0x30 */ f32 m30;
        /* 0x34 */ f32 m34;
        /* 0x38 */ s16 m38;
        /* 0x3C */ f32 m3C;
        /* 0x40 */ f32 m40;
        /* 0x44 */ f32 m44;
        /* 0x48 */ f32 m48;
        /* 0x4C */ f32 m4C;
        /* 0x50 */ f32 m50;
        /* 0x54 */ f32 m54;
        /* 0x58 */ int mModelFileIndex;
        /* 0x5C */ int mDZBFileIndex;
        /* 0x60 */ int mDZBHeapSize;
        /* 0x64 */ f32 mScaleY;
        /* 0x68 */ f32 m68;
        /* 0x6C */ f32 m6C;
        /* 0x70 */ f32 mScaleXZ;
        /* 0x74 */ f32 m74;
        /* 0x78 */ u32 mMoveSE;
        /* 0x7C */ u32 mCantMoveSE;
        /* 0x80 */ u32 mNormalFallSE;
        /* 0x84 */ u32 mWaterFallSE;
        /* 0x88 */ u32 mMagmaFallSE;
        /* 0x8C */ s16 mCullMinX;
        /* 0x8E */ s16 mCullMinY;
        /* 0x90 */ s16 mCullMinZ;
        /* 0x92 */ s16 mCullMaxX;
        /* 0x94 */ s16 mCullMaxY;
        /* 0x96 */ s16 mCullMaxZ;
        /* 0x98 */ bool mbUseBGTevType;
        /* 0x99 */ bool mbCastsShadow;
        /* 0x9A */ bool m9A;
    };  // Size: 0x9C
    
    struct BgcSrc_c {
        /* 0x00 */ f32 m00; // z
        /* 0x04 */ f32 m04; // x
        /* 0x08 */ f32 m08; // z
        /* 0x0C */ f32 m0C; // x
    };
    
    struct Bgc_c {
    public:
        enum State_e {
            BgcState_ON_GROUND_e = 0x01,
            BgcState_JUST_LEFT_GROUND_e = 0x02,
            BgcState_JUST_HIT_GROUND_e = 0x04,
            BgcState_ABOVE_WATER_e = 0x08,
            BgcState_IN_WATER_e = 0x10,
            BgcState_JUST_HIT_WATER_e = 0x20,
        };
        
        Bgc_c();
        ~Bgc_c();
        void gnd_pos(const Act_c*, const BgcSrc_c*, int, f32);
        void wrt_pos(const cXyz&);
        void wall_pos(const Act_c*, const BgcSrc_c*, int, s16, f32);
        void proc_vertical(Act_c*);
        bool chk_wall_pre(const Act_c*, const BgcSrc_c*, int, s16);
        bool chk_wall_touch(const Act_c*, const BgcSrc_c*, s16);
        bool chk_wall_touch2(const Act_c*, const BgcSrc_c*, int, s16);
    
    public:
        /* 0x000 */ f32 mGroundY[23];
        /* 0x05C */ int mMaxGroundIdx;
        /* 0x060 */ f32 mWaterY;
        /* 0x064 */ cXyz mWallPos[23];
        /* 0x178 */ int mWallIdx;
        /* 0x17C */ f32 mNearestWallDist;
        /* 0x180 */ State_e mStateFlags;
        
        static dBgS_ObjGndChk M_gnd_work[23];
        static dBgS_WtrChk M_wrt_work;
        static dBgS_ObjLinChk M_wall_work[23];
        static const BgcSrc_c M_lin5[5];
        static const BgcSrc_c M_lin20[23];
    };  // Size: 0x184
    
    class EffSmokeCB : public dPa_smokeEcallBack {
    public:
        EffSmokeCB() {}
        virtual ~EffSmokeCB() {}
    
    public:
        /* 0x20 */ cXyz field_0x20;
        /* 0x2C */ csXyz field_0x2C;
    };  // Size: 0x34
    
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Type {
            TYPE_BREAKABLE_WOODEN_CRATE = 0x0,  // Actor names: Kkiba or DKkiba
            TYPE_BLACK_BOX              = 0x1,  // Actor names: osiBLK0 or DBLK0
            TYPE_BLACK_BOX_WITH_STATUE  = 0x2,  // Actor names: osiBLK1 or DBLK1
            TYPE_BIG_BLACK_BOX          = 0x3,  // Actor names: MpwrB
            TYPE_WOODEN_CRATE           = 0x4,  // Actor names: (N/A)
            TYPE_GOLDEN_CRATE           = 0x5,  // Actor names: Hbox2
            TYPE_METAL_BOX              = 0x6,  // Actor names: Hbox1
            TYPE_METAL_BOX_WITH_SPRING  = 0x7,  // Actor names: Hjump1
            TYPE_WOODEN_CRATE_2         = 0x8,  // Actor names: Hseki2
            TYPE_WOODEN_CRATE_3         = 0x9,  // Actor names: Hseki7
            TYPE_MIRROR                 = 0xA,  // Actor names: Mmrr
            TYPE_BLACK_BOX_WITH_MKIE    = 0xB,  // Actor names: MkieBB
            TYPE_MOSSY_BLACK_BOX        = 0xC,  // Actor names: Ecube
        };
        
        enum Mode {
            MODE_WAIT   = 0x0,
            MODE_WALK   = 0x1,
            MODE_AFLOAT = 0x2,
        };
        
        enum Prm_e {
            PRM_TYPE_W = 0x04,
            PRM_TYPE_S = 0x18,
            
            PRM_SWSAVE_W = 0x01,
            PRM_SWSAVE_S = 0x1E,
            
            PRM_SWSAVE1_W = 0x08,
            PRM_SWSAVE1_S = 0x08,
            
            PRM_ITEMNO_W = 0x06,
            PRM_ITEMNO_S = 0x00,
            
            PRM_ITEMSAVE_W = 0x07,
            PRM_ITEMSAVE_S = 0x10,
            
            PRM_BUOY_W = 0x01,
            PRM_BUOY_S = 0x1F,
        };
        
        typedef void (Act_c::*ModeFunc)();
        
        inline s32 Mthd_Create();
        inline BOOL Mthd_Delete();
        
        s32 prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prm_get_swSave1() const;
        s32 prmZ_get_swSave2() const { return mType == TYPE_BLACK_BOX_WITH_MKIE ? 0xFF : (u8)(mPrmZ >> 8); }
        s32 prmZ_get_swSave2_MkieB() const { return mType == TYPE_BLACK_BOX_WITH_MKIE ? (u8)(mPrmZ >> 8) : 0xFF; }
        s32 prmZ_get_pathId() const { return mType == TYPE_BLACK_BOX_WITH_MKIE ? 0xFF : (mPrmZ & 0x00FF) >> 0; }
        s32 prmX_get_evId() const { return (mPrmX & 0x00FF) >> 0; }
        s32 prm_get_itemNo() const { return daObj::PrmAbstract(this, PRM_ITEMNO_W, PRM_ITEMNO_S); }
        s32 prm_get_itemSave() const { return daObj::PrmAbstract(this, PRM_ITEMSAVE_W, PRM_ITEMSAVE_S); }
        s32 prm_get_buoy() const { return daObj::PrmAbstract(this, PRM_BUOY_W, PRM_BUOY_S); }
        s32 prm_get_dmy() const; // Unused?
        
        BOOL is_switch1() const { return fopAcM_isSwitch(const_cast<Act_c*>(this), prm_get_swSave1()); };
        BOOL is_switch2() const { return fopAcM_isSwitch(const_cast<Act_c*>(this), prmZ_get_swSave2()); };
        void on_switch1() const { fopAcM_onSwitch(const_cast<Act_c*>(this), prm_get_swSave1()); };
        void on_switch2() const { fopAcM_onSwitch(const_cast<Act_c*>(this), prmZ_get_swSave2()); };
        void off_switch1() const { fopAcM_offSwitch(const_cast<Act_c*>(this), prm_get_swSave1()); };
        void off_switch2() const { fopAcM_offSwitch(const_cast<Act_c*>(this), prmZ_get_swSave2()); };
        
        inline void mode_proc_call();
        bool chk_walk(cXyz*) { /* TODO */ }
        void set_rollCrash() { mbRollCrash = TRUE; }
        
        void prmZ_init();
        void prmX_init();
        const Attr_c* attr() const; // TODO weak?
        inline const Attr_c* i_attr() const { return &M_attr[mType]; } // TODO weak?
        void set_mtx();
        void init_mtx();
        void path_init();
        void path_save();
        int CreateHeap();
        static void RideCallBack(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        static fopAc_ac_c* PPCallBack(fopAc_ac_c*, fopAc_ac_c*, s16, dBgW::PushPullLabel);
        int Create();
        void afl_sway();
        int check_to_walk();
        void clr_moment_cnt();
        bool chk_appear() const;
        void eff_set_slip_smoke_pos();
        void eff_smoke_slip_start();
        void eff_smoke_slip_end();
        void eff_smoke_slip_remove();
        void mode_wait_init();
        void mode_wait();
        void mode_walk_init();
        void mode_walk();
        void mode_afl_init();
        void mode_afl();
        void make_item();
        void eff_break();
        void sound_break();
        void sound_slip();
        void sound_limit();
        void sound_land();
        void vib_land();
        void eff_land_smoke();
        int Execute(Mtx**);
        int Draw();
        int Delete();
        
        static const s16 M_dir_base[4];
    
    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ Mtx mMtx;
        /* 0x300 */ J3DModel* mpModel;
        /* 0x304 */ int mMode;
        /* 0x308 */ dCcD_Stts mStts;
        /* 0x344 */ dCcD_Cyl mCyl;
        /* 0x474 */ Bgc_c mBgc;
        /* 0x5F8 */ int mType;
        /* 0x5FC */ u16 mPrmZ;
        /* 0x5FE */ u16 mPrmX;
        /* 0x600 */ dPath* mpPath;
        /* 0x604 */ s16 m604;
        /* 0x606 */ u8 m606[0x608 - 0x606];
        /* 0x608 */ f32 m608;
        /* 0x60C */ f32 m60C;
        /* 0x610 */ f32 m610;
        /* 0x614 */ f32 m614;
        /* 0x618 */ f32 m618;
        /* 0x61C */ f32 m61C;
        /* 0x620 */ f32 m620;
        /* 0x624 */ f32 m624;
        /* 0x628 */ int m628;
        /* 0x62C */ int m62C;
        /* 0x630 */ f32 m630;
        /* 0x634 */ int m634;
        /* 0x638 */ dBgW::PushPullLabel mPPLabel;
        /* 0x63C */ s16 mMomentCnt[4];
        /* 0x644 */ s16 m644;
        /* 0x646 */ s16 m646;
        /* 0x648 */ s16 m648;
        /* 0x64A */ bool m64A;
        /* 0x64B */ s8 mReverb;
        /* 0x64C */ bool mbShouldAppear;
        /* 0x64D */ bool mbPrmZInitialized;
        /* 0x64E */ bool mbPrmXInitialized;
        /* 0x64F */ bool m64F;
        /* 0x650 */ EffSmokeCB mSmokeCbs[2];
        /* 0x6B8 */ uint mChildPID;
        /* 0x6BC */ BOOL mbRollCrash;
        
        static const char* const M_arcname[13];
        static const dCcD_SrcCyl M_cyl_src;
        static const Attr_c M_attr[13];
    };
    
    STATIC_ASSERT(sizeof(Act_c) == 0x6C0);
}

#endif /* D_A_OBJ_MOVEBOX_H */
