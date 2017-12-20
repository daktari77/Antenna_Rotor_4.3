# 1 "C:\\Users\\miche\\Dropbox (Personale)\\Progetti\\Antenna_Rotor\\Control_box_ARDUINO_4.3\\Rotore_4.3\\TOUCH version\\Rotore_4.3_short_touch_version\\Rotore_4.3_short_touch_version.ino"
# 1 "C:\\Users\\miche\\Dropbox (Personale)\\Progetti\\Antenna_Rotor\\Control_box_ARDUINO_4.3\\Rotore_4.3\\TOUCH version\\Rotore_4.3_short_touch_version\\Rotore_4.3_short_touch_version.ino"
/*

   CONTROL BOX arduino based

   Nextion Display 4.3"

*/
# 6 "C:\\Users\\miche\\Dropbox (Personale)\\Progetti\\Antenna_Rotor\\Control_box_ARDUINO_4.3\\Rotore_4.3\\TOUCH version\\Rotore_4.3_short_touch_version\\Rotore_4.3_short_touch_version.ino"
# 7 "C:\\Users\\miche\\Dropbox (Personale)\\Progetti\\Antenna_Rotor\\Control_box_ARDUINO_4.3\\Rotore_4.3\\TOUCH version\\Rotore_4.3_short_touch_version\\Rotore_4.3_short_touch_version.ino" 2
# 8 "C:\\Users\\miche\\Dropbox (Personale)\\Progetti\\Antenna_Rotor\\Control_box_ARDUINO_4.3\\Rotore_4.3\\TOUCH version\\Rotore_4.3_short_touch_version\\Rotore_4.3_short_touch_version.ino" 2
# 9 "C:\\Users\\miche\\Dropbox (Personale)\\Progetti\\Antenna_Rotor\\Control_box_ARDUINO_4.3\\Rotore_4.3\\TOUCH version\\Rotore_4.3_short_touch_version\\Rotore_4.3_short_touch_version.ino" 2
# 10 "C:\\Users\\miche\\Dropbox (Personale)\\Progetti\\Antenna_Rotor\\Control_box_ARDUINO_4.3\\Rotore_4.3\\TOUCH version\\Rotore_4.3_short_touch_version\\Rotore_4.3_short_touch_version.ino" 2
# 11 "C:\\Users\\miche\\Dropbox (Personale)\\Progetti\\Antenna_Rotor\\Control_box_ARDUINO_4.3\\Rotore_4.3\\TOUCH version\\Rotore_4.3_short_touch_version\\Rotore_4.3_short_touch_version.ino" 2

/*

   Register a button object to the touch event list.

*/
# 15 "C:\\Users\\miche\\Dropbox (Personale)\\Progetti\\Antenna_Rotor\\Control_box_ARDUINO_4.3\\Rotore_4.3\\TOUCH version\\Rotore_4.3_short_touch_version\\Rotore_4.3_short_touch_version.ino"
NexTouch *nex_listen_list[] =
{
  &TOU_CCW, //evento pressione touch ccw
  &TOU_CW, //evento pressione touch cw
  &TOU_UP, //evento pressione touch up
  &TOU_DOWN, //evento pressione touch DOWN
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
  __null
};

void setup(void)
{
  unsigned long previousMillis = 0;
  VAR_AZIMUT_LAST_TARGET = ((EEPROM.read(0) * 4)); // RECUPERA INFO SU ULTIMO TARGET RICHIESTO

  for (int X = 8; X <= 11; X++) {
    pinMode( X, 0x1 );
    digitalWrite( X, 0x0 );
  }
  nexInit();
  /* Register the pop and push event callback function of the current button component. */
  TOU_CCW.attachPop(TOU_CCWPopCallback, &TOU_CCW); // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_CCW.attachPush(TOU_CCWPushCallback, &TOU_CCW); // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_CW.attachPop(TOU_CWPopCallback, &TOU_CW); // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_CW.attachPush(TOU_CWPushCallback, &TOU_CW); // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_UP.attachPop(TOU_UPPopCallback, &TOU_UP); // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_UP.attachPush(TOU_UPPushCallback, &TOU_UP); // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
  TOU_DOWN.attachPop(TOU_DOWNPopCallback, &TOU_DOWN); // TOUCH AREA PER AZIONAMENTO MANUALE DEL ROTORE
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
  TOU_MEM_EST.attachPop(TOU_MEM_ESTPopCallback, &TOU_MEM_EST); // BUTTON PER POSIZIONI PREIMPOSTATE EST
  TOU_MEM_SUD.attachPop(TOU_MEM_SUDPopCallback, &TOU_MEM_SUD); // BUTTON PER POSIZIONI PREIMPOSTATE SUN
  TOU_MEM_NORD.attachPop(TOU_MEM_NORDPopCallback, &TOU_MEM_NORD); // BUTTON PER POSIZIONI PREIMPOSTATE NORD

  Serial.println("setup done");

  delay(1000);

  int x = 20;
  for (int a = 0; a >= -1; a = a + x ) { //DEMO gauge
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

  int X = map(analogRead(0 /*Sensore al quale sarà collegato il centrale del potenziometro del rotore per azimut*/), 0, 1023, 0, 450);
  int Y = map(analogRead(1 /*Sensore al quale sarà collegato il centrale del potenziometro del rotore per alevazione*/), 0, 1023, 0, 180);
  int AZ_CURR_DIFF = (((X)>(AZIMUT_CURRENT)?(X):(AZIMUT_CURRENT)) - ((X)<(AZIMUT_CURRENT)?(X):(AZIMUT_CURRENT))); //CALCOLO LA DIFFERENZA TRA AZIMUT_CURRENT E VALORE ATTUALE
  int EL_CURR_DIFF = (((Y)>(ELEVAZ_CURRENT)?(Y):(ELEVAZ_CURRENT)) - ((Y)<(ELEVAZ_CURRENT)?(Y):(ELEVAZ_CURRENT))); //CALCOLO LA DIFFERENZA TRA VAR_ELEVAZT_CURRENT E VALORE ATTUALE
  unsigned long currentMillis = millis();

  nexLoop(nex_listen_list);

  if ((AZIMUT_ROTAZIONE == "CCW")) {
    unsigned long previousMillis = 0;
    rotazione_CCW();
    AZ_MAX = ((AZIMUT_CURRENT)>(AZIMUT_TARGET)?(AZIMUT_CURRENT):(AZIMUT_TARGET));
    AZ_MIN = ((AZIMUT_CURRENT)<(AZIMUT_TARGET)?(AZIMUT_CURRENT):(AZIMUT_TARGET));
    while ( AZ_MAX - AZ_MIN > 1) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 500) { // aggiorna la posizione ogni 750ms
        Serial.println("ogni secondo, richiamata rotazione CCW");
        azimut_current(); // invia valori al display e Leggere il valore del potenziometro
        previousMillis = currentMillis;
      }
      AZ_MAX = ((AZIMUT_CURRENT)>(AZIMUT_TARGET)?(AZIMUT_CURRENT):(AZIMUT_TARGET));
      AZ_MIN = ((AZIMUT_CURRENT)<(AZIMUT_TARGET)?(AZIMUT_CURRENT):(AZIMUT_TARGET));
    }
    azimut_stop();
    AZIMUT_ROTAZIONE = "STOP";
  }

  else if ((AZIMUT_ROTAZIONE == "CW")) {
    unsigned long previousMillis = 0;
    Serial.println("Ciclo IF richiamato da rotazione(), richiamata rotazione CW");
    rotazione_CW();
    AZ_MAX = ((AZIMUT_CURRENT)>(AZIMUT_TARGET)?(AZIMUT_CURRENT):(AZIMUT_TARGET));
    AZ_MIN = ((AZIMUT_CURRENT)<(AZIMUT_TARGET)?(AZIMUT_CURRENT):(AZIMUT_TARGET));
    while ( AZ_MAX - AZ_MIN > 1) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 500) { // aggiorna la posizione ogni 750ms
        Serial.println("ogni secondo, richiamata rotazione CW");
        azimut_current(); // invia valori al display e Leggere il valore del potenziometro
        previousMillis = currentMillis;
      }
      AZ_MAX = ((AZIMUT_CURRENT)>(AZIMUT_TARGET)?(AZIMUT_CURRENT):(AZIMUT_TARGET));
      AZ_MIN = ((AZIMUT_CURRENT)<(AZIMUT_TARGET)?(AZIMUT_CURRENT):(AZIMUT_TARGET));
    }
    azimut_stop();
    AZIMUT_ROTAZIONE = "STOP";
  }


  if (currentMillis - previousMillis >= 500) {
    previousMillis = currentMillis;
    if (AZ_CURR_DIFF > 2) //Aggiorno valore display solo se differenza maggiore di 2
    {
      azimut_current(); //Calcolo e visualizzazione azimut corrente su display
      EEPROM.update(L_A, AZIMUT_CURRENT / 4);
    }
    if (EL_CURR_DIFF > 2) //Aggiorno valore display solo se differenza maggiore di 2
    {
      elevaz_current(); //Calcolo e visualizzazione ELEVAZ corrente su display
      EEPROM.update(L_E, ELEVAZ_CURRENT); // NON è NECESSARIO DIVIDERE IL VALORE PER 4 POICHE' ELEVAZ MAX = 180 (< 255)
    }
  }
}
