#include "array.hpp"

Array::Array() : size(0), memorySize(0), memory(nullptr) {}

Array::~Array()
{
    delete[] this->memory;
}

Array::Array(std::string &file, bool binary) : size(0), memorySize(0), memory(nullptr)
{
    if(binary)
    {
        std::ifstream ifs(file, std::ifstream::binary);
        if(!ifs.is_open())
        {
            throw std::ios_base::failure("cant open file");
        }
        
        size_t stringSize;
        while(ifs.read((char*)&stringSize, sizeof(stringSize)).gcount() == sizeof(stringSize))
        {
            char s[stringSize+1];
            ifs.read(s, stringSize+1);// \0
            if(ifs.gcount() != stringSize+1)
            {
                delete[] this->memory;
                throw std::ios_base::failure("bad file");
            }
            add(s);
        }
        if(ifs.gcount() != 0)
        {
            delete[] this->memory;
            throw std::ios_base::failure("bad file");
        }

        ifs.close();
    }
    else
    {
        std::ifstream ifs(file);
        if(!ifs.is_open())
        {
            throw std::ios_base::failure("cant open file");
        }

        std::string a;
        while(ifs >> a)
        {
            add(a);
        }
        ifs.close();
    }
}

void Array::resize()
{
    std::string *oldMemory = this->memory;
    this->memorySize = size * 2 + static_cast<size_t>(size == 0);
    this->memory = new std::string[this->memorySize];
    for(size_t i = 0; i < this->size; i++)
    {
        this->memory[i] = oldMemory[i];
    }
    delete[] oldMemory;
}

bool Array::add(std::string key)
{
    if(this->memorySize < this->size + 1)
    {
        resize();
    }
    this->memory[size] = key;
    this->size++;
    return true;
}

bool Array::add(std::string key, size_t index)
{
    if(index > size)
    {
        return false;
    }

    if(memorySize < size + 1)
    {
        resize();
    }
    for(size_t i = size; i > index; i--)
    {
        this->memory[i] = this->memory[i-1];
    }
    this->memory[index] = key;
    
    this->size++;
    return true;
}

std::string Array::get(size_t index)
{
    if(index >= size)
    {
        throw std::out_of_range("");
    }
    return memory[index];
}

bool Array::remove(size_t index)
{
    if(index >= size)
    {
        return false;
    }
    
    for(size_t i = index; i < size-1; i++)
    {
        this->memory[i] = this->memory[i+1];
    }
    this->size--;
    return true;
}

bool Array::change(size_t index, std::string key)
{
    if(index >= size)
    {
        return false;
    }
    memory[index] = key;
    return true;
}

size_t Array::getSize()
{
    return this->size;
}

std::string Array::toString()
{
    std::string a = "";
    if(this->size == 0)
    {
        return a;
    }

    for(size_t i = 0; i < size-1; i++)
    {
        a += this->memory[i] + ' ';
    }
    a += this->memory[size-1];
    return a;
}

void Array::writeToFile(std::string &file)
{
    std::ofstream ofs(file);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }
    ofs << toString();
    ofs.close();
}

void Array::writeToFileBinary(std::string &file)
{
    std::ofstream ofs(file, std::ofstream::binary);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }
    for(size_t i = 0; i < this->size; i++)
    {
        size_t stringSize = this->memory[i].size();
        ofs.write((char*)&stringSize, sizeof(this->size));
        ofs.write(this->memory[i].c_str(), stringSize+1);// \0
    }
    ofs.close();
}