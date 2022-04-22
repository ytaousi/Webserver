# include "server.hpp"

server::server(const std::vector<std::string> & serverBlock)
{
    // getConfigurations(serverBlock);
    for (std::vector<std::string>::const_iterator it = serverBlock.begin(); it != serverBlock.end(); ++it)
    {
        if (it->find("listen :") != std::string::npos)
        {
            if (_port != "")
                continue;
            _port = it->substr(it->find("listen :") + 9, it->size());
        }
        if (it->find("server_name :") != std::string::npos)
        {
            if (_serverName != "")
            continue;
            _serverName = it->substr(it->find("server_name :") + 14, it->size());
        }
        if (it->find("root :") != std::string::npos)
        {
            // if root is not empty continue.
            if (_root != "")
                continue;
            _root = it->substr(it->find("root :") + 7, it->size());
        }
        if (it->find("error_page :") != std::string::npos)
        {
            std::string errorDirective = it->substr(it->find("error_page :") + 13, it->size());

            _errorPageStatus = errorDirective.substr(0, errorDirective.find(" "));
            _errorPage = errorDirective.substr(errorDirective.find(" ") + 1, errorDirective.size());
        }
        if (it->find("charset :") != std::string::npos)
        {
            if (_charSet != "")
                continue;
            _charSet = it->substr(it->find("charset :") + 10, it->size());
        }
        if (it->find("index :") != std::string::npos)
        {
            if (_indexFiles.empty() == false)
                continue;
            std::string indexDirective = it->substr(it->find("index :") + 8, it->size());
            // split index directive by space and fill _indexFiles.
            std::stringstream ss(indexDirective);
            std::string       token;
            while (std::getline(ss, token, ' '))
            {
                _indexFiles.push_back(token);
            }
        }
        if (it->find("location :", 0) != std::string::npos)
        {
               std::cout << "location directive found at line " << std::distance(serverBlock.begin(), it) << std::endl;
               // setup locations map<string, vector<string> >.
               //
               setLocations(serverBlock, &it);
        }
    }
}

server::~server()
{
    // clear server member variables.
    _port.clear();
    _serverName.clear();
    _root.clear();
    _errorPage.clear();
    _errorPageStatus.clear();
    _charSet.clear();
    _indexFiles.clear();
    _locations.clear();
}

// print server configuration.
void server::printServerConfig() const
{
    std::cout << "port: " << _port << std::endl;
    std::cout << "server_name: " << _serverName << std::endl;
    std::cout << "root: " << _root << std::endl;
    std::cout << "error_page: " << _errorPage << std::endl;
    std::cout << "error_page Status: " << _errorPageStatus << std::endl;
    std::cout << "charset: " << _charSet << std::endl;
    std::cout << "indexFiles: " << std::endl;
    for (std::vector<std::string>::const_iterator it = _indexFiles.begin(); it != _indexFiles.end(); it++)
    {
        std::cout << "\t" << *it << std::endl;
    }
    std::cout << "locations: " << std::endl;
}


// getters
std::string server::getPort() const
{
    return _port;
}

std::string server::getServerName() const
{
    return _serverName;
}

std::string server::getRoot() const
{
    return _root;
}

std::string server::getErrorPage() const
{
    return _errorPage;
}

std::string server::getCharSet() const
{
    return _charSet;
}

std::vector<std::string> server::getIndexFiles() const
{
    return _indexFiles;
}

std::map<std::string, std::vector<std::string> > server::getLocations() const
{
    return _locations;
}

// setters
void server::setPort(const std::string & port)
{
    ;
}
void setServerName(const std::string & serverName)
{
    ;
}

void setRoot(const std::string & root)
{
    ;
}

void setErrorPage(const std::string & errorPage)
{
    ;
}

void setCharSet(const std::string & charSet)
{
    ;
}

void setIndexFiles(const std::vector<std::string> & indexFiles)
{
    ;
}

void server::setLocations(const std::vector<std::string> & serverBlock, std::vector<std::string>::const_iterator *it)
{
    std::string locationDirectivePath;

    locationDirectivePath = (*it)->substr((*it)->find("location : ") + 11, (*it)->size());
    std::cout << "locationDirectivePath :" << locationDirectivePath << std::endl;

    std::vector<std::string> locationDirectiveContent;

    locationDirectiveContent = getLocationBlock(serverBlock, &locationDirectivePath);
    std::cout << "locationDirectiveContent : " << std::endl;

    for (std::vector<std::string>::const_iterator it = locationDirectiveContent.begin(); it != locationDirectiveContent.end(); it++)
    {
        std::cout << "\t" << *it << std::endl;
    }
    
    
    // std::vector<std::string> locationDirectiveContentVector;
    
    
    // std::stringstream ss(locationDirectiveContent);
    // std::string       token;
    // while (std::getline(ss, token, ' '))
    // {
    //     locationDirectiveContentVector.push_back(token);
    // }
    // _locations.insert(std::pair<std::string, std::vector<std::string> >(locationPath, locationDirectiveContentVector));
}

std::vector<std::string> server::getLocationBlock(const std::vector<std::string> & serverBlock, std::string *locationDirectivePath)
{
    ;
}