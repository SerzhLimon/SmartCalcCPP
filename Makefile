FLAGS = -Wall -Wextra -std=c++17 -Werror
TEST_FILES = test/*.cpp Model.cpp Controller.cpp

CC = clang++

ifeq ($(OS), Linux)
    CHECK_FLAGS = -lgtest -pthread -lrt -lm -lsubunit
else
    CHECK_FLAGS = $(shell pkg-config --libs --cflags gtest)
endif

TEST_COMPILE = $(CC) $(FLAGS) $(TEST_FILES) $(CHECK_FLAGS) 

all: install

run:
	export 'DYLD_FRAMEWORK_PATH=/usr/local/lib/' && cd build/testCalc.app/Contents/MacOS && ./testCalc

install: uninstall
	export DYLD_FRAMEWORK_PATH=/usr/local/lib/
	mkdir build
	cd build && qmake ../testCalc.pro
	cd build && make

uninstall:
	rm -rf build

dvi:
	doxygen .
	open html/index.html

dist: install
	tar --totals -cvf SmartCalc.tar .

clean:
	rm -rf *.a *.o *.out *.html *.css *.gcno *.gcov *.gcda *.tar test_res html latex

test: 
	$(TEST_COMPILE) -o test_res
	./test_res

.PHONY: test