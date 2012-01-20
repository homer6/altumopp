

PHP_ARG_ENABLE(altumo,
    [Whether to enable the "altumo" extension],
    [  enable-altumo         Enable "altumo" extension support])


if test $PHP_ALTUMO != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(ALTUMO_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, ALTUMO_SHARED_LIBADD)
    PHP_NEW_EXTENSION(altumo, altumo.cc, $ext_shared)
fi

