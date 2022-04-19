# include <iostream>
# include <string>
# include <fstream>

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
    
    printf("+++++++++++++++++ EndofServers Configuration File ++++++++++++++++++\n");
    return (0);
}