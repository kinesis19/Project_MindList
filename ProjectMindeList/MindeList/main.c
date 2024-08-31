#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdbool.h>
#include "LCD_Text.h"
#include "robot-move.h"
#include "robot-mode-army.h"
#include "robot-mode-medic.h"
#include "robot-mode-rescue.h"
#include "Debugging.h"

void Initializing(void);
void USART1_Init(unsigned int ubrr);
unsigned char USART1_Receive(void);
void FunctionA(void);
void FunctionB(void);


char command[10] = "";
uint8_t idxChoose = 0; // 0 ~ 255 ������ �ڷ����� ����� ����!
bool isModeSelect = false;

int main(void) {

    Initializing();
	
	// -----[SYSTEM: GUI]-----
    lcdString(0, 0, "Hello, MindList!");
    
    _delay_ms(1000);
    for(int i = 3; i > 0; i--){
	    lcdNumber(1, 15, i);
	    _delay_ms(500);
    }
	lcdClear();
	lcdString(0, 0, "What do u want?");
	_delay_ms(2000);
	for(int i = 2; i > 0; i--){
		lcdNumber(1, 15, i);
		_delay_ms(500);
	}
	strcpy(command, "ModeSelect");
	lcdClear();
	lcdString(0, 0, ">1.Army");
	lcdString(0, 9, "2.Medic");
	lcdString(1, 1, "3.Rescue");
	lcdString(1, 10, "4.DBG");
	
	DDRG |= (1 << PG0) | (1 << PG1);  // PG0, PG1�� ��� ���� ����
	
	USART1_Init(103);  // 9600 baud rate �ʱ�ȭ
	
	while (1) {
		unsigned char command = USART1_Receive();  // ������� ��� ����
		
		if (command == 'A') {
			Moving_Forward();
		}else if (command == 'B') {
			Moving_BackWord();
		}else if (command == 'C') {
			Moving_Left();  // ��ư B�� ���� �Լ� ȣ��
		}else if (command == 'D') {
			Moving_Left();  // ��ư B�� ���� �Լ� ȣ��
		}else if (command == 'S') {
			Moving_Stop();
		}
	}
	   
}


void USART1_Init(unsigned int ubrr) {
	UBRR1H = (unsigned char)(ubrr >> 8);
	UBRR1L = (unsigned char)ubrr;
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

unsigned char USART1_Receive(void) {
	while (!(UCSR1A & (1 << RXC1)));
	return UDR1;
}

void FunctionA(void) {
	
	Moving_Forward();
	PORTG |= (1 << PG0);  // ���� ��
	_delay_ms(500);
	PORTG &= ~(1 << PG0);  // ���� ��
}

void FunctionB(void) {
	Moving_BackWord();
	PORTG |= (1 << PG1);  // �ٸ� ����� ��
	_delay_ms(500);
	PORTG &= ~(1 << PG1);  // �ٸ� ����� ��
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
			lcdString(1, 10, "4.DBG");
		}else if(idxChoose == 1){
			idxChoose = 2;
			lcdClear();
			lcdString(0, 1, "1.Army");
			lcdString(0, 9, "2.Medic");
			lcdString(1, 0, ">3.Rescue");
			lcdString(1, 10, "4.DBG");
		}else if(idxChoose == 2){
			idxChoose = 3;
			lcdClear();
			lcdString(0, 1, "1.Army");
			lcdString(0, 9, "2.Medic");
			lcdString(1, 1, "3.Rescue");
			lcdString(1, 9, ">4.DBG");
		}else if(idxChoose == 3){
			idxChoose = 0;
			lcdClear();
			lcdString(0, 0, ">1.Army");
			lcdString(0, 9, "2.Medic");
			lcdString(1, 1, "3.Rescue");
			lcdString(1, 10, "4.DBG");
		}
	}
	
}

// -----[Button: Select]-----
ISR(INT1_vect){
	
	if(!isModeSelect){ // Mode Select�� ���� �ʾ��� ���� 1ȸ�� �۵� ��.
		
		if(strcmp(command, "ModeSelect") == 0){
			if(idxChoose == 0){
				
				Working_Mode_Army();
			}else if(idxChoose == 1){
				
				Working_Mode_Medic();
			}else if(idxChoose == 2){
				
				Working_Mode_Rescue();
				
			}else if(idxChoose == 3){
				
				Working_Mode_Debugging();
				
			}
		}
		
	}
}
