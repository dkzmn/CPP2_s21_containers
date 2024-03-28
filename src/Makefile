CC = g++
COVFLAGS = -fprofile-arcs -ftest-coverage
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17
LDLIBS = -lgtest 
PREF_TEST = ./tests/
SOURCES =  $(wildcard *.cc)
OBJECTS = $(patsubst %.cc, %.o, $(SOURCES))
HEADERS = $(wildcard *.h)
TESTS = $(wildcard $(PREF_TEST)*.cc)
REPORT_DIR=report
LIB = s21_containers.a

all: clean $(LIB) test

test: $(LIB)
	$(CC) $(TESTS) $(CFLAGS) $(LDLIBS) -L. $(LIB)
	./a.out

$(LIB): $(OBJECTS)
	ar rcs $(LIB) $^
	ranlib $(LIB)

%.o : %.cc s21_containers.h 
	$(CC) $(CFLAGS) -c $< -o $@

gcov_report :
	$(CC) $(COVFLAGS) $(TESTS) $(LDLIBS) -o report.out
	./report.out
	gcov -f $(HEADERS)
	lcov -t "gcov_report" --no-external -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	xdg-open ./report/index-sort-f.html

valgrind: test
	valgrind -s --leak-check=full --show-leak-kinds=all  ./a.out

clang:
	cppcheck  *.h *.cc  --language=c++
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(PREF_TEST)* *.h
	clang-format -n $(PREF_TEST)* *.h
	rm -rf .clang-format

clean:
	rm -rf *.o *.a *.gcda *.gcno *.info *.out ./report test
