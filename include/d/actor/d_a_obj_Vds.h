#ifndef D_A_OBJ_VDS_H
#define D_A_OBJ_VDS_H

#include "SSystem/SComponent/c_phase.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class dBgW;
class J3DAnmTevRegKey;
class J3DAnmTransformKey;

namespace daObjVds {
    static void ds_search_switchCB(void*, void*);

    class Act_c : public fopAc_ac_c {
    public:
        virtual ~Act_c() {}

        void is_switch() const {}
    
        void SetLoopJointAnimation(J3DAnmTransformKey*, J3DAnmTransformKey*, float, float);
        void PlayLoopJointAnimation();
        void set_first_process();
        void search_switchCB(fopAc_ac_c*);
        void process_off_init();
        void process_off_main();
        void process_on_init();
        void process_on_main();
        void process_init(int);
        void process_main();
        void process_common();
        void create_point_light(int, cXyz*);
        void execute_point_light();
        void delete_point_light();
        void Event_init();
        void Event_exe();
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        bool _execute();
        bool _draw();
    
    public:
        /* 0x290 */  // vtable
        /* 0x294 */ request_of_phase_process_class mPhs;
        /* 0x29C */ Mtx mMtx;
        /* 0x2CC */ mDoExt_McaMorf* mpMorf0;
        /* 0x2D0 */ J3DAnmTransformKey* mpBck0;
        /* 0x2D4 */ mDoExt_brkAnm mBrk0;
        /* 0x2EC */ J3DAnmTevRegKey* mpBrk0;
        /* 0x2F0 */ mDoExt_McaMorf* mpMorf1;
        /* 0x2F4 */ J3DAnmTransformKey* mpBck1;
        /* 0x2F8 */ mDoExt_brkAnm mBrk1;
        /* 0x310 */ J3DAnmTevRegKey* mpBrk1;
        /* 0x314 */ dBgW* mpBgW;
        /* 0x318 */ int field_0x318;
        /* 0x31C */ int field_0x31C;
        /* 0x320 */ int field_0x320;
        /* 0x324 */ fpc_ProcID field_0x324[2];
        /* 0x32C */ f32 field_0x32C[2];
        /* 0x334 */ s16 field_0x334;
        /* 0x336 */ s16 field_0x336;
        /* 0x338 */ s16 field_0x338;
        /* 0x33A */ u8 field_0x33A[0x33C - 0x33A];
        /* 0x33C */ LIGHT_INFLUENCE mLightInfluence[2];
        /* 0x37C */ cXyz field_0x37C[2];
    };
};

STATIC_ASSERT(sizeof(daObjVds::Act_c) == 0x394);

#endif /* D_A_OBJ_VDS_H */
