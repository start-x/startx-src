#include <SoftwareSerial.h>
#include <Servo.h>

#define TACOMETER 5
#define GUIDAO A0
#define SERVO_PIN 9

Servo servoBrk;


float TacAct = 0, TacPast = 0, Vact=0, Vpast=0, velocity = 0;
float transicao=0;
int Vguidao;

void setup()  
{
    /*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/
    //Configurando a entrada digital
    pinMode(TACOMETER, INPUT_PULLUP);
   
    /*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/
    
    /*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/    
    /* configurando o servomotor*/
    servoBrk.attach(SERVO_PIN);
    
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
  int count = 0, cmd;
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
  if(count < 120)
  {
       if((TacAct-TacPast)!=0)
       {
         transicao = 1;
       }
       else
       {
         transicao = 0;
       }
       
       Vact = 1*transicao/1 + Vact;
       if(Vact < 0)
         Vact = 0;
       else if(Vact > 1000)
         Vact = 1000;
       
       count++;
  }
  else 
  {
    velocity = Vact;
    Vact = 0;
    count = 0;
  }
     /*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/
     
     /* Envio das informacoes */
     
     switch(cmd = Serial.read())
     {

       case 'A' :
       
       //Serial.println("mixed = ");
       Serial.print(Vguidao);
       Serial.print(' ');
       Serial.println(velocity);
       
       break;
       
       case '0':
       case '1':
       case '2':
       case '3':
       case '4':
       case '5':
       case '6':
       case '7':
       case '8':
       case '9':
       
       
       cmd = map(cmd, '0', '9', 0, 90); // 0 <= pot_direction <= 179
       servoBrk.write(cmd);
       Serial.println(cmd);
       
       break;
       
       default :
        //Serial.println("mixed = ");
       //Serial.println(Vguidao);
       //Serial.println(velocity);
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

