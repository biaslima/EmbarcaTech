#include <stdio.h>
#include "pico/stdlib.h"

const uint led_pin_red =12;
const uint button_a = 5;
static volatile uint a = 1;
static void gpio_irq_handler(uint gpio, uint32_t events);


int main()
{
    stdio_init_all();

    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);

    gpio_init(button_a);
    gpio_set_dir(button_a, GPIO_IN);
    gpio_pull_up(button_a);

    gpio_set_irq_enabled_with_callback(button_a, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}

void gpio_irq_handler(uint gpio, uint32_t events){
    a++;
    if (a&2 == 0)
    gpio_put(led_pin_red, true);
    else 
    gpio_put(led_pin_red, false);
}
