#ifndef D_A_SAKU_H
#define D_A_SAKU_H

#include "f_op/f_op_actor.h"

class dCcD_SrcCyl;

class daSaku_c : public fopAc_ac_c {
public:
    void chkFlag(unsigned char) {}
    void setFlag(unsigned char) {}

    inline cPhs_State _daSaku_create();
    inline BOOL _daSaku_delete();
    inline BOOL _daSaku_draw();
    inline BOOL _daSaku_execute();
    inline BOOL _daSaku_isdelete();

    void CreateInit();
    BOOL saku_draw_sub(int);
    BOOL mode_break_none(int);
    BOOL mode_break_fire(int);
    BOOL mode_break_throw_obj(int);
    BOOL RecreateHeap(int, int);
    BOOL CreateHeap(int, int);
    s32 GetDzbId(int);
    BOOL CreateDummyHeap(int);
    BOOL loadMoveBG(int, int, int);
    BOOL loadModel(int, int, int);
    BOOL burn();
    BOOL broken(int);
    BOOL changeCollision(int);
    void setMtx();
    void setMoveBGMtx();
    void checkCol();
    void setCol();
    BOOL MoveBGResist(int, int);
    BOOL setEffFire(int);
    BOOL setEffBreak(int);

    static const dCcD_SrcCyl m_cyl_src;
    static u8 dust_color[4];
    static const char* m_arcname[3];
    static s32 m_saku_alpha_out_time;
    static s32 m_max_particle_timer;
    static u8 m_smoke_alpha;
    static s32 m_alpha_start_time;
    static s32 m_fade_time;

public:
    /* 0x290 */ u8 m290[0xEF2 - 0x290];
    /* 0xEF2 */ u8 mSturdinessType;
    /* 0xEF3 */ u8 mEF3[0xF00 - 0xEF3];
    /* 0xF00 */ u32 mBottomHalfDestroyedSwitch;
    /* 0xF04 */ u32 mTopHalfDestroyedSwitch;
};

#endif /* D_A_SAKU_H */
