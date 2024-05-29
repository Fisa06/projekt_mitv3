#include "stm8s.h"
void send3(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]);
void send22(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]);
void send2(uint8_t r_array[64], uint8_t g_array[64], uint8_t b_array[64]);
void reverseSubArray(uint32_t *array, uint8_t start, uint8_t end);
void reverseEverySecondRow(uint32_t *array);
void transposeMatrix(uint32_t *array);

void color_fill_basic_horizontal(void);


void color_fill_with_reverse_horizontal(void);


void color_fill_with_reverse_vertical(void);


