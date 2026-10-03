#include "graphics_test.h"


bool graphics_test_passed;

void graphics_test(void) {
    if (!graphics_draw_pixel(0, 0, 0x1111) || graphics_get_pixel(0, 0) != 0x1111) {
        graphics_test_passed = false;
        return;
    }
    if (!graphics_draw_pixel(239, 159, 0x1111) || graphics_get_pixel(239, 159) != 0x1111) {
        graphics_test_passed = false;
        return;
    }
    if (!graphics_draw_pixel(120, 80, 0x1111) || graphics_get_pixel(120, 80) != 0x1111) {
        graphics_test_passed = false;
        return;
    }
    if (graphics_draw_pixel(240, 160, 0x1111)) {
        graphics_test_passed = false;
        return;
    }
    graphics_test_passed = true;
    return;

}