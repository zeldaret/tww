#ifndef D_A_OBJ_MAGMAROCK_H
#define D_A_OBJ_MAGMAROCK_H

#include "f_op/f_op_actor.h"

class dBgW;

namespace daObjMagmarock {
    static void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
    static BOOL CheckCreateHeap(fopAc_ac_c*);

    class Act_c : public fopAc_ac_c {
    public:
        typedef void (Act_c::*ProcFunc)();

        virtual BOOL LiftUpRequest(cXyz&);
        virtual BOOL BeforeLiftRequest(cXyz&);
        inline cPhs_State _create();
        inline bool _delete();
        inline bool _draw();
        inline bool _execute();
        inline BOOL checkProcess(ProcFunc);
        inline f32 getMagmaY(cXyz*);
        void setProcess(ProcFunc func) { field_0x2E0 = func; }

        void set_mtx();
        void demo_move();
        void ControlEffect();
        void play_anim();
        void appear_proc_init();
        void appear_proc();
        void wait_proc_init();
        void wait_proc();
        void stay_proc_init();
        void stay_proc();
        void quake_proc_init();
        void quake_proc();
        void vanish_proc_init();
        void vanish_proc();
        int CreateHeap();
        BOOL CreateInit();
        void calc_ground_quat();
        static const char M_arcname[];
        static GXColor default_color;
    public:
        /* 0x294 */ u8 padding[0x298 - 0x294];
        /* 0x298 */ s16 field_0x298;
        /* 0x29A */ s16 field_0x29A;
        /* 0x29C */ s16 field_0x29C;
        /* 0x29E */ u8 field_0x29E;
        /* 0x29F */ u8 field_0x29F;
        /* 0x2A0 */ JPABaseEmitter* field_0x2A0;
        /* 0x2A4 */ JPABaseEmitter* field_0x2A4;
        /* 0x2A8 */ JPABaseEmitter* field_0x2A8;
        /* 0x2AC */ JPABaseEmitter* field_0x2AC;
        /* 0x2B0 */ Quaternion field_0x2B0;
        /* 0x2C0 */ Quaternion field_0x2C0;
        /* 0x2D0 */ Quaternion field_0x2D0;
        /* 0x2E0 */ ProcFunc field_0x2E0;
        /* 0x2EC */ request_of_phase_process_class field_0x2EC;
        /* 0x2F4 */ J3DModel* model;
        /* 0x2F8 */ J3DAnmTevRegKey* M_brk;
        /* 0x2FC */ mDoExt_brkAnm field_0x2FC;
        /* 0x314 */ J3DAnmTransform* M_bck;
        /* 0x318 */ mDoExt_bckAnm field_0x318;
        /* 0x328 */ Mtx field_0x328;
        /* 0x358 */ dBgW* field_0x358;
        /* 0x35C */ dKy_tevstr_c field_0x35C;
        /* 0x40C */ cXyz field_0x40C[3];
        /* 0x430 */ f32 field_0x430;
        /* 0x434 */ f32 field_0x434;
        /* 0x438 */ f32 field_0x438;
        /* 0x43C */ cXyz field_0x43C;
        /* 0x448 */ int field_0x448;
        /* 0x44C */ int field_0x44C;
        /* 0x450 */ s32 field_0x450;
        /* 0x454 */ s16 field_0x454;
        /* 0x456 */ s16 field_0x456;
        /* 0x458 */ s16 field_0x458;
        /* 0x45A */ s16 field_0x45A;
        /* 0x45C */ s16 field_0x45C;
        /* 0x45E */ s16 field_0x45E;
    }; // Size: 0x460
    
    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_MAGMAROCK_H */
