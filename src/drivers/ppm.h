#ifdef __cplusplus
 extern "C" {
#endif

#define SERVO_MIN 16000
#define SERVO_MAX 32000
#define SERVO_RANGE (SERVO_MAX-SERVO_MIN)
#define SERVO_CENTER ((SERVO_MIN+SERVO_MAX)/2)

extern void processPPM ();
extern void startPPM ();

#ifdef __cplusplus
}
#endif
