#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "api.h"
#include "api-asm.h"
#include <libopencm3/stm32/usart.h>

void glitch_loop(void);

#pragma GCC push_options
#pragma GCC optimize("O0")

#define LOOP_LENGTH 300
void glitch_loop() {
	printf_uart("Reset!\r\n");
	while(1) {
		uint32_t cnt = 0, i, j;
		for (i = 0; i < LOOP_LENGTH; i++)
		{
			for (j = 0; j < LOOP_LENGTH; j++)
			{
				cnt++;
			}
		}
		if (i != LOOP_LENGTH || j != LOOP_LENGTH ||
			cnt != (LOOP_LENGTH * LOOP_LENGTH))
		{
			printf_uart("Glitch! %u %u %u\r\n", i, j, cnt);
		} else {
			printf_uart("Normal %u %u %u\r\n", i, j, cnt);
		}
	}
	
	// Endless loop
	while(1) {}
}
#pragma GCC pop_options

int main(void) {
	// Uncomment to enable USART on PA9 (TX) and PA10 (RX)
	usart_setup();

	// Enable GPIOB clock
	rcc_periph_clock_enable(RCC_GPIOB);

	// Set PB13 as output
	gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);

	// Clear PB13
	gpio_clear(GPIOB, GPIO13);

	// Enter glitch loop
	glitch_loop();

	while(1) {
		// Toggle PB13
		gpio_toggle(GPIOB, GPIO13);
	}
}
