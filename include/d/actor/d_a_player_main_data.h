
#include "d/d_cc_d.h"

extern char l_arcName[];

extern char l_tact_event_label[];
extern char l_tact_night_event_label[];
extern char l_tact_wind_change_event_label[];
extern char l_tact_wind_change_event_label2[];

extern const Vec l_ship_offset;
extern const Vec l_ship_offset2;
extern const Vec l_ship_offset3;
extern const Vec l_ship_redge;
extern const Vec l_ship_ledge;
extern const Vec l_heel_pos;
extern const Vec l_toe_pos;
extern const Vec l_eye_offset;
extern const Vec l_head_center_offset;
extern const Vec l_neck_front;
extern const Vec l_neck_top;
extern const Vec l_land_smoke_offset;
extern const Vec l_ms_light_local_start;
extern const Vec l_ms_light_local_vec;
extern const Vec l_tact_top;
extern const Vec l_crawl_start_front_offset;
extern const Vec l_crawl_front_offset;
extern const Vec l_crawl_back_offset;
extern const Vec l_crawl_top_offset;
extern const Vec l_crawl_front_up_offset;
extern const Vec l_crawl_back_up_offset;
extern const Vec l_crawl_stand_up_offset;
extern const Vec l_crawl_top_up_offset;
extern const Vec l_crawl_side_offset;
extern const Vec l_crawl_lside_offset;
extern const Vec l_crawl_rside_offset;
extern const Vec l_crawl_lside_front_offset;
extern const Vec l_crawl_rside_front_offset;
extern const Vec l_crawl_min_side_offset;

// I believe these won't link properly with the static variables
//extern dCcD_SrcCyl l_cyl_src;
extern dCcD_SrcCyl l_wind_cyl_src;
extern dCcD_SrcCyl l_at_cyl_src;
//extern dCcD_SrcCps l_at_cps_src;
extern dCcD_SrcCps l_fan_wind_cps_src;
extern dCcD_SrcSph l_fan_wind_sph_src;
