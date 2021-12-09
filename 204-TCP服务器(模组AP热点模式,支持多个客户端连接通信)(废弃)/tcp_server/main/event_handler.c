#define event_handler_c_
#include <stdio.h>
#include <string.h>
#include "event_handler.h"
//-----------------------------------------



static const char *TAG = "event_handler";
/*WiFi事件回调*/
void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {//有设备连接上ESP32的热点
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        /*打印连接设备的MAC地址*/
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d", MAC2STR(event->mac), event->aid);
    } 
    else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;

        /*打印断开设备的MAC地址*/
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",MAC2STR(event->mac), event->aid);
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {//配置好了wifi的STA模式
        esp_wifi_connect();//连接热点
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {//和路由器断开
        esp_wifi_connect();//连接热点
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {//连接上路由器(获取到了分配的IP地址)
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
    }
}