/**
 * d_a_player_weapon.inc
 *
 * Code relating to using enemy weapons.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is not known, but a best guess was taken 
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_boko.h"

/* 80153554-801535D8       .text setEnemyWeaponAtParam__9daPy_lk_cFi */
void daPy_lk_c::setEnemyWeaponAtParam(BOOL r4) {
    static const u8 cut_type[] = {
        0x0B,
        0x0D,
        0x14,
        0x16,
        0x18,
        0x1C,
    };
    daBoko_c* boko = (daBoko_c*)mActorKeepEquip.getActor();
    u8 cutType = cut_type[fopAcM_GetParam(boko)];
    dCcG_At_Spl spl;
    u8 hitMark;
    if (r4) {
        spl = dCcG_At_Spl_UNK1;
        hitMark = G_AT_MARK_BIG_HIT;
        cutType++;
    } else {
        spl = dCcG_At_Spl_UNK0;
        hitMark = G_AT_MARK_NORMAL_HIT;
    }
    setAtParam(boko->getAtType(), boko->getAtPoint(), spl, boko->getSeType(), hitMark, cutType, boko->getCpsR());
}

/* 801535D8-8015372C       .text procWeaponNormalSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponNormalSwing_init() {
    /* Nonmatching */
}

/* 8015372C-801539C8       .text procWeaponNormalSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponNormalSwing() {
    /* Nonmatching */
}

/* 801539C8-80153A68       .text procWeaponSideSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponSideSwing_init() {
    /* Nonmatching */
}

/* 80153A68-80153C30       .text procWeaponSideSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponSideSwing() {
    /* Nonmatching */
}

/* 80153C30-80153D1C       .text procWeaponFrontSwingReady_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponFrontSwingReady_init() {
    /* Nonmatching */
}

/* 80153D1C-80153DBC       .text procWeaponFrontSwingReady__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponFrontSwingReady() {
    /* Nonmatching */
}

/* 80153DBC-80153ED8       .text procWeaponFrontSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponFrontSwing_init() {
    /* Nonmatching */
}

/* 80153ED8-80153FA0       .text procWeaponFrontSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponFrontSwing() {
    /* Nonmatching */
}

/* 80153FA0-80154014       .text procWeaponFrontSwingEnd_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponFrontSwingEnd_init() {
    /* Nonmatching */
}

/* 80154014-801540B4       .text procWeaponFrontSwingEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponFrontSwingEnd() {
    /* Nonmatching */
}

/* 801540B4-8015411C       .text procWeaponThrow_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponThrow_init() {
    /* Nonmatching */
}

/* 8015411C-80154334       .text procWeaponThrow__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponThrow() {
    /* Nonmatching */
}
