/*
 * 	LAB 10 
 * 	Rodrigo Cordero 17001922
 * 	Marcelo del Aguila 17001380
 */

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

char valADC = 0;
char m = 0;
int vddConv = 0;
int ADCRTemp25 = 0;
int ADCRmCold = 0;
int ADCRmHot = 0;
int temperatura = 0;

int centenas, decenas;

//100Temp = 2500 - [(Vtemp - Vtemp25)*100/164]
//100Temp = 2500 - [(Vtemp - Vtemp25)*100/176]
void enviarADC(int num){
	
	while((SCIS1 & 0b10000000) == 0);
	
	if(num == 0){
		SCID = '0';
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
	}else {
		SCID = '0';
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
	}else {
		SCID = '0';
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
	SCID = '\n';
	
	while((SCIS1 & 0b10000000) == 0);
	SCID = '\r';
	
	return;
}


void enviarTemp(int num){
	
	while((SCIS1 & 0b10000000) == 0);
	
	if(num == 0){
		SCID = '0';
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
	} else {
		SCID = '0';
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
	SCID = 'C';
	
	while((SCIS1 & 0b10000000) == 0);
	SCID = '\t';
	
	while((SCIS1 & 0b10000000) == 0);
	SCID = '\t';
	
	return;
}

void main(void) {
	
  DisableInterrupts;
  
  SOPT1_COPT = 0; // matamos al chucho
  SPMSC1 |= 1;	// Activar Bandgap
  
  // Termistor
  //ADCCFG = 0b01111011;  //High Speed, 1MHz, Long Sample, 10bits, asincrono
  ADCCFG = 0b00101000;  
 /* APCTL1_ADPC0 = 1;  
  ADCSC1_AIEN = 0; 
  ADCSC1_ADCO = 1; 
  ADCSC1_ADCH = 0;*/
  
  //Serial
  SCIBDL = 0b110101;	// (8MHz)/(9600*16) = 52
  SCIC3 |= 0b1110;
  SCIC2 |= 0b00101100;
  
  //Trim
  //ICSTRM = 0b10110101;
  ICSTRM = 0x90;
  ICSSC_FTRIM = 1;
  
  //Bandgap
  ADCSC1_AIEN = 1;	//Interrupciones
  ADCSC1_ADCO = 1;	//Continuo
  ADCSC1_ADCH = 27;	// ADC27
  
  EnableInterrupts;

  for(;;) {
    
  } 
  
}

interrupt 23 void ADCInt(void){
	if(vddConv == 0){
		int conversion = (ADCRL | ADCRH << 8);  
		vddConv = 12276/conversion;
		ADCRTemp25 = 7173/vddConv;
		ADCRmCold = 1684/vddConv;
		ADCRmHot = 1810/vddConv;
		ADCSC1_ADCH = 26;	// Temperatura
	}else{
		int conversion = (ADCRL | ADCRH << 8);
		
		if( conversion > ADCRTemp25 ){ //Frio
			temperatura = 25 - (((conversion - ADCRTemp25)/ADCRmCold));
		}else{			// Calor 
			temperatura = 25 - (((conversion - ADCRTemp25)/ADCRmHot));
		}
		ADCSC1_ADCH = 26;	// Temperatura
		enviarTemp(temperatura);
		enviarADC(conversion);
	}
}
