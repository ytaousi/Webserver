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
#include <sstream>
#include "serverRequest.hpp"
#include "server.hpp"
#include "httpWebServer.hpp"

int main(int ac, char **av)
{
    int server_fd;
    int new_socket; // socket created when a connection is started between 
    long value_read;
    struct sockaddr_in address;
    int addrlen = sizeof(address);


    address.sin_family = AF_INET; // domain (type of ip address) used to connect to socket
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( atoi(av[1]) ); // htons convert from numerical value to network representation  from host_byte rep to network_byte rep 
    
    //memset c++ ish.
    memset(address.sin_zero, '\0', sizeof (address.sin_zero));
    
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
        else
        {
            printf("\n+++++++ got New Connection ++++++++\n\n");
            std::cout << "Client Filedescriptor : " << new_socket << std::endl;
        }

        
        char buffer[30000] = {0}; // buffer to fill with request data.
        

        // check if filedescriptor is ready to read from either using select or poll.
        // if filedescriptor is ready to read then read from it.
        value_read = recv(new_socket, buffer, 30000, 0);
        if (value_read < 0)
        {
            std::cout << "Server Failed to Read Request" << std::endl;
            exit(1);
        }

        // parse the request for the specific clientFiledescriptor.
        // handle the request.
        // check content-type if cgi is true then build the cgi request object and pass it to the serverRequest object.





        


        // response part of the code.
        std::string responseHeader = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\n"; // should update the content length
        std::string responseBody = "Hello World!";
        size_t      responseBodySize = responseBody.size();
        
        char * responseHtml = (char *)malloc(sizeof(char) * (responseHeader.length() + responseBody.length() + 1));
        responseHtml = strcpy(responseHtml, responseHeader.c_str());
        responseHtml = strcat(responseHtml, responseBody.c_str());
        send(new_socket, responseHtml, strlen(responseHtml), 0);
        // close client socket.
        close(new_socket);
    }
    return (0);
}