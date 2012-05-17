// Diese Beispiel zeigt die Anwendung des ADC eines ATmega169
// unter Verwendung der internen Referenzspannung von nominell 1,1V.
// Zur Anpassung an andere AVR und/oder andere Referenzspannungen
// siehe Erläuterungen in diesem Tutorial und im Datenblatt
 
/* ADC initialisieren */
void ADC_Init(void) {
 
  uint16_t result;
 
  // interne Referenzspannung als Refernz für den ADC wählen:
  ADMUX = (1<<REFS1) | (1<<REFS0);
  
  // Bit ADFR ("free running") in ADCSRA steht beim Einschalten
  // schon auf 0, also single conversion
  ADCSRA = (1<<ADPS1) | (1<<ADPS0);     // Frequenzvorteiler
  ADCSRA |= (1<<ADEN);                  // ADC aktivieren
 
  /* nach Aktivieren des ADC wird ein "Dummy-Readout" empfohlen, man liest
     also einen Wert und verwirft diesen, um den ADC "warmlaufen zu lassen" */
 
  ADCSRA |= (1<<ADSC);                  // eine ADC-Wandlung 
  while (ADCSRA & (1<<ADSC) ) {}        // auf Abschluss der Konvertierung warten
  /* ADCW muss einmal gelesen werden, sonst wird Ergebnis der nächsten
     Wandlung nicht übernommen. */
  result = ADCW;
}
 
/* ADC Einzelmessung */
void ADC_start( uint8_t channel )
{
  // Kanal waehlen, ohne andere Bits zu beeinflußen
  ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
  ADCSRA |= (1<<ADSC);            // eine Wandlung "single conversion"
}

uint16_t ADC_result() {
  while (ADCSRA & (1<<ADSC) ) {}  // auf Abschluss der Konvertierung warten
  return ADCW;                    // ADC auslesen und zurückgeben
}

