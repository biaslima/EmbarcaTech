#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define led_pin_blue 12

uint columns[4] = { 4, 3, 2, 1};
uint rows [4] = {8, 7 , 6, 5};

//mapa de teclas
char KEY_MAP[16] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B', 
    '7', '8', '9', 'C',
    '*', '0', '#', 'D', 
};
 
 uint _columns[4];
 uint _rows[4];
 char _matrix_values[16];
 uint all_columns_mask = 0x0;
 uint column_mask[4];

void pico_keypad_init(uint columns[4], uint rows[4], char matrix_values[16]){

    for (int i = 0; i < 16; i ++){
        _matrix_values[i] = matrix_values[i]; //Por que é necessário copiar as variáveis? 
    }

    for (int i = 0 ; i < 4 ; i++){
        
        _columns[i] = columns[i];
        _rows[i] = rows[i];

        gpio_init(_columns[i]);
        gpio_init(_rows[i]);

        gpio_set_dir(_columns[1], GPIO_OUT);
        gpio_set_dir(_rows[1], GPIO_IN);

        gpio_put(_rows[i], 1);

        all_columns_mask = all_columns_mask + (1 << _columns[i]);
        column_mask[i] = 1 << _columns[i];
    }
}

char pico_keypad_get_key(void){
    int row;
    uint32_t cols;
    bool pressed = false;

    cols = gpio_get_all();
    cols = cols & all_columns_mask;

    if (cols = 0x0){
        return 0;
    }

    for (int j = 0; j < 4; row++) {
        gpio_put(_rows[j], 0);
    }
    for (row = 0; row < 4; row++) {

        gpio_put(_rows[row], 1);

        busy_wait_us(10000);

        cols = gpio_get_all();
        gpio_put(_rows[row], 0);
        cols = cols & all_columns_mask;
        if (cols != 0x0) {
            break;
        }  
    }
    for (int i = 0; i < 4; i++) {
        gpio_put(_rows[i], 1);
    }
    if (cols == column_mask[0]) {
        return (char)_matrix_values[row * 4 + 0];
    }
    else if (cols == column_mask[1]) {
        return (char)_matrix_values[row * 4 + 1];
    }
    if (cols == column_mask[2]) {
        return (char)_matrix_values[row * 4 + 2];
    }
    else if (cols == column_mask[3]) {
        return (char)_matrix_values[row * 4 + 3];
    }
    else {
        return 0;
    }
}
int main()
{
    stdio_init_all();
    pico_keypad_init(columns, rows, KEY_MAP);
    char caracter_press;
    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);

    while (true) {
        caracter_press = pico_keypad_get_key();
        printf("\nTecla pressionada: %c\n", caracter_press);

        //Avaliação de caractere para o LED
        if (caracter_press=='B')
        {
            gpio_put(led_pin_blue,true);
        }else
        {
            gpio_put(led_pin_blue,false);
        }
        busy_wait_us(500000);
    }
}
