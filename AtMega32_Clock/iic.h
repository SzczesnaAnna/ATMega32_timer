#ifndef iic_h
#define iic_h

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define dec2bcd(x) ((( (x)/10)<<4) + ((x) % 10))
#define bcd2dec(x) ((( (x)>>4)*10) + ((x) & 0x0f))

// procedura transmisji sygnału START
void twistart(void);

// procedura transmisji sygnału STOP
void twistop(void);

// procedura transmisji bajtu danych
void twiwrite(uint8_t bajt);

//procedura odczytu bajtu danych
uint8_t twiread(uint8_t ack);

//ustawianie predkosci 1000Hz
void rtcinit(void);

//branie czasu
void gettime(uint8_t* sec, uint8_t* min, uint8_t* h, uint8_t* md, uint8_t* wd, uint8_t* m, uint8_t* y);

//ustawianie obecnego czasu
void settime(uint8_t sec, uint8_t min, uint8_t h, uint8_t md, uint8_t wd, uint8_t m, uint8_t y);

#endif
