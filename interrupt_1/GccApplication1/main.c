/*
Assume that the INT0 pin is connected to a switch that is normally low. 
Write a program that toggle PORTC.3 whenever INT0 pin goes high. 
Use external interrupt in the rising edge trigger mode. 
 */ 
# include <avr/io.h>
# include <avr/interrupt.h>
int main ( )
{
	DDRC =1<<3;  // led
	MCUCR |= (1<<ISC01)|(1<<ISC00) ; // +ve (rising) edge trigger 
	//MCUCR |= (1<<ISC01) ; // falling edge trigger
    //MCUCR |= (1<<ISC00) ; // any logical change trigger
	GICR= (1<<INT0);
	//PORTC = (1<<3);
	sei();
	while (1) ;

}

ISR (INT0_vect )
{
	PORTC ^= (1<<3); // change state (toggle)
	
}







































/*

	if (PORTC &(1<<3)) // if LED is ON
	PORTC &= ~(1<<3); //turn it off
	else
	PORTC |= (1<<3);//turn it ON
	*/