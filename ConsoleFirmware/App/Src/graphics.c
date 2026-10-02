#include "graphics.h"
/*
    Game Res: 240x160 px
    RGB565 (16bits)
        2 bytes/px
    --------------------
    1 Framebuffer: 76,800 bytes
    Double buffering: 153,600 bytes

*/

// Frame Buffer Declarations
// __attribute__ is GNU compiler syntax, tells us to align the starting address of each buffer to
// 32 bytes, and put the memory in a specific section named .framebuffer which we will then define
// in the linker script
uint16_t FRAME_BUFFER_A[240][160] __attribute__((section(".framebuffer"), aligned(32)));
uint16_t FRAME_BUFFER_B[240][160] __attribute__((section(".framebuffer"), aligned(32)));

void graphics_init(void) {
    return;
}

uint16_t* graphics_get_framebuffer() {
    uint16_t* ptr = NULL;
    return ptr;
}

void graphics_clear(uint16_t fill_color) {
    
}