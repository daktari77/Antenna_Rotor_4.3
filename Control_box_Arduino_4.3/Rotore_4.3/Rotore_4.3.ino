/*
   CONTROL BOX arduino based
   Nextion Display 4.3"
*/

#include <Nextion.h>

#include "declare.h" // variabili e costanti di ambiente
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
  &TOU_AZIMUT_ENT,
  &BTN_MEM1,
  &BTN_MEM2,
  &BTN_MEM3,
  &BTN_MEM4,
  &BTN_MEM5,
  &BTN_MEM6,
  &BTN_MEM7,
  &BTN_MEM0,
  &TOU_MEM_WEST,
  &TOU_MEM_EST,
  &TOU_MEM_SUD,
  &TOU_MEM_NORD,
  NULL
};

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
  BTN_MEM0.attachPop(BTN_MEM0PopCallback, &BTN_MEM0);
  TOU_MEM_WEST.attachPop(TOU_MEM_WESTPopCallback, &TOU_MEM_WEST);
  TOU_MEM_EST.attachPop(TOU_MEM_ESTPopCallback, &TOU_MEM_EST);
  TOU_MEM_SUD.attachPop(TOU_MEM_SUDPopCallback, &TOU_MEM_SUD);
  TOU_MEM_NORD.attachPop(TOU_MEM_NORDPopCallback, &TOU_MEM_NORD);
  //azimut_current();
  dbSerialPrintln("setup done");
  delay(2500);
  int x = 10;
  /*
  for (int a = 0; a >= -1; a = a + x ) {   //DEMO gauge
    int b = (a * 2);
    GAU_ELEVAZ.setValue( a );
    itoa(a, BUFFER, 10);
    TXT_ELEVAZ.setText( BUFFER );
    GAU_AZIMUT.setValue( b );
    itoa(b, BUFFER_1, 10);
    TXT_AZIMUT.setText( BUFFER_1 );
    if (a == 180) x = -10;
    //delay(1000);
  }
  */
}

void loop() {
  nexLoop(nex_listen_list);

  switch (AZIMUT_ROTAZIONE) {
    case STOP:
      azimut_stop();
      break;
    case CCW:
      rotazione_CCW();
      while (abs(VAR_AZIMUT_CURRENT - VAR_AZIMUT_TARGET) < 5 && abs(VAR_AZIMUT_CURRENT - VAR_AZIMUT_TARGET) > 5) {
        azimut_current();
        delay(10);
      }
      azimut_stop();
      AZIMUT_ROTAZIONE = STOP;
      break;
    case CW:
      rotazione_CW();
      while (abs(VAR_AZIMUT_CURRENT - VAR_AZIMUT_TARGET) < 5 && abs(VAR_AZIMUT_CURRENT - VAR_AZIMUT_TARGET) > 5)  {
        azimut_current();
        delay(10);
      }
      azimut_stop();
      AZIMUT_ROTAZIONE = STOP;
      break;
  }

  int y = map(analogRead(SENS_POT_AZIMUT), 0, 1023, 0, 450);
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    if (abs( y - VAR_AZIMUT_CURRENT) > 2) {
      azimut_current(); //Calcolo e visualizzazione azimut corrente su display
      ser_print_azimut(); //Serial print posizione corrente e target
    }
  }

  if (RUN_CALIBRAZIONE == 1) {
    int VAR_AZIMUT_PREV = analogRead(SENS_POT_AZIMUT);
    rotazione_CCW();
    //VAR_AZIMUT_PREV = analogRead(SENS_POT_AZIMUT);
    while (VAR_AZIMUT_CURRENT <= VAR_AZIMUT_PREV) {
      VAR_AZIMUT_PREV = VAR_AZIMUT_CURRENT;
    }
    azimut_stop();
    VAR_AZIMUT_MIN = analogRead(SENS_POT_AZIMUT);
    delay(1000);
    rotazione_CW();
    while (VAR_AZIMUT_CURRENT > VAR_AZIMUT_PREV) {
      VAR_AZIMUT_PREV = VAR_AZIMUT_CURRENT;
    }
    azimut_stop();
    VAR_AZIMUT_MAX = analogRead(SENS_POT_AZIMUT);
    RUN_CALIBRAZIONE = 0;
  }
}
