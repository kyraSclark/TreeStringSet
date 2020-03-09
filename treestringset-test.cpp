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
#include "treestringset.hpp"

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

    affirm(!(tree1.exists("hello")));

    tree1.insert("hello");
    affirm(tree1.exists("hello"));
    affirm(tree1.size() == 1);

    tree1.insert("it's me");
    affirm(tree1.exists("it's me"));
    affirm(tree1.size() == 2);

    tree1.insert("bye");
    affirm(tree1.exists("bye"));
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
* PART 5 TESTS
* \brief Tests the Iterator functionality
*/
bool part5Test() {
    TestingLogger log("part5Test");

    TreeStringSet tree{LEAF};

    // end() calls default constructor
    TreeStringSet::iterator it1 = tree.end();
    TreeStringSet::iterator it2 = tree.end();
    affirm(it1 == it2);

    // begin() calls parameterized constructor
    tree.insert("hello");
    TreeStringSet::iterator it3 = tree.begin();
    TreeStringSet::iterator it4 = tree.begin();
    affirm(it3 == it4);
    affirm(it3 != it1);
    affirm(*it3 == "hello");

    it1 = it3;
    affirm(it1 == it3);
    affirm(it1 != it2);

    TreeStringSet::iterator it5 = it3;
    affirm(it5 == it3);

    ++it1;
    affirm(it1 == it2);

    tree.insert("bye");
    ++it3;
    affirm(it3 != it4);
    affirm(*it3 == "bye");

    ++it4;
    affirm(it3 == it4);

    ++it3;
    affirm(it3 == it2);


    TreeStringSet tree2{LEAF};
    tree2.insert("d");
    tree2.insert("b");
    tree2.insert("a");
    tree2.insert("c");
    tree2.insert("f");
    tree2.insert("e");
    tree2.insert("g");

    TreeStringSet::iterator it6 = tree2.begin();
    affirm(*it6 == "d");
    ++it6;
    affirm(*it6 == "b");
    ++it6;
    affirm(*it6 == "f");
    ++it6;
    affirm(*it6 == "a");
    ++it6;
    affirm(*it6 == "c");
    ++it6;
    affirm(*it6 == "e");
    ++it6;
    affirm(*it6 == "g");
    ++it6;
    affirm(it6 == tree2.end());

    return log.summarize();
}

/**
* PART 6 TESTS
* \brief Tests the operator== and operator!= functionality
*/
bool part6Test() {
    TestingLogger log("part6Test");

    TreeStringSet tree1{LEAF};
    TreeStringSet tree2{LEAF};

    affirm(tree1 == tree2);
    tree1.insert("Never");

    affirm(tree1 != tree2);
    tree2.insert("Never");

    affirm(tree1 == tree2);

    tree1.insert("gonna");
    tree2.insert("gonna");
    affirm(tree1 == tree2);

    tree1.insert("give");
    tree2.insert("a");

    // We think this is odd behavior,
    //  although, this is the output we expect
    TreeStringSet tree3{LEAF};
    tree3.insert("give");
    tree3.insert("gonna");
    tree3.insert("Never");
    affirm(tree3 == tree1);

    return log.summarize();
}

/**
* PART 7 TESTS
* \brief Tests the showStatistics, which will also test
*           height, heightHelper, averageDepth, totalDepth
*/
bool part7Test() {
    TestingLogger log("part7Test");

    TreeStringSet tree1{LEAF};
    stringstream ss;
    tree1.showStatistics(ss);
    affirm(tree1.size() == 0);
    affirm(tree1.height() == -1);
    double expectedDepth = 0.0;
    affirm(tree1.averageDepth() == expectedDepth);

    tree1.insert("a");
    affirm(tree1.size() == 1);
    affirm(tree1.height() == 0);
    // affirm(tree1.averageDepth() == expectedDepth);

    // Create a stick
    tree1.insert("b");
    tree1.insert("c");
    tree1.insert("d");
    tree1.insert("e");

    affirm(tree1.size() == 5);
    affirm(tree1.height() == 4);
    // double expectedDepth3 = 10 / 5;
    // affirm(tree1.averageDepth() == expectedDepth3);

    // Create an (almost) balanced tree
    TreeStringSet tree2{LEAF};
    tree2.insert("d");
    tree2.insert("b");
    tree2.insert("a");
    tree2.insert("c");
    tree2.insert("f");

    affirm(tree2.size() == 5);
    affirm(tree2.height() == 2);
    // double expectedDepth4 = 6/5;
    // affirm(tree2.averageDepth() == expectedDepth4);

    // Make it balanced
    tree2.insert("e");
    tree2.insert("g");

    affirm(tree2.size() == 7);
    affirm(tree2.height() == 2);
    // double expectedDepth5 = 10 / 7;
    // affirm(tree2.averageDepth() == expectedDepth5);

    return log.summarize();
}

/**
* PART 8 TESTS
* \brief Tests insert (for root trees)
*/
bool part8Test() {
    TestingLogger log("part8Test");

    TreeStringSet tree{ROOT};

    tree.insert("d");
    string expected = "1:(-, d, -)";
    stringstream ss1;
    ss1 << tree;
    affirm(ss1.str() == expected);
    affirm(tree.height() == 0);

    tree.insert("b");
    expected = "2:(-, b, 1:(-, d, -))";
    stringstream ss2;
    ss2 << tree;
    affirm(ss2.str() == expected);

    tree.insert("c");
    expected = "3:(1:(-, b, -), c, 1:(-, d, -))";
    stringstream ss3;
    ss3 << tree;
    affirm(ss3.str() == expected);

    tree.insert("f");
    expected = "4:(3:(1:(-, b, -), c, 1:(-, d, -)), f, -)";
    stringstream ss4;
    ss4 << tree;
    affirm(ss4.str() == expected);

    TreeStringSet tree2{ROOT};
    tree2.insert("d");
    tree2.insert("b");
    tree2.insert("c");

    tree2.insert("a");
    expected = "4:(-, a, 3:(1:(-, b, -), c, 1:(-, d, -)))";
    stringstream ss5;
    ss5 << tree2;
    affirm(ss5.str() == expected);

    return log.summarize();
}

/**
* PART 9 TESTS
* \brief Tests insert (for randomized trees)
*/
bool part9Test() {
    TestingLogger log("part9Test");

    TreeStringSet tree{RANDOMIZED};

    tree.insert("d");
    affirm(tree.size() == 1);
    affirm(tree.exists("d"));

    tree.insert("b");
    affirm(tree.size() == 2);
    affirm(tree.exists("b"));

    tree.insert("c");
    affirm(tree.size() == 3);
    affirm(tree.exists("c"));

    tree.insert("f");
    affirm(tree.size() == 4);
    affirm(tree.exists("f"));

    tree.insert("e");
    affirm(tree.size() == 5);
    affirm(tree.exists("e"));

    // Run this test several times to see that the trees are randomized
    // cout << tree << endl;

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

    affirm(part5Test());

    affirm(part6Test());

    affirm(part7Test());

    affirm(part8Test());

    affirm(part9Test());

    // Print a summary of all the affirmations and exit program.

    if (alltests.summarize(true)) {
        return 0;  // Exit code 0 == success!!
    } else {
        return 2;  // Arbitrarily chosen exit code of 2 means tests failed
    }
}
