#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Text.h"
#include "robot-move.h"

void Initializing(void);

int main(void) {

    Initializing();
	
    while (1) {
		
    }   
}

// Timer/Counter1의 초기화
void Initializing(void){
	// -----[Declare Register]-----
	// -----[Initializing: PORT]-----
	DDRB = 0x6F;  // PB5, PB6 PIN을 출력으로 설정하기(OC1A, OC1B). -> DC Motor.
	DDRE = 0x38;  // PE3, PE4, PE5 핀을 출력으로 설정하기(OC3A, OC3B, OC3C). -> Servo Motor.
	
	// -----[Initializing: Interrupt]-----
	EIMSK = 0b00000011; // Switch는 두 개.
	EICRA = 0b00001010;
	sei();
	
	// -----[Initializing: Timer/Count]-----
	TCCR1A = 0xA2; // 0b10100010, Fast PWM 모드, 비반전 출력하기.
	TCCR1B = 0x1A; // 0b00011010, Prescaler 8, Fast PWM 모드.
	TCCR1C = 0x00;
	
	ICR1 = 399;   // TOP 값 설정, PWM 주기 결정
	TCNT1 = 0x00;
	
	// -----[Initializing: LCD]-----
	lcdInit();
	lcdClear();
}


// -----[Switch Interrupt Control]-----
// -----[Moving: Forward]-----
ISR(INT0_vect){
	Moving_Forward();
}

// -----[Moving: Back]-----
ISR(INT1_vect){
	Moving_BackWord();
}
