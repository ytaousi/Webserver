#ifndef SERVERREQUEST_HPP
# define SERVERREQUEST_HPP

# include <vector>
# include <string>
# include <map>

// check some directives in http request header if they are valid.
// check if every line stored ends with '\r\n'
// important request directives: Host, Connection, Content-Length, Transfer-Encoding, Content-Type...


class serverRequest
{
    public:
        serverRequest(const std::string & httpRequestMessage);
        ~serverRequest();
        
        // getters for serverRequest object.
        const std::string &                 getRequestMethod() const;
        const std::string &                 getRequestUriPath() const;
        const std::string &                 getRequestVersion() const;
        std::map<std::string, std::string>  getRequestHeaderDirectives();
        const std::vector<std::string> &    getRequestBody() const;
        size_t                              getRequestBodySize() const;

        // setters for serverRequest object.
        void setHeader(const std::string & httpRequestMessage);
        void setBody(const std::string & httpRequestMessage);
    private:
        // Method - uriPath - version - headerDirectives - responseBody. 
        std::string                         method;
        std::string                         uriPath;
        std::string                         version;
        std::map<std::string, std::string>  headerDirectives;
        std::vector<std::string>            requestBody;
        size_t                              requestBodylength;

        // serverRequest default constructor.
        serverRequest();
        // serverRequest copy constructor
        serverRequest(const serverRequest & other);
        // serverRequest assignment operator.
        serverRequest & operator=(const serverRequest & other);
};

#endif
