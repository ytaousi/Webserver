# include "httpWebServer.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Usage : ./a.out configueFilePath " << std::endl;
        exit(1);
    }
    httpWebServer servers(av[1]);
    std::vector<int> clientFds;

    ;
    while (1)
    {
        // (new_socket = accept(it->getSocketFd(), (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0
        // accept new connection
        
        for (int i = 0; i < servers.getServers().size() ; i++)
        {
            clientFds.push_back(accept(servers.getServers()[i].getSocketFd(), (struct sockaddr *)&address, (socklen_t*)&addrlen));
        }

        std::string responseHeader = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 285\n\n"; // should update the content length
        char buffer[30000] = {0}; // buffer to fill with request data.
        long value_read;

        value_read = recv(new_socket, buffer, 30000, 0);
        if (value_read < 0)
        {
            std::cout << "Server Failed to Read Request" << std::endl;
            exit(1);
        }

        
        
        char * responseHtml = (char *)malloc(sizeof(char) * (responseHeader.length() + responseBody.length() + 1));
        responseHtml = strcpy(responseHtml, responseHeader.c_str());
        responseHtml = strcat(responseHtml, responseBody.c_str());
        send(new_socket, responseHtml, strlen(responseHtml), 0);
    }
    return (0);
}