// B) STM8 -> WS2812B (STM8S208, 16MHz internal RC)
// test driver for WS2812B using TIM1 (CH1 used as data ouput, using One-Pulse mode)
// edit to use another channel
#include "stm8s.h"
#include "stm8s_it.h"
#include "milis.h"
#include "delay.h"
#include "main.h"
#include "stdio.h"
#include "neopixel.h"
#include "animations.h"
#include "conway.h"

void draw_frame(int frame[8][8], uint32_t color3, uint32_t color2, uint32_t color1){
    uint32_t empty_list[64] = {0};
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            uint8_t index = i * 8 + j;
            if (frame[i][j] == 3) {
                empty_list[index] = color3;
            } else if (frame[i][j] == 2) {
                empty_list[index] = color2;
            } else if (frame[i][j] ==1) {
                empty_list[index] = color1;
            }
            else{
                empty_list[index] = 0x000000;
    let_that_sink_in(empty_list);
}}}}

void cross_animation(void){
#define SIZE 8
#define color3 0x400000
#define color2 0x6000000
#define color1 0x8000000
#define speed_ms 100
#define color_bg 0x000002
    int grid[SIZE][SIZE] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int grid2[SIZE][SIZE] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int grid3[SIZE][SIZE] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };




    int frame1[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 1, 2},
        {2, 1, 0, 0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    int frame2[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {2, 3, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 3, 2},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int frame3[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 2, 3, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 2, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int frame4[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 2, 3, 0, 0, 0, 0},
        {0, 0, 0, 0, 3, 2, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int frame5[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 3, 0, 0, 0, 0},
        {0, 0, 1, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 1, 0, 0},
        {0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int frame6[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 3, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int frame7[8][8] = {
        {0, 0, 0, 3, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 0, 0}
    };
    int frame8[8][8] = {
        {0, 0, 0, 2, 3, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 3, 2, 0, 0, 0}
    };
    int frame9[8][8] = {
        {0, 0, 0, 1, 2, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 3, 0, 0, 0, 0},
        {0, 0, 0, 2, 1, 0, 0, 0}
    };
    int frame10[8][8] = {
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 3, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0}
    };
    int frame11[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 3, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int frame12[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 2, 3, 0, 0},
        {0, 0, 3, 2, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int frame13[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 2, 3, 0},
        {0, 3, 2, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int frame14[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 2, 3},
        {3, 2, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    draw_frame(frame1, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame2, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame3, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame4, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame5, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame6, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame7, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame8, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame9, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame10, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame11, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame12, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame13, color3, color2, color1);
        delay_ms(speed_ms);
        draw_frame(frame14, color3, color2, color1);
        delay_ms(speed_ms);

}







void in_it(){
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz from internal RC
    init_milis(); // millis using TIM4 - not necessary
    init_tim();
}

void hihi(void){
    uint32_t grid1[64] = {0};
    uint32_t result[64];
    for(uint8_t i = 1; i < 128; i+=2){
        // Example usage
        grid1[0] = _merge(0,0,i);  // Top-left corner, green
        grid1[63] = 0x008000; // Bottom-right corner, blue

        generate_diagonal_gradient(grid1, result);
        let_that_sink_in(result);
        delay_ms(25);}
    for(uint8_t i = 0; i < 128; i+=2){
        // Example usage
        grid1[0] = _merge(0,0,(127-i));  // Top-left corner, green
        grid1[63] = 0x008000; // Bottom-right corner, blue

        generate_diagonal_gradient(grid1, result);
        let_that_sink_in(result);
        delay_ms(25);
    }
    for(uint8_t i = 0; i < 128; i+=2){
        // Example usage
        grid1[0] = _merge(0,127,0);  // Top-left corner, green
        grid1[63] = _merge(0,0,(127-i)); // Bottom-right corner, blue

        generate_diagonal_gradient(grid1, result);
        let_that_sink_in(result);
        delay_ms(25);
    }

    for(uint8_t i = 1; i < 128; i+=2){
        // Example usage
        grid1[0] = _merge(0,0,127);  // Top-left corner, green
        grid1[63] = _merge(0,i,0); // Bottom-right corner, blue

        generate_diagonal_gradient(grid1, result);
        let_that_sink_in(result);
        delay_ms(25);}



    for(uint8_t i = 0; i < 128; i+=2){
        // Example usage
        grid1[0] = _merge(0,0,(127-i));  // Top-left corner, green
        grid1[63] = 0x008000; // Bottom-right corner, blue

        generate_diagonal_gradient(grid1, result);
        let_that_sink_in(result);
        delay_ms(25);

    }
    for(uint8_t i = 1; i < 128; i+=2){
        // Example usage
        grid1[0] = _merge(0,0,i);  // Top-left corner, green
        grid1[63] = 0x008000; // Bottom-right corner, blue

        generate_diagonal_gradient(grid1, result);
        let_that_sink_in(result);
        delay_ms(25);}

}

void main(void) {
    in_it();

    // let_that_sink_in(values);

    // let_that_sink_in(out);
    // delay_ms(1);
    // let_that_sink_in(out2);
    // delay_ms(1);
    // let_that_sink_in(out3);
    // delay_ms(1);
    // color_fill_with_reverse_horizontal();
    // color_fill_with_reverse_vertical();

    // fill_with_color_hex(0xffffff, 64);



    while (1) {
        color_gradient_corner_effect();
       //cross_animation();
    }
}
    /*













        for (uint8_t i = 0; i < 20; i++) {
            grid_to_1d_array(grid, array, color, color_bg);
            let_that_sink_in(array);
            update_grid(grid);
            delay_ms(250);



*/





//-----------------------------------------------------------------



















