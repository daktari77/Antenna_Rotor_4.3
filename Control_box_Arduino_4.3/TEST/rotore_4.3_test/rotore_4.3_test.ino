/*
   CONTROL BOX arduino based
   Nextion Display 4.3"
*/

#include <Nextion.h>

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
/*
   Indice delle pagine
*/
const uint8_t PAG_SPLASH = 0;
const uint8_t PAG_MAIN = 1;
const uint8_t PAG_AZIMUT = 2;
const uint8_t PAG_ELEVAZ = 3;
const uint8_t PAG_KEYBOARD = 4;
const uint8_t PAG_CONFIG = 5;


uint32_t VAR_AZIMUT_TARGET;  // Variabile per la memorizzazione dell'azimuth finale //DEVE RIMANERE A 32
uint32_t VAR_ELEVAZ_TARGET; // Variabile per la memorizzazione dell'elevazione finale //DEVE RIMANERE A 32
uint8_t VAR_TEMP;//
uint16_t VAR_AZIMUT_CURRENT;
uint16_t VAR_ELEVAZ_CURRENT;

const uint32_t GREEN = 1024;
const uint32_t RED = 63488;
const uint32_t BLACK = 0;
const uint32_t WHITE = 65535;

const long TIMER_S = 1000;
const long TIMER_M = 2000;
const long TIMER_L = 4000;




const unsigned int DELAY_S = 20;
const unsigned int DELAY_M = 50;
const unsigned int DELAY_L = 100;
bool OVERLAP; // Variabile boolenana per condizione di overlap
char BUFFER[100] = {0};
char BUFFER_1[10] = {0};
/*-------------------------*/


/*
  Dichiarazione oggetti Nextion
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
/*
   RADIO
*/
NexRadio r0 = NexRadio(PAG_MAIN, 12, "r0");

/*
   Register a button object to the touch event list.
*/
NexTouch *nex_listen_list[] =
{
  &TOU_CCW,
  &TOU_CW,
  &TOU_UP,
  &TOU_DOWN,
  &TOU_AZIMUT_ENT,
  &BTN_MEM1,
  &BTN_MEM2,
  &BTN_MEM3,
  &BTN_MEM4,
  &BTN_MEM5,
  &BTN_MEM6,
  &BTN_MEM7,
  &BTN_MEM8,
  &BTN_MEM9,
  &BTN_MEM10,
  &BTN_MEM11,
  &BTN_MEM12,
  NULL
};

/*
  Callback eventi oggetti Nextion display
*/

/*
   Memory recall
*/

void BTN_MEM1PopCallback(void *ptr) {

}
void BTN_MEM2PopCallback(void *ptr) {

}
void BTN_MEM3PopCallback(void *ptr) {

}
void BTN_MEM4PopCallback(void *ptr) {

}
void BTN_MEM5PopCallback(void *ptr) {

}
void BTN_MEM6PopCallback(void *ptr) {

}
void BTN_MEM7PopCallback(void *ptr) {

}
void BTN_MEM8PopCallback(void *ptr) {

}
void BTN_MEM9PopCallback(void *ptr) {

}
void BTN_MEM10PopCallback(void *ptr) {

}
void BTN_MEM11PopCallback(void *ptr) {

}
void BTN_MEM12PopCallback(void *ptr) {

}

void TOU_AZIMUT_ENTPopCAllback(void *ptr) {
  dbSerialPrintln("TOU_AZIMUT_ENTPopCAllback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  va2.getValue(&VAR_AZIMUT_TARGET);
  AZIMUT_ROTAZIONE = 1;
}

void TOU_UPPushCallback(void *ptr) {   //Funzione callback per l'evento PUSH del button TOU_UP
  dbSerialPrintln("TOU_UPPushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(DELAY_S);
  //digitalWrite( RELE_DOWN, LOW );
  digitalWrite( RELE_UP, HIGH );
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

void TOU_UPPopCallback(void *ptr) {   //Funzione callback per l'evento POP del button TOU_UP
  dbSerialPrintln("TOU_UPPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(DELAY_S);
  digitalWrite( RELE_UP, LOW );
  //digitalWrite( RELE_DOWN, LOW );
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

int azimut_current() {
  /*
     Set puntatore OK
     Set colore puntatore FAIL
     set TXT_OVERLAP OK
     set TXT_AZIMUT txt OK
     set TXT_AZIMUT color OK
  */
  VAR_AZIMUT_CURRENT = map(analogRead(SENS_POT_AZIMUT), 0, 1023, 0, 450); //mappo il valore letto su A0
  itoa(VAR_AZIMUT_CURRENT, BUFFER, 10);

  if (VAR_AZIMUT_CURRENT >= 0 && VAR_AZIMUT_CURRENT <= 270) {
    GAU_AZIMUT.setValue(VAR_AZIMUT_CURRENT + 90 );
    TXT_AZIMUT.setText(BUFFER);
    TXT_AZIMUT.Set_font_color_pco(GREEN);
    r0.setValue(0);
    OVERLAP = 0;
  }
  else
  {
    GAU_AZIMUT.setValue(VAR_AZIMUT_CURRENT - 270 );
    TXT_AZIMUT.setText(BUFFER);
    if (VAR_AZIMUT_CURRENT > 360 && VAR_AZIMUT_CURRENT <= 450) {
      r0.setValue(1);
      TXT_AZIMUT.Set_font_color_pco(RED);
      OVERLAP = 1;
    }
    else
    {
      GAU_AZIMUT.Set_background_color_bco(GREEN);
      TXT_OVERLAP.Set_font_color_pco(GREEN);
      TXT_AZIMUT.Set_font_color_pco(GREEN);
      r0.setValue(0);
      OVERLAP = 0;
    }
  }
  return VAR_AZIMUT_CURRENT;
}

void azimut_stop()  {
  digitalWrite( RELE_UP, LOW);
  digitalWrite( RELE_DOWN, LOW);
}

void elevaz_stop()  {
  digitalWrite( RELE_CCW, LOW);
  digitalWrite( RELE_CW, LOW);
}
void elevaz_attuale() {
  VAR_ELEVAZ_CURRENT = map(analogRead(SENS_POT_ELEVAZ), 0, 1023, 0, 180); //mappo il valore letto su A1
  itoa(VAR_ELEVAZ_CURRENT, BUFFER, 3);
  GAU_ELEVAZ.setValue(VAR_ELEVAZ_CURRENT );
  TXT_ELEVAZ.setText(BUFFER);
}

void rotazione_CW() {
  delay(10);
  digitalWrite( RELE_CW, HIGH);
}

void rotazione_CCW() {
  delay(10);
  digitalWrite( RELE_CCW, HIGH);
}

void setup(void)
{

  /* Set the baudrate which is for debug and communicate with Nextion screen. */
  nexSerial.begin(115200);
  dbSerialBegin(115200);
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

  TOU_AZIMUT_ENT.attachPop(TOU_AZIMUT_ENTPopCAllback, &TOU_AZIMUT_ENT);


  BTN_MEM1.attachPop(BTN_MEM1PopCallback, &BTN_MEM1);
  BTN_MEM2.attachPop(BTN_MEM2PopCallback, &BTN_MEM2);
  BTN_MEM3.attachPop(BTN_MEM3PopCallback, &BTN_MEM3);
  BTN_MEM4.attachPop(BTN_MEM4PopCallback, &BTN_MEM4);
  BTN_MEM5.attachPop(BTN_MEM5PopCallback, &BTN_MEM5);
  BTN_MEM6.attachPop(BTN_MEM6PopCallback, &BTN_MEM6);
  BTN_MEM7.attachPop(BTN_MEM7PopCallback, &BTN_MEM7);
  BTN_MEM8.attachPop(BTN_MEM8PopCallback, &BTN_MEM8);
  BTN_MEM9.attachPop(BTN_MEM9PopCallback, &BTN_MEM9);
  BTN_MEM10.attachPop(BTN_MEM10PopCallback, &BTN_MEM10);
  BTN_MEM11.attachPop(BTN_MEM11PopCallback, &BTN_MEM11);
  BTN_MEM12.attachPop(BTN_MEM12PopCallback, &BTN_MEM12);

  dbSerialPrintln("setup done");
  delay(2500);
  int x = 5;
  for (int a = 0; a > -1; a = a + x ) {   //DEMO gauge
    int b = (a * 2);
    GAU_ELEVAZ.setValue( a );
    GAU_AZIMUT.setValue( a * 2 );
    itoa(a, BUFFER, 10);
    itoa(b, BUFFER_1, 10);
    TXT_AZIMUT.setText( BUFFER_1 );
    TXT_ELEVAZ.setText( BUFFER );
    if (a == 180) x = -5;
    //delay(1000);
  }
}

void loop() {
  nexLoop(nex_listen_list);

  if (AZIMUT_ROTAZIONE == 1)  {
    int t_min = (VAR_AZIMUT_TARGET - 5);
    int t_max = (VAR_AZIMUT_TARGET + 5);
    digitalWrite( RELE_CW, HIGH);
    while (VAR_AZIMUT_CURRENT < t_min && VAR_AZIMUT_CURRENT > t_max );
    {
      azimut_current();
      delay(10);
    }
    digitalWrite( RELE_CW, LOW);
    AZIMUT_ROTAZIONE == 0;
  }

  int y = map(analogRead(SENS_POT_AZIMUT), 0, 1023, 0, 450);
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > 1000) {
    previousMillis = currentMillis;
    if (abs( y - VAR_AZIMUT_CURRENT) > 3) {
      azimut_current();
    }
  }
}
