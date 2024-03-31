#ifndef PLOT_H
#define PLOT_H

#include "../../lib/manager.h"
#include "../../qcustomplot_lib/qcustomplot.h"
#include "QString"
#include "QTabWidget"

class Plot : public QWidget {
  Q_OBJECT
 public:
  void setManager();
  virtual void draw(QCustomPlot*) = 0;
  virtual void setOptions() = 0;
};

class LinePlot : public Plot {
  Q_OBJECT
 private:
  std::vector<std::vector<int>> colors{
      {255, 0, 0},    // Красный
      {0, 255, 0},    // Зелёный
      {0, 0, 255},    // Синий
      {128, 0, 128},  // Фиолетовый
      {255, 255, 0},  // Жёлтый
      {0, 255, 255},  // Голубой
      {255, 165, 0},  // Оранжевый
      {50, 205, 50}   // Салатовый
  };
  QString title;
  QString X_axisname;
  QString Y_axisname;

 public:
  void draw(QCustomPlot*) override;
  void customization(auto& visual, auto& graph);
  void point_form(int form, auto& graph, int width);
  void line_type(int line, QPen& graphPen);
  void setOptions() override;
};

#endif  // PLOT_H
