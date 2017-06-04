#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

#define TX_BUF_SIZE	256


void dbg_init(uint32_t baud);
void dbg_printf(const char *format, ...);
void dbg_send_char(char ch);

#endif /* _DEBUGGER_H_ */