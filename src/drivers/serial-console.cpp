#include <Arduino.h>

char buffer[20];
int bufptr = 0;

int x = 0;

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
		return 1;
	}
	return 0;
}