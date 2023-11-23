CC=gcc -std=c11 -Wall -Werror -Wextra -g -pedantic
GCOVFLAGS =  -fprofile-arcs -ftest-coverage 
OS = $(shell uname)
ifeq ($(OS), Linux)
#-lsubunit
	F_LIB_CHECK=-lpthread -lcheck -pthread -lrt -lm
else
	F_LIB_CHECK=-lcheck -lm -lpthread
endif

all: clean install dist dvi clean

rebuild: clean all

install: uninstall
	mkdir build
	cp -rf SmartCalc/* build
	cd build && qmake SmartCalc.pro
	make -C build
	cd build && make clean
	open ./build/SmartCalc.app/Contents/MacOS/SmartCalc

uninstall:
	rm -rf build
	make clean

dvi:
	open ./documentation/README_CALC.md

dist:
	tar -cvf build/calculator.tar build
	gzip build/calculator.tar
	mv build/calculator.tar.gz ./

test:
	$(CC) $(GCOVFLAGS) *.c -o s21_test $(F_LIB_CHECK) -lgcov --coverage
	./s21_test

gcov_report: test
	lcov -t "test" -o report.info -c -d . 
	genhtml -o gcov_report/ report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index.html

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.c 
	clang-format -i *.h 
	clang-format -i SmartCalc/*.cpp 
	clang-format -i SmartCalc/*.h 
	rm -rf .clang-format

style_check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c 
	clang-format -n *.h 
	clang-format -n SmartCalc/*.cpp 
	clang-format -n SmartCalc/*.h 
	rm -rf .clang-format

leaks: 
	CK_FORK=no leaks --atExit -- ./build/SmartCalc.app/Contents/MacOS/SmartCalc

clean:
	@rm -rf *.o \
		*.a \
		*.app \
		*.so \
		*.gcno \
		*gcda \
		*.gcov \
		gcov_report \
		*.dSYM \
        RESULT_VALGRIND.txt \
		*.out \
        s21_test \
        vtests_run \
		run \
		*.gz \

test_val:
	$(CC) *.c -o run $(F_LIB_CHECK) -lgcov --coverage
	sh valgrind.sh ./run