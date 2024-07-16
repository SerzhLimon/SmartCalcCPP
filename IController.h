#ifndef ICONTROLLER_H
#define ICONTROLLER_H

namespace s21 {

enum Keys {
  ZERO_BUTTON,
  ONE_BUTTON,
  TWO_BUTTON,
  THREE_BUTTON,
  FOUR_BUTTON,
  FIVE_BUTTON,
  SIX_BUTTON,
  SEVEN_BUTTON,
  EIGHT_BUTTON,
  NINE_BUTTON,

  X_BUTTON,
  POINT_BUTTON,

  PLUS_BUTTON,
  MINUS_BUTTON,
  MULT_BUTTON,
  DIVIDE_BUTTON,
  PERCENT_BUTTON,
  POW_BUTTON,

  SQRT_BUTTON,
  SIN_BUTTON,
  COS_BUTTON,
  TAN_BUTTON,
  ASIN_BUTTON,
  ACOS_BUTTON,
  ATAN_BUTTON,
  LOG_BUTTON,
  LN_BUTTON,

  OPEN_BRACKETS_BUTTON,
  CLOSE_BRACKETS_BUTTON,

  SIGN_BUTTON,
  DELETE_BUTTON,
  AC_BUTTON,

  RESULT_BUTTON,
  GRAPH_BUTTON,

  X_MIN_ADD10,
  X_MIN_SUB10,
  X_MIN_ADD25,
  X_MIN_SUB25,
  X_MIN_ADD100,
  X_MIN_SUB100,

  X_MAX_ADD10,
  X_MAX_SUB10,
  X_MAX_ADD25,
  X_MAX_SUB25,
  X_MAX_ADD100,
  X_MAX_SUB100
};

// class IModel;

class IController {
 public:
  virtual void OnClick(Keys key) = 0;
  virtual void ChangeView() = 0;
  virtual void Start() = 0;
  virtual ~IController() = default;
  virtual float Get_x_max() = 0;
  virtual float Get_x_min() = 0;
  virtual void Set_x_max(float value) = 0;
  virtual void Set_x_min(float value) = 0;
};

}  //  namespace s21

#endif  // ICONTROLLER_H
