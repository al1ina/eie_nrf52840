#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/sys/printk.h>
#include <stdint.h>
#include <inttypes.h>
#include "../include/BTN.h"
#include "LED.h"

#define SLEEP_TIME_MS 1000

#define SW0_NODE DT_ALIAS(sw0)
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

static struct gpio_callback button_isr_data;

void button_isr(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    printk("Button 0 pressed!\n");
}


int main(void) {
    int ret;
    
    
    // if(!gpio_is_ready_dt(&button)) {
    //     return 0;
    // }
    if(BTN_init() < 0) {
        return 0;
    }
    if(LED_init() < 0>) {
        return 0;
    }

    // ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    // if (0 > ret) {
    //     return 0;
    // }

    // ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
    // if (0 > ret) {
    //     return 0;
    // }
    // gpio_init_callback(&button_isr_data, button_isr, BIT(button.pin));
    // gpio_add_callback(button.port, &button_isr_data);
    
    while (1) {
        if(BTN_check_clear_pressed(BTN0)) {
            LED_toggle(LED0);
            printk("Button 0 pressed!\n");
        }
        k_msleep(SLEEP_MS);
    }
    return 0;
}