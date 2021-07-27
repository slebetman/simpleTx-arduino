#include "src/pinout.h"
#include "src/drivers/ppm.h"
#include "src/drivers/serial-console.h"

int tickTracker = 0;

void setup() {
	// put your setup code here, to run once:
	pinMode(DEBUG_OUT, OUTPUT);
	initConsole();
	initPPM();
}

ISR(TIMER1_OVF_vect) {
	processPPM();
}

void loop() {

	int now = millis();

	if (now-tickTracker >= 20) {
		tickTracker = now;

		startPPM();
		DEBUG_OUT_TOGGLE;
		return;
	}

	if (processConsole()) return;
}
