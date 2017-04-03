#include "usbrot.h"

#define SERIAL_DEBUG_DDR DDRB
#define SERIAL_DEBUG_PORT PORTB
#define SERIAL_DEBUG_PIN PB4

#include "dbginclude.c"


//ISR(PCINT0_vect) {
ISR(PCINT0_vect,ISR_NOBLOCK) {
/*
  static uint8_t l_previous = 0 ;
  static uint8_t l_pinb ;


  l_pinb = PINB ;
  if (l_pinb & _BV(PIN_ENCODEUR2)) {
    if (l_previous & _BV(PIN_ENCODEUR1))  g_rotate-- ;
    else g_rotate++ ;
  } else {
    if (l_previous & _BV(PIN_ENCODEUR1))  g_rotate++ ;
    else g_rotate-- ;
  }
  l_previous = l_pinb ;
*/
  static uint8_t l_prevpina = 0 ;
  uint8_t l_currpinb ;

  l_currpinb = (PINB & _BV(PIN_ENCODEUR2)) ? 1 : 0 ;
  if (l_currpinb ^ l_prevpina) g_rotate-- ; else g_rotate++ ;
  l_prevpina = (PINB & _BV(PIN_ENCODEUR1)) ? 1 : 0 ;
}


ISR(ADC_vect,ISR_NOBLOCK) {
}


void Init_Fake_Mouse(void) {
  DDRB &= ~MSK_ENCODEUR ; // Input
  PORTB |= MSK_ENCODEUR ; // Pull-up
  GIMSK |= _BV(PCIE) ;
  PCMSK |= _BV(PCINT3) | _BV(PCINT0) ;
  Serial_Debug_Init() ;
}
