#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "i2c-lcd.h"

static const char *TAG = "i2c-simple-example";

char temp[10];
char hum [10];
float t = 38.5;
float h = 10.5;

/**
 * @brief i2c master initialization
 */
static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_NUM_0;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = GPIO_NUM_21,
        .scl_io_num = GPIO_NUM_22,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, 0, 0, 0);
}


void app_main(void)
{
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");

    lcd_init();
    lcd_clear();

    //lcd_put_cur(0, 0);
    //lcd_send_string("factos!!!");
    //lcd_put_cur(1, 0);
    //lcd_send_string("tao depzai vcl !!!");

    sprintf(temp, "temp: %.1f", t);
    lcd_put_cur(0, 0);
    lcd_send_string(temp);

    sprintf(hum,"hum: %.1f", h);
    lcd_put_cur(1,0);
    lcd_send_string(hum);
}
