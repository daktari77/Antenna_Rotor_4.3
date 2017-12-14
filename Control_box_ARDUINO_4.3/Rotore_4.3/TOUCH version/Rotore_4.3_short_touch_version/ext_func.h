void ser_print_azimut() { //Serial print posizione corrente e target
  dbSerialPrintln("E' stata richiamata la funzione ser_print_azimut()");
  dbSerialPrintln("____________________________");
  dbSerialPrint("|TARGET = ");
  dbSerialPrintln(VAR_AZIMUT_TARGET);
  dbSerialPrint("|LAST TARGET = ");
  dbSerialPrintln(VAR_AZIMUT_LAST_TARGET );
  dbSerialPrint("|CURRENT= ");
  dbSerialPrintln(VAR_AZIMUT_CURRENT);
  dbSerialPrint("|DIFF(function)= ");
  AZ_MAX = max(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
  AZ_MIN = min(VAR_AZIMUT_CURRENT , VAR_AZIMUT_TARGET);
  EL_MAX = max(VAR_ELEVAZ_CURRENT , VAR_ELEVAZ_TARGET);
  EL_MIN = min(VAR_ELEVAZ_CURRENT , VAR_ELEVAZ_TARGET);
  dbSerialPrintln(AZ_MAX - AZ_MIN);
  dbSerialPrintln("____________________________");
}

void rotazione() {
  dbSerialPrintln("E' stata richiamata la funzione  rotazione() ");
  if (VAR_AZIMUT_CURRENT < VAR_AZIMUT_TARGET) {
    dbSerialPrintln("Rotazione CCW in corso ");
    AZIMUT_ROTAZIONE = "CCW";
  }
  else {
    dbSerialPrintln("Rotazione CW in corso ");
    AZIMUT_ROTAZIONE = "CW";
  }
}  //Chiusura void

void elevaz_current() {
  dbSerialPrintln("E' stata richiamata la funzione  elevaz_current()");
  VAR_ELEVAZ_CURRENT = map(analogRead(SENS_POT_ELEVAZ), 0, 1023, 0, 180); //mappo il valore letto su A1
  itoa(VAR_ELEVAZ_CURRENT, BUFFER_EL, 10);
  GAU_ELEVAZ.setValue(VAR_ELEVAZ_CURRENT );
  TXT_ELEVAZ.setText(BUFFER_EL);
}

void azimut_current() {
  /*
     Set puntatore OK
     Set colore puntatore FAIL
     set TXT_OVERLAP OK
     set TXT_AZIMUT txt OK
     set TXT_AZIMUT color OK
  */
  dbSerialPrintln("E' stata richiamata la funzione  azimut_current()");
  int previusMillis = 0;
  VAR_AZIMUT_CURRENT = map(analogRead(SENS_POT_AZIMUT), 0, 1023, 0, 450); //mappo il valore letto su A0
  itoa(VAR_AZIMUT_CURRENT, BUFFER_AZ, 10); //CONVERTE LA POSIZIONE IN STRINGA DA INVIARE A TXT_AZIMUT
  unsigned long  currentMillis = millis();
  if (currentMillis - previusMillis > 100) { //AGGIORNA IL VALORE OGNI 100ms (DA MODIFICARE ALL'OCCORRENZA)
    previusMillis = currentMillis;
    if (VAR_AZIMUT_CURRENT >= 0 && VAR_AZIMUT_CURRENT <= 270) {
      ser_print_azimut();
      GAU_AZIMUT.setValue(VAR_AZIMUT_CURRENT + 90 );
      GAU_AZIMUT.Set_background_color_bco(GREEN);
      TXT_AZIMUT.setText(BUFFER_AZ);
      TXT_AZIMUT.Set_font_color_pco(GREEN);
      OVERLAP = 0;
    }
    else
    {
      GAU_AZIMUT.setValue(VAR_AZIMUT_CURRENT - 270 );
      TXT_AZIMUT.setText(BUFFER_AZ);
      if (VAR_AZIMUT_CURRENT > 360 && VAR_AZIMUT_CURRENT <= 450) {
        ser_print_azimut();
        GAU_AZIMUT.Set_background_color_bco(RED);
        TXT_AZIMUT.Set_font_color_pco(RED);
        OVERLAP = 1;
      }
      else
      {
        GAU_AZIMUT.Set_background_color_bco(GREEN);
        TXT_AZIMUT.Set_font_color_pco(GREEN);
        OVERLAP = 0;
      }
    }
  }
}
void rotazione_CW() {
  dbSerialPrintln("E' stata richiamata la funzione rotazione_CW()");
  delay(10);
  digitalWrite( RELE_CW, HIGH);
}

void rotazione_CCW() {
  dbSerialPrintln("|VOID rotazione_CCW()");
  delay(10);
  digitalWrite( RELE_CCW, HIGH);
}

void rotazione_UP() {
  delay(10);
  digitalWrite( RELE_UP, HIGH);
}

void rotazione_DOWN() {
  int  previusMillis = 0;
  unsigned long  currentMillis = millis();
  if (currentMillis - previusMillis > 10); {
    previusMillis = currentMillis;
    digitalWrite( RELE_DOWN, HIGH);
  }
}

void elevaz_stop()  {
  digitalWrite( RELE_UP, LOW);
  digitalWrite( RELE_DOWN, LOW);
}

void azimut_stop() {
  digitalWrite( RELE_CCW, LOW);
  digitalWrite( RELE_CW, LOW);
}

void emergency() {
  int previusMillis = 0;
  for (int X = 8; X <= 11; X++) {
    unsigned long  currentMillis = millis();
    if (currentMillis - previusMillis > 10); {
      previusMillis = currentMillis;
      digitalWrite( X, LOW );
    }
  }
}
