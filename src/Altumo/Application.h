#ifndef ALTUMO_APPLICATION_H
#define ALTUMO_APPLICATION_H


#include <boost/asio.hpp>
#include <queue>

#include "FastCgi/Server.h"
#include "FastCgi/FastCgiRecord.h"

namespace Altumo{

    class Application{

        public:

            void run( short port ){

                FastCgi::Server server( io_service, port );
                io_service.run();

            }

        protected:
            boost::asio::io_service io_service;
            //std::queue< FastCgiRecord* > record_queue;
            //std::queue< FastCgiRecord* > aggregated_record_queue;


    };

}



#endif //ALTUMO_APPLICATION_H
