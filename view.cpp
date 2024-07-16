#include "View.h"

#define WRONG_ACTION                                                        \
  "border-style: solid;border-width: 1px;border-color: red;border-radius: " \
  "12px; padding-right: 10px; margin: 5px 5px;"
#define RIGHT_ACTION                                                          \
  "border-style: solid;border-width: 1px;border-color: black;border-radius: " \
  "12px; padding-right: 10px; margin: 5px 5px;"

using namespace s21;

View::View(QWidget *parent) : QMainWindow(parent), ui(new Ui::View) {
  this->ui->setupUi(this);
  this->bind();
}

View::~View() { delete this->ui; }

void View::Show() { this->show(); }

void View::AddListener(IController *controller) {
  this->controller = controller;
}

void View::SetOutput(std::string str) {
  const char *output = str.c_str();
  this->ui->label->setText(output);
}

auto View::onClick(Keys key) {
  return [=]() {
    if (this->controller != nullptr) try {
        this->controller->OnClick(key);
        this->ui->label->setStyleSheet(RIGHT_ACTION);
      } catch (std::exception e) {
        this->ui->label->setStyleSheet(WRONG_ACTION);
      }
  };
}

auto View::TmpChangeView() {
  return [=]() { this->controller->ChangeView(); };
}

void View::bind() {
  connect(ui->zero_button, &QPushButton::clicked, this,
          this->onClick(ZERO_BUTTON));
  connect(ui->one_button, &QPushButton::clicked, this,
          this->onClick(ONE_BUTTON));
  connect(ui->two_button, &QPushButton::clicked, this,
          this->onClick(TWO_BUTTON));
  connect(ui->three_button, &QPushButton::clicked, this,
          this->onClick(THREE_BUTTON));
  connect(ui->four_button, &QPushButton::clicked, this,
          this->onClick(FOUR_BUTTON));
  connect(ui->five_button, &QPushButton::clicked, this,
          this->onClick(FIVE_BUTTON));
  connect(ui->six_button, &QPushButton::clicked, this,
          this->onClick(SIX_BUTTON));
  connect(ui->seven_button, &QPushButton::clicked, this,
          this->onClick(SEVEN_BUTTON));
  connect(ui->eight_button, &QPushButton::clicked, this,
          this->onClick(EIGHT_BUTTON));
  connect(ui->nine_button, &QPushButton::clicked, this,
          this->onClick(NINE_BUTTON));

  connect(ui->x_button, &QPushButton::clicked, this, this->onClick(X_BUTTON));
  connect(ui->point_button, &QPushButton::clicked, this,
          this->onClick(POINT_BUTTON));

  connect(ui->plus_button, &QPushButton::clicked, this,
          this->onClick(PLUS_BUTTON));
  connect(ui->minus_button, &QPushButton::clicked, this,
          this->onClick(MINUS_BUTTON));
  connect(ui->mult_button, &QPushButton::clicked, this,
          this->onClick(MULT_BUTTON));
  connect(ui->divide_button, &QPushButton::clicked, this,
          this->onClick(DIVIDE_BUTTON));
  connect(ui->percent_button, &QPushButton::clicked, this,
          this->onClick(PERCENT_BUTTON));
  connect(ui->sqrt_button, &QPushButton::clicked, this,
          this->onClick(SQRT_BUTTON));
  connect(ui->pow_button, &QPushButton::clicked, this,
          this->onClick(POW_BUTTON));

  connect(ui->sin_button, &QPushButton::clicked, this,
          this->onClick(SIN_BUTTON));
  connect(ui->cos_button, &QPushButton::clicked, this,
          this->onClick(COS_BUTTON));
  connect(ui->tan_button, &QPushButton::clicked, this,
          this->onClick(TAN_BUTTON));

  connect(ui->asin_button, &QPushButton::clicked, this,
          this->onClick(ASIN_BUTTON));
  connect(ui->acos_button, &QPushButton::clicked, this,
          this->onClick(ACOS_BUTTON));
  connect(ui->atan_button, &QPushButton::clicked, this,
          this->onClick(ATAN_BUTTON));

  connect(ui->log_button, &QPushButton::clicked, this,
          this->onClick(LOG_BUTTON));
  connect(ui->ln_button, &QPushButton::clicked, this, this->onClick(LN_BUTTON));

  connect(ui->open_brackets_button, &QPushButton::clicked, this,
          this->onClick(OPEN_BRACKETS_BUTTON));
  connect(ui->close_brackets_button, &QPushButton::clicked, this,
          this->onClick(CLOSE_BRACKETS_BUTTON));

  connect(ui->sign_button, &QPushButton::clicked, this,
          this->onClick(SIGN_BUTTON));
  connect(ui->delete_button, &QPushButton::clicked, this,
          this->onClick(DELETE_BUTTON));
  connect(ui->ac_button, &QPushButton::clicked, this, this->onClick(AC_BUTTON));

  connect(ui->result_button, &QPushButton::clicked, this,
          this->onClick(RESULT_BUTTON));
  connect(ui->graph_button, &QPushButton::clicked, this, this->TmpChangeView());
}
