CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.. -O3
LDFLAGS = -lbenchmark -lpthread

# Исходные файлы структур
SOURCES = ../array.cpp ../stack.cpp ../queue.cpp ../list.cpp ../forwardlist.cpp ../hashtabledouble.cpp ../bstree.cpp

# Бенчмарки
BENCHMARKS = arraybench stackbench queuebench listbench forwardlistbench hashtablebench treebench

all: $(BENCHMARKS)

arraybench: arraybench.cpp ../array.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

stackbench: stackbench.cpp ../stack.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

queuebench: queuebench.cpp ../queue.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

listbench: listbench.cpp ../list.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

forwardlistbench: forwardlistbench.cpp ../forwardlist.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

hashtablebench: hashtablebench.cpp ../hashtabledouble.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

treebench: treebench.cpp ../bstree.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(BENCHMARKS)

run: $(BENCHMARKS)
	@echo "=========================================="
	@echo "RUNNING ALL BENCHMARKS"
	@echo "=========================================="
	@for bench in $(BENCHMARKS); do \
		echo ""; \
		echo "$$bench"; \
		echo "------------------------------------------"; \
		./$$bench --benchmark_min_time=0.1s; \
	done

.PHONY: all clean run
