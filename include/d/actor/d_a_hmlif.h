#ifndef D_A_HMLIF_H
#define D_A_HMLIF_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_cc_d.h"

class mDoExt_btpAnm;
class mDoExt_brkAnm;
class dPath;

class daHmlif_c : public dBgS_MoveBgActor {
public:
    virtual BOOL Delete();
    BOOL daHmlifDelete();
    virtual BOOL CreateHeap();
    virtual BOOL Create();
    cPhs_State daHmlifCreate();
    void set_mtx();
    virtual BOOL Execute(Mtx**);
    void move();
    void set_se();
    void anim_play();
    void check_col();
    void lift_smooth_move();
    void lift_normal_move();
    BOOL check_path_point(cXyz, cXyz, cXyz, s8);
    void set_next_pnt();
    BOOL setNextPath();
    bool chkSwitchPathType();
    virtual BOOL Draw();

    static char* m_arcname[];
    static const f32 m_speed[];
    static const s16 m_bmdidx[];
    static const s16 m_dzbidx[];
    static const s16 m_btpidx[];
    static const s16 m_brkidx[];
    static const f32 m_cull_box[][6];
    static const s16 m_heapsize[];

public:
    /* 0x2C8 */ request_of_phase_process_class mPhase;
    /* 0x2D0 */ J3DModel* mpModel;
    /* 0x2D4 */ mDoExt_btpAnm* mpBtp;
    /* 0x2D8 */ mDoExt_brkAnm* mpBrk;
    /* 0x2DC */ dCcD_Sph mSph;
    /* 0x408 */ dCcD_Stts mStts;
    /* 0x444 */ u8 m444;
    /* 0x445 */ u8 m445;
    /* 0x446 */ s8 m446;
    /* 0x447 */ s8 m447;
    /* 0x448 */ s8 m448;
    /* 0x449 */ u8 m449[0x44C - 0x449];
    /* 0x44C */ dPath* ppd;
    /* 0x450 */ cXyz m450;
    /* 0x45C */ cXyz m45C;
    /* 0x468 */ cXyz m468;
    /* 0x474 */ s32 m474;
    /* 0x478 */ u32 m478;
    /* 0x47C */ u8 m47C[0x47E - 0x47C];
    /* 0x47E */ bool m47E;
    /* 0x47F */ u8 m47F[0x480 - 0x47F];
    /* 0x480 */ f32 m480;
    /* 0x484 */ s32 m484;
    /* 0x488 */ u8 m488;
    /* 0x489 */ u8 m489;
    /* 0x48A */ s16 m48A;
}; // size = 0x48C

#endif /* D_A_HMLIF_H */
