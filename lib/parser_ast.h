#ifndef PARSER_AST_H
#define PARSER_AST_H

#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/optional.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <cmath>
#include <list>

#include "formula_parser.h"
#include "manager.h"

namespace client {
namespace ast {
struct nil {};
struct signed_;
struct program;

struct variable {
  variable(const std::string& name)
      : values(lib::Manager::GetInstance()->GetVariable(name).measurements) {}
  variable(double val) { values.push_back(val); }
  variable(QList<double> vals) : values(vals) {}

  QList<double> values;
};
// clang-format off
typedef boost::variant<
    nil
    , variable
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

namespace client {
namespace ast {
struct eval {
  typedef struct variable result_type;

  struct variable operator()(nil) const {BOOST_ASSERT(0); return variable(0);}

  struct variable operator()(double n) const { return variable(n); }

  struct variable operator()(struct variable var) const { return var; }
  // clang-format on
  struct variable operator()(operation const& x, struct variable lhs) const {
    struct variable rhs = boost::apply_visitor(*this, x.operand_);
    QList<double> result;
    switch (x.operator_) {
      case '+':
        if (lhs.values.size() == 1 || rhs.values.size() == 1) {
          if (lhs.values.size() == 1) std::swap(lhs, rhs);
          for (double i : lhs.values) result.push_back(i + rhs.values[0]);
          return variable(result);
        } else {
          for (int i = 0; i < lhs.values.size(); i++)
            result.push_back(lhs.values[i] + rhs.values[i]);
          return variable(result);
        }
      case '-':
        if (lhs.values.size() == 1 && rhs.values.size() == 1) {
          result.push_back(lhs.values[0] - rhs.values[0]);
          return variable(result);
        }
        if (lhs.values.size() == 1 && rhs.values.size() != 1) {
          for (double i : rhs.values) result.push_back(lhs.values[0] - i);
          return variable(result);
        }
        if (lhs.values.size() != 1 && rhs.values.size() == 1) {
          for (double i : lhs.values) result.push_back(i - rhs.values[0]);
          return variable(result);
        }
        if (lhs.values.size() != 1 && rhs.values.size() != 1) {
          for (int i = 0;
               i < lib::Manager::GetInstance()->GetMeasurementsCount(); i++)
            result.push_back(lhs.values[i] - rhs.values[i]);
          return variable(result);
        }
      case '*':
        if (lhs.values.size() == 1 || rhs.values.size() == 1) {
          if (lhs.values.size() == 1) std::swap(lhs, rhs);
          for (double i : lhs.values) result.push_back(i * rhs.values[0]);
          return variable(result);
        } else {
          for (int i = 0; i < lhs.values.size(); i++)
            result.push_back(lhs.values[i] * rhs.values[i]);
          return variable(result);
        }
      case '/':
        if (lhs.values.size() == 1 && rhs.values.size() == 1) {
          result.push_back(lhs.values[0] / rhs.values[0]);
          return variable(result);
        }
        if (lhs.values.size() == 1 && rhs.values.size() != 1) {
          for (double i : rhs.values) result.push_back(lhs.values[0] / i);
          return variable(result);
        }
        if (lhs.values.size() != 1 && rhs.values.size() == 1) {
          for (double i : lhs.values) result.push_back(i / rhs.values[0]);
          return variable(result);
        }
        if (lhs.values.size() != 1 && rhs.values.size() != 1) {
          for (int i = 0;
               i < lib::Manager::GetInstance()->GetMeasurementsCount(); i++)
            result.push_back(lhs.values[i] / rhs.values[i]);
          return variable(result);
        }
      case '^':
        if (lhs.values.size() == 1 && rhs.values.size() == 1) {
          result.push_back(pow(lhs.values[0], rhs.values[0]));
          return variable(result);
        }
        if (lhs.values.size() == 1 && rhs.values.size() != 1) {
          for (double i : rhs.values) result.push_back(pow(lhs.values[0], i));
          return variable(result);
        }
        if (lhs.values.size() != 1 && rhs.values.size() == 1) {
          for (double i : lhs.values) result.push_back(pow(i, rhs.values[0]));
          return variable(result);
        }
        if (lhs.values.size() != 1 && rhs.values.size() != 1) {
          for (int i = 0;
               i < lib::Manager::GetInstance()->GetMeasurementsCount(); i++)
            result.push_back(pow(lhs.values[i], rhs.values[i]));
          return variable(result);
        }
    }
    BOOST_ASSERT(0);
    return variable(0);
  }

  struct variable operator()(signed_ const& x) const {
    struct variable rhs = boost::apply_visitor(*this, x.operand_);
    QList<double> result;
    switch (x.sign) {
      case '-':
        for (double i : rhs.values) result.push_back(-i);
        return variable(result);
      case '+':
        return rhs;
    }
    BOOST_ASSERT(0);
    return variable(0);
  }

  struct variable operator()(program const& x) const {
    struct variable state = boost::apply_visitor(*this, x.first);
    BOOST_FOREACH (operation const& oper, x.rest) {
      state = (*this)(oper, state);
    }
    return state;
  }
};
}  // namespace ast
}  // namespace client
#endif  // PARSER_AST_H
