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
#define SIZE 8
volatile bool break_flag = 0;



void in_it(){                                      // incializace MCU a periferii
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz from internal RC
    init_milis(); // millis using TIM4 - not necessary
    init_tim();
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_IT);
}

void main(void) {
    in_it();

    uint32_t time = 0;

    uint8_t state = 0;
    while (1) {

        switch (state) {
        case 0:                                   //case 0 - 2 full color fill test
            while (break_flag == 0) {
                fill_with_color_hex(0x008000, 64);
                delay_ms(100);
            }
            break_flag = 0;
            state = 1;
            break;
        case 1:
            while (break_flag == 0) {
                fill_with_color_hex(0x000080, 64);
                delay_ms(100);
            }
            state = 2;
            break_flag = 0;
            break;

        case 2:
            while (break_flag == 0) {
                fill_with_color_hex(0x800000, 64);
                delay_ms(100);
            }
            state = 3;
            break_flag = 0;
            break;
        case 3:                                //Color animation
            while (break_flag == 0) {
                color_gradient_corner_effect();
            }
            state = 4;
            break_flag = 0;
            break;

        case 4:

            while (break_flag == 0) {
                cross_animation();              //Animated cross
            }
            state = 5;
            break_flag = 0;
            break;
        case 5:                                             //conways game of life
            while (break_flag == 0) {
                int grid[SIZE][SIZE] = {
                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0},
                    {0, 0, 1, 0, 1, 0, 0, 0}, {0, 1, 0, 0, 0, 0, 0, 0},
                    {0, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
                int grid2[SIZE][SIZE] = {
                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0},
                    {0, 0, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
                int grid3[SIZE][SIZE] = {
                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0},
                    {0, 0, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
                uint32_t array[64] = {0};

                for (uint8_t i = 0; i < 20; i++) {
                    grid_to_1d_array(grid2, array, 0x008000, 0x000080);
                    let_that_sink_in(array);
                    update_grid(grid2);
                    delay_ms(250);
                    if(break_flag){
                        break;
                    }
                }

            }
            state = 0;
            break_flag = 0;
            break;
        }
    }
}


INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7)    // handles change of cases
{
  break_flag = 1;
}


















