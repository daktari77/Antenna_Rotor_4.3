/*
   CONTROL BOX arduino based
   Nextion Display 4.3"
*/

#include <Nextion.h>
#include <EEPROM.h>
#include "declare.h"  // variabili e costanti di ambiente
#include "ext_func.h" //funzioni da richiamare esternamente
#include "callback.h" // funzioni callback di Nextion display

/*
   Register a button object to the touch event list.
*/
NexTouch *nex_listen_list[] =
{
  &TOU_CCW,         //evento pressione touch ccw
  &TOU_CW,          //evento pressione touch cw
  &TOU_UP,          //evento pressione touch up
  &TOU_DOWN,        //evento pressione touch DOWN
  &BTN_AZIMUT_ENT,
  &BTN_MEM0,
  &BTN_MEM1,
  &BTN_MEM2,
  &BTN_MEM3,
  &BTN_MEM4,
  &BTN_MEM5,
  &BTN_MEM6,
  &BTN_MEM7,
  &TOU_MEM_WEST,
  &TOU_MEM_EST,
  &TOU_MEM_SUD,
  &TOU_MEM_NORD,
  NULL
};

void setup(void)
{
  /* Set the baudrate which is for debug and communicate with Nextion screen. */
  VAR_AZIMUT_LAST_TARGET = ((EEPROM.read(0) * 4)); // RECUPERA INFO SU ULTIMO TARGET RICHIESTO

  for (int X = 8; X <= 11; X++) {
    pinMode( X, OUTPUT );
    digitalWrite( X, LOW );
  }
  nexInit();
  /* Register the pop and push event callback function of the current button component. */
  TOU_CCW.attachPop(TOU_CCWPopCallback, &TOU_CCW);      // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_CCW.attachPush(TOU_CCWPushCallback, &TOU_CCW);    // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_CW.attachPop(TOU_CWPopCallback, &TOU_CW);         // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_CW.attachPush(TOU_CWPushCallback, &TOU_CW);       // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_UP.attachPop(TOU_UPPopCallback, &TOU_UP);         // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_UP.attachPush(TOU_UPPushCallback, &TOU_UP);       // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_DOWN.attachPop(TOU_DOWNPopCallback, &TOU_DOWN);   // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_DOWN.attachPush(TOU_DOWNPushCallback, &TOU_DOWN); // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  BTN_AZIMUT_ENT.attachPop(BTN_AZIMUT_ENTPopCallback, &BTN_AZIMUT_ENT);

  BTN_MEM1.attachPop(BTN_MEM1PopCallback, &BTN_MEM1); // BUTTON PER POSIZIONI PREIMPOSTATE
  BTN_MEM2.attachPop(BTN_MEM2PopCallback, &BTN_MEM2); // BUTTON PER POSIZIONI PREIMPOSTATE
  BTN_MEM3.attachPop(BTN_MEM3PopCallback, &BTN_MEM3); // BUTTON PER POSIZIONI PREIMPOSTATE
  BTN_MEM4.attachPop(BTN_MEM4PopCallback, &BTN_MEM4); // BUTTON PER POSIZIONI PREIMPOSTATE
  BTN_MEM5.attachPop(BTN_MEM5PopCallback, &BTN_MEM5); // BUTTON PER POSIZIONI PREIMPOSTATE
  BTN_MEM6.attachPop(BTN_MEM6PopCallback, &BTN_MEM6); // BUTTON PER POSIZIONI PREIMPOSTATE
  BTN_MEM7.attachPop(BTN_MEM7PopCallback, &BTN_MEM7); // BUTTON PER POSIZIONI PREIMPOSTATE
  BTN_MEM0.attachPop(BTN_MEM0PopCallback, &BTN_MEM0); // BUTTON PER POSIZIONI PREIMPOSTATE

  TOU_MEM_WEST.attachPop(TOU_MEM_WESTPopCallback, &TOU_MEM_WEST); // BUTTON PER POSIZIONI PREIMPOSTATE OVEST
  TOU_MEM_EST.attachPop(TOU_MEM_ESTPopCallback, &TOU_MEM_EST);    // BUTTON PER POSIZIONI PREIMPOSTATE EST
  TOU_MEM_SUD.attachPop(TOU_MEM_SUDPopCallback, &TOU_MEM_SUD);    // BUTTON PER POSIZIONI PREIMPOSTATE SUN
  TOU_MEM_NORD.attachPop(TOU_MEM_NORDPopCallback, &TOU_MEM_NORD); // BUTTON PER POSIZIONI PREIMPOSTATE NORD

  dbSerialPrintln("setup done");

  delay(1000);

  int x = 20;
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
  int AZ_CURR_DIFF = (max(X, VAR_AZIMUT_CURRENT) - min(X, VAR_AZIMUT_CURRENT)); //CALCOLO LA DIFFERENZA TRA VAR_AZIMUT_CURRENT E VALORE ATTUALE
  int EL_CURR_DIFF = (max(X, VAR_ELEVAZ_CURRENT) - min(X, VAR_ELEVAZ_CURRENT)); //CALCOLO LA DIFFERENZA TRA VAR_ELEVAZT_CURRENT E VALORE ATTUALE
  unsigned long currentMillis = millis();
  nexLoop(nex_listen_list);

  if ((AZIMUT_ROTAZIONE == "CCW")) {
    int previusMillis = 0;
    rotazione_CCW();
    AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    while ( AZ_MAX - AZ_MIN > 1) {
      currentMillis = millis();
      if (currentMillis - previusMillis > 250) { // aggiorna la posizione ogni 750ms
        dbSerialPrintln("ogni secondo, richiamata rotazione CCW");
        azimut_current(); // invia valori al display e Leggere il valore del potenziometro
        previusMillis = currentMillis;
      }
      AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
      AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    }
    azimut_stop();
    AZIMUT_ROTAZIONE = "STOP";
  }
  else if ((AZIMUT_ROTAZIONE  == "CW")) {
    int previusMillis = 0;
    dbSerialPrintln("Ciclo IF richiamato da rotazione(), richiamata rotazione CW");
    rotazione_CW();
    AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    while ( AZ_MAX - AZ_MIN > 1) {
      currentMillis = millis();
      if (currentMillis - previusMillis > 250) { // aggiorna la posizione ogni 750ms
        dbSerialPrintln("ogni secondo, richiamata rotazione CW");
        azimut_current(); // invia valori al display e Leggere il valore del potenziometro
        previusMillis = currentMillis;
      }
      AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
      AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    }
    azimut_stop();
    AZIMUT_ROTAZIONE = "STOP";
  }

  /*
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
    }*/
}
