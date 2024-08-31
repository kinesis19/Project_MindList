#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "robot-move.h"
#include "LCD_Text.h"

void Moving_Forward(void){
	PORTB = (PORTB & 0xF0) | 0x0A;
	OCR1A = ICR1 * 0.75;
	OCR1B = ICR1 * 0.75;
	
	lcdClear();
	lcdString(0, 0, "Moving Foward!");
}

void Moving_BackWord(void){
	PORTB = (PORTB & 0xF0) | 0x05;
	OCR1A = ICR1 * 0.9;
	OCR1B = ICR1 * 0.875;
	
	lcdClear();
	lcdString(0, 0, "Moving Back!");
}


void Moving_Stop(void){
	PORTB = (PORTB & 0xF0) | 0x0A;
	OCR1A = ICR1 * 0;
	OCR1B = ICR1 * 0;
	
	lcdClear();
	lcdString(0, 0, "Moving Stop!");
}


void Moving_Right(void){
	PORTB = (PORTB & 0xF0) | 0x0A;
	OCR1A = ICR1 * 0.9;
	OCR1B = ICR1 * 0;
	
	lcdClear();
	lcdString(0, 0, "Moving Right!");
}

void Moving_Left(void){
	PORTB = (PORTB & 0xF0) | 0x05;
	OCR1A = ICR1 * 0.0;
	OCR1B = ICR1 * 0.875;
	
	lcdClear();
	lcdString(0, 0, "Moving Left!");
}