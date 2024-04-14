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
  struct program;

  // struct variable
  // {
  //   variable(std::string const& name = "") : name(name) {}
  //   std::string name;
  // };

  typedef boost::variant<
      nil
      // , variable
      , double
      , boost::recursive_wrapper<signed_>
      , boost::recursive_wrapper<program>
      >
      operand;

  struct signed_
  {
    char sign;
    operand operand_;
  };

  struct operation
  {
    char operator_;
    operand operand_;
  };

  struct program
  {
    operand first;
    std::list<operation> rest;
  };
}}

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::signed_,
    (char, sign)
    (client::ast::operand, operand_)
    )

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::operation,
    (char, operator_)
    (client::ast::operand, operand_)
    )

BOOST_FUSION_ADAPT_STRUCT(
    client::ast::program,
    (client::ast::operand, first)
    (std::list<client::ast::operation>, rest)
    )

namespace client { namespace ast
{
  struct eval
  {
    typedef double result_type;

    double operator()(nil) const { BOOST_ASSERT(0); return 0; }
    double operator()(double n) const { return n; }

    // double operator()(variable& var) const
    // {
    //   return find_var_value(var.name);
    // }

    double operator()(operation const& x, double lhs) const
    {
      double rhs = boost::apply_visitor(*this, x.operand_);
      switch (x.operator_)
      {
      case '+': return lhs + rhs;
      case '-': return lhs - rhs;
      case '*': return lhs * rhs;
      case '/': return lhs / rhs;
      }
      BOOST_ASSERT(0);
      return 0;
    }

    double operator()(signed_ const& x) const
    {
      double rhs = boost::apply_visitor(*this, x.operand_);
      switch (x.sign)
      {
      case '-': return -rhs;
      case '+': return +rhs;
      }
      BOOST_ASSERT(0);
      return 0;
    }

    double operator()(program const& x) const
    {
      double state = boost::apply_visitor(*this, x.first);
      BOOST_FOREACH(operation const& oper, x.rest)
      {
        state = (*this)(oper, state);
      }
      return state;
    }
  };
}}
#endif  // PARSER_AST_H
