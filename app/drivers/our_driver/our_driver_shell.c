#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell.h>

static const struct device *led_dev = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

static int cmd_sensor_fetch(const struct shell *sh, size_t argc, char **argv)
{
    sensor_sample_fetch(led_dev);
    shell_info(sh, "Sensor sample Fetch executed");
    return 0;
}

static int cmd_sensor_read(const struct shell *sh, size_t argc, char **argv)
{
    struct sensor_value val;
    sensor_channel_get(led_dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    shell_fprintf(sh, SHELL_INFO, "Sensor channel get Temperature: %d\n", val.val1);
    return 0;
}

static int cmd_sensor_info(const struct shell *sh, size_t argc, char **argv)
{
    shell_fprintf(sh, SHELL_INFO, "Device name: %s and State: %d\n", led_dev->name, device_is_ready(led_dev));
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sensor_subcmd, 
    SHELL_CMD(fetch, NULL, "Sensor Fetch", cmd_sensor_fetch),
    SHELL_CMD(read, NULL, "Sensor Read", cmd_sensor_read),
    SHELL_CMD(info, NULL, "Sensor Info", cmd_sensor_info),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sensor_subcmd, "Sensor commands", NULL);
