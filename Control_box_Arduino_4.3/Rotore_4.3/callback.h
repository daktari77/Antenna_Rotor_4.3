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
void BTN_ENTERPopCallback(void *ptr) {

}

void TOU_AZIMUT_ENTPopCAllback(void *ptr){
  dbSerialPrintln("TOU_AZIMUT_ENTPopCAllback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
}

void TOU_UPPushCallback(void *ptr) {   //Funzione callback per l'evento PUSH del button TOU_UP
  dbSerialPrintln("TOU_UPPushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  azimut_attuale();
  digitalWrite( RELE_DOWN, LOW );
  delay(DELAY_S);
  digitalWrite( RELE_UP, HIGH );
}

void TOU_DOWNPushCallback(void *ptr) {  //Funzione callback per l'evento PUSH del button TOU_DOWN
  dbSerialPrintln("TOU_DOWNPushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  azimut_attuale();
  digitalWrite( RELE_UP, LOW );
  delay(DELAY_S);
  digitalWrite( RELE_DOWN, HIGH );
}

void TOU_CCWPushCallback(void *ptr) { //Funzione callback per l'evento PUSH del button TOU_CCW
  dbSerialPrintln("TOU_CCWPushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  azimut_attuale();
  digitalWrite( RELE_CW, LOW );
  delay(DELAY_S);
  digitalWrite( RELE_CCW, HIGH );
}

void TOU_CWPushCallback(void *ptr) {  //Funzione callback per l'evento PUSH del button TOU_CW
  //NexButton *btn = (NexButton *)ptr;
  dbSerialPrintln("TOU_CWPushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  azimut_attuale();
  digitalWrite( RELE_CCW, LOW );
  delay(DELAY_S);
  digitalWrite( RELE_CW, HIGH );
}

void TOU_UPPopCallback(void *ptr) {   //Funzione callback per l'evento POP del button TOU_UP
  dbSerialPrintln("TOU_UPPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(DELAY_S);
  digitalWrite( RELE_UP, LOW );
  delay(DELAY_S);
  digitalWrite( RELE_DOWN, LOW );
  azimut_attuale();
}

void TOU_CWPopCallback(void *ptr) { //Funzione callback per l'evento POP del button TOU_CW
  dbSerialPrintln("TOU_CWPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  azimut_attuale();
  delay(DELAY_L);
  digitalWrite( RELE_CCW, LOW );
  delay(DELAY_L);
  digitalWrite( RELE_CW, LOW );
}

void TOU_CCWPopCallback(void *ptr)  { //Funzione callback per l'evento POP del button TOU_CCW
  dbSerialPrintln("TOU_CCWPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  azimut_attuale();
  delay(DELAY_L);
  digitalWrite( RELE_CCW, LOW );
  delay(DELAY_L);
  digitalWrite( RELE_CW, LOW );
}

void TOU_DOWNPopCallback(void *ptr) { //Funzione callback per l'evento POP del button TOU_DOWN
  dbSerialPrintln("TOU_DOWNPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  azimut_attuale();
  delay(DELAY_L);
  digitalWrite( RELE_UP, LOW );
  delay(DELAY_L);
  digitalWrite( RELE_DOWN, LOW );
}
