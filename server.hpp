#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <string>
# include <map>
# include <iostream>
# include <sstream>

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
        server(const std::vector<std::string> & serverBlock);
        ~server();
        
        // print server configuration.
        void printServerConfig() const;
        
        // getters.
        std::string getPort() const;
        std::string getServerName() const;
        std::string getRoot() const;
        std::string getErrorPage() const;
        std::string getCharSet() const;
        std::vector<std::string> getIndexFiles() const;
        std::vector<std::string> getLocations() const;



};

#endif