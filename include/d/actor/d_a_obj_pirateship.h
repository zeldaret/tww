#ifndef D_A_OBJ_PIRATESHIP_H
#define D_A_OBJ_PIRATESHIP_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "d/d_bg_s_gnd_chk.h"

class dPath;
class JPABaseEmitter;
class daKnob00_c;

namespace daObjPirateship {
    f32 getShipOffsetY(s16*, s16*, f32);
    
    class Act_c : public dBgS_MoveBgActor {
        struct PirateOffset {
            /* 0x00 */ char* name;
            /* 0x04 */ u32 params;
            /* 0x08 */ Vec pos;
            /* 0x14 */ SVec angle;
            /* 0x1A */ u8 m1A;
        }; // size = 0x1C

        static PirateOffset p_offset[];

    public:
        inline cPhs_State _create();
        inline bool _delete();
        inline bool _draw();
        inline bool _execute();
        void getKajiID() {}
    
        void set_mtx();
        void pirateCreate(int*);
        void partsCreate();
        void sound_proc();
        virtual BOOL CreateHeap();
        void CreateWave();
        void SetWave();
        void DeleteWave();
        virtual BOOL Create();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
        virtual BOOL Delete();
        BOOL demo_move();

        static const char mArcname[];
    
    public:
        /* 0x2C8 */ u8 m2C8[0x2CA - 0x2C8];
        /* 0x2CA */ s16 m2CA;
        /* 0x2CC */ u8 m2CC;
        /* 0x2CD */ u8 m2CD;
        /* 0x2CE */ u8 m2CE;
        /* 0x2CF */ u8 m2CF[0x2D0 - 0x2CF];
        /* 0x2D0 */ J3DModel* mModel;
        /* 0x2D4 */ request_of_phase_process_class mPhase;
        /* 0x2DC */ u8 m2DC[0x2E4 - 0x2DC];
        /* 0x2E4 */ fopAc_ac_c* m2E4;
        /* 0x2E8 */ fpc_ProcID m_sail_id;
        /* 0x2EC */ fopAc_ac_c* m2EC;
        /* 0x2F0 */ fpc_ProcID m2F0;
        /* 0x2F4 */ u8 m2F4[0x2F8 - 0x2F4];
        /* 0x2F8 */ fpc_ProcID m2F8;
        /* 0x2FC */ fopAc_ac_c* m2FC;
        /* 0x300 */ fpc_ProcID m300;
        /* 0x304 */ daKnob00_c* m304;
        /* 0x308 */ fpc_ProcID m308;
        /* 0x30C */ cXyz m30C;
        /* 0x318 */ cXyz m318;
        /* 0x324 */ u8 m324[0x32E - 0x324];
        /* 0x32E */ s16 m32E;
        /* 0x330 */ s16 m330;
        /* 0x332 */ u8 m332[0x338 - 0x332];
        /* 0x338 */ dCcD_Stts m338;
        /* 0x374 */ dCcD_Cyl mCyl;
        /* 0x4A4 */ s8 m4A4;
        /* 0x4A8 */ dPath* m4A8;
        /* 0x4AC */ dPa_trackEcallBack m4AC;
        /* 0x4FC */ JPABaseEmitter* m4FC;
        /* 0x500 */ GXColor m500;
        /* 0x504 */ dBgS_ObjAcch m504;
        /* 0x6C8 */ cXyz m6C8;
    }; // size = 0x6D4

    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_PIRATESHIP_H */
