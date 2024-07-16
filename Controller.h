#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "IController.h"
#include "IModel.h"
#include "IView.h"
// #include "View.h"
#include "Model.h"
// #include "graphview.h"

namespace s21 {

class Controller : public IController {
 public:
  // Controller();
  Controller(IView* view, IView* graphview, IModel* model);
  ~Controller();

  void OnClick(Keys key);
  void ChangeView();
  void Start();

  float Get_x_max();
  float Get_x_min();
  void Set_x_max(float value);
  void Set_x_min(float value);

 private:
  IView* view;
  IView* graphView;
  IModel* model;

  int activeView;
  float x_min_ = 0;
  float x_max_ = 0;
};

}  //  namespace s21

#endif  // CONTROLLER_H
