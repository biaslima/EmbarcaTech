#include <stdio.h>
#include "pico/stdlib.h"

const uint led_pin_green = 11;
const uint button_a = 5;
static volatile uint a = 1;

//rotina de interrupção
static void gpio_irq_handler(uint gpio, uint32_t events){
    
    a++;
    printf("Interrupção ocorreu no pino %d, no evento %d\n", gpio, events);
    if(a%2 == 0)
    gpio_put(led_pin_green, true);
    else 
    gpio_put (led_pin_green, false);
}

int main()
{
    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);

    gpio_init(button_a);
    gpio_set_dir(button_a, GPIO_IN);
    gpio_pull_up(button_a);

    stdio_init_all();

    gpio_set_irq_enabled_with_callback(button_a, GPIO_IRQ_EDGE_FALL, true , &gpio_irq_handler);

    while (true) {
        printf("Teste de Interrupção\n");
        sleep_ms(10000);
        
    }
}

