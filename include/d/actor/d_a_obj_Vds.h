#ifndef D_A_OBJ_VDS_H
#define D_A_OBJ_VDS_H

#include "d/d_a_obj.h"
#include "d/d_bg_w.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"

class J3DAnmTransformKey;

namespace daObjVds {
    static void* ds_search_switchCB(void*, void*);

    class Act_c : public fopAc_ac_c {
    public:
        // Enums, Structs, Types
        typedef BOOL (daObjVds::Act_c::*procInitFun_t)();   
        typedef void (daObjVds::Act_c::*procMainFun_t)();

        enum Prm_e {
            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 0,
        };

        

        // Globals variables
        static const char M_arcname[4];
        
        // Methods
        bool is_switch() {
            return fopAcM_isSwitch(this, daObj::PrmAbstract(this, 8, 0));
        }

        virtual ~Act_c() {};
    
        BOOL SetLoopJointAnimation(J3DAnmTransformKey*, J3DAnmTransformKey*, float, float);
        bool PlayLoopJointAnimation();
        void set_first_process();
        void* search_switchCB(fopAc_ac_c*);
        BOOL process_off_init();
        void process_off_main();
        BOOL process_on_init();
        void process_on_main();
        BOOL process_init(int);
        void process_main();
        void process_common();
        void create_point_light(int, cXyz*);
        void execute_point_light();
        void delete_point_light();
        void Event_init();
        void Event_exe();
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        bool _execute();
        bool _draw();
    
    public:
        /* 0x294 */ request_of_phase_process_class mPhs;
        /* 0x29C */ Mtx m29C;
        /* 0x2CC */ mDoExt_McaMorf* M_anm0;
        /* 0x2D0 */ J3DAnmTransformKey* M_bck_data0;
        /* 0x2D4 */ mDoExt_brkAnm mBrkAnm0;
        /* 0x2EC */ J3DAnmTevRegKey* M_brk_data0;
        /* 0x2F0 */ mDoExt_McaMorf* M_anm1;
        /* 0x2F4 */ J3DAnmTransformKey* M_bck_data1;
        /* 0x2F8 */ mDoExt_brkAnm mBrkAnm1;
        /* 0x310 */ J3DAnmTevRegKey* M_brk_data1;
        /* 0x314 */ dBgW* m314;
        /* 0x318 */ u32 m318;
        /* 0x31C */ s32 mSide;
        /* 0x320 */ s32 m320;
        /* 0x324 */ fpc_ProcID m324[2];
        /* 0x32C */ f32 m32C[2];
        /* 0x334 */ s16 mEventIdx;
        /* 0x336 */ s16 m336;
        /* 0x338 */ u16 m338;
        /* 0x33A */ u16 m33A;
        /* 0x33C */ LIGHT_INFLUENCE m33C[2];
        /* 0x37C */ cXyz m37C[2];
    }; // Size : 0x394
};

#endif /* D_A_OBJ_VDS_H */
