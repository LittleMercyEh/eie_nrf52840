/*
* main.c
*/

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

static const struct gpio_dt_spec leds[] = { // Array of LED specifications
    GPIO_DT_SPEC_GET(LED0_NODE, gpios),
    GPIO_DT_SPEC_GET(LED1_NODE, gpios),
    GPIO_DT_SPEC_GET(LED2_NODE, gpios),
    GPIO_DT_SPEC_GET(LED3_NODE, gpios)
};

int main(void) {
    int ret;

    for (int i = 0; i < 4; i++) { // check each led 
        if (!gpio_is_ready_dt(&leds[i])) { //  if not ready fail
            return -1; 
        }

        ret = gpio_pin_configure_dt(&leds[i], GPIO_OUTPUT_ACTIVE); //  configure
        if (ret < 0) {
            return ret; 
        }
    }

    while (1) {
        for (int i = 0; i < 4; i++) { // toggle all leds
            gpio_pin_toggle_dt(&leds[i]);
        }
        k_msleep(1000);
    }

    return 0;
}
