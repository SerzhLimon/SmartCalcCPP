#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <qvector.h>

#include <QDialog>
#include <sstream>
#include <vector>

#include "IController.h"
#include "IView.h"
#include "ui_graphview.h"

namespace Ui {
class GraphView;
}

namespace s21 {

class GraphView : public QDialog, public IView {
  Q_OBJECT

 public:
  explicit GraphView(QWidget* parent = nullptr);
  ~GraphView();

  void AddListener(IController* controller);
  void SetOutput(std::string str);
  void Show();
  void Hide() { this->hide(); }

 private slots:
  void on_x_min_add10_clicked();
  void on_x_min_add25_clicked();
  void on_x_min_add100_clicked();
  void on_x_min_sub10_clicked();
  void on_x_min_sub25_clicked();
  void on_x_min_sub100_clicked();
  void on_x_max_add10_clicked();
  void on_x_max_add25_clicked();
  void on_x_max_add100_clicked();
  void on_x_max_sub10_clicked();
  void on_x_max_sub25_clicked();
  void on_x_max_sub100_clicked();

 private:
  Ui::GraphView* ui;
  IController* controller;

  void bind();
  auto onClick(Keys key);

  std::vector<float> parseStringToVector(std::string& str);
  auto TmpChangeView();
  auto clear_xs();

  void show_x_min();
  void show_x_max();
};

}  // namespace s21

#endif  // GRAPHVIEW_H
