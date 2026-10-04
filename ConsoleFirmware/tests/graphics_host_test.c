#include "graphics_host.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
    graphics_init();
    if (!graphics_draw_pixel(0, 0, 0x1111) || graphics_get_pixel(0, 0) != 0x1111) {
        printf("Failed to draw pixel at 0, 0 or pixel color post-drawing did not match expectations.\n");
        return 1;
    }
    if (!graphics_draw_pixel(239, 159, 0x1111) || graphics_get_pixel(239, 159) != 0x1111) {
        printf("Failed to draw pixel at 239, 159 or pixel color post-drawing did not match expectations.\n");
        return 1;
    }
    if (!graphics_draw_pixel(120, 80, 0x1111) || graphics_get_pixel(120, 80) != 0x1111) {
        printf("Failed to draw pixel at 120, 80 or pixel color post-drawing did not match expectations.\n");
        return 1;
    }
    if (graphics_draw_pixel(240, 160, 0x1111)) {
        printf("Drew pixel past screen bounds. Error.\n");
        return 1;
    }

    graphics_clear(0x0000);
    
    if (!graphics_fill_rect(1, 1, 5, 7, 0x1111)) {
        printf("Invalid rectangle bounds detected on valid input.\n");
        return 1;
    }
    if (graphics_get_pixel(5, 7) != 0x1111) {
        printf("Rectangle not properly filled.\n");
        return 1;
    }
    if (graphics_get_pixel(6, 8) == 0x1111) {
        printf("Rectangle over-filled.\n");
        return 1;
    }

    graphics_clear(0x0000);
    if (!graphics_fill_rect(230, 150, 10, 10, 0x1111)) {
        printf("Invalid rectangle bounds detected on valid input.\n");
        return 1;
    }
    if (graphics_get_pixel(239, 159) != 0x1111) {
        printf("Rectangle not properly filled.\n");
        return 1;
    }

    graphics_clear(0x0000);
    
    if (!graphics_fill_rect(231, 151, 10, 10, 0x1111)) {
        printf("Invalid rectangle bounds detected on valid input.\n");
        return 1;
    }
    if (graphics_get_pixel(239, 159) != 0x1111) {
        printf("Rectangle not properly filled.\n");
        return 1;
    }

    graphics_clear(0x0000);
    if (graphics_fill_rect(231, 151, 10, 0, 0x1111)) {
        printf("Rect of 0 width and height should be invalid.\n");
        return 1;
    }
    if (graphics_fill_rect(231, 151, 0, 10, 0x1111)) {
        printf("Rect of 0 width and height should be invalid.\n");
        return 1;
    }
    if (graphics_fill_rect(240, 159, 1, 1, 0x1111)) {
        printf("Out of bound x or y should not be valid inputs\n");
        return 1;
    }
    if (graphics_fill_rect(239, 160, 1, 1, 0x1111)) {
        printf("Out of bound x or y should not be valid inputs\n");
        return 1;
    }

    graphics_clear(0x0000);


    uint16_t* pre_present_ptr = graphics_get_framebuffer();
    graphics_present();
    uint16_t* post_present_ptr = graphics_get_framebuffer();
    if (pre_present_ptr == post_present_ptr) {
        printf("Presenting did not switch buffers\n");
        return 1;
    }
    printf("All tests passed.\n");
    return 0;

}