unsigned long previousMillis = 0;

/*
  Dichiarazione variabili ambiente
*/
uint8_t RELE_UP = 8;  //RELE UP
uint8_t RELE_DOWN = 9;  //RELE DOWN
uint8_t RELE_CW = 10; //RELE rotazione sendo orario //lasciare 10 per arduino MEGA
uint8_t RELE_CCW = 11; //RELE rotazione sendo anti-orario //lasciare 11 per arduino MEGA
uint8_t SENS_POT_AZIMUT = 0; //Sensore al quale sarà collegato il centrale del potenziometro del rotore per azimut
uint8_t SENS_POT_ELEVAZ = 1; //Sensore al quale sarà collegato il centrale del potenziometro del rotore per alevazione
boolean AZIMUT_ROTAZIONE = 0;
boolean ELEVAZ_ROTAZIONE = 0;

/*-----Indice delle pagine-----*/
const uint8_t PAG_SPLASH = 0;
const uint8_t PAG_MAIN = 1;
const uint8_t PAG_AZIMUT = 2;
const uint8_t PAG_ELEVAZ = 3;
const uint8_t PAG_KEYBOARD = 4;
const uint8_t PAG_CONFIG = 5;
/*-----------------------------*/

/*--------variabili----------*/
uint32_t VAR_AZIMUT_TARGET;  // Variabile per la memorizzazione dell'azimuth finale //DEVE RIMANERE A 32
uint32_t VAR_ELEVAZ_TARGET; // Variabile per la memorizzazione dell'elevazione finale //DEVE RIMANERE A 32
uint8_t VAR_TEMP;//
uint16_t VAR_AZIMUT_CURRENT;
uint16_t VAR_ELEVAZ_CURRENT;
int t_skew = 5;
int t_max = (VAR_AZIMUT_TARGET + 5);
int t_min = (VAR_AZIMUT_TARGET - 5);
/*---------------------------*/

/*-----colori Nextion-----*/
const uint32_t GREEN = 1024;
const uint32_t RED = 63488;
const uint32_t BLACK = 0;
const uint32_t WHITE = 65535;
/*------------------------*/

/*--------timer--------*/
const long TIMER_S = 1000;
const long TIMER_M = 2000;
const long TIMER_L = 4000;
/*---------------------*/



const unsigned int DELAY_S = 20;
const unsigned int DELAY_M = 50;
const unsigned int DELAY_L = 100;
bool OVERLAP; // Variabile boolenana per condizione di overlap
char BUFFER[10] = {0};
char BUFFER_1[10] = {0};
/*-------------------------*/


/*
  Dichiarazione oggetti Nextion
*/

/*--------BUTTON--------*/
NexButton BTN_MEM1 = NexButton (PAG_AZIMUT, 20, "BTN_MEM1"); // Richiama memoria per AZIMUT
NexButton BTN_MEM2 = NexButton (PAG_AZIMUT, 21, "BTN_MEM2"); // Richiama memoria per AZIMUT
NexButton BTN_MEM3 = NexButton (PAG_AZIMUT, 22, "BTN_MEM3"); // Richiama memoria per AZIMUT
NexButton BTN_MEM4 = NexButton (PAG_AZIMUT, 23, "BTN_MEM4"); // Richiama memoria per AZIMUT
NexButton BTN_MEM5 = NexButton (PAG_AZIMUT, 24, "BTN_MEM5"); // Richiama memoria per AZIMUT
NexButton BTN_MEM6 = NexButton (PAG_AZIMUT, 25, "BTN_MEM6"); // Richiama memoria per AZIMUT
NexButton BTN_MEM7 = NexButton (PAG_AZIMUT, 26, "BTN_MEM7"); // Richiama memoria per AZIMUT
NexButton BTN_MEM0 = NexButton (PAG_AZIMUT, 27, "BTN_MEM0"); // Richiama memoria per AZIMUT
NexButton BTN_MEM_WEST = NexButton (PAG_AZIMUT, 28, "BTN_MEM_WEST"); // Richiama memoria per AZIMUT
NexButton BTN_MEM_EST = NexButton (PAG_AZIMUT, 29, "BTN_MEM_EST"); // Richiama memoria per AZIMUT
NexButton BTN_MEM_SUD = NexButton (PAG_AZIMUT, 30, "BTN_MEM_SUD"); // Richiama memoria per AZIMUT
NexButton BTN_MEM_NORD = NexButton (PAG_AZIMUT, 31, "BTN_MEM_NORD"); // Richiama memoria per AZIMUT
/*----------------------*/

/*
   TOUCH AREA
*/
NexHotspot TOU_AZIMUT_ENT = NexHotspot(PAG_AZIMUT, 38, "TOU_ENTER");
NexHotspot TOU_UP = NexHotspot(PAG_MAIN, 7, "TOU_UP"); // Pulsante
NexHotspot TOU_DOWN = NexHotspot(PAG_MAIN, 8, "TOU_DOWN");
NexHotspot TOU_CW = NexHotspot(PAG_MAIN, 9, "TOU_CW");
NexHotspot TOU_CCW = NexHotspot(PAG_MAIN, 10, "TOU_CCW");

/*
   TEXT
*/
NexText TXT_AZIMUT = NexText(PAG_MAIN, 8, "TXT_AZIMUT");
NexText TXT_ELEVAZ = NexText(PAG_MAIN, 7, "TXT_ELEVAZ");
NexText TXT_VAR_AZIMUT_TARGET = NexText(PAG_KEYBOARD, 8, "TXT_VAR_AZIMUT_TARGET");
NexText TXT_OVERLAP = NexText(PAG_MAIN, 12, "TXT_OVERLAP");

/*
   GAUGE
*/
NexGauge GAU_AZIMUT = NexGauge(PAG_MAIN, 5, "GAU_AZIMUT");  //dichiarazione oggetto gauge
NexGauge GAU_ELEVAZ = NexGauge(PAG_MAIN, 6, "GAU_ELEVAZ");  //dichiarazione oggetto gauge

/*
   VARIABLES
*/
NexVariable va2 = NexVariable(PAG_AZIMUT, 27, "va2");
NexVariable VA_MEM0 = NexVariable(PAG_AZIMUT, 16, "VA_MEM0");
NexVariable VA_MEM1 = NexVariable(PAG_AZIMUT, 9, "VA_MEM1");
NexVariable VA_MEM2 = NexVariable(PAG_AZIMUT, 10, "VA_MEM2");
NexVariable VA_MEM3 = NexVariable(PAG_AZIMUT, 11, "VA_MEM3");
NexVariable VA_MEM4 = NexVariable(PAG_AZIMUT, 12, "VA_MEM4");
NexVariable VA_MEM5 = NexVariable(PAG_AZIMUT, 13, "VA_MEM5");
NexVariable VA_MEM6 = NexVariable(PAG_AZIMUT, 14, "VA_MEM6");
NexVariable VA_MEM7 = NexVariable(PAG_AZIMUT, 15, "VA_MEM7");
NexVariable VA_MEM_NORD = NexVariable(PAG_AZIMUT, 9, "VA_MEM_NORD");
NexVariable VA_MEM_SUD = NexVariable(PAG_AZIMUT, 9, "VA_MEM_SUD");
NexVariable VA_MEM_WEST = NexVariable(PAG_AZIMUT, 9, "VA_MEM_WEST");
NexVariable VA_MEM_EST = NexVariable(PAG_AZIMUT, 9, "VA_MEM_EST");

/*
   RADIO
*/
NexRadio r0 = NexRadio(PAG_MAIN, 12, "r0");
