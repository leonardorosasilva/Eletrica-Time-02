CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Werror -O2 -DHOST_BUILD

.PHONY: all test clean

all: test

test: mock
	./mock.exe

mock: mock.c adc_reader.c telemetry.c adc_reader.h telemetry.h sensoriamento.h
	$(CC) $(CFLAGS) -o mock.exe adc_reader.c telemetry.c mock.c

clean:
	del /q mock.exe 2>nul
