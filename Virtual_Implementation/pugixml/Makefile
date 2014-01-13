# SelectServer makefile

CC=g++
CFLAGS=-Wall -g
LDFLAGS=
SOURCES=testxml.cpp pugixml.cpp device.cpp
EXECUTABLE=testxml
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.pp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *~ $(EXECUTABLE) *.txt xml_*
