#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <string>
# include <map>
# include <iostream>

class server
{
    private:
        std::string                 _port;
        std::string                 _serverName;
        std::string                 _root;
        std::string                 _errorPage;
        std::string                 _errorPageStatus;
        std::string                 _charSet;
        std::vector<std::string>    _indexFiles;
        std::vector<std::string>    _locations;


    public:
        server(const std::vector<std::string> & serverBlock)
        {
            for (std::vector<std::string>::const_iterator it = serverBlock.begin(); it != serverBlock.end(); ++it)
            {
                if (it->find("listen") != std::string::npos)
                {
                    if (_port != "")
                        continue;
                    _port = it->substr(it->find("listen") + 7, it->size());
                }
                if (it->find("server_name") != std::string::npos)
                {
                    if (_serverName != "")
                        continue;
                    _serverName = it->substr(it->find("server_name") + 12, it->size());
                }
                if (it->find("root") != std::string::npos)
                {
                    // if root is not empty continue.
                    if (_root != "")
                        continue;
                    _root = it->substr(it->find("root") + 5, it->size());
                }
                if (it->find("error_page") != std::string::npos)
                {
                    std::string errorDirective = it->substr(it->find("error_page") + 11, it->size());

                    _errorPageStatus = errorDirective.substr(0, errorDirective.find(" "));
                    _errorPage = errorDirective.substr(errorDirective.find(" ") + 1, errorDirective.size());
                }
                if (it->find("charset") != std::string::npos)
                {
                    if (_charSet != "")
                        continue;
                    _charSet = it->substr(it->find("charset") + 8, it->size());
                }
                // if (it->find("indexFiles", 0) != std::string::npos)
                // {
                //     ;
                // }
                // if (it->find("location", 0) != std::string::npos)
                // {
                //     
                // }
            }
        }
        ~server()
        {
            std::cout << "server destructor" << std::endl;
        }
        void printServerConfig() const
        {
            std::cout << "Port: " << _port << std::endl;
            std::cout << "Server Name: " << _serverName << std::endl;
            std::cout << "Root: " << _root << std::endl;
            std::cout << "Error Page: " << _errorPage << std::endl;
            std::cout << "Error Page Status: " << _errorPageStatus << std::endl;
            std::cout << "Character Set: " << _charSet << std::endl;
            std::cout << "Index Files: " << std::endl;
            for (std::vector<std::string>::const_iterator it = _indexFiles.begin(); it != _indexFiles.end(); ++it)
            {
                std::cout << *it << std::endl;
            }
            std::cout << "Locations: " << std::endl;
            for (std::vector<std::string>::const_iterator it = _locations.begin(); it != _locations.end(); ++it)
            {
                std::cout << *it << std::endl;
            }
        }
        
        // getters.
        std::string getPort() const
        {
            return _port;
        }

        std::string getServerName() const
        {
            return _serverName;
        }

        std::string getRoot() const
        {
            return _root;
        }

        std::string getErrorPage() const
        {
            return _errorPage;
        }

        std::string getCharSet() const
        {
            return _charSet;
        }

        std::vector<std::string> getIndexFiles() const
        {
            return _indexFiles;
        }

        std::vector<std::string> getLocations() const
        {
            return _locations;
        }



};

#endif