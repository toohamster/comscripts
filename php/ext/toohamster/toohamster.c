
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_toohamster.h"

/* If you declare any globals in php_toohamster.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(toohamster)
*/

/* True global resources - no need for thread safety here */
static int le_toohamster;

/* {{{ toohamster_functions[]
 *
 * Every user visible function must have an entry in toohamster_functions[].
 */
const zend_function_entry toohamster_functions[] = {
	PHP_FE(confirm_toohamster_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in toohamster_functions[] */
};
/* }}} */

/* {{{ toohamster_module_entry
 */
zend_module_entry toohamster_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"toohamster",
	toohamster_functions,
	PHP_MINIT(toohamster),
	PHP_MSHUTDOWN(toohamster),
	PHP_RINIT(toohamster),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(toohamster),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(toohamster),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_TOOHAMSTER_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TOOHAMSTER
ZEND_GET_MODULE(toohamster)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("toohamster.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_toohamster_globals, toohamster_globals)
    STD_PHP_INI_ENTRY("toohamster.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_toohamster_globals, toohamster_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_toohamster_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_toohamster_init_globals(zend_toohamster_globals *toohamster_globals)
{
	toohamster_globals->global_value = 0;
	toohamster_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(toohamster)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(toohamster)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(toohamster)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(toohamster)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(toohamster)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "toohamster support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

PHP_FUNCTION(toohamster_string)
{
    char *str = NULL;
    int argc = ZEND_NUM_ARGS();
    int str_len;
    char *result;

    if (zend_parse_parameters(argc TSRMLS_CC, "s", &str, &str_len) == FAILURE) 
        return;

    str_len = spprintf(&result, 0, "<a href=\"%.78s\">Link</a>", str);
    RETURN_STRINGL(result, str_len, 0); 
}

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_toohamster_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_toohamster_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "toohamster", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
