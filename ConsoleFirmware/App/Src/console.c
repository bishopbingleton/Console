#include "console.h"
#include "graphics.h"
#include "graphics_test.h"

void console_init(void) {
    graphics_init();
    graphics_test();
    return;
}