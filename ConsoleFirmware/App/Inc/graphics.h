#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <stdbool.h>

void graphics_init(void);
uint16_t* graphics_get_framebuffer(void);
void graphics_clear(uint16_t fill_color);
void graphics_present(void);
bool graphics_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
//For testing Purposes only
uint16_t graphics_get_pixel(uint16_t x, uint16_t y);

#endif