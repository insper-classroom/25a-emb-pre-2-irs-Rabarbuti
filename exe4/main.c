#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>


const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
const int LED_PIN_R = 4;
const int LED_PIN_G = 6;
volatile int fall_red = 0;
volatile int fall_green = 0;
volatile int rise_red = 0;
volatile int rise_green = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    if (gpio == BTN_PIN_R){
      rise_red = 0;
      fall_red = 1;
    }else if (gpio == BTN_PIN_G){
      rise_green = 0;
      fall_green = 1;
  }
  }
  if (events == 0x8) { // rise edge
    if (gpio == BTN_PIN_R){
      fall_red = 0;
      rise_red = 1;
    }else if (gpio == BTN_PIN_G){
      fall_green = 0;
      rise_green = 1;
  }}
}


int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_init(LED_PIN_R);
  gpio_init(BTN_PIN_G);
  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_pull_up(BTN_PIN_G);


  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
    &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true);

  while (true) {
    if (fall_red ==1){
      gpio_put(LED_PIN_R, 1);
      fall_red = 0;
    }
    if (rise_red == 1){
      gpio_put(LED_PIN_R, 0);
      rise_red = 0;
    }
    if (fall_green ==1){
      gpio_put(LED_PIN_G, 1);
      fall_green = 0;
    }
    if (rise_green == 1){
      gpio_put(LED_PIN_G, 0);
      rise_green = 0;
  }
}
}