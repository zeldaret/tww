
#include "d/d_cc_d.h"

char l_arcName[];

char l_tact_event_label[];
char l_tact_night_event_label[];
char l_tact_wind_change_event_label[];
char l_tact_wind_change_event_label2[];

const Vec l_ship_offset;
const Vec l_ship_offset2;
const Vec l_ship_offset3;
const Vec l_ship_redge;
const Vec l_ship_ledge;
const Vec l_heel_pos;
const Vec l_toe_pos;
const Vec l_eye_offset;
const Vec l_head_center_offset;
const Vec l_neck_front;
const Vec l_neck_top;
const Vec l_land_smoke_offset;
const Vec l_ms_light_local_start;
const Vec l_ms_light_local_vec;
const Vec l_tact_top;
const Vec l_crawl_start_front_offset;
const Vec l_crawl_front_offset;
const Vec l_crawl_back_offset;
const Vec l_crawl_top_offset;
const Vec l_crawl_front_up_offset;
const Vec l_crawl_back_up_offset;
const Vec l_crawl_stand_up_offset;
const Vec l_crawl_top_up_offset;
const Vec l_crawl_side_offset;
const Vec l_crawl_lside_offset;
const Vec l_crawl_rside_offset;
const Vec l_crawl_lside_front_offset;
const Vec l_crawl_rside_front_offset;
const Vec l_crawl_min_side_offset;

static dCcD_SrcCyl l_cyl_src;
static dCcD_SrcCyl l_wind_cyl_src;
static dCcD_SrcCyl l_at_cyl_src;
static dCcD_SrcCps l_at_cps_src;
static dCcD_SrcCps l_fan_wind_cps_src;
static dCcD_SrcSph l_fan_wind_sph_src;
