# include "httpWebServer.hpp"
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


