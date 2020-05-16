#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

unsigned short i = 0;
unsigned char valSCI;
unsigned char respuesta;

void configurarBT(void){

	//Nombre
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'A';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'T';
	while((SCIS1 & 0b10000000) == 0);
	SCID = '+';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'N';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'A';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'M';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'E';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'R';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'A';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'C';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'A';
	while((SCIS1 & 0b10000000) == 0);
	SCID = '_';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'B';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'T';
	while((SCIS1 & 0b10000000) == 0);
	SCID = '2';
	
	while(i < 2){
		while((SCIS1 & 0b00100000) == 0);
		if(SCID == 'e'){
			i = i + 1;
		}
	}
	
	i = 0;
	
	//Contraseña
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'A';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'T';
	while((SCIS1 & 0b10000000) == 0);
	SCID = '+';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'P';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'I';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'N';
	while((SCIS1 & 0b10000000) == 0);
	SCID = '9';
	while((SCIS1 & 0b10000000) == 0);
	SCID = '6';
	while((SCIS1 & 0b10000000) == 0);
	SCID = '0';
	while((SCIS1 & 0b10000000) == 0);
	SCID = '0';
	
	while(i < 1){
		while((SCIS1 & 0b00100000) == 0);
		if(SCID == 'N'){
			i = i + 1;
		}
	}
	
	i = 0;
	
	//Contraseña
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'A';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'T';
	while((SCIS1 & 0b10000000) == 0);
	SCID = '+';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'B';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'A';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'U';
	while((SCIS1 & 0b10000000) == 0);
	SCID = 'D';
	while((SCIS1 & 0b10000000) == 0);
	SCID = '4';
	
	while(i < 2){
		while((SCIS1 & 0b00100000) == 0);
		if(SCID == '0'){
			i = i + 1;
		}
	}
	
	while((SCIS1 & 0b10000000) == 0);
	SCID = '\n';
	while((SCIS1 & 0b10000000) == 0);
	SCID = '\r';
	
}


void main(void) {
  DisableInterrupts;
  
  SOPT1_COPT=0; // matamos al chucho
  
  //Serial
  SCIBDL = 0b110101;	// (8MHz)/(9600*16) = 52
  SCIC3 |= 0b1110;
  SCIC2 |= 0b00101100;
  
  ICSTRM = 0x90;
  ICSSC_FTRIM = 1;
  
  configurarBT();

  for(;;) {
	while((SCIS1 & 0b00100000) == 0);
	respuesta = SCID;
	if(respuesta > 64 && respuesta < 91)
		respuesta = respuesta + 32;
	while((SCIS1 & 0b10000000) == 0);
	SCID = respuesta;
  } 
}
