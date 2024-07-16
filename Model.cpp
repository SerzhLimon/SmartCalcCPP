#include "Model.h"

using namespace s21;

Model::Model() {
  this->bind_keys();
  this->bind_types();
}

Model::~Model() {}

std::string Model::get_output() { return input_str_; }

void Model::on_click(Keys key) { (this->*key_mapping[key])(); }

void Model::bind_keys() {
  this->key_mapping = {{ZERO_BUTTON, &Model::print_zero},
                       {ONE_BUTTON, &Model::print_one},
                       {TWO_BUTTON, &Model::print_two},
                       {THREE_BUTTON, &Model::print_three},
                       {FOUR_BUTTON, &Model::print_four},
                       {FIVE_BUTTON, &Model::print_five},
                       {SIX_BUTTON, &Model::print_six},
                       {SEVEN_BUTTON, &Model::print_seven},
                       {EIGHT_BUTTON, &Model::print_eightg},
                       {NINE_BUTTON, &Model::print_nine},

                       {POINT_BUTTON, &Model::print_point},

                       {PLUS_BUTTON, &Model::print_plus},
                       {MINUS_BUTTON, &Model::print_minus},
                       {MULT_BUTTON, &Model::print_mult},
                       {DIVIDE_BUTTON, &Model::print_divide},
                       {PERCENT_BUTTON, &Model::print_percent},
                       {POW_BUTTON, &Model::print_pow},

                       {SQRT_BUTTON, &Model::print_sqrt},
                       {SIN_BUTTON, &Model::print_sin},
                       {COS_BUTTON, &Model::print_cos},
                       {TAN_BUTTON, &Model::print_tan},
                       {ASIN_BUTTON, &Model::print_asin},
                       {ACOS_BUTTON, &Model::print_acos},
                       {ATAN_BUTTON, &Model::print_atan},
                       {LOG_BUTTON, &Model::print_log},
                       {LN_BUTTON, &Model::print_ln},

                       {OPEN_BRACKETS_BUTTON, &Model::print_open_b},
                       {CLOSE_BRACKETS_BUTTON, &Model::print_close_b},

                       {AC_BUTTON, &Model::print_ac},
                       {DELETE_BUTTON, &Model::print_delete},

                       {SIGN_BUTTON, &Model::print_sign},
                       {X_BUTTON, &Model::print_x},
                       {RESULT_BUTTON, &Model::res_clicked},
                       {GRAPH_BUTTON, &Model::graph_clicked},

                       {X_MIN_ADD10, &Model::x_min_add10},
                       {X_MIN_SUB10, &Model::x_min_sub10},
                       {X_MIN_ADD25, &Model::x_min_add25},
                       {X_MIN_SUB25, &Model::x_min_sub25},
                       {X_MIN_ADD100, &Model::x_min_add100},
                       {X_MIN_SUB100, &Model::x_min_sub100},

                       {X_MAX_ADD10, &Model::x_max_add10},
                       {X_MAX_SUB10, &Model::x_max_sub10},
                       {X_MAX_ADD25, &Model::x_max_add25},
                       {X_MAX_SUB25, &Model::x_max_sub25},
                       {X_MAX_ADD100, &Model::x_max_add100},
                       {X_MAX_SUB100, &Model::x_max_sub100}};
}

void Model::bind_types() {
  this->types_mapping = {
      {"+", Node{OPERATOR, PLUS, LOW, &Model::handler_plus}},
      {"-", Node{OPERATOR, MINUS, LOW, &Model::handler_minus}},
      {"*", Node{OPERATOR, MULT, MEDIUM, &Model::handler_mult}},
      {"/", Node{OPERATOR, DIVIDE, MEDIUM, &Model::handler_div}},
      {"%", Node{OPERATOR, PERCENT, MEDIUM, &Model::handler_percent}},
      {"^", Node{OPERATOR, POW, HIGH, &Model::handler_pow}},

      {"sqrt", Node{FUNCTION, SQRT, HIGH, &Model::handler_sqrt}},
      {"~", Node{FUNCTION, UN_MINUS, LOW, &Model::handler_umin}},
      {"sin", Node{FUNCTION, SIN, HIGH, &Model::handler_sin}},
      {"cos", Node{FUNCTION, COS, HIGH, &Model::handler_cos}},
      {"tan", Node{FUNCTION, TAN, HIGH, &Model::handler_tan}},
      {"asin", Node{FUNCTION, ASIN, HIGH, &Model::handler_asin}},
      {"acos", Node{FUNCTION, ACOS, HIGH, &Model::handler_acos}},
      {"atan", Node{FUNCTION, ATAN, HIGH, &Model::handler_atan}},
      {"log", Node{FUNCTION, LOG, HIGH, &Model::handler_log}},
      {"ln", Node{FUNCTION, LN, HIGH, &Model::handler_ln}}};
}

void Model::push_open_brackets() {
  tmp_list_.push_back(Node(OPEN_B, 0, VERY_HIGH, nullptr));
}

void Model::push_other_to_polish() {
  if (!(tmp_list_.empty()))
    while (!(tmp_list_.empty())) {
      polish_list_.push_back(tmp_list_.back());
      tmp_list_.pop_back();
    }
}

void Model::push_between_brackets() {
  while (tmp_list_.back().type != OPEN_B) {
    polish_list_.push_back(tmp_list_.back());
    tmp_list_.pop_back();
  }
  tmp_list_.pop_back();
}

void Model::push_digit(std::string::iterator& it, std::string& substr) {
  auto tmp_it = it;
  while (isdigit(*tmp_it) || *tmp_it == '.') {
    substr.push_back(*tmp_it);
    tmp_it++;
  }
  polish_list_.push_back(Node(DIGIT, stof(substr), VERY_HIGH, nullptr));
  substr.clear();
  it = tmp_it;
}

void Model::search_oper_or_func(std::string::iterator& it,
                                std::string& substr) {
  while (it != input_str_.end()) {
    substr.push_back(*it);
    it++;
    if (types_mapping.find(substr) != types_mapping.end()) break;
  }
}

bool Model::check_prioryty_in_tmp(std::string& substr) {
  if ((tmp_list_.back().prioryty >= types_mapping[substr].prioryty) &&
      tmp_list_.back().type != OPEN_B && !(tmp_list_.empty()))
    return true;
  return false;
}

void Model::push_high_prioryty(Node node) {
  while (!tmp_list_.empty() && tmp_list_.back().type != OPEN_B) {
    polish_list_.push_back(tmp_list_.back());
    tmp_list_.pop_back();
    if (tmp_list_.back().prioryty < node.prioryty) break;
  }
}

void Model::make_polish_list() {
  std::string substr;
  auto it = input_str_.begin();
  while (it != input_str_.end()) {
    if (*it == '(') {
      push_open_brackets();
      it++;
    } else if (isdigit(*it) || *it == '.')
      push_digit(it, substr);
    else if (*it == ')') {
      push_between_brackets();
      it++;
    } else {
      search_oper_or_func(it, substr);
      if (check_prioryty_in_tmp(substr)) {
        push_high_prioryty(types_mapping[substr]);
      }
      tmp_list_.push_back(types_mapping[substr]);
      substr.clear();
    }
  }
  push_other_to_polish();
}

bool Model::check_two_prev_node(std::list<Node>::iterator& it) {
  bool res = false;
  auto tmp_it = it;
  if (tmp_it != polish_list_.begin()) {
    tmp_it--;
    if (tmp_it != polish_list_.begin() && tmp_it->type == DIGIT) {
      tmp_it--;
      if (tmp_it->type == DIGIT) {
        res = true;
      }
    }
  }
  return res;
}

void Model::calc_operation(std::list<Node>::iterator& it) {
  auto tmp_it = it;
  float res = (this->*tmp_it->handler)((--tmp_it)->value, (--tmp_it)->value);

  tmp_it++;
  tmp_it = polish_list_.erase(tmp_it);
  tmp_it--;
  tmp_it = polish_list_.erase(tmp_it);

  tmp_it->value = res;
  tmp_it->type = DIGIT;
  it = tmp_it;
}

bool Model::check_one_prev_node(std::list<Node>::iterator& it) {
  bool res = false;
  auto tmp_it = it;
  if (tmp_it != polish_list_.begin()) {
    tmp_it--;
    if (tmp_it->type == DIGIT) res = true;
  }
  return res;
}

void Model::calc_function(std::list<Node>::iterator& it) {
  auto tmp_it = it;
  float res = (this->*tmp_it->handler)((--tmp_it)->value, 0);

  tmp_it = polish_list_.erase(tmp_it);
  tmp_it->value = res;
  tmp_it->type = DIGIT;
  it = tmp_it;
}

bool Model::check_digit_in_list() {
  for (auto iter = polish_list_.begin(); iter != polish_list_.end(); iter++)
    if (iter->type != DIGIT) return false;
  return true;
}

void Model::add_digits() {
  float result = 0;
  for (auto iter = polish_list_.begin(); iter != polish_list_.end(); iter++)
    result += iter->value;
  polish_list_.clear();
  polish_list_.push_back(Node(DIGIT, result, VERY_HIGH, nullptr));
}

void Model::calculate() {
  auto it = polish_list_.end();
  it--;

  while (polish_list_.size() != 1) {
    if (it->type == OPERATOR) {
      if (check_two_prev_node(it)) {
        calc_operation(it);
      } else
        it--;
    } else if (it->type == FUNCTION) {
      if (check_one_prev_node(it)) {
        calc_function(it);
      } else
        it--;
    } else
      it--;
    if (it == polish_list_.begin()) {
      if (check_digit_in_list()) add_digits();
      it = polish_list_.end();
      it--;
    }
  }
  this->input_str_ = std::to_string(it->value);
  polish_list_.clear();
}

void Model::print_zero() {
  char choose = this->input_str_.back();
  if (choose == ')') {
    input_str_.append("*0.");
    point = false;
  } else if (is_action(choose) || !(input_str_.size())) {
    input_str_.append("0.");
    point = false;
  } else
    input_str_.push_back('0');
}

void Model::print_one() {
  char choose = this->input_str_.back();
  if (choose == ')' || choose == 'x') input_str_.push_back('*');
  input_str_.push_back('1');
}

void Model::print_two() {
  char choose = this->input_str_.back();
  if (choose == ')' || choose == 'x') input_str_.push_back('*');
  input_str_.push_back('2');
}

void Model::print_three() {
  char choose = this->input_str_.back();
  if (choose == ')' || choose == 'x') input_str_.push_back('*');
  input_str_.push_back('3');
}

void Model::print_four() {
  char choose = this->input_str_.back();
  if (choose == ')' || choose == 'x') input_str_.push_back('*');
  input_str_.push_back('4');
}

void Model::print_five() {
  char choose = this->input_str_.back();
  if (choose == ')' || choose == 'x') input_str_.push_back('*');
  input_str_.push_back('5');
}

void Model::print_six() {
  char choose = this->input_str_.back();
  if (choose == ')' || choose == 'x') input_str_.push_back('*');
  input_str_.push_back('6');
}

void Model::print_seven() {
  char choose = this->input_str_.back();
  if (choose == ')' || choose == 'x') input_str_.push_back('*');
  input_str_.push_back('7');
}

void Model::print_eightg() {
  char choose = this->input_str_.back();
  if (choose == ')' || choose == 'x') input_str_.push_back('*');
  input_str_.push_back('8');
}

void Model::print_nine() {
  char choose = this->input_str_.back();
  if (choose == ')' || choose == 'x') input_str_.push_back('*');
  input_str_.push_back('9');
}

void Model::print_point() {
  char choose = this->input_str_.back();
  if (!isdigit(choose) || point == false || choose == 'x')
    throw std::logic_error("Недопустимый ввод!");
  input_str_.push_back('.');
  point = false;
}

void Model::print_plus() {
  char choose = this->input_str_.back();
  if (input_str_.empty() || choose == '(')
    throw std::logic_error("Недопустимый ввод!");
  if (is_action(choose))
    input_str_.back() = '+';
  else
    input_str_.push_back('+');
  point = true;
}

void Model::print_minus() {
  char choose = this->input_str_.back();
  if (input_str_.empty() || choose == '(')
    throw std::logic_error("Недопустимый ввод!");
  if (is_action(choose))
    input_str_.back() = '-';
  else
    input_str_.push_back('-');
  point = true;
}

void Model::print_mult() {
  char choose = this->input_str_.back();
  if (input_str_.empty() || choose == '(')
    throw std::logic_error("Недопустимый ввод!");
  if (is_action(choose))
    input_str_.back() = '*';
  else
    input_str_.push_back('*');
  point = true;
}

void Model::print_divide() {
  char choose = this->input_str_.back();
  if (input_str_.empty() || choose == '(')
    throw std::logic_error("Недопустимый ввод!");
  if (is_action(choose))
    input_str_.back() = '/';
  else
    input_str_.push_back('/');
  point = true;
}

void Model::print_percent() {
  char choose = this->input_str_.back();
  if (input_str_.empty() || choose == '(')
    throw std::logic_error("Недопустимый ввод!");
  if (is_action(choose))
    input_str_.back() = '%';
  else
    input_str_.push_back('%');
  point = true;
}

void Model::print_pow() {
  char choose = this->input_str_.back();
  if (input_str_.empty() || choose == '(')
    throw std::logic_error("Недопустимый ввод!");
  if (is_action(choose))
    input_str_.back() = '^';
  else
    input_str_.push_back('^');
  input_str_.push_back('(');
  ;
  count_of_open_b++;
  point = true;
}

void Model::print_sqrt() {
  std::string str = "sqrt(";
  char choose = this->input_str_.back();
  if (isdigit(choose) || choose == ')' || choose == 'x' || choose == '.')
    input_str_.push_back('*');
  input_str_.append(str);
  count_of_open_b++;
  point = true;
}

void Model::print_sin() {
  std::string str = "sin(";
  char choose = this->input_str_.back();
  if (isdigit(choose) || choose == ')' || choose == 'x' || choose == '.')
    input_str_.push_back('*');
  input_str_.append(str);
  count_of_open_b++;
  point = true;
}

void Model::print_cos() {
  std::string str = "cos(";
  char choose = this->input_str_.back();
  if (isdigit(choose) || choose == ')' || choose == 'x' || choose == '.')
    input_str_.push_back('*');
  input_str_.append(str);
  count_of_open_b++;
  point = true;
}

void Model::print_tan() {
  std::string str = "tan(";
  char choose = this->input_str_.back();
  if (isdigit(choose) || choose == ')' || choose == 'x' || choose == '.')
    input_str_.push_back('*');
  input_str_.append(str);
  count_of_open_b++;
  point = true;
}

void Model::print_asin() {
  std::string str = "asin(";
  char choose = this->input_str_.back();
  if (isdigit(choose) || choose == ')' || choose == 'x' || choose == '.')
    input_str_.push_back('*');
  input_str_.append(str);
  count_of_open_b++;
  point = true;
}

void Model::print_acos() {
  std::string str = "acos(";
  char choose = this->input_str_.back();
  if (isdigit(choose) || choose == ')' || choose == 'x' || choose == '.')
    input_str_.push_back('*');
  input_str_.append(str);
  count_of_open_b++;
  point = true;
}

void Model::print_atan() {
  std::string str = "atan(";
  char choose = this->input_str_.back();
  if (isdigit(choose) || choose == ')' || choose == 'x' || choose == '.')
    input_str_.push_back('*');
  input_str_.append(str);
  count_of_open_b++;
  point = true;
}

void Model::print_log() {
  std::string str = "log(";
  char choose = this->input_str_.back();
  if (isdigit(choose) || choose == ')' || choose == 'x' || choose == '.')
    input_str_.push_back('*');
  input_str_.append(str);
  count_of_open_b++;
  point = true;
}

void Model::print_ln() {
  std::string str = "ln(";
  char choose = this->input_str_.back();
  if (isdigit(choose) || choose == ')' || choose == 'x' || choose == '.')
    input_str_.push_back('*');
  input_str_.append(str);
  count_of_open_b++;
  point = true;
}

void Model::print_open_b() {
  char choose = this->input_str_.back();
  if (isdigit(choose) || choose == ')' || choose == 'x' || choose == '.')
    input_str_.push_back('*');
  input_str_.push_back('(');
  count_of_open_b++;
  point = true;
}

void Model::print_close_b() {
  char choose = this->input_str_.back();
  if (is_action(choose) || choose == '(' || !count_of_open_b)
    throw std::logic_error("Недопустимый ввод!");
  input_str_.push_back(')');
  count_of_open_b--;
  point = true;
}

void Model::print_ac() {
  input_str_.clear();
  input_str_tmp_.clear();
  point = true;
  count_of_open_b = 0;
  with_x = false;
  x_min_ = 0;
  x_max_ = 0;
}

void Model::print_delete() {
  if (input_str_.empty()) throw std::logic_error("Недопустимый ввод!");
  char choose = this->input_str_.back();
  if (choose == '(') {
    input_str_.pop_back();
    count_of_open_b--;
    if (islower(input_str_.back()))
      while (islower(input_str_.back())) input_str_.pop_back();
  } else if (choose == '.') {
    input_str_.pop_back();
    point = true;
    choose = this->input_str_.back();
    if (choose == '0') input_str_.pop_back();
  } else if (choose == ')') {
    count_of_open_b++;
    input_str_.pop_back();
  } else
    input_str_.pop_back();
}

void Model::print_sign() {
  if (this->input_str_.empty()) {
    input_str_.append("(-");
    count_of_open_b++;
  } else if (input_str_.size() == 1 && isdigit(input_str_.back())) {
    for_single_digit();
  } else if (input_str_.front() == '-') {
    input_str_.erase(input_str_.begin());
  } else {
    char choose = this->input_str_.back();
    switch (choose) {
      case '+':
        input_str_.back() = '-';
        break;
      case '-':
        input_str_.back() = '+';
        break;
      case '*':
      case '/':
      case '(':
      case '%':
        input_str_.append("(-");
        count_of_open_b++;
        break;
      case ')':
        input_str_.append("*(-");
        count_of_open_b++;
        break;
      default:
        correct_sign(choose);
    }
  }
}

void Model::for_single_digit() {
  char tmp = input_str_.back();
  input_str_.clear();
  input_str_.append("(-");
  input_str_.push_back(tmp);
  count_of_open_b++;
}

void Model::insert_sign(std::string::iterator& it, int& count_of_open_b) {
  input_str_.insert(++it, '(');
  input_str_.insert(++it, '-');
  count_of_open_b++;
}

void Model::correct_sign(char choose) {
  if (isdigit(choose) || choose == '.') {
    auto it = input_str_.end() - 1;
    while (isdigit(*it) || *it == '.') {
      it--;
      if (it == input_str_.begin()) break;
    }
    if (*it == '-') {
      it--;
      if (*it == '(') {
        input_str_.erase(++it);
        input_str_.insert(it, '+');
      } else {
        it++;
        insert_sign(it, count_of_open_b);
      }
    } else if (*it == '+') {
      it--;
      if (*it == '(') {
        input_str_.erase(it);
        input_str_.erase(it);
        count_of_open_b--;
      } else {
        it++;
        insert_sign(it, count_of_open_b);
      }
    } else if (*it == '(') {
      insert_sign(it, count_of_open_b);
    } else {
      if (it == input_str_.begin())
        input_str_.insert(it, '(');
      else
        input_str_.insert(++it, '(');
      input_str_.insert(++it, '-');
      count_of_open_b++;
    }
  }
}

void Model::print_x() {
  if (!(input_str_tmp_.empty())) throw std::logic_error("Недопустимый ввод!");
  char choose = this->input_str_.back();
  if (choose == ')' || isdigit(choose) || choose == 'x' || choose == '.')
    input_str_.push_back('*');
  input_str_.push_back('x');
  point = true;
}

bool Model::is_action(char sym) {
  return sym == '+' || sym == '-' || sym == '/' || sym == '*' || sym == '%' ||
         sym == '^';
}

bool Model::validation() {
  char choose = this->input_str_.back();
  if (!count_of_open_b && !(is_action(choose)) && choose != '(') return true;
  return false;
}

void Model::erase_un_plus() {
  for (auto it = input_str_.begin(); it != input_str_.end(); it++) {
    if (*it == '(') {
      it++;
      if (*it == '+')
        input_str_.erase(it);
      else
        it--;
    }
  }
}

void Model::change_un_minus() {
  for (auto it = input_str_.begin(); it != input_str_.end(); it++) {
    if (*(it) == '(') {
      it++;
      if (*it == '-')
        *it = '~';
      else
        it--;
    }
  }
}

void Model::change_x(std::string& input_str_tmp_, std::string& input_str_) {
  size_t pos = 0;
  input_str_ = "(" + input_str_ + ")";
  while ((pos = input_str_tmp_.find('x', pos)) != std::string::npos) {
    input_str_tmp_.replace(pos, 1, input_str_);
    pos += input_str_.length();
  }
  input_str_.swap(input_str_tmp_);
}

void Model::make_u_min(std::string& str) {
  if (str.front() == '-') {
    str.insert(str.begin(), '(');
    str.push_back(')');
  }
}

void Model::res_clicked() {
  if (!(validation())) throw std::logic_error("Недопустимый ввод!");
  make_u_min(input_str_);
  size_t x = input_str_.find("x");
  if (x != std::string::npos) {
    input_str_tmp_ = input_str_;
    input_str_.clear();
    with_x = true;
    return;
  }
  if (with_x) {
    change_x(input_str_tmp_, input_str_);
    with_x = false;
    input_str_tmp_.clear();
  }
  erase_un_plus();
  change_un_minus();
  make_polish_list();
  calculate();
  point = false;
}

void Model::change_x_for_graph(std::string& input_str_tmp_,
                               std::string& input_str_) {
  input_str_ = "(" + input_str_ + ")";
  size_t pos = 0;
  while ((pos = input_str_tmp_.find('x', pos)) != std::string::npos) {
    input_str_tmp_.replace(pos, 1, input_str_);
    pos += input_str_.length();
  }
}

void Model::x_min_add10() { this->x_min_ += 10; }

void Model::x_min_add25() { this->x_min_ += 25; }

void Model::x_min_add100() { this->x_min_ += 100; }

void Model::x_max_add10() { this->x_max_ += 10; }

void Model::x_max_add25() { this->x_max_ += 25; }

void Model::x_max_add100() { this->x_max_ += 100; }

void Model::x_min_sub10() { this->x_min_ -= 10; }

void Model::x_min_sub25() { this->x_min_ -= 25; }

void Model::x_min_sub100() { this->x_min_ -= 100; }

void Model::x_max_sub10() { this->x_max_ -= 10; }

void Model::x_max_sub25() { this->x_max_ -= 25; }

void Model::x_max_sub100() { this->x_max_ -= 100; }

void Model::graph_clicked() {
  if (!(validation()) || input_str_.empty() || (!x_max_ && !x_min_))
    throw std::logic_error("Недопустимый ввод!");
  if (input_str_tmp_.empty()) make_u_min(input_str_);
  if (input_str_.back() == '|') {
    make_u_min(input_str_tmp_);
    input_str_ = input_str_tmp_;
  }
  input_str_tmp_ = input_str_;

  std::string str_for_graph;

  if (this->x_min_ > this->x_max_) std::swap(this->x_min_, this->x_max_);

  float step = (x_max_ - x_min_) / 1000;
  bool with_x = false;

  size_t x = input_str_.find("x");
  if (x != std::string::npos) with_x = true;

  while (x_min_ < x_max_) {
    std::string tmp = std::to_string(x_min_);
    str_for_graph += tmp + "|";
    if (with_x) change_x_for_graph(input_str_, tmp);
    erase_un_plus();
    change_un_minus();
    make_polish_list();
    calculate();

    str_for_graph += input_str_ + "|";
    input_str_ = input_str_tmp_;
    x_min_ += step;
  }
  input_str_ = str_for_graph;
  x_min_ = 0;
  x_max_ = 0;
}
