#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#define PWM_PIN 12 //LED PINO = 12

const uint16_t WRAP_PERIOD = 20000;
const float PWM_DIVISER = 125.0; //divisor do clock para o PWM
uint16_t pwm_level = 500; //nível inicial do pwm (duty cycle)

int main() {
    stdio_init_all();
    
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);

    uint slice_servo = pwm_gpio_to_slice_num(PWM_PIN);

    pwm_set_clkdiv(slice_servo, PWM_DIVISER); //define o divisor de clock do PWM

    pwm_set_wrap(slice_servo, WRAP_PERIOD); //definir o valor de wrap

    pwm_set_enabled(PWM_PIN, true); //habilita o pwm no slice correspondente

    pwm_set_gpio_level(PWM_PIN, 2400);
    sleep_ms(5000);

    pwm_set_gpio_level(PWM_PIN, 1470);
    sleep_ms(5000);

    pwm_set_gpio_level(PWM_PIN, 500);
    sleep_ms(5000);

    bool up_down = 1;

    
    while (true) {
        sleep_ms(10);
        if (up_down){
            pwm_level += 5;
        } else {
            pwm_level -= 5;
        }
        pwm_set_gpio_level(PWM_PIN, pwm_level);
        if(pwm_level > 2400 || pwm_level < 500) {
            up_down = !up_down;
        }
    }
}
