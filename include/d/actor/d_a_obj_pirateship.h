#ifndef D_A_OBJ_PIRATESHIP_H
#define D_A_OBJ_PIRATESHIP_H

#include "f_op/f_op_actor.h"

namespace daObjPirateship {
    class Act_c : public fopAc_ac_c {
    public:
        void _create() {}
        void _delete() {}
        void _draw() {}
        void _execute() {}
        void getKajiID() {}
    
        void set_mtx();
        void pirateCreate(int*);
        void partsCreate();
        void sound_proc();
        void CreateHeap();
        void CreateWave();
        void SetWave();
        void DeleteWave();
        void Create();
        void Execute(float(**)[3][4]);
        void Draw();
        void Delete();
        void demo_move();
    
    public:
        /* 0x290 */ u8 m290[0x2CC - 0x290];
        /* 0x2CC */ u8 m2CC;
        /* 0x2CD */ u8 m2CD[0x2D0 - 0x2CD];
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ u8 m2D4[0x6D4 - 0x2D4];
    };

    static f32 getShipOffsetY(s16*, s16*, f32);
};

#endif /* D_A_OBJ_PIRATESHIP_H */
