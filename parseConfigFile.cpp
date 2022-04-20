# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include "server.hpp"

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
    // extract server block between brackets from config file.
    const std::vector<std::string>    serverBlock1 = getServerBlock(configFile);
    //std::vector<std::string>    serverBlock2;
    //std::vector<server *>         servers;

    server server1(serverBlock1);

    server1.printServerConfig();

    // print server blocks c++98 syntax.
    
    
    
    printf("++++++++++++++++ EndofServer block +++++++++++++++++++++++++++++\n");

    printf("+++++++++++++++++ EndofServers Configuration File ++++++++++++++++++\n");
    configFile.close();
    return (0);
}