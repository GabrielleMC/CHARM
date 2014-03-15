# Client makefile

CC=g++
CFLAGS=-Wall -g
LDFLAGS= `mysql_config --cflags` `mysql_config --libs`
SOURCES=client.cpp ../common/pugixml.cpp ../common/device.cpp
EXECUTABLE=client
OBJECTS=$(SOURCES:.o=.cpp)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
.pp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *~ $(EXECUTABLE) *.txt xml_*
