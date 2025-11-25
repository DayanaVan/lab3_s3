#define BOOST_TEST_MODULE StructuresTest
#include <boost/test/included/unit_test.hpp>

#include "../stack.hpp"
#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(StackTests)

BOOST_AUTO_TEST_CASE(Push_Pop_Test)
{
    Stack s;
    BOOST_CHECK_THROW(s.pop(), std::out_of_range);
    s.push("1");
    s.push("2");
    s.push("3");
    BOOST_CHECK_EQUAL(s.pop(), "3");
    BOOST_CHECK_EQUAL(s.pop(), "2");
    BOOST_CHECK_EQUAL(s.pop(), "1");
    BOOST_CHECK_THROW(s.pop(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ToString_Test)
{
    Stack s;
    BOOST_CHECK_EQUAL(s.toString(), "");
    s.push("1");
    s.push("2");
    s.push("3");
    BOOST_CHECK_EQUAL(s.toString(), "3 2 1");
}

BOOST_AUTO_TEST_CASE(IO_Test)
{
    string textTestFile = ".texttestfile";
    string binTestFile = ".bintestfile";
    //empty
    Stack s;
    BOOST_CHECK_NO_THROW(s.writeToFile(textTestFile));
    BOOST_CHECK_NO_THROW(s.writeToFileBinary(binTestFile));
    s = Stack(textTestFile, false);
    BOOST_CHECK_EQUAL(s.toString(), "");
    s = Stack(binTestFile, true);
    BOOST_CHECK_EQUAL(s.toString(), "");

    //not empty
    s.push("1");
    s.push("2");
    s.push("3");
    BOOST_CHECK_NO_THROW(s.writeToFile(textTestFile));
    BOOST_CHECK_NO_THROW(s.writeToFileBinary(binTestFile));

    Stack textStack(textTestFile, false);
    Stack binStack(binTestFile, true);
    BOOST_CHECK_EQUAL(textStack.toString(), binStack.toString());
    BOOST_CHECK_EQUAL(textStack.toString(), s.toString());

    //wrong file paths
    string badPath = "/.txt....";
    BOOST_CHECK_THROW(s.writeToFile(badPath), std::ios_base::failure);
    BOOST_CHECK_THROW(s.writeToFileBinary(badPath), std::ios_base::failure);
    BOOST_CHECK_THROW(new Stack(badPath, true), std::ios_base::failure);
    BOOST_CHECK_THROW(new Stack(badPath, false), std::ios_base::failure);

    string badFile = ".badfile";
    ofstream ofs(badFile);
    ofs << "text";
    ofs.close();
    BOOST_CHECK_THROW(new Stack(badFile, true), std::ios_base::failure);
}

BOOST_AUTO_TEST_SUITE_END()