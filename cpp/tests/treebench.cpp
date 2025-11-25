#include <benchmark/benchmark.h>
#include "../rbtree.hpp"
#include <iostream>
#include <random>

static const int arraySize = 10000;

static void TreeAddOrder(benchmark::State& state)
{
    for (auto _ : state)
    {
        for(auto i = 0; i < arraySize; i++)
        {
            state.PauseTiming();
            Tree t;
            state.ResumeTiming();
            t.add(i);
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(TreeAddOrder);

static void TreeAddRandom(benchmark::State& state)
{
    std::random_device rd; // Obtain a random seed from the OS
    std::mt19937 gen(rd()); // Standard Mersenne Twister engine seeded with rd()
    std::vector<int> indexes(10000);
    for(int i = 0; i < arraySize; i++)
    {
        indexes[i] = i;
    }
    std::shuffle(indexes.begin(), indexes.end(), gen);
    for (auto _ : state)
    {
        state.PauseTiming();
        Tree t;
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            t.add(indexes[i]);
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(TreeAddRandom);

static void TreeSearchRandom(benchmark::State& state)
{
    std::random_device rd; // Obtain a random seed from the OS
    std::mt19937 gen(rd()); // Standard Mersenne Twister engine seeded with rd()
    std::vector<int> indexes(10000);
    for(int i = 0; i < arraySize; i++)
    {
        indexes[i] = i;
    }
    std::shuffle(indexes.begin(), indexes.end(), gen);
    for (auto _ : state)
    {
        state.PauseTiming();
        Tree t;
        for(int i = 0; i < arraySize; i++)
        {
            t.add(i);
        }
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            t.search(indexes[i]);
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(TreeSearchRandom);

static void TreeRemoveRandom(benchmark::State& state)
{
    std::random_device rd; // Obtain a random seed from the OS
    std::mt19937 gen(rd()); // Standard Mersenne Twister engine seeded with rd()
    std::vector<int> indexes(10000);
    for(int i = 0; i < arraySize; i++)
    {
        indexes[i] = i;
    }
    std::shuffle(indexes.begin(), indexes.end(), gen);
    for (auto _ : state)
    {
        state.PauseTiming();
        Tree t;
        for(int i = 0; i < arraySize; i++)
        {
            t.add(i);
        }
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            t.remove(t.search(indexes[i]));
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(TreeRemoveRandom);

BENCHMARK_MAIN();