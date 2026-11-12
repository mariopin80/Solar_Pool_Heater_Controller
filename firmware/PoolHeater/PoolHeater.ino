/****************************************************/
/* Controlador de terperatura e filtro para piscina */
/* Autor: Mario Pin                                 */
/* Vesão: 0.1.0 - 22/06/2021  >>>MVP<<<             */
/****************************************************/

#include <LiquidCrystal.h>
#include <BigNums2x2.h>
#include <EEPROM.h>
#include <RTC.h>

// define as portas a serem usadas pelas entradas e saidas de dados
#define PB_1 4 //input Menu/Enter
#define PB_2 3 //input NXT/+
#define PB_3 2 //input ESC/-
#define AQC 6 //output relé aquecedor
#define FIL 5 //output relé filtro
#define PSC A0 //analog sensor piscina
#define CLT A1 //analog sensor coletor
#define RS 8
#define EN 9
#define D4 13
#define D5 12
#define D6 11
#define D7 10

// parametros do termistor
const double beta = 3600.0;
const double r0 = 10000.0;
const double t0 = 273.15 + 25;
const float rx = r0 * exp(-beta/t0);

// parametros do circuito de medicao de temperatura
const double vcc = 5.0;
const double R = 10000.0;
 
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //define pinos do LCD
BigNums2x2 bigNuma(TREK); // inicializa as fontes grandes
static DS1307 RTC1;

//cria os possiveis estados do menu e inicializa em HOME
enum Estados{HOME, GERAL, BOMBAS, AJUSTES_AQC, AJUSTES_FIL, PROG_1L, PROG_1D, PROG_2L, PROG_2D, AJUSTES_DH, HORA, DATA, SEMAN, AJUSTES_TEC, ADJ_BOMBAS, ADJ_T, PISC_LG, PISC_DL, DIFF_ON, DIFF_OFF, PSC_OS, CLT_OS};
Estados estado = HOME;

//strings para os dias da semana
String semana[]{"TOD", "DOM", "SEG", "TER", "QUA", "QUI", "SEX", "SAB", "FDS", "UTL"}; 
String bomba[]{"AUTO", "LIGA", "DESL"};

//cria variaveis globais
float pscTemp;
float cltTemp;
float pscOS;
float cltOS;
float difTempON;
float difTempOFF;
float DeICE = 4;
float OverHeat = 60;
float tempSet;
float v;
float rt;
byte segundo;
byte minuto;
byte hora;
byte dia;
byte mes;
byte dsemana;
byte dsem_prog[2];
byte hora_prog[2];
byte min_prog[2];
byte AQC_bomba;
byte FIL_bomba;
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
  EEPROM.put(50, 0x00);
  EEPROM.put(52, 0x00);  
  RTC1.setDate(01,01,00);
  RTC1.setTime(00,00,00);
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
  EEPROM.get(50, AQC_bomba);
  EEPROM.get(52, FIL_bomba);  

  //inicializa entradas e saidas
  pinMode(PB_1, INPUT_PULLUP);
  pinMode(PB_2, INPUT_PULLUP);
  pinMode(PB_3, INPUT_PULLUP);
  pinMode(AQC, OUTPUT);
  pinMode(FIL, OUTPUT);  

  //tela de inicializacao
  byte i;
  lcd.setCursor(0,0);
  lcd.print("MPS01-v0.1.0 MVP");
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
      lcd.setCursor(7,1); lcd.write(223); lcd.print("C");
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
        lcd.setCursor(13, 1); lcd.print(semana[dsemana]);
        delay (100);
         }
       if (digitalRead(PB_2) == LOW)
        estado = GERAL;
      if (digitalRead(PB_1) == LOW)
        estado = BOMBAS;  
      delay(200);
      break;
      }
      
    case GERAL:{  //****************************************************GERAL**************************************
      lcd.clear();
      while (digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        lcd.setCursor(0,0); lcd.print(semana[dsemana]); 
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
        lcd.setCursor(0, 1); lcd.print(semana[dsemana]);
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
    
    case BOMBAS:{  //****************************Entrada de estados das bombas***********************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ESTADO BOMBAS");
      while (digitalRead(PB_1) && digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        }
      if (digitalRead(PB_1) == LOW)
        estado = AJUSTES_AQC;
      if (digitalRead(PB_2) == LOW)
        estado = ADJ_BOMBAS; 
      if (digitalRead(PB_3) == LOW)
        estado = HOME;   
      delay(200);
      break;
      } 
    
    case ADJ_BOMBAS:{  //**********************Ajuste de estado das bombas**********************
      lcd.clear();
      lcd.setCursor(0,0); lcd.print(" AQUEC.  FILTRO");
      lcd.setCursor(1,1); lcd.print (bomba[AQC_bomba]);
      lcd.setCursor(9,1); lcd.print (bomba[FIL_bomba]);

      while (digitalRead(PB_2) && digitalRead(PB_3) == HIGH){
        atualiza_sistema();
        if (digitalRead(PB_1) == LOW){
          lcd.setCursor(0, 1); lcd.write(0x3E);
          delay(200);
          while (digitalRead(PB_1) == HIGH){
            atualiza_sistema();
            delay(200);
            if (digitalRead (PB_2) == LOW){
              if (AQC_bomba < 2){
                AQC_bomba ++;
                lcd.setCursor(1,1); lcd.print(bomba[AQC_bomba]);
              }
            }
            if (digitalRead (PB_3) == LOW){
              if (AQC_bomba > 0){
                AQC_bomba --;
                lcd.setCursor(1,1); lcd.print(bomba[AQC_bomba]);
              }
            }
          }
          lcd.setCursor(0,1); lcd.print(" ");
          lcd.setCursor(8, 1); lcd.write(0x3E);
          delay(200);
          while (digitalRead(PB_1) == HIGH){
            atualiza_sistema();
            delay(200);
            if (digitalRead (PB_2) == LOW){
              if (FIL_bomba < 2){
                FIL_bomba ++;
                lcd.setCursor(9,1); lcd.print(bomba[FIL_bomba]);
              }
            }
            if (digitalRead (PB_3) == LOW){
              if (FIL_bomba > 0){
                FIL_bomba --;
                lcd.setCursor(9,1); lcd.print(bomba[FIL_bomba]);
              }
            }
          }
          lcd.setCursor(8,1); lcd.print(" ");
          delay(200);
      }
      EEPROM.put(50, AQC_bomba);
      EEPROM.put(52, FIL_bomba);
      }
      if (digitalRead(PB_2) == LOW)
        estado = BOMBAS;
      if (digitalRead(PB_3) == LOW)
        estado = BOMBAS;    
      delay(200);
      break;
      }
    
    case AJUSTES_AQC:{  //****************************Entrada de ajustes de aquecedor***********************************
      lcd.clear();
      lcd.setCursor(0,0); lcd.print("AJUSTE AQUECEDOR");
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


//#####################################################################################################

    case PISC_LG:{  //*****************Ajuste de PROG_1 LIGA **************************
      index = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LIGA");
      lcd.setCursor(0,1);
      lcd.print("CIRC DIARIA");
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
        estado = PISC_DL;
      if (digitalRead(PB_3) == LOW)
        estado = AJUSTES_AQC;    
      delay(200);
      break;
      }

    case PISC_DL:{  //*****************Ajuste de PROG_1 DESL **************************
      index = 1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DESL");
      lcd.setCursor(0,1);
      lcd.print("CIRC DIARIA");
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
        estado = AJUSTES_AQC;
      if (digitalRead(PB_3) == LOW)
        estado = AJUSTES_AQC;    
      delay(200);
      break;
      }

//#####################################################################################################


       
    case AJUSTES_FIL:{  //****************************Entrada de ajustes do filtro***********************************
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("AJUSTE FILTRO");
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
      lcd.print("LIGA");
      lcd.setCursor(0,1);
      lcd.print("PROG.1");
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
      lcd.print("DESLPROG.1");
      lcd.setCursor(0,1);
      lcd.print("PROG.1");
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
      lcd.print("AJUSTE DATA/HORA");
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

  // ***************************** AQUECEDOR **********************************
  
  v  = (vcc*analogRead(PSC))/1023;
  rt = v*R/(vcc-v);
  pscTemp  = (beta / log(rt/rx)) - 273 + pscOS;
 
  v  = (vcc*analogRead(CLT))/1023;
  rt = v*R/(vcc-v);
  cltTemp  = (beta / log(rt/rx)) - 273 + cltOS;
    
  if (AQC_bomba == 0){  
    if(cltTemp < DeICE || cltTemp > OverHeat) // verifica as condicoes excepcionais - congelamento e sobreaquecimento
      digitalWrite(AQC, HIGH);
      else{                                   // verifica o ajuste de temperatura
        if(pscTemp < (tempSet-0.5) && difTempON < (cltTemp - pscTemp))
          digitalWrite(AQC, HIGH);
        if(pscTemp > tempSet || difTempOFF > (cltTemp - pscTemp))
          digitalWrite(AQC, LOW);
    }
  }
  else{
    if(AQC_bomba == 1)
      digitalWrite(AQC, HIGH);
    else
      digitalWrite(AQC, LOW);
  }  
  // ***************************** FILTRO **************************************
  if(FIL_bomba == 0){
    
    int tempo_a = hora*60 + minuto;
    int tempo_l = hora_prog[0]*60 + min_prog[0];
    int tempo_d = hora_prog[1]*60 + min_prog[1];
  
    switch(dsemana){
      case 1:{
        if(dsem_prog[0] == 1 || dsem_prog[0] == 0 || dsem_prog[0] == 8){
          if (tempo_a >= tempo_l && tempo_a < tempo_d)
            digitalWrite(FIL, HIGH);
            else
            digitalWrite(FIL, LOW); 
        }
       break;
      }
      case 2:{
        if(dsem_prog[0] == 2 || dsem_prog[0] == 0 || dsem_prog[0] == 9){
         if (tempo_a >= tempo_l && tempo_a < tempo_d)
            digitalWrite(FIL, HIGH);
            else
            digitalWrite(FIL, LOW); 
        }
        break;
      }
      case 3:{
        if(dsem_prog[0] == 3 || dsem_prog[0] == 0 || dsem_prog[0] == 9){
          if (tempo_a >= tempo_l && tempo_a < tempo_d)
            digitalWrite(FIL, HIGH);
            else
            digitalWrite(FIL, LOW); 
        }
        break;
      }
      case 4:{
        if(dsem_prog[0] == 4 || dsem_prog[0] == 0 || dsem_prog[0] == 9){
          if (tempo_a >= tempo_l && tempo_a < tempo_d)
            digitalWrite(FIL, HIGH);
            else
            digitalWrite(FIL, LOW); 
        }
        break;
      }
      case 5:{
        if(dsem_prog[0] == 5 || dsem_prog[0] == 0 || dsem_prog[0] == 9){
          if (tempo_a >= tempo_l && tempo_a < tempo_d)
            digitalWrite(FIL, HIGH);
            else
            digitalWrite(FIL, LOW); 
        }
        break;
      }
      case 6:{
        if(dsem_prog[0] == 6 || dsem_prog[0] == 0 || dsem_prog[0] == 9){
          if (tempo_a >= tempo_l && tempo_a < tempo_d)
            digitalWrite(FIL, HIGH);
            else
            digitalWrite(FIL, LOW); 
        }
        break;
      }
      case 7:{
        if(dsem_prog[0] == 7 || dsem_prog[0] == 0 || dsem_prog[0] == 8){
          if (tempo_a >= tempo_l && tempo_a < tempo_d)
            digitalWrite(FIL, HIGH);
            else
            digitalWrite(FIL, LOW); 
        }
        break;
      }
     }
  }
  else{
    if(FIL_bomba == 1)
      digitalWrite(FIL, HIGH);
    else
      digitalWrite(FIL, LOW);
  }  
  //************ ATUALIZA HORA E DATA ***************     
  hora    = RTC1.getHours();
  minuto  = RTC1.getMinutes();
  segundo = RTC1.getSeconds();
  dsemana = RTC1.getWeek();
  dia     = RTC1.getDay();
  mes     = RTC1.getMonth();
  ano     = RTC1.getYear();
  //if (hora+minuto+segundo == 0)
  //  RTC1.setSeconds(20);  
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
