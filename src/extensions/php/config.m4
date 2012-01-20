

PHP_ARG_ENABLE(altumo,
    [Whether to enable the "altumo" extension],
    [  enable-altumo         Enable "altumo" extension support])


if test $PHP_ALTUMO != "no"; then
    PHP_SUBST(ALTUMO_SHARED_LIBADD)
    PHP_NEW_EXTENSION(altumo, altumo.c, $ext_shared)
fi

