#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <stddef.h>

void graphics_init(void);
uint16_t* graphics_get_framebuffer();
void graphics_clear(uint16_t fill_color);

#endif