//
// A simple CGI program.
//
// Outputs only "Hello there, universe." and saves a session cookie "test=check" to the browser.
//

#define BOOST_CGI_ENABLE_SESSIONS

#include <iostream>
#include <boost/cgi/fcgi.hpp>

namespace fcgi = boost::fcgi;

int main(){

    try {

        // Construct a request. Parses all GET, POST and environment data,
        // as well as cookies.
        fcgi::request req;
        // Using a response is the simplest way to write data back to the client.
        fcgi::response resp;

        // This is a minimal response. The cgi::cookie(...) may go before or after
        // the response text.
        resp << "Hello there, universe."
            << fcgi::cookie( "test", "check" )
            << fcgi::charset( "ascii" )
        ;
        //resp.set(cgi::cookie("test", "check"));

        // Leave this function, after sending the response and closing the request.
        // Returns 0 on success.
        return fcgi::commit( req, resp );

    } catch(std::exception& e) {

        std::cout<< "Content-type: text/plain\r\n\r\n"
        << "Error: " << e.what() << std::endl;
        return 1;

    } catch(...) {

        std::cout<< "Content-type: text/plain\r\n\r\n"
        << "Unexpected exception." << std::endl;
        return 1;

    }

}
