#ifndef PARSER_EXPRESSION_H
#define PARSER_EXPRESSION_H

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/spirit/include/qi.hpp>
#include "parser_ast.h"

namespace client {
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct parser : qi::grammar<Iterator, ast::program(), ascii::space_type>
{
  parser();

  qi::rule<Iterator, ast::program(), ascii::space_type> expression;
  qi::rule<Iterator, ast::program(), ascii::space_type> additive_expr;
  qi::rule<Iterator, ast::program(), ascii::space_type> multiplicative_expr;
  qi::rule<Iterator, ast::program(), ascii::space_type> pow_expr;
  qi::rule<Iterator, ast::operand(), ascii::space_type> unary_expr;
  qi::rule<Iterator, ast::operand(), ascii::space_type> primary_expr;
  qi::rule<Iterator, std::string(), ascii::space_type> varname;
};
}

#endif  // PARSER_EXPRESSION_H
