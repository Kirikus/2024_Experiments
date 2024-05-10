#include "scatter_plot_2d.h"

#include "manager.h"

void ScatterPlot2D::Draw() {
  clearGraphs();

  if (lib::Manager::GetInstance()->GetVariablesCount() <= std::max(x_, y_))
    return;

  const lib::Variable& variable_x =
      lib::Manager::GetInstance()->GetVariable(x_);

  const lib::Variable& variable_y =
      lib::Manager::GetInstance()->GetVariable(y_);

  if (variable_x.GetMeasurementsCount() == 0 ||
      variable_y.GetMeasurementsCount() == 0)
    return;

  QCPGraph* graph = addGraph();

  graph->setLineStyle(QCPGraph::lsNone);

  QVector<double> xAxis_data;
  QVector<double> yAxis_data;

  if (variable_y.visual.point_shape == QCPScatterStyle::ScatterShape::ssNone) {
    graph->setScatterStyle(QCPScatterStyle::ScatterShape::ssDisc);
  } else {
    graph->setScatterStyle(variable_y.visual.point_shape);
  }

  graph->setPen(QPen(QBrush(variable_y.visual.color), variable_y.visual.width,
                     variable_y.visual.line_type));

  for (int j = 0; j < variable_x.GetMeasurementsCount(); j++) {
    xAxis_data.push_back(variable_x.measurements[j]);
    yAxis_data.push_back(variable_y.measurements[j]);
  }
  xAxis->setLabel("Axis " + variable_x.naming.title);
  yAxis->setLabel("Axis " + variable_y.naming.title);
  graph->setData(xAxis_data, yAxis_data);

  setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  replot();
}

void ScatterPlot2D::Options() {
  OptionsScatter2D a(index_x_, index_y_);
  a.exec();

  x_ = a.choose_AxisX();
  y_ = a.choose_AxisY();

  index_x_ = a.get()->AxisXComboBox->currentIndex();
  index_y_ = a.get()->AxisYComboBox->currentIndex();

  Draw();
}

OptionsScatter2D::OptionsScatter2D(int index_x_, int index_y_)
    : ui(new Ui::DialogScattetPlot2D) {
  ui->setupUi(this);

  setWindowTitle("ScatterPlot2D options");

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->AxisXComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }
  ui->AxisXComboBox->setCurrentIndex(index_x_);

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->AxisYComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }
  ui->AxisYComboBox->setCurrentIndex(index_y_);

  connect(ui->okPushButton, &QPushButton::clicked, this, &QDialog::close);
}

int OptionsScatter2D::choose_AxisX() {
  return ui->AxisXComboBox->currentIndex();
}

int OptionsScatter2D::choose_AxisY() {
  return ui->AxisYComboBox->currentIndex();
}

OptionsScatter2D::~OptionsScatter2D() { delete ui; }
