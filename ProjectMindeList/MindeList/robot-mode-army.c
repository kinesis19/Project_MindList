#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "robot-mode-army.h"
#include "LCD_Text.h"

void Working_Mode_Army(void){
	
	// Debugging
	lcdClear();
	lcdString(0, 0, "This is Army Mode");
	
}