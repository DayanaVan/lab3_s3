#pragma once

#include <string>
#include <fstream>

class Array
{
private:
    size_t size;

    size_t memorySize;
    
    std::string *memory;

    void resize();

public:
    Array();
    Array(std::string &file, bool binary);
    ~Array();

    bool add(std::string key);

    bool add(std::string key, size_t index);

    std::string get(size_t index);

    bool remove(size_t index);

    bool change(size_t index, std::string key);

    size_t getSize();

    std::string toString();

    void writeToFile(std::string &file);

    void writeToFileBinary(std::string &file);
};