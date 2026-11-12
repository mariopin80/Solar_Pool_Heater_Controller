/****************************************************/
/* Controlador de terperatura e filtro para piscina */
/* Autor: Mario Pin                                 */
/* Vesão: 0.0.1 - 13/05/2021                        */
/****************************************************/

#include <LiquidCrystal.h>
#include <BigNums2x2.h>
#include <EEPROM.h>



// define as portas a serem usadas pelas entradas e saidas de dados
#define PB1 2 //input Menu/Enter
#define PB2 3 //input NXT/+
#define PB3 4 //input ESC/-
#define AQC 5 //output relé aquecedor
#define FIL 6 //output relé filtro
#define PSC A0 //analog sensor piscina
#define CLT A1 //analog sensor coletor

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); //define pinos do LCD (RS, E, D4, D5, D6, D7)
BigNums2x2 bigNuma(NASA);
static DS1307 RTC1;

//cria os possiveis estados do menu e inicializa em HOME
enum Estados{HOME, GERAL, AJUSTES_AQC,AJUSTES_FIL, ADJ_T, DIFF_ON, DIFF_OFF};
Estados estado = HOME;

//strings para os dias da semana
String semana[]{"DOM", "SEG", "TER", "QUA", "QUI", "SEX", "SAB"}; 

//cria variaveis globais
float pscTemp;
float cltTemp;
float pscOS;
float cltOS;
float difTempON;
float difTempOFF;
float tempSet;
byte minuto;
byte hora;
byte dia;
byte mes;
byte dsemana;
int ano;



//funcao para atualizar os dados
void atualiza_sistema();

void setup(){
  lcd.begin(16,2); //inicializa display lcd
  RTC1.begin();
  RTC1.startClock();

  //*** USAR SOMENTE na montagem inicial ***
  /*
  tempSet = 25.0;
  difTempON = 12.0;
  difTempOFF = 5.0;
  pscOS = 0.0;
  cltOS = 0.0;
  EEPROM.put(0, tempSet);
  EEPROM.put(4, difTempON);
  EEPROM.put(8, difTempOFF);
  EEPROM.put(12, pscOS);
  EEPROM.put(16, cltOS);  
  */

  /*
  RTC1.setDate(27,05,21);
  RTC1.setTime(13,52,35);
  */
  
  //busca valores de parametros na EEPROM
  EEPROM.get(0, tempSet);
  EEPROM.get(4, difTempON);
  EEPROM.get(8, difTempOFF);
  EEPROM.get(12, pscOS);
  EEPROM.get(16, cltOS);

  //inicializa entradas e saidas
  pinMode(PB1, INPUT_PULLUP);
  pinMode(PB2, INPUT_PULLUP);
  pinMode(PB3, INPUT_PULLUP);
  pinMode(AQC, OUTPUT);
  pinMode(FIL, OUTPUT);  

  //tela de inicializacao
  byte i;
  lcd.setCursor(1,0);
  lcd.print("MP LABS PSC-01");
  lcd.setCursor(0,1);
  for (i=0; i<=19; i++){
    lcd.write(255);
    delay(50);
  }
}

void loop(){
  switch(estado){
    
    case HOME:{  //*********************************************HOME**************************************************
      lcd.clear();
      lcd.setCursor(7,1);
      lcd.write(223); lcd.print("C");
      while (digitalRead(PB1) && digitalRead(PB2) == HIGH){
        
        atualiza_sistema();
        
        bigNuma.print(pscTemp, 2, 0, 0); 
        lcd.setCursor(5,1);
        int decimal = pscTemp * 100; decimal = decimal % 100; decimal = decimal/10;
        lcd.print("."); lcd.print(decimal);

        if (hora < 10)
           lcd.setCursor(12, 0);
        else
           lcd.setCursor(11, 0); 
        lcd.print(hora);
        if (segundo % 2 == 0)
           lcd.print(":"); 
        else
           lcd.print(" ");   
        if (minuto < 10)
           lcd.print("0");
        lcd.print(minuto); 
        

        lcd.setCursor(11, 1);
        lcd.print(semana[dsemana]);
        delay (100);
         }

      //saida da pagina HOME      
      if (digitalRead(PB2) == LOW)
        estado = GERAL;
      if (digitalRead(PB1) == LOW)
        estado = AJUSTES_AQC;  
      delay(300);
      break;
      }
      
    case GERAL:{  //****************************************************GERAL**************************************
      lcd.clear();
      while (digitalRead(PB2) && digitalRead(PB3) == HIGH){

        atualiza_sistema();
        
        lcd.setCursor(0,0);
        lcd.print(semana[dsemana]); 
        lcd.setCursor(6, 0);
        if (pscTemp < 10)
          lcd.print("PSC  ");
        else
          lcd.print("PSC ");
        lcd.print(pscTemp, 1); lcd.write(223); lcd.print("C");
        lcd.setCursor(0,1);
        lcd.print(hora); lcd.print(":"); lcd.print(minuto); lcd.print(":"); lcd.print(segundo);
        lcd.setCursor(6, 10);
        if (cltTemp < 10)
          lcd.print("CLT  ");
        else
          lcd.print("CLT ");
        lcd.print(cltTemp, 1); lcd.write(223); lcd.print("C");
        if (digitalRead(PB3) == LOW)
          estado = HOME;
        delay(200);
        }

      estado = HOME;
      delay(200);
      break;
      }
    
    case AJUSTES_AQC:{  //****************************Entrada de ajustes de aquecedor***********************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CONFIG AQUECEDOR");
      while (digitalRead(PB1) && digitalRead(PB2) && digitalRead(PB3) == HIGH){

        atualiza_sistema();
        
        }
      if (digitalRead(PB1) == LOW)
        estado = AJUSTES_FIL;
      if (digitalRead(PB2) == LOW)
        estado = ADJ_T; 
      if (digitalRead(PB3) == LOW)
        estado = HOME;   
      delay(200);
      break;
      }  
    case AJUSTES_FIL:{  //****************************Entrada de ajustes do filtro***********************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CONFIG FILTRO");
      while (digitalRead(PB1) && digitalRead(PB2) && digitalRead(PB3) == HIGH){

        atualiza_sistema();
        
        }
      if (digitalRead(PB1) == LOW)
        estado = HOME;
      if (digitalRead(PB2) == LOW)
        estado = ADJ_T; 
      if (digitalRead(PB3) == LOW)
        estado = HOME; 
      delay(200);
      break;
      }    

    case ADJ_T:{  //******************************Ajuste de Temperatura da piscina********************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TEMP PISCINA");
      while (digitalRead(PB2) && digitalRead(PB3) == HIGH){
        atualiza_sistema();
        lcd.setCursor(1,1);
        lcd.print(tempSet, 1); lcd.write(223); lcd.print("C");
        if (digitalRead(PB1) == LOW){
          lcd.setCursor(0, 1);
          lcd.write(">");
          delay(200);
          while (digitalRead(PB1) == HIGH){
            atualiza_sistema();
            delay(100);
            if (digitalRead (PB2) == LOW){
              tempSet = tempSet + 0.1;
              lcd.setCursor(1,1);
              lcd.print(tempSet, 1); lcd.write(223); lcd.print("C  ");
            }
            if (digitalRead (PB3) == LOW){
              tempSet = tempSet - 0.1;
              lcd.setCursor(1,1);
              lcd.print(tempSet, 1); lcd.write(223); lcd.print("C  ");
            }
          }
          lcd.setCursor(0,1);
          lcd.print(" ");
         }
        delay(200);
        }
      EEPROM.put(0, tempSet);
      if (digitalRead(PB2) == LOW)
        estado = DIFF_ON;
      if (digitalRead(PB3) == LOW)
        estado = AJUSTES_AQC;    
      delay(300);

      break;
      }

    case DIFF_ON:{  //***********************Ajuste de temperatura diferencial para ligar**************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DIFERENCIAL LIGA");
      while (digitalRead(PB2) && digitalRead(PB3) == HIGH){
        atualiza_sistema();
        lcd.setCursor(1,1);
        lcd.print(difTempON, 1); lcd.write(223); lcd.print("C");
        if (digitalRead(PB1) == LOW){
          lcd.setCursor(0, 1);
          lcd.write(">");
          delay(200);
          while (digitalRead(PB1) == HIGH){
            atualiza_sistema();
            delay(100);
            if (digitalRead (PB2) == LOW){
              difTempON = difTempON + 0.1;
              lcd.setCursor(1,1);
              lcd.print(difTempON, 1); lcd.write(223); lcd.print("C  ");
            }
            if (digitalRead (PB3) == LOW){
              difTempON = difTempON - 0.1;
              lcd.setCursor(1,1);
              lcd.print(difTempON, 1); lcd.write(223); lcd.print("C  ");
            }
          }
          lcd.setCursor(0,1);
          lcd.print(" ");
         }
        delay(200);
        }
      EEPROM.put(4, difTempON);
      if (digitalRead(PB2) == LOW)
        estado = DIFF_OFF;
      if (digitalRead(PB3) == LOW)
        estado = AJUSTES_AQC;    
      delay(300);

      break;
      }

    case DIFF_OFF:{  //******************************Ajuste de temperatura diferencial para desligar********************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DIFERENCIAL DESL");
      while (digitalRead(PB2) && digitalRead(PB3) == HIGH){
        atualiza_sistema();
        lcd.setCursor(1,1);
        lcd.print(difTempOFF, 1); lcd.write(223); lcd.print("C");
        if (digitalRead(PB1) == LOW){
          lcd.setCursor(0, 1);
          lcd.write(">");
          delay(200);
          while (digitalRead(PB1) == HIGH){
            atualiza_sistema();
            delay(100);
            if (digitalRead (PB2) == LOW){
              difTempOFF = difTempOFF + 0.1;
              lcd.setCursor(1,1);
              lcd.print(difTempOFF, 1); lcd.write(223); lcd.print("C  ");
            }
            if (digitalRead (PB3) == LOW){
              difTempOFF = difTempOFF - 0.1;
              lcd.setCursor(1,1);
              lcd.print(difTempOFF, 1); lcd.write(223); lcd.print("C  ");
            }
          }
          lcd.setCursor(0,1);
          lcd.print(" ");
         }
        delay(200);
        }
      EEPROM.put(8, difTempOFF);
      if (digitalRead(PB2) == LOW)
        estado = AJUSTES_AQC;
      if (digitalRead(PB3) == LOW)
        estado = AJUSTES_AQC;    
      delay(300);

      break;
      }




        
    }
}



void atualiza_sistema(){
  pscTemp = 0.05376 * analogRead(PSC);
  cltTemp = 0.05376 * analogRead(CLT);
  if(pscTemp < tempSet-0.3 && difTempON < (cltTemp - pscTemp))
    digitalWrite(AQC, HIGH);
  if(pscTemp > tempSet || difTempOFF > (cltTemp - pscTemp))
    digitalWrite(AQC, LOW);
     
  hora = RTC1.getHours();
  minuto = RTC1.getMinutes();
  dsemana = 2;
  segundo = RTC1.getSeconds();
}
