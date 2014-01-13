/*
 * A simple TCP client that sends messages to a server and display the message
   from the server. 
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
#include <stdio.h>      // for fgets()
#include "device.h"

#define PORT 55555
//#define IP_ADDRESS "127.0.0.1"

const int BUFFERSIZE = 1500;   // Size the message buffers

int main(int argc, char *argv[])
{
        char inBuffer[BUFFERSIZE];       // Buffer for the message from the server
        int bytesRecv;                   // Number of bytes received
        unsigned int fileSize;                    // Size of the file after being transferred
        bool terminate = false;
        char* server_ip;

        char outBuffer[BUFFERSIZE];      // Buffer for message to the server
        int msgLength;                   // Length of the outgoing message
        int bytesSent;                   // Number of bytes sent
        bool receivingFile = false;      // flag to indicate if currently receiving a file
        std::ofstream outFile;
        std::string fileName;
        
        Device device = Device();
        srandom(time(NULL));
        pugi::xml_document doc;
        std::stringstream ss;
        
        if(argc < 2) {
                std::cout << "Usage = " << argv[0] << " <server ip> <device_file (optional)>" << std::endl;
                return -1;
        
        } else {
                server_ip = argv[1];
                
                if(argv[2] != NULL) {
                        pugi::xml_parse_result result = doc.load_file(argv[2]);
                        if(result) {
                                device.process_confirm_xml(doc);
                        }
                }
        }

        ss.str(std::string());
        doc.reset();
        
        for(int n = 0; n < 5; n++) {
                int sock;                        // A socket descriptor
                struct sockaddr_in serverAddr;   // Address of the server
                 // Create a TCP socket
                // * AF_INET: using address family "Internet Protocol address"
                // * SOCK_STREAM: Provides sequenced, reliable, bidirectional, connection-mode byte streams.
                // * IPPROTO_TCP: TCP protocol
                if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
                        std::cout << "socket() failed" << std::endl;
                        exit(1);
                }

                // Free up the port before binding
                // * sock: the socket just created
                // * SOL_SOCKET: set the protocol level at the socket level
                // * SO_REUSEADDR: allow reuse of local addresses
                // * &yes: set SO_REUSEADDR on a socket to true (1)
                // * sizeof(int): size of the value pointed by "yes"
                int yes = 1;
                if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0) {
                        std::cout << "setsockopt() failed" << std::endl;
                        exit(1);
                }

                // Initialize the server information
                // Note that we can't choose a port less than 1023 if we are not privileged users (root)
                memset(&serverAddr, 0, sizeof(serverAddr));         // Zero out the structure
                serverAddr.sin_family = AF_INET;                    // Use Internet address family
                serverAddr.sin_port = htons(PORT);         // Server port number
                serverAddr.sin_addr.s_addr = inet_addr(server_ip);    // Server IP address

                // Connect to the server
                // * sock: the socket for this connection
                // * serverAddr: the server address
                // * sizeof(*): the size of the server address
                if (connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
                        std::cout << "connect() failed" << std::endl;
                        exit(1);
                }
                
                device.set_battery(100);
                std::cout << "Device " << device.get_uid() << " booted up and is at full battery" << std::endl;
                
                int i = 0;
                while((device.get_battery() > 0) && (device.get_state() != SHUTDOWN)) {
                        time_t t = time(NULL);
                        int r = random() % 4;
                        device.set_battery(device.get_battery() - r);
                        i += r;
                        device.add_reading(t, i);
                        device.print();
                        
                        while (!terminate) {
                                std::stringstream st;
                                device.create_readings_xml(doc, 5);
                                
                                doc.save(st);
                                doc.reset();
                                
                                strcpy(outBuffer, st.str().c_str());
                                
                                st.str(std::string());
                        
                                msgLength = strlen(outBuffer);

                                // Send the message to the server when not receiving a file
                                bytesSent = send(sock, (char *) &outBuffer, msgLength, 0);
                                if (bytesSent < 0 || bytesSent != msgLength) {
                                        std::cout << "error in sending" << std::endl;
                                        exit(1);
                                }
                                
                                // Receive the response from the server
                                bytesRecv = recv(sock, (char *) &inBuffer, BUFFERSIZE, 0);
                                // Check for connection close (0) or errors (< 0)
                                if (bytesRecv <= 0) {
                                        std::cout << "recv() failed, or the connection is closed. " << std::endl;
                                        exit(1); 
                                }
                                
                                // output to screen if not receiving a file
                                //std::cout << "Server: " << inBuffer << std::endl;
                                
                                st << inBuffer;
                                doc.load(st);
                                device.process_confirm_xml(doc);
                                doc.save_file("client_settings.xml");
                                doc.reset();
                                st.str(std::string());
                                
                                // Clear the buffers
                                memset(&outBuffer, 0, BUFFERSIZE);
                                memset(&inBuffer, 0, BUFFERSIZE);
                                
                                if(device.num_readings() == 0)
                                        terminate = true;
                        }
                        device.save_readings();
                        sleep(device.get_frequency());
                        terminate = false;
                }

                std::cout << "Client shutting down, battery = " << device.get_battery()  << std::endl;
                
                // Close the socket
                close(sock);
                int nap = random() % 60;
                std::cout << "Battery will be replaced after " << nap << " seconds" << std::endl;
                sleep(nap);
                
        }
        exit(0);
}

