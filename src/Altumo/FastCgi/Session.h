#ifndef ALTUMO_FASTCGI_SESSION_H
#define ALTUMO_FASTCGI_SESSION_H

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <fstream>

using boost::asio::ip::tcp;



namespace Altumo{
    namespace FastCgi{

        class Session{

            public:

                Session( boost::asio::io_service& io_service ):socket_( io_service ){

                    output_log.open( "log.txt", std::ios::out | std::ios::app );

                }

                ~Session(){

                    output_log.close();

                }


                tcp::socket& socket(){

                    return socket_;

                }


                void start(){

                    socket_.async_read_some(
                        boost::asio::buffer( data_, max_length ),
                        boost::bind( &Session::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred )
                    );

                }


            private:

                void handle_read( const boost::system::error_code& error, size_t bytes_transferred ){

                    if( !error ){

                        std::size_t buffer_size = boost::asio::buffer_size( boost::asio::buffer(data_) );

                        std::cout << bytes_transferred << " " << buffer_size << " " << data_ << std::endl;

                        output_log.write( data_, bytes_transferred );
                        output_log.flush();

                        boost::asio::async_write(
                            socket_,
                            boost::asio::buffer( data_, bytes_transferred ),
                            boost::bind( &Session::handle_write, this, boost::asio::placeholders::error )
                        );

                    }else{

                        delete this;

                    }

                }


                void handle_write( const boost::system::error_code& error ){

                    if( !error ){

                        socket_.async_read_some(
                            boost::asio::buffer( data_, max_length ),
                            boost::bind( &Session::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred )
                        );

                    }else{

                        delete this;

                    }

                }


                tcp::socket socket_;
                enum { max_length = 1024 };
                char data_[max_length];
                std::ofstream output_log;

        };

    }
}



#endif //ALTUMO_FASTCGI_SESSION_H
