#include <stdio.h>
#include "pico/stdlib.h"

#define led_pin_green 11
#define button_a 5

int main()
{
    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);

    gpio_init(button_a);
    gpio_set_dir(button_a, GPIO_IN);
    gpio_pull_up(button_a);

    stdio_init_all();


    while (true) {
        if (!gpio_get(button_a))
        {
            gpio_put(led_pin_green, 1);
        } else {
            gpio_put(led_pin_green, 0);
        }
        
    }
}
