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
        size_t getServerCount() const
        {
            return _serverCount;
        }
        httpWebServer(const std::string & configFilePath)
        {
            _configFilePath = configFilePath;
            _serverCount = 0;
            getConfigurations(_configFilePath);
        }
        ~httpWebServer()
        {
            _servers.clear();
            _configFilePath.clear();
            _serverCount = 0;
        }
        
        void    createNewServer(const std::vector<std::string> & serverBlock)
        {
            server  newServer(serverBlock);
            
            _servers.push_back(newServer);
        }

        void    getConfigurations(const std::string & configFilePath)
        {
            std::ifstream configFile;

            configFile.open(configFilePath, std::ios::out);
            if (!configFile)
            {
                std::cout << "Couldnt Open Configuration File" << std::endl;
                exit(1);
            }

            // create new server object if server block is found.
            for (std::vector<std::string>  serverBlock = getServerBlock(configFile); serverBlock.size() > 0; serverBlock = getServerBlock(configFile))
            {
                createNewServer(serverBlock);
                _serverCount++;
            }
        }
        // i think i wont need to use this function here, stop feeding.
        // i think i will need it lol.
        const std::vector<std::string>  getServerBlock(std::istream & configFile)
        {
            std::vector<std::string> serverBlock;
            for (std::string line ; std::getline(configFile, line);)
            {
                if (line.find("server {", 0) != std::string::npos)
                {
                    for (; line.find("};", 0) == std::string::npos; std::getline(configFile, line))
                    {
                        serverBlock.push_back(line);
                    }
                }
                if (line.find("};", 0) != std::string::npos)
                {
                    serverBlock.push_back(line);
                    break;
                }
            }
            return serverBlock;
        }

        
        void checkConfigurations()
        {
            ;
        } 

        // print server configuration of the selected server.
        void printServerConfiguration() const
        {
            for (size_t i = 0; i < _serverCount; i++)
            {
                _servers[i].printServerConfig();
            }
        }
};

#endif