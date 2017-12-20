
#include <Nextion.h>

uint8_t RELE_UP = 8;  //RELE UP
uint8_t RELE_DOWN = 9;  //RELE DOWN
uint8_t RELE_CW = 10; //RELE rotazione sendo orario //lasciare 10 per arduino MEGA
uint8_t RELE_CCW = 11; //RELE rotazione sendo anti-orario //lasciare 11 per arduino MEGA
uint8_t SENS_POT_AZIMUT = 0; //Sensore al quale sarà collegato il centrale del potenziometro del rotore per azimut
uint8_t SENS_POT_ELEVAZ = 1; //Sensore al quale sarà collegato il centrale del potenziometro del rotore per alevazione
uint8_t AZIMUT_ROTAZIONE; // Array usato per il case switch, accetta valori STOP CW CCW

const uint8_t PAG_SPLASH = 0; //rimettere a 0
const uint8_t PAG_MAIN = 1;
const uint8_t PAG_AZIMUT = 2;
const uint8_t PAG_KEYBOARD = 3;
const uint8_t PAG_CONFIG = 4;
const uint8_t PAG_ERROR = 5;
const uint8_t PAG_ROTARY = 6;


NexButton BTN_ROT_ENT = NexButton(PAG_ROTARY, 10, "b6"); //rotary
NexVariable va0 = NexVariable(PAG_ROTARY, 12, "va0");
NexNumber n3 = NexNumber(PAG_ROTARY, 11, "n3");
NexTouch *nex_listen_list[] =
{
  &BTN_ROT_ENT,
  NULL
};



void BTN_ROT_ENTPopCallback(void *ptr) {
  uint32_t k;
  dbSerialPrintln("BTN_ROT_ENT PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(25);
  n3.getValue(&k);
  dbSerialPrint("k=");
  dbSerialPrintln(k);
}


void setup() {
  nexInit();
  // put your setup code here, to run once:
  BTN_ROT_ENT.attachPop(BTN_ROT_ENTPopCallback, &BTN_ROT_ENT); //test rotary insert
  dbSerialPrintln("setup done");
}

void loop() {
  // put your main code here, to run repeatedly:
  nexLoop(nex_listen_list);

}
