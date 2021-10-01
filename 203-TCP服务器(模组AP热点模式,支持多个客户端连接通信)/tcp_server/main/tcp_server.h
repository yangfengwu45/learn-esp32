#ifndef tcp_server_h_
#define tcp_server_h_

#ifndef tcp_server_c_
#define tcp_server_cx_ extern
#else
#define tcp_server_cx_
#endif


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#define CONFIG_EXAMPLE_IPV4
#define TCP_SERVER_PORT 8080   //服务器监听的端口号

#define TCP_SERVER_MAX_COUNT 6    //设置最大支持的TCP客户端连接个数(超过6需要用户自己增加回调函数)
#define TCP_SERVER_MIN_PRIORITY 8 //客户端接收数据任务最低优先级(6个客户端的优先级分别为: 8,9,10,11,12,13)

typedef void(*tcp_client_recv_callback)(void *pvParameters);//定义一个函数指针类型

typedef struct tcp_server_typedef_struct
{
    char state;//状态
    int  sock_id;
    tcp_client_recv_callback tcp_client_recv_cb;//存储tcp接收函数地址
} tcp_server_struct;

tcp_server_cx_ tcp_server_struct tcp_server_struct_value[TCP_SERVER_MAX_COUNT];



void tcp_server(void);


#endif