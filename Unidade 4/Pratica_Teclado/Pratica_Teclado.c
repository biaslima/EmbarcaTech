#include <stdio.h> // biblioteca geral para entrada e saída
#include "pico/stdlib.h" // biblioteca geral para trabalhar em C

#define LED_PIN_RED 13
#define LED_PIN_BLUE 12
#define LED_PIN_GREEN 11
#define BUZZER_PIN 17

const uint8_t COL_PINS[] = {1, 2, 3, 4}; // definição dos pinos das colunas
const uint8_t ROW_PINS[] = {5, 6 , 7 ,8}; // definição dos pinos das linhas

const char KEY_MAP[4][4] = { //Matriz para mapear tecla
    {'D', '#', '0', '*'},
    {'C', '9', '8', '7'},
    {'B', '6', '5', '4'},
    {'A', '3', '2', '1'}
};

char leitura_teclado(uint8_t *cols, uint8_t *rows){
    for (int i = 0; i < 4 ; i++){
        gpio_put(ROW_PINS[i], 0); // coloca a linha atual como nível baixo
        int coluna_selecionada = 0; // armazena a coluna que será selecionada
        for (int j = 0; j < 4; j++){ //percorre as colunas dentor da linha 
            coluna_selecionada |= gpio_get(cols[j]) << j; // recebe a coluna selecionada
        }
        if(coluna_selecionada){ // se a coluna foi selecionada, ela foi posta em nível baixo
            char tecla = KEY_MAP[i][__builtin_ctz(coluna_selecionada)]; // armazena a tecla selecionada com a matriz da linha (i) e da coluna 
            gpio_put(ROW_PINS[i], 1); // recoloca a linha atual em nível alto
            return tecla; // rtorna a tecla
        }
        gpio_put(ROW_PINS[i], 1);
    }
    return 0;
}


int main()
{
    stdio_init_all();

    for (int i = 0; i < 4 ; i++){ // ativa todas as linhas e as define como saida
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(ROW_PINS[i], GPIO_OUT);
        gpio_put(ROW_PINS[i], 1); 
    }

    for (int i = 0; i < 4 ; i++){ // ativa todas as colunas e as coloca com entrada, além de pull-up
        gpio_init(COL_PINS[i]);
        gpio_set_dir(COL_PINS[i], GPIO_IN);
        gpio_pull_up(COL_PINS[i]);
    }

    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    while (true) {
            char tecla = leitura_teclado(COL_PINS, ROW_PINS); // recebe tecla chamando a função de leitura
            
            if (tecla != 0){ //verifica se alguma tecla foi pressionada
                switch (tecla)
                {
                case 'A':
                    gpio_put(LED_PIN_BLUE, 1);
                    sleep_ms(2000);
                    gpio_put(LED_PIN_BLUE, 0);
                    break;
                case 'B':
                    gpio_put(LED_PIN_RED, 1);
                    sleep_ms(2000);
                    gpio_put(LED_PIN_RED, 0);
                    break;
                case 'C':
                    gpio_put(LED_PIN_GREEN, 1);
                    sleep_ms(2000);
                    gpio_put(LED_PIN_GREEN, 0);
                    break;
                
                default:
                    printf("Essa tecla não faz nada\n");
                    break;
                }
            }
            
    }
}
