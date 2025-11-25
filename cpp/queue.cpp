#include "queue.hpp"

QueueNode::QueueNode(std::string key) : next(nullptr), key(key) {}

Queue::Queue() : top(nullptr), bot(nullptr) {}

Queue::~Queue()
{
    deleteQueue();
}

Queue::Queue(std::string &file, bool binary) : top(nullptr), bot(nullptr)
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
                deleteQueue();
                throw std::ios_base::failure("bad file");
            }
            push(s);
        }
        if(ifs.gcount() != 0)
        {
            deleteQueue();
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
            push(a);
        }
        ifs.close();
    }
}

void Queue::deleteQueue()
{
    QueueNode *node = this->bot;
    while(node != nullptr)
    {
        QueueNode *toDelete = node;
        node = node->next;
        delete toDelete;
    }
}

void Queue::push(std::string key)
{
    QueueNode *newNode = new QueueNode(key);
    if(this->top == nullptr)
    {
        this->bot = newNode;
        this->top = newNode;
        return;
    }

    this->top->next = newNode;
    this->top = newNode;
}

std::string Queue::pop()
{
    if(this->bot == nullptr)
    {
        throw std::out_of_range("");
    }

    QueueNode *node = this->bot;
    this->bot = node->next;
    if(this->bot == nullptr)
    {
        this->top = nullptr;
    }
    std::string ret = node->key;
    delete node;
    return ret;
}

std::string Queue::toString()
{
    QueueNode *node = this->bot;
    if(node == nullptr)
    {
        return "";
    }

    std::string a = "";
    while(node->next != nullptr)
    {
        a += node->key + " ";
        node = node->next;
    }
    a += node->key;
    return a;
}

void Queue::writeToFile(std::string &file)
{
    std::ofstream ofs(file);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }
    ofs << toString();
    ofs.close();
}

void Queue::writeToFileBinary(std::string &file)
{
    std::ofstream ofs(file, std::ofstream::binary);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }
    QueueNode *node = this->bot;
    while(node != nullptr)
    {
        size_t stringSize = node->key.size();
        ofs.write((char*)&stringSize, sizeof(stringSize));
        ofs.write(node->key.c_str(), stringSize+1);// \0
        node = node->next;
    }
    ofs.close();
}