#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include "ble_comm.h"

#define LOG_MODULE_NAME app
LOG_MODULE_REGISTER(LOG_MODULE_NAME);


static const struct device *get_ds18b20_device(void);

int main(void)
{
    int res;
    int err;

    const struct device *sensor_dev = get_ds18b20_device();
	err = ble_init();
    

	if (sensor_dev == NULL) {
		return 0;
	}
    if (err) {
        LOG_ERR("BLE init error %d", err);
		return 0;
	}

    LOG_INF("BLE Running...");


	// while (true) {
	// 	struct sensor_value temp;
	
	// 	res = sensor_sample_fetch(sensor_dev);
	// 	if (res != 0) {
	// 		printk("sample_fetch() failed: %d\n", res);
	// 		return res;
	// 	}

	// 	res = sensor_channel_get(sensor_dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
	// 	if (res != 0) {
	// 		printk("channel_get() failed: %d\n", res);
	// 		return res;
	// 	}

	// 	printk("Temp: %d.%06d\n", temp.val1, temp.val2);
	// 	k_sleep(K_MSEC(2000));
	// }
    return 0;
}

// Gets DS18B20 from device tree
static const struct device *get_ds18b20_device(void)
{
	const struct device *const dev = DEVICE_DT_GET_ANY(maxim_ds18b20);

	if (dev == NULL) {
		/* No such node, or the node does not have status "okay". */
		printk("\nError: no device found.\n");
		return NULL;
	}

	if (!device_is_ready(dev)) {
		printk("\nError: Device \"%s\" is not ready; "
		       "check the driver initialization logs for errors.\n",
		       dev->name);
		return NULL;
	}

	printk("Found device \"%s\", getting sensor data\n", dev->name);
	return dev;
}