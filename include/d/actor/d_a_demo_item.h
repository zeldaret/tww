#ifndef D_A_DEMO_ITEM_H
#define D_A_DEMO_ITEM_H

#include "d/actor/d_a_itembase.h"
#include "f_op/f_op_actor_mng.h"
#include "SSystem/SComponent/c_lib.h"

class JPABaseEmitter;

class daDitem_c : public daItemBase_c {
public:
    enum ArgFlag {
        FLAG_UNK01 = 0x01,
        FLAG_UNK02 = 0x02,
        FLAG_UNK04 = 0x04,
        FLAG_UNK08 = 0x08,
    };
    
    BOOL chkArgFlag(u8 flag) { return mArgFlag & flag; }
    void clrFlag() { cLib_setBit(mFlag, (u8)0); }
    void setOffsetPos(cXyz pos) { mOffsetPos = pos; }

    static const int m_rot_time;
    static u8 m_effect_type[];

    inline BOOL Delete();
    inline cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();
    inline BOOL isdelete();
    void setParticle();
    bool CreateInit();
    void set_effect();
    void set_pos();
    void anim_control();
    void set_mtx();
    void settingBeforeDraw();
    void setListStart();

public:
    /* 0x63C */ JPABaseEmitter* mpEmitters[4];
    /* 0x64C */ cXyz mOffsetPos;
    /* 0x658 */ u8 mFlag;
    /* 0x659 */ u8 mArgFlag;
};

namespace daDitem_prm {
    inline u32 getNo(daDitem_c* i_this) { return (fopAcM_GetParam(i_this) >> 0x00) & 0xFF; }
    inline u32 getFlag(daDitem_c* i_this) { return (fopAcM_GetParam(i_this) >> 0x10) & 0xFF; }
};

#endif /* D_A_DEMO_ITEM_H */
