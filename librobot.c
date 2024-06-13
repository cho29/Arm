#include "librobot.h"

void init_gripper_motor(void) {
	DDRD    = (1<<PD5);                   
	TCCR0A  = (0<<WGM01 ) | (1<<WGM00);   
	TCCR0B  = (1<<WGM02);
	TCCR0A |= (1<<COM0B1) | (0<<COM0B0);
	TCCR0B |= (1<<CS02  ) | (1<<CS00);    
	OCR0A   = OCR0_TOP;
	return;
}

void init_knob_sensors(void){
   ADMUX = (1<<REFS0) | (1<<ADLAR); 
   ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
   return;
}

void write_arm_motors(float motor0, float motor1){
	OCR1A = OCR1_GAIN*motor0+OCR1_MIN;
	OCR1B = OCR1_GAIN*motor1+OCR1_MIN;
	return;
}

void write_gripper_motor(int open){
	if( open )
	{
		OCR0B = OCR0_OPEN;
	}
	else
	{
		OCR0B = OCR0_CLOSE;
	}
	return;
}
