/* 
 Rodrigo Cordero 17001922
 Marcelo del Aguila 17001380
 Código por Eduardo Corpeño 
*/


#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */



#define CW 0
#define CCW 1

unsigned char *patron;
unsigned char patronFSHT[8]={0b00001000,0b00000100,0b00000010,0b00000001,
                             0b00001000,0b00000100,0b00000010,0b00000001};

unsigned char patronFSFT[8]={0b00001001,0b00001100,0b00000110,0b00000011, 
                             0b00001001,0b00001100,0b00000110,0b00000011};

unsigned char patronHS[8]  ={0b00001001,0b00001000,0b00001100,0b00000100,
							 0b00000110,0b00000010,0b00000011,0b00000001};
unsigned char fase = 0;
unsigned char sentido = CW;
unsigned char retardo = 0;
unsigned char detenido = 0;
unsigned char eladc = 0;

void wait(){
	volatile long int x;
	volatile long int y;
	volatile long int z;

	x=retardo*10;
	while(x){  //
		x--;  //  reemplazado por x=0;
		y=retardo;
		while(y)
			y--;
	}
	
}

void main(void) {
  DisableInterrupts;
  
  //patron = patronHS;
  patron = patronFSHT;   
  //patron = patronFSFT;
    
  SOPT1_COPT=0; 

  
  PTBDD_PTBDD3=1; 
  PTBDD_PTBDD2=1;
  PTBDD_PTBDD1=1;
  PTBDD_PTBDD0=1;
  
  ADCCFG = 0b00100000;
  APCTL1_ADPC0 = 1;
  ADCSC1_AIEN = 0; 
  ADCSC1_ADCO = 1; 
  ADCSC1_ADCH = 0;  
    

  for(;;) {
	  eladc=ADCRL;
	  if(((unsigned char)eladc)>=0x90){
		  sentido=CW;
		  detenido=0;
		  retardo = eladc-0x90;
	  }
	  else if(((unsigned char)eladc)<=0x70){
          sentido=CCW;
		  detenido=0;
		  retardo = 0x70-eladc;
	  }
	  else
		  detenido=1;
	  
	  // ESTO SE ME FUE EN CLASE!!!!
	  if(!detenido){
		  
		  PTBD_PTBD0 = (patron[fase] & 0b00000001)>>0;
		  PTBD_PTBD2 = (patron[fase] & 0b00000010)>>1;
		  PTBD_PTBD1 = (patron[fase] & 0b00000100)>>2;
		  PTBD_PTBD3 = (patron[fase] & 0b00001000)>>3;
		  
		  // cambiar fase
		  if(sentido==CW)
			  fase=(fase+1)&0b00000111;
		  else
			  fase=(fase-1)&0b00000111;  // sup. 0-1=255
	  
		  // esperar
		  wait();
  	  }
  } 
}
