
#include "animations.h"
#include "stm8s.h"
#include "neopixel.h"
#include "delay.h"
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

void rotate90Clockwise(uint32_t matrix[64]) {
    uint32_t temp[64];

    // Copy the rotated values into a temporary array
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            temp[j * 8 + (7 - i)] = matrix[i * 8 + j];
        }
    }

    // Copy the temporary array back to the original matrix
    for (uint8_t i = 0; i < 64; i++) {
        matrix[i] = temp[i];
    }
}


uint32_t interpolate_color(uint32_t color1, uint32_t color2, float factor) {
    uint8_t g1 = (color1 >> 16) & 0xFF;
    uint8_t r1 = (color1 >> 8) & 0xFF;
    uint8_t b1 = color1 & 0xFF;

    uint8_t g2 = (color2 >> 16) & 0xFF;
    uint8_t r2 = (color2 >> 8) & 0xFF;
    uint8_t b2 = color2 & 0xFF;

    uint8_t g = g1 + (g2 - g1) * factor;
    uint8_t r = r1 + (r2 - r1) * factor;
    uint8_t b = b1 + (b2 - b1) * factor;

    return ((uint32_t)g << 16) | ((uint32_t)r << 8) | b;
}

void generate_diagonal_gradient(uint32_t* gridos, uint32_t* result) {
    int pos1 = -1, pos2 = -1;
    uint32_t color2 = 0;
    uint32_t color1 = 0;

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
                float factor = (float)(i > j ? i : j) / (float)max_dist;
                result[index] = interpolate_color(color1, color2, factor);
            }
        }
    }
}




void color_gradient_corner_effect(void) {
    uint8_t i_red = 0;
    uint8_t i_green = 0;
    uint8_t i_blue = 0;

#define speed_ms 1
#define step 2
#define red_offset -30
#define green_offset 0
#define blue_offset 0

    // hihi();
    uint32_t values[64] = {0};
    uint32_t out[64];

    for (uint8_t i = 0; i < 64; i += step) {
        values[63] =
            _merge((i + red_offset) < 0 ? 0 : (i + red_offset), 0, (127 - i));
        values[0] = _merge(
            (127 - i + red_offset) < 0 ? 0 : (127 - i + red_offset), 0, i);

        generate_diagonal_gradient(values, out);

        let_that_sink_in(out);
        delay_ms(speed_ms);
    }
    for (uint8_t i = 64; i < 128; i += step) {

        values[63] = _merge(
            (127 - i + red_offset) < 0 ? 0 : (127 - i + red_offset), 0, i);
        values[0] =
            _merge((i + red_offset) < 0 ? 0 : (i + red_offset), 0, (127 - i));

        generate_diagonal_gradient(values, out);
        rotate90Clockwise(out);

        let_that_sink_in(out);
        delay_ms(speed_ms);
    }
    for (uint8_t i = 0; i < 64; i += step) {

        values[63] =
            _merge((i + red_offset) < 0 ? 0 : (i + red_offset), 0, (127 - i));
        values[0] = _merge(
            (127 - i + red_offset) < 0 ? 0 : (127 - i + red_offset), 0, i);

        generate_diagonal_gradient(values, out);
        rotate90Clockwise(out);
        let_that_sink_in(out);
        delay_ms(speed_ms);
    }
    for (uint8_t i = 64; i < 128; i += step) {

        values[63] = _merge(
            (127 - i + red_offset) < 0 ? 0 : (127 - i + red_offset), 0, i);
        values[0] =
            _merge((i + red_offset) < 0 ? 0 : (i + red_offset), 0, (127 - i));

        generate_diagonal_gradient(values, out);
        rotate90Clockwise(out);
        rotate90Clockwise(out);

        let_that_sink_in(out);
        delay_ms(speed_ms);
    }
    for (uint8_t i = 0; i < 64; i += step) {

        values[63] =
            _merge((i + red_offset) < 0 ? 0 : (i + red_offset), 0, (127 - i));
        values[0] = _merge(
            (127 - i + red_offset) < 0 ? 0 : (127 - i + red_offset), 0, i);

        generate_diagonal_gradient(values, out);
        rotate90Clockwise(out);
        rotate90Clockwise(out);
        let_that_sink_in(out);
        delay_ms(speed_ms);
    }
    for (uint8_t i = 64; i < 128; i += step) {

        values[63] = _merge(
            (127 - i + red_offset) < 0 ? 0 : (127 - i + red_offset), 0, i);
        values[0] =
            _merge((i + red_offset) < 0 ? 0 : (i + red_offset), 0, (127 - i));

        generate_diagonal_gradient(values, out);
        rotate90Clockwise(out);
        rotate90Clockwise(out);
        rotate90Clockwise(out);

        let_that_sink_in(out);
        delay_ms(speed_ms);
    }
    for (uint8_t i = 0; i < 64; i += step) {

        values[63] =
            _merge((i + red_offset) < 0 ? 0 : (i + red_offset), 0, (127 - i));
        values[0] = _merge(
            (127 - i + red_offset) < 0 ? 0 : (127 - i + red_offset), 0, i);

        generate_diagonal_gradient(values, out);
        rotate90Clockwise(out);
        rotate90Clockwise(out);
        rotate90Clockwise(out);
        let_that_sink_in(out);
        delay_ms(speed_ms);
    }
    for (uint8_t i = 64; i < 128; i += step) {

        values[63] = _merge(
            (127 - i + red_offset) < 0 ? 0 : (127 - i + red_offset), 0, i);
        values[0] =
            _merge((i + red_offset) < 0 ? 0 : (i + red_offset), 0, (127 - i));

        generate_diagonal_gradient(values, out);
        rotate90Clockwise(out);
        rotate90Clockwise(out);
        rotate90Clockwise(out);
        rotate90Clockwise(out);

        let_that_sink_in(out);
        delay_ms(speed_ms);
    }
}

void draw_frame(int frame[8][8], uint32_t color3, uint32_t color2, uint32_t color1){
    uint32_t empty_list[64] = {0};
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            uint8_t index = i * 8 + j;
            if (frame[i][j] == 3) {
                empty_list[index] = 0x008000;
            }  else if (frame[i][j] == 2) {
                empty_list[index] = 0x004000;
            } else if (frame[i][j] ==1) {
                empty_list[index] = 0x002000;
            }


        }}
    let_that_sink_in(empty_list);}

void cross_animation(void){
#define SIZE 8
#define color3 0x400000
#define color2 0x6000000
#define color1 0x8000000
#define speed_mss 5
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
    delay_ms(speed_mss);
    draw_frame(frame2, color3, color2, color1);
    delay_ms(speed_mss);
    draw_frame(frame3, color3, color2, color1);
    delay_ms(speed_mss);
    draw_frame(frame4, color3, color2, color1);
    delay_ms(speed_mss);
    draw_frame(frame5, color3, color2, color1);
    delay_ms(speed_mss);
    draw_frame(frame6, color3, color2, color1);
    delay_ms(speed_mss);
    draw_frame(frame7, color3, color2, color1);
    delay_ms(speed_mss);
    draw_frame(frame8, color3, color2, color1);
    delay_ms(speed_mss);
    draw_frame(frame9, color3, color2, color1);
    delay_ms(speed_mss);
    draw_frame(frame10, color3, color2, color1);
    delay_ms(speed_mss);
    draw_frame(frame11, color3, color2, color1);
    delay_ms(speed_mss);
    draw_frame(frame12, color3, color2, color1);
    delay_ms(speed_mss);
    draw_frame(frame13, color3, color2, color1);
    delay_ms(speed_mss);
    draw_frame(frame14, color3, color2, color1);
    delay_ms(speed_mss);

}














