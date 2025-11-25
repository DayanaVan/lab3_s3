#include <benchmark/benchmark.h>
#include "../queue.hpp"
#include <iostream>
#include <random>

static const int arraySize = 10000;

static void QueueAdd(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        Queue s;
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            s.push("123");
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(QueueAdd);

static void QueueRemove(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        Queue s;
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
BENCHMARK(QueueRemove);

BENCHMARK_MAIN();