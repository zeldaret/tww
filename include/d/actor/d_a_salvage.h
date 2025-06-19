#ifndef D_A_SALVAGE_H
#define D_A_SALVAGE_H

#include "f_op/f_op_actor.h"
#include "d/actor/d_a_oship.h"

class dSalvage_control_c;

class daSalvage_c : public fopAc_ac_c {
public:
    static int getSalvageId() { return mSalvageId; }
    void setSalvageId(int) {}
    static BOOL isValidSalvageId() {
        if (mSalvageId != -1) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    void getSalvageKind() {}
    
    void checkRegist(int) {}
    void checkUsed(int) {}
    void clrFlag(int, u8) {}
    void debug_print() {}
    void debug_print_reg() {}
    void getAlphaP(int) {}
    void getDistance_sub(int) {}
    void getDrawMode(int) {}
    void getH(int) {}
    void getItemNo(int) {}
    void getKind(int) {}
    void getPos(int) {}
    void getPosP(int) {}
    void getR(int) {}
    void getRoomNo(int) {}
    void getSRoomNo() {}
    void getSaveNo(int) {}
    void getScale(int) {}
    void getSwitchNo(int) {}
    void getType(int) {}
    void init_one(int) {}
    void setDrawMode(int, int) {}
    void setFlag(int, u8) {}
    void setNowAlpha(int, u8) {}
    void setPos(int, cXyz) {}
    void setSRoomNo(s8) {}

    void CreateHeap();
    void CreateInit();
    cPhs_State _create();
    bool _delete();
    bool _execute();
    void checkOrder();
    void eventOrder();
    void proc_wait_init();
    void proc_wait();
    void proc_salvage_init();
    void proc_salvage();
    void calcAlpha();
    void checkArea(cXyz, int);
    void createEnemy();
    void onSalvageForOship(daOship_c*);
    void end_salvage();
    void checkDistance();
    void checkXZDistance();
    void getDistance(int, f32*);
    void send_agb();
    void debug_print2();
    bool _draw();
    void set_mtx(J3DModel*, int);
    void isEffectKind(int);
    void debugDraw();

    static void init_room(s8);

    static void init() {
        mNowRoomNo = -1;
        mTagData_p = NULL;
        mSalvageId = -1;
    }

    static const u16 m_savelabel[];
    static dSalvage_control_c* mTagData_p;
    static s8 mNowRoomNo;
    static int mSalvageId;

public:
    /* Place member variables here */
};

#endif /* D_A_SALVAGE_H */
