#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "ws2818b.pio.h"
#include "includes/funcoesMatriz.h"


#define MATRIX_ROWS 5
#define MATRIX_COLS 5
#define MATRIX_DEPTH 3

#define BUTTON_A_PIN 5     // Pino do botão A
#define BUTTON_B_PIN 6     // Pino do botão B

#define LED_RGB_PIN 13 // Pino do LED RGB

volatile int contador = 0;
npLED_t leds[LED_COUNT];
int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH];

volatile uint32_t last_interrupt_time = 0;
#define DEBOUNCE_DELAY 300  // 300 ms de debounce

void drawPattern(int pattern[5][5], npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]);
void a0(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]);
void a1(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]);
void a2(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]);
void a3(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]);
void a4(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]);
void a5(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]);
void a6(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]);
void a7(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]);
void a8(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]);
void a9(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]);

// Função de callback para interrupções
typedef void (*AnimationFunction)(npLED_t[], int[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]);
AnimationFunction animations[] = {a0, a1, a2, a3, a4, a5, a6, a7, a8, a9};

void gpio_callback(uint gpio, uint32_t events) {
    uint32_t current_time = time_us_32();  // Tempo atual em microssegundos
    if (current_time - last_interrupt_time > DEBOUNCE_DELAY * 1000) {  // Verifica se passou o tempo de debounce (em microssegundos)
        last_interrupt_time = current_time;  // Atualiza o tempo da última interrupção

        if (gpio == BUTTON_A_PIN && contador < 9) {
            contador++;
        } else if (gpio == BUTTON_B_PIN && contador > 0) {
            contador--;
        }
        printf("Contador: %d\n", contador);
        turnOffLEDs(leds);
        animations[contador](leds, rgb_matrix);
    }
}

int main() {
    stdio_init_all();
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    matrizInit(LED_PIN, leds);
    gpio_init(LED_RGB_PIN);
    gpio_set_dir(LED_RGB_PIN, GPIO_OUT);

    a0(leds, rgb_matrix);

    while (true) {
        gpio_put(LED_RGB_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_RGB_PIN, 0);
        sleep_ms(100);
    }
}

void a0(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]) {
    int pattern[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    drawPattern(pattern, leds, rgb_matrix);
}

void a1(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]) {
    int pattern[5][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0}
    };
    drawPattern(pattern, leds, rgb_matrix);
}

void a2(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]) {
    int pattern[5][5] = {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1}
    };
    drawPattern(pattern, leds, rgb_matrix);
}

void a3(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]) {
    int pattern[5][5] = {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    drawPattern(pattern, leds, rgb_matrix);
}

void a4(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]) {
    int pattern[5][5] = {
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0}
    };
    drawPattern(pattern, leds, rgb_matrix);
}

void a5(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]) {
    int pattern[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    drawPattern(pattern, leds, rgb_matrix);
}

void a6(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]) {
    int pattern[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    drawPattern(pattern, leds, rgb_matrix);
}

void a7(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]) {
    int pattern[5][5] = {
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0}
    };
    drawPattern(pattern, leds, rgb_matrix);
}

void a8(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]) {
    int pattern[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    drawPattern(pattern, leds, rgb_matrix);
}

void a9(npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]) {
    int pattern[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    drawPattern(pattern, leds, rgb_matrix);
}

void drawPattern(int pattern[5][5], npLED_t leds[], int rgb_matrix[MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH]) {
    printf("Desenhando padrão na matriz...\n");
    turnOffLEDs(leds);

    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
             printf("Acendendo LED na posição [%d][%d]\n", row, col);
            if (pattern[row][col]) {
                rgb_matrix[row][col][0] = 100; // Vermelho
                rgb_matrix[row][col][1] = 100; // Ve10rde
                rgb_matrix[row][col][2] = 100; // Azul
            } else {
                rgb_matrix[row][col][0] = 0;
                rgb_matrix[row][col][1] = 0;
                rgb_matrix[row][col][2] = 0;
            }
        }
    }
    spriteWirite(rgb_matrix, leds);
    matrizWrite(leds);
}
