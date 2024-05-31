#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "iic.h"
//lab8
uint8_t sec, min, h, md, wd, m, y;
char* tab[7]={"pn", "wt", "sr", "cz", "pt", "sb", "nd"};
ISR(INT0_vect)
{
	gettime(&sec, &min, &h, &md, &wd, &m, &y);
	lcd_set_xy(0,0);
	fprintf(&lcd_stream, "%02d:%02d:%02d", h, min, sec);
	lcd_set_xy(0,1);
	fprintf(&lcd_stream, "%02d/%02d/20%02d  %s", md, m, y, tab[wd]);
}
int main(void)
{ 	
	lcdinit();
	lcd_kursor(0);
	rtcinit();
	
	MCUCR|=(1<<ISC01);
	GICR|=(1<<INT0);
	settime(56,59,23,31,0,12,24);
	sei();
	
	while(1)
	{ 
	}
	return 1;
}

