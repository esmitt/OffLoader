//
// Created by reinaldo on 4/20/19.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Unittesting for OffObject"

#include <boost/test/unit_test.hpp>
#include "OffObject.h"
#include <iostream>


BOOST_AUTO_TEST_SUITE(test_offobject)
    BOOST_AUTO_TEST_CASE(test_load) {
	std::cout << "Test1 \n";	
        OffObject off;
        BOOST_CHECK(off.loadFile("./cube.off") == true);
    }
    BOOST_AUTO_TEST_CASE(test_load_no_existing_file) {
	std::cout << "Test2 \n";	
        OffObject off;
        BOOST_CHECK(off.loadFile("./no_existing_file.off") == false);
    }
BOOST_AUTO_TEST_SUITE_END();
