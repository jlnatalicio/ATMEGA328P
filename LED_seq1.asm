 ;
 ;  Created: 21/04/2021
 ;  Author: Leonardo
 ; 

 ;  Objective:
 ;  Ligar sequencialmente 1 LED da direita para a esquerda (o LED deve
 ;  permanecer ligado até que todos os 8 estejam ligados, depois eles
 ;  devem ser desligados e o processo repetido).
 ;
 ; Da direita para esquerda: LED7, LED6, LED5, LED4, LED3, LED2, LED1, LED0
 ; OBS.: LEDs configurados para acender com bit 0
 ; --------------------------------------------------------------------------------

.ORG    $00
LDI     R16, $FF   ; carregando registrador com bits 1111 1111
OUT     DDRD, R16  ; definindo os pinos do PORTD como saída
LDI     R17, $FF   ; carregando registrador com bits 1111 1111
OUT     PORTD, R17 ; escrevendo pinos do PORTD em nível alto (mantendo LEDs apagados)

PRINCIPAL: 
        LDI     R19, $7F   ; carregando registrador com bits 0111 1111
	OUT     PORTD, R19
	RCALL   PAUSA
	LDI     R20, $06   ; carregando registrador de iterações do loop

LOOP:
        LSR     R19        ; divide o valor decimal do registrador por 2
	OUT     PORTD, R19
	RCALL   PAUSA
	DEC     R20        ; decrementa registrador de iterações do loop
	SBIC    PORTD, 0   ; testa se PD0 = 0
	RJMP    LOOP       ; se PD0 = 0, pula essa instrução
	LDI     R19, $FF   ; carregando registrador com bits 1111 1111
	OUT     PORTD, R19
	RCALL   PAUSA
	RJMP    PRINCIPAL

PAUSA:
        LDI     R16, $51
	LDI     R17, $00
	LDI     R18, $00
        VOLTA:
                DEC     R18
		BRNE    VOLTA
		DEC     R17
		BRNE    VOLTA
		DEC     R16
		BRNE    VOLTA
RET
