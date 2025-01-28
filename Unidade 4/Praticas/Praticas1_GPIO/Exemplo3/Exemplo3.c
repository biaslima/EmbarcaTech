#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"

#define LED_PIN 7         // GPIO conectado ao Din da matriz
#define NUM_PIXELS 25     // Número de LEDs na matriz (5x5)
#define IS_RGBW true      // Define se os LEDs suportam RGBW (caso contrário, use false)

void set_pixel_color(uint32_t color) {
    // Configura todos os LEDs com uma única cor
    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio0, 0, color << 8u);
    }
}

uint32_t rgb_to_color(uint8_t r, uint8_t g, uint8_t b) {
    // Converte valores RGB para o formato esperado pelo WS2812B
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

int main() {
    stdio_init_all();

    // Inicializa o PIO e o estado para comunicação com WS2812B
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, LED_PIN, 800000, IS_RGBW);

    while (true) {
        // Acende os LEDs em vermelho
        set_pixel_color(rgb_to_color(255, 0, 0));
        sleep_ms(1000);

        // Troca para verde
        set_pixel_color(rgb_to_color(0, 255, 0));
        sleep_ms(1000);

        // Troca para azul
        set_pixel_color(rgb_to_color(0, 0, 255));
        sleep_ms(1000);
    }

    return 0;
}
