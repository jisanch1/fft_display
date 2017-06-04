#include <avr/io.h>
#include <string.h>
#include "filters.h"

uint8_t* median_filter(uint8_t *dest, uint8_t *source, uint8_t start, uint8_t end, uint8_t n, uint8_t bias)
{
	uint8_t i;
	uint8_t temp_buf[n];
	for (i = start; i <= end; i++)
	{
		memcpy(temp_buf, source + i - start + bias, n);
		dest[i] = median(n, temp_buf);
	}
	return dest;
}

uint8_t* threshold_filter(uint8_t *dest, uint8_t *source, uint8_t start, uint8_t end, uint8_t thres, uint8_t gap)
{
	uint8_t i;
	for (i = start; i <= end; i++)
	{
		dest[i] = (source[i] <= thres + gap && source[i] >= thres - gap) ? thres : 0;
	}
	return dest;
}





// fuente: https://en.wikiversity.org/wiki/C_Source_Code/Find_the_median_and_mean
uint8_t median(uint8_t n, uint8_t x[]) {
    uint8_t temp;
    uint8_t i, j;
    // the following two loops sort the array x in ascending order
    for(i=0; i<n-1; i++) {
        for(j=i+1; j<n; j++) {
            if(x[j] < x[i]) {
                // swap elements
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }

    if(n%2==0) {
        // if there is an even number of elements, return mean of the two elements in the middle
        return((x[n/2] + x[n/2 - 1]) / 2);
    } else {
        // else return the element in the middle
        return x[n/2];
    }
}

uint8_t minimum(uint8_t* array, uint8_t start, uint8_t end)
{
	uint8_t c;
	uint8_t minimum = array[start];
	for (c = start + 1 ; c <= end; c++) 
    {
        if (array[c] < minimum) 
        {
           minimum = array[c];
        }
    } 
    return minimum;
}