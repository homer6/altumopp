

#include <cstdlib>
#include <iostream>

#include "../Altumo/Application.h"



int main( int argc, char* argv[] ){

    try{







        if( argc != 2 ){
            std::cerr << "Usage: webapp <port>\n";
            return 1;
        }


        Altumo::Application application;

        application.run( std::atoi(argv[1]) );



    }catch( std::exception& e ){

        std::cerr << "Exception: " << e.what() << "\n";

    }

    return 0;

}
