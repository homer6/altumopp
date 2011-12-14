#ifndef ALTUMO_APPLICATION_H
#define ALTUMO_APPLICATION_H


#include <boost/asio.hpp>

#include "FastCgi/Server.h"

namespace Altumo{

    class Application{

        public:

            void run( short port ){

                FastCgi::Server server( io_service, port );
                io_service.run();

            }

        protected:
            boost::asio::io_service io_service;


    };

}



#endif //ALTUMO_APPLICATION_H
