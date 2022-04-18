#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h> // for listenning and binding
#include <netinet/in.h> // for manipulating addr family structur !!!!??
#include <fstream> // read/write from files

int main(int ac, char **av)
{
    int server_fd;
    int new_socket; // socket created when a connection is started between 
    long value_read;
    struct sockaddr_in address;
    int addrlen = sizeof(address);


    address.sin_family = AF_INET; // domain (type of ip address) used to connect to socket
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( 8080 ); // htons convert from numerical value to network representation  from host_byte rep to network_byte rep 
    
    //memset c++ ish.
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Couldn't Create Socket for Communication" << std::endl;
        exit(1);
    }

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) // when the socket is created there is no address assigned to it
    {
        std::cout << "Couldn't Bind Socket" << std::endl;
        exit(1);
    }

    if (listen(server_fd, 10) < 0)
    {
        std::cout << "Server Failed to listen on Port" << std::endl;
        exit(1);
    }

    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) <0 )
        {
            std::cout << "Server Failed to Accept Any Connection" << std::endl;
            exit(1);
        }

        std::ifstream readFromFile;
        std::string uriPath;
        std::string responseFile;
        std::string responseHeader = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 285\n\n"; // should update the content length
        
        readFromFile.open("./views/index.html", std::ios::out);
        if (!readFromFile)
        {
            std::cout << "Couldnt Open File for Reading" << std::endl;
            exit(1);
        }

        char buffer[30000] = {0}; // buffer to fill with request data.
        std::string buff;
        
        value_read = recv(new_socket, buffer, 30000, 0);

        printf("\n+++++++++++ Buffer Content ++++++++++\n\n"); 
        std::cout << buffer << std::endl; // print the request header got from the browser
        buff = buffer;
        printf("\n+++++++++++ EndOfBufferContent +++++++++++++\n\n");
        

        printf("\n++++++++++++++ Path Requsted +++++++++\n\n");
        
        for (char *tmp = buffer; *tmp != '\n'; tmp++)
            uriPath += *tmp;
        
        std::vector<std::string> bufferHeaders; // vector to store the headers for parsing



        
        printf("\n++++++++++++++ EndOfPath ++++++++++++\n\n");
        
        printf("\n++++++++++++++ Response Content ++++++++++++++++++\n\n");
        std::cout << responseHeader + responseFile << std::endl;
        printf("\n++++++++++++++ EndofResponse Content ++++++++++++++++++\n\n");

        char * responseHtml = (char *)malloc(sizeof(char) * (responseHeader.length() + responseFile.length() + 1));
        responseHtml = strcpy(responseHtml, responseHeader.c_str());
        responseHtml = strcat(responseHtml, responseFile.c_str());
        send(new_socket, responseHtml, strlen(responseHtml), 0);
        printf("------------------Hello message sent-------------------\n");
        readFromFile.close();
        close(new_socket);
    }
    return (0);
}