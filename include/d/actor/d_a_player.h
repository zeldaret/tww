#ifndef D_A_PLAYER
#define D_A_PLAYER

#include "f_op/f_op_actor_mng.h"
#include "d/d_particle.h"
#include "d/d_cc_d.h"

inline u8 dComIfGs_getSelectEquip(int i_no);
inline u8 dComIfGp_getMiniGameType();

class daPy_mtxFollowEcallBack_c : public dPa_levelEcallBack {
public:
    void execute(JPABaseEmitter*);
    void end();
    void makeEmitter(u16, MtxP, const cXyz*, const cXyz*);
    void makeEmitterColor(u16, MtxP, const cXyz*, const GXColor*, const GXColor*);
    void setup(JPABaseEmitter* emitter, const cXyz*, const csXyz*, s8) { mpEmitter = emitter; }

    JPABaseEmitter* getEmitter() { return mpEmitter; }

    /* 0x04 */ JPABaseEmitter* mpEmitter;
    /* 0x08 */ MtxP mpMtx;
};  // Size: 0x0C

STATIC_ASSERT(sizeof(daPy_mtxFollowEcallBack_c) == 0x0C);

// TODO: this probably does not belong in d_a_player.h based on the .text section splitting in d_a_player_main
class daPy_HIO_c {
public:
    // TODO: constructor should be weak, but not inlined?
    // daPy_HIO_c() {}
    daPy_HIO_c();

public:
    /* 0x00 */ u8 temp[0x3F - 0x00];
};  // Size: 0x3F

class daPy_demo_c {
public:
    enum {
        // TODO
        DEMO_LAST_e = 0x4B,
        DEMO_NEW_ANM0_e = 0x200,
    };

    void setDemoType(u16 pType) { mDemoType = pType; }
    int getDemoType() const { return mDemoType; }
    void setDemoMode(u32 mode) { mDemoMode = mode; }
    u32 getDemoMode() const { return mDemoMode; }
    int getParam1() const { return mParam1; }
    void setTimer(s16 time) { mTimer = time; }
    void decTimer() { mTimer--; }
    void setOriginalDemoType() { setDemoType(3); }
    void setSpecialDemoType() { setDemoType(5); }
    void setSystemDemoType() { setDemoType(2); }
    void setStick(f32 stick) { mStick = stick; }
    void setMoveAngle(s16 angle) { mDemoMoveAngle = angle; }
    s16 getMoveAngle() const { return mDemoMoveAngle; }
    f32 getStick() { return mStick; }
    int getParam0() const { return mParam0; }
    void setParam0(int value) { mParam0 = value; }
    void setParam1(int value) { mParam1 = value; }
    void setParam2(int value) { mParam2 = value; }

private:
    /* 0x00 */ u16 mDemoType;
    /* 0x02 */ s16 mDemoMoveAngle;
    /* 0x04 */ s16 mTimer;
    /* 0x06 */ s16 mParam2;
    /* 0x08 */ int mParam0;
    /* 0x0C */ int mParam1;
    /* 0x10 */ u32 mDemoMode;
    /* 0x14 */ f32 mStick;
};  // Size: 0x18

class daPy_py_c : public fopAc_ac_c {
public:
    enum daPy_FLG0 {
        daPyFlg0_UNK4               = 0x00000004,
        daPyFlg0_UNK8               = 0x00000008,
        daPyFlg0_DEKU_SP_RETURN_FLG = 0x00000010,
        daPyFlg0_CUT_AT_FLG         = 0x00000040,
        daPyFlg0_UNK100             = 0x00000100,
        daPyFlg0_SHIP_DROP          = 0x00000200,
        daPyFlg0_PUSH_PULL_KEEP     = 0x00000800,
        daPyFlg0_HOVER_BOOTS        = 0x00001000,
        daPyFlg0_UNK4000            = 0x00004000,
        daPyFlg0_UNK10000           = 0x00010000,
        daPyFlg0_UNK20000           = 0x00020000,
        daPyFlg0_NO_FALL_VOICE      = 0x00040000,
        daPyFlg0_SCOPE_CANCEL       = 0x00080000,
        daPyFlg0_PHOTO_BOX_CANCEL   = 0x00080000, // Same as scope cancel
        daPyFlg0_UNK200000          = 0x00200000,
        daPyFlg0_UNK400000          = 0x00400000,
        daPyFlg0_UNK1000000         = 0x01000000,
        daPyFlg0_EQUIP_HEAVY_BOOTS  = 0x02000000,
        daPyFlg0_NO_DRAW            = 0x08000000,
        daPyFlg0_UNK10000000        = 0x10000000,
        daPyFlg0_UNK20000000        = 0x20000000,
        daPyFlg0_HEAVY_STATE        = 0x40000000,
        daPyFlg0_UNK80000000        = 0x80000000,
    };
    
    enum daPy_FLG1 {
        daPyFlg1_EQUIP_DRAGON_SHIELD    = 0x00000001,
        daPyFlg1_NPC_CALL_COMMAND       = 0x00000002,
        daPyFlg1_UNK4                   = 0x00000004,
        daPyFlg1_CASUAL_CLOTHES         = 0x00000008,
        daPyFlg1_FORCE_VOMIT_JUMP       = 0x00000010,
        daPyFlg1_NPC_NOT_CHANGE         = 0x00000040,
        daPyFlg1_UNK80                  = 0x00000080,
        daPyFlg1_CONFUSE                = 0x00000100,
        daPyFlg1_UNK200                 = 0x00000200,
        daPyFlg1_UNK400                 = 0x00000400,
        daPyFlg1_FREEZE_STATE           = 0x00000800,
        daPyFlg1_SHIP_TACT              = 0x00001000,
        daPyFlg1_USE_ARROW_EFFECT       = 0x00002000,
        daPyFlg1_LETTER_READ_EYE_MOVE   = 0x00004000,
        daPyFlg1_UNK8000                = 0x00008000,
        daPyFlg1_FORCE_VOMIT_JUMP_SHORT = 0x00010000,
        daPyFlg1_FOREST_WATER_USE       = 0x00020000,
        daPyFlg1_UNK40000               = 0x00040000,
        daPyFlg1_WATER_DROP             = 0x00080000,
        daPyFlg1_UNK200000              = 0x00200000,
        daPyFlg1_UNK800000              = 0x00800000,
        daPyFlg1_UNK1000000             = 0x01000000,
        daPyFlg1_VINE_CATCH             = 0x02000000,
        daPyFlg1_UNK8000000             = 0x08000000,
        daPyFlg1_UNK10000000            = 0x10000000,
        daPyFlg1_LAST_COMBO_WAIT        = 0x20000000,
        daPyFlg1_UNK40000000            = 0x40000000,
    };
    
    enum daPy_RFLG0 {
        daPyRFlg0_UNK2                  = 0x00000002,
        daPyRFlg0_ROPE_GRAB_RIGHT_HAND  = 0x00000004,
        daPyRFlg0_GRAB_UP_END           = 0x00000020,
        daPyRFlg0_AUTO_JUMP_LAND        = 0x00000040,
        daPyRFlg0_UNK80                 = 0x00000080,
        daPyRFlg0_UNK200                = 0x00000200,
        daPyRFlg0_RIGHT_FOOT_ON_GROUND  = 0x00000400,
        daPyRFlg0_LEFT_FOOT_ON_GROUND   = 0x00000800,
        daPyRFlg0_FRONT_ROLL_CRASH      = 0x00002000,
        daPyRFlg0_UNK4000               = 0x00004000,
        daPyRFlg0_GRAB_UP_START         = 0x00008000,
        daPyRFlg0_ATTENTION_LOCK        = 0x00010000,
        daPyRFlg0_HAMMER_QUAKE          = 0x00020000,
        daPyRFlg0_UNK80000              = 0x00080000,
        daPyRFlg0_POISON_CURSE          = 0x00100000,
        daPyRFlg0_GRAB_PUT_START        = 0x00400000,
        daPyRFlg0_TACT_USE              = 0x01000000,
        daPyRFlg0_FAIRY_USE             = 0x02000000,
        daPyRFlg0_UNK8000000            = 0x08000000,
        daPyRFlg0_UNK10000000           = 0x10000000,
        daPyRFlg0_ARROW_SHOOT           = 0x20000000,
        // 0x00000001 and 0x00000002 set in daPy_lk_c::dProcLastCombo
        // 0x00001000 set in daPy_lk_c::procCrawlMove_init, checked in checkNoCollisionCorret__9daPy_lk_cFv
        // 0x04000000 set in daPy_lk_c::procShipPaddle
    };
    
    enum daPy_FACE {
        // Index in daPy_lk_c::mTexAnmIndexTable
        daPyFace_TMABAA = 0x00,
        daPyFace_TMABAA_TEUP = 0x01,
        daPyFace_TMABAB = 0x02,
        daPyFace_TMABAC = 0x03,
        daPyFace_TMABACB = 0x04,
        daPyFace_TMABACB_TEDW = 0x05,
        daPyFace_TMABACC = 0x06,
        daPyFace_TMABAD = 0x07,
        daPyFace_TMABAD_TEDW = 0x08,
        daPyFace_TMABAE = 0x09,
        daPyFace_TMABAE_TEUP = 0x0A,
        daPyFace_TMABAE_TEDW = 0x0B,
        daPyFace_TMABAE_TEL = 0x0C,
        daPyFace_TMABAE_TER = 0x0D,
        daPyFace_TMABAF = 0x0E,
        daPyFace_TMABAG = 0x0F,
        daPyFace_TMABAH = 0x10,
        daPyFace_TMABAI = 0x11,
        daPyFace_TMABAJ_TEYORIME = 0x12,
        daPyFace_TMABAD_TWAITPICKUP = 0x13,
        daPyFace_TMABAC_THOOKSHOTJMP = 0x14,
        daPyFace_TGRABP = 0x15,
        daPyFace_TGRABUP = 0x16,
        daPyFace_TGRABNG = 0x17,
        daPyFace_TGRABTHROW = 0x18,
        daPyFace_TGRABRE = 0x19,
        daPyFace_TWALLWL = 0x1A,
        daPyFace_TWALLWR = 0x1B,
        daPyFace_TWALLPL = 0x1C,
        daPyFace_TWALLPR = 0x1D,
        daPyFace_TCUT = 0x1E,
        daPyFace_TCUTEA = 0x1F,
        daPyFace_TCUTEA_TECN = 0x20,
        daPyFace_TEXCA1 = 0x21,
        daPyFace_TEXCB1 = 0x22,
        daPyFace_TJATTACK = 0x23,
        daPyFace_TJATTACK_TEUP = 0x24,
        daPyFace_TCUTTURNP = 0x25,
        daPyFace_TCUTTURN = 0x26,
        daPyFace_TMJMP = 0x27,
        daPyFace_TMJMPC = 0x28,
        daPyFace_TMROLLL = 0x29,
        daPyFace_TMROLLR = 0x2A,
        daPyFace_TMROLLLC = 0x2B,
        daPyFace_TMROLLRC = 0x2C,
        daPyFace_TMSTEPOVER = 0x2D,
        daPyFace_TMSTEPOVERA = 0x2E,
        daPyFace_TMSTEPOVERLAND = 0x2F,
        daPyFace_TATNJL = 0x30,
        daPyFace_TATNJR = 0x31,
        daPyFace_TJMP = 0x32,
        daPyFace_TROLLF = 0x33,
        daPyFace_TROLLB = 0x34,
        daPyFace_TROLLBLAND = 0x35,
        daPyFace_TROLLFMIS = 0x36,
        daPyFace_TFALL = 0x37,
        daPyFace_TLANDDAMA = 0x38,
        daPyFace_TLANDDAMAST = 0x39,
        daPyFace_TDAM = 0x3A,
        daPyFace_TDAMF = 0x3B,
        daPyFace_TDAMFFUP = 0x3C,
        daPyFace_TDAMFBUP = 0x3D,
        daPyFace_TDAMFLUP = 0x3E,
        daPyFace_TDAMFRUP = 0x3F,
        daPyFace_TDAMDASH = 0x40,
        daPyFace_TGUARD = 0x41,
        daPyFace_TSLIDEF = 0x42,
        daPyFace_TSLIDEFLAND = 0x43,
        daPyFace_TSLIDEB = 0x44,
        daPyFace_TSLIDEBLAND = 0x45,
        daPyFace_TSWIMP = 0x46,
        daPyFace_TSWIMING = 0x47,
        daPyFace_TBOOMTHROW = 0x48,
        daPyFace_TBOOMCATCH = 0x49,
        daPyFace_TWALKPUSH = 0x4A,
        daPyFace_TWALKPULL = 0x4B,
        daPyFace_TVJMPCHA = 0x4C,
        daPyFace_TVJMPCL = 0x4D,
        daPyFace_TROPECLIMB = 0x4E,
        daPyFace_TROPEDOWN = 0x4F,
        daPyFace_TLADDERUPST = 0x50,
        daPyFace_TLADDERDWST = 0x51,
        daPyFace_TLADDERUPED = 0x52,
        daPyFace_TLADDERDWED = 0x53,
        daPyFace_THANGING = 0x54,
        daPyFace_THANGUP = 0x55,
        daPyFace_TLAVADAM = 0x56,
        daPyFace_TCUTRE = 0x57,
        daPyFace_TCUTTURNB = 0x58,
        daPyFace_TWAITATOB = 0x59,
        daPyFace_TCOMEOUT = 0x5A,
        daPyFace_THOLDUP = 0x5B,
        daPyFace_TWALLHOLDUP = 0x5C,
        daPyFace_TITEMGET = 0x5D,
        daPyFace_TSALTATION = 0x5E,
        daPyFace_TWHO = 0x5F,
        daPyFace_TPICKUP = 0x60,
        daPyFace_TBOXOPENLINK = 0x61,
        daPyFace_TBOXOPENSHORTLINK = 0x62,
        daPyFace_TDIELONG = 0x63,
        daPyFace_TSWIMDIE = 0x64,
        daPyFace_TSURPRISED = 0x65,
        daPyFace_TTURNBACK = 0x66,
        daPyFace_TLOOKUP = 0x67,
        daPyFace_TWAITQ = 0x68,
        daPyFace_TGLAD = 0x69,
        daPyFace_TCUTBOKO = 0x6A,
        daPyFace_SHIP_JUMP1 = 0x6B,
        daPyFace_SHIP_JUMP2 = 0x6C,
        daPyFace_TUSEFANA = 0x6D,
        daPyFace_TUSEFANB = 0x6E,
        daPyFace_TUSEFANB2 = 0x6F,
        daPyFace_TBOWWAIT = 0x70,
        daPyFace_TVOMITJMP = 0x71,
        daPyFace_TREST = 0x72,
        daPyFace_TTAKE = 0x73,
        daPyFace_TTAKELR = 0x74,
        daPyFace_TSLIPICE = 0x75,
        daPyFace_THAMSWINGA = 0x76,
        daPyFace_THAMSWINGBPRE = 0x77,
        daPyFace_THAMSWINGBHIT = 0x78,
        daPyFace_THAMSWINGBEND = 0x79,
        daPyFace_TSETBOOTS = 0x7A,
        daPyFace_TDOOROPENALINK = 0x7B,
        daPyFace_TDOOROPENBLINK = 0x7C,
        daPyFace_TSEYYES = 0x7D,
        daPyFace_TPRESENTATIONA = 0x7E,
        daPyFace_TWINDL = 0x7F,
        daPyFace_TWINDR = 0x80,
        daPyFace_TPRESENTATIONB = 0x81,
        daPyFace_TBINDRINKPRE = 0x82,
        daPyFace_TBINDRINKING = 0x83,
        daPyFace_TBINDRINKAFTER = 0x84,
        daPyFace_TBINDRINKPRE2 = 0x85,
        daPyFace_TBINDRINKING2 = 0x86,
        daPyFace_TBINDRINKAFTER2 = 0x87,
        daPyFace_TBINOPENPRE = 0x88,
        daPyFace_TBINOPENA = 0x89,
        daPyFace_TBINOPENB = 0x8A,
        daPyFace_TBINSWING = 0x8B,
        daPyFace_TBINGET = 0x8C,
        daPyFace_TARROWRELORD = 0x8D,
        daPyFace_TSURPRISEDB = 0x8E,
        daPyFace_TFAN = 0x8F,
        daPyFace_TNENRIKI = 0x90,
        daPyFace_TMABAB_TEDL = 0x91,
        daPyFace_TMABAH_TABEKOBE = 0x92,
        daPyFace_TSETHYOINOMI = 0x93,
        daPyFace_LINK_FREEZ = 0x94,
        daPyFace_LINK_MOGAKI = 0x95,
        daPyFace_TDAMBIRI = 0x96,
        daPyFace_SALVLR = 0x97,
        daPyFace_SALVWAIT = 0x98,
        daPyFace_SALVBAD = 0x99,
        daPyFace_SALVGOOD = 0x9A,
        daPyFace_SEARESET = 0x9B,
        daPyFace_TWARPIN = 0x9C,
        daPyFace_TWARPOUT = 0x9D,
        daPyFace_TPOWUPWAIT = 0x9E,
        daPyFace_TPOWUP = 0x9F,
        daPyFace_TCUTKESA = 0xA0,
        daPyFace_TWARPOUTFIRST = 0xA1,
        daPyFace_TDASHKAZE = 0xA2,
        daPyFace_TIYAYA = 0xA3,
        daPyFace_TFREEA = 0xA4,
        daPyFace_TFREEB = 0xA5,
        daPyFace_TFREED = 0xA6,
        daPyFace_TTAKTKAZE = 0xA7,
        daPyFace_TTAKTSIPPU = 0xA8,
        daPyFace_TTAKTCHUYA = 0xA9,
        daPyFace_TTAKTFUJIN = 0xAA,
        daPyFace_TTAKTAYATSURI = 0xAB,
        daPyFace_TTAKTCHISIN = 0xAC,
        daPyFace_UNKNOWN = 0xAD, // Not an index, this is a special value checked in checkNormalFace()
    };
    
    /* 0x290 */ u8 mCutType;
    /* 0x291 */ u8 mCutCount;
    /* 0x292 */ u8 field_0x292[0x294 - 0x292];
    /* 0x294 */ s16 mDamageWaitTimer;
    /* 0x296 */ s16 mQuakeTimer;
    /* 0x298 */ int mFace;
    /* 0x29C */ u32 mNoResetFlg0;
    /* 0x2A0 */ u32 mNoResetFlg1;
    /* 0x2A4 */ u32 mResetFlg0;
    /* 0x2A8 */ f32 field_0x2a8;
    /* 0x2AC */ f32 mHeight;
    /* 0x2B0 */ f32 field_0x2b0;
    /* 0x2B4 */ csXyz mBodyAngle;
    /* 0x2BA */ u8 field_0x2BA[0x2BC - 0x2BA];
    /* 0x2BC */ cXyz mHeadTopPos;
    /* 0x2C8 */ cXyz mSwordTopPos;
    /* 0x2D4 */ cXyz mLeftHandPos;
    /* 0x2E0 */ cXyz mRightHandPos;
    /* 0x2EC */ cXyz mRopePos;
    /* 0x2F8 */ cXyz field_0x2f8;
    /* 0x304 */ daPy_demo_c mDemo;
    /* 0x31C */ /* vtable */

    f32 getSpeedF() const { return speedF; }
    u8 getCutType() const { return mCutType; }
    u8 getCutCount() const { return mCutCount; }
    s16 getDamageWaitTimer() const { return mDamageWaitTimer; }
    f32 getHeight() const { return mHeight; }
    s16 getBodyAngleX() const { return mBodyAngle.x; }
    s16 getBodyAngleY() const { return mBodyAngle.y; }
    cXyz getHeadTopPos() const { return mHeadTopPos; }
    cXyz* getHeadTopPosP() { return &mHeadTopPos; }
    cXyz getSwordTopPos() const { return mSwordTopPos;}
    cXyz getLeftHandPos() const { return mLeftHandPos; }
    cXyz getRightHandPos() const { return mRightHandPos; }
    cXyz getRopePos() const { return mRopePos; }
    void getYPos() const {}
    
    void changeDemoMode(u32) {}
    void changeDemoMoveAngle(s16 angle) { mDemo.setMoveAngle(angle); }
    void changeDemoParam0(int) {}
    void changeOriginalDemo() {
        mDemo.setOriginalDemoType();
        mDemo.setParam0(0);
    }
    void cancelOriginalDemo() {}

    void onNoResetFlg0(daPy_FLG0 flag) { mNoResetFlg0 |= flag; }
    void offNoResetFlg0(daPy_FLG0 flag) { mNoResetFlg0 &= ~flag; }
    bool checkNoResetFlg0(daPy_FLG0 flag) const { return mNoResetFlg0 & flag; }
    bool getCutAtFlg() const { return checkNoResetFlg0(daPyFlg0_CUT_AT_FLG); }
    void onPushPullKeep() { onNoResetFlg0(daPyFlg0_PUSH_PULL_KEEP); }
    void offPushPullKeep() { offNoResetFlg0(daPyFlg0_PUSH_PULL_KEEP); }
    bool checkEquipHoverBoots() const { return checkNoResetFlg0(daPyFlg0_HOVER_BOOTS); }
    void onNoFallVoice() { onNoResetFlg0(daPyFlg0_NO_FALL_VOICE); }
    void onScopeCancel() { onNoResetFlg0(daPyFlg0_SCOPE_CANCEL); }
    void onPhotoBoxCancel() { onNoResetFlg0(daPyFlg0_PHOTO_BOX_CANCEL); }
    bool checkEquipHeavyBoots() const { return checkNoResetFlg0(daPyFlg0_EQUIP_HEAVY_BOOTS); }
    void onPlayerNoDraw() { onNoResetFlg0(daPyFlg0_NO_DRAW); }
    void offPlayerNoDraw() { offNoResetFlg0(daPyFlg0_NO_DRAW); }
    void onHeavyState() { onNoResetFlg0(daPyFlg0_HEAVY_STATE); }
    void offHeavyState() { offNoResetFlg0(daPyFlg0_HEAVY_STATE); }
    bool getHeavyState() { return checkNoResetFlg0(daPyFlg0_HEAVY_STATE); }
    bool getHeavyStateAndBoots() { return checkNoResetFlg0(static_cast<daPy_FLG0>(daPyFlg0_HEAVY_STATE | daPyFlg0_EQUIP_HEAVY_BOOTS)); }
    
    void onNoResetFlg1(daPy_FLG1 flag) { mNoResetFlg1 |= flag; }
    void offNoResetFlg1(daPy_FLG1 flag) { mNoResetFlg1 &= ~flag; }
    bool checkNoResetFlg1(daPy_FLG1 flag) const { return mNoResetFlg1 & flag; }
    bool checkEquipDragonShield() const { return checkNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD); }
    void onNpcCallCommand() { onNoResetFlg1(daPyFlg1_NPC_CALL_COMMAND); }
    void onNpcCall() { onNoResetFlg1(daPyFlg1_NPC_CALL_COMMAND); }
    void offNpcCallCommand() { offNoResetFlg1(daPyFlg1_NPC_CALL_COMMAND); }
    bool checkNpcCallCommand() const { return checkNoResetFlg1(daPyFlg1_NPC_CALL_COMMAND); }
    void onForceVomitJump() { onNoResetFlg1(daPyFlg1_FORCE_VOMIT_JUMP); }
    void onNpcNotChange() { onNoResetFlg1(daPyFlg1_NPC_NOT_CHANGE); }
    void offNpcNotChange() { offNoResetFlg1(daPyFlg1_NPC_NOT_CHANGE); }
    bool checkNpcNotChange() const { return checkNoResetFlg1(daPyFlg1_NPC_NOT_CHANGE); }
    void onConfuse() { onNoResetFlg1(daPyFlg1_CONFUSE); }
    void offConfuse() { offNoResetFlg1(daPyFlg1_CONFUSE); }
    bool checkConfuse() const { return checkNoResetFlg1(daPyFlg1_CONFUSE); }
    bool checkFreezeState() const { return checkNoResetFlg1(daPyFlg1_FREEZE_STATE); }
    void onUseArrowEffect() { onNoResetFlg1(daPyFlg1_USE_ARROW_EFFECT); }
    void offUseArrowEffect() { offNoResetFlg1(daPyFlg1_USE_ARROW_EFFECT); }
    void onLetterReadEyeMove() { onNoResetFlg1(daPyFlg1_LETTER_READ_EYE_MOVE); }
    void onForceVomitJumpShort() { onNoResetFlg1(daPyFlg1_FORCE_VOMIT_JUMP_SHORT); }
    bool checkForestWaterUse() const { return checkNoResetFlg1(daPyFlg1_FOREST_WATER_USE); }
    void onWaterDrop() { onNoResetFlg1(daPyFlg1_WATER_DROP); }
    void onVineCatch() { onNoResetFlg1(daPyFlg1_VINE_CATCH); }
    bool checkLastComboWait() const { return checkNoResetFlg1(daPyFlg1_LAST_COMBO_WAIT); }
    
    void onResetFlg0(daPy_RFLG0 flag) { mResetFlg0 |= flag; }
    void offResetFlg0(daPy_RFLG0 flag) { mResetFlg0 &= ~flag; }
    bool checkResetFlg0(daPy_RFLG0 flag) const { return mResetFlg0 & flag; }
    bool getRopeGrabRightHand() const { return checkResetFlg0(daPyRFlg0_ROPE_GRAB_RIGHT_HAND); }
    bool getGrabUpEnd() const { return checkResetFlg0(daPyRFlg0_GRAB_UP_END); }
    bool getAutoJumpLand() const { return checkResetFlg0(daPyRFlg0_AUTO_JUMP_LAND); }
    bool getRightFootOnGround() const { return checkResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND); }
    bool getLeftFootOnGround() const { return checkResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND); }
    bool getFootOnGround() const { return getRightFootOnGround() || getLeftFootOnGround(); }
    bool checkFrontRollCrash() const { return checkResetFlg0(daPyRFlg0_FRONT_ROLL_CRASH); }
    bool getGrabUpStart() const { return checkResetFlg0(daPyRFlg0_GRAB_UP_START); }
    bool checkAttentionLock() const { return checkResetFlg0(daPyRFlg0_ATTENTION_LOCK); }
    bool checkHammerQuake() const { return checkResetFlg0(daPyRFlg0_HAMMER_QUAKE); }
    void onPoisonCurse() { onResetFlg0(daPyRFlg0_POISON_CURSE); }
    bool getGrabPutStart() const { return checkResetFlg0(daPyRFlg0_GRAB_PUT_START); }
    bool checkFairyUse() const { return checkResetFlg0(daPyRFlg0_FAIRY_USE); }
    bool checkTactUse() const { return checkResetFlg0(daPyRFlg0_TACT_USE); }
    bool checkArrowShoot() const { return checkResetFlg0(daPyRFlg0_ARROW_SHOOT); }
    
    bool checkGrabWear() const { return field_0x2b0 < 0.0f; }
    bool checkNormalSwordEquip() const {
        return dComIfGs_getSelectEquip(0) == SWORD ||
            dComIfGp_getMiniGameType() == 2;
    }
    bool checkMasterSwordEquip() const {
        return dComIfGs_getSelectEquip(0) == MASTER_SWORD ||
            dComIfGs_getSelectEquip(0) == LV3_SWORD ||
            dComIfGs_getSelectEquip(0) == MASTER_SWORD_EX;
    }
    void setFace(daPy_FACE face) { mFace = face; }
    
    void checkFinalMasterSwordEquip() const {}
    void checkBowMiniGame() const {}
    void checkSwordMiniGame() const {}
    void checkSoupPowerUp() const {}
    void checkSubjectAccept() const {}
    void checkTactInput() const {}
    void checkUseArrowEffect() const {}
    void getRopeJumpLand() const {}
    void checkRopeForceEnd() const {}
    
    // This class's weak virtual functions tend to cause weak function ordering issues in TUs that use them.
    // The proper way to match this is still unknown, so some of the definitions have been temporarily commented out
    // here so that they can be fakematched instead.
    virtual MtxP getLeftHandMatrix() = 0;
    virtual MtxP getRightHandMatrix() = 0;
    virtual f32 getGroundY() = 0;
    virtual s32 getTactMusic() const;// { return -1; }
    virtual int getTactTimerCancel() const { return 0; }
    virtual BOOL checkPlayerGuard() const { return FALSE; }
    virtual fopAc_ac_c* getGrabMissActor() { return NULL; }
    virtual u32 checkPlayerFly() const;// { return 0; }
    virtual BOOL checkFrontRoll() const { return FALSE; }
    virtual BOOL checkBottleSwing() const { return FALSE; }
    virtual BOOL checkCutCharge() const { return FALSE; }
    virtual BOOL getBokoFlamePos(cXyz*);// { return FALSE; }
    virtual BOOL checkTactWait() const { return FALSE; }
    virtual void setTactZev(uint, int, char*) {}
    virtual void onDekuSpReturnFlg(u8) {}
    virtual BOOL checkComboCutTurn() const { return false; }
    virtual f32 getBaseAnimeFrameRate() = 0;
    virtual f32 getBaseAnimeFrame() = 0;
    virtual uint getItemID() const { return fpcM_ERROR_PROCESS_ID_e; }
    virtual uint getThrowBoomerangID() const { return fpcM_ERROR_PROCESS_ID_e; }
    virtual uint getGrabActorID() const;// { return fpcM_ERROR_PROCESS_ID_e; }
    virtual BOOL checkGrabBarrel() { return FALSE; }
    virtual u32 checkPlayerNoDraw() { return FALSE; }
    virtual BOOL checkRopeTag() { return FALSE; }
    virtual BOOL checkRopeReadyAnime() const { return FALSE; }
    virtual void voiceStart(u32) {}
    virtual void setOutPower(f32, s16, int) {}
    virtual void onFrollCrashFlg(u32);// {}
    virtual MtxP getModelJointMtx(u16) { return NULL; }
    virtual f32 getOldSpeedY() { return 0.0f; }
    virtual BOOL setHookshotCarryOffset(uint, const cXyz*) { return FALSE; }
    virtual void setPlayerPosAndAngle(cXyz*, s16) {}
    virtual void setPlayerPosAndAngle(cXyz*, csXyz*) {}
    virtual void setPlayerPosAndAngle(MtxP) {}
    virtual BOOL setThrowDamage(cXyz*, s16, f32, f32, int) { return FALSE; }
    virtual void changeTextureAnime(u16, u16, int) {}
    virtual void cancelChangeTextureAnime() {}
    
    void changePlayer(fopAc_ac_c*);
    void objWindHitCheck(dCcD_Cyl*);
    void setDoButtonQuake();
    void stopDoButtonQuake(BOOL);
};  // Size: 0x320

#endif /* D_A_PLAYER */
