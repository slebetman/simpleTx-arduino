#include <Arduino.h>
#include "../pinout.h"
#include "ppm.h"

bool ppmState = 0;
int currentChannel = 0;

void initPPM () {
	pinMode(PPM_OUT, OUTPUT);
	pinMode(TX_POWER, OUTPUT);
	pinMode(BIND, OUTPUT);

	digitalWrite(BIND, HIGH);
	digitalWrite(TX_POWER, HIGH);

	// initialize timer1
	noInterrupts();           // disable all interrupts
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 65536 - (SERVO_MIN/4);
	TCCR1B |= (1 << CS10);    // 1:1 prescaler
	TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
	interrupts();             // enable all interrupts
}

void startPPM () {
	currentChannel = 0;
	ppmState = 0;
	TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
}

void processPPM () {
	if (currentChannel < 6) {
		if (ppmState) {
			TCNT1 = 65536 - SERVO_CENTER;
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
