/*
  Dichiarazione variabili ambiente
*/
uint8_t RELE_UP = 8;  //RELE UP
uint8_t RELE_DOWN = 9;  //RELE DOWN
uint8_t RELE_CCW = 10; //
uint8_t RELE_CW = 11;
uint8_t SENS_POT_AZIMUT = 0; //Sensore al quale sarà collegato il centrale del potenziometro del rotore
uint8_t SENS_POT_ELEVAZ = 1;

const unsigned int PAG_SPLASH = 0;
const unsigned int PAG_MAIN = 1;
const unsigned int PAG_AZIMUT = 2;
const unsigned int PAG_MEM = 3;
const unsigned int PAG_CONFIG = 4;
const unsigned int PAG_ELEVAZ = 5;

unsigned int VAR_AZIMUT_TARGET;  // Variabile per la memorizzazione dell'azimuth finale
unsigned int VAR_ELEVAZ_TARGET; // Variabile per la memorizzazione dell'elevazione finale
int VAR_TEMT;//
uint16_t VAR_AZIMUT_CURRENT;
uint16_t VAR_ELEVAZ_CURRENT;

const uint16_t GREEN = 2016;
const uint16_t RED = 63488;
const uint8_t BLACK = 0;
const uint16_t WHITE = 65535;

const long TIMER_S = 1000;
const long TIMER_M = 2000;
const long TIMER_L = 4000;
unsigned long previousMillis = 0;

const unsigned int DELAY_S = 20;
const unsigned int DELAY_M = 50;
const unsigned int DELAY_L = 100;
bool OVERLAP; // Variabile boolenana per condizione di overlap
char BUFFER[100] = {0};
char BUFFER_TMP[10] = {0};
/*-------------------------*/


/*
  Dichiarazione variabili Nextion
*/

/*
   BUTTON
*/

NexButton BTN_MEM1 = NexButton (PAG_AZIMUT, 20, "BTN_MEM1"); // Richiama memoria per AZIMUT
NexButton BTN_MEM2 = NexButton (PAG_AZIMUT, 21, "BTN_MEM2"); // Richiama memoria per AZIMUT
NexButton BTN_MEM3 = NexButton (PAG_AZIMUT, 22, "BTN_MEM3"); // Richiama memoria per AZIMUT
NexButton BTN_MEM4 = NexButton (PAG_AZIMUT, 23, "BTN_MEM4"); // Richiama memoria per AZIMUT
NexButton BTN_MEM5 = NexButton (PAG_AZIMUT, 24, "BTN_MEM5"); // Richiama memoria per AZIMUT
NexButton BTN_MEM6 = NexButton (PAG_AZIMUT, 25, "BTN_MEM6"); // Richiama memoria per AZIMUT
NexButton BTN_MEM7 = NexButton (PAG_AZIMUT, 26, "BTN_MEM7"); // Richiama memoria per AZIMUT
NexButton BTN_MEM8 = NexButton (PAG_AZIMUT, 27, "BTN_MEM8"); // Richiama memoria per AZIMUT
NexButton BTN_MEM9 = NexButton (PAG_AZIMUT, 28, "BTN_MEM9"); // Richiama memoria per AZIMUT
NexButton BTN_MEM10 = NexButton (PAG_AZIMUT, 29, "BTN_MEM10"); // Richiama memoria per AZIMUT
NexButton BTN_MEM11 = NexButton (PAG_AZIMUT, 30, "BTN_MEM11"); // Richiama memoria per AZIMUT
NexButton BTN_MEM12 = NexButton (PAG_AZIMUT, 31, "BTN_MEM12"); // Richiama memoria per AZIMUT
/*-------------------------*/

/*
   TOUCH AREA
*/
NexHotspot TOU_AZIMUT_ENT = NexHotspot(PAG_AZIMUT, 3, "BTN_ENTER");
NexHotspot TOU_UP = NexHotspot(PAG_MAIN, 8, "TOU_UP"); // Pulsante
NexHotspot TOU_DOWN = NexHotspot(PAG_MAIN, 9, "TOU_DOWN");
NexHotspot TOU_CW = NexHotspot(PAG_MAIN, 10, "TOU_CW");
NexHotspot TOU_CCW = NexHotspot(PAG_MAIN, 11, "TOU_CCW");
/*-------------------------*/

/*
   TEXT
*/
NexText TXT_AZIMUT = NexText(PAG_MAIN, 8, "TXT_AZIMUT");
NexText TXT_ELEVAZ = NexText(PAG_MAIN, 7, "TXT_ELEVAZ");
NexText TXT_VAR_AZIMUT_TARGET = NexText(PAG_MEM, 8, "TXT_VAR_AZIMUT_TARGET");
NexText TXT_OVERLAP = NexText(PAG_MAIN, 4, "TXT_OVERLAP");
/*-------------------------*/

/*
   GAUGE
*/
NexGauge GAU_AZIMUT = NexGauge(PAG_MAIN, 5, "GAU_AZIMUT");	//dichiarazione oggetto gauge
NexGauge GAU_ELEVAZ = NexGauge(PAG_MAIN, 6, "GAU_ELEVAZ");  //dichiarazione oggetto gauge
/*-------------------------*/
