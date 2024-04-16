#ifndef D_A_OBJ_PIRATESHIP_H
#define D_A_OBJ_PIRATESHIP_H

#include "f_op/f_op_actor.h"

namespace daObjPirateship {
    f32 getShipOffsetY(s16*, s16*, f32);
    
    class Act_c : public fopAc_ac_c {
    public:
        inline s32 _create();
        inline BOOL _delete();
        inline BOOL _draw();
        inline BOOL _execute();
        void getKajiID() {}
    
        void set_mtx();
        void pirateCreate(int*);
        void partsCreate();
        void sound_proc();
        void CreateHeap();
        void CreateWave();
        void SetWave();
        void DeleteWave();
        s32 Create();
        void Execute(float(**)[3][4]);
        BOOL Draw();
        BOOL Delete();
        void demo_move();
    
    public:
        /* 0x290 */ u8 m290[0x2CC - 0x290];
        /* 0x2CC */ u8 m2CC;
        /* 0x2CD */ u8 m2CD[0x2CE - 0x2CD];
        /* 0x2CE */ u8 m2CE;
        /* 0x2CF */ u8 m2CF[0x2D0 - 0x2CF];
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ u8 m2D4[0x6D4 - 0x2D4];
    };

    namespace Method {
        s32 Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
    };
};

#endif /* D_A_OBJ_PIRATESHIP_H */
