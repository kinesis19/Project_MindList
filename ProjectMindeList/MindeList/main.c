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

// Timer/Counter1�� �ʱ�ȭ
void Initializing(void){
	// -----[Declare Register]-----
	// -----[Initializing: PORT]-----
	DDRB = 0x6F;  // PB5, PB6 PIN�� ������� �����ϱ�(OC1A, OC1B). -> DC Motor.
	DDRE = 0x38;  // PE3, PE4, PE5 ���� ������� �����ϱ�(OC3A, OC3B, OC3C). -> Servo Motor.
	
	// -----[Initializing: Interrupt]-----
	EIMSK = 0b00000011; // Switch�� �� ��.
	EICRA = 0b00001010;
	sei();
	
	// -----[Initializing: Timer/Count]-----
	TCCR1A = 0xA2; // 0b10100010, Fast PWM ���, ����� ����ϱ�.
	TCCR1B = 0x1A; // 0b00011010, Prescaler 8, Fast PWM ���.
	TCCR1C = 0x00;
	
	ICR1 = 399;   // TOP �� ����, PWM �ֱ� ����
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
