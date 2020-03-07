/**
 * \file treestringset-test.cpp
 * \authors Ellie and Kyra! :)
 * \brief The program unit tests the TreeStringSet class
 *
 * \details part of the treeStringSet assigment
 */

 #include <iostream>
 #include <string>
 #include <queue>
 #include <cs70/testinglogger.hpp>
 #include "treeStringSet.hpp"

///////////////////////////////////////////////////////
// TESTING
///////////////////////////////////////////////////////

/**
* PART 1 TESTS
* \brief Tests Tree constuctors, Node constructors, and size()
*/
bool part1Test() {
    TreeStringSet tree1{ROOT};
    affirm(tree1.size() == 0);

    TreeStringSet tree2{LEAF};
    affirm(tree2.size() == 0);

    TreeStringSet tree3{RANDOM};
    affirm(tree3.size() == 0);

    TreeStringSet tree4{ROOT, 3};
    affirm(tree4.size() == 0);

    TreeStringSet tree5{LEAF, 42};
    affirm(tree5size() == 0);

    TreeStringSet tree6{RANDOM, 27};
    affirm(tree6.size() == 0);
}

/**
 * Test the tree string set!!
 */
int main() {
    TestingLogger alltests("All tests");

    affirm(true);

    // Print a summary of all the affirmations and exit program.

    if (alltests.summarize(true)) {
        return 0; // Exit code 0 == success!!
    } else {
        return 2; //Arbitrarily chosen exit code of 2 means tests failed
    }
}