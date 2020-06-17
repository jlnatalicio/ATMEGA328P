;*
;* arduinoUno_blinkASM.asm
;*
;* programa básico para acender a apagar o LED na placa do arduino UNO,
;* em um período de 1 segundo.
;*
;*  Created: 16/06/2020
;*   Author: José L. Natalício

.EQU LED = PB5
.ORG $00

LDI R17, $00
LDI R18, $00

INICIO:
	LDI R19, $FF
	OUT DDRB, R19

PRINCIPAL:
	SBI PORTB, LED
	RCALL PAUSA
	CBI PORTB, LED
	RCALL PAUSA
	RJMP PRINCIPAL
 
PAUSA:
	LDI R16, $51
	VOLTA:
		DEC R18
		BRNE VOLTA
		DEC R17
		BRNE VOLTA
		DEC R16
		BRNE VOLTA
		RET


