#define wifi_softap_c_
#include <stdio.h>
#include <string.h>
#include "wifi_softap.h"
//-----------------------------------------



#define EXAMPLE_ESP_WIFI_SSID      "ESP32_WIFI"  //设置模块发出的无线名称
#define EXAMPLE_ESP_WIFI_PASS      "11223344"    //无线密码
#define EXAMPLE_ESP_WIFI_CHANNEL   11            //信道(默认1)
#define EXAMPLE_MAX_STA_CONN       5             //最大连接数(最大10个)


void wifi_init_softap(void)
{
    esp_netif_create_default_wifi_ap();//创建有 TCP/IP 堆栈的默认网络接口实例绑定AP。

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));//创建 Wi-Fi 驱动程序任务，并初始化 Wi-Fi 驱动程序。


    /*注册系统事件回调函数*/
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,           //WiFi事件函数
                                                        ESP_EVENT_ANY_ID,     //事件ID
                                                        &wifi_event_handler,  //回调函数
                                                        NULL,
                                                        NULL));
    /*配置热点*/
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,             
            .ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
            .channel = EXAMPLE_ESP_WIFI_CHANNEL,
            .password = EXAMPLE_ESP_WIFI_PASS,
            .max_connection = EXAMPLE_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };
    /*如果密码长度是0,则不设置密码*/
    if (strlen(EXAMPLE_ESP_WIFI_PASS) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));//设置AP模式
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));//配置AP参数
    ESP_ERROR_CHECK(esp_wifi_start());//启动
}