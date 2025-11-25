CXXFLAGS := -Wall -Wextra -std=c++17
BENCHFLAGS := $(CXXFLAGS) -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread

all: main

main: main.o array.o forwardlist.o list.o stack.o queue.o rbtree.o hashtabledouble.o
	g++ main.o array.o forwardlist.o list.o stack.o queue.o rbtree.o hashtabledouble.o $(CXXFLAGS) -o main

main.o: main.cpp
	g++ $(CXXFLAGS) main.cpp -c -o main.o

test: CXXFLAGS += -coverage
test: tests/arraytest tests/forwardlisttest tests/listtest tests/stacktest tests/queuetest tests/hashtabletest tests/rbtreetest

tests/rbtreetest: tests/rbtreetest.o rbtree.o
	g++ tests/rbtreetest.o rbtree.o $(CXXFLAGS) -o tests/rbtreetest

tests/rbtreetest.o: tests/rbtreetest.cpp
	g++ tests/rbtreetest.cpp $(CXXFLAGS) -c -o tests/rbtreetest.o

tests/hashtabletest: tests/hashtabletest.o hashtabledouble.o
	g++ tests/hashtabletest.o hashtabledouble.o $(CXXFLAGS) -o tests/hashtabletest

tests/hashtabletest.o: tests/hashtabletest.cpp
	g++ tests/hashtabletest.cpp $(CXXFLAGS) -c -o tests/hashtabletest.o

tests/queuetest: tests/queuetest.o queue.o
	g++ tests/queuetest.o queue.o $(CXXFLAGS) -o tests/queuetest

tests/queuetest.o: tests/stacktest.cpp
	g++ tests/queuetest.cpp $(CXXFLAGS) -c -o tests/queuetest.o

tests/stacktest: tests/stacktest.o stack.o
	g++ tests/stacktest.o stack.o $(CXXFLAGS) -o tests/stacktest

tests/stacktest.o: tests/stacktest.cpp
	g++ tests/stacktest.cpp $(CXXFLAGS) -c -o tests/stacktest.o

tests/listtest: tests/listtest.o list.o
	g++ tests/listtest.o list.o $(CXXFLAGS) -o tests/listtest

tests/listtest.o: tests/listtest.cpp
	g++ tests/listtest.cpp $(CXXFLAGS) -c -o tests/listtest.o

tests/forwardlisttest: tests/forwardlisttest.o forwardlist.o
	g++ tests/forwardlisttest.o forwardlist.o $(CXXFLAGS) -o tests/forwardlisttest

tests/forwardlisttest.o: tests/forwardlisttest.cpp
	g++ tests/forwardlisttest.cpp $(CXXFLAGS) -c -o tests/forwardlisttest.o

tests/arraytest: tests/arraytest.o array.o
	g++ tests/arraytest.o array.o $(CXXFLAGS) -o tests/arraytest

tests/arraytest.o: tests/arraytest.cpp
	g++ tests/arraytest.cpp $(CXXFLAGS) -c -o tests/arraytest.o

array.o: array.cpp array.hpp
	g++ array.cpp $(CXXFLAGS) -c -o array.o

forwardlist.o: forwardlist.cpp forwardlist.hpp
	g++ forwardlist.cpp $(CXXFLAGS) -c -o forwardlist.o

list.o: list.cpp list.hpp
	g++ list.cpp $(CXXFLAGS) -c -o list.o

queue.o: queue.cpp queue.hpp
	g++ queue.cpp $(CXXFLAGS) -c -o queue.o

rbtree.o: rbtree.cpp rbtree.hpp
	g++ rbtree.cpp $(CXXFLAGS) -c -o rbtree.o

stack.o: stack.cpp stack.hpp
	g++ stack.cpp $(CXXFLAGS) -c -o stack.o

hashtabledouble.o: hashtabledouble.cpp hashtabledouble.hpp
	g++ hashtabledouble.cpp $(CXXFLAGS) -c -o hashtabledouble.o

benchmark: clean .WAIT tests/arraybench tests/forwardlistbench tests/listbench tests/hashtablebench tests/queuebench tests/stackbench tests/treebench
	./tests/arraybench
	./tests/forwardlistbench
	./tests/listbench
	./tests/hashtablebench
	./tests/stackbench
	./tests/queuebench
	./tests/treebench

tests/arraybench: tests/arraybench.o array.o
	g++ tests/arraybench.o array.o $(BENCHFLAGS) -o tests/arraybench

tests/arraybench.o: tests/arraybench.cpp
	g++ tests/arraybench.cpp $(CXXFLAGS) -c -o tests/arraybench.o

tests/forwardlistbench: tests/forwardlistbench.o forwardlist.o
	g++ tests/forwardlistbench.o forwardlist.o $(BENCHFLAGS) -o tests/forwardlistbench

tests/forwardlistbench.o: tests/forwardlistbench.cpp
	g++ tests/forwardlistbench.cpp $(CXXFLAGS) -c -o tests/forwardlistbench.o

tests/listbench: tests/listbench.o list.o
	g++ tests/listbench.o list.o $(BENCHFLAGS) -o tests/listbench

tests/listbench.o: tests/listbench.cpp
	g++ tests/listbench.cpp $(CXXFLAGS) -c -o tests/listbench.o

tests/hashtablebench: tests/hashtablebench.o hashtabledouble.o
	g++ tests/hashtablebench.o hashtabledouble.o $(BENCHFLAGS) -o tests/hashtablebench

tests/hashtablebench.o: tests/hashtablebench.cpp
	g++ tests/hashtablebench.cpp $(CXXFLAGS) -c -o tests/hashtablebench.o

tests/stackbench: tests/stackbench.o stack.o
	g++ tests/stackbench.o stack.o $(BENCHFLAGS) -o tests/stackbench

tests/stackbench.o: tests/stackbench.cpp
	g++ tests/stackbench.cpp $(CXXFLAGS) -c -o tests/stackbench.o

tests/queuebench: tests/queuebench.o queue.o
	g++ tests/queuebench.o queue.o $(BENCHFLAGS) -o tests/queuebench

tests/queuebench.o: tests/queuebench.cpp
	g++ tests/queuebench.cpp $(CXXFLAGS) -c -o tests/queuebench.o

tests/treebench: tests/treebench.o rbtree.o
	g++ tests/treebench.o rbtree.o $(BENCHFLAGS) -o tests/treebench

tests/treebench.o: tests/treebench.cpp
	g++ tests/treebench.cpp $(CXXFLAGS) -c -o tests/treebench.o

coverage:
	$(MAKE) clean
	$(MAKE) test
	cd tests ; ./arraytest ; ./forwardlisttest ; ./listtest ; ./stacktest ; ./queuetest ; ./hashtabletest ; ./rbtreetest
	lcov --capture --ignore-errors inconsistent --directory . --output-file coverage.info
	lcov -r coverage.info "/usr/*" -o coverage.info
	genhtml coverage.info --output-directory coverage_html

clean:
	rm -f *.o tests/*.o tests/arraytest tests/forwardlisttest tests/listtest tests/queuetest tests/stacktest tests/hashtabletest tests/rbtreetest
	rm -f tests/.bintestfile tests/.texttestfile tests/.badfile
	rm -rf *.gcda *.gcno tests/*.gcda tests/*.gcno coverage_html coverage.info
	rm -rf tests/arraybench tests/forwardlistbench tests/listbench tests/hashtablebench tests/queuebench tests/stackbench

.PHONY: all coverage clean test benchmark