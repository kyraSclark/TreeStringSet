/**
* treestringset.hpp
* A binary search tree of strings
*
*/


#ifndef TREESTRINGSET_HPP_INCLUDED
#define TREESTRINGSET_HPP_INCLUDED

#include <cs70/randuint32.hpp>
#include <iostream>
#include <utility>
#include <string>
#include <queue>

using namespace std;

enum treetype { LEAF, ROOT, RANDOMIZED };

/**
* TreeStringSet
*
* a binary search tree of many Node objects with string values
*
*/
class TreeStringSet {
    friend ostream& operator<<(ostream& os, const TreeStringSet& t);
 private:
    /**
    * Node
    *
    * A Node is part of the tree,
    *   hold a string value and the size of the subtree below it,
    *   as well as pointers to its children nodes
    */
    struct Node {

        // Data Members
        string value_;
        Node* left_;
        Node* right_;
        size_t size_;

        Node(string value);
        ~Node();
        // Disable default constructor, copy constructor,
        //  and assignment operator
        Node() = delete;
        Node& operator=(const Node& rhs) = delete;
        Node(const Node& other) = delete;

        /**
        * print()
        * \brief prints a tree rooted at a node
        * \param o an ostream reference
        * \returns an ostream reference
        */
        ostream& print(ostream& o) const;

        /**
        * heightHelper
        * \brief a helper function for height (allows recursion),
        *        looks through the subtrees to calculate max height
        * \returns the height of the node it is called on
        */
        int heightHelper() const;

        /**
        * totalDepth
        * \brief a helper function for averageDepth (allows recursion),
        *        calculates the total depth of each node's, starting at the node it's called on
        * \param level is the depth of the node the function is called on
        * \returns the total depth of the subtree with the root it's called on
        */
        int totalDepth(int level) const;
    };

    // Data Members
    Node* root_;
    treetype type_;
    size_t size_;
    RandUInt32 rand;

    // Member Functions

    /**
    * insertAtLeafNode
    * \brief inserts a new Node to the tree in a leaf position
    * \param root a pointer to the root of the tree to be inserted into
    * \param value a reference to the string value of our new Node
    */
    void insertAtLeafNode(Node*& root, const string& value);

    /**
    * insertAtRoot
    * \brief inserts a new Node to the tree in the root position
    * \param root a pointer to the root of the tree to be inserted into
    * \param value a reference to the string value of our new Node
    */
    void insertAtRoot(Node*& root, const string& value);

    /**
    * insertAtRandom
    * \brief inserts a new Node to the tree in a random valid position
    * \param root a pointer to the root of the tree to be inserted into
    * \param value a reference to the string value of our new Node
    */
    void insertAtRandom(Node*& root, const string& value);

    /**
    * rotateRight
    * \brief a helper function for insertAtRoot, rotates the tree right about the root
    * \param root a pointer to the root of the tree to rotate around
    */
    void rotateRight(Node* root);

    /**
    * rotateLeft
    * \brief a helper function for insertAtRoot, rotates the tree left about the root
    * \param root a pointer to the root of the tree to rotate around
    */
    void rotateLeft(Node* root);

    /**
    * existsHelper
    * \brief a helper function for exists (allows recursion),
    *        looks through the tree to find if the value is present
    * \param root a pointer to the root of the tree to search in
    * \param value the string that we are looking for
    */
    bool existsHelper(Node* root, const string& value) const;

    /**
    * Iterator 
    * an STL-style iterator for TreeStringSet 
    */
    class Iterator {
     private:
        friend class TreeStringSet;

        // Data Members
        Node* current_;
        std::queue<Node*> pending_;

     public:
        // Makes Iterator well-behaved
        using value_type = string;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::forward_iterator_tag;

        // Provide usual operations for a forward iterator

        Iterator();
        Iterator(Node* current);
        ~Iterator();
        Iterator& operator=(const Iterator& other) = default;

        /**
        * operator==
        * \brief checks if two iterators point to the same node
        * \param rhs refers to the other Iterator we are checking
        * \returns a boolean true if equal; else false
        */
        bool operator==(const Iterator& rhs) const;

        /**
        * operator!=
        * \brief checks if two iterators do not point to the same node
        * \param rhs refers to the other Iterator we are checking
        * \returns a boolean false if equal; else true
        */
        bool operator!=(const Iterator& rhs) const;

        /**
        * operator*
        * \brief returns a reference to the value stored in current
        * \param rhs refers to the other Iterator we are checking
        * \returns a string reference to the value we have stored in current
        */
        reference operator*() const;

        /**
        * operator->
        * \brief returns a pointer to the value stored in current
        * \param rhs refers to the other Iterator we are checking
        * \returns a string pointer to the value we have stored in current
        */
        pointer operator->() const;

        /**
        * operator++
        * \brief increments our iterator using the queue we have stored.
        * \returns a reference to our iterator
        */
        Iterator& operator++();
    };

 public:
    // Provide our own destructor and parametrized constructors
    TreeStringSet(treetype type);
    TreeStringSet(treetype type, size_t seed);
    ~TreeStringSet();

    // Delete the default, copy constructor, and assignment operator.
    TreeStringSet() = delete;
    TreeStringSet(const TreeStringSet& other) = delete;
    TreeStringSet& operator=(const TreeStringSet& rhs) = delete;

    /**
    * operator==
    * \brief checks if two trees have precisely the same values
    * \param rhs refers to the other tree we are checking
    * \returns a boolean true if equal; else false
    */
    bool operator==(const TreeStringSet& rhs) const;

    /**
    * operator!=
    * \brief checks if two trees don't have precisely the same values
    * \param rhs refers to the other tree we are checking
    * \returns a boolean false if equal; else true
    */
    bool operator!=(const TreeStringSet& rhs) const;

    /**
    * size()
    * \brief returns the number of nodes in the tree
    * \returns a size_t size of the tree
    */
    size_t size() const;

    /**
    * consistent()
    * \brief checks if the size and the root are consistent
    * \returns a boolean reflecting the above
    */
    bool consistent() const;

    /**
    * insert()
    * \brief inserts a node containing a string value, dependent on the tree's type
    * \param value a string reference that will be added to our tree.
    */
    void insert(const string& value);

    /**
    * exists()
    * \brief returns true if there is a node containing value in our tree
    * \param value the string we're searching for
    * \returns true if the string exists in our tree, else false
    */
    bool exists(const string& value) const;

    /**
    * print()
    * \brief prints a tree
    * \param o an ostream reference
    * \returns an ostream reference
    */
    ostream& print(ostream& o) const;

    /**
    * height()
    * \brief returns the height of the tree using a helper function
    * \returns the height of the tree
    */
    int height() const;

    /**
    * averageDepth()
    * \brief returns the average depth of nodes in the tree using a helper function
    * \returns the average depth of nodes in the tree
    */
    double averageDepth() const;

    /**
    * averageDepth()
    * \brief displays the height, size, and the average depth of the tree.
    */
    void showStats() const;

    // allow clients to iterate over the contents of a tree
    using iterator = Iterator;

    /**
    * begin()
    * \brief creates an iterator pointing to the first element of the tree
    * \returns an iterator pointing to the first element of the tree
    */
    iterator begin() const;

    /**
    * end()
    * \brief creates an iterator pointing past the last element of a tree
    * \returns the default iterator
    */
    iterator end() const;
};

/**
* operator<<()
* \brief adds the representation of a tree to the ostream
* \param o an ostream reference
* \param t the tree to add
* \returns an ostream reference
*/
ostream& operator<<(ostream& o, const TreeStringSet& t);

#endif
