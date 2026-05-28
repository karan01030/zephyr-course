#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "../drivers/our_driver/our_driver.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    int ret, ret1;
    bool led_state = true;
    const struct device *driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
    struct sensor_value val;

    our_driver_custom_param(driver, 7);

    while (1) {
        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
	ret = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
        k_msleep(CONFIG_LED_HEARTBEAT_PERIOD_MS);
	ret = sensor_sample_fetch(driver);
	k_msleep(CONFIG_LED_HEARTBEAT_PERIOD_MS);
    }

    return 0;
}
