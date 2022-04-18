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
        size_t                              responseBodylength;

        serverRequest(const std::string & httpRequestMessage)
        {
            setHeader(httpRequestMessage);
            setBody(httpRequestMessage);
        }
        ~serverRequest()
        {
            headerDirectives.clear();
            requestBody.clear();
        }
    private:
        serverRequest();
        void setHeader(const std::string & httpRequestMessage)
        {
            std::string httpRequestHeader = httpRequestMessage.substr(0, httpRequestMessage.find("\r\n\r\n"));
            std::string httpRequestHeaderFirstLine = httpRequestHeader.substr(0, httpRequestHeader.find("\r\n"));
            std::string httpRequestDirectives = httpRequestHeader.substr(httpRequestHeader.find("\r\n") + 2);
            
            method = httpRequestHeaderFirstLine.substr(0, httpRequestHeaderFirstLine.find(" "));
            uriPath = httpRequestHeaderFirstLine.substr(httpRequestHeaderFirstLine.find(" ") + 1, httpRequestHeaderFirstLine.find("HTTP/") - httpRequestHeaderFirstLine.find(" ") - 1);
            version = httpRequestHeaderFirstLine.substr(httpRequestHeaderFirstLine.find("HTTP/"));

            while (httpRequestDirectives.find("\r\n") != std::string::npos)
            {
                std::string httpRequestDirectiveLine = httpRequestDirectives.substr(0, httpRequestDirectives.find("\r\n"));
                httpRequestDirectives = httpRequestDirectives.substr(httpRequestDirectives.find("\r\n") + 2);
                headerDirectives[httpRequestDirectiveLine.substr(0, httpRequestDirectiveLine.find(":"))] = httpRequestDirectiveLine.substr(httpRequestDirectiveLine.find(":") + 2);
            }
            
        }
        void setBody(const std::string &requestBody);
};

#endif
