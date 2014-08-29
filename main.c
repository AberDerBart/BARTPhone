#include <avr/io.h>
#include <util/delay.h>
#include "config.h"

void redButton();
void greenButton();

void setDigitRow(char);
void setDigitCol(char);
void dial(char);

int main(void){
	while(1){
		greenButton();
		redButton();
	}
   	return 0;
}

void greenButton(){
	_delay_ms(10);
	GREEN_BTN_PORT |= (1 << GREEN_BTN_PIN);
	_delay_ms(10);
	GREEN_BTN_PORT &= ~(1 << GREEN_BTN_PIN);
}

void redButton(){
	_delay_ms(10);
	RED_BTN_PORT |= (1 << RED_BTN_PIN);
	_delay_ms(10);
	RED_BTN_PORT &= ~(1 << RED_BTN_PIN);

}

void setDigitRow(char row){
	if(row & 0x01){
		DIGIT_ROW_LOW_PORT |= (1 << DIGIT_ROW_LOW_PIN);
	}else{
		DIGIT_ROW_LOW_PORT &= ~(1 << DIGIT_ROW_LOW_PIN);
	}
	
	if(row & 0x02){
		DIGIT_ROW_HIGH_PORT |= (1 << DIGIT_ROW_HIGH_PIN);
	}else{
		DIGIT_ROW_HIGH_PORT &= ~(1 << DIGIT_ROW_HIGH_PIN);
	}
}

void setDigitCol(char col){
	if(col & 0x01){
		DIGIT_COL_LOW_PORT |= (1 << DIGIT_COL_LOW_PIN);
	}else{
		DIGIT_COL_LOW_PORT &= ~(1 << DIGIT_COL_LOW_PIN);
	}
	
	if(col & 0x02){
		DIGIT_COL_HIGH_PORT |= (1 << DIGIT_COL_HIGH_PIN);
	}else{
		DIGIT_COL_HIGH_PORT &= ~(1 << DIGIT_COL_HIGH_PIN);
	}

}

void dial(char digit){
	//dials the digit digit

	//
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

	_delay_ms(10);
	DIGIT_PORT |= (1 << DIGIT_PIN);
	_delay_ms(10);
	DIGIT_PORT &= ~(1 << DIGIT_PIN);
}
