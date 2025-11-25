#pragma once

#include <string>
#include <fstream>
#include <iostream>
struct QueueNode
{
    QueueNode *next;

    std::string key;

    QueueNode(std::string key);
};

class Queue
{
private:
    QueueNode *top;

    QueueNode *bot;

    void deleteQueue();

public:
    Queue();
    Queue(std::string &file, bool binary);
    ~Queue();

    void push(std::string key);
    std::string pop();
    std::string toString();

    void writeToFile(std::string &file);

    void writeToFileBinary(std::string &file);
};