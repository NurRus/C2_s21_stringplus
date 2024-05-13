CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
#TEST_LIBS=-lcheck
SRC=$(wildcard s21_*.c)
OBJ=$(patsubst %.c,%.o, ${SRC})
TARGET=s21_string.a 

all: $(TARGET) test gcov_report clean_test open_report

$(TARGET): ${SRC}
	$(CC) -c $(STDFLAGS) $(SRC)
	ar rc $@ $(OBJ)
	ranlib $@
	cp $@ lib$@
	make clean_obj

test: tests/test_s21string.c s21_string.a
	$(CC) $(CFLAGS) -c tests/test_s21string.c -o test.o
	$(CC) test.o s21_string.a $(TEST_LIBS) -o test

gcov_report: $(TARGET)
	$(CC) $(CFLAGS) --coverage tests/test_s21string.c ${SRC} $(TARGET) -o gcov_test $(TEST_LIBS)
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info

open_report:
	open report/index.html

style_test:
	clang-format -style=Google -n *.c *.h tests/test_s21string.c

editing_style:
	clang-format -style=Google -i *.c *.h tests/test_s21string.c

rebuild:
	make clean
	make all

clean: clean_obj clean_lib clean_test
	rm -rf test
	rm -rf report
	
clean_obj:
	rm -rf *.o

clean_lib: 
	rm -rf *.a

clean_test: clean_lib
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf gcov_test
	rm -rf test.o
