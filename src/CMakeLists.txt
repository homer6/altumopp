include_directories( ./fastcgi )



#file( GLOB sources *.cc )
#file( GLOB fastcgi_sources ./fastcgi/libfcgi/fcgio.cpp ./fastcgi/libfcgi/fcgi_stdio.c ./fastcgi/libfcgi/fcgiapp.c ./fastcgi/libfcgi/os_unix.c )
add_executable( ../webapp ./server/main.cc )


find_package( Boost 1.42 COMPONENTS system program_options regex date_time filesystem thread REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
target_link_libraries( ../webapp ${Boost_LIBRARIES} )


# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
  message(STATUS "GCC detected, adding compile flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
endif(CMAKE_COMPILER_IS_GNUCXX)
