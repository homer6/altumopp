#ifndef ALTUMO_FASTCGI_SERVER_H
#define ALTUMO_FASTCGI_SERVER_H


#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "Session.h"

using boost::asio::ip::tcp;



namespace Altumo{
    namespace FastCgi{


        class Server{

            public:
                Server( boost::asio::io_service& io_service, short port )
                    :io_service_( io_service ), acceptor_( io_service, tcp::endpoint(tcp::v4(), port) )
                {

                    start_accept();

                }

            private:

                void start_accept(){

                    Session* new_session = new Session( io_service_ );
                    acceptor_.async_accept(
                        new_session->socket(),
                        boost::bind( &Server::handle_accept, this, new_session, boost::asio::placeholders::error )
                    );

                }

                void handle_accept( Session* new_session, const boost::system::error_code& error ){

                    if( !error ){
                        new_session->start();
                    }else{
                        delete new_session;
                    }

                    start_accept();

                }

                boost::asio::io_service& io_service_;
                tcp::acceptor acceptor_;

        };

    }
}



#endif //ALTUMO_FASTCGI_SERVER_H
