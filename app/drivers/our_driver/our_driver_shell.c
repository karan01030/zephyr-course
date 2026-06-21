#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell.h>
#include "our_driver.h"

static const struct device *led_dev = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

static int cmd_sensor_fetch(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    sensor_sample_fetch(led_dev);
    shell_info(sh, "Sensor sample Fetch executed");
<<<<<<< HEAD
    struct our_driver_t *data = led_dev->data;
=======
    our_driver_t *data = led_dev->data;
>>>>>>> 46a9047 (Custom extension API for lesson 7)
    shell_fprintf(sh, SHELL_INFO, "Blink counter = %d\n", data->param);
    return 0;
}

static int cmd_sensor_read(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    struct sensor_value val;
    sensor_channel_get(led_dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    shell_fprintf(sh, SHELL_INFO, "Sensor channel get Temperature: %d\n", val.val1);
    return 0;
}

static int cmd_sensor_info(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    shell_fprintf(sh, SHELL_INFO, "Device name: %s and State: %d\n", led_dev->name, device_is_ready(led_dev));
    return 0;
}

static int cmd_sensor_set_value(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);
    int error_code;
    long value_received = shell_strtol(argv[1], 10, &error_code);

    if (value_received < 0) {
        shell_error(sh, "The value to set must be great than 0");
        return -EINVAL;
    } else if (value_received > 200) {
        shell_error(sh, "The value to set must be less than 200");
        return -EINVAL;
    }

    uint8_t value_set = (uint8_t)value_received;
    shell_fprintf(sh, SHELL_INFO, "Value Received: %d\n", value_set);

    our_driver_custom_param(led_dev, value_set);
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sensor_subcmd, 
    SHELL_CMD(fetch, NULL, "Sensor Fetch", cmd_sensor_fetch),
    SHELL_CMD(read, NULL, "Sensor Read", cmd_sensor_read),
    SHELL_CMD(info, NULL, "Sensor Info", cmd_sensor_info),
    SHELL_CMD_ARG(set, NULL, "Sensor Set Value", cmd_sensor_set_value, 2, 0),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sensor_subcmd, "Sensor commands", NULL);
