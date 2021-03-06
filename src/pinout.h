#define OLED_SCL SCL
#define OLED_SDA SDA

#define DEBUG_OUT 10
#define PPM_OUT   2
#define TX_POWER  3
#define BIND      4

#define DEBUG_OUT_HIGH    PORTB=PORTB|0x04
#define DEBUG_OUT_LOW     PORTB=PORTB&0xfb
#define DEBUG_OUT_TOGGLE  PORTB=PORTB^0x04

#define PPM_OUT_MARK      PORTD=PORTD&0xfb
#define PPM_OUT_SPACE     PORTD=PORTD|0x04

#define JOYSTICK0 14 /* A0 */
#define JOYSTICK1 15 /* A1 */
#define JOYSTICK2 16 /* A2 */
#define JOYSTICK3 17 /* A3 */

#define BUTTON1   9
#define BUTTON2   8

#define BIND_ON   0
#define BIND_OFF  1

#define POWER_ON  1
#define POWER_OFF 0

#define MARK      0
#define SPACE     1
