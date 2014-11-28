#include <SoftwareSerial.h>

#define TACOMETER 5
#define GUIDAO A0

float TacAct = 0, TacPast = 0, Vact=0, Vpast=0;
float transicao=0;
int Vguidao;

void setup()  
{
    /*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/
    //Configurando a entrada digital
    pinMode(TACOMETER, INPUT_PULLUP);
   
    /*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/




  /*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/
  // Configurando a porta serial
  Serial.begin(9600);
  while (!Serial) {
    ; // Espera a porta serial conectar
  }
  /*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/
}

void loop() // run over and over
{
  int count = 0;
  /* Laço principal */
  for(;;)
  {
     /* Leitura de todos os sensores */
     /*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/
     /* Leitura de todos os sensores */
     
     TacAct = digitalRead(TACOMETER); // Tacometro
 
     Vguidao = analogRead(GUIDAO);
     
     /*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/
     
     /* Processamento de todas as informaçes */
     /*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/

     if((TacAct-TacPast)!=0)
     {
       transicao = 100;
     }
     else
     {
       transicao = -10;
     }
     
     Vact = 1*transicao/50 + Vpast;
     if(Vact < 0)
       Vact = 0;
     else if(Vact > 1000)
       Vact = 1000;
       
     /*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/
     
     /* Envio das informacoes */
     
     switch(Serial.read())
     {
       case 'a':
       
       Serial.println("valor = ");
       Serial.println(TacAct);
       
       break;
       
       case 'b':
       
       Serial.println("valor guidao = ");
       Serial.println(Vguidao);
       
       break;
       
       case 'c' :
       
       Serial.println("mixed = ");
       Serial.println(Vguidao);
       Serial.println(Vact);
       
       break;
       
       default :
        //Serial.println("mixed = ");
       //Serial.println(Vguidao);
       Serial.println(Vact);
       break;
       
     }
     
     /* Atualizacao das tretas */
     Vpast = Vact;
     TacPast = TacAct;
     delay(1);

     
  }
  
  
  /*
  for(;;)
  {
    switch(Serial.read())
    {
      case 'a':
        Serial.println("opçao 1");
      break;
      
      case 'b':
        Serial.println("opçao 2");
      break;
      
      default:
        break;
        //Serial.println("opçao 3");
      
      
    }

  }
*/
/*
    while(1)
    {
      if(Serial.read()=='a')
        Serial.println("Hello, world?");
    }*/
}

