//***********************
// Single conversion
//*************************
#define F_CPU 8000000UL 
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "LCD_16x2_H.h"

void ADC_Init()// configuration
{
	ADMUX |=(1<<REFS0); /* Vref: Avcc */
	ADMUX |=(1<<MUX0);	/* , ADC channel: 1 */
	//ADMUX = 0x41;			/* Vref: Avcc, ADC channel: 1 */
	ADCSRA |= (1<<ADEN);// ENABLE ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//fr/128
	//ADCSRA = 0x87;			/* Enable ADC, fr/128  */ 

	//ADMUX |=(1<<ADLAR); // left justified Q4
}


int ADC_Read()
{
	int out,OutLow;
	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* wait until conversion is complete */
	OutLow = ADCL;		/* Read lower byte*/
	out = ADCH*256;		/* Read higher byte (has only 2 bits) and Multiply with weight */
	//OutLow = ADCL/64;	// in case of left justified Q4
	//out = ADCH*4;		// in case of left justified Q4
	out = out + OutLow;
	return(out);			/* Return digital value*/
}
 
int main()
{
	char String[5];
	int value;
	//float value;

	ADC_Init();// configuration
	
	LCD_Init();			/* Initialization of LCD */
	LCD_String("ADC value");	/* Write string on 1st line of LCD */
	LCD_Command(0xc4);	// LCD16x2 cursor position
	
	value=ADC_Read();	// Read ADC after conversion (one time conversion)
	
	itoa(value,String,10);
	LCD_String(String);
	
	while(1)
	{
	
	}
	return 0;
}




