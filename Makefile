BOARD  =  arduino:avr:pro
PORT   = $(shell echo /dev/ttyUSB* | cut -d " " -f1)

SOURCES = $(shell ls *.ino src/*/*.c src/*/*.cpp)
HEADERS = $(shell ls src/*.h src/*/*.h)

all: $(SOURCES) $(HEADERS)
	arduino-cli compile -b $(BOARD) --clean

install: all
	arduino-cli upload -b $(BOARD) -p $(PORT)
