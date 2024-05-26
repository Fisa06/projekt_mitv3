
#include "ws2812.h"
#include <propeller.h>

int ws2812_init(int pin, uint32_t *colors, int count)
{
    extern uint32_t binary_ws2812_driver_dat_start[];
    ws2812_hdr *hdr = (ws2812_hdr *)binary_ws2812_driver_dat_start;
    ws2812_params params;
    uint32_t ustix;
    int cog;

    if (CLKFREQ != 80000000)            // requires 80MHz clock
        return -1;

    ustix = CLKFREQ / 1000000;          // ticks in 1us

    hdr->resettix = ustix * 50;         // 50.00us min reset timing
    hdr->bit0hi   = ustix * 35 / 100;   //  0.35us
    hdr->bit0lo   = ustix * 80 / 100;   //  0.80us
    hdr->bit1hi   = ustix * 70 / 100;   //  0.70us
    hdr->bit1lo   = ustix * 60 / 100;   //  0.60us
    
    params.pin = pin;
    params.colors = colors;
    params.count = count;
    
    if ((cog = cognew(hdr, &params)) < 0)
        return -1;
        
    while (params.count)
        ;
     
    return cog;
}

void ws2812_fill(uint32_t *colors, int count, uint32_t color)
{
    int i;
    for (i = 0; i < count; ++i)
        colors[i] = color;
}

