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

 using namespace std;

///////////////////////////////////////////////////////
// TESTING
///////////////////////////////////////////////////////

/**
* PART 2 TESTS
* \brief Tests Tree constuctors, Node constructors, and size()
*/
bool part2Test() {
    TestingLogger log("part2Test");

    TreeStringSet tree1{treetype::ROOT};
    affirm(tree1.size() == 0);

    TreeStringSet tree2{treetype::LEAF};
    affirm(tree2.size() == 0);

    TreeStringSet tree3{treetype::RANDOMIZED};
    affirm(tree3.size() == 0);

    TreeStringSet tree4{treetype::ROOT, 3};
    affirm(tree4.size() == 0);

    TreeStringSet tree5{treetype::LEAF, 42};
    affirm(tree5.size() == 0);

    TreeStringSet tree6{treetype::RANDOMIZED, 27};
    affirm(tree6.size() == 0);

    return log.summarize();
}

/**
* PART 3 TESTS
* \brief Tests insert (LEAF), and exists
*/
bool part3Test() {
    TestingLogger log("part3Test");
    
    TreeStringSet tree1{treetype::LEAF};

    affirm(!tree1.exists("hello"));

    tree1.insert("hello");
    affirm(tree1.exists("hello"));
    affirm(tree1.size() == 1);

    tree1.insert("it's me");
    affirm(tree1.exists("it's me"));
    affirm(tree1.size() == 2);

    tree1.insert("bye");
    affirm(tree1.exists("bye"));
    affirm(tree1.size() == 3);

    tree1.insert("hello");
    affirm(tree1.exists("hello"));
    affirm(tree1.size() == 3);

    affirm(!tree1.exists("I was wondering if after all these years"));

    return log.summarize();
}

/**
* PART 4 TESTS
* \brief Tests the print functionality
*/
bool part4Test() {
    TestingLogger log("part4Test");
    
    TreeStringSet tree{LEAF};
    string expected = "-";
    stringstream ss1;
    ss1 << tree;
    affirm(ss1.str() == expected);

    tree.insert("4");
    expected = "1:(-, 4, -)";
    stringstream ss2;
    ss2 << tree;
    affirm(ss2.str() == expected);

    tree.insert("2");
    expected = "2:(1:(-, 2, -), 4, -)";
    stringstream ss3;
    ss3 << tree;
    affirm(ss3.str() == expected);

    tree.insert("6");
    expected = "3:(1:(-, 2, -), 4, 1:(-, 6, -))";
    stringstream ss4;
    ss4 << tree;
    affirm(ss4.str() == expected);

    tree.insert("5");
    expected = "4:(1:(-, 2, -), 4, 2:(1:(-, 5, -), 6, -))";
    stringstream ss5;
    ss5 << tree;
    affirm(ss5.str() == expected);

    tree.insert("3");
    expected = "5:(2:(-, 2, 1:(-, 3, -)), 4, 2:(1:(-, 5, -), 6, -))";
    stringstream ss6;
    ss6 << tree;
    affirm(ss6.str() == expected);

    return log.summarize();
}

/**
 * Test the tree string set!!
 */
int main() {
    TestingLogger alltests("All tests");

    affirm(true);

    affirm(part2Test());

    affirm(part3Test());

    affirm(part4Test());

    // Print a summary of all the affirmations and exit program.

    if (alltests.summarize(true)) {
        return 0; // Exit code 0 == success!!
    } else {
        return 2; //Arbitrarily chosen exit code of 2 means tests failed
    }
}