#include "Controller.h"

using namespace s21;

Controller::Controller(IView* view, IView* graphview, IModel* model) {
  this->view = view;
  this->graphView = graphview;
  this->model = model;
  if (this->view) this->view->AddListener(this);
  if (graphView) this->graphView->AddListener(this);
  this->activeView = 0;
}

Controller::~Controller() { delete this->view; }

void Controller::OnClick(Keys key) {
  this->model->on_click(key);
  std::string output = this->model->get_output();
  if (!activeView) {
    this->view->SetOutput(output);
  } else
    this->graphView->SetOutput(output);
}

void Controller::ChangeView() {
  this->activeView = !this->activeView;
  this->graphView->Show();
}

void Controller::Start() { this->view->Show(); }

float Controller::Get_x_max() { return x_max_; }

float Controller::Get_x_min() { return x_min_; }

void Controller::Set_x_max(float value) { this->x_max_ = value; }

void Controller::Set_x_min(float value) { this->x_min_ = value; }
