# include <iostream>
# include <string>
# include <fstream>
# include "server.hpp"

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

    std::ifstream configFile;
    configFile.open(configFilePath, std::ios::out);
    if (!configFile)
    {
        std::cout << "Couldnt Open Configuration File" << std::endl;
        exit(1);
    }

    for (std::string line; std::getline(configFile, line);)
    {
        std::cout << line << std::endl;
    }
    printf("++++++++++++++++ extract server block +++++++++++++++++++++++++++++\n");
    // extract server block between brackets from config file.
    std::vector<std::string> serverBlock; // vector to store server block content between curly brackets.
    
    // store server block in serverBlock vector.
    for (std::string line; std::getline(configFile, line);)
    {
        ;      
    }
    
    // print server block vector.
    for (std::vector<std::string>::iterator it = serverBlock.begin(); it != serverBlock.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    
    printf("++++++++++++++++ EndofServer block +++++++++++++++++++++++++++++\n");

    printf("+++++++++++++++++ EndofServers Configuration File ++++++++++++++++++\n");
    configFile.close();
    return (0);
}