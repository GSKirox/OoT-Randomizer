#include <stdint.h>
#include "color.h"
#include "z64.h"

void update_hud_colors();
void use_default_rupee_color(uint8_t useDefaultRupeeColor);
void set_rupee_color_extern(colorRGB8_t rupee_color);
uint32_t rupee_hud_color();
extern const colorRGB8_t rupee_colors[4];
extern const colorRGB16_t defaultHeart;
extern const colorRGB16_t defaultDDHeart;

