#ifndef SERVERRESPONSE_HPP
#define SERVERRESPONSE_HPP

# include <vector>
# include <string>

class serverResponce
{
    public:
        std::vector<std::string> responseHeaders;
    private:
        serverResponce();
        ~serverResponce();
};

#endif