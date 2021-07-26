#include <Arduino.h>
#include "../pinout.h"
#include "ppm.h"

bool ppmState = 0;
int currentChannel = 0;

void startPPM () {
  currentChannel = 0;
  ppmState = 0;
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
}

void processPPM () {
  if (currentChannel < 6) {
    if (ppmState) {
      TCNT1 = 65536 - SERVO_MAX;
      digitalWrite(PPM_OUT, MARK);
      currentChannel++;
    }
    else {
      TCNT1 = 65536 - (SERVO_MIN/4);
      digitalWrite(PPM_OUT, SPACE);
    }
    ppmState = !ppmState;
  }
  else {
    TIMSK1 = 0;   // disable timer overflow interrupt
    digitalWrite(PPM_OUT, SPACE);
  }
}
