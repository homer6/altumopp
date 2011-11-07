#ifndef GEOIP_CLIENT_H
#define GEOIP_CLIENT_H

    #include <stdio.h>
    #include <string>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #include <boost/program_options.hpp>

    #include "location.h"

    using namespace std;

    namespace Altumo{

        class GeoIpClient{

            public:
                GeoIpClient();
                ~GeoIpClient();
                int setProgramOptions( int argc, char** argv );
                string *getLocationByIp( const string ip_address );
                string *getLocationByIp( unsigned ip_address );

            protected:
                string host;
                string ip_address;

        };

    }

#endif //GEOIP_CLIENT_H
