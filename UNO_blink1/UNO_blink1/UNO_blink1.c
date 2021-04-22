/*
 * UNO_blink1.c
 *
 * Objetivo: Piscar LED da placa Arduino UNO 3 vezes rapidamente,
 *           e 3 vezes lentamente.
 *
 * Created: 16/06/2020
 *  Author: José L. Natalício
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define setBit(reg,bit) (reg |= (1<<bit))
#define clearBit(reg,bit) (reg &= ~(1<<bit))
#define toogleBit(reg,bit) (reg ^= (1<<bit))

int main(void) {
	
	setBit(DDRB, PORTB5);    // define PB5 como saída
	clearBit(PORTB, PORTB5); // seta PB5 em nível lógico 0
	
    while(1) {
		
		// piscando LED 3 vezes rapidamente:
		for (int i = 0; i < 6; i++) {
			toogleBit(PORTB, PORTB5);
			_delay_ms(250);
		}
		
		// piscando LED 3 vezes lentamente:
		for (int i = 0; i < 6; i++) {
			toogleBit(PORTB, PORTB5);
			_delay_ms(500);
		}
		
    } // end loop
} // end main