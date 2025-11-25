#pragma once

#include <string>
#include <queue>
#include <vector>
#include <fstream>

#define Color bool
#define red true
#define black false

struct TreeNode
{
    TreeNode *right;
    TreeNode *left;
    TreeNode *parent;
    Color color;
    int key;

    TreeNode(int key, TreeNode *nil);
};

class Tree
{
public:
    TreeNode *nil;
    TreeNode *root;

    Tree();
    Tree(std::string &file, bool binary);
    ~Tree();

    void add(int key);

    void remove(TreeNode *z);

    TreeNode *search(int key);

    void DFSin(std::string &vec);

    void DFSpre(std::string &vec);

    void DFSpost(std::string &vec);

    void BFS(std::string &vec);

    std::string print();

    void writeToFile(std::string &file);

    void writeToFileBinary(std::string &file);

private:
    TreeNode *minimum(TreeNode *x);

    void transplant(TreeNode *u, TreeNode *v);

    void removeFix(TreeNode *node);

    void leftRotate(TreeNode *x);

    void rightRotate(TreeNode *x);

    void addFix(TreeNode *node);

    void destruct();
    
    void DFSinRec(std::string &vec, TreeNode *node);

    void DFSpreRec(std::string &vec, TreeNode *node);

    void DFSpostRec(std::string &vec, TreeNode *node);

    void deleteTreeRec(TreeNode *node);

    int readTreeNode(std::ifstream &ifs, TreeNode *&node);

    int readTreeNodeBinary(std::ifstream &ifs, TreeNode *&node);
};

bool isNumber(std::string &s);