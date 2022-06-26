#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "pico/binary_info.h"

const uint LED_PIN = 25;

int main(){
    
    stdio_init_all();
    
    // Initialise UART0 and UART1
    uart_init(uart0, 9600);
    uart_init(uart1, 9600);
    
    // Set GPIO pin mux to the UART - 0 is TX, 1 is RX
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);
    
    // Set GPIO pin mux to the UART - 4 is TX, 5 is RX
    gpio_set_function(4, GPIO_FUNC_UART);
    gpio_set_function(5, GPIO_FUNC_UART);
    
    bi_decl(bi_program_description("This is a test binary"));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));
    
    bi_decl(bi_1pin_with_func(0, GPIO_FUNC_UART));
    bi_decl(bi_1pin_with_func(1, GPIO_FUNC_UART));
    bi_decl(bi_1pin_with_func(4, GPIO_FUNC_UART));
    bi_decl(bi_1pin_with_func(5, GPIO_FUNC_UART));

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    uint8_t buff[20] = {0};
    
    gpio_put(LED_PIN, 0);

    while (1)
    {   
        uart_read_blocking(uart0, buff, 2);
        uart_write_blocking(uart1, buff, 2);
    }
    
}
