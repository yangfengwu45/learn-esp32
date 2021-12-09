#define tcp_server_c_

#include <string.h>
#include <sys/param.h>
#include "tcp_server.h"


static const char *TAG = "example";

//信号量
SemaphoreHandle_t TaskToTrqSemaphoreCounting;



void tcp_server_send(char *data,int len)
{
    int i;
    for(i=0;i<TCP_SERVER_MAX_COUNT;i++)
    {
        if(tcp_server_struct_value[i].state == 1)//该客户端是连接的
        {
            /*给对应客户端的socket id 发送数据*/
            send(tcp_server_struct_value[i].sock_id, data, len, 0);
        }
    }
}

void tcp_client0_recv(void *pvParameters)
{
    int len;
    char rx_buffer[128];
    int sock=tcp_server_struct_value[0].sock_id;
    do {
        len = recv(sock, rx_buffer, sizeof(rx_buffer)-1, 0);
        if (len < 0) {
            ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
        } else if (len == 0) {
            ESP_LOGW(TAG, "Connection closed");
        } else {
            rx_buffer[len] = 0; // Null-terminate whatever is received and treat it like a string
            ESP_LOGI(TAG, "Received %d bytes: %s", len, rx_buffer);

            // send() can return less bytes than supplied length.
            // Walk-around for robust implementation. 
            int to_write = len;
            while (to_write > 0) {
                int written = send(sock, rx_buffer + (len - to_write), to_write, 0);
                if (written < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                }
                to_write -= written;
            }
        }
    } while (len > 0);

    tcp_server_struct_value[0].state=0;
    xSemaphoreGive(TaskToTrqSemaphoreCounting);
    shutdown(sock, 0);
    close(sock);
    vTaskDelete(NULL);
}

void tcp_client1_recv(void *pvParameters)
{
    int len;
    char rx_buffer[128];
    int sock=tcp_server_struct_value[1].sock_id;
    do {
        len = recv(sock, rx_buffer, sizeof(rx_buffer)-1, 0);
        if (len < 0) {
            ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
        } else if (len == 0) {
            ESP_LOGW(TAG, "Connection closed");
        } else {
            rx_buffer[len] = 0; // Null-terminate whatever is received and treat it like a string
            ESP_LOGI(TAG, "Received %d bytes: %s", len, rx_buffer);

            // send() can return less bytes than supplied length.
            // Walk-around for robust implementation. 
            int to_write = len;
            while (to_write > 0) {
                int written = send(sock, rx_buffer + (len - to_write), to_write, 0);
                if (written < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                }
                to_write -= written;
            }
        }
    } while (len > 0);

    tcp_server_struct_value[1].state=0;
    xSemaphoreGive(TaskToTrqSemaphoreCounting);
    shutdown(sock, 0);
    close(sock);
    vTaskDelete(NULL);
}

void tcp_client2_recv(void *pvParameters)
{
    int len;
    char rx_buffer[128];
    int sock=tcp_server_struct_value[2].sock_id;
    do {
        len = recv(sock, rx_buffer, sizeof(rx_buffer)-1, 0);
        if (len < 0) {
            ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
        } else if (len == 0) {
            ESP_LOGW(TAG, "Connection closed");
        } else {
            rx_buffer[len] = 0; // Null-terminate whatever is received and treat it like a string
            ESP_LOGI(TAG, "Received %d bytes: %s", len, rx_buffer);

            // send() can return less bytes than supplied length.
            // Walk-around for robust implementation. 
            int to_write = len;
            while (to_write > 0) {
                int written = send(sock, rx_buffer + (len - to_write), to_write, 0);
                if (written < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                }
                to_write -= written;
            }
        }
    } while (len > 0);

    tcp_server_struct_value[2].state=0;
    xSemaphoreGive(TaskToTrqSemaphoreCounting);
    shutdown(sock, 0);
    close(sock);
    vTaskDelete(NULL);
}

void tcp_client3_recv(void *pvParameters)
{
    int len;
    char rx_buffer[128];
    int sock=tcp_server_struct_value[3].sock_id;
    do {
        len = recv(sock, rx_buffer, sizeof(rx_buffer)-1, 0);
        if (len < 0) {
            ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
        } else if (len == 0) {
            ESP_LOGW(TAG, "Connection closed");
        } else {
            rx_buffer[len] = 0; // Null-terminate whatever is received and treat it like a string
            ESP_LOGI(TAG, "Received %d bytes: %s", len, rx_buffer);

            // send() can return less bytes than supplied length.
            // Walk-around for robust implementation. 
            int to_write = len;
            while (to_write > 0) {
                int written = send(sock, rx_buffer + (len - to_write), to_write, 0);
                if (written < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                }
                to_write -= written;
            }
        }
    } while (len > 0);

    tcp_server_struct_value[3].state=0;
    xSemaphoreGive(TaskToTrqSemaphoreCounting);
    shutdown(sock, 0);
    close(sock);
    vTaskDelete(NULL);
}

void tcp_client4_recv(void *pvParameters)
{
    int len;
    char rx_buffer[128];
    int sock=tcp_server_struct_value[4].sock_id;
    do {
        len = recv(sock, rx_buffer, sizeof(rx_buffer)-1, 0);
        if (len < 0) {
            ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
        } else if (len == 0) {
            ESP_LOGW(TAG, "Connection closed");
        } else {
            rx_buffer[len] = 0; // Null-terminate whatever is received and treat it like a string
            ESP_LOGI(TAG, "Received %d bytes: %s", len, rx_buffer);

            // send() can return less bytes than supplied length.
            // Walk-around for robust implementation. 
            int to_write = len;
            while (to_write > 0) {
                int written = send(sock, rx_buffer + (len - to_write), to_write, 0);
                if (written < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                }
                to_write -= written;
            }
        }
    } while (len > 0);

    tcp_server_struct_value[4].state=0;
    xSemaphoreGive(TaskToTrqSemaphoreCounting);
    shutdown(sock, 0);
    close(sock);
    vTaskDelete(NULL);
}

void tcp_client5_recv(void *pvParameters)
{
    int len;
    char rx_buffer[128];
    int sock=5;
    do {
        len = recv(sock, rx_buffer, sizeof(rx_buffer)-1, 0);
        if (len < 0) {
            ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
        } else if (len == 0) {
            ESP_LOGW(TAG, "Connection closed");
        } else {
            rx_buffer[len] = 0; // Null-terminate whatever is received and treat it like a string
            ESP_LOGI(TAG, "Received %d bytes: %s", len, rx_buffer);

            // send() can return less bytes than supplied length.
            // Walk-around for robust implementation. 
            int to_write = len;
            while (to_write > 0) {
                int written = send(sock, rx_buffer + (len - to_write), to_write, 0);
                if (written < 0) {
                    ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                }
                to_write -= written;
            }
        }
    } while (len > 0);

    tcp_server_struct_value[5].state=0;
    xSemaphoreGive(TaskToTrqSemaphoreCounting);
    shutdown(sock, 0);
    close(sock);
    vTaskDelete(NULL);
}



static void tcp_server_task(void *pvParameters)
{
    int i;
    char addr_str[128];
    int addr_family = (int)pvParameters;
    int ip_protocol = 0;
    struct sockaddr_in6 dest_addr;
    if (addr_family == AF_INET) {
        struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
        dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
        dest_addr_ip4->sin_family = AF_INET;
        dest_addr_ip4->sin_port = htons(TCP_SERVER_PORT);
        ip_protocol = IPPROTO_IP;
    } else if (addr_family == AF_INET6) {
        bzero(&dest_addr.sin6_addr.un, sizeof(dest_addr.sin6_addr.un));
        dest_addr.sin6_family = AF_INET6;
        dest_addr.sin6_port = htons(TCP_SERVER_PORT);
        ip_protocol = IPPROTO_IPV6;
    }
    int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
    if (listen_sock < 0) {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        vTaskDelete(NULL);
        return;
    }
#if defined(CONFIG_EXAMPLE_IPV4) && defined(CONFIG_EXAMPLE_IPV6)
    // Note that by default IPV6 binds to both protocols, it is must be disabled
    // if both protocols used at the same time (used in CI)
    int opt = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt(listen_sock, IPPROTO_IPV6, IPV6_V6ONLY, &opt, sizeof(opt));
#endif

    ESP_LOGI(TAG, "Socket created");

    int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err != 0) {
        ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        ESP_LOGE(TAG, "IPPROTO: %d", addr_family);
        goto CLEAN_UP;
    }
    ESP_LOGI(TAG, "Socket bound, port %d", TCP_SERVER_PORT);

    err = listen(listen_sock, 1);
    if (err != 0) {
        ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
        goto CLEAN_UP;
    }

    //创建信号量
    TaskToTrqSemaphoreCounting=xSemaphoreCreateCounting( TCP_SERVER_MAX_COUNT, TCP_SERVER_MAX_COUNT );
    struct sockaddr_in6 source_addr; // Large enough for both IPv4 or IPv6
    uint addr_len = sizeof(source_addr);

    for(i=0;i<TCP_SERVER_MAX_COUNT;i++) tcp_server_struct_value[i].state=0;

    /*如果修改了客户端个数,需要修改这个地方,设置回调函数*/
    tcp_server_struct_value[0].tcp_client_recv_cb = tcp_client0_recv;
    tcp_server_struct_value[1].tcp_client_recv_cb = tcp_client1_recv;
    tcp_server_struct_value[2].tcp_client_recv_cb = tcp_client2_recv;
    tcp_server_struct_value[3].tcp_client_recv_cb = tcp_client3_recv;
    tcp_server_struct_value[4].tcp_client_recv_cb = tcp_client4_recv;
    tcp_server_struct_value[5].tcp_client_recv_cb = tcp_client5_recv;

    while (1) {

        //获取一个信号量
        if(xSemaphoreTake(TaskToTrqSemaphoreCounting,portMAX_DELAY))
        {
            ESP_LOGI(TAG, "Socket listening");
            int sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);//等待客户端连接
            if (sock < 0) {
                ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
                break;
            }
            // Convert ip address to string
            if (source_addr.sin6_family == PF_INET) {
                inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr.s_addr, addr_str, sizeof(addr_str) - 1);
            } else if (source_addr.sin6_family == PF_INET6) {
                inet6_ntoa_r(source_addr.sin6_addr, addr_str, sizeof(addr_str) - 1);
            }
            ESP_LOGI(TAG, "Socket id =%d accepted ip address: %s", sock,addr_str);


            for(i=0;i<TCP_SERVER_MAX_COUNT;i++)
            {
                if(tcp_server_struct_value[i].state==0)
                {
                    tcp_server_struct_value[i].state=1;
                    tcp_server_struct_value[i].sock_id = sock;
                    xTaskCreate(tcp_server_struct_value[i].tcp_client_recv_cb, "tcp_server_client", 4096, (void*)&tcp_server_struct_value[i], TCP_SERVER_MIN_PRIORITY+i, NULL);  
                    break;     
                }
            }
        }
    }

CLEAN_UP:
    close(listen_sock);
    vTaskDelete(NULL);
}

void tcp_server(void)
{
    #ifdef CONFIG_EXAMPLE_IPV4
        xTaskCreate(tcp_server_task, "tcp_server", 4096, (void*)AF_INET, 12, NULL);
    #endif
    #ifdef CONFIG_EXAMPLE_IPV6
        xTaskCreate(tcp_server_task, "tcp_server", 4096, (void*)AF_INET6, 5, NULL);
    #endif
}
