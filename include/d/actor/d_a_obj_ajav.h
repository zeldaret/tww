#ifndef D_A_OBJ_AJAV_H
#define D_A_OBJ_AJAV_H

#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"

namespace daObjAjav {
    static void daObjAjav_make_splash(cXyz, f32);
    static BOOL check_angle(s16*, s16);
    static void daObjAjav_limit_angle(s16*, s16);
    static csXyz daObjAjav_get_rot_speed(cXyz, cXyz, s16);
    
    class Act_c;
    
    class Part_c {
    public:
        typedef void(Part_c::*daObjAjavPartCallback)(daObjAjav::Act_c*);
    public:
        bool checkExeProc(daObjAjavPartCallback i_proc) { return mExeProc == i_proc; }
        void draw(daObjAjav::Act_c* i_actor) {  (this->*mDrawProc)(i_actor); }
        void execute(daObjAjav::Act_c* i_actor) { (this->*mExeProc)(i_actor); }
        void setDrawProc(daObjAjavPartCallback i_drawProc) { mDrawProc = i_drawProc; }
        void setExeProc(daObjAjavPartCallback i_exeProc) { mExeProc = i_exeProc; }
        inline void set_se_pos(cXyz i_pos); // weak but not inlined
        
        void make_hamon(cXyz, f32);
        void no_proc(daObjAjav::Act_c*);
        void init_data(cXyz, cXyz, dKy_tevstr_c*, cXyz*);
        BOOL set_mdl_area(const char*, int, u32);
        void init_mtx(cXyz, csXyz, cXyz);
        void set_flaw_mtx(cXyz, csXyz);
        void set_fall_mtx(cXyz, csXyz);
        void fall_init(cXyz, csXyz, s16, u16);
        void fall_0(daObjAjav::Act_c*);
        void fall_1(daObjAjav::Act_c*);
        void flaw(daObjAjav::Act_c*);
        void draw_normal(daObjAjav::Act_c*);
        void draw_flashing(daObjAjav::Act_c*);
        void draw_flashing_shy(daObjAjav::Act_c*);
        void draw_flashing_normal(daObjAjav::Act_c*);
        void draw_shy(daObjAjav::Act_c*);
        void make_fall_rock(BOOL);
    public:
        /* 0x00 */ cXyz mCenterPos;
        /* 0x0C */ cXyz mCenterToOriginTrans;
        /* 0x18 */ cXyz mRockDisplacement;
        /* 0x24 */ cXyz mRockDisplacementRate;
        /* 0x30 */ cXyz mFlawPos;
        /* 0x3C */ csXyz mAccumulatedRotation;
        /* 0x42 */ csXyz mRotationSpeed;
        /* 0x48 */ cXyz mSePos;
        /* 0x54 */ u16 mTimerTrigger;
        /* 0x56 */ u16 mTimer; // also used as a vertical velocity in fall_1
        /* 0x58 */ s16 mAngleLimit;
        /* 0x5A */ bool mbHasSplashed;
        /* 0x5B */ u8 mB8[0x6C - 0x5B];
        /* 0x6C */ cXyz mRockParticlePos;
        /* 0x78 */ J3DModel* mpModel;
        /* 0x7C */ dKy_tevstr_c* mpTevStr;
        /* 0x80 */ daObjAjavPartCallback mExeProc;
        /* 0x8C */ daObjAjavPartCallback mDrawProc;
    };  // Size: 0x98


    class Act_c : public fopAc_ac_c {
    public:
        enum {
            STATUS_MAX = 4
        };
    public:
        BOOL check_ev() { return dComIfGs_isEventBit(dSv_event_flag_c::ENDLESS_NIGHT); }
        BOOL check_sw(int sw_no) { return dComIfGs_isSwitch(sw_no, fopAcM_GetHomeRoomNo(this)); }
        void on_sw(int sw_no) { dComIfGs_onSwitch(sw_no, fopAcM_GetHomeRoomNo(this)); }
        
        // Fake inline method to match _execute, this isn't in the debug maps but is needed
        // in the call to set_hamon.
        // The stone is 6 fragments arranged in a 3x2 (row x col) grid, so
        // this gets the starting index of the n'th row.
        int get_rock_row() { return M_status << 1; }

        static BOOL solidHeapCB(fopAc_ac_c*);
        BOOL create_heap();
        cPhs_State _create();
        bool _delete();
        void init_mtx();
        void set_tex();
        void set_co_offset();
        BOOL check_all_wait();
        BOOL check_end();
        void to_broken();
        BOOL damage_part();
        void make_shot_rock();
        void make_hamon2(cXyz, float);
        void set_hamon(float);
        bool _execute();
        bool _draw();
    
    public:
        static const char M_arcname[];
    public:
        /* 0x290 */ u32 mSwNo;
        /* 0x294 */ request_of_phase_process_class mPhs;
        /* 0x29C */ dCcD_Stts mSphStts;
        /* 0x2D8 */ dCcD_Sph mSph;
        /* 0x404 */ cXyz mSphCoOffset;
        /* 0x410 */ dCcD_Stts mCylStts;
        /* 0x44C */ dCcD_Cyl mCyl;
        /* 0x57C */ dCcD_Stts mHintCylStts[2];
        /* 0x5F4 */ dCcD_Cyl mHintCyls[2];
        /* 0x854 */ Mtx mMtx;
        /* 0x884 */ u8 m884[0x890 - 0x884];
        /* 0x890 */ Part_c mRockParts[6];
        /* 0xC20 */ s16 mEventIdx;
        /* 0xC22 */ u8 M_status;
        /* 0xC23 */ bool mbResLoaded;
        /* 0xC24 */ u8 mActionIdx;
        /* 0xC25 */ u8 mC25[0xC26 - 0xC25];
        /* 0xC26 */ u16 mCutsceneEndDelay;
        /* 0xC28 */ u8 mHintCylHits;
        /* 0xC29 */ u8 mC29[0xC2C - 0xC29];
        /* 0xC2C */ dBgW* mpBgW;
    };  // Size: 0xC30
};

#endif /* D_A_OBJ_AJAV_H */
