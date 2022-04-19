#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <string>
# include <map>

class server
{
    private:
        std::string _host;
        std::string _port;
        std::string _serverName;
        std::string _root;
        std::string _errorPage;
        std::string _location;
    public:
        server();
        ~server();

};

#endif