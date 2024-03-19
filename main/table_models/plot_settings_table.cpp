#include "QVariant"
#include "manager.h"
#include "naming_table.h"

namespace plot_settings_shell {
enum class Data : size_t { columnCount = 5 };
enum class ColumnNames : QString {
  visible = "Visible",
  width = "Width",
  point_form = "Point form",
  line_type = "Line type",
  color = "Color"
};
}  // namespace plot_settings_shell
