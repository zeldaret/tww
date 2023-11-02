/**
 * d_a_player_main.cpp
 * 
 * Main file for the Link (Player) actor.
 * 
 * Much of Link's code is spread across various `.inc` files and included directly
 * into this one to make the file size more managable.
 * The original split locations are indicated in the map file.
*/

#include "d/actor/d_a_player_main.h"
#include "d/d_com_inf_game.h"
#include "d/d_com_lib_game.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "d/d_procname.h"
#include "d/d_kankyo.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/actor/d_a_itembase.h"
#include "d/d_item_data.h"

#include "d/actor/d_a_player_HIO.inc"

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};

char l_arcName[] = "Link";

char l_tact_event_label[] = "OPTION_CHAR_START";
char l_tact_night_event_label[] = "TIMEWARP";
char l_tact_wind_change_event_label[] = "TACT_WINDOW2";
char l_tact_wind_change_event_label2[] = "TACT_WINDOW2_SHIP";

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt Type     */ 0,
        /* SrcObjAt Atp      */ 0,
        /* SrcObjAt SPrm     */ 0,
        /* SrcObjTg Type     */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_LEAF_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
        /* SrcObjTg SPrm     */ 0x05,
        /* SrcObjCo SPrm     */ 0x73,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt GFlag   */ 0,
        /* SrcGObjTg Se      */ 0x25,
        /* SrcGObjTg HitMark */ 0x0C,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg GFlag   */ 0,
        /* SrcGObjCo GFlag   */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 30.0f,
        /* Height */ 125.0f,
    },
};

static dCcD_SrcCyl l_wind_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt Type     */ 0,
        /* SrcObjAt Atp      */ 0,
        /* SrcObjAt SPrm     */ 0,
        /* SrcObjTg Type     */ AT_TYPE_LEAF_WIND,
        /* SrcObjTg SPrm     */ 0x05,
        /* SrcObjCo SPrm     */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt GFlag   */ 0x02,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg GFlag   */ 0,
        /* SrcGObjCo GFlag   */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 30.0f,
        /* Height */ 125.0f,
    },
};

static dCcD_SrcCyl l_at_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt Type     */ AT_TYPE_SWORD,
        /* SrcObjAt Atp      */ 0x02,
        /* SrcObjAt SPrm     */ 0x0B,
        /* SrcObjTg Type     */ 0,
        /* SrcObjTg SPrm     */ 0,
        /* SrcObjCo SPrm     */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0x0F,
        /* SrcGObjAt Spl     */ 0x01,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt GFlag   */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg GFlag   */ 0,
        /* SrcGObjCo GFlag   */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 180.0f,
        /* Height */ 75.0f,
    },
};

static dCcD_SrcCps l_at_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt Type     */ AT_TYPE_SWORD,
        /* SrcObjAt Atp      */ 0x01,
        /* SrcObjAt SPrm     */ 0x0B,
        /* SrcObjTg Type     */ 0,
        /* SrcObjTg SPrm     */ 0,
        /* SrcObjCo SPrm     */ 0,
        /* SrcGObjAt Se      */ 0x01,
        /* SrcGObjAt HitMark */ 0x0D,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt GFlag   */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg GFlag   */ 0,
        /* SrcGObjCo GFlag   */ 0,
    },
    // cM3dGCpsS
    {
        /* Start  */ 0.0f, 0.0f, 0.0f,
        /* End    */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 20.0f,
    },
};

static dCcD_SrcCps l_fan_wind_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt Type     */ AT_TYPE_LEAF_WIND,
        /* SrcObjAt Atp      */ 0,
        /* SrcObjAt SPrm     */ 0x0B,
        /* SrcObjTg Type     */ 0,
        /* SrcObjTg SPrm     */ 0,
        /* SrcObjCo SPrm     */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt GFlag   */ 0x02,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg GFlag   */ 0,
        /* SrcGObjCo GFlag   */ 0,
    },
    // cM3dGCpsS
    {
        /* Start  */ 0.0f, 0.0f, 0.0f,
        /* End    */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 70.0f,
    },
};

static dCcD_SrcSph l_fan_wind_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt Type     */ AT_TYPE_LEAF_WIND,
        /* SrcObjAt Atp      */ 0,
        /* SrcObjAt SPrm     */ 0x0B,
        /* SrcObjTg Type     */ 0,
        /* SrcObjTg SPrm     */ 0,
        /* SrcObjCo SPrm     */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt GFlag   */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg GFlag   */ 0,
        /* SrcGObjCo GFlag   */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 150.0f,
    },
};

daPy_lk_c::ProcInitTableEntry daPy_lk_c::mProcInitTable[0xDB] = {
    /* 0x00 */ {&daPy_lk_c::procScope,                 0x00000001},
    /* 0x01 */ {&daPy_lk_c::procSubjectivity,          0x20001005},
    /* 0x02 */ {&daPy_lk_c::procCall,                  0x00000181},
    /* 0x03 */ {&daPy_lk_c::procControllWait,          0x00000001},
    /* 0x04 */ {&daPy_lk_c::procWait,                  0x000211C5},
    /* 0x05 */ {&daPy_lk_c::procFreeWait,              0x00020445},
    /* 0x06 */ {&daPy_lk_c::procMove,                  0x000211C4},
    /* 0x07 */ {&daPy_lk_c::procAtnMove,               0x000211C4},
    /* 0x08 */ {&daPy_lk_c::procAtnActorWait,          0x000211C5},
    /* 0x09 */ {&daPy_lk_c::procAtnActorMove,          0x000211C4},
    /* 0x0A */ {&daPy_lk_c::procSideStep,              0x000014C6},
    /* 0x0B */ {&daPy_lk_c::procSideStepLand,          0x000010C5},
    /* 0x0C */ {&daPy_lk_c::procCrouchDefense,         0x68800101},
    /* 0x0D */ {&daPy_lk_c::procCrouchDefenseSlip,     0x60800400},
    /* 0x0E */ {&daPy_lk_c::procCrouch,                0x00800101},
    /* 0x0F */ {&daPy_lk_c::procCrawlStart,            0x03008100},
    /* 0x10 */ {&daPy_lk_c::procCrawlMove,             0x0B008100},
    /* 0x11 */ {&daPy_lk_c::procCrawlAutoMove,         0x0F008100},
    /* 0x12 */ {&daPy_lk_c::procCrawlEnd,              0x03008000},
    /* 0x13 */ {&daPy_lk_c::procWHideReady,            0x00000011},
    /* 0x14 */ {&daPy_lk_c::procWHideWait,             0x00000115},
    /* 0x15 */ {&daPy_lk_c::procWHideMove,             0x00000014},
    /* 0x16 */ {&daPy_lk_c::procWHidePeep,             0x00000415},
    /* 0x17 */ {&daPy_lk_c::procWaitTurn,              0x00025145},
    /* 0x18 */ {&daPy_lk_c::procMoveTurn,              0x00024044},
    /* 0x19 */ {&daPy_lk_c::procSlip,                  0x00000100},
    /* 0x1A */ {&daPy_lk_c::procSlideFront,            0x00008400},
    /* 0x1B */ {&daPy_lk_c::procSlideBack,             0x00000000},
    /* 0x1C */ {&daPy_lk_c::procSlideFrontLand,        0x00000404},
    /* 0x1D */ {&daPy_lk_c::procSlideBackLand,         0x00000404},
    /* 0x1E */ {&daPy_lk_c::procFrontRoll,             0x00008400},
    /* 0x1F */ {&daPy_lk_c::procFrontRollCrash,        0x00000402},
    /* 0x20 */ {&daPy_lk_c::procNockBackEnd,           0x00008400},
    /* 0x21 */ {&daPy_lk_c::procSideRoll,              0x00008400},
    /* 0x22 */ {&daPy_lk_c::procBackJump,              0x00000446},
    /* 0x23 */ {&daPy_lk_c::procBackJumpLand,          0x00000445},
    /* 0x24 */ {&daPy_lk_c::procAutoJump,              0x00005406},
    /* 0x25 */ {&daPy_lk_c::procLand,                  0x00005005},
    /* 0x26 */ {&daPy_lk_c::procLandDamage,            0x00000409},
    /* 0x27 */ {&daPy_lk_c::procFall,                  0x00001006},
    /* 0x28 */ {&daPy_lk_c::procSlowFall,              0x00000002},
    /* 0x29 */ {&daPy_lk_c::procSmallJump,             0x00004002},
    /* 0x2A */ {&daPy_lk_c::procVerticalJump,          0x00000001},
    /* 0x2B */ {&daPy_lk_c::procHangStart,             0x00000421},
    /* 0x2C */ {&daPy_lk_c::procHangFallStart,         0x00000421},
    /* 0x2D */ {&daPy_lk_c::procHangUp,                0x00000421},
    /* 0x2E */ {&daPy_lk_c::procHangWait,              0x00000121},
    /* 0x2F */ {&daPy_lk_c::procHangMove,              0x00000120},
    /* 0x30 */ {&daPy_lk_c::procHangClimb,             0x00000420},
    /* 0x31 */ {&daPy_lk_c::procHangWallCatch,         0x00000020},
    /* 0x32 */ {&daPy_lk_c::procPushPullWait,          0x00200101},
    /* 0x33 */ {&daPy_lk_c::procPushMove,              0x00200000},
    /* 0x34 */ {&daPy_lk_c::procPullMove,              0x00200400},
    /* 0x35 */ {&daPy_lk_c::procSwimUp,                0x04040400},
    /* 0x36 */ {&daPy_lk_c::procSwimWait,              0x04040181},
    /* 0x37 */ {&daPy_lk_c::procSwimMove,              0x04040480},
    /* 0x38 */ {&daPy_lk_c::procLadderUpStart,         0x00400400},
    /* 0x39 */ {&daPy_lk_c::procLadderUpEnd,           0x00400400},
    /* 0x3A */ {&daPy_lk_c::procLadderDownStart,       0x00400400},
    /* 0x3B */ {&daPy_lk_c::procLadderDownEnd,         0x00400400},
    /* 0x3C */ {&daPy_lk_c::procLadderMove,            0x00400100},
    /* 0x3D */ {&daPy_lk_c::procClimbUpStart,          0x00010400},
    /* 0x3E */ {&daPy_lk_c::procClimbDownStart,        0x00010400},
    /* 0x3F */ {&daPy_lk_c::procClimbMoveUpDown,       0x00010100},
    /* 0x40 */ {&daPy_lk_c::procClimbMoveSide,         0x00010100},
    /* 0x41 */ {&daPy_lk_c::procCutA,                  0x00000480},
    /* 0x42 */ {&daPy_lk_c::procCutF,                  0x00000480},
    /* 0x43 */ {&daPy_lk_c::procCutR,                  0x00000480},
    /* 0x44 */ {&daPy_lk_c::procCutL,                  0x00000480},
    /* 0x45 */ {&daPy_lk_c::procCutEA,                 0x00000480},
    /* 0x46 */ {&daPy_lk_c::procCutEB,                 0x00000480},
    /* 0x47 */ {&daPy_lk_c::procCutExA,                0x00000400},
    /* 0x48 */ {&daPy_lk_c::procCutExB,                0x00000400},
    /* 0x49 */ {&daPy_lk_c::procCutExMJ,               0x08000402},
    /* 0x4A */ {&daPy_lk_c::procCutKesa,               0x00000400},
    /* 0x4B */ {&daPy_lk_c::procWeaponNormalSwing,     0x00000480},
    /* 0x4C */ {&daPy_lk_c::procWeaponSideSwing,       0x08000400},
    /* 0x4D */ {&daPy_lk_c::procWeaponFrontSwingReady, 0x08000400},
    /* 0x4E */ {&daPy_lk_c::procWeaponFrontSwing,      0x08000400},
    /* 0x4F */ {&daPy_lk_c::procWeaponFrontSwingEnd,   0x08000400},
    /* 0x50 */ {&daPy_lk_c::procWeaponThrow,           0x00000480},
    /* 0x51 */ {&daPy_lk_c::procHammerSideSwing,       0x08000400},
    /* 0x52 */ {&daPy_lk_c::procHammerFrontSwingReady, 0x08000400},
    /* 0x53 */ {&daPy_lk_c::procHammerFrontSwing,      0x08000400},
    /* 0x54 */ {&daPy_lk_c::procHammerFrontSwingEnd,   0x08000400},
    /* 0x55 */ {&daPy_lk_c::procCutTurn,               0x00000400},
    /* 0x56 */ {&daPy_lk_c::procCutRoll,               0x00000400},
    /* 0x57 */ {&daPy_lk_c::procCutRollEnd,            0x00000101},
    /* 0x58 */ {&daPy_lk_c::procCutTurnCharge,         0x00000400},
    /* 0x59 */ {&daPy_lk_c::procCutTurnMove,           0x00000080},
    /* 0x5A */ {&daPy_lk_c::procCutReverse,            0x00000400},
    /* 0x5B */ {&daPy_lk_c::procJumpCut,               0x08000402},
    /* 0x5C */ {&daPy_lk_c::procJumpCutLand,           0x08000401},
    /* 0x5D */ {&daPy_lk_c::procBtJump,                0x88000402},
    /* 0x5E */ {&daPy_lk_c::procBtJumpCut,             0x80000402},
    /* 0x5F */ {&daPy_lk_c::procBtSlide,               0x80000000},
    /* 0x60 */ {&daPy_lk_c::procBtRoll,                0x80008400},
    /* 0x61 */ {&daPy_lk_c::procBtRollCut,             0x88000402},
    /* 0x62 */ {&daPy_lk_c::procBtVerticalJump,        0x88000402},
    /* 0x63 */ {&daPy_lk_c::procBtVerticalJumpCut,     0x88000402},
    /* 0x64 */ {&daPy_lk_c::procBtVerticalJumpLand,    0x00000400},
    /* 0x65 */ {&daPy_lk_c::procGuardCrash,            0x00000000},
    /* 0x66 */ {&daPy_lk_c::procDamage,                0x00000488},
    /* 0x67 */ {&daPy_lk_c::procPolyDamage,            0x00000408},
    /* 0x68 */ {&daPy_lk_c::procLargeDamage,           0x0000000A},
    /* 0x69 */ {&daPy_lk_c::procLargeDamageUp,         0x0A008408},
    /* 0x6A */ {&daPy_lk_c::procLargeDamageWall,       0x0000040A},
    /* 0x6B */ {&daPy_lk_c::procLavaDamage,            0x0000000A},
    /* 0x6C */ {&daPy_lk_c::procElecDamage,            0x00008009},
    /* 0x6D */ {&daPy_lk_c::procGuardSlip,             0x00001480},
    /* 0x6E */ {&daPy_lk_c::procGrabReady,             0x00100401},
    /* 0x6F */ {&daPy_lk_c::procGrabUp,                0x00100401},
    /* 0x70 */ {&daPy_lk_c::procGrabMiss,              0x00100401},
    /* 0x71 */ {&daPy_lk_c::procGrabThrow,             0x00100401},
    /* 0x72 */ {&daPy_lk_c::procGrabPut,               0x00100401},
    /* 0x73 */ {&daPy_lk_c::procGrabWait,              0x00104181},
    /* 0x74 */ {&daPy_lk_c::procGrabHeavyWait,         0x00100181},
    /* 0x75 */ {&daPy_lk_c::procGrabRebound,           0x00100401},
    /* 0x76 */ {&daPy_lk_c::procRopeSubject,           0x20001005},
    /* 0x77 */ {&daPy_lk_c::procRopeReady,             0x04000800},
    /* 0x78 */ {&daPy_lk_c::procRopeSwing,             0x04000C00},
    /* 0x79 */ {&daPy_lk_c::procRopeHangWait,          0x04000901},
    /* 0x7A */ {&daPy_lk_c::procRopeUp,                0x04000800},
    /* 0x7B */ {&daPy_lk_c::procRopeDown,              0x04000800},
    /* 0x7C */ {&daPy_lk_c::procRopeSwingStart,        0x04000C00},
    /* 0x7D */ {&daPy_lk_c::procRopeMove,              0x20001104},
    /* 0x7E */ {&daPy_lk_c::procRopeThrowCatch,        0x00000401},
    /* 0x7F */ {&daPy_lk_c::procRopeUpHang,            0x04000800},
    /* 0x80 */ {&daPy_lk_c::procBoomerangSubject,      0x20021105},
    /* 0x81 */ {&daPy_lk_c::procBoomerangMove,         0x20021104},
    /* 0x82 */ {&daPy_lk_c::procBoomerangCatch,        0x00001401},
    /* 0x83 */ {&daPy_lk_c::procHookshotSubject,       0x20001305},
    /* 0x84 */ {&daPy_lk_c::procHookshotMove,          0x20001304},
    /* 0x85 */ {&daPy_lk_c::procHookshotFly,           0x00000202},
    /* 0x86 */ {&daPy_lk_c::procShipReady,             0x00002420},
    /* 0x87 */ {&daPy_lk_c::procShipJumpRide,          0x00002400},
    /* 0x88 */ {&daPy_lk_c::procShipSteer,             0x40002180},
    /* 0x89 */ {&daPy_lk_c::procShipPaddle,            0x40002180},
    /* 0x8A */ {&daPy_lk_c::procShipScope,             0x40002100},
    /* 0x8B */ {&daPy_lk_c::procShipBoomerang,         0x60022100},
    /* 0x8C */ {&daPy_lk_c::procShipHookshot,          0x60002100},
    /* 0x8D */ {&daPy_lk_c::procShipBow,               0x60002100},
    /* 0x8E */ {&daPy_lk_c::procShipCannon,            0x40002100},
    /* 0x8F */ {&daPy_lk_c::procShipCrane,             0x08002180},
    /* 0x90 */ {&daPy_lk_c::procShipGetOff,            0x00002000},
    /* 0x91 */ {&daPy_lk_c::procShipRestart,           0x00002400},
    /* 0x92 */ {&daPy_lk_c::procFanSwing,              0x08000400},
    /* 0x93 */ {&daPy_lk_c::procFanGlide,              0x00000482},
    /* 0x94 */ {&daPy_lk_c::procBowSubject,            0x20001105},
    /* 0x95 */ {&daPy_lk_c::procBowMove,               0x20001104},
    /* 0x96 */ {&daPy_lk_c::procVomitReady,            0x00000402},
    /* 0x97 */ {&daPy_lk_c::procVomitWait,             0x04008001},
    /* 0x98 */ {&daPy_lk_c::procVomitJump,             0x00000002},
    /* 0x99 */ {&daPy_lk_c::procVomitLand,             0x00000401},
    /* 0x9A */ {&daPy_lk_c::procTactWait,              0x08000101},
    /* 0x9B */ {&daPy_lk_c::procTactPlay,              0x08000401},
    /* 0x9C */ {&daPy_lk_c::procTactPlayEnd,           0x00000101},
    /* 0x9D */ {&daPy_lk_c::procTactPlayOriginal,      0x00000001},
    /* 0x9E */ {&daPy_lk_c::procIceSlipFall,           0x00000002},
    /* 0x9F */ {&daPy_lk_c::procIceSlipFallUp,         0x0A008400},
    /* 0xA0 */ {&daPy_lk_c::procIceSlipAlmostFall,     0x00000001},
    /* 0xA1 */ {&daPy_lk_c::procBootsEquip,            0x08004403},
    /* 0xA2 */ {&daPy_lk_c::procNotUse,                0x00000401},
    /* 0xA3 */ {&daPy_lk_c::procBottleDrink,           0x00000401},
    /* 0xA4 */ {&daPy_lk_c::procBottleOpen,            0x00000401},
    /* 0xA5 */ {&daPy_lk_c::procBottleSwing,           0x00000401},
    /* 0xA6 */ {&daPy_lk_c::procBottleGet,             0x00000401},
    /* 0xA7 */ {&daPy_lk_c::procFoodThrow,             0x00000101},
    /* 0xA8 */ {&daPy_lk_c::procFoodSet,               0x00000401},
    /* 0xA9 */ {&daPy_lk_c::dProcTool,                 0x00008000},
    /* 0xAA */ {&daPy_lk_c::dProcTalk,                 0x00080181},
    /* 0xAB */ {&daPy_lk_c::dProcDamage,               0x00000401},
    /* 0xAC */ {&daPy_lk_c::dProcHoldup,               0x00004001},
    /* 0xAD */ {&daPy_lk_c::dProcOpenTreasure,         0x00008401},
    /* 0xAE */ {&daPy_lk_c::dProcGetItem,              0x00008001},
    /* 0xAF */ {&daPy_lk_c::dProcUnequip,              0x00000101},
    /* 0xB0 */ {&daPy_lk_c::dProcLavaDamage,           0x0000000A},
    /* 0xB1 */ {&daPy_lk_c::dProcFreezeDamage,         0x0000400A},
    /* 0xB2 */ {&daPy_lk_c::dProcDead,                 0x00008409},
    /* 0xB3 */ {&daPy_lk_c::dProcLookAround,           0x00000401},
    /* 0xB4 */ {&daPy_lk_c::dProcSalute,               0x00000401},
    /* 0xB5 */ {&daPy_lk_c::dProcLookAround2,          0x00080401},
    /* 0xB6 */ {&daPy_lk_c::dProcTalismanPickup,       0x00080401},
    /* 0xB7 */ {&daPy_lk_c::dProcTalismanWait,         0x00080101},
    /* 0xB8 */ {&daPy_lk_c::dProcSurprised,            0x00000401},
    /* 0xB9 */ {&daPy_lk_c::dProcTurnBack,             0x00004401},
    /* 0xBA */ {&daPy_lk_c::dProcLookUp,               0x00000401},
    /* 0xBB */ {&daPy_lk_c::dProcQuakeWait,            0x00000401},
    /* 0xBC */ {&daPy_lk_c::dProcDance,                0x00000401},
    /* 0xBD */ {&daPy_lk_c::dProcCaught,               0x10000000},
    /* 0xBE */ {&daPy_lk_c::dProcLookWait,             0x00001181},
    /* 0xBF */ {&daPy_lk_c::dProcPushPullWait,         0x00200101},
    /* 0xC0 */ {&daPy_lk_c::dProcPushMove,             0x00200000},
    /* 0xC1 */ {&daPy_lk_c::dProcDoorOpen,             0x00000400},
    /* 0xC2 */ {&daPy_lk_c::dProcNod,                  0x00080481},
    /* 0xC3 */ {&daPy_lk_c::dProcPresent,              0x00080001},
    /* 0xC4 */ {&daPy_lk_c::dProcWindChange,           0x00000401},
    /* 0xC5 */ {&daPy_lk_c::dProcStandItemPut,         0x00000001},
    /* 0xC6 */ {&daPy_lk_c::dProcVorcanoFail,          0x00000002},
    /* 0xC7 */ {&daPy_lk_c::dProcSlightSurprised,      0x00000401},
    /* 0xC8 */ {&daPy_lk_c::dProcSmile,                0x00000001},
    /* 0xC9 */ {&daPy_lk_c::dProcBossWarp,             0x00000402},
    /* 0xCA */ {&daPy_lk_c::dProcAgbUse,               0x00000101},
    /* 0xCB */ {&daPy_lk_c::dProcLookTurn,             0x00000401},
    /* 0xCC */ {&daPy_lk_c::dProcLetterOpen,           0x00000101},
    /* 0xCD */ {&daPy_lk_c::dProcLetterRead,           0x00000101},
    /* 0xCE */ {&daPy_lk_c::dProcRedeadStop,           0x08000401},
    /* 0xCF */ {&daPy_lk_c::dProcRedeadCatch,          0x00000401},
    /* 0xD0 */ {&daPy_lk_c::dProcGetDance,             0x00008401},
    /* 0xD1 */ {&daPy_lk_c::dProcBottleOpenFairy,      0x00000401},
    /* 0xD2 */ {&daPy_lk_c::dProcWarpShort,            0x00000102},
    /* 0xD3 */ {&daPy_lk_c::dProcOpenSalvageTreasure,  0x00000401},
    /* 0xD4 */ {&daPy_lk_c::dProcSurprisedWait,        0x00000001},
    /* 0xD5 */ {&daPy_lk_c::dProcPowerUpWait_init,     0x00008401},
    /* 0xD6 */ {&daPy_lk_c::dProcPowerUp,              0x00008401},
    /* 0xD7 */ {&daPy_lk_c::dProcShipSit,              0x00082181},
    /* 0xD8 */ {&daPy_lk_c::dProcLastCombo,            0x00008001},
    /* 0xD9 */ {&daPy_lk_c::dProcHandUp,               0x00080181},
    /* 0xDA */ {&daPy_lk_c::dProcIceSlip,              0x00000401},
};

daPy_lk_c::daPy_ProcFunc daPy_lk_c::mDemoProcInitFuncTable[0x4B] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &daPy_lk_c::procWaitTurn_init,
    NULL,
    &daPy_lk_c::dProcDamage_init,
    NULL,
    NULL,
    &daPy_lk_c::dProcOpenTreasure_init,
    &daPy_lk_c::dProcGetItem_init,
    &daPy_lk_c::dProcUnequip_init,
    &daPy_lk_c::dProcHoldup_init,
    NULL,
    &daPy_lk_c::dProcLookAround_init,
    NULL,
    NULL,
    NULL,
    &daPy_lk_c::dProcSalute_init,
    &daPy_lk_c::dProcLookAround2_init,
    &daPy_lk_c::dProcTalismanPickup_init,
    &daPy_lk_c::dProcTalismanWait_init,
    NULL,
    &daPy_lk_c::dProcSurprised_init,
    &daPy_lk_c::dProcTurnBack_init,
    &daPy_lk_c::dProcLookUp_init,
    NULL,
    &daPy_lk_c::dProcQuakeWait_init,
    &daPy_lk_c::dProcDance_init,
    &daPy_lk_c::dProcCaught_init,
    NULL,
    &daPy_lk_c::dProcPushPullWait_init,
    &daPy_lk_c::dProcPushMove_init,
    NULL,
    &daPy_lk_c::dProcDoorOpen_init,
    &daPy_lk_c::dProcNod_init,
    &daPy_lk_c::dProcPresent_init,
    &daPy_lk_c::dProcWindChange_init,
    &daPy_lk_c::procShipPaddle_init,
    &daPy_lk_c::dProcStandItemPut_init,
    NULL,
    NULL,
    NULL,
    NULL,
    &daPy_lk_c::procTactPlayOriginal_init,
    &daPy_lk_c::dProcPowerUp_init,
    &daPy_lk_c::dProcVorcanoFail_init,
    &daPy_lk_c::dProcBossWarp_init,
    &daPy_lk_c::dProcSlightSurprised_init,
    &daPy_lk_c::dProcSmile_init,
    NULL,
    &daPy_lk_c::dProcAgbUse_init,
    &daPy_lk_c::dProcLookTurn_init,
    &daPy_lk_c::dProcLetterOpen_init,
    &daPy_lk_c::dProcLetterRead_init,
    &daPy_lk_c::procGrabPut_init,
    &daPy_lk_c::dProcRedeadStop_init,
    &daPy_lk_c::dProcRedeadCatch_init,
    &daPy_lk_c::dProcGetDance_init,
    &daPy_lk_c::dProcBottleOpenFairy_init,
    NULL,
    &daPy_lk_c::dProcWarpShort_init,
    &daPy_lk_c::dProcOpenSalvageTreasure_init,
    NULL,
    &daPy_lk_c::procFoodSet_init,
    &daPy_lk_c::dProcSurprisedWait_init,
    &daPy_lk_c::dProcPowerUpWait_init,
    &daPy_lk_c::procShipBow_init,
    &daPy_lk_c::dProcShipSit_init,
    &daPy_lk_c::dProcLastCombo_init,
    &daPy_lk_c::procShipGetOff_init,
    &daPy_lk_c::dProcHandUp_init,
    &daPy_lk_c::procFoodThrow_init,
    &daPy_lk_c::dProcIceSlip_init,
};

/* 80102E8C-80102EAC       .text daPy_createHeap__FP10fopAc_ac_c */
static BOOL daPy_createHeap(fopAc_ac_c* i_this) {
    return static_cast<daPy_lk_c*>(i_this)->createHeap();
}

/* 80102F64-80103074       .text calc__13daPy_matAnm_cCFP11J3DMaterial */
void daPy_matAnm_c::calc(J3DMaterial* mat) const {
    daPy_matAnm_c* i_this = const_cast<daPy_matAnm_c*>(this);
    
    J3DMaterialAnm::calc(mat);
    
    for (u32 i = 0; i < 8; i++) {
        if (getTexMtxAnm(i)) {
            J3DTextureSRTInfo& srt = mat->getTexMtx(i)->getTexMtxInfo().mSRT;
            if (m_morf_frame != 0) {
                f32 temp = 1.0f / (m_morf_frame + 1);
                srt.mTranslationX = mEyePosOld.x * (1.0f - temp) + (srt.mTranslationX * temp);
                srt.mTranslationY = mEyePosOld.y * (1.0f - temp) + (srt.mTranslationY * temp);
            } else if (m_eye_move_flg != 0) {
                srt.mTranslationX = mEyePos.x;
                srt.mTranslationY = mEyePos.y;
            }
            i_this->mEyePosOld.x = srt.mTranslationX;
            i_this->mEyePosOld.y = srt.mTranslationY;
        }
    }
}

/* 80103074-801030BC       .text seStartOnlyReverb__9daPy_lk_cFUl */
void daPy_lk_c::seStartOnlyReverb(u32 sfxID) {
    mDoAud_seStart(sfxID, &current.pos, 0, mReverb);
}

/* 801030BC-80103104       .text seStartMapInfo__9daPy_lk_cFUl */
void daPy_lk_c::seStartMapInfo(u32 sfxID) {
    mDoAud_seStart(sfxID, &current.pos, mMtrlSndId, mReverb);
}

/* 80103104-8010314C       .text seStartSwordCut__9daPy_lk_cFUl */
void daPy_lk_c::seStartSwordCut(u32 sfxID) {
    mDoAud_seStart(sfxID, &mSwordTopPos, 0, mReverb);
}

/* 8010314C-801031A4       .text voiceStart__9daPy_lk_cFUl */
void daPy_lk_c::voiceStart(u32 param_1) {
    mDoAud_linkVoiceStart(param_1, &mEyePos, mDoAud_getLinkVoiceVowel(param_1), mReverb);
}

/* 801031A4-801031DC       .text itemButton__9daPy_lk_cCFv */
void daPy_lk_c::itemButton() const {
    /* Nonmatching */
}

/* 801031DC-80103214       .text itemTrigger__9daPy_lk_cCFv */
void daPy_lk_c::itemTrigger() const {
    /* Nonmatching */
}

/* 80103214-80103258       .text getReadyItem__9daPy_lk_cFv */
void daPy_lk_c::getReadyItem() {
    /* Nonmatching */
}

/* 80103258-801032E4       .text checkGroupItem__9daPy_lk_cFii */
void daPy_lk_c::checkGroupItem(int, int) {
    /* Nonmatching */
}

/* 801032E4-801033E4       .text checkSetItemTrigger__9daPy_lk_cFii */
void daPy_lk_c::checkSetItemTrigger(int, int) {
    /* Nonmatching */
}

/* 801033E4-80103450       .text auraJointCB0__9daPy_lk_cFi */
void daPy_lk_c::auraJointCB0(int) {
    /* Nonmatching */
}

/* 80103450-80103494       .text daPy_auraCallback__FP7J3DNodei */
static BOOL daPy_auraCallback(J3DNode*, int) {
    /* Nonmatching */
}

/* 80103494-80103A88       .text jointBeforeCB__9daPy_lk_cFiP16J3DTransformInfoP10Quaternion */
BOOL daPy_lk_c::jointBeforeCB(int, J3DTransformInfo*, Quaternion*) {
    /* Nonmatching */
}

/* 80103A88-80103AAC       .text daPy_jointBeforeCallback__FUlUsP16J3DTransformInfoP10Quaternion */
static BOOL daPy_jointBeforeCallback(u32 userArea, u16 param_1, J3DTransformInfo* param_2, Quaternion* param_3) {
    return reinterpret_cast<daPy_lk_c*>(userArea)->jointBeforeCB(param_1, param_2, param_3);
}

/* 80103AAC-80103C1C       .text jointAfterCB__9daPy_lk_cFiP16J3DTransformInfoP10Quaternion */
BOOL daPy_lk_c::jointAfterCB(int, J3DTransformInfo*, Quaternion*) {
    /* Nonmatching */
}

/* 80103C1C-80103C40       .text daPy_jointAfterCallback__FUlUsP16J3DTransformInfoP10Quaternion */
static BOOL daPy_jointAfterCallback(u32 userArea, u16 param_1, J3DTransformInfo* param_2, Quaternion* param_3) {
    return reinterpret_cast<daPy_lk_c*>(userArea)->jointAfterCB(param_1, param_2, param_3);
}

/* 80103C40-80103EE4       .text jointCB0__9daPy_lk_cFi */
void daPy_lk_c::jointCB0(int) {
    /* Nonmatching */
}

/* 80103EE4-80103F28       .text daPy_jointCallback0__FP7J3DNodei */
static BOOL daPy_jointCallback0(J3DNode*, int) {
    /* Nonmatching */
}

/* 80103F28-80104178       .text jointCB1__9daPy_lk_cFv */
void daPy_lk_c::jointCB1() {
    /* Nonmatching */
}

/* 80104178-801041B4       .text daPy_jointCallback1__FP7J3DNodei */
static BOOL daPy_jointCallback1(J3DNode*, int) {
    /* Nonmatching */
}

/* 801041B4-801041EC       .text setAnimeHeap__9daPy_lk_cFP12JKRSolidHeap */
void daPy_lk_c::setAnimeHeap(JKRSolidHeap* animeHeap) {
    animeHeap->freeAll();
    mDoExt_setCurrentHeap(animeHeap);
}

/* 801041EC-80104240       .text setItemHeap__9daPy_lk_cFv */
void daPy_lk_c::setItemHeap() {
    if (!checkResetFlg0(daPyRFlg0_UNK4000)) {
        mCurrItemHeapIdx ^= 1;
        onResetFlg0(daPyRFlg0_UNK4000);
    }
    setAnimeHeap(mpItemHeaps[mCurrItemHeapIdx]);
}

/* 80104240-80104280       .text setBlurPosResource__9daPy_lk_cFUs */
void daPy_lk_c::setBlurPosResource(u16) {
    /* Nonmatching */
}

/* 80104280-80104364       .text getItemAnimeResource__9daPy_lk_cFUs */
J3DAnmTransform* daPy_lk_c::getItemAnimeResource(u16) {
    /* Nonmatching */
}

/* 80104364-801043F0       .text getAnimeResource__9daPy_lk_cFP14daPy_anmHeap_cUsUl */
void daPy_lk_c::getAnimeResource(daPy_anmHeap_c*, u16, u32) {
    /* Nonmatching */
}

/* 801043F0-801044E8       .text getUnderUpperAnime__9daPy_lk_cFPC15daPy_anmIndex_cPP15J3DAnmTransformPP15J3DAnmTransformiUl */
void daPy_lk_c::getUnderUpperAnime(const daPy_anmIndex_c*, J3DAnmTransform**, J3DAnmTransform**, int, u32) {
    /* Nonmatching */
}

/* 801044E8-80104564       .text setTextureAnimeResource__9daPy_lk_cFP16J3DAnmTexPatterni */
void daPy_lk_c::setTextureAnimeResource(J3DAnmTexPattern*, int) {
    /* Nonmatching */
}

/* 80104564-80104600       .text loadTextureAnimeResource__9daPy_lk_cFUli */
void daPy_lk_c::loadTextureAnimeResource(u32, int) {
    /* Nonmatching */
}

/* 80104600-801046CC       .text checkBossBgm__9daPy_lk_cFv */
void daPy_lk_c::checkBossBgm() {
    /* Nonmatching */
}

/* 801046CC-801046EC       .text checkMabaAnimeBtp__9daPy_lk_cFi */
void daPy_lk_c::checkMabaAnimeBtp(int) {
    /* Nonmatching */
}

/* 801046EC-80104A08       .text checkNormalFace__9daPy_lk_cFv */
void daPy_lk_c::checkNormalFace() {
    /* Nonmatching */
}

/* 80104A08-80104E08       .text setTextureAnime__9daPy_lk_cFUsi */
void daPy_lk_c::setTextureAnime(u16, int) {
    /* Nonmatching */
}

/* 80104E08-80104EC8       .text setPriTextureAnime__9daPy_lk_cFUsi */
void daPy_lk_c::setPriTextureAnime(u16, int) {
    /* Nonmatching */
}

/* 80104EC8-80104F74       .text resetPriTextureAnime__9daPy_lk_cFv */
void daPy_lk_c::resetPriTextureAnime() {
    /* Nonmatching */
}

/* 80104F74-80105040       .text setDemoTextureAnime__9daPy_lk_cFUsUsiUs */
void daPy_lk_c::setDemoTextureAnime(u16, u16, int, u16) {
    /* Nonmatching */
}

/* 80105040-80105164       .text resetDemoTextureAnime__9daPy_lk_cFv */
void daPy_lk_c::resetDemoTextureAnime() {
    /* Nonmatching */
}

/* 80105164-80105220       .text setTextureScrollResource__9daPy_lk_cFP19J3DAnmTextureSRTKeyi */
void daPy_lk_c::setTextureScrollResource(J3DAnmTextureSRTKey*, int) {
    /* Nonmatching */
}

/* 80105220-801052BC       .text loadTextureScrollResource__9daPy_lk_cFUli */
void daPy_lk_c::loadTextureScrollResource(u32, int) {
    /* Nonmatching */
}

/* 801052BC-8010552C       .text playTextureAnime__9daPy_lk_cFv */
void daPy_lk_c::playTextureAnime() {
    /* Nonmatching */
}

/* 8010552C-8010558C       .text checkPlayerGuard__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkPlayerGuard() const {
    /* Nonmatching */
}

/* 8010558C-801056E4       .text setOutPower__9daPy_lk_cFfsi */
void daPy_lk_c::setOutPower(f32, s16, int) {
    /* Nonmatching */
}

/* 801056E4-80105814       .text checkSightLine__9daPy_lk_cFfP4cXyz */
void daPy_lk_c::checkSightLine(f32, cXyz*) {
    /* Nonmatching */
}

/* 80105814-80105910       .text setBootsModel__9daPy_lk_cFPP8J3DModel */
void daPy_lk_c::setBootsModel(J3DModel**) {
    /* Nonmatching */
}

/* 80105910-80106660       .text setItemModel__9daPy_lk_cFv */
void daPy_lk_c::setItemModel() {
    /* Nonmatching */
}

/* 80106660-801066DC       .text checkUpperReadyAnime__9daPy_lk_cCFv */
void daPy_lk_c::checkUpperReadyAnime() const {
    /* Nonmatching */
}

/* 801066DC-80106750       .text checkUpperReadyThrowAnime__9daPy_lk_cCFv */
void daPy_lk_c::checkUpperReadyThrowAnime() const {
    /* Nonmatching */
}

/* 80106750-801067D8       .text checkNoCollisionCorret__9daPy_lk_cFv */
void daPy_lk_c::checkNoCollisionCorret() {
    /* Nonmatching */
}

/* 801067D8-80106BD0       .text setDrawHandModel__9daPy_lk_cFv */
void daPy_lk_c::setDrawHandModel() {
    /* Nonmatching */
}

/* 80106BD0-80106C40       .text entryDLSetLight__9daPy_lk_cFP8J3DModelUl */
void daPy_lk_c::entryDLSetLight(J3DModel*, u32) {
    /* Nonmatching */
}

/* 80106C40-80106CB0       .text updateDLSetLight__9daPy_lk_cFP8J3DModelUl */
void daPy_lk_c::updateDLSetLight(J3DModel*, u32) {
    /* Nonmatching */
}

/* 80106CB0-80106D8C       .text hideHatAndBackle__9daPy_lk_cFP11J3DMaterial */
void daPy_lk_c::hideHatAndBackle(J3DMaterial*) {
    /* Nonmatching */
}

/* 80106D8C-80106E50       .text drawMirrorLightModel__9daPy_lk_cFv */
void daPy_lk_c::drawMirrorLightModel() {
    /* Nonmatching */
}

/* 80106E50-80107210       .text drawShadow__9daPy_lk_cFv */
void daPy_lk_c::drawShadow() {
    /* Nonmatching */
}

/* 80107210-8010728C       .text offBodyEffect__9daPy_lk_cFv */
void daPy_lk_c::offBodyEffect() {
    /* Nonmatching */
}

/* 8010728C-80107308       .text onBodyEffect__9daPy_lk_cFv */
void daPy_lk_c::onBodyEffect() {
    /* Nonmatching */
}

/* 80107308-80108204       .text draw__9daPy_lk_cFv */
BOOL daPy_lk_c::draw() {
    /* Nonmatching */
}

/* 80108204-80108224       .text daPy_Draw__FP9daPy_lk_c */
static BOOL daPy_Draw(daPy_lk_c* i_this) {
    return static_cast<daPy_lk_c*>(i_this)->draw();
}

/* 80108224-8010841C       .text setAtnList__9daPy_lk_cFv */
void daPy_lk_c::setAtnList() {
    /* Nonmatching */
}

/* 8010841C-8010848C       .text setActor__16daPy_actorKeep_cFv */
void daPy_actorKeep_c::setActor() {
    /* Nonmatching */
}

/* 8010848C-801084AC       .text setData__16daPy_actorKeep_cFP10fopAc_ac_c */
void daPy_actorKeep_c::setData(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 801084AC-801084C0       .text clearData__16daPy_actorKeep_cFv */
void daPy_actorKeep_c::clearData() {
    /* Nonmatching */
}

/* 801084C0-80108564       .text setActorPointer__9daPy_lk_cFv */
void daPy_lk_c::setActorPointer() {
    /* Nonmatching */
}

/* 80108564-80108634       .text setTalkStatus__9daPy_lk_cFv */
void daPy_lk_c::setTalkStatus() {
    /* Nonmatching */
}

/* 80108634-801086C8       .text setHintActor__9daPy_lk_cFv */
void daPy_lk_c::setHintActor() {
    /* Nonmatching */
}

/* 801086C8-801088E8       .text setDoStatusBasic__9daPy_lk_cFv */
void daPy_lk_c::setDoStatusBasic() {
    /* Nonmatching */
}

/* 801088E8-80108A9C       .text setDoStatus__9daPy_lk_cFv */
void daPy_lk_c::setDoStatus() {
    /* Nonmatching */
}

/* 80108A9C-80108B08       .text getDirectionFromAngle__9daPy_lk_cFs */
void daPy_lk_c::getDirectionFromAngle(s16) {
    /* Nonmatching */
}

/* 80108B08-80108B38       .text getDirectionFromShapeAngle__9daPy_lk_cFv */
void daPy_lk_c::getDirectionFromShapeAngle() {
    /* Nonmatching */
}

/* 80108B38-80108B68       .text getDirectionFromCurrentAngle__9daPy_lk_cFv */
void daPy_lk_c::getDirectionFromCurrentAngle() {
    /* Nonmatching */
}

/* 80108B68-80108D80       .text setNormalSpeedF__9daPy_lk_cFffff */
void daPy_lk_c::setNormalSpeedF(f32, f32, f32, f32) {
    /* Nonmatching */
}

/* 80108D80-8010959C       .text posMoveFromFootPos__9daPy_lk_cFv */
void daPy_lk_c::posMoveFromFootPos() {
    /* Nonmatching */
}

/* 8010959C-80109E80       .text posMove__9daPy_lk_cFv */
void daPy_lk_c::posMove() {
    /* Nonmatching */
}

/* 80109E80-80109ED8       .text setShapeAngleToAtnActor__9daPy_lk_cFv */
void daPy_lk_c::setShapeAngleToAtnActor() {
    /* Nonmatching */
}

/* 80109ED8-80109F4C       .text cancelItemUpperReadyAnime__9daPy_lk_cFv */
void daPy_lk_c::cancelItemUpperReadyAnime() {
    /* Nonmatching */
}

/* 80109F4C-8010A204       .text checkBodyAngleX__9daPy_lk_cFs */
void daPy_lk_c::checkBodyAngleX(s16) {
    /* Nonmatching */
}

/* 8010A204-8010A2F4       .text setBodyAngleToCamera__9daPy_lk_cFv */
void daPy_lk_c::setBodyAngleToCamera() {
    /* Nonmatching */
}

/* 8010A2F4-8010A4D4       .text setBodyAngleXReadyAnime__9daPy_lk_cFv */
void daPy_lk_c::setBodyAngleXReadyAnime() {
    /* Nonmatching */
}

/* 8010A4D4-8010A96C       .text setSpeedAndAngleNormal__9daPy_lk_cFs */
void daPy_lk_c::setSpeedAndAngleNormal(s16) {
    /* Nonmatching */
}

/* 8010A96C-8010AA90       .text setSpeedAndAngleAtn__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleAtn() {
    /* Nonmatching */
}

/* 8010AA90-8010AB84       .text setSpeedAndAngleAtnBack__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleAtnBack() {
    /* Nonmatching */
}

/* 8010AB84-8010AC8C       .text setSpeedAndAngleAtnActor__9daPy_lk_cFv */
void daPy_lk_c::setSpeedAndAngleAtnActor() {
    /* Nonmatching */
}

/* 8010AC8C-8010ACEC       .text setFrameCtrl__9daPy_lk_cFP12J3DFrameCtrlUcssff */
void daPy_lk_c::setFrameCtrl(J3DFrameCtrl*, u8, s16, s16, f32, f32) {
    /* Nonmatching */
}

/* 8010ACEC-8010AD2C       .text checkAtnWaitAnime__9daPy_lk_cFv */
void daPy_lk_c::checkAtnWaitAnime() {
    /* Nonmatching */
}

/* 8010AD2C-8010B798       .text setBlendMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendMoveAnime(f32) {
    /* Nonmatching */
}

/* 8010B798-8010BB08       .text setBlendAtnBackMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendAtnBackMoveAnime(f32) {
    /* Nonmatching */
}

/* 8010BB08-8010C010       .text setBlendAtnMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendAtnMoveAnime(f32) {
    /* Nonmatching */
}

/* 8010C010-8010C100       .text setAnimeEquipSword__9daPy_lk_cFi */
void daPy_lk_c::setAnimeEquipSword(int) {
    /* Nonmatching */
}

/* 8010C100-8010C158       .text setAnimeEquipSingleItem__9daPy_lk_cFUs */
void daPy_lk_c::setAnimeEquipSingleItem(u16) {
    /* Nonmatching */
}

/* 8010C158-8010C1D4       .text setAnimeEquipItem__9daPy_lk_cFv */
void daPy_lk_c::setAnimeEquipItem() {
    /* Nonmatching */
}

/* 8010C1D4-8010C284       .text setAnimeUnequipSword__9daPy_lk_cFv */
void daPy_lk_c::setAnimeUnequipSword() {
    /* Nonmatching */
}

/* 8010C284-8010C3C0       .text setAnimeUnequipItem__9daPy_lk_cFUs */
void daPy_lk_c::setAnimeUnequipItem(u16) {
    /* Nonmatching */
}

/* 8010C3C0-8010C430       .text setAnimeUnequip__9daPy_lk_cFv */
void daPy_lk_c::setAnimeUnequip() {
    /* Nonmatching */
}

/* 8010C430-8010C4A4       .text checkBossGomaStage__9daPy_lk_cFv */
BOOL daPy_lk_c::checkBossGomaStage() {
    /* Nonmatching */
}

/* 8010C4A4-8010C4C8       .text checkSingleItemEquipAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkSingleItemEquipAnime() const {
    return m_anm_heap_upper[2].mIdx == LKANM_BCK_TAKEL || m_anm_heap_upper[2].mIdx == LKANM_BCK_TAKER;
}

/* 8010C4C8-8010C528       .text checkItemEquipAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkItemEquipAnime() const {
    /* Nonmatching */
}

/* 8010C528-8010C570       .text checkEquipAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkEquipAnime() const {
    /* Nonmatching */
}

/* 8010C570-8010C71C       .text deleteEquipItem__9daPy_lk_cFi */
void daPy_lk_c::deleteEquipItem(int) {
    /* Nonmatching */
}

/* 8010C71C-8010C7F4       .text setFallVoice__9daPy_lk_cFv */
void daPy_lk_c::setFallVoice() {
    /* Nonmatching */
}

/* 8010C7F4-8010C854       .text keepItemData__9daPy_lk_cFv */
/* Saves which item the player was holding in their hand so it can be restored later. */
void daPy_lk_c::keepItemData() {
    mKeepItemType = mHeldItemType;
    
    deleteEquipItem(0);
    
    if (mKeepItemType == 0x101) {
        mKeepItemType = 0x100;
    } else if (mKeepItemType == 0x100) {
        mKeepItemType = 0x10B;
    }
}

/* 8010C854-8010C8D4       .text returnKeepItemData__9daPy_lk_cFv */
/* Restores which item the player was holding in their hand. */
void daPy_lk_c::returnKeepItemData() {
    if (mKeepItemType == 0x100) {
        return;
    }
    
    deleteEquipItem(0);
    mHeldItemType = mKeepItemType;
    mKeepItemType = 0x100;
    
    if (mHeldItemType == 0x10B) {
        mHeldItemType = 0x100;
    } else if (mHeldItemType == 0x103) {
        setSwordModel(1);
    } else {
        makeItemType();
    }
}

/* 8010C8D4-8010CB70       .text makeItemType__9daPy_lk_cFv */
void daPy_lk_c::makeItemType() {
    /* Nonmatching */
}

/* 8010CB70-8010CBC8       .text setScopeModel__9daPy_lk_cFv */
void daPy_lk_c::setScopeModel() {
    /* Nonmatching */
}

/* 8010CBC8-8010CC78       .text setPhotoBoxModel__9daPy_lk_cFv */
void daPy_lk_c::setPhotoBoxModel() {
    /* Nonmatching */
}

/* 8010CC78-8010CD34       .text changeDragonShield__9daPy_lk_cFi */
void daPy_lk_c::changeDragonShield(int) {
    /* Nonmatching */
}

/* 8010CD34-8010CFB4       .text checkNewItemChange__9daPy_lk_cFUc */
void daPy_lk_c::checkNewItemChange(u8) {
    /* Nonmatching */
}

/* 8010CFB4-8010D26C       .text checkItemChangeFromButton__9daPy_lk_cFv */
void daPy_lk_c::checkItemChangeFromButton() {
    /* Nonmatching */
}

/* 8010D26C-8010D754       .text checkItemAction__9daPy_lk_cFv */
void daPy_lk_c::checkItemAction() {
    /* Nonmatching */
}

/* 8010D754-8010D810       .text getSlidePolygon__9daPy_lk_cFv */
void daPy_lk_c::getSlidePolygon() {
    /* Nonmatching */
}

/* 8010D810-8010D8B0       .text checkJumpCutFromButton__9daPy_lk_cFv */
void daPy_lk_c::checkJumpCutFromButton() {
    /* Nonmatching */
}

/* 8010D8B0-8010DB58       .text orderTalk__9daPy_lk_cFv */
void daPy_lk_c::orderTalk() {
    /* Nonmatching */
}

/* 8010DB58-8010E448       .text checkNextActionFromButton__9daPy_lk_cFv */
void daPy_lk_c::checkNextActionFromButton() {
    /* Nonmatching */
}

/* 8010E448-8010E75C       .text setShieldGuard__9daPy_lk_cFv */
void daPy_lk_c::setShieldGuard() {
    /* Nonmatching */
}

/* 8010E75C-8010E7C4       .text checkItemModeActorPointer__9daPy_lk_cFv */
void daPy_lk_c::checkItemModeActorPointer() {
    /* Nonmatching */
}

/* 8010E7C4-8010E828       .text checkNextActionItemFly__9daPy_lk_cFv */
void daPy_lk_c::checkNextActionItemFly() {
    /* Nonmatching */
}

/* 8010E828-8010EC78       .text checkNextMode__9daPy_lk_cFi */
void daPy_lk_c::checkNextMode(int) {
    /* Nonmatching */
}

/* 8010EC78-8010ED68       .text checkIceSlipFall__9daPy_lk_cFv */
void daPy_lk_c::checkIceSlipFall() {
    /* Nonmatching */
}

/* 8010ED68-8010F9AC       .text setFrontWallType__9daPy_lk_cFv */
void daPy_lk_c::setFrontWallType() {
    /* Nonmatching */
}

/* 8010F9AC-8010FEC4       .text changeFrontWallTypeProc__9daPy_lk_cFv */
void daPy_lk_c::changeFrontWallTypeProc() {
    /* Nonmatching */
}

/* 8010FEC4-8010FFB0       .text changeSlideProc__9daPy_lk_cFv */
void daPy_lk_c::changeSlideProc() {
    /* Nonmatching */
}

/* 8010FFB0-80110028       .text changeWaitProc__9daPy_lk_cFv */
void daPy_lk_c::changeWaitProc() {
    /* Nonmatching */
}

/* 80110028-8011029C       .text changeLandProc__9daPy_lk_cFf */
void daPy_lk_c::changeLandProc(f32) {
    /* Nonmatching */
}

/* 8011029C-80110338       .text setDamagePoint__9daPy_lk_cFf */
void daPy_lk_c::setDamagePoint(f32) {
    /* Nonmatching */
}

/* 80110338-80110448       .text checkNormalDamage__9daPy_lk_cFi */
void daPy_lk_c::checkNormalDamage(int) {
    /* Nonmatching */
}

/* 80110448-801104E4       .text setDashDamage__9daPy_lk_cFv */
void daPy_lk_c::setDashDamage() {
    /* Nonmatching */
}

/* 801104E4-8011054C       .text checkAtHitEnemy__9daPy_lk_cFP12dCcD_GObjInf */
void daPy_lk_c::checkAtHitEnemy(dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 8011054C-801105D8       .text checkElecReturnDamage__9daPy_lk_cFP12dCcD_GObjInfP4cXyz */
void daPy_lk_c::checkElecReturnDamage(dCcD_GObjInf*, cXyz*) {
    /* Nonmatching */
}

/* 801105D8-80110654       .text checkWallAtributeDamage__9daPy_lk_cFP12dBgS_AcchCir */
void daPy_lk_c::checkWallAtributeDamage(dBgS_AcchCir*) {
    /* Nonmatching */
}

/* 80110654-80110F3C       .text changeDamageProc__9daPy_lk_cFv */
void daPy_lk_c::changeDamageProc() {
    /* Nonmatching */
}

/* 80110F3C-80111424       .text changeAutoJumpProc__9daPy_lk_cFv */
void daPy_lk_c::changeAutoJumpProc() {
    /* Nonmatching */
}

/* 80111424-80111A80       .text changeDemoProc__9daPy_lk_cFv */
void daPy_lk_c::changeDemoProc() {
    /* Nonmatching */
}

/* 80111A80-80111B80       .text changeDeadProc__9daPy_lk_cFv */
void daPy_lk_c::changeDeadProc() {
    /* Nonmatching */
}

/* 80111B80-80111D64       .text getDamageVec__9daPy_lk_cFP12dCcD_GObjInf */
void daPy_lk_c::getDamageVec(dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 80111D64-80111E54       .text setOldRootQuaternion__9daPy_lk_cFsss */
void daPy_lk_c::setOldRootQuaternion(s16, s16, s16) {
    /* Nonmatching */
}

/* 80111E54-80111EFC       .text checkRestHPAnime__9daPy_lk_cFv */
void daPy_lk_c::checkRestHPAnime() {
    /* Nonmatching */
}

/* 80111EFC-80111F5C       .text checkHeavyStateOn__9daPy_lk_cFv */
BOOL daPy_lk_c::checkHeavyStateOn() {
    if (!dComIfGp_event_runCheck() && mDemo.getDemoType() == 0 &&
        (getHeavyStateAndBoots() || checkGrabSpecialHeavyState()))
    {
        return TRUE;
    }
    return FALSE;
}

/* 80111F5C-80111F7C       .text checkBottleItem__9daPy_lk_cCFi */
BOOL daPy_lk_c::checkBottleItem(int itemNo) const {
    return itemNo >= EMPTY_BOTTLE && itemNo <= UNK_BOTTLE_60;
}

/* 80111F7C-80111FEC       .text checkDrinkBottleItem__9daPy_lk_cCFi */
void daPy_lk_c::checkDrinkBottleItem(int) const {
    /* Nonmatching */
}

/* 80111FEC-8011201C       .text checkOpenBottleItem__9daPy_lk_cCFi */
void daPy_lk_c::checkOpenBottleItem(int) const {
    /* Nonmatching */
}

/* 8011201C-80112044       .text checkBowItem__9daPy_lk_cCFi */
BOOL daPy_lk_c::checkBowItem(int) const {
    /* Nonmatching */
}

/* 80112044-80112064       .text checkPhotoBoxItem__9daPy_lk_cCFi */
void daPy_lk_c::checkPhotoBoxItem(int) const {
    /* Nonmatching */
}

/* 80112064-80112100       .text checkScopeEnd__9daPy_lk_cFv */
void daPy_lk_c::checkScopeEnd() {
    /* Nonmatching */
}

/* 80112100-8011215C       .text setSubjectMode__9daPy_lk_cFv */
void daPy_lk_c::setSubjectMode() {
    /* Nonmatching */
}

/* 8011215C-801121C8       .text checkMaskDraw__9daPy_lk_cFv */
void daPy_lk_c::checkMaskDraw() {
    /* Nonmatching */
}

/* 801121C8-80112280       .text checkSubjectEnd__9daPy_lk_cFi */
void daPy_lk_c::checkSubjectEnd(int) {
    /* Nonmatching */
}

/* 80112280-80112330       .text checkGuardAccept__9daPy_lk_cFv */
BOOL daPy_lk_c::checkGuardAccept() {
    if (mProcFlags & 0x40 && !checkBowAnime()) {
        u32 stageType = dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo());
        if (stageType != 2 ||
            strcmp(dComIfGp_getStartStageName(), "Ojhous") == 0 ||
            strcmp(dComIfGp_getStartStageName(), "Orichh") == 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}

/* 80112330-80112348       .text cancelNoDamageMode__9daPy_lk_cFv */
void daPy_lk_c::cancelNoDamageMode() {
    /* Nonmatching */
}

/* 80112348-80112954       .text commonProcInit__9daPy_lk_cFQ29daPy_lk_c9daPy_PROC */
BOOL daPy_lk_c::commonProcInit(daPy_lk_c::daPy_PROC procID) {
    ProcInitTableEntry& procInit = mProcInitTable[procID];
    
    s32 temp_r29;
    BOOL resetDemoAnime = FALSE;
    s32 temp_r28;
    
    if (mCurProcID == PROC_SLIP_e) {
        mDoAud_seStop(JA_SE_LK_RUN_SLIP, 0);
    } else if (mCurProcID == PROC_GRAB_MISS_e || (mCurProcID == PROC_GRAB_READY_e && procID != PROC_GRAB_MISS_e)) {
        mActorKeepRope.clearData();
    } else if (mCurProcID == DPROC_TALISMAN_WAIT_e) {
        seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
        mpHeldItemModel = NULL;
    } else if (mCurProcID == PROC_FAN_SWING_e) {
        setSmallFanModel();
    } else if (mCurProcID == PROC_FAN_GLIDE_e) {
        deleteEquipItem(0);
        mMaxFallSpeed = daPy_HIO_autoJump_c0::m.field_0x10;
        setSmallFanModel();
        mHeldItemType = DEKU_LEAF;
        m35F0 = m3688.y;
        m3730 = cXyz::Zero;
        m34E0 = 0;
        m34E4 = 0;
    } else if (mCurProcID == PROC_SLOW_FALL_e) {
        mMaxFallSpeed = daPy_HIO_autoJump_c0::m.field_0x10;
    } else if (mCurProcID == DPROC_TOOL_e) {
        resetDemoAnime = TRUE;
        speed.y = 0.0f;
    } else if (mCurProcID == DPROC_GET_ITEM_e || mCurProcID == DPROC_GET_DANCE_e) {
        dKy_Itemgetcol_chg_off();
        if (mCurProcID == DPROC_GET_ITEM_e && m34D8 != 0) {
            m34C2 = 0xB;
        }
    } else if (mCurProcID == DPROC_PRESENT_e || mCurProcID == PROC_NOT_USE_e) {
        daItemBase_c* item = (daItemBase_c*)fopAcM_getItemEventPartner(this);
        if (item && (fopAcM_GetName(item) == PROC_ITEM || fopAcM_GetName(item) == PROC_Demo_Item)) {
            item->dead();
        }
    } else if (mCurProcID == DPROC_LETTER_READ_e) {
        deleteEquipItem(0);
    } else if (mCurProcID == PROC_CUT_ROLL_END_e) {
        if (m33A8.getEmitter()) {
            m33A8.getEmitter()->setGlobalAlpha(0);
        }
    } else if (mCurProcID == PROC_SHIP_BOW_e) {
        deleteArrow();
    }
    
    returnKeepItemData();
    
    temp_r28 = (mProcFlags & 0x40000) >> 0x12;
    
    if (mProcFlags & 0x10040820) {
        m34C2 = 0xA;
    }
    
    temp_r29 = ((mProcFlags & 0x2) >> 1) ^ 1;
    
    mCurProcID = procID;
    mCurProcFunc = procInit.mProcFunc;
    m3598 = 0.0f;
    mProcFlags = procInit.mProcFlags;
    
    if (m34C2 == 1) {
        m34C2 = 2;
    }
    
    if (mProcFlags & 0x10040820) {
        m34C2 = 0xB;
    }
    
    if (mProcFlags & 0x20) {
        mAcch.OffLineCheck();
    } else {
        mAcch.OnLineCheck();
    }
    
    dComIfGp_clearPlayerStatus0(0, ~0x00400010);
    dComIfGp_clearPlayerStatus1(0, ~0xFFF48400);
    
    mGravity = daPy_HIO_autoJump_c0::m.field_0xC;
    m34F2 = 0;
    m34F4 = 0;
    onResetFlg0(daPyRFlg0_UNK8000000);
    m34C5 = 0;
    offNoResetFlg0(daPyFlg0_UNK4);
    offResetFlg0(daPyRFlg0_UNK2);
    offNoResetFlg1(daPyFlg1_UNK8000000);
    
    m3544 = 0;
    mSightPacket.offDrawFlg();
    mSightPacket.offLockFlg();
    m35C4 = 0.0f;
    mFanSwingCb.onAlphaOutFlg();
    shape_angle.x = 0;
    shape_angle.z = 0;
    m34EC = 0;
    
    if (!(checkEquipAnime() && (mProcFlags & 0x4)) && !(mProcFlags & 0x1000)) {
        if (!(checkGrabAnime() || checkBoomerangThrowAnime()) || !(mProcFlags & 0x4000)) {
            resetActAnimeUpper(UPPER_UNK2, -1.0f);
            if (!(mProcFlags & 0x00100000)) {
                freeGrabItem();
            }
        }
    }
    
    if (!(mProcFlags & 0x00100000) && !checkGrabAnime() && mActorKeepGrab.getActor()) {
        freeGrabItem();
    }
    
    if (temp_r29 && (mProcFlags & 2)) {
        m3688 = current.pos;
        m35F0 = m3688.y;
        m35F4 = m3688.y;
    }
    
    if (mCurProcID != PROC_SWIM_MOVE_e) {
        mSwimTailEcallBack[0].onEnd();
        mSwimTailEcallBack[1].onEnd();
    }
    
    if (!(mProcFlags & 0x40000)) {
        m3608 = 0.0f;
    }
    
    resetFootEffect();
    
    if (resetDemoAnime) {
        resetDemoTextureAnime();
    }
    
    m338C.end();
    m33A8.end();
    m32E4.end();
    m32F0.end();
    mSmokeEcallBack.end();
    
    if (!checkGrabWear()) {
        m35D8 = 0.0f;
    }
    
    offNoResetFlg1(static_cast<daPy_FLG1>(daPyFlg1_UNK80 | daPyFlg1_UNK800000 | daPyFlg1_UNK1000000));
    
    m35EC = 0.0f;
    
    if (mHeldItemType == HUMMER) {
        mSwordAnim.changeBckOnly(getItemAnimeResource(0x97));
    } else if (checkBowItem(mHeldItemType) && !checkBowAnime()) {
        mSwordAnim.changeBckOnly(getItemAnimeResource(0xD));
    }
    
    m35E8 = 0.0f;
    
    if (!(mProcFlags & 0x800) && mCurProcID != PROC_ROPE_SUBJECT_e && mCurProcID != PROC_ROPE_MOVE_e) {
        freeRopeItem();
    }
    if (!(mProcFlags & 0x200)) {
        freeHookshotItem();
    }
    if (temp_r28 && !(mProcFlags & 0x40000)) {
        swimOutAfter(0);
    }
    
    g_dComIfG_gameInfo.play.field_0x4941 = 0; // is this dComIfGp_setAdvanceDirection__FUc?
    
    setBgCheckParam();
    
    return TRUE;
}

/* 80112954-80112A24       .text procScope_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procScope_init(int) {
    /* Nonmatching */
}

/* 80112A24-80112AA8       .text procScope__9daPy_lk_cFv */
BOOL daPy_lk_c::procScope() {
    /* Nonmatching */
}

/* 80112AA8-80112B18       .text procSubjectivity_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSubjectivity_init(int) {
    /* Nonmatching */
}

/* 80112B18-80112BEC       .text procSubjectivity__9daPy_lk_cFv */
BOOL daPy_lk_c::procSubjectivity() {
    /* Nonmatching */
}

/* 80112BEC-80112C90       .text procCall_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCall_init() {
    /* Nonmatching */
}

/* 80112C90-80112D38       .text procCall__9daPy_lk_cFv */
BOOL daPy_lk_c::procCall() {
    /* Nonmatching */
}

/* 80112D38-80112DF4       .text procControllWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procControllWait_init() {
    /* Nonmatching */
}

/* 80112DF4-80112E60       .text procControllWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procControllWait() {
    /* Nonmatching */
}

/* 80112E60-80113044       .text procWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWait_init() {
    /* Nonmatching */
}

/* 80113044-801133FC       .text procWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procWait() {
    /* Nonmatching */
}

/* 801133FC-801134A0       .text procFreeWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procFreeWait_init() {
    /* Nonmatching */
}

/* 801134A0-801135C4       .text procFreeWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procFreeWait() {
    /* Nonmatching */
}

/* 801135C4-80113628       .text procMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procMove_init() {
    /* Nonmatching */
}

/* 80113628-801136D4       .text procMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procMove() {
    /* Nonmatching */
}

/* 801136D4-80113738       .text procAtnMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnMove_init() {
    /* Nonmatching */
}

/* 80113738-801137B4       .text procAtnMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnMove() {
    /* Nonmatching */
}

/* 801137B4-8011388C       .text procAtnActorWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorWait_init() {
    /* Nonmatching */
}

/* 8011388C-801138FC       .text procAtnActorWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorWait() {
    /* Nonmatching */
}

/* 801138FC-80113960       .text procAtnActorMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorMove_init() {
    /* Nonmatching */
}

/* 80113960-801139C0       .text procAtnActorMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procAtnActorMove() {
    /* Nonmatching */
}

/* 801139C0-80113AC4       .text procSideStep_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSideStep_init(int) {
    /* Nonmatching */
}

/* 80113AC4-80113BDC       .text procSideStep__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideStep() {
    /* Nonmatching */
}

/* 80113BDC-80113CBC       .text procSideStepLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideStepLand_init() {
    /* Nonmatching */
}

/* 80113CBC-80113D30       .text procSideStepLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideStepLand() {
    /* Nonmatching */
}

/* 80113D30-80113DBC       .text procCrouchDefense_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouchDefense_init() {
    /* Nonmatching */
}

/* 80113DBC-80114014       .text procCrouchDefense__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouchDefense() {
    /* Nonmatching */
}

/* 80114014-801142F4       .text procCrouchDefenseSlip_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouchDefenseSlip_init() {
    /* Nonmatching */
}

/* 801142F4-801143D4       .text procCrouchDefenseSlip__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouchDefenseSlip() {
    /* Nonmatching */
}

/* 801143D4-80114440       .text procCrouch_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouch_init() {
    /* Nonmatching */
}

/* 80114440-8011476C       .text procCrouch__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrouch() {
    /* Nonmatching */
}

/* 8011476C-80114804       .text procWaitTurn_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWaitTurn_init() {
    /* Nonmatching */
}

/* 80114804-80114908       .text procWaitTurn__9daPy_lk_cFv */
BOOL daPy_lk_c::procWaitTurn() {
    /* Nonmatching */
}

/* 80114908-801149EC       .text procMoveTurn_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procMoveTurn_init(int) {
    /* Nonmatching */
}

/* 801149EC-80114A60       .text procMoveTurn__9daPy_lk_cFv */
BOOL daPy_lk_c::procMoveTurn() {
    /* Nonmatching */
}

/* 80114A60-80114B28       .text procSlip_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlip_init() {
    /* Nonmatching */
}

/* 80114B28-80114D2C       .text procSlip__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlip() {
    /* Nonmatching */
}

/* 80114D2C-80114DE4       .text procSlideFront_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procSlideFront_init(s16) {
    /* Nonmatching */
}

/* 80114DE4-80114EE8       .text procSlideFront__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideFront() {
    /* Nonmatching */
}

/* 80114EE8-80114FA0       .text procSlideBack_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procSlideBack_init(s16) {
    /* Nonmatching */
}

/* 80114FA0-801150B0       .text procSlideBack__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideBack() {
    /* Nonmatching */
}

/* 801150B0-80115118       .text procSlideFrontLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideFrontLand_init() {
    /* Nonmatching */
}

/* 80115118-801151C8       .text procSlideFrontLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideFrontLand() {
    /* Nonmatching */
}

/* 801151C8-80115220       .text procSlideBackLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideBackLand_init() {
    /* Nonmatching */
}

/* 80115220-801152D0       .text procSlideBackLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlideBackLand() {
    /* Nonmatching */
}

/* 801152D0-80115478       .text procFrontRoll_init__9daPy_lk_cFf */
BOOL daPy_lk_c::procFrontRoll_init(f32) {
    /* Nonmatching */
}

/* 80115478-80115628       .text procFrontRoll__9daPy_lk_cFv */
BOOL daPy_lk_c::procFrontRoll() {
    /* Nonmatching */
}

/* 80115628-801157D8       .text procFrontRollCrash_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procFrontRollCrash_init() {
    /* Nonmatching */
}

/* 801157D8-801158AC       .text procFrontRollCrash__9daPy_lk_cFv */
BOOL daPy_lk_c::procFrontRollCrash() {
    /* Nonmatching */
}

/* 801158AC-8011590C       .text procNockBackEnd_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procNockBackEnd_init() {
    /* Nonmatching */
}

/* 8011590C-80115968       .text procNockBackEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procNockBackEnd() {
    /* Nonmatching */
}

/* 80115968-80115A18       .text procSideRoll_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideRoll_init() {
    /* Nonmatching */
}

/* 80115A18-80115B08       .text procSideRoll__9daPy_lk_cFv */
BOOL daPy_lk_c::procSideRoll() {
    /* Nonmatching */
}

/* 80115B08-80115BFC       .text procBackJump_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJump_init() {
    /* Nonmatching */
}

/* 80115BFC-80115CA0       .text procBackJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJump() {
    /* Nonmatching */
}

/* 80115CA0-80115DA8       .text procBackJumpLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJumpLand_init() {
    /* Nonmatching */
}

/* 80115DA8-80115E88       .text procBackJumpLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procBackJumpLand() {
    /* Nonmatching */
}

/* 80115E88-80115EA4       .text checkAutoJumpFlying__9daPy_lk_cCFv */
int daPy_lk_c::checkAutoJumpFlying() const {
    return mCurProcID != PROC_AUTO_JUMP_e ? -1 : m34D0;
}

/* 80115EA4-8011602C       .text procAutoJump_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procAutoJump_init() {
    /* Nonmatching */
}

/* 8011602C-801163D4       .text procAutoJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procAutoJump() {
    /* Nonmatching */
}

/* 801163D4-8011651C       .text procLand_init__9daPy_lk_cFfi */
BOOL daPy_lk_c::procLand_init(f32, int) {
    /* Nonmatching */
}

/* 8011651C-801165B4       .text procLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procLand() {
    /* Nonmatching */
}

/* 801165B4-80116768       .text procLandDamage_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procLandDamage_init(int) {
    /* Nonmatching */
}

/* 80116768-80116864       .text procLandDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procLandDamage() {
    /* Nonmatching */
}

/* 80116864-80116A38       .text procFall_init__9daPy_lk_cFif */
BOOL daPy_lk_c::procFall_init(int, f32) {
    /* Nonmatching */
}

/* 80116A38-80116C14       .text procFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procFall() {
    /* Nonmatching */
}

/* 80116C14-80116CC4       .text procSlowFall_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlowFall_init() {
    /* Nonmatching */
}

/* 80116CC4-80116D3C       .text procSlowFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procSlowFall() {
    /* Nonmatching */
}

/* 80116D3C-80116EB4       .text procSmallJump_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procSmallJump_init(int) {
    /* Nonmatching */
}

/* 80116EB4-80116F54       .text procSmallJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procSmallJump() {
    /* Nonmatching */
}

/* 80116F54-80116FEC       .text procVerticalJump_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procVerticalJump_init() {
    /* Nonmatching */
}

/* 80116FEC-80117088       .text procVerticalJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procVerticalJump() {
    /* Nonmatching */
}

/* 80117088-801170F0       .text procGuardCrash__9daPy_lk_cFv */
BOOL daPy_lk_c::procGuardCrash() {
    /* Nonmatching */
}

/* 801170F0-80117448       .text procDamage_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procDamage_init() {
    /* Nonmatching */
}

/* 80117448-801176FC       .text procDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procDamage() {
    /* Nonmatching */
}

/* 801176FC-80117794       .text procPolyDamage_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procPolyDamage_init() {
    /* Nonmatching */
}

/* 80117794-801177CC       .text procPolyDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procPolyDamage() {
    /* Nonmatching */
}

/* 801177CC-80117EAC       .text procLargeDamage_init__9daPy_lk_cFiiss */
BOOL daPy_lk_c::procLargeDamage_init(int, int, s16, s16) {
    /* Nonmatching */
}

/* 80117EAC-8011810C       .text procLargeDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procLargeDamage() {
    /* Nonmatching */
}

/* 8011810C-80118504       .text procLargeDamageUp_init__9daPy_lk_cFiiss */
BOOL daPy_lk_c::procLargeDamageUp_init(int, int, s16, s16) {
    /* Nonmatching */
}

/* 80118504-80118640       .text procLargeDamageUp__9daPy_lk_cFv */
BOOL daPy_lk_c::procLargeDamageUp() {
    /* Nonmatching */
}

/* 80118640-801189AC       .text procLargeDamageWall_init__9daPy_lk_cFiiss */
BOOL daPy_lk_c::procLargeDamageWall_init(int, int, s16, s16) {
    /* Nonmatching */
}

/* 801189AC-801189F0       .text procLargeDamageWall__9daPy_lk_cFv */
BOOL daPy_lk_c::procLargeDamageWall() {
    /* Nonmatching */
}

/* 801189F0-80118BC4       .text procLavaDamage_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procLavaDamage_init() {
    /* Nonmatching */
}

/* 80118BC4-80118C58       .text procLavaDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procLavaDamage() {
    /* Nonmatching */
}

/* 80118C58-80118E6C       .text procElecDamage_init__9daPy_lk_cFPC4cXyz */
BOOL daPy_lk_c::procElecDamage_init(const cXyz*) {
    /* Nonmatching */
}

/* 80118E6C-80118F40       .text procElecDamage__9daPy_lk_cFv */
BOOL daPy_lk_c::procElecDamage() {
    /* Nonmatching */
}

/* 80118F40-80119248       .text procGuardSlip_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procGuardSlip_init() {
    /* Nonmatching */
}

/* 80119248-80119334       .text procGuardSlip__9daPy_lk_cFv */
BOOL daPy_lk_c::procGuardSlip() {
    /* Nonmatching */
}

/* 80119334-80119478       .text procIceSlipFall_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipFall_init() {
    /* Nonmatching */
}

/* 80119478-80119500       .text procIceSlipFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipFall() {
    /* Nonmatching */
}

/* 80119500-80119688       .text procIceSlipFallUp_init__9daPy_lk_cFiss */
BOOL daPy_lk_c::procIceSlipFallUp_init(int, s16, s16) {
    /* Nonmatching */
}

/* 80119688-8011970C       .text procIceSlipFallUp__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipFallUp() {
    /* Nonmatching */
}

/* 8011970C-801197D4       .text procIceSlipAlmostFall_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipAlmostFall_init() {
    /* Nonmatching */
}

/* 801197D4-80119864       .text procIceSlipAlmostFall__9daPy_lk_cFv */
BOOL daPy_lk_c::procIceSlipAlmostFall() {
    /* Nonmatching */
}

/* 80119864-801198E0       .text procBootsEquip_init__9daPy_lk_cFUs */
BOOL daPy_lk_c::procBootsEquip_init(u16) {
    /* Nonmatching */
}

/* 801198E0-80119A5C       .text procBootsEquip__9daPy_lk_cFv */
BOOL daPy_lk_c::procBootsEquip() {
    /* Nonmatching */
}

/* 80119A5C-80119BA0       .text procNotUse_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procNotUse_init(int) {
    /* Nonmatching */
}

/* 80119BA0-80119DA0       .text procNotUse__9daPy_lk_cFv */
BOOL daPy_lk_c::procNotUse() {
    /* Nonmatching */
}

/* 80119DA0-80119EBC       .text getGroundAngle__9daPy_lk_cFP13cBgS_PolyInfos */
void daPy_lk_c::getGroundAngle(cBgS_PolyInfo*, s16) {
    /* Nonmatching */
}

/* 80119EBC-8011A508       .text setLegAngle__9daPy_lk_cFfiPsPs */
void daPy_lk_c::setLegAngle(f32, int, s16*, s16*) {
    /* Nonmatching */
}

/* 8011A508-8011ABB0       .text footBgCheck__9daPy_lk_cFv */
void daPy_lk_c::footBgCheck() {
    /* Nonmatching */
}

/* 8011ABB0-8011AC78       .text setWaterY__9daPy_lk_cFv */
void daPy_lk_c::setWaterY() {
    /* Nonmatching */
}

/* 8011AC78-8011AD9C       .text autoGroundHit__9daPy_lk_cFv */
void daPy_lk_c::autoGroundHit() {
    /* Nonmatching */
}

/* 8011AD9C-8011AE20       .text checkAttentionPosAngle__9daPy_lk_cFP10fopAc_ac_cPP4cXyz */
void daPy_lk_c::checkAttentionPosAngle(fopAc_ac_c*, cXyz**) {
    /* Nonmatching */
}

/* 8011AE20-8011BE08       .text setNeckAngle__9daPy_lk_cFv */
void daPy_lk_c::setNeckAngle() {
    /* Nonmatching */
}

/* 8011BE08-8011BEA4       .text checkOriginalHatAnimation__9daPy_lk_cFv */
void daPy_lk_c::checkOriginalHatAnimation() {
    /* Nonmatching */
}

/* 8011BEA4-8011CBA4       .text setHatAngle__9daPy_lk_cFv */
void daPy_lk_c::setHatAngle() {
    /* Nonmatching */
}

/* 8011CBA4-8011CCF4       .text setMoveSlantAngle__9daPy_lk_cFv */
void daPy_lk_c::setMoveSlantAngle() {
    /* Nonmatching */
}

/* 8011CCF4-8011CDB4       .text setWaistAngle__9daPy_lk_cFv */
void daPy_lk_c::setWaistAngle() {
    /* Nonmatching */
}

/* 8011CDB4-8011D070       .text setWorldMatrix__9daPy_lk_cFv */
void daPy_lk_c::setWorldMatrix() {
    /* Nonmatching */
}

/* 8011D070-8011D0E4       .text setAtParam__9daPy_lk_cFUli11dCcG_At_SplUcUcUcf */
void daPy_lk_c::setAtParam(u32, int, dCcG_At_Spl, u8, u8, u8, f32) {
    /* Nonmatching */
}

/* 8011D0E4-8011D110       .text resetCurse__9daPy_lk_cFv */
void daPy_lk_c::resetCurse() {
    /* Nonmatching */
}

/* 8011D110-8011D4D0       .text checkLightHit__9daPy_lk_cFv */
void daPy_lk_c::checkLightHit() {
    /* Nonmatching */
}

/* 8011D4D0-8011D6C4       .text setSwordAtCollision__9daPy_lk_cFv */
void daPy_lk_c::setSwordAtCollision() {
    /* Nonmatching */
}

/* 8011D6C4-8011D788       .text getBlurTopRate__9daPy_lk_cFv */
void daPy_lk_c::getBlurTopRate() {
    /* Nonmatching */
}

/* 8011D788-8011EC0C       .text setCollision__9daPy_lk_cFv */
void daPy_lk_c::setCollision() {
    /* Nonmatching */
}

/* 8011EC0C-8011EEBC       .text setAttentionPos__9daPy_lk_cFv */
void daPy_lk_c::setAttentionPos() {
    /* Nonmatching */
}

/* 8011EEBC-8011EF94       .text setRoomInfo__9daPy_lk_cFv */
void daPy_lk_c::setRoomInfo() {
    /* Nonmatching */
}

/* 8011EF94-8011F9C0       .text setDemoData__9daPy_lk_cFv */
void daPy_lk_c::setDemoData() {
    /* Nonmatching */
}

/* 8011F9C0-8011FF50       .text setStickData__9daPy_lk_cFv */
void daPy_lk_c::setStickData() {
    /* Nonmatching */
}

/* 8011FF50-801200F8       .text setBgCheckParam__9daPy_lk_cFv */
void daPy_lk_c::setBgCheckParam() {
    mAcchCir[0].SetWallH(30.1f);
    mAcchCir[1].SetWallH(89.9f);
    mAcchCir[2].SetWallH(125.0f);
    
    if (mCurProcID == PROC_ROPE_SWING_START_e) {
        mAcchCir[0].SetWallH(-125.0f);
        mAcchCir[1].SetWallH(-89.9f);
        mAcchCir[2].SetWallH(0.0f);
    } else if (mCurProcID == PROC_LARGE_DAMAGE_WALL_e || mProcFlags & 0x410000) {
        mAcchCir[0].SetWallR(5.0f);
    } else if (mProcFlags & 0x200000) {
        mAcchCir[0].SetWallR(40.0f);
    } else if (mProcFlags & 0x10) {
        mAcchCir[0].SetWallR(daPy_HIO_wall_c0::m.field_0x50);
        if (checkNoResetFlg0(daPyFlg0_UNK10000)) {
            mAcchCir[2].SetWallH(89.9f);
        }
    } else if (mProcFlags & 0x40000) {
        mAcchCir[0].SetWallR(67.5f);
        mAcchCir[0].SetWallH(-5.0f);
        mAcchCir[1].SetWallH(0.0f);
        mAcchCir[2].SetWallH(20.0f);
    } else if (mProcFlags & 0x1000000 && mCurProcID != PROC_CRAWL_END_e) {
        mAcchCir[0].SetWallR(30.0f);
        mAcchCir[0].SetWallH(10.0f);
        mAcchCir[1].SetWallH(50.0f);
        mAcchCir[2].SetWallH(50.0f);
    } else if (mProcFlags & 0x20) {
        mAcchCir[0].SetWallR(12.5f);
        mAcchCir[0].SetWallH(25.0f);
        mAcchCir[1].SetWallH(25.0f);
        mAcchCir[2].SetWallH(25.0f);
    } else if (checkGrabWear()) {
        mAcchCir[0].SetWallR(50.0f);
    } else {
        mAcchCir[0].SetWallR(35.0f);
    }
    
    mAcchCir[1].SetWallR(mAcchCir[0].GetWallR());
    mAcchCir[2].SetWallR(mAcchCir[0].GetWallR());
}

/* 801200F8-8012010C       .text setParamData__9daPy_lk_cFiiii */
u32 daPy_lk_c::setParamData(int roomNo, int spawnType, int eventInfoIdx, int extraParams) {
    return roomNo & 0x3F | (spawnType & 0xF) << 0xC | eventInfoIdx << 0x18 | extraParams;
}

/* 8012010C-8012024C       .text checkLavaFace__9daPy_lk_cFP4cXyzi */
BOOL daPy_lk_c::checkLavaFace(cXyz* param_1, int attributeCode) {
    if (mDemo.getDemoType() == 5) {
        return FALSE;
    }
    
    if (param_1) {
        cXyz temp(current.pos.x, param_1->y + 20.0f, current.pos.z);
        m08EC.SetPos(&temp);
        m35D4 = dComIfG_Bgsp()->GroundCross(&m08EC);
        if (mAcch.GetGroundH() > m35D4) {
            m35D4 = -1000000000.0f;
        }
        if (m35D4 > current.pos.y) {
            attributeCode = dComIfG_Bgsp()->GetAttributeCode(m08EC);
        } else {
            return FALSE;
        }
    }
    
    if (attributeCode == 6) {
        if (param_1) {
            current.pos.y = m35D4;
        }
        if (checkBossGomaStage()) {
            return procLavaDamage_init();
        } else {
            return dProcLavaDamage_init();
        }
    } else if (attributeCode == 8) {
        startRestartRoom(5, 0xC9, -1.0f, 0);
    }
    
    return FALSE;
}

/* 8012024C-80120724       .text checkFallCode__9daPy_lk_cFv */
void daPy_lk_c::checkFallCode() {
    /* Nonmatching */
}

/* 80120724-80120BBC       .text startRestartRoom__9daPy_lk_cFUlifi */
BOOL daPy_lk_c::startRestartRoom(u32 param_1, int eventInfoIdx, f32 param_3, int i_point) {
    /* Nonmatching - npc_sarace */
    if (!checkNoResetFlg0(daPyFlg0_UNK4000) && (i_point != 0 || dComIfGp_event_compulsory(this, NULL, -1))) {
        mDemo.setOriginalDemoType();
        if (i_point == 0) {
            mDemo.setDemoMode(1);
        }
        onNoResetFlg0(daPyFlg0_UNK4000);
        changePlayer(this);
        
        if (dComIfGp_getMiniGameType() == 1) {
            dComIfGp_setNextStage("sea", 1, 48, -1, 0.0f, 0, 1, 0);
            mDoAud_seStart(JA_SE_FORCE_BACK, NULL, 0, 0);
            // daNpc_Sarace_c::ship_race_result = 3;
            mTinkleShieldTimer = 0;
            return TRUE;
        } else {
            u32 stageType = dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo());
            setDamagePoint(param_3);
            mTinkleShieldTimer = 0;
            
            if (stageType == 7 && !dComIfGs_isEventBit(0x2A08) && (current.roomNo == 11 || current.roomNo == 44) && dStage_chkPlayerId(0x80, current.roomNo)) {
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), 0x80, current.roomNo, -1, 0.0f, param_1, 1, 0);
                u32 roomParam = setParamData(-1, 0, eventInfoIdx, 0);
                dComIfGs_setRestartRoomParam(roomParam);
                mDoAud_seStart(JA_SE_FORCE_BACK, NULL, 0, 0);
                return TRUE;
            }
            
            if (checkNoResetFlg0(daPyFlg0_UNK10) && mCurProcID != DPROC_DEAD_e) {
                i_point = m34CB;
            } else {
                i_point = m3594;
                if (i_point != 0xFF && !dComIfGs_checkSeaLandingEvent(current.roomNo)) {
                    i_point = 0xFF;
                }
            }
            
            if (i_point == 0xFF) {
                if (stageType == 7) {
                    cXyz* pos;
                    if (dComIfGp_getShipActor()) {
                        pos = &((fopAc_ac_c*)dComIfGp_getShipActor())->current.pos;
                    } else {
                        pos = &current.pos;
                    }
                    
                    int quad_x = (1.0f/50000.0f) * (350000.0f + pos->x);
                    int quad_z = (1.0f/50000.0f) * (350000.0f + pos->z);
                    if (quad_x < 0) {
                        quad_x = 0;
                    } else if (quad_x > 13) {
                        quad_x = 13;
                    }
                    if (quad_z < 0) {
                        quad_z = 0;
                    } else if (quad_z > 13) {
                        quad_z = 13;
                    }
                    
                    int subsector_z = quad_z & 1;
                    int subsector_x = quad_x & 1;
                    int sector_z = quad_z >> 1;
                    int sector_x = quad_x >> 1;
                    int sector_num = sector_z*7 + sector_x;
                    int scls_idx = subsector_x + (sector_num << 2) + (subsector_z << 1);
                    
                    dStage_changeScene(scls_idx, 0.0f, param_1, -1);
                } else {
                    if (mCurProcID == DPROC_DEAD_e) {
                        dStage_changeScene(0, 0.0f, param_1, -1);
                    } else {
                        int roomNo = dComIfGs_getRestartRoomNo();
                        u32 roomParam = setParamData(roomNo, 0, eventInfoIdx, 0);
                        dStage_restartRoom(roomParam, param_1);
                        mDoAud_seStart(JA_SE_FORCE_BACK, NULL, 0, 0);
                    }
                    return TRUE;
                }
            } else if (checkNoResetFlg0(daPyFlg0_UNK10)) {
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), i_point, 41, -1, 0.0f, param_1, 1, 0);
            } else {
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), i_point, current.roomNo, -1, 0.0f, param_1, 1, 0);
            }
            
            if (mCurProcID != DPROC_DEAD_e) {
                u32 roomParam = setParamData(-1, 0, eventInfoIdx, 0);
                dComIfGs_setRestartRoomParam(roomParam);
                mDoAud_seStart(JA_SE_FORCE_BACK, NULL, 0, 0);
            }
            
            return TRUE;
        }
    }
    
    return FALSE;
}

/* 80120BBC-80120BE0       .text checkSuccessGuard__9daPy_lk_cFi */
void daPy_lk_c::checkSuccessGuard(int) {
    /* Nonmatching */
}

/* 80120BE0-80120F94       .text setShapeAngleOnGround__9daPy_lk_cFv */
void daPy_lk_c::setShapeAngleOnGround() {
    /* Nonmatching */
}

/* 80120F94-801211B8       .text setStepsOffset__9daPy_lk_cFv */
void daPy_lk_c::setStepsOffset() {
    /* Nonmatching */
}

/* 801211B8-8012135C       .text setBeltConveyerPower__9daPy_lk_cFv */
void daPy_lk_c::setBeltConveyerPower() {
    /* Nonmatching */
}

/* 8012135C-801216A8       .text setWindAtPower__9daPy_lk_cFv */
void daPy_lk_c::setWindAtPower() {
    /* Nonmatching */
}

/* 801216A8-80121870       .text checkRoofRestart__9daPy_lk_cFv */
void daPy_lk_c::checkRoofRestart() {
    /* Nonmatching */
}

/* 80121870-80122D30       .text execute__9daPy_lk_cFv */
BOOL daPy_lk_c::execute() {
    /* Nonmatching */
}

/* 80122D30-80122D50       .text daPy_Execute__FP9daPy_lk_c */
static BOOL daPy_Execute(daPy_lk_c* i_this) {
    return static_cast<daPy_lk_c*>(i_this)->execute();
}

/* 80122D50-80122D58       .text daPy_IsDelete__FP9daPy_lk_c */
static BOOL daPy_IsDelete(daPy_lk_c*) {
    return TRUE;
}

/* 80122D58-80123058       .text playerDelete__9daPy_lk_cFv */
BOOL daPy_lk_c::playerDelete() {
    int i;
    for (i = 0; i < (int)ARRAY_SIZE(m31E8); i++) {
        m31E8[i].getSmokeCallBack()->end();
        m31E8[i].getOtherCallBack()->end();
    }
    if (mFanSwingCb.mpEmitter) {
        mFanSwingCb.mpEmitter->clearStatus(0x40);
        mFanSwingCb.mpEmitter->setEmitterCallBackPtr(NULL);
        mFanSwingCb.mpEmitter = NULL;
    }
    m338C.end();
    m33A8.end();
    m3280.end();
    m334C.end();
    m336C.end();
    mSwimTailEcallBack[0].remove();
    mSwimTailEcallBack[1].remove();
    m32E4.end();
    m32F0.end();
    m33E8.end();
    mSmokeEcallBack.end();
    m331C.end();
    m332C.end();
    m333C.end();
    m3400.end();
    m3410.end();
    m3438.end();
    m342C.end();
    m3454.end();
    m3460[0].end();
    m3460[1].end();
    
    endDamageEmitter();
    dKy_plight_cut(&mLightInfluence);
    mDoAud_seDeleteObject(&mSwordTopPos);
    mDoAud_seDeleteObject(&mRopePos);
    mDoAud_seDeleteObject(&m338C.field_0x08);
    mDoAud_seDeleteObject(&mFanWindCps1.GetEndP());
    
    for (i = 0; i < (int)ARRAY_SIZE(m_anm_heap_under); i++) {
        mDoExt_destroySolidHeap(m_anm_heap_under[i].mpAnimeHeap);
    }
    for (i = 0; i < (int)ARRAY_SIZE(m_anm_heap_upper); i++) {
        mDoExt_destroySolidHeap(m_anm_heap_upper[i].mpAnimeHeap);
    }
    
    mDoExt_destroySolidHeap(mpTextureAnimeResHeap);
    mDoExt_destroySolidHeap(mpTextureScrollResHeap);
    mDoExt_destroySolidHeap(mpItemHeaps[0]);
    mDoExt_destroySolidHeap(mpItemHeaps[1]);
    mDoExt_destroySolidHeap(m2ECC);
    
    mJAIZelAnime.stop();
    
    if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES)) {
        *mpCurrLinktex = mOtherLinktex;
    }
    
    dComIfGp_clearPlayerStatus0(0, 0x00400000); // Waiting for the boomerang to come back
    dComIfGp_clearPlayerStatus1(0, 0x00040000);
    g_dComIfG_gameInfo.play.field_0x4947 = 0;
    
    cancelNoDamageMode();
    
    return TRUE;
}

/* 80123058-80123078       .text daPy_Delete__FP9daPy_lk_c */
static BOOL daPy_Delete(daPy_lk_c* i_this) {
    return static_cast<daPy_lk_c*>(i_this)->playerDelete();
}

/* 80123078-80123360       .text initTextureAnime__9daPy_lk_cFv */
void daPy_lk_c::initTextureAnime() {
    /* Nonmatching */
}

/* 80123360-80123830       .text initTextureScroll__9daPy_lk_cFv */
void daPy_lk_c::initTextureScroll() {
    /* Nonmatching */
}

/* 80123834-8012469C       .text createHeap__9daPy_lk_cFv */
BOOL daPy_lk_c::createHeap() {
    /* Nonmatching - data offsets */
    J3DModelData* tmp_modelData;
    J3DAnmTransform* bck;
    J3DAnmTevRegKey* brk;
    int ret;
    
    mpCLModelData = initModel(&mpCLModel, LINK_BDL_CL, 0x37221222);
    tmp_modelData = initModel(&mpHandsModel, LINK_BDL_HANDS, 0x37221222);
    tmp_modelData = initModel(&mpKatsuraModel, LINK_BDL_KATSURA, 0x37221222);
    tmp_modelData = initModel(&mpYamuModel, LINK_BDL_YAMU, 0x37221222);
    tmp_modelData = initModel(&mpPringModel, LINK_BDL_PRING, 0x37221222);
    tmp_modelData = initModel(&mpSwgripaModel, LINK_BDL_SWGRIPA, 0x37221222);
    
    tmp_modelData = initModel(&mpSwgripmsModel, LINK_BDL_SWGRIPMS, 0x37221222);
    bck = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, LINK_BCK_SWGRIPMSAB);
    ret = mSwgripmsabBckAnim.init(mpSwgripmsModel->getModelData(), bck, false, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(21046, 0); }
    mpTswgripmsabBrk = entryBrk(tmp_modelData, LINK_BRK_TSWGRIPMSAB);
    mpTswgripmsBtk = entryBtk(tmp_modelData, LINK_BTK_TSWGRIPMS);
    
    tmp_modelData = initModel(&mpPodmsModel, LINK_BDL_PODMS, 0x37221222);
    
    tmp_modelData = initModel(&mpShaModel, LINK_BDL_SHA, 0x37221222);
    bck = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, LINK_BCK_ATNGSHA);
    ret = mAtngshaBck.init(mpShaModel->getModelData(), bck, false, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(21063, 0); }
    
    tmp_modelData = initModel(&mpShmsModel, LINK_BDL_SHMS, 0x37221222);
    mpTshmsBtk = entryBtk(tmp_modelData, LINK_BTK_TSHMS);
    J3DSkinDeform* shmsSkinDeform = new J3DSkinDeform();
    if (!shmsSkinDeform) { JUT_ASSERT(21077, 0); }
    if (!mpShmsModel->setSkinDeform(shmsSkinDeform, 1)) { JUT_ASSERT(21080, 0); }
    
    tmp_modelData = initModel(&mpYmsls00Model, LINK_BDL_YMSLS00, 0x13000222);
    mpYmsls00Btk = entryBtk(tmp_modelData, LINK_BTK_YMSLS00);
    
    tmp_modelData = initModel(&mpHbootsModelRightFoot, LINK_BDL_HBOOTS, 0x37221222);
    tmp_modelData = initModel(&mpHbootsModelLeftFoot, LINK_BDL_HBOOTS, 0x37221222);
    
    tmp_modelData = initModel(&mpSuimenMunyaModel, LINK_BDL_SUIMEN_MUNYA, 0x11001222);
    mpSuimenMunyaBtk = entryBtk(tmp_modelData, LINK_BTK_SUIMEN_MUNYA);
    
    tmp_modelData = initModel(&mpYuchw00Model, LINK_BDL_YUCHW00, 0x13000222);
    bck = (J3DAnmTransform*)dComIfG_getObjectRes(l_arcName, LINK_BCK_YUCHW00);
    ret = mYuchw00Bck.init(tmp_modelData, bck, 1, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(21113, 0); }
    mpYuchw00Btk = entryBtk(tmp_modelData, LINK_BTK_YUCHW00);
    mpYuchw00Brk = entryBrk(tmp_modelData, LINK_BRK_YUCHW00);
    mpYuchw00Brk->setFrame(mpYuchw00Brk->getFrameMax()-0.001f);
    
    tmp_modelData = initModel(&mpYbafo00Model, LINK_BDL_YBAFO00, 0x13000222);
    mpYbafo00Btk = entryBtk(tmp_modelData, LINK_BTK_YBAFO00);
    mpYbafo00Btk->setFrame(mpYbafo00Btk->getFrameMax()-0.001f);
    
    tmp_modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcName, LINK_BDL_YAURA00);
    JUT_ASSERT(21130, tmp_modelData != 0);
    daPy_aura_c* aura_p = mMagicArmorAuraEntries;
    for (int i = 0; i < 6; i++) {
        aura_p->setModel(mDoExt_J3DModel__create(tmp_modelData, 0x00080000, 0x11001222));
        JUT_ASSERT(21139, aura_p->getModel() != 0);
        aura_p++;
    }
    mpYaura00Btk = entryBtk(tmp_modelData, LINK_BTK_YAURA00);
    brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(l_arcName, LINK_BRK_YAURA00_R);
    ret = mYaura00rBrk.init(tmp_modelData, brk, false, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false, 0);
    if (!ret) { JUT_ASSERT(21147, 0); }
    mYaura00rBrk.setFrame(0.0f);
    
    tmp_modelData = initModel(&mpYmgcs00Model, LINK_BDL_YMGCS00, 0x11001222);
    mpYmgcs00Btk = entryBtk(tmp_modelData, LINK_BTK_YMGCS00);
    brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(l_arcName, LINK_BRK_YMGCS00_MS);
    ret = mYmgcs00Brk.init(tmp_modelData, brk, false, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false, 0);
    if (!ret) { JUT_ASSERT(21161, 0); }
    mYmgcs00Brk.setFrame(0.0f);
    
    tmp_modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcName, LINK_BDL_BOMB);
    JUT_ASSERT(21169, tmp_modelData != 0);
    mpBombBrk = entryBrk(tmp_modelData, LINK_BRK_BOMB);
    
    tmp_modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcName, LINK_BDL_GWP00);
    JUT_ASSERT(21176, tmp_modelData != 0);
    mpGwp00BrkData = entryBrk(tmp_modelData, LINK_BRK_GWP00);
    mpGwp00BtkData = entryBtk(tmp_modelData, LINK_BTK_GWP00);
    
    tmp_modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcName, LINK_BDL_ARROW);
    JUT_ASSERT(21184, tmp_modelData != 0);
    mpIceArrowBtk = entryBtk(tmp_modelData, LINK_BTK_TTIPICE);
    
    tmp_modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcName, LINK_BDL_ARROWGLITTER);
    JUT_ASSERT(21191, tmp_modelData != 0);
    mpLightArrowBtk = entryBtk(tmp_modelData, LINK_BTK_TARROWGLITTER);
    
    tmp_modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcName, LINK_BDL_GICER00);
    JUT_ASSERT(21198, tmp_modelData != 0);
    mpGicer00Btk = entryBtk(tmp_modelData, LINK_BTK_GICER00);
    
    tmp_modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcName, LINK_BDL_GICER01);
    JUT_ASSERT(21198, tmp_modelData != 0);
    mpGicer01Btk = entryBtk(tmp_modelData, LINK_BTK_GICER01);
    
    const int numCLJoints = 0x2A;
    m_old_fdata = new mDoExt_MtxCalcOldFrame(new J3DTransformInfo[numCLJoints], new Quaternion[numCLJoints]);
    JUT_ASSERT(21233, m_old_fdata != 0);
    
    m_pbCalc[PART_UNDER_e] = new mDoExt_MtxCalcAnmBlendTblOld(m_old_fdata, ARRAY_SIZE(mAnmRatioUnder), mAnmRatioUnder);
    JUT_ASSERT(21239, m_pbCalc[PART_UNDER_e] != 0);
    
    m_pbCalc[PART_UPPER_e] = new mDoExt_MtxCalcAnmBlendTblOld(m_old_fdata, ARRAY_SIZE(mAnmRatioUpper), mAnmRatioUpper);
    JUT_ASSERT(21245, m_pbCalc[PART_UPPER_e] != 0);
    
    initTextureScroll();
    initTextureAnime();
    
    m_HIO = new daPy_HIO_c();
    JUT_ASSERT(21254, m_HIO != 0);
    
    m_anm_heap_under[UNDER_MOVE0_e].m_buffer = new(0x20) u8[0xB400];
    JUT_ASSERT(21259, m_anm_heap_under[UNDER_MOVE0_e].m_buffer != 0);
    
    m_sanm_buffer = new(0x20) u8[0x200];
    JUT_ASSERT(21266, m_sanm_buffer != 0);
    
    m_item_bck_buffer = new(0x20) u8[0x1000];
    JUT_ASSERT(21269, m_item_bck_buffer != 0);
    
    return TRUE;
}

/* 8012469C-801249F8       .text createAnimeHeap__9daPy_lk_cFPP12JKRSolidHeapQ29daPy_lk_c14daPy_HEAP_TYPE */
void daPy_lk_c::createAnimeHeap(JKRSolidHeap**, daPy_lk_c::daPy_HEAP_TYPE) {
    /* Nonmatching */
}

/* 80124A40-80124B30       .text initModel__9daPy_lk_cFPP8J3DModeliUl */
J3DModelData* daPy_lk_c::initModel(J3DModel**, int, u32) {
    /* Nonmatching */
}

/* 80124B30-80124BE4       .text entryBtk__9daPy_lk_cFP12J3DModelDatai */
J3DAnmTextureSRTKey* daPy_lk_c::entryBtk(J3DModelData*, int) {
    /* Nonmatching */
}

/* 80124BE4-80124C98       .text entryBrk__9daPy_lk_cFP12J3DModelDatai */
J3DAnmTevRegKey* daPy_lk_c::entryBrk(J3DModelData*, int) {
    /* Nonmatching */
}

/* 80124C98-80125CC8       .text playerInit__9daPy_lk_cFv */
void daPy_lk_c::playerInit() {
    if (!fopAcM_entrySolidHeap(this, (heapCallbackFunc)&daPy_createHeap, 0xB0000)) {
        JUT_ASSERT(0x53B6, 0);
    }
    
    fopAcM_SetMtx(this, mpCLModel->getBaseTRMtx());
    
    mpCLModel->setUserArea(reinterpret_cast<u32>(this));
    mpYmgcs00Model->setUserArea(reinterpret_cast<u32>(this));
    for (u16 i = 0; i < mpYmgcs00Model->getModelData()->getJointNum(); i++) {
        mpYmgcs00Model->getModelData()->getJointNodePointer(i)->setCallBack(daPy_auraCallback);
    }
    
    mpCLModelData->getJointNodePointer(0x01)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x0D)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x04)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x08)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x0C)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x1C)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x0F)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x00)->setCallBack(daPy_jointCallback0);
    mpCLModelData->getJointNodePointer(0x28)->setCallBack(daPy_jointCallback1);
    
    m_pbCalc[0]->setUserArea(reinterpret_cast<u32>(this));
    m_pbCalc[0]->setBeforeCalc(daPy_jointBeforeCallback);
    m_pbCalc[0]->setAfterCalc(daPy_jointAfterCallback);
    m_pbCalc[1]->setUserArea(reinterpret_cast<u32>(this));
    m_pbCalc[1]->setBeforeCalc(daPy_jointBeforeCallback);
    m_pbCalc[1]->setAfterCalc(daPy_jointAfterCallback);
    
    int i;
    J3DMaterial* mat = mpCLModelData->getJointNodePointer(0x13)->getMesh();
    int zoff_blend_cnt = 0;
    int zoff_none_cnt = 0;
    int zon_cnt = 0;
    for (i = 0; i < 2; i++) {
        while (mat) {
            mat->setMaterialMode(1);
            if (j3dZModeTable[mat->getZMode()->mZModeID].mCompareEnable == 0) {
                if (mat->getBlend()->mBlendMode == 1) {
                    mpZOffBlendShape[zoff_blend_cnt] = mat->getShape();
                    zoff_blend_cnt++;
                    JUT_ASSERT(0x53EE, zoff_blend_cnt <= 4);
                } else {
                    mpZOffNoneShape[zoff_none_cnt] = mat->getShape();
                    zoff_none_cnt++;
                    JUT_ASSERT(0x53F2, zoff_none_cnt <= 4);
                }
            } else {
                mpZOnShape[zon_cnt] = mat->getShape();
                zon_cnt++;
                JUT_ASSERT(0x53F6, zon_cnt <= 4);
            }
            mat = mat->getNext();
        }
        mat = mpCLModelData->getJointNodePointer(0x15)->getMesh();
    }
    JUT_ASSERT(0x53FD, zon_cnt == 4);
    JUT_ASSERT(0x53FE, zoff_none_cnt == 4);
    JUT_ASSERT(0x53FF, zoff_blend_cnt == 4);
    
    m03A4 = mpCLModelData->getJointNodePointer(0x08)->getMesh()->getShape();
    m03A8 = mpCLModelData->getJointNodePointer(0x0C)->getMesh()->getShape();
    J3DModelData* handsModelData = mpHandsModel->getModelData();
    for (u16 i = 0x01; i < 0x0B; i++) {
        handsModelData->getJointNodePointer(i)->getMesh()->getShape()->hide();
    }
    
    u32 buffer_start = reinterpret_cast<u32>(m_anm_heap_under[0].m_buffer) + 0x2400;
    m_anm_heap_under[1].m_buffer = reinterpret_cast<void*>(buffer_start);
    buffer_start = reinterpret_cast<u32>(m_anm_heap_under[0].m_buffer) + 0x4800;
    m_anm_heap_upper[0].m_buffer = reinterpret_cast<void*>(buffer_start);
    for (int i = 1; i <= 2; i++) {
        buffer_start = reinterpret_cast<u32>(m_anm_heap_upper[0].m_buffer) + i*0x2400;
        m_anm_heap_upper[i].m_buffer = reinterpret_cast<void*>(buffer_start);
    }
    
    mAcch.Set(&current.pos, &next.pos, this, ARRAY_SIZE(mAcchCir), mAcchCir, &speed, &current.angle, &shape_angle);
    mAcch.ClrWaterNone();
    mAcch.SetWaterCheckOffset(500.0f);
    mAcch.OnLineCheck();
    mAcch.ClrRoofNone();
    mAcch.SetRoofCrrHeight(125.0f);
    field_0x2a8 = daPy_HIO_move_c0::m.field_0x18;
    mGravity = daPy_HIO_autoJump_c0::m.field_0xC;
    mMaxFallSpeed = daPy_HIO_autoJump_c0::m.field_0x10;
    mAcchCir[0].SetWall(30.1f, 35.0f);
    mAcchCir[1].SetWall(89.9f, 35.0f);
    mAcchCir[2].SetWall(125.0f, 35.0f);
    mHeadTopPos.setall(0.0f);
    field_0x2ac = 125.0f;
    mHeldItemType = 0x100;
    mKeepItemType = 0x100;
    mCameraInfoIdx = dComIfGp_getPlayerCameraID(0);
    mpAttention = &dComIfGp_getAttention();
    
    mStts.Init(0x78, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl.OnTgShieldFrontRange();
    mShieldFrontRangeYAngle = shape_angle.y + mBodyAngle.y;
    mCyl.SetTgShieldFrontRangeYAngle(&mShieldFrontRangeYAngle);
    mWindCyl1.Set(l_wind_cyl_src);
    mWindCyl1.SetStts(&mStts);
    mWindCyl2.Set(l_wind_cyl_src);
    mWindCyl2.SetStts(&mStts);
    mWindCyl2.SetTgType(AT_TYPE_LIGHT);
    mAtCps[0].Set(l_at_cps_src);
    mAtCps[0].SetStts(&mStts);
    mAtCps[1].Set(l_at_cps_src);
    mAtCps[1].SetStts(&mStts);
    mAtCps[2].Set(l_at_cps_src);
    mAtCps[2].SetStts(&mStts);
    mAtCyl.Set(l_at_cyl_src);
    mAtCyl.SetStts(&mStts);
    mFanWindCps1.Set(l_fan_wind_cps_src);
    mFanWindCps1.SetR(70.0f);
    mFanWindCps1.SetStts(&mStts);
    mFanWindSph.Set(l_fan_wind_sph_src);
    mFanWindSph.SetStts(&mStts);
    mFanWindCps2.Set(l_fan_wind_cps_src);
    mFanWindCps2.SetStts(&mStts);
    mFanWindCps2.SetAtType(AT_TYPE_LIGHT);
    mFanWindCps2.SetR(20.0f);
    
    for (int i = 0; i < (int)ARRAY_SIZE(m_anm_heap_under); i++) {
        createAnimeHeap(&m_anm_heap_under[i].mpAnimeHeap, HEAP_TYPE_UNDER_UPPER_e);
        m_anm_heap_under[i].mIdx = -1;
        m_anm_heap_under[i].field_0x2 = -1;
        m_anm_heap_under[i].field_0x4 = -1;
    }
    for (int i = 0; i < (int)ARRAY_SIZE(m_anm_heap_upper); i++) {
        createAnimeHeap(&m_anm_heap_upper[i].mpAnimeHeap, HEAP_TYPE_UNDER_UPPER_e);
        m_anm_heap_upper[i].mIdx = -1;
        m_anm_heap_upper[i].field_0x2 = -1;
        m_anm_heap_upper[i].field_0x4 = -1;
    }
    createAnimeHeap(&mpTextureAnimeResHeap, HEAP_TYPE_TEXTURE_ANIME_e);
    mTexAnimeResIdx = -1;
    m31BA = -1;
    m31BC = -1;
    m31BE = -1;
    createAnimeHeap(&mpTextureScrollResHeap, HEAP_TYPE_TEXTURE_SCROLL_e);
    mTexScrollResIdx = -1;
    m31CA = -1;
    m31CC = -1;
    m31CE = -1;
    m34EE = -1;
    m34F0 = -1;
    
    mpItemHeaps[0] = mDoExt_createSolidHeapFromGameToCurrent(0xE600, 0x20);
    u8* dummy_data = new u8[0xE600];
    JUT_ASSERT(0x5493, dummy_data != 0);
    mDoExt_restoreCurrentHeap();
    mDoExt_adjustSolidHeap(mpItemHeaps[0]);
    
    mpItemHeaps[1] = mDoExt_createSolidHeapFromGameToCurrent(0xE600, 0x20);
    dummy_data = new u8[0xE600];
    JUT_ASSERT(0x5499, dummy_data != 0);
    mDoExt_restoreCurrentHeap();
    mDoExt_adjustSolidHeap(mpItemHeaps[1]);
    
    createAnimeHeap(&m2ECC, HEAP_TYPE_UNK3_e);
    
    mActorKeepEquip.clearData();
    mActorKeepThrow.clearData();
    mActorKeepGrab.clearData();
    mActorKeepRope.clearData();
    m3628 = -1;
    m3634 = -1;
    m362C = -1;
    m3630 = -1;
    
    ResTIMG* blur_img = (ResTIMG*)dComIfG_getObjectRes(l_arcName, LINK_BTI_BLUR);
    mSwBlur.mpBlurTex = blur_img;
    
    current.angle.z = 0;
    shape_angle.z = 0;
    m3526 = 8;
    m3654 = 1.0f;
    resetSeAnime();
    
    ResTIMG* tmp_tex = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_I4_BALL128B);
    JUT_ASSERT(0x54B7, tmp_tex != 0);
    mSightPacket.setSightTex(tmp_tex);
    ResTIMG* tmp_img = (ResTIMG*)dComIfG_getObjectRes(l_arcName, LINK_BTI_ROCK_MARK);
    JUT_ASSERT(0x54BD, tmp_img != 0);
    void* tmp_img_data = reinterpret_cast<void*>(reinterpret_cast<u32>(tmp_img) + tmp_img->imageOffset);
    mSightPacket.setLockTex(tmp_img_data);
    mSightPacket.setImage(tmp_img);
    
    int startMode = getStartMode();
    u8 lastMode = dComIfGs_getLastSceneMode();
    if (startMode == 0xE) {
        mEventIdx = dComIfGp_evmng_startDemo(0xD4);
    } else if (startMode == 0xC) {
        mEventIdx = dComIfGp_evmng_startDemo(0xD0);
    } else if (startMode == 0x6) {
        mEventIdx = dComIfGp_evmng_startDemo(0xCF);
    } else if (startMode == 0xA) {
        mEventIdx = dComIfGp_evmng_startDemo(0xD2);
    } else if (startMode == 0xB) {
        mEventIdx = dComIfGp_evmng_startDemo(0xD3);
    } else if (startMode == 0x9 || lastMode == 0x6) {
        mEventIdx = dComIfGp_evmng_startDemo(0xCB);
    } else if (startMode == 0x2 && (lastMode == 0x4 || lastMode == 0x5)) {
        mEventIdx = dComIfGp_evmng_startDemo(0xC9);
    } else if (startMode == 0xF) {
        mEventIdx = dComIfGp_evmng_startDemo(0xD5);
    } else {
        mEventIdx = dComIfGp_evmng_startDemo(getStartEvent());
    }
    
    onNoResetFlg0(daPyFlg0_UNK100);
    m08EC.OffWaterGrp();
    mDemo.setStick(1.0f);
    endDamageEmitter();
    mMirrorPacket.init(NULL);
    
    mLightInfluence.mColor.r = 600;
    mLightInfluence.mColor.g = 400;
    mLightInfluence.mColor.b = 120;
    mLightInfluence.mFluctuation = 250.0f;
    mLightInfluence.mPos = current.pos;
    mLightInfluence.mPower = 0.0f;
    dKy_plight_set(&mLightInfluence);
    
    m352E = 900;
    field_0x298 = 0xAD;
    m34DE = shape_angle.y;
    
    ResTIMG* linktex_casual = (ResTIMG*)dComIfG_getObjectRes(l_arcName, LINK_BTI_LINKTEXBCI4);
    int num_linktex_headers_seen = 0;
    J3DTexture* texture = mpCLModelData->getTexture();
    JUT_ASSERT(0x5504, texture != 0);
    JUTNameTab* textureName = mpCLModelData->getTextureName();
    JUT_ASSERT(0x5506, textureName != 0);
    for (u16 i = 0; i < texture->getNum(); i++) {
        const char* texName = textureName->getName(i);
        if (strcmp(texName, "linktexS3TC") != 0) {
            continue;
        }
        if (num_linktex_headers_seen == 0) {
            // Link's model's TEX1 section has two headers for the linktexS3TC texture.
            // They seem identical except the first has alpha enabled and the second does not.
            // The second is the one that is actually used, so we have to skip over the first one.
            num_linktex_headers_seen += 1;
            continue;
        }
        
        mpCurrLinktex = texture->getResTIMG(i);
        mOtherLinktex = *mpCurrLinktex;
        
        // Modify the linktexS3TC texture in Link's model to be the casual clothes texture.
        texture->setResTIMG(i, *linktex_casual);
        
        if (!dComIfGs_isEventBit(0x2A80) || dComIfGs_getClearCount() != 0) {
            onNoResetFlg1(daPyFlg1_CASUAL_CLOTHES);
        }
        if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES)) {
            break;
        }
        
        // If Link isn't wearing the casual clothes, then load the hero's clothes texture from the backup and swap them.
        ResTIMG casualLinktex = *mpCurrLinktex;
        *mpCurrLinktex = mOtherLinktex;
        mOtherLinktex = casualLinktex;
        break;
    }
}

int phase_1(daPy_lk_c* i_this) {
    dComIfGp_setPlayer(0, i_this);
    dComIfGp_setLinkPlayer(i_this);

    fopAcM_setStageLayer(i_this);
    i_this->mAttentionInfo.mFlags = 0xFFFFFFFF;

    i_this->mAttentionInfo.mPosition.x = i_this->current.pos.x;
    i_this->mAttentionInfo.mPosition.y = i_this->current.pos.y + 125.0f;
    i_this->mAttentionInfo.mPosition.z = i_this->current.pos.z;

    return cPhs_NEXT_e;
}

int phase_2(daPy_lk_c* i_this) {
    int result;

    if (dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0)) == NULL)  {
        result = cPhs_INIT_e;
    } else {
        fopAcM_SetupActor(i_this, daPy_lk_c);
        i_this->playerInit();

        result = cPhs_NEXT_e;
    }

    return result;
}

/* 80125DB4-80126F00       .text __ct__9daPy_lk_cFv */
daPy_lk_c::daPy_lk_c() {
    /* Nonmatching */
}

/* 80126F00-8012704C       .text __dt__15daPy_footData_cFv */
daPy_footData_c::~daPy_footData_c() {
    /* Nonmatching */
}

/* 8012704C-80127160       .text __ct__15daPy_footData_cFv */
daPy_footData_c::daPy_footData_c() {
    /* Nonmatching */
}

/* 80127160-80127B50       .text makeBgWait__9daPy_lk_cFv */
int daPy_lk_c::makeBgWait() {
    /* Nonmatching */
    return cPhs_NEXT_e;
}

int phase_3(daPy_lk_c* i_this) {
    return i_this->makeBgWait();
}

static s32 daPy_Create(fopAc_ac_c* i_this) {
    static int (*l_method[3])(daPy_lk_c*) = {
        phase_1, 
        phase_2,
        phase_3,
    };
    daPy_lk_c* player_link = (daPy_lk_c*)i_this;

    return dComLbG_PhaseHandler(player_link->getPhase(), (cPhs__Handler*)l_method, player_link);
}

/* 80127BA0-80127CC0       .text setSeAnime__9daPy_lk_cFPC14daPy_anmHeap_cP12J3DFrameCtrl */
void daPy_lk_c::setSeAnime(const daPy_anmHeap_c*, J3DFrameCtrl*) {
    /* Nonmatching */
}

/* 80127CC0-80127DEC       .text initSeAnime__9daPy_lk_cFv */
void daPy_lk_c::initSeAnime() {
    /* Nonmatching */
}

/* 80127DEC-80127E08       .text resetSeAnime__9daPy_lk_cFv */
void daPy_lk_c::resetSeAnime() {
    /* Nonmatching */
}

/* 80127E08-8012821C       .text setMoveAnime__9daPy_lk_cFfffQ29daPy_lk_c8daPy_ANMQ29daPy_lk_c8daPy_ANMif */
void daPy_lk_c::setMoveAnime(f32, f32, f32, daPy_lk_c::daPy_ANM, daPy_lk_c::daPy_ANM, int, f32) {
    /* Nonmatching */
}

/* 8012821C-80128494       .text setSingleMoveAnime__9daPy_lk_cFQ29daPy_lk_c8daPy_ANMffsf */
void daPy_lk_c::setSingleMoveAnime(daPy_lk_c::daPy_ANM, f32, f32, s16, f32) {
    /* Nonmatching */
}

/* 80128494-801285F8       .text setActAnimeUpper__9daPy_lk_cFUsQ29daPy_lk_c10daPy_UPPERffsf */
void daPy_lk_c::setActAnimeUpper(u16, daPy_lk_c::daPy_UPPER, f32, f32, s16, f32) {
    /* Nonmatching */
}

/* 801285F8-801286C0       .text resetActAnimeUpper__9daPy_lk_cFQ29daPy_lk_c10daPy_UPPERf */
void daPy_lk_c::resetActAnimeUpper(daPy_lk_c::daPy_UPPER, f32) {
    /* Nonmatching */
}

/* 801286C0-801287E8       .text animeUpdate__9daPy_lk_cFv */
void daPy_lk_c::animeUpdate() {
    /* Nonmatching */
}

/* 801287E8-8012887C       .text simpleAnmPlay__9daPy_lk_cFP10J3DAnmBase */
void daPy_lk_c::simpleAnmPlay(J3DAnmBase*) {
    /* Nonmatching */
}

/* 8012887C-801288A0       .text setHandModel__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
void daPy_lk_c::setHandModel(daPy_lk_c::daPy_ANM) {
    /* Nonmatching */
}

/* 801288A0-8012894C       .text getAnmData__9daPy_lk_cCFQ29daPy_lk_c8daPy_ANM */
void daPy_lk_c::getAnmData(daPy_lk_c::daPy_ANM) const {
    /* Nonmatching */
}

/* 8012894C-80128988       .text checkGrabWeapon__9daPy_lk_cFi */
BOOL daPy_lk_c::checkGrabWeapon(int) {
    /* Nonmatching */
}

/* 80128988-801289A8       .text onDekuSpReturnFlg__9daPy_lk_cFUc */
void daPy_lk_c::onDekuSpReturnFlg(u8) {
    /* Nonmatching */
}

/* 801289A8-80128AA4       .text changeTextureAnime__9daPy_lk_cFUsUsi */
void daPy_lk_c::changeTextureAnime(u16, u16, int) {
    /* Nonmatching */
}

/* 80128AA4-80128B50       .text setThrowDamage__9daPy_lk_cFP4cXyzsffi */
BOOL daPy_lk_c::setThrowDamage(cXyz*, s16, f32, f32, int) {
    /* Nonmatching */
}

/* 80128B50-80128C10       .text setPlayerPosAndAngle__9daPy_lk_cFP4cXyzs */
void daPy_lk_c::setPlayerPosAndAngle(cXyz*, s16) {
    /* Nonmatching */
}

/* 80128C10-80128CE4       .text setPlayerPosAndAngle__9daPy_lk_cFP4cXyzP5csXyz */
void daPy_lk_c::setPlayerPosAndAngle(cXyz*, csXyz*) {
    /* Nonmatching */
}

/* 80128CE4-80128DC0       .text setPlayerPosAndAngle__9daPy_lk_cFPA4_f */
void daPy_lk_c::setPlayerPosAndAngle(MtxP) {
    /* Nonmatching */
}

/* 80128DC0-80128F8C       .text endDemoMode__9daPy_lk_cFv */
void daPy_lk_c::endDemoMode() {
    /* Nonmatching */
}

/* 80128F8C-8012901C       .text getBokoFlamePos__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::getBokoFlamePos(cXyz*) {
    /* Nonmatching */
}

#include "d/actor/d_a_player_particle.inc"

#include "d/actor/d_a_player_dproc.inc"

#include "d/actor/d_a_player_ladder.inc"

#include "d/actor/d_a_player_hang.inc"

#include "d/actor/d_a_player_climb.inc"

#include "d/actor/d_a_player_whide.inc"

#include "d/actor/d_a_player_crawl.inc"

#include "d/actor/d_a_player_grab.inc"

#include "d/actor/d_a_player_swim.inc"

#include "d/actor/d_a_player_battle.inc"

#include "d/actor/d_a_player_ship.inc"

#include "d/actor/d_a_player_rope.inc"

#include "d/actor/d_a_player_boomerang.inc"

#include "d/actor/d_a_player_bow.inc"

#include "d/actor/d_a_player_hook.inc"

#include "d/actor/d_a_player_fan.inc"

#include "d/actor/d_a_player_tact.inc"

#include "d/actor/d_a_player_vomit.inc"

#include "d/actor/d_a_player_hammer.inc"

#include "d/actor/d_a_player_pushpull.inc"

#include "d/actor/d_a_player_bottle.inc"

#include "d/actor/d_a_player_weapon.inc"

#include "d/actor/d_a_player_food.inc"

#include "d/actor/d_a_player_sword.inc"

actor_method_class l_daPy_Method = {
    (process_method_func)daPy_Create,
    (process_method_func)daPy_Delete,
    (process_method_func)daPy_Execute,
    (process_method_func)daPy_IsDelete,
    (process_method_func)daPy_Draw,
};

actor_process_profile_definition2 g_profile_PLAYER = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 5,
    /* ListPrio     */ fpcLy_CURRENT_e,
    /* ProcName     */ PROC_PLAYER,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daPy_lk_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0068,
    /* Actor SubMtd */ &l_daPy_Method,
    /* Status       */ fopAcStts_FREEZE_e,
    /* Group        */ fopAc_PLAYER_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
    /* field_0x30   */ 2,
};
