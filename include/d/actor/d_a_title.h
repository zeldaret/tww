#ifndef D_A_TITLE_H
#define D_A_TITLE_H

#include "d/d_com_inf_game.h"
#include "d/d_drawlist.h"
#include "f_op/f_op_actor.h"

class daTitle_proc_c : public dDlst_base_c {
public:
    daTitle_proc_c();
    ~daTitle_proc_c();
    void proc_init3D();
    void proc_init2D();
    void setEnterMode();
    void set_mtx();
    void calc_2d_alpha();
    void proc_execute();
    void model_draw();
    void proc_draw();
    inline void draw();
    s32 getEnterMode() { return mEnterMode; }

    static void daTitle_Kirakira_Sound_flag_on();

    static bool daTitle_Kirakira_Sound_flag;
public:
    /* 0x004 */ JPABaseEmitter* mpEmitter;
    /* 0x008 */ JPABaseEmitter* mpEmitter2;
    /* 0x00C */ cXyz m00C;
    /* 0x018 */ s32 m018;
    /* 0x01C */ s32 m01C;
    /* 0x020 */ s32 m020;
    /* 0x024 */ s32 m024;
    /* 0x028 */ s32 m028;
    /* 0x02C */ s32 m02C;
    /* 0x030 */ s32 mEnterMode;
    /* 0x034 */ u8 m034[0x038 - 0x034];
    /* 0x038 */ J3DModel* mModel_ship;
    /* 0x03C */ J3DModel* mModel_subtitle;
    /* 0x040 */ J3DModel* mModel_kirari;
    /* 0x044 */ mDoExt_bckAnm mBckShip;
    /* 0x054 */ mDoExt_bpkAnm mBpkShip;
    /* 0x068 */ mDoExt_btkAnm mBtkSub;
    /* 0x07C */ mDoExt_btkAnm mBtkKirari;
    /* 0x090 */ u8 m090;
    /* 0x094 */ f32 m094;
    /* 0x098 */ s32 m098;
    /* 0x09C */ J2DScreen* m_Screen;
    /* 0x0A0 */ J2DPane* m0A0[6];
    /* 0x0B8 */ fopMsgM_pane_class pane[6];
    /* 0x208 */ JKRExpHeap* m_exp_heap;
    /* 0x20C */ JKRSolidHeap* m_solid_heap;
};

class daTitle_c : public fopAc_ac_c {
public:
    inline ~daTitle_c();

    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ daTitle_proc_c* mpTitleProc;
    /* 0x29C */ bool m29C;
};

#endif /* D_A_TITLE_H */
