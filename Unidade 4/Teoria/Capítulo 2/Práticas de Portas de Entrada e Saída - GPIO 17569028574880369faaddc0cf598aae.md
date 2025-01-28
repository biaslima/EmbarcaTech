# Práticas de Portas de Entrada e Saída - GPIO

# Cuidados com os pinos GPIO

- Avaliar limites de Tensão e Corrente → cada pino possui um limite máximo de tensão e corrente;
- Prevenção de Curto-Circuitos → evitar que os pinos configurados como saída entrem em contato um com outro ou com GND;
- Isolamento elétrico → isolar o microcontrolador de circuitos que envolvam tensões ou correntes perigosamente altas;

<aside>
💡

Abrir link de manual breve do microcontrolador. 

[Breve Manual RP2040.pdf](Breve_Manual_RP2040.pdf)

</aside>

# Raspberry Pi Pico W e BitDogLab

- Resistores de pull-up e pull-down programáveis;
- Conta com módulo Wi-Fi 4 e Bluetooth 5.2;
- A BitDogLab possui um conjunto de periféricos embarcados;

<aside>
💡

Diagrama esquemático da BitDogLab:

[bitdoglab_v6_3_smd.kicad_pro.pdf](bitdoglab_v6_3_smd.kicad_pro.pdf)

</aside>

## Periféricos

- LED Colorido
    - Conectado aos pinos:
        - 11 → verde;
        - 12 → azul;
        - 13 → vermelho;
- Botões **A**(pino 5) e **B**(pino 6);

## Principais Funções Pico SDK

- `void gpio_init(uint gpio)` → Inicializa o pino GPIO;
    - Ex:
        
        ```c
        gpio_init(LED_PIN_RED); // Limpa qualquer valor de saída.;
        ```
        
- `static void gpio_set_dir (uint gpio, bool out)` → Define a direção do pino (entrada ou saída);
    - Saída é true e entrado é false;
    - Ex.:
        
        ```c
        gpio_set_dir(LED_PIN_RED, GPIO_OUT);
        ```
        
- `static void gpio_put(uint gpio, bool value)` → Aciona o pino GPIO(alto/baixo) de acordo com os parâmetros de entrada;
    - False → nível baixo (low)
    - True → nível alto (high)
    - Ex.:
        
        ```c
        gpio_put(LED_PIN_GREEN, 0);
        ```
        
- static void gpio_get(uint_gpio) → Obtém estado de um único GPIO especificado;
    - 0 → baixo(low);
    - 1 → alto(high)
    - Ex.:
        
        ```c
        gpio_get (GPIO_BOTAO)
        ```