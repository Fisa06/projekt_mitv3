#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
//#include "uart1.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stm8s_spi.h>



void In_it(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    SPI_DeInit();
    SPI_Init(SPI_FIRSTBIT_MSB,
             SPI_BAUDRATEPRESCALER_4,
             SPI_MODE_MASTER,
             SPI_CLOCKPOLARITY_LOW,
             SPI_CLOCKPHASE_1EDGE,
             SPI_DATADIRECTION_1LINE_TX,
             SPI_NSS_SOFT,
             0x07);
    //GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
   // GPIO_Init(ONE_WIRE_PORT, ONE_WIRE_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
}
// Example SPI initialization function

// Function to convert RGB values to the SPI data format for WS2812B
void WS2812B_SendPixel(uint8_t r, uint8_t g, uint8_t b) {
    // WS2812B expects data in GRB order
    uint8_t colors[3] = {g, r, b};

    for (int i = 0; i < 3; i++) {
        for (int bit = 7; bit >= 0; bit--) {
            if (colors[i] & (1 << bit)) {
                // 1 bit: SPI should send a pattern that corresponds to a high pulse (e.g., 0b11100000)
                SPI_SendData(0b01110000);
            } else {
                // 0 bit: SPI should send a pattern that corresponds to a low pulse (e.g., 0b10000000)
                SPI_SendData(0b01000000);
            }
        }
    }
}

// Function to send a series of WS2812B LEDs
void WS2812B_Send(uint8_t *leds, size_t count) {
    // Send each pixel's data
    for (size_t i = 0; i < count; i++) {
        WS2812B_SendPixel(leds[i * 3], leds[i * 3 + 1], leds[i * 3 + 2]);
    }

    // After sending all data, ensure a reset by sending a low signal for a period
    // This can be achieved by sending a number of zero bytes over SPI
    for (int i = 0; i < 50; i++) {  // Number of zero bytes for reset (depends on clock frequency)
        SPI_SendData(0x00);
    }
}

int main() {
    In_it();

    // Array to hold color data for 64 LEDs, all set to red
    uint8_t ledData[64 * 3];

    // Fill the array with red color data

    // Send data to LEDs


    // Main loop
    while (1) {
        WS2812B_Send(0xffffff,64);
        // Your main application code
    }

    return 0;
}






