//defina abaixo, o tempo que será feito cada medida e o valor de A e B encontrados na calibração
#define     TEMPERATURA_EXPERIMENTO_1    0.0 //insira em kelvin   e coloque o numero com .0
#define     TEMPERATURA_EXPERIMENTO_2     0.0 //insira em kelvin e coloque o numero com .0


#define     RESISTOR                      1000 //Esse valor é fixo e é dado pelo Beto

#include <math.h>

int termistor= A0; //porta do termistor 
int val_discretizado = 0; 
float ddp = 0.0; //diferença de potencial a ser lida pelo arduino em volts  
 

char rx_byte = 0; 
int auxiliar = 0;
int i = 0;

float ddp_1 = 0.0;
float ddp_2 = 0.0;
float ddp_acumulado = 0.0; 

double valor_A = 0.0; 
double valor_B = 0.0; 
 


void setup(){
  Serial.begin(9600); 
}


void loop(){
  if ((TEMPERATURA_EXPERIMENTO_1  < 270) || (TEMPERATURA_EXPERIMENTO_2 < 270))
  {
    Serial.println("Insira temperaturas para os experimentos em kelvin e reenvie o código clicando no botao de seta para direita no contao superior direito");
    delay(10000000000); 
  }
    

   if (auxiliar==0)
   {
     Serial.println("Envie um número para começar a coletar dados para o experimento!");
      auxiliar++;    
   }

   if (Serial.available() > 0)
   {
      Serial.println("Iniciando leitura de dados...");
      rx_byte=Serial.read();
   }

    //le o valor do arduino e converte para um número em volts
   if (rx_byte!=0)
   {

      if (ddp_1 == 0)
      {
        Serial.println("iniciando experimento 1! ");
        for (int i=1; i <= 90; i++)
        {
              val_discretizado = analogRead(termistor); 
              ddp = (float) val_discretizado * 0.0049; 
              Serial.print(i);
              Serial.print("/90   =  ");
              Serial.println(ddp);
              ddp_acumulado = ddp_acumulado + ddp; 
              delay(500); 
        }
       
        ddp_1= ddp_acumulado/90; 

        Serial.println();
        Serial.println("Experimento 1 concluído!");
        Serial.print("O valor médio de DDP encontrado foi ");
        Serial.println(ddp_1);
 
        Serial.println();

        rx_byte=0; 
        ddp_acumulado=0.0; 
        auxiliar=0;         
      }
     else if (ddp_2 == 0) 
      {
        Serial.println("iniciando experimento 2! ");
        for (int i=1; i <= 90; i++)
        {
              val_discretizado = analogRead(termistor); 
              ddp = (float) val_discretizado * 0.0049; 
              Serial.print(i);
              Serial.print("/90   =  ");
              Serial.println(ddp);
              ddp_acumulado = ddp_acumulado + ddp; 
              delay(500); 
         }
        ddp_2= ddp_acumulado/90; 
        Serial.print("O valor médio de DDP encontrado foi ");
        Serial.println(ddp_2);
        Serial.println();

        
        ddp_acumulado=0.0;
        auxiliar=0;
      }

      else
      {
        valor_B = (TEMPERATURA_EXPERIMENTO_1 * TEMPERATURA_EXPERIMENTO_2)/(TEMPERATURA_EXPERIMENTO_1-TEMPERATURA_EXPERIMENTO_2); //* log((ddp_2*(5.0-ddp_1)/(ddp_1*(5.0-ddp_2))));
        valor_A = (double) (((ddp_1*RESISTOR)/(5.0-ddp_1) * (1/(exp(valor_B/TEMPERATURA_EXPERIMENTO_1)))));  
        Serial.println("Calibração completa!");
        Serial.print("Valor de A calibrado é ");
        Serial.println(valor_A);
        
        Serial.print("Valor de B calibrado é ");
        Serial.println(valor_B);
        delay(10000000000000); 
        
      }
 
    }
}

