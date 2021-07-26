# SimpleTX

Simple RC computer radio

## Setup

This projects uses arduino-cli. It is possible to build this with
Arduino IDE but you will not be able to edit most of the source
files. Use a normal IDE or code editor (VScode, Sublime etc.) and
use the Makefile provided to build (verify) and upload the program.

1. Download **arduino-cli** from https://github.com/arduino/arduino-cli/releases

2. Install it somewhere in your $PATH (eg. /usr/local/bin)

3. You may need to download or update board definitions. Run the following command:

        arduino-cli core install arduino:avr


## Usage

To build/verify the code:

    make

To upload the program to your Arduino:

    make install
