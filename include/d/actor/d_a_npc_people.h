#ifndef D_A_NPC_PEOPLE_H
#define D_A_NPC_PEOPLE_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"

struct sUbMsgDat {
    
};

struct sPeopleAnmDat {
    
};

struct daNpcPeople_c__l_npc_dat {
    
};

class daNpcPeople_c : public fopAc_ac_c {
public:
    void getNpcNo() {}
    void getPhaseP() {}
    void setAnmFlag(unsigned char) {}
    void setEtcFlag(unsigned long) {}
    void setNoTalk(unsigned char) {}
    void setOrderEventNum(unsigned char) {}
    void setResFlag(unsigned char) {}
    void setTalk(unsigned char) {}

    daNpcPeople_c();
    s32 _create();
    void createHeap();
    void createInit();
    BOOL _delete();
    BOOL _draw();
    BOOL _execute();
    void executeCommon();
    void executeSetMode(unsigned char);
    void executeWaitInit();
    void executeWait();
    void executeTalkInit();
    void executeTalk();
    void executeWalkInit();
    void executeWalk();
    void executeTurnInit();
    void executeTurn();
    void executeBikkuriInit();
    void executeBikkuri();
    void executeFurueInit();
    void executeFurue();
    void executeKyoroInit();
    void executeKyoro();
    void executeLetterInit();
    void executeLetter();
    void executeLookInit();
    void executeLook();
    void executeLook2Init();
    void executeLook2();
    void executeUgWalkInit();
    void executeUgWalk();
    void executeUgTurnInit();
    void executeUgTurn();
    void executeUgLookInit();
    void executeUgLook();
    void executeUgLook2Init();
    void executeUgLook2();
    void executeUgSitInit();
    void executeUgSit();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetTpInit(int);
    void eventMesSetInit(int);
    void eventMesSet();
    void eventMesSet2();
    void eventFlagSetInit(int);
    void eventGetItemInit(int);
    void eventGetItem();
    void eventTurnToPlayerInit();
    void eventTurnToPlayer();
    void eventUb1TalkInit(int);
    void eventUb1Talk();
    void eventUb1TalkXyInit(int);
    void eventUb1TalkXy();
    void eventUb2Talk();
    void eventUbSetAnm();
    void eventAreaMaxInit();
    void eventCameraStopInit();
    void eventCameraStop();
    void eventCameraStartInit();
    void eventCoCylRInit(int);
    void eventLookPo();
    void eventMesSetPoInit(int);
    void eventMesSetPo();
    void talk2(int, fopAc_ac_c*);
    void talk3(int);
    void next_msgStatus(unsigned long*);
    void getMsg();
    void getMsg3();
    void chkMsg();
    void setMessage(unsigned long);
    void setMessageUb(sUbMsgDat*);
    void setAnmFromMsgTag();
    void setAnmFromMsgTagUo(int);
    void setAnmFromMsgTagUb(int);
    void setAnmFromMsgTagUw(int);
    void setAnmFromMsgTagUm(int);
    void setAnmFromMsgTagSa(int);
    void setAnmFromMsgTagUg(int);
    void getPrmNpcNo();
    void getPrmRailID();
    void getPrmArg0();
    void setMtx();
    void chkAttention();
    void lookBack();
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void getBck(unsigned char);
    void getHeadBck(unsigned char);
    void setAnm(unsigned char, int, float, float);
    void setAnmTbl(sPeopleAnmDat*, int);
    void setWaitAnm();
    void XyCheckCB(int);
    void XyEventCB(int);
    void photoCB(int);
    void getRand(int);
    void isPhoto(unsigned char);
    void isColor();
    void setCollision(dCcD_Cyl*, cXyz, float, float);
    void chkSurprise();
    void chkEndEvent();
    void is1GetMap20();
    void is1DayGetMap20();
    void getWindDir();
    void isUo1FdaiAll();
    void isUo1FdaiOne();
    void chkDaiza();
    void checkPig();
    void isPigOk();
    void getPigTimer();
    void resetPig();
    void initUgSearchArea();
    void getDirDistToPos(short, float);
    void warp();

public:
    /* 0x6C4 */ u8 m6C4[0x6CC - 0x6C4];
    /* 0x6CC */ request_of_phase_process_class mPhs;
    /* 0x6D4 */ u8 m6D4[0x6E4 - 0x6D4];
    /* 0x6E4 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F8 */ u8 m6F8[0x6FC - 0x6F8];
    /* 0x6FC */ dNpc_PathRun_c mPathRun;
    /* 0x704 */ u8 m704[0x710 - 0x704];
    /* 0x710 */ cXyz mLookAtPos;
    /* 0x71C */ cXyz m71C;
    /* 0x728 */ u8 m728[0x72C - 0x728];
    /* 0x72C */ daNpcPeople_c__l_npc_dat* mpNpcDat;
    /* 0x730 */ int m730;
    /* 0x734 */ u8 m734[0x738 - 0x734];
    /* 0x738 */ int m738;
    /* 0x73C */ u8 m73C[0x740 - 0x73C];
    /* 0x740 */ f32 m740;
    /* 0x744 */ f32 m744;
    /* 0x748 */ f32 m748;
    /* 0x74C */ f32 m74C;
    /* 0x750 */ u8 m750[0x758 - 0x750];
    /* 0x758 */ u32 m758;
    /* 0x75C */ u8 m75C[0x760 - 0x75C];
    /* 0x760 */ int m760;
    /* 0x764 */ u8 m764;
    /* 0x765 */ u8 m765[0x766 - 0x765];
    /* 0x766 */ s16 m766;
    /* 0x768 */ s16 m768;
    /* 0x76A */ u8 m76A[0x76C - 0x76A];
    /* 0x76C */ s16 m76C;
    /* 0x76E */ s16 m76E;
    /* 0x770 */ u8 m770[0x776 - 0x770];
    /* 0x776 */ s16 m776;
    /* 0x778 */ s16 m778;
    /* 0x77A */ s16 m77A;
    /* 0x77C */ u8 m77C[0x77E - 0x77C];
    /* 0x77E */ u16 m77E;
    /* 0x780 */ u8 m780[0x782 - 0x780];
    /* 0x782 */ s16 m782;
    /* 0x784 */ s16 m784;
    /* 0x786 */ s16 m786;
    /* 0x788 */ u8 m788;
    /* 0x789 */ u8 m789;
    /* 0x78A */ u8 m78A;
    /* 0x78B */ u8 m78B;
    /* 0x78C */ u8 m78C;
    /* 0x78D */ u8 m78D;
    /* 0x78E */ u8 m78E[0x78F - 0x78E];
    /* 0x78F */ u8 m78F;
    /* 0x790 */ u8 m790;
    /* 0x791 */ u8 mNpcType;
    /* 0x792 */ u8 m792[0x793 - 0x792];
    /* 0x793 */ u8 m793;
    /* 0x794 */ u8 m794;
    /* 0x795 */ u8 m795[0x799 - 0x795];
    /* 0x799 */ u8 m799;
    /* 0x79A */ u8 m79A[0x79B - 0x79A];
    /* 0x79B */ bool mbIsNight;
    /* 0x79C */ u8 m79C;
    /* 0x79D */ u8 m79D;
    /* 0x79E */ u8 m79E;
    /* 0x79F */ u8 m79F;
    /* 0x7A0 */ u8 m7A0[0x7A1 - 0x7A0];
    /* 0x7A1 */ u8 m7A1;
    /* 0x7A2 */ u8 m7A2[0x7A6 - 0x7A2];
    /* 0x7A6 */ u8 m7A6;
    /* 0x7A7 */ u8 m7A7[0x7AC - 0x7A7];
};

#endif /* D_A_NPC_PEOPLE_H */
