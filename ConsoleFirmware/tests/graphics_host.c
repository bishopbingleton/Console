#include <stdint.h>
#include <stdbool.h>


#define GRAPHICS_WIDTH 240 // Game graphics width
#define GRAPHICS_HEIGHT 160 // Game graphics height
#define LCD_WIDTH 480 // Display graphics width
#define LCD_HEIGHT 320 // Display graphics height
static void graphics_clear_buffer(uint16_t* ptr, uint16_t fill_color);
uint16_t FRAME_BUFFER_A[LCD_HEIGHT][LCD_WIDTH];
uint16_t FRAME_BUFFER_B[LCD_HEIGHT][LCD_WIDTH];
static uint16_t *drawing_buffer = &FRAME_BUFFER_A[0][0];
static uint16_t *display_buffer  = &FRAME_BUFFER_B[0][0];
const uint16_t G_BLACK = 0x0000;

void graphics_init(void) {
    graphics_clear_buffer(display_buffer, G_BLACK);
    graphics_clear_buffer(drawing_buffer, G_BLACK);
}

// uint16_t* graphics_get_framebuffer(void) {
//     return drawing_buffer;
// }

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
    for (uint16_t i = 0; i < LCD_HEIGHT; i++) {
        for (uint16_t j = 0; j < LCD_WIDTH; j++) {
            ptr[i * LCD_WIDTH + j] = fill_color;
        }
    }
}


uint16_t graphics_get_screen_pixel(uint16_t x, uint16_t y) {
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT) {
        return G_BLACK;
    }
    
    return drawing_buffer[y * LCD_WIDTH + x];
}

uint16_t graphics_get_game_pixel(uint16_t x, uint16_t y) {
    if (x >= GRAPHICS_WIDTH || y >= GRAPHICS_HEIGHT) {
        return G_BLACK;
    }
    
    return drawing_buffer[y * LCD_WIDTH * 2 + x * 2];
}

bool graphics_draw_game_pixel(uint16_t x, uint16_t y, uint16_t color) {
    if (x >= GRAPHICS_WIDTH || y >= GRAPHICS_HEIGHT) {
        return false;
    }
    drawing_buffer[2 * y * LCD_WIDTH + x * 2] = color;
    drawing_buffer[2 * y * LCD_WIDTH + x * 2 + 1] = color;
    drawing_buffer[(2 * y + 1) * LCD_WIDTH + x * 2] = color;
    drawing_buffer[(2 * y + 1) * LCD_WIDTH + x * 2 + 1] = color;
    return true;
}

bool graphics_fill_game_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
    if (x >= GRAPHICS_WIDTH || y >= GRAPHICS_HEIGHT
      || width == 0 || height == 0) {
        return false;
    }
    uint32_t x_lim = x + width;
    uint32_t y_lim = y + height;
    x_lim *= 2;
    y_lim *= 2;
    if (x_lim > LCD_WIDTH) {
        x_lim = LCD_WIDTH;
    }
    if (y_lim > LCD_HEIGHT) {
        y_lim = LCD_HEIGHT;
    }
    for (uint16_t i = 2 * y; i < y_lim; i++) {
        for (uint16_t j = 2 * x; j < x_lim; j++) {
            drawing_buffer[i * LCD_WIDTH + j] = color;
        }
    }
    return true;

}


bool graphics_draw_game_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
    if (x >= 240 || y >= 160 || width == 0 || height == 0) {
        return false;
    }
    uint32_t x_bound = x + width;
    uint32_t y_bound = y + height;
    bool draw_right = true;
    bool draw_bot = true;
    if (x_bound > 240) {
        draw_right = false;
        x_bound = 240;
    }
    if (y_bound > 160) {
        draw_bot = false;
        y_bound = 160;
    }

    for (uint32_t i = x; i < x_bound; i++) {
        graphics_draw_game_pixel(i, y, color);
    }

    for (uint32_t i = y; i < y_bound; i++) {
        graphics_draw_game_pixel(x, i, color);
    }
    if (draw_bot) {
        for (uint32_t i = x; i < x_bound; i++) {
            graphics_draw_game_pixel(i, y_bound - 1, color);
        }
    }
    if (draw_right) {
        for (uint32_t i = y; i < y_bound; i++) {
            graphics_draw_game_pixel(x_bound - 1, i, color);
        }
    }
    return true;
}