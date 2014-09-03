#include <avr/io.h>
#include <util/delay.h>
#include "config.h"

void redButton();
void greenButton();

void setDigitRow(char);
void setDigitCol(char);
void dial(char);

void setupPins();
void setupTimer();

int main(void){
	char lastStateHook;

	char stateHook;

	char stableStateHook;

	char counterHook;

	setupTimer();
	setupPins();

	while(1){
		stateHook=HOOK_IN & (1 << HOOK_PIN);

		if(stateHook!=lastStateHook){
			counterHook=0;
			lastStateHook=stateHook;
		}
		if(TIFR & 0x02){
			TIFR |= 0x02;
			counterHook++;

			if(counterHook==DEBOUNCE_TIMER_LOOPS){
				if(stableStateHook!=stateHook){
					stableStateHook=stateHook;
					if(stableStateHook){
						greenButton();
					}else{
						redButton();
					}
				}
			}
			if(counterHook>DEBOUNCE_TIMER_LOOPS){
				counterHook=DEBOUNCE_TIMER_LOOPS;
			}
		}	
	}

   	return 0;
}

void greenButton(){
	_delay_ms(PRESSTIME);
	GREEN_BTN_PORT |= (1 << GREEN_BTN_PIN);
	_delay_ms(PRESSTIME);
	GREEN_BTN_PORT &= ~(1 << GREEN_BTN_PIN);
}

void redButton(){
	_delay_ms(PRESSTIME);
	RED_BTN_PORT |= (1 << RED_BTN_PIN);
	_delay_ms(PRESSTIME);
	RED_BTN_PORT &= ~(1 << RED_BTN_PIN);

}

void setDigitRow(char row){
	DIGIT_ROW_LOW_PORT &= ~(1 << DIGIT_ROW_LOW_PIN);
	DIGIT_ROW_HIGH_PORT &= ~(1 << DIGIT_ROW_HIGH_PIN);

	if(row & 0x01){
		DIGIT_ROW_LOW_PORT |= (1 << DIGIT_ROW_LOW_PIN);
	}
	if(row & 0x02){
		DIGIT_ROW_HIGH_PORT |= (1 << DIGIT_ROW_HIGH_PIN);
	}
}

void setDigitCol(char col){
	DIGIT_COL_LOW_PORT &= ~(1 << DIGIT_COL_LOW_PIN);
	DIGIT_COL_HIGH_PORT &= ~(1 << DIGIT_COL_HIGH_PIN);

	if(col & 0x01){
		DIGIT_COL_LOW_PORT |= (1 << DIGIT_COL_LOW_PIN);
	}
	if(col & 0x02){
		DIGIT_COL_HIGH_PORT |= (1 << DIGIT_COL_HIGH_PIN);
	}
}

void dial(char digit){
	//dials the digit digit

	if(digit==0){
		setDigitRow(3);
		setDigitCol(1);
	}else{
		if(digit<=3){
			setDigitRow(0);
		}else if(digit<=6){
			setDigitRow(1);
		}else{
			setDigitRow(2);
		}
		if(digit%3==1){
			setDigitCol(0);
		}else if(digit%3==2){
			setDigitCol(1);
		}else{
			setDigitCol(2);
		}
	}

	_delay_ms(PRESSTIME);
	DIGIT_PORT |= (1 << DIGIT_PIN);
	_delay_ms(PRESSTIME);
	DIGIT_PORT &= ~(1 << DIGIT_PIN);
}

void setupPins(){
	//outputs
	GREEN_BTN_PORT &= ~(1 << GREEN_BTN_PIN);
	GREEN_BTN_DDR |= (1 << GREEN_BTN_PIN);
	RED_BTN_PORT &= ~(1 << RED_BTN_PIN);
	RED_BTN_DDR |= (1 << RED_BTN_PIN);
	DIGIT_ROW_LOW_PORT &= ~(1 << DIGIT_ROW_LOW_PIN);
	DIGIT_ROW_LOW_DDR |= (1 << DIGIT_ROW_LOW_PIN);
	DIGIT_ROW_HIGH_PORT &= ~(1 << DIGIT_ROW_HIGH_PIN);
	DIGIT_ROW_HIGH_DDR |= (1 << DIGIT_ROW_HIGH_PIN);
	DIGIT_COL_LOW_PORT &= ~(1 << DIGIT_COL_LOW_PIN);
	DIGIT_COL_LOW_DDR |= (1 << DIGIT_COL_LOW_PIN);
	DIGIT_COL_HIGH_PORT &= ~(1 << DIGIT_COL_HIGH_PIN);
	DIGIT_COL_HIGH_DDR |= (1 << DIGIT_COL_HIGH_PIN);
	DIGIT_PORT &= ~(1 << DIGIT_PIN);
	DIGIT_DDR |= (1 << DIGIT_PIN);
	//inputs
	DIAL_PORT |= (1 << DIAL_PIN);
	DIAL_DDR &= ~(1 << DIAL_PIN);
	TICK_PORT |= (1 << TICK_PIN);
	TICK_DDR &= ~(1 << TICK_PIN);
	HOOK_PORT |= (1 << HOOK_PIN);
	HOOK_DDR &= ~(1 << HOOK_PIN);

	//enables pullups
	MCUCR &= ~(1 << 7);
}

void setupTimer(){
	TCCR0A=0x00;	
	TCCR0B=0x03;
	TIMSK=0x00;
}
