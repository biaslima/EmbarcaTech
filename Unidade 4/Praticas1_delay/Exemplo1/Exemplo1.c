#include <stdio.h>
#include "pico/stdlib.h"

#define led_pin_red 13
#define led_pin_green 11
#define led_pin_blue 12
#define button_a 5

bool ciclo_ativo = false;

void iniciar_ciclo (){
    while (ciclo_ativo) {
        gpio_put(led_pin_green, 1);
        sleep_ms(5000);
        gpio_put(led_pin_green,0);

        gpio_put(led_pin_red, 1);
        gpio_put(led_pin_green,1);
        sleep_ms(2000);
        gpio_put(led_pin_red, 0);
        gpio_put(led_pin_green,0);

        gpio_put(led_pin_red, 1);
        sleep_ms(5000);
        gpio_put(led_pin_red, 0);
    }
}

int main()
{
    stdio_init_all();
    
    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);

    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);

    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);

    gpio_init(button_a);
    gpio_set_dir(button_a, GPIO_IN);
    gpio_pull_up(button_a);
    
    while(1){
        if(!gpio_get(button_a)){
            ciclo_ativo = !ciclo_ativo;

            if (ciclo_ativo){
                iniciar_ciclo();
            }
            
        }
        sleep_ms(200);
    }
    return 0;
}
