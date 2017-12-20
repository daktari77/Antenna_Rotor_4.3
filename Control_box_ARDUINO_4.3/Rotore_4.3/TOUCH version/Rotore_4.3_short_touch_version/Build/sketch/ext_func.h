void ser_print_azimut() { //Serial print posizione corrente e target
  dbSerialPrintln("E' stata richiamata la funzione ser_print_azimut()");
  dbSerialPrintln("____________________________");
  dbSerialPrint("|TARGET = ");
  dbSerialPrintln(AZIMUT_TARGET);
  dbSerialPrint("|LAST TARGET = ");
  dbSerialPrintln(VAR_AZIMUT_LAST_TARGET );
  dbSerialPrint("|CURRENT= ");
  dbSerialPrintln(AZIMUT_CURRENT);
  dbSerialPrint("|DIFF(function)= ");
  AZ_MAX = max(AZIMUT_CURRENT , AZIMUT_TARGET);
  AZ_MIN = min(AZIMUT_CURRENT , AZIMUT_TARGET);
  EL_MAX = max(ELEVAZ_CURRENT , VAR_ELEVAZ_TARGET);
  EL_MIN = min(ELEVAZ_CURRENT , VAR_ELEVAZ_TARGET);
  dbSerialPrintln(AZ_MAX - AZ_MIN);
  dbSerialPrintln("____________________________");
}

void rotazione() {
  dbSerialPrintln("E' stata richiamata la funzione  rotazione() ");

  if (0 <= AZIMUT_CURRENT && AZIMUT_CURRENT < 180) { // CURRENT NEL PRIMO E SECONDO QUADRANTE
    if (AZIMUT_CURRENT < AZIMUT_TARGET) {
      dbSerialPrintln("Rotazione CCW in corso ");
      AZIMUT_ROTAZIONE = "CCW";
    }
    else {
      dbSerialPrintln("Rotazione CW in corso ");
      AZIMUT_ROTAZIONE = "CW";
    }
  }
  else if (180 <= AZIMUT_CURRENT && AZIMUT_CURRENT < 270) {
    if (0 <= AZIMUT_TARGET && AZIMUT_TARGET < 90) {
      if ( (AZIMUT_TARGET + 360 - AZIMUT_CURRENT) < (AZIMUT_CURRENT - AZIMUT_TARGET) ) {
        AZIMUT_TARGET = (AZIMUT_TARGET + 360);
        AZIMUT_ROTAZIONE = "CCW";
      }
      else if ((AZIMUT_TARGET + 360 - AZIMUT_CURRENT) > (AZIMUT_CURRENT - AZIMUT_TARGET))
      {
        AZIMUT_ROTAZIONE = "CW";
      }
    }
   }
  else if (270 <= AZIMUT_CURRENT && AZIMUT_CURRENT < 360) {
    if (0 <= AZIMUT_TARGET && AZIMUT_TARGET < 90) {
      AZIMUT_TARGET = AZIMUT_TARGET + 360;
      AZIMUT_ROTAZIONE = "CW";
    }

    if (AZIMUT_CURRENT < AZIMUT_TARGET) {
      dbSerialPrintln("Rotazione CCW in corso ");
      AZIMUT_ROTAZIONE = "CCW";
    }
    else {
      dbSerialPrintln("Rotazione CW in corso ");
      AZIMUT_ROTAZIONE = "CW";
    }
  }
  else if (360 <= AZIMUT_CURRENT && AZIMUT_CURRENT < 450) {
    if (0 <= AZIMUT_TARGET && AZIMUT_TARGET < 90) {
      AZIMUT_TARGET = AZIMUT_TARGET + 360;
      if (AZIMUT_CURRENT < AZIMUT_TARGET) {
        dbSerialPrintln("Rotazione CCW in corso ");
        AZIMUT_ROTAZIONE = "CCW";
      }
      else {
        dbSerialPrintln("Rotazione CW in corso ");
        AZIMUT_ROTAZIONE = "CW";
      }
    }
    else {
      if (AZIMUT_CURRENT < AZIMUT_TARGET) {
        dbSerialPrintln("Rotazione CCW in corso ");
        AZIMUT_ROTAZIONE = "CCW";
      }
      else {
        dbSerialPrintln("Rotazione CW in corso ");
        AZIMUT_ROTAZIONE = "CW";
      }
    }
  }
}  //Chiusura void rotazione()

void elevaz_current() {
  dbSerialPrintln("E' stata richiamata la funzione  elevaz_current()");
  ELEVAZ_CURRENT = map(analogRead(SENS_POT_ELEVAZ), 0, 1023, 0, 180); //mappo il valore letto su A1
  itoa(ELEVAZ_CURRENT, BUFFER_EL, 10);
  GAU_ELEVAZ.setValue(ELEVAZ_CURRENT );
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
  //int previusMillis = 0;
  AZIMUT_CURRENT = map(analogRead(SENS_POT_AZIMUT), 0, 1023, 0, 450); //mappo il valore letto su A0
  itoa(AZIMUT_CURRENT, BUFFER_AZ, 10); //CONVERTE LA POSIZIONE IN STRINGA DA INVIARE A TXT_AZIMUT
  //unsigned long  currentMillis = millis();
  //if (currentMillis - previusMillis > 200) { //AGGIORNA IL VALORE OGNI 100ms (DA MODIFICARE ALL'OCCORRENZA)
  //previusMillis = currentMillis;
  if (AZIMUT_CURRENT >= 0 && AZIMUT_CURRENT <= 270) {
    ser_print_azimut();
    GAU_AZIMUT.setValue(AZIMUT_CURRENT + 90 );
    GAU_AZIMUT.Set_background_color_bco(NORMAL);
    TXT_AZIMUT.setText(BUFFER_AZ);
    TXT_AZIMUT.Set_font_color_pco(NORMAL);
    //OVERLAP = 0;
  }
  else
  {
    GAU_AZIMUT.setValue(AZIMUT_CURRENT - 270 );
    TXT_AZIMUT.setText(BUFFER_AZ);
    if (AZIMUT_CURRENT > 360 && AZIMUT_CURRENT <= 450) {
      ser_print_azimut();
      GAU_AZIMUT.Set_background_color_bco(OVERLAP);
      TXT_AZIMUT.Set_font_color_pco(OVERLAP);
      //OVERLAP = 1;
    }
    else
    {
      GAU_AZIMUT.Set_background_color_bco(NORMAL);
      TXT_AZIMUT.Set_font_color_pco(NORMAL);
      //OVERLAP = 0;
    }
  }
  //}
}
void rotazione_CW() {
  dbSerialPrintln("E' stata richiamata la funzione rotazione_CW()");
  int  previusMillis = 0;
  unsigned long  currentMillis = millis();
  if (currentMillis - previusMillis > 10); {
    previusMillis = currentMillis;
    digitalWrite( RELE_CW, HIGH);
  }
}

void rotazione_CCW() {
  dbSerialPrintln("|VOID rotazione_CCW()");
  int  previusMillis = 0;
  unsigned long  currentMillis = millis();
  if (currentMillis - previusMillis > 10); {
    previusMillis = currentMillis;
    digitalWrite( RELE_CCW, HIGH);
  }
}

void rotazione_UP() {
  int  previusMillis = 0;
  unsigned long  currentMillis = millis();
  if (currentMillis - previusMillis > 10); {
    previusMillis = currentMillis;
    digitalWrite( RELE_UP, HIGH);
  }
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
