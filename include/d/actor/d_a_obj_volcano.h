#ifndef D_A_OBJ_VOLCANO_H
#define D_A_OBJ_VOLCANO_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_bg_s_movebg_actor.h"
#include "m_Do/m_Do_ext.h"

class J3DMaterial;

namespace daObjVolcano {
    class Act_c : public dBgS_MoveBgActor {
    public:
        
        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,
        };    

        int prm_get_swSave() const {return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S);}
    
        void StartFire();
        void StopFire();
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void daObjVolcano_fire_demo_wait();
        void daObjVolcano_fire_demo_main();
        void daObjVolcano_fire_main();
        void daObjVolcano_freeze_demo_wait();
        void daObjVolcano_freeze_demo_main();
        void daObjVolcano_freeze_main();
        void daObjVolcano_fail_demo_wait();
        void daObjVolcano_fail_demo_main();
        virtual BOOL Execute(Mtx**);
        void set_material(J3DMaterial*, unsigned char);
        virtual BOOL Draw();
        
        static const char M_arcname[];
    
    public:
        /* Place member variables here */
        /* 0x2C8 */ JPABaseEmitter* field_0x2C8[10];
        /* 0x2F0 */ request_of_phase_process_class field_0x2F0;
        /* 0x2F8 */ J3DModel* field_0x2F8;
        /* 0x2FC */ mDoExt_btkAnm field_0x2FC;
        /* 0x310 */ J3DModel* field_0x310;
        /* 0x314 */ mDoExt_btkAnm field_0x314;
        /* 0x328 */ mDoExt_brkAnm field_0x328;
        /* 0x340 */ dCcD_Stts field_0x340;
        /* 0x37C */ dCcD_Cyl field_0x37C;
        /* 0x4AC */ cXyz field_0x4AC;
        /* 0x4B8 */ cXyz field_0x4B8[4];
        /* 0x4E8 */ int field_0x4E8;
        /* 0x4EC */ f32 field_0x4EC;
        /* 0x4F0 */ f32 field_0x4F0;
        /* 0x4F4 */ char field_0x4F4;
        /* 0x4F5 */ char field_0x4F5;
        /* 0x4F6 */ char field_0x4F6;
        /* 0x4F7 */ char field_0x4F7;
        /* 0x4F8 */ f32 field_0x4F8;
        /* 0x4FC */ s16 field_0x4FC;
        /* 0x4FE */ s16 field_0x4FE;
        /* 0x500 */ int field_0x500;
    };  // Size: 0x504
};

#endif /* D_A_OBJ_VOLCANO_H */
