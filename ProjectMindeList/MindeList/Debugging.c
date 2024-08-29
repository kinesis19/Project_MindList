#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Debugging.h"
#include "LCD_Text.h"

uint8_t channels2[] = {0, 2, 3, 4, 5}; // PF0, PF2, PF3, PF4, PF5
uint16_t sensor_values2[5] = {0};  // 센서 값을 저장할 배열

void Working_Mode_Debugging(void){
	
	Mode_Debugging_Initializing();
	
	// Debugging
	lcdClear();
	lcdString(0, 0, "Debugging Mode");
	
	while(1){
		
		for (uint8_t i = 0; i < 5; i++) {
			ADMUX = (ADMUX & 0xF0) | (channels2[i] & 0x0F);  // 채널 선택하기.
			ADCSRA |= (1 << ADSC);  // ADC 변환 시작하기.
			
			while (!(ADCSRA & (1 << ADIF)));  // 변환 완료 대기하기.
			ADCSRA |= (1 << ADIF);  // ADC 클리어하기.

			sensor_values2[i] = ADC;  // ADC 저장하기.
		}
		
		// ADC 출력하기
		lcdNumber(0, 0, sensor_values2[0]);
		lcdNumber(0, 5, sensor_values2[1]);
		lcdNumber(0, 10, sensor_values2[2]);
		lcdNumber(1, 0, sensor_values2[3]);
		lcdNumber(1, 5, sensor_values2[4]);
		if (PING & (1 << PG1)) {
			lcdString(1, 10, "Not"); // 불꽃 감지 X
			} else {
			lcdString(1, 10, "Yes"); // 불꽃 감지 O
		}
		_delay_ms(500);
		lcdClear();
		
	}
}

void Mode_Debugging_Initializing(void){
	
	DDRG = 0b00000001; // Buzzer, Flame Sensor
	
	ADMUX = 0x40;
	ADCSRA = 0x87; // ADC Enable 및 Prescaler를 128로 Setting하기
}