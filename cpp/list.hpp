#pragma once

#include <string>
#include <fstream>

struct ListNode
{
    ListNode *next;
    ListNode *prev;
    std::string key;

    ListNode(std::string key);
};

class List
{
public:
    ListNode *tail;
    ListNode *head;

    List();
    List(std::string &file, bool binary);
    ~List();

    void addHead(std::string key);

    void addTail(std::string key);

    bool insert(std::string key, size_t index);

    bool remove(size_t index);

    bool removeHead();

    bool removeTail();

    std::string toStringFromHead();

    std::string toStringFromTail();

    bool removeKey(std::string key, size_t num);

    ListNode *find(std::string key, size_t num);

    void writeToFile(std::string &file);

    void writeToFileBinary(std::string &file);

private:
    void deleteList();
};