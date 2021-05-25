/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "esp_system.h"
#include "test1.h"
#include "test2.h"
#include "test3.h"

extern int test1_value;

extern int test3_value;

void app_main(void)
{
    printf("test3_value = %d!\n",test3_value);
    test1_value = 2;
    test1_fun();
    printf("Hello world!\n");
}
