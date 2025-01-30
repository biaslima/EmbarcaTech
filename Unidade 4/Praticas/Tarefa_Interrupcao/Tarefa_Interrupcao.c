#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

//Definição dos Pins e variáveis
#define led_pin_red 13
#define led_pin_blue 12
#define led_pin_green 11
#define button_a 5
#define button_b 6

#define led_matrix_pin 7
#define NUM_LEDS 25

#define IS_RGBW false

static volatile uint32_t last_time = 0;

uint32_t leds[NUM_LEDS];

//Função para localizar LEDs da matriz através de linhas e colunas
uint8_t localizar_led_xy(uint8_t x, uint8_t y) {
    return (4 - y) * 5 + x;
}

//Gerar números na matriz
const uint8_t numbers[10][5][5] = {
    { // Número 0
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    },
    { //Número 1
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0}
    },
    { // Número 2
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1}
    },
    { //Número 3
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    },
    { //Número 4
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0}
    },
    { // Número 5
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    },
    { // Número 6 
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    },
    { //Número 7
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0}
    },
    {// Número 8
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    },
    { // Número 9
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    }
};

// Função para criar uma cor GRB
uint32_t create_color(uint8_t green, uint8_t red, uint8_t blue) {
    return ((uint32_t)green << 16) | ((uint32_t)red << 8) | blue;
}

// Função para exibir um número na matriz
void display_number(uint32_t leds[NUM_LEDS], uint8_t number) {
    for (uint8_t y = 0; y < 5; y++) {
        for (uint8_t x = 0; x < 5; x++) {
            if (numbers[number][y][x]) {
                leds[localizar_led_xy(x, y)] = create_color(0, 50, 50);
            } else {
                leds[localizar_led_xy(x, y)] = 0; 
            }
        }
    }
}

void update_leds(PIO pio, uint sm) {
    for (int i = 0; i < NUM_LEDS; i++) {
        pio_sm_put_blocking(pio, sm, leds[i] << 8u);
    }
}

// Prototipo da função de interrupção
static void gpio_irq_handler(uint gpio, uint32_t events);


int main()
{
    stdio_init_all();

    //Inicialização e configuração inicial de GPIOs
    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);

    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);

    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);

    gpio_init(led_matrix_pin);
    gpio_set_dir(led_matrix_pin, GPIO_OUT);

    gpio_init(button_a);
    gpio_set_dir(button_a, GPIO_IN);
    gpio_pull_up(button_a);

    gpio_init(button_b);
    gpio_set_dir(button_b, GPIO_IN);
    gpio_pull_up(button_b);

    // Configurações PIO
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    printf("Loaded program at %d\n", offset);

    ws2812_program_init(pio, sm, offset, led_matrix_pin, 800000, IS_RGBW);

     for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = 0; 
    }
    update_leds(pio, sm);

    // Configuração da interrupções
    gpio_set_irq_enabled_with_callback(button_a, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(button_b, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        gpio_put(led_pin_red, 1);
        sleep_ms(200);
        gpio_put(led_pin_red, 0);
        sleep_ms(200);
    }
}

//Funções de interrupção
void gpio_irq_handler(uint gpio, uint32_t events)
{

    uint32_t current_time = to_us_since_boot(get_absolute_time());
    
    if (current_time - last_time > 200000){
        last_time = current_time;

        static uint8_t numero = 0;

        if (!gpio_get(button_a)){
        numero = (numero + 1) % 10;
        }
        else if (!gpio_get(button_b)){
        numero = (numero == 0) ? 9 : numero - 1;
        }

        display_number(leds, numero);
        update_leds(pio0, 0);
    }
}

