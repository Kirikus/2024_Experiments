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

BOOST_AUTO_TEST_SUITE(aboba)

BOOST_AUTO_TEST_CASE(simple_parse1) {
  typedef std::string::const_iterator iterator_type;
  typedef client::calculator<iterator_type> calculator;

  boost::spirit::ascii::space_type space;
  calculator calc;

  std::string str = "2 + nsadfmhf";

  std::string::const_iterator iter = str.begin();
  std::string::const_iterator end = str.end();

  bool r = phrase_parse(iter, end, calc, space);

  BOOST_CHECK(r && iter == end);
}

BOOST_AUTO_TEST_CASE(simple_parse2) {
  typedef std::string::const_iterator iterator_type;
  typedef client::calculator<iterator_type> calculator;

  boost::spirit::ascii::space_type space;
  calculator calc;

  std::string str = "2 + 3*6 - mama";

  std::string::const_iterator iter = str.begin();
  std::string::const_iterator end = str.end();

  bool r = phrase_parse(iter, end, calc, space);

  BOOST_CHECK(r && iter == end);
}

BOOST_AUTO_TEST_CASE(simple_parse3) {
  typedef std::string::const_iterator iterator_type;
  typedef client::calculator<iterator_type> calculator;

  boost::spirit::ascii::space_type space;
  calculator calc;

  std::string str = "2 + mama_2*4-(mama_0 - 2)";

  std::string::const_iterator iter = str.begin();
  std::string::const_iterator end = str.end();

  bool r = phrase_parse(iter, end, calc, space);

  BOOST_CHECK(r && iter == end);
}

BOOST_AUTO_TEST_SUITE_END()
