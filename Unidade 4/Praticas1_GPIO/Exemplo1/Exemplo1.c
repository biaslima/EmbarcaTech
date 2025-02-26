#include "pico/stdlib.h"

#define LED_PIN 13
#define BTN_PIN 5

int main() {
    // Configuração do LED como saída
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Configuração do botão como entrada com pull-up interno
    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN); // Ativa resistor pull-up interno

    while (1) {
        // Verifica o estado do botão
        if (!gpio_get(BTN_PIN)) { // Botão pressionado
            gpio_put(LED_PIN, 1); // Liga o LED
        } else {
            gpio_put(LED_PIN, 0); // Desliga o LED
        }
    }
}

