#ifndef D_KANKYO_D_KANKYO_RAIN_H
#define D_KANKYO_D_KANKYO_RAIN_H

#include "dolphin/types.h"

class cXyz;

void dKyr_drawSun(f32(*)[4], cXyz*, GXColor&, u8**);
void dKyr_drawLenzflare(f32(*)[4], cXyz*, GXColor&, u8**);
void dKyr_drawRain(f32(*)[4], u8**);
void dKyr_drawSibuki(f32(*)[4], u8**);
void drawPoison(f32(*)[4], u8**);
void dKyr_drawHousi(f32(*)[4], u8**);
void dKyr_drawKazanbai(f32(*)[4], u8**);
void dKyr_drawSnow(f32(*)[4], u8**);
void dKyr_drawStar(f32(*)[4], u8**);
void drawWave(f32(*)[4], u8**);
void drawCloudShadow(f32(*)[4], u8**);
void drawVrkumo(f32(*)[4], GXColor&, u8**);
void dKyr_thunder_init();
void dKyr_thunder_move();
void dKyr_poison_light_colision();
void dKyr_wind_init();
void dKyr_wind_move();
void dKyr_sun_move();
void dKyr_lenzflare_move();
void dKyr_rain_init();
void dKyr_rain_move();
void dKyr_snow_move();
void dKyr_kazanbai_move();
void dKyr_snow_init();
void dKyr_star_init();
void dKyr_star_move();
void poison_init();
void poison_move();
void dKyr_housi_move();
void cloud_shadow_move();
void vrkumo_move();
void wave_move();
void dKyr_get_vectle_calc(cXyz*, cXyz*, cXyz*);
BOOL dKyr_poison_live_check();
BOOL dKyr_moon_arrival_check();

#endif /* D_KANKYO_D_KANKYO_RAIN_H */