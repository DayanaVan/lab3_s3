#include "rbtree.hpp"

TreeNode::TreeNode(int key, TreeNode *nil) : right(nil), left(nil),
                                             parent(nil), color(red), key(key) {}

Tree::Tree() : nil(new TreeNode(0, nullptr)), root(nil)
{
    this->nil->color = black;
}

Tree::Tree(std::string &file, bool binary) : nil(new TreeNode(0, nullptr)), root(nil)
{
    this->nil->color = black;
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
            if(node != this->nil)
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
                if(l != this->nil)
                {
                    l->parent = node;
                    q.push(l);
                }
                if(r != this->nil)
                {
                    r->parent = node;
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
            if(node != this->nil)
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
                if(l != this->nil)
                {
                    l->parent = node;
                    q.push(l);
                }
                if(r != this->nil)
                {
                    r->parent = node;
                    q.push(r);
                }
            }
        }
        ifs.close();
    }
}

void Tree::deleteTreeRec(TreeNode *node)
{
    if(node->left != this->nil)
    {
        deleteTreeRec(node->left);
    }
    if(node->right != this->nil)
    {
        deleteTreeRec(node->right);
    }
    delete node;
}

void Tree::destruct()
{
    if(this->root != this->nil)
    {
        deleteTreeRec(this->root);
    }
    delete this->nil;
}

Tree::~Tree()
{
    destruct();   
}

void Tree::leftRotate(TreeNode *x)
{
    TreeNode *y = x->right;
    x->right = y->left;

    if(y->left != this->nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == this->nil)
    {
        this->root = y;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;

    x->parent = y;
}

void Tree::rightRotate(TreeNode *x)
{
    TreeNode *y = x->left;
    x->left = y->right;

    if(y->right != this->nil)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == this->nil)
    {
        this->root = y;
    }
    else if(x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    y->right = x;

    x->parent = y;
}

void Tree::addFix(TreeNode *z)
{
    while(z->parent->color == red)
    {
        if(z->parent == z->parent->parent->left)
        {
            TreeNode *y = z->parent->parent->right;
            if(y->color == red)
            {
                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            }
            else 
            {
                if(z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = black;
                z->parent->parent->color = red;
                rightRotate(z->parent->parent);
            }
        }                
        else
        {
            TreeNode *y = z->parent->parent->left;
            if(y->color == red)
            {
                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            }
            else 
            {
                if(z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = black;
                z->parent->parent->color = red;
                leftRotate(z->parent->parent);
            }
        }
    }
    this->root->color = black;
}

void Tree::add(int key)
{
    TreeNode *z = new TreeNode(key, this->nil);
    TreeNode *y = this->nil;
    TreeNode *x = this->root;
    while(x != this->nil)
    {
        y = x;
        if(z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if(y == this->nil)
    {
        this->root = z;
    }
    else if(z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = this->nil;
    z->right = this->nil;
    addFix(z);
}

void Tree::transplant(TreeNode *u, TreeNode *v)
{
    if(u->parent == this->nil)
    {
        this->root = v;
    }
    else if(u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

TreeNode *Tree::minimum(TreeNode *x)
{
    while(x->left != this->nil)
    {
        x = x->left;
    }
    return x;
}

void Tree::removeFix(TreeNode *x)
{
    while(x != this->root && x->color == black)
    {
        if(x == x->parent->left)
        {
            TreeNode *w = x->parent->right;
            if(w->color == red)
            {
                w->color = black;
                x->parent->color = red;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if(w->left->color == black && w->right->color == black)
            {
                w->color = red;
                x = x->parent;
            }
            else
            {
                if(w->right->color == black)
                {
                    w->left->color = black;
                    w->color = red;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = black;
                w->right->color = black;
                leftRotate(x->parent);
                x = this->root;
            }
        }
        else
        {
            TreeNode *w = x->parent->left;
            if(w->color == red)
            {
                w->color = black;
                x->parent->color = red;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if(w->right->color == black && w->left->color == black)
            {
                w->color = red;
                x = x->parent;
            }
            else
            {
                if(w->left->color == black)
                {
                    w->right->color = black;
                    w->color = red;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = black;
                w->left->color = black;
                rightRotate(x->parent);
                x = this->root;
            }
        }
    }
    x->color = black;
}

void Tree::remove(TreeNode *z)
{
    if(z == this->nil)
    {
        return;
    }
    TreeNode *y = z;
    TreeNode *x = this->nil;
    Color y_origColor = y->color;
    if(z->left == this->nil)
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if(z->right == this->nil)
    {
        x = z->left;
        transplant(z, z->left);
    }
    else
    {
        y = minimum(z->right);
        y_origColor = y->color;
        x = y->right;
        if(y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if(y_origColor == black)
    {
        removeFix(x);
    }
    delete z;
}

TreeNode *Tree::search(int key)
{
    TreeNode *node = this->root;
    while(node != this->nil && node->key != key)
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
    if(node == this->nil)
    {
        return;
    }

    DFSinRec(vec, node->left);
    vec += std::to_string(node->key);
    if(node->color == red)
    {
        vec += "_R ";
    }
    else
    {
        vec += "_B ";
    }
    DFSinRec(vec, node->right);
}

void Tree::DFSpreRec(std::string &vec, TreeNode *node)
{
    if (node == this->nil)
    {
        return;
    }

    vec += std::to_string(node->key);
    if(node->color == red)
    {
        vec += "_R ";
    }
    else
    {
        vec += "_B ";
    }
    DFSpreRec(vec, node->left);
    DFSpreRec(vec, node->right);
}

void Tree::DFSpostRec(std::string &vec, TreeNode *node)
{
    if(node == this->nil)
    {
        return;
    }

    DFSpostRec(vec, node->left);
    DFSpostRec(vec, node->right);
    vec += std::to_string(node->key);
    if(node->color == red)
    {
        vec += "_R ";
    }
    else
    {
        vec += "_B ";
    }
}

void Tree::DFSin(std::string &vec)
{
    vec.clear();
    if(this->root == this->nil)
    {
        return;
    }

    DFSinRec(vec, this->root);
}

void Tree::DFSpre(std::string &vec)
{
    vec.clear();
    if(this->root == this->nil)
    {
        return;
    }

    DFSpreRec(vec, this->root);
}

void Tree::DFSpost(std::string &vec)
{
    vec.clear();
    if(this->root == this->nil)
    {
        return;
    }

    DFSpostRec(vec, this->root);
}

void Tree::BFS(std::string &vec)
{
    vec.clear();
    if(this->root == this->nil)
    {
        return;
    }
    
    std::queue<TreeNode*> q;
    q.push(this->root);
    while (!q.empty())
    {
        TreeNode* node = q.front();
        q.pop();
        vec += std::to_string(node->key);
        if(node->color == red)
        {
            vec += "_R ";
        }
        else
        {
            vec += "_B ";
        }
        
        if(node->left != this->nil)
        {
            q.push(node->left);
        }
        if(node->right != this->nil)
        {
            q.push(node->right);
        }
    }
}

std::string Tree::print()
{
    if(this->root == this->nil)
    {
        return "";
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
        int colorIndex = a.size()-1;
        std::string keystr(a.begin(), a.end() - 1);
        if(!(a == "00" || ((a[colorIndex] == 'R' || a[colorIndex] == 'B') && isNumber(keystr))))
        {
            return 2;//not node
        }
        if(a == "00")
        {
            node = this->nil;
        }
        else
        {
            node = new TreeNode(std::stoi(keystr), this->nil);
            if(a[colorIndex] == 'R')
            {
                node->color = red;
            }
            else
            {
                node->color = black;
            }
        }
    }
    else
    {
        return 1;//nothing
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
        if(node != this->nil)
        {
            ofs << node->key;
            if(node->color == black)
            {
                ofs << "B";
            }
            else
            {
                ofs << "R";
            }
            ofs << " ";
            q.push(node->left);
            q.push(node->right);
        }
        else
        {
            ofs << "00 ";
        }
    }
}

int Tree::readTreeNodeBinary(std::ifstream &ifs, TreeNode *&node)
{
    int key;
    if(ifs.read((char*)&key, sizeof(key)).gcount() == sizeof(key))
    {
        char color;
        ifs.read((char*)&color, sizeof(color));
        if(color < 0 || color > 2)
        {
            return 2; //not node
        }

        if(color == 2)
        {
            node = this->nil;
        }
        else
        {
            node = new TreeNode(key, this->nil);
            node->color = color;
        }
    }
    else if(ifs.gcount() == 0)
    {
        return 1; //nothing
    }
    else
    {
        return 2; //not node
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
        if(node != this->nil)
        {
            ofs.write((char*)&node->key, sizeof(node->key));
            ofs.write((char*)&node->color, sizeof(node->color));
            q.push(node->left);
            q.push(node->right);
        }
        else
        {
            ofs.write((char*)&this->nil->key, sizeof(this->nil->key));
            char c = 2;
            ofs.write(&c, sizeof(c));
        }
    }
}