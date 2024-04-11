#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/spirit/include/qi.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <string>
#include <list>

namespace client
{
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct calculator : qi::grammar<Iterator, ascii::space_type>
{
  calculator() : calculator::base_type(expression)
  {
    qi::double_type double_;
    qi::lexeme_type lexeme;
    qi::char_type char_;
    qi::uint_type uint_;
    qi::raw_type raw;

    expression =
        additive_expr
        >> *(('+' >> additive_expr)
        |    ('-' >> additive_expr))
        ;

    additive_expr =
        multiplicative_expr
        >> *((char_('+') | char_('-')) > multiplicative_expr)
        ;

    multiplicative_expr =
        primary_expr
        >> *((char_('*') | char_('/')) > primary_expr)
        ;

    primary_expr =
        number
        |   varname
        |   '(' > expression > ')'
        ;

    number = lexeme[double_];

    varname = raw[lexeme[+(char_) >> *(uint_ | '_')]];
  }

  qi::rule<Iterator, ascii::space_type> expression, additive_expr, multiplicative_expr, primary_expr, number, varname;
};
}
#endif  // FORMULA_PARSER_H
