#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Text.h"
#include "robot-move.h"

void Initializing(void);

int main(void) {

    Initializing();
    lcdString(0, 0, "Hello, MindList");
    while (1) {
		
    }   
}

void Initializing(void){
    // -----[Declare Register]-----
	// -----[Initializing: PORT]-----
    DDRB = 0x6F;  // PB1, PB2 핀을 출력으로 설정하기(OC1A, OC1B).
    DDRE = 0x38;  // PE3, PE4, PE5 핀을 출력으로 설정하기(OC3A, OC3B, OC3C).
    
    // -----[Initializing: Interrupt]-----
    EIMSK = 0b00000011;
    EICRA = 0b00001010;
    sei();
	
    // -----[Initializing: Timer/Count]-----
    TCCR1A = 0xA2; // 0b10100010
    
    ICR1 = 399;
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
