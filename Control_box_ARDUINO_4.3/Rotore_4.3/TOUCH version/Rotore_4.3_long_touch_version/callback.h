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
  uint32_t AAA = 0;
  
  dbSerialPrintln("TOU_AZIMUT_ENTPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  //delay(100);
  memset(BUFFER, 0, sizeof(BUFFER));
  VA_TARGET.getText(BUFFER, sizeof(BUFFER));
  delay(100);
  VA_TARGET_INT.getValue(&AAA);
  //if (AAA) {
    int XXX = (int)AAA;
    int YYY = (int)BUFFER;
    delay(100);
    VAR_AZIMUT_TARGET = atoi(BUFFER);
    dbSerialPrintln("|------------------------------|");
    dbSerialPrint("|                    a = ");
    dbSerialPrintln(XXX);
    dbSerialPrint("|               BUFFER = ");
    dbSerialPrintln(BUFFER);
    dbSerialPrint("|TARGET da atoi BUFFER = ");
    dbSerialPrintln(VAR_AZIMUT_TARGET);
    dbSerialPrintln("|------------------------------|");
    //EEPROM.update(0, VAR_AZIMUT_TARGET / 4);
    rotazione();
  //}
//  else
//  {
//    dbSerialPrintln("ERRORE NELLA RICEZIONE DEL VALORE DELLA VARIABILE");
//  }
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
