
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
    delay_ms(5);
}


void send3(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]) {
    uint32_t data[64];
    for (uint8_t i = 0; i < 64; i++) {
        data[i] = _merge(r_array[i], g_array[i], b_array[i]);
    }
    transposeMatrix(data);

    let_that_sink_in(data);
    delay_ms(5);
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


uint32_t interpolate_color(uint32_t color1, uint32_t color2, float factor) {
    uint8_t r1 = (color1 >> 16) & 0xFF;
    uint8_t g1 = (color1 >> 8) & 0xFF;
    uint8_t b1 = color1 & 0xFF;

    uint8_t r2 = (color2 >> 16) & 0xFF;
    uint8_t g2 = (color2 >> 8) & 0xFF;
    uint8_t b2 = color2 & 0xFF;

    uint8_t r = r1 + (r2 - r1) * factor;
    uint8_t g = g1 + (g2 - g1) * factor;
    uint8_t b = b1 + (b2 - b1) * factor;

    return (r << 16) | (g << 8) | b;
}

void generate_diagonal_gradient(uint32_t* gridos, uint32_t* result) {
    int pos1 = -1, pos2 = -1;
    uint32_t color1, color2;

    // Identify the set colors and their positions
    for (uint8_t i = 0; i < 64; i++) {
        if (gridos[i] != 0) {
            if (pos1 == -1) {
                pos1 = i;
                color1 = gridos[i];
            } else {
                pos2 = i;
                color2 = gridos[i];
                break;
            }
        }
    }


    // Initialize the result grid with 0 values
    for (uint8_t i = 0; i < 64; i++) {
        result[i] = 0;
    }

    // Set the start and end colors
    result[pos1] = color1;
    result[pos2] = color2;

    // Calculate the diagonal distances
    uint8_t dist_x = abs((pos2 % 8) - (pos1 % 8));
    uint8_t dist_y = abs((pos2 / 8) - (pos1 / 8));
    uint8_t max_dist = dist_x > dist_y ? dist_x : dist_y;

    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            uint8_t index = i * 8 + j;
            if (result[index] == 0) {
                float factor = (float)(i > j ? i : j) / max_dist;
                result[index] = interpolate_color(color1, color2, factor);
            }
        }
    }
}







