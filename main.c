#include <avr/io.h>
#include <util/delay.h>
#include "config.h"

void redButton();
void greenButton();

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
