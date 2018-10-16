//defina abaixo, o tempo que será feito cada medida e o valor de A e B encontrados na calibração
#define     TEMPO_EM_MILISEGUNDOS         1000
#define     A_CALIBRADO                   0.34
#define     B_CALIBRADO                   2343.25


#define     RESISTOR                      10000

#include <math.h>

int termistor= A0; //porta do termistor 
int val_discretizado = 0; 

float ddp = 0.0; //diferença de potencial a ser lida pelo arduino em volts  
double temperatura = 0.0; 
unsigned long tempo_atual = 0; //tempo transcorrido de medidas

char rx_byte = 0; 
int auxiliar=0;
void setup(){
	Serial.begin(9600); 
}


void loop(){
    
	if ((A_CALIBRADO == 0.0) || (B_CALIBRADO == 0.0)){
		Serial.println("Insira os valores de calibração e reenvie o código clicando no botao de seta para direita no contao superior direito");
		delay(10000); 
	}
 
  if(tempo_atual ==0){

    if (auxiliar==0){
        Serial.println("Envie um número para começar o experimento!");
        auxiliar++;    
    }

    if (Serial.available() > 0){
      
        Serial.println("nova entrada enviada!");
        rx_byte=Serial.read();
     }

  }
		//le o valor do arduino e converte para um número em volts
    if (rx_byte!=0){
      
		    val_discretizado = analogRead(termistor); 
		    ddp = (float) val_discretizado * 0.0049; 

		    temperatura= (double) (B_CALIBRADO)/log((RESISTOR*ddp)/(A_CALIBRADO*(5-ddp))); 

		    Serial.print(tempo_atual);
		    Serial.print(',');
		    Serial.println(temperatura);

	    	tempo_atual=tempo_atual+TEMPO_EM_MILISEGUNDOS;

		    delay(TEMPO_EM_MILISEGUNDOS); 
    }
}

