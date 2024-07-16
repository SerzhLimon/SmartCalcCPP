#include "graphview.h"

using namespace s21;

GraphView::GraphView(QWidget* parent) : QDialog(parent), ui(new Ui::GraphView) {
  ui->setupUi(this);
  ui->widget->xAxis->setRange(-100, 100);
  ui->widget->yAxis->setRange(-100, 100);
  setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint);
  setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                 Qt::WindowMinimizeButtonHint);
  this->bind();
}

GraphView::~GraphView() { delete ui; }

void GraphView::Show() {
  if (this->isVisible())
    this->hide();
  else {
    this->show();
    this->focusWidget();
  }
}

void GraphView::AddListener(IController* controller) {
  this->controller = controller;
}

std::vector<float> GraphView::parseStringToVector(std::string& str) {
  std::vector<float> for_gr;
  std::stringstream ss(str);
  std::string token;
  while (std::getline(ss, token, '|')) {
    if (!token.empty()) {
      for_gr.push_back(std::stof(token));
    }
  }
  return for_gr;
}

void GraphView::show_x_min() {
  std::string s = std::to_string(this->controller->Get_x_min());
  const char* str = s.c_str();
  ui->x_min_line->setText(str);
}

void GraphView::show_x_max() {
  std::string s = std::to_string(this->controller->Get_x_max());
  const char* str = s.c_str();
  ui->x_max_line->setText(str);
}

void GraphView::SetOutput(std::string str) {
  if (str.back() == '|') {
    std::vector<float> numbers = parseStringToVector(str);

    ui->widget->clearGraphs();

    QVector<double> x, y;
    for (auto it = numbers.begin(); it != numbers.end(); it++) {
      x += *it;
      y += *(++it);
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);

    show_x_min();
    show_x_max();

    x.clear();
    y.clear();
  }
}

auto GraphView::onClick(Keys key) {
  return [=]() {
    if (this->controller != nullptr) try {
        this->controller->OnClick(key);
      } catch (std::exception e) {
        std::logic_error("Недопустимый ввод!");
      }
  };
}

auto GraphView::TmpChangeView() {
  return [=]() { this->controller->ChangeView(); };
  this->controller->Set_x_max(0);
  this->controller->Set_x_min(0);
}

auto GraphView::clear_xs() {
  return [=]() {
    this->controller->Set_x_min(0);
    this->controller->Set_x_max(0);
  };
}

void GraphView::bind() {
  connect(ui->x_min_add10, &QPushButton::clicked, this,
          this->onClick(X_MIN_ADD10));
  connect(ui->x_min_sub10, &QPushButton::clicked, this,
          this->onClick(X_MIN_SUB10));
  connect(ui->x_min_add25, &QPushButton::clicked, this,
          this->onClick(X_MIN_ADD25));
  connect(ui->x_min_sub25, &QPushButton::clicked, this,
          this->onClick(X_MIN_SUB25));
  connect(ui->x_min_add100, &QPushButton::clicked, this,
          this->onClick(X_MIN_ADD100));
  connect(ui->x_min_sub100, &QPushButton::clicked, this,
          this->onClick(X_MIN_SUB100));

  connect(ui->x_max_add10, &QPushButton::clicked, this,
          this->onClick(X_MAX_ADD10));
  connect(ui->x_max_sub10, &QPushButton::clicked, this,
          this->onClick(X_MAX_SUB10));
  connect(ui->x_max_add25, &QPushButton::clicked, this,
          this->onClick(X_MAX_ADD25));
  connect(ui->x_max_sub25, &QPushButton::clicked, this,
          this->onClick(X_MAX_SUB25));
  connect(ui->x_max_add100, &QPushButton::clicked, this,
          this->onClick(X_MAX_ADD100));
  connect(ui->x_max_sub100, &QPushButton::clicked, this,
          this->onClick(X_MAX_SUB100));

  connect(ui->make_button, &QPushButton::clicked, this, this->clear_xs());
  connect(ui->make_button, &QPushButton::clicked, this,
          this->onClick(GRAPH_BUTTON));

  connect(ui->return_button, &QPushButton::clicked, this,
          this->TmpChangeView());
  connect(ui->return_button, &QPushButton::clicked, this,
          this->onClick(AC_BUTTON));
}

void GraphView::on_x_min_add10_clicked() {
  float x = this->controller->Get_x_min() + 10;
  this->controller->Set_x_min(x);
  show_x_min();
}

void GraphView::on_x_min_add25_clicked() {
  float x = this->controller->Get_x_min() + 25;
  this->controller->Set_x_min(x);
  show_x_min();
}

void GraphView::on_x_min_add100_clicked() {
  float x = this->controller->Get_x_min() + 100;
  this->controller->Set_x_min(x);
  show_x_min();
}

void GraphView::on_x_min_sub10_clicked() {
  float x = this->controller->Get_x_min() - 10;
  this->controller->Set_x_min(x);
  show_x_min();
}

void GraphView::on_x_min_sub25_clicked() {
  float x = this->controller->Get_x_min() - 25;
  this->controller->Set_x_min(x);
  show_x_min();
}

void GraphView::on_x_min_sub100_clicked() {
  float x = this->controller->Get_x_min() - 100;
  this->controller->Set_x_min(x);
  show_x_min();
}

void GraphView::on_x_max_add10_clicked() {
  float x = this->controller->Get_x_max() + 10;
  this->controller->Set_x_max(x);
  show_x_max();
}

void GraphView::on_x_max_add25_clicked() {
  float x = this->controller->Get_x_max() + 25;
  this->controller->Set_x_max(x);
  show_x_max();
}

void GraphView::on_x_max_add100_clicked() {
  float x = this->controller->Get_x_max() + 100;
  this->controller->Set_x_max(x);
  show_x_max();
}

void GraphView::on_x_max_sub10_clicked() {
  float x = this->controller->Get_x_max() - 10;
  this->controller->Set_x_max(x);
  show_x_max();
  ;
}

void GraphView::on_x_max_sub25_clicked() {
  float x = this->controller->Get_x_max() - 25;
  this->controller->Set_x_max(x);
  show_x_max();
}

void GraphView::on_x_max_sub100_clicked() {
  float x = this->controller->Get_x_max() - 100;
  this->controller->Set_x_max(x);
  show_x_max();
}
