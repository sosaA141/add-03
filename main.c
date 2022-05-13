#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

int main() {
stdio_init_all();
printf("temperatura\n");

adc_init();

float r1 = 10000;
float vcc = 3.3f;
float beta = 3950.0;
float temp0 = 298.0;
float r0 = 10000;
float vm;
float rntc;
float tempK;

adc_gpio_init(26);
adc_select_input(0);

while (1) {
    const float conversion_factor = 3.3f / (1 << 12);
    uint16_t result = adc_read();
    vm = result * conversion_factor;
    rntc = r1 / ((vcc/vm)-1);
    tempK = beta / ( log( rntc / r0 ) + ( beta / temp0 ) );
    printf("Resistencia: %f Ohm, Temperatura: %.2f C \n", rntc, tempK - 273);
    sleep_ms(500);
    }
}