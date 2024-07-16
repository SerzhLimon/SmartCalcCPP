#ifndef IMODEL_H
#define IMODEL_H

#include <string>

#include "IController.h"

namespace s21 {

class IModel {
 public:
  virtual std::string get_output() = 0;
  virtual void on_click(Keys key) = 0;
  virtual ~IModel() = default;
};

}  // namespace s21

#endif  // IMODEL_H
