#ifndef D_A_SALVAGE_H
#define D_A_SALVAGE_H

#include "f_op/f_op_actor.h"
#include "d/actor/d_a_oship.h"
#include "d/d_salvage.h"

class mDoExt_brkAnm;

class daSalvage_c : public fopAc_ac_c {
    typedef bool (daSalvage_c::*ModeProcFunc)();

public:
    static int getSalvageId() { return mSalvageId; }
    void setSalvageId(int salvageId) { mSalvageId = salvageId; }
    static BOOL isValidSalvageId() {
        if (mSalvageId != -1) {
            return TRUE;
        }
        return FALSE;
    }
    void getSalvageKind() {}
    
    BOOL checkRegist(int arg1) { return mTagData_p->checkRegist(arg1); }
    BOOL checkUsed(int arg1) { return mTagData_p->checkUsed(arg1); }
    void clrFlag(int arg1, u8 arg2) { mTagData_p->clrFlag(arg1, arg2); }
    void debug_print() {}
    void debug_print_reg() {}
    u8* getAlphaP(int arg1) { return mTagData_p->getAlphaPtr(arg1); }
    f32 getDistance_sub(int arg1) { return mTagData_p->getDistance(arg1); }
    s32 getDrawMode(int arg1) { return mTagData_p->getDrawMode(arg1); }
    f32 getH(int arg1) { return mTagData_p->getH(arg1); }
    u8 getItemNo(int arg1) { return mTagData_p->getItemNo(arg1); }
    u8 getKind(int arg1) { return mTagData_p->getKind(arg1); }
    cXyz getPos(int arg1) { return mTagData_p->getPos(arg1); }
    cXyz* getPosP(int arg1) { return mTagData_p->getPosP(arg1); }
    f32 getR(int arg1) { return mTagData_p->getR(arg1); }
    s8 getRoomNo(int arg1) { return mTagData_p->getRoomNo(arg1); }
    s8 getSRoomNo() { return mNowRoomNo; }
    u8 getSaveNo(int arg1) { return mTagData_p->getSaveNo(arg1); }
    cXyz getScale(int arg1) { return mTagData_p->getScale(arg1); }
    s32 getSwitchNo(int arg1) { return mTagData_p->getSwitchNo(arg1); }
    u8 getType(int arg1) { return mTagData_p->getType(arg1); }
    void init_one(int arg1) { mTagData_p->init_one(arg1); }
    void setDrawMode(int arg1, int arg2) { mTagData_p->setDrawMode(arg1, arg2); }
    void setFlag(int arg1, u8 arg2) { mTagData_p->setFlag(arg1, arg2); }
    void setNowAlpha(int arg1, u8 alpha) { mTagData_p->setNowAlpha(arg1, alpha); }
    void setPos(int arg1, cXyz arg2) { mTagData_p->setPos(arg1,arg2); }
    void setSRoomNo(s8 roomNo) { mNowRoomNo = roomNo; }

    f32 GetR(int arg1) { return getR(arg1); }

    BOOL CreateHeap();
    bool CreateInit();
    cPhs_State _create();
    bool _delete();
    bool _execute();
    void checkOrder();
    void eventOrder();
    bool proc_wait_init();
    bool proc_wait();
    bool proc_salvage_init();
    bool proc_salvage();
    void calcAlpha();
    BOOL checkArea(cXyz, int);
    void createEnemy();
    bool onSalvageForOship(daOship_c*);
    bool end_salvage();
    int checkDistance();
    int checkXZDistance();
    BOOL getDistance(int, f32*);
    void send_agb();
    void debug_print2();
    bool _draw();
    void set_mtx(J3DModel*, int);
    BOOL isEffectKind(int);
    void debugDraw();

    static void init_room(s8);

    static void init() {
        mNowRoomNo = -1;
        mTagData_p = NULL;
        mSalvageId = -1;
    }

    static char* m_arcname;
    static const f32 m_outersea_near;
    static const f32 m_inside_near;
    static const f32 m_cmap_near;
    static const u8 m_disappear_frame;
    static const u16 m_savelabel[];
    static dSalvage_control_c* mTagData_p;
    static s8 mNowRoomNo;
    static int mSalvageId;

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModelData* mModelData;
    /* 0x29C */ J3DModel* mModels[16];
    /* 0x2DC */ mDoExt_brkAnm* mpBrk;
    /* 0x2E0 */ mDoExt_btkAnm* mpBtk;
    /* 0x2E4 */ JPABaseEmitter* mEmitter;
    /* 0x2E8 */ s8 m2E8;
    /* 0x2E9 */ u8 m2E9;
    /* 0x2EA */ bool m2EA;
    /* 0x2EC */ u32 m2EC;
    /* 0x2F0 */ s16 mSalvageGetItemEventIdx;
    /* 0x2F2 */ s16 mSalvageHazureEventIdx;
    /* 0x2F4 */ s16 mSlvgGetItemLeftEventIdx;
    /* 0x2F6 */ s16 mEventIdx;
    /* 0x2F8 */ s8 mStayNo;
    /* 0x2FC */ s32 m2FC;
    /* 0x300 */ u8 mRndDepthIdx;
    /* 0x301 */ bool m301;
    /* 0x302 */ u8 m302;
    /* 0x304 */ fpc_ProcID m304;
    /* 0x308 */ ModeProcFunc mProc;
}; // size = 0x314

#endif /* D_A_SALVAGE_H */
