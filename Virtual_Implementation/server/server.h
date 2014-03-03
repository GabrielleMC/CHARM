/*
 * A TCP server that accepts multiple connections from clients
 * The TCP server accepts xml messages from devices and logs their values
 * For use in CPSC 441 lectures
 * Instructor: Prof. Mea Wang
 */
 
 
#include <iostream>
#include <fstream>
#include <sys/socket.h> // for socket(), connect(), send(), and recv()
#include <arpa/inet.h>  // for sockaddr_in and inet_addr()
#include <stdlib.h>     // for atoi() and exit()
#include <string.h>     // for memset()
#include <unistd.h>     // for close()
#include "netdb.h"
#include "../common/device.h"
#include <vector>
#include "../common/pugixml.hpp"

#define DEBUG 1
#define PORT 55555

using namespace std;

const int BUFFERSIZE = 1500;   // Size the message buffers (1500 bytes)
const int MAXPENDING = 10;    // Maximum pending connections

fd_set recvSockSet;   // The set of descriptors for incoming connections
int maxDesc = 0;      // The max descriptor
bool terminated = false;    

void initServer (int&, int);
void processTCPSockets (fd_set);
void sendData (int, char[], int);
void receiveData (int, char[], int&);
struct in_addr getIP(const char* hostname);
//int setupTcpConnection(HttpHeader);
string listFiles ();
//RequestMap requestMap;
int main(int argc, char *argv[]);
