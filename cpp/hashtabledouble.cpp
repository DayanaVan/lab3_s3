#include "hashtabledouble.hpp"

HashTableDouble::HashTableDouble(size_t capacity) : size(0), capacity(capacity), table(new Entry*[capacity])
{
    initialiseTable();
}

HashTableDouble::~HashTableDouble()
{
    deleteTable(this->table, this->capacity);
}

HashTableDouble::HashTableDouble(std::string &file, bool binary) : size(0), capacity(2), table(new Entry*[2])
{
    initialiseTable();
    if(binary)
    {
        std::ifstream ifs(file, std::ifstream::binary);
        if(!ifs.is_open())
        {
            throw std::ios_base::failure("cant open file");
        }

        int key;
        int val;
        while(ifs.read((char*)&key, sizeof(key)).gcount() == sizeof(key))
        {
            if(ifs.read((char*)&val, sizeof(val)).gcount() == sizeof(val))
            {
                insert(key, val);
            }
            else
            {
                deleteTable(this->table, this->capacity);
                throw std::ios_base::failure("bad file");
            }
        }
        if(ifs.gcount() != 0)
        {
            deleteTable(this->table, this->capacity);
            throw std::ios_base::failure("bad file");
        }
        ifs.close();
    }
    else
    {
        std::ifstream ifs(file, std::ifstream::binary);
        if(!ifs.is_open())
        {
            throw std::ios_base::failure("cant open file");
        }

        std::string a;
        while(ifs >> a)
        {
            size_t index = a.find(':');
            if(index == std::string::npos)
            {
                deleteTable(this->table, this->capacity);
                throw std::ios_base::failure("bad file");
            }
            std::string keyStr = a.substr(0, index);
            std::string valStr = a.substr(index+1, a.size() - index - 1);
            int key;
            int val;
            try
            {
                key = std::stoi(keyStr);
                val = std::stoi(valStr);
            } catch(...)
            {
                deleteTable(this->table, this->capacity);
                throw std::ios_base::failure("bad file");
            }
            insert(key, val);
        }

        ifs.close();
    }
}

void HashTableDouble::initialiseTable()
{
    for(size_t i = 0; i < this->capacity; i++)
    {
        this->table[i] = nullptr;
    }
}

void HashTableDouble::deleteTable(Entry **table, size_t capacity)
{
    if(table != nullptr)
    {
        for(size_t i = 0; i < capacity; i++)
        {
            delete table[i];
        }
        delete[] table;
    }
}

void HashTableDouble::rehash()
{
    Entry **oldTable = this->table;
    size_t oldCapacity = this->capacity;
    this->size = 0;

    //find new prime capacity
    this->capacity = this->capacity * 2;
    if(this->capacity % 2 == 0)
    {
        this->capacity++;
    }
    while (true)
    {
        bool isPrime = true;
        for (size_t i = 3; i * i <= this->capacity; i += 2)
        {
            if (this->capacity % i == 0)
            {
                isPrime = false;
                break;
            }
        }
        
        if(isPrime)
        {
            break;
        }
        this->capacity += 2;
    }

    this->table = new Entry*[this->capacity];
    initialiseTable();
    for(size_t i = 0; i < oldCapacity; i++)
    {
        if(oldTable[i] != nullptr && !oldTable[i]->deleted)
        {
            insert(oldTable[i]->key, oldTable[i]->value);
        }
    }

    deleteTable(oldTable, oldCapacity);
}

size_t HashTableDouble::hash1(int key)
{
    double x = key * 0.6180339887;
    if(x < 0)
    {
        x = -x;
    }
    double xx = x - size_t(x);
    return size_t(xx * this->capacity);
}

size_t HashTableDouble::hash2(int key)
{
    return (key % (this->capacity - 1)) + 1;
}

bool HashTableDouble::contains(int key)
{
    size_t h1 = hash1(key);
    size_t h2 = hash2(key);

    for(size_t i = 0; i < this->capacity; i++)
    {
        size_t h = (h1 + i * h2) % this->capacity;
        if(this->table[h] == nullptr)
        {
            return false;
        }
        if(this->table[h]->key == key)
        {
            return !this->table[h]->deleted;
        }
    }
    return false;
}

void HashTableDouble::insert(int key, int value)
{
    if(((double) this->size / this->capacity) > MAX_LOAD)
    {
        rehash();
    }
    size_t h1 = hash1(key);
    size_t h2 = hash2(key);

    for(size_t i = 0; i < this->capacity; i++)
    {
        size_t h = (h1 + i * h2) % this->capacity;
        if(this->table[h] == nullptr)
        {
            this->table[h] = new Entry{key, value, false};
            this->size++;
            return;
        }
        else if(this->table[h]->key == key)
        {
            this->table[h]->deleted = false;
            this->table[h]->value = value;
            return;
        }
    }
    rehash();
    insert(key, value);
}

bool HashTableDouble::remove(int key)
{
    size_t h1 = hash1(key);
    size_t h2 = hash2(key);

    for(size_t i = 0; i < this->capacity; i++)
    {
        size_t h = (h1 + i * h2) % this->capacity;
        if(this->table[h] == nullptr)
        {
            return false;
        }
        else if(this->table[h]->key == key)
        {
            if(this->table[h]->deleted)
            {
                return false;
            }
            this->table[h]->deleted = true;
            return true;
        }
    }
    return false;
}

int HashTableDouble::get(int key)
{
    size_t h1 = hash1(key);
    size_t h2 = hash2(key);

    for(size_t i = 0; i < this->capacity; i++)
    {
        size_t h = (h1 + i * h2) % this->capacity;
        if(this->table[h] == nullptr)
        {
            throw std::out_of_range("null");
        }
        else if(this->table[h]->key == key)
        {
            if(this->table[h]->deleted)
            {
                throw std::out_of_range("deleted");
            }
            else
            {
                return this->table[h]->value;
            }
        }
    }
    throw std::out_of_range("null");
}

std::string HashTableDouble::toString()
{
    std::string result = "";
    for(size_t i = 0; i < this->capacity; i++)
    {
        if(this->table[i] != nullptr && !this->table[i]->deleted)
        {
            result += std::to_string(this->table[i]->key) + " : "
            + std::to_string(this->table[i]->value) + "\n";
        }
    }
    return result;
}

void HashTableDouble::writeToFile(std::string &file)
{
    std::ofstream ofs(file);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }

    for(size_t i = 0; i < this->capacity; i++)
    {
        if(this->table[i] != nullptr && !this->table[i]->deleted)
        {
            ofs << std::to_string(this->table[i]->key) << ":" << std::to_string(this->table[i]->value) << " ";
        }
    }
}

void HashTableDouble::writeToFileBinary(std::string &file)
{
    std::ofstream ofs(file, std::ofstream::binary);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }

    for(size_t i = 0; i < this->capacity; i++)
    {
        if(this->table[i] != nullptr && !this->table[i]->deleted)
        {
            ofs.write((char*)&this->table[i]->key, sizeof(this->table[i]->key));
            ofs.write((char*)&this->table[i]->value, sizeof(this->table[i]->value));
        }
    }
}