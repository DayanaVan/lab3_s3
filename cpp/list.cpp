#include "list.hpp"

ListNode::ListNode(std::string key) : next(nullptr), prev(nullptr), key(key) {}

List::List() : tail(nullptr), head(nullptr) {}

List::~List()
{
    deleteList();
}

List::List(std::string &file, bool binary) : tail(nullptr), head(nullptr)
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
                ifs.close();
                deleteList();
                throw std::ios_base::failure("bad file");
            }

            addTail(s);
        }
        if(ifs.gcount() != 0)
        {
            ifs.close();
            deleteList();
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
            addTail(a);
        }
        ifs.close();
    }
}

void List::deleteList()
{
    ListNode *node = this->head;
    while(node != nullptr)
    {
        ListNode *toDelete = node;
        node = node->next;
        delete toDelete;
    }
}

bool List::insert(std::string key, size_t index)
{
    if(index == 0)
    {
        addHead(key);
        return true;
    }
    
    ListNode *node = this->head;
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
    if(node == this->tail)
    {
        addTail(key);
        return true;
    }
    ListNode *newNode = new ListNode(key);
    newNode->next = node->next;
    newNode->prev = node;
    node->next = newNode;
    newNode->next->prev = node->prev;
    return true;
}

bool List::remove(size_t index)
{
    if(index == 0)
    {
        return removeHead();
    }

    ListNode *node = this->head;
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
    if(node->next == this->tail)
    {
        return removeTail();
    }
    ListNode *toDelete = node->next;
    if(toDelete != nullptr)
    {
        node->next = toDelete->next;
        toDelete->next->prev = node;
        delete toDelete;
        return true;
    }
    return false;
}

void List::addTail(std::string key)
{
    ListNode *node = new ListNode(key);
    if(this->tail == nullptr)
    {
        this->tail = node;
        this->head = node;
        return;
    }
    node->prev = this->tail;
    this->tail->next = node;
    this->tail = node;
}

void List::addHead(std::string key)
{
    ListNode *node = new ListNode(key);
    if(this->tail == nullptr)
    {
        this->tail = node;
        this->head = node;
        return;
    }
    node->next = this->head;
    this->head->prev = node;
    this->head = node;
}

bool List::removeTail()
{
    if(this->tail == nullptr)
    {
        return false;
    }

    if(this->tail == this->head)
    {
        delete this->head;
        this->tail = nullptr;
        this->head = nullptr;
        return true;
    }
    this->tail = this->tail->prev;
    delete this->tail->next;
    this->tail->next = nullptr;
    return true;
}

bool List::removeHead()
{
    if(this->head == nullptr)
    {
        return false;
    }

    if(this->tail == this->head)
    {
        delete this->tail;
        this->tail = nullptr;
        this->head = nullptr;
        return true;
    }
    this->head = this->head->next;
    delete this->head->prev;
    this->head->prev = nullptr;
    return true;
}

std::string List::toStringFromTail()
{
    ListNode *node = this->tail;
    if(node == nullptr)
    {
        return "";
    }
    std::string a = "";
    while(node->prev != nullptr)
    {
        a += node->key + ' ';
        node = node->prev;
    }
    a += node->key;
    return a;
}

std::string List::toStringFromHead()
{
    ListNode *node = this->head;
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

bool List::removeKey(std::string key, size_t num)
{
    if(num == 0)
    {
        return false;
    }
    size_t n = 1;
    ListNode *node = this->head;
    while(node != nullptr)
    {
        if(node->key == key)
        {
            if(n == num)
            {
                if(node == this->tail)
                {
                    return removeTail();
                }
                else if(node == this->head)
                {
                    return removeHead();
                }
                node->prev->next = node->next;
                node->next->prev = node->prev;
                node->next = node->next;
                delete node;
                return true;
            }
            n++;
        }
        node = node->next;
    }
    return false;
}

ListNode *List::find(std::string key, size_t num)
{
    if(num == 0)
    {
        return nullptr;
    }

    size_t n = 1;
    ListNode *node = this->head;
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

void List::writeToFile(std::string &file)
{
    std::ofstream ofs(file);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }
    ofs << toStringFromHead();
    ofs.close();
}

void List::writeToFileBinary(std::string &file)
{
    std::ofstream ofs(file, std::ofstream::binary);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }

    ListNode *node = this->head;
    while(node != nullptr)
    {
        size_t stringSize = node->key.size();
        ofs.write((char*)&stringSize, sizeof(stringSize));
        ofs.write(node->key.c_str(), stringSize+1);// \0
        node = node->next;
    }
    ofs.close();
}