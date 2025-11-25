#define BOOST_TEST_MODULE StructuresTest
#include <boost/test/included/unit_test.hpp>

#include "../array.hpp"
#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(Array_Tests)

BOOST_AUTO_TEST_CASE(Add_Get_Test)
{
    Array arr;
    BOOST_CHECK_EQUAL(arr.add("123"), true);
    BOOST_CHECK_EQUAL(arr.add("789"), true);
    BOOST_CHECK_EQUAL(arr.add("456", 1), true);
    BOOST_CHECK_EQUAL(arr.add("111", 3), true);
    BOOST_CHECK_EQUAL(arr.add("1", 5), false);

    BOOST_CHECK_EQUAL(arr.getSize(), 4);

    BOOST_CHECK_EQUAL(arr.get(0), "123");
    BOOST_CHECK_EQUAL(arr.get(1), "456");
    BOOST_CHECK_EQUAL(arr.get(2), "789");
    BOOST_CHECK_EQUAL(arr.get(3), "111");
    BOOST_CHECK_THROW(arr.get(4), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(Change_Test)
{
    Array arr;
    arr.add("123");
    BOOST_CHECK_EQUAL(arr.change(0, "1"), true);
    BOOST_CHECK_EQUAL(arr.get(0), "1");
    BOOST_CHECK_EQUAL(arr.change(1, "2"), false);
}

BOOST_AUTO_TEST_CASE(Remove_Test)
{
    Array arr;

    BOOST_CHECK_EQUAL(arr.add("123"), true);
    BOOST_CHECK_EQUAL(arr.add("456"), true);

    BOOST_CHECK_EQUAL(arr.remove(0), true);
    BOOST_CHECK_EQUAL(arr.getSize(), 1);
    BOOST_CHECK_EQUAL(arr.get(0), "456");
    BOOST_CHECK_EQUAL(arr.remove(1), false);
}

BOOST_AUTO_TEST_CASE(ToString_Test)
{
    Array arr;
    
    BOOST_CHECK_EQUAL(arr.add("123"), true);
    BOOST_CHECK_EQUAL(arr.add("456"), true);

    BOOST_CHECK_EQUAL(arr.toString(), "123 456");
}

BOOST_AUTO_TEST_CASE(IO_Test)
{
    string textTestFile = ".texttestfile";
    string binTestFile = ".bintestfile";
    //empty
    Array arr;
    BOOST_CHECK_NO_THROW(arr.writeToFile(textTestFile));
    BOOST_CHECK_NO_THROW(arr.writeToFileBinary(binTestFile));
    arr = Array(textTestFile, false);
    BOOST_CHECK_EQUAL(arr.getSize(), 0);
    arr = Array(binTestFile, true);
    BOOST_CHECK_EQUAL(arr.getSize(), 0);
    
    //not empty
    arr.add("123");
    arr.add("456");
    BOOST_CHECK_NO_THROW(arr.writeToFile(textTestFile));
    BOOST_CHECK_NO_THROW(arr.writeToFileBinary(binTestFile));

    Array textArr(textTestFile, false);
    Array binArr(binTestFile, true);
    BOOST_CHECK_EQUAL(textArr.get(0), binArr.get(0));
    BOOST_CHECK_EQUAL(textArr.get(1), binArr.get(1));
    BOOST_CHECK_EQUAL(textArr.get(0), arr.get(0));
    BOOST_CHECK_EQUAL(textArr.get(1), arr.get(1));

    //wrong file paths
    string badPath = "/.txt....";
    BOOST_CHECK_THROW(arr.writeToFile(badPath), std::ios_base::failure);
    BOOST_CHECK_THROW(arr.writeToFileBinary(badPath), std::ios_base::failure);
    BOOST_CHECK_THROW(new Array(badPath, true), std::ios_base::failure);
    BOOST_CHECK_THROW(new Array(badPath, false), std::ios_base::failure);

    string badFile = ".badfile";
    ofstream ofs(badFile);
    ofs << "text";
    ofs.close();
    BOOST_CHECK_THROW(new Array(badFile, true), std::ios_base::failure);
}

BOOST_AUTO_TEST_SUITE_END()