#ifndef PARSER_EXPRESSION_H
#define PARSER_EXPRESSION_H

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/spirit/include/qi.hpp>
#include "parser_ast.h"
#include <vector>

namespace client { namespace parser
{
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;

  template <typename Iterator>
  struct expression : qi::grammar<Iterator, ast::expression(), ascii::space_type>
  {
    expression();

    qi::rule<Iterator, ast::expression(), ascii::space_type> expr;
    qi::rule<Iterator, ast::expression(), ascii::space_type> additive_expr;
    qi::rule<Iterator, ast::expression(), ascii::space_type> multiplicative_expr;
    qi::rule<Iterator, ast::operand(), ascii::space_type> primary_expr;
    qi::rule<Iterator, std::string(), ascii::space_type> varname;
  };
}}

#endif  // PARSER_EXPRESSION_H
