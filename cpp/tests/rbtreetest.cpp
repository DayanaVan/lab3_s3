#define BOOST_TEST_MODULE StructuresTest
#include <boost/test/included/unit_test.hpp>

#include "../rbtree.hpp"
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

    BOOST_CHECK_EQUAL(t.search(0), t.nil);
    BOOST_CHECK_EQUAL(t.search(1)->key, 1);
    BOOST_CHECK_EQUAL(t.search(2)->key, 2);
    BOOST_CHECK_EQUAL(t.search(3)->key, 3);
    BOOST_CHECK_EQUAL(t.search(4)->key, 4);
    BOOST_CHECK_EQUAL(t.search(5)->key, 5);
    BOOST_CHECK_EQUAL(t.search(10)->key, 10);
    BOOST_CHECK_EQUAL(t.search(8)->key, 8);
    BOOST_CHECK_EQUAL(t.search(7)->key ,7);

    std::string a = "";
    t.BFS(a);
    BOOST_CHECK_EQUAL(a, "4_B 2_R 8_R 1_B 3_B 5_B 10_B 7_R ");

    Tree t2;
    t2.add(5);
    t2.add(4);
    t2.add(3);
    t2.add(2);
    t2.add(1);
    t2.add(-5);
    t2.add(-3);
    t2.add(-2);

    BOOST_CHECK_EQUAL(t2.search(0), t2.nil);
    BOOST_CHECK_EQUAL(t2.search(5)->key, 5);
    BOOST_CHECK_EQUAL(t2.search(4)->key, 4);
    BOOST_CHECK_EQUAL(t2.search(3)->key, 3);
    BOOST_CHECK_EQUAL(t2.search(2)->key, 2);
    BOOST_CHECK_EQUAL(t2.search(1)->key, 1);
    BOOST_CHECK_EQUAL(t2.search(-5)->key, -5);
    BOOST_CHECK_EQUAL(t2.search(-3)->key, -3);
    BOOST_CHECK_EQUAL(t2.search(-2)->key, -2);

    t2.BFS(a);
    BOOST_CHECK_EQUAL(a, "2_B -3_R 4_R -5_B 1_B 3_B 5_B -2_R ");
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

    t.remove(t.search(2));
    t.remove(t.search(8));
    t.remove(t.search(5));
    t.remove(t.search(10));
    t.remove(t.search(4));
    t.remove(t.search(3));
    t.remove(t.search(1));
    t.remove(t.nil);

    BOOST_CHECK_EQUAL(t.root, t.nil);

    t.add(5);
    t.add(4);
    t.add(3);
    t.add(2);
    t.add(1);
    t.add(-5);
    t.add(-3);

    t.remove(t.search(3));
    t.remove(t.search(-3));
    t.remove(t.search(5));
    t.remove(t.search(-5));
    t.remove(t.search(2));
    t.remove(t.search(1));
    t.remove(t.search(4));

    BOOST_CHECK_EQUAL(t.root, t.nil);
}

BOOST_AUTO_TEST_CASE(Print_Test)
{
    
    Tree t;
    t.add(1);
    t.add(2);
    t.add(3);
    t.add(4);
    t.add(5);

    BOOST_CHECK_EQUAL(t.print(), "BFS: 2_B 1_B 4_B 3_R 5_R \n"
                                 "DFS in order: 1_B 2_B 3_R 4_B 5_R \n"
                                 "DFS post order: 1_B 3_R 5_R 4_B 2_B \n"
                                 "DFS pre order: 2_B 1_B 4_B 3_R 5_R \n");
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
}

BOOST_AUTO_TEST_SUITE_END()