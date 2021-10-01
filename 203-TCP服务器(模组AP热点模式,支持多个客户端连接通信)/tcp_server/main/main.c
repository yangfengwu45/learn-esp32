#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "wifi_softap.h"
#include "tcp_server.h"

void app_main(void)
{
    //初始化 NVS(配置WiFi的参数存储需要用到NVS)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    //初始化内部的lwip
    ESP_ERROR_CHECK(esp_netif_init());
    //创建系统事件任务
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    //初始化AP热点
    wifi_init_softap();
    //创建TCP服务器
    tcp_server();
}