#ifndef MODEL_H
#define MODEL_H

#include <cctype>
#include <cmath>
#include <list>
#include <map>
#include <stdexcept>

#include "IModel.h"

namespace s21 {

enum Types { DIGIT, OPERATOR, FUNCTION, OPEN_B };

enum Operators { PLUS, MINUS, MULT, DIVIDE, PERCENT, POW };

enum Functions { SQRT, UN_MINUS, SIN, COS, TAN, ASIN, ACOS, ATAN, LOG, LN };

enum Priotity { LOW, MEDIUM, HIGH, VERY_HIGH };

struct Node;

class Model : public IModel {
 public:
  Model();
  ~Model();

  std::string get_output();
  void on_click(Keys key);
  typedef float (Model::*math_method_t)(float, float) const;

 private:
  float x_min_;
  float x_max_;
  std::string input_str_;
  std::string input_str_tmp_;

  int count_of_open_b;
  bool point = true;
  bool with_x = false;

  typedef void (Model::*FunctionType)();
  ;
  std::map<Keys, FunctionType> key_mapping;

  std::list<Node> polish_list_;
  std::list<Node> tmp_list_;

  std::map<std::string, Node> types_mapping;

  void make_polish_list();
  //  for make_polish_list {
  void push_open_brackets();
  void push_digit(std::string::iterator& it, std::string& substr);
  void push_other_to_polish();
  void push_between_brackets();
  void push_high_prioryty(Node node);
  void search_oper_or_func(std::string::iterator& it, std::string& substr);
  bool check_prioryty_in_tmp(std::string& substr);
  //  }

  void calculate();
  //  for calculate {
  bool check_two_prev_node(std::list<Node>::iterator& it);
  bool check_one_prev_node(std::list<Node>::iterator& it);

  void calc_operation(std::list<Node>::iterator& it);
  void calc_function(std::list<Node>::iterator& it);
  bool check_digit_in_list();
  void add_digits();
  //}

  float handler_plus(float a, float b) const { return b + a; }
  float handler_minus(float a, float b) const { return b - a; }
  float handler_mult(float a, float b) const { return b * a; }
  float handler_div(float a, float b) const { return b / a; }
  float handler_percent(float a, float b) const { return (int)b % (int)a; }
  float handler_pow(float a, float b) const { return pow(b, a); }

  float handler_sqrt(float a, float b) const {
    (void)b;
    return sqrt(a);
  }
  float handler_sin(float a, float b) const {
    (void)b;
    return sin(a);
  }
  float handler_cos(float a, float b) const {
    (void)b;
    return cos(a);
  }
  float handler_tan(float a, float b) const {
    (void)b;
    return tan(a);
  }
  float handler_asin(float a, float b) const {
    (void)b;
    return asin(a);
  }
  float handler_acos(float a, float b) const {
    (void)b;
    return acos(a);
  }
  float handler_atan(float a, float b) const {
    (void)b;
    return atan(a);
  }
  float handler_log(float a, float b) const {
    (void)b;
    return log10(a);
  }
  float handler_ln(float a, float b) const {
    (void)b;
    return logf(a);
  }
  float handler_umin(float a, float b) const {
    (void)b;
    return -a;
  }

  void bind_keys();
  void bind_types();

  void print_zero();
  void print_one();
  void print_two();
  void print_three();
  void print_four();
  void print_five();
  void print_six();
  void print_seven();
  void print_eightg();
  void print_nine();

  void print_point();

  void print_plus();
  void print_minus();
  void print_mult();
  void print_divide();
  void print_percent();
  void print_pow();

  void print_sqrt();
  void print_sin();
  void print_cos();
  void print_tan();
  void print_asin();
  void print_acos();
  void print_atan();
  void print_log();
  void print_ln();
  void print_open_b();
  void print_close_b();

  void print_ac();
  void print_delete();

  void print_x();

  void print_sign();
  void correct_sign(char choose);
  void for_single_digit();
  void insert_sign(std::string::iterator& it, int& count_of_open_b);

  bool is_action(char sym);
  bool validation();

  void make_u_min(std::string& str);
  void res_clicked();
  void graph_clicked();

  void erase_un_plus();
  void change_un_minus();
  void change_x(std::string& input_str_tmp_, std::string& input_str_);
  void change_x_for_graph(std::string& input_str_tmp_, std::string& input_str_);

  void x_min_sub10();
  void x_min_sub25();
  void x_min_sub100();

  void x_max_sub10();
  void x_max_sub25();
  void x_max_sub100();

  void x_min_add10();
  void x_min_add25();
  void x_min_add100();

  void x_max_add10();
  void x_max_add25();
  void x_max_add100();
};

struct Node {
  Types type;
  float value;
  Priotity prioryty;
  ;

  Model::math_method_t handler;

  Node() = default;
  Node(Types type, float value, Priotity prioryty, Model::math_method_t handler)
      : type(type), value(value), prioryty(prioryty), handler(handler) {}
};

}  // namespace s21

#endif  // MODEL_H
