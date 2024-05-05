#include <QApplication>
#include <iostream>
#include <random>

#include "../lib/formula_parser.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

bool parser_test_func(std::string str, client::ast::variable result)
{
  boost::spirit::ascii::space_type space;

  typedef std::string::const_iterator iterator_type;
  typedef client::parser<iterator_type> parser;
  typedef client::ast::program ast_program;
  typedef client::ast::eval ast_eval;

  parser pars;
  ast_program program;
  ast_eval eval;

  std::string::const_iterator iter = str.begin();
  std::string::const_iterator end = str.end();
  bool r = phrase_parse(iter, end, pars, space, program);
  qDebug() << eval(program).values[0];
  return r && iter == end/* && eval(program).values == result.values*/;
}

BOOST_AUTO_TEST_SUITE(parser)

BOOST_AUTO_TEST_CASE(simple) {

  BOOST_CHECK(parser_test_func("9/3", client::ast::variable(3)));

}

BOOST_AUTO_TEST_SUITE_END()
