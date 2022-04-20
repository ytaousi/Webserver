#ifndef HTTPWEBSERVER_HPP
# define HTTPWEBSERVER_HPP

# include "server.hpp"

class httpWebServer
{
    private:
        std::vector<server>         _servers;
    public:
        httpWebServer();
        ~httpWebServer();

};

#endif