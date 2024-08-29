#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "robot-mode-medic.h"
#include <stdbool.h>
#include "LCD_Text.h"

uint8_t channels[] = {0, 2, 3, 4, 5}; // PF0, PF2, PF3, PF4, PF5
uint16_t sensor_values[5] = {0};  // 센서 값을 저장할 배열
bool isRangeOkay = false;
bool isServo1Move = false;
bool isServo2Move = false;

void Working_Mode_Medic(void){
	
	Mode_Medic_Initializing();
	
	lcdClear();
	lcdString(0, 0, "Medic Mode");
	
	while(1){
		for (uint8_t i = 0; i < 5; i++) {
			ADMUX = (ADMUX & 0xF0) | (channels[i] & 0x0F);  // 채널 선택하기
			ADCSRA |= (1 << ADSC);  // ADC 변환 시작하기
			
			while (!(ADCSRA & (1 << ADIF)));  // 변환 완료 대기하기
			ADCSRA |= (1 << ADIF);  // ADC 클리어하기

			sensor_values[i] = ADC;  // ADC 저장하기
		}
		
		if(sensor_values[0] < 150){
			lcdString(0, 0, "Come closer");
			PORTG |= (1 << PG0);
			_delay_ms(1000);
			PORTG &= ~(1 << PG0);
			_delay_ms(1000);
			isRangeOkay = false;
		}else if(sensor_values[0] < 200){
			lcdString(0, 0, "More plz");
			PORTG |= (1 << PG0);
			_delay_ms(500);
			PORTG &= ~(1 << PG0);
			_delay_ms(500);
			isRangeOkay = false;
		}else if(sensor_values[0] < 250){
			lcdString(0, 0, "Almost Done!");
			PORTG |= (1 << PG0);
			_delay_ms(250);
			PORTG &= ~(1 << PG0);
			_delay_ms(250);
			isRangeOkay = false;
		}else if(sensor_values[0] > 250){
			lcdString(0, 0, "Good Job!");
			if(isRangeOkay == false){
				PORTG |= (1 << PG0);
				_delay_ms(2000);
				PORTG &= ~(1 << PG0);
				_delay_ms(2000);
				isRangeOkay = true;
				
				// 알코올 검사 세팅하기
				if(isServo1Move == false){
					OCR3A = 1500;
					isServo1Move = true;
					_delay_ms(5000);
				}
				// 심박수 검사 세팅하기
				if(isServo2Move == false){
					OCR3B = 4500;
					isServo2Move = true;
					_delay_ms(5000);
				}
			}
			break;
		}		
	}
	
		
		for (uint8_t i = 0; i < 5; i++) {
			ADMUX = (ADMUX & 0xF0) | (channels[i] & 0x0F);  // 채널 선택하기
			ADCSRA |= (1 << ADSC);  // ADC 변환 시작하기
			
			while (!(ADCSRA & (1 << ADIF)));  // 변환 완료 대기하기
			ADCSRA |= (1 << ADIF);  // ADC 클리어하기

			sensor_values[i] = ADC;  // ADC 저장하기
		}
		if(sensor_values[4] > 300 && sensor_values[3] > 800){
			lcdClear();
			lcdString(0, 0, "You r so sick!");
		}else if(sensor_values[4] > 300){
			lcdClear();
			lcdString(0, 0, "You drunk!");
		}else if(sensor_values[3] > 800){
			lcdClear();
			lcdString(0, 0, "Are you okay?");
		}else{
			lcdClear();
			lcdString(0, 0, "You r okay!");
		}
	lcdNumber(1, 0, sensor_values[4]);
	lcdNumber(1, 6, sensor_values[3]);
	
	_delay_ms(10000);
	lcdClear();
		
	OCR3A = 0;
	OCR3B = 0;
	Working_Mode_Medic();
}

void Mode_Medic_Initializing(void){
	DDRG = 0b00000001; // Buzzer 및 Flame Sensor 설정
	
	ADMUX = 0x40;
	ADCSRA = 0x87; // ADC Enable 및 Prescaler 설정
	
	DDRE |= (1 << PE3) | (1 << PE4);  // PE3, PE4 핀을 출력 모드로 설정 (OC3A, OC3B)
	
	// Timer/Counter3 설정 (Fast PWM 모드, TOP = ICR3)
	TCCR3A = (1 << COM3A1) | (1 << COM3B1) | (1 << WGM31);  // OC3A, OC3B 비반전 PWM 모드, Fast PWM
	TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS31);  // Fast PWM 모드, 분주비 8
	
	ICR3 = 39999;  // PWM 주기: 20ms (16MHz / (8 * (39999 + 1)))
}
