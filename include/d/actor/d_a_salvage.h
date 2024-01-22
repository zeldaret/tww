#ifndef D_A_SALVAGE_H
#define D_A_SALVAGE_H

#include "f_op/f_op_actor.h"
#include "d/actor/d_a_oship.h"

class daSalvage_control_c;

class daSalvage_c : public fopAc_ac_c {
public:
    void checkRegist(int) {}
    void checkUsed(int) {}
    void clrFlag(int, unsigned char) {}
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
    void getSalvageId() {}
    void getSalvageKind() {}
    void getSaveNo(int) {}
    void getScale(int) {}
    void getSwitchNo(int) {}
    void getType(int) {}
    void init_one(int) {}
    void isValidSalvageId() {}
    void setDrawMode(int, int) {}
    void setFlag(int, unsigned char) {}
    void setNowAlpha(int, unsigned char) {}
    void setPos(int, cXyz) {}
    void setSRoomNo(signed char) {}
    void setSalvageId(int) {}

    void CreateHeap();
    void CreateInit();
    s32 _create();
    BOOL _delete();
    BOOL _execute();
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
    void getDistance(int, float*);
    void send_agb();
    void debug_print2();
    BOOL _draw();
    void set_mtx(J3DModel*, int);
    void isEffectKind(int);
    void debugDraw();

    static void init_room(signed char);

    static void init() {
        mNowRoomNo = -1;
        mTagData_p = NULL;
        mSalvageId = -1;
    }

    static s8 mNowRoomNo;
    static daSalvage_control_c* mTagData_p;
    static s32 mSalvageId;
    static const u16 m_savelabel[];

public:
    /* Place member variables here */
};

#endif /* D_A_SALVAGE_H */
