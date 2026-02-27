#include "bstree.hpp"
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <cstring>
#include <stdexcept>

TreeNode::TreeNode(int key) : right(nullptr), left(nullptr), key(key) {}

Tree::Tree() : root(nullptr) {}

Tree::Tree(std::string &file, bool binary) : root(nullptr)
{
    if(binary)
    {
        std::ifstream ifs(file, std::ifstream::binary);
        if(!ifs.is_open())
        {
            throw std::ios_base::failure("cant open file");
        }

        TreeNode *node = nullptr;
        std::queue<TreeNode*> q;
        switch(readTreeNodeBinary(ifs, node))
        {
            case 0:
                this->root = node;
                q.push(node);
                break;
            case 2:
                destruct();
                throw std::ios_base::failure("bad file");
                break;
        }
        while(!q.empty())
        {
            node = q.front();
            q.pop();
            if(node != nullptr)
            {
                TreeNode *l;
                TreeNode *r;
                if(readTreeNodeBinary(ifs, l) || readTreeNodeBinary(ifs, r))
                {
                    destruct();
                    throw std::ios_base::failure("bad file");
                }
                node->right = r;
                node->left = l;
                if(l != nullptr)
                {
                    q.push(l);
                }
                if(r != nullptr)
                {
                    q.push(r);
                }
            }
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

        TreeNode *node = nullptr;
        std::queue<TreeNode*> q;
        switch(readTreeNode(ifs, node))
        {
            case 0:
                this->root = node;
                q.push(node);
                break;
            case 2:
                destruct();
                throw std::ios_base::failure("bad file");
                break;
        }
        while(!q.empty())
        {
            node = q.front();
            q.pop();
            if(node != nullptr)
            {
                TreeNode *l;
                TreeNode *r;
                if(readTreeNode(ifs, l) || readTreeNode(ifs, r))
                {
                    destruct();
                    throw std::ios_base::failure("bad file");
                }
                node->right = r;
                node->left = l;
                if(l != nullptr)
                {
                    q.push(l);
                }
                if(r != nullptr)
                {
                    q.push(r);
                }
            }
        }
        ifs.close();
    }
}

void Tree::deleteTreeRec(TreeNode *node)
{
    if(node == nullptr)
    {
        return;
    }
    deleteTreeRec(node->left);
    deleteTreeRec(node->right);
    delete node;
}

void Tree::destruct()
{
    deleteTreeRec(this->root);
}

Tree::~Tree()
{
    destruct();   
}

TreeNode *Tree::findMin(TreeNode *x)
{
    if(x == nullptr) return nullptr;
    while(x->left != nullptr)
    {
        x = x->left;
    }
    return x;
}

TreeNode* Tree::removeRec(TreeNode *node, int key)
{
    if(node == nullptr) return nullptr;
    
    if(key < node->key)
    {
        node->left = removeRec(node->left, key);
    }
    else if(key > node->key)
    {
        node->right = removeRec(node->right, key);
    }
    else
    {
        // Узел найден
        TreeNode* temp;
        
        // Случай 1: Узел без детей или с одним ребенком
        if(node->left == nullptr)
        {
            temp = node->right;
            delete node;
            return temp;
        }
        else if(node->right == nullptr)
        {
            temp = node->left;
            delete node;
            return temp;
        }
        
        // Случай 2: Узел с двумя детьми
        // Находим минимальный элемент в правом поддереве (преемник)
        temp = findMin(node->right);
        
        // Копируем значение преемника в текущий узел
        node->key = temp->key;
        
        // Удаляем преемника
        node->right = removeRec(node->right, temp->key);
    }
    
    return node;
}

void Tree::remove(int key)
{
    root = removeRec(root, key);
}

void Tree::add(int key)
{
    TreeNode *newNode = new TreeNode(key);
    
    // Если дерево пустое
    if(root == nullptr)
    {
        root = newNode;
        return;
    }
    
    // Поиск места для вставки
    TreeNode *current = root;
    TreeNode *parent = nullptr;
    
    while(current != nullptr)
    {
        parent = current;
        if(key < current->key)
        {
            current = current->left;
        }
        else if(key > current->key)
        {
            current = current->right;
        }
        else
        {
            // Элемент уже существует, не добавляем дубликаты
            delete newNode;
            return;
        }
    }
    
    // Вставка нового узла
    if(key < parent->key)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }
}

TreeNode *Tree::search(int key)
{
    TreeNode *node = this->root;
    while(node != nullptr && node->key != key)
    {
        if(key < node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return node;
}

void Tree::DFSinRec(std::string &vec, TreeNode *node)
{
    if(node == nullptr)
    {
        return;
    }

    DFSinRec(vec, node->left);
    vec += std::to_string(node->key) + " ";
    DFSinRec(vec, node->right);
}

void Tree::DFSpreRec(std::string &vec, TreeNode *node)
{
    if (node == nullptr)
    {
        return;
    }

    vec += std::to_string(node->key) + " ";
    DFSpreRec(vec, node->left);
    DFSpreRec(vec, node->right);
}

void Tree::DFSpostRec(std::string &vec, TreeNode *node)
{
    if(node == nullptr)
    {
        return;
    }

    DFSpostRec(vec, node->left);
    DFSpostRec(vec, node->right);
    vec += std::to_string(node->key) + " ";
}

void Tree::DFSin(std::string &vec)
{
    vec.clear();
    if(this->root == nullptr)
    {
        return;
    }

    DFSinRec(vec, this->root);
}

void Tree::DFSpre(std::string &vec)
{
    vec.clear();
    if(this->root == nullptr)
    {
        return;
    }

    DFSpreRec(vec, this->root);
}

void Tree::DFSpost(std::string &vec)
{
    vec.clear();
    if(this->root == nullptr)
    {
        return;
    }

    DFSpostRec(vec, this->root);
}

void Tree::BFS(std::string &vec)
{
    vec.clear();
    if(this->root == nullptr)
    {
        return;
    }
    
    std::queue<TreeNode*> q;
    q.push(this->root);
    
    while (!q.empty())
    {
        TreeNode* node = q.front();
        q.pop();
        
        if (node != nullptr)
        {
            vec += std::to_string(node->key) + " ";
            
            // Добавляем детей в очередь
            q.push(node->left);
            q.push(node->right);
        }
        else
        {
            vec += "null ";
        }
    }
}

std::string Tree::print()
{
    if(this->root == nullptr)
    {
        return "Дерево пустое\n";
    }
    
    std::string a = "";
    std::string order = "";

    BFS(order);
    a += "BFS: " + order + "\n";

    DFSin(order);
    a += "DFS in order: " + order + "\n";

    DFSpost(order);
    a += "DFS post order: " + order + "\n";

    DFSpre(order);
    a += "DFS pre order: " + order + "\n";
    return a;
}

bool isNumber(std::string &s)
{
    if(s.empty()) return false;
    if(!(s[0] == '-' || (s[0] >= '0' && s[0] <= '9')))
    {
        return false;
    }

    for(size_t i = 1; i < s.size(); i++)
    {
        if(s[i] < '0' || s[i] > '9')
        {
            return false;
        }
    }
    return true;
}

int Tree::readTreeNode(std::ifstream &ifs, TreeNode *&node)
{
    std::string a;
    if(ifs >> a)
    {
        if(a == "null")
        {
            node = nullptr;
        }
        else if(isNumber(a))
        {
            node = new TreeNode(std::stoi(a));
        }
        else
        {
            return 2; // не узел
        }
    }
    else
    {
        return 1; // ничего не прочитано
    }
    return 0;
}

void Tree::writeToFile(std::string &file)
{    
    std::ofstream ofs(file);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }
    std::queue<TreeNode*> q;
    q.push(this->root);
    while (!q.empty())
    {
        TreeNode* node = q.front();
        q.pop();
        if(node != nullptr)
        {
            ofs << node->key << " ";
            q.push(node->left);
            q.push(node->right);
        }
        else
        {
            ofs << "null ";
        }
    }
}

int Tree::readTreeNodeBinary(std::ifstream &ifs, TreeNode *&node)
{
    int key;
    if(ifs.read((char*)&key, sizeof(key)).gcount() == sizeof(key))
    {
        if(key == -2147483648) // специальное значение для null
        {
            node = nullptr;
        }
        else
        {
            node = new TreeNode(key);
        }
    }
    else if(ifs.gcount() == 0)
    {
        return 1; // ничего
    }
    else
    {
        return 2; // не узел
    }
    return 0;
}

void Tree::writeToFileBinary(std::string &file)
{
    std::ofstream ofs(file, std::ofstream::binary);
    if(!ofs.is_open())
    {
        throw std::ios_base::failure("cant open file");
    }
    std::queue<TreeNode*> q;
    q.push(this->root);
    while (!q.empty())
    {
        TreeNode* node = q.front();
        q.pop();
        if(node != nullptr)
        {
            ofs.write((char*)&node->key, sizeof(node->key));
            q.push(node->left);
            q.push(node->right);
        }
        else
        {
            int nullMarker = -2147483648; // специальное значение для null
            ofs.write((char*)&nullMarker, sizeof(nullMarker));
        }
    }
}
