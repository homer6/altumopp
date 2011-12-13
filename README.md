Overview
------------
C++ web framework as a fastcgi process via nginx.


Dependencies
------------

  - Boost 1.37 (apt-get install libboost-all-dev)
  - cmake 2.8.2 (apt-get install cmake)
  - nginx 0.7.65 (apt-get install nginx)

Note: these are just the versions that I used when installing. This program
may run on earlier versions just fine.



Installation
------------

  - git clone git://github.com/homer6/altumopp.git
  - cd altumopp
  - cmake .
  - make


    Configure nginx:


    server {
           listen 81;
           server_name _;

           location / {
                include /etc/nginx/fastcgi_params;
                fastcgi_pass 127.0.0.1:9000;
           }
    }




Usage
-----
  - ./webapp 9000



