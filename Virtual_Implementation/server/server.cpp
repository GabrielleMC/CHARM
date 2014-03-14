/*
 * A TCP server that accepts multiple connections from clients
 * The TCP server accepts xml messages from devices and logs their values
 * For use in CPSC 441 lectures
 * Instructor: Prof. Mea Wang
 */
 
#include "server.h"
#define LOW_BATTERY 10
 
vector<Device>devices;
int device_exists(int test_uid);

int main(int argc, char *argv[])
{
        int tcpSock;                     // server tcp socket descriptor
        int clientSock;                  // client socket descriptor
        struct sockaddr_in clientAddr;   // address of the client

        struct timeval timeout = {0, 10};  // The timeout value for select()
        struct timeval selectTime;
        fd_set tempRecvSockSet;            // Temp. receive socket set for select()

        // Initilize the server
        initServer(tcpSock, PORT);

        // Clear the socket sets 
        FD_ZERO(&recvSockSet);

        // Add the listening sockets to the set
        FD_SET(tcpSock, &recvSockSet); 
        maxDesc = max(maxDesc, tcpSock);

        // Run the server until a "terminate" command is received)
        while (!terminated) {
                // copy the receive/send descriptors to the working set
                memcpy(&tempRecvSockSet, &recvSockSet, sizeof(recvSockSet));

                // Select timeout has to be reset every time before select() is
                // called, since select() may update the timeout parameter to
                // indicate how much time was left.
                selectTime = timeout;
                int ready = select(maxDesc + 1, &tempRecvSockSet, NULL, NULL, &selectTime);
                if (ready < 0) {
                    cout << "PS: select() failed" << endl;
                    break;
                }
				//insert status info and check if there are any new readings to insert into database
				for(unsigned int i = 0; i < devices.size(); i++){
					devices[i].update_db_status();
					if(devices[i].num_readings() != 0){
						//cout << "Readings found for device " << i;
						devices[i].update_db_readings();
					}
				}
                // Process new connection request, if any.
                if (FD_ISSET(tcpSock, &tempRecvSockSet)) {
                        // set the size of the client address structure
                        unsigned int size = sizeof(clientAddr);

                        // Establish a connection
                        if ((clientSock = accept(tcpSock, (struct sockaddr *) &clientAddr, &size)) < 0)
                                break;
                        cout << "PS: Accepted a connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << clientAddr.sin_port << endl;

                        // Add the new connection to the receive socket set
                        FD_SET(clientSock, &recvSockSet);
                        maxDesc = max(maxDesc, clientSock);
                }

                // Process tcp messages waiting at each ready socket
                else {
                        processTCPSockets(tempRecvSockSet);
                }
        }

        // Close the connections with the client
        for (int sock = 0; sock <= maxDesc; sock++) {
                if (FD_ISSET(sock, &recvSockSet))
                        close(sock);
        }
        // Close the server sockets
        close(tcpSock);
}

void initServer(int& tcpSock, int port)
{
        struct sockaddr_in serverAddr;   // address of the server

        // Create a TCP socket
        // * AF_INET: using address family "Internet Protocol address"
        // * SOCK_STREAM: Provides sequenced, reliable, bidirectional, connection-mode byte streams.
        // * IPPROTO_TCP: TCP protocol
        if ((tcpSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
                cout << "socket() failed (TCP)" << endl;
                exit(1);
        }

        // Free up the port before binding
        // * sock: the socket just created
        // * SOL_SOCKET: set the protocol level at the socket level
        // * SO_REUSEADDR: allow reuse of local addresses
        // * &yes: set SO_REUSEADDR on a socket to true (1)
        // * sizeof(int): size of the value pointed by "yes"
        int yes1 = 1;
        if (setsockopt(tcpSock, SOL_SOCKET, SO_REUSEADDR, &yes1, sizeof(int)) < 0) {
                cout << "PS: setsockopt() failed (TCP)" << endl;
                exit(1);
        }

        // Initialize the server information
        // Note that we can't choose a port less than 1023 if we are not privileged users (root)
        memset(&serverAddr, 0, sizeof(serverAddr));         // Zero out the structure
        serverAddr.sin_family = AF_INET;                    // Use Internet address family
        serverAddr.sin_port = htons(port);                  // Server port number
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);     // Any incoming interface

        // Bind to the local address
        if (bind(tcpSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
                cout << "PS: bind() failed (TCP)" << endl;
                exit(1);
        }

        // Listen for connection requests
        if (listen(tcpSock, MAXPENDING) < 0) {
                cout << "PS: listen() failed" << endl;
                exit(1);
        }
}

void processTCPSockets (fd_set readySocks)
{
        int size;
        // Loop through the descriptors and process
        for (int sock = 0; sock <= maxDesc; sock++) {
                if (!FD_ISSET(sock, &readySocks))
                        continue;
                
                char* inBuffer = new char[BUFFERSIZE];
                char* outBuffer = new char[BUFFERSIZE];
                memset(inBuffer, 0, BUFFERSIZE);
                memset(outBuffer, 0, BUFFERSIZE);
                
#if DEBUG
                cout << "PS: ProcessTCPSockets(" << sock << ")" << endl << endl;
#endif

                // Receive data from the client
                receiveData(sock, inBuffer, size);
                //cout << "PS: " << size << " bytes received from socket " << sock << endl;
                std::stringstream ss;
                ss << inBuffer;
                pugi::xml_document doc;
                doc.load(ss);
                int processed;
                int test_uid = atoi(doc.first_child().child("uid").child_value());
                int pos = device_exists(test_uid);
                if(pos == -1) {
                        devices.push_back(Device());
                        std::cout << std::endl << "Devices:  " << std::endl << std::endl;
                        pos = devices.size()-1;
                        std::cout << "Added new device " << std::endl << std::endl;
                        devices[pos].set_state(WORKING);
                }
                processed = devices[pos].process_readings_xml(doc);
                
                if(devices[pos].get_battery() < LOW_BATTERY)
                        devices[pos].set_state(SHUTDOWN);
                else if((devices[pos].get_state() == SHUTDOWN) \
                        && (devices[pos].get_battery() > LOW_BATTERY))
                        devices[pos].set_state(WORKING);
                        
                
                doc.reset();
                ss.str(std::string());
                devices[pos].create_confirm_xml(doc, processed);
                doc.print(ss);
                strcpy(outBuffer, ss.str().c_str());
                
                sendData(sock, outBuffer, strlen(outBuffer));
                
                devices[pos].save_readings();
                delete[] inBuffer;
                delete[] outBuffer;
                devices[pos].print();
        }
}

void receiveData (int sock, char* inBuffer, int& size)
{
        size = 0;

        size = recv(sock, inBuffer, BUFFERSIZE, 0);
        if (size <= 0) {
                cout << "PS: recv() failed, or the connection is closed. " << endl;
                FD_CLR(sock, &recvSockSet);

                // Update the max descriptor
                while (FD_ISSET(maxDesc, &recvSockSet) == false)
                        maxDesc -= 1;
                return;
        } 

#ifdef DEBUG
        string msg = string(inBuffer);
        cout << "TCP Client: " << msg;
#endif

}

void sendData (int sock, char* buffer, int size)
{
        int bytesSent = 0;

        //cout << "PS: Size " << size << ", Buffer " << endl << buffer << endl;

        // Sent the data
        bytesSent = send(sock, (char *) buffer, size, 0);
        //cout << "PS: " << bytesSent << " bytes sent of " << size << endl;

        // Check for errors
        if (bytesSent < 0 || bytesSent != size) {
                cout << "PS: error in sending" << endl;
                return;
        }
}

int device_exists(int test_uid) 
{
        for(unsigned int i = 0; i < devices.size(); i++) {
                if(devices[i].get_uid() == test_uid)
                        return i;
        }
        return -1;

}
