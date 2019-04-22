//
// Created by reinaldo on 4/20/19.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Unittesting for OffObject"

#include <boost/test/unit_test.hpp>
#include "OffObject.h"


BOOST_AUTO_TEST_SUITE(test_offobject)
    BOOST_AUTO_TEST_CASE(test_load) {
        OffObject off;
        BOOST_CHECK(off.loadFile("./algo.off") == true);

    }
BOOST_AUTO_TEST_SUITE_END();
