#define wifi_softap_c_
#include <stdio.h>
#include <string.h>
#include "wifi_softap_sta.h"
//-----------------------------------------


/*配置模组自身的无线热点*/
#define ESP_WIFI_AP_SSID       "ESP32_WIFI"  //设置模块发出的无线名称
#define ESP_WIFI_AP_PASS       "11223344"    //无线密码
#define ESP_WIFI_AP_CHANNEL    11            //信道(默认1)
#define ESP_WIFI_AP_MAX_COUNT  5             //最大连接数(最大10个)


/*配置模组连接的路由器*/
#define ESP_WIFI_STA_SSID       "QQQQQ"  //设置模块发出的无线名称
#define ESP_WIFI_STA_PASS       "11223344"    //无线密码


void wifi_init_softap(void)
{
    esp_event_handler_instance_t instance_any_id = {0};  //处理ID 实例句柄
    esp_event_handler_instance_t instance_got_ip = {0};  //处理IP 实例句柄

    esp_netif_create_default_wifi_ap();//创建有 TCP/IP 堆栈的默认网络接口实例绑定AP。
    esp_netif_create_default_wifi_sta();//创建有 TCP/IP 堆栈的默认网络接口实例绑定STA。

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));//创建 Wi-Fi 驱动程序任务，并初始化 Wi-Fi 驱动程序。


    /*注册系统事件回调函数*/
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,           //WiFi事件函数
                                                        ESP_EVENT_ANY_ID,     //事件ID
                                                        &wifi_event_handler,  //回调函数
                                                        NULL,
                                                        &instance_any_id));
    /*注册系统事件回调函数*/
    ESP_ERROR_CHECK( esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        &instance_got_ip) );

    
    /*配置连接的热点参数*/
    wifi_config_t wifi_config_sta = {
        .sta = {
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,//加密方式
            /*配置pmf,当前最新加密技术*/
            .pmf_cfg = {
                .capable = true,  //告诉热点这边有能力使用PMF进行加密通信(防止窃听密码)
                .required = false //告诉热点这边不强制要求使用PMF进行加密通信(防止窃听密码)
            },
        },
    };
    strcpy( (char *) wifi_config_sta.sta.ssid     ,  ESP_WIFI_STA_SSID );
    if(strlen(ESP_WIFI_STA_PASS)==0)//没有密码
    {
        wifi_config_sta.sta.threshold.authmode = WIFI_AUTH_OPEN;//加密方式
    }
    else{
        strcpy( (char *) wifi_config_sta.sta.password ,  ESP_WIFI_STA_PASS);
    }
    
    

    /*配置热点*/
    wifi_config_t wifi_config_ap = {
        .ap = {
            // .ssid = ESP_WIFI_AP_SSID,             
            // .ssid_len = strlen(ESP_WIFI_AP_SSID),
            .channel = ESP_WIFI_AP_CHANNEL,
            // .password = ESP_WIFI_AP_PASS,
            .max_connection = ESP_WIFI_AP_MAX_COUNT,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };
    strcpy( (char *) wifi_config_ap.ap.ssid , ESP_WIFI_AP_SSID );
    wifi_config_ap.ap.ssid_len = strlen(ESP_WIFI_AP_SSID);
    strcpy( (char *) wifi_config_ap.ap.password ,  ESP_WIFI_AP_PASS);


    /*如果密码长度是0,则不设置密码*/
    if (strlen(ESP_WIFI_AP_PASS) == 0) {
        wifi_config_ap.ap.authmode = WIFI_AUTH_OPEN;
    }


    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));//设置AP+STA模式

    // 设置AP模式配置
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP , &wifi_config_ap) );
	// 设置STA模式配置
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config_sta) );

    ESP_ERROR_CHECK(esp_wifi_start());//启动
}