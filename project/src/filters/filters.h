#ifndef _FILTERS_H_
#define _FILTERS_H_

uint8_t* median_filter(uint8_t *dest, uint8_t *source, uint8_t start, uint8_t end, uint8_t n, uint8_t bias);
uint8_t* threshold_filter(uint8_t *dest, uint8_t *source, uint8_t start, uint8_t end, uint8_t thres, uint8_t gap);
uint8_t median(uint8_t n, uint8_t x[]);
uint8_t minimum(uint8_t* array, uint8_t start, uint8_t end);

#endif // _FILTERS_H_