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


void test(uint8_t* data, uint16_t length);
void in_it(){
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz from internal RC
    init_milis(); // millis using TIM4 - not necessary
    init_tim();
}
void main(void){
    uint8_t lol[64] = {0};
    for (uint8_t i = 1; i < 64; i= i+3) {

        lol[i] = 1;
    }
    uint32_t color = 0xff00ff;
    uint32_t out[64] = {0};
    for(uint8_t i = 0; i < 64; i++){
        if(lol[i]){
            out[i] = color;
        }
    }

    uint8_t lol2[64] = {0};
    for (uint8_t i = 0; i < 64; i= i+3) {
        lol2[i] = 1;
    }
    uint32_t color2 = 0x00ff00;
    uint32_t out2[64] = {0};
    for(uint8_t i = 0; i < 64; i++){
        if(lol2[i]){
            out2[i] = color2;
        }
    }
    uint8_t lol3[64] = {0};
    for (uint8_t i = 2; i < 64; i= i+3) {
        lol3[i] = 1;
    }
    uint32_t color3 = 0x00ff0f;
    uint32_t out3[64] = {0};
    for(uint8_t i = 0; i < 64; i++){
        if(lol3[i]){
            out3[i] = color3;
        }
    }
    while(1){
    let_that_sink_in(out);
    delay_ms(75);
    let_that_sink_in(out2);
    delay_ms(75);
    let_that_sink_in(out3);
    delay_ms(75);
        //let_that_sink_in(lol);
        //fill_with_color_hex(0xB6FF00,64);
        //fill_with_color(32,128,32,64);
        //test(out2,sizeof(out2));

        //test(out2,sizeof(out2));
        //delay_ms(15);
        //test(colorsos,sizeof(colorsos));
       // delay_ms(40);

}}
















