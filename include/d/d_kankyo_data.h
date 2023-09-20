#ifndef D_KANKYO_DATA_H
#define D_KANKYO_DATA_H

#include "dolphin/types.h"

struct stage_vrbox_info_class;
struct stage_pselect_info_class;
struct stage_envr_info_class;
struct stage_palet_info_class;

struct dKyd_Schedule {
    /* 0x0 */ f32 mTimeEnd;
    /* 0x4 */ f32 mTimeBegin;
    /* 0x8 */ u8 mPalIdx0;
    /* 0x9 */ u8 mPalIdx1;
};

stage_palet_info_class* dKyd_dmpalet_getp();
stage_pselect_info_class* dKyd_dmpselect_getp();
stage_envr_info_class* dKyd_dmenvr_getp();
stage_vrbox_info_class* dKyd_dmvrbox_getp();
dKyd_Schedule* dKyd_schejule_getp();
dKyd_Schedule* dKyd_schejule_boss_getp();
dKyd_Schedule* dKyd_schejule_menu_getp();
void dKyd_xfog_table_set(u8);

#endif /* D_KANKYO_DATA_H */