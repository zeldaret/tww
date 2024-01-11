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
#include "d/actor/d_a_player_HIO.h"
#include "d/d_com_inf_game.h"
#include "d/d_com_lib_game.h"
#include "d/d_procname.h"
#include "d/d_kankyo.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/actor/d_a_itembase.h"
#include "d/d_item_data.h"
#include "d/d_item.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_lib.h"
#include "d/d_material.h"
#include "JSystem/J3DGraphLoader/J3DAnmLoader.h"
#include "d/actor/d_a_hookshot.h"
#include "d/actor/d_a_ship.h"
#include "SSystem/SComponent/c_counter.h"

const Vec l_ship_offset = {0.0f, 15.0f, -35.0f};
const Vec l_ship_offset2 = {0.0f, 15.0f, -66.8f};
const Vec l_ship_offset3 = {0.0f, 15.0f, -96.0f};
const Vec l_ship_redge = {-57.0f, 35.0f, -35.0f};
const Vec l_ship_ledge = {57.0f, 35.0f, -35.0f};
const Vec l_heel_pos = {-6.0f, 3.25f, 0.0f};
const Vec l_toe_pos = {6.0f, 3.25f, 0.0f};
const Vec l_eye_offset = {11.25f, 18.75f, 0.0f};
const Vec l_head_center_offset = {11.25f, 0.0f, 0.0f};
const Vec l_neck_front = {0.0f, 1.0f, 0.0f};
const Vec l_neck_top = {1.0f, 0.0f, 0.0f};
const Vec l_land_smoke_offset = {0.0f, 0.0f, 30.0f};
const Vec l_ms_light_local_start = {5.0f, 7.0f, 0.0f};
const Vec l_ms_light_local_vec = {0.0f, 0.0f, -10000.0f};
const Vec l_tact_top = {38.0f, 7.5f, 12.5f};
const Vec l_crawl_start_front_offset = {0.0f, 10.0f, 112.0f};
const Vec l_crawl_front_offset = {0.0f, 10.0f, 80.0f};
const Vec l_crawl_back_offset = {0.0f, 10.0f, -50.0f};
const Vec l_crawl_top_offset = {0.0f, 10.0f, 0.0f};
const Vec l_crawl_front_up_offset = {0.0f, 50.0f, 80.0f};
const Vec l_crawl_back_up_offset = {0.0f, 50.0f, -50.0f};
const Vec l_crawl_stand_up_offset = {0.0f, 50.0f, -20.0f};
const Vec l_crawl_top_up_offset = {0.0f, 50.0f, 0.0f};
const Vec l_crawl_side_offset = {50.0f, 50.0f, 0.0f};
const Vec l_crawl_lside_offset = {50.0f, 0.0f, 0.0f};
const Vec l_crawl_rside_offset = {-50.0f, 0.0f, 0.0f};
const Vec l_crawl_lside_front_offset = {50.0f, 5.0f, 80.0f};
const Vec l_crawl_rside_front_offset = {-50.0f, 5.0f, 80.0f};
const Vec l_crawl_min_side_offset = {30.0f, 0.0f, 0.0f};

const daPy_lk_c::TexAnmTableEntry daPy_lk_c::mTexAnmIndexTable[] = {
    /* 0x00 */ {LKANM_BTP_TMABAA,            LKANM_BTK_TMABA},
    /* 0x01 */ {LKANM_BTP_TMABAA,            LKANM_BTK_TEUP},
    /* 0x02 */ {LKANM_BTP_TMABAB,            LKANM_BTK_TMABA},
    /* 0x03 */ {LKANM_BTP_TMABAC,            LKANM_BTK_TMABA},
    /* 0x04 */ {LKANM_BTP_TMABACB,           LKANM_BTK_TMABA},
    /* 0x05 */ {LKANM_BTP_TMABACB,           LKANM_BTK_TEDW},
    /* 0x06 */ {LKANM_BTP_TMABACC,           LKANM_BTK_TMABA},
    /* 0x07 */ {LKANM_BTP_TMABAD,            LKANM_BTK_TMABA},
    /* 0x08 */ {LKANM_BTP_TMABAD,            LKANM_BTK_TEDW},
    /* 0x09 */ {LKANM_BTP_TMABAE,            LKANM_BTK_TMABA},
    /* 0x0A */ {LKANM_BTP_TMABAE,            LKANM_BTK_TEUP},
    /* 0x0B */ {LKANM_BTP_TMABAE,            LKANM_BTK_TEDW},
    /* 0x0C */ {LKANM_BTP_TMABAE,            LKANM_BTK_TEL},
    /* 0x0D */ {LKANM_BTP_TMABAE,            LKANM_BTK_TER},
    /* 0x0E */ {LKANM_BTP_TMABAF,            LKANM_BTK_TMABA},
    /* 0x0F */ {LKANM_BTP_TMABAG,            LKANM_BTK_TMABA},
    /* 0x10 */ {LKANM_BTP_TMABAH,            LKANM_BTK_TMABA},
    /* 0x11 */ {LKANM_BTP_TMABAI,            LKANM_BTK_TMABA},
    /* 0x12 */ {LKANM_BTP_TMABAJ,            LKANM_BTK_TEYORIME},
    /* 0x13 */ {LKANM_BTP_TMABAD,            LKANM_BTK_TWAITPICKUP},
    /* 0x14 */ {LKANM_BTP_TMABAC,            LKANM_BTK_THOOKSHOTJMP},
    /* 0x15 */ {LKANM_BTP_TGRABP,            LKANM_BTK_TGRABP},
    /* 0x16 */ {LKANM_BTP_TGRABUP,           LKANM_BTK_TGRABUP},
    /* 0x17 */ {LKANM_BTP_TGRABNG,           LKANM_BTK_TGRABNG},
    /* 0x18 */ {LKANM_BTP_TGRABTHROW,        LKANM_BTK_TGRABTHROW},
    /* 0x19 */ {LKANM_BTP_TGRABRE,           LKANM_BTK_TECN},
    /* 0x1A */ {LKANM_BTP_TWALLWL,           LKANM_BTK_TER},
    /* 0x1B */ {LKANM_BTP_TWALLWR,           LKANM_BTK_TEL},
    /* 0x1C */ {LKANM_BTP_TWALLPL,           LKANM_BTK_TWALLPL},
    /* 0x1D */ {LKANM_BTP_TWALLPR,           LKANM_BTK_TWALLPR},
    /* 0x1E */ {LKANM_BTP_TCUT,              LKANM_BTK_TECN},
    /* 0x1F */ {LKANM_BTP_TCUTEA,            LKANM_BTK_TCUTEA},
    /* 0x20 */ {LKANM_BTP_TCUTEA,            LKANM_BTK_TECN},
    /* 0x21 */ {LKANM_BTP_TEXCA1,            LKANM_BTK_TEXCA1},
    /* 0x22 */ {LKANM_BTP_TEXCB1,            LKANM_BTK_TEXCB1},
    /* 0x23 */ {LKANM_BTP_TJATTACK,          LKANM_BTK_TJATTACK},
    /* 0x24 */ {LKANM_BTP_TJATTACK,          LKANM_BTK_TEUP},
    /* 0x25 */ {LKANM_BTP_TCUTTURNP,         LKANM_BTK_TECN},
    /* 0x26 */ {LKANM_BTP_TCUTTURN,          LKANM_BTK_TCUTTURN},
    /* 0x27 */ {LKANM_BTP_TMJMP,             LKANM_BTK_TMJMP},
    /* 0x28 */ {LKANM_BTP_TMJMPC,            LKANM_BTK_TMJMPC},
    /* 0x29 */ {LKANM_BTP_TMROLLL,           LKANM_BTK_TMROLLL},
    /* 0x2A */ {LKANM_BTP_TMROLLR,           LKANM_BTK_TMROLLR},
    /* 0x2B */ {LKANM_BTP_TMROLLLRC,         LKANM_BTK_TMROLLLC},
    /* 0x2C */ {LKANM_BTP_TMROLLLRC,         LKANM_BTK_TMROLLRC},
    /* 0x2D */ {LKANM_BTP_TMSTEPOVER,        LKANM_BTK_TMSTEPOVER},
    /* 0x2E */ {LKANM_BTP_TMSTEPOVERA,       LKANM_BTK_TMSTEPOVERA},
    /* 0x2F */ {LKANM_BTP_TMSTEPOVERLAND,    LKANM_BTK_TMSTEPOVERLAND},
    /* 0x30 */ {LKANM_BTP_TATNJLR,           LKANM_BTK_TATNJL},
    /* 0x31 */ {LKANM_BTP_TATNJLR,           LKANM_BTK_TATNJR},
    /* 0x32 */ {LKANM_BTP_TJMP,              LKANM_BTK_TJMP},
    /* 0x33 */ {LKANM_BTP_TROLLF,            LKANM_BTK_TROLLF},
    /* 0x34 */ {LKANM_BTP_TROLLB,            LKANM_BTK_TROLLB},
    /* 0x35 */ {LKANM_BTP_TROLLBLAND,        LKANM_BTK_TECN},
    /* 0x36 */ {LKANM_BTP_TROLLFMIS,         LKANM_BTK_TROLLFMIS},
    /* 0x37 */ {LKANM_BTP_TFALL,             LKANM_BTK_TEDW},
    /* 0x38 */ {LKANM_BTP_TLANDDAMA,         LKANM_BTK_TLANDDAMA},
    /* 0x39 */ {LKANM_BTP_TLANDDAMAST,       LKANM_BTK_TLANDDAMAST},
    /* 0x3A */ {LKANM_BTP_TDAM,              LKANM_BTK_TDAM},
    /* 0x3B */ {LKANM_BTP_TDAMF,             LKANM_BTK_TECN},
    /* 0x3C */ {LKANM_BTP_TDAMFFUP,          LKANM_BTK_TDAMFFUP},
    /* 0x3D */ {LKANM_BTP_TDAMFBUP,          LKANM_BTK_TDAMFBUP},
    /* 0x3E */ {LKANM_BTP_TDAMFLRUP,         LKANM_BTK_TDAMFLUP},
    /* 0x3F */ {LKANM_BTP_TDAMFLRUP,         LKANM_BTK_TDAMFRUP},
    /* 0x40 */ {LKANM_BTP_TDAMDASH,          LKANM_BTK_TECN},
    /* 0x41 */ {LKANM_BTP_TGUARD,            LKANM_BTK_TGUARD},
    /* 0x42 */ {LKANM_BTP_TSLIDEF,           LKANM_BTK_TSLIDEF},
    /* 0x43 */ {LKANM_BTP_TSLIDEFLAND,       LKANM_BTK_TSLIDEFLAND},
    /* 0x44 */ {LKANM_BTP_TSLIDEB,           LKANM_BTK_TEDW},
    /* 0x45 */ {LKANM_BTP_TSLIDEBLAND,       LKANM_BTK_TSLIDEFLAND},
    /* 0x46 */ {LKANM_BTP_TSWIMP,            LKANM_BTK_TSWIMP},
    /* 0x47 */ {LKANM_BTP_TSWIMING,          LKANM_BTK_TSWIMING},
    /* 0x48 */ {LKANM_BTP_TBOOMTHROW,        LKANM_BTK_TBOOMTHROW},
    /* 0x49 */ {LKANM_BTP_TBOOMCATCH,        LKANM_BTK_TBOOMCATCH},
    /* 0x4A */ {LKANM_BTP_TWALKPUSH,         LKANM_BTK_TWALKPUSH},
    /* 0x4B */ {LKANM_BTP_TWALKPULL,         LKANM_BTK_TWALKPULL},
    /* 0x4C */ {LKANM_BTP_TVJMPCHA,          LKANM_BTK_TVJMPCHA},
    /* 0x4D */ {LKANM_BTP_TVJMPCL,           LKANM_BTK_TVJMPCL},
    /* 0x4E */ {LKANM_BTP_TROPECLIMB,        LKANM_BTK_TEUP},
    /* 0x4F */ {LKANM_BTP_TROPEDOWN,         LKANM_BTK_TEDW},
    /* 0x50 */ {LKANM_BTP_TLADDERUPST,       LKANM_BTK_TLADDERUPST},
    /* 0x51 */ {LKANM_BTP_TLADDERDWST,       LKANM_BTK_TLADDERDWST},
    /* 0x52 */ {LKANM_BTP_TLADDERUPED,       LKANM_BTK_TLADDERUPED},
    /* 0x53 */ {LKANM_BTP_TLADDERDWED,       LKANM_BTK_TLADDERDWED},
    /* 0x54 */ {LKANM_BTP_THANGING,          LKANM_BTK_THANGING},
    /* 0x55 */ {LKANM_BTP_THANGUP,           LKANM_BTK_THANGUP},
    /* 0x56 */ {LKANM_BTP_TLAVADAM,          LKANM_BTK_TLAVADAM},
    /* 0x57 */ {LKANM_BTP_TCUTRE,            LKANM_BTK_TCUTRE},
    /* 0x58 */ {LKANM_BTP_TCUTTURNB,         LKANM_BTK_TCUTTURNB},
    /* 0x59 */ {LKANM_BTP_TWAITATOB,         LKANM_BTK_TWAITATOB},
    /* 0x5A */ {LKANM_BTP_TCOMEOUT,          LKANM_BTK_TCOMEOUT},
    /* 0x5B */ {LKANM_BTP_THOLDUP,           LKANM_BTK_TMABA},
    /* 0x5C */ {LKANM_BTP_TWALLHOLDUP,       LKANM_BTK_TWALLHOLDUP},
    /* 0x5D */ {LKANM_BTP_TITEMGET,          LKANM_BTK_TITEMGET},
    /* 0x5E */ {LKANM_BTP_TSALTATION,        LKANM_BTK_TSALTATION},
    /* 0x5F */ {LKANM_BTP_TWHO,              LKANM_BTK_TWHO},
    /* 0x60 */ {LKANM_BTP_TPICKUP,           LKANM_BTK_TPICKUP},
    /* 0x61 */ {LKANM_BTP_TBOXOPENLINK,      LKANM_BTK_TBOXOPENLINK},
    /* 0x62 */ {LKANM_BTP_TBOXOPENSHORTLINK, LKANM_BTK_TBOXOPENSHORTLINK},
    /* 0x63 */ {LKANM_BTP_TDIELONG,          LKANM_BTK_TDIELONG},
    /* 0x64 */ {LKANM_BTP_TSWIMDIE,          LKANM_BTK_TECN},
    /* 0x65 */ {LKANM_BTP_TSURPRISED,        LKANM_BTK_TSURPRISED},
    /* 0x66 */ {LKANM_BTP_TTURNBACK,         LKANM_BTK_TTURNBACK},
    /* 0x67 */ {LKANM_BTP_TLOOKUP,           LKANM_BTK_TLOOKUP},
    /* 0x68 */ {LKANM_BTP_TWAITQ,            LKANM_BTK_TECN},
    /* 0x69 */ {LKANM_BTP_TGLAD,             LKANM_BTK_TECN},
    /* 0x6A */ {LKANM_BTP_TCUTBOKO,          LKANM_BTK_TCUTBOKO},
    /* 0x6B */ {LKANM_BTP_SHIP_JUMP1,        LKANM_BTK_TECN},
    /* 0x6C */ {LKANM_BTP_SHIP_JUMP2,        LKANM_BTK_TECN},
    /* 0x6D */ {LKANM_BTP_TUSEFANA,          LKANM_BTK_TUSEFANA},
    /* 0x6E */ {LKANM_BTP_TUSEFANB,          LKANM_BTK_TUSEFANB},
    /* 0x6F */ {LKANM_BTP_TUSEFANB2,         LKANM_BTK_TEDW},
    /* 0x70 */ {LKANM_BTP_TBOWWAIT,          LKANM_BTK_TBOWWAIT},
    /* 0x71 */ {LKANM_BTP_TVOMITJMP,         LKANM_BTK_TEDW},
    /* 0x72 */ {LKANM_BTP_TREST,             LKANM_BTK_TREST},
    /* 0x73 */ {LKANM_BTP_TTAKE,             LKANM_BTK_TTAKE},
    /* 0x74 */ {LKANM_BTP_TTAKELR,           LKANM_BTK_TECN},
    /* 0x75 */ {LKANM_BTP_TSLIPICE,          LKANM_BTK_TECN},
    /* 0x76 */ {LKANM_BTP_THAMSWINGA,        LKANM_BTK_THAMSWINGA},
    /* 0x77 */ {LKANM_BTP_THAMSWINGBPRE,     LKANM_BTK_THAMSWINGBPRE},
    /* 0x78 */ {LKANM_BTP_THAMSWINGBHIT,     LKANM_BTK_THAMSWINGBHIT},
    /* 0x79 */ {LKANM_BTP_THAMSWINGBEND,     LKANM_BTK_THAMSWINGBEND},
    /* 0x7A */ {LKANM_BTP_TSETBOOTS,         LKANM_BTK_TECN},
    /* 0x7B */ {LKANM_BTP_TDOOROPENALINK,    LKANM_BTK_TDOOROPENALINK},
    /* 0x7C */ {LKANM_BTP_TDOOROPENBLINK,    LKANM_BTK_TDOOROPENBLINK},
    /* 0x7D */ {LKANM_BTP_TSEYYES,           LKANM_BTK_TSEYYES},
    /* 0x7E */ {LKANM_BTP_TPRESENTATION,     LKANM_BTK_TPRESENTATIONA},
    /* 0x7F */ {LKANM_BTP_TWIND,             LKANM_BTK_TWINDL},
    /* 0x80 */ {LKANM_BTP_TWIND,             LKANM_BTK_TWINDR},
    /* 0x81 */ {LKANM_BTP_TPRESENTATION,     LKANM_BTK_TPRESENTATIONB},
    /* 0x82 */ {LKANM_BTP_TBINDRINKPRE,      LKANM_BTK_TBINDRINKPRE},
    /* 0x83 */ {LKANM_BTP_TBINDRINKING,      LKANM_BTK_TECN},
    /* 0x84 */ {LKANM_BTP_TBINDRINKAFTER,    LKANM_BTK_TBINDRINKAFTER},
    /* 0x85 */ {LKANM_BTP_TBINDRINKPRE2,     LKANM_BTK_TBINDRINKPRE},
    /* 0x86 */ {LKANM_BTP_TBINDRINKING2,     LKANM_BTK_TECN},
    /* 0x87 */ {LKANM_BTP_TBINDRINKAFTER2,   LKANM_BTK_TBINDRINKAFTER2},
    /* 0x88 */ {LKANM_BTP_TBINOPENPRE,       LKANM_BTK_TBINOPENPRE},
    /* 0x89 */ {LKANM_BTP_TBINOPENA,         LKANM_BTK_TBINOPENA},
    /* 0x8A */ {LKANM_BTP_TBINOPENB,         LKANM_BTK_TBINOPENB},
    /* 0x8B */ {LKANM_BTP_TBINSWING,         LKANM_BTK_TBINSWING},
    /* 0x8C */ {LKANM_BTP_TBINGET,           LKANM_BTK_TBINGET},
    /* 0x8D */ {LKANM_BTP_TARROWRELORD,      LKANM_BTK_TARROWRELORD},
    /* 0x8E */ {LKANM_BTP_TSURPRISEDB,       LKANM_BTK_TSURPRISEDB},
    /* 0x8F */ {LKANM_BTP_TFAN,              LKANM_BTK_TFAN},
    /* 0x90 */ {LKANM_BTP_TNENRIKI,          LKANM_BTK_TECN},
    /* 0x91 */ {LKANM_BTP_TMABAB,            LKANM_BTK_TEDL},
    /* 0x92 */ {LKANM_BTP_TMABAH,            LKANM_BTK_TABEKOBE},
    /* 0x93 */ {LKANM_BTP_TSETHYOINOMI,      LKANM_BTK_TSETHYOINOMI},
    /* 0x94 */ {LKANM_BTP_LINK_FREEZ,        LKANM_BTK_TECN},
    /* 0x95 */ {LKANM_BTP_LINK_MOGAKI,       LKANM_BTK_TECN},
    /* 0x96 */ {LKANM_BTP_TDAMBIRI,          LKANM_BTK_TDAMBIRI},
    /* 0x97 */ {LKANM_BTP_SALVLR,            LKANM_BTK_SALVWAIT},
    /* 0x98 */ {LKANM_BTP_SALVWAIT,          LKANM_BTK_SALVWAIT},
    /* 0x99 */ {LKANM_BTP_SALVBAD,           LKANM_BTK_SALVWAIT},
    /* 0x9A */ {LKANM_BTP_SALVGOOD,          LKANM_BTK_SALVWAIT},
    /* 0x9B */ {LKANM_BTP_SEARESET,          LKANM_BTK_SEARESET},
    /* 0x9C */ {LKANM_BTP_TWARPIN,           LKANM_BTK_TWARPIN},
    /* 0x9D */ {LKANM_BTP_TWARPOUT,          LKANM_BTK_TWARPOUT},
    /* 0x9E */ {LKANM_BTP_TPOWUPWAIT,        LKANM_BTK_TPOWUPWAIT},
    /* 0x9F */ {LKANM_BTP_TPOWUP,            LKANM_BTK_TPOWUP},
    /* 0xA0 */ {LKANM_BTP_TCUTKESA,          LKANM_BTK_TCUTKESA},
    /* 0xA1 */ {LKANM_BTP_TWARPOUTFIRST,     LKANM_BTK_TWARPOUTFIRST},
    /* 0xA2 */ {LKANM_BTP_TDASHKAZE,         LKANM_BTK_TDASHKAZE},
    /* 0xA3 */ {LKANM_BTP_TIYAYA,            LKANM_BTK_TECN},
    /* 0xA4 */ {LKANM_BTP_TFREEA,            LKANM_BTK_TFREEA},
    /* 0xA5 */ {LKANM_BTP_TFREEB,            LKANM_BTK_TFREEB},
    /* 0xA6 */ {LKANM_BTP_TFREED,            LKANM_BTK_TFREED},
    /* 0xA7 */ {LKANM_BTP_TTAKTKAZE,         LKANM_BTK_TECN},
    /* 0xA8 */ {LKANM_BTP_TTAKTSIPPU,        LKANM_BTK_TECN},
    /* 0xA9 */ {LKANM_BTP_TTAKTCHUYA,        LKANM_BTK_TECN},
    /* 0xAA */ {LKANM_BTP_TTAKTFUJIN,        LKANM_BTK_TECN},
    /* 0xAB */ {LKANM_BTP_TTAKTAYATSURI,     LKANM_BTK_TECN},
    /* 0xAC */ {LKANM_BTP_TTAKTCHISIN,       LKANM_BTK_TECN},
};

const daPy_anmIndex_c daPy_lk_c::mSwordAnmIndexTable[] = {
    {   // 0x00
        /* mUnderBckIdx */ LKANM_BCK_WAITS,
        /* mUpperBckIdx */ LKANM_BCK_WAITS,
    },
    {   // 0x01
        /* mUnderBckIdx */ LKANM_BCK_WALKS,
        /* mUpperBckIdx */ LKANM_BCK_WALKS,
    },
    {   // 0x02
        /* mUnderBckIdx */ LKANM_BCK_DASHS,
        /* mUpperBckIdx */ LKANM_BCK_DASHS,
    },
    {   // 0x03
        /* mUnderBckIdx */ LKANM_BCK_DASHS,
        /* mUpperBckIdx */ LKANM_BCK_DASHKAZE,
    },
    {   // 0x04
        /* mUnderBckIdx */ LKANM_BCK_WALKHBOOTS,
        /* mUpperBckIdx */ LKANM_BCK_WALKHBOOTS,
    },
    {   // 0x05
        /* mUnderBckIdx */ LKANM_BCK_WALKHBOOTS,
        /* mUpperBckIdx */ LKANM_BCK_DASHKAZE,
    },
    {   // 0x06
        /* mUnderBckIdx */ LKANM_BCK_WALKSLOPE,
        /* mUpperBckIdx */ LKANM_BCK_WALKSLOPE,
    },
    {   // 0x07
        /* mUnderBckIdx */ LKANM_BCK_ATNLS,
        /* mUpperBckIdx */ LKANM_BCK_ATNLS,
    },
    {   // 0x08
        /* mUnderBckIdx */ LKANM_BCK_ATNRS,
        /* mUpperBckIdx */ LKANM_BCK_ATNRS,
    },
    {   // 0x09
        /* mUnderBckIdx */ LKANM_BCK_ATNWLS,
        /* mUpperBckIdx */ LKANM_BCK_ATNWLS,
    },
    {   // 0x0A
        /* mUnderBckIdx */ LKANM_BCK_ATNWRS,
        /* mUpperBckIdx */ LKANM_BCK_ATNWRS,
    },
    {   // 0x0B
        /* mUnderBckIdx */ LKANM_BCK_ATNDLS,
        /* mUpperBckIdx */ LKANM_BCK_ATNDLS,
    },
    {   // 0x0C
        /* mUnderBckIdx */ LKANM_BCK_ATNDRS,
        /* mUpperBckIdx */ LKANM_BCK_ATNDRS,
    },
    {   // 0x0D
        /* mUnderBckIdx */ LKANM_BCK_JMPEDS,
        /* mUpperBckIdx */ LKANM_BCK_JMPEDS,
    },
    {   // 0x0E
        /* mUnderBckIdx */ LKANM_BCK_ATNWB,
        /* mUpperBckIdx */ LKANM_BCK_ATNWB,
    },
    {   // 0x0F
        /* mUnderBckIdx */ LKANM_BCK_ATNDB,
        /* mUpperBckIdx */ LKANM_BCK_ATNDB,
    },
    {   // 0x10
        /* mUnderBckIdx */ LKANM_BCK_ATNJL,
        /* mUpperBckIdx */ LKANM_BCK_ATNJL,
    },
    {   // 0x11
        /* mUnderBckIdx */ LKANM_BCK_ATNJR,
        /* mUpperBckIdx */ LKANM_BCK_ATNJR,
    },
    {   // 0x12
        /* mUnderBckIdx */ LKANM_BCK_ATNJLLAND,
        /* mUpperBckIdx */ LKANM_BCK_ATNJLLAND,
    },
    {   // 0x13
        /* mUnderBckIdx */ LKANM_BCK_ATNJRLAND,
        /* mUpperBckIdx */ LKANM_BCK_ATNJRLAND,
    },
    {   // 0x14
        /* mUnderBckIdx */ LKANM_BCK_ROT,
        /* mUpperBckIdx */ LKANM_BCK_ROT,
    },
    {   // 0x15
        /* mUnderBckIdx */ LKANM_BCK_CUTREL,
        /* mUpperBckIdx */ LKANM_BCK_CUTRER,
    },
    {   // 0x16
        /* mUnderBckIdx */ LKANM_BCK_DIFENCE,
        /* mUpperBckIdx */ LKANM_BCK_DIFENCE,
    },
    {   // 0x17
        /* mUnderBckIdx */ LKANM_BCK_DIFENCEA,
        /* mUpperBckIdx */ LKANM_BCK_DIFENCEA,
    },
    {   // 0x18
        /* mUnderBckIdx */ LKANM_BCK_CUTTURNP,
        /* mUpperBckIdx */ LKANM_BCK_CUTTURNP,
    },
    {   // 0x19
        /* mUnderBckIdx */ LKANM_BCK_CUTTURNPWFB,
        /* mUpperBckIdx */ LKANM_BCK_CUTTURNPWFB,
    },
    {   // 0x1A
        /* mUnderBckIdx */ LKANM_BCK_CUTTURNPWLR,
        /* mUpperBckIdx */ LKANM_BCK_CUTTURNPWLR,
    },
};

const daPy_anmIndex_c daPy_lk_c::mBokoAnmIndexTable[] = {
    {   // 0x00
        /* mUnderBckIdx */ LKANM_BCK_WAITS,
        /* mUpperBckIdx */ LKANM_BCK_WAITBOKO,
    },
    {   // 0x01
        /* mUnderBckIdx */ LKANM_BCK_WALKS,
        /* mUpperBckIdx */ LKANM_BCK_WALKBOKO,
    },
    {   // 0x02
        /* mUnderBckIdx */ LKANM_BCK_DASHS,
        /* mUpperBckIdx */ LKANM_BCK_DASHBOKO,
    },
    {   // 0x03
        /* mUnderBckIdx */ LKANM_BCK_DASHS,
        /* mUpperBckIdx */ LKANM_BCK_DASHBOKO,
    },
    {   // 0x04
        /* mUnderBckIdx */ LKANM_BCK_WALKHBOOTS,
        /* mUpperBckIdx */ LKANM_BCK_WALKBOKO,
    },
    {   // 0x05
        /* mUnderBckIdx */ LKANM_BCK_WALKHBOOTS,
        /* mUpperBckIdx */ LKANM_BCK_WALKBOKO,
    },
    {   // 0x06
        /* mUnderBckIdx */ LKANM_BCK_WALKSLOPE,
        /* mUpperBckIdx */ LKANM_BCK_WALKBOKO,
    },
    {   // 0x07
        /* mUnderBckIdx */ LKANM_BCK_ATNLS,
        /* mUpperBckIdx */ LKANM_BCK_ATNBOKO,
    },
    {   // 0x08
        /* mUnderBckIdx */ LKANM_BCK_ATNRS,
        /* mUpperBckIdx */ LKANM_BCK_ATNBOKO,
    },
    {   // 0x09
        /* mUnderBckIdx */ LKANM_BCK_ATNWLS,
        /* mUpperBckIdx */ LKANM_BCK_ATNBOKO,
    },
    {   // 0x0A
        /* mUnderBckIdx */ LKANM_BCK_ATNWRS,
        /* mUpperBckIdx */ LKANM_BCK_ATNBOKO,
    },
    {   // 0x0B
        /* mUnderBckIdx */ LKANM_BCK_ATNDLS,
        /* mUpperBckIdx */ LKANM_BCK_ATNBOKO,
    },
    {   // 0x0C
        /* mUnderBckIdx */ LKANM_BCK_ATNDRS,
        /* mUpperBckIdx */ LKANM_BCK_ATNBOKO,
    },
    {   // 0x0D
        /* mUnderBckIdx */ LKANM_BCK_JMPEDS,
        /* mUpperBckIdx */ LKANM_BCK_JMPEDS,
    },
    {   // 0x0E
        /* mUnderBckIdx */ LKANM_BCK_ATNWB,
        /* mUpperBckIdx */ LKANM_BCK_ATNBOKO,
    },
    {   // 0x0F
        /* mUnderBckIdx */ LKANM_BCK_ATNDB,
        /* mUpperBckIdx */ LKANM_BCK_ATNBOKO,
    },
    {   // 0x10
        /* mUnderBckIdx */ LKANM_BCK_ATNJL,
        /* mUpperBckIdx */ LKANM_BCK_ATNBOKO,
    },
    {   // 0x11
        /* mUnderBckIdx */ LKANM_BCK_ATNJR,
        /* mUpperBckIdx */ LKANM_BCK_ATNBOKO,
    },
    {   // 0x12
        /* mUnderBckIdx */ LKANM_BCK_ATNJLLAND,
        /* mUpperBckIdx */ LKANM_BCK_ATNBOKO,
    },
    {   // 0x13
        /* mUnderBckIdx */ LKANM_BCK_ATNJRLAND,
        /* mUpperBckIdx */ LKANM_BCK_ATNBOKO,
    },
    {   // 0x14
        /* mUnderBckIdx */ LKANM_BCK_ROT,
        /* mUpperBckIdx */ LKANM_BCK_WAITBOKO,
    },
    {   // 0x15
        /* mUnderBckIdx */ LKANM_BCK_CUTREL,
        /* mUpperBckIdx */ LKANM_BCK_CUTRER,
    },
    {   // 0x16
        /* mUnderBckIdx */ LKANM_BCK_DIFENCE,
        /* mUpperBckIdx */ LKANM_BCK_DIFENCE,
    },
    {   // 0x17
        /* mUnderBckIdx */ LKANM_BCK_DIFENCEA,
        /* mUpperBckIdx */ LKANM_BCK_DIFENCEA,
    },
    {   // 0x18
        /* mUnderBckIdx */ LKANM_BCK_CUTTURNP,
        /* mUpperBckIdx */ LKANM_BCK_CUTTURNPB,
    },
    {   // 0x19
        /* mUnderBckIdx */ LKANM_BCK_CUTTURNPWFB,
        /* mUpperBckIdx */ LKANM_BCK_CUTTURNPB,
    },
    {   // 0x1A
        /* mUnderBckIdx */ LKANM_BCK_CUTTURNPWLR,
        /* mUpperBckIdx */ LKANM_BCK_CUTTURNPB,
    },
};

const daPy_anmIndex_c daPy_lk_c::mHammerAnmIndexTable[] = {
    {   // 0x00
        /* mUnderBckIdx */ LKANM_BCK_WAITS,
        /* mUpperBckIdx */ LKANM_BCK_WAITHAM,
    },
    {   // 0x01
        /* mUnderBckIdx */ LKANM_BCK_WALKS,
        /* mUpperBckIdx */ LKANM_BCK_WALKHAM,
    },
    {   // 0x02
        /* mUnderBckIdx */ LKANM_BCK_DASHS,
        /* mUpperBckIdx */ LKANM_BCK_DASHHAM,
    },
    {   // 0x03
        /* mUnderBckIdx */ LKANM_BCK_DASHS,
        /* mUpperBckIdx */ LKANM_BCK_DASHHAM,
    },
    {   // 0x04
        /* mUnderBckIdx */ LKANM_BCK_WALKHBOOTS,
        /* mUpperBckIdx */ LKANM_BCK_WALKHAM,
    },
    {   // 0x05
        /* mUnderBckIdx */ LKANM_BCK_WALKHBOOTS,
        /* mUpperBckIdx */ LKANM_BCK_WALKHAM,
    },
    {   // 0x06
        /* mUnderBckIdx */ LKANM_BCK_WALKSLOPE,
        /* mUpperBckIdx */ LKANM_BCK_WALKHAM,
    },
    {   // 0x07
        /* mUnderBckIdx */ LKANM_BCK_ATNLS,
        /* mUpperBckIdx */ LKANM_BCK_ATNHAM,
    },
    {   // 0x08
        /* mUnderBckIdx */ LKANM_BCK_ATNRS,
        /* mUpperBckIdx */ LKANM_BCK_ATNHAM,
    },
    {   // 0x09
        /* mUnderBckIdx */ LKANM_BCK_ATNWLS,
        /* mUpperBckIdx */ LKANM_BCK_ATNHAM,
    },
    {   // 0x0A
        /* mUnderBckIdx */ LKANM_BCK_ATNWRS,
        /* mUpperBckIdx */ LKANM_BCK_ATNHAM,
    },
    {   // 0x0B
        /* mUnderBckIdx */ LKANM_BCK_ATNDLS,
        /* mUpperBckIdx */ LKANM_BCK_ATNHAM,
    },
    {   // 0x0C
        /* mUnderBckIdx */ LKANM_BCK_ATNDRS,
        /* mUpperBckIdx */ LKANM_BCK_ATNHAM,
    },
    {   // 0x0D
        /* mUnderBckIdx */ LKANM_BCK_JMPEDS,
        /* mUpperBckIdx */ LKANM_BCK_JMPEDS,
    },
    {   // 0x0E
        /* mUnderBckIdx */ LKANM_BCK_ATNWB,
        /* mUpperBckIdx */ LKANM_BCK_ATNHAM,
    },
    {   // 0x0F
        /* mUnderBckIdx */ LKANM_BCK_ATNDB,
        /* mUpperBckIdx */ LKANM_BCK_ATNHAM,
    },
    {   // 0x10
        /* mUnderBckIdx */ LKANM_BCK_ATNJL,
        /* mUpperBckIdx */ LKANM_BCK_ATNHAM,
    },
    {   // 0x11
        /* mUnderBckIdx */ LKANM_BCK_ATNJR,
        /* mUpperBckIdx */ LKANM_BCK_ATNHAM,
    },
    {   // 0x12
        /* mUnderBckIdx */ LKANM_BCK_ATNJLLAND,
        /* mUpperBckIdx */ LKANM_BCK_ATNHAM,
    },
    {   // 0x13
        /* mUnderBckIdx */ LKANM_BCK_ATNJRLAND,
        /* mUpperBckIdx */ LKANM_BCK_ATNHAM,
    },
    {   // 0x14
        /* mUnderBckIdx */ LKANM_BCK_ROT,
        /* mUpperBckIdx */ LKANM_BCK_WAITHAM,
    },
    {   // 0x15
        /* mUnderBckIdx */ LKANM_BCK_CUTREL,
        /* mUpperBckIdx */ LKANM_BCK_CUTREHAM,
    },
    {   // 0x16
        /* mUnderBckIdx */ LKANM_BCK_DIFENCE,
        /* mUpperBckIdx */ LKANM_BCK_DIFENCEHAM,
    },
    {   // 0x17
        /* mUnderBckIdx */ LKANM_BCK_DIFENCEA,
        /* mUpperBckIdx */ LKANM_BCK_DIFENCEAHAM,
    },
    {   // 0x18
        /* mUnderBckIdx */ LKANM_BCK_CUTTURNP,
        /* mUpperBckIdx */ LKANM_BCK_CUTTURNP,
    },
    {   // 0x19
        /* mUnderBckIdx */ LKANM_BCK_CUTTURNPWFB,
        /* mUpperBckIdx */ LKANM_BCK_CUTTURNPWFB,
    },
    {   // 0x1A
        /* mUnderBckIdx */ LKANM_BCK_CUTTURNPWLR,
        /* mUpperBckIdx */ LKANM_BCK_CUTTURNPWLR,
    },
};

const daPy_lk_c::AnmDataTableEntry daPy_lk_c::mAnmDataTable[] = {
    {   // 0x00
        /* mUnderBckIdx  */ LKANM_BCK_WAITS,
        /* mUpperBckIdx  */ LKANM_BCK_WAIT,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x01
        /* mUnderBckIdx  */ LKANM_BCK_WALK,
        /* mUpperBckIdx  */ LKANM_BCK_WALK,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x02
        /* mUnderBckIdx  */ LKANM_BCK_DASH,
        /* mUpperBckIdx  */ LKANM_BCK_DASH,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x03
        /* mUnderBckIdx  */ LKANM_BCK_DASH,
        /* mUpperBckIdx  */ LKANM_BCK_DASHKAZE,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x04
        /* mUnderBckIdx  */ LKANM_BCK_WALKHBOOTS,
        /* mUpperBckIdx  */ LKANM_BCK_WALKHBOOTS,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x05
        /* mUnderBckIdx  */ LKANM_BCK_WALKHBOOTS,
        /* mUpperBckIdx  */ LKANM_BCK_DASHKAZE,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x06
        /* mUnderBckIdx  */ LKANM_BCK_WALKSLOPE,
        /* mUpperBckIdx  */ LKANM_BCK_WALKSLOPE,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x07
        /* mUnderBckIdx  */ LKANM_BCK_ATNLS,
        /* mUpperBckIdx  */ LKANM_BCK_ATNL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x08
        /* mUnderBckIdx  */ LKANM_BCK_ATNRS,
        /* mUpperBckIdx  */ LKANM_BCK_ATNR,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x09
        /* mUnderBckIdx  */ LKANM_BCK_ATNWLS,
        /* mUpperBckIdx  */ LKANM_BCK_ATNWL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x0A
        /* mUnderBckIdx  */ LKANM_BCK_ATNWRS,
        /* mUpperBckIdx  */ LKANM_BCK_ATNWR,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x0B
        /* mUnderBckIdx  */ LKANM_BCK_ATNDLS,
        /* mUpperBckIdx  */ LKANM_BCK_ATNDL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x0C
        /* mUnderBckIdx  */ LKANM_BCK_ATNDRS,
        /* mUpperBckIdx  */ LKANM_BCK_ATNDR,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x0D
        /* mUnderBckIdx  */ LKANM_BCK_JMPEDS,
        /* mUpperBckIdx  */ LKANM_BCK_JMPED,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x0E
        /* mUnderBckIdx  */ LKANM_BCK_ATNWB,
        /* mUpperBckIdx  */ LKANM_BCK_ATNWB,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x0F
        /* mUnderBckIdx  */ LKANM_BCK_ATNDB,
        /* mUpperBckIdx  */ LKANM_BCK_ATNDB,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x10
        /* mUnderBckIdx  */ LKANM_BCK_ATNJL,
        /* mUpperBckIdx  */ LKANM_BCK_ATNJL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0030,
    },
    {   // 0x11
        /* mUnderBckIdx  */ LKANM_BCK_ATNJR,
        /* mUpperBckIdx  */ LKANM_BCK_ATNJR,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0031,
    },
    {   // 0x12
        /* mUnderBckIdx  */ LKANM_BCK_ATNJLLAND,
        /* mUpperBckIdx  */ LKANM_BCK_ATNJLLAND,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x13
        /* mUnderBckIdx  */ LKANM_BCK_ATNJRLAND,
        /* mUpperBckIdx  */ LKANM_BCK_ATNJRLAND,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x14
        /* mUnderBckIdx  */ LKANM_BCK_ROT,
        /* mUpperBckIdx  */ LKANM_BCK_ROT,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x15
        /* mUnderBckIdx  */ LKANM_BCK_CUTREL,
        /* mUpperBckIdx  */ LKANM_BCK_CUTRER,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0057,
    },
    {   // 0x16
        /* mUnderBckIdx  */ LKANM_BCK_DIFENCE,
        /* mUpperBckIdx  */ LKANM_BCK_DIFENCE,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0002,
    },
    {   // 0x17
        /* mUnderBckIdx  */ LKANM_BCK_DIFENCEA,
        /* mUpperBckIdx  */ LKANM_BCK_DIFENCEA,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0041,
    },
    {   // 0x18
        /* mUnderBckIdx  */ LKANM_BCK_CUTTURNP,
        /* mUpperBckIdx  */ LKANM_BCK_CUTTURNP,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0025,
    },
    {   // 0x19
        /* mUnderBckIdx  */ LKANM_BCK_CUTTURNPWFB,
        /* mUpperBckIdx  */ LKANM_BCK_CUTTURNPWFB,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0026,
    },
    {   // 0x1A
        /* mUnderBckIdx  */ LKANM_BCK_CUTTURNPWLR,
        /* mUpperBckIdx  */ LKANM_BCK_CUTTURNPWLR,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0026,
    },
    {   // 0x1B
        /* mUnderBckIdx  */ LKANM_BCK_TALKA,
        /* mUpperBckIdx  */ LKANM_BCK_TALKA,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x1C
        /* mUnderBckIdx  */ LKANM_BCK_WAITB,
        /* mUpperBckIdx  */ LKANM_BCK_WAITB,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x000E,
    },
    {   // 0x1D
        /* mUnderBckIdx  */ LKANM_BCK_WAITATOB,
        /* mUpperBckIdx  */ LKANM_BCK_WAITATOB,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0059,
    },
    {   // 0x1E
        /* mUnderBckIdx  */ LKANM_BCK_CUTA,
        /* mUpperBckIdx  */ LKANM_BCK_CUTA,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x001E,
    },
    {   // 0x1F
        /* mUnderBckIdx  */ LKANM_BCK_CUTF,
        /* mUpperBckIdx  */ LKANM_BCK_CUTF,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x001E,
    },
    {   // 0x20
        /* mUnderBckIdx  */ LKANM_BCK_CUTR,
        /* mUpperBckIdx  */ LKANM_BCK_CUTR,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x001E,
    },
    {   // 0x21
        /* mUnderBckIdx  */ LKANM_BCK_CUTL,
        /* mUpperBckIdx  */ LKANM_BCK_CUTL,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x001E,
    },
    {   // 0x22
        /* mUnderBckIdx  */ LKANM_BCK_CUTEA,
        /* mUpperBckIdx  */ LKANM_BCK_CUTEA,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x001F,
    },
    {   // 0x23
        /* mUnderBckIdx  */ LKANM_BCK_CUTEB,
        /* mUpperBckIdx  */ LKANM_BCK_CUTEB,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0020,
    },
    {   // 0x24
        /* mUnderBckIdx  */ LKANM_BCK_EXCA1,
        /* mUpperBckIdx  */ LKANM_BCK_EXCA1,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0021,
    },
    {   // 0x25
        /* mUnderBckIdx  */ LKANM_BCK_EXCB1,
        /* mUpperBckIdx  */ LKANM_BCK_EXCB1,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0022,
    },
    {   // 0x26
        /* mUnderBckIdx  */ LKANM_BCK_CUTBOKO,
        /* mUpperBckIdx  */ LKANM_BCK_CUTBOKO,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x006A,
    },
    {   // 0x27
        /* mUnderBckIdx  */ LKANM_BCK_CUTRER,
        /* mUpperBckIdx  */ LKANM_BCK_CUTRER,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0057,
    },
    {   // 0x28
        /* mUnderBckIdx  */ LKANM_BCK_CUTTURN,
        /* mUpperBckIdx  */ LKANM_BCK_CUTTURN,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0026,
    },
    {   // 0x29
        /* mUnderBckIdx  */ LKANM_BCK_CUTTURN,
        /* mUpperBckIdx  */ LKANM_BCK_CUTTURNC,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0026,
    },
    {   // 0x2A
        /* mUnderBckIdx  */ LKANM_BCK_CUTTURNB,
        /* mUpperBckIdx  */ LKANM_BCK_CUTTURNB,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0058,
    },
    {   // 0x2B
        /* mUnderBckIdx  */ LKANM_BCK_JATTACK,
        /* mUpperBckIdx  */ LKANM_BCK_JATTACK,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0023,
    },
    {   // 0x2C
        /* mUnderBckIdx  */ LKANM_BCK_JATTCKP,
        /* mUpperBckIdx  */ LKANM_BCK_JATTCKP,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0023,
    },
    {   // 0x2D
        /* mUnderBckIdx  */ LKANM_BCK_JATTCKCUT,
        /* mUpperBckIdx  */ LKANM_BCK_JATTCKCUT,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0023,
    },
    {   // 0x2E
        /* mUnderBckIdx  */ LKANM_BCK_JATTCKCUTHAM,
        /* mUpperBckIdx  */ LKANM_BCK_JATTCKCUTHAM,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0023,
    },
    {   // 0x2F
        /* mUnderBckIdx  */ LKANM_BCK_JATTACKLAND,
        /* mUpperBckIdx  */ LKANM_BCK_JATTACKLAND,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0024,
    },
    {   // 0x30
        /* mUnderBckIdx  */ LKANM_BCK_LANDDAMA,
        /* mUpperBckIdx  */ LKANM_BCK_LANDDAMA,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0038,
    },
    {   // 0x31
        /* mUnderBckIdx  */ LKANM_BCK_LANDDAMAST,
        /* mUpperBckIdx  */ LKANM_BCK_LANDDAMAST,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0039,
    },
    {   // 0x32
        /* mUnderBckIdx  */ LKANM_BCK_ROLLF,
        /* mUpperBckIdx  */ LKANM_BCK_ROLLF,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0033,
    },
    {   // 0x33
        /* mUnderBckIdx  */ LKANM_BCK_ROLLFMIS,
        /* mUpperBckIdx  */ LKANM_BCK_ROLLFMIS,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0036,
    },
    {   // 0x34
        /* mUnderBckIdx  */ LKANM_BCK_SLIP,
        /* mUpperBckIdx  */ LKANM_BCK_SLIP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x35
        /* mUnderBckIdx  */ LKANM_BCK_SLIDEF,
        /* mUpperBckIdx  */ LKANM_BCK_SLIDEF,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0042,
    },
    {   // 0x36
        /* mUnderBckIdx  */ LKANM_BCK_SLIDEFLAND,
        /* mUpperBckIdx  */ LKANM_BCK_SLIDEFLAND,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0043,
    },
    {   // 0x37
        /* mUnderBckIdx  */ LKANM_BCK_SLIDEB,
        /* mUpperBckIdx  */ LKANM_BCK_SLIDEB,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0044,
    },
    {   // 0x38
        /* mUnderBckIdx  */ LKANM_BCK_SLIDEBLAND,
        /* mUpperBckIdx  */ LKANM_BCK_SLIDEBLAND,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0045,
    },
    {   // 0x39
        /* mUnderBckIdx  */ LKANM_BCK_ATNGAL,
        /* mUpperBckIdx  */ LKANM_BCK_ATNGAL,
        /* mLeftHandIdx  */ 0x01,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0041,
    },
    {   // 0x3A
        /* mUnderBckIdx  */ LKANM_BCK_ATNGAR,
        /* mUpperBckIdx  */ LKANM_BCK_ATNGAR,
        /* mLeftHandIdx  */ 0x01,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0041,
    },
    {   // 0x3B
        /* mUnderBckIdx  */ LKANM_BCK_ATNGAHAM,
        /* mUpperBckIdx  */ LKANM_BCK_ATNGAHAM,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0041,
    },
    {   // 0x3C
        /* mUnderBckIdx  */ LKANM_BCK_JMPST,
        /* mUpperBckIdx  */ LKANM_BCK_JMPST,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0032,
    },
    {   // 0x3D
        /* mUnderBckIdx  */ LKANM_BCK_ROLLB,
        /* mUpperBckIdx  */ LKANM_BCK_ROLLB,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0034,
    },
    {   // 0x3E
        /* mUnderBckIdx  */ LKANM_BCK_ROLLBLAND,
        /* mUpperBckIdx  */ LKANM_BCK_ROLLBLAND,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0035,
    },
    {   // 0x3F
        /* mUnderBckIdx  */ LKANM_BCK_CROUCH,
        /* mUpperBckIdx  */ LKANM_BCK_CROUCH,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x000A,
    },
    {   // 0x40
        /* mUnderBckIdx  */ LKANM_BCK_LIE,
        /* mUpperBckIdx  */ LKANM_BCK_LIE,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x000A,
    },
    {   // 0x41
        /* mUnderBckIdx  */ LKANM_BCK_LIEFORWARD,
        /* mUpperBckIdx  */ LKANM_BCK_LIEFORWARD,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x000A,
    },
    {   // 0x42
        /* mUnderBckIdx  */ LKANM_BCK_WALL,
        /* mUpperBckIdx  */ LKANM_BCK_WALL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x000F,
    },
    {   // 0x43
        /* mUnderBckIdx  */ LKANM_BCK_WALLDW,
        /* mUpperBckIdx  */ LKANM_BCK_WALLDW,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x000F,
    },
    {   // 0x44
        /* mUnderBckIdx  */ LKANM_BCK_WALLWL,
        /* mUpperBckIdx  */ LKANM_BCK_WALLWL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x001A,
    },
    {   // 0x45
        /* mUnderBckIdx  */ LKANM_BCK_WALLWR,
        /* mUpperBckIdx  */ LKANM_BCK_WALLWR,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x001B,
    },
    {   // 0x46
        /* mUnderBckIdx  */ LKANM_BCK_WALLWLDW,
        /* mUpperBckIdx  */ LKANM_BCK_WALLWLDW,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x001A,
    },
    {   // 0x47
        /* mUnderBckIdx  */ LKANM_BCK_WALLWRDW,
        /* mUpperBckIdx  */ LKANM_BCK_WALLWRDW,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x001B,
    },
    {   // 0x48
        /* mUnderBckIdx  */ LKANM_BCK_WALLPL,
        /* mUpperBckIdx  */ LKANM_BCK_WALLPL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x001C,
    },
    {   // 0x49
        /* mUnderBckIdx  */ LKANM_BCK_WALLPR,
        /* mUpperBckIdx  */ LKANM_BCK_WALLPR,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x001D,
    },
    {   // 0x4A
        /* mUnderBckIdx  */ LKANM_BCK_WALLPLDW,
        /* mUpperBckIdx  */ LKANM_BCK_WALLPLDW,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x001C,
    },
    {   // 0x4B
        /* mUnderBckIdx  */ LKANM_BCK_WALLPRDW,
        /* mUpperBckIdx  */ LKANM_BCK_WALLPRDW,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x001D,
    },
    {   // 0x4C
        /* mUnderBckIdx  */ LKANM_BCK_VJMP,
        /* mUpperBckIdx  */ LKANM_BCK_VJMP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x4D
        /* mUnderBckIdx  */ LKANM_BCK_VJMPCHA,
        /* mUpperBckIdx  */ LKANM_BCK_VJMPCHA,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x004C,
    },
    {   // 0x4E
        /* mUnderBckIdx  */ LKANM_BCK_VJMPCHB,
        /* mUpperBckIdx  */ LKANM_BCK_VJMPCHB,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x4F
        /* mUnderBckIdx  */ LKANM_BCK_VJMPCL,
        /* mUpperBckIdx  */ LKANM_BCK_VJMPCL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x004D,
    },
    {   // 0x50
        /* mUnderBckIdx  */ LKANM_BCK_HANGING,
        /* mUpperBckIdx  */ LKANM_BCK_HANGING,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0054,
    },
    {   // 0x51
        /* mUnderBckIdx  */ LKANM_BCK_HANGUP,
        /* mUpperBckIdx  */ LKANM_BCK_HANGUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0055,
    },
    {   // 0x52
        /* mUnderBckIdx  */ LKANM_BCK_HANGMOVEL,
        /* mUpperBckIdx  */ LKANM_BCK_HANGMOVEL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x000C,
    },
    {   // 0x53
        /* mUnderBckIdx  */ LKANM_BCK_HANGMOVER,
        /* mUpperBckIdx  */ LKANM_BCK_HANGMOVER,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x000D,
    },
    {   // 0x54
        /* mUnderBckIdx  */ LKANM_BCK_DAM,
        /* mUpperBckIdx  */ LKANM_BCK_DAM,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x003A,
    },
    {   // 0x55
        /* mUnderBckIdx  */ LKANM_BCK_DAML,
        /* mUpperBckIdx  */ LKANM_BCK_DAML,
        /* mLeftHandIdx  */ 0x01,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x003A,
    },
    {   // 0x56
        /* mUnderBckIdx  */ LKANM_BCK_DAMR,
        /* mUpperBckIdx  */ LKANM_BCK_DAMR,
        /* mLeftHandIdx  */ 0x01,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x003A,
    },
    {   // 0x57
        /* mUnderBckIdx  */ LKANM_BCK_DAMF,
        /* mUpperBckIdx  */ LKANM_BCK_DAMF,
        /* mLeftHandIdx  */ 0x01,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x003A,
    },
    {   // 0x58
        /* mUnderBckIdx  */ LKANM_BCK_DAMB,
        /* mUpperBckIdx  */ LKANM_BCK_DAMB,
        /* mLeftHandIdx  */ 0x01,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x003A,
    },
    {   // 0x59
        /* mUnderBckIdx  */ LKANM_BCK_DAMFL,
        /* mUpperBckIdx  */ LKANM_BCK_DAMFL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x003B,
    },
    {   // 0x5A
        /* mUnderBckIdx  */ LKANM_BCK_DAMFR,
        /* mUpperBckIdx  */ LKANM_BCK_DAMFR,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x003B,
    },
    {   // 0x5B
        /* mUnderBckIdx  */ LKANM_BCK_DAMFF,
        /* mUpperBckIdx  */ LKANM_BCK_DAMFF,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x003B,
    },
    {   // 0x5C
        /* mUnderBckIdx  */ LKANM_BCK_DAMFB,
        /* mUpperBckIdx  */ LKANM_BCK_DAMFB,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x003B,
    },
    {   // 0x5D
        /* mUnderBckIdx  */ LKANM_BCK_DAMFLUP,
        /* mUpperBckIdx  */ LKANM_BCK_DAMFLUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x003E,
    },
    {   // 0x5E
        /* mUnderBckIdx  */ LKANM_BCK_DAMFRUP,
        /* mUpperBckIdx  */ LKANM_BCK_DAMFRUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x003F,
    },
    {   // 0x5F
        /* mUnderBckIdx  */ LKANM_BCK_DAMFFUP,
        /* mUpperBckIdx  */ LKANM_BCK_DAMFFUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x003C,
    },
    {   // 0x60
        /* mUnderBckIdx  */ LKANM_BCK_DAMFBUP,
        /* mUpperBckIdx  */ LKANM_BCK_DAMFBUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x003D,
    },
    {   // 0x61
        /* mUnderBckIdx  */ LKANM_BCK_LAVADAM,
        /* mUpperBckIdx  */ LKANM_BCK_LAVADAM,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0056,
    },
    {   // 0x62
        /* mUnderBckIdx  */ LKANM_BCK_DIELONG,
        /* mUpperBckIdx  */ LKANM_BCK_DIELONG,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0063,
    },
    {   // 0x63
        /* mUnderBckIdx  */ LKANM_BCK_SHIPDIE,
        /* mUpperBckIdx  */ LKANM_BCK_SHIPDIE,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0063,
    },
    {   // 0x64
        /* mUnderBckIdx  */ LKANM_BCK_SWIMDIE,
        /* mUpperBckIdx  */ LKANM_BCK_SWIMDIE,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0064,
    },
    {   // 0x65
        /* mUnderBckIdx  */ LKANM_BCK_GRABP,
        /* mUpperBckIdx  */ LKANM_BCK_GRABP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0015,
    },
    {   // 0x66
        /* mUnderBckIdx  */ LKANM_BCK_GRABUP,
        /* mUpperBckIdx  */ LKANM_BCK_GRABUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0016,
    },
    {   // 0x67
        /* mUnderBckIdx  */ LKANM_BCK_GRABNG,
        /* mUpperBckIdx  */ LKANM_BCK_GRABNG,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0017,
    },
    {   // 0x68
        /* mUnderBckIdx  */ LKANM_BCK_GRABWAIT,
        /* mUpperBckIdx  */ LKANM_BCK_GRABWAIT,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0009,
    },
    {   // 0x69
        /* mUnderBckIdx  */ LKANM_BCK_GRABWAITB,
        /* mUpperBckIdx  */ LKANM_BCK_GRABWAITB,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0012,
    },
    {   // 0x6A
        /* mUnderBckIdx  */ LKANM_BCK_GRABTHROW,
        /* mUpperBckIdx  */ LKANM_BCK_GRABTHROW,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0018,
    },
    {   // 0x6B
        /* mUnderBckIdx  */ LKANM_BCK_GRABRE,
        /* mUpperBckIdx  */ LKANM_BCK_GRABRE,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0019,
    },
    {   // 0x6C
        /* mUnderBckIdx  */ LKANM_BCK_MJMP,
        /* mUpperBckIdx  */ LKANM_BCK_MJMP,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0027,
    },
    {   // 0x6D
        /* mUnderBckIdx  */ LKANM_BCK_MJMPC,
        /* mUpperBckIdx  */ LKANM_BCK_MJMPC,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0028,
    },
    {   // 0x6E
        /* mUnderBckIdx  */ LKANM_BCK_MROLLL,
        /* mUpperBckIdx  */ LKANM_BCK_MROLLL,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0029,
    },
    {   // 0x6F
        /* mUnderBckIdx  */ LKANM_BCK_MROLLR,
        /* mUpperBckIdx  */ LKANM_BCK_MROLLR,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x002A,
    },
    {   // 0x70
        /* mUnderBckIdx  */ LKANM_BCK_MROLLLC,
        /* mUpperBckIdx  */ LKANM_BCK_MROLLLC,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x002B,
    },
    {   // 0x71
        /* mUnderBckIdx  */ LKANM_BCK_MROLLRC,
        /* mUpperBckIdx  */ LKANM_BCK_MROLLRC,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x002C,
    },
    {   // 0x72
        /* mUnderBckIdx  */ LKANM_BCK_MSTEPOVER,
        /* mUpperBckIdx  */ LKANM_BCK_MSTEPOVER,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x002D,
    },
    {   // 0x73
        /* mUnderBckIdx  */ LKANM_BCK_MSTEPOVERA,
        /* mUpperBckIdx  */ LKANM_BCK_MSTEPOVERA,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x002E,
    },
    {   // 0x74
        /* mUnderBckIdx  */ LKANM_BCK_MSTEPOVERLAND,
        /* mUpperBckIdx  */ LKANM_BCK_MSTEPOVERLAND,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x002F,
    },
    {   // 0x75
        /* mUnderBckIdx  */ LKANM_BCK_ROPECATCH,
        /* mUpperBckIdx  */ LKANM_BCK_ROPECATCH,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x004C,
    },
    {   // 0x76
        /* mUnderBckIdx  */ LKANM_BCK_ROPESWINGF,
        /* mUpperBckIdx  */ LKANM_BCK_ROPESWINGF,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x0008,
    },
    {   // 0x77
        /* mUnderBckIdx  */ LKANM_BCK_ROPESWINGB,
        /* mUpperBckIdx  */ LKANM_BCK_ROPESWINGB,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x0008,
    },
    {   // 0x78
        /* mUnderBckIdx  */ LKANM_BCK_ROPEWAIT,
        /* mUpperBckIdx  */ LKANM_BCK_ROPEWAIT,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x0009,
    },
    {   // 0x79
        /* mUnderBckIdx  */ LKANM_BCK_ROPECLIMB,
        /* mUpperBckIdx  */ LKANM_BCK_ROPECLIMB,
        /* mLeftHandIdx  */ 0x01,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x004E,
    },
    {   // 0x7A
        /* mUnderBckIdx  */ LKANM_BCK_ROPEDOWN,
        /* mUpperBckIdx  */ LKANM_BCK_ROPEDOWN,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x004F,
    },
    {   // 0x7B
        /* mUnderBckIdx  */ LKANM_BCK_ROPETHROWCATCH,
        /* mUpperBckIdx  */ LKANM_BCK_ROPETHROWCATCH,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0049,
    },
    {   // 0x7C
        /* mUnderBckIdx  */ LKANM_BCK_BOOMCATCH,
        /* mUpperBckIdx  */ LKANM_BCK_BOOMCATCH,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0049,
    },
    {   // 0x7D
        /* mUnderBckIdx  */ LKANM_BCK_VOYAGE1,
        /* mUpperBckIdx  */ LKANM_BCK_VOYAGE1,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x0002,
    },
    {   // 0x7E
        /* mUnderBckIdx  */ LKANM_BCK_WAITPUSHPULL,
        /* mUpperBckIdx  */ LKANM_BCK_WAITPUSHPULL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0002,
    },
    {   // 0x7F
        /* mUnderBckIdx  */ LKANM_BCK_WALKPUSH,
        /* mUpperBckIdx  */ LKANM_BCK_WALKPUSH,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x004A,
    },
    {   // 0x80
        /* mUnderBckIdx  */ LKANM_BCK_WALKPULL,
        /* mUpperBckIdx  */ LKANM_BCK_WALKPULL,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x004B,
    },
    {   // 0x81
        /* mUnderBckIdx  */ LKANM_BCK_SWIMP,
        /* mUpperBckIdx  */ LKANM_BCK_SWIMP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0046,
    },
    {   // 0x82
        /* mUnderBckIdx  */ LKANM_BCK_SWIMWAIT,
        /* mUpperBckIdx  */ LKANM_BCK_SWIMWAIT,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0003,
    },
    {   // 0x83
        /* mUnderBckIdx  */ LKANM_BCK_SWIMING,
        /* mUpperBckIdx  */ LKANM_BCK_SWIMING,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0047,
    },
    {   // 0x84
        /* mUnderBckIdx  */ LKANM_BCK_LADDERUPST,
        /* mUpperBckIdx  */ LKANM_BCK_LADDERUPST,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0050,
    },
    {   // 0x85
        /* mUnderBckIdx  */ LKANM_BCK_LADDERUPEDR,
        /* mUpperBckIdx  */ LKANM_BCK_LADDERUPEDR,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0052,
    },
    {   // 0x86
        /* mUnderBckIdx  */ LKANM_BCK_LADDERUPEDL,
        /* mUpperBckIdx  */ LKANM_BCK_LADDERUPEDL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0052,
    },
    {   // 0x87
        /* mUnderBckIdx  */ LKANM_BCK_LADDERDWST,
        /* mUpperBckIdx  */ LKANM_BCK_LADDERDWST,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0051,
    },
    {   // 0x88
        /* mUnderBckIdx  */ LKANM_BCK_LADDERDWEDR,
        /* mUpperBckIdx  */ LKANM_BCK_LADDERDWEDR,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0053,
    },
    {   // 0x89
        /* mUnderBckIdx  */ LKANM_BCK_LADDERDWEDL,
        /* mUpperBckIdx  */ LKANM_BCK_LADDERDWEDL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0053,
    },
    {   // 0x8A
        /* mUnderBckIdx  */ LKANM_BCK_LADDERRTOL,
        /* mUpperBckIdx  */ LKANM_BCK_LADDERRTOL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x000A,
    },
    {   // 0x8B
        /* mUnderBckIdx  */ LKANM_BCK_LADDERLTOR,
        /* mUpperBckIdx  */ LKANM_BCK_LADDERLTOR,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x000A,
    },
    {   // 0x8C
        /* mUnderBckIdx  */ LKANM_BCK_FCLIMBSLIDELUP,
        /* mUpperBckIdx  */ LKANM_BCK_FCLIMBSLIDELUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0009,
    },
    {   // 0x8D
        /* mUnderBckIdx  */ LKANM_BCK_FCLIMBSLIDERUP,
        /* mUpperBckIdx  */ LKANM_BCK_FCLIMBSLIDERUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0009,
    },
    {   // 0x8E
        /* mUnderBckIdx  */ LKANM_BCK_BOXOPENLINK,
        /* mUpperBckIdx  */ LKANM_BCK_BOXOPENLINK,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0061,
    },
    {   // 0x8F
        /* mUnderBckIdx  */ LKANM_BCK_BOXOPENSHORTLINK,
        /* mUpperBckIdx  */ LKANM_BCK_BOXOPENSHORTLINK,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0062,
    },
    {   // 0x90
        /* mUnderBckIdx  */ LKANM_BCK_ITEMGET,
        /* mUpperBckIdx  */ LKANM_BCK_ITEMGET,
        /* mLeftHandIdx  */ 0x04,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x005D,
    },
    {   // 0x91
        /* mUnderBckIdx  */ LKANM_BCK_HOLDUP,
        /* mUpperBckIdx  */ LKANM_BCK_HOLDUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x005B,
    },
    {   // 0x92
        /* mUnderBckIdx  */ LKANM_BCK_WALLHOLDUP,
        /* mUpperBckIdx  */ LKANM_BCK_WALLHOLDUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x005C,
    },
    {   // 0x93
        /* mUnderBckIdx  */ LKANM_BCK_WALLHOLDUPDW,
        /* mUpperBckIdx  */ LKANM_BCK_WALLHOLDUPDW,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x005C,
    },
    {   // 0x94
        /* mUnderBckIdx  */ LKANM_BCK_COMEOUT,
        /* mUpperBckIdx  */ LKANM_BCK_COMEOUT,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x005A,
    },
    {   // 0x95
        /* mUnderBckIdx  */ LKANM_BCK_WALKBARREL,
        /* mUpperBckIdx  */ LKANM_BCK_WALKBARREL,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0x96
        /* mUnderBckIdx  */ LKANM_BCK_SALTATION,
        /* mUpperBckIdx  */ LKANM_BCK_SALTATION,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x005E,
    },
    {   // 0x97
        /* mUnderBckIdx  */ LKANM_BCK_WHO,
        /* mUpperBckIdx  */ LKANM_BCK_WHO,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x005F,
    },
    {   // 0x98
        /* mUnderBckIdx  */ LKANM_BCK_PICKUP,
        /* mUpperBckIdx  */ LKANM_BCK_PICKUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0060,
    },
    {   // 0x99
        /* mUnderBckIdx  */ LKANM_BCK_WAITPICKUP,
        /* mUpperBckIdx  */ LKANM_BCK_WAITPICKUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0013,
    },
    {   // 0x9A
        /* mUnderBckIdx  */ LKANM_BCK_SURPRISED,
        /* mUpperBckIdx  */ LKANM_BCK_SURPRISED,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0065,
    },
    {   // 0x9B
        /* mUnderBckIdx  */ LKANM_BCK_TURNBACK,
        /* mUpperBckIdx  */ LKANM_BCK_TURNBACK,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0066,
    },
    {   // 0x9C
        /* mUnderBckIdx  */ LKANM_BCK_LOOKUP,
        /* mUpperBckIdx  */ LKANM_BCK_LOOKUP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0067,
    },
    {   // 0x9D
        /* mUnderBckIdx  */ LKANM_BCK_WAITQ,
        /* mUpperBckIdx  */ LKANM_BCK_WAITQ,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0092,
    },
    {   // 0x9E
        /* mUnderBckIdx  */ LKANM_BCK_GLAD,
        /* mUpperBckIdx  */ LKANM_BCK_GLAD,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0069,
    },
    {   // 0x9F
        /* mUnderBckIdx  */ LKANM_BCK_SHIP_JUMP1,
        /* mUpperBckIdx  */ LKANM_BCK_SHIP_JUMP1,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x006B,
    },
    {   // 0xA0
        /* mUnderBckIdx  */ LKANM_BCK_SHIP_JUMP2,
        /* mUpperBckIdx  */ LKANM_BCK_SHIP_JUMP2,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x006C,
    },
    {   // 0xA1
        /* mUnderBckIdx  */ LKANM_BCK_USEFANA,
        /* mUpperBckIdx  */ LKANM_BCK_USEFANA,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x006D,
    },
    {   // 0xA2
        /* mUnderBckIdx  */ LKANM_BCK_USEFANB,
        /* mUpperBckIdx  */ LKANM_BCK_USEFANB,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x006E,
    },
    {   // 0xA3
        /* mUnderBckIdx  */ LKANM_BCK_USEFANB2,
        /* mUpperBckIdx  */ LKANM_BCK_USEFANB2,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x006F,
    },
    {   // 0xA4
        /* mUnderBckIdx  */ LKANM_BCK_MOGAKU1,
        /* mUpperBckIdx  */ LKANM_BCK_MOGAKU1,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0xA5
        /* mUnderBckIdx  */ LKANM_BCK_FM_BATA,
        /* mUpperBckIdx  */ LKANM_BCK_FM_BATA,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0xA6
        /* mUnderBckIdx  */ LKANM_BCK_HOOKSHOTJMP,
        /* mUpperBckIdx  */ LKANM_BCK_HOOKSHOTJMP,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0014,
    },
    {   // 0xA7
        /* mUnderBckIdx  */ LKANM_BCK_VOMITJMP,
        /* mUpperBckIdx  */ LKANM_BCK_VOMITJMP,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0071,
    },
    {   // 0xA8
        /* mUnderBckIdx  */ LKANM_BCK_WAITTAKT,
        /* mUpperBckIdx  */ LKANM_BCK_WAITTAKT,
        /* mLeftHandIdx  */ 0x05,
        /* mRightHandIdx */ 0x0A,
        /* mTexAnmIdx    */ 0x0006,
    },
    {   // 0xA9
        /* mUnderBckIdx  */ LKANM_BCK_SLIPICE,
        /* mUpperBckIdx  */ LKANM_BCK_SLIPICE,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0075,
    },
    {   // 0xAA
        /* mUnderBckIdx  */ LKANM_BCK_HAMSWINGA,
        /* mUpperBckIdx  */ LKANM_BCK_HAMSWINGA,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x0076,
    },
    {   // 0xAB
        /* mUnderBckIdx  */ LKANM_BCK_HAMSWINGBPRE,
        /* mUpperBckIdx  */ LKANM_BCK_HAMSWINGBPRE,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x0077,
    },
    {   // 0xAC
        /* mUnderBckIdx  */ LKANM_BCK_HAMSWINGBHIT,
        /* mUpperBckIdx  */ LKANM_BCK_HAMSWINGBHIT,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x0078,
    },
    {   // 0xAD
        /* mUnderBckIdx  */ LKANM_BCK_HAMSWINGBEND,
        /* mUpperBckIdx  */ LKANM_BCK_HAMSWINGBEND,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x0079,
    },
    {   // 0xAE
        /* mUnderBckIdx  */ LKANM_BCK_SETBOOTS,
        /* mUpperBckIdx  */ LKANM_BCK_SETBOOTS,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x007A,
    },
    {   // 0xAF
        /* mUnderBckIdx  */ LKANM_BCK_DOOROPENALINK,
        /* mUpperBckIdx  */ LKANM_BCK_DOOROPENALINK,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x007B,
    },
    {   // 0xB0
        /* mUnderBckIdx  */ LKANM_BCK_DOOROPENBLINK,
        /* mUpperBckIdx  */ LKANM_BCK_DOOROPENBLINK,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x007C,
    },
    {   // 0xB1
        /* mUnderBckIdx  */ LKANM_BCK_SEYYES,
        /* mUpperBckIdx  */ LKANM_BCK_SEYYES,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x007D,
    },
    {   // 0xB2
        /* mUnderBckIdx  */ LKANM_BCK_PRESENTATIONA,
        /* mUpperBckIdx  */ LKANM_BCK_PRESENTATIONA,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x007E,
    },
    {   // 0xB3
        /* mUnderBckIdx  */ LKANM_BCK_WINDL,
        /* mUpperBckIdx  */ LKANM_BCK_WINDL,
        /* mLeftHandIdx  */ 0x05,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x007F,
    },
    {   // 0xB4
        /* mUnderBckIdx  */ LKANM_BCK_WINDR,
        /* mUpperBckIdx  */ LKANM_BCK_WINDR,
        /* mLeftHandIdx  */ 0x05,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0080,
    },
    {   // 0xB5
        /* mUnderBckIdx  */ LKANM_BCK_PRESENTATIONB,
        /* mUpperBckIdx  */ LKANM_BCK_PRESENTATIONB,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x0081,
    },
    {   // 0xB6
        /* mUnderBckIdx  */ LKANM_BCK_BINDRINKPRE,
        /* mUpperBckIdx  */ LKANM_BCK_BINDRINKPRE,
        /* mLeftHandIdx  */ 0x06,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x0082,
    },
    {   // 0xB7
        /* mUnderBckIdx  */ LKANM_BCK_BINDRINKING,
        /* mUpperBckIdx  */ LKANM_BCK_BINDRINKING,
        /* mLeftHandIdx  */ 0x06,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x0083,
    },
    {   // 0xB8
        /* mUnderBckIdx  */ LKANM_BCK_BINDRINKAFTER,
        /* mUpperBckIdx  */ LKANM_BCK_BINDRINKAFTER,
        /* mLeftHandIdx  */ 0x06,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x0084,
    },
    {   // 0xB9
        /* mUnderBckIdx  */ LKANM_BCK_BINOPENPRE,
        /* mUpperBckIdx  */ LKANM_BCK_BINOPENPRE,
        /* mLeftHandIdx  */ 0x06,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x0088,
    },
    {   // 0xBA
        /* mUnderBckIdx  */ LKANM_BCK_BINOPENA,
        /* mUpperBckIdx  */ LKANM_BCK_BINOPENA,
        /* mLeftHandIdx  */ 0x06,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0089,
    },
    {   // 0xBB
        /* mUnderBckIdx  */ LKANM_BCK_BINOPENB,
        /* mUpperBckIdx  */ LKANM_BCK_BINOPENB,
        /* mLeftHandIdx  */ 0x06,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x008A,
    },
    {   // 0xBC
        /* mUnderBckIdx  */ LKANM_BCK_BINSWINGS,
        /* mUpperBckIdx  */ LKANM_BCK_BINSWINGS,
        /* mLeftHandIdx  */ 0x06,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x008B,
    },
    {   // 0xBD
        /* mUnderBckIdx  */ LKANM_BCK_BINSWINGU,
        /* mUpperBckIdx  */ LKANM_BCK_BINSWINGU,
        /* mLeftHandIdx  */ 0x06,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x008B,
    },
    {   // 0xBE
        /* mUnderBckIdx  */ LKANM_BCK_BINGET,
        /* mUpperBckIdx  */ LKANM_BCK_BINGET,
        /* mLeftHandIdx  */ 0x06,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x008C,
    },
    {   // 0xBF
        /* mUnderBckIdx  */ LKANM_BCK_SURPRISEDB,
        /* mUpperBckIdx  */ LKANM_BCK_SURPRISEDB,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x008E,
    },
    {   // 0xC0
        /* mUnderBckIdx  */ LKANM_BCK_RISE,
        /* mUpperBckIdx  */ LKANM_BCK_RISE,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0001,
    },
    {   // 0xC1
        /* mUnderBckIdx  */ LKANM_BCK_USETCEIVER,
        /* mUpperBckIdx  */ LKANM_BCK_USETCEIVER,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x0005,
    },
    {   // 0xC2
        /* mUnderBckIdx  */ LKANM_BCK_YOBU,
        /* mUpperBckIdx  */ LKANM_BCK_YOBU,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0006,
    },
    {   // 0xC3
        /* mUnderBckIdx  */ LKANM_BCK_NENRIKI,
        /* mUpperBckIdx  */ LKANM_BCK_NENRIKI,
        /* mLeftHandIdx  */ 0x06,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x0090,
    },
    {   // 0xC4
        /* mUnderBckIdx  */ LKANM_BCK_ESAMAKI,
        /* mUpperBckIdx  */ LKANM_BCK_ESAMAKI,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0004,
    },
    {   // 0xC5
        /* mUnderBckIdx  */ LKANM_BCK_SETHYOINOMI,
        /* mUpperBckIdx  */ LKANM_BCK_SETHYOINOMI,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0093,
    },
    {   // 0xC6
        /* mUnderBckIdx  */ LKANM_BCK_GETLETTER,
        /* mUpperBckIdx  */ LKANM_BCK_GETLETTER,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x0005,
    },
    {   // 0xC7
        /* mUnderBckIdx  */ LKANM_BCK_WAITLETTER,
        /* mUpperBckIdx  */ LKANM_BCK_WAITLETTER,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x09,
        /* mTexAnmIdx    */ 0x0005,
    },
    {   // 0xC8
        /* mUnderBckIdx  */ LKANM_BCK_LINK_FREEZ,
        /* mUpperBckIdx  */ LKANM_BCK_LINK_FREEZ,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0094,
    },
    {   // 0xC9
        /* mUnderBckIdx  */ LKANM_BCK_LINK_MOGAKI,
        /* mUpperBckIdx  */ LKANM_BCK_LINK_MOGAKI,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0095,
    },
    {   // 0xCA
        /* mUnderBckIdx  */ LKANM_BCK_TAKTDGE,
        /* mUpperBckIdx  */ LKANM_BCK_TAKTDGE,
        /* mLeftHandIdx  */ 0x05,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x005D,
    },
    {   // 0xCB
        /* mUnderBckIdx  */ LKANM_BCK_DAMBIRI,
        /* mUpperBckIdx  */ LKANM_BCK_DAMBIRI,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0096,
    },
    {   // 0xCC
        /* mUnderBckIdx  */ LKANM_BCK_SALVLR,
        /* mUpperBckIdx  */ LKANM_BCK_SALVLR,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0097,
    },
    {   // 0xCD
        /* mUnderBckIdx  */ LKANM_BCK_SALVRWAIT,
        /* mUpperBckIdx  */ LKANM_BCK_SALVRWAIT,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0xCE
        /* mUnderBckIdx  */ LKANM_BCK_SALVLWAIT,
        /* mUpperBckIdx  */ LKANM_BCK_SALVLWAIT,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0xCF
        /* mUnderBckIdx  */ LKANM_BCK_SALVRBAD,
        /* mUpperBckIdx  */ LKANM_BCK_SALVRBAD,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0099,
    },
    {   // 0xD0
        /* mUnderBckIdx  */ LKANM_BCK_SALVLBAD,
        /* mUpperBckIdx  */ LKANM_BCK_SALVLBAD,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0099,
    },
    {   // 0xD1
        /* mUnderBckIdx  */ LKANM_BCK_SALVRGOOD,
        /* mUpperBckIdx  */ LKANM_BCK_SALVRGOOD,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x009A,
    },
    {   // 0xD2
        /* mUnderBckIdx  */ LKANM_BCK_SALVLGOOD,
        /* mUpperBckIdx  */ LKANM_BCK_SALVLGOOD,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x009A,
    },
    {   // 0xD3
        /* mUnderBckIdx  */ LKANM_BCK_MSTEPOVER,
        /* mUpperBckIdx  */ LKANM_BCK_JMPED,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0037,
    },
    {   // 0xD4
        /* mUnderBckIdx  */ LKANM_BCK_BOXOPENSLINK,
        /* mUpperBckIdx  */ LKANM_BCK_BOXOPENSLINK,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0061,
    },
    {   // 0xD5
        /* mUnderBckIdx  */ LKANM_BCK_SEARESET,
        /* mUpperBckIdx  */ LKANM_BCK_SEARESET,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x009B,
    },
    {   // 0xD6
        /* mUnderBckIdx  */ LKANM_BCK_WARPIN,
        /* mUpperBckIdx  */ LKANM_BCK_WARPIN,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x009C,
    },
    {   // 0xD7
        /* mUnderBckIdx  */ LKANM_BCK_WARPOUT,
        /* mUpperBckIdx  */ LKANM_BCK_WARPOUT,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x009D,
    },
    {   // 0xD8
        /* mUnderBckIdx  */ LKANM_BCK_SURPRISEDWAIT,
        /* mUpperBckIdx  */ LKANM_BCK_SURPRISEDWAIT,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0065,
    },
    {   // 0xD9
        /* mUnderBckIdx  */ LKANM_BCK_PRESENTATIONAWAIT,
        /* mUpperBckIdx  */ LKANM_BCK_PRESENTATIONAWAIT,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x07,
        /* mTexAnmIdx    */ 0x0004,
    },
    {   // 0xDA
        /* mUnderBckIdx  */ LKANM_BCK_POWUPWAIT,
        /* mUpperBckIdx  */ LKANM_BCK_POWUPWAIT,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x009E,
    },
    {   // 0xDB
        /* mUnderBckIdx  */ LKANM_BCK_POWUP,
        /* mUpperBckIdx  */ LKANM_BCK_POWUP,
        /* mLeftHandIdx  */ 0x02,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x009F,
    },
    {   // 0xDC
        /* mUnderBckIdx  */ LKANM_BCK_KOSHIKAKE,
        /* mUpperBckIdx  */ LKANM_BCK_KOSHIKAKE,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0002,
    },
    {   // 0xDD
        /* mUnderBckIdx  */ LKANM_BCK_COMBO_LINK,
        /* mUpperBckIdx  */ LKANM_BCK_COMBO_LINK,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x0003,
    },
    {   // 0xDE
        /* mUnderBckIdx  */ LKANM_BCK_CUTKESA,
        /* mUpperBckIdx  */ LKANM_BCK_CUTKESA,
        /* mLeftHandIdx  */ 0x03,
        /* mRightHandIdx */ 0x08,
        /* mTexAnmIdx    */ 0x00A0,
    },
    {   // 0xDF
        /* mUnderBckIdx  */ LKANM_BCK_WARPOUTFIRST,
        /* mUpperBckIdx  */ LKANM_BCK_WARPOUTFIRST,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x00A1,
    },
    {   // 0xE0
        /* mUnderBckIdx  */ LKANM_BCK_WAITAUCTION,
        /* mUpperBckIdx  */ LKANM_BCK_WAITAUCTION,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x0000,
    },
    {   // 0xE1
        /* mUnderBckIdx  */ LKANM_BCK_FREEA,
        /* mUpperBckIdx  */ LKANM_BCK_FREEA,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x00A4,
    },
    {   // 0xE2
        /* mUnderBckIdx  */ LKANM_BCK_FREEB,
        /* mUpperBckIdx  */ LKANM_BCK_FREEB,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x00A5,
    },
    {   // 0xE3
        /* mUnderBckIdx  */ LKANM_BCK_FREED,
        /* mUpperBckIdx  */ LKANM_BCK_FREED,
        /* mLeftHandIdx  */ 0x00,
        /* mRightHandIdx */ 0x00,
        /* mTexAnmIdx    */ 0x00A6,
    },
    {   // 0xE4
        /* mUnderBckIdx  */ LKANM_BCK_TAKTKAZE,
        /* mUpperBckIdx  */ LKANM_BCK_TAKTKAZE,
        /* mLeftHandIdx  */ 0x05,
        /* mRightHandIdx */ 0x0A,
        /* mTexAnmIdx    */ 0x00A7,
    },
    {   // 0xE5
        /* mUnderBckIdx  */ LKANM_BCK_TAKTSIPPU,
        /* mUpperBckIdx  */ LKANM_BCK_TAKTSIPPU,
        /* mLeftHandIdx  */ 0x05,
        /* mRightHandIdx */ 0x0A,
        /* mTexAnmIdx    */ 0x00A8,
    },
    {   // 0xE6
        /* mUnderBckIdx  */ LKANM_BCK_TAKTCHUYA,
        /* mUpperBckIdx  */ LKANM_BCK_TAKTCHUYA,
        /* mLeftHandIdx  */ 0x05,
        /* mRightHandIdx */ 0x0A,
        /* mTexAnmIdx    */ 0x00A9,
    },
    {   // 0xE7
        /* mUnderBckIdx  */ LKANM_BCK_TAKTFUJIN,
        /* mUpperBckIdx  */ LKANM_BCK_TAKTFUJIN,
        /* mLeftHandIdx  */ 0x05,
        /* mRightHandIdx */ 0x0A,
        /* mTexAnmIdx    */ 0x00AA,
    },
    {   // 0xE8
        /* mUnderBckIdx  */ LKANM_BCK_TAKTAYATSURI,
        /* mUpperBckIdx  */ LKANM_BCK_TAKTAYATSURI,
        /* mLeftHandIdx  */ 0x05,
        /* mRightHandIdx */ 0x0A,
        /* mTexAnmIdx    */ 0x00AB,
    },
    {   // 0xE9
        /* mUnderBckIdx  */ LKANM_BCK_TAKTCHISIN,
        /* mUpperBckIdx  */ LKANM_BCK_TAKTCHISIN,
        /* mLeftHandIdx  */ 0x05,
        /* mRightHandIdx */ 0x0A,
        /* mTexAnmIdx    */ 0x00AC,
    },
};

#include "d/actor/d_a_player_HIO.inc"

// Needed for the .data section to match.
static Vec dummy_2100 = {1.0f, 1.0f, 1.0f};
static Vec dummy_2080 = {1.0f, 1.0f, 1.0f};

char l_arcName[] = "Link";

char l_tact_event_label[] = "OPTION_CHAR_START";
char l_tact_night_event_label[] = "TIMEWARP";
char l_tact_wind_change_event_label[] = "TACT_WINDOW2";
char l_tact_wind_change_event_label2[] = "TACT_WINDOW2_SHIP";

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_PLAYER,
        /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK2 | CO_SPRM_VSGRP,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0x25,
        /* SrcGObjTg HitMark */ G_TG_MARK_PURPLE_HIT,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
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
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_WIND,
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_PLAYER,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ G_AT_SPRM_NO_HIT_MARK,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
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
        /* SrcObjAt  Type    */ AT_TYPE_SWORD,
        /* SrcObjAt  Atp     */ 0x02,
        /* SrcObjAt  SPrm    */ AT_SPRM_SET | AT_SPRM_VS_ENEMY | AT_SPRM_VS_OTHER,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ G_AT_MARK_BIG_HIT,
        /* SrcGObjAt Spl     */ 0x01,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
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
        /* SrcObjAt  Type    */ AT_TYPE_SWORD,
        /* SrcObjAt  Atp     */ 0x01,
        /* SrcObjAt  SPrm    */ AT_SPRM_SET | AT_SPRM_VS_ENEMY | AT_SPRM_VS_OTHER,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0x01,
        /* SrcGObjAt HitMark */ G_AT_MARK_NORMAL_HIT,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
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
        /* SrcObjAt  Type    */ AT_TYPE_WIND,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ AT_SPRM_SET | AT_SPRM_VS_ENEMY | AT_SPRM_VS_OTHER,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ G_AT_SPRM_NO_HIT_MARK,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
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
        /* SrcObjAt  Type    */ AT_TYPE_WIND,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ AT_SPRM_SET | AT_SPRM_VS_ENEMY | AT_SPRM_VS_OTHER,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 150.0f,
    },
};

Vec dummy_3569;
JGeometry::TVec3<f32> l_hammer_splash_particle_scale(0.00002f, 0.00002f, 0.00002f);

daPy_lk_c::ProcInitTableEntry daPy_lk_c::mProcInitTable[] = {
    /* 0x00 */ {&daPy_lk_c::procScope,                 ModeFlg_00000001},
    /* 0x01 */ {&daPy_lk_c::procSubjectivity,          ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_00001000 | ModeFlg_SUBJECT},
    /* 0x02 */ {&daPy_lk_c::procCall,                  ModeFlg_00000001 | ModeFlg_00000080 | ModeFlg_00000100},
    /* 0x03 */ {&daPy_lk_c::procControllWait,          ModeFlg_00000001},
    /* 0x04 */ {&daPy_lk_c::procWait,                  ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_00000040 | ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_00001000 | ModeFlg_00020000},
    /* 0x05 */ {&daPy_lk_c::procFreeWait,              ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_00000040 | ModeFlg_00000400 | ModeFlg_00020000},
    /* 0x06 */ {&daPy_lk_c::procMove,                  ModeFlg_00000004 | ModeFlg_00000040 | ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_00001000 | ModeFlg_00020000},
    /* 0x07 */ {&daPy_lk_c::procAtnMove,               ModeFlg_00000004 | ModeFlg_00000040 | ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_00001000 | ModeFlg_00020000},
    /* 0x08 */ {&daPy_lk_c::procAtnActorWait,          ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_00000040 | ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_00001000 | ModeFlg_00020000},
    /* 0x09 */ {&daPy_lk_c::procAtnActorMove,          ModeFlg_00000004 | ModeFlg_00000040 | ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_00001000 | ModeFlg_00020000},
    /* 0x0A */ {&daPy_lk_c::procSideStep,              ModeFlg_MIDAIR | ModeFlg_00000004 | ModeFlg_00000040 | ModeFlg_00000080 | ModeFlg_00000400 | ModeFlg_00001000},
    /* 0x0B */ {&daPy_lk_c::procSideStepLand,          ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_00000040 | ModeFlg_00000080 | ModeFlg_00001000},
    /* 0x0C */ {&daPy_lk_c::procCrouchDefense,         ModeFlg_00000001 | ModeFlg_00000100 | ModeFlg_CROUCH | ModeFlg_08000000 | ModeFlg_SUBJECT | ModeFlg_40000000},
    /* 0x0D */ {&daPy_lk_c::procCrouchDefenseSlip,     ModeFlg_00000400 | ModeFlg_CROUCH | ModeFlg_SUBJECT | ModeFlg_40000000},
    /* 0x0E */ {&daPy_lk_c::procCrouch,                ModeFlg_00000001 | ModeFlg_00000100 | ModeFlg_CROUCH},
    /* 0x0F */ {&daPy_lk_c::procCrawlStart,            ModeFlg_00000100 | ModeFlg_00008000 | ModeFlg_CRAWL | ModeFlg_02000000},
    /* 0x10 */ {&daPy_lk_c::procCrawlMove,             ModeFlg_00000100 | ModeFlg_00008000 | ModeFlg_CRAWL | ModeFlg_02000000 | ModeFlg_08000000},
    /* 0x11 */ {&daPy_lk_c::procCrawlAutoMove,         ModeFlg_00000100 | ModeFlg_00008000 | ModeFlg_CRAWL | ModeFlg_02000000 | ModeFlg_04000000 | ModeFlg_08000000},
    /* 0x12 */ {&daPy_lk_c::procCrawlEnd,              ModeFlg_00008000 | ModeFlg_CRAWL | ModeFlg_02000000},
    /* 0x13 */ {&daPy_lk_c::procWHideReady,            ModeFlg_00000001 | ModeFlg_WHIDE},
    /* 0x14 */ {&daPy_lk_c::procWHideWait,             ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_WHIDE | ModeFlg_00000100},
    /* 0x15 */ {&daPy_lk_c::procWHideMove,             ModeFlg_00000004 | ModeFlg_WHIDE},
    /* 0x16 */ {&daPy_lk_c::procWHidePeep,             ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_WHIDE | ModeFlg_00000400},
    /* 0x17 */ {&daPy_lk_c::procWaitTurn,              ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_00000040 | ModeFlg_00000100 | ModeFlg_00001000 | ModeFlg_00004000 | ModeFlg_00020000},
    /* 0x18 */ {&daPy_lk_c::procMoveTurn,              ModeFlg_00000004 | ModeFlg_00000040 | ModeFlg_00004000 | ModeFlg_00020000},
    /* 0x19 */ {&daPy_lk_c::procSlip,                  ModeFlg_00000100},
    /* 0x1A */ {&daPy_lk_c::procSlideFront,            ModeFlg_00000400 | ModeFlg_00008000},
    /* 0x1B */ {&daPy_lk_c::procSlideBack,             0},
    /* 0x1C */ {&daPy_lk_c::procSlideFrontLand,        ModeFlg_00000004 | ModeFlg_00000400},
    /* 0x1D */ {&daPy_lk_c::procSlideBackLand,         ModeFlg_00000004 | ModeFlg_00000400},
    /* 0x1E */ {&daPy_lk_c::procFrontRoll,             ModeFlg_00000400 | ModeFlg_00008000},
    /* 0x1F */ {&daPy_lk_c::procFrontRollCrash,        ModeFlg_MIDAIR | ModeFlg_00000400},
    /* 0x20 */ {&daPy_lk_c::procNockBackEnd,           ModeFlg_00000400 | ModeFlg_00008000},
    /* 0x21 */ {&daPy_lk_c::procSideRoll,              ModeFlg_00000400 | ModeFlg_00008000},
    /* 0x22 */ {&daPy_lk_c::procBackJump,              ModeFlg_MIDAIR | ModeFlg_00000004 | ModeFlg_00000040 | ModeFlg_00000400},
    /* 0x23 */ {&daPy_lk_c::procBackJumpLand,          ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_00000040 | ModeFlg_00000400},
    /* 0x24 */ {&daPy_lk_c::procAutoJump,              ModeFlg_MIDAIR | ModeFlg_00000004 | ModeFlg_00000400 | ModeFlg_00001000 | ModeFlg_00004000},
    /* 0x25 */ {&daPy_lk_c::procLand,                  ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_00001000 | ModeFlg_00004000},
    /* 0x26 */ {&daPy_lk_c::procLandDamage,            ModeFlg_00000001 | ModeFlg_DAMAGE | ModeFlg_00000400},
    /* 0x27 */ {&daPy_lk_c::procFall,                  ModeFlg_MIDAIR | ModeFlg_00000004 | ModeFlg_00001000},
    /* 0x28 */ {&daPy_lk_c::procSlowFall,              ModeFlg_MIDAIR},
    /* 0x29 */ {&daPy_lk_c::procSmallJump,             ModeFlg_MIDAIR | ModeFlg_00004000},
    /* 0x2A */ {&daPy_lk_c::procVerticalJump,          ModeFlg_00000001},
    /* 0x2B */ {&daPy_lk_c::procHangStart,             ModeFlg_00000001 | ModeFlg_HANG | ModeFlg_00000400},
    /* 0x2C */ {&daPy_lk_c::procHangFallStart,         ModeFlg_00000001 | ModeFlg_HANG | ModeFlg_00000400},
    /* 0x2D */ {&daPy_lk_c::procHangUp,                ModeFlg_00000001 | ModeFlg_HANG | ModeFlg_00000400},
    /* 0x2E */ {&daPy_lk_c::procHangWait,              ModeFlg_00000001 | ModeFlg_HANG | ModeFlg_00000100},
    /* 0x2F */ {&daPy_lk_c::procHangMove,              ModeFlg_HANG | ModeFlg_00000100},
    /* 0x30 */ {&daPy_lk_c::procHangClimb,             ModeFlg_HANG | ModeFlg_00000400},
    /* 0x31 */ {&daPy_lk_c::procHangWallCatch,         ModeFlg_HANG},
    /* 0x32 */ {&daPy_lk_c::procPushPullWait,          ModeFlg_00000001 | ModeFlg_00000100 | ModeFlg_PUSHPULL},
    /* 0x33 */ {&daPy_lk_c::procPushMove,              ModeFlg_PUSHPULL},
    /* 0x34 */ {&daPy_lk_c::procPullMove,              ModeFlg_00000400 | ModeFlg_PUSHPULL},
    /* 0x35 */ {&daPy_lk_c::procSwimUp,                ModeFlg_00000400 | ModeFlg_SWIM | ModeFlg_04000000},
    /* 0x36 */ {&daPy_lk_c::procSwimWait,              ModeFlg_00000001 | ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_SWIM | ModeFlg_04000000},
    /* 0x37 */ {&daPy_lk_c::procSwimMove,              ModeFlg_00000080 | ModeFlg_00000400 | ModeFlg_SWIM | ModeFlg_04000000},
    /* 0x38 */ {&daPy_lk_c::procLadderUpStart,         ModeFlg_00000400 | ModeFlg_LADDER},
    /* 0x39 */ {&daPy_lk_c::procLadderUpEnd,           ModeFlg_00000400 | ModeFlg_LADDER},
    /* 0x3A */ {&daPy_lk_c::procLadderDownStart,       ModeFlg_00000400 | ModeFlg_LADDER},
    /* 0x3B */ {&daPy_lk_c::procLadderDownEnd,         ModeFlg_00000400 | ModeFlg_LADDER},
    /* 0x3C */ {&daPy_lk_c::procLadderMove,            ModeFlg_00000100 | ModeFlg_LADDER},
    /* 0x3D */ {&daPy_lk_c::procClimbUpStart,          ModeFlg_00000400 | ModeFlg_CLIMB},
    /* 0x3E */ {&daPy_lk_c::procClimbDownStart,        ModeFlg_00000400 | ModeFlg_CLIMB},
    /* 0x3F */ {&daPy_lk_c::procClimbMoveUpDown,       ModeFlg_00000100 | ModeFlg_CLIMB},
    /* 0x40 */ {&daPy_lk_c::procClimbMoveSide,         ModeFlg_00000100 | ModeFlg_CLIMB},
    /* 0x41 */ {&daPy_lk_c::procCutA,                  ModeFlg_00000080 | ModeFlg_00000400},
    /* 0x42 */ {&daPy_lk_c::procCutF,                  ModeFlg_00000080 | ModeFlg_00000400},
    /* 0x43 */ {&daPy_lk_c::procCutR,                  ModeFlg_00000080 | ModeFlg_00000400},
    /* 0x44 */ {&daPy_lk_c::procCutL,                  ModeFlg_00000080 | ModeFlg_00000400},
    /* 0x45 */ {&daPy_lk_c::procCutEA,                 ModeFlg_00000080 | ModeFlg_00000400},
    /* 0x46 */ {&daPy_lk_c::procCutEB,                 ModeFlg_00000080 | ModeFlg_00000400},
    /* 0x47 */ {&daPy_lk_c::procCutExA,                ModeFlg_00000400},
    /* 0x48 */ {&daPy_lk_c::procCutExB,                ModeFlg_00000400},
    /* 0x49 */ {&daPy_lk_c::procCutExMJ,               ModeFlg_MIDAIR | ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x4A */ {&daPy_lk_c::procCutKesa,               ModeFlg_00000400},
    /* 0x4B */ {&daPy_lk_c::procWeaponNormalSwing,     ModeFlg_00000080 | ModeFlg_00000400},
    /* 0x4C */ {&daPy_lk_c::procWeaponSideSwing,       ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x4D */ {&daPy_lk_c::procWeaponFrontSwingReady, ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x4E */ {&daPy_lk_c::procWeaponFrontSwing,      ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x4F */ {&daPy_lk_c::procWeaponFrontSwingEnd,   ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x50 */ {&daPy_lk_c::procWeaponThrow,           ModeFlg_00000080 | ModeFlg_00000400},
    /* 0x51 */ {&daPy_lk_c::procHammerSideSwing,       ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x52 */ {&daPy_lk_c::procHammerFrontSwingReady, ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x53 */ {&daPy_lk_c::procHammerFrontSwing,      ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x54 */ {&daPy_lk_c::procHammerFrontSwingEnd,   ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x55 */ {&daPy_lk_c::procCutTurn,               ModeFlg_00000400},
    /* 0x56 */ {&daPy_lk_c::procCutRoll,               ModeFlg_00000400},
    /* 0x57 */ {&daPy_lk_c::procCutRollEnd,            ModeFlg_00000001 | ModeFlg_00000100},
    /* 0x58 */ {&daPy_lk_c::procCutTurnCharge,         ModeFlg_00000400},
    /* 0x59 */ {&daPy_lk_c::procCutTurnMove,           ModeFlg_00000080},
    /* 0x5A */ {&daPy_lk_c::procCutReverse,            ModeFlg_00000400},
    /* 0x5B */ {&daPy_lk_c::procJumpCut,               ModeFlg_MIDAIR | ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x5C */ {&daPy_lk_c::procJumpCutLand,           ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x5D */ {&daPy_lk_c::procBtJump,                ModeFlg_MIDAIR | ModeFlg_00000400 | ModeFlg_08000000 | ModeFlg_BT},
    /* 0x5E */ {&daPy_lk_c::procBtJumpCut,             ModeFlg_MIDAIR | ModeFlg_00000400 | ModeFlg_BT},
    /* 0x5F */ {&daPy_lk_c::procBtSlide,               ModeFlg_BT},
    /* 0x60 */ {&daPy_lk_c::procBtRoll,                ModeFlg_00000400 | ModeFlg_00008000 | ModeFlg_BT},
    /* 0x61 */ {&daPy_lk_c::procBtRollCut,             ModeFlg_MIDAIR | ModeFlg_00000400 | ModeFlg_08000000 | ModeFlg_BT},
    /* 0x62 */ {&daPy_lk_c::procBtVerticalJump,        ModeFlg_MIDAIR | ModeFlg_00000400 | ModeFlg_08000000 | ModeFlg_BT},
    /* 0x63 */ {&daPy_lk_c::procBtVerticalJumpCut,     ModeFlg_MIDAIR | ModeFlg_00000400 | ModeFlg_08000000 | ModeFlg_BT},
    /* 0x64 */ {&daPy_lk_c::procBtVerticalJumpLand,    ModeFlg_00000400},
    /* 0x65 */ {&daPy_lk_c::procGuardCrash,            0},
    /* 0x66 */ {&daPy_lk_c::procDamage,                ModeFlg_DAMAGE | ModeFlg_00000080 | ModeFlg_00000400},
    /* 0x67 */ {&daPy_lk_c::procPolyDamage,            ModeFlg_DAMAGE | ModeFlg_00000400},
    /* 0x68 */ {&daPy_lk_c::procLargeDamage,           ModeFlg_MIDAIR | ModeFlg_DAMAGE},
    /* 0x69 */ {&daPy_lk_c::procLargeDamageUp,         ModeFlg_DAMAGE | ModeFlg_00000400 | ModeFlg_00008000 | ModeFlg_02000000 | ModeFlg_08000000},
    /* 0x6A */ {&daPy_lk_c::procLargeDamageWall,       ModeFlg_MIDAIR | ModeFlg_DAMAGE | ModeFlg_00000400},
    /* 0x6B */ {&daPy_lk_c::procLavaDamage,            ModeFlg_MIDAIR | ModeFlg_DAMAGE},
    /* 0x6C */ {&daPy_lk_c::procElecDamage,            ModeFlg_00000001 | ModeFlg_DAMAGE | ModeFlg_00008000},
    /* 0x6D */ {&daPy_lk_c::procGuardSlip,             ModeFlg_00000080 | ModeFlg_00000400 | ModeFlg_00001000},
    /* 0x6E */ {&daPy_lk_c::procGrabReady,             ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_GRAB},
    /* 0x6F */ {&daPy_lk_c::procGrabUp,                ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_GRAB},
    /* 0x70 */ {&daPy_lk_c::procGrabMiss,              ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_GRAB},
    /* 0x71 */ {&daPy_lk_c::procGrabThrow,             ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_GRAB},
    /* 0x72 */ {&daPy_lk_c::procGrabPut,               ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_GRAB},
    /* 0x73 */ {&daPy_lk_c::procGrabWait,              ModeFlg_00000001 | ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_00004000 | ModeFlg_GRAB},
    /* 0x74 */ {&daPy_lk_c::procGrabHeavyWait,         ModeFlg_00000001 | ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_GRAB},
    /* 0x75 */ {&daPy_lk_c::procGrabRebound,           ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_GRAB},
    /* 0x76 */ {&daPy_lk_c::procRopeSubject,           ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_00001000 | ModeFlg_SUBJECT},
    /* 0x77 */ {&daPy_lk_c::procRopeReady,             ModeFlg_ROPE | ModeFlg_04000000},
    /* 0x78 */ {&daPy_lk_c::procRopeSwing,             ModeFlg_00000400 | ModeFlg_ROPE | ModeFlg_04000000},
    /* 0x79 */ {&daPy_lk_c::procRopeHangWait,          ModeFlg_00000001 | ModeFlg_00000100 | ModeFlg_ROPE | ModeFlg_04000000},
    /* 0x7A */ {&daPy_lk_c::procRopeUp,                ModeFlg_ROPE | ModeFlg_04000000},
    /* 0x7B */ {&daPy_lk_c::procRopeDown,              ModeFlg_ROPE | ModeFlg_04000000},
    /* 0x7C */ {&daPy_lk_c::procRopeSwingStart,        ModeFlg_00000400 | ModeFlg_ROPE | ModeFlg_04000000},
    /* 0x7D */ {&daPy_lk_c::procRopeMove,              ModeFlg_00000004 | ModeFlg_00000100 | ModeFlg_00001000 | ModeFlg_SUBJECT},
    /* 0x7E */ {&daPy_lk_c::procRopeThrowCatch,        ModeFlg_00000001 | ModeFlg_00000400},
    /* 0x7F */ {&daPy_lk_c::procRopeUpHang,            ModeFlg_ROPE | ModeFlg_04000000},
    /* 0x80 */ {&daPy_lk_c::procBoomerangSubject,      ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_00000100 | ModeFlg_00001000 | ModeFlg_00020000 | ModeFlg_SUBJECT},
    /* 0x81 */ {&daPy_lk_c::procBoomerangMove,         ModeFlg_00000004 | ModeFlg_00000100 | ModeFlg_00001000 | ModeFlg_00020000 | ModeFlg_SUBJECT},
    /* 0x82 */ {&daPy_lk_c::procBoomerangCatch,        ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_00001000},
    /* 0x83 */ {&daPy_lk_c::procHookshotSubject,       ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_00000100 | ModeFlg_HOOKSHOT | ModeFlg_00001000 | ModeFlg_SUBJECT},
    /* 0x84 */ {&daPy_lk_c::procHookshotMove,          ModeFlg_00000004 | ModeFlg_00000100 | ModeFlg_HOOKSHOT | ModeFlg_00001000 | ModeFlg_SUBJECT},
    /* 0x85 */ {&daPy_lk_c::procHookshotFly,           ModeFlg_MIDAIR | ModeFlg_HOOKSHOT},
    /* 0x86 */ {&daPy_lk_c::procShipReady,             ModeFlg_HANG | ModeFlg_00000400 | ModeFlg_IN_SHIP},
    /* 0x87 */ {&daPy_lk_c::procShipJumpRide,          ModeFlg_00000400 | ModeFlg_IN_SHIP},
    /* 0x88 */ {&daPy_lk_c::procShipSteer,             ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_IN_SHIP | ModeFlg_40000000},
    /* 0x89 */ {&daPy_lk_c::procShipPaddle,            ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_IN_SHIP | ModeFlg_40000000},
    /* 0x8A */ {&daPy_lk_c::procShipScope,             ModeFlg_00000100 | ModeFlg_IN_SHIP | ModeFlg_40000000},
    /* 0x8B */ {&daPy_lk_c::procShipBoomerang,         ModeFlg_00000100 | ModeFlg_IN_SHIP | ModeFlg_00020000 | ModeFlg_SUBJECT | ModeFlg_40000000},
    /* 0x8C */ {&daPy_lk_c::procShipHookshot,          ModeFlg_00000100 | ModeFlg_IN_SHIP | ModeFlg_SUBJECT | ModeFlg_40000000},
    /* 0x8D */ {&daPy_lk_c::procShipBow,               ModeFlg_00000100 | ModeFlg_IN_SHIP | ModeFlg_SUBJECT | ModeFlg_40000000},
    /* 0x8E */ {&daPy_lk_c::procShipCannon,            ModeFlg_00000100 | ModeFlg_IN_SHIP | ModeFlg_40000000},
    /* 0x8F */ {&daPy_lk_c::procShipCrane,             ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_IN_SHIP | ModeFlg_08000000},
    /* 0x90 */ {&daPy_lk_c::procShipGetOff,            ModeFlg_IN_SHIP},
    /* 0x91 */ {&daPy_lk_c::procShipRestart,           ModeFlg_00000400 | ModeFlg_IN_SHIP},
    /* 0x92 */ {&daPy_lk_c::procFanSwing,              ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x93 */ {&daPy_lk_c::procFanGlide,              ModeFlg_MIDAIR | ModeFlg_00000080 | ModeFlg_00000400},
    /* 0x94 */ {&daPy_lk_c::procBowSubject,            ModeFlg_00000001 | ModeFlg_00000004 | ModeFlg_00000100 | ModeFlg_00001000 | ModeFlg_SUBJECT},
    /* 0x95 */ {&daPy_lk_c::procBowMove,               ModeFlg_00000004 | ModeFlg_00000100 | ModeFlg_00001000 | ModeFlg_SUBJECT},
    /* 0x96 */ {&daPy_lk_c::procVomitReady,            ModeFlg_MIDAIR | ModeFlg_00000400},
    /* 0x97 */ {&daPy_lk_c::procVomitWait,             ModeFlg_00000001 | ModeFlg_00008000 | ModeFlg_04000000},
    /* 0x98 */ {&daPy_lk_c::procVomitJump,             ModeFlg_MIDAIR},
    /* 0x99 */ {&daPy_lk_c::procVomitLand,             ModeFlg_00000001 | ModeFlg_00000400},
    /* 0x9A */ {&daPy_lk_c::procTactWait,              ModeFlg_00000001 | ModeFlg_00000100 | ModeFlg_08000000},
    /* 0x9B */ {&daPy_lk_c::procTactPlay,              ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_08000000},
    /* 0x9C */ {&daPy_lk_c::procTactPlayEnd,           ModeFlg_00000001 | ModeFlg_00000100},
    /* 0x9D */ {&daPy_lk_c::procTactPlayOriginal,      ModeFlg_00000001},
    /* 0x9E */ {&daPy_lk_c::procIceSlipFall,           ModeFlg_MIDAIR},
    /* 0x9F */ {&daPy_lk_c::procIceSlipFallUp,         ModeFlg_00000400 | ModeFlg_00008000 | ModeFlg_02000000 | ModeFlg_08000000},
    /* 0xA0 */ {&daPy_lk_c::procIceSlipAlmostFall,     ModeFlg_00000001},
    /* 0xA1 */ {&daPy_lk_c::procBootsEquip,            ModeFlg_00000001 | ModeFlg_MIDAIR | ModeFlg_00000400 | ModeFlg_00004000 | ModeFlg_08000000},
    /* 0xA2 */ {&daPy_lk_c::procNotUse,                ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xA3 */ {&daPy_lk_c::procBottleDrink,           ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xA4 */ {&daPy_lk_c::procBottleOpen,            ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xA5 */ {&daPy_lk_c::procBottleSwing,           ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xA6 */ {&daPy_lk_c::procBottleGet,             ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xA7 */ {&daPy_lk_c::procFoodThrow,             ModeFlg_00000001 | ModeFlg_00000100},
    /* 0xA8 */ {&daPy_lk_c::procFoodSet,               ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xA9 */ {&daPy_lk_c::dProcTool,                 ModeFlg_00008000},
    /* 0xAA */ {&daPy_lk_c::dProcTalk,                 ModeFlg_00000001 | ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_00080000},
    /* 0xAB */ {&daPy_lk_c::dProcDamage,               ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xAC */ {&daPy_lk_c::dProcHoldup,               ModeFlg_00000001 | ModeFlg_00004000},
    /* 0xAD */ {&daPy_lk_c::dProcOpenTreasure,         ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_00008000},
    /* 0xAE */ {&daPy_lk_c::dProcGetItem,              ModeFlg_00000001 | ModeFlg_00008000},
    /* 0xAF */ {&daPy_lk_c::dProcUnequip,              ModeFlg_00000001 | ModeFlg_00000100},
    /* 0xB0 */ {&daPy_lk_c::dProcLavaDamage,           ModeFlg_MIDAIR | ModeFlg_DAMAGE},
    /* 0xB1 */ {&daPy_lk_c::dProcFreezeDamage,         ModeFlg_MIDAIR | ModeFlg_DAMAGE | ModeFlg_00004000},
    /* 0xB2 */ {&daPy_lk_c::dProcDead,                 ModeFlg_00000001 | ModeFlg_DAMAGE | ModeFlg_00000400 | ModeFlg_00008000},
    /* 0xB3 */ {&daPy_lk_c::dProcLookAround,           ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xB4 */ {&daPy_lk_c::dProcSalute,               ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xB5 */ {&daPy_lk_c::dProcLookAround2,          ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_00080000},
    /* 0xB6 */ {&daPy_lk_c::dProcTalismanPickup,       ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_00080000},
    /* 0xB7 */ {&daPy_lk_c::dProcTalismanWait,         ModeFlg_00000001 | ModeFlg_00000100 | ModeFlg_00080000},
    /* 0xB8 */ {&daPy_lk_c::dProcSurprised,            ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xB9 */ {&daPy_lk_c::dProcTurnBack,             ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_00004000},
    /* 0xBA */ {&daPy_lk_c::dProcLookUp,               ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xBB */ {&daPy_lk_c::dProcQuakeWait,            ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xBC */ {&daPy_lk_c::dProcDance,                ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xBD */ {&daPy_lk_c::dProcCaught,               ModeFlg_CAUGHT},
    /* 0xBE */ {&daPy_lk_c::dProcLookWait,             ModeFlg_00000001 | ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_00001000},
    /* 0xBF */ {&daPy_lk_c::dProcPushPullWait,         ModeFlg_00000001 | ModeFlg_00000100 | ModeFlg_PUSHPULL},
    /* 0xC0 */ {&daPy_lk_c::dProcPushMove,             ModeFlg_PUSHPULL},
    /* 0xC1 */ {&daPy_lk_c::dProcDoorOpen,             ModeFlg_00000400},
    /* 0xC2 */ {&daPy_lk_c::dProcNod,                  ModeFlg_00000001 | ModeFlg_00000080 | ModeFlg_00000400 | ModeFlg_00080000},
    /* 0xC3 */ {&daPy_lk_c::dProcPresent,              ModeFlg_00000001 | ModeFlg_00080000},
    /* 0xC4 */ {&daPy_lk_c::dProcWindChange,           ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xC5 */ {&daPy_lk_c::dProcStandItemPut,         ModeFlg_00000001},
    /* 0xC6 */ {&daPy_lk_c::dProcVorcanoFail,          ModeFlg_MIDAIR},
    /* 0xC7 */ {&daPy_lk_c::dProcSlightSurprised,      ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xC8 */ {&daPy_lk_c::dProcSmile,                ModeFlg_00000001},
    /* 0xC9 */ {&daPy_lk_c::dProcBossWarp,             ModeFlg_MIDAIR | ModeFlg_00000400},
    /* 0xCA */ {&daPy_lk_c::dProcAgbUse,               ModeFlg_00000001 | ModeFlg_00000100},
    /* 0xCB */ {&daPy_lk_c::dProcLookTurn,             ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xCC */ {&daPy_lk_c::dProcLetterOpen,           ModeFlg_00000001 | ModeFlg_00000100},
    /* 0xCD */ {&daPy_lk_c::dProcLetterRead,           ModeFlg_00000001 | ModeFlg_00000100},
    /* 0xCE */ {&daPy_lk_c::dProcRedeadStop,           ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_08000000},
    /* 0xCF */ {&daPy_lk_c::dProcRedeadCatch,          ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xD0 */ {&daPy_lk_c::dProcGetDance,             ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_00008000},
    /* 0xD1 */ {&daPy_lk_c::dProcBottleOpenFairy,      ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xD2 */ {&daPy_lk_c::dProcWarpShort,            ModeFlg_MIDAIR | ModeFlg_00000100},
    /* 0xD3 */ {&daPy_lk_c::dProcOpenSalvageTreasure,  ModeFlg_00000001 | ModeFlg_00000400},
    /* 0xD4 */ {&daPy_lk_c::dProcSurprisedWait,        ModeFlg_00000001},
    /* 0xD5 */ {&daPy_lk_c::dProcPowerUpWait_init,     ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_00008000},
    /* 0xD6 */ {&daPy_lk_c::dProcPowerUp,              ModeFlg_00000001 | ModeFlg_00000400 | ModeFlg_00008000},
    /* 0xD7 */ {&daPy_lk_c::dProcShipSit,              ModeFlg_00000001 | ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_IN_SHIP | ModeFlg_00080000},
    /* 0xD8 */ {&daPy_lk_c::dProcLastCombo,            ModeFlg_00000001 | ModeFlg_00008000},
    /* 0xD9 */ {&daPy_lk_c::dProcHandUp,               ModeFlg_00000001 | ModeFlg_00000080 | ModeFlg_00000100 | ModeFlg_00080000},
    /* 0xDA */ {&daPy_lk_c::dProcIceSlip,              ModeFlg_00000001 | ModeFlg_00000400},
};

daPy_lk_c::ProcFunc daPy_lk_c::mDemoProcInitFuncTable[] = {
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

GXColor l_freeze_fade_color = {0xFF, 0xFF, 0xFF, 0xFF};

cXyz l_debug_keep_pos;
csXyz l_debug_current_angle;
csXyz l_debug_shape_angle;

u8 daPy_matAnm_c::m_maba_flg;
u8 daPy_matAnm_c::m_eye_move_flg;
u8 daPy_matAnm_c::m_maba_timer;
u8 daPy_matAnm_c::m_morf_frame;

s16 daPy_dmEcallBack_c::m_timer = 0;
u16 daPy_dmEcallBack_c::m_type = 3;

u8 right_dir_4883[0xC];
u8 texObj_5157[0x20];

daPy_waterDropPcallBack_c daPy_waterDropEcallBack_c::m_pcallback;

u8 normal_ripple_scale_5638[0xC];
u8 small_ripple_scale_5641[0xC];
u8 waterfall_splash_trans_5699[0xC];
u8 run_splash_scale_6040[0xC];
u8 run_grass_scale_6043[0xC];
u8 heavy_emit_smoke_scale_6046[0xC];
u8 heavy_dyn_smoke_scale_6049[0xC];
u8 heavy_pat_smoke_scale_6052[0xC];
u8 tail_scale_6508[0xC];
u8 arm_flame_scale_6651[0xC];
u8 _6785[0xC];
u8 eff_scale0_6784[0xC];
u8 _6789[0xC];
u8 eff_scale2_6788[0xC];
u8 direction_6792[0xC];
u8 splash_scale_14445[0xC];
u8 ripple_scale_14448[0xC];
u8 _15293[0xC];
u8 arm_pos_15292[0xC];
u8 _15297[0xC];
u8 armA_offset_15296[0xC];
u8 dynamic_scale_16750[0xC];
u8 particle_scale_16753[0xC];
u8 _17480[0xC];
u8 local_height_offset_17479[0xC];
u8 eff_scale_18886[0xC];
u8 eff_dscale_18889[0xC];
u8 eff_pscale_18892[0xC];
u8 smoke_kusa_particle_scale_21005[0xC];
u8 emitter_scale_21008[0xC];
u8 emitter_trans_21011[0xC];
u8 d_scale_23162[0xC];
u8 p_scale_23165[0xC];
u8 emitter_trans_24824[0xC];
u8 particle_scale_24827[0xC];
u8 root_mtx_25647[0x30];

static mDoExt_offCupOnAupPacket l_offCupOnAupPacket1;
static mDoExt_offCupOnAupPacket l_offCupOnAupPacket2;
static mDoExt_onCupOffAupPacket l_onCupOffAupPacket1;
static mDoExt_onCupOffAupPacket l_onCupOffAupPacket2;

static void dummydatafunc(f32* temp, f64* temp2) {
    // temporary hack to improve diffs until sdata2 offsets are figured out
    *temp = 2.0f;
    *temp = -1000000000.0f;
    *temp = -1.0f;
    *temp = 0.0f;
    *temp = 0.08f;
    *temp = 1.0f;
    *temp = 12.0f;
    *temp = 13.0f;
    *temp = 150.0f;
    *temp = 30.0f;
    *temp = 0.65f;
    *temp = 0.35f;
    *temp = 32768.0f;
    *temp = 16384.0f;
    *temp = 10.0f;
    *temp2 = 4503601774854144.0;
    *temp2 = 4503599627370496.0;
    *temp = 25.0f;
    *temp = -0.05f;
    *temp2 = 0.5;
    *temp2 = 3.0;
    *temp = 0.6f;
    *temp = 0.01f;
    *temp = 0.001f;
    *temp = 15.0f;
    *temp = 1.5f;
    *temp = 3.1415927f;
    *temp = 0.5f;
    *temp = 0.3f;
    *temp = 1.2f;
    *temp = 0.4f;
    *temp = 5.0f;
    *temp = 0.1f;
    *temp = 0.8f;
    *temp = 60.0f;
    *temp = 4.0f;
    *temp = 0.25f;
    *temp = 0.75f;
    *temp = 16.0f;
    *temp = 8.0f;
    *temp = 18.0f;
    *temp = 3.0f;
    *temp = 0.2f;
    *temp = 0.05f;
    *temp = 45.0f;
    *temp = 11.0f;
    *temp = 17.5f;
    *temp = 1000000000.0f;
	OSReport("Adanmae");
	OSReport("d_a_player_dproc.inc");
	OSReport("0");
	OSReport("Halt");
	OSReport("Link");
	OSReport("DEFAULT_GETITEM");
	OSReport("GanonK");
	OSReport("GTower");
	OSReport("d_a_player_bow.inc");
	OSReport("d_a_player_hook.inc");
	OSReport("d_a_player_fan.inc");
	OSReport("d_a_player_hammer.inc");
	OSReport("Type");
	OSReport("Omori");
	OSReport("d_a_player_sword.inc");
	OSReport("M_DaiB");
	OSReport("Xboss2");
	OSReport("M_DragB");
	OSReport("Xboss0");
	OSReport("fall");
	OSReport("d_a_player_main.cpp");
	OSReport("(demo_mode < daPy_demo_c::DEMO_LAST_e) || (demo_mode == daPy_demo_c::DEMO_NEW_ANM0_e)");
	OSReport("Ojhous");
	OSReport("Orichh");
	OSReport("kinBOSS");
	OSReport("Xboss1");
	OSReport("ICE_FAILED");
	OSReport("pos");
	OSReport("angle");
	OSReport("prm0");
	OSReport("prm1");
	OSReport("stick");
	OSReport("face");
	OSReport("GanonM");
	OSReport("sea");
	OSReport("m_tex_anm_heap.m_buffer != 0");
	OSReport("m_texNoAnms != 0");
	OSReport("mat_anm != 0");
	OSReport("m_tex_scroll_heap.m_buffer != 0");
	OSReport("material_num == 2");
	OSReport("m_texMtxAnm != 0");
	OSReport("m_tex_eye_scroll[no] != 0");
	OSReport("tmtx != 0");
	OSReport("mtl->getMaterialAnm() != 0");
	OSReport("tmp_modelData != 0");
	OSReport("aura_p->getModel() != 0");
	OSReport("m_old_fdata != 0");
	OSReport("m_pbCalc[PART_UNDER_e] != 0");
	OSReport("m_pbCalc[PART_UPPER_e] != 0");
	OSReport("m_HIO != 0");
	OSReport("m_anm_heap_under[UNDER_MOVE0_e].m_buffer != 0");
	OSReport("m_sanm_buffer != 0");
	OSReport("m_item_bck_buffer != 0");
	OSReport("tmp_trans_bas != 0");
	OSReport("tmp_trans != 0");
	OSReport("tmp_tp != 0");
	OSReport("tmp_tk != 0");
	OSReport("*i_model != 0");
	OSReport("btk_anm != 0");
	OSReport("brk_anm != 0");
	OSReport("zoff_blend_cnt <= 4");
	OSReport("zoff_none_cnt <= 4");
	OSReport("zon_cnt <= 4");
	OSReport("zon_cnt == 4");
	OSReport("zoff_none_cnt == 4");
	OSReport("zoff_blend_cnt == 4");
	OSReport("dummy_data != 0");
	OSReport("Always");
	OSReport("tmp_tex != 0");
	OSReport("tmp_img != 0");
	OSReport("texture != 0");
	OSReport("textureName != 0");
	OSReport("linktexS3TC");
	OSReport("Pjavdou");
	OSReport("ShipD");
	OSReport("Siren");
	OSReport("data_size < l_sanm_buffer_size");
}

/* 80102E8C-80102EAC       .text daPy_createHeap__FP10fopAc_ac_c */
static BOOL daPy_createHeap(fopAc_ac_c* i_this) {
    return static_cast<daPy_lk_c*>(i_this)->createHeap();
}

/* 80102EAC-80102F1C       .text __ct__13daPy_matAnm_cFv */
daPy_matAnm_c::daPy_matAnm_c() {
    mEyePosOld.x = 0.0f;
    mEyePosOld.y = 0.0f;
    mEyePos.x = 0.0f;
    mEyePos.y = 0.0f;
    
    m_maba_flg = 0;
    m_eye_move_flg = 0;
    m_maba_timer = 0;
    m_morf_frame = 0;
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
BOOL daPy_lk_c::itemButton() const {
    if (mLastUsedItemButtonIdx == 0) {
        return m34C9 & 0x04;
    } else if (mLastUsedItemButtonIdx == 1) {
        return m34C9 & 0x08;
    } else {
        return m34C9 & 0x10;
    }
}

/* 801031DC-80103214       .text itemTrigger__9daPy_lk_cCFv */
BOOL daPy_lk_c::itemTrigger() const {
    if (mLastUsedItemButtonIdx == 0) {
        return mPressedButtonsBitfield & 0x04;
    } else if (mLastUsedItemButtonIdx == 1) {
        return mPressedButtonsBitfield & 0x08;
    } else {
        return mPressedButtonsBitfield & 0x10;
    }
}

/* 80103214-80103258       .text getReadyItem__9daPy_lk_cFv */
u8 daPy_lk_c::getReadyItem() {
    if (mLastUsedItemButtonIdx == 0) {
        return dComIfGp_getSelectItem(0);
    } else if (mLastUsedItemButtonIdx == 1) {
        return dComIfGp_getSelectItem(1);
    } else {
        return dComIfGp_getSelectItem(2);
    }
}

/* 80103258-801032E4       .text checkGroupItem__9daPy_lk_cFii */
BOOL daPy_lk_c::checkGroupItem(int param_1, int itemNo) {
    if (param_1 == 0x105) {
        return checkDrinkBottleItem(itemNo);
    } else if (param_1 == 0x106) {
        return checkOpenBottleItem(itemNo);
    } else if (param_1 == 0x107) {
        return isEsa(itemNo);
    } else if (param_1 == 0x108) {
        return checkBowItem(itemNo);
    } else if (param_1 == 0x109) {
        return checkPhotoBoxItem(itemNo);
    } else {
        return param_1 == itemNo;
    }
}

/* 801032E4-801033E4       .text checkSetItemTrigger__9daPy_lk_cFii */
BOOL daPy_lk_c::checkSetItemTrigger(int param_1, int param_2) {
    if (param_2 == 0 || !daPy_dmEcallBack_c::checkCurse()) {
        if (mPressedButtonsBitfield & 0x04 && checkGroupItem(param_1, dComIfGp_getSelectItem(0))) {
            mLastUsedItemButtonIdx = 0;
            return TRUE;
        }
        if (mPressedButtonsBitfield & 0x08 && checkGroupItem(param_1, dComIfGp_getSelectItem(1))) {
            mLastUsedItemButtonIdx = 1;
            return TRUE;
        }
        if (mPressedButtonsBitfield & 0x10 && checkGroupItem(param_1, dComIfGp_getSelectItem(2))) {
            mLastUsedItemButtonIdx = 2;
            return TRUE;
        }
    }
    return FALSE;
}

/* 801033E4-80103450       .text auraJointCB0__9daPy_lk_cFi */
BOOL daPy_lk_c::auraJointCB0(int jntNo) {
    mpYmgcs00Model->setAnmMtx(jntNo, mpCLModel->getAnmMtx(jntNo));
    mDoMtx_copy(mpCLModel->getAnmMtx(jntNo), j3dSys.mCurrentMtx);
    return TRUE;
}

/* 80103450-80103494       .text daPy_auraCallback__FP7J3DNodei */
static BOOL daPy_auraCallback(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        i_this->auraJointCB0(jntNo);
    }
    return TRUE;
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
BOOL daPy_lk_c::jointCB0(int) {
    /* Nonmatching */
}

/* 80103EE4-80103F28       .text daPy_jointCallback0__FP7J3DNodei */
static BOOL daPy_jointCallback0(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        i_this->jointCB0(jntNo);
    }
    return TRUE;
}

/* 80103F28-80104178       .text jointCB1__9daPy_lk_cFv */
BOOL daPy_lk_c::jointCB1() {
    /* Nonmatching */
}

/* 80104178-801041B4       .text daPy_jointCallback1__FP7J3DNodei */
static BOOL daPy_jointCallback1(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        i_this->jointCB1();
    }
    return TRUE;
}

/* 801041B4-801041EC       .text setAnimeHeap__9daPy_lk_cFP12JKRSolidHeap */
JKRHeap* daPy_lk_c::setAnimeHeap(JKRSolidHeap* animeHeap) {
    animeHeap->freeAll();
    return mDoExt_setCurrentHeap(animeHeap);
}

/* 801041EC-80104240       .text setItemHeap__9daPy_lk_cFv */
JKRHeap* daPy_lk_c::setItemHeap() {
    if (!checkResetFlg0(daPyRFlg0_UNK4000)) {
        mCurrItemHeapIdx ^= 1;
        onResetFlg0(daPyRFlg0_UNK4000);
    }
    return setAnimeHeap(mpItemHeaps[mCurrItemHeapIdx]);
}

/* 80104240-80104280       .text setBlurPosResource__9daPy_lk_cFUs */
void daPy_lk_c::setBlurPosResource(u16 index) {
    dComIfGp_getAnmArchive()->readIdxResource(mSwBlur.mpBlurPos, 0x4800, index);
}

/* 80104280-80104364       .text getItemAnimeResource__9daPy_lk_cFUs */
J3DAnmTransform* daPy_lk_c::getItemAnimeResource(u16 index) {
    dComIfGp_getAnmArchive()->readIdxResource(m_item_bck_buffer, 0x1000, index);
    JKRHeap* oldHeap = setAnimeHeap(m2ECC);
    mDoExt_transAnmBas* bas = new mDoExt_transAnmBas(NULL);
    J3DAnmLoaderDataBase::setResource(bas, m_item_bck_buffer);
    mDoExt_setCurrentHeap(oldHeap);
    return bas;
}

/* 80104364-801043F0       .text getAnimeResource__9daPy_lk_cFP14daPy_anmHeap_cUsUl */
J3DAnmTransform* daPy_lk_c::getAnimeResource(daPy_anmHeap_c* anmHeap, u16 index, u32 bufferSize) {
    J3DAnmTransform* bck;
    dComIfGp_getAnmArchive()->readIdxResource(anmHeap->m_buffer, bufferSize, index);
    JKRHeap* oldHeap = setAnimeHeap(anmHeap->mpAnimeHeap);
    bck = static_cast<J3DAnmTransform*>(J3DAnmLoaderDataBase::load(anmHeap->m_buffer));
    mDoExt_setCurrentHeap(oldHeap);
    anmHeap->mIdx = index;
    anmHeap->field_0x2 = -1;
    return bck;
}

/* 801043F0-801044E8       .text getUnderUpperAnime__9daPy_lk_cFPC15daPy_anmIndex_cPP15J3DAnmTransformPP15J3DAnmTransformiUl */
void daPy_lk_c::getUnderUpperAnime(const daPy_anmIndex_c* anmIndex, J3DAnmTransform** pUnderBck, J3DAnmTransform** pUpperBck, int r7, u32 bufferSize) {
    if (m_anm_heap_under[r7].mIdx != anmIndex->mUnderBckIdx) {
        *pUnderBck = getAnimeResource(&m_anm_heap_under[r7], anmIndex->mUnderBckIdx, bufferSize);
    } else {
        *pUnderBck = mAnmRatioUnder[r7].getAnmTransform();
    }
    if (anmIndex->mUnderBckIdx != anmIndex->mUpperBckIdx) {
        if (bufferSize == 0xB400) {
            bufferSize = 0x4800;
        }
        if (m_anm_heap_upper[r7].mIdx != anmIndex->mUpperBckIdx) {
            *pUpperBck = getAnimeResource(&m_anm_heap_upper[r7], anmIndex->mUpperBckIdx, bufferSize);
        } else {
            *pUpperBck = mAnmRatioUpper[r7].getAnmTransform();
        }
    } else {
        *pUpperBck = NULL;
        m_anm_heap_upper[r7].mIdx = -1;
    }
}

/* 801044E8-80104564       .text setTextureAnimeResource__9daPy_lk_cFP16J3DAnmTexPatterni */
void daPy_lk_c::setTextureAnimeResource(J3DAnmTexPattern* btp, int r31) {
    btp->searchUpdateMaterialID(mpCLModelData);
    m035C = btp;
    m3530 = r31;
    u16 material_num = btp->getUpdateMaterialNum();
    for (u16 i = 0; i < material_num; i++) {
        m_texNoAnms[i].setAnmTexPattern(btp);
    }
}

/* 80104564-80104600       .text loadTextureAnimeResource__9daPy_lk_cFUli */
J3DAnmTexPattern* daPy_lk_c::loadTextureAnimeResource(u32 index, BOOL isDemo) {
    J3DAnmTexPattern* btp;
    if (isDemo) {
        dComIfGp_getLkDemoAnmArchive()->readResource(m_tex_anm_heap.m_buffer, 0x1000, index);
    } else {
        dComIfGp_getAnmArchive()->readIdxResource(m_tex_anm_heap.m_buffer, 0x1000, index);
    }
    JKRHeap* oldHeap = setAnimeHeap(m_tex_anm_heap.mpAnimeHeap);
    btp = static_cast<J3DAnmTexPattern*>(J3DAnmLoaderDataBase::load(m_tex_anm_heap.m_buffer));
    mDoExt_setCurrentHeap(oldHeap);
    return btp;
}

/* 80104600-801046CC       .text checkBossBgm__9daPy_lk_cFv */
BOOL daPy_lk_c::checkBossBgm() {
    u32 mainBgm = mDoAud_checkPlayingMainBgmFlag();
    u32 subBgm = mDoAud_checkPlayingSubBgmFlag();
    if (mainBgm == JA_BGM_GOMA || mainBgm == JA_BGM_GOMA_2 || mainBgm == JA_BGM_KINDAN_BOSS ||
        mainBgm == JA_BGM_DK_BATTLE || mainBgm == JA_BGM_MJ_TOWER_BATTLE || mainBgm == JA_BGM_BST_BATTLE ||
        mainBgm == JA_BGM_RANE_BATTLE || mainBgm == JA_BGM_PAST_GOMA_2 || mainBgm == JA_BGM_BIG_POW ||
        mainBgm == JA_BGM_PAST_BIG_POW || mainBgm == JA_BGM_PAST_BKM || mainBgm == JA_BGM_PAST_GOMA ||
        mainBgm == JA_BGM_PAST_RANE || mainBgm == JA_BGM_GANON_BATTLE || mainBgm == JA_BGM_BGN_KUGUTSU ||
        mainBgm == JA_BGM_BGN_TARABA || mainBgm == JA_BGM_BGN_HAYAMUSHI || subBgm == JA_BGM_MBOSS ||
        subBgm == JA_BGM_MBOSS_S || subBgm == JA_BGM_P_GANON_1 || subBgm == JA_BGM_P_GANON_2 ||
        subBgm == JA_BGM_DIOCTA_BATTLE || subBgm == JA_BGM_DIOCTA_2)
    {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 801046CC-801046EC       .text checkMabaAnimeBtp__9daPy_lk_cFi */
BOOL daPy_lk_c::checkMabaAnimeBtp(int anmIdx) {
    if (anmIdx >= LKANM_BTP_TMABAA && anmIdx <= LKANM_BTP_TMABAJ) {
        return TRUE;
    }
    return FALSE;
}

/* 801046EC-80104A08       .text checkNormalFace__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNormalFace() {
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
BOOL daPy_lk_c::checkSightLine(f32, cXyz*) {
    /* Nonmatching */
}

/* 80105814-80105910       .text setBootsModel__9daPy_lk_cFPP8J3DModel */
void daPy_lk_c::setBootsModel(J3DModel** pBootModels) {
    u16 temp;
    if (checkEquipHeavyBoots()) {
        // TODO: add enum for link's joint numbers
        pBootModels[0]->setAnmMtx(0x01, mpCLModel->getAnmMtx(0x26));
        pBootModels[1]->setAnmMtx(0x01, mpCLModel->getAnmMtx(0x21));
        temp = 2;
    } else {
        temp = 1;
    }
    
    J3DModel* bootModel = pBootModels[0];
    bootModel->setAnmMtx(temp, mpCLModel->getAnmMtx(0x28));
    bootModel->setAnmMtx(temp+1, mpCLModel->getAnmMtx(0x27));
    
    bootModel = pBootModels[1];
    bootModel->setAnmMtx(temp, mpCLModel->getAnmMtx(0x23));
    bootModel->setAnmMtx(temp+1, mpCLModel->getAnmMtx(0x22));
}

/* 80105910-80106660       .text setItemModel__9daPy_lk_cFv */
void daPy_lk_c::setItemModel() {
    /* Nonmatching */
}

/* 80106660-801066DC       .text checkUpperReadyAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkUpperReadyAnime() const {
    /* Nonmatching */
}

/* 801066DC-80106750       .text checkUpperReadyThrowAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkUpperReadyThrowAnime() const {
    /* Nonmatching */
}

/* 80106750-801067D8       .text checkNoCollisionCorret__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNoCollisionCorret() {
    /* Nonmatching */
}

/* 801067D8-80106BD0       .text setDrawHandModel__9daPy_lk_cFv */
void daPy_lk_c::setDrawHandModel() {
    /* Nonmatching */
}

/* 80106BD0-80106C40       .text entryDLSetLight__9daPy_lk_cFP8J3DModelUl */
void daPy_lk_c::entryDLSetLight(J3DModel* model, u32 param_2) {
    g_env_light.setLightTevColorType(model, &mTevStr);
    if (param_2 != 0) {
        dMat_control_c::iceEntryDL(model, -1, NULL);
    } else {
        mDoExt_modelEntryDL(model);
    }
}

/* 80106C40-80106CB0       .text updateDLSetLight__9daPy_lk_cFP8J3DModelUl */
void daPy_lk_c::updateDLSetLight(J3DModel* model, u32 param_2) {
    g_env_light.setLightTevColorType(model, &mTevStr);
    if (param_2 != 0) {
        dMat_control_c::iceUpdateDL(model, -1, NULL);
    } else {
        mDoExt_modelUpdateDL(model);
    }
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
    /* Nonmatching - regalloc */
    if (mSightPacket.getDrawFlg()) {
        mSightPacket.setSight();
    }
    g_env_light.settingTevStruct(TEV_TYPE_PLAYER, &current.pos, &mTevStr);
    if (checkPlayerNoDraw()) {
        offBodyEffect();
        drawMirrorLightModel();
        return TRUE;
    }
    
    if (dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x20)) {
        offBodyEffect();
    } else {
        onBodyEffect();
    }
    
    s16 origFogR, origFogG, origFogB;
    f32 origFogStartZ, origFogEndZ;
    origFogR = mTevStr.mFogColor.r;
    origFogG = mTevStr.mFogColor.g;
    origFogB = mTevStr.mFogColor.b;
    origFogStartZ = mTevStr.mFogStartZ;
    origFogEndZ = mTevStr.mFogEndZ;
    if (!checkFreezeState() && mCurProc != PROC_ELEC_DAMAGE_e && (daPy_dmEcallBack_c::checkCurse() || checkConfuse() || mDamageWaitTimer > 0)) {
        cXyz sp18;
        mDoLib_pos2camera(&current.pos, &sp18);
        f32 f2 = fabsf(cM_ssin(g_Counter.mTimer * 0x800));
        if (daPy_dmEcallBack_c::checkCurse() || checkConfuse()) {
            mTevStr.mFogColor.r = 0x80;
            mTevStr.mFogColor.g = 0x00;
            mTevStr.mFogColor.b = 0xFF;
        } else {
            mTevStr.mFogColor.r = 0xFF;
            mTevStr.mFogColor.g = 0x3C;
            mTevStr.mFogColor.b = 0x3C;
        }
        mTevStr.mFogStartZ = -sp18.z - 200.0f + 200.0f * f2;
        mTevStr.mFogEndZ = mTevStr.mFogStartZ + 300.0f;
    }
    
    u16 material_num = m035C->getUpdateMaterialNum();
    for (u16 i = 0; i < material_num; i++) {
        u16 matID = m035C->getUpdateMaterialID(i);
        if (matID != 0xFFFF) {
            J3DMaterial* mtl = mpCLModelData->getMaterialNodePointer(matID);
            J3DMaterialAnm* mtlAnm = mtl->getMaterialAnm();
            u8 texNo = m035C->getAnmTable()[i].mTexNo;
            mtlAnm->setTexNoAnm(texNo, &m_texNoAnms[i]);
            if (matID != 0xE) {
                // Not mouth (i.e. it's eyeL, eyeR, mayuL, or mayuR)
                mtl = mpCLModelData->getMaterialNodePointer(matID+1);
                mtlAnm = mtl->getMaterialAnm();
                mtlAnm->setTexNoAnm(texNo, &m_texNoAnms[i]);
            }
        }
    }
    
    mpCLModelData->setTexMtxAnimator(mpTexScrollResData, m_texMtxAnm, NULL);
    m035C->setFrame(m3530);
    mpTexScrollResData->setFrame(m3532);
    g_env_light.setLightTevColorType(mpCLModel, &mTevStr);
    J3DJoint* link_root_joint = mpCLModelData->getJointNodePointer(0x00); // link_root joint
    mpCLModelData->getJointNodePointer(0x08)->getMesh()->getShape()->hide(); // cl_LhandA joint
    mpCLModelData->getJointNodePointer(0x0C)->getMesh()->getShape()->hide(); // cl_RhandA joint
    
    J3DMaterial* mtl = link_root_joint->getMesh();
    for (int i = 0; i < 4; i++) {
        mtl = mtl->getNext();
    }
    mtl->getShape()->show();
    
    J3DJoint* cl_eye_joint = mpCLModelData->getJointNodePointer(0x13); // cl_eye joint
    J3DJoint* cl_mayu_joint = mpCLModelData->getJointNodePointer(0x15); // cl_mayu joint
    setDrawHandModel();
    j3dSys.setModel(mpCLModel);
    j3dSys.setTexture(mpCLModelData->getTexture());
    j3dSys.getModel()->unlock();
    
    BOOL r24 = field_0x2b0 <= -85.0f;
    if (r24) {
        for (int i = 0; i < ARRAY_SIZE(mpZOffBlendShape); i++) {
            mpZOffBlendShape[i]->hide();
            mpZOffNoneShape[i]->hide();
            mpZOnShape[i]->hide();
        }
        mpCLModelData->getJointNodePointer(0x08)->getMesh()->getShape()->hide(); // cl_LhandA joint
        mpCLModelData->getJointNodePointer(0x0C)->getMesh()->getShape()->hide(); // cl_RhandA joint
        mtl = link_root_joint->getMesh();
        for (int i = 0; mtl != NULL; i++, mtl = mtl->getNext()) {
            if (i != 3) {
                mtl->getShape()->hide();
            } else {
                mtl->getShape()->show();
            }
        }
    } else if (dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x20)) {
        for (int i = 0; i < ARRAY_SIZE(mpZOffBlendShape); i++) {
            mpZOffBlendShape[i]->hide();
            mpZOffNoneShape[i]->hide();
            mpZOnShape[i]->hide();
        }
        mtl = link_root_joint->getMesh();
        for (int i = 0; mtl != NULL; i++, mtl = mtl->getNext()) {
            if (i != 0 && i != 3) {
                mtl->getShape()->hide();
            } else {
                mtl->getShape()->show();
            }
        }
        mpCLModelData->getJointNodePointer(0x14)->getMesh()->getShape()->hide(); // cl_hana joint
    } else {
        if (!checkFreezeState()) {
            dComIfGd_setListP0();
            l_onCupOffAupPacket2.entryOpa();
            for (int i = 0; i < ARRAY_SIZE(mpZOffBlendShape); i++) {
                mpZOffBlendShape[i]->hide();
                mpZOnShape[i]->hide();
                mpZOffNoneShape[i]->show();
            }
            cl_eye_joint->entryIn();
            cl_mayu_joint->entryIn();
            l_offCupOnAupPacket2.entryOpa();
            for (int i = 0; i < ARRAY_SIZE(mpZOffBlendShape); i++) {
                mpZOffBlendShape[i]->show();
                mpZOffNoneShape[i]->hide();
            }
            cl_eye_joint->entryIn();
            cl_mayu_joint->entryIn();
            mtl = link_root_joint->getMesh();
            for (int i = 0; mtl != NULL; i++, mtl = mtl->getNext()) {
                if (i != 2 && i != 5) {
                    mtl->getShape()->hide();
                }
            }
            link_root_joint->entryIn();
            if (checkMaskDraw()) {
                entryDLSetLight(mpYamuModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
            }
            j3dSys.setModel(mpCLModel);
            j3dSys.setTexture(mpCLModelData->getTexture());
            hideHatAndBackle(link_root_joint->getMesh());
            l_onCupOffAupPacket1.entryOpa();
            for (int i = 0; i < ARRAY_SIZE(mpZOffBlendShape); i++) {
                mpZOffBlendShape[i]->hide();
                mpZOnShape[i]->show();
                mpZOffNoneShape[i]->hide();
            }
            cl_eye_joint->entryIn();
            cl_mayu_joint->entryIn();
            l_offCupOnAupPacket1.entryOpa();
            for (int i = 0; i < ARRAY_SIZE(mpZOffBlendShape); i++) {
                mpZOnShape[i]->hide();
            }
        } else {
            hideHatAndBackle(link_root_joint->getMesh());
        }
        bool r4 = dComIfGs_getSelectEquip(0) == SWORD || dComIfGp_getMiniGameType() == 2; // TODO this may be an inline
        if (!r4 && dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) != dStageType_FF1_e ||
            checkCaughtShapeHide() || checkDemoShieldNoDraw())
        {
            mpCLModelData->getJointNodePointer(0x0D)->getMesh()->getShape()->hide(); // cl_podA joint
        } else {
            mpCLModelData->getJointNodePointer(0x0D)->getMesh()->getShape()->show(); // cl_podA joint
        }
    }
    
    // regalloc issues with j3dSys from here on
    dComIfGd_setListP1();
    if (checkFreezeState()) {
        dMat_control_c::iceEntryDL(mpCLModel, -1, NULL);
    } else {
        mDoExt_modelEntryDL(mpCLModel);
    }
    mtl = link_root_joint->getMesh();
    while (mtl != NULL) {
        mtl->getShape()->show();
        mtl = mtl->getNext();
    }
    mpCLModelData->getJointNodePointer(0x14)->getMesh()->getShape()->show(); // cl_hana joint
    mpCLModelData->getJointNodePointer(0x29)->getMesh()->getShape()->show(); // cl_back joint
    if (!r24) {
        entryDLSetLight(mpHandsModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES) && !checkCaughtShapeHide() && !dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x20)) {
            entryDLSetLight(mpKatsuraModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        }
        if (checkFreezeState() && checkMaskDraw()) {
            entryDLSetLight(mpYamuModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        }
        if (dComIfGs_getSelectEquip(2) == PWR_GROOVE) {
            entryDLSetLight(mpPringModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        }
        // TODO this may be an inline
        bool r4 = dComIfGs_getSelectEquip(0) == MASTER_SWORD || dComIfGs_getSelectEquip(0) == LV3_SWORD || dComIfGs_getSelectEquip(0) == MASTER_SWORD_EX;
        if (r4 && !checkCaughtShapeHide() && !checkDemoShieldNoDraw()) {
            updateDLSetLight(mpPodmsModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        }
    }
    if (checkEquipHeavyBoots()) {
        entryDLSetLight(mpHbootsModels[0], mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        entryDLSetLight(mpHbootsModels[1], mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
    }
    
    mTevStr.mFogColor.r = origFogR;
    mTevStr.mFogColor.g = origFogG;
    mTevStr.mFogColor.b = origFogB;
    mTevStr.mFogStartZ = origFogStartZ;
    mTevStr.mFogEndZ = origFogEndZ;
    
    if (!r24) {
        if (mCurProc == PROC_CUT_F_e || mCurProc == PROC_BT_VERTICAL_JUMP_CUT_e) {
            updateDLSetLight(mpSwordTipStabModel, 0);
        } else if (checkModeFlg(ModeFlg_SWIM) && checkNoResetFlg0(daPyFlg0_UNK100) && !(mCurProc == DPROC_DEAD_e && m34D6 == 0)) {
            GXColor spc;
            GXColor sp8;
            dKy_get_seacolor(&spc, &sp8);
            J3DGXColorS10 sp10;
            sp10.mColor.r = spc.r;
            sp10.mColor.g = spc.g;
            sp10.mColor.b = spc.b;
            int matID = mpSuimenMunyaModel->getModelData()->getMaterialNum() - 1;
            for (; matID >= 0; matID--) {
                mpSuimenMunyaModel->getModelData()->getMaterialNodePointer(matID)->setTevColor(0, &sp10);
            }
            mDoExt_modelUpdateDL(mpSuimenMunyaModel);
        }
        if (!r24 && !dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x20)) {
            bool r4 = dComIfGs_getSelectEquip(0) != NO_ITEM || dComIfGp_getMiniGameType() == 2; // TODO this may be an inline
            if (r4 && !checkDemoSwordNoDraw(1)) {
                entryDLSetLight(mpEquippedSwordModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
            }
        }
        if (dComIfGs_getSelectEquip(1) != NO_ITEM && !checkCaughtShapeHide() && !checkDemoShieldNoDraw()) {
            entryDLSetLight(mpEquippedShieldModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
        }
        dComIfGd_setList();
        drawMirrorLightModel();
        dComIfGd_setListP1();
        
        if (mpBottleContentsModel != NULL) {
            updateDLSetLight(mpBottleContentsModel, 0);
        }
        if (mpHeldItemModel && !checkCaughtShapeHide() && !checkDemoSwordNoDraw(0)) {
            if (!checkBowItem(mHeldItemType) || !checkPlayerGuard()) {
                if (mHeldItemType == HOOKSHOT) {
                    if (mActorKeepEquip.getActor()) {
                        daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
                        mpHeldItemModel->setAnmMtx(4, hookshot->getMtxTop());
                    }
                }
                entryDLSetLight(mpHeldItemModel, mNoResetFlg1 & daPyFlg1_FREEZE_STATE);
                if (mpSwordModel1 != NULL) {
                    if (checkChanceMode() || checkNoResetFlg1(daPyFlg1_UNK8000) || dComIfGs_getSelectEquip(0) == MASTER_SWORD_EX) {
                        updateDLSetLight(mpSwordModel1, 0);
                    }
                }
            }
        }
        if (mpBottleCapModel != NULL && m355E != 0) {
            updateDLSetLight(mpBottleCapModel, 0);
        }
        
        if (!dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x20)) {
            f32 frame = mYaura00rBrk.getBrkAnm()->getFrame();
            if (frame > 0.0f) {
                daPy_aura_c* auraEntry = &mMagicArmorAuraEntries[0];
                mYaura00rBrk.entry(auraEntry->getModel()->getModelData(), frame);
                for (int i = 0; i < (s32)ARRAY_SIZE(mMagicArmorAuraEntries); i++, auraEntry++) {
                    mpYaura00Btk->setFrame(auraEntry->getFrame());
                    updateDLSetLight(auraEntry->getModel(), 0);
                }
            }
            frame = mYmgcs00Brk.getBrkAnm()->getFrame();
            if (frame > 0.0f) {
                mYmgcs00Brk.entry(mpYmgcs00Model->getModelData(), frame);
                mDoExt_modelEntryDL(mpYmgcs00Model);
            }
        }
    }
    if (fanWindEffectDraw()) {
        updateDLSetLight(mpYuchw00Model, 0);
    }
    if (fanWindCrashEffectDraw()) {
        updateDLSetLight(mpYbafo00Model, 0);
    }
    dComIfGd_setList();
    if (mCurProc != DPROC_CAUGHT_e && !dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        drawShadow();
    }
    if (mSwBlur.field_0x014 > 0) {
        dComIfGd_entryZSortXluList(&mSwBlur, mSwBlur.field_0x304[0]);
    }
    
    return TRUE;
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
    if (mID != fpcM_ERROR_PROCESS_ID_e) {
        mActor = fopAcM_SearchByID(mID);
        if (mActor == NULL) {
            mID = fpcM_ERROR_PROCESS_ID_e;
        }
    } else {
        mActor = NULL;
    }
}

/* 8010848C-801084AC       .text setData__16daPy_actorKeep_cFP10fopAc_ac_c */
void daPy_actorKeep_c::setData(fopAc_ac_c* actor) {
    mActor = actor;
    mID = fopAcM_GetID(actor);
}

/* 801084AC-801084C0       .text clearData__16daPy_actorKeep_cFv */
void daPy_actorKeep_c::clearData() {
    mID = fpcM_ERROR_PROCESS_ID_e;
    mActor = NULL;
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
int daPy_lk_c::getDirectionFromAngle(s16 angle) {
    if (abs(angle) > 0x6000) {
        return 1;
    } else if (angle >= 0x2000) {
        return 2;
    } else if (angle <= -0x2000) {
        return 3;
    } else {
        return 0;
    }
}

/* 80108B08-80108B38       .text getDirectionFromShapeAngle__9daPy_lk_cFv */
int daPy_lk_c::getDirectionFromShapeAngle() {
    return getDirectionFromAngle(m34E8 - shape_angle.y);
}

/* 80108B38-80108B68       .text getDirectionFromCurrentAngle__9daPy_lk_cFv */
int daPy_lk_c::getDirectionFromCurrentAngle() {
    return getDirectionFromAngle(m34E8 - current.angle.y);
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
BOOL daPy_lk_c::checkBodyAngleX(s16) {
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
void daPy_lk_c::setFrameCtrl(J3DFrameCtrl* frameCtrl, u8 attribute, s16 start, s16 end, f32 rate, f32 frame) {
    frameCtrl->setAttribute(attribute);
    frameCtrl->setEnd(end);
    frameCtrl->setRate(rate);
    frameCtrl->setStart(start);
    frameCtrl->setFrame(frame);
    if (rate >= 0.0f) {
        frameCtrl->setLoop(start);
    } else {
        frameCtrl->setLoop(end);
    }
}

/* 8010ACEC-8010AD2C       .text checkAtnWaitAnime__9daPy_lk_cFv */
BOOL daPy_lk_c::checkAtnWaitAnime() {
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
    if (strcmp(dComIfGp_getStartStageName(), "M_DragB") == 0 ||
        strcmp(dComIfGp_getStartStageName(), "Xboss0") == 0)
    {
        return TRUE;
    }
    return FALSE;
}

/* 8010C4A4-8010C4C8       .text checkSingleItemEquipAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkSingleItemEquipAnime() const {
    return m_anm_heap_upper[2].mIdx == LKANM_BCK_TAKEL || m_anm_heap_upper[2].mIdx == LKANM_BCK_TAKER;
}

/* 8010C4C8-8010C528       .text checkItemEquipAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkItemEquipAnime() const {
    return m_anm_heap_upper[2].mIdx == LKANM_BCK_TAKE || checkSingleItemEquipAnime() || m_anm_heap_upper[2].mIdx == LKANM_BCK_TAKEBOTH;
}

/* 8010C528-8010C570       .text checkEquipAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkEquipAnime() const {
    return m_anm_heap_upper[2].mIdx == LKANM_BCK_REST || checkItemEquipAnime();
}

/* 8010C570-8010C71C       .text deleteEquipItem__9daPy_lk_cFi */
void daPy_lk_c::deleteEquipItem(BOOL param_1) {
    fopAc_ac_c* equipActor = mActorKeepEquip.getActor();
    if (param_1 && (mHeldItemType != 0x100 && mHeldItemType != 0x101)) {
        if (mHeldItemType == 0x103) {
            seStartOnlyReverb(JA_SE_LK_SW_PUTIN_S);
        } else {
            seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
        }
    }
    
    if (mHeldItemType == 0x103) {
        mDoAud_bgmSetSwordUsing(0);
    } else if (mHeldItemType == 0x101) {
        if (equipActor != NULL) {
            fopAcM_cancelCarryNow(equipActor);
        }
    } else if (equipActor != NULL) {
        fopAcM_delete(equipActor);
    }
    
    if ((mHeldItemType == ROPE && checkRopeAnime()) ||
        (mHeldItemType == BOOMERANG && checkBoomerangAnime()) ||
        (mHeldItemType == HOOKSHOT && m_anm_heap_upper[2].mIdx == LKANM_BCK_HOOKSHOTWAIT) ||
        (checkBowItem(mHeldItemType) && checkBowAnime()))
    {
        resetActAnimeUpper(UPPER_UNK2, -1.0f);
    }
    
    mActorKeepEquip.clearData();
    mHeldItemType = 0x100;
    mpHeldItemModel = NULL;
    if (mSwordAnim.getBckAnm() != NULL) {
        mSwordAnim.changeBckOnly(NULL);
    }
    m2EAC = NULL;
    mpHeldItemModelAnimTexEx = NULL;
    mpBottleContentsModel = NULL;
    mpBottleCapModel = NULL;
    mpHeldItemAnimBRK = NULL;
    mpSwordAnimBTK = NULL;
    mpSwordModel1 = NULL;
    m3454.end();
    mpSwordTipStabModel = NULL;
    m2EF8 = 0;
    m2EF4 = 0;
    m2EF0 = 0;
    offNoResetFlg1(daPyFlg1_UNK200000);
}

/* 8010C71C-8010C7F4       .text setFallVoice__9daPy_lk_cFv */
void daPy_lk_c::setFallVoice() {
    /* Nonmatching */
}

/* 8010C7F4-8010C854       .text keepItemData__9daPy_lk_cFv */
/* Saves which item the player was holding in their hand so it can be restored later. */
void daPy_lk_c::keepItemData() {
    mKeepItemType = mHeldItemType;
    
    deleteEquipItem(FALSE);
    
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
    
    deleteEquipItem(FALSE);
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
    JKRHeap* oldHeap = setItemHeap();
    initModel(&mpHeldItemModel, LINK_BDL_TELESCOPE, 0x37221222);
    mDoExt_setCurrentHeap(oldHeap);
}

/* 8010CBC8-8010CC78       .text setPhotoBoxModel__9daPy_lk_cFv */
void daPy_lk_c::setPhotoBoxModel() {
    JKRHeap* oldHeap = setItemHeap();
    initModel(&mpHeldItemModel, LINK_BDL_CAMERA, 0x37221222);
    mDoExt_setCurrentHeap(oldHeap);
    if (mHeldItemType == CAMERA) {
        mpHeldItemModel->getModelData()->getJointNodePointer(0x02)->getMesh()->getShape()->hide();
    } else {
        mpHeldItemModel->getModelData()->getJointNodePointer(0x02)->getMesh()->getShape()->show();
    }
}

/* 8010CC78-8010CD34       .text changeDragonShield__9daPy_lk_cFi */
void daPy_lk_c::changeDragonShield(int) {
    /* Nonmatching */
}

/* 8010CD34-8010CFB4       .text checkNewItemChange__9daPy_lk_cFUc */
BOOL daPy_lk_c::checkNewItemChange(u8) {
    /* Nonmatching */
}

/* 8010CFB4-8010D26C       .text checkItemChangeFromButton__9daPy_lk_cFv */
BOOL daPy_lk_c::checkItemChangeFromButton() {
    /* Nonmatching */
}

/* 8010D26C-8010D754       .text checkItemAction__9daPy_lk_cFv */
BOOL daPy_lk_c::checkItemAction() {
    /* Nonmatching */
}

/* 8010D754-8010D810       .text getSlidePolygon__9daPy_lk_cFv */
void daPy_lk_c::getSlidePolygon() {
    /* Nonmatching */
}

/* 8010D810-8010D8B0       .text checkJumpCutFromButton__9daPy_lk_cFv */
BOOL daPy_lk_c::checkJumpCutFromButton() {
    /* Nonmatching */
}

/* 8010D8B0-8010DB58       .text orderTalk__9daPy_lk_cFv */
void daPy_lk_c::orderTalk() {
    /* Nonmatching */
}

/* 8010DB58-8010E448       .text checkNextActionFromButton__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionFromButton() {
    /* Nonmatching */
}

/* 8010E448-8010E75C       .text setShieldGuard__9daPy_lk_cFv */
void daPy_lk_c::setShieldGuard() {
    /* Nonmatching */
}

/* 8010E75C-8010E7C4       .text checkItemModeActorPointer__9daPy_lk_cFv */
BOOL daPy_lk_c::checkItemModeActorPointer() {
    /* Nonmatching */
}

/* 8010E7C4-8010E828       .text checkNextActionItemFly__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionItemFly() {
    /* Nonmatching */
}

/* 8010E828-8010EC78       .text checkNextMode__9daPy_lk_cFi */
BOOL daPy_lk_c::checkNextMode(int) {
    /* Nonmatching */
}

/* 8010EC78-8010ED68       .text checkIceSlipFall__9daPy_lk_cFv */
BOOL daPy_lk_c::checkIceSlipFall() {
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
BOOL daPy_lk_c::setDamagePoint(f32 amount) {
    if (!checkNoDamageMode()) {
        dComIfGp_setItemLifeCount(amount);
        if (amount < 0.0f) {
            offNoResetFlg1(daPyFlg1_UNK8000);
            if (dComIfGs_getSelectEquip(0) != MASTER_SWORD_EX) {
                offNoResetFlg1(daPyFlg1_UNK200000);
            }
        }
        return TRUE;
    } else {
        seStartMapInfo(JA_SE_LK_MGC_SHIELD_DEF);
        return FALSE;
    }
}

/* 80110338-80110448       .text checkNormalDamage__9daPy_lk_cFi */
BOOL daPy_lk_c::checkNormalDamage(int) {
    /* Nonmatching */
}

/* 80110448-801104E4       .text setDashDamage__9daPy_lk_cFv */
void daPy_lk_c::setDashDamage() {
    /* Nonmatching */
}

/* 801104E4-8011054C       .text checkAtHitEnemy__9daPy_lk_cFP12dCcD_GObjInf */
BOOL daPy_lk_c::checkAtHitEnemy(dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 8011054C-801105D8       .text checkElecReturnDamage__9daPy_lk_cFP12dCcD_GObjInfP4cXyz */
BOOL daPy_lk_c::checkElecReturnDamage(dCcD_GObjInf*, cXyz*) {
    /* Nonmatching */
}

/* 801105D8-80110654       .text checkWallAtributeDamage__9daPy_lk_cFP12dBgS_AcchCir */
s32 daPy_lk_c::checkWallAtributeDamage(dBgS_AcchCir*) {
    /* Nonmatching */
}

/* 80110654-80110F3C       .text changeDamageProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeDamageProc() {
    if (!checkModeFlg(ModeFlg_DAMAGE) && mDamageWaitTimer > 0) {
        mDamageWaitTimer--;
        if (mDamageWaitTimer == 0) {
            if (m_anm_heap_upper[2].mIdx == LKANM_BCK_DAMDASH) {
                resetActAnimeUpper(UPPER_UNK2, daPy_HIO_basic_c0::m.field_0xC);
            } else if (checkModeFlg(ModeFlg_SWIM)) {
                resetPriTextureAnime();
            }
        }
    }
    
    if (checkNoResetFlg0(daPyFlg0_UNK1000000)) {
        offNoResetFlg0(daPyFlg0_UNK1000000);
        changePlayer(this);
        return procLargeDamage_init(-5, 1, 0, 0);
    }
    
    daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
    if (dComIfGp_event_runCheck() ||
        mDemo.getDemoType() != 0 ||
        checkNoControll() ||
        mCurProc == PROC_SHIP_READY_e ||
        (
            dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) &&
            ship && ship->unknown_inline_TODO()
        )
    ) {
        offNoResetFlg0(daPyFlg0_SHIP_DROP);
        return FALSE;
    }
    
    BOOL r30;
    int r29;
    s32 r28 = dBgS_Attr_NORMAL_e;
    
    if (checkNoResetFlg1(daPyFlg1_UNK4) || (
        mAcch.ChkGroundHit() &&
        !checkModeFlg(ModeFlg_HANG) &&
        mCurrAttributeCode == dBgS_Attr_FREEZE_e
    )) {
        changePlayer(this);
        return dProcFreezeDamage_init();
    } else if (
        dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) &&
        checkNoResetFlg0(daPyFlg0_SHIP_DROP)
    ) {
        offNoResetFlg0(daPyFlg0_SHIP_DROP);
        changePlayer(this);
        return procLargeDamage_init(-2, 1, 0, 0);
    } else if (!checkModeFlg(ModeFlg_DAMAGE) && mDamageWaitTimer == 0) {
        if (mAcch.ChkGroundHit() && (
            mCurrAttributeCode == dBgS_Attr_DAMAGE_e ||
            mCurrAttributeCode == dBgS_Attr_ELECTRICITY_e
        )) {
            r28 = mCurrAttributeCode;
        } else {
            for (int i = 0; r28 == dBgS_Attr_NORMAL_e && i < (s32)ARRAY_SIZE(mAcchCir); i++) {
                r28 = checkWallAtributeDamage(&mAcchCir[i]);
            }
        }
    }
    
    if (r28 != dBgS_Attr_NORMAL_e) {
        r30 = TRUE;
        r29 = 1;
    } else {
        r30 = FALSE;
        r29 = mStts.GetDmg();
        if (mCyl.ChkTgHit() && mCyl.GetTgHitGObj() && mCyl.GetTgHitGObj()->GetAtType() == 0x20) {
            r29 = 1;
        }
    }
    
    dCcG_At_Spl r27;
    if (mCyl.ChkTgHit()) {
        dCcD_GObjInf* gobj = mCyl.GetTgHitGObj();
        if (gobj) {
            r27 = gobj->GetAtSpl();
        } else {
            r27 = mStts.GetAtSpl();
        }
    } else {
        r27 = (dCcG_At_Spl)0;
    }
    
    if (checkModeFlg(ModeFlg_04000000)) {
        if (r30 || mCyl.ChkTgHit() && !checkSuccessGuard(r27)) {
            setDamagePoint(-r29);
            mDamageWaitTimer = daPy_HIO_dam_c0::m.field_0x2;
            
            voiceStart(2);
            
            seStartOnlyReverb(JA_SE_LK_DAMAGE_NORMAL);
            changePlayer(this);
            if (mCyl.ChkTgHit() && !checkSuccessGuard(r27)) {
                setDamageEmitter();
            } else if (r28 == dBgS_Attr_ELECTRICITY_e) {
                setDamageElecEmitter();
            }
            if (daPy_dmEcallBack_c::checkElec()) {
                if (checkModeFlg(ModeFlg_ROPE)) {
                    return procElecDamage_init(NULL);
                } else if (checkModeFlg(ModeFlg_SWIM)) {
                    return procElecDamage_init(NULL);
                }
            }
            if (checkModeFlg(ModeFlg_SWIM) && !checkNoDamageMode()) {
                setPriTextureAnime(0x40, 0);
            }
        }
    } else {
        if (mAtCps[0].GetAtType() != 0x80 && mAtCps[0].GetAtType() != 0x100) {
            cXyz sp8;
            if (checkElecReturnDamage(&mAtCps[0], &sp8) ||
                checkElecReturnDamage(&mAtCps[1], &sp8) ||
                checkElecReturnDamage(&mAtCps[2], &sp8)
            ) {
                setDamagePoint(-1.0f);
                onResetFlg0(daPyRFlg0_UNK80000);
                setDamageElecEmitter();
                changePlayer(this);
                
                if (procElecDamage_init(&sp8)) {
                    return TRUE;
                }
                
                if (daPy_lk_c::checkPlayerFly()) {
                    return procLargeDamage_init(-1, 1, 0, 0);
                } else {
                    return procDamage_init();
                }
            }
        }
        
        if (mCyl.ChkTgHit() && !checkGuardSlip() &&
            (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) || !checkNoDamageMode())
        ) {
            freeRopeItem();
            freeHookshotItem();
            
            if (!checkSuccessGuard(r27)) {
                if (mHeldItemType == 0x101) {
                    deleteEquipItem(FALSE);
                }
                
                setDamageEmitter();
                changePlayer(this);
                setDamagePoint(-r29);
                fopAc_ac_c* grabActor = mActorKeepGrab.getActor();
                if (daPy_dmEcallBack_c::checkElec()) {
                    if (procElecDamage_init(NULL)) {
                        return TRUE;
                    }
                }
                
                if (checkModeFlg(ModeFlg_IN_SHIP)) {
                    return procLargeDamage_init(-9, 1, 0, 0);
                }
                
                if (checkGrabWear() &&
                    mCyl.GetTgHitAc() && fopAcM_GetName(mCyl.GetTgHitAc()) == PROC_NZ &&
                    grabActor)
                {
                    cXyz* r3 = getDamageVec(&mCyl);
                    grabActor->shape_angle.y = cM_atan2s(r3->x, r3->z);
                    grabActor->shape_angle.x = 0x2000;
                    return procLargeDamage_init(-4, 1, 0, 0);
                }
                if (r27 == 7 || r27 == 2 || r27 == 10) {
                    return procLargeDamage_init(-6, 0, 0, 0);
                }
                if (daPy_lk_c::checkPlayerFly() || r27 == 6 || r27 == 1 || r27 == 9) {
                    return procLargeDamage_init(-1, 1, 0, 0);
                }
                if (checkNormalDamage(r29)) {
                    return procDamage_init();
                }
                setDashDamage();
            } else {
                u8 hitSe = mCyl.GetTgHitObjSe();
                if (hitSe == 6) {
                    seStartOnlyReverb(JA_SE_OBJ_COL_N_BDY_MPLT);
                } else if (hitSe == 2 || hitSe == 5) {
                    seStartOnlyReverb(JA_SE_OBJ_COL_SWS_NMTLP);
                } else if (hitSe == 4) {
                    seStartOnlyReverb(JA_SE_OBJ_COL_NWHP_NMTL);
                } else {
                    seStartOnlyReverb(JA_SE_OBJ_COL_SWM_NSWL);
                }
                
                if (mCurProc == PROC_CROUCH_DEFENSE_e) {
                    return procCrouchDefenseSlip_init();
                } else {
                    return procGuardSlip_init();
                }
            }
        } else if (r30) {
            changePlayer(this);
            if (mHeldItemType == 0x101) {
                deleteEquipItem(FALSE);
            }
            setDamagePoint(-r29);
            
            if (r28 == dBgS_Attr_ELECTRICITY_e) {
                setDamageElecEmitter();
                if (procElecDamage_init(NULL)) {
                    return TRUE;
                }
            }
            
            if (checkNormalDamage(r29)) {
                return procPolyDamage_init();
            }
            
            setDashDamage();
        }
    }
    
    mStts.ClrTg();
    mStts.ClrAt();
    
    return FALSE;
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
cXyz* daPy_lk_c::getDamageVec(dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 80111D64-80111E54       .text setOldRootQuaternion__9daPy_lk_cFsss */
void daPy_lk_c::setOldRootQuaternion(s16, s16, s16) {
    /* Nonmatching */
}

/* 80111E54-80111EFC       .text checkRestHPAnime__9daPy_lk_cFv */
BOOL daPy_lk_c::checkRestHPAnime() {
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
BOOL daPy_lk_c::checkDrinkBottleItem(int itemNo) const {
    return itemNo == RED_BOTTLE || itemNo == GREEN_BOTTLE || itemNo == BLUE_BOTTLE || itemNo == SOUP_BOTTLE || itemNo == BOTTLESHIP;
}

/* 80111FEC-8011201C       .text checkOpenBottleItem__9daPy_lk_cCFi */
BOOL daPy_lk_c::checkOpenBottleItem(int itemNo) const {
    return itemNo == FIREFLY_BOTTLE || itemNo == BIN_IN_WATER || itemNo == FWATER_BOTTLE || itemNo == FAIRY_BOTTLE;
}

/* 8011201C-80112044       .text checkBowItem__9daPy_lk_cCFi */
BOOL daPy_lk_c::checkBowItem(int itemNo) const {
    return itemNo == BOW || itemNo == MAGIC_ARROW || itemNo == LIGHT_ARROW;
}

/* 80112044-80112064       .text checkPhotoBoxItem__9daPy_lk_cCFi */
BOOL daPy_lk_c::checkPhotoBoxItem(int itemNo) const {
    return itemNo == CAMERA || itemNo == CAMERA2;
}

/* 80112064-80112100       .text checkScopeEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::checkScopeEnd() {
    /* Nonmatching */
}

/* 80112100-8011215C       .text setSubjectMode__9daPy_lk_cFv */
void daPy_lk_c::setSubjectMode() {
    /* Nonmatching */
}

/* 8011215C-801121C8       .text checkMaskDraw__9daPy_lk_cFv */
BOOL daPy_lk_c::checkMaskDraw() {
    /* Nonmatching */
}

/* 801121C8-80112280       .text checkSubjectEnd__9daPy_lk_cFi */
BOOL daPy_lk_c::checkSubjectEnd(int) {
    /* Nonmatching */
}

/* 80112280-80112330       .text checkGuardAccept__9daPy_lk_cFv */
BOOL daPy_lk_c::checkGuardAccept() {
    if (checkModeFlg(ModeFlg_00000040) && !checkBowAnime()) {
        if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) != dStageType_MISC_e ||
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
    offNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD);
    mTinkleShieldTimer = 0;
}

/* 80112348-80112954       .text commonProcInit__9daPy_lk_cFQ29daPy_lk_c9daPy_PROC */
BOOL daPy_lk_c::commonProcInit(daPy_lk_c::daPy_PROC proc) {
    ProcInitTableEntry& procInit = mProcInitTable[proc];
    
    s32 temp_r29;
    BOOL resetDemoAnime = FALSE;
    s32 temp_r28;
    
    if (mCurProc == PROC_SLIP_e) {
        mDoAud_seStop(JA_SE_LK_RUN_SLIP, 0);
    } else if (mCurProc == PROC_GRAB_MISS_e || (mCurProc == PROC_GRAB_READY_e && proc != PROC_GRAB_MISS_e)) {
        mActorKeepRope.clearData();
    } else if (mCurProc == DPROC_TALISMAN_WAIT_e) {
        seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
        mpHeldItemModel = NULL;
    } else if (mCurProc == PROC_FAN_SWING_e) {
        setSmallFanModel();
    } else if (mCurProc == PROC_FAN_GLIDE_e) {
        deleteEquipItem(FALSE);
        mMaxFallSpeed = daPy_HIO_autoJump_c0::m.field_0x10;
        setSmallFanModel();
        mHeldItemType = DEKU_LEAF;
        m35F0 = m3688.y;
        m3730 = cXyz::Zero;
        m34E0 = 0;
        m34E4 = 0;
    } else if (mCurProc == PROC_SLOW_FALL_e) {
        mMaxFallSpeed = daPy_HIO_autoJump_c0::m.field_0x10;
    } else if (mCurProc == DPROC_TOOL_e) {
        resetDemoAnime = TRUE;
        speed.y = 0.0f;
    } else if (mCurProc == DPROC_GET_ITEM_e || mCurProc == DPROC_GET_DANCE_e) {
        dKy_Itemgetcol_chg_off();
        if (mCurProc == DPROC_GET_ITEM_e && m34D8 != 0) {
            m34C2 = 0xB;
        }
    } else if (mCurProc == DPROC_PRESENT_e || mCurProc == PROC_NOT_USE_e) {
        daItemBase_c* item = (daItemBase_c*)fopAcM_getItemEventPartner(this);
        if (item && (fopAcM_GetName(item) == PROC_ITEM || fopAcM_GetName(item) == PROC_Demo_Item)) {
            item->dead();
        }
    } else if (mCurProc == DPROC_LETTER_READ_e) {
        deleteEquipItem(FALSE);
    } else if (mCurProc == PROC_CUT_ROLL_END_e) {
        if (m33A8.getEmitter()) {
            m33A8.getEmitter()->setGlobalAlpha(0);
        }
    } else if (mCurProc == PROC_SHIP_BOW_e) {
        deleteArrow();
    }
    
    returnKeepItemData();
    
    temp_r28 = checkModeFlg(ModeFlg_SWIM) >> 0x12; // TODO fakematch? fixes regalloc
    
    // TODO: is this an inline?
    if (checkModeFlg(ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_SWIM | ModeFlg_CAUGHT)) {
        m34C2 = 0xA;
    }
    
    temp_r29 = (checkModeFlg(ModeFlg_MIDAIR) >> 1) ^ 1; // TODO fakematch? fixes regalloc
    
    mCurProc = proc;
    mCurProcFunc = procInit.mProcFunc;
    m3598 = 0.0f;
    mModeFlg = procInit.mProcFlags;
    
    if (m34C2 == 1) {
        m34C2 = 2;
    }
    
    // TODO: is this an inline?
    if (checkModeFlg(ModeFlg_HANG | ModeFlg_ROPE | ModeFlg_SWIM | ModeFlg_CAUGHT)) {
        m34C2 = 0xB;
    }
    
    if (checkModeFlg(ModeFlg_HANG)) {
        mAcch.OffLineCheck();
    } else {
        mAcch.OnLineCheck();
    }
    
    dComIfGp_clearPlayerStatus0(0, ~(daPyStts0_BOOMERANG_WAIT_e | daPyStts0_UNK10_e));
    dComIfGp_clearPlayerStatus1(0, ~(daPyStts1_SAIL_e | daPyStts1_UNK8000_e | daPyStts1_UNK40000_e) & 0x000FFFFF);
    
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
    
    if (!(checkEquipAnime() && checkModeFlg(ModeFlg_00000004)) && !checkModeFlg(ModeFlg_00001000)) {
        if (!(checkGrabAnime() || checkBoomerangThrowAnime()) || !checkModeFlg(ModeFlg_00004000)) {
            resetActAnimeUpper(UPPER_UNK2, -1.0f);
            if (!checkModeFlg(ModeFlg_GRAB)) {
                freeGrabItem();
            }
        }
    }
    
    if (!checkModeFlg(ModeFlg_GRAB) && !checkGrabAnime() && mActorKeepGrab.getActor()) {
        freeGrabItem();
    }
    
    if (temp_r29 && checkModeFlg(ModeFlg_MIDAIR)) {
        m3688 = current.pos;
        m35F0 = m3688.y;
        m35F4 = m3688.y;
    }
    
    if (mCurProc != PROC_SWIM_MOVE_e) {
        mSwimTailEcallBack[0].onEnd();
        mSwimTailEcallBack[1].onEnd();
    }
    
    if (!checkModeFlg(ModeFlg_SWIM)) {
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
    
    if (!checkModeFlg(ModeFlg_ROPE) && mCurProc != PROC_ROPE_SUBJECT_e && mCurProc != PROC_ROPE_MOVE_e) {
        freeRopeItem();
    }
    if (!checkModeFlg(ModeFlg_HOOKSHOT)) {
        freeHookshotItem();
    }
    if (temp_r28 && !checkModeFlg(ModeFlg_SWIM)) {
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
    return mCurProc != PROC_AUTO_JUMP_e ? -1 : m34D0;
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
BOOL daPy_lk_c::checkAttentionPosAngle(fopAc_ac_c* actor, cXyz** pOutPos) {
    if (actor) {
        s16 targetAngle = cLib_targetAngleY(&current.pos, &actor->mEyePos);
        int angleDiff = cLib_distanceAngleS(targetAngle, m34DE);
        if (angleDiff <= 0x6000) {
            *pOutPos = &actor->mEyePos;
            if (actor->mGroup == fopAc_ENEMY_e) {
                onNoResetFlg1(daPyFlg1_UNK400);
            }
            return TRUE;
        }
    }
    return FALSE;
}

/* 8011AE20-8011BE08       .text setNeckAngle__9daPy_lk_cFv */
void daPy_lk_c::setNeckAngle() {
    /* Nonmatching */
}

/* 8011BE08-8011BEA4       .text checkOriginalHatAnimation__9daPy_lk_cFv */
BOOL daPy_lk_c::checkOriginalHatAnimation() {
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

u8 normal_scale_38064[0xC];
u8 boss_scale_38067[0xC];

/* 8011D110-8011D4D0       .text checkLightHit__9daPy_lk_cFv */
BOOL daPy_lk_c::checkLightHit() {
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
    
    if (mCurProc == PROC_ROPE_SWING_START_e) {
        mAcchCir[0].SetWallH(-125.0f);
        mAcchCir[1].SetWallH(-89.9f);
        mAcchCir[2].SetWallH(0.0f);
    } else if (mCurProc == PROC_LARGE_DAMAGE_WALL_e || checkModeFlg(ModeFlg_CLIMB | ModeFlg_LADDER)) {
        mAcchCir[0].SetWallR(5.0f);
    } else if (checkModeFlg(ModeFlg_PUSHPULL)) {
        mAcchCir[0].SetWallR(40.0f);
    } else if (checkModeFlg(ModeFlg_WHIDE)) {
        mAcchCir[0].SetWallR(daPy_HIO_wall_c0::m.field_0x50);
        if (checkNoResetFlg0(daPyFlg0_UNK10000)) {
            mAcchCir[2].SetWallH(89.9f);
        }
    } else if (checkModeFlg(ModeFlg_SWIM)) {
        mAcchCir[0].SetWallR(67.5f);
        mAcchCir[0].SetWallH(-5.0f);
        mAcchCir[1].SetWallH(0.0f);
        mAcchCir[2].SetWallH(20.0f);
    } else if (checkModeFlg(ModeFlg_CRAWL) && mCurProc != PROC_CRAWL_END_e) {
        mAcchCir[0].SetWallR(30.0f);
        mAcchCir[0].SetWallH(10.0f);
        mAcchCir[1].SetWallH(50.0f);
        mAcchCir[2].SetWallH(50.0f);
    } else if (checkModeFlg(ModeFlg_HANG)) {
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
        cXyz pos(current.pos.x, param_1->y + 20.0f, current.pos.z);
        m08EC.SetPos(&pos);
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
    
    if (attributeCode == dBgS_Attr_LAVA_e) {
        if (param_1) {
            current.pos.y = m35D4;
        }
        if (checkBossGomaStage()) {
            return procLavaDamage_init();
        } else {
            return dProcLavaDamage_init();
        }
    } else if (attributeCode == dBgS_Attr_VOID_e) {
        startRestartRoom(5, 0xC9, -1.0f, 0);
    }
    
    return FALSE;
}

/* 8012024C-80120724       .text checkFallCode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkFallCode() {
    /* Nonmatching */
}

/* 80120724-80120BBC       .text startRestartRoom__9daPy_lk_cFUlifi */
BOOL daPy_lk_c::startRestartRoom(u32 param_1, int eventInfoIdx, f32 param_3, int i_point) {
    /* Nonmatching - npc_sarace */
    if (!checkNoResetFlg0(daPyFlg0_UNK4000) && (i_point != 0 || dComIfGp_event_compulsory(this))) {
        mDemo.setOriginalDemoType();
        if (i_point == 0) {
            mDemo.setDemoMode(1);
        }
        onNoResetFlg0(daPyFlg0_UNK4000);
        changePlayer(this);
        
        if (dComIfGp_getMiniGameType() == 1) {
            dComIfGp_setNextStage("sea", 1, 48);
            mDoAud_seStart(JA_SE_FORCE_BACK);
            // daNpc_Sarace_c::ship_race_result = 3;
            mTinkleShieldTimer = 0;
            return TRUE;
        } else {
            u32 stageType = dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo());
            setDamagePoint(param_3);
            mTinkleShieldTimer = 0;
            
            if (stageType == dStageType_SEA_e && !dComIfGs_isEventBit(dSv_evtBit_c::RODE_KORL) &&
                (current.roomNo == 11 || current.roomNo == 44) && dStage_chkPlayerId(0x80, current.roomNo))
            {
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), 0x80, current.roomNo, -1, 0.0f, param_1);
                u32 roomParam = setParamData(-1, 0, eventInfoIdx, 0);
                dComIfGs_setRestartRoomParam(roomParam);
                mDoAud_seStart(JA_SE_FORCE_BACK);
                return TRUE;
            }
            
            if (checkNoResetFlg0(daPyFlg0_DEKU_SP_RETURN_FLG) && mCurProc != DPROC_DEAD_e) {
                i_point = mDekuSpRestartPoint;
            } else {
                i_point = mRestartPoint;
                if (i_point != 0xFF && !dComIfGs_checkSeaLandingEvent(current.roomNo)) {
                    i_point = 0xFF;
                }
            }
            
            if (i_point == 0xFF) {
                if (stageType == dStageType_SEA_e) {
                    cXyz* pos;
                    if (dComIfGp_getShipActor()) {
                        pos = &dComIfGp_getShipActor()->current.pos;
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
                    if (mCurProc == DPROC_DEAD_e) {
                        dStage_changeScene(0, 0.0f, param_1, -1);
                    } else {
                        int roomNo = dComIfGs_getRestartRoomNo();
                        u32 roomParam = setParamData(roomNo, 0, eventInfoIdx, 0);
                        dStage_restartRoom(roomParam, param_1);
                        mDoAud_seStart(JA_SE_FORCE_BACK);
                    }
                    return TRUE;
                }
            } else if (checkNoResetFlg0(daPyFlg0_DEKU_SP_RETURN_FLG)) {
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), i_point, 41, -1, 0.0f, param_1);
            } else {
                dComIfGp_setNextStage(dComIfGp_getStartStageName(), i_point, current.roomNo, -1, 0.0f, param_1);
            }
            
            if (mCurProc != DPROC_DEAD_e) {
                u32 roomParam = setParamData(-1, 0, eventInfoIdx, 0);
                dComIfGs_setRestartRoomParam(roomParam);
                mDoAud_seStart(JA_SE_FORCE_BACK);
            }
            
            return TRUE;
        }
    }
    
    return FALSE;
}

/* 80120BBC-80120BE0       .text checkSuccessGuard__9daPy_lk_cFi */
BOOL daPy_lk_c::checkSuccessGuard(int atSpl) {
    if (!mCyl.ChkTgShieldHit() || atSpl >= 8) {
        return FALSE;
    }
    return TRUE;
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
BOOL daPy_lk_c::checkRoofRestart() {
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
    mDoAud_seDeleteObject(&mFanWindCps.GetEndP());
    
    for (i = 0; i < (int)ARRAY_SIZE(m_anm_heap_under); i++) {
        mDoExt_destroySolidHeap(m_anm_heap_under[i].mpAnimeHeap);
    }
    for (i = 0; i < (int)ARRAY_SIZE(m_anm_heap_upper); i++) {
        mDoExt_destroySolidHeap(m_anm_heap_upper[i].mpAnimeHeap);
    }
    
    mDoExt_destroySolidHeap(m_tex_anm_heap.mpAnimeHeap);
    mDoExt_destroySolidHeap(m_tex_scroll_heap.mpAnimeHeap);
    mDoExt_destroySolidHeap(mpItemHeaps[0]);
    mDoExt_destroySolidHeap(mpItemHeaps[1]);
    mDoExt_destroySolidHeap(m2ECC);
    
    mJAIZelAnime.stop();
    
    if (checkNoResetFlg1(daPyFlg1_CASUAL_CLOTHES)) {
        *mpCurrLinktex = mOtherLinktex;
    }
    
    dComIfGp_clearPlayerStatus0(0, daPyStts0_BOOMERANG_WAIT_e);
    dComIfGp_clearPlayerStatus1(0, daPyStts1_UNK40000_e);
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
    m_tex_anm_heap.m_buffer = new(0x20) u8[0x1000];
    JUT_ASSERT(20869, m_tex_anm_heap.m_buffer != 0);
    
    dComIfGp_getAnmArchive()->readIdxResource(m_tex_anm_heap.m_buffer, 0x1000, LKANM_BTP_TMABAA);
    J3DAnmTexPattern* btp = static_cast<J3DAnmTexPattern*>(J3DAnmLoaderDataBase::load(m_tex_anm_heap.m_buffer));
    btp->searchUpdateMaterialID(mpCLModelData);
    u16 material_num = btp->getUpdateMaterialNum();
    m_texNoAnms = new J3DTexNoAnm[material_num];
    JUT_ASSERT(20885, m_texNoAnms != 0);
    
    for (u16 i = 0; i < material_num; i++) {
        u16 matID = btp->getUpdateMaterialID(i);
        if (matID != 0xFFFF) {
            J3DMaterialAnm* mat_anm = new J3DMaterialAnm();
            JUT_ASSERT(20894, mat_anm != 0);
            
            if (matID != 1 && matID != 4) {
                // Not eyeL or eyeR (i.e. it's mouth, mayuL, or mayuR)
                // Set the animation on the specified material
                mpCLModelData->getMaterialNodePointer(matID)->change();
                mpCLModelData->getMaterialNodePointer(matID)->setMaterialAnm(mat_anm);
                if (matID != 0xE) {
                    // Not mouth (i.e. it's mayuL or mayuR)
                    // Additionally, set the animation on mayuLdamA and mayuLdamB or mayuRdamA and mayuRdamB
                    mpCLModelData->getMaterialNodePointer(matID+1)->change();
                    mpCLModelData->getMaterialNodePointer(matID+1)->setMaterialAnm(mat_anm);
                    mpCLModelData->getMaterialNodePointer(matID+2)->change();
                    mpCLModelData->getMaterialNodePointer(matID+2)->setMaterialAnm(mat_anm);
                }
            } else {
                // eyeL or eyeR
                // Don't the animation on the specified material
                // Instead, set it on eyeLdamA and eyeLdamB or eyeRdamA and eyeRdamB
                mpCLModelData->getMaterialNodePointer(matID+1)->change();
                mpCLModelData->getMaterialNodePointer(matID+1)->setMaterialAnm(mat_anm);
                mpCLModelData->getMaterialNodePointer(matID+2)->change();
                mpCLModelData->getMaterialNodePointer(matID+2)->setMaterialAnm(mat_anm);
            }
        }
        
        m_texNoAnms[i].setAnmIndex(i);
    }
}

/* 80123360-80123830       .text initTextureScroll__9daPy_lk_cFv */
void daPy_lk_c::initTextureScroll() {
    /* Nonmatching - regalloc */
    m_tex_scroll_heap.m_buffer = new(0x20) u8[0x800];
    JUT_ASSERT(20944, m_tex_scroll_heap.m_buffer != 0);
    
    dComIfGp_getAnmArchive()->readIdxResource(m_tex_scroll_heap.m_buffer, 0x800, LKANM_BTK_TMABA);
    J3DAnmTextureSRTKey* btk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(m_tex_scroll_heap.m_buffer));
    btk->searchUpdateMaterialID(mpCLModelData);
    u16 material_num = btk->getUpdateMaterialNum();
    JUT_ASSERT(20958, material_num == 2);
    
    m_texMtxAnm = new J3DTexMtxAnm[material_num];
    JUT_ASSERT(20961, m_texMtxAnm != 0);
    
    for (u16 no = 0; no < material_num; no++) {
        u16 matID = btk->getUpdateMaterialID(no);
        if (matID != 0xFFFF) {
            m_tex_eye_scroll[no] = new daPy_matAnm_c();
            JUT_ASSERT(20972, m_tex_eye_scroll[no] != 0);
            
            mpCLModelData->getMaterialNodePointer(matID)->change();
            mpCLModelData->getMaterialNodePointer(matID)->setMaterialAnm(m_tex_eye_scroll[no]);
            
            J3DMaterial* mtl = mpCLModelData->getMaterialNodePointer(matID);
            u8 texMtxID = btk->getUpdateTexMtxID(no);
            if (texMtxID != 0xFF) {
                J3DTexMtx* tmtx;
                if (mtl->getTexMtx(texMtxID) == NULL) {
                    tmtx = new J3DTexMtx();
                    JUT_ASSERT(20984, tmtx != 0);
                    mtl->setTexMtx(no, tmtx);
                }
                if (mtl->getTexCoord(texMtxID) != NULL) {
                    mtl->getTexCoord(texMtxID)->setTexGenMtx(GX_TEXMTX0 + (texMtxID & 0xFF) * 3);
                }
                tmtx = mtl->getTexMtx(no);
                
                m_texMtxAnm[no].setAnmTransform(btk);
                m_texMtxAnm[no].setAnmIndex(no);
                
                tmtx->getTexMtxInfo().mInfo = tmtx->getTexMtxInfo().mInfo & 0x7F | btk->getTexMtxCalcType() << 7;
                // Fakematch? The codegen doesn't match unless a temp variable is used and assigned to multiple times.
                Vec* temp = &btk->getSRTCenter(no);
                tmtx->getTexMtxInfo().mCenter.x = temp->x;
                temp = &btk->getSRTCenter(no);
                tmtx->getTexMtxInfo().mCenter.y = temp->y;
                temp = &btk->getSRTCenter(no);
                tmtx->getTexMtxInfo().mCenter.z = temp->z;
                
                JUT_ASSERT(21001, mtl->getMaterialAnm() != 0);
                
                mtl->getMaterialAnm()->setTexMtxAnm(texMtxID, &m_texMtxAnm[no]);
            }
        }
    }
}

/* 80123834-8012469C       .text createHeap__9daPy_lk_cFv */
BOOL daPy_lk_c::createHeap() {
    /* Nonmatching - daPy_HIO_c constructor */
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
    if (mpShmsModel->setSkinDeform(shmsSkinDeform, 1) != J3DErrType_Success ) { JUT_ASSERT(21080, 0); }
    
    tmp_modelData = initModel(&mpYmsls00Model, LINK_BDL_YMSLS00, 0x13000222);
    mpYmsls00Btk = entryBtk(tmp_modelData, LINK_BTK_YMSLS00);
    
    tmp_modelData = initModel(&mpHbootsModels[0], LINK_BDL_HBOOTS, 0x37221222);
    tmp_modelData = initModel(&mpHbootsModels[1], LINK_BDL_HBOOTS, 0x37221222);
    
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
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_YAURA00));
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
    mYaura00rBrk.entryFrame(0.0f);
    
    tmp_modelData = initModel(&mpYmgcs00Model, LINK_BDL_YMGCS00, 0x11001222);
    mpYmgcs00Btk = entryBtk(tmp_modelData, LINK_BTK_YMGCS00);
    brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(l_arcName, LINK_BRK_YMGCS00_MS);
    ret = mYmgcs00Brk.init(tmp_modelData, brk, false, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false, 0);
    if (!ret) { JUT_ASSERT(21161, 0); }
    mYmgcs00Brk.entryFrame(0.0f);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_BOMB));
    JUT_ASSERT(21169, tmp_modelData != 0);
    mpBombBrk = entryBrk(tmp_modelData, LINK_BRK_BOMB);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_GWP00));
    JUT_ASSERT(21176, tmp_modelData != 0);
    mpGwp00BrkData = entryBrk(tmp_modelData, LINK_BRK_GWP00);
    mpGwp00BtkData = entryBtk(tmp_modelData, LINK_BTK_GWP00);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_ARROW));
    JUT_ASSERT(21184, tmp_modelData != 0);
    mpIceArrowBtk = entryBtk(tmp_modelData, LINK_BTK_TTIPICE);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_ARROWGLITTER));
    JUT_ASSERT(21191, tmp_modelData != 0);
    mpLightArrowBtk = entryBtk(tmp_modelData, LINK_BTK_TARROWGLITTER);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_GICER00));
    JUT_ASSERT(21198, tmp_modelData != 0);
    mpGicer00Btk = entryBtk(tmp_modelData, LINK_BTK_GICER00);
    
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_GICER01));
    JUT_ASSERT(21205, tmp_modelData != 0);
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
J3DModelData* daPy_lk_c::initModel(J3DModel** i_model, int i_fileIndex, u32 i_differedDlistFlag) {
    J3DModelData* tmp_modelData;
    tmp_modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, i_fileIndex));
    JUT_ASSERT(21340, tmp_modelData != 0);
    *i_model = mDoExt_J3DModel__create(tmp_modelData, 0x00080000, i_differedDlistFlag);
    JUT_ASSERT(21344, *i_model != 0);
    return tmp_modelData;
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
    if (!fopAcM_entrySolidHeap(this, daPy_createHeap, 0xB0000)) {
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
    mHeight = 125.0f;
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
    mWindCyl.Set(l_wind_cyl_src);
    mWindCyl.SetStts(&mStts);
    mLightCyl.Set(l_wind_cyl_src);
    mLightCyl.SetStts(&mStts);
    mLightCyl.SetTgType(AT_TYPE_LIGHT);
    mAtCps[0].Set(l_at_cps_src);
    mAtCps[0].SetStts(&mStts);
    mAtCps[1].Set(l_at_cps_src);
    mAtCps[1].SetStts(&mStts);
    mAtCps[2].Set(l_at_cps_src);
    mAtCps[2].SetStts(&mStts);
    mAtCyl.Set(l_at_cyl_src);
    mAtCyl.SetStts(&mStts);
    mFanWindCps.Set(l_fan_wind_cps_src);
    mFanWindCps.SetR(70.0f);
    mFanWindCps.SetStts(&mStts);
    mFanWindSph.Set(l_fan_wind_sph_src);
    mFanWindSph.SetStts(&mStts);
    mFanLightCps.Set(l_fan_wind_cps_src);
    mFanLightCps.SetStts(&mStts);
    mFanLightCps.SetAtType(AT_TYPE_LIGHT);
    mFanLightCps.SetR(20.0f);
    
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
    createAnimeHeap(&m_tex_anm_heap.mpAnimeHeap, HEAP_TYPE_TEXTURE_ANIME_e);
    m_tex_anm_heap.mIdx = -1;
    m_tex_anm_heap.field_0x2 = -1;
    m_tex_anm_heap.field_0x4 = -1;
    m_tex_anm_heap.field_0x6 = -1;
    createAnimeHeap(&m_tex_scroll_heap.mpAnimeHeap, HEAP_TYPE_TEXTURE_SCROLL_e);
    m_tex_scroll_heap.mIdx = -1;
    m_tex_scroll_heap.field_0x2 = -1;
    m_tex_scroll_heap.field_0x4 = -1;
    m_tex_scroll_heap.field_0x6 = -1;
    mSeAnmIdx = -1;
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
    mTactZevPartnerPID = fpcM_ERROR_PROCESS_ID_e;
    m3630 = -1;
    
    ResTIMG* blur_img = (ResTIMG*)dComIfG_getObjectRes(l_arcName, LINK_BTI_BLUR);
    mSwBlur.mpBlurTex = blur_img;
    
    current.angle.z = 0;
    shape_angle.z = 0;
    m3526 = 8;
    m3648.w = 1.0f;
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
    mFace = daPyFace_UNKNOWN;
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
    i_this->mAttentionInfo.mFlags = ~0;

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
}

/* 80126F00-8012704C       .text __dt__15daPy_footData_cFv */
daPy_footData_c::~daPy_footData_c() {
}

/* 8012704C-80127160       .text __ct__15daPy_footData_cFv */
daPy_footData_c::daPy_footData_c() {
    /* Nonmatching - regalloc */
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
void daPy_lk_c::setSeAnime(const daPy_anmHeap_c* anmHeap, J3DFrameCtrl* frameCtrl) {
    /* Nonmatching */
    u32 seAnmOffsetInBck = *reinterpret_cast<u32*>(reinterpret_cast<u32>(anmHeap->m_buffer) + 0x1C);
    if (seAnmOffsetInBck == -1) {
        resetSeAnime();
    } else if (mSeAnmIdx == anmHeap->mIdx && m34F0 == anmHeap->field_0x6 && mSeAnmRate * frameCtrl->getRate() >= 0.0f) {
        mpSeAnmFrameCtrl = frameCtrl;
    } else {
        u32 data_size = *reinterpret_cast<u32*>(anmHeap->m_buffer); // TODO
        const u32 l_sanm_buffer_size = 0x200;
        JUT_ASSERT(22318, data_size < l_sanm_buffer_size);
        
        u32 seAnmPtr = *reinterpret_cast<u32*>(anmHeap->m_buffer); // TODO
        cLib_memCpy(m_sanm_buffer, anmHeap->m_buffer, seAnmPtr);
        mpSeAnmFrameCtrl = frameCtrl;
        mSeAnmIdx = anmHeap->mIdx;
        m34F0 = anmHeap->field_0x6;
        mSeAnmRate = frameCtrl->getRate();
        initSeAnime();
    }
}

/* 80127CC0-80127DEC       .text initSeAnime__9daPy_lk_cFv */
void daPy_lk_c::initSeAnime() {
    if (mpSeAnmFrameCtrl) {
        s16 loop = mpSeAnmFrameCtrl->getLoop();
        u32 direction = mpSeAnmFrameCtrl->getRate() >= 0.0f ? 1 : -1;
        mJAIZelAnime.initActorAnimSound(m_sanm_buffer, direction, loop);
    }
    
    if (mpSeAnmFrameCtrl->getAttribute() == J3DFrameCtrl::LOOP_REPEAT_e) {
        f32 position = mpSeAnmFrameCtrl->getFrame() - mpSeAnmFrameCtrl->getRate();
        if (position <= mpSeAnmFrameCtrl->getStart()) {
            position = mpSeAnmFrameCtrl->getEnd() - position;
        } else if (position >= mpSeAnmFrameCtrl->getEnd()) {
            position = position - mpSeAnmFrameCtrl->getEnd();
        }
        mJAIZelAnime.setPlayPosition(position);
    }
}

/* 80127DEC-80127E08       .text resetSeAnime__9daPy_lk_cFv */
void daPy_lk_c::resetSeAnime() {
    mSeAnmIdx = -1;
    m34F0 = -1;
    mpSeAnmFrameCtrl = NULL;
}

/* 80127E08-8012821C       .text setMoveAnime__9daPy_lk_cFfffQ29daPy_lk_c8daPy_ANMQ29daPy_lk_c8daPy_ANMif */
void daPy_lk_c::setMoveAnime(f32, f32, f32, daPy_lk_c::daPy_ANM, daPy_lk_c::daPy_ANM, int, f32) {
    /* Nonmatching */
}

/* 8012821C-80128494       .text setSingleMoveAnime__9daPy_lk_cFQ29daPy_lk_c8daPy_ANMffsf */
BOOL daPy_lk_c::setSingleMoveAnime(daPy_lk_c::daPy_ANM anm, f32 rate, f32 start, s16 end, f32 param_5) {
    const daPy_anmIndex_c* anmData = getAnmData(anm);
    J3DAnmTransform* under_bck;
    J3DAnmTransform* upper_bck;
    getUnderUpperAnime(anmData, &under_bck, &upper_bck, 0, 0xB400);
    m_anm_heap_under[1].mIdx = -1;
    m_anm_heap_upper[1].mIdx = -1;
    mAnmRatioUpper[0].setRatio(1.0f);
    mAnmRatioUpper[1].setRatio(0.0f);
    mAnmRatioUnder[0].setRatio(1.0f);
    mAnmRatioUnder[1].setRatio(0.0f);
    mAnmRatioUnder[0].setAnmTransform(under_bck);
    mAnmRatioUnder[1].setAnmTransform(NULL);
    
    s16 endUnder = end < 0 ? under_bck->getFrameMax() : end;
    f32 frame = rate < 0.0f ? endUnder-0.001f : start;
    setFrameCtrl(&mFrameCtrlUnder[0], under_bck->getAttribute(), start, endUnder, rate, frame);
    under_bck->setFrame(frame);
    
    if (upper_bck) {
        mAnmRatioUpper[0].setAnmTransform(upper_bck);
        s16 endUpper = end < 0 ? upper_bck->getFrameMax() : end;
        frame = rate < 0.0f ? endUpper-0.001f : start;
        // Note: It uses under_bck->getAttribute() again here instead of using upper_bck->getAttribute().
        setFrameCtrl(&mFrameCtrlUpper[0], under_bck->getAttribute(), start, endUpper, rate, frame);
        upper_bck->setFrame(frame);
    } else {
        mAnmRatioUpper[0].setAnmTransform(under_bck);
    }
    mAnmRatioUpper[1].setAnmTransform(NULL);
    
    if (param_5 >= 0.0f) {
        m_old_fdata->initOldFrameMorf(param_5, 0, 0x2A);
    }
    
    setTextureAnime(mAnmDataTable[anm].mTexAnmIdx, 0);
    setHandModel(anm);
    setSeAnime(&m_anm_heap_under[0], &mFrameCtrlUnder[0]);
    m34C3 = 0;
    
    return TRUE;
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
    J3DAnmTransform* underPack0 = getNowAnmPackUnder(UNDER_UNK0);
    J3DAnmTransform* underPack1 = getNowAnmPackUnder(UNDER_UNK1);
    J3DAnmTransform* upperPack0 = getNowAnmPackUpper(UPPER_UNK0);
    J3DAnmTransform* upperPack1 = getNowAnmPackUpper(UPPER_UNK1);
    mFrameCtrlUnder[UNDER_UNK0].update();
    underPack0->setFrame(mFrameCtrlUnder[UNDER_UNK0].getFrame());
    if (underPack1) {
        mFrameCtrlUnder[UNDER_UNK1].update();
        underPack1->setFrame(mFrameCtrlUnder[UNDER_UNK1].getFrame());
    }
    if (upperPack0 && upperPack0 != underPack0) {
        mFrameCtrlUpper[UPPER_UNK0].update();
        upperPack0->setFrame(mFrameCtrlUpper[UPPER_UNK0].getFrame());
    }
    if (upperPack1 && upperPack1 != underPack1) {
        mFrameCtrlUpper[UPPER_UNK1].update();
        upperPack1->setFrame(mFrameCtrlUpper[UPPER_UNK1].getFrame());
    }
    
    // TODO: not sure if this is a fakematch or a bug, but the under array is length 2 and this accesses at index 2.
    // so it's actually accessing index 0 of the next array (upper).
    for (int i = 2; i < 2; i++) {
        J3DAnmTransform* underPack2 = getNowAnmPackUnder((daPy_UNDER)i);
        if (underPack2) {
            mFrameCtrlUnder[i].update();
            underPack2->setFrame(mFrameCtrlUnder[i].getFrame());
        }
    }
    
    J3DAnmTransform* upperPack2 = getNowAnmPackUpper(UPPER_UNK2);
    if (upperPack2) {
        mFrameCtrlUpper[UPPER_UNK2].update();
        upperPack2->setFrame(mFrameCtrlUpper[UPPER_UNK2].getFrame());
    }
    
    if (m2EAC) {
        m2EAC->play(NULL, 0, 0);
    }
}

/* 801287E8-8012887C       .text simpleAnmPlay__9daPy_lk_cFP10J3DAnmBase */
void daPy_lk_c::simpleAnmPlay(J3DAnmBase*) {
    /* Nonmatching */
}

/* 8012887C-801288A0       .text setHandModel__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
void daPy_lk_c::setHandModel(daPy_lk_c::daPy_ANM anmIdx) {
    mLeftHandIdx = mAnmDataTable[anmIdx].mLeftHandIdx;
    mRightHandIdx = mAnmDataTable[anmIdx].mRightHandIdx;
}

/* 801288A0-8012894C       .text getAnmData__9daPy_lk_cCFQ29daPy_lk_c8daPy_ANM */
const daPy_anmIndex_c* daPy_lk_c::getAnmData(daPy_lk_c::daPy_ANM anm) const {
    if (mHeldItemType == 0x103) {
        if (anm < (s32)ARRAY_SIZE(mSwordAnmIndexTable)) {
            return &mSwordAnmIndexTable[anm];
        }
    } else if (mHeldItemType == 0x101) {
        if (anm < (s32)ARRAY_SIZE(mBokoAnmIndexTable)) {
            return &mBokoAnmIndexTable[anm];
        }
    } else if (mHeldItemType == HUMMER) {
        if (anm < (s32)ARRAY_SIZE(mHammerAnmIndexTable)) {
            return &mHammerAnmIndexTable[anm];
        }
    } else if (mHeldItemType == BOOMERANG || mHeldItemType == DEKU_LEAF || mHeldItemType == TELESCOPE) {
        if (anm == ANM_DASH) {
            return &mSwordAnmIndexTable[anm];
        }
    }
    return &mAnmDataTable[anm].mAnmIdx;
}

/* 8012894C-80128988       .text checkGrabWeapon__9daPy_lk_cFi */
BOOL daPy_lk_c::checkGrabWeapon(int) {
    /* Nonmatching */
}

/* 80128988-801289A8       .text onDekuSpReturnFlg__9daPy_lk_cFUc */
void daPy_lk_c::onDekuSpReturnFlg(u8 i_point) {
    if (i_point != 0xFF) {
        mDekuSpRestartPoint = i_point;
    }
    onNoResetFlg0(daPyFlg0_DEKU_SP_RETURN_FLG);
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
