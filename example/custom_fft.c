#include "custom_fft.h"
#include <stdio.h>


void cfft(double *input_buf, double *real_buf, double * imag_buf, int n)
{
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			k = (i*j) % n;
			real_buf[i] += input_buf[j]*tcos[k];
			imag_buf[i] -= input_buf[j]*tsin[k];
		}
	}
}



int main()
{
	double inbuf[] = {0,1,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
	double rbuf[FFT_LEN];
	double ibuf[FFT_LEN];
	cfft(inbuf, rbuf, ibuf, FFT_LEN);
	int i;
	for (i = 0; i < FFT_LEN; i++)
	{
		printf("%.5f \t %.5f\r\n", rbuf[i], ibuf[i] );
	} 
}