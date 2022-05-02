#ifndef HTTPWEBSERVER_HPP
# define HTTPWEBSERVER_HPP

# include "server.hpp"
# include "serverRequest.hpp"


class httpWebServer
{
    private:
        std::vector<server>     _servers;
        std::string             _configFilePath;
        size_t                  _serverCount;
        std::vector<int>                _clientFds;
    public:
        httpWebServer(const std::string & configFilePath);
        ~httpWebServer();
        
        void                            createNewServer(const std::vector<std::string> & serverBlock);
        void                            checkConfigurations();
        void                            printServerConfiguration() const;
        void                            connectServers();
        
        
        
        
        std::vector<server>             getServers() const;
        void                            getConfigurations(const std::string & configFilePath);
        size_t                          getServerCount() const;
        const std::vector<std::string>  getServerBlock(std::istream & configFile);


        
};

#endif