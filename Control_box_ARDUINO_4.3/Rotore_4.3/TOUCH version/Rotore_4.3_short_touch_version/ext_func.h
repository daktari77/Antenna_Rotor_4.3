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
  dbSerialPrint("|analogRead =  ");
  dbSerialPrintln(analogRead(SENS_POT_AZIMUT));
  dbSerialPrint("|POT_MIN =  ");
  dbSerialPrintln(VAR_AZIMUT_MIN);
  dbSerialPrint("|POT_MAX =  ");
  dbSerialPrintln(VAR_AZIMUT_MAX * 4);
  dbSerialPrintln("____________________________");
  
}

void rotazione() {
  dbSerialPrintln("E' stata richiamata la funzione  rotazione() ");
  TXT_ROTAZIONE.Set_font_color_pco(NORMAL);
  if (0 <= AZIMUT_CURRENT && AZIMUT_CURRENT < 180) { // CURRENT NEL PRIMO E SECONDO QUADRANTE
    if (AZIMUT_CURRENT < AZIMUT_TARGET) {
      dbSerialPrintln("Rotazione CW in corso ");
      AZIMUT_ROTAZIONE = "CW";
    }
    else {
      dbSerialPrintln("Rotazione CCW in corso ");
      AZIMUT_ROTAZIONE = "CCW";
    }
  }
  else if (180 <= AZIMUT_CURRENT && AZIMUT_CURRENT < 270) {
    if (0 <= AZIMUT_TARGET && AZIMUT_TARGET < 90) {
      if ( (AZIMUT_TARGET + 360 - AZIMUT_CURRENT) < (AZIMUT_CURRENT - AZIMUT_TARGET) ) {
        AZIMUT_TARGET = (AZIMUT_TARGET + 360);
        AZIMUT_ROTAZIONE = "CW";
      }
      else if ((AZIMUT_TARGET + 360 - AZIMUT_CURRENT) > (AZIMUT_CURRENT - AZIMUT_TARGET))
      {
        AZIMUT_ROTAZIONE = "CCW";
      }
    }
  }
  else if (270 <= AZIMUT_CURRENT && AZIMUT_CURRENT < 360) {
    if (0 <= AZIMUT_TARGET && AZIMUT_TARGET < 90) {
      AZIMUT_TARGET = AZIMUT_TARGET + 360;
      AZIMUT_ROTAZIONE = "CCW";
    }

    if (AZIMUT_CURRENT < AZIMUT_TARGET) {
      dbSerialPrintln("Rotazione CW in corso ");
      AZIMUT_ROTAZIONE = "CW";
    }
    else {
      dbSerialPrintln("Rotazione CCW in corso ");
      AZIMUT_ROTAZIONE = "CCW";
    }
  }
  else if (360 <= AZIMUT_CURRENT && AZIMUT_CURRENT < 450) {
    if (0 <= AZIMUT_TARGET && AZIMUT_TARGET < 90) {
      AZIMUT_TARGET = AZIMUT_TARGET + 360;
      if (AZIMUT_CURRENT < AZIMUT_TARGET) {
        dbSerialPrintln("Rotazione CW in corso ");
        AZIMUT_ROTAZIONE = "CW";
      }
      else {
        dbSerialPrintln("Rotazione CCW in corso ");
        AZIMUT_ROTAZIONE = "CCW";
      }
    }
    else {
      if (AZIMUT_CURRENT < AZIMUT_TARGET) {
        dbSerialPrintln("Rotazione CCW in corso ");
        AZIMUT_ROTAZIONE = "CW";
      }
      else {
        dbSerialPrintln("Rotazione CCW in corso ");
        AZIMUT_ROTAZIONE = "CCW";
      }
    }
  }
}  //Chiusura void rotazione()


void rotazione_CW() {
  dbSerialPrintln("VOID rotazione_CW()");
  delay(DELAY_S);
  digitalWrite( RELE_CW, HIGH);
}

void rotazione_CCW() {
  dbSerialPrintln("VOID rotazione_CCW()");
  delay(DELAY_S);
  digitalWrite( RELE_CCW, HIGH);
}

void rotazione_UP() {
  delay(DELAY_S);
  digitalWrite( RELE_UP, HIGH);
}

void rotazione_DOWN() {
  delay(DELAY_S);
  digitalWrite( RELE_DOWN, HIGH);
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
  for (int X = 8; X <= 11; X++) {
    delay(DELAY_S);
    digitalWrite( X, LOW );
  }
}

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
  dbSerialPrintln("VOID azimut_current()");
  AZIMUT_CURRENT = map(analogRead(SENS_POT_AZIMUT), VAR_AZIMUT_MIN, VAR_AZIMUT_MAX, 0, 450); //mappo il valore letto su A0
  itoa(AZIMUT_CURRENT, BUFFER_AZ, 10); //CONVERTE LA POSIZIONE IN STRINGA DA INVIARE A TXT_AZIMUT
  if (AZIMUT_CURRENT >= 0 && AZIMUT_CURRENT <= 270) {
    ser_print_azimut();
    GAU_AZIMUT.setValue(AZIMUT_CURRENT + 90 );
    GAU_AZIMUT.Set_background_color_bco(NORMAL);
    TXT_AZIMUT.setText(BUFFER_AZ);
    TXT_AZIMUT.Set_font_color_pco(NORMAL);
    TXT_OVERLAP.Set_font_color_pco(SFONDO);
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
      TXT_OVERLAP.Set_font_color_pco(OVERLAP);
    }
    else
    {
      GAU_AZIMUT.Set_background_color_bco(NORMAL);
      TXT_AZIMUT.Set_font_color_pco(NORMAL);
      TXT_OVERLAP.Set_font_color_pco(SFONDO);
    }
  }
}

