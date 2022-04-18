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
        std::string responseBody;
        size_t      responseBodySize;
        std::string responseHeader = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 285\n\n"; // should update the content length
        
        readFromFile.open("./views/index.html", std::ios::out);
        if (!readFromFile)
        {
            std::cout << "Couldnt Open File for Reading" << std::endl;
            exit(1);
        }

        for (std::string line; std::getline(readFromFile, line);)
        {
            responseBody += line;
        }

        responseBodySize = responseBody.size();
        readFromFile.close();
        
        char buffer[30000] = {0}; // buffer to fill with request data.
        
        value_read = recv(new_socket, buffer, 30000, 0);
        if (value_read < 0)
        {
            std::cout << "Server Failed to Read Request" << std::endl;
            exit(1);
        }

        // printf("++++++++++++++ Response Content ++++++++++++++++++\n");
        
        // std::cout << responseHeader + '\n' + responseBody << std::endl;

        // printf("++++++++++++++ EndofResponse Content ++++++++++++++++++\n");


        printf("++++++++++++++ Parsing Header and Body from the httpRequestMessage +++++++++\n");
        std::string                         httpRequestMessage = buffer; // buffer is the http request message as char * filled with recv().
        
        std::string                         httpRequestHeader = httpRequestMessage.substr(0, httpRequestMessage.find("\r\n\r\n"));
        std::string                         httpRequestBody   = httpRequestMessage.substr(httpRequestMessage.find("\r\n\r\n") + 4);

        std::string                         httpRequestDirectiveLine;
        std::string                         httpMethod; // GET or POST or DELETE.
        std::string                         httpUriPath; // check if its a valid path.
        std::string                         httpVersion;
        std::vector<std::string>            httpRequestBodyVector; // vector to store body of http request.
        std::string                         httpRequestHeaderFirstLine;

        httpRequestHeaderFirstLine = httpRequestHeader.substr(0, httpRequestHeader.find("\r\n"));
        // remove first line from httpRequestHeader.
        httpRequestHeader = httpRequestHeader.substr(httpRequestHeader.find("\r\n") + 2);
        
        httpMethod = httpRequestHeaderFirstLine.substr(0, httpRequestHeaderFirstLine.find(" "));
        httpUriPath = httpRequestHeaderFirstLine.substr(httpRequestHeaderFirstLine.find(" ") + 1, httpRequestHeaderFirstLine.find("HTTP/") - httpRequestHeaderFirstLine.find(" ") - 1);
        httpVersion = httpRequestHeaderFirstLine.substr(httpRequestHeaderFirstLine.find("HTTP/"));

        
        std::cout << "RequestHeaderFirstLine to Parse : " << httpRequestHeaderFirstLine << std::endl;      
        std::cout << "METHOD : " << httpMethod << std::endl;
        std::cout << "URIPATH : " << httpUriPath << std::endl;
        std::cout << "VERSION : " << httpVersion << std::endl;
        
        printf("+++++++++++++++++++ Directives +++++++++++++++++++++++++++++++++\n");
        std::map<std::string, std::string>  httpHeaderDirectives; // map to store directives after first line of http request header.

        // fill map directives from httpRequestHeader.
        while (httpRequestHeader.find("\r\n") != std::string::npos)
        {
            httpRequestDirectiveLine = httpRequestHeader.substr(0, httpRequestHeader.find("\r\n"));
            httpRequestHeader = httpRequestHeader.substr(httpRequestHeader.find("\r\n") + 2);
            //std::cout << "httpRequestDirectiveLine : " << httpRequestDirectiveLine << std::endl;
            httpHeaderDirectives[httpRequestDirectiveLine.substr(0, httpRequestDirectiveLine.find(":"))] = httpRequestDirectiveLine.substr(httpRequestDirectiveLine.find(":") + 2);
        }
        
        printf("+++++++++++++++++++ Map of Directives +++++++++++++++++++++++++\n");
        // print httpHeaderDirectives map.
        for (auto it = httpHeaderDirectives.begin(); it != httpHeaderDirectives.end(); ++it)
        {
            std::cout << "Map Directive line "<< it->first << " : " << it->second << std::endl;
        }
        
        printf("+++++++++++++++++++ Directives +++++++++++++++++++++++++++++++++\n");        
        char * responseHtml = (char *)malloc(sizeof(char) * (responseHeader.length() + responseBody.length() + 1));
        responseHtml = strcpy(responseHtml, responseHeader.c_str());
        responseHtml = strcat(responseHtml, responseBody.c_str());
        send(new_socket, responseHtml, strlen(responseHtml), 0);
        close(new_socket);
    }
    return (0);
}