#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE arrayTemplateClassTest

#include <boost/test/unit_test.hpp>

#include <iostream>

#include "../array_template_classes.h"

BOOST_AUTO_TEST_CASE(test_fill) {
    int testIntArr[5] {0};

    Array<int, 5> intArr;
    intArr.fill(0);

    std::cout << intArr[0] << " == " << testIntArr[0] <<std::endl;
    BOOST_CHECK(intArr[0] == testIntArr[0]);
}

BOOST_AUTO_TEST_CASE(test_wrong) 
{
    int a = 5;
    BOOST_TEST(a == 5);
}

BOOST_AUTO_TEST_CASE(test_set_fill) {
    int testIntArr[5] {0};
    testIntArr[3] = 10;

    Array<int, 5> intArr {0};
    intArr.set_fill(10, 3);

    std::cout << intArr[3] << " == " << testIntArr[3] << std::endl;
    BOOST_CHECK(intArr[3] == testIntArr[3]);
}

BOOST_AUTO_TEST_CASE(test_get_size) {
    int testIntArr[5] {0};
    int sizeOfTestIntArr = std::end(testIntArr) - std::begin(testIntArr);
   
    Array<int, 5> intArr {0};

    std::cout << intArr.get_size() << " == " << sizeOfTestIntArr << std::endl;
    BOOST_CHECK_EQUAL(intArr.get_size(), sizeOfTestIntArr);
}

BOOST_AUTO_TEST_CASE(test_incorrect) 
{
    int a = 5;
    BOOST_TEST(a == 5);
}

BOOST_AUTO_TEST_CASE(blah_blah_blah) 
{
    int a = 5;
    BOOST_TEST(a == 5);
}
