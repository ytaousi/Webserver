# include "server.hpp"

std::vector<std::string> server::getLocationBlock(const std::vector<std::string> & serverBlock, std::vector<std::string>::const_iterator  it)
{
    std::vector<std::string> locationBlockContent;

    // extract block location content between brackets starts with "[" and ends with "];"
    for (; it->find("];") == std::string::npos ; it++)
    {
        locationBlockContent.push_back(*it);
    }
    locationBlockContent.push_back(*it);

    return locationBlockContent;
}

void server::setLocations(const std::vector<std::string> & serverBlock, std::vector<std::string>::const_iterator *it)
{
    std::string locationDirectivePath;

    locationDirectivePath = (*it)->substr((*it)->find("location : ") + 11, (*it)->size());

    std::vector<std::string>    locationDirectiveContent;

    locationDirectiveContent = getLocationBlock(serverBlock, *it);
    _tmp++;

    std::vector<std::string> locationDiv;

    for (std::vector<std::string>::const_iterator it2 = locationDirectiveContent.begin(); it2 != locationDirectiveContent.end(); it2++)
    {
        if (it2->find("[") != std::string::npos)
        {
            for (; it2->find("];") == std::string::npos; it2++)
            {
                locationDiv.push_back(*it2);
            }
            locationDiv.push_back(*it2);
        }
    }

    // fill _locations map with key as locationDirectivePath and value as locationDirectiveContent
    _locations.insert(std::make_pair(locationDirectivePath, locationDiv));
}

server::server(const std::vector<std::string> & serverBlock)
{
    _tmp = 0;
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
               //std::cout << "location directive found at line : " << std::distance(serverBlock.begin(), it) << " : " << *it  << std::endl;

               // setup locations map<string, vector<string> >.
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
    // still not working.
    std::cout << "locations: " << std::endl;
    int i = 0;
    for (std::map<std::string, std::vector<std::string> >::const_iterator it = _locations.begin(); it != _locations.end(); it++)
    {
        std::cout << "\t" << (*it).first << std::endl;
        for (std::vector<std::string>::const_iterator it2 = (*it).second.begin() ; it2 != (*it).second.end() ; it2++)
        {
            std::cout << *it2 << std::endl;
        }
    }
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
    _port = port;
}
void server::setServerName(const std::string & serverName)
{
    _serverName = serverName;
}

void server::setRoot(const std::string & root)
{
    _root = root;
}

void server::setErrorPage(const std::string & errorPage)
{
    _errorPage = errorPage;
}

void server::setCharSet(const std::string & charSet)
{
    _charSet = charSet;
}

void server::setIndexFiles(const std::vector<std::string> & indexFiles)
{
    for (std::vector<std::string>::const_iterator it = indexFiles.begin(); it != indexFiles.end(); it++)
    {
        _indexFiles.push_back(*it);
    }
}