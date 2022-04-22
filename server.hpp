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
        std::string                                     _port;
        std::string                                     _serverName;
        std::string                                     _root;
        std::string                                     _errorPage;
        std::string                                     _errorPageStatus;
        std::string                                     _charSet;
        std::vector<std::string>                        _indexFiles;
        std::map<std::string, std::vector<std::string> > _locations;

    public:
        server(const std::vector<std::string> & serverBlock);
        ~server();
        
        // print server
        void printServerConfig() const;
        
        // getters.
        std::string getPort() const;
        std::string getServerName() const;
        std::string getRoot() const;
        std::string getErrorPage() const;
        std::string getCharSet() const;
        std::vector<std::string> getIndexFiles() const;
        std::map<std::string, std::vector<std::string> > getLocations() const;
        std::vector<std::string> getLocationBlock(const std::vector<std::string> & serverBlock, std::string *locationDirectivePath);


        // setters not difined yet.
        void setPort(const std::string & port);
        void setServerName(const std::string & serverName);
        void setRoot(const std::string & root);
        void setErrorPage(const std::string & errorPage);
        void setCharSet(const std::string & charSet);
        void setIndexFiles(const std::vector<std::string> & indexFiles);
        void setLocations(const std::vector<std::string> & serverBlock, std::vector<std::string>::const_iterator * it);
};

#endif