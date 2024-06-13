CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -std=c11
LFLAGS = -Wall -Werror -Wextra -g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector -fanalyzer
COVFLAGS = -fprofile-arcs -ftest-coverage
TESTFLAGS = -lcheck
TARGET = SmartCalc
VERSION = 1.0

FILES= calc.c doublestack.c stack.c validation.c parser.c RPN.c loan_calc.c replace_x.c deposit_calc.c

all: test

install:
	@echo "Start installation"
	@mkdir -p ../build
	@cd app/CalcSmart && qmake && make && make clean && rm -rf Makefile && mv CalcSmart.app ../../../build/$(TARGET).app
	@cp -R ../build/$(TARGET).app ~/Desktop/$(TARGET).app
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃     The project is located in the       ┃"
	@echo "┃    build folder and on the desktop.     ┃"
	@echo "┗=========================================┛"
	@make run_app

run_app:
	@echo "Opening $(TARGET).app"
	../build/SmartCalc.app/Contents/MacOS/CalcSmart

uninstall:
	@rm -rf ~/Desktop/$(TARGET).app ../build
	@echo "Uninstall completed successfully"

s21_calc.a: s21_calc.o
	ar rc s21_calc.a *.o
	ranlib s21_calc.a
	rm *.o

s21_calc.o: $(FILES) calc.h
	$(CC) $(CFLAGS) -c $(FILES)

test: s21_calc.o
	$(CC) $(CFLAGS) test.c $(FILES) $(TESTFLAGS) -o test_calc

calc: s21_calc.o
	$(CC) $(CFLAGS) test.c $(FILES) $(TESTFLAGS) -o test_calc

leaks: s21_calc.a
	clear
	$(CC) $(CFLAGS) $(TESTFLAGS) test.c s21_calc.a -o v
	valgrind --tool=memcheck --leak-check=yes ./v
	leaks -atExit -- ./v
	$(CC) $(LFLAGS) $(TESTFLAGS) test.c s21_calc.a -o 1
	./1

gcov_report:
	$(CC) $(CFLAGS) test.c $(FILES) $(TESTFLAGS) $(COVFLAGS) -o test_calc
	./test_calc
	lcov -t "Calc_tests" -o test_calc.info -c -d .
	genhtml -o report test_calc.info
	rm *.gcda *.gcno *.info
	open report/index.html

style:
	clang-format -n -style=Google *.c *.h app/CalcSmart/*.cpp app/CalcSmart/*.h

clean:
	rm -rf report
	rm -f *.a
	rm -f *.o
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.info
	rm -f test_calc
	rm -rf *.dSYM
	@rm -rf ../build ../dist app/CalcSmart/*.app app/CalcSmart/*.o app/CalcSmart/Makefile

dvi:
	@open ../README_RUS.md

dist:
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET)_v1.0.tgz *
	@cd ../dist && rm -rf $(TARGET).app README.md README_RUS.md
	@echo "The build was successfully archived"

.PHONY: all test gcov_report style clean s21_calc.a install uninstall dist dvi