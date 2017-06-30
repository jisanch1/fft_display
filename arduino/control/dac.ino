/****** DAC *******/
#define DAC_SS          10
#define DAC_REF         1024
#define DAC_RESOLUTION  4096


void dac_init()
{
    // set the dac pin as an output:
    pinMode(DAC_SS, OUTPUT);
    // start the dac at zero
    dac_val = 0;
}

void dac_write(unsigned int val) 
{
    // valid dac values
    val = constrain(val, 0, DAC_RESOLUTION - 1);
    // mapping to resolution of dac
    
    val += 0x3000;
    
    // transmision to dac
    digitalWrite(DAC_SS, LOW);
    SPI.transfer(val>>8);
    SPI.transfer(val);
    digitalWrite(DAC_SS, HIGH);
}
