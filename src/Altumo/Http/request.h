#ifndef ALTUMO_HTTP_REQUEST_H
#define ALTUMO_HTTP_REQUEST_H


#include <map>
#include <string>


namespace Altumo{
    namespace Http{


        class Request{

            public:
                Request();
                ~Request();

                std::map headers;
                string body;
                bool asynchronous;

        };


    }
}



#endif //ALTUMO_HTTP_REQUEST_H
