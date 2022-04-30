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
    
    std::vector<server> servers = httpServer.getServers();
    std::vector<std::string> serverBlock = getServerBlock(configFile);
    std::map<std::string, std::vector<std::string> > locations = servers[0].getLocations();
  
    printf("++++++++++++++++ EndofServer block +++++++++++++++++++++++++++++\n");

    printf("+++++++++++++++++ EndofServers Configuration File ++++++++++++++++++\n");
    configFile.close();
    return (0);
}