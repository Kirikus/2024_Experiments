#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/spirit/include/qi.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/optional.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <list>

#include "parser_ast.h"
#include "parser_expression.h"

namespace client {
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
parser<Iterator>::parser() : parser::base_type(expression)
{
  qi::int_type int_;
  qi::char_type char_;
  qi::double_type double_;
  qi::lexeme_type lexeme;

  expression =
      additive_expr.alias()
      ;

  additive_expr =
      multiplicative_expr
      >> *(   (char_('+') > multiplicative_expr)
           |   (char_('-') > multiplicative_expr)
           )
      ;

  multiplicative_expr =
      primary_expr
      >> *(   (char_('*') > primary_expr)
           |   (char_('/') > primary_expr)
           )
      ;

  primary_expr =
      double_
      // |   identifier
      |   '(' > expression > ')'
      ;

  // identifier = lexeme[+(char_)];
}
}
#endif  // FORMULA_PARSER_H
