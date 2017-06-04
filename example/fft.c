
#include <stdio.h>
#include <math.h>
#include <complex.h>
 
double PI;
typedef double complex cplx;
 
void _fft(cplx buf[], cplx out[], int n, int step)
{
	if (step < n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);
 
		for (int i = 0; i < n; i += 2 * step) {
			cplx t = cexp(-I * PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}
 
void fft(cplx buf[], int n)
{
	cplx out[n];
	for (int i = 0; i < n; i++) out[i] = buf[i];
 
	_fft(buf, out, n, 1);
}
 
 
void show(const char * s, cplx buf[], int len) {
	printf("%s", s);
	for (int i = 0; i < len; i++) {
		printf("(%2.4g\t\t, %2.4g\t\t) \n", creal(buf[i]), cimag(buf[i]));
		//printf("%g\n", cabs(buf[i]));
	}
	printf("\n");
}
 
int main()
{
	PI = atan2(1, 1) * 4;
	cplx buf[] = {0, 1, 0, 0, 0, 0, 0, 0,
				  0, 0, 0, 0, 0, 0, 0, 0, 
				  0, 0, 0, 0, 0, 0, 0, 0, 
				  0, 0, 0, 0, 0, 0, 0, 1};
 	int len = sizeof(buf)/sizeof(cplx);
	show("Data: ", buf, len);
	fft(buf, len);
	show("\nFFT : ", buf, len);
 
	return 0;
}
 