#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

#define LED_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

// Get my GPIO data
static int our_driver_channel_get(const struct device *dev,
                                  enum sensor_channel chan,
                                  struct sensor_value *val) {

    LOG_INF("Hello From our_driver_channel_get %d", chan);
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    return 0;
}

static int our_driver_sample_fetch(const struct device *dev,
		                   enum sensor_channel chan) {

    LOG_INF("Hello From our_driver_sample_fetch %d", chan);
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);

    return 0;
}

// Link the driver with function pointer of structure declared
static DEVICE_API(sensor, api_our_driver) = {
    .channel_get = our_driver_channel_get,
    .sample_fetch = our_driver_sample_fetch,
};

// Init Function
static int init(const struct device* dev) {
    LOG_INF("Device Initialized");

    if (!gpio_is_ready_dt(&led)) {
        LOG_ERR("LED node not ready");
	return -ENODEV;
    }

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) {
        LOG_ERR("Failed to configure LED");
	return -ENODEV;
    }

    return 0;
}

// To make the instance of our driver
// 0 -> zeroth instance
DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_our_driver);
