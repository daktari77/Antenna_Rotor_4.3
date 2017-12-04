void rotazione() {
  if (0 <= VAR_AZIMUT_CURRENT && VAR_AZIMUT_CURRENT < 180) {
    if (VAR_AZIMUT_CURRENT < VAR_AZIMUT_TARGET) {
      dbSerialPrint("TARGET = ");
      dbSerialPrintln( VAR_AZIMUT_TARGET );
      dbSerialPrint("CURRENT= ");
      dbSerialPrintln(VAR_AZIMUT_CURRENT);
      dbSerialPrint("DIFF= ");
      dbSerialPrintln(VAR_AZIMUT_TARGET - VAR_AZIMUT_CURRENT);
      AZIMUT_ROTAZIONE = CCW;

    }
    else {
      dbSerialPrint("TARGET = ");
      dbSerialPrintln( VAR_AZIMUT_TARGET );
      dbSerialPrint("CURRENT= ");
      dbSerialPrintln(VAR_AZIMUT_CURRENT);
      dbSerialPrint("DIFF= ");
      dbSerialPrintln(VAR_AZIMUT_CURRENT - VAR_AZIMUT_TARGET);
      AZIMUT_ROTAZIONE = CW;
    }
  }
  else if (VAR_AZIMUT_CURRENT < VAR_AZIMUT_TARGET) {
    dbSerialPrint("TARGET = ");
    dbSerialPrintln( VAR_AZIMUT_TARGET );
    dbSerialPrint("CURRENT= ");
    dbSerialPrintln(VAR_AZIMUT_CURRENT);
    dbSerialPrint("DIFF= ");
    dbSerialPrintln(VAR_AZIMUT_TARGET - VAR_AZIMUT_CURRENT);
    AZIMUT_ROTAZIONE = CCW;

  }
  else {
    dbSerialPrint("TARGET = ");
    dbSerialPrintln( VAR_AZIMUT_TARGET );
    dbSerialPrint("CURRENT= ");
    dbSerialPrintln(VAR_AZIMUT_CURRENT);
    dbSerialPrint("DIFF= ");
    dbSerialPrintln(VAR_AZIMUT_CURRENT - VAR_AZIMUT_TARGET);
    AZIMUT_ROTAZIONE = CW;
  }

  /*
    if (180 <= VAR_AZIMUT_CURRENT && VAR_AZIMUT_CURRENT < 270) {
      if (90 <= VAR_AZIMUT_TARGET && VAR_AZIMUT_TARGET < 360) {
        if (VAR_AZIMUT_CURRENT < VAR_AZIMUT_TARGET) {
          dbSerialPrint("TARGET = ");
          dbSerialPrintln( VAR_AZIMUT_TARGET );
          dbSerialPrint("CURRENT= ");
          dbSerialPrintln(VAR_AZIMUT_CURRENT);
          dbSerialPrint("DIFF= ");
          dbSerialPrintln(VAR_AZIMUT_TARGET - VAR_AZIMUT_CURRENT);
          AZIMUT_ROTAZIONE = CCW;

        }
        else {
          dbSerialPrint("TARGET = ");
          dbSerialPrintln( VAR_AZIMUT_TARGET );
          dbSerialPrint("CURRENT= ");
          dbSerialPrintln(VAR_AZIMUT_CURRENT);
          dbSerialPrint("DIFF= ");
          dbSerialPrintln(VAR_AZIMUT_CURRENT - VAR_AZIMUT_TARGET);
          AZIMUT_ROTAZIONE = CW;
        }
      }
    }
  */
} //Chiusura void


void azimut_current() {
  /*
     Set puntatore OK
     Set colore puntatore FAIL
     set TXT_OVERLAP OK
     set TXT_AZIMUT txt OK
     set TXT_AZIMUT color OK
  */
  VAR_AZIMUT_CURRENT = map(analogRead(SENS_POT_AZIMUT), 0, 1023, 0, 450); //mappo il valore letto su A0
  itoa(VAR_AZIMUT_CURRENT, BUFFER, 10);

  if (VAR_AZIMUT_CURRENT >= 0 && VAR_AZIMUT_CURRENT <= 270) {
    GAU_AZIMUT.setValue(VAR_AZIMUT_CURRENT + 90 );
    TXT_AZIMUT.setText(BUFFER);
    TXT_AZIMUT.Set_font_color_pco(GREEN);

    r0.setValue(0);
    OVERLAP = 0;
  }
  else
  {
    GAU_AZIMUT.setValue(VAR_AZIMUT_CURRENT - 270 );
    TXT_AZIMUT.setText(BUFFER);
    if (VAR_AZIMUT_CURRENT > 360 && VAR_AZIMUT_CURRENT <= 450) {
      r0.setValue(1);
      TXT_AZIMUT.Set_font_color_pco(RED);
      OVERLAP = 1;
    }
    else
    {
      GAU_AZIMUT.Set_background_color_bco(GREEN);
      TXT_OVERLAP.Set_font_color_pco(GREEN);
      TXT_AZIMUT.Set_font_color_pco(GREEN);
      r0.setValue(0);
      OVERLAP = 0;
    }
  }
}

void azimut_stop()  {
  digitalWrite( RELE_UP, LOW);
  digitalWrite( RELE_DOWN, LOW);
}

void elevaz_stop()  {
  digitalWrite( RELE_CCW, LOW);
  digitalWrite( RELE_CW, LOW);
}
void elevaz_attuale() {
  VAR_ELEVAZ_CURRENT = map(analogRead(SENS_POT_ELEVAZ), 0, 1023, 0, 180); //mappo il valore letto su A1
  itoa(VAR_ELEVAZ_CURRENT, BUFFER, 3);
  GAU_ELEVAZ.setValue(VAR_ELEVAZ_CURRENT );
  TXT_ELEVAZ.setText(BUFFER);
}

void rotazione_CW() {
  delay(10);
  digitalWrite( RELE_CW, HIGH);
}

void rotazione_CCW() {
  delay(10);
  digitalWrite( RELE_CCW, HIGH);
}

void ser_print_azimut() { //Serial print posizione corrente e target
  dbSerialPrint("TARGET = ");
  dbSerialPrintln( VAR_AZIMUT_TARGET );
  dbSerialPrint("CURRENT= ");
  dbSerialPrintln(VAR_AZIMUT_CURRENT);
}
