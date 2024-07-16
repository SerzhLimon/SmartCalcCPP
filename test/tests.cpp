#include <gtest/gtest.h>

#include "../Controller.h"
#include "../Model.h"
#include "MockView.h"

using namespace s21;

TEST(CALC, case1) {
  IView* view = new MockView("1+5-3=", "3.000000");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case2) {
  IView* view = new MockView("1.234-5=", "-3.766");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case3) {
  IView* view = new MockView("3/2=", "1.500000");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case4) {
  IView* view = new MockView("5*(-10)=", "-50.000000");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case5) {
  IView* view = new MockView("sin(10)=", "-0.544021");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case6) {
  IView* view = new MockView("cos(10)=", "-0.839072");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case7) {
  IView* view = new MockView("tan(10)=", "0.648361");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case8) {
  IView* view = new MockView("log(10)=", "1.0");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case9) {
  IView* view = new MockView("7%2=", "1");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case10) {
  IView* view = new MockView("7^(2)=", "49");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case11) {
  IView* view = new MockView("sqrt(16)=", "4");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case12) {
  IView* view = new MockView("1/0=", "inf");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case13) {
  IView* view = new MockView("(-1+3)*4=", "8");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  }
}

TEST(CALC, case14) {
  IView* view = new MockView("2=", "2");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  };
}

TEST(CALC, case15) {
  IView* view = new MockView("1+6/3=", "3");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  };
}

TEST(CALC, case16) {
  IView* view = new MockView("sqrt(256)/4=", "4");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  };
}

TEST(CALC, case17) {
  IView* view = new MockView("log(10)*3=", "3");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  };
}

TEST(CALC, case18) {
  IView* view = new MockView("9%3=", "0");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  };
}

TEST(CALC, case19) {
  IView* view = new MockView("9%3=", "0");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  };
}

TEST(CALC, case20) {
  IView* view = new MockView("sin(3)+4=", "4.14112");
  IModel* model = new Model();
  IController* app = new Controller(view, nullptr, model);
  try {
    app->Start();
  } catch (std::exception e) {
    FAIL();
  };
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
