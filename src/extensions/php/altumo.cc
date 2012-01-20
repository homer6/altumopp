extern "C"{
    #include "php.h"
}
#include "php_altumo.h"




static function_entry altumo_functions[] = {
    PHP_FE(altumo_run, NULL)
    {NULL, NULL, NULL}
};


zend_module_entry altumo_module_entry = {

    #if ZEND_MODULE_API_NO >= 20010901
        STANDARD_MODULE_HEADER,
    #endif
    PHP_ALTUMO_EXTNAME,
    altumo_functions, /* functions */
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


#ifdef COMPILE_DL_ALTUMO
    extern "C" {
        ZEND_GET_MODULE(altumo)
    }
#endif



PHP_FUNCTION(altumo_run){
    RETURN_STRING("Altumo RUN", 1);
}

