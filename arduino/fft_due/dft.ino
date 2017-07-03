const double tsin[] = {
  0.0,
  0.0980171403296,
  0.195090322016,
  0.290284677254,
  0.382683432365,
  0.471396736826,
  0.55557023302,
  0.634393284164,
  0.707106781187,
  0.773010453363,
  0.831469612303,
  0.881921264348,
  0.923879532511,
  0.956940335732,
  0.980785280403,
  0.995184726672,
  1.0,
  0.995184726672,
  0.980785280403,
  0.956940335732,
  0.923879532511,
  0.881921264348,
  0.831469612303,
  0.773010453363,
  0.707106781187,
  0.634393284164,
  0.55557023302,
  0.471396736826,
  0.382683432365,
  0.290284677254,
  0.195090322016,
  0.0980171403296,
  0.0,
  -0.0980171403296,
  -0.195090322016,
  -0.290284677254,
  -0.382683432365,
  -0.471396736826,
  -0.55557023302,
  -0.634393284164,
  -0.707106781187,
  -0.773010453363,
  -0.831469612303,
  -0.881921264348,
  -0.923879532511,
  -0.956940335732,
  -0.980785280403,
  -0.995184726672,
  -1.0,
  -0.995184726672,
  -0.980785280403,
  -0.956940335732,
  -0.923879532511,
  -0.881921264348,
  -0.831469612303,
  -0.773010453363,
  -0.707106781187,
  -0.634393284164,
  -0.55557023302,
  -0.471396736826,
  -0.382683432365,
  -0.290284677254,
  -0.195090322016,
  -0.0980171403296,
};


const double tcos[] = {
  1.0,
  0.995184726672,
  0.980785280403,
  0.956940335732,
  0.923879532511,
  0.881921264348,
  0.831469612303,
  0.773010453363,
  0.707106781187,
  0.634393284164,
  0.55557023302,
  0.471396736826,
  0.382683432365,
  0.290284677254,
  0.195090322016,
  0.0980171403296,
  0.0,
  -0.0980171403296,
  -0.195090322016,
  -0.290284677254,
  -0.382683432365,
  -0.471396736826,
  -0.55557023302,
  -0.634393284164,
  -0.707106781187,
  -0.773010453363,
  -0.831469612303,
  -0.881921264348,
  -0.923879532511,
  -0.956940335732,
  -0.980785280403,
  -0.995184726672,
  -1.0,
  -0.995184726672,
  -0.980785280403,
  -0.956940335732,
  -0.923879532511,
  -0.881921264348,
  -0.831469612303,
  -0.773010453363,
  -0.707106781187,
  -0.634393284164,
  -0.55557023302,
  -0.471396736826,
  -0.382683432365,
  -0.290284677254,
  -0.195090322016,
  -0.0980171403296,
  0.0,
  0.0980171403296,
  0.195090322016,
  0.290284677254,
  0.382683432365,
  0.471396736826,
  0.55557023302,
  0.634393284164,
  0.707106781187,
  0.773010453363,
  0.831469612303,
  0.881921264348,
  0.923879532511,
  0.956940335732,
  0.980785280403,
  0.995184726672,
};

void dft(double *input_buf, double *real_buf, double *imag_buf, int n)
{
  uint16_t i, j, k;
  for (i = 0; i < n; i++)
  {
    real_buf[i] = 0;
    imag_buf[i] = 0;
    for (j = 0; j < n; j++)
    {
      k = (i*j) % n;
      real_buf[i] += input_buf[j]*tcos[k];
      imag_buf[i] -= input_buf[j]*tsin[k];
    }
  }
}

// calcula la magnitud y entrega la frecuencia de la máxima magnitud
int mag(double *output_buf, double *real_buf, double *imag_buf, int n)
{
  int pos, j;
  double val = 0;
  for (j = 0; j < n/2; j++)
  {
    output_buf[j] = sqrt(real_buf[j]*real_buf[j] + imag_buf[j]*imag_buf[j]);
    if (output_buf[j] > val)
    {
      val = output_buf[j];
      pos = j;
    }
  }
  return pos;
}