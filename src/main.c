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
void xlol(void);
void send(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]);
void xloll(void);
void send2(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]);
void reverseSubArray(uint32_t *array, uint8_t start, uint8_t end);
void reverseEverySecondRow(uint32_t *array);
void transposeMatrix(uint32_t *array);
void send3(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]);
void xlolll(void);
void send22(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]);



void in_it(){
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz from internal RC
    init_milis(); // millis using TIM4 - not necessary
    init_tim();
}
void main(void){
    in_it();
    uint8_t lol[64] = {0};
    for (uint8_t i = 1; i < 64; i= i+3) {

        lol[i] = 1;
    }
    uint32_t color = 0x400040;
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
    uint32_t color2 = 0x004000;
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
    uint32_t color3 = 0x0040f;
    uint32_t out3[64] = {0};
    for(uint8_t i = 0; i < 64; i++){
        if(lol3[i]){
            out3[i] = color3;
        }
    }
    while(1){
    //let_that_sink_in(out);
    //delay_ms(1);
    //let_that_sink_in(out2);
    //delay_ms(1);
    //let_that_sink_in(out3);
    //delay_ms(1);
    xloll();
    xlolll();

        //let_that_sink_in(lol);
        //fill_with_color_hex(0xB6FF00,64);
        //fill_with_color(32,128,32,64);
        //test(out2,sizeof(out2));

        //test(out2,sizeof(out2));
        //delay_ms(15);
        //test(colorsos,sizeof(colorsos));
       // delay_ms(40);

}}





void xlol(void) {
    uint8_t r_array[64] = {0};
    uint8_t g_array[64] = {0};
    uint8_t b_array[64] = {0};

    uint8_t base_color[3] = {0, 0, 125};

    for (uint8_t m = 0; m < 64; m++) {
        for (uint8_t i = 0; i < 64 - m; i++) {
            // flush
            for (uint8_t j = 0; j < 64; j++) {
                r_array[j] = 0;
                g_array[j] = 0;
                b_array[j] = 0;
            }

            // set
            for (uint8_t z = 0; z < m; z++) {
                r_array[63 - z] = base_color[0];
                g_array[63 - z] = base_color[1];
                b_array[63 - z] = base_color[2];
            }

            r_array[i] = base_color[0];
            g_array[i] = base_color[1];
            b_array[i] = base_color[2];

            // shading
            for (uint8_t n = 1; n < 5; n++) {
                if (i - n >= 0) {
                    r_array[i - n] = base_color[0] / 5 * (5 - n);
                    g_array[i - n] = base_color[1] / 5 * (5 - n);
                    b_array[i - n] = base_color[2] / 5 * (5 - n);
                }
            }

            send(r_array, g_array, b_array);
        }

        // end shade
        for (uint8_t i = 1; i < 5; i++) {
            if ((63 - m) - (5 - i) >= 0) {
                r_array[(63 - m) - (5 - i)] = 0;
                g_array[(63 - m) - (5 - i)] = 0;
                b_array[(63 - m) - (5 - i)] = 0;
            }

            send(r_array, g_array, b_array);
        }
    }

    // blur out
    for (uint8_t i = 1; i < 15; i++) {
        delay_ms(5);
        for (uint8_t j = 0; j < 64; j++) {
            r_array[j] = base_color[0] / i;
            g_array[j] = base_color[1] / i;
            b_array[j] = base_color[2] / i;

        }

        send(r_array, g_array, b_array);
    }

}



void xloll(void) {
    uint8_t r_array[64] = {0};
    uint8_t g_array[64] = {0};
    uint8_t b_array[64] = {0};

    uint8_t base_color[3] = {0, 0, 0x04};

    for (uint8_t m = 0; m < 64; m++) {
        for (uint8_t i = 0; i < 64 - m; i++) {
            // flush
            for (uint8_t j = 0; j < 64; j++) {
                r_array[j] = 0;
                g_array[j] = 0x04;
                b_array[j] = 0;
            }

            // set
            for (uint8_t z = 0; z < m; z++) {
                r_array[63 - z] = base_color[0];
                g_array[63 - z] = base_color[1];
                b_array[63 - z] = base_color[2];
            }

            r_array[i] = base_color[0];
            g_array[i] = base_color[1];
            b_array[i] = base_color[2];

            // shading
            for (uint8_t n = 1; n < 5; n++) {
                if (i - n >= 0) {
                    r_array[i - n] = base_color[0] / 5 * (5 - n);
                    g_array[i - n] = base_color[1] / 5 * (5 - n);
                    b_array[i - n] = base_color[2] / 5 * (5 - n);
                }
            }

            send2(r_array, g_array, b_array);
        }

        // end shade
        for (uint8_t i = 1; i < 5; i++) {
            if ((63 - m) - (5 - i) >= 0) {
                r_array[(63 - m) - (5 - i)] = 0;
                g_array[(63 - m) - (5 - i)] = 0;
                b_array[(63 - m) - (5 - i)] = 0;
            }

            send22(r_array, g_array, b_array);
        }
    }

    // blur out
    for (uint8_t i = 1; i < 15; i++) {
        delay_ms(5);
        for (uint8_t j = 0; j < 64; j++) {
            r_array[j] = base_color[0] / i;
            g_array[j] = base_color[1] / i;
            b_array[j] = base_color[2] / i;

        }

        send2(r_array, g_array, b_array);
    }

}


void xlolll(void) {
    uint8_t r_array[64] = {0};
    uint8_t g_array[64] = {0};
    uint8_t b_array[64] = {0};

    uint8_t base_color[3] = {0, 0x04,0 };

    for (uint8_t m = 0; m < 64; m++) {
        for (uint8_t i = 0; i < 64 - m; i++) {
            // flush
            for (uint8_t j = 0; j < 64; j++) {
                r_array[j] = 0;
                g_array[j] = 0;
                b_array[j] = 0x04;
            }

            // set
            for (uint8_t z = 0; z < m; z++) {
                r_array[63 - z] = base_color[0];
                g_array[63 - z] = base_color[1];
                b_array[63 - z] = base_color[2];
            }

            r_array[i] = base_color[0];
            g_array[i] = base_color[1];
            b_array[i] = base_color[2];

            // shading
            for (uint8_t n = 1; n < 5; n++) {
                if (i - n >= 0) {
                    r_array[i - n] = base_color[0] / 5 * (5 - n);
                    g_array[i - n] = base_color[1] / 5 * (5 - n);
                    b_array[i - n] = base_color[2] / 5 * (5 - n);
                }
            }

            send3(r_array, g_array, b_array);
        }

        // end shade
        for (uint8_t i = 1; i < 5; i++) {
            if ((63 - m) - (5 - i) >= 0) {
                r_array[(63 - m) - (5 - i)] = 0;
                g_array[(63 - m) - (5 - i)] = 0;
                b_array[(63 - m) - (5 - i)] = 0;
            }

            send3(r_array, g_array, b_array);
        }
    }
    }


void send(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]) {
    uint32_t data[64];
    for (uint8_t i = 0; i < 64; i++) {
        data[i] = _merge(r_array[i], g_array[i], b_array[i]);
    }

    let_that_sink_in(data);
    //delay_ms(0);
}


void send2(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]) {
    uint32_t data[64];
    for (uint8_t i = 0; i < 64; i++) {
        data[i] = _merge(r_array[i], g_array[i], b_array[i]);
    }
    reverseEverySecondRow(data);

    let_that_sink_in(data);
    //delay_ms(5);
}


void send22(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]) {
    uint32_t data[64];
    for (uint8_t i = 0; i < 64; i++) {
        data[i] = _merge(r_array[i], g_array[i], b_array[i]);
    }

    reverseEverySecondRow(data);
    for (uint8_t i = 0; i < 64; i++) {
        if (data[i] == 0) {
            data[i] = 0x000400;
        }
    }

    let_that_sink_in(data);
    //delay_ms(5);
}


void send3(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]) {
    uint32_t data[64];
    for (uint8_t i = 0; i < 64; i++) {
        data[i] = _merge(r_array[i], g_array[i], b_array[i]);
    }
    transposeMatrix(data);

    let_that_sink_in(data);
    //delay_ms(15);
}


void reverseSubArray(uint32_t *array, uint8_t start, uint8_t end) {
    uint32_t temp;
    while (start < end) {
        temp = array[start];
        array[start] = array[end];
        array[end] = temp;
        start++;
        end--;
    }
}

void reverseEverySecondRow(uint32_t *array) {

    for (uint8_t i = 1; i < 8; i += 2) {
        reverseSubArray(array, i * 8, (i * 8) + 7);
    }
}

void transposeMatrix(uint32_t *array) {

    uint32_t temp;
    for (uint8_t i = 0; i < 8; ++i) {
        for (uint8_t j = i + 1; j < 8; ++j) {
            // Swap array[i][j] with array[j][i]
            temp = array[i * 8 + j];
            array[i * 8 + j] = array[j * 8 + i];
            array[j * 8 + i] = temp;
        }
    }
}














