FILES=src/main.c src/uart/uart.c src/uart/debugger.c src/uart/cbuf.c src/timer/timer0.c src/adc/adc.c
NAME=plataforma
CC=avr-gcc
CFLAGS=-Wall -Wextra -Wpedantic --std=gnu99 -O1 
EXTFLAGS=-Wl,-u,vfprintf -lprintf_flt
MCU=atmega328p
PORT=/dev/ttyACM0

compile:
	$(CC) $(FILES) $(CFLAGS) -mmcu=$(MCU) -o bin/$(NAME).elf $(EXTFLAGS)
	avr-objcopy -j .text -j .data -O ihex bin/$(NAME).elf bin/$(NAME).hex

burn: 
	avrdude -p atmega328p -c arduino -P $(PORT) -b 115200 -U flash:w:bin/$(NAME).hex:i

clean:
	rm bin/$(NAME).elf bin/$(NAME).hex



