#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdarg.h>	
#include "uart.h"
#include "cbuf.h"
#include "debugger.h"


static char tx_buffer[TX_BUF_SIZE];

void dbg_init(uint32_t baud)
{
	uart_default_conf();
	uart_set_baudrate(baud);
	uart_enable_tx();

}

void dbg_printf(const char *format, ...)
{
	uint8_t j, n;
	va_list arg;
	va_start(arg, format);
	n = vsnprintf(tx_buffer, TX_BUF_SIZE, format, arg);
	va_end(arg);
	for (j = 0; j < n; j++) {
		uart_send_char(tx_buffer[j]);
	}
}

void dbg_send_char(char ch)
{
	uart_send_char(ch);
}

