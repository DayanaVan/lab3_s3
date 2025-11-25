#define BOOST_TEST_MODULE StructuresTest
#include <boost/test/included/unit_test.hpp>

#include "../forwardlist.hpp"
#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(ForwardListTests)

BOOST_AUTO_TEST_CASE(Add_Get_Test)
{
    ForwardList fl;
    fl.addHead("123");
    fl.addTail("789");
    BOOST_CHECK_EQUAL(fl.insert("456", 1), true);
    BOOST_CHECK_EQUAL(fl.insert("456", 4), false);
    BOOST_CHECK_EQUAL(fl.insert("456", 5), false);
    BOOST_CHECK_EQUAL(fl.head->key, "123");
    BOOST_CHECK_EQUAL(fl.head->next->key, "456");
    BOOST_CHECK_EQUAL(fl.head->next->next->key, "789");
    BOOST_CHECK_EQUAL(fl.insert("1", 0), true);
    BOOST_CHECK_EQUAL(fl.head->key, "1");
}

BOOST_AUTO_TEST_CASE(Remove_Test)
{
    ForwardList fl;
    fl.addHead("1");
    fl.addTail("2");
    fl.addTail("3");
    fl.addTail("4");
    BOOST_CHECK_EQUAL(fl.removeHead(), true);//1
    BOOST_CHECK_EQUAL(fl.removeTail(), true);//4
    BOOST_CHECK_EQUAL(fl.remove(2), false);
    BOOST_CHECK_EQUAL(fl.remove(4), false);
    BOOST_CHECK_EQUAL(fl.remove(1), true); //3
    BOOST_CHECK_EQUAL(fl.removeKey("2", 1), true); //
    BOOST_CHECK(fl.head == nullptr);

    fl.addTail("1");
    BOOST_CHECK_EQUAL(fl.remove(0), true);//1
    BOOST_CHECK_EQUAL(fl.remove(1), false);
    BOOST_CHECK_EQUAL(fl.removeTail(), false);
    BOOST_CHECK_EQUAL(fl.removeHead(), false);

    fl.addTail("1");
    fl.addTail("2");
    fl.addTail("1");
    fl.addTail("3");
    BOOST_CHECK_EQUAL(fl.removeKey("1", 3), false);
    BOOST_CHECK_EQUAL(fl.removeKey("1", 0), false);
    BOOST_CHECK_EQUAL(fl.removeKey("1", 2), true);
    BOOST_CHECK_EQUAL(fl.head->next->next->key, "3");
}

BOOST_AUTO_TEST_CASE(Find_Test)
{
    ForwardList fl;
    fl.addTail("1");
    fl.addTail("2");
    fl.addTail("1");
    BOOST_CHECK_EQUAL(fl.find("3", 1), nullptr);
    BOOST_CHECK_EQUAL(fl.find("3", 0), nullptr);
    BOOST_CHECK_EQUAL(fl.find("1", 1), fl.head);
    BOOST_CHECK(fl.find("1", 2) != nullptr);
    BOOST_CHECK_EQUAL(fl.find("1", 2)->next, nullptr);
}

BOOST_AUTO_TEST_CASE(Print_Test)
{
    ForwardList fl;
    BOOST_CHECK_EQUAL(fl.toStringFromHead(), "");
    BOOST_CHECK_EQUAL(fl.toStringFromTail(), "");
    fl.addTail("1");
    fl.addTail("2");
    fl.addTail("3");
    BOOST_CHECK_EQUAL(fl.toStringFromHead(), "1 2 3");
    BOOST_CHECK_EQUAL(fl.toStringFromTail(), "3 2 1");
}

BOOST_AUTO_TEST_CASE(IO_Test)
{
    string textTestFile = ".texttestfile";
    string binTestFile = ".bintestfile";
    //empty
    ForwardList fl;
    fl.writeToFile(textTestFile);
    fl.writeToFileBinary(binTestFile);
    fl = ForwardList(textTestFile, false);
    BOOST_CHECK_EQUAL(fl.head, nullptr);
    fl = ForwardList(binTestFile, true);
    BOOST_CHECK_EQUAL(fl.head, nullptr);
    
    //not empty
    fl.addTail("123");
    fl.addTail("456");
    fl.writeToFile(textTestFile);
    fl.writeToFileBinary(binTestFile);

    ForwardList textFL(textTestFile, false);
    ForwardList binFL(binTestFile, true);
    BOOST_CHECK(textFL.toStringFromHead() == binFL.toStringFromHead());
    BOOST_CHECK(fl.toStringFromHead() == textFL.toStringFromHead());

    //wrong file paths
    string badPath = "/.txt....";
    BOOST_CHECK_THROW(fl.writeToFile(badPath), std::ios_base::failure);
    BOOST_CHECK_THROW(fl.writeToFileBinary(badPath), std::ios_base::failure);
    BOOST_CHECK_THROW(new ForwardList(badPath, true), std::ios_base::failure);
    BOOST_CHECK_THROW(new ForwardList(badPath, false), std::ios_base::failure);

    string badFile = ".badfile";
    ofstream ofs(badFile);
    ofs << "text";
    ofs.close();
    BOOST_CHECK_THROW(new ForwardList(badFile, true), std::ios_base::failure);
}

BOOST_AUTO_TEST_SUITE_END()