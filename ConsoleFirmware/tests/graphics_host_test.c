#include "graphics_host.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
    graphics_init();
    graphics_clear(0x0000);
    graphics_draw_game_rect(10, 10, 20, 15, 0x1111);
    if (graphics_get_game_pixel(10, 10) != 0x1111
     || graphics_get_game_pixel(29, 10) != 0x1111
     || graphics_get_game_pixel(10, 24) != 0x1111
     || graphics_get_game_pixel(29, 24) != 0x1111) {
        printf("Drawing rect outline failed.\n");
        return 1;
    }
    if (graphics_get_game_pixel(11,11) != 0x0000) {
        printf("Drawng rect outline spilled inwards.\n");
        return 1;
    }

    graphics_clear(0x0000);
    graphics_draw_game_rect(200, 100, 40, 60, 0x1111);
    if (graphics_get_game_pixel(200, 100) != 0x1111
     || graphics_get_game_pixel(239, 100) != 0x1111
     || graphics_get_game_pixel(200, 159) != 0x1111
     || graphics_get_game_pixel(239, 159) != 0x1111) {
        printf("Drawing rect outline touching edge failed.\n");
        return 1;
    }

    graphics_clear(0x0000);
    graphics_draw_game_rect(200, 100, 41, 61, 0x1111);
    if (graphics_get_game_pixel(200, 100) != 0x1111
     || graphics_get_game_pixel(239, 100) != 0x1111
     || graphics_get_game_pixel(200, 159) != 0x1111
     || graphics_get_game_pixel(239, 159) != 0x0000) {
        printf("Drawing clipping rect outline failed.\n");
        return 1;
    }
    if (graphics_get_game_pixel(220,130) != 0x0000) {
        printf("Drawng rect outline spilled inwards.\n");
        return 1;
    }

    graphics_clear(0x0000);
    graphics_draw_game_rect(200, 100, 41, 60, 0x1111);
    if (graphics_get_game_pixel(200, 100) != 0x1111
     || graphics_get_game_pixel(239, 100) != 0x1111
     || graphics_get_game_pixel(200, 159) != 0x1111
     || graphics_get_game_pixel(239, 159) != 0x1111
     || graphics_get_game_pixel(239, 130) != 0x0000) {
        printf("Drawing clipping rect outline failed.\n");
        return 1;
    }

    graphics_clear(0x0000);
    graphics_draw_game_rect(200, 100, 40, 61, 0x1111);
    if (graphics_get_game_pixel(200, 100) != 0x1111
     || graphics_get_game_pixel(239, 100) != 0x1111
     || graphics_get_game_pixel(200, 159) != 0x1111
     || graphics_get_game_pixel(239, 159) != 0x1111
     || graphics_get_game_pixel(220, 159) != 0x0000) {
        printf("Drawing clipping rect outline failed.\n");
        return 1;
    }

    graphics_clear(0x0000);
    graphics_draw_game_rect(1, 1, 1, 1, 0x1111);
    if (graphics_get_game_pixel(1, 1) != 0x1111
     || graphics_get_game_pixel(2, 2) != 0x0000) {
        printf("Drawing single-px rect outline failed.\n");
        return 1;
    }
    
    if (graphics_draw_game_rect(250, 300, 1, 1, 0x1111) != false) {
        printf("Drawing rect outline accepts invalid out-of-bounds inputs \n");
        return 1;
    }
    
    if (graphics_draw_game_rect(1, 1, 0, 0,0x1111) != false) {
        printf("Drawing rect outline accepts invalid out-of-bounds inputs \n");
        return 1;
    }

    graphics_clear(0x0000);
    printf("All tests passed.\n");
    return 0;
}
// OLD (Primitive graphics tests)
// int main() {
//     // Scaling Tests
//     graphics_init();
//     graphics_draw_game_pixel(0, 0, 0x1111);
//     if (graphics_get_game_pixel(0, 0) != 0x1111) {
//         printf("Drawing game pixel to screen failed.\n");
//         return 1;
//     }
//     if (graphics_get_screen_pixel(0, 0) != 0x1111
//      || graphics_get_screen_pixel(0, 1) != 0x1111
//      || graphics_get_screen_pixel(1, 0) != 0x1111
//      || graphics_get_screen_pixel(1, 1) != 0x1111) {
//         printf("Drawing game pixel to screen failed.\n");
//         return 1;
//     }

//     graphics_clear(0x0000);

//     graphics_draw_game_pixel(239, 159, 0x1111);
//     if (graphics_get_game_pixel(239, 159) != 0x1111) {
//         printf("Drawing game pixel to screen failed.\n");
//         return 1;
//     }
//     if (graphics_get_screen_pixel(478, 318) != 0x1111
//      || graphics_get_screen_pixel(479, 318) != 0x1111
//      || graphics_get_screen_pixel(478, 319) != 0x1111
//      || graphics_get_screen_pixel(479, 319) != 0x1111) {
//         printf("Drawing game pixel to screen failed.\n");
//         return 1;
//     }

//     graphics_fill_game_rect(1, 1, 5, 7, 0x1111);
//     if (graphics_get_screen_pixel(2, 2) != 0x1111
//      || graphics_get_screen_pixel(11, 2) != 0x1111
//      || graphics_get_screen_pixel(2, 15) != 0x1111
//      || graphics_get_screen_pixel(11, 15) != 0x1111) {
//         printf("Drawing game rect to screen failed.\n");
//         return 1;
//     }

//     if (graphics_get_screen_pixel(12, 2) != 0x0000
//      || graphics_get_screen_pixel(2, 16) != 0x0000) {
//         printf("Drawing game rect overflowed boundaries.\n");
//         return 1;
//      } 

//     graphics_present();

//     if (graphics_get_screen_pixel(2, 2) == 0x1111) {
//         printf("Presenting failed to switch buffers.\n");
//         return 1;
//     }

//     graphics_present();

//      if (graphics_get_screen_pixel(2, 2) != 0x1111) {
//         printf("Presenting failed to switch buffers (2).\n");
//         return 1;
//     }

//     graphics_clear(0x0000);

//     // Clipping and Invalid Input Tests;
//     if(graphics_fill_game_rect(0, 0, 0, 10, 0x1111)) {
//         printf("Drawing a rectcangle failed to detect invalid input.\n");
//         return 1;
//     }
//     if(graphics_fill_game_rect(0, 0, 10, 0, 0x1111)) {
//         printf("Drawing a rectcangle failed to detect invalid input.\n");
//         return 1;
//     }
//     if(graphics_fill_game_rect(240, 0, 10, 10, 0x1111)) {
//         printf("Drawing a rectcangle failed to detect invalid input.\n");
//         return 1;
//     }
//     if(graphics_fill_game_rect(0, 160, 10, 10, 0x1111)) {
//         printf("Drawing a rectcangle failed to detect invalid input.\n");
//         return 1;
//     }
//     if(graphics_draw_game_pixel(0, 160, 0x1111)) {
//         printf("Drawing a pixel failed to detect invalid input.\n");
//         return 1;
//     }
//     if(graphics_draw_game_pixel(240, 0, 0x1111)) {
//         printf("Drawing a pixel failed to detect invalid input.\n");
//         return 1;
//     }
//     if(graphics_get_game_pixel(0, 160) != 0x0000) {
//         printf("Getting a pixel failed to detect invalid input.\n");
//         return 1;
//     }
//     if(graphics_get_game_pixel(240, 0) != 0x0000) {
//         printf("Getting a pixel failed to detect invalid input.\n");
//         return 1;
//     }

//     if (!graphics_fill_game_rect(239, 159, 10, 10, 0x1111)) {
//         printf("Mistook valid input for invalid.\n");
//         return 1;
//     }
    
//     if (graphics_get_game_pixel(239, 159) != 0x1111) {
//         printf("Filling a clipped rect failed.\n");
//         return 1;
//     }
//     if (graphics_get_screen_pixel(478, 318) != 0x1111
//      || graphics_get_screen_pixel(479, 318) != 0x1111
//      || graphics_get_screen_pixel(478, 319) != 0x1111
//      || graphics_get_screen_pixel(479, 319) != 0x1111) {
//         printf("Filling a clipped rect failed.\n");
//         return 1;
//     }
//     if (graphics_get_screen_pixel(477, 318) != 0x0000) {
//         printf("Filling a clipped rect went past bounds.\n");
//         return 1;
//     }


//     printf("All tests passed.\n");
//     return 0;

// }

// OLD (pre-bufffer-size-switch tests)
//
// int main() {
//     graphics_init();
//     if (!graphics_draw_pixel(0, 0, 0x1111) || graphics_get_pixel(0, 0) != 0x1111) {
//         printf("Failed to draw pixel at 0, 0 or pixel color post-drawing did not match expectations.\n");
//         return 1;
//     }
//     if (!graphics_draw_pixel(239, 159, 0x1111) || graphics_get_pixel(239, 159) != 0x1111) {
//         printf("Failed to draw pixel at 239, 159 or pixel color post-drawing did not match expectations.\n");
//         return 1;
//     }
//     if (!graphics_draw_pixel(120, 80, 0x1111) || graphics_get_pixel(120, 80) != 0x1111) {
//         printf("Failed to draw pixel at 120, 80 or pixel color post-drawing did not match expectations.\n");
//         return 1;
//     }
//     if (graphics_draw_pixel(240, 160, 0x1111)) {
//         printf("Drew pixel past screen bounds. Error.\n");
//         return 1;
//     }

//     graphics_clear(0x0000);
    
//     if (!graphics_fill_rect(1, 1, 5, 7, 0x1111)) {
//         printf("Invalid rectangle bounds detected on valid input.\n");
//         return 1;
//     }
//     if (graphics_get_pixel(5, 7) != 0x1111) {
//         printf("Rectangle not properly filled.\n");
//         return 1;
//     }
//     if (graphics_get_pixel(6, 8) == 0x1111) {
//         printf("Rectangle over-filled.\n");
//         return 1;
//     }

//     graphics_clear(0x0000);
//     if (!graphics_fill_rect(230, 150, 10, 10, 0x1111)) {
//         printf("Invalid rectangle bounds detected on valid input.\n");
//         return 1;
//     }
//     if (graphics_get_pixel(239, 159) != 0x1111) {
//         printf("Rectangle not properly filled.\n");
//         return 1;
//     }

//     graphics_clear(0x0000);
    
//     if (!graphics_fill_rect(231, 151, 10, 10, 0x1111)) {
//         printf("Invalid rectangle bounds detected on valid input.\n");
//         return 1;
//     }
//     if (graphics_get_pixel(239, 159) != 0x1111) {
//         printf("Rectangle not properly filled.\n");
//         return 1;
//     }

//     graphics_clear(0x0000);
//     if (graphics_fill_rect(231, 151, 10, 0, 0x1111)) {
//         printf("Rect of 0 width and height should be invalid.\n");
//         return 1;
//     }
//     if (graphics_fill_rect(231, 151, 0, 10, 0x1111)) {
//         printf("Rect of 0 width and height should be invalid.\n");
//         return 1;
//     }
//     if (graphics_fill_rect(240, 159, 1, 1, 0x1111)) {
//         printf("Out of bound x or y should not be valid inputs\n");
//         return 1;
//     }
//     if (graphics_fill_rect(239, 160, 1, 1, 0x1111)) {
//         printf("Out of bound x or y should not be valid inputs\n");
//         return 1;
//     }

//     graphics_clear(0x0000);


//     uint16_t* pre_present_ptr = graphics_get_framebuffer();
//     graphics_present();
//     uint16_t* post_present_ptr = graphics_get_framebuffer();
//     if (pre_present_ptr == post_present_ptr) {
//         printf("Presenting did not switch buffers\n");
//         return 1;
//     }
//     printf("All tests passed.\n");
//     return 0;

// }