
#define F_CPU 4000000UL

 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
unsigned long millis;


void set_millis(void)
{
	sei();
	TCB0_CCMP = 3999;				// Write a TOP value to the Compare/Capture (TCBn.CCMP) register
	
	TCB0_CTRLB |= (0x0 << 0);
	TCB0_INTCTRL |= (1<<0);
	
	TCB0_CTRLA |= (1<<0)|(0x0 <<1); // ENABLE bit in the Control A (TCBn.CTRLA) register,
}

ISR(TCB0_INT_vect)
{
	millis++;
	TCB0_INTFLAGS |= (1<<0);
}

ISR(PORTA_PORT_vect)
{
	PORTA_INTFLAGS & (1<<1);
	PORTA_OUT |= (1<<0);
}

int main(void)
{
	
	set_millis();
	
	PORTA_DIR |= (1<<0);    // OUTPUT
	
	PORTA_DIR &= ~(1<<1);   // INPUT
	
	PORTA_PIN1CTRL=0x01;
	
    while(1)
    {
	
		//PORTA_OUT |= (1<<0);
		//_delay_ms(10000);
		//PORTA_OUT |= (0<<0);
		//_delay_ms(1000);
    }
}