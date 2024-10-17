CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
SOURCES = $(wildcard model/model.cc) 
OBJECTS = $(SOURCES:.cc=.o)
TESTS = $(wildcard tests/test_model.cc)
OBJECTS_TESTS = $(TESTS:.cc=.o)
PROJECT = 3DViewer
EXECUTABLE = test
OS = $(shell uname)
REPORT = report
INSTALL_DIR = build
ccFiles = $(shell find . -name "*.cc")
cppFiles = $(shell find . -name "*.cpp")
headFiles = $(shell find . -name "*.h")
DOXYGEN = doxygen
DOXYFILE = Doxyfile

ifeq ($(OS), Linux)
	OPEN_RUN = ./$(INSTALL_DIR)/$(PROJECT)
	OPEN_CMD = xdg-open
	LIBFLAGS = $(shell pkg-config --cflags --libs gtest) -lgtest_main
endif
ifeq ($(OS), Darwin)
	OPEN_RUN = open $(INSTALL_DIR)/$(PROJECT).app
	OPEN_CMD = open
	LIBFLAGS = -lgtest -lgmock -pthread
endif

#all, install, uninstall, clean, dvi, dist, tests

all: clean clang-format $(PROJECT).a test install

install: clean uninstall
	mkdir $(INSTALL_DIR)
	cd $(INSTALL_DIR) && qmake ../$(PROJECT) && make

uninstall:
	rm -rf $(INSTALL_DIR)

clean: 
	rm -rf $(EXECUTABLE) $(PROJECT).a $(PROJECT)_test.a *.gcda *.gcno *.info
	rm -rf $(REPORT) docs/

dvi: 

	doxygen Doxyfile && open docs/html/index.html

dist: install uninstall
	rm -rf dist-develop-3DViewer.tar.gz
	tar -czf dist-develop-3DViewer.tar.gz *

tests: clang-format $(PROJECT).a $(TESTS)
	$(CC) $(CFLAGS) $(TESTS) -L. $(PROJECT).a $(LIBFLAGS) -o $(EXECUTABLE)
	clear
	./$(EXECUTABLE)

run:
	$(OPEN_RUN)

gcov_report: clean clang-format $(SOURCES) $(PROJECT)_test.a
	$(CC) $(CFLAGS) $(SOURCES) --coverage -L. $(PROJECT)_test.a $(LIBFLAGS) -o $(EXECUTABLE)
	./$(EXECUTABLE)
	lcov --no-external -t "$(PROJECT)" -o $(PROJECT).info -c -d . 
	genhtml -o $(REPORT) $(PROJECT).info
	$(OPEN_CMD) $(REPORT)/index.html

$(PROJECT).a:$(OBJECTS)
	ar -rcs $@ $^
	ranlib $@
	rm -f $^

$(PROJECT)_test.a:$(OBJECTS_TESTS)
	ar -rcs $@ $^
	ranlib $@
	rm -f $^

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

clang-format: $(ccFiles) $(cppFiles) $(headFiles)
ifeq ("","$(wildcard ./.clang-format)") # если файла нет, копируем его.
	cp -f ../materials/linters/.clang-format .
endif
	@echo "\033[33m┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\033[0m"
	@echo "\033[33m┃   Checking your code for Google Style   ┃\033[0m"
	@echo "\033[33m┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\033[0m"
	clang-format -i $^
	clang-format -style=Google -n $^

rebuild:
	clean | make

cc: *.cc $(TESTS)
	cccheck -I $(PROJECT).h --enable=all --suppress=missingIncludeSystem --checkers-report=cc.txt $^

valgrind: $(PROJECT).a $(TESTS)
	$(CC) $(CFLAGS) $(TESTS) -L. $(PROJECT).a $(LIBFLAGS) -o $(EXECUTABLE)
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file="log_valgrind.txt" ./$(EXECUTABLE)
	grep ERROR log_valgrind.txt
	make clean
	cat log_valgrind.txt

.PHONY: clean gcov_report clang-format rebuild cc

# запуск теста на Мак
gtests: tests/test_s21_calc.cc s21_smart_calc.cc s21_smart_calc.h
	g++ -Wall -Werror -Wextra $^ -o $(EXECUTABLE) -lgtest -lgmock -pthread -lgtest_main
	clear
	./$(EXECUTABLE)

# запуск теста на Линукс
go: tests/test_model.cc model/model.cc model/model.h controller.h
	g++ -Wall -Werror -Wextra $^ -o $(EXECUTABLE)  $(shell pkg-config --cflags --libs gtest) -lgtest_main
	./$(EXECUTABLE) 

go_val: tests/test_model.cc model/model.cc model/model.h controller.h
	g++ -Wall -Werror -Wextra $^ -o $(EXECUTABLE)  $(shell pkg-config --cflags --libs gtest) -lgtest_main
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file="log_valgrind.txt" ./$(EXECUTABLE) 
	grep ERROR log_valgrind.txt || true
	cat log_valgrind.txt

main: main.cc
	g++ -Wall -Werror -Wextra $^ -o $(EXECUTABLE)
	./$(EXECUTABLE)

go2: tests/test_model2.cc model/model.cc model/model.h
	g++ -Wall -Werror -Wextra $^ -o $(EXECUTABLE)  $(shell pkg-config --cflags --libs gtest) -lgtest_main
	./$(EXECUTABLE) 