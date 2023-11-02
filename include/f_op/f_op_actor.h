#ifndef F_OP_ACTOR_H_
#define F_OP_ACTOR_H_

#include "SSystem/SComponent/c_sxyz.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_kankyo.h"
#include "f_pc/f_pc_leaf.h"
#include "global.h"

class J3DModel;

struct actor_method_class {
    /* 0x00 */ leafdraw_method_class base;
    /* 0x14 */ u8 field_0x14[0xC];  // Likely padding
};

enum fopAc_Status_e {
    fopAcStts_SHOWMAP_e     = 0x00000020,
    fopAcStts_NOCULLEXEC_e  = 0x00000080,
    fopAcStts_CULL_e        = 0x00000100,
    fopAcStts_FREEZE_e      = 0x00000400,
    fopAcStts_UNK800_e      = 0x00000800,
    fopAcStts_CARRY_e       = 0x00002000,
    fopAcStts_UNK4000_e     = 0x00004000,
    fopAcStts_NOPAUSE_e     = 0x00020000,
    fopAcStts_UNK40000_e    = 0x00040000,
    fopAcStts_UNK80000_e    = 0x00080000,
    fopAcStts_HOOK_CARRY_e  = 0x00100000,
    fopAcStts_UNK200000_e   = 0x00200000,
    fopAcStts_NODRAW_e      = 0x01000000,
    fopAcStts_UNK2000000_e  = 0x02000000,
    fopAcStts_BOSS_e        = 0x04000000,
    fopAcStts_UNK8000000_e  = 0x08000000,
};

enum fopAc_Condition_e {
    fopAcCnd_NOEXEC_e       = 0x02,
    fopAcCnd_NODRAW_e       = 0x04,
    fopAcCnd_INIT_e         = 0x08,
};

enum fopAc_Group_e {
    fopAc_ACTOR_e,
    fopAc_PLAYER_e,
    fopAc_ENEMY_e,
    fopAc_ENV_e,
    fopAc_NPC_e,
};

enum fopAc_AttentionFlag_e {
    fopAc_Attn_LOCKON_MISC_e        = 0x00000001,
    fopAc_Attn_LOCKON_TALK_e        = 0x00000002,
    fopAc_Attn_LOCKON_ENEMY_e       = 0x00000004,
    fopAc_Attn_ACTION_TALK_e        = 0x00000008,
    fopAc_Attn_ACTION_CARRY_e       = 0x00000010,
    fopAc_Attn_ACTION_DOOR_e        = 0x00000020,
    fopAc_Attn_ACTION_TREASURE_e    = 0x00000040,
    fopAc_Attn_ACTION_SHIP_e        = 0x00000080,
    fopAc_Attn_TALKFLAG_NOTALK_e    = 0x02000000,
    fopAc_Attn_ENEMYFLAG_NOLOCKON_e = 0x04000000,
    fopAc_Attn_TALKFLAG_LOOK_e      = 0x08000000,
    fopAc_Attn_TALKFLAG_CHECK_e     = 0x20000000,
    fopAc_Attn_TALKFLAG_READ_e      = 0x40000000,
};

enum fopAc_Cull_e {
    fopAc_CULLBOX_0_e,
    fopAc_CULLBOX_1_e,
    fopAc_CULLBOX_2_e,
    fopAc_CULLBOX_3_e,
    fopAc_CULLBOX_4_e,
    fopAc_CULLBOX_5_e,
    fopAc_CULLBOX_6_e,
    fopAc_CULLBOX_7_e,
    fopAc_CULLBOX_8_e,
    fopAc_CULLBOX_9_e,
    fopAc_CULLBOX_10_e,
    fopAc_CULLBOX_11_e,
    fopAc_CULLBOX_12_e,
    fopAc_CULLBOX_13_e,
    fopAc_CULLBOX_CUSTOM_e,
    fopAc_CULLSPHERE_0_e,
    fopAc_CULLSPHERE_1_e,
    fopAc_CULLSPHERE_2_e,
    fopAc_CULLSPHERE_3_e,
    fopAc_CULLSPHERE_4_e,
    fopAc_CULLSPHERE_5_e,
    fopAc_CULLSPHERE_6_e,
    fopAc_CULLSPHERE_7_e,
    fopAc_CULLSPHERE_CUSTOM_e,
};

struct actor_process_profile_definition {
    /* 0x00 */ leaf_process_profile_definition mBase;
    /* 0x24 */ actor_method_class* mSubMtd;
    /* 0x28 */ u32 mStatus;
    /* 0x2C */ u8 mGroup;
    /* 0x2D */ u8 mCullType;
};

// Unclear what this is. Only appears in 2 profiles (PLAYER,BG)
struct actor_process_profile_definition2 {
    /* 0x00 */ actor_process_profile_definition def;
    /* 0x30 */ u32 field_0x30;
};

class JKRSolidHeap;

enum dEvt_Command_e {
    dEvtCmd_NONE_e      = 0x0000,
    dEvtCmd_INTALK_e    = 0x0001,
    dEvtCmd_INDEMO_e    = 0x0002,
    dEvtCmd_INDOOR_e    = 0x0003,
    dEvtCmd_INGETITEM_e = 0x0004,
    dEvtCmd_INCATCH_e   = 0x0006,
};

enum dEvt_Condition_e {
    dEvtCnd_NONE_e        = 0x0000,
    dEvtCnd_CANTALK_e     = 0x0001,
    dEvtCnd_CANDOOR_e     = 0x0004,
    dEvtCnd_CANGETITEM_e  = 0x0008,
    dEvtCnd_CANTALKITEM_e = 0x0020,
};

class dEvt_info_c {
public:
    dEvt_info_c();
    virtual ~dEvt_info_c() {}
    void setEventName(char*);
    char* getEventName();
    void beforeProc();

    void setCommand(u16 command) { mCommand = command; }
    void setMapToolId(u8 id) { mMapToolId = id; }
    void setEventId(s16 id) { mEventId = id; }
    void setCondition(u16 condition) { mCondition = condition; }
    u16 getCondition() { return mCondition; }
    //void setArchiveName(char* name) { mArchiveName = name; }
    u8 getMapToolId() { return mMapToolId; }
    s16 getEventId() { return mEventId; }
    s16 getIdx() { return mIndex; }
    void setIdx(u8 i_idx) { mIndex = i_idx; }
    //char* getArchiveName() { return mArchiveName; }
    BOOL chkCondition(u16 condition) { return (mCondition & condition) == condition; }
    void onCondition(u16 cond) { mCondition |= cond; }
    void offCondition(u16 cond) { mCondition &= ~cond; }

    BOOL checkCommandTalk() { return mCommand == dEvtCmd_INTALK_e; }
    BOOL checkCommandItem() { return mCommand == dEvtCmd_INGETITEM_e; }
    BOOL checkCommandDoor() { return mCommand == dEvtCmd_INDOOR_e; }
    BOOL checkCommandDemoAccrpt() { return mCommand == dEvtCmd_INDEMO_e; }
    BOOL checkCommandCatch() { return mCommand == dEvtCmd_INCATCH_e; }

    /* 0x04 */ u16 mCommand;
    /* 0x06 */ u16 mCondition;
    /* 0x08 */ s16 mEventId;
    /* 0x0A */ u8 mMapToolId;
    /* 0x0B */ s8 mIndex;
    /* 0x0C */ s16 (*mpEventCB)(void*, int);
    /* 0x10 */ s16 (*mpCheckCB)(void*, int);
    /* 0x14 */ s16 (*mpPhotoCB)(void*, int);
};  // Size = 0x18

struct actor_place {
    // void operator=(actor_place const&);

    /* 0x00 */ cXyz pos;
    /* 0x0C */ csXyz angle;
    /* 0x12 */ s8 roomNo;
    /* 0x13 */ u8 field_0x13;
};

struct actor_attention_types {
    /* 0x00 */ u8 mDistances[8];
    /* 0x08 */ cXyz mPosition;
    /* 0x14 */ u32 mFlags;
};  // Size = 0x18

class JntHit_c;

struct fopAc_cullSizeSphere {
public:
#ifdef __INTELLISENSE__
    /* 0x0 */ Vec mCenter;
    /* 0xC */ f32 mRadius;
#else
    /* 0x0 */ cXyz mCenter;
    /* 0xC */ f32 mRadius;

    fopAc_cullSizeSphere() {}
    fopAc_cullSizeSphere(cXyz, float);
    ~fopAc_cullSizeSphere() {}
#endif
};

struct fopAc_cullSizeBox {
public:
#ifdef __INTELLISENSE__
    /* 0x0 */ Vec mMin;
    /* 0xC */ Vec mMax;
#else
    fopAc_cullSizeBox() {}
    fopAc_cullSizeBox(const fopAc_cullSizeBox&);
    fopAc_cullSizeBox(cXyz, cXyz);
    ~fopAc_cullSizeBox() {}

    /* 0x0 */ cXyz mMin;
    /* 0xC */ cXyz mMax;
#endif
};

class fopAc_ac_c : public leafdraw_class {
public:
    /* 0x0C0 */ int mAcType;
    /* 0x0C4 */ create_tag_class mAcTg;
    /* 0x0D8 */ create_tag_class mDwTg;
    /* 0x0EC */ actor_method_class* mSubMtd;
    /* 0x0F0 */ JKRSolidHeap* heap;
    /* 0x0F4 */ dEvt_info_c mEvtInfo;
    /* 0x10C */ dKy_tevstr_c mTevStr;
    /* 0x1BC */ u16 mSetId;
    /* 0x1BE */ u8 mGroup;
    /* 0x1BF */ u8 mCullType;
    /* 0x1C0 */ u8 mDemoActorId;
    /* 0x1C1 */ s8 mSubtype;
    /* 0x1C2 */ u8 mGbaName;
    /* 0x1C4 */ u32 mStatus;
    /* 0x1C8 */ u32 mCondition;
    /* 0x1CC */ u32 mParentPcId;
    /* 0x1D0 */ actor_place orig;
    /* 0x1E4 */ actor_place next;
    /* 0x1F8 */ actor_place current;
    /* 0x20C */ csXyz shape_angle;
    /* 0x214 */ cXyz mScale;
    /* 0x220 */ cXyz speed;
    /* 0x22C */ MtxP mCullMtx;
    union {
        /* 0x230 */ fopAc_cullSizeBox mBox;
        /* 0x230 */ fopAc_cullSizeSphere mSphere;
    } mCull;
    /* 0x248 */ f32 mCullSizeFar;
    /* 0x24C */ J3DModel* model;
    /* 0x250 */ JntHit_c* mJntHit;
    /* 0x254 */ f32 speedF;
    /* 0x258 */ f32 mGravity;
    /* 0x25C */ f32 mMaxFallSpeed;
    /* 0x260 */ cXyz mEyePos;
    /* 0x26C */ actor_attention_types mAttentionInfo;
    /* 0x284 */ s8 mMaxHealth;
    /* 0x285 */ s8 mHealth;
    /* 0x288 */ s32 mItemTableIdx;
    /* 0x28C */ u8 mItemStealNum;
    /* 0x28D */ s8 mItemStealLeft;

    fopAc_ac_c();
    ~fopAc_ac_c();

    static u32 stopStatus;

    const cXyz& getPosition() const { return current.pos; }
    cXyz* getPositionP() { return &current.pos; }
    const csXyz& getAngle() const { return current.angle; }
};  // Size: 0x290

STATIC_ASSERT(sizeof(fopAc_ac_c) == 0x290);

class fopEn_enemy_c : public fopAc_ac_c {
public:
    enum ParryOpeningType {
        OPENING_NONE = 0,
        OPENING_JUMP_PARRY = 1,
        OPENING_ROLL_PARRY = 2,
        OPENING_VERTICAL_JUMP_PARRY = 3,
        OPENING_GANONDORF_FINISHER_PARRY = 4,
    };
    
    /* 0x290 */ f32 m290;
    /* 0x294 */ f32 m294;
    /* 0x298 */ f32 m298;
    /* 0x29C */ f32 m29C;
    /* 0x2A0 */ f32 m2A0;
    /* 0x2A4 */ f32 m2A4;
    /* 0x2A8 */ u8 mCurrParryOpeningType;
    /* 0x2A9 */ u8 field_2A9[0x2AC - 0x2A9];
};

STATIC_ASSERT(sizeof(fopEn_enemy_c) == 0x2AC);

s32 fopAc_IsActor(void* actor);

extern actor_method_class g_fopAc_Method;

#endif
