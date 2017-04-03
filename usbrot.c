#include "usbrot.h"

#define SERIAL_DEBUG_DDR DDRB
#define SERIAL_DEBUG_PORT PORTB
#define SERIAL_DEBUG_PIN PB4

#include "dbginclude.c"


ISR(PCINT0_vect,ISR_NOBLOCK) {
  static uint8_t l_prevpina = 0 ;
  uint8_t l_currpinb ;

  l_currpinb = (PINB & _BV(PIN_ENCODEUR2)) ? 1 : 0 ;
  if (l_currpinb ^ l_prevpina) g_rotate-- ; else g_rotate++ ;
  l_prevpina = (PINB & _BV(PIN_ENCODEUR1)) ? 1 : 0 ;
}


ISR(ADC_vect,ISR_NOBLOCK) {
}


#define Start_Conversion() ADCSRA |= _BV(ADSC)
#define Conversion_In_Progress() (ADCSRA & _BV(ADSC))


uint8_t Read_Buttons(void) {
  uint8_t l_adcl, l_adch ;

  l_adcl = ADCL ;
  l_adch = ADCH ;
  switch(l_adch) {
    case 1 :
      if (l_adcl >= 0xFB)      return BUTTON4 ;                 // 0x1FD
      else if (l_adcl >= 0xA8) return BUTTON1|BUTTON4 ;         // 0x1AA
      else if (l_adcl >= 0x98) return BUTTON2|BUTTON4 ;         // 0x19A
      else if (l_adcl >= 0x86) return BUTTON1|BUTTON2|BUTTON4 ; // 0x188
      else if (l_adcl >= 0x7D) return BUTTON3|BUTTON4 ;         // 0x17F
      else if (l_adcl >= 0x66) return BUTTON1|BUTTON3|BUTTON4 ; // 0x168
      else                     return BUTTON2|BUTTON3|BUTTON4 ; // 0x161
    case 2 :
      if (l_adcl >= 0xE0)      return BUTTON1 ;                 // 0x2E2
      else if (l_adcl >= 0xB0) return BUTTON2 ;                 // 0x2B2
      else if (l_adcl >= 0x7E) return BUTTON1|BUTTON2 ;         // 0x280
      else if (l_adcl >= 0x68) return BUTTON3 ;                 // 0x26A
      else if (l_adcl >= 0x2C) return BUTTON1|BUTTON3 ;         // 0x22E
      else if (l_adcl >= 0x1E) return BUTTON2|BUTTON3 ;         // 0x220
      else if (l_adcl >= 0x0D) return BUTTON1|BUTTON2|BUTTON3 ; // 0x20F
      else                     return BUTTON4 ;                 // 0x1FD+
    default :
      return 0x0000 ;
  }
}


void Init_Fake_Mouse(void) {
  // Coding rotator
  DDRB &= ~MSK_ENCODEUR ; // Input
  PORTB |= MSK_ENCODEUR ; // Pull-up
  GIMSK |= _BV(PCIE) ;
  PCMSK |= _BV(PCINT3) | _BV(PCINT0) ;
  // Analog 4 buttons pin
  ADMUX = _BV(MUX1) ; // ADC2
  ADCSRA = _BV(ADEN) ; // Enable 
  ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) ; // Prescaler 128
//  Serial_Debug_Init() ;
}
