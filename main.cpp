#include <QApplication>

#include "Controller.h"
#include "Model.h"
#include "View.h"
#include "graphview.h"

using namespace s21;

int main(int argc, char** argv) {
  QApplication a(argc, argv);

  IView* view = new View();
  IView* graphview = new GraphView();
  IModel* model = new Model();

  IController* app = new Controller(view, graphview, model);
  // IController *app = new Controller();
  app->Start();
  return a.exec();
}
