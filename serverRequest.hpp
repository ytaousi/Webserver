#ifndef SERVERREQUEST_HPP
# define SERVERREQUEST_HPP

# include <vector>
# include <string>

class serverRequest
{
    public:
        std::vector<std::string> requestHeaders;
    private:
        serverRequest();
        ~serverRequest();
};

#endif