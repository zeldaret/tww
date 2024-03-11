#ifndef D_A_OBJ_FTREE_H
#define D_A_OBJ_FTREE_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_gnd_chk.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

namespace daObjFtree {
    struct _ftree_seach_info_ {
        
    };

    static void Ftree_get_water_pos(cXyz*, cXyz*);
    static void Ftree_checkXyEventCallBack(void*, int);
    static void Ftree_XyEventCallBack(void*, int);
    static void is_broughtID(int);
    static BOOL Ftree_NodeCallBack_Effect(J3DNode*, int);
    static BOOL Ftree_NodeCallBack_M(J3DNode*, int);
    static BOOL Ftree_NodeCallBack_L(J3DNode*, int);

    class Act_c : public fopAc_ac_c {
    public:
        void GetRate(float, float, float) {}
        void brought() {}
        void check_heart() {}
        void check_water() {}
        void init_water() {}
        void param_get_tree_idx() const; // weak but not inlined?
        void set_heart(short) {}
        void set_water(short) {}
        void tree_brouht(int) {}
    
        void search_heart_part();
        void launch_heart_part();
        void place_heart_part();
        void estimate_water();
        void XyEventCallBack(int);
        void XyEvent_init();
        void XyEvent_set(short);
        void XyEvent_exe();
        void SetJointAnimation(int, float, float, int);
        void PlayStopJointAnimation();
        void PlayStopColorAnimation();
        void set_first_stat();
        void set_collision();
        void talk_ct();
        void talk_main();
        void get_tev_material0_color(J3DModelData*, unsigned long, short*, short*, short*);
        void set_tev_color(J3DModelData*, unsigned long, short, short, short);
        void is_brought();
        void set_broughtID(int);
        void set_brought();
        void unset_broughtID(int);
        void unset_brought();
        void get_ftree_info(_ftree_seach_info_*);
        void iam_last();
        void action_none_init(short);
        void action_none_main();
        void action_waitS_init(short);
        void action_waitS_main();
        void action_waitM_init(short);
        void action_waitM_main();
        void action_waitL_init(short);
        void action_waitL_main();
        void action_pikupikuS_init(short);
        void action_pikupikuS_main();
        void action_pikupikuM_init(short);
        void action_pikupikuM_main();
        void action_pikupikuL_init(short);
        void action_pikupikuL_main();
        void action_changeSL_init(short);
        void action_changeSL_main();
        void action_changeSL2_init(short);
        void action_changeSL2_main();
        void action_changeLS_init(short);
        void action_changeLS_main();
        void action_changeLS2_init(short);
        void action_changeLS2_main();
        void action_changeSM_init(short);
        void action_changeSM_main();
        void action_changeMS_init(short);
        void action_changeMS_main();
        void process_init(int, short);
        void process_main();
        void solidHeapCB(fopAc_ac_c*);
        BOOL NodeCallBack_Effect(J3DNode*, int);
        void create_heap();
        s32 _create();
        BOOL _delete();
        void set_mtx();
        BOOL _execute();
        BOOL _draw();
    
    public:
        /* 0x290 */ void* m290;
        /* 0x294 */ s16 m294;
        /* 0x296 */ s16 m296;
        /* 0x298 */ s16 m298;
        /* 0x29A */ s16 m29A;
        /* 0x29C */ request_of_phase_process_class mPhs;
        /* 0x2A4 */ u8 m2A4[0x2A8 - 0x2A4];
        /* 0x2A8 */ Mtx m2A8;
        /* 0x2D8 */ mDoExt_McaMorf* mpMorf;
        /* 0x2DC */ J3DModel* mpModel;
        /* 0x2E0 */ mDoExt_brkAnm mBrkAnm;
        /* 0x2F8 */ cBgS_GndChk mGndChk;
        /* 0x338 */ void* m338;
        /* 0x33C */ u8 m33C[0x344 - 0x33C];
        /* 0x344 */ void* m344;
        /* 0x348 */ u8 m348[0x34C - 0x348];
        /* 0x34C */ f32 m34C;
        /* 0x350 */ s16 mEventCam0Idx;
        /* 0x352 */ s16 mEventCam1Idx;
        /* 0x354 */ s16 mEventCam2Idx;
        /* 0x356 */ s16 m356;
        /* 0x358 */ s16 m358;
        /* 0x35A */ u8 m35A[0x35C - 0x35A];
        /* 0x35C */ dCcD_Stts m35C;
        /* 0x398 */ dCcD_Cyl m398;
        /* 0x4C8 */ f32 m4C8;
        /* 0x4CC */ dCcD_Stts m4CC;
        /* 0x508 */ dCcD_Cyl m508;
        /* 0x638 */ u8 m638[0x64C - 0x638];
        /* 0x64C */ uint mSpawnedHeartPieceProcessId;
        /* 0x650 */ s16 m650;
        /* 0x652 */ s16 m652;
        /* 0x654 */ GXColorS10 m654;
        /* 0x65C */ u8 m65C[0x664 - 0x65C];
        /* 0x664 */ GXColorS10 m664;
        /* 0x66C */ GXColorS10 m66C;
        /* 0x674 */ GXColorS10 m674;
        /* 0x67C */ u8 m67C[0x680 - 0x67C];
        /* 0x680 */ u32 mMode;
        /* 0x684 */ u8 m684[0x696 - 0x684];
        /* 0x696 */ s16 m696;
        /* 0x698 */ s16 m698;
        /* 0x69A */ u8 m69A[0x6A0 - 0x69A];
        /* 0x6A0 */ s16 m6A0;
        /* 0x6A2 */ s16 m6A2;
        /* 0x6A4 */ u8 m6A4[0x6B0 - 0x6A4];
    };
};

#endif /* D_A_OBJ_FTREE_H */
