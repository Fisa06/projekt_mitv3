#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
#include "../inc/Adafruit_NeoPixel.h"
#include "../inc/main.h"
#include "../inc/milis.h"
//#include "delay.h"
//#include "uart1.h"
#define LED_PORT GPIOC
#define LED_PIN  GPIO_PIN_5
#define BTN_PORT GPIOE
#define BTN_PIN  GPIO_PIN_4

#define ONE_WIRE_PORT GPIOC
#define ONE_WIRE_PIN GPIO_PIN_4

void init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz

    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
#if defined (BTN_PORT) || defined (BTN_PIN)
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);
#endif

    init_milis();

    //init_uart1();
}


int main(void)
{
  
    uint32_t time = 0;

    init();

    while (1) {
        if (milis() - time > 333 && !PUSH(BTN)) {

        if (milis() - time > 333 ) {

            REVERSE(LED); 
            time = milis();
            //printf("%ld\n", time);
        }
        //delay_ms(333);
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "../inc/__assert__.h"
