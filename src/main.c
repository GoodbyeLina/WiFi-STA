#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "wifi_sta.h"
#include "uart.h"
#include "i2c.h"
#include "led.h"

int main() {

    stdio_init_all();

    led_init();
    init_uart();

    // 初始化显示屏
    SSD1306_i2c_init();
    SSD1306_init();
    
    SSD1306_WriteStrings();

    // 先将数据发送到ESP8285
    configure_esp8285();
    uint8_t send_data[] = {0x11, 0x22, 0x33};
    send_data_to_esp8285(send_data, sizeof(send_data));

    // 可以在这里等待接收端的反馈等操作（可选）

    while (1){

        led_blink_ms(500);    
        
        // 手柄段发送数据
        send_data_to_esp8285(text, sizeof(text));
    
        // 接收从监视狗返回的标志，看是否接收完毕
        received_size = receive_data_from_esp8285(receive_buffer, RECEIVE_BUFFER_SIZE);
        if (received_size > 0) {
            // 在这里可以对接收到的数据进行处理，比如打印查看内容等
            printf("Received data from ESP8285, size: %d\n", received_size);
            for (int i = 0; i < received_size; i++) {
                printf("0x%02X ", receive_buffer[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
