#pragma once

#include <string>
#include <fstream>

class HashTableDouble
{
private:
    const double MAX_LOAD = 0.75;

    struct Entry
    {
        int key;
        int value;
        bool deleted;
    };

    size_t size;
    size_t capacity;
    Entry **table;

    void rehash();

    void initialiseTable();
    
    void deleteTable(Entry **table, size_t capacity);

    size_t hash1(int key);
    size_t hash2(int key);

public:
    HashTableDouble(size_t capacity);

    HashTableDouble(std::string &file, bool binary);

    ~HashTableDouble();

    void insert(int key, int value);

    bool contains(int key);

    bool remove(int key);

    int get(int key);

    std::string toString();

    void writeToFile(std::string &file);

    void writeToFileBinary(std::string &file);
};