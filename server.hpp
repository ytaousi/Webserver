#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <string>
# include <map>
# include <iostream>
# include <sstream>
# include <sys/socket.h> // for listenning and binding
# include <netinet/in.h> // for manipulating addr family structur !!!!??
# include <fstream> // read/write from files


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
        size_t                                           _tmp;
        std::vector<std::string>                        _cgiExtentions;

        struct sockaddr_in              _address;
        int                             _socketFd;
        std::vector<int>                _clientFds;

    public:
        server(const std::vector<std::string> & serverBlock);
        ~server();
        
        // print server
        void printServerConfig() const;
        
        // getters.
        std::string getCgiExtentions() const;
        std::string getPort() const;
        std::string getServerName() const;
        std::string getRoot() const;
        std::string getErrorPage() const;
        std::string getCharSet() const;
        std::vector<std::string> getIndexFiles() const;
        std::map<std::string, std::vector<std::string> > getLocations() const;
        
        // under Construction
        std::vector<std::string> getLocationBlock(const std::vector<std::string> & serverBlock, std::vector<std::string>::const_iterator  it);

        // setters not difined yet.
        void setCgiExtentions(const std::string & cgiExtentions);
        void setPort(const std::string & port);
        void setServerName(const std::string & serverName);
        void setRoot(const std::string & root);
        void setErrorPage(const std::string & errorPage);
        void setCharSet(const std::string & charSet);
        void setIndexFiles(const std::vector<std::string> & indexFiles);
        // under Construction - done partially.
        void setLocations(const std::vector<std::string> & serverBlock, std::vector<std::string>::const_iterator * it);

        // Under Construction
        void                            createSocket(void);
        void                            bindSocket(void);
        void                            listenForConnection(int maxConnections);

        int                             getSocketFd(void) const;

};

#endif