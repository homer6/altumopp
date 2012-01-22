include_directories( ./fastcgi )

# set(fastcgipp_lib)
link_directories( "./fastcgi/fastcgi++/fastcgi++-1.2/lib" )

#file( GLOB sources *.cc )
#file( GLOB fastcgi_sources ./fastcgi/libfcgi/fcgio.cpp ./fastcgi/libfcgi/fcgi_stdio.c ./fastcgi/libfcgi/fcgiapp.c ./fastcgi/libfcgi/os_unix.c )

add_executable( ../webapp ./server/main3.cc )

#find_library(FASTCGIPP fastcgipp PATHS ./fastcgi/fastcgi++/fastcgi++-1.2/lib )

#add_executable( ../geoip ./client/main.cc ${sources} )



find_package( Boost 1.40 COMPONENTS system program_options regex thread REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )


target_link_libraries( ../webapp ${Boost_LIBRARIES} fastcgipp )



#FIND_PATH( FCGI_INCLUDE_DIR fastcgi.h )
#IF( NOT FCGI_INCLUDE_DIR )
#    FIND_PATH( FCGI_INCLUDE_DIR fastcgi.h ${PROJECT_SOURCE_DIR}/fastcgi_devkit )
#ENDIF()
#INCLUDE_DIRECTORIES( ${FCGI_INCLUDE_DIR} )







# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
  message(STATUS "GCC detected, adding compile flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
endif(CMAKE_COMPILER_IS_GNUCXX)
