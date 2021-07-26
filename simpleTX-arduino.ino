#include "src/pinout.h"
#include "src/drivers/ppm.h"
#include "src/drivers/serial-console.h"

int tickTracker = 0;
int tick = 0;

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

	if (tickTracker != now) {
		tick += now-tickTracker;
		tickTracker = now;

		if (tick >= 20) {
			tick = 0;
			startPPM();
			digitalWrite(DEBUG_OUT, !digitalRead(DEBUG_OUT));
			return;
		}
	}

	if (processConsole()) return;
}
