/*
 * squarewave.c
 * este programa gera uma onda quadrada de aproximadamente 60Hz, utilizando o interruptor TC0 do microcontrolador ATMega328P
 * calculo para valor de OCR0A:
 *
 * OCR0A =   fosc          =    16E6         = 130.21 - 1 ~ 129;     OCR0A/2 ~= 64;
 *        ----------- -  1   ----------- - 1
 *         2*N*foc0a          2*1024*60
 *
 * Created: 16/10/2018 23:06:11
 *  Author: José L. Natalício
 */ 

//frequencia do cristal externo = 16MHz
#define F_CPU (16000000)

//bibliotecas necessárias
#include <avr/io.h>
#include <avr/interrupt.h> 

uint8_t interrompido = 1;

/*--------------------------------------------------bloco de interrupção do TC0-------------------------------------------*/
ISR(TIMER0_COMPA_vect)
{
	if (interrompido < 2)
	{
		interrompido++;
		asm("nop");
	} 
	else
	{
		PORTB ^= (1<<PORTB2);                            // quando contador estourar, realizar troca de estado do bit PB2
		interrompido = 1;	
	}
}
/*------------------------------------------------------------------------------------------------------------------------*/

/*como carregar interrupcoes:
1 - setar wgm0,1,2
2 - calcular prescaler (N = 1024)
3 - calcular e carregar OCR0A (no cabecalho)
4 - habilitar interrupções OCIEA0, e interrupção global (TIMSK0)
5 - setar valor do prescaler (TCCR0B)
6 - programar ISR
*/

void iniciar_timer(void);

int main(void)
{
	DDRB  = 0b00000100;                                   // ativando somente o bit 2 do registrador PORTB como saida
	PORTB = 0b11111011;                                   // habilita pull-ups nos terminais nao utilizados
	
	iniciar_timer();                                      //carrega interrupcao do timer 0
	sei();                                                // habilita a chave de interrupcao global (datasheet)
	
    while(1)
    {
        //TODO:: Please write your application code 
		asm("nop");
    }
}

void iniciar_timer(void)
{
	TCCR0A = 0b01000010;                                  // habilita modo CTC, com TOP em OCR0A || (1<<WGM01) | (1<<WGM00)
	OCR0A = 64;                                           // valor do registrador de comparacao da saida OC0A (TOP)
	TIMSK0 = 0b00000010;                                  // habilita a interrupcao do TC0 || 1<<OCIE0A
	TCCR0B = 0b10000101;                                  /* TC0 com prescaler de 1024, a 16 MHz gera uma
	                                                         interrupção a cada 16,384 ms || TCCR0B = (1<<CS02) | (1<<CS00); 
					                         modo ctc de operação -> (0<<WGM02)  */
}
