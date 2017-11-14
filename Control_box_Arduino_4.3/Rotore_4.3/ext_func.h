void azimut_attuale() {
  /*
     Set puntatore OK
     Set colore puntatore FAIL
     set TXT_OVERLAP OK
     set TXT_AZIMUT txt OK
     set TXT_AZIMUT color OK
  */
  VAR_AZIMUT_CURRENT = map(analogRead(SENS_POT_AZIMUT), 0, 1023, 0, 450); //mappo il valore letto su A0
  //uint32_t VAR_GAUGE_AZIMUT = map(analogRead(0), 0, 1023, 0, 360);
  itoa(VAR_AZIMUT_CURRENT, BUFFER, 10);

  if (VAR_AZIMUT_CURRENT >= 0 && VAR_AZIMUT_CURRENT <= 270) {
    GAU_AZIMUT.setValue(VAR_AZIMUT_CURRENT + 90 );
    GAU_AZIMUT.Set_background_color_bco(GREEN);
    TXT_OVERLAP.Set_font_color_pco(0);
    TXT_AZIMUT.setText(BUFFER);
    TXT_AZIMUT.Set_font_color_pco(GREEN);
  }
  else
  {
    GAU_AZIMUT.setValue(VAR_AZIMUT_CURRENT - 270 );
    TXT_AZIMUT.setText(BUFFER);
    if (VAR_AZIMUT_CURRENT > 360 && VAR_AZIMUT_CURRENT <= 450) {
      GAU_AZIMUT.Set_background_color_bco(RED);
      TXT_OVERLAP.Set_font_color_pco(RED);
      TXT_AZIMUT.Set_font_color_pco(RED);
    }
    else
    {
      GAU_AZIMUT.Set_background_color_bco(GREEN);
      TXT_OVERLAP.Set_font_color_pco(GREEN);
      TXT_AZIMUT.Set_font_color_pco(GREEN);
    }
  }
}

void elevaz_attuale() {

  VAR_ELEVAZ_CURRENT = map(analogRead(SENS_POT_ELEVAZ), 0, 1023, 0, 450); //mappo il valore letto su A1
  itoa(VAR_ELEVAZ_CURRENT, BUFFER, 3);
  GAU_ELEVAZ.setValue(VAR_ELEVAZ_CURRENT );
  TXT_ELEVAZ.setText(BUFFER);
}

void rotazione_CW() {
  while (VAR_AZIMUT_TARGET != VAR_AZIMUT_CURRENT) {
    digitalWrite( RELE_CCW, LOW );
    delay(10);
    digitalWrite( RELE_CW, HIGH);
  }
}

void rotazione_CCW() {
  while (VAR_AZIMUT_TARGET != VAR_AZIMUT_CURRENT) {
    digitalWrite( RELE_CW, LOW );
    delay(10);
    digitalWrite( RELE_CCW, HIGH);
  }
}

