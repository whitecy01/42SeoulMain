#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_CLIENTS 128    // Maximum number of client connections allowed
#define BUFFER_SIZE 200000 // Size of the buffer used for message exchange

int main(int argc, char **argv) 
{
    if (argc != 2)  // 명령줄 인수 개수가 잘못된지 확인하세요. 
    {                         
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);  // Print an error message to the standard error stream
        exit(1);                              // Terminate the program with a non-zero status code
    }

    int clientSockets[MAX_CLIENTS];           // 클라이언트 소켓 설명자를 저장하는 배열
    int next_id = 0;                          // 다음 클라이언트 연결을 위한 식별자

    // File descriptor sets
    fd_set activeSockets, readySockets;        // 소켓 활동을 추적하기 위한 파일 설명자 세트(File descriptor sets for tracking socket activity)
    char buffer[BUFFER_SIZE];                  // 수신된 메시지를 저장하기 위한 버퍼 Buffer for storing received messages

    // Create the server socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);  // IPv4 주소 지정 및 TCP 프로토콜을 사용하여 소켓 만들기, Create a socket with IPv4 addressing and TCP protocol
    if (serverSocket < 0)  // Check if socket creation failed
    {                    
        perror("Error creating server socket"); // Print an error message with a description of the error
        exit(1);                              // Terminate the program with a non-zero status code
    }

    // Set up the server address
    struct sockaddr_in serverAddress = {0};    // 서버 주소를 보유하는 구조 Structure to hold the server address
    serverAddress.sin_family = AF_INET;        // 주소 계열을 IPv4로 설정 Set address family to IPv4
    serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // IP 주소를 localhost로 설정 Set the IP address to localhost
    serverAddress.sin_port = htons(atoi(argv[1]));  // 명령줄 인수에서 포트 번호 설정 Set the port number from the command line argument

    // 서버 소켓을 지정된 주소에 바인딩 Bind the server socket to the specified address
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) 
    {
        perror("Error binding server socket");  // Print an error message if binding fails
        exit(1);                              // Terminate the program with a non-zero status code
    }

    // Listen for incoming connections
    if (listen(serverSocket, MAX_CLIENTS) < 0) 
    {
        perror("Error listening on server socket");  // Print an error message if listening fails
        exit(1);                              // Terminate the program with a non-zero status code
    }

    // Initialise the active sockets set
    FD_ZERO(&activeSockets);                   // 활성 소켓 세트 지우기 , Clear the set of active sockets
    FD_SET(serverSocket, &activeSockets);      // 세트에 서버 소켓 추가 Add the server socket to the set
    int maxSocket = serverSocket;              // 최대 소켓 설명자를 추적하는 변수 Variable to track the maximum socket descriptor

    while (1) 
    {
        // Wait for activity on the sockets
        readySockets = activeSockets;           // select()와 함께 사용할 활성 소켓 세트를 복사합니다. Copy the active sockets set for use with select()
        if (select(maxSocket + 1, &readySockets, NULL, NULL, NULL) < 0) 
        {
            perror("Error in select");         // Print an error message if select() fails
            exit(1);                          // Terminate the program with a non-zero status code
        }

        // Check each socket for activity
        for (int socketId = 0; socketId <= maxSocket; socketId++) 
        {
            if (FD_ISSET(socketId, &readySockets)) 
            {
                // New client connection
                if (socketId == serverSocket)  // 활동이 서버 소켓에 있는지 확인하십시오. Check if the activity is on the server socket
                {
                    int clientSocket = accept(serverSocket, NULL, NULL);  // Accept a new client connection
                    if (clientSocket < 0) 
                    {
                        perror("Error accepting client connection");  // Print an error message if accepting fails
                        exit(1);                          // Terminate the program with a non-zero status code
                    }

                    // 활성 세트에 새 클라이언트 소켓 추가 Add the new client socket to the active set
                    FD_SET(clientSocket, &activeSockets);     //활성 소켓 세트에 클라이언트 소켓 추가  Add the client socket to the set of active sockets
                    maxSocket = (clientSocket > maxSocket) ? clientSocket : maxSocket;  //최대 소켓 설명자 업데이트  Update the maximum socket descriptor

                    // Send a welcome message to the client
                    sprintf(buffer, "server: client %d just arrived\n", next_id);  // 환영 메시지를 준비하세요 Prepare the welcome message
                    send(clientSocket, buffer, strlen(buffer), 0);  // 고객에게 환영 메시지 보내기 Send the welcome message to the client

                    // 나중에 참조할 수 있도록 클라이언트 소켓을 저장합니다. Store the client socket for future reference
                    clientSockets[next_id++] = clientSocket;  //배열에 클라이언트 소켓 추가  Add the client socket to the array
                } 
                else 
                {
                    //클라이언트로부터 받은 데이터 Data received from a client
                    int bytesRead = recv(socketId, buffer, sizeof(buffer) - 1, 0);  //클라이언트로부터 데이터 수신 Receive data from the client

                    if (bytesRead <= 0) 
                    {
                        // Client disconnected
                        sprintf(buffer, "server: client %d just left\n", socketId);  //연결 끊김 메시지 준비 Prepare the disconnection message

                        //연결이 끊긴 클라이언트에 대해 나머지 클라이언트에게 알립니다. Notify remaining clients about the disconnected client
                        for (int i = 0; i < next_id; i++) 
                        {
                            if (clientSockets[i] != socketId) 
                            {
                                send(clientSockets[i], buffer, strlen(buffer), 0); //다른 클라이언트에게 연결 해제 메시지 보내기 Send the disconnection message to other clients
                            }
                        }

                        //소켓을 닫고 활성 세트에서 제거합니다. Close the socket and remove it from the active set
                        close(socketId);                          // Close the client socket
                        FD_CLR(socketId, &activeSockets);         // Remove the client socket from the set of active sockets
                    } 
                    else 
                    {
                        //수신된 메시지를 다른 모든 클라이언트에게 브로드캐스트 Broadcast the received message to all other clients
                        buffer[bytesRead] = '\0';                  // Null-terminate the received message
                        sprintf(buffer, "client %d: %s\n", socketId, buffer);  //메시지에 클라이언트 식별자 추가 Add client identifier to the message

                        for (int i = 0; i < next_id; i++) 
                        {
                            if (clientSockets[i] != socketId) 
                            {
                                send(clientSockets[i], buffer, strlen(buffer), 0);  //다른 클라이언트에게 메시지 보내기 Send the message to other clients
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}