#define event_handler_c_
#include <stdio.h>
#include <string.h>
#include "event_handler.h"
//-----------------------------------------

static const char *TAG = "event_handler";

/*重新连接热点*/
void WIFI_EVENT_STA_DISCONNECTED_FUN(void)
{
    esp_wifi_connect();//连接热点
    ESP_LOGI(TAG,"connect to the AP fail");
}

/*有设备连接上ESP32的热点*/
void WIFI_EVENT_AP_STACONNECTED_FUN( void* event_data  )
{
    wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
    /*打印连接设备的MAC地址*/
    ESP_LOGI(TAG, "station "MACSTR" join, AID=%d", MAC2STR(event->mac), event->aid);
}

/*有设备断开和ESP32的热点*/
void WIFI_EVENT_AP_STADISCONNECTED_FUN( void* event_data  )
{
    wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
    /*打印断开设备的MAC地址*/
    ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",MAC2STR(event->mac), event->aid);
}

/*连接上路由器(获取到了分配的IP地址)*/
void IP_EVENT_STA_GOT_IP_FUN( void* event_data )
{
    ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
    ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
}


/*WiFi事件回调*/
void wifi_event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data)
{
    /* 事件剥离 */
    if( event_base == WIFI_EVENT )
    {
        switch ( event_id )
        {
            case WIFI_EVENT_STA_START:          esp_wifi_connect();                  break; // STA START
            case WIFI_EVENT_STA_STOP:           ESP_LOGI(TAG,"WIFI_EVENT_STA_STOP"); break; // STA STOP 
            case WIFI_EVENT_STA_DISCONNECTED:   WIFI_EVENT_STA_DISCONNECTED_FUN();   break; //和路由器断开
            case WIFI_EVENT_AP_START:           ESP_LOGI(TAG,"WIFI_EVENT_AP_START"); break; // AP  START 
            case WIFI_EVENT_AP_STOP:            ESP_LOGI(TAG,"WIFI_EVENT_AP_STOP");  break; // AP  STOP
            case WIFI_EVENT_AP_STACONNECTED:    WIFI_EVENT_AP_STACONNECTED_FUN( event_data );    break; //有设备连接上ESP32的热点
            case WIFI_EVENT_AP_STADISCONNECTED: WIFI_EVENT_AP_STADISCONNECTED_FUN(event_data );  break; //有设备断开和ESP32的热点                    
            default:  break;
        }
    }
    else if( event_base == IP_EVENT )  // 路由事件ID 组
    {
        switch ( event_id )
        {
            case IP_EVENT_STA_GOT_IP:        IP_EVENT_STA_GOT_IP_FUN(event_data);       break; //获取到指定IP
            case IP_EVENT_STA_LOST_IP:       ESP_LOGI(TAG,"IP_EVENT_STA_LOST_IP");      break;
            case IP_EVENT_AP_STAIPASSIGNED:  ESP_LOGI(TAG,"IP_EVENT_AP_STAIPASSIGNED"); break;
            default:  break;
        }
    }
}