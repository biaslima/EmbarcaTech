#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN_RED 13
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define BTN_A 5
#define BTN_B 6


int main()
{
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);

    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);

    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);

    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);


    while (1) {
        if(!gpio_get(BTN_A) && gpio_get(BTN_B)){
            gpio_put(LED_PIN_RED, 1);
            gpio_put(LED_PIN_BLUE, 0);
            gpio_put(LED_PIN_GREEN, 0);
        }
        else if (!gpio_get(BTN_B) && gpio_get(BTN_A))
        {
            gpio_put(LED_PIN_GREEN, 1);
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_BLUE, 0);
        }
        else if (!gpio_get(BTN_B) && !gpio_get(BTN_A))
        {
            gpio_put(LED_PIN_BLUE, 1);
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_GREEN, 0);
        }
        else{
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_BLUE, 0);
            gpio_put(LED_PIN_GREEN, 0);
        }
    }
}
