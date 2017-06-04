#include <avr/io.h>
#include "cbuf.h"


void cbuf_create(struct cbuf *cb, char *buf, uint16_t size)
{
	cb->buf = buf;
	cb->size = size;
	cbuf_clear(cb);
}

void cbuf_put(struct cbuf *cb, char ch)
{
	cb->buf[cb->in++] = ch;
	cb->n++;
	cb->in %= cb->size;
}

char cbuf_get(struct cbuf *cb)
{
	char ch = 0x00;
	if (cb->n > 0)
	{
		ch = cb->buf[cb->out++];
		cb->n--;
		cb->out %= cb->size;
	}
	return ch;
}

void cbuf_clear(struct cbuf *cb)
{
	cb->in = 0;
	cb->out = 0;
	cb->n = 0;
	cb->buf[0] = 0x00;
}