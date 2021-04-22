/*
 * ins_and_outs.c
 *
 * Created: 10/07/2018 00:11:11
 * Author : José Leonardo
 * Objetivo: Criar primeiro programa funcional para o Arduino UNO, para familiarização/aprendizado
 *           Nesse caso, esse programa fará um gerador de pulso de 0.5s ("Hello World da Eletrônica Digital")
 */ 

//1º: definir frequência que será utilizada 
#define F_CPU (16000000)				//(nesse caso, 16 MHz do cristal oscilador externo do Arduino)

//2º: definir bibliotecas utilizadas
#include <avr/io.h>
#include <util/delay.h>

/*3º: definir funções que serão utilizadas no projeto (elas são definidas aqui, pois melhora 
*     a visualização do código como um todo).
* 
*     Como visto no datasheet do microcontrolador, para trabalharmos com uma das GPIO, devemos utilizar a função DDRB,
*     que funciona da seguinte forma:
*
* registrador = registrador OU bit_de_interesse(1) -> ligando um determinado bit
* registrador = registrador E [NÃO bit_de_interesse(1)] -> desligando um determinado bit
*
*     traduzindo para um pseudo-código: reg |= (1<<bit) e reg &= ~(1<<(bit))
*/

#define bit_set(reg,bit) (reg |= (1<<bit))
#define bit_reset(reg,bit) (reg &= ~(1<<bit))

int main(void)
{
	bit_set (DDRB,PORTB5);	/*Como visto no datasheet, quando temos um bit do DDRx em 1, temos aquele bit do registrador como
							 * saída. Então, usando a função que acabamos de definir, ligamos o bit 5 do DDRB (0001 0000),
							 * definindo-o então como saída!
							*/						
    while (1) 
    {
		bit_set(PORTB,PORTB5);					//liga o bit 5 do PORTB
		_delay_ms(500);							//Aguarda 500 ms
		bit_reset(PORTB,PORTB5);				//desliga o bit 5 do PORTB
		_delay_ms(500);							//Aguarda 500 ms
    }
}
