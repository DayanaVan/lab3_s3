#include <benchmark/benchmark.h>
#include "../array.hpp"
#include <iostream>
#include <random>

static const int arraySize = 10000;

static void ArrayAddStart(benchmark::State& state)
{
    Array arr;
    for (auto _ : state)
    {
        for(auto i = 0; i < arraySize; i++)
        {
            arr.add("123", 0);
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(ArrayAddStart);

static void ArrayAddEnd(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        Array arr;
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            arr.add("123");
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(ArrayAddEnd);

static void ArrayAddRandom(benchmark::State& state)
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
        Array arr;
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            arr.add("123", indexes[i]);
        }
        state.PauseTiming();
    }
}
BENCHMARK(ArrayAddRandom);

static void ArrayRemoveStart(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        Array arr;
        for(auto i = 0; i < arraySize; i++)
        {
            arr.add("123");
        }
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            arr.remove(0);
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(ArrayRemoveStart);

static void ArrayRemoveEnd(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        Array arr;
        for(auto i = 0; i < arraySize; i++)
        {
            arr.add("123");
        }
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            arr.remove(arr.getSize()-1);
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(ArrayRemoveEnd);

static void ArrayRemoveRandom(benchmark::State& state)
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
        Array arr;
        for(auto i = 0; i < arraySize; i++)
        {
            arr.add("123");
        }
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            arr.remove(indexes[i]);
        }
        state.PauseTiming();
    }
}
BENCHMARK(ArrayRemoveRandom);

BENCHMARK_MAIN();