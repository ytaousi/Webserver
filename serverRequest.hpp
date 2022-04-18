#ifndef SERVERREQUEST_HPP
# define SERVERREQUEST_HPP

# include <vector>
# include <string>

class serverRequest
{
    public:
        // Method - uriPath - version 

        std::map<std::string, std::string> headerDirectives;
        std::vector<std::string> requestBody;

    private:
        serverRequest();
        ~serverRequest();
};

#endif
