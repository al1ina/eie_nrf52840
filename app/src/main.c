/*
 * main.c
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>
#include "BTN.h"
#include "LED.h"

#define SLEEP_TIME_MS 1000

#define SW0_NODE DT_ALIAS(sw0)
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

static struct gpio_callback button_isr_data;

void button_isr(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    printk("Button 0 pressed!\n");
}

int main(void) {
    if(BTN_init() < 0) {
        return 0;
    }
    if(LED_init() < 0>) {
        return 0;
    }

    while (1) {
        if(BTN_check_clear_pressed(BTN0)) {
            LED_toggle(LED0);
            printk("Button 0 pressed!\n");
        }
        k_msleep(SLEEP_MS);
    }
    return 0;
}
