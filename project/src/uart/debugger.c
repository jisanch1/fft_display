#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdarg.h>	
#include "uart.h"
#include "debugger.h"


static char tx_buffer[TX_BUF_SIZE];
static char* tx_pos;

void dbg_init(uint32_t baud)
{
	uart_default_conf();
	uart_set_baudrate(baud);
	uart_enable_tx();
	tx_pos = tx_buffer;
}

void dbg_printf(const char *format, ...)
{
	va_list arg;
	va_start(arg, format);
	vsnprintf(tx_buffer, TX_BUF_SIZE, format, arg);
	va_end(arg);
	uart_enable_empty_register_interrupt();
}

void dbg_send_next(void)
{
	if (*tx_pos)	// si hay algo por mandar
	{
		uart_send_char(*tx_pos++);
	}
	else // Se limpia el buffer
	{
		tx_buffer[0] = '\0';
		tx_pos = tx_buffer;
		uart_disable_empty_register_interrupt();
	}
}

ISR(USART_UDRE_vect)
{
	dbg_send_next();
}