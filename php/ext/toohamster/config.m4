dnl $Id$
dnl config.m4 for extension toohamster

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(toohamster, for toohamster support,
dnl Make sure that the comment is aligned:
dnl [  --with-toohamster             Include toohamster support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(toohamster, whether to enable toohamster support,
dnl Make sure that the comment is aligned:
dnl [  --enable-toohamster           Enable toohamster support])

if test "$PHP_TOOHAMSTER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-toohamster -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/toohamster.h"  # you most likely want to change this
  dnl if test -r $PHP_TOOHAMSTER/$SEARCH_FOR; then # path given as parameter
  dnl   TOOHAMSTER_DIR=$PHP_TOOHAMSTER
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for toohamster files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       TOOHAMSTER_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$TOOHAMSTER_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the toohamster distribution])
  dnl fi

  dnl # --with-toohamster -> add include path
  dnl PHP_ADD_INCLUDE($TOOHAMSTER_DIR/include)

  dnl # --with-toohamster -> check for lib and symbol presence
  dnl LIBNAME=toohamster # you may want to change this
  dnl LIBSYMBOL=toohamster # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TOOHAMSTER_DIR/lib, TOOHAMSTER_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_TOOHAMSTERLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong toohamster lib version or lib not found])
  dnl ],[
  dnl   -L$TOOHAMSTER_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(TOOHAMSTER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(toohamster, toohamster.c, $ext_shared)
fi
