
/*
  Callback eventi oggetti Nextion display
*/

//-------------------------------- MEMORY BUTTON-------------------------------
void BTN_MEM0PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM0PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  AZIMUT_TARGET = 0;
  ser_print_azimut();
  rotazione();
}

void BTN_MEM1PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM1PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  AZIMUT_TARGET = 0;
  ser_print_azimut();
  rotazione();
}

void BTN_MEM2PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM2PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  AZIMUT_TARGET = 0;
  ser_print_azimut();
  rotazione();
}

void BTN_MEM3PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM3PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  AZIMUT_TARGET = 0;
  ser_print_azimut();
  rotazione();
}

void BTN_MEM4PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM4PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  AZIMUT_TARGET = 0;
  ser_print_azimut();
  rotazione();
}

void BTN_MEM5PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM5PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  AZIMUT_TARGET = 0;
  ser_print_azimut();
  rotazione();
}

void BTN_MEM6PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM6PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  AZIMUT_TARGET = 0;
  ser_print_azimut();
  rotazione();
}

void BTN_MEM7PopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM7PopCallback");
  dbSerialPrint("ptr=");

  dbSerialPrintln((uint32_t)ptr);
  AZIMUT_TARGET = 0;
  ser_print_azimut();
  rotazione();
}

void TOU_MEM_NORDPopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM_NORDPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  AZIMUT_TARGET = 0;
  EEPROM.update(0, AZIMUT_TARGET / 4);
  ser_print_azimut();
  rotazione();
}

void TOU_MEM_ESTPopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM_ESTPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  AZIMUT_TARGET = 90;
  EEPROM.update(0, AZIMUT_TARGET / 4);
  ser_print_azimut();
  rotazione();
}

void TOU_MEM_SUDPopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM_SUDPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  AZIMUT_TARGET = 180;
  EEPROM.update(0, AZIMUT_TARGET / 4);
  ser_print_azimut();
  rotazione();
}

void TOU_MEM_WESTPopCallback(void *ptr) {
  dbSerialPrintln("BTN_MEM_WESTPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  AZIMUT_TARGET = 270;
  EEPROM.update(0, AZIMUT_TARGET / 4);
  ser_print_azimut();
  rotazione();
}
//------------------------------------------------------------------


//----------------------------------- ENTER BUTTON ---------------------------------------------
void TOU_MANUAL_ENTPopCallback(void *ptr) {
  dbSerialPrintln("TOU_MANUAL_ENT PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  delay(50);
  memset(BUFFER, 0, sizeof(BUFFER)); // scrive "0" sull'array
  VA_TARGET.getText(BUFFER, sizeof(BUFFER));
  delay(100);
  AZIMUT_TARGET = atoi(BUFFER);
  dbSerialPrintln("|------------------------------|");
  dbSerialPrint("|               BUFFER = ");
  dbSerialPrint(BUFFER);
  dbSerialPrintln("     |");
  dbSerialPrint("|TARGET da atoi BUFFER = ");
  dbSerialPrint(AZIMUT_TARGET);
  dbSerialPrintln("     |");
  dbSerialPrintln("|------------------------------|");
  EEPROM.update(0, AZIMUT_TARGET / 4);
  rotazione();
}
//------------------------------------------------------------------------------------------------

//----------------------------------------- MANUAL BUTTON ----------------------------------------
void TOU_UPPushCallback(void *ptr) {   //Funzione callback per l'evento PUSH del button TOU_UP
  dbSerialPrintln("TOU_UP PushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  TXT_ROTAZIONE.Set_font_color_pco(NORMAL);
  delay(DELAY_S);
  digitalWrite( RELE_UP, HIGH);
}
void TOU_UPPopCallback(void *ptr) {   //Funzione callback per l'evento POP del button TOU_UP
  dbSerialPrintln("TOU_UP PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  TXT_ROTAZIONE.Set_font_color_pco(SFONDO);
  delay(DELAY_S);
  digitalWrite( RELE_UP, LOW );
}
void TOU_DOWNPushCallback(void *ptr) {  //Funzione callback per l'evento PUSH del button TOU_DOWN
  dbSerialPrintln("TOU_DOWNPushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  TXT_ROTAZIONE.Set_font_color_pco(NORMAL);
  delay(DELAY_S);
  digitalWrite( RELE_DOWN, HIGH);
}
void TOU_CCWPushCallback(void *ptr) { //Funzione callback per l'evento PUSH del button TOU_CCW
  dbSerialPrintln("TOU_CCWPushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  TXT_ROTAZIONE.Set_font_color_pco(NORMAL);
  delay(DELAY_S);
  digitalWrite( RELE_CCW, HIGH);
}
void TOU_CWPushCallback(void *ptr) {  //Funzione callback per l'evento PUSH del button TOU_CW
  dbSerialPrintln("TOU_CWPushCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  TXT_ROTAZIONE.Set_font_color_pco(NORMAL);
  delay(DELAY_S);
  digitalWrite( RELE_CW, HIGH);
}
void TOU_CWPopCallback(void *ptr) { //Funzione callback per l'evento POP del button TOU_CW
  dbSerialPrintln("TOU_CWPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  TXT_ROTAZIONE.Set_font_color_pco(SFONDO);
  delay(DELAY_S);
  digitalWrite( RELE_CW, LOW );
}
void TOU_CCWPopCallback(void *ptr)  { //Funzione callback per l'evento POP del button TOU_CCW
  dbSerialPrintln("TOU_CCWPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  TXT_ROTAZIONE.Set_font_color_pco(SFONDO);
  delay(DELAY_S);
  digitalWrite( RELE_CCW, LOW );
}
void TOU_DOWNPopCallback(void *ptr) { //Funzione callback per l'evento POP del button TOU_DOWN
  dbSerialPrintln("TOU_DOWNPopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  TXT_ROTAZIONE.Set_font_color_pco(SFONDO);
  delay(DELAY_S);
  digitalWrite( RELE_DOWN, LOW );
}
//--------------------------------------------------------------------------------------------------
