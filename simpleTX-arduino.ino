#include "src/drivers/ppm.h"
#include "src/pinout.h"

char buffer[20];
int bufptr;

int x;
int tickTracker = 0;
int tick = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bufptr = 0;
  buffer[19] = 0;
  pinMode(DEBUG_OUT, OUTPUT);
  pinMode(PPM_OUT, OUTPUT);
  pinMode(TX_POWER, OUTPUT);
  pinMode(BIND, OUTPUT);

  digitalWrite(BIND, HIGH);
  digitalWrite(TX_POWER, LOW);

  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 65536 - SERVO_MIN;
  TCCR1B |= (1 << CS10);    // 1:1 prescaler
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER1_OVF_vect) {
  processPPM();
}


char* trimn(char *str, int n) {
  char *ret = str;

  if (*ret == '\n' || *ret == '\r') {
    n--;
    ret++;
  }

  for (int i=0;i<n;i++) {
    if (ret[i] == '\n' || ret[i] == '\r') {
      ret[i] = 0;
      break;
    }
  }

  return ret;
}

void loop() {
  char input;
  char* cmd;

  int now = millis();

  if (tickTracker != now) {
    tick += now-tickTracker;
    tickTracker = now;

    if (tick >= 20) {
      tick = 0;
      startPPM();
      digitalWrite(DEBUG_OUT, !digitalRead(DEBUG_OUT));
    }
  }
  
  if ( Serial.available() ) {
    input = Serial.read();
    buffer[bufptr] = input;
    if (bufptr < 19) {
      bufptr++;
    }

    if (input == '\n' || input == '\r') {
      cmd = trimn(buffer, 20);

      if (strncmp(cmd, "hello", 20) == 0) {
        Serial.println("hi there!");
      }
      else if (strncmp(cmd, "help", 20) == 0) {
        Serial.println("hello  : say hi to me");
        Serial.println("val    : get current value");
        Serial.println("inc    : increment value");
        Serial.println("dec    : decrement value");
        Serial.println("help   : print this help");
        Serial.println("");
      }
      else if (strncmp(cmd, "inc", 20) == 0) {
        x++;
        Serial.println(x);
      }
      else if (strncmp(cmd, "dec", 20) == 0) {
        x--;
        Serial.println(x);
      }
      else if (strncmp(cmd, "val", 20) == 0) {
        Serial.println(x);
      }
      else {
        Serial.print("sorry, unknown command: ");
        Serial.println(cmd);
      }

      bufptr = 0;
    }
  }
}
