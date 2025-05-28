#include "api.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <libopencm3/stm32/usart.h>

/* 

UART Notes

- The USART we are using is USART
- PA9 (pin 42) is set to TX
- PA10 (pin 43) is set to RX

*/
void usart_setup(void) {
	// Enable required clocks
	rcc_periph_clock_enable(CLOCK_USART_GPIO);
    rcc_periph_clock_enable(CLOCK_USART);
    rcc_periph_clock_enable(RCC_GPIOA);

    // Set USART parameters
    usart_set_baudrate(USART, 115200);
    usart_set_databits(USART, 8);
    usart_set_stopbits(USART, USART_STOPBITS_1);
    usart_set_mode(USART, USART_MODE_TX);
    usart_set_parity(USART, USART_PARITY_NONE);
    usart_set_flow_control(USART, USART_FLOWCONTROL_NONE);

	// Setup IO
	gpio_mode_setup(PORT_USART, GPIO_MODE_AF, GPIO_PUPD_NONE, PIN_TX | PIN_RX);

	// AF stands for alternate function. AF7 is USART for these pins
	// according to the datasheet.
	gpio_set_af(PORT_USART, GPIO_AF7, PIN_TX | PIN_RX);

    // Enable USART
    usart_enable(USART);
}


void write_uart(char *buf, size_t length) {
	for (size_t i = 0; i < length; i++) {
        usart_send_blocking(USART, buf[i]);
        usart_wait_send_ready (USART);
        while(!usart_get_flag(USART, USART_SR_TC));
	}
}


void usart_send_string(const char *str) {
    while (*str) {
        usart_send_blocking(USART, *str);
		usart_wait_send_ready (USART);
		while(!usart_get_flag(USART, USART_SR_TC));
        str++;
    }
}


void print_uart(char *buf)
{
	int msg_len = strlen(buf);

    write_uart(buf, msg_len);
}

void printf_uart(const char *format, ...) {
    char buffer[256];
    va_list args;

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    buffer[sizeof(buffer) - 1] = '\0';  // Ensure null-termination
    print_uart(buffer);
}

void putchar_uart(char c) {
	usart_send_blocking(USART, c);
		usart_wait_send_ready (USART);
		while(!usart_get_flag(USART, USART_SR_TC));
}