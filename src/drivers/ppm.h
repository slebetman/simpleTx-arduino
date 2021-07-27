#ifdef __cplusplus
 extern "C" {
#endif

#define SERVO_MIN 16000
#define SERVO_MAX 32000
#define SERVO_RANGE 1600 /* (SERVO_MAX-SERVO_MIN) */
#define SERVO_CENTER 24000 /* ((SERVO_MIN+SERVO_MAX)/2) */

extern short output[6];

extern void processPPM ();
extern void startPPM ();
extern void initPPM ();

#ifdef __cplusplus
}
#endif
