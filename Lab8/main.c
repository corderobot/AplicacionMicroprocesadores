#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */


int map(int val, int valMin, int valMax, int min, int max){
	return ((max - min)/(valMax - valMin)) * (val-valMin) + min;
}


void main(void) {
	int valADC = 0xFF;
	
	DisableInterrupts;
	SOPT1_COPT=0; // matamos al chucho
	SOPT2_T1CH0PS = 1; //Usar PTC0 en lugar de PTA0
	SOPT2_T1CH1PS = 1; //Usar PTC1 en lugar de PTB5
	
	ADCCFG = 0b00100000;
	APCTL1_ADPC0 = 1;  // alambramos canal 0
	ADCSC1_AIEN = 0; 
	ADCSC1_ADCO = 1; 
	ADCSC1_ADCH = 0; 

	// Verde TPM1CH0
	
	TPM1SC = 0b00001000; // 8 MHz / 8 = 1MHz 1us
	TPM1C0SC = 0b00111000; // OUTPUT COMPARE
	TPM1MODH = 0x1F;
	TPM1MODL = 0x3F;
	TPM1C0VH = 0x00;
	TPM1C0VL = 0x00;
	
	// Rojo; TPM1CH1
	
	TPM1SC = 0b00001000; // 8 MHz / 8 = 1MHz 1us
	TPM1C1SC = 0b00111000; // OUTPUT COMPARE
	TPM1MODH = 0x1F;
	TPM1MODL = 0x3F;
	TPM1C1VH = 0x00;
	TPM1C1VL = 0x00;
	
	// Azul TMP2CH0
	TPM2SC = 0b00001000; // 8 MHz / 1 = 8MHz 125ns
	TPM2C0SC = 0b00111000; // OUTPUT COMPARE
	TPM2MODH = 0x1F;
	TPM2MODL = 0x3F;
	TPM2C0VH = 0x00;
	TPM2C0VL = 0x00;

	for(;;) {
		valADC = ADCRL;
		if(valADC < 43){
			//Rojo; Verde Asc
			//Rojo
			TPM1C1VH = 0x1F;
			TPM1C1VL = 0x3F;
			//Azul
			TPM2C0VH = 0x00;
			TPM2C0VL = 0x00;
			//Verde
			valADC = map(ADCRL, 0, 42, 0, 7999);
			TPM1C0VH = (valADC & 0xFF00)>>8;
			TPM1C0VL = valADC & 0x00FF;
		}else if(valADC >= 43 && valADC < 86){
			//Verde; Rojo Desc
			//Rojo
			valADC = map(ADCRL, 43, 86, 7999, 0);
			TPM1C1VH = (valADC & 0xFF00)>>8;
			TPM1C1VL = valADC & 0x00FF;
			//Azul
			TPM2C0VH = 0x00;
			TPM2C0VL = 0x00;
			//Verde
			TPM1C0VH = 0x1F;
			TPM1C0VL = 0x3F;
		}else if(valADC >= 86 && valADC < 129){
			//Verde; Azul Asc	
			//Rojo
			TPM1C1VH = 0x00;
			TPM1C1VL = 0x00;
			//Azul
			valADC = map(ADCRL, 86, 129, 0, 7999);
			TPM2C0VH = (valADC & 0xFF00)>>8;
			TPM2C0VL = valADC & 0x00FF;
			//Verde
			TPM1C0VH = 0x1F;
			TPM1C0VL = 0x3F;
		}else if(valADC >= 129 && valADC < 172){
			// Azul; Verde Desc
			//Rojo
			TPM1C1VH = 0x00;
			TPM1C1VL = 0x00;
			//Azul
			TPM2C0VH = 0x1F;
			TPM2C0VL = 0x3F;
			//Verde
			valADC = map(ADCRL, 129, 172, 7999, 0);
			TPM1C0VH = (valADC & 0xFF00)>>8;
			TPM1C0VL = valADC & 0x00FF;
		}else if(valADC >= 172 && valADC < 215){
			// Azul; Rojo asc
			//Rojo
			valADC = map(ADCRL, 172, 215, 0, 7999);
			TPM1C1VH = (valADC & 0xFF00)>>8;
			TPM1C1VL = valADC & 0x00FF;
			//Azul
			TPM2C0VH = 0x1F;
			TPM2C0VL = 0x3F;
			//Verde
			TPM1C0VH = 0x00;
			TPM1C0VL = 0x00;
		}else if(valADC >= 215){
			// Rojo; Azul Desc
			//Rojo
			TPM1C1VH = 0x1F;
			TPM1C1VL = 0x3F;
			//Azul
			valADC = map(ADCRL, 215, 255, 7999, 0);
			TPM2C0VH = (valADC & 0xFF00)>>8;
			TPM2C0VL = valADC & 0x00FF;
			//Verde
			TPM1C0VH = 0x00;
			TPM1C0VL = 0x00;
		}
	} /* loop forever */
  
}
