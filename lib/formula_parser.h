#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/foreach.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "parser_ast.h"
#include "parser_expression.h"


namespace client {
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
parser<Iterator>::parser() : parser::base_type(expression) {
  qi::int_type int_;
  qi::char_type char_;
  qi::double_type double_;
  qi::lexeme_type lexeme;
  qi::raw_type raw;
  qi::alpha_type alpha;
  // clang-format off
  assignment =
      varname
      >   '='
      >   expression
      ;

  expression =
      additive_expr.alias()
      ;

  additive_expr =
      multiplicative_expr
      >>  *(   (char_('+') > multiplicative_expr)
           |   (char_('-') > multiplicative_expr)
           )
      ;

  multiplicative_expr =
      pow_expr
      >> *(   (char_('*') > pow_expr)
           |   (char_('/') > pow_expr)
           )
      ;

  pow_expr =
      unary_expr
      >> *( char_('^') > unary_expr)
      ;

  unary_expr =
      primary_expr
      |   (char_('-') > primary_expr)
      |   (char_('+') > primary_expr)
      ;

  primary_expr =
      double_
      |   varname
      |   '(' > expression > ')'
      ;

  varname = raw[lexeme[+(alpha) >> *(double_ | alpha | char_('_'))]];
}
}
// clang-format on
#endif  // FORMULA_PARSER_H
