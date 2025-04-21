//***********************
// FREE RUNNING MODE
//*********************
#define F_CPU 8000000UL 
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
# include <avr/interrupt.h>
#include "LCD_16x2_H.h"

float Ain=0;
float AinLow=0;

void ADC_Init()
{
	ADMUX |=(1<<REFS0); // Vref: Avcc
	ADMUX |=(1<<MUX0);			/* , ADC channel: 1 */
	ADCSRA |= (1<<ADEN)|(1<<ADIE);// ENABLE ADC, INT
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//fr/128
	ADCSRA |= (1<<ADATE);// TRIGGER MODE
	ADCSRA |= (1<<ADSC); // START FIRST TIME
}




int main()
{
	float value;
	//int value;
	ADC_Init();
	sei();
	LCD_Init();			/* Initialization of LCD */
	LCD_String("ADC value");	/* Write string on 1st line of LCD */
	char String[5];

	while(1)
	{
		LCD_Command(0xc4);	// LCD16x2 cursor position
		value=Ain;
		
		itoa(value,String,10);	/* Integer to string conversion, 10 for decimal */
		//value*=4.88E-3; // value as volt, where max input is VCC=5 V.
		//sprintf(String, "%f", value);/* float to string BUT you have to activate some properties https://startingelectronics.org/articles/atmel-AVR-8-bit/print-float-atmel-studio-7/ */		
		
		LCD_String(String);
		LCD_String("  ");
	}
	return 0;
}

ISR (ADC_vect)
{
	AinLow = ADCL;		/* Read lower byte*/
	Ain = ADCH*256;		/* Read higher 2 bits and Multiply with weight */
	Ain = Ain + AinLow;
}














