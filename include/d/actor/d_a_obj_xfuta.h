#ifndef D_A_OBJ_XFUTA_H
#define D_A_OBJ_XFUTA_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"

namespace daObjXfuta {
	static int tev_mode[] = {
	TEV_TYPE_ACTOR,
    TEV_TYPE_BG0,
    TEV_TYPE_BG1,
    TEV_TYPE_BG2,
    TEV_TYPE_BG3,
    TEV_TYPE_BG0_FULL,
    TEV_TYPE_BG1_FULL,
    TEV_TYPE_BG2_FULL,
    TEV_TYPE_BG3_FULL,
    TEV_TYPE_PLAYER,
    0x5B,
    0x5C,
    0x5D,
    0x5E};
    class Act_c : public fopAc_ac_c {
    public:
		virtual ~Act_c() {}
    	static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        s32 _create();
        bool _delete();
        void set_mtx();
        bool _execute();
        bool _draw();
		s32 Mthd_Delete();
		s32 Mthd_Create();
		s32 Mthd_Execute();
		s32 Mthd_Draw();
		s32 Mthd_IsDelete();
		static const char M_arcname[];
    public:
        /* 0x290 */ //void* vtbl;
        /* 0x294 */ request_of_phase_process_class mPhs;
        /* 0x29C */ J3DModel* mpModel;
   		/* 0x2A0 */ Mtx mMtx;
    };
};
#endif /* D_A_OBJ_XFUTA_H */
