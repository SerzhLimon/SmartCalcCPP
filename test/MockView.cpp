#include "MockView.h"

using namespace s21;

MockView::MockView(std::string input, std::string require) {
  this->input = input;
  this->require = require;
  this->bind();
}

void MockView::bind() {
  this->types_mapping = {{"0", ZERO_BUTTON},
                         {"1", ONE_BUTTON},
                         {"2", TWO_BUTTON},
                         {"3", THREE_BUTTON},
                         {"4", FOUR_BUTTON},
                         {"5", FIVE_BUTTON},
                         {"6", SIX_BUTTON},
                         {"7", SEVEN_BUTTON},
                         {"8", EIGHT_BUTTON},
                         {"9", NINE_BUTTON},
                         {".", POINT_BUTTON},

                         {"+", PLUS_BUTTON},
                         {"-", MINUS_BUTTON},
                         {"*", MULT_BUTTON},
                         {"/", DIVIDE_BUTTON},
                         {"%", PERCENT_BUTTON},
                         {"^(", POW_BUTTON},

                         {"sqrt(", SQRT_BUTTON},
                         {"sin(", SIN_BUTTON},
                         {"cos(", COS_BUTTON},
                         {"tan(", TAN_BUTTON},
                         {"asin(", ASIN_BUTTON},
                         {"acos(", ACOS_BUTTON},
                         {"atan(", ATAN_BUTTON},
                         {"log(", LOG_BUTTON},
                         {"ln(", LN_BUTTON},
                         {"(-", SIGN_BUTTON},
                         {")", CLOSE_BRACKETS_BUTTON},

                         {"=", RESULT_BUTTON}};
}

void MockView::AddListener(IController* controller) {
  this->controller = controller;
}

auto MockView::onClick(Keys key) {
  if (this->controller != nullptr) {
    if (key == RESULT_BUTTON) {
      res = true;
    }
    this->controller->OnClick(key);
  }
}

void MockView::Show() {
  for (size_t input_begin = 0; input_begin < this->input.size();
       input_begin++) {
    auto mapping_iter = this->types_mapping.begin();
    for (; mapping_iter != this->types_mapping.end(); mapping_iter++) {
      if (input_begin == this->input.find(mapping_iter->first)) {
        this->onClick(mapping_iter->second);
        // input_begin += mapping_iter->first.length();
      }
    }
  }
}

void MockView::SetOutput(std::string str) {
  if (res) {
    // std::cout << stof(str) << std::endl;
    // std::cout << stof(require) << std::endl;
    if (stof(str) != stof(require)) {
      throw std::logic_error("Значения не рывны");
    }
  }
}
