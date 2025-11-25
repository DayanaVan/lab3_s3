#pragma once

#include <string>
#include <iostream>
#include <fstream>

struct ForwardListNode
{
    ForwardListNode *next;
    std::string key;

    ForwardListNode(std::string key);
};

class ForwardList
{
public:
    ForwardListNode *head;

    ForwardList();
    ForwardList(std::string &file, bool binary);
    ~ForwardList();

    bool insert(std::string key, size_t index);

    bool remove(size_t index);

    void addHead(std::string key);

    void addTail(std::string key);

    bool removeHead();

    bool removeTail();

    std::string toStringFromHead();

    std::string toStringFromTail();

    bool removeKey(std::string key, size_t num);

    ForwardListNode *find(std::string key, size_t num);

    void writeToFile(std::string &file);

    void writeToFileBinary(std::string &file);

private:
    void toStringFromTailRec(std::string &s, ForwardListNode *node);

    void deleteForwardList();
};