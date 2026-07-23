#ifndef D_A_KAJI_H
#define D_A_KAJI_H

#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Kaji.h"

class mDoExt_McaMorf;

class daKaji_c : public fopAc_ac_c {
public:
    static const char M_arcname[];

    void set_mtx() {
        mpMorf->getModel()->setBaseScale(scale);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(shape_angle);
        mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        MTXCopy(mDoMtx_stack_c::get(), mMtx);
    }
    void setAnm(int i_m668, f32 frame) {
        J3DAnmTransform* pAnimRes;
        void* pSoundAnimRes;
        switch(i_m668 - 9){
            case 0:
                pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes("Kaji",dRes_INDEX_KAJI_BCK_KJ_WAIT_e);
                pSoundAnimRes = dComIfG_getObjectRes("Kaji",dRes_INDEX_KAJI_BAS_KJ_WAIT_e);
                break;
            case 1:
                pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes("Kaji",dRes_INDEX_KAJI_BCK_KJ_OMO_e);
                pSoundAnimRes = dComIfG_getObjectRes("Kaji",dRes_INDEX_KAJI_BAS_KJ_OMO_e);
                break;
            case 2:
                pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes("Kaji",dRes_INDEX_KAJI_BCK_KJ_TORI_e);
                pSoundAnimRes = dComIfG_getObjectRes("Kaji",dRes_INDEX_KAJI_BAS_KJ_TORI_e);
                break;      
            case 3:
                pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes("Kaji",dRes_INDEX_KAJI_BCK_KJ_ANG_e);
                pSoundAnimRes = dComIfG_getObjectRes("Kaji",dRes_INDEX_KAJI_BAS_KJ_ANG_e);
                break;
            default:
                return;
        }
        mpMorf->setAnm(pAnimRes,J3DFrameCtrl::EMode_LOOP,0.0,1.0,0.0,-1.0,pSoundAnimRes);
        if(frame >= 0.0f){
            mpMorf->setFrame(frame);
        }
        return;
    }

    inline cPhs_State _create();
    inline bool _delete();
    inline bool _execute();
    inline bool _draw();

    BOOL CreateHeap();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ u8 pad[0x29C - 0x298];
    /* 0x29C */ mDoExt_McaMorf* mpMorf;
    /* 0x2A0 */ Mtx mMtx;
};

#endif /* D_A_KAJI_H */
