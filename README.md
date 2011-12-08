Overview
------------
C++ web framework as a fastcgi process via nginx.


Dependencies
------------

  - Boost 1.37 (apt-get install libboost-all-dev)
  - cmake 2.8.2 (apt-get install cmake)
  - spawn fastcgi 1.6.3 (apt-get install spawn-fcgi)
  - nginx 0.7.65 (apt-get install nginx)

Note: these are just the versions that I used when installing. This program
may run on earlier versions just fine.



Installation
------------

  - git clone https://github.com/homer6/some-repository.git
  - cd some-repository
  - cmake .
  - make


    Configure nginx:


    server {
           listen 81;
           server_name _;

           location / {
                    root   /websites/fastcgi_demo;
                    index  index.html;

                    fastcgi_pass 127.0.0.1:9000;
           }
    }



Usage
-----
  - spawn-fcgi -a127.0.0.1 -p9000 -n ./webapp



