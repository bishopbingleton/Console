#ifndef GRAPHICS_HOST_H
#define GRAPHICS_HOST_H

#include <stdint.h>
#include <stdbool.h>

void graphics_init(void);
void graphics_clear(uint16_t fill_color);
void graphics_present(void);
bool graphics_draw_game_pixel(uint16_t x, uint16_t y, uint16_t color);

uint16_t graphics_get_screen_pixel(uint16_t x, uint16_t y);
uint16_t graphics_get_game_pixel(uint16_t x, uint16_t y);
bool graphics_fill_game_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
bool graphics_draw_game_rect(uint16_t x, uint16_t y, uint16_t semi_width, uint16_t semi_height, uint16_t color);
#endif