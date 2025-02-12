#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#define PWM_SERVO 22
#define PWM_LED 12

const uint16_t WRAP_PERIOD = 20000;
const float PWM_DIVISER = 104.0; //divisor do clock para o PWM
uint16_t led_level = 0; //nível inicial do pwm (duty cycle)
uint16_t servo_level = 0; //nível inicial do pwm (duty cycle)

int main() {
    stdio_init_all();
    
    gpio_set_function(PWM_LED, GPIO_FUNC_PWM);
    gpio_set_function(PWM_SERVO, GPIO_FUNC_PWM);

    uint slice_led = pwm_gpio_to_slice_num(PWM_LED);
    uint slice_servo = pwm_gpio_to_slice_num(PWM_SERVO);

    pwm_set_clkdiv(slice_led, PWM_DIVISER); //define o divisor de clock do PWM
    pwm_set_clkdiv(slice_servo, PWM_DIVISER); //define o divisor de clock do PWM

    pwm_set_wrap(slice_led, WRAP_PERIOD); //definir o valor de wrap
    pwm_set_wrap(slice_servo, WRAP_PERIOD); //definir o valor de wrap

    pwm_set_gpio_level(PWM_LED, 0); //definir o cico de trabalho (duty cycle) do pwm
    pwm_set_gpio_level(PWM_SERVO, 0); //definir o cico de trabalho (duty cycle) do pwm

    pwm_set_enabled(PWM_LED, true); //habilita o pwm no slice correspondente
    pwm_set_enabled(PWM_SERVO, true); //habilita o pwm no slice correspondente

    pwm_set_gpio_level(PWM_SERVO, 2400);
    sleep_ms(5000);

    pwm_set_gpio_level(PWM_SERVO, 1470);
    sleep_ms(5000);

    pwm_set_gpio_level(PWM_SERVO, 500);
    sleep_ms(5000);



    
    while (true) {
        printf("Level: %d\n", servo_level);
        servo_level += 1;
        pwm_set_gpio_level(PWM_SERVO, servo_level);
        sleep_ms(5);
    }
}
