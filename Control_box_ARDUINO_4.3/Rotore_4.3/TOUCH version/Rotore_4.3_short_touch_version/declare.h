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
String AZIMUT_ROTAZIONE = "STOP"; // Array usato per il case switch, INSERIRE valori STOP CW CCW
//bool ELEVAZ_ROTAZIONE_PROGRESS = 0; // FLAG per movimento in corso si/no
//bool AZIMUT_ROTAZIONE_PROGRESS = 0; // FLAG per movimento in corso si/no
/*-----------------------------*/

/*-----Indice delle pagine-----*/

const uint8_t PAG_SPLASH = 0;
const uint8_t PAG_MAIN = 1;
const uint8_t PAG_AZIMUT = 2;
const uint8_t PAG_CONFIG = 3;
//  const uint8_t PAG_ERROR = 4;

/*-----------------------------*/

/*--------variabili----------*/
uint32_t  VAR_AZIMUT_TARGET = 0; // Variabile per la memorizzazione dell'azimuth finale //DEVE RIMANERE A 32
uint32_t  VAR_AZIMUT_LAST_TARGET;
uint32_t  VAR_ELEVAZ_TARGET; // Variabile per la memorizzazione dell'elevazione finale //DEVE RIMANERE A 32
uint32_t  VAR_AZIMUT_CURRENT; // Variabile per la memorizzazione dell'azimuth corrente //DEVE RIMANERE A 32
uint32_t  VAR_ELEVAZ_CURRENT; // Variabile per la memorizzazione dell'elevazione corrente //DEVE RIMANERE A 32
uint8_t   VAR_AZIMUT_MIN; //Variabile appoggio per memorizzazione valore minimo potenziometro azimut minimo
uint8_t   VAR_AZIMUT_MAX; //Variabile appoggio per memorizzazione valore massimo potenziometro azimut minimo
//uint8_t   VAR_TEMP;//

int t_skew = 5;
int t_max = (VAR_AZIMUT_TARGET + 5);
int t_min = (VAR_AZIMUT_TARGET - 5);
/*---------------------------*/

/*-----colori Nextion-----*/
const uint32_t NORMAL = 62819;
const uint32_t OVERLAP = 63488;
const uint32_t BLACK = 0;
const uint32_t WHITE = 65535;

/*------------------------*/

/*--------timer--------*/
const long TIMER_S = 1000;
const long TIMER_M = 2000;
const long TIMER_L = 4000;
const unsigned int DELAY_S = 20;
const unsigned int DELAY_M = 50;
const unsigned int DELAY_L = 100;
/*---------------------*/


//bool OVERLAP; // Variabile boolenana per condizione di overlap
char BUFFER_AZ[10] = {0};
char BUFFER_EL[10] = {0};
char BUFFER[5] = {0};
int AZ_MIN;
int AZ_MAX;
int EL_MIN;
int EL_MAX;
/*-------------------------*/

/*
  Dichiarazione oggetti Nextion
*/

/*
   --------------------------------PAGES-----------------------------------------
*/

//NexPage PAG_SPLASH = NexPage(0, 0, "PAG_SPLASH");
//NexPage PAG_MAIN = NexPage(1, 0, "PAG_MAI");
//NexPage PAG_AZIMUT = NexPage(2, 0, "PAG_AZIMUT");
//NexPage PAG_CONFIG = NexPage(3, 0, "PAG_CONFIG");
NexPage PAG_ERROR = NexPage(4, 0, "PAG_ERROR");

//---------------------------------BUTTON----------------------------------------


NexButton BTN_MEM0 = NexButton (PAG_AZIMUT, 11, "BTN_MEM0"); // Richiama memoria per AZIMUT
NexButton BTN_MEM1 = NexButton (PAG_AZIMUT, 33, "BTN_MEM1"); // Richiama memoria per AZIMUT
NexButton BTN_MEM2 = NexButton (PAG_AZIMUT, 12, "BTN_MEM2"); // Richiama memoria per AZIMUT
NexButton BTN_MEM3 = NexButton (PAG_AZIMUT, 34, "BTN_MEM3"); // Richiama memoria per AZIMUT
NexButton BTN_MEM4 = NexButton (PAG_AZIMUT, 13, "BTN_MEM4"); // Richiama memoria per AZIMUT
NexButton BTN_MEM5 = NexButton (PAG_AZIMUT, 35, "BTN_MEM5"); // Richiama memoria per AZIMUT
NexButton BTN_MEM6 = NexButton (PAG_AZIMUT, 14, "BTN_MEM6"); // Richiama memoria per AZIMUT
NexButton BTN_MEM7 = NexButton (PAG_AZIMUT, 36, "BTN_MEM7"); // Richiama memoria per AZIMUT
NexButton BTN_AZIMUT_ENT = NexButton(PAG_AZIMUT, 37, "BTN_AZIMUT_ENT");

/*
   TOUCH AREA
*/
NexHotspot TOU_UP = NexHotspot(PAG_MAIN, 6, "TOU_UP"); // Pulsante
NexHotspot TOU_DOWN = NexHotspot(PAG_MAIN, 7, "TOU_DOWN");
NexHotspot TOU_CW = NexHotspot(PAG_MAIN, 8, "TOU_CW");
NexHotspot TOU_CCW = NexHotspot(PAG_MAIN, 9, "TOU_CCW");
NexHotspot TOU_MEM_WEST = NexHotspot(PAG_AZIMUT, 9, "TOU_MEM_WEST");
NexHotspot TOU_MEM_EST = NexHotspot(PAG_AZIMUT, 8, "TOU_MEM_EST");
NexHotspot TOU_MEM_NORD = NexHotspot(PAG_AZIMUT, 6, "TOU_MEM_NORD");
NexHotspot TOU_MEM_SUD = NexHotspot(PAG_AZIMUT, 7, "TOU_MEM_SUD");
/*
   TEXT
*/
NexText TXT_AZIMUT = NexText(PAG_MAIN, 5, "TXT_AZIMUT");
NexText TXT_ELEVAZ = NexText(PAG_MAIN, 4, "TXT_ELEVAZ");
NexText TXT_TARGET = NexText(PAG_AZIMUT, 7, "TXT_TARGET");


/*
   GAUGE
*/
NexGauge GAU_AZIMUT = NexGauge(PAG_MAIN, 10, "GAU_AZIMUT");  //dichiarazione oggetto gauge azimut
NexGauge GAU_ELEVAZ = NexGauge(PAG_MAIN, 3, "GAU_ELEVAZ");  //dichiarazione oggetto gauge elevazione

/*
   VARIABLES
*/
NexVariable VA_TARGET_INT = NexVariable(PAG_AZIMUT, 25, "VA_TARGET_INT"); //variabile di appoggio per il target
NexVariable VA_TARGET = NexVariable(PAG_AZIMUT, 24, "VA_TARGET"); //variabile di appoggio per il target

/*
    CHECK BOX
*/
