#include "ble_comm.h"

#define LOG_MODULE_NAME temp_sensor_ble
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

static K_SEM_DEFINE(bt_init_ok, 1, 1);

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME)-1)

static const struct bt_data adv_data[] = {
        BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
        BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN)
};

static const struct bt_data scan_resp_data[] = {
        BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_BLE_SERV_VAL),
};

/* Callbacks */ 
void bt_ready(int err)
{
    if(err)
    {
        LOG_ERR("bt_enable returned %d", err);
    }
    k_sem_give(&bt_init_ok);
}

int ble_init(void)
{
    int err;
    LOG_INF("Initializing BLE service XXXXXXXXXXXXXXX");
    
    err = bt_enable(bt_ready);

    if(err){
        LOG_ERR("bt_enable returned %d", err);
        return err;
    }

    k_sem_take(&bt_init_ok, K_FOREVER);

    err = bt_le_adv_start(BT_LE_ADV_CONN, adv_data, ARRAY_SIZE(adv_data), scan_resp_data, ARRAY_SIZE(scan_resp_data));

    if(err){
        LOG_ERR("couldn't start advertising, error: %d", err);
        return err;
    }

    return err;
}