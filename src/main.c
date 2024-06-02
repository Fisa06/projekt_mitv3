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
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_IT);
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

bool is_btn_pressed_event(void) // returns true if button one is pressed but not when it is hold
{
    static bool last_state = false;
    bool state = GPIO_ReadInputPin(BTN_PORT, BTN_PIN) == RESET;
    bool event = state && !last_state;
    last_state = state;
    return event;
}
void main(void) {
    in_it();
#define SIZE 8
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
    uint32_t time = 0;

    uint8_t state = 0;
    while (1) {

        if (1) {
            state++;
            time = milis();
            if (state > 5) {
                state = 0;
            }
        }
        switch(state){
        case 0:
                fill_with_color_hex(0x008000, 64);
                break;
        case 1:
                fill_with_color_hex(0x000080, 64);
                break;

        case 2:
                fill_with_color_hex(0x800000, 64);
                break;
        case 3:
                color_gradient_corner_effect();
                break;
        case 4:
            for(uint8_t i = 0; i < 64; i++) {
                cross_animation();
            }
            break;
case 5:
    uint32_t array[64] = {0};
    for (uint8_t i = 0; i < 20; i++) {
        grid_to_1d_array(grid2, array, 0x008000, 0x000080);
        let_that_sink_in(array);
        update_grid(grid2);
        delay_ms(250);
    }

    break;
        }



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



















