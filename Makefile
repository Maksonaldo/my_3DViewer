.PHONY: clean all linter cppcheck test style_check gcov_report parsing.a build
CC=gcc
CFLAGS=-c -Wall -Werror -Wextra -std=c11
LDFLAGS= -lcheck -L. -lparsing
GFLAGS= -fprofile-arcs -ftest-coverage
HEADERS=parsing.h afins.h
SOURCES=parsing.c afins.c

OBJECTS=$(SOURCES:.c=.o)
OS := $(shell uname)

ifeq ($(OS), Linux) 
	LDFLAGS += -lrt -lm -lpthread -lsubunit
endif

all: parsing.a

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES)

parsing.a: $(OBJECTS)
	ar rc parsing.a $(OBJECTS)
	cp parsing.a libparsing.a

clean:
	rm -rf $(OBJECTS) *.a *.out *.gcda *.gcno *.info *.cfg gcov_report *.html *.tgz

build:
	mkdir -p build; cd ./build; qmake ../QT_OpenGL; make; 

install: build dvi
	mkdir -p 3DViewer;
	cp -R build/QT_OpenGL.app 3DViewer
	cp README.html 3DViewer

uninstall:
	rm -rf 3DViewer build 3DViewer_v1.0

test: parsing.a
	$(CC) test.c parsing.a $< -o test.out $(LDFLAGS)
	./test.out

dvi:
	makeinfo --html --no-split -o README.html README.texi --force
	
dist: install
	rm -rf 3DViewer_v1.0
	mkdir 3DViewer_v1.0/
	cp *.c *.h  README.texi Makefile 3DViewer_v1.0/ 
	cp -R QT_OpenGL 3DViewer_v1.0
	tar cvzf 3DViewer_v1.0.tgz 3DViewer_v1.0
	rm -rf 3DViewer_v1.0
gcov_report: clean
	$(CC) $(CFLAGS) $(SOURCES) $(GFLAGS)
	ar rcs libparsing.a $(OBJECTS)
	$(CC) -o test.out test.c $(LDFLAGS) -lgcov
	rm -f *.o
	./test.out
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o gcov_report

.IGNORE: linter
linter:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h 
	rm -rf CPPLINT.cfg

cppcheck:
	cppcheck --suppress=missingIncludeSystem --suppress=unmatchedSuppression  *.c *.h

leaks:
	CK_FORK=no leaks --atExit -- ./test.out

style_check: linter cppcheck

