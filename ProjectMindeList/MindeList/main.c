#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdbool.h>
#include "LCD_Text.h"
#include "robot-move.h"

void Initializing(void);

char command[10] = "";
uint8_t idxChoose = 0; // 0 ~ 255 ������ �ڷ����� ����� ����!
bool isModeSelect = false;

int main(void) {

    Initializing();
	
	// -----[SYSTEM: GUI]-----
    lcdString(0, 0, "Hello, MindList!");
    
    _delay_ms(2000);
    for(int i = 5; i > 0; i--){
	    lcdNumber(1, 15, i);
	    _delay_ms(1000);
    }
	lcdClear();
	lcdString(0, 0, "What do u want?");
	strcpy(command, "ModeSelect");
	lcdString(0, 0, ">1.Army");
	lcdString(0, 9, "2.Medic");
	lcdString(1, 1, "3.Rescue");
	
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
// -----[Button: Choose]-----
ISR(INT0_vect){
	
	_delay_ms(100); // Switch�� �������� ������ ������ �����ϱ� ����. (debounce)
	
	if(strcmp(command, "ModeSelect") == 0){
		if(idxChoose == 0){
			idxChoose = 1;
			lcdClear();
			lcdString(0, 1, "1.Army");
			lcdString(0, 8, ">2.Medic");
			lcdString(1, 1, "3.Rescue");
		}else if(idxChoose == 1){
			idxChoose = 2;
			lcdClear();
			lcdString(0, 1, "1.Army");
			lcdString(0, 9, "2.Medic");
			lcdString(1, 0, ">3.Rescue");
		}else if(idxChoose == 2){
			idxChoose = 0;
			lcdClear();
			lcdString(0, 0, ">1.Army");
			lcdString(0, 9, "2.Medic");
			lcdString(1, 1, "3.Rescue");
		}
	}
	
}

// -----[Button: Select]-----
ISR(INT1_vect){
	
	if(!isModeSelect){ // Mode Select�� ���� �ʾ��� ���� 1ȸ�� �۵� ��.
		
		if(strcmp(command, "ModeSelect") == 0){
			if(idxChoose == 0){
				
			}else if(idxChoose == 1){
				
			}else if(idxChoose == 2){
				
			}
		}
		
	}
}
