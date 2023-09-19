#ifndef D_KANKYO_DATA_H
#define D_KANKYO_DATA_H

#include "dolphin/types.h"

struct stage_vrbox_info_class;
struct stage_pselect_info_class;
struct stage_envr_info_class;
struct stage_palet_info_class;
struct dScnKy__Schedule;

stage_palet_info_class* dKyd_dmpalet_getp();
stage_pselect_info_class* dKyd_dmpselect_getp();
stage_envr_info_class* dKyd_dmenvr_getp();
stage_vrbox_info_class* dKyd_dmvrbox_getp();
dScnKy__Schedule* dKyd_schejule_getp();
dScnKy__Schedule* dKyd_schejule_boss_getp();
void dKyd_schejule_menu_getp();
void dKyd_xfog_table_set(u8);

#endif /* D_KANKYO_DATA_H */