#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdlib.h>
#include <string>
#include <fcntl.h>
#include <sys/ioctl.h>
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
        close(server_fd);
        exit(1);
    }

    if (listen(server_fd, 10) < 0)
    {
        std::cout << "Server Failed to listen on Port" << std::endl;
        close(server_fd);
        exit(1);
    }

    # define NUM_FDS 10 // number of file descriptors to poll

    nfds_t nfds = 0;
    struct pollfd *pollfds; 
    int maxFds = 0;
    int numFds = 0;

    if ((pollfds = (struct pollfd *)malloc(sizeof(struct pollfd) * NUM_FDS)) == NULL)
    {
        std::cout << "Couldn't Allocate Memory for Pollfds" << std::endl;
        exit(1);
    }

    maxFds = NUM_FDS;
    pollfds[0].fd = server_fd;
    pollfds[0].events = POLLIN;
    pollfds[0].revents = 0;
    numFds = 1;

    std::string responseBody = "Hello World\r\n";
    std::string responseHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(responseBody.length()) + "\r\n\r\n";
    while (1)
    {
        // monitor readFds for readiness for reading
        nfds = numFds;
        if (poll(pollfds, nfds, -1) < 0)
        {
            std::cout << "Server Failed to Poll" << std::endl;
            exit(1);
        }

        // use fcntl() for non-blocking I/O
        
        // some sockets are ready. examine readFds
        for (int fd = 0; fd < nfds + 1; fd++)
        {
            if ((pollfds + fd)->fd <= 0)
            {
                continue;
            }

            // if the socket is ready for reading
            if (((pollfds + fd)->revents & POLLIN)) // == POLLIN ??!.
            {
                if ((pollfds + fd)->fd == server_fd) // request for new connection
                {
                    int newFd;
                    if ((newFd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
                    {
                        std::cout << "Server Failed to Accept" << std::endl;
                        exit(1);
                    }
                    // add newFd to pollfds
                    if (numFds == maxFds)
                    {
                        if ((pollfds = (struct pollfd *)realloc(pollfds, sizeof(struct pollfd) * (maxFds + NUM_FDS))) == NULL)
                        {
                            std::cout << "Couldn't Reallocate Memory for Pollfds" << std::endl;
                            exit(1);
                        }
                        maxFds += NUM_FDS;
                    }
                    numFds++;
                    (pollfds + numFds - 1)->fd = newFd;
                    (pollfds + numFds - 1)->events = POLLIN;
                    (pollfds + numFds - 1)->revents = 0;
                }
                else // data from an existing connection recieve it
                {
                    char buffer[1024]; 
                    // use recv() unstead of read()
                    memset (buffer, '\0', sizeof (buffer));
                    size_t value_read = recv((pollfds + fd)->fd, buffer, sizeof (buffer), 0);
                    if (value_read < 0)
                    {
                        std::cout << "Server Failed to Recieve" << std::endl;
                        exit(1);
                    }
                    else if (value_read == 0)
                    {
                        // connection closed
                        if (close((pollfds + fd)->fd) < 0)
                        {
                            std::cout << "Server Failed to Close" << std::endl;
                            exit(1);
                        }
                        (pollfds + fd)->fd *= -1; // make it negative so that it is ignored in the next loop
                    }
                    else
                    {
                        // new client file descriptor
                        printf("\n++++++++++++++++\n");
                        std::cout << "Client File Descriptor: " << (pollfds + fd)->fd << std::endl;
                        printf("\n++++++++++++++++\n");
                        // parse request
                        
                        // print request header to stdout
                        std::cout << buffer << std::endl;

                        // send response

                        if (send((pollfds + fd)->fd, responseHeader.c_str(), responseHeader.length(), 0) < 0)
                        {
                            std::cout << "Server Failed to Send" << std::endl;
                            exit(1);
                        }
                        if (send((pollfds + fd)->fd, responseBody.c_str(), responseBody.length(), 0) < 0)
                        {
                            std::cout << "Server Failed to Send" << std::endl;
                            exit(1);
                        }

                        // close connection
                        if ( close((pollfds + fd)->fd) < 0)
                        {
                            std::cout << "Server Failed to Close" << std::endl;
                            exit(1);
                        }
                        (pollfds + fd)->fd *= -1; // make it negative so that it is ignored in the next loop
                    }
                }
            } // end if POLLIN 
        } // end for loop over all file descriptors
    
    }    // while 1

    return 0;
}