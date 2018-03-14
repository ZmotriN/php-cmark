/*
  +----------------------------------------------------------------------+
  | cmark                                                                |
  +----------------------------------------------------------------------+
  | Copyright (c) Joe Watkins 2018                                       |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: krakjoe <krakjoe@php.net>                                    |
  +----------------------------------------------------------------------+
 */
#ifndef PHP_CMARK_NODE_TEXT
#define PHP_CMARK_NODE_TEXT

#include <php.h>

#include <src/common.h>
#include <src/node.h>

zend_class_entry *php_cmark_node_text_ce;
zend_class_entry *php_cmark_node_text_emphasis_ce;
zend_class_entry *php_cmark_node_text_strong_ce;

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_text_construct, 0, 0, 0)
	ZEND_ARG_INFO(0, literal)
ZEND_END_ARG_INFO()

PHP_METHOD(Text, __construct)
{
	zend_string *literal;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRICT_STR(literal)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_node_text_new(getThis(), CMARK_NODE_TEXT, literal);
}

PHP_METHOD(Text, getLiteral)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());

	php_cmark_no_parameters();

	RETURN_STRING(cmark_node_get_literal(n->node));
}

ZEND_BEGIN_ARG_INFO_EX(php_cmark_node_text_set_literal, 0, 0, 1)
	ZEND_ARG_INFO(0, literal)
ZEND_END_ARG_INFO()

PHP_METHOD(Text, setLiteral)
{
	php_cmark_node_t *n = php_cmark_node_fetch(getThis());
	zend_string *literal;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRICT_STR(literal)
	ZEND_PARSE_PARAMETERS_END();

	cmark_node_set_literal(n->node, ZSTR_VAL(literal));

	php_cmark_chain();
}


static zend_function_entry php_cmark_node_text_methods[] = {
	PHP_ME(Text, __construct, php_cmark_node_text_construct, ZEND_ACC_PUBLIC)
	PHP_ME(Text, getLiteral, php_cmark_no_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(Text, setLiteral, php_cmark_node_text_set_literal, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(Emphasis, __construct)
{
	zend_string *literal = NULL;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRICT_STR(literal)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_node_text_new(getThis(), CMARK_NODE_EMPH, literal);
}

static zend_function_entry php_cmark_node_text_emphasis_methods[] = {
	PHP_ME(Emphasis, __construct, php_cmark_node_text_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(Strong, __construct)
{
	zend_string *literal;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRICT_STR(literal)
	ZEND_PARSE_PARAMETERS_END();

	php_cmark_node_text_new(getThis(), CMARK_NODE_STRONG, literal);
}

static zend_function_entry php_cmark_node_text_strong_methods[] = {
	PHP_ME(Strong, __construct, php_cmark_node_text_construct, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(CommonMark_Node_Text) 
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node", "Text", php_cmark_node_text_methods);

	php_cmark_node_text_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node\\Text", "Emphasis", php_cmark_node_text_emphasis_methods);

	php_cmark_node_text_emphasis_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	INIT_NS_CLASS_ENTRY(ce, "CommonMark\\Node\\Text", "Strong", php_cmark_node_text_strong_methods);

	php_cmark_node_text_strong_ce = zend_register_internal_class_ex(&ce, php_cmark_node_ce);

	return SUCCESS;
}

PHP_RINIT_FUNCTION(CommonMark_Node_Text)
{
	php_cmark_node_text_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_text_emphasis_ce->ce_flags |= ZEND_ACC_FINAL;
	php_cmark_node_text_strong_ce->ce_flags |= ZEND_ACC_FINAL;

	return SUCCESS;
}
#endif
