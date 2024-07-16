#ifndef IVIEW_H
#define IVIEW_H

#include <string>

#include "IController.h"

namespace s21 {

class IView {
 public:
  virtual void AddListener(IController* controller) = 0;
  virtual void SetOutput(std::string str) = 0;
  virtual void Show() = 0;
  virtual void Hide() = 0;
  virtual ~IView() = default;
};

}  // namespace s21

#endif  // IVIEW_H
