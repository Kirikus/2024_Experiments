#include "formula_parser.h"
#include "parser_ast.h"
#include "parser_expression.h"

double find_var_value(std::string name)
{
  if (name == "mama") return 2; else return 0;
}
