#include <Arduino.h>
#include "../pinout.h"
#include "ppm.h"

bool ppmState = 0;
char currentChannel = 0;
short servoGap;

short output[6];

void initPPM () {
	pinMode(PPM_OUT, OUTPUT);
	pinMode(TX_POWER, OUTPUT);
	pinMode(BIND, OUTPUT);

	digitalWrite(BIND, HIGH);
	digitalWrite(TX_POWER, HIGH);

	servoGap = 65536 - (SERVO_MIN/4);

	for (char i=0;i<6;i++) {
		output[i] = 65536 - SERVO_CENTER;
	}

	// initialize timer1
	noInterrupts();           // disable all interrupts
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = servoGap;
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
	if (ppmState) {
		TCNT1 = output[currentChannel];
		PPM_OUT_MARK;
		currentChannel++;
	}
	else {
		TCNT1 = servoGap;
		PPM_OUT_SPACE;
	}
	ppmState = !ppmState;

	if (currentChannel >= 6) {
		TIMSK1 = 0;   // disable timer overflow interrupt
		PPM_OUT_SPACE;
	}
}
