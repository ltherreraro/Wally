
#ifndef USread
#define USread

/* The devicetree node identifier for the "led0" alias. */
#define ECHO_PIN5 DT_ALIAS(echo1)
#define TRIG_PIN6 DT_ALIAS(trig1)
#define ECHO_PIN7 DT_ALIAS(echo2)
#define TRIG_PIN8 DT_ALIAS(trig2)
#define ECHO_PIN9 DT_ALIAS(echo3)
#define TRIG_PIN10 DT_ALIAS(trig3)
#define ECHO_PIN18 DT_ALIAS(echo4)
#define TRIG_PIN26 DT_ALIAS(trig4)

void hola(void);
void getDistance(void);
void uscounter(uint8_t us);

#endif