#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

unsigned int eladc = 0;
unsigned int distancia = 0;
int centenas, decenas;

void enviarNum(int num){
	
	while((SCIS1 & 0b10000000) == 0);
	
	if(num == 0){
		SCID = '0';
		while((SCIS1 & 0b10000000) == 0);
		SCID = '\n';
		
		while((SCIS1 & 0b10000000) == 0);
		SCID = '\r';
		return;
	}
	
	centenas = num / 100;
	num = num - (centenas * 100);
	decenas = num/10;
	num = num - (decenas * 10);
	
	if (centenas == 9) {
		SCID = '9';
	}else if (centenas == 8) {
		SCID = '8';
	}else if (centenas == 7) {
		SCID = '7';
	}else if (centenas == 6) {
		SCID = '6';
	}else if (centenas == 5) {
		SCID = '5';
	}else if (centenas == 4) {
		SCID = '4';
	}else if (centenas == 3) {
		SCID = '3';
	}else if (centenas == 2) {
		SCID = '2';
	}else if (centenas == 1) {
		SCID = '1';
	}
	
	while((SCIS1 & 0b10000000) == 0);
	
	if (decenas == 9) {
		SCID = '9';
	} else if (decenas == 8) {
		SCID = '8';
	} else if (decenas == 7) {
		SCID = '7';
	} else if (decenas == 6) {
		SCID = '6';
	} else if (decenas == 5) {
		SCID = '5';
	} else if (decenas == 4) {
		SCID = '4';
	} else if (decenas == 3) {
		SCID = '3';
	} else if (decenas == 2) {
		SCID = '2';
	} else if (decenas == 1) {
		SCID = '1';
	}
	
	while((SCIS1 & 0b10000000) == 0);
	
	if (num == 9) {
		SCID = '9';
	} else if (num == 8) {
		SCID = '8';
	} else if (num == 7) {
		SCID = '7';
	} else if (num == 6) {
		SCID = '6';
	} else if (num == 5) {
		SCID = '5';
	} else if (num == 4) {
		SCID = '4';
	} else if (num == 3) {
		SCID = '3';
	} else if (num == 2) {
		SCID = '2';
	} else if(num == 1){
		SCID = '1';
	} else {
		SCID = '0';
	}
	
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'c';
	
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'm';
	
	while((SCIS1 & 0b10000000) == 0);
	SCID = '\n';
	
	while((SCIS1 & 0b10000000) == 0);
	SCID = '\r';
	
	return;
}


void main(void) {
  DisableInterrupts;
  
  SOPT1_COPT=0; // matamos al chucho

  ADCCFG = 0b00101000;
  APCTL1_ADPC0 = 1;  
  ADCSC1_AIEN = 0; 
  ADCSC1_ADCO = 1; 
  ADCSC1_ADCH = 0; 
  
  //Serial
  SCIBDL = 0b110101;	// (8MHz)/(9600*16) = 52
  SCIC3 |= 0b1110;
  SCIC2 |= 0b00101100;
  
  ICSTRM = 0x90;
  ICSSC_FTRIM = 1;

  for(;;) {
    eladc = ADCRL;
    if(eladc < 16){
    	distancia = ((5*eladc) - 10)/2;
    }else if(eladc < 24){
    	distancia = ((125*eladc) + 1000)/100;
    }
    enviarNum(eladc);
  } 
}
