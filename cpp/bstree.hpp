#pragma once

#include <string>
#include <queue>
#include <vector>
#include <fstream>

struct TreeNode
{
    TreeNode *right;
    TreeNode *left;
    int key;

    TreeNode(int key);
};

class Tree
{
public:
    TreeNode *root;

    Tree();
    Tree(std::string &file, bool binary);
    ~Tree();

    void add(int key);
    void remove(int key);
    TreeNode *search(int key);
    
    // Публичные методы для обходов
    void DFSin(std::string &vec);
    void DFSpre(std::string &vec);
    void DFSpost(std::string &vec);
    void BFS(std::string &vec);
    
    std::string print();
    void writeToFile(std::string &file);
    void writeToFileBinary(std::string &file);
    
    TreeNode *findMin(TreeNode *x);

private:
    TreeNode *removeRec(TreeNode *node, int key);
    void destruct();
    
    void DFSinRec(std::string &vec, TreeNode *node);
    void DFSpreRec(std::string &vec, TreeNode *node);
    void DFSpostRec(std::string &vec, TreeNode *node);
    void deleteTreeRec(TreeNode *node);

    int readTreeNode(std::ifstream &ifs, TreeNode *&node);
    int readTreeNodeBinary(std::ifstream &ifs, TreeNode *&node);
};

bool isNumber(std::string &s);
