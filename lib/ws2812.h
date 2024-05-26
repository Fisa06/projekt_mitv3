#ifndef __WS2812_H__
#define __WS2812_H__

#include <stdint.h>

// parameter structure
typedef struct {
    uint32_t pin;
    uint32_t *colors;
    volatile uint32_t count;
} ws2812_params;

// driver header structure
typedef struct {
    uint32_t    jmp_inst;
    uint32_t    resettix;
    uint32_t    bit0hi;
    uint32_t    bit0lo;
    uint32_t    bit1hi;
    uint32_t    bit1lo;
} ws2812_hdr;

#define COLOR(r, g, b)      (((r) << 16) | ((g) << 8) | (b))
#define SCALE(x, l)         ((x) * (l) / 255)
#define COLORX(r, g, b, l)  ((SCALE(r, l) << 16) | (SCALE(g, l) << 8) | SCALE(b, l))

#define COLOR_BLACK     COLOR(  0,   0,   0)
#define COLOR_RED       COLOR(255,   0,   0)
#define COLOR_GREEN     COLOR(  0, 255,   0)
#define COLOR_BLUE      COLOR(  0,   0, 255)

int ws2812_init(int pin, uint32_t *colors, int count);
void ws2812_fill(uint32_t *colors, int count, uint32_t color);

#endif
