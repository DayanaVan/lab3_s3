#define BOOST_TEST_MODULE StructuresTest
#include <boost/test/included/unit_test.hpp>

#include "../bstree.hpp" 
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

BOOST_AUTO_TEST_SUITE(TreeTests)

BOOST_AUTO_TEST_CASE(Add_Search_Test)
{
    Tree t;
    t.add(1);
    t.add(2);
    t.add(3);
    t.add(4);
    t.add(5);
    t.add(10);
    t.add(8);
    t.add(7);

    BOOST_CHECK_EQUAL(t.search(0), nullptr);
    BOOST_REQUIRE(t.search(1) != nullptr);
    BOOST_CHECK_EQUAL(t.search(1)->key, 1);
    BOOST_REQUIRE(t.search(2) != nullptr);
    BOOST_CHECK_EQUAL(t.search(2)->key, 2);
    BOOST_REQUIRE(t.search(3) != nullptr);
    BOOST_CHECK_EQUAL(t.search(3)->key, 3);
    BOOST_REQUIRE(t.search(4) != nullptr);
    BOOST_CHECK_EQUAL(t.search(4)->key, 4);
    BOOST_REQUIRE(t.search(5) != nullptr);
    BOOST_CHECK_EQUAL(t.search(5)->key, 5);
    BOOST_REQUIRE(t.search(10) != nullptr);
    BOOST_CHECK_EQUAL(t.search(10)->key, 10);
    BOOST_REQUIRE(t.search(8) != nullptr);
    BOOST_CHECK_EQUAL(t.search(8)->key, 8);
    BOOST_REQUIRE(t.search(7) != nullptr);
    BOOST_CHECK_EQUAL(t.search(7)->key ,7);

    // Проверка дубликатов
    t.add(5);
    t.add(5);
    string a = "";
    t.BFS(a);
    // Проверяем, что нет дубликатов
    BOOST_CHECK(a.find("5 5") == string::npos);

    Tree t2;
    t2.add(5);
    t2.add(4);
    t2.add(3);
    t2.add(2);
    t2.add(1);
    t2.add(-5);
    t2.add(-3);
    t2.add(-2);

    BOOST_CHECK_EQUAL(t2.search(0), nullptr);
    BOOST_REQUIRE(t2.search(5) != nullptr);
    BOOST_CHECK_EQUAL(t2.search(5)->key, 5);
    BOOST_REQUIRE(t2.search(4) != nullptr);
    BOOST_CHECK_EQUAL(t2.search(4)->key, 4);
    BOOST_REQUIRE(t2.search(3) != nullptr);
    BOOST_CHECK_EQUAL(t2.search(3)->key, 3);
    BOOST_REQUIRE(t2.search(2) != nullptr);
    BOOST_CHECK_EQUAL(t2.search(2)->key, 2);
    BOOST_REQUIRE(t2.search(1) != nullptr);
    BOOST_CHECK_EQUAL(t2.search(1)->key, 1);
    BOOST_REQUIRE(t2.search(-5) != nullptr);
    BOOST_CHECK_EQUAL(t2.search(-5)->key, -5);
    BOOST_REQUIRE(t2.search(-3) != nullptr);
    BOOST_CHECK_EQUAL(t2.search(-3)->key, -3);
    BOOST_REQUIRE(t2.search(-2) != nullptr);
    BOOST_CHECK_EQUAL(t2.search(-2)->key, -2);
}

BOOST_AUTO_TEST_CASE(Remove_Test)
{
    Tree t;
    t.add(1);
    t.add(2);
    t.add(3);
    t.add(4);
    t.add(5);
    t.add(10);
    t.add(8);

    t.remove(2);
    t.remove(8);
    t.remove(5);
    t.remove(10);
    t.remove(4);
    t.remove(3);
    t.remove(1);

    BOOST_CHECK_EQUAL(t.root, nullptr);

    t.add(5);
    t.add(4);
    t.add(3);
    t.add(2);
    t.add(1);
    t.add(-5);
    t.add(-3);

    t.remove(3);
    t.remove(-3);
    t.remove(5);
    t.remove(-5);
    t.remove(2);
    t.remove(1);
    t.remove(4);

    BOOST_CHECK_EQUAL(t.root, nullptr);
    
    // Тест удаления несуществующего элемента
    Tree t3;
    t3.add(10);
    t3.add(5);
    t3.add(15);
    t3.remove(20); // несуществующий
    BOOST_REQUIRE(t3.search(10) != nullptr);
    BOOST_CHECK_EQUAL(t3.search(10)->key, 10);
    BOOST_REQUIRE(t3.search(5) != nullptr);
    BOOST_CHECK_EQUAL(t3.search(5)->key, 5);
    BOOST_REQUIRE(t3.search(15) != nullptr);
    BOOST_CHECK_EQUAL(t3.search(15)->key, 15);
}

BOOST_AUTO_TEST_CASE(Print_Test)
{
    Tree t;
    // Добавляем элементы для сбалансированного дерева
    t.add(4);
    t.add(2);
    t.add(1);
    t.add(3);
    t.add(5);
    
    std::string actual = t.print();
    
    // Проверяем, что основные части строки совпадают
    BOOST_CHECK(actual.find("DFS in order: 1 2 3 4 5") != std::string::npos);
    BOOST_CHECK(actual.find("DFS post order: 1 3 2 5 4") != std::string::npos);
    BOOST_CHECK(actual.find("DFS pre order: 4 2 1 3 5") != std::string::npos);
    
    // Для BFS проверяем только начало (ключи в правильном порядке)
    std::string bfsPart = actual.substr(0, actual.find('\n'));
    BOOST_CHECK(bfsPart.find("BFS: 4 2 5 1 3") != std::string::npos);
    
    // Пустое дерево
    Tree t2;
    BOOST_CHECK_EQUAL(t2.print(), "Дерево пустое\n");
}

BOOST_AUTO_TEST_CASE(FindMin_Test)
{
    Tree t;
    t.add(10);
    t.add(5);
    t.add(15);
    t.add(3);
    t.add(7);
    t.add(12);
    t.add(18);
    
    TreeNode* min = t.findMin(t.root);
    BOOST_REQUIRE(min != nullptr);
    BOOST_CHECK_EQUAL(min->key, 3);
    
    TreeNode* minRight = t.findMin(t.root->right);
    BOOST_REQUIRE(minRight != nullptr);
    BOOST_CHECK_EQUAL(minRight->key, 12);
    
    // Тест на пустом поддереве
    TreeNode* emptyNode = t.findMin(nullptr);
    BOOST_CHECK_EQUAL(emptyNode, nullptr);
}

BOOST_AUTO_TEST_CASE(IO_Test)
{
    string textTestFile = ".texttestfile";
    string binTestFile = ".bintestfile";
    //empty
    Tree *t = new Tree();
    BOOST_CHECK_NO_THROW(t->writeToFile(textTestFile));
    BOOST_CHECK_NO_THROW(t->writeToFileBinary(binTestFile));
    delete t;
    t = new Tree(textTestFile, false);
    std::string a;
    t->BFS(a);
    BOOST_CHECK_EQUAL(a, "");
    delete t;
    t = new Tree(binTestFile, true);
    t->BFS(a);
    BOOST_CHECK_EQUAL(a, "");
    
    //not empty
    t->add(1);
    t->add(2);
    t->add(3);
    t->add(4);
    t->add(5);
    BOOST_CHECK_NO_THROW(t->writeToFile(textTestFile));
    BOOST_CHECK_NO_THROW(t->writeToFileBinary(binTestFile));

    Tree textTree(textTestFile, false);
    Tree binTree(binTestFile, true);
    std::string tS, bS, S;
    t->BFS(S);
    textTree.BFS(tS);
    binTree.BFS(bS);
    BOOST_CHECK_EQUAL(tS, bS);
    BOOST_CHECK_EQUAL(bS, S);

    //wrong file paths
    string badPath = "/.txt....";
    BOOST_CHECK_THROW(t->writeToFile(badPath), std::ios_base::failure);
    BOOST_CHECK_THROW(t->writeToFileBinary(badPath), std::ios_base::failure);
    BOOST_CHECK_THROW(new Tree(badPath, true), std::ios_base::failure);
    BOOST_CHECK_THROW(new Tree(badPath, false), std::ios_base::failure);

    string badFile = ".badfile";
    ofstream ofs(badFile);
    ofs << "text";
    ofs.close();
    BOOST_CHECK_THROW(new Tree(badFile, true), std::ios_base::failure);
    BOOST_CHECK_THROW(new Tree(badFile, false), std::ios_base::failure);
    
    // Тест бинарного файла с неверным форматом
    string invalidBinFile = ".invalidbin";
    ofstream ofsBin(invalidBinFile, ios::binary);
    int invalidData = 12345;
    ofsBin.write((char*)&invalidData, sizeof(invalidData));
    ofsBin.close();
    BOOST_CHECK_THROW(new Tree(invalidBinFile, true), std::ios_base::failure);
    
    delete t;
}

BOOST_AUTO_TEST_SUITE_END()
