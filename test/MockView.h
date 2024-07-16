#ifndef MOCKVIEW_H
#define MOCKVIEW_H

#include <map>
#include <string>

#include "../IController.h"
#include "../IView.h"

using namespace s21;

class MockView : public IView {
 public:
  MockView(std::string input, std::string require);
  ~MockView(){};

  void AddListener(IController* controller);
  void SetOutput(std::string str);
  void Show();
  void Hide() { return; }

 private:
  IController* controller;
  std::string input;
  std::string require;
  std::map<std::string, Keys> types_mapping;
  void bind();
  auto onClick(Keys key);
  bool res = false;
};

#endif  // MOCKVIEW_H