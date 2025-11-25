#define BOOST_TEST_MODULE StructuresTest
#include <boost/test/included/unit_test.hpp>

#include "../queue.hpp"
#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(QueueTests)

BOOST_AUTO_TEST_CASE(Push_Pop_Test)
{
    Queue q;
    BOOST_CHECK_THROW(q.pop(), std::out_of_range);
    q.push("1");
    q.push("2");
    q.push("3");
    BOOST_CHECK_EQUAL(q.pop(), "1");
    BOOST_CHECK_EQUAL(q.pop(), "2");
    BOOST_CHECK_EQUAL(q.pop(), "3");
    BOOST_CHECK_THROW(q.pop(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ToString_Test)
{
    Queue q;
    BOOST_CHECK_EQUAL(q.toString(), "");
    q.push("1");
    q.push("2");
    q.push("3");
    BOOST_CHECK_EQUAL(q.toString(), "1 2 3");
}

BOOST_AUTO_TEST_CASE(IO_Test)
{
    string textTestFile = ".texttestfile";
    string binTestFile = ".bintestfile";
    //empty
    Queue q;
    q.writeToFile(textTestFile);
    q.writeToFileBinary(binTestFile);
    q = Queue(textTestFile, false);
    BOOST_CHECK_EQUAL(q.toString(), "");
    q = Queue(binTestFile, true);
    BOOST_CHECK_EQUAL(q.toString(), "");
    
    //not empty
    q.push("1");
    q.push("2");
    q.push("3");
    q.writeToFile(textTestFile);
    q.writeToFileBinary(binTestFile);

    Queue textQueue(textTestFile, false);
    Queue binQueue(binTestFile, true);
    BOOST_CHECK_EQUAL(textQueue.toString(), binQueue.toString());
    BOOST_CHECK_EQUAL(textQueue.toString(), q.toString());

    //wrong file paths
    string badPath = "/.txt....";
    BOOST_CHECK_THROW(q.writeToFile(badPath), std::ios_base::failure);
    BOOST_CHECK_THROW(q.writeToFileBinary(badPath), std::ios_base::failure);
    BOOST_CHECK_THROW(new Queue(badPath, true), std::ios_base::failure);
    BOOST_CHECK_THROW(new Queue(badPath, false), std::ios_base::failure);

    string badFile = ".badfile";
    ofstream ofs(badFile);
    ofs << "text";
    ofs.close();
    BOOST_CHECK_THROW(new Queue(badFile, true), std::ios_base::failure);
}

BOOST_AUTO_TEST_SUITE_END()