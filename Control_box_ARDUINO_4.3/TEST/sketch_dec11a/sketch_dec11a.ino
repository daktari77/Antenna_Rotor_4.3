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
  &TOU_CCW,
  &TOU_CW,
  &TOU_UP,
  &TOU_DOWN,
  &TOU_MEM_WEST,
  &TOU_MEM_EST,
  &TOU_MEM_SUD,
  &TOU_MEM_NORD,
  NULL
};

























void setup() {
  // put your setup code here, to run once:
  for (int X = 8; X <= 11; X++) { //ciclo for per inizializzare i pin per i rele
    pinMode( X, OUTPUT );
    digitalWrite( X, LOW );
  }
  nexInit();
  TOU_CCW.attachPop(TOU_CCWPopCallback, &TOU_CCW);
  TOU_CCW.attachPush(TOU_CCWPushCallback, &TOU_CCW);
  TOU_CW.attachPop(TOU_CWPopCallback, &TOU_CW);
  TOU_CW.attachPush(TOU_CWPushCallback, &TOU_CW);
  TOU_UP.attachPop(TOU_UPPopCallback, &TOU_UP);
  TOU_UP.attachPush(TOU_UPPushCallback, &TOU_UP);
  TOU_DOWN.attachPop(TOU_DOWNPopCallback, &TOU_DOWN);
  TOU_DOWN.attachPush(TOU_DOWNPushCallback, &TOU_DOWN);
  TOU_MEM_WEST.attachPop(TOU_MEM_WESTPopCallback, &TOU_MEM_WEST);
  TOU_MEM_EST.attachPop(TOU_MEM_ESTPopCallback, &TOU_MEM_EST);
  TOU_MEM_SUD.attachPop(TOU_MEM_SUDPopCallback, &TOU_MEM_SUD);
  TOU_MEM_NORD.attachPop(TOU_MEM_NORDPopCallback, &TOU_MEM_NORD);
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
  dbSerialPrintln("setup done");
}

void loop() {
  // put your main code here, to run repeatedly:

  int X = map(analogRead(SENS_POT_AZIMUT), 0, 1023, 0, 450);
  int Y = map(analogRead(SENS_POT_ELEVAZ), 0, 1023, 0, 180);
  int AZ_MAX;
  int AZ_MIN;
  int AZ_CURR_DIFF = (max(X, VAR_AZIMUT_CURRENT) - min(X, VAR_AZIMUT_CURRENT)); //CALCOLO LA DIFFERENZA TRA VAR_AZIMUT_CURRENT E VALORE ATTUALE
  int EL_CURR_DIFF = (max(X, VAR_ELEVAZ_CURRENT) - min(X, VAR_ELEVAZ_CURRENT)); //CALCOLO LA DIFFERENZA TRA VAR_ELEVAZ_CURRENT E VALORE ATTUALE
  unsigned long currentMillis = millis();
  nexLoop(nex_listen_list);

  if ((AZIMUT_ROTAZIONE == CCW)) {
    rotazione_CCW();
    AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);

    while ( AZ_MAX - AZ_MIN > 1) {
      azimut_current(); // invia valori al display e Leggere il valore del potenziometro
      AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
      AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    }
    azimut_stop();
    AZIMUT_ROTAZIONE = STOP;
  }
  else if ((AZIMUT_ROTAZIONE  == CW)) {
    rotazione_CW();
    AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    while ( AZ_MAX - AZ_MIN > 1) {
      azimut_current();
      AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
      AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
    }
    azimut_stop();
    AZIMUT_ROTAZIONE = STOP;
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
}
