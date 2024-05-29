#include "animations.h"
#include "stm8s.h"
#include "neopixel.h"
#include "delay.h"
//------------------------------------------
// send functions with different matrix transformations
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
    delay_ms(20);
}


void send3(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]) {
    uint32_t data[64];
    for (uint8_t i = 0; i < 64; i++) {
        data[i] = _merge(r_array[i], g_array[i], b_array[i]);
    }
    transposeMatrix(data);

    let_that_sink_in(data);
    delay_ms(70);
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

//------------------------------------------

// animations
void color_fill_basic_horizontal(void) {
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


void color_fill_with_reverse_horizontal(void) {
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

            send22(r_array, g_array, b_array);
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
        for (uint8_t j = 0; j < 64; j++) {
            r_array[j] = base_color[0] / i;
            g_array[j] = base_color[1] / i;
            b_array[j] = base_color[2] / i;

        }

        send22(r_array, g_array, b_array);
    }

}


void color_fill_with_reverse_vertical(void) {
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

            send22(r_array, g_array, b_array);
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
        // blur out
        for (uint8_t i = 1; i < 15; i++) {
            for (uint8_t j = 0; j < 64; j++) {
                r_array[j] = base_color[0] / i;
                g_array[j] = base_color[1] / i;
                b_array[j] = base_color[2] / i;

            }

            send22(r_array, g_array, b_array);
    }
}}







