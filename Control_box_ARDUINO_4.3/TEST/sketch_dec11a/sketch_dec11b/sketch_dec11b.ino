/*
   CONTROL BOX arduino based
   Nextion Display 4.3"
*/

#include <Nextion.h>
#include <EEPROM.h>

/*
   PINOUT ROTORE YAESU G650
   1  ROSA  POT +
   2  GRIGIO  POT COMMON
   3  GIALLO  POT -
   4  VERDE AVV CW
   5  MARRONE AVV CCW
   6  BIANCO COMMON
*/

//  LOCAZIONI EEPROM
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
uint8_t AZIMUT_ROTAZIONE; // Array usato per il case switch, accetta valori STOP CW CCW
bool ELEVAZ_ROTAZIONE_PROGRESS = 0; // FLAG per movimento in corso si/no
bool AZIMUT_ROTAZIONE_PROGRESS = 0; // FLAG per movimento in corso si/no
/*-----------------------------*/

/*-----Indice delle pagine-----*/

const uint8_t PAG_SPLASH = 0;
const uint8_t PAG_MAIN = 1;
const uint8_t PAG_AZIMUT = 2;
const uint8_t PAG_KEYBOARD = 3;
const uint8_t PAG_CONFIG = 4;
const uint8_t PAG_ERROR = 5;
const uint8_t PAG_ROTARY = 6;

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
NexButton BTN_MEM0 = NexButton (PAG_AZIMUT, 19, "B0"); // Richiama memoria per AZIMUT
NexButton BTN_MEM1 = NexButton (PAG_AZIMUT, 20, "B1"); // Richiama memoria per AZIMUT
NexButton BTN_MEM2 = NexButton (PAG_AZIMUT, 21, "B2"); // Richiama memoria per AZIMUT
NexButton BTN_MEM3 = NexButton (PAG_AZIMUT, 22, "B3"); // Richiama memoria per AZIMUT
/*NexButton BTN_MEM4 = NexButton (PAG_AZIMUT, 38, "B4"); // Richiama memoria per AZIMUT
  NexButton BTN_MEM5 = NexButton (PAG_AZIMUT, 39, "B5"); // Richiama memoria per AZIMUT
  NexButton BTN_MEM6 = NexButton (PAG_AZIMUT, 40, "B6"); // Richiama memoria per AZIMUT
*/NexButton BTN_MEM7 = NexButton (PAG_AZIMUT, 41, "B7"); // Richiama memoria per AZIMUT
//NexButton BTN_ROT_ENT = NexButton(PAG_ROTARY, 10, "b6"); //rotary

/*
   TOUCH AREA
*/
NexHotspot TOU_AZIMUT_ENT = NexHotspot(PAG_AZIMUT, 36, "TOU_ENTER");
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
NexVariable VA_TARGET_INT = NexVariable(PAG_AZIMUT, 44, "VA_TARGET_INT"); //variabile di appoggio per il target
NexVariable VA_TARGET = NexVariable(PAG_AZIMUT, 43, "VA_TARGET"); //variabile di appoggio per il target
/*NexVariable VA_MEM0 = NexVariable(PAG_AZIMUT, 16, "VA_MEM0"); //Varibile per tasto mem0
  NexVariable VA_MEM1 = NexVariable(PAG_AZIMUT,  9, "VA_MEM1"); //Varibile per tasto mem1
  NexVariable VA_MEM2 = NexVariable(PAG_AZIMUT, 10, "VA_MEM2"); //Varibile per tasto mem2
  NexVariable VA_MEM3 = NexVariable(PAG_AZIMUT, 11, "VA_MEM3"); //Varibile per tasto mem3
  NexVariable VA_MEM4 = NexVariable(PAG_AZIMUT, 12, "VA_MEM4"); //Varibile per tasto mem4
  NexVariable VA_MEM5 = NexVariable(PAG_AZIMUT, 13, "VA_MEM5"); //Varibile per tasto mem5
  NexVariable VA_MEM6 = NexVariable(PAG_AZIMUT, 14, "VA_MEM6"); //Varibile per tasto mem6
  NexVariable VA_MEM7 = NexVariable(PAG_AZIMUT, 15, "VA_MEM7"); //Varibile per tasto mem7
*/NexVariable va0 = NexVariable(PAG_ROTARY, 12, "va0");

/*
   Register a button object to the touch event list.
*/
NexTouch *nex_listen_list[] =
{
  &TOU_CCW, //evento pressione touch ccw
  &TOU_CW,  //evento pressione touch cw
  &TOU_UP,  //evento pressione touch up
  &TOU_DOWN,  //evento pressione touch DOWN
  &TOU_AZIMUT_ENT,
  // &BTN_MEM0,
  // &BTN_MEM1,
  // &BTN_MEM2,
  // &BTN_MEM3,
  // &BTN_MEM4,
  // &BTN_MEM5,
  // &BTN_MEM6,
  // &BTN_MEM7,
  &TOU_MEM_WEST,
  &TOU_MEM_EST,
  &TOU_MEM_SUD,
  &TOU_MEM_NORD,
  // &BTN_ROT_ENT,
  NULL
};

/*
  Callback eventi oggetti Nextion display
*/

/*
   Memory recall
*/
/*
  void BTN_MEM0PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM0PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM0.getValue(&VAR_AZIMUT_TARGET);
  dbSerialPrint("TARGET da VA_MEM0 = ");
  dbSerialPrintln(VAR_AZIMUT_TARGET);
  EEPROM.update(0, VAR_AZIMUT_TARGET / 4);
  //ser_print_azimut(); //Serial print posizione corrente e target
  rotazione();
  }

  void BTN_MEM1PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM1PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM1.getValue(&VAR_AZIMUT_TARGET);
  rotazione();
  }

  void BTN_MEM2PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM2PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM2.getValue(&VAR_AZIMUT_TARGET);
  rotazione();
  }

  void BTN_MEM3PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM3PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM3.getValue(&VAR_AZIMUT_TARGET);
  rotazione();

  }
  void BTN_MEM4PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM4PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM4.getValue(&VAR_AZIMUT_TARGET);
  rotazione();

  }
  void BTN_MEM5PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM5PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM5.getValue(&VAR_AZIMUT_TARGET);
  rotazione();

  }
  void BTN_MEM6PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM6PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM6.getValue(&VAR_AZIMUT_TARGET);
  rotazione();

  }
  void BTN_MEM7PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM7PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM7.getValue(&VAR_AZIMUT_TARGET);
  rotazione();

  }
*/

void TOU_MEM_NORDPopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM_NORDPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VAR_AZIMUT_TARGET = 0;
  EEPROM.update(0, VAR_AZIMUT_TARGET / 4);
  ser_print_azimut();
  rotazione();
}
void TOU_MEM_ESTPopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM_ESTPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VAR_AZIMUT_TARGET = 90;
  EEPROM.update(0, VAR_AZIMUT_TARGET / 4);
  ser_print_azimut();
  rotazione();
}
void TOU_MEM_SUDPopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM_SUDPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VAR_AZIMUT_TARGET = 180;
  EEPROM.update(0, VAR_AZIMUT_TARGET / 4);
  ser_print_azimut();
  rotazione();
}
void TOU_MEM_WESTPopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM_WESTPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VAR_AZIMUT_TARGET = 270;
  EEPROM.update(0, VAR_AZIMUT_TARGET / 4);
  ser_print_azimut();
  rotazione();
}

void TOU_AZIMUT_ENTPopCallback(void *ptr) {
  uint32_t a;
  dbSerialPrintln("TOU_AZIMUT_ENTPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_TARGET.getText(BUFFER, 3);
  dbSerialPrint("BUFFER = ");
  dbSerialPrintln(BUFFER);

  VA_TARGET_INT.getValue(&a);
  dbSerialPrint("a = ");
  dbSerialPrintln(a);

  VAR_AZIMUT_TARGET = atoi(BUFFER);
  dbSerialPrint("TARGET da atoi BUFFER = ");
  dbSerialPrintln(VAR_AZIMUT_TARGET);
  //EEPROM.update(0, VAR_AZIMUT_TARGET / 4);
  rotazione();
}

void TOU_UPPushCallback(void *ptr) {   //Funzione callback per l'evento PUSH del button TOU_UP
  dbSerialPrintln("TOU_UPPushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(DELAY_S);
  digitalWrite( RELE_UP, HIGH );
}
void TOU_UPPopCallback(void *ptr) {   //Funzione callback per l'evento POP del button TOU_UP
  dbSerialPrintln("TOU_UPPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(DELAY_S);
  digitalWrite( RELE_UP, LOW );
}

void TOU_DOWNPushCallback(void *ptr) {  //Funzione callback per l'evento PUSH del button TOU_DOWN
  dbSerialPrintln("TOU_DOWNPushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(DELAY_S);
  //digitalWrite( RELE_UP, LOW );
  digitalWrite( RELE_DOWN, HIGH );
}

void TOU_CCWPushCallback(void *ptr) { //Funzione callback per l'evento PUSH del button TOU_CCW
  dbSerialPrintln("TOU_CCWPushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(DELAY_S);
  //digitalWrite( RELE_CW, LOW );
  digitalWrite( RELE_CCW, HIGH );
}

void TOU_CWPushCallback(void *ptr) {  //Funzione callback per l'evento PUSH del button TOU_CW
  dbSerialPrintln("TOU_CWPushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(DELAY_S);
  //digitalWrite( RELE_CCW, LOW );
  digitalWrite( RELE_CW, HIGH );
}



void TOU_CWPopCallback(void *ptr) { //Funzione callback per l'evento POP del button TOU_CW
  dbSerialPrintln("TOU_CWPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(DELAY_S);
  //digitalWrite( RELE_CCW, LOW );
  digitalWrite( RELE_CW, LOW );
}

void TOU_CCWPopCallback(void *ptr)  { //Funzione callback per l'evento POP del button TOU_CCW
  dbSerialPrintln("TOU_CCWPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(DELAY_S);
  digitalWrite( RELE_CCW, LOW );
  //digitalWrite( RELE_CW, LOW );
}

void TOU_DOWNPopCallback(void *ptr) { //Funzione callback per l'evento POP del button TOU_DOWN
  dbSerialPrintln("TOU_DOWNPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(DELAY_S);
  //digitalWrite( RELE_UP, LOW );
  digitalWrite( RELE_DOWN, LOW );
}

void ser_print_azimut() { //Serial print posizione corrente e target
  dbSerialPrint("TARGET = ");
  dbSerialPrintln(VAR_AZIMUT_TARGET);
  dbSerialPrint("LAST TARGET = ");
  dbSerialPrintln(VAR_AZIMUT_LAST_TARGET );
  dbSerialPrint("CURRENT= ");
  dbSerialPrintln(VAR_AZIMUT_CURRENT);
  dbSerialPrint("DIFF(function)= ");
  int AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
  int AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
  int EL_MAX = max(VAR_ELEVAZ_CURRENT , VAR_ELEVAZ_TARGET);
  int EL_MIN = min(VAR_ELEVAZ_CURRENT , VAR_ELEVAZ_TARGET);
  dbSerialPrintln(AZ_MAX - AZ_MIN);
}

void rotazione() {
  if (VAR_AZIMUT_TARGET <= 360) {
    //if (0 <= VAR_AZIMUT_CURRENT && VAR_AZIMUT_CURRENT < 180) {
    if (VAR_AZIMUT_CURRENT < VAR_AZIMUT_TARGET) {
      dbSerialPrintln("Rotazione CCW in corso ");
      AZIMUT_ROTAZIONE = "CCW";
    }
    else {
      dbSerialPrintln("Rotazione CW in corso ");
      AZIMUT_ROTAZIONE = "CW";
    }
  }
  //}
  /*
    if (180 <= VAR_AZIMUT_CURRENT && VAR_AZIMUT_CURRENT < 270) {
    if (90 <= VAR_AZIMUT_TARGET && VAR_AZIMUT_TARGET < 360) {
      if (VAR_AZIMUT_CURRENT < VAR_AZIMUT_TARGET) {
        dbSerialPrintln("Rotazione CCW in corso ");
        AZIMUT_ROTAZIONE = CCW;
      }
      else {
        dbSerialPrintln("Rotazione CW in corso ");
        AZIMUT_ROTAZIONE = CW;
      }
    }
    else if ((VAR_AZIMUT_CURRENT - VAR_AZIMUT_TARGET) < 180) {
      dbSerialPrintln("Rotazione CCW in corso ");
      AZIMUT_ROTAZIONE = CCW;
    }
    else {
      VAR_AZIMUT_TARGET = VAR_AZIMUT_TARGET + 360;
      dbSerialPrintln("Rotazione CW in corso ");
      AZIMUT_ROTAZIONE = CW;
    }
    if ((270 <= VAR_AZIMUT_CURRENT && VAR_AZIMUT_CURRENT < 450) && (270 <= VAR_AZIMUT_TARGET && VAR_AZIMUT_TARGET < 450)) {
      fif (VAR_AZIMUT_CURRENT < VAR_AZIMUT_TARGET) {
        dbSerialPrintln("Rotazione CCW in corso ");
        AZIMUT_ROTAZIONE = CCW;
      }
      else {
        dbSerialPrintln("Rotazione CW in corso ");
        AZIMUT_ROTAZIONE = CW;
      }
    }
    } */
}  //Chiusura void

void elevaz_current() {
  VAR_ELEVAZ_CURRENT = map(analogRead(SENS_POT_ELEVAZ), 0, 1023, 0, 180); //mappo il valore letto su A1
  itoa(VAR_ELEVAZ_CURRENT, BUFFER_EL, 10);
  GAU_ELEVAZ.setValue(VAR_ELEVAZ_CURRENT );
  TXT_ELEVAZ.setText(BUFFER_EL);
}

void azimut_current() {
  /*
     Set puntatore OK
     Set colore puntatore FAIL
     set TXT_OVERLAP OK
     set TXT_AZIMUT txt OK
     set TXT_AZIMUT color OK
  */

  VAR_AZIMUT_CURRENT = map(analogRead(SENS_POT_AZIMUT), 0, 1023, 0, 450); //mappo il valore letto su A0
  itoa(VAR_AZIMUT_CURRENT, BUFFER_AZ, 10);
  if (VAR_AZIMUT_CURRENT >= 0 && VAR_AZIMUT_CURRENT <= 270) {
    ser_print_azimut();
    GAU_AZIMUT.setValue(VAR_AZIMUT_CURRENT + 90 );
    GAU_AZIMUT.Set_background_color_bco(GREEN);
    TXT_AZIMUT.setText(BUFFER_AZ);
    TXT_AZIMUT.Set_font_color_pco(GREEN);

    OVERLAP = 0;
  }
  else
  {
    GAU_AZIMUT.setValue(VAR_AZIMUT_CURRENT - 270 );
    TXT_AZIMUT.setText(BUFFER_AZ);
    if (VAR_AZIMUT_CURRENT > 360 && VAR_AZIMUT_CURRENT <= 450) {
      ser_print_azimut();
      GAU_AZIMUT.Set_background_color_bco(RED);
      TXT_AZIMUT.Set_font_color_pco(RED);
      OVERLAP = 1;
    }
    else
    {
      GAU_AZIMUT.Set_background_color_bco(GREEN);
      TXT_OVERLAP.Set_font_color_pco(GREEN);
      TXT_AZIMUT.Set_font_color_pco(GREEN);
      OVERLAP = 0;
    }
  }
}

void rotazione_CW() {
  delay(10);
  digitalWrite( RELE_CW, HIGH);
}

void rotazione_CCW() {
  delay(10);
  digitalWrite( RELE_CCW, HIGH);
}

void rotazione_UP() {
  delay(10);
  digitalWrite( RELE_UP, HIGH);
}

void rotazione_DOWN() {
  delay(10);
  digitalWrite( RELE_DOWN, HIGH);
}
void elevaz_stop()  {
  digitalWrite( RELE_UP, LOW);
  digitalWrite( RELE_DOWN, LOW);
}

void azimut_stop()  {
  digitalWrite( RELE_CCW, LOW);
  digitalWrite( RELE_CW, LOW);
}




void setup(void)
{
  /* Set the baudrate which is for debug and communicate with Nextion screen. */
  //nexSerial.begin(115200); // inizializzo la velicità della serial a 115200
  //dbSerialBegin(115200);  // inizializzo la velicità della serial a 115200
  VAR_AZIMUT_LAST_TARGET = ((EEPROM.read(0) * 4)); // RECUPERA INFO SU ULTIMO TARGET RICHIESTO
  //ciao
  for (int X = 8; X <= 11; X++) {
    pinMode( X, OUTPUT );
    digitalWrite( X, LOW );
  }
  nexInit();
  /* Register the pop and push event callback function of the current button component. */
  TOU_CCW.attachPop(TOU_CCWPopCallback, &TOU_CCW);
  TOU_CCW.attachPush(TOU_CCWPushCallback, &TOU_CCW);
  TOU_CW.attachPop(TOU_CWPopCallback, &TOU_CW);
  TOU_CW.attachPush(TOU_CWPushCallback, &TOU_CW);
  TOU_UP.attachPop(TOU_UPPopCallback, &TOU_UP);
  TOU_UP.attachPush(TOU_UPPushCallback, &TOU_UP);
  TOU_DOWN.attachPop(TOU_DOWNPopCallback, &TOU_DOWN);
  TOU_DOWN.attachPush(TOU_DOWNPushCallback, &TOU_DOWN);
  TOU_AZIMUT_ENT.attachPop(TOU_AZIMUT_ENTPopCallback, &TOU_AZIMUT_ENT);

  // BTN_MEM1.attachPop(BTN_MEM1PopCallback, &BTN_MEM1);
  // BTN_MEM2.attachPop(BTN_MEM2PopCallback, &BTN_MEM2);
  // BTN_MEM3.attachPop(BTN_MEM3PopCallback, &BTN_MEM3);
  // BTN_MEM4.attachPop(BTN_MEM4PopCallback, &BTN_MEM4);
  // BTN_MEM5.attachPop(BTN_MEM5PopCallback, &BTN_MEM5);
  // BTN_MEM6.attachPop(BTN_MEM6PopCallback, &BTN_MEM6);
  // BTN_MEM7.attachPop(BTN_MEM7PopCallback, &BTN_MEM7);
  // BTN_MEM0.attachPop(BTN_MEM0PopCallback, &BTN_MEM0);
  TOU_MEM_WEST.attachPop(TOU_MEM_WESTPopCallback, &TOU_MEM_WEST);
  TOU_MEM_EST.attachPop(TOU_MEM_ESTPopCallback, &TOU_MEM_EST);
  TOU_MEM_SUD.attachPop(TOU_MEM_SUDPopCallback, &TOU_MEM_SUD);
  TOU_MEM_NORD.attachPop(TOU_MEM_NORDPopCallback, &TOU_MEM_NORD);
  //  BTN_ROT_ENT.attachPop(BTN_ROT_ENTPopCallback, &BTN_ROT_ENT); //test rotary insert

  dbSerialPrintln("setup done");

  delay(2500);

  int x = 15;
  for (int a = 0; a >= -1; a = a + x ) {   //DEMO gauge
    int b = (a * 2);
    GAU_ELEVAZ.setValue( a );
    itoa(a, BUFFER_EL, 10);
    TXT_ELEVAZ.setText( BUFFER_EL );
    GAU_AZIMUT.setValue( b );
    itoa(b, BUFFER_AZ, 10);
    TXT_AZIMUT.setText( BUFFER_AZ );
    if (a == 180) x = -x;
    //delay(1000);
  }

  azimut_current();
  elevaz_current();
}

void loop(void) {
  int X = map(analogRead(SENS_POT_AZIMUT), 0, 1023, 0, 450);
  int Y = map(analogRead(SENS_POT_ELEVAZ), 0, 1023, 0, 180);
  int AZ_MAX;
  int AZ_MIN;
  int AZ_CURR_DIFF = (max(X, VAR_AZIMUT_CURRENT) - min(X, VAR_AZIMUT_CURRENT)); //CALCOLO LA DIFFERENZA TRA VAR_AZIMUT_CURRENT E VALORE ATTUALE
  int EL_CURR_DIFF = (max(X, VAR_ELEVAZ_CURRENT) - min(X, VAR_ELEVAZ_CURRENT)); //CALCOLO LA DIFFERENZA TRA VAR_ELEVAZT_CURRENT E VALORE ATTUALE
  unsigned long currentMillis = millis();
  nexLoop(nex_listen_list);

  if ((AZIMUT_ROTAZIONE == "CCW")) {
    rotazione_CCW();
    AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);

    while ( AZ_MAX - AZ_MIN > 1) {
      azimut_current(); // invia valori al display e Leggere il valore del potenziometro
      AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
      AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    }
    azimut_stop();
    AZIMUT_ROTAZIONE = "STOP";
  }
  else if ((AZIMUT_ROTAZIONE  == "CW")) {
    rotazione_CW();
    AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    while ( AZ_MAX - AZ_MIN > 1) {
      azimut_current();
      AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
      AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    }
    azimut_stop();
    AZIMUT_ROTAZIONE = "STOP";
  }


  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    if (AZ_CURR_DIFF > 2)  //Aggiorno valore display solo se differenza maggiore di 2
    {
      azimut_current(); //Calcolo e visualizzazione azimut corrente su display
      EEPROM.update(L_A, VAR_AZIMUT_CURRENT / 4);
    }
    if (EL_CURR_DIFF > 2)  //Aggiorno valore display solo se differenza maggiore di 2
    {
      elevaz_current(); //Calcolo e visualizzazione ELEVAZ corrente su display
      EEPROM.update(L_E, VAR_ELEVAZ_CURRENT); // NON è NECESSARIO DIVIDERE IL VALORE PER 4 POICHE' ELEVAZ MAX = 180 (< 255)
    }
  }

  /*if (RUN_CALIBRAZIONE == 1) {
    calibrazione();
    }*/
}
