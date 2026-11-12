/****************************************************/
/* Controlador de terperatura e filtro para piscina */
/* Autor: Mario Pin                                 */
/* Vesão: 0.0.5 - 28/05/2021                        */
/****************************************************/

#include <LiquidCrystal.h>
#include <BigNums2x2.h>
#include <EEPROM.h>
#include <RTC.h>

// define as portas a serem usadas pelas entradas e saidas de dados
#define PB_1 2 //input Menu/Enter
#define PB_2 3 //input NXT/+
#define PB_3 4 //input ESC/-
#define AQC 5 //output relé aquecedor
#define FIL 6 //output relé filtro
#define PSC A0 //analog sensor piscina
#define CLT A1 //analog sensor coletor

// parametros do termistor
const double beta = 3600.0;
const double r0 = 10000.0;
const double t0 = 273.15 + 25;
const float rx = r0 * exp(-beta/t0);

// parametros do circuito de medicao de temperatura
const double vcc = 5.0;
const double R = 10000.0;
 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); //define pinos do LCD (RS, E, D4, D5, D6, D7)
BigNums2x2 bigNuma(TREK); // inicializa as fontes grandes
static DS1307 RTC1;

//cria os possiveis estados do menu e inicializa em HOME
enum Estados{HOME, GERAL, AJUSTES_AQC, AJUSTES_FIL, PROG_1L, PROG_1D, PROG_2L, PROG_2D, AJUSTES_DH, HORA, DATA, SEMAN, AJUSTES_TEC, ADJ_T, DIFF_ON, DIFF_OFF, PSC_OS, CLT_OS};
Estados estado = HOME;

//strings para os dias da semana
String semana[]{"TOD", "DOM", "SEG", "TER", "QUA", "QUI", "SEX", "SAB", "FDS", "UTL"}; 

//cria variaveis globais
float pscTemp;
float cltTemp;
float pscOS;
float cltOS;
float difTempON;
float difTempOFF;
float DeICE = 4;
float OverHeat = 50;
float tempSet;
byte segundo;
byte minuto;
byte hora;
byte dia;
byte mes;
byte dsemana;
byte dsem_prog[2];
byte hora_prog[2];
byte min_prog[2];
int ano;
byte index;
bool semFlag = 0;

void atualiza_sistema();        //funcao para atualizar os dados
float configura (float param, float minimo, float maximo);  //funcao para entrada de configuracoes
int configuraDH (int param, int minimo, int maximo, int pos); //funcao para entrada de configuracoes de data

void setup(){
  lcd.begin(16,2); //inicializa display lcd
  RTC1.begin();
  
  //*** USAR SOMENTE na montagem inicial ***
  /*
  EEPROM.put(0, 25.0);
  EEPROM.put(4, 12.0);
  EEPROM.put(8,  5.0);
  EEPROM.put(12, 0.0);
  EEPROM.put(16, 0.0);
  EEPROM.put(20, 0x00);
  EEPROM.put(30, 0x00);
  EEPROM.put(40, 0x00);
  EEPROM.put(22, 0x00);
  EEPROM.put(32, 0x00);
  EEPROM.put(42, 0x00);   
  RTC1.setDate(27,05,21);
  RTC1.setTime(14,56,00);
  RTC1.setWeek(1);
  RTC1.startClock();
  */

  
  
  //busca valores de parametros na EEPROM
  EEPROM.get(0, tempSet);
  EEPROM.get(4, difTempON);
  EEPROM.get(8, difTempOFF);
  EEPROM.get(12, pscOS);
  EEPROM.get(16, cltOS);
  EEPROM.get(20, dsem_prog[0]);
  EEPROM.get(30, hora_prog[0]);
  EEPROM.get(40, min_prog[0]);
  EEPROM.get(22, dsem_prog[1]);
  EEPROM.get(32, hora_prog[1]);
  EEPROM.get(42, min_prog[1]);       

  //inicializa entradas e saidas
  pinMode(PB_1, INPUT_PULLUP);
  pinMode(PB_2, INPUT_PULLUP);
  pinMode(PB_3, INPUT_PULLUP);
  pinMode(AQC, OUTPUT);
  pinMode(FIL, OUTPUT);  

  //tela de inicializacao
  byte i;
  lcd.setCursor(0,0);
  lcd.print("MPS01 - v0.0.5");
  lcd.setCursor(0,1);
  for (i=0; i<=19; i++){
    lcd.write(255);
    delay(150);
  }
}

void loop(){
  switch(estado){
    
    case HOME:{  //*********************************************HOME**************************************************
      lcd.clear();
      lcd.setCursor(7,1);
      lcd.write(223); lcd.print("C");
      while (digitalRead(PB_1) && digitalRead(PB_2) == HIGH){
        atualiza_sistema();
        bigNuma.print(pscTemp, 2, 0, 0); 
        lcd.setCursor(5,1);
        int decimal = pscTemp * 100; decimal = decimal % 100; decimal = decimal/10;
        lcd.print("."); lcd.print(decimal);
        if (hora < 10){
           lcd.setCursor(11, 0);
           lcd.print (" ");
        }
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
        lcd.setCursor(13, 1);
        lcd.print(semana[dsemana]);
        delay (100);
         }
       if (digitalRead(PB_2) == LOW)
        estado = GERAL;
      if (digitalRead(PB_1) == LOW)
        estado = AJUSTES_AQC;  
      delay(200);
      break;
      }
      
    case GERAL:{  //****************************************************GERAL**************************************
      lcd.clear();
      while (digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        lcd.setCursor(0,0);
        lcd.print(semana[dsemana]); 
        lcd.setCursor(6, 0);
        if (pscTemp < 10)
          lcd.print("PSC  ");
        else
          lcd.print("PSC ");
        lcd.print(pscTemp, 1); lcd.write(223); lcd.print("C");
        if (hora < 10){
           lcd.setCursor(0, 0);
           lcd.print(" ");
        }
        else
           lcd.setCursor(0, 0); 
        lcd.print(hora);
        if (segundo % 2 == 0)
           lcd.print(":"); 
        else
           lcd.print(" ");   
        if (minuto < 10)
           lcd.print("0");
        lcd.print(minuto);
        lcd.setCursor(0, 1);
        lcd.print(semana[dsemana]);
        lcd.setCursor(6, 10);
        if (cltTemp < 10)
          lcd.print("CLT  ");
        else
          lcd.print("CLT ");
        lcd.print(cltTemp, 1); lcd.write(223); lcd.print("C");
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
      while (digitalRead(PB_1) && digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        }
      if (digitalRead(PB_1) == LOW)
        estado = AJUSTES_FIL;
      if (digitalRead(PB_2) == LOW)
        estado = ADJ_T; 
      if (digitalRead(PB_3) == LOW)
        estado = HOME;   
      delay(200);
      break;
      } 

    case ADJ_T:{  //**********************Ajuste de Temperatura da piscina**********************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TEMP PISCINA");
      tempSet = configura(tempSet, 10, 40);
      EEPROM.put(0, tempSet);
      if (digitalRead(PB_2) == LOW)
        estado = AJUSTES_AQC;
      if (digitalRead(PB_3) == LOW)
        estado = AJUSTES_AQC;    
      delay(200);
      break;
      }

       
    case AJUSTES_FIL:{  //****************************Entrada de ajustes do filtro***********************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CONFIG FILTRO");
      while (digitalRead(PB_1) && digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        }
      if (digitalRead(PB_1) == LOW)
        estado = AJUSTES_DH;
      if (digitalRead(PB_2) == LOW)
        estado = PROG_1L; 
      if (digitalRead(PB_3) == LOW)
        estado = HOME; 
      delay(200);
      break;
      } 

    case PROG_1L:{  //*****************Ajuste de PROG_1 LIGA **************************
      index = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PROG.1");
      lcd.setCursor(0,1);
      lcd.print("LIGA");
      lcd.setCursor(7,0);
      lcd.print(semana[dsem_prog[index]]); 
      lcd.print(" "); 
      if(hora_prog[index] < 10)
        lcd.print("0");
      lcd.print(hora_prog[index]); 
      lcd.print(":");
      if(min_prog[index] < 10)
        lcd.print("0");
      lcd.print(min_prog[index]);
      while (digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        if(digitalRead(PB_1) == LOW){
          semFlag = 1;
          dsem_prog[index]  = configuraDH(dsem_prog[index], 0, 9, 7);
          EEPROM.put(20+(2*index), dsem_prog[index]);
          delay(200);
          hora_prog[index] = configuraDH(hora_prog[index], 0, 23, 11);
          EEPROM.put(30+(2*index), hora_prog[index]);
          delay(200);
          min_prog[index] = configuraDH(min_prog[index], 0, 59, 14);
          EEPROM.put(40+(2*index), min_prog[index]);
          delay(200);
        }
      }
      if (digitalRead(PB_2) == LOW)
        estado = PROG_1D;
      if (digitalRead(PB_3) == LOW)
        estado = AJUSTES_FIL;    
      delay(200);
      break;
      }

    case PROG_1D:{  //*****************Ajuste de PROG_1 DESL **************************
      index = 1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PROG.1");
      lcd.setCursor(0,1);
      lcd.print("DESL");
      lcd.setCursor(7,0);
      lcd.print(semana[dsem_prog[index-1]]); 
      lcd.print(" "); 
      if(hora_prog[index] < 10)
        lcd.print("0");
      lcd.print(hora_prog[index]); 
      lcd.print(":");
      if(min_prog[index] < 10)
        lcd.print("0");
      lcd.print(min_prog[index]);
      while (digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        if(digitalRead(PB_1) == LOW){
          hora_prog[index] = configuraDH(hora_prog[index], 0, 23, 11);
          EEPROM.put(30+(2*index), hora_prog[index]);
          delay(200);
          min_prog[index] = configuraDH(min_prog[index], 0, 59, 14);
          EEPROM.put(40+(2*index), min_prog[index]);
          delay(200);
        }
      }
      if (digitalRead(PB_2) == LOW)
        estado = AJUSTES_FIL;
      if (digitalRead(PB_3) == LOW)
        estado = AJUSTES_FIL;    
      delay(200);
      break;
      }
      

    case AJUSTES_DH:{  //*******************************Entrada de data e hora***************************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CONFIG DATA/HORA");
      while (digitalRead(PB_1) && digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        }
      if (digitalRead(PB_1) == LOW)
        estado = AJUSTES_TEC;
      if (digitalRead(PB_2) == LOW)
        estado = HORA; 
      if (digitalRead(PB_3) == LOW)
        estado = HOME; 
      delay(200);
      break;
      }  

    case HORA:{  //*****************Ajuste de HORA **************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("HORA");
      lcd.setCursor(11,0);
      if(hora < 10)
        lcd.print("0");
      lcd.print(hora), lcd.print(":");
      if(minuto < 10)
        lcd.print("0");
      lcd.print(minuto);
      
      while (digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        if(digitalRead(PB_1) == LOW){
          hora  = configuraDH (hora, 0, 23, 11);
          RTC1.setHours(hora);
          delay(200);
          minuto = configuraDH(minuto, 0, 59, 14);
          RTC1.setMinutes(minuto);
          RTC1.setSeconds(0);
          delay(200);
        }
      }
      if (digitalRead(PB_2) == LOW)
        estado = DATA;
      if (digitalRead(PB_3) == LOW)
        estado = AJUSTES_DH;    
      delay(200);
      break;
      }

    case DATA:{  //*****************Ajuste de DATA **************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DATA");
      lcd.setCursor(6,0);
      if(dia < 10)
        lcd.print("0");
      lcd.print(dia); lcd.print("/"); 
      if(mes < 10)
        lcd.print("0");
      lcd.print(mes); lcd.print("/"); 
      lcd.print(ano);
      
      while (digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        if(digitalRead(PB_1) == LOW){
          dia  = configuraDH(dia, 1, 31, 6);
          RTC1.setDay(dia);
          delay(200);
          mes = configuraDH(mes, 1, 12, 9);
          RTC1.setMonth(mes);
          delay(200);
          ano = 2000 + configuraDH((ano - 2000), 00, 99, 14);
          RTC1.setYear(ano);
          delay(200);
        }
      }
      if (digitalRead(PB_2) == LOW)
        estado = SEMAN;
      if (digitalRead(PB_3) == LOW)
        estado = AJUSTES_DH;    
      delay(200);
      break;
      } 

    case SEMAN:{  //*****************Ajuste de DIA DA SEMANA **************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DIA SEMANA");
      lcd.setCursor(13,0);
      lcd.print(semana[dsemana]); 
            
      while (digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        if(digitalRead(PB_1) == LOW){
          semFlag = 1;
          dsemana  = configuraDH(dsemana, 1, 7, 13);
          RTC1.setWeek(dsemana);
          delay(200);
        }
      }
      if (digitalRead(PB_2) == LOW)
        estado = AJUSTES_DH;
      if (digitalRead(PB_3) == LOW)
        estado = AJUSTES_DH;    
      delay(200);
      break;
      }   
    

    case AJUSTES_TEC:{  //*******************************Entrada de ajustes tecnicos***************************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CONFIG TECNICA");
      while (digitalRead(PB_1) && digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        }
      if (digitalRead(PB_1) == LOW)
        estado = HOME;
      if (digitalRead(PB_2) == LOW)
        estado = DIFF_ON; 
      if (digitalRead(PB_3) == LOW)
        estado = HOME; 
      delay(200);
      break;
      }    

    case DIFF_ON:{  //***************Ajuste de temperatura diferencial para ligar******************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DIFERENCIAL LIGA");
      difTempON = configura(difTempON, 2, 25);
      EEPROM.put(4, difTempON);
      if (digitalRead(PB_2) == LOW)
        estado = DIFF_OFF;
      if (digitalRead(PB_3) == LOW)
        estado = AJUSTES_TEC;    
      delay(200);
      break;
      }

    case DIFF_OFF:{  //**************Ajuste de temperatura diferencial para desligar***************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DIFERENCIAL DESL");
      difTempOFF = configura(difTempOFF, 2, 25);
      EEPROM.put(8, difTempOFF);
      if (digitalRead(PB_2) == LOW)
        estado = PSC_OS;
      if (digitalRead(PB_3) == LOW)
        estado = AJUSTES_TEC;    
      delay(200);
      break;
      }

    case PSC_OS:{  //******************Ajuste de Offset sensor da piscina *************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("OFFSET SENS. PSC");
      pscOS = configura(pscOS, -5.0, 5.0);
      EEPROM.put(12, pscOS);
      if (digitalRead(PB_2) == LOW)
        estado = CLT_OS;
      if (digitalRead(PB_3) == LOW)
        estado = AJUSTES_TEC;    
      delay(200);
      break;
      }

    case CLT_OS:{  //*******************Ajuste de Offset sensor do coletor solar ******************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("OFFSET SENS. CLT");
      cltOS = configura(cltOS, -5.0, 5.0);
      EEPROM.put(16, cltOS);
      if (digitalRead(PB_2) == LOW)
        estado = AJUSTES_TEC;
      if (digitalRead(PB_3) == LOW)
        estado = AJUSTES_TEC;    
      delay(200);
      break;
      }
    }
}

//******************************************Funcoes auxiliares***************************************
void atualiza_sistema(){

  float v  = (vcc*analogRead(PSC))/1023;
  float rt = (vcc*R)/v - R;
  pscTemp  = (beta / log(rt/rx)) - 273 + pscOS;
    
  cltTemp  = 0.05376 * analogRead(CLT) + cltOS;
  
  if(cltTemp < DeICE || cltTemp > OverHeat) // verifica as condicoes excepcionais - congelamento e sobreaquecimento
    digitalWrite(AQC, HIGH);
    else{                                   // verifica o ajuste de temperatura
      if(pscTemp < (tempSet-0.5) && difTempON < (cltTemp - pscTemp))
        digitalWrite(AQC, HIGH);
      if(pscTemp > tempSet || difTempOFF > (cltTemp - pscTemp))
        digitalWrite(AQC, LOW);
    }
  
  hora    = RTC1.getHours();
  minuto  = RTC1.getMinutes();
  segundo = RTC1.getSeconds();
  dsemana = RTC1.getWeek();
  dia     = RTC1.getDay();
  mes     = RTC1.getMonth();
  ano     = RTC1.getYear();
}

float configura (float param, float minimo, float maximo){
  lcd.setCursor(1,1);
  lcd.print(param, 1); lcd.write(0xDF); lcd.print("C");
  while (digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        if (digitalRead(PB_1) == LOW){
          lcd.setCursor(0, 1);
          lcd.write(0x3E);
          delay(200);
          while (digitalRead(PB_1) == HIGH){
            atualiza_sistema();
            delay(100);
            if (digitalRead (PB_2) == LOW){
              if (param < maximo){
                param = param + 0.1;
                lcd.setCursor(1,1);
                lcd.print(param, 1); lcd.write(0xDF); lcd.print("C  ");
              }
            }
            if (digitalRead (PB_3) == LOW){
              if (param > minimo){
                param = param - 0.1;
                lcd.setCursor(1,1);
                lcd.print(param, 1); lcd.write(0xDF); lcd.print("C  ");
              }
            }
          }
          lcd.setCursor(0,1);
          lcd.print(" ");
         }
        delay(200);
        }
  return (param);
}

int configuraDH (int param, int minimo, int maximo , int pos){
  lcd.setCursor(pos, 1);
  lcd.write(0x5E); lcd.write(0x5E);
  delay(200);
  while (digitalRead(PB_1) == HIGH){
    atualiza_sistema();
    delay(100);
    if (digitalRead (PB_2) == LOW){
      if (param < maximo){
        param ++;
        lcd.setCursor(pos,0);
        if(semFlag == HIGH)
          lcd.print(semana[param]);
        else{
          if(param < 10)
            lcd.print("0");
        lcd.print(param);
                 }
              }
            }
    if (digitalRead (PB_3) == LOW){
      if (param > minimo){
        param --;
        lcd.setCursor(pos,0);
       if(semFlag == HIGH)
          lcd.print(semana[param]);
        else{
          if(param < 10)
            lcd.print("0");
        lcd.print(param);
        }
       }
      }
     }
  lcd.setCursor(pos,1);
  lcd.print("  ");
  semFlag = 0;
  return (param);
}
