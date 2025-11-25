#include <benchmark/benchmark.h>
#include "../hashtabledouble.hpp"
#include <iostream>
#include <random>

static const int arraySize = 10000;

static void HashTableAdd(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        HashTableDouble ht(3);
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            ht.insert(i, 0);
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(HashTableAdd);

static void HashTableRemove(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        HashTableDouble ht(3);
        for(auto i = 0; i < arraySize; i++)
        {
            ht.insert(i, 0);
        }
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            ht.remove(i);
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(HashTableRemove);

static void HashTableSearch(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        HashTableDouble ht(3);
        for(auto i = 0; i < arraySize; i++)
        {
            ht.insert(i, 0);
        }
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            ht.get(i);
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(HashTableSearch);

BENCHMARK_MAIN();