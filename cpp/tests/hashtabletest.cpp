#define BOOST_TEST_MODULE StructuresTest
#include <boost/test/included/unit_test.hpp>

#include "../hashtabledouble.hpp"
#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(HashTableTests)

BOOST_AUTO_TEST_CASE(Add_Get_Test)
{
    HashTableDouble ht(7);
    ht.insert(-9, 1);
    ht.insert(-4, 2);
    ht.insert(9, 3);
    ht.insert(5, 4);
    ht.insert(6, 5);
    ht.insert(7, 6);
    ht.insert(7, 7);

    BOOST_CHECK_EQUAL(ht.contains(-9), true);
    BOOST_CHECK_EQUAL(ht.get(-9), 1);

    BOOST_CHECK_EQUAL(ht.contains(-4), true);
    BOOST_CHECK_EQUAL(ht.get(-4), 2);
    
    BOOST_CHECK_EQUAL(ht.contains(9), true);
    BOOST_CHECK_EQUAL(ht.get(9), 3);
    
    BOOST_CHECK_EQUAL(ht.contains(5), true);
    BOOST_CHECK_EQUAL(ht.get(5), 4);
    
    BOOST_CHECK_EQUAL(ht.contains(6), true);
    BOOST_CHECK_EQUAL(ht.get(6), 5);
    
    BOOST_CHECK_EQUAL(ht.contains(7), true);
    BOOST_CHECK_EQUAL(ht.get(7), 7);
    
    BOOST_CHECK_EQUAL(ht.contains(0), false);
    BOOST_CHECK_THROW(ht.get(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(Remove_Test)
{
    HashTableDouble ht(7);
    ht.insert(-9, 1);
    ht.insert(-4, 2);
    ht.insert(9, 3);
    ht.insert(5, 4);

    BOOST_CHECK_EQUAL(ht.remove(-9), true);
    BOOST_CHECK_EQUAL(ht.remove(-9), false);
    BOOST_CHECK_EQUAL(ht.remove(5), true);
    BOOST_CHECK_EQUAL(ht.remove(5), false);
    BOOST_CHECK_EQUAL(ht.remove(0), false);

    BOOST_CHECK_THROW(ht.get(-9), std::out_of_range);
    BOOST_CHECK_THROW(ht.get(5), std::out_of_range);
    BOOST_CHECK_EQUAL(ht.contains(-4), true);
    BOOST_CHECK_EQUAL(ht.contains(9), true);
}

BOOST_AUTO_TEST_CASE(ToString_Test)
{
    HashTableDouble ht(7);
    ht.insert(-9, 1);
    ht.insert(-4, 2);
    ht.insert(9, 3);
    ht.insert(5, 4);
    BOOST_CHECK_EQUAL(ht.toString(), "9 : 3\n"
                                     "-9 : 1\n"
                                     "-4 : 2\n"
                                     "5 : 4\n");
}

BOOST_AUTO_TEST_CASE(IO_Test)
{
    string textTestFile = ".texttestfile";
    string binTestFile = ".bintestfile";
    //empty
    HashTableDouble *ht = new HashTableDouble(7);
    BOOST_CHECK_NO_THROW(ht->writeToFile(textTestFile));
    BOOST_CHECK_NO_THROW(ht->writeToFileBinary(binTestFile));
    delete ht;
    ht = new HashTableDouble(textTestFile, false);
    BOOST_CHECK_EQUAL(ht->toString(), "");
    delete ht;
    ht = new HashTableDouble(binTestFile, true);
    BOOST_CHECK_EQUAL(ht->toString(), "");
    
    //not empty
    ht->insert(1, 1);
    ht->insert(2, 2);
    ht->insert(3, 3);
    ht->insert(4, 4);
    BOOST_CHECK_NO_THROW(ht->writeToFile(textTestFile));
    BOOST_CHECK_NO_THROW(ht->writeToFileBinary(binTestFile));

    HashTableDouble textHT(textTestFile, false);
    HashTableDouble binHT(binTestFile, true);
    BOOST_CHECK_EQUAL(textHT.toString(), binHT.toString());
    BOOST_CHECK_EQUAL(binHT.toString(), ht->toString());

    //wrong file paths
    string badPath = "/.txt....";
    BOOST_CHECK_THROW(ht->writeToFile(badPath), std::ios_base::failure);
    BOOST_CHECK_THROW(ht->writeToFileBinary(badPath), std::ios_base::failure);
    BOOST_CHECK_THROW(new HashTableDouble(badPath, true), std::ios_base::failure);
    BOOST_CHECK_THROW(new HashTableDouble(badPath, false), std::ios_base::failure);

    string badFile = ".badfile";
    ofstream ofs(badFile);
    ofs << "text";
    ofs.close();
    BOOST_CHECK_THROW(new HashTableDouble(badFile, true), std::ios_base::failure);
    BOOST_CHECK_THROW(new HashTableDouble(badFile, false), std::ios_base::failure);
}

BOOST_AUTO_TEST_SUITE_END()