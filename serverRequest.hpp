#ifndef SERVERREQUEST_HPP
# define SERVERREQUEST_HPP

# include <vector>
# include <string>
# include <map>

class serverRequest
{
    public:
        // Method - uriPath - version - headerDirectives - responseBody. 
        std::string                         method;
        std::string                         uriPath;
        std::string                         version;
        std::map<std::string, std::string>  headerDirectives;
        std::vector<std::string>            requestBody;

    private:
        serverRequest();
        ~serverRequest();
};

#endif
