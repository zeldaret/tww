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

// Unclear what this is. Only used by one actor (PLAYER)
struct actor_method_class2 {
    /* 0x00 */ actor_method_class base;
    /* 0x20 */ u32 field_0x20;
};

enum fopAc_Status_e {
    // Note: The lowest 5 bits of the status field (& 0x1F) act as an index controlling the map icon type.
    fopAcStts_SHOWMAP_e     = 0x00000020,
    fopAcStts_UNK40_e       = 0x00000040, // Related to talking to the Killer Bees?
    fopAcStts_NOCULLEXEC_e  = 0x00000080,
    fopAcStts_CULL_e        = 0x00000100,
    fopAcStts_FREEZE_e      = 0x00000400,
    fopAcStts_UNK800_e      = 0x00000800,
    fopAcStts_UNK1000_e     = 0x00001000, // Door related
    fopAcStts_CARRY_e       = 0x00002000,
    fopAcStts_UNK4000_e     = 0x00004000,
    fopAcStts_FORCEMOVE_e   = 0x00008000,
    fopAcStts_NOPAUSE_e     = 0x00020000,
    fopAcStts_UNK40000_e    = 0x00040000,
    fopAcStts_UNK80000_e    = 0x00080000, // Hookshot related
    fopAcStts_HOOK_CARRY_e  = 0x00100000,
    fopAcStts_UNK200000_e   = 0x00200000, // Hookshot related
    fopAcStts_NODRAW_e      = 0x01000000,
    fopAcStts_UNK2000000_e  = 0x02000000,
    fopAcStts_BOSS_e        = 0x04000000,
    fopAcStts_UNK8000000_e  = 0x08000000,
    fopAcStts_UNK10000000_e = 0x10000000, // Hookshot related
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
    fopAc_Attn_UNK1000000_e         = 0x01000000,
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
    /* 0x00 */ leaf_process_profile_definition base;
    /* 0x24 */ actor_method_class* sub_method;
    /* 0x28 */ u32 status;
    /* 0x2C */ u8 group;
    /* 0x2D */ u8 cullType;
};  // Size: 0x30

// Unclear what this is. Only appears in 2 profiles (PLAYER,BG)
struct actor_process_profile_definition2 {
    /* 0x00 */ actor_process_profile_definition def;
    /* 0x30 */ u32 field_0x30;
};  // Size: 0x34

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
    dEvtCnd_UNK2_e        = 0x0002,
    dEvtCnd_CANDOOR_e     = 0x0004,
    dEvtCnd_CANGETITEM_e  = 0x0008,
    dEvtCnd_UNK10_e       = 0x0010,
    dEvtCnd_CANTALKITEM_e = 0x0020,
    dEvtCnd_CANCATCH_e    = 0x0040,
};

// TODO: move to d_event.h
class dEvt_info_c {
public:
    typedef s16 (*CallbackFunc)(void*, int);

    dEvt_info_c();
    virtual ~dEvt_info_c() {}
    void setEventName(char*);
    char* getEventName();

    void setToolId(u8 id) { mMapToolId = id; }
    s16 getEventId() { return mEventId; }
    void setEventId(s16 id) { mEventId = id; }

    u16 getCondition() { return mCondition; }
    void setCondition(u16 condition) { mCondition = condition; }
    BOOL chkCondition(u16 condition) { return (mCondition & condition) == condition; }
    void onCondition(u16 cond) { mCondition |= cond; }
    void beforeProc() { mCondition = dEvtCnd_NONE_e; }

    BOOL checkCommandTalk() { return mCommand == dEvtCmd_INTALK_e; }
    BOOL checkCommandItem() { return mCommand == dEvtCmd_INGETITEM_e; }
    BOOL checkCommandDoor() { return mCommand == dEvtCmd_INDOOR_e; }
    BOOL checkCommandDemoAccrpt() { return mCommand == dEvtCmd_INDEMO_e; }
    BOOL checkCommandCatch() { return mCommand == dEvtCmd_INCATCH_e; }
    u16 getCommand() { return mCommand; }
    void setCommand(u16 command) { mCommand = command; }

    void setXyEventCB(CallbackFunc cb) { mpEventCB = cb; }
    s16 runXyEventCB(void* ac, int equippedItemIdx) {
        if (mpEventCB == NULL)
            return -1;
        return mpEventCB(ac, equippedItemIdx);
    }
    void setXyCheckCB(CallbackFunc cb) { mpCheckCB = cb; }
    s16 runXyCheckCB(void* ac, int equippedItemIdx) {
        if (mpCheckCB == NULL)
            return -1;
        return mpCheckCB(ac, equippedItemIdx);
    }
    void setPhotoEventCB(CallbackFunc cb) { mpPhotoCB = cb; }
    s16 runPhotoEventCB(void* ac, int equippedItemIdx) {
        if (mpPhotoCB == NULL)
            return -1;
        return mpPhotoCB(ac, equippedItemIdx);
    }

public:
    /* 0x04 */ u16 mCommand;
    /* 0x06 */ u16 mCondition;
    /* 0x08 */ s16 mEventId;
    /* 0x0A */ u8 mMapToolId;
    /* 0x0B */ s8 mIndex;
    /* 0x0C */ CallbackFunc mpEventCB;
    /* 0x10 */ CallbackFunc mpCheckCB;
    /* 0x14 */ CallbackFunc mpPhotoCB;
};  // Size = 0x18

struct actor_place {
    /* 0x00 */ cXyz pos;
    /* 0x0C */ csXyz angle;
    /* 0x12 */ s8 roomNo;
    /* 0x13 */ u8 field_0x13;
};

struct actor_attention_types {
    /* 0x00 */ u8 distances[8];
    /* 0x08 */ cXyz position;
    /* 0x14 */ u32 flags;
};  // Size = 0x18

class JntHit_c;

struct fopAc_cullSizeSphere {
public:
#ifdef __INTELLISENSE__
    /* 0x0 */ Vec center;
    /* 0xC */ f32 radius;
#else
    /* 0x0 */ cXyz center;
    /* 0xC */ f32 radius;

    fopAc_cullSizeSphere() {}
    fopAc_cullSizeSphere(cXyz p, f32 r) {
        center = p;
        radius = r;
    }
    ~fopAc_cullSizeSphere() {}
#endif
};

struct fopAc_cullSizeBox {
public:
#ifdef __INTELLISENSE__
    /* 0x0 */ Vec min;
    /* 0xC */ Vec max;
#else
    fopAc_cullSizeBox() {}
    fopAc_cullSizeBox(const fopAc_cullSizeBox& box) {
        min = box.min;
        max = box.max;
    }
    fopAc_cullSizeBox(cXyz min, cXyz max) {
        this->min = min;
        this->max = max;
    }
    ~fopAc_cullSizeBox() {}

    /* 0x0 */ cXyz min;
    /* 0xC */ cXyz max;
#endif
};

class fopAc_ac_c : public leafdraw_class {
public:
    /* 0x0C0 */ int actor_type;
    /* 0x0C4 */ create_tag_class actor_tag;
    /* 0x0D8 */ create_tag_class draw_tag;
    /* 0x0EC */ actor_method_class* sub_method;
    /* 0x0F0 */ JKRSolidHeap* heap;
    /* 0x0F4 */ dEvt_info_c eventInfo;
    /* 0x10C */ dKy_tevstr_c tevStr;
    /* 0x1BC */ u16 setID;
    /* 0x1BE */ u8 group;
    /* 0x1BF */ u8 cullType;
    /* 0x1C0 */ u8 demoActorID;
    /* 0x1C1 */ s8 subtype;
    /* 0x1C2 */ u8 gbaName;
    /* 0x1C4 */ u32 actor_status;
    /* 0x1C8 */ u32 actor_condition;
    /* 0x1CC */ uint parentActorID;
    /* 0x1D0 */ actor_place home;
    /* 0x1E4 */ actor_place old;
    /* 0x1F8 */ actor_place current;
    /* 0x20C */ csXyz shape_angle;
    /* 0x214 */ cXyz scale;
    /* 0x220 */ cXyz speed;
    /* 0x22C */ MtxP cullMtx;
    union {
        /* 0x230 */ fopAc_cullSizeBox box;
        /* 0x230 */ fopAc_cullSizeSphere sphere;
    } cull;
    /* 0x248 */ f32 cullSizeFar;
    /* 0x24C */ J3DModel* model;
    /* 0x250 */ JntHit_c* jntHit;
    /* 0x254 */ f32 speedF;
    /* 0x258 */ f32 gravity;
    /* 0x25C */ f32 maxFallSpeed;
    /* 0x260 */ cXyz eyePos;
    /* 0x26C */ actor_attention_types attention_info;
    /* 0x284 */ s8 max_health;
    /* 0x285 */ s8 health;
    /* 0x288 */ s32 itemTableIdx;
    /* 0x28C */ u8 stealItemBitNo; // For limited items (Blue Chu Jelly), this is the first itemBitNo to set.
    /* 0x28D */ s8 stealItemLeft;

    fopAc_ac_c();
    ~fopAc_ac_c();

    static u32 stopStatus;

    static u32 getStopStatus() { return stopStatus; }
    static void setStopStatus(u32 status) { stopStatus = status; }
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
    
    void initBt(f32 height, f32 radius) {
        setBtHeight(height);
        setBtBodyR(radius);
    }
    f32 getBtHeight() const { return mBtHeight; }
    void setBtHeight(f32 height) { mBtHeight = height; }
    f32 getBtBodyR() const { return mBtBodyR; }
    void setBtBodyR(f32 radius) { mBtBodyR = radius; }
    
    void setBtAttackData(f32 startFrame, f32 endFrame, f32 maxDis, u8 attackType) {
        setBtStartFrame(startFrame);
        setBtEndFrame(endFrame);
        setBtMaxDis(maxDis);
        setBtAttackType(attackType);
    }
    f32 getBtStartFrame() const { return mBtStartFrame; }
    void setBtStartFrame(f32 frame) { mBtStartFrame = frame; }
    f32 getBtEndFrame() const { return mBtEndFrame; }
    void setBtEndFrame(f32 frame) { mBtEndFrame = frame; }
    f32 getBtNowFrame() const { return mBtNowFrame; }
    void setBtNowFrame(f32 frame) { mBtNowFrame = frame; }
    u8 getBtAttackType() const { return mBtAttackType; }
    void setBtAttackType(u8 type) { mBtAttackType = type; }
    f32 getBtMaxDis() const { return mBtMaxDis; }
    void setBtMaxDis(f32 dis) { mBtMaxDis = dis; }
    
    /* 0x290 */ f32 mBtHeight;
    /* 0x294 */ f32 mBtBodyR;
    /* 0x298 */ f32 mBtMaxDis;
    /* 0x29C */ f32 mBtStartFrame;
    /* 0x2A0 */ f32 mBtEndFrame;
    /* 0x2A4 */ f32 mBtNowFrame;
    /* 0x2A8 */ u8 mBtAttackType; // Which type of parry opening to give the player
    /* 0x2A9 */ u8 field_2A9[0x2AC - 0x2A9];
};  // Size: 0x2AC

STATIC_ASSERT(sizeof(fopEn_enemy_c) == 0x2AC);

s32 fopAc_IsActor(void* actor);

extern actor_method_class g_fopAc_Method;

#endif
