# Client makefile

CC=g++
CFLAGS=-Wall -g
LDFLAGS= -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql
SOURCES=client.cpp ../common/pugixml.cpp ../common/device.cpp
EXECUTABLE=client
OBJECTS=$(SOURCES:.o=.cpp)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJECTS) -o $@
.pp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *~ $(EXECUTABLE) *.txt xml_*
