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
#include <sys/types.h>

typedef struct s_apah {
    int server_fd;
    struct sockaddr_in *address;
    int address_len;
} apah;

host: localhost
port: 9000
server_name: a.com b.com

apah create_socket(int port, char *ip)
{
//simple server using sockets
    int server_fd;
    int new_socket; // socket created when a connection is started between 
    long value_read;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    address.sin_family = AF_INET; // domain (type of ip address) used to connect to socket


    address.sin_addr.s_addr = inet_addr(ip);

    address.sin_port = htons( port ); // htons convert from numerical value to network representation  from host_byte rep to network_byte rep

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

    apah a;
    a.server_fd = server_fd;
    a.address = &address;
    a.address_len = &address_len;

    return a;
}   


int main(int ac, char **av)
{
    // 2 servers using sockets
    apah a  = create_socket(atoi(av[1]), av[2]);
    apah b  = create_socket(atoi(av[1]), av[3]);
    
    int client;
    while (1)
    {

        if ((client = accept(a.server_fd, (struct sockaddr *)&a.address, (socklen_t *)&addrlen)) < 0)
        {
            std::cout << "Server Failed to accept connection" << std::endl;
            close(server_fd1)
        }
        else
        {
            std::cout << "Server 1 Accepted Connection" << std::endl;
        }
        

    }
    

    return 0;
}

