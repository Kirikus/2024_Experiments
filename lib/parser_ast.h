#ifndef PARSER_AST_H
#define PARSER_AST_H

#include <boost/variant/recursive_variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/optional.hpp>
#include <list>

namespace client { namespace ast
{

  struct nil {};
  struct signed_;
  struct expression;

  struct variable
  {
    variable(std::string const& name = "") : name(name) {}
    std::string name;
  };

  typedef boost::variant<
      nil
      , double
      , variable
      , boost::recursive_wrapper<signed_>
      , boost::recursive_wrapper<expression>
      >
      operand;

  enum optoken
  {
    op_plus,
    op_minus,
    op_times,
    op_divide,
    op_positive,
    op_negative,
  };

  struct signed_
  {
    char sign;
    operand operand_;
  };

  struct operation
  {
    optoken operator_;
    operand operand_;
  };

  struct expression
  {
    operand first;
    std::list<operation> rest;
  };

  // struct expression_list : std::list<expression> {};
}}

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::signed_,
    (char, sign)
    (client::ast::operand, operand_)
    )

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::operation,
    (client::ast::optoken, operator_)
    (client::ast::operand, operand_)
    )

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::expression,
    (client::ast::operand, first)
    (std::list<client::ast::operation>, rest)
    )


#endif  // PARSER_AST_H
