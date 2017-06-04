#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

#define TX_BUF_SIZE	128

void dbg_init(uint32_t baud);
void dbg_printf(const char *format, ...);
void dbg_send_next(void);

#endif /* _DEBUGGER_H_ */