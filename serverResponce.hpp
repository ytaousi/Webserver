#ifndef SERVERRESPONSE_HPP
#define SERVERRESPONSE_HPP

# include <vector>
# include <string>
# include <map>

class serverResponce
{
    public:
        std::map<std::string, std::string> headerDirectives;
        std::vector<std::string> responseBody;
    private:
        serverResponce();
        ~serverResponce();
};

#endif
