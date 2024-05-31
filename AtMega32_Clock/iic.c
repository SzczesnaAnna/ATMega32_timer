#include "iic.h"
#include <util/delay.h>

// procedura transmisji sygnału START
void twistart(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}
// procedura transmisji sygnału STOP
void twistop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while ((TWCR & (1<<TWSTO)));
}
// procedura transmisji bajtu danych
void twiwrite(uint8_t bajt)
{
	TWDR = bajt;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}
//procedura odczytu bajtu danych
uint8_t twiread(uint8_t ack)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (ack << TWEA);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}
void rtcinit(void)
{
	TWBR=72;
	twistart();
	twiwrite(0xa2);
	twiwrite(0x0d);
	twiwrite(0b10000011);
	twistop();
}
void gettime(uint8_t* sec, uint8_t* min, uint8_t* h, uint8_t* md, uint8_t* wd, uint8_t* m, uint8_t* y)
{
	uint8_t tmp;
	
	twistart();
	
	twiwrite(0xa2);
	twiwrite(0x02);
	twistart();
	twiwrite(0xa3);
	
	tmp=(twiread(1)&0b01111111);
	*sec=bcd2dec(tmp);
		
	tmp=(twiread(1)&0b01111111);
	*min=bcd2dec(tmp);
		
	tmp=(twiread(1)&0b00111111);
	*h=bcd2dec(tmp);
		
	tmp=(twiread(1)&0b00111111);
	*md=bcd2dec(tmp);
		
	tmp=(twiread(1)&0b00000111);
	*wd=bcd2dec(tmp);
		
	tmp=(twiread(1)&0b00011111);
	*m=bcd2dec(tmp);
		
	tmp=twiread(0);
	*y=bcd2dec(tmp);
	
	twistop();
}
//ustawianie obecnego czasu
void settime(uint8_t sec, uint8_t min, uint8_t h, uint8_t md, uint8_t wd, uint8_t m, uint8_t y)
{
	uint8_t tmp=0;
	
	twistart();
	twiwrite(0xa2);
	twiwrite(0x02);
	
	tmp=dec2bcd(sec);
	twiwrite(tmp);
		
	tmp=dec2bcd(min);
	twiwrite(tmp);
		
	tmp=dec2bcd(h);
	twiwrite(tmp);
		
	tmp=dec2bcd(md);
	twiwrite(tmp);
		
	tmp=dec2bcd(wd);
	twiwrite(tmp);
		
	tmp=dec2bcd(m);
	twiwrite(tmp);
		
	tmp=dec2bcd(y);
	twiwrite(tmp);
	
	twistop();
}
