CC=avr-gcc
CFLAGS += -DF_CPU=8000000UL
CFLAGS += -mmcu=atmega168
CFLAGS += -Os
all: main.o
	avr-gcc -mmcu=atmega168 -o firmware $^
	avr-objcopy -O ihex -R .eeprom firmware firmware.hex
	avr-size --mcu=atmega168 -C firmware

clean:
	rm firmware.hex main.o

flash:
	avrdude -c usbasp -p atmega168 -U firmware.hex

lookup:
	g++ -Wall -pedantic -o lookup generate_lookup.cpp
	./lookup
	gnuplot lookup.gpl
