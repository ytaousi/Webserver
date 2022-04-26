#ifndef HTTPWEBSERVER_HPP
# define HTTPWEBSERVER_HPP

# include "server.hpp"
# include <fstream>

class httpWebServer
{
    private:
        std::vector<server>     _servers;
        std::string             _configFilePath;
        size_t                  _serverCount;
    
    public:
        size_t getServerCount() const;
        httpWebServer(const std::string & configFilePath);
        ~httpWebServer();
        void    createNewServer(const std::vector<std::string> & serverBlock);
        void    getConfigurations(const std::string & configFilePath);
        // i think i wont need to use this function here, stop feeding.
        // i think i will need it lol.
        const std::vector<std::string>  getServerBlock(std::istream & configFile);
        void checkConfigurations();
        // print server configuration of the selected server.
        void printServerConfiguration() const;
        std::vector<server> getServers() const;
};

#endif