#ifndef D_A_BRANCH_H
#define D_A_BRANCH_H

#include "f_op/f_op_actor.h"
#include "dolphin/types.h"
#include "d/d_com_inf_game.h"

class daBranch_c : public fopAc_ac_c {
public:
    ~daBranch_c() {
        for (int i = 0; i < 2; i++) {
            mDoExt_McaMorf* anim = mAnims[i];
            if (anim != 0) {
                anim->stopZelAnime();
            }
        }

        dComIfG_resDelete(&mPhs, m_arcname);
    }
    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();

    void set_mtx();
    void set_anim(int, int, int);
    void demoPlay(mDoExt_McaMorf*);

    s32 CreateHeap();
    static BOOL solidHeapCB(fopAc_ac_c*);
    
    MtxP getJointMtx(const char*);

    /* 0x0290 */ request_of_phase_process_class mPhs;
    /* 0x0298 */ J3DModel* mModel[2];
    /* 0x02A0 */ u8 dummy2[0x08];
    /* 0x02A8 */ mDoExt_McaMorf* mAnims[2];
    /* 0x02B0 */ u8 dummy[0x08];
    /* 0x02B8 */ u32 m02B8;
    /* 0x02BC */ u8 m02BC;
    /* 0x02BD */ u8 m02BD;

    static char m_arcname[];
};

#endif /* D_A_BRANCH_H */
