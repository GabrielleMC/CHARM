# SelectServer makefile

CC=g++
CFLAGS=-Wall
LDFLAGS=
SOURCES=client.cpp device.cpp pugixml.cpp
EXECUTABLE=client
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.pp.o:
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -rf *.o *~
