#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "ws2818b.pio.h"
#include "ssd1306.h"

#define LED_PIN 7
#define LED_COUNT 25
#define MAX_BRIGHTNESS 255
#define BUTTON_A 5
#define BUTTON_B 6
#define BUTTON_JOYSTICK 22

uint8_t brightnessLevel = 200;

struct pixel_t {
    uint8_t G, R, B;
};
typedef struct pixel_t pixel_t;
pixel_t leds[LED_COUNT];
PIO np_pio;
uint sm;

void npInit(uint pin);
void setBrightness(uint8_t brightness);
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);
void npWrite(void);
void npClear(void);
void drawPattern(int pattern[5][5][3]);
void displayPatterns(void);
int getIndex(int x, int y);
void initButtons(void);
bool isButtonPressed(uint button);
void handleButtonPress(void);

int main() {
    stdio_init_all();
    sleep_ms(5000);
    npInit(LED_PIN);
    setBrightness(brightnessLevel);
    npClear();
    initButtons();
    
    while (true) {
        handleButtonPress();
        displayPatterns();
        sleep_ms(500);
    }
    return 0;
}

void initButtons(void) {
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
    gpio_init(BUTTON_JOYSTICK);
    gpio_set_dir(BUTTON_JOYSTICK, GPIO_IN);
    gpio_pull_up(BUTTON_JOYSTICK);
}

bool isButtonPressed(uint button) {
    return !gpio_get(button);
}

void handleButtonPress(void) {
    if (isButtonPressed(BUTTON_A)) {
        if (brightnessLevel < MAX_BRIGHTNESS) brightnessLevel += 20;
        setBrightness(brightnessLevel);
    }
    if (isButtonPressed(BUTTON_B)) {
        if (brightnessLevel > 20) brightnessLevel -= 20;
        setBrightness(brightnessLevel);
    }
}

void npInit(uint pin) {
    np_pio = pio0;
    uint offset = pio_add_program(np_pio, &ws2818b_program);
    sm = pio_claim_unused_sm(np_pio, true);
    ws2818b_program_init(np_pio, sm, offset, pin, 800000);
}

void setBrightness(uint8_t brightness) {
    brightnessLevel = brightness;
}

void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
    leds[index].R = (r * brightnessLevel) / MAX_BRIGHTNESS;
    leds[index].G = (g * brightnessLevel) / MAX_BRIGHTNESS;
    leds[index].B = (b * brightnessLevel) / MAX_BRIGHTNESS;
}

void npWrite(void) {
    for (uint i = 0; i < LED_COUNT; i++) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    sleep_us(100);
}

void npClear(void) {
    for (uint i = 0; i < LED_COUNT; i++) {
        npSetLED(i, 0, 0, 0);
    }
    npWrite();
}

void drawPattern(int pattern[5][5][3]) {
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            int pos = getIndex(x, y);
            npSetLED(pos, pattern[y][x][0], pattern[y][x][1], pattern[y][x][2]);
        }
    }
    npWrite();
    sleep_ms(2000);
    npClear();
}

void displayPatterns(void) {
    int heart[5][5][3] = {
        {{0,0,0}, {255,0,0}, {0,0,0}, {255,0,0}, {0,0,0}},
        {{255,0,0}, {0,0,0}, {255,0,0}, {0,0,0}, {255,0,0}},
        {{255,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {255,0,0}},
        {{0,0,0}, {255,0,0}, {0,0,0}, {255,0,0}, {0,0,0}},
        {{0,0,0}, {0,0,0}, {255,0,0}, {0,0,0}, {0,0,0}}
    };
    drawPattern(heart);
}

int getIndex(int x, int y) {
    return (y % 2 == 0) ? (24 - (y * 5 + x)) : (24 - (y * 5 + (4 - x)));
}
