#include <benchmark/benchmark.h>
#include "../forwardlist.hpp"
#include <iostream>
#include <random>

static const int arraySize = 10000;

static void ForwardListAddStart(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        ForwardList fl;
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            fl.addHead("123");
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(ForwardListAddStart);

static void ForwardListAddEnd(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        ForwardList fl;
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            fl.addTail("123");
        }
        state.PauseTiming();
    }
}
// Register the function as a benchmark
BENCHMARK(ForwardListAddEnd);

static void ForwardListAddRandom(benchmark::State& state)
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
        ForwardList fl;
        state.ResumeTiming();
        for(auto i = 0; i < arraySize; i++)
        {
            fl.insert("123", indexes[i]);
        }
        state.PauseTiming();
    }
}
BENCHMARK(ForwardListAddRandom);

static void ForwardListRemoveStart(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        ForwardList fl;
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
BENCHMARK(ForwardListRemoveStart);

static void ForwardListRemoveEnd(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        ForwardList fl;
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
BENCHMARK(ForwardListRemoveEnd);

static void ForwardListRemoveRandom(benchmark::State& state)
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
        ForwardList fl;
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
BENCHMARK(ForwardListRemoveRandom);

BENCHMARK_MAIN();