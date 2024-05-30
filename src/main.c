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


void test(uint8_t* data, uint16_t length);
void generateGradient(uint8_t startG, uint8_t startR, uint8_t startB,uint8_t endG, uint8_t endR, uint8_t endB, uint32_t gradient[64]);
void in_it(){
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz from internal RC
    init_milis(); // millis using TIM4 - not necessary
    init_tim();
}
void main(void){
    in_it();

    uint32_t grid[64] = {0xff0000,0xff000f, 0xda0024, 0xb60048,
                         0x91006d, 0x6d0091, 0x4800b6,
                         0x2400da, 0x0000ff, 0xda0024,
                         0xda0024, 0xb60048, 0x91006d,
                         0x6d0091, 0x4800b6, 0x2400da,
                         0x0000ff, 0xb60048, 0xb60048,
                         0xb60048, 0x91006d, 0x6d0091,
                         0x4800b6, 0x2400da, 0x0000ff,
                         0x91006d, 0x91006d, 0x91006d,
                         0x91006d, 0x6d0091, 0x4800b6,
                         0x2400da, 0x0000ff, 0x6d0091,
                         0x6d0091, 0x6d0091, 0x6d0091,
                         0x6d0091, 0x4800b6, 0x2400da,
                         0x0000ff, 0x4800b6, 0x4800b6,
                         0x4800b6, 0x4800b6, 0x4800b6,
                         0x4800b6, 0x2400da, 0x0000ff,
                         0x2400da, 0x2400da, 0x2400da,
                         0x2400da, 0x2400da, 0x2400da,
                         0x2400da, 0x0000ff, 0x0000ff,
                         0x0000ff, 0x0000ff, 0x0000ff,
                         0x0000ff, 0x0000ff, 0x0000ff};

    uint32_t grid2[64] = {0x00ff00, 0x00da24, 0x00b648, 0x00916d, 0x006d91, 0x0048b6, 0x0024da, 0x0000ff, 0x00da24, 0x00da24, 0x00b648, 0x00916d, 0x006d91, 0x0048b6, 0x0024da, 0x0000ff, 0x00b648, 0x00b648, 0x00b648, 0x00916d, 0x006d91, 0x0048b6, 0x0024da, 0x0000ff, 0x00916d, 0x00916d, 0x00916d, 0x00916d, 0x006d91, 0x0048b6, 0x0024da, 0x0000ff, 0x006d91, 0x006d91, 0x006d91, 0x006d91, 0x006d91, 0x0048b6, 0x0024da, 0x0000ff, 0x0048b6, 0x0048b6, 0x0048b6, 0x0048b6, 0x0048b6, 0x0048b6, 0x0024da, 0x0000ff, 0x0024da, 0x0024da, 0x0024da, 0x0024da, 0x0024da, 0x0024da, 0x0024da, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff,0x0000ff};

    uint32_t grid3[64] = {0x0000ff, 0x00ff00, 0x001fff, 0x002f1e, 0x003e2d, 0x004d3c, 0x005c4b, 0x006b5a, 0x00ff00, 0x00ff00, 0x001fff, 0x002f1e, 0x003e2d, 0x004d3c, 0x005c4b, 0x006b5a, 0x001fff, 0x001fff, 0x001fff, 0x002f1e, 0x003e2d, 0x004d3c, 0x005c4b, 0x006b5a, 0x0000ff, 0x002f1e, 0x002f1e, 0x002f1e, 0x003e2d, 0x004d3c, 0x005c4b, 0x006b5a, 0x00ff00, 0x003e2d, 0x003e2d, 0x003e2d, 0x003e2d, 0x004d3c, 0x005c4b, 0x006b5a, 0x004d3c, 0x004d3c, 0x004d3c, 0x004d3c, 0x004d3c, 0x004d3c, 0x005c4b, 0x006b5a, 0x005c4b, 0x005c4b, 0x005c4b, 0x005c4b, 0x005c4b, 0x005c4b, 0x005c4b, 0x006b5a, 0x006b5a, 0x006b5a, 0x006b5a, 0x006b5a, 0x006b5a, 0x006b5a, 0x006b5a, 0x006b5a
    };

    uint32_t values[64] = {
                                0x00ff00, 0x00da24, 0x00b648, 0x00916d, 0x006d91, 0x0048b6, 0x0024da, 0x0000ff,
                                0x00da24, 0x00da24, 0x00b648, 0x00916d, 0x006d91, 0x0048b6, 0x0024da, 0x0000ff,
                                0x00b648, 0x00b648, 0x00b648, 0x00916d, 0x006d91, 0x0048b6, 0x0024da, 0x0000ff,
                                0x00916d, 0x00916d, 0x00916d, 0x00916d, 0x006d91, 0x0048b6, 0x0024da, 0x0000ff,
                                0x006d91, 0x006d91, 0x006d91, 0x006d91, 0x006d91, 0x0048b6, 0x0024da, 0x0000ff,
                                0x0048b6, 0x0048b6, 0x0048b6, 0x0048b6, 0x0048b6, 0x0048b6, 0x0024da, 0x0000ff,
                                0x0024da, 0x0024da, 0x0024da, 0x0024da, 0x0024da, 0x0024da, 0x0024da, 0x0000ff,
                                0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff, 0x0000ff

    };


    let_that_sink_in(values);
    while(1){
    //let_that_sink_in(out);
    //delay_ms(1);
    //let_that_sink_in(out2);
    //delay_ms(1);
    //let_that_sink_in(out3);
    //delay_ms(1);
    //color_fill_with_reverse_horizontal();
    //color_fill_with_reverse_vertical();





    }
        //let_that_sink_in(lol);
        //fill_with_color_hex(0xB6FF00,64);
        //fill_with_color(32,128,32,64);
        //test(out2,sizeof(out2));

        //test(out2,sizeof(out2));
        //delay_ms(15);
        //test(colorsos,sizeof(colorsos));
       // delay_ms(40);

}




//-----------------------------------------------------------------


uint32_t hexToGRB(uint32_t rgb) {

    uint8_t green = (rgb >> 7) & 0xFF;
    uint8_t red = (rgb >> 15) & 0xFF;
    uint8_t blue = rgb & 0xFF;
    return (green << 15) | (red << 7) | blue;
}

// Function to generate the gradient colors
void generateGradient(uint8_t startG, uint8_t startR, uint8_t startB,
                      uint8_t endG, uint8_t endR, uint8_t endB, uint32_t gradient[64]) {
    for (uint8_t i = 0; i < 64; i++) {
        uint8_t intermediateG = (uint8_t)(startG + ((float)i / 63) * (endG - startG));
        uint8_t intermediateR = (uint8_t)(startR + ((float)i / 63) * (endR - startR));
        uint8_t intermediateB = (uint8_t)(startB + ((float)i / 63) * (endB - startB));

        gradient[i] = (intermediateG << 16) | (intermediateR << 8) | intermediateB;
    }
}
















