#ifndef PHP_ALTUMO_H
#define PHP_ALTUMO_H

    #define PHP_ALTUMO_EXTNAME "altumo"
    #define PHP_ALTUMO_EXTVER "0.1"

    #ifdef HAVE_CONFIG_H
        #include "config.h"
    #endif


    extern "C" {
        #include "php.h"
    }

    PHP_FUNCTION(altumo_run);


    extern zend_module_entry altumo_module_entry;
    #define phpext_altumo_ptr &altumo_module_entry


#endif
