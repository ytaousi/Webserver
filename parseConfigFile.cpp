# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include "httpWebServer.hpp"
# include "parseUtils.hpp"

int main(int ac, char **av)
{
    printf("+++++++++++++++++ Servers Configuration File ++++++++++++++++++++++\n");
        
    // server object under construction.
    if (av[1] == NULL)
    {
        std::cout << "No Configuration File Specified" << std::endl;
        exit(1);
    }

    const std::string configFilePath = av[1];

    std::ifstream   configFile;
    configFile.open(configFilePath, std::ios::out);
    if (!configFile)
    {
        std::cout << "Couldnt Open Configuration File" << std::endl;
        exit(1);
    }

    printf("++++++++++++++++ extract server block +++++++++++++++++++++++++++++\n");
    httpWebServer   httpServer(configFilePath);
    //const std::vector<std::string>    serverBlock1 = getServerBlock(configFile);
    //const std::vector<std::string>    serverBlock2 = getServerBlock(configFile);

    // server server1(serverBlock1);

    // server1.printServerConfig();
    //httpServer.createNewServer(serverBlock1);
    //httpServer.createNewServer(serverBlock2);
    
    // print all virtual servers configuration.
    //httpServer.printServerConfiguration();
    
    std::vector<server> servers = httpServer.getServers();
    std::vector<std::string> serverBlock = getServerBlock(configFile);
    std::map<std::string, std::vector<std::string> > locations = servers[0].getLocations();

    for (std::map<std::string, std::vector<std::string> >::const_iterator it = locations.begin(); it != locations.end(); it++)
    {
        std::cout << it->first << std::endl;
        for (std::vector<std::string>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            std::cout << *it2 << std::endl;
        }
    }    
    // print server block of selected server.
    for (std::vector<std::string>::const_iterator it = serverBlock.begin(); it != serverBlock.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    // print location block of selected server.
    for (std::map<std::string, std::vector<std::string> >::const_iterator it = locations.begin(); it != locations.end(); it++)
    {
        std::cout << "locationDirectives : \n";
        for (std::vector<std::string>::const_iterator it2 = (*it).second.begin() ; it2 != (*it).second.end() ; it2++)
        {
            std::cout << *it2 << std::endl;
        };
    }





    // print server blocks c++98 syntax.
    
    
    
    printf("++++++++++++++++ EndofServer block +++++++++++++++++++++++++++++\n");

    printf("+++++++++++++++++ EndofServers Configuration File ++++++++++++++++++\n");
    configFile.close();
    return (0);
}