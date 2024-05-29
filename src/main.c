// B) STM8 -> WS2812B (STM8S208, 16MHz internal RC)
// test driver for WS2812B using TIM1 (CH1 used as data ouput, using One-Pulse mode)
// edit to use another channel
#include "stm8s.h"
#include "stm8s_it.h"
#include "milis.h"
#include "delay.h"
#include "main.h"
#include "stdio.h"
#define L_PULSE 6 // 6*1/16MHz = 6*62.5 = 375ns (~400ns)
#define H_PULSE 12 // 12*1/16MHz = 12*62.5 = 750ns (~800ns)

void test(uint8_t* data, uint16_t length);
void test2(uint32_t* data, uint16_t length);
void fill_with_color(uint8_t r, uint16_t g, uint8_t b, uint8_t n_leds);
uint32_t merge(uint8_t r, uint8_t g, uint8_t b);
void init_tim(void);
void fill_with_color_hex(uint32_t hex, uint8_t n_leds);
void let_that_sink_in(uint32_t data[64]);
uint8_t colors[64*3]={
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00, // G
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0xff,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0xff,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0xff,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0xff,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,
    0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0xff,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0xff,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0xff,0x00, // B






};

uint8_t colorsos[64*3]={
    0xff,0x00,0x00, // B
    0x00,0xff,0x00, // R
    0xff,0x00,0x00, // G
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0xff,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0xff,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0xff,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0xff,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0xff,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0xff,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0x00,0x00, // B
    0xff,0x00,0x00, // R
    0xff,0x00,0x00,
    0xff,0xff,0x00, // B
    };

uint8_t colors2[64*3]={
    0xff,0x00,0x00, // B
    0x00,0xff,0x00, // R
     // B
    };

uint32_t colorss[64]={
    0xff0000, // R
    0x00ff00, // G
    0x0000ff, // B
};



void main(void){
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz from internal RC
    init_milis(); // millis using TIM4 - not necessary
    init_tim();
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


void init_tim(void){
    GPIO_Init(GPIOC,GPIO_PIN_1,GPIO_MODE_OUT_PP_LOW_FAST); // PC1 (TIM1_CH1)
    TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, 15, 0); // Upcounting, prescaler 0, dont care period/ARR value
    // OC1 as output with Polarity High in PWM2 mode (OC1N not used)
    TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
                 1, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
                 TIM1_OCNIDLESTATE_RESET);
    TIM1_CtrlPWMOutputs(ENABLE); // Timer output global enable
    TIM1_Select
        OnePulseMode(TIM1_OPMODE_SINGLE); // Selecting One Pulse Mode
}

void test(uint8_t* data, uint16_t length){
    uint8_t mask;
    disableInterrupts(); // can be omitted if interrupts do not take more then about ~25us
    while(length){   // for all bytes from input array
        length--;
        mask=0b10000000; // for all bits in byte
        while(mask){
            while(TIM1->CR1 & TIM1_CR1_CEN); // wait if timer run (transmitting last bit)
            if(mask & data[length]){ // send pulse with coresponding length ("L" od "H")
                TIM1->ARRL = H_PULSE; // set pulse width for "H" bit
            }else{
                TIM1->ARRL = L_PULSE; // set pulse width for "L" bit
            }
            TIM1->CR1 |= TIM1_CR1_CEN; // Start timer (start single pulse generation)
            mask = mask >> 1;
        }
    }

    enableInterrupts();
}

uint32_t merge(uint8_t r, uint8_t g, uint8_t b){
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}



void fill_with_color(uint8_t r, uint16_t g, uint8_t b, uint8_t n_leds){
    uint32_t data =  merge(r,g,b);
    uint32_t mask;
    disableInterrupts(); // can be omitted if interrupts do not take more then about ~25us
    while(n_leds){   // for all bytes from input array
        n_leds--;
        mask=0b100000000000000000000000; // for all bits in byte
        while(mask){
            while(TIM1->CR1 & TIM1_CR1_CEN); // wait if timer run (transmitting last bit)
            if(mask & data){ // send pulse with coresponding length ("L" od "H")
                TIM1->ARRL = H_PULSE; // set pulse width for "H" bit
            }else{
                TIM1->ARRL = L_PULSE; // set pulse width for "L" bit
            }
            TIM1->CR1 |= TIM1_CR1_CEN; // Start timer (start single pulse generation)
            mask = mask >> 1;
        }
    }

    enableInterrupts();
}



void fill_with_color_hex(uint32_t hex, uint8_t n_leds){
    uint32_t mask;
    disableInterrupts(); // can be omitted if interrupts do not take more then about ~25us
    while(n_leds){   // for all bytes from input array
        n_leds--;
        mask=0b100000000000000000000000; // for all bits in byte
        while(mask){
            while(TIM1->CR1 & TIM1_CR1_CEN); // wait if timer run (transmitting last bit)
            if(mask & hex){ // send pulse with coresponding length ("L" od "H")
                TIM1->ARRL = H_PULSE; // set pulse width for "H" bit
            }else{
                TIM1->ARRL = L_PULSE; // set pulse width for "L" bit
            }
            TIM1->CR1 |= TIM1_CR1_CEN; // Start timer (start single pulse generation)
            mask = mask >> 1;
        }
    }

    enableInterrupts();
}


void let_that_sink_in(uint32_t data[64]){

    uint8_t length = 64;
    uint32_t mask;
    disableInterrupts(); // can be omitted if interrupts do not take more then about ~25us
    while(length){   // for all bytes from input array
        length--;
        mask=0b100000000000000000000000; // for all bits in byte
        while(mask){
            while(TIM1->CR1 & TIM1_CR1_CEN); // wait if timer run (transmitting last bit)
            if(mask & data[length]){ // send pulse with coresponding length ("L" od "H")
                TIM1->ARRL = H_PULSE; // set pulse width for "H" bit
            }else{
                TIM1->ARRL = L_PULSE; // set pulse width for "L" bit
            }
            TIM1->CR1 |= TIM1_CR1_CEN; // Start timer (start single pulse generation)
            mask = mask >> 1;
        }
    }

    enableInterrupts();
}










