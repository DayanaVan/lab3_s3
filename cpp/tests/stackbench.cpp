#include <benchmark/benchmark.h>
#include "../stack.hpp"
#include <iostream>
#include <random>

static const int arraySize = 10000;

static void StackAdd(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        Stack s;
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            s.push("123");
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(StackAdd);

static void StackRemove(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        Stack s;
        for(auto i = 0; i < arraySize; i++)
        {
            s.push("123");
        }
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            s.pop();
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(StackRemove);

BENCHMARK_MAIN();