
#ifndef PHP_TOOHAMSTER_H
#define PHP_TOOHAMSTER_H

extern zend_module_entry toohamster_module_entry;
#define phpext_toohamster_ptr &toohamster_module_entry

#define PHP_TOOHAMSTER_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_TOOHAMSTER_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_TOOHAMSTER_API __attribute__ ((visibility("default")))
#else
#	define PHP_TOOHAMSTER_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(toohamster);
PHP_MSHUTDOWN_FUNCTION(toohamster);
PHP_RINIT_FUNCTION(toohamster);
PHP_RSHUTDOWN_FUNCTION(toohamster);
PHP_MINFO_FUNCTION(toohamster);

PHP_FUNCTION(toohamster_string);
PHP_FUNCTION(confirm_toohamster_compiled);	/* For testing, remove later. */

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(toohamster)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(toohamster)
*/

/* In every utility function you add that needs to use variables 
   in php_toohamster_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as TOOHAMSTER_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define TOOHAMSTER_G(v) TSRMG(toohamster_globals_id, zend_toohamster_globals *, v)
#else
#define TOOHAMSTER_G(v) (toohamster_globals.v)
#endif

#endif	/* PHP_TOOHAMSTER_H */

