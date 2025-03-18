#ifndef D_A_OBJ_MKIE_H
#define D_A_OBJ_MKIE_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjMkie {
    class Act_c : public dBgS_MoveBgActor {
    public:
        static u32 prm_make(u8 eventId, int swNo) {
            return swNo << 0x10 | (eventId | 0x3000);
        }
    
        void setup(const cXyz* pos) {
            current.pos = *pos;
            mF58 = 1;
        }
        void attr() const {}
        void prm_get_correct() const {}
        void prm_get_evId() const {}
        void prm_get_swSave() const {}
        void prm_get_type() const {}
    
        virtual BOOL CreateHeap();
        void init_cc();
        void set_cc_pos();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void chk_light();
        void eff_break();
        void sound_melt();
        void sound_break();
        void vib_break();
        void mode_wait();
        void mode_demoWait_init();
        void mode_demoWait();
        void mode_demo_init();
        void mode_demo();
        void mode_proc_call();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* 0x2C8 */ u8 m2C8[0xF58 - 0x2C8];
        /* 0xF58 */ u8 mF58;
        /* 0xF59 */ u8 mF59[0xF64 - 0xF59];
    };
};

#endif /* D_A_OBJ_MKIE_H */
