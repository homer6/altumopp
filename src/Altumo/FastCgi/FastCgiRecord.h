#ifndef ALTUMO_FASTCGI_RECORD_H
#define ALTUMO_FASTCGI_RECORD_H


#include <boost/cstdint.hpp>


namespace Altumo{
    namespace FastCgi{

        enum FastCgiRecordType {
            FCGI_BEGIN_REQUEST = 1,
            FCGI_ABORT_REQUEST = 2,
            FCGI_END_REQUEST = 3,
            FCGI_PARAMS = 4,
            FCGI_STDIN = 5,
            FCGI_STDOUT = 6,
            FCGI_STDERR = 7,
            FCGI_DATA = 8,
            FCGI_GET_VALUES = 9,
            FCGI_GET_VALUES_RESULT = 10,
            FCGI_UNKNOWN_TYPE = 11
        };

        class FastCgiRecord{

            public:
                FastCgiRecord();
                ~FastCgiRecord();

            protected:
                FastCgiRecordType type;
                uint32_t data_size;
                char *data;

        };

    }
}



#endif //ALTUMO_FASTCGI_RECORD_H
