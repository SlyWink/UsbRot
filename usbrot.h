#define PIN_ENCODEUR1 PB3
#define PIN_ENCODEUR2 PB0
  #define MSK_ENCODEUR (_BV(PIN_ENCODEUR1)|_BV(PIN_ENCODEUR2))
#define ADC_BOUTONS ADC2

#define STAT_ROTATION 0b00001
#define STAT_DROITE   0b00010
#define STAT_BOUTON1  0b00100
#define STAT_BOUTON2  0b01000
#define STAT_BOUTON3  0b10000

static int8_t  g_rotate = 0 ;
