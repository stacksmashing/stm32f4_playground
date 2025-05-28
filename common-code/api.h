#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>

#define USART USART1
#define PORT_USART GPIOA
#define CLOCK_USART_GPIO RCC_GPIOA
#define CLOCK_USART RCC_USART1
#define PIN_TX GPIO9
#define PIN_RX GPIO10

void usart_setup(void);
void usart_send_string(const char *str);

void printf_uart(const char *format, ...);
void print_uart(char *buf);
void write_uart(char *buf, size_t length);
void putchar_uart(char c);
void deobfuscate(unsigned char *data, unsigned int len, unsigned char key);
