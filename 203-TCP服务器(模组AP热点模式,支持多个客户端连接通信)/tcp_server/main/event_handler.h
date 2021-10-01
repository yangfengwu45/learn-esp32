#ifndef event_handler_h_
#define event_handler_h_

#ifndef event_handler_c_
#define event_handler_c_ extern
#else
#define event_handler_c_
#endif


#include "esp_system.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "wifi_softap.h"

/*WiFi事件回调*/
void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data);


#endif