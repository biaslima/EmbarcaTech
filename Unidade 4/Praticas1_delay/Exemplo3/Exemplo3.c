#include <stdio.h>
#include "pico/stdlib.h"

#define led_pin_green 16
#define led_pin_red 17

const uint8_t colunas[4] = {1, 2 ,3, 4};
const uint8_t linhas[4] = {5, 6 ,7, 8};
const uint8_t segment_pins[] = {9, 10, 11, 12, 13, 14, 15};

//Mapeamento das teclas
const char teclado[4][4] = 
    {
    {'1', '2', '3', 'A'}, 
    {'4', '5', '6', 'B'}, 
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
    };

// Mapeamento dos dígitos para os segmentos do display
const uint8_t digits[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 0, 0, 1, 1}  // 9
};

char ler_teclado(){

    char digito = 'n';
    for (int i = 0; i < 4; i++){
        gpio_put (colunas[i], 1);
    }

    for (int coluna = 0; coluna < 4; coluna ++){
        gpio_put(colunas[coluna], 0);

        for (int linha = 0; linha < 4 ; linha++){
            if (gpio_get(linhas[linha]) == 0){
                digito = teclado[linha][coluna];

                while (gpio_get(linhas[linha]) == 0){
                    sleep_ms(10); 
                }
            }
        }
        gpio_put(colunas[coluna],1);
        if (digito != 'n'){
            break;
        }

    }
    return digito; 
}
// Função para exibir um dígito no display
void display_digit(uint8_t digit) {
    for (int i = 1; i < 7; i++) {
        gpio_put(segment_pins[i], digits[digit][i]);
    }
}

int senha = 4;
int senha_index = 0; 

int main()
{
    char tentativa[2];
    int num_tentativas = 0;
    bool bloqueado = false;

    stdio_init_all();

    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);

    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);

    for (int i = 0; i < 7; i++) {
        gpio_init(segment_pins[i]);
        gpio_set_dir(segment_pins[i], GPIO_OUT);
    }

    for (int i = 0; i < 4; i++)
    {//Os pinos de 1 a 4 sao outputs
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_OUT);
        gpio_put(colunas[i], 1); // Inicializa todas as colunas como baixo
    }

    for (int i = 0; i < 4; i++)
    {//Os pinos de 5 a 8 sao inputs
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_IN);
        gpio_pull_up(linhas[i]); // Habilita pull-up para as linhas
    }

    while (true) {
        
        if(bloqueado){
            sleep_ms (3000);
            bloqueado = false;
            num_tentativas = 0; 
            continue;
        } if (senha_index < 2){
            char tecla = ler_teclado();

            if (tecla != 'n') {
                tentativa[senha_index] = tecla;
                display_digit(tecla - '0');
                sleep_ms(1000); 
                 for (int i = 0; i < 7; i++) {
                    gpio_put(segment_pins[i], 0);
                }
                senha_index ++;
                }
            }
            if (senha_index == 2){
                if (tentativa[0] == '4' && tentativa[1] == '1'){
                    gpio_put(led_pin_green, 1);
                    sleep_ms(2000);
                    gpio_put(led_pin_green, 0);
                    num_tentativas = 0;
                } else {
                    gpio_put(led_pin_red, 1);
                    sleep_ms(2000);
                    gpio_put(led_pin_red, 0);
                    num_tentativas ++;

                    if(num_tentativas >= 3){
                        bloqueado = true;
                    }
                }
                senha_index = 0;
            }
            sleep_ms(200);
        }
        
    }
        


