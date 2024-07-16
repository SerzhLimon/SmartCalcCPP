#ifndef VIEW_H
#define VIEW_H

#include <QApplication>
#include <QMainWindow>

#include "IController.h"
#include "IView.h"
#include "ui_view.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow, public IView {
  Q_OBJECT

 public:
  View(QWidget* parent = nullptr);
  ~View();

  void AddListener(IController* controller);
  void SetOutput(std::string str);
  void Show();
  void Hide() { this->hide(); }

 private:
  Ui::View* ui;
  IController* controller;

  void bind();
  auto onClick(Keys key);
  auto TmpChangeView();
};

}  //  namespace s21

#endif  // VIEW_H
