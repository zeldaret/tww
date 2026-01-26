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
    void saku_draw_sub(int);
    void mode_break_none(int);
    void mode_break_fire(int);
    void mode_break_throw_obj(int);
    void RecreateHeap(int, int);
    void CreateHeap(int, int);
    void GetDzbId(int);
    void CreateDummyHeap(int);
    void loadMoveBG(int, int, int);
    void loadModel(int, int, int);
    void burn();
    void broken(int);
    void changeCollision(int);
    void setMtx();
    void setMoveBGMtx();
    void checkCol();
    void setCol();
    void MoveBGResist(int, int);
    void setEffFire(int);
    void setEffBreak(int);

    static const dCcD_SrcCyl m_cyl_src;

public:
    /* 0x290 */ u8 m290[0xEF2 - 0x290];
    /* 0xEF2 */ u8 mSturdinessType;
    /* 0xEF3 */ u8 mEF3[0xF00 - 0xEF3];
    /* 0xF00 */ u32 mBottomHalfDestroyedSwitch;
    /* 0xF04 */ u32 mTopHalfDestroyedSwitch;
};

#endif /* D_A_SAKU_H */
