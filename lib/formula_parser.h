#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/foreach.hpp>

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

    expression =
        term
        >> *(   ('+' >> term)
             |   ('-' >> term)
             )
        ;

    term =
        factor
        >> *(   ('*' >> factor)
             |   ('/' >> factor)
             )
        ;

    factor =
        simple
        |   '(' >> expression >> ')'
        |   ('-' >> factor)
        |   ('+' >> factor)
        ;

    simple = number | varname;

    number = lexeme[double_];

    varname = lexeme[+(char_) >> *(uint_ | '_')];
  }

  qi::rule<Iterator, ascii::space_type> expression, term, factor, number, varname, simple;
};
}
#endif  // FORMULA_PARSER_H
