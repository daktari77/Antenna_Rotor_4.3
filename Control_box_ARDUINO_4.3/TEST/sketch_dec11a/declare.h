/*
   PINOUT ROTORE YAESU G650
   1  ROSA  POT +
   2  GRIGIO  POT COMMON
   3  GIALLO  POT -
   4  VERDE AVV CW
   5  MARRONE AVV CCW
   6  BIANCO COMMON
*/

//   LOCAZIONI EEPROM
int L_T = 0; //ULTIMO TARGET AZIMUT RICHIESTO
int L_A = 1; //ULTIMA POSIZIONE AZIMUT CORRENTE CONOSCIUTA
int L_E = 2; //ULTIMA POSIZIONE ELEVAZIONE CONOSCIUTA
int POT_MIN = 3; //memorizzazione pot min
int POT_MAX = 4; //memorizzazione pot max

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
uint8_t AZIMUT_ROTAZIONE; // variabile usata per il ciclo if nel loop per il sesno di rotazione, accetta valori STOP CW CCW
const int STOP = 0; //case switch 0 (stop)
const int CCW = 1;  //case switch 1 (rotazione ccw)
const int CW = 2; //case switch 2 (rotazione cw)
bool ELEVAZ_ROTAZIONE_PROGRESS = 0; // FLAG per movimento in corso si/no
bool AZIMUT_ROTAZIONE_PROGRESS = 0; // FLAG per movimento in corso si/no
/*-----------------------------*/

/*-----Indice delle pagine-----*/

const uint8_t PAG_SPLASH = 0;
const uint8_t PAG_MAIN = 1;
const uint8_t PAG_AZIMUT = 2;
const uint8_t PAG_ELEVAZ = 3;
const uint8_t PAG_KEYBOARD = 4;
const uint8_t PAG_CONFIG = 5;
const uint8_t PAG_ERROR = 6;

/*-----------------------------*/

/*--------variabili----------*/
uint32_t  VAR_AZIMUT_TARGET = 0; // Variabile per la memorizzazione dell'azimuth finale //DEVE RIMANERE A 32
uint32_t  VAR_AZIMUT_LAST_TARGET;
uint32_t  VAR_ELEVAZ_TARGET; // Variabile per la memorizzazione dell'elevazione finale //DEVE RIMANERE A 32
uint32_t  VAR_AZIMUT_CURRENT; // Variabile per la memorizzazione dell'azimuth corrente //DEVE RIMANERE A 32
uint32_t  VAR_ELEVAZ_CURRENT; // Variabile per la memorizzazione dell'elevazione corrente //DEVE RIMANERE A 32
uint8_t   VAR_AZIMUT_MIN; //Variabile appoggio per memorizzazione valore minimo potenziometro azimut minimo
uint8_t   VAR_AZIMUT_MAX; //Variabile appoggio per memorizzazione valore massimo potenziometro azimut minimo
bool      RUN_CALIBRAZIONE = 0;
uint8_t   VAR_TEMP;//

int t_skew = 5;
int t_max = (VAR_AZIMUT_TARGET + 5);
int t_min = (VAR_AZIMUT_TARGET - 5);
/*---------------------------*/

/*-----colori Nextion-----*/
const uint32_t GREEN = 1024;
const uint32_t RED = 63488;
const uint32_t BLACK = 0;
const uint32_t WHITE = 65535;
const uint32_t YELLOW = 61058;

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
char BUFFER_AZ[10] = {0};
char BUFFER_EL[10] = {0};
char BUFFER[10];
/*-------------------------*/

/*
  Dichiarazione oggetti Nextion
*/

/*--------BUTTON--------*/
NexButton BTN_MEM0 = NexButton (PAG_AZIMUT, 34, "B0"); // Richiama memoria per AZIMUT
NexButton BTN_MEM1 = NexButton (PAG_AZIMUT, 35, "B1"); // Richiama memoria per AZIMUT
NexButton BTN_MEM2 = NexButton (PAG_AZIMUT, 36, "B2"); // Richiama memoria per AZIMUT
NexButton BTN_MEM3 = NexButton (PAG_AZIMUT, 37, "B3"); // Richiama memoria per AZIMUT
NexButton BTN_MEM4 = NexButton (PAG_AZIMUT, 38, "B4"); // Richiama memoria per AZIMUT
NexButton BTN_MEM5 = NexButton (PAG_AZIMUT, 39, "B5"); // Richiama memoria per AZIMUT
NexButton BTN_MEM6 = NexButton (PAG_AZIMUT, 40, "B6"); // Richiama memoria per AZIMUT
NexButton BTN_MEM7 = NexButton (PAG_AZIMUT, 41, "B7"); // Richiama memoria per AZIMUT

/*
   TOUCH AREA
*/
NexHotspot TOU_AZIMUT_ENT = NexHotspot(PAG_AZIMUT, 33, "TOU_ENTER");
NexHotspot TOU_UP = NexHotspot(PAG_MAIN, 6, "TOU_UP"); // Pulsante
NexHotspot TOU_DOWN = NexHotspot(PAG_MAIN, 7, "TOU_DOWN");
NexHotspot TOU_CW = NexHotspot(PAG_MAIN, 8, "TOU_CW");
NexHotspot TOU_CCW = NexHotspot(PAG_MAIN, 9, "TOU_CCW");
NexHotspot TOU_MEM_WEST = NexHotspot(PAG_AZIMUT, 20, "TOU_MEM_WEST");
NexHotspot TOU_MEM_EST = NexHotspot(PAG_AZIMUT, 19, "TOU_MEM_EST");
NexHotspot TOU_MEM_NORD = NexHotspot(PAG_AZIMUT, 17, "TOU_MEM_NORD");
NexHotspot TOU_MEM_SUD = NexHotspot(PAG_AZIMUT, 18, "TOU_MEM_SUD");
/*
   TEXT
*/
NexText TXT_AZIMUT = NexText(PAG_MAIN, 8, "TXT_AZIMUT");
NexText TXT_ELEVAZ = NexText(PAG_MAIN, 7, "TXT_ELEVAZ");
NexText TXT_VAR_AZIMUT_TARGET = NexText(PAG_KEYBOARD, 8, "TXT_VAR_AZIMUT_TARGET");
NexText TXT_OVERLAP = NexText(PAG_MAIN, 12, "TXT_OVERLAP");
NexText TXT_TARGET = NexText(PAG_AZIMUT, 7, "TXT_TARGET");


/*
   GAUGE
*/
NexGauge GAU_AZIMUT = NexGauge(PAG_MAIN, 11, "GAU_AZIMUT");  //dichiarazione oggetto gauge azimut
NexGauge GAU_ELEVAZ = NexGauge(PAG_MAIN, 4, "GAU_ELEVAZ");  //dichiarazione oggetto gauge elevazione

/*
   VARIABLES
*/
NexVariable VA_TARGET = NexVariable(PAG_AZIMUT, 43, "VA_TARGET"); //variabile di appoggio per il target
NexVariable VA_MEM0 = NexVariable(PAG_AZIMUT, 16, "VA_MEM0"); //Varibile per tasto mem0
NexVariable VA_MEM1 = NexVariable(PAG_AZIMUT,  9, "VA_MEM1"); //Varibile per tasto mem1
NexVariable VA_MEM2 = NexVariable(PAG_AZIMUT, 10, "VA_MEM2"); //Varibile per tasto mem2
NexVariable VA_MEM3 = NexVariable(PAG_AZIMUT, 11, "VA_MEM3"); //Varibile per tasto mem3
NexVariable VA_MEM4 = NexVariable(PAG_AZIMUT, 12, "VA_MEM4"); //Varibile per tasto mem4
NexVariable VA_MEM5 = NexVariable(PAG_AZIMUT, 13, "VA_MEM5"); //Varibile per tasto mem5
NexVariable VA_MEM6 = NexVariable(PAG_AZIMUT, 14, "VA_MEM6"); //Varibile per tasto mem6
NexVariable VA_MEM7 = NexVariable(PAG_AZIMUT, 15, "VA_MEM7"); //Varibile per tasto mem7

/*
  NexVariable VA_MEM_NORD = NexVariable(PAG_AZIMUT, 17, "VA_MEM_NORD");
  NexVariable VA_MEM_SUD = NexVariable(PAG_AZIMUT, 18, "VA_MEM_SUD");
  NexVariable VA_MEM_EST = NexVariable(PAG_AZIMUT, 20, "VA_MEM_EST");
  NexVariable VA_MEM_WEST = NexVariable(PAG_AZIMUT, 19, "VA_MEM_WEST");
*/

