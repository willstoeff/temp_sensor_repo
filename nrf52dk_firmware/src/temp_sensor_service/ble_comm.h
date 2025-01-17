#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci.h>

#define BT_UUID_BLE_SERV_VAL \
    BT_UUID_128_ENCODE(0x6d750001, 0x5d2a, 0x4fa8, 0x8339, 0x2573a30cefff)

#define BT_UUID_BLE_SERVICE BT_UUID_DECLARE_128(BT_UUID_BLE_SERV_VAL) 


int ble_init(void);