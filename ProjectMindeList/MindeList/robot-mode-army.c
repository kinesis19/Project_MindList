#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "robot-mode-army.h"
#include "LCD_Text.h"

void Working_Mode_Army(void){
	
	Mode_Army_Initializing(); // Mode Army Initializing하기.
	OCR3C = 1800; // 180도 회전하기(수동으로 찾음)
	
	// Debugging
	lcdClear();
	lcdString(0, 0, "Army Mode");
	
	// Buzzer System
	while (1) {
		PORTG |= (1 << PG0);
		_delay_ms(500);
		PORTG &= ~(1 << PG0);
		_delay_ms(500);
	 }
}

void Mode_Army_Initializing(void){
	
	DDRG |= (1 << PG0); // Buzzer
	DDRA = 0b01010100; // RGB LED
	
	// 0b1000000; // RGB LED: Green Color
	// 0b0010100; // RGB LED: White ~ Blue Color
	PORTA = 0b10111011; //
	
	DDRE |= (1<<PE5);  // PE5 PIN을 Output Mode로 설정하기 (OC3C PIN)
	 
	// Servo Motor 같은 경우에는 10개 넘는 레퍼런스랑 데이터 시트 보면서 공부하고 참고함.
	// DC 제어랑 비슷한 느낌이 있지만, ADC 제어보다 조금은 어렵게 느껴짐.
	// Timer/Counter3 설정 (Fast PWM 모드, TOP = ICR3) 
	TCCR3A = (1<<COM3C1) | (1<<WGM31);  // 비반전 PWM 모드, Fast PWM
	TCCR3B = (1<<WGM33) | (1<<WGM32) | (1<<CS31);  // Fast PWM 모드, 분주비 8

	ICR3 = 39999;  // PWM 주기: 20ms (16MHz / (8 * (39999 + 1)))
	
}
