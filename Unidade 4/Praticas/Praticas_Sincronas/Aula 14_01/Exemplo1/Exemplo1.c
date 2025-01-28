#include <stdio.h>
#include "pico/stdlib.h"

#define led_pin_red 13
#define led_pin_blue 12
#define led_pin_green 11

int main()
{
    gpio_init (led_pin_red);
    gpio_set_dir (led_pin_red, GPIO_OUT);

    gpio_init (led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);

    gpio_init (led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);

    stdio_init_all();

    while (true) {
        printf("Pisca led vermelho\r\n");
        gpio_put (led_pin_red, 1);
        sleep_ms(1000);
        gpio_put (led_pin_red, 0);
        sleep_ms(1000);

        printf("Pisca led azul\r\n");
        gpio_put (led_pin_blue, 1);
        sleep_ms(1000);
        gpio_put (led_pin_blue, 0);
        sleep_ms(1000);

        printf("Pisca led verde\r\n");
        gpio_put (led_pin_green, 1);
        sleep_ms(1000);
        gpio_put (led_pin_green, 0);
        sleep_ms(1000);
    }
}
