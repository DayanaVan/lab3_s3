#pragma once

#include <string>
#include <fstream>

struct StackNode
{
    StackNode *prev;
    std::string key;

    StackNode(std::string key);
};

class Stack
{
private:
    StackNode *top;
    
public:
    Stack();
    Stack(std::string &file, bool binary);
    ~Stack();

    void push(std::string key);
    std::string pop();
    std::string toString();

    void writeToFile(std::string &file);

    void writeToFileBinary(std::string &file);

private:
    void deleteStack();

    void writeToFileRec(std::ofstream &ofs, StackNode *node);

    void writeToFileBinaryRec(std::ofstream &ofs, StackNode *node);
};