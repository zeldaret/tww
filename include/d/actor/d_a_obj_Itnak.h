#ifndef D_A_OBJ_ITNAK_H
#define D_A_OBJ_ITNAK_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_gnd_chk.h"

namespace daObjItnak {
    class Act_c : public fopAc_ac_c {
    public:
        virtual ~Act_c() {}
        static BOOL solidHeapCB(fopAc_ac_c*);
        BOOL create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        BOOL set_co_se(dCcD_Cyl*);
        void manage_draw_flag();
        void set_collision();
        bool _execute();
        bool _draw();
        struct Attr_c {
          /* 0x00 */ f32 cyl1_r;
          /* 0x04 */ f32 cyl1_h;
          /* 0x08 */ f32 cyl2_r;
          /* 0x0C */ f32 cyl2_h;
          /* 0x10 */ f32 cyl2_pos_x;
          /* 0x14 */ f32 cyl2_pos_y;
          /* 0x18 */ f32 cyl2_pos_z;
          /* 0x1C */ f32 cyl3_r;
          /* 0x20 */ f32 cyl3_h;
          /* 0x24 */ f32 cyl3_pos_x;
          /* 0x28 */ f32 cyl3_pos_y;
          /* 0x2C */ f32 cyl3_pos_z;
        };
        static const char M_arcname[];
        enum Prm_e {
          PRM_STATE_W = 8,
          PRM_STATE_S = 0,
          PRM_SWSAVE_W = 8,
          PRM_SWSAVE_S = 8,
        };
    public:
    // /* 0x290 */ void* mpVtbl;
    /* 0x294 */ request_of_phase_process_class mPhase;
    /* 0x29C */ J3DModel* mpModel;
    /* 0x2A0 */ Mtx mMtx;
    /* 0x2D0 */ u32 mShadowId;
    /* 0x2D4 */ dBgS_ObjGndChk mFloorPoly;
    /* 0x328 */ f32 mGroundY;
    /* 0x32C */ dCcD_Stts mStts1;
    /* 0x368 */ dCcD_Cyl mCyl1;
    /* 0x498 */ dCcD_Stts mStts2;
    /* 0x4D4 */ dCcD_Cyl mCyl2;
    /* 0x604 */ dCcD_Stts mStts3;
    /* 0x640 */ dCcD_Cyl mCyl3;
    /* 0x770 */ int mInitVisible;
    /* 0x774 */ int mVisible;
  // Size: 0x778
  private:
  static const Attr_c L_attr;
};
};

#endif /* D_A_OBJ_ITNAK_H */
