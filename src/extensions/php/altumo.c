#include "php_altumo.h"



zend_module_entry altumo_module_entry = {

    #if ZEND_MODULE_API_NO >= 20010901
        STANDARD_MODULE_HEADER,
    #endif
    PHP_ALTUMO_EXTNAME,
    NULL, /* functions */
    NULL, /* MINIT */
    NULL, /* MSHUTDOWN */
    NULL, /* RINIT */
    NULL, /* RSHUTDOWN */
    NULL, /* MINFO */
    #if ZEND_MODULE_API_NO >= 20010901
        PHP_ALTUMO_EXTVER,
    #endif
    STANDARD_MODULE_PROPERTIES

};


#ifdef COMPILE_DL_SAMPLE
    ZEND_GET_MODULE(altumo)
#endif
