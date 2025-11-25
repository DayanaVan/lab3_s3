#include "stack.hpp"

StackNode::StackNode(std::string key) : prev(nullptr), key(key) {}

Stack::Stack() : top(nullptr) {}

Stack::~Stack()
{
    deleteStack();
}

Stack::Stack(std::string &file, bool binary) : top(nullptr)
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
                deleteStack();
                throw std::ios_base::failure("bad file");
            }
            push(s);
        }
        if(ifs.gcount() != 0)
        {
            deleteStack();
            throw std::ios_base::failure("bad file");
        }
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
            push(a);
        }
    }
}

void Stack::deleteStack()
{
    StackNode *node = this->top;
    while(node != nullptr)
    {
        StackNode *toDelete = node;
        node = node->prev;
        delete toDelete;
    }
}

void Stack::push(std::string key)
{
    StackNode *newNode = new StackNode(key);
    if(this->top == nullptr)
    {
        this->top = newNode;
        return;
    }

    newNode->prev = this->top;
    this->top = newNode;
}

std::string Stack::pop()
{
    if(this->top == nullptr)
    {
        throw std::out_of_range("");
    }
    StackNode *node = this->top;
    this->top = node->prev;
    std::string ret = node->key;
    delete node;
    return ret;
}

std::string Stack::toString()
{
    StackNode *node = this->top;
    if(node == nullptr)
    {
        return "";
    }

    std::string a = "";
    while(node->prev != nullptr)
    {
        a += node->key + " ";
        node = node->prev;
    }
    a += node->key;
    return a;
}

void Stack::writeToFileRec(std::ofstream &ofs, StackNode *node)
{
    if(node == nullptr)
    {
        return;
    }
    
    writeToFileRec(ofs, node->prev);
    ofs << node->key << " ";
}

void Stack::writeToFile(std::string &file)
{
    std::ofstream ofs(file);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }
    writeToFileRec(ofs, this->top);
    ofs.close();
}

void Stack::writeToFileBinaryRec(std::ofstream &ofs, StackNode *node)
{
    if(node == nullptr)
    {
        return;
    }
    
    writeToFileBinaryRec(ofs, node->prev);
    size_t stringSize = node->key.size();
    ofs.write((char*)&stringSize, sizeof(stringSize));
    ofs.write(node->key.c_str(), stringSize+1);// \0
}

void Stack::writeToFileBinary(std::string &file)
{
    std::ofstream ofs(file, std::ofstream::binary);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }
    writeToFileBinaryRec(ofs, this->top);
    ofs.close();
}