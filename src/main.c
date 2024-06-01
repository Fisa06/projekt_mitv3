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

void main(void){
    in_it();


    //let_that_sink_in(values);


    //let_that_sink_in(out);
    //delay_ms(1);
    //let_that_sink_in(out2);
    //delay_ms(1);
    //let_that_sink_in(out3);
    //delay_ms(1);
    //color_fill_with_reverse_horizontal();
    //color_fill_with_reverse_vertical();

    //fill_with_color_hex(0xffffff, 64);
#define color 0x008000
#define color_bg 0x000040
#define SIZE 8
    while(1){

        int grid[SIZE][SIZE] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
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

        uint32_t array[64];

        for (uint8_t i = 0; i < 20; i++) {
            grid_to_1d_array(grid2, array, color, color_bg);
            let_that_sink_in(array);
            update_grid(grid2);
            delay_ms(250);
        }


    }
        }







        //let_that_sink_in(lol);
        //fill_with_color_hex(0xB6FF00,64);
        //fill_with_color(32,128,32,64);
        //test(out2,sizeof(out2));

        //test(out2,sizeof(out2));
        //delay_ms(15);
        //test(colorsos,sizeof(colorsos));
       // delay_ms(40);






//-----------------------------------------------------------------



















