#include <benchmark/benchmark.h>
#include "../list.hpp"
#include <iostream>
#include <random>

static const int arraySize = 10000;

static void ListAddStart(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        List fl;
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            fl.addHead("123");
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(ListAddStart);

static void ListAddEnd(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        List fl;
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            fl.addTail("123");
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(ListAddEnd);

static void ListAddRandom(benchmark::State& state)
{
    std::random_device rd; // Obtain a random seed from the OS
    std::mt19937 gen(rd()); // Standard Mersenne Twister engine seeded with rd()
    std::vector<int> indexes(10000);
    for(int i = 0; i < arraySize; i++)
    {
        std::uniform_int_distribution<> distrib(0, i); // Distribution for integers between 1 and 100
        indexes[i] = distrib(gen);
    }
    for (auto _ : state)
    {
        state.PauseTiming();
        List fl;
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            fl.insert("123", indexes[i]);
        }
        state.PauseTiming();
    }
}
BENCHMARK(ListAddRandom);

static void ListRemoveStart(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        List fl;
        for(int i = 0; i < arraySize; i++)
        {
            fl.addHead("123");
        }
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            fl.removeHead();
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(ListRemoveStart);

static void ListRemoveEnd(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        List fl;
        for(int i = 0; i < arraySize; i++)
        {
            fl.addHead("123");
        }
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            fl.removeTail();
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(ListRemoveEnd);

static void ListRemoveRandom(benchmark::State& state)
{
    std::random_device rd; // Obtain a random seed from the OS
    std::mt19937 gen(rd()); // Standard Mersenne Twister engine seeded with rd()
    std::vector<int> indexes(10000);
    for(int i = 0; i < arraySize; i++)
    {
        std::uniform_int_distribution<> distrib(0, arraySize-i-1); // Distribution for integers between 1 and 100
        indexes[i] = distrib(gen);
    }
    for (auto _ : state)
    {
        state.PauseTiming();
        List fl;
        for(int i = 0; i < arraySize; i++)
        {
            fl.addHead("123");
        }
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            fl.remove(indexes[i]);
        }
        state.PauseTiming();
    }
}
BENCHMARK(ListRemoveRandom);

BENCHMARK_MAIN();