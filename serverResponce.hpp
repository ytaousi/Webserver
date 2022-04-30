#ifndef SERVERRESPONSE_HPP
#define SERVERRESPONSE_HPP

# include <vector>
# include <string>
# include <map>

class serverResponce
{
    public:
        std::map<std::string, std::string>  _headerDirectives;
        std::vector<std::string>            _responseBody;
    private:
        serverResponce();
        ~serverResponce();
};

#endif
