#include "librobot.h"

void init_button_sensor(void){
    DDRD = (0<<PD7);
    PORTD = 0xff; //pull-up on

	return;
}

int read_button_sensor(void){
	int pressed;

    if(PIND & (1<<PD7)){ //not pressed
        pressed = 1;
    }
    else{ //pressed
        pressed = 0;
    }

	return pressed;
}

float read_knob_sensor(int knob){
	float reading = 0; /* Sensor reading, normalised
						  (i.e., scaled) to be between 
						  zero and one. */

    if(!knob){ //knob0
        ADMUX |= (0<<MUX0); //ADC0
        
    }
    else{ //knob1
        ADMUX |= (1<<MUX0); //ADC1
            
    }
    
    ADCSRA |= (1<<ADSC); //start conversion
    
    while(ADCSRA & (1<<ADSC)); //wait until ADSC unsets
    
    reading = ADCH/255; /*as ADCH is a 8-bit register(0~255), dividing it by 255 will produce a normalised value between 0 and 1*/

	return reading;
}


void init_arm_motors(void) {
    DDRB = (1<<PB1) | (1<<PB2); //PB1(OC1A) and PB2(OC1B) as output
    PORTB = 0;
    
    TCCR1A = (0<<COM1A0) | (1<<COM1A1); //clear OC1A on compare match
    TCCR1A |= (0<<COM1B0) | (1<<COM1B1); //clear OC1B on compare match
    
    TCCR1A |= (0<<WGM10) | (1<<WGM11);
    TCCR1B = (1<<WGM12) | (1<<WGM13); //fast pwm, TOP: ICR1
    
    TCCR1B |= (0<<CS10) | (1<<CS11) | (0<<CS12); //prescaler 8
    
    ICR1 = 40000; //(F_CPU/8)*(20*10^-3)

	return;
}


