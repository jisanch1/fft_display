#ifndef CBUF_H
#define CBUF_H

struct cbuf {
	char *buf;
	uint16_t size;
	uint16_t in;
	uint16_t out;
	uint16_t n;
};


void cbuf_create(struct cbuf *cb, char *buf, uint16_t size);
void cbuf_put(struct cbuf *cb, char ch);
char cbuf_get(struct cbuf *cb);
void cbuf_clear(struct cbuf *cb);

#endif /* CBUF_H */