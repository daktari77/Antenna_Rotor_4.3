/*
   CONTROL BOX arduino based
   Nextion Display 4.3"
*/
#include <doxygen.h>
#include <NexButton.h>
#include <NexCheckbox.h>
#include <NexConfig.h>
#include <NexCrop.h>
#include <NexDualStateButton.h>
#include <NexGauge.h>
#include <NexGpio.h>
#include <NexHardware.h>
#include <NexHotspot.h>
#include <NexNumber.h>
#include <NexObject.h>
#include <NexPage.h>
#include <NexPicture.h>
#include <NexProgressBar.h>
#include <NexRadio.h>
#include <NexRtc.h>
#include <NexScrolltext.h>
#include <NexSlider.h>
#include <NexText.h>
#include <NexTimer.h>
#include <Nextion.h>
#include <NexTouch.h>
#include <NexUpload.h>
#include <NexVariable.h>
#include <NexWaveform.h>

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
  &BTN_MEM8,
  &BTN_MEM9,
  &BTN_MEM10,
  &BTN_MEM11,
  &BTN_MEM12,
  NULL
};

void setup(void)
{
  /* Set the baudrate which is for debug and communicate with Nextion screen. */

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

  //BTN_ENTER.attachPop(BTN_ENTERPopCallback, &BTN_ENTER);

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

  azimut_attuale(); // prima lettura della posizione del rotore

  dbSerialPrintln("setup done");
}

void loop()
{
  int X;
  for (X = 0; X < 101; X++) {

  }
  nexLoop(nex_listen_list);
}
