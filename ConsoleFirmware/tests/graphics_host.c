#include <stdint.h>
#include <stdbool.h>


#define GRAPHICS_WIDTH 240
#define GRAPHICS_HEIGHT 160
static void graphics_clear_buffer(uint16_t* ptr, uint16_t fill_color);
uint16_t FRAME_BUFFER_A[GRAPHICS_HEIGHT][GRAPHICS_WIDTH];
uint16_t FRAME_BUFFER_B[GRAPHICS_HEIGHT][GRAPHICS_WIDTH];
static uint16_t *drawing_buffer = &FRAME_BUFFER_A[0][0];
static uint16_t *display_buffer  = &FRAME_BUFFER_B[0][0];
const uint16_t G_BLACK = 0x0000;

void graphics_init(void) {
    graphics_clear_buffer(display_buffer, G_BLACK);
    graphics_clear_buffer(drawing_buffer, G_BLACK);
}

uint16_t* graphics_get_framebuffer(void) {
    return drawing_buffer;
}

//Supposed to switch display -> switch the two buffer pointers,
//(todo) update LCD through LTDC later
void graphics_present(void) {
    uint16_t* temp_ptr = drawing_buffer;
    drawing_buffer = display_buffer;
    display_buffer = temp_ptr;
}

//Sets the entirety of the drawing buffer to one color
//(todo) optimize process by using DMA2D later
void graphics_clear(uint16_t fill_color) {
    graphics_clear_buffer(drawing_buffer, fill_color);
}


//Sets the entirety of a specified buffer to one color
//(todo) optimize process by using DMA2D later
static void graphics_clear_buffer(uint16_t* ptr, uint16_t fill_color) {
    for (uint16_t i = 0; i < GRAPHICS_HEIGHT; i++) {
        for (uint16_t j = 0; j < GRAPHICS_WIDTH; j++) {
            ptr[i * GRAPHICS_WIDTH + j] = fill_color;
        }
    }
}


uint16_t graphics_get_pixel(uint16_t x, uint16_t y) {
    if (x >= GRAPHICS_WIDTH || y >= GRAPHICS_HEIGHT) {
        return G_BLACK;
    }
    
    return drawing_buffer[y * GRAPHICS_WIDTH + x];
}

bool graphics_draw_pixel(uint16_t x, uint16_t y, uint16_t color) {
    if (x >= GRAPHICS_WIDTH || y >= GRAPHICS_HEIGHT) {
        return false;
    }
    drawing_buffer[y * GRAPHICS_WIDTH + x] = color;
    return true;
}



bool graphics_fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
    uint32_t x_lim = x + width;
    uint32_t y_lim = y + height;
    if (x >= GRAPHICS_WIDTH || y >= GRAPHICS_HEIGHT
      || width == 0 || height == 0) {
        return false;
    }
    if (x_lim > GRAPHICS_WIDTH) {
        x_lim = GRAPHICS_WIDTH;
    }
    if (y_lim > GRAPHICS_HEIGHT) {
        y_lim = GRAPHICS_HEIGHT;
    }
    for (uint16_t i = y; i < y_lim; i++) {
        for (uint16_t j = x; j < x_lim; j++) {
            drawing_buffer[i * GRAPHICS_WIDTH + j] = color;
        }
    }
    return true;

}