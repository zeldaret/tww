#ifndef D_A_NPC_PEOPLE_H
#define D_A_NPC_PEOPLE_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"

struct sUbMsgDat {
    /* 0x00 */ u32 field_0x00;
    /* 0x04 */ u8 field_0x04;
    /* 0x05 */ u8 field_0x05;
    /* 0x06 */ u8 field_0x06;
    /* 0x06 */ u8 field_0x07;
}; // Size: 0x07

struct sPeopleAnmDat {
    /* 0x00 */ u8 field_0x00;
    /* 0x01 */ u8 field_0x01;
    /* 0x02 */ u8 field_0x02;
}; // Size: 0x03

struct daNpcPeople_c__l_npc_dat {
    /* 0x00 */ s16 field_0x00;
    /* 0x02 */ s16 field_0x02;
    /* 0x04 */ s16 field_0x04;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
    /* 0x0E */ s16 field_0x0E;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ s16 field_0x34;
    /* 0x36 */ s16 field_0x36;
    /* 0x38 */ s16 field_0x38;
    /* 0x3A */ s16 field_0x3A;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ s16 field_0x4C;
    /* 0x4E */ s16 field_0x4E;
    /* 0x50 */ s16 field_0x50;
    /* 0x52 */ s16 field_0x52;
    /* 0x54 */ s16 field_0x54;
    /* 0x56 */ s16 field_0x56;
    /* 0x58 */ s16 field_0x58;
    /* 0x5A */ u8 field_0x5A;
    /* 0x5B */ u8 field_0x5B;
    /* 0x5C */ u8 field_0x5C;
    /* 0x5D */ u8 field_0x5D;
    /* 0x5E */ u8 field_0x5E;
    /* 0x5F */ u8 field_0x5F;
}; // Size: 0x60

class daNpcPeople_c : public fopNpc_npc_c {
public:
    enum Prm_e {
        PRM_RAIL_ID_W = 0x8,
        PRM_RAIL_ID_S = 0x10,

        PRM_ARG0_W = 0x8,
        PRM_ARG0_S = 0x0,
    };

    u8 getNpcNo() { return mNpcType; }
    request_of_phase_process_class* getPhaseP() { return &mPhs; }
    void setEtcFlag(u32 flags) { mEtcFlag |= flags; }
    void setResFlag(u8 flag) { mResFlag = flag; }
    void setAnmFlag(u8 flags) { mAnmFlag |= flags; }
    void setTalk(u8) {}
    void setNoTalk(u8) {}
    void setOrderEventNum(u8) {}

    daNpcPeople_c();
    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    bool executeCommon();
    void executeSetMode(u8);
    s32 executeWaitInit();
    void executeWait();
    s32 executeTalkInit();
    void executeTalk();
    s32 executeWalkInit();
    void executeWalk();
    s32 executeTurnInit();
    void executeTurn();
    s32 executeBikkuriInit();
    void executeBikkuri();
    s32 executeFurueInit();
    void executeFurue();
    s32 executeKyoroInit();
    void executeKyoro();
    s32 executeLetterInit();
    void executeLetter();
    s32 executeLookInit();
    void executeLook();
    s32 executeLook2Init();
    void executeLook2();
    s32 executeUgWalkInit();
    void executeUgWalk();
    s32 executeUgTurnInit();
    void executeUgTurn();
    s32 executeUgLookInit();
    void executeUgLook();
    s32 executeUgLook2Init();
    void executeUgLook2();
    s32 executeUgSitInit();
    void executeUgSit();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetTpInit(int);
    void eventMesSetInit(int);
    bool eventMesSet();
    bool eventMesSet2();
    void eventFlagSetInit(int);
    void eventGetItemInit(int);
    bool eventGetItem();
    void eventTurnToPlayerInit();
    bool eventTurnToPlayer();
    void eventUb1TalkInit(int);
    bool eventUb1Talk();
    void eventUb1TalkXyInit(int);
    bool eventUb1TalkXy();
    bool eventUb2Talk();
    bool eventUbSetAnm();
    void eventAreaMaxInit();
    void eventCameraStopInit();
    bool eventCameraStop();
    void eventCameraStartInit();
    void eventCoCylRInit(int);
    bool eventLookPo();
    void eventMesSetPoInit(int);
    bool eventMesSetPo();
    u16 talk2(int, fopAc_ac_c*);
    u16 talk3(int);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    u32 getMsg3();
    void chkMsg();
    void setMessage(u32);
    void setMessageUb(sUbMsgDat*);
    void setAnmFromMsgTag();
    void setAnmFromMsgTagUo(int);
    void setAnmFromMsgTagUb(int);
    void setAnmFromMsgTagUw(int);
    void setAnmFromMsgTagUm(int);
    void setAnmFromMsgTagSa(int);
    void setAnmFromMsgTagUg(int);
    u8 getPrmNpcNo();
    u8 getPrmRailID();
    u8 getPrmArg0();
    void setMtx();
    void chkAttention();
    void lookBack();
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    int getBck(u8);
    int getHeadBck(u8);
    void setAnm(u8, int, f32, f32);
    bool setAnmTbl(sPeopleAnmDat*, int);
    void setWaitAnm();
    s16 XyCheckCB(int);
    s16 XyEventCB(int);
    s16 photoCB(int);
    int getRand(int max);
    BOOL isPhoto(u8);
    BOOL isColor();
    void setCollision(dCcD_Cyl*, cXyz, f32, f32);
    BOOL chkSurprise();
    BOOL chkEndEvent();
    BOOL is1GetMap20();
    BOOL is1DayGetMap20();
    int getWindDir();
    BOOL isUo1FdaiAll();
    BOOL isUo1FdaiOne();
    s32 chkDaiza();
    BOOL checkPig();
    BOOL isPigOk();
    s16 getPigTimer();
    void resetPig();
    void initUgSearchArea();
    cXyz getDirDistToPos(s16, f32);
    void warp();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ request_of_phase_process_class mPhs2;
    /* 0x6D4 */ J3DModel* m6D4;
    /* 0x6D8 */ J3DModel* m6D8;
    /* 0x6DC */ mDoExt_McaMorf* m6DC;
    /* 0x6E0 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x6E4 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F8 */ u32 mShadowId;
    /* 0x6FC */ dNpc_PathRun_c mPathRun;
    /* 0x704 */ u8 m704[0x710 - 0x704];
    /* 0x710 */ cXyz mLookAtPos;
    /* 0x71C */ cXyz m71C;
    /* 0x728 */ sPeopleAnmDat* m728;
    /* 0x72C */ daNpcPeople_c__l_npc_dat* mpNpcDat;
    /* 0x730 */ daNpcPeople_c* m730;
    /* 0x734 */ u32* m734;
    /* 0x738 */ sUbMsgDat* m738;
    /* 0x73C */ sUbMsgDat** m73C;
    /* 0x740 */ f32 m740;
    /* 0x744 */ f32 m744;
    /* 0x748 */ f32 m748;
    /* 0x74C */ f32 m74C;
    /* 0x750 */ f32 m750;
    /* 0x754 */ u8 m754[0x758 - 0x754];
    /* 0x758 */ u32 mEtcFlag;
    /* 0x75C */ int m75C;
    /* 0x760 */ int m760;
    /* 0x764 */ bool m764;
    /* 0x765 */ u8 m765;
    /* 0x766 */ s16 m766[4];
    /* 0x76E */ s16 m76E;
    /* 0x770 */ s16 m770;
    /* 0x772 */ s16 m772;
    /* 0x774 */ s16 m774;
    /* 0x776 */ s16 m776;
    /* 0x778 */ s16 m778;
    /* 0x77A */ s16 m77A;
    /* 0x77C */ u16 m77C;
    /* 0x77E */ u16 m77E;
    /* 0x780 */ s16 m780;
    /* 0x782 */ s16 m782;
    /* 0x784 */ s16 m784;
    /* 0x786 */ s16 m786;
    /* 0x788 */ u8 m788;
    /* 0x789 */ u8 m789;
    /* 0x78A */ u8 m78A;
    /* 0x78B */ u8 m78B;
    /* 0x78C */ u8 m78C;
    /* 0x78D */ u8 m78D;
    /* 0x78E */ u8 m78E;
    /* 0x78F */ u8 m78F;
    /* 0x790 */ u8 mResFlag;
    /* 0x791 */ u8 mNpcType;
    /* 0x792 */ u8 m792;
    /* 0x793 */ u8 m793;
    /* 0x794 */ u8 m794;
    /* 0x795 */ u8 mAnmFlag;
    /* 0x796 */ s8 m796;
    /* 0x797 */ s8 m797;
    /* 0x798 */ u8 m798;
    /* 0x799 */ s8 m799;
    /* 0x79A */ u8 m79A;
    /* 0x79B */ u8 mbIsNight;
    /* 0x79C */ u8 m79C;
    /* 0x79D */ u8 m79D;
    /* 0x79E */ u8 m79E;
    /* 0x79F */ u8 m79F;
    /* 0x7A0 */ u8 m7A0;
    /* 0x7A1 */ u8 m7A1;
    /* 0x7A2 */ u8 m7A2;
    /* 0x7A3 */ s8 m7A3;
    /* 0x7A4 */ u8 m7A4;
    /* 0x7A5 */ u8 m7A5;
    /* 0x7A6 */ u8 m7A6;
    /* 0x7A7 */ u8 m7A7;
    /* 0x7A8 */ u8 m7A8;

    static const char m_arcname[];
}; // Size: 0x7A9

#endif /* D_A_NPC_PEOPLE_H */
