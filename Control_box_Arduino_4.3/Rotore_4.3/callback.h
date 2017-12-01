/*
  Callback eventi oggetti Nextion display
*/

/*
   Memory recall
*/
void BTN_MEM0PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM0PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM0.getValue(&VAR_AZIMUT_TARGET);
  rotazione();
}

void BTN_MEM1PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM1PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM1.getValue(&VAR_AZIMUT_TARGET);
}

void BTN_MEM2PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM2PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM2.getValue(&VAR_AZIMUT_TARGET);
}

void BTN_MEM3PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM3PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM3.getValue(&VAR_AZIMUT_TARGET);

}
void BTN_MEM4PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM4PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM4.getValue(&VAR_AZIMUT_TARGET);

}
void BTN_MEM5PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM5PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM5.getValue(&VAR_AZIMUT_TARGET);

}
void BTN_MEM6PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM6PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM6.getValue(&VAR_AZIMUT_TARGET);

}
void BTN_MEM7PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM7PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VA_MEM7.getValue(&VAR_AZIMUT_TARGET);

}

void BTN_MEM_WESTPopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM_WESTPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VAR_AZIMUT_TARGET = 270;
}
void BTN_MEM_ESTPopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM_ESTPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VAR_AZIMUT_TARGET = 90;
}
void BTN_MEM_SUDPopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM_SUDPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VAR_AZIMUT_TARGET = 180;
}
void BTN_MEM_NORDPopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM_NORDPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  VAR_AZIMUT_TARGET = 0;
}

void TOU_AZIMUT_ENTPopCAllback(void *ptr) {
  dbSerialPrintln("TOU_AZIMUT_ENTPopCAllback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  va2.getValue(&VAR_AZIMUT_TARGET);

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
