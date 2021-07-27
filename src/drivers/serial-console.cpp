#include <Arduino.h>
#include "ppm.h"

char buffer[20];
int bufptr = 0;

char chan = 0;

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

void initConsole () {
	Serial.begin(9600);
	buffer[19] = 0;
}

char processConsole () {
	char input;
	char* cmd;

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
				Serial.println("hello     : say hi to me");
				Serial.println("val       : get current values");
				Serial.println("chan <x>  : set channel to configure");
				Serial.println("inc       : increment channel value");
				Serial.println("dec       : decrement channel value");
				Serial.println("help      : print this help");
				Serial.println("");
			}
			else if (strncmp(cmd, "chan", 4) == 0) {
				chan = cmd[5] - '0';
				if (chan < 0 || chan >= 6) {
					chan = 0;
					Serial.print("invalid channel!");
				}
				else {
					Serial.print("selected channel: ");
					Serial.println((short)chan);
				}
			}
			else if (strncmp(cmd, "inc", 20) == 0) {
				output[chan] += 3200;
				Serial.println(output[chan]);
			}
			else if (strncmp(cmd, "dec", 20) == 0) {
				output[chan] -= 3200;
				Serial.println(output[chan]);
			}
			else if (strncmp(cmd, "val", 20) == 0) {
				for (char i=0;i<6;i++) {
					if (i>0) Serial.print(", ");
					Serial.print(chan);
					Serial.print(":");
					Serial.print(output[chan]);
				}
				Serial.println("");
			}
			else if (strlen(cmd) == 0) {
				// do nothing
			}
			else {
				Serial.print("sorry, unknown command: ");
				Serial.println(cmd);
			}

			for (char i=0;i<20;i++) {
				buffer[i] = 0;
			}

			bufptr = 0;
		}
		return 1;
	}
	return 0;
}