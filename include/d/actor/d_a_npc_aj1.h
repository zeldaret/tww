#ifndef D_A_NPC_AJ1_H
#define D_A_NPC_AJ1_H

#include "f_op/f_op_actor.h"

class J3DNode;
class JPABaseEmitter;

class daNpc_Aj1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    void _XyCheckCB(int);
    void init_AJ1_0();
    void init_AJ1_1();
    void init_AJ1_2();
    void createInit();
    void play_animation();
    void ctrl_WAITanm();
    void ctrl_TIREanm();
    void setMtx(bool);
    void bckResID(int);
    void btpResID(int);
    void init_texPttrnAnm(signed char, bool);
    void play_texPttrnAnm();
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    void next_msgStatus(unsigned long*);
    void getMsg_AJ1_0();
    void getMsg_AJ1_1();
    void getMsg_AJ1_2();
    void getMsg();
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void chk_parts_notMov();
    void lookBack();
    void chkAttention();
    void setAttention(bool);
    void decideType(int);
    void cut_init_AJ1_TLK();
    void cut_move_AJ1_TLK();
    void cut_init_INI_ANGRY();
    void cut_move_INI_ANGRY();
    void cut_init_VIVRATE();
    void cut_move_VIVRATE();
    void cut_init_JMP();
    void cut_move_JMP();
    void cut_init_SPPRISE();
    void cut_move_SPPRISE();
    void cut_init_LOK();
    void cut_move_LOK();
    void cut_init_DAN();
    void cut_move_DAN();
    void cut_init_INVIT();
    void cut_move_INVIT();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_pa_pun();
    void set_pa_aka();
    void set_pa_don();
    void set_pa_smk();
    void flw_pa_pun();
    void flw_pa_aka();
    void del_pa_aka();
    void del_pa(JPABaseEmitter**);
    void setSmoke();
    void set_action(int (daNpc_Aj1_c::*)(void*), void*);
    void setStt(signed char);
    void chk_areaIN(float, short, cXyz);
    void FARwai();
    void call_1();
    void wait_1();
    void talk_1();
    void wait_action1(void*);
    void wait_action2(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void bodyCreateHeap();
    void itemCreateHeap();
    void CreateHeap();

public:
    /* Place member variables here */
};

class daNpc_Aj1_HIO_c {
public:
    daNpc_Aj1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_AJ1_H */
