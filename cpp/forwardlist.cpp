#include "forwardlist.hpp"

ForwardListNode::ForwardListNode(std::string key) : next(nullptr), key(key) {}

ForwardList::ForwardList() : head(nullptr){}

ForwardList::~ForwardList()
{
    deleteForwardList();
}

ForwardList::ForwardList(std::string &file, bool binary) : head(nullptr)
{
    if(binary)
    {
        std::ifstream ifs(file, std::ifstream::binary);
        if(!ifs.is_open())
        {
            throw std::ios_base::failure("cant open file");
        }

        ForwardListNode *tail;
        size_t stringSize;
        while(ifs.read((char*)&stringSize, sizeof(stringSize)).gcount() == sizeof(stringSize))
        {
            char s[stringSize+1];
            ifs.read(s, stringSize+1);// \0
            if(ifs.gcount() != stringSize+1)
            {
                ifs.close();
                deleteForwardList();
                throw std::ios_base::failure("bad file");
            }

            if(this->head == nullptr)
            {
                addHead(s);
                tail = this->head;
            }
            else
            {
                tail->next = new ForwardListNode(s);
                tail = tail->next;
            }
        }
        if(ifs.gcount() != 0)
        {
            deleteForwardList();
            ifs.close();
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
        ForwardListNode *tail;
        while(ifs >> a)
        {
            if(this->head == nullptr)
            {
                addHead(a);
                tail = this->head;
            }
            else
            {
                tail->next = new ForwardListNode(a);
                tail = tail->next;
            }
        }
        ifs.close();
    }
}

void ForwardList::deleteForwardList()
{
    ForwardListNode *node = this->head;
    while(node != nullptr)
    {
        ForwardListNode *toDelete = node;
        node = node->next;
        delete toDelete;
    }
}

bool ForwardList::insert(std::string key, size_t index)
{
    if(index == 0)
    {
        addHead(key);
        return true;
    }
    
    ForwardListNode *node = this->head;
    for(size_t i = 0; i < index - 1; i++)
    {
        if(node == nullptr)
        {
            break;
        }
        node = node->next;
    }
    if(node == nullptr)
    {
        return false;
    }
    ForwardListNode *newNode = new ForwardListNode(key);
    newNode->next = node->next;
    node->next = newNode;
    return true;
}

bool ForwardList::remove(size_t index)
{
    if(index == 0)
    {
        return removeHead();
    }

    ForwardListNode *node = this->head;
    for(size_t i = 0; i < index - 1; i++)
    {
        if(node == nullptr)
        {
            break;
        }
        node = node->next;
    }
    if(node == nullptr)
    {
        return false;
    }
    ForwardListNode *toDelete = node->next;
    if(toDelete != nullptr)
    {
        node->next = toDelete->next;
        delete toDelete;
        return true;
    }
    return false;
}

void ForwardList::addTail(std::string key)
{
    if(this->head == nullptr)
    {
        this->head = new ForwardListNode(key);
        return;
    }
    ForwardListNode *node = this->head;
    while(node->next != nullptr)
    {
        node = node->next;
    }
    node->next = new ForwardListNode(key);
}

void ForwardList::addHead(std::string key)
{
    if(this->head == nullptr)
    {
        this->head = new ForwardListNode(key);
        return;
    }
    ForwardListNode *node = new ForwardListNode(key);
    node->next = this->head;
    this->head = node;
}

bool ForwardList::removeTail()
{
    if(this->head == nullptr)
    {
        return false;
    }

    ForwardListNode *node = this->head;
    if(node->next == nullptr)
    {
        return removeHead();
    }
    while(node->next->next != nullptr)
    {
        node = node->next;
    }
    delete node->next;
    node->next = nullptr;
    return true;
}

bool ForwardList::removeHead()
{
    if(this->head == nullptr)
    {
        return false;
    }

    ForwardListNode *toDelete = this->head;
    this->head = toDelete->next;
    delete toDelete;
    return true;
}

std::string ForwardList::toStringFromHead()
{
    ForwardListNode *node = this->head;
    if(node == nullptr)
    {
        return "";
    }
    std::string a = "";
    while(node->next != nullptr)
    {
        a += node->key + ' ';
        node = node->next;
    }
    a += node->key;
    return a;
}

void ForwardList::toStringFromTailRec(std::string &s, ForwardListNode *node)
{
    if(node == nullptr)
    {
        return;
    }
    toStringFromTailRec(s, node->next);
    s += node->key + " ";
}

std::string ForwardList::toStringFromTail()
{
    std::string s = "";
    if(this->head == nullptr)
    {
        return s;
    }
    toStringFromTailRec(s, this->head->next);
    return s + this->head->key;
}

bool ForwardList::removeKey(std::string key, size_t num)
{
    if(this->head == nullptr || num == 0)
    {
        return false;
    }
    size_t n = 1;
    ForwardListNode *node = this->head;
    if(node->key == key)
    {
        if(num == n)
        {
            return removeHead();
        }
        n++;
    }
    while(node->next != nullptr)
    {
        if(node->next->key == key)
        {
            if(n == num)
            {
                ForwardListNode *toDelete = node->next;
                node->next = toDelete->next;
                delete toDelete;
                return true;
            }
            n++;
        }
        node = node->next;
    }
    return false;
}

ForwardListNode *ForwardList::find(std::string key, size_t num)
{
    if(num == 0)
    {
        return nullptr;
    }
    size_t n = 1;
    ForwardListNode *node = this->head;
    while(node != nullptr)
    {
        if(node->key == key)
        {
            if(n == num)
            {
                return node;
            }
            n++;
        }
        node = node->next;
    }
    return nullptr;
}

void ForwardList::writeToFile(std::string &file)
{
    std::ofstream ofs(file);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }
    ofs << toStringFromHead();
    ofs.close();
}

void ForwardList::writeToFileBinary(std::string &file)
{
    std::ofstream ofs(file, std::ofstream::binary);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }
    ForwardListNode *node = this->head;
    while(node != nullptr)
    {
        size_t stringSize = node->key.size();
        ofs.write((char*)&stringSize, sizeof(stringSize));
        ofs.write(node->key.c_str(), stringSize+1);// \0
        node = node->next;
    }
    ofs.close();
}