#ifndef D_A_NPC_JI1_H
#define D_A_NPC_JI1_H

#include "f_op/f_op_actor.h"

class daNpc_Ji1_c : public fopAc_ac_c {
public:
    void SpRollCutChcek() {}
    void checkAction(int (daNpc_Ji1_c::*)(void*)) {}
    void checkSubAction(int (daNpc_Ji1_c::*)()) {}
    void setAction(int (daNpc_Ji1_c::*)(void*), void*) {}
    void setSubAction(int (daNpc_Ji1_c::*)()) {}

    void isGuardAnim();
    void isAttackAnim();
    void isAttackFrame();
    void isItemWaitAnim();
    void isClearRecord(short);
    void setClearRecord(short);
    void normalSubActionHarpoonGuard(short);
    void normalSubActionGuard(short);
    void normalAction(void*);
    void kaitenExpAction(void*);
    void kaitenspeakAction(void*);
    void kaitenwaitAction(void*);
    void kaitenAction(void*);
    void getMsg1stType();
    void getMsg2ndType();
    void getMsg();
    void next_msgStatus(unsigned long*);
    void talkAction(void*);
    void speakAction(void*);
    void speakBadAction(void*);
    void initPosObject(void*, void*);
    void initPos(int);
    void createItem();
    void set_mtx();
    void getEventActionNo(int);
    void eventAction(void*);
    void evn_init_pos_init(int);
    void evn_setAnm_init(int);
    void evn_talk_init(int);
    void evn_talk();
    void evn_continue_talk_init(int);
    void evn_continue_talk();
    void evn_setAngle_init(int);
    void evn_sound_proc_init(int);
    void evn_head_swing_init(int);
    void evn_harpoon_proc_init(int);
    void evn_RollAtControl_init(int);
    void evn_RollAtControl();
    void evn_game_mode_init(int);
    void evn_turn_to_player();
    void evn_hide_init(int);
    void AnimeControlToWait();
    void privateCut();
    void setParticle(int, float, float);
    void dtParticle();
    void setParticleAT(int, float, float);
    void dtParticleAT();
    void startspeakAction(void*);
    void endspeakAction(void*);
    void reiAction(void*);
    void plmoveAction(void*);
    void teachMove(float);
    void teachSpRollCutMove(float);
    void calcCoCorrectValue();
    void calcBgCorrectValue();
    void MoveToPlayer(float, unsigned char);
    void teachSubActionAttackInit();
    void teachSubActionAttack();
    void teachSubActionJumpInit();
    void teachSubActionJump();
    void teachAction(void*);
    void teachSPRollCutAction(void*);
    void battleGameSetTimer();
    void battleMove(float);
    void battleSubActionWaitInit();
    void battleSubActionWait();
    void battleSubActionNockBackInit(int);
    void battleSubActionNockBack();
    void battleSubActionAttackInit();
    void battleSubActionAttack();
    void battleSubActionTateAttackInit();
    void battleSubActionTateAttack();
    void battleSubActionYokoAttackInit();
    void battleSubActionYokoAttack();
    void battleSubActionJumpInit();
    void battleSubActionJump();
    void battleSubActionDamageInit();
    void battleSubActionDamage();
    void battleSubActionJpGuardInit();
    void battleSubActionJpGuard();
    void battleSubActionGuardInit();
    void battleSubActionGuard();
    void battleAtSet();
    void battleGuardCheck();
    void battleAction(void*);
    void checkCutType(int, int);
    void setAnimFromMsgNo(unsigned long);
    void setAnm(int, float, int);
    void _create();
    void CreateHeap();
    void CreateInit();
    void _delete();
    void _execute();
    void _draw();
    void chkAttention(cXyz, short);
    void lookBack();
    void setHitParticle(cXyz*, unsigned long);
    void setGuardParticle();
    void BackSlideInit();
    void BackSlide(float, float);
    void harpoonRelease(cXyz*);
    void harpoonMove();

public:
    /* 0x290 */ u8 m290[0xD88 - 0x290];
};

#endif /* D_A_NPC_JI1_H */
